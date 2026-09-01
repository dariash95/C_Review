#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/gpio.h"

#define TASK_A_CONSOLE_STACK    4096
#define TASK_A_CONSOLE_PRIO     3

#define TASK_B_LED_STACK        2048
#define TASK_B_LED_PRIO         3

#define LED                     GPIO_NUM_12
#define LED_MASK                (1 << LED)

#define QUEUE_DELAYS_LEN        3
#define QUEUE_MSG_LEN           10

static QueueHandle_t q_delays;
static QueueHandle_t q_msgs;

typedef struct {
    char payload[32];
}StringToQueue_t;

void console_task (void* params) {

    char buffer[20];
    int delay = 0;

    printf("Enter the delay in miliseconds: \n");

    while (1){

        if (fgets(buffer, sizeof(buffer), stdin) != NULL){

            // Handle terminators
            size_t terminator = strcspn(buffer, "\n");
            buffer[terminator] = '\0';

            terminator = strcspn(buffer, "\r");
            buffer[terminator] = '\0';

            if (strlen(buffer) > 0){
                printf("Echo '%s'\n", buffer);

                if ((strncmp(buffer, "delay ", 6) == 0)|| (strncmp(buffer, "Delay ", 6) == 0)){

                    delay = atoi(&buffer[6]);
                    //printf("Received: %d\n", delay);
                    
                    if (xQueueSend(q_delays, (void *)&delay, 10) != pdTRUE){
                        printf("Couldn't send to queue\n");
                    } else {
                        printf("Sent %d to delays queue\n", delay);
                    }
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }

}

void led_task (void* params) {

    gpio_config_t led_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = LED_MASK,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };

    gpio_config(&led_conf);

    int rcv_delay;
    bool rcv = false;

    while (1){
        if (rcv){
            gpio_set_level(LED, 1);
            vTaskDelay(pdMS_TO_TICKS(rcv_delay));
            gpio_set_level(LED, 0);
            vTaskDelay(pdMS_TO_TICKS(rcv_delay));
        }
        
        if (xQueueReceive(q_delays, (void *)&rcv_delay, 0) == pdTRUE){
            printf("Toggling LED with %d delay\n", rcv_delay);
            rcv = true;
        }

        //vTaskDelay(pdMS_TO_TICKS(1000));
    }

}

void app_main() {

    //Goofd practice: give some time to the processor
    vTaskDelay(pdMS_TO_TICKS(100));

    // Create queues
    q_delays = xQueueCreate(QUEUE_DELAYS_LEN, sizeof(int));

    if (q_delays == NULL){
        printf("Couldn't create Queue for Delays\n");
    }

    q_msgs = xQueueCreate(QUEUE_MSG_LEN, sizeof(StringToQueue_t));

    if (q_msgs == NULL){
        printf("Couldn't create Queue for Messages\n");
    }

    //Create Tasks
    BaseType_t xConsoleTask = xTaskCreatePinnedToCore(console_task, "Console Task", TASK_A_CONSOLE_STACK, NULL, TASK_A_CONSOLE_PRIO, NULL, tskNO_AFFINITY);

    if (xConsoleTask != pdPASS){
        printf("Couldn't create task\n");
    }

    BaseType_t xLEDTask = xTaskCreatePinnedToCore(led_task, "LED Task", TASK_B_LED_STACK, NULL, TASK_B_LED_PRIO, NULL, tskNO_AFFINITY);

    if (xLEDTask != pdPASS){
        printf("Couldn't create task\n");
    }

}