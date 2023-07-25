#include <stdio.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

void app_main(void)
{
    while (true)
    {
        ESP_LOGW("TEST", "HELLO WORLD");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}