#include <stdio.h>
#include "pico/stdlib.h"

const int ADC0 = 0;
const int TEMP_SENSOR = 4;
const float CONV_FACTOR = 3.3f / (1 << 12);

int main()
{
    stdio_init_all();
    adc_init();
    adc_gpio_init(ADC_BASE_PIN);

    adc_set_temp_sensor_enabled(true);
    int pin_mask = (1 << ADC0) | (1 << TEMP_SENSOR);
    adc_set_round_robin(pin_mask);
    adc_select_input(ADC0);

    while (true)
    {
        // Read from moisture sensor first
        uint16_t moist_output = adc_read();
        printf("Moisture output: %f\n", moist_output * CONV_FACTOR);

        // Now read from temperature sensor
        uint16_t temp_output = adc_read();
        printf("Temp output: %f\n", temp_output * CONV_FACTOR);
    }
}
