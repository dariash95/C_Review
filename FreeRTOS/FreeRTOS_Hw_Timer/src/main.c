
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "driver/gpio.h"
#include "driver/gptimer.h"

#define TASK_PRINT_STACK    4096
#define TASK_PRINT_PRIO     3

#define LED                     GPIO_NUM_12
#define LED_MASK                (1 << LED)

volatile bool led_state;

volatile int isr_count;
static portMUX_TYPE spinlock = portMUX_INITIALIZER_UNLOCKED;

bool timer_on_alarm_cb(gptimer_handle_t timer, const gptimer_alarm_event_data_t *edata, void *user_ctx){

    portENTER_CRITICAL_ISR(&spinlock);
    isr_count++;
    portEXIT_CRITICAL_ISR(&spinlock);
       
    return false;
}

void print_task(void* params){

    while (1){
        while (isr_count >0){
            printf("%d\n", isr_count);

            portENTER_CRITICAL(&spinlock);
            isr_count--;
            portEXIT_CRITICAL(&spinlock);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main() {
    
   isr_count = 0;

    xTaskCreatePinnedToCore(print_task, "Print", TASK_PRINT_STACK, NULL, TASK_PRINT_PRIO, NULL, tskNO_AFFINITY);

    gptimer_handle_t gptimer = NULL;

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

    ESP_ERROR_CHECK(gptimer_start(gptimer));
}