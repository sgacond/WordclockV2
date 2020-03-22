
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

// LAYOUT
// E   | S   | K   | I   | S   | T   | L   | F   | Ü   | N   | F
// 10  | 9   | 8   | 7   | 6   | 5   | 4   | 3   | 2   | 1   | 0    
// ----------------------------------------------------------------
// Z   | E   | H   | N   | Z   | W   | A   | N   | Z   | I   | G
// 11  | 12  | 13  | 14  | 15  | 16  | 17  | 18  | 19  | 20  | 21
// ----------------------------------------------------------------
// D   | R   | E   | I   | V   | I   | E   | R   | T   | E   | L
// 32  | 31  | 30  | 29  | 28  | 27  | 26  | 25  | 24  | 23  | 22
// ----------------------------------------------------------------
// T   | G   | N   | A   | C   | H   | V   | O   | R   | J   | M
// 33  | 34  | 35  | 36  | 37  | 38  | 39  | 40  | 41  | 42  | 43 
// ----------------------------------------------------------------
// H   | A   | L   | B   | Q   | Z   | W   | Ö   | L   | F   | P
// 54  | 53  | 52  | 51  | 50  | 49  | 48  | 47  | 46  | 45  | 44
// ----------------------------------------------------------------
// Z   | W   | E   | I   | N   | S   | I   | E   | B   | E   | N
// 55  | 56  | 57  | 58  | 59  | 60  | 61  | 62  | 63  | 64  | 65
// ----------------------------------------------------------------
// K   | D   | R   | E   | I   | R   | H   | F   | Ü   | N   | F
// 76  | 75  | 74  | 73  | 72  | 71  | 70  | 69  | 68  | 67  | 66
// ----------------------------------------------------------------
// E   | L   | F   | N   | E   | U   | N   | V   | I   | E   | R
// 77  | 78  | 79  | 80  | 81  | 82  | 83  | 84  | 85  | 86  | 87
// ----------------------------------------------------------------
// W   | A   | C   | H   | T   | Z   | E   | H   | N   | R   | S
// 98  | 97  | 96  | 95  | 94  | 93  | 92  | 91  | 90  | 89  | 88
// ----------------------------------------------------------------
// B   | S   | E   | C   | H   | S   | F   | M   | U   | H   | R
// 99  | 100 | 101 | 102 | 103 | 104 | 105 | 106 | 107 | 108 | 109

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
    

    float b = 1;//0.25;
    leds_clear();

    // ES IST
    leds_set(10, b);
    leds_set(9, b);
    leds_set(7, b);
    leds_set(6, b);
    leds_set(5, b);

    // minutes
    switch(minPart1) {
        case 0:
            leds_set(107, b); // UHR
            leds_set(108, b);
            leds_set(109, b);
            ESP_LOGI(TAG, "Es ist %i Uhr (+ %i).", hourPart, minPart2);
            break;
        case 1:
            leds_set(3, b); // FÜNF
            leds_set(2, b);
            leds_set(1, b);
            leds_set(0, b);
            leds_set(35, b); // NACH
            leds_set(36, b);
            leds_set(37, b);
            leds_set(38, b);
            ESP_LOGI(TAG, "Es ist fünf nach %i (+ %i).", hourPart, minPart2);
            break;
        case 2:
            leds_set(11, b); // ZEHN
            leds_set(12, b);
            leds_set(13, b);
            leds_set(14, b);
            leds_set(35, b); // NACH
            leds_set(36, b);
            leds_set(37, b);
            leds_set(38, b);
            ESP_LOGI(TAG, "Es ist zehn nach %i (+ %i).", hourPart, minPart2);
            break;
        case 3:
            leds_set(28, b); // VIERTEL
            leds_set(27, b);
            leds_set(26, b);
            leds_set(25, b);
            leds_set(24, b);
            leds_set(23, b);
            leds_set(22, b);
            leds_set(35, b); // NACH
            leds_set(36, b);
            leds_set(37, b);
            leds_set(38, b);
            ESP_LOGI(TAG, "Es ist viertel nach %i (+ %i).", hourPart, minPart2);
            break;
        case 4:
            leds_set(15, b); // ZWANZIG
            leds_set(16, b);
            leds_set(17, b);
            leds_set(18, b);
            leds_set(19, b);
            leds_set(20, b);
            leds_set(21, b);
            leds_set(35, b); // NACH
            leds_set(36, b);
            leds_set(37, b);
            leds_set(38, b);
            ESP_LOGI(TAG, "Es ist zwanzig nach %i (+ %i).", hourPart, minPart2);
            break;
        case 5:
            leds_set(3, b); // FÜNF
            leds_set(2, b);
            leds_set(1, b);
            leds_set(0, b);
            leds_set(39, b); // VOR
            leds_set(40, b);
            leds_set(41, b);
            leds_set(54, b); // HALB
            leds_set(53, b);
            leds_set(52, b);
            leds_set(51, b);
            hourPart++;
            ESP_LOGI(TAG, "Es ist fünf vor halb %i (+ %i).", hourPart, minPart2);
            break;
        case 6:
            leds_set(54, b); // HALB
            leds_set(53, b);
            leds_set(52, b);
            leds_set(51, b);
            hourPart++;
            ESP_LOGI(TAG, "Es ist halb %i (+ %i).", hourPart, minPart2);
            break;
        case 7:
            leds_set(3, b); // FÜNF
            leds_set(2, b);
            leds_set(1, b);
            leds_set(0, b);
            leds_set(35, b); // NACH
            leds_set(36, b);
            leds_set(37, b);
            leds_set(38, b);
            leds_set(54, b); // HALB
            leds_set(53, b);
            leds_set(52, b);
            leds_set(51, b);
            hourPart++;
            ESP_LOGI(TAG, "Es ist fünf nach halb %i (+ %i).", hourPart, minPart2);
            break;
        case 8:
            leds_set(15, b); // ZWANZIG
            leds_set(16, b);
            leds_set(17, b);
            leds_set(18, b);
            leds_set(19, b);
            leds_set(20, b);
            leds_set(21, b);
            leds_set(39, b); // VOR
            leds_set(40, b);
            leds_set(41, b);
            hourPart++;
            ESP_LOGI(TAG, "Es ist zwanzig vor %i (+ %i).", hourPart, minPart2);
            break;
        case 9:
            leds_set(28, b); // VIERTEL
            leds_set(27, b);
            leds_set(26, b);
            leds_set(25, b);
            leds_set(24, b);
            leds_set(23, b);
            leds_set(22, b);
            leds_set(39, b); // VOR
            leds_set(40, b);
            leds_set(41, b);
            hourPart++;
            ESP_LOGI(TAG, "Es ist viertel vor %i (+ %i).", hourPart, minPart2);
            break;
        case 10:
            leds_set(11, b); // ZEHN
            leds_set(12, b);
            leds_set(13, b);
            leds_set(14, b);
            leds_set(39, b); // VOR
            leds_set(40, b);
            leds_set(41, b);
            hourPart++;
            ESP_LOGI(TAG, "Es ist zehn vor %i (+ %i).", hourPart, minPart2);
            break;
        case 11:
            leds_set(3, b); // FÜNF
            leds_set(2, b);
            leds_set(1, b);
            leds_set(0, b);
            leds_set(39, b); // VOR
            leds_set(40, b);
            leds_set(41, b);
            hourPart++;
            ESP_LOGI(TAG, "Es ist fünf vor %i (+ %i).", hourPart, minPart2);
            break;
    } 
            
    switch(hourPart) {
        case 0:
        case 12:
            leds_set(49, b); // ZWÖLF
            leds_set(48, b);
            leds_set(47, b);
            leds_set(46, b);
            leds_set(45, b);
            break;
        case 1:
        case 13:
            leds_set(57, b); // EINS
            leds_set(58, b);
            leds_set(59, b);
            leds_set(60, b);
            break;
        case 2:
        case 14:
            leds_set(55, b); // ZWEI
            leds_set(56, b);
            leds_set(57, b);
            leds_set(58, b);
            break;
        case 3:
        case 15:
            leds_set(75, b); // DREI
            leds_set(74, b);
            leds_set(73, b);
            leds_set(72, b);
            break;
        case 4:
        case 16:
            leds_set(84, b); // VIER
            leds_set(85, b);
            leds_set(86, b);
            leds_set(87, b);
            break;
        case 5:
        case 17:
            leds_set(69, b); // FÜNF
            leds_set(68, b);
            leds_set(67, b);
            leds_set(66, b);
            break;
        case 6:
        case 18:
            leds_set(100, b); // SECHS
            leds_set(101, b);
            leds_set(102, b);
            leds_set(103, b);
            leds_set(104, b);
            break;
        case 7:
        case 19:
            leds_set(60, b); // SIEBEN
            leds_set(61, b);
            leds_set(62, b);
            leds_set(63, b);
            leds_set(64, b);
            leds_set(65, b);
            break;
        case 8:
        case 20:
            leds_set(97, b); // ACHT
            leds_set(96, b);
            leds_set(95, b);
            leds_set(94, b);
            break;
        case 9:
        case 21:
            leds_set(80, b); // NEUN
            leds_set(81, b);
            leds_set(82, b);
            leds_set(83, b);
            break;
        case 10:
        case 22:
            leds_set(93, b); // ZEHN
            leds_set(92, b);
            leds_set(91, b);
            leds_set(90, b);
            break;
        case 11:
        case 23:
            leds_set(77, b); // ELF
            leds_set(78, b);
            leds_set(79, b);
            break;
    }

    leds_update();
}
