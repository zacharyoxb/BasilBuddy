#pragma once
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"
#include "hardware/sync.h"

typedef struct
{
    volatile uint32_t seq;
    volatile uint16_t moisture;
    volatile uint16_t temp;
    volatile absolute_time_t timestamp;
} sensor_data_t;

void sensors_init(void);
sensor_data_t sensors_read(void);
