#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_vfs_dev.h"
#include "driver/gpio.h"

#define CONSOLE_TASK_STACK  4096
#define CONSOLE_TASK_PRIO   3

#define LED_TASK_STACK      4096
#define LED_TASK_PRIO       2

#define LED             GPIO_NUM_12
#define LED_GPIO_MASK   (1 << LED)

char g_buffer[128];
bool g_buffer_filled = false;
int g_led_delay = 0;

void console_task (void *params){
    
    printf("Console task running. Type something and press Enter:\n");

    while (1){
        if(fgets(g_buffer, sizeof(g_buffer), stdin) != NULL){

            // Clean string from terminators
            size_t terminator = strcspn(g_buffer, "\r");
            g_buffer[terminator] = '\0';
            terminator = strcspn(g_buffer, "\n");
            g_buffer[terminator] = '\0';

            if (strlen(g_buffer) > 0) {
                //printf("Received: '%s' \n", g_buffer);
                g_buffer_filled = true;
                g_led_delay = atoi(g_buffer);
                printf("Received: %d \n", g_led_delay);
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }

}

void led_task (void *params){

    gpio_config_t led_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = LED_GPIO_MASK,
        .pull_up_en = GPIO_PULLUP_ENABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE
    };

    int gpio_init_error = gpio_config(&led_config);

    if (gpio_init_error){
        printf("Error initializing GPIO\n");
    }

    while (1)
    {   
        if (g_buffer_filled){
            printf("Toggling LED with updated value of %d\n", g_led_delay);
            gpio_set_level(LED, 1);
            vTaskDelay(pdMS_TO_TICKS(g_led_delay));
            gpio_set_level(LED, 0);
            vTaskDelay(pdMS_TO_TICKS(g_led_delay));
        } else {
            printf("Toggling LED with default value\n");
            gpio_set_level(LED, 1);
            vTaskDelay(pdMS_TO_TICKS(1000));
            gpio_set_level(LED, 0);
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
    }
}

void app_main(void) {
    // 2. Initialize UART and VFS first
    uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0);
    esp_vfs_dev_uart_use_driver(UART_NUM_0);
    esp_vfs_dev_uart_port_set_rx_line_endings(UART_NUM_0, ESP_LINE_ENDINGS_CRLF);
    esp_vfs_dev_uart_port_set_tx_line_endings(UART_NUM_0, ESP_LINE_ENDINGS_CRLF);

    BaseType_t xReturnConsole = xTaskCreatePinnedToCore(console_task, "Console Task", CONSOLE_TASK_STACK, NULL, CONSOLE_TASK_PRIO, NULL, tskNO_AFFINITY);
    BaseType_t xReturnLED = xTaskCreatePinnedToCore(led_task, "LED Task", LED_TASK_STACK, NULL, LED_TASK_PRIO, NULL, tskNO_AFFINITY);
}