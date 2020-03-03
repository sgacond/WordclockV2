#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "esp8266/gpio_struct.h"
#include "esp_system.h"
#include "esp_log.h"

#include "driver/gpio.h"

#include "leds.h"

#define PIN_D 13
#define PIN_CLK 14

void leds_init() {
    
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL<<PIN_D) | (1ULL<<PIN_CLK));
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

}

void leds_display(struct led *leds, uint32_t length) {

    // start frame: 0x00 0x00 0x00 0x00
    gpio_set_level(PIN_D, 0);
    gpio_set_level(PIN_CLK, 0);
    for(int i=0; i<32; i++) {
        gpio_set_level(PIN_CLK, 1);
        gpio_set_level(PIN_CLK, 0);
    }

    // led frames
    for (int i = 0; i < length; i++) {

        uint32_t ledBits = 
            (((111 << 5) | (leds[i].global & 0b00011111)) << 24) |
            ((leds[i].w1) << 16) |
            ((leds[i].w2) << 8) |
            (leds[i].w3);

        for (int j = 31; j >= 0; j--) {
            gpio_set_level(PIN_D, (ledBits & (1 << j)) > 0);
            gpio_set_level(PIN_CLK, 1);
            gpio_set_level(PIN_CLK, 0);
        }
        gpio_set_level(PIN_D, 0);

    }

    // end frame: 0xFF 0xFF 0xFF 0xFF
    gpio_set_level(PIN_D, 1);
    gpio_set_level(PIN_CLK, 0);
    for(int i=0; i<32; i++) {
        gpio_set_level(PIN_CLK, 1);
        gpio_set_level(PIN_CLK, 0);
    }
    gpio_set_level(PIN_D, 0);

}