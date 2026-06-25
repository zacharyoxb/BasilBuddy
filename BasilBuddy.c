#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/timer.h"

const int ADC0 = 0;
const int TEMP_SENSOR = 4;

typedef struct
{
    volatile uint16_t moisture_raw;
    volatile uint16_t temp_raw;
    volatile uint16_t timestamp;
} sensor_data_t;

static struct repeating_timer timer;
static sensor_data_t LAST_READING = {0};

void adc_setup()
{
    adc_init();
    adc_gpio_init(ADC_BASE_PIN);
    adc_set_temp_sensor_enabled(true);
}

void send_bt_packet() {}

bool read_sensors_callback(struct repeating_timer *t)
{
    adc_select_input(ADC0);
    LAST_READING.moisture_raw = adc_read();
    adc_select_input(TEMP_SENSOR);
    LAST_READING.temp_raw = adc_read();
    LAST_READING.timestamp = get_absolute_time();

    send_bt_packet();

    return true;
}

void init_timer_interrupt(struct repeating_timer timer)
{
    add_repeating_timer_ms(1000, read_sensors_callback, NULL, &timer);
}

int main()
{
    stdio_init_all();
    adc_setup();
    init_timer_interrupt(timer);

    while (true)
        ;
}
