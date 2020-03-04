#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

struct led {
    uint8_t global;
    uint8_t w1;
    uint8_t w2;
    uint8_t w3;
};

void leds_init(int n);
void leds_set(int i, float v);
void leds_update();

#ifdef __cplusplus
}
#endif
