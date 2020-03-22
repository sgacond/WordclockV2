#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <rom/ets_sys.h>

#include "esp8266/gpio_struct.h"
#include "esp_system.h"
#include "esp_log.h"

#include "driver/gpio.h"

#include "leds.h"

#define PIN_D 13
#define PIN_CLK 14

#define BITBANG_DELAY_US 1

static int nLeds = 0;
struct led *leds;

void leds_init(int n) {
    
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = ((1ULL<<PIN_D) | (1ULL<<PIN_CLK));
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    if(leds != NULL)
        free(leds);

    nLeds = n;
    leds = malloc(sizeof(struct led) * n);

    leds_clear();
}

void leds_clear() {
    for(int i=0; i<nLeds; i++) {
        leds[i].global = 31;
        leds[i].w1 = 0x00;
        leds[i].w2 = 0x00;
        leds[i].w3 = 0x00;
    }
}

void leds_set(int i, float v) {
    if(i >= nLeds || i < 0)
        return;

    uint32_t val = v * 0xFFFFFF;
    leds[i].w1 = (val & 0xFF0000) >> 16;
    leds[i].w2 = (val & 0x00FF00) >> 8;
    leds[i].w3 = (val & 0x0000FF);
}

void leds_update() {

    // start frame: 0x00 0x00 0x00 0x00
    gpio_set_level(PIN_D, 0);
    gpio_set_level(PIN_CLK, 0);
    for(int i=0; i<32; i++) {
        ets_delay_us(BITBANG_DELAY_US);
        gpio_set_level(PIN_CLK, 1);
        ets_delay_us(BITBANG_DELAY_US);
        gpio_set_level(PIN_CLK, 0);
    }

    ets_delay_us(BITBANG_DELAY_US);

    // led frames
    for (int i = 0; i <= nLeds; i++) {

        uint32_t ledBits = 
            (((111 << 5) | (leds[i].global & 0b00011111)) << 24) |
            ((leds[i].w1) << 16) |
            ((leds[i].w2) << 8) |
            (leds[i].w3);

        for (int j = 31; j >= 0; j--) {
            gpio_set_level(PIN_D, (ledBits & (1 << j)) > 0);
            ets_delay_us(BITBANG_DELAY_US);
            gpio_set_level(PIN_CLK, 1);
            ets_delay_us(BITBANG_DELAY_US);
            gpio_set_level(PIN_CLK, 0);
            ets_delay_us(BITBANG_DELAY_US);
        }
        gpio_set_level(PIN_D, 0);

    }

    // end frame: 0xFF 0xFF 0xFF 0xFF
    gpio_set_level(PIN_D, 1);
    gpio_set_level(PIN_CLK, 0);
    for(int i=0; i<32; i++) {
        ets_delay_us(BITBANG_DELAY_US);
        gpio_set_level(PIN_CLK, 1);
        ets_delay_us(BITBANG_DELAY_US);
        gpio_set_level(PIN_CLK, 0);
    }
    gpio_set_level(PIN_D, 0);

}