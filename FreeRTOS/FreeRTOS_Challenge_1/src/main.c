/*
This project samples an analog input at 10 Hz using a hardware timer interrupt, 
hands each sample off to a task through a FreeRTOS queue, and computes a rolling average
every 10 samples (i.e., once per second). A second task provides a simple serial console: 
it echoes any typed line, and prints the current average when the user types avg.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/adc.h"
#include "esp_adc_cal.h"
#include "driver/gptimer.h"

#define TASK_A_AVG_STACK        4096
#define TASK_A_AVG_PRIO         3

#define TASK_B_CONSOLE_STACK    4096
#define TASK_B_CONSOLE_PRIO     5

#define DEFAULT_VREF    1100

// ADC variables
static esp_adc_cal_characteristics_t *adc_chars;
static const adc_channel_t channel = ADC_CHANNEL_6;     //GPIO34 if ADC1, GPIO14 if ADC2
static const adc_bits_width_t width = ADC_WIDTH_BIT_12;

static const adc_atten_t atten = ADC_ATTEN_DB_0;
static const adc_unit_t unit = ADC_UNIT_1;

// Timer variables
static gptimer_handle_t gptimer = NULL;

// Queue
QueueHandle_t adc_queue = NULL;
#define QUEUE_ELEMENTS  10

float adc_average;

static portMUX_TYPE spinlock = portMUX_INITIALIZER_UNLOCKED;

bool timer_on_alarm_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx);

static void check_efuse(void) {
    //Check if TP is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_TP) == ESP_OK) {
        printf("eFuse Two Point: Supported\n");
    } else {
        printf("eFuse Two Point: NOT supported\n");
    }

    //Check Vref is burned into eFuse
    if (esp_adc_cal_check_efuse(ESP_ADC_CAL_VAL_EFUSE_VREF) == ESP_OK) {
        printf("eFuse Vref: Supported\n");
    } else {
        printf("eFuse Vref: NOT supported\n");
    }
}

void config_adc(void){
    
    //Check if Two Point or Vref are burned into eFuse
    check_efuse();

    //Configure ADC
    adc1_config_width(width);
    adc1_config_channel_atten(channel, atten);
    
    //Characterize ADC
    adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(unit, atten, width, DEFAULT_VREF, adc_chars);
}

void config_timer(void){

    gptimer_config_t timer_conf = {
        .clk_src = GPTIMER_CLK_SRC_DEFAULT,
        .direction = GPTIMER_COUNT_UP,
        .resolution_hz = 1000000
    };

    ESP_ERROR_CHECK(gptimer_new_timer(&timer_conf, &gptimer));

    gptimer_alarm_config_t alarm_config = {
        .reload_count = 0,
        .alarm_count = 100000,
        .flags.auto_reload_on_alarm = true
    };

    ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));

    gptimer_event_callbacks_t cbs = {
        .on_alarm = timer_on_alarm_cb,
    };

    ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, NULL));

    ESP_ERROR_CHECK(gptimer_enable(gptimer));

}

bool timer_on_alarm_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx){
    
    BaseType_t task_woken = pdFALSE;

    uint32_t adc_reading = adc1_get_raw((adc1_channel_t)channel);

    xQueueSendFromISR(adc_queue, (void*)&adc_reading, &task_woken);

    return task_woken;
}

void task_a_avg(void *params){

    uint32_t adc_value_rcv;
    uint32_t accum = 0;
    int i;

    while (1){
        for ( i= 0; i < QUEUE_ELEMENTS; i++){
            xQueueReceive(adc_queue, (void*)&adc_value_rcv, portMAX_DELAY);
            accum += adc_value_rcv; 
        }

        taskENTER_CRITICAL(&spinlock);
        adc_average = accum/ QUEUE_ELEMENTS;
        taskEXIT_CRITICAL(&spinlock);

        accum = 0;
    }
}

void task_b_console(void *params){

    char buffer[128];
    float aux_avg;

    while (1){
        if (fgets(buffer, sizeof(buffer), stdin) != NULL){

            // Handle terminators
            size_t terminator = strcspn(buffer, "\r");
            buffer[terminator] = '\0';
            terminator = strcspn(buffer, "\n");
            buffer[terminator] = '\0';

            if (strlen(buffer) > 0){
                
                if (strcmp(buffer, "avg") == 0){
                    taskENTER_CRITICAL(&spinlock);
                    aux_avg = adc_average;
                    taskEXIT_CRITICAL(&spinlock);

                    printf("Average : %.2f\n", aux_avg);
                } else {
                    printf("Echo: %s\n", buffer);
                }
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void app_main() {

    config_adc();
    config_timer();

    adc_queue = xQueueCreate(QUEUE_ELEMENTS, sizeof(uint32_t));
    
    if (adc_queue == NULL){
        printf("Problem creating queue\n");
    }

    xTaskCreatePinnedToCore(task_a_avg, "AvgTask", TASK_A_AVG_STACK, NULL, TASK_A_AVG_PRIO, NULL, tskNO_AFFINITY);
    xTaskCreatePinnedToCore(task_b_console, "ConsoleTask", TASK_B_CONSOLE_STACK, NULL, TASK_B_CONSOLE_PRIO, NULL, tskNO_AFFINITY);

    ESP_ERROR_CHECK(gptimer_start(gptimer));

}