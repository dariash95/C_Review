#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

#define TASK_1_STACK    4096
#define TASK_1_PRIO     3 

static const char *TAG_1 = "Task 1";
static const char *TAG_2 = "Task 2";


#define TASK_2_STACK    4096
#define TASK_2_PRIO     5

#define TASK_MAIN_STACK 2048
#define TASK_MAIN_PRIO  1

static TaskHandle_t task_1_handle = NULL;
static TaskHandle_t task_2_handle = NULL;
static TaskHandle_t task_main_handle = NULL;

const char message[] = "uhuiog FGHJK Rhdkl";


void task1 (void *params){

    ESP_LOGI(TAG_1, "Task 1");

    // Count numbers in string
    int msg_len = sizeof(message) - 1; // Minus /0

    while (1){
        for (int i = 0; i < msg_len; i++){
            printf("%c", message[i]);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("\n");
    }

}

void task2 (void *params){

    ESP_LOGI(TAG_2, "Task 2");

    while (1){
        printf("*");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void task_app (void *parms){

    while (1){
        for (int i = 0; i < 3; i++){
            vTaskSuspend(task_2_handle);
            vTaskDelay(pdMS_TO_TICKS(2000));
            vTaskResume(task_2_handle);
            vTaskDelay(pdMS_TO_TICKS(2000));
        }

        if (task_1_handle != NULL){
            vTaskDelete(task_1_handle);
            task_1_handle = NULL;
        }
    }
}

void app_main() {

    //Allow other core to finish initialization
    vTaskDelay(pdMS_TO_TICKS(100));

    BaseType_t xReturned2 = xTaskCreatePinnedToCore(task2, "Task 2" , TASK_2_STACK, NULL, TASK_2_PRIO, &task_2_handle, tskNO_AFFINITY);
    BaseType_t xReturned1 = xTaskCreatePinnedToCore(task1, "Task 1", TASK_1_STACK, NULL, TASK_1_PRIO, &task_1_handle, tskNO_AFFINITY);
    BaseType_t xReturnMain = xTaskCreatePinnedToCore(task_app, "Main Task", TASK_MAIN_STACK, NULL, TASK_MAIN_PRIO, &task_main_handle, tskNO_AFFINITY);    

}