#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"
#include "driver/gpio.h"

static const char *TAG = "Task LED 1";

#define LED_TASK_STACK      1024
#define LED_TASK_PRIORITY   3

TaskHandle_t app_task_handle;

#define LED_1    GPIO_NUM_12
#define LED_2    GPIO_NUM_23
#define GPIO_PIN_SEL_MASK ((1 << LED_1) | (1 << LED_2))

void toggleLED1 (void *parameter){

    while (1){
        gpio_set_level(LED_1, 1);
        vTaskDelay(pdMS_TO_TICKS(500));
        gpio_set_level(LED_1, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void toggleLED2(void *parameter){

    while (1){
        gpio_set_level(LED_2, 1);
        vTaskDelay(pdMS_TO_TICKS(250));
        gpio_set_level(LED_2, 0);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}

void app_main() {

    //Allow other core to finish initialization
    vTaskDelay(pdMS_TO_TICKS(100));

    gpio_config_t leds_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = GPIO_PIN_SEL_MASK,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };

    esp_err_t gpio_init_error = gpio_config(&leds_conf);

    if (gpio_init_error){
        ESP_LOGI(TAG, "Problem initializing LED");
    }

    BaseType_t xReturned1 = xTaskCreatePinnedToCore(toggleLED1, "Toggle LED", LED_TASK_STACK, NULL, LED_TASK_PRIORITY, NULL, tskNO_AFFINITY);
    BaseType_t xReturned2 = xTaskCreatePinnedToCore(toggleLED2, "Toggle LED", LED_TASK_STACK, NULL, LED_TASK_PRIORITY, NULL, tskNO_AFFINITY);


}
