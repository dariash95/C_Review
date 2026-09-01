#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "esp_vfs_dev.h"

void app_main(void) {
    // 1. Install UART driver for standard console (UART 0)
    uart_driver_install(UART_NUM_0, 256, 0, 0, NULL, 0);

    // 2. Tell VFS to use UART driver for standard I/O (stdin)
    esp_vfs_dev_uart_use_driver(UART_NUM_0);

    // 3. Configure line endings to match the serial monitor
    esp_vfs_dev_uart_port_set_rx_line_endings(UART_NUM_0, ESP_LINE_ENDINGS_CRLF);
    esp_vfs_dev_uart_port_set_tx_line_endings(UART_NUM_0, ESP_LINE_ENDINGS_CRLF);

    char buffer[128];
    printf("ESP32-MINI-1 Ready. Type something and press Enter:\n");

    while (1) {
        // fgets will now block until a newline character is received
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            
            // Strip the trailing newline/carriage return characters
            buffer[strcspn(buffer, "\r")] = 0;
            buffer[strcspn(buffer, "\n")] = 0;

            // Ensure the string isn't empty before processing
            if (strlen(buffer) > 0) {
                printf("You entered: '%s'\n", buffer);
                
                // Add your custom logic here
                if (strcmp(buffer, "ping") == 0) {
                    printf("pong!\n");
                }
            }
        }
        
        // Brief delay to yield to the RTOS watchdog
        vTaskDelay(pdMS_TO_TICKS(10)); 
    }
}