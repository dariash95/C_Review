#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"

#define PROD_TASK_STACK 4096
#define PROD_TASK_PRIO  3
#define PROD_TASKS      5

#define CONS_TASK_STACK 4096
#define CONS_TASK_PRIO  3
#define CONS_TASKS      3

#define BUFFER_SIZE 5

SemaphoreHandle_t buffer_mutex;
SemaphoreHandle_t bin_semaphore;
SemaphoreHandle_t empty_semaphore;
SemaphoreHandle_t filled_semaphore;

int buffer[BUFFER_SIZE];
int head = 0;
int tail = 0;

void producer_task (void* params){

    int num = *(int *)params;

    xSemaphoreGive(bin_semaphore);

    for (int i = 0; i < 3; i++) {
        xSemaphoreTake(empty_semaphore, portMAX_DELAY);
        
        // Critical section: writing to the buffer
        xSemaphoreTake(buffer_mutex, portMAX_DELAY);
        buffer[head] = num;
        head = (head + 1) % BUFFER_SIZE;
        xSemaphoreGive(buffer_mutex);

        xSemaphoreGive(filled_semaphore);
    }   
    
    vTaskDelete(NULL);

}

void consumer_task (void* params){
    
    while(1){
        xSemaphoreTake(filled_semaphore, portMAX_DELAY);

        //Critical section: reading from the buffer
        xSemaphoreTake(buffer_mutex, portMAX_DELAY);
        int num = buffer[tail];
        tail = (tail+ 1) % BUFFER_SIZE;
        xSemaphoreGive(buffer_mutex);

        xSemaphoreGive(empty_semaphore);

        printf("%d\n", num);
    }
    
}

void app_main() {

    // Let system start
    vTaskDelay(pdMS_TO_TICKS(100));

    //Create mutex and semaphores
    buffer_mutex = xSemaphoreCreateMutex();
    bin_semaphore = xSemaphoreCreateBinary();
    empty_semaphore = xSemaphoreCreateCounting(BUFFER_SIZE, BUFFER_SIZE);
    filled_semaphore = xSemaphoreCreateCounting(BUFFER_SIZE, 0);

    char task_name[25];

    // Create 5 producer tasks
    for (int i = 0; i < PROD_TASKS; i++){
        sprintf(task_name, "Producer %i", i);
        xTaskCreatePinnedToCore(producer_task, task_name, PROD_TASK_STACK, (void*)&i, PROD_TASK_PRIO, NULL, tskNO_AFFINITY);
        
        // Force main app to stay here and not change i
        xSemaphoreTake(bin_semaphore, portMAX_DELAY);
    }

    // Create 2 consumer tasks
    for (int i = 0; i < CONS_TASKS; i++){
        sprintf(task_name, "Consumer %i", i);
        xTaskCreatePinnedToCore(consumer_task, task_name, CONS_TASK_STACK, NULL, CONS_TASK_PRIO, NULL, tskNO_AFFINITY);
    }

}