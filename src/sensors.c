#include "sensors.h"

const int ADC0_PIN = 0;
const int TEMP_SENSOR_PIN = 4;

const double DEVICE_V = 3.29;
const double ADC_CODES = 4096.0;
const double VBE_VOLTAGE = 0.706;
const double VBE_TEMP = 27.0;
const double SLOPE = 0.001721;

const double MAX_DRY_VAL = 3600;

void sensors_init()
{
    adc_init();
    adc_gpio_init(ADC_BASE_PIN);
    adc_set_temp_sensor_enabled(true);
}

static sensor_data_t LAST_READING = {0};

double _moisture_to_percent(uint16_t raw_value)
{
    double multiplier = 100 / MAX_DRY_VAL;
    double clamped = (double)raw_value > MAX_DRY_VAL ? MAX_DRY_VAL : (double)raw_value;
    double dry_percent = clamped * multiplier;
    return 100.0 - dry_percent;
}

double _temp_to_c(uint16_t raw_value)
{
    double adc_v = (double)raw_value * DEVICE_V / ADC_CODES;
    double temp_c = VBE_TEMP - (adc_v - VBE_VOLTAGE) / SLOPE;
    return temp_c;
}

sensor_data_t sensors_read()
{
    LAST_READING.seq++;
    __dmb();
    adc_select_input(ADC0_PIN);
    LAST_READING.moisture = _moisture_to_percent(adc_read());
    adc_select_input(TEMP_SENSOR_PIN);
    LAST_READING.temp = _temp_to_c(adc_read());
    LAST_READING.timestamp = get_absolute_time();
    __dmb();
    LAST_READING.seq++;
    return LAST_READING;
}
