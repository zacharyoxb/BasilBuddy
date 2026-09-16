#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/sync.h"

#include "btstack.h"
#include "plant_service.h"

const int ADC0_PIN = 0;
const int TEMP_SENSOR_PIN = 4;

const double DEVICE_V = 3.29;
const double ADC_CODES = 4096.0;
const double VBE_VOLTAGE = 0.706;
const double VBE_TEMP = 27.0;
const double SLOPE = 0.001721;

const double MAX_DRY_VAL = 3600;

typedef struct
{
    volatile uint32_t seq;
    volatile uint16_t moisture_raw;
    volatile uint16_t temp_raw;
    volatile absolute_time_t timestamp;
} sensor_data_t;

static struct repeating_timer timer;
static sensor_data_t LAST_READING = {0};

void adc_setup()
{
    adc_init();
    adc_gpio_init(ADC_BASE_PIN);
    adc_set_temp_sensor_enabled(true);
}

bool read_sensors_irq(struct repeating_timer *t)
{
    LAST_READING.seq++;
    __dmb();
    adc_select_input(ADC0_PIN);
    LAST_READING.moisture_raw = adc_read();
    adc_select_input(TEMP_SENSOR_PIN);
    LAST_READING.temp_raw = adc_read();
    LAST_READING.timestamp = get_absolute_time();
    __dmb();
    LAST_READING.seq++;
    return true;
}

double moisture_to_percent(uint16_t raw_value)
{
    double multiplier = 100 / MAX_DRY_VAL;
    double clamped = (double)raw_value > MAX_DRY_VAL ? MAX_DRY_VAL : (double)raw_value;
    double dry_percent = clamped * multiplier;
    return 100.0 - dry_percent;
}

double temp_to_c(uint16_t raw_value)
{
    double adc_v = (double)raw_value * DEVICE_V / ADC_CODES;
    double temp_c = VBE_TEMP - (adc_v - VBE_VOLTAGE) / SLOPE;
    return temp_c;
}

void send_bt_packet() {}

int main()
{
    stdio_init_all();
    adc_setup();

    add_repeating_timer_ms(30000, read_sensors_irq, NULL, &timer);

    while (true)
    {
        // printf("%u, %.2f%%, %.2f, %llu\n",
        //        LAST_READING.seq,
        //        moisture_to_percent(LAST_READING.moisture_raw),
        //        temp_to_c(LAST_READING.temp_raw),
        //        to_us_since_boot(LAST_READING.timestamp));

        // sleep_ms(30000);
    }
}
