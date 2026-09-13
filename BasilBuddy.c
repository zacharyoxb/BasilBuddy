#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "hardware/timer.h"
#include "hardware/sync.h"

const int ADC0 = 0;
const int TEMP_SENSOR = 4;

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

int main()
{
    stdio_init_all();
    adc_setup();

    // Every 30 seconds
    add_repeating_timer_ms(30000, read_sensors_irq, NULL, &timer);

    while (true)
    {
        sleep_ms(30000);
        printf("Seq: %u, Moisture: %u, Temp: %u, Timestamp: %llu\n",
               LAST_READING.seq,
               LAST_READING.moisture_raw,
               LAST_READING.temp_raw,
               to_us_since_boot(LAST_READING.timestamp));
    }
}
