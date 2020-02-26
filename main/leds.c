#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "ringbuf.h"

#include "esp8266/spi_struct.h"
#include "esp8266/gpio_struct.h"
#include "esp_system.h"
#include "esp_log.h"

#include "driver/gpio.h"
#include "driver/spi.h"

#include "leds.h"

static const char *TAG = "leds";

static uint32_t start_end_frame = 0xFFFFFFFF;

// https://github.com/espressif/ESP8266_RTOS_SDK/blob/master/examples/peripherals/spi/normal_performance/spi_master/main/spi_master_example_main.c

/* SPI transmit data, format: 8bit command (read value: 3, write value: 4) + 8bit address(value: 0x0) + 64byte data */
static void IRAM_ATTR spi_master_send(uint32_t* data, uint32_t len)
{
    spi_trans_t trans;
    uint16_t cmd;
    uint32_t addr = 0x0;

    if (len > 16) {
        ESP_LOGE(TAG, "ESP8266 only support transmit 64bytes(16 * sizeof(uint32_t)) one time");
        return;
    }

    memset(&trans, 0x0, sizeof(trans));
    trans.bits.val = 0;            // clear all bit

    cmd = SPI_MASTER_WRITE_DATA_TO_SLAVE_CMD;  
    trans.bits.mosi = len * 32;             // One time transmit only support 64bytes
    trans.mosi = data;

    trans.bits.cmd = 8 * 1;
    trans.bits.addr = 8 * 1;     // transmit data will use 8bit address
    trans.cmd = &cmd;
    trans.addr = &addr;
    
    spi_trans(HSPI_HOST, &trans); 
}

/* SPI master send length, format: 8bit command(value:1) + 32bit status length */
static void IRAM_ATTR spi_master_send_length(uint32_t len)
{
    spi_trans_t trans;
    uint16_t cmd = SPI_MASTER_WRITE_STATUS_TO_SLAVE_CMD;
    memset(&trans, 0x0, sizeof(trans));
    trans.bits.val = 0;
    trans.bits.cmd = 8 * 1;  
    trans.bits.addr = 0;          // transmit status do not use address bit
    trans.bits.mosi = 8 * 4;      // status length is 32bit
    trans.cmd = &cmd;
    trans.addr = NULL;
    trans.mosi = &len;
    spi_trans(HSPI_HOST, &trans);    
}

void leds_display(struct led *leds, uint32_t length) {

    spi_master_send_length((length + 2) * 32);
    
    // start frame
    spi_master_send(&start_end_frame, 1);

    for (uint32_t i = 0; i < length; i++) {

        uint32_t ledBits = 
            (((111 << 5) | (leds[i].global & 0b00011111)) << 24) |
            ((leds[i].w1) << 16) |
            ((leds[i].w2) << 8) |
            (leds[i].w3);

        spi_master_send(&ledBits, 1);

    }

    // end frame
    spi_master_send(&start_end_frame, 1);

    spi_master_send_length(0);
}