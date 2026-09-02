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

TimerHandle_t led_dim_timer;

void timerCallback(TimerHandle_t pxTimer){
    gpio_set_level(LED, 0);
}

void console_task (void* params) {

    char buffer[20];

    printf("Type! \n");

    while (1){

        if (fgets(buffer, sizeof(buffer), stdin) != NULL){

            gpio_set_level(LED, 1);
            xTimerReset(led_dim_timer, 0);

            // Handle terminators
            size_t terminator = strcspn(buffer, "\n");
            buffer[terminator] = '\0';

            terminator = strcspn(buffer, "\r");
            buffer[terminator] = '\0';

            if (strlen(buffer) > 0){
                printf("Echo '%s'\n", buffer);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main() {

        gpio_config_t led_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = LED_MASK,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };

    gpio_config(&led_conf);

    gpio_set_level(LED, 0);

    led_dim_timer = xTimerCreate("Timer", pdMS_TO_TICKS(5000), pdFALSE, (void*) 0, timerCallback); 

    //Create Tasks
    BaseType_t xConsoleTask = xTaskCreatePinnedToCore(console_task, "Console Task", TASK_A_CONSOLE_STACK, NULL, TASK_A_CONSOLE_PRIO, NULL, tskNO_AFFINITY);
}