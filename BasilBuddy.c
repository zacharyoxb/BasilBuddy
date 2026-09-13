#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/sync.h"

// Pins
const int ADC0 = 0;
const int TEMP_SENSOR = 4;

// Values for estimating moisture
const uint16_t dry = 3650;

// Values for estimating temperature
const double device_v = 3.3;
const double adc_codes = 4096.0;
const double vbe_voltage = 0.706;
const double vbe_temp = 27.0;
const double slope = 0.001721;

// Struct for storing readings
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

void send_bt_packet() {}

bool read_sensors_irq(struct repeating_timer *t)
{
    LAST_READING.seq++;
    __dmb();
    adc_select_input(ADC0);
    LAST_READING.moisture_raw = adc_read();
    adc_select_input(TEMP_SENSOR);
    LAST_READING.temp_raw = adc_read();
    LAST_READING.timestamp = get_absolute_time();
    __dmb();
    LAST_READING.seq++;
    return true;
}

double raw_to_centigrade(uint16_t raw_value)
{
    double v = (double)raw_value * device_v / adc_codes;
    double result = vbe_temp - ((v - vbe_voltage) / slope);
    return result;
}

int main()
{
    stdio_init_all();
    adc_setup();

    add_repeating_timer_ms(30000, read_sensors_irq, NULL, &timer);

    while (true)
    {
        sleep_ms(30000);

        printf("Seq: %u, Moisture: %u, Temp: %.2f, Timestamp: %llu\n",
               LAST_READING.seq,
               LAST_READING.moisture_raw,
               raw_to_centigrade(LAST_READING.temp_raw),
               to_us_since_boot(LAST_READING.timestamp));
    }
}
