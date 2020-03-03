
// hourPart
// 0 - 12

// minPart1:
// 0   --
// 1   fünf nach
// 2   zehn nach
// 3   viertel nach
// 4   zwanzig nach
// 5   fünf vor halb 
// 6   halb
// 7   fünf nach halb
// 8   zwanzig vor
// 9   viertel vor
// 10  zehn vor
// 11  fünf vor

// minPart2:
// 0 - 4

#include <time.h>
#include <stdint.h>

#include "esp_log.h"
#include "words.h"
#include "leds.h"

static const char *TAG = "words";

void words_display(struct tm time) {

    uint8_t hourPart = time.tm_hour % 12;
    uint8_t minPart1 = (uint8_t)(time.tm_min / 5);
    uint8_t minPart2 = time.tm_min % 5;
    
    // dummy
    struct led leds[1];
    leds[0].global = 31;
    leds[0].w1 = 0xFF;
    leds[0].w2 = 0xFF;
    leds[0].w3 = 0xFF;
    leds_display(leds, 1);


    switch(minPart1) {
        case 0:
            ESP_LOGI(TAG, "Es ist %i Uhr (+ %i).", hourPart, minPart2);
            break;
        case 1:
            ESP_LOGI(TAG, "Es ist fünf nach %i (+ %i).", hourPart, minPart2);
            break;
        case 2:
            ESP_LOGI(TAG, "Es ist zehn nach %i (+ %i).", hourPart, minPart2);
            break;
        case 3:
            ESP_LOGI(TAG, "Es ist viertel nach %i (+ %i).", hourPart, minPart2);
            break;
        case 4:
            ESP_LOGI(TAG, "Es ist zwanzig nach %i (+ %i).", hourPart, minPart2);
            break;
        case 5:
            hourPart++;
            ESP_LOGI(TAG, "Es ist fünf vor halb %i (+ %i).", hourPart, minPart2);
            break;
        case 6:
            hourPart++;
            ESP_LOGI(TAG, "Es ist halb %i (+ %i).", hourPart, minPart2);
            break;
        case 7:
            hourPart++;
            ESP_LOGI(TAG, "Es ist fünf nach halb %i (+ %i).", hourPart, minPart2);
            break;
        case 8:
            hourPart++;
            ESP_LOGI(TAG, "Es ist zwanzig vor %i (+ %i).", hourPart, minPart2);
            break;
        case 9:
            hourPart++;
            ESP_LOGI(TAG, "Es ist viertel vor %i (+ %i).", hourPart, minPart2);
            break;
        case 10:
            hourPart++;
            ESP_LOGI(TAG, "Es ist zehn vor %i (+ %i).", hourPart, minPart2);
            break;
        case 11:
            hourPart++;
            ESP_LOGI(TAG, "Es ist fünf vor %i (+ %i).", hourPart, minPart2);
            break;
    } 


}
