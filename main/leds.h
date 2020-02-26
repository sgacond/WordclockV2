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

void leds_display(struct led *leds, uint32_t length);

#ifdef __cplusplus
}
#endif
