#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"

void watch_start_task(QueueHandle_t tickQueue);

#ifdef __cplusplus
}
#endif
