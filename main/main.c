/* LwIP SNTP example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_event.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "driver/gpio.h"
#include "lwip/apps/sntp.h"

#include "wifi.h"
#include "watch.h"
#include "words.h"
#include "leds.h"

static const char *TAG = "main";
static QueueHandle_t tickQueue;

static void main_task(void *arg)
{
    struct tm now;
    char strftime_buf[64];

    leds_init(11);

    while(1) {
        if(xQueueReceive(tickQueue, &now, (TickType_t)10) == pdPASS) {

            strftime(strftime_buf, sizeof(strftime_buf), "%c", &now);
            ESP_LOGI(TAG, "The current date/time in Azmoos is: %s", strftime_buf);

            words_display(now);
        }
   }
}

void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    ESP_ERROR_CHECK(wifi_connect());

    tickQueue = xQueueCreate(10, sizeof(struct tm));
    watch_start_task(tickQueue);

    xTaskCreate(main_task, "main_task", 2048, NULL, 10, NULL);
}