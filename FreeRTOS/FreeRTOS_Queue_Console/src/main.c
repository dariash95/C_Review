#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include <string.h>

#define QUEUE_LEN 5

#define PRINT_TASK_STACK    4096
#define PRINT_TASK_PRIO     3

#define CONSOLE_TASK_STACK  4096
#define CONSOLE_TASK_PRIO   3

static QueueHandle_t msg_queue; 

void console_task(void* params){

    char aux_buffer[128];
    int item_to_send;

    while (1){
        if (fgets(aux_buffer, sizeof(aux_buffer), stdin) != NULL){

            size_t terminator = strcspn(aux_buffer, "\n");
            aux_buffer[terminator] = '\0';
            terminator = strcspn(aux_buffer, "\r");
            aux_buffer[terminator] = '\0';

            if (strlen(aux_buffer)> 0){
                item_to_send = atoi(aux_buffer);
                printf("Sending to q: %d\n", item_to_send);

                if (xQueueSend(msg_queue, (void *)&item_to_send, 10) != pdTRUE){
                    printf("Queue is full\n");
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void print_task (void* params){

   int item;

    while (1){
        // No blocking, doesn't wait
        if (xQueueReceive(msg_queue, (void*)&item, 0)  == pdTRUE){
            printf("Received from queue: '%d'\n", item);
        }
        vTaskDelay(pdMS_TO_TICKS(3000));
        
    }
}

void app_main() {

    // Wait for processor to finish setting up
    vTaskDelay(pdMS_TO_TICKS(100));

    msg_queue = xQueueCreate(QUEUE_LEN, sizeof(int));

    BaseType_t xConsoleTask = xTaskCreatePinnedToCore(console_task, "Console Task", CONSOLE_TASK_STACK, NULL, CONSOLE_TASK_PRIO, NULL, tskNO_AFFINITY);
    BaseType_t xPrintTask = xTaskCreatePinnedToCore(print_task, "Print Task", PRINT_TASK_STACK, NULL, PRINT_TASK_PRIO, NULL, tskNO_AFFINITY);
}