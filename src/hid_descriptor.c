#include <stdint.h>
#include "hid_sensor_spec.h"

// from USB HID Specification
const uint8_t hid_descriptor_plant_sensor[] = {
    // --- Combined Plant Sensor (Temperature + Humidity) ---
    HID_USAGE_PAGE_SENSOR,
    HID_USAGE_SENSOR_TYPE_COLLECTION,
    HID_COLLECTION(0x01),

    // --- Report ID ---
    HID_REPORT_ID(0x01), //   1

    // --- Temperature Field ---
    HID_USAGE_PAGE_SENSOR,
    HID_USAGE_SENSOR_DATA_ENVIRONMENTAL_TEMPERATURE,
    HID_LOGICAL_MIN_16(0xF0, 0xD8), //  -10000
    HID_LOGICAL_MAX_16(0x10, 0x27), //   10000 -> -100.00C to 100.00C
    HID_REPORT_SIZE(0x10),          //   16
    HID_REPORT_COUNT(0x01),         //   1
    HID_UNIT_EXPONENT(0x0E),        //   -2 (i.e. divide by 100)
    HID_USAGE_SENSOR_UNITS_DEGREES,

    // --- Humidity Field ---
    HID_USAGE_SENSOR_TYPE_ENVIRONMENTAL_HUMIDITY,
    HID_LOGICAL_MIN_8(0x00),        // 0
    HID_LOGICAL_MAX_16(0x10, 0x27), // 10000  -> 0.00% to 100.00%
    HID_REPORT_SIZE(0x10),          // 16
    HID_REPORT_COUNT(0x01),         // REPORT_COUNT (1)
    HID_UNIT_EXPONENT(0x0E),        // UNIT_EXPONENT (-2, i.e. divide by 100)
    HID_USAGE_SENSOR_GENERIC_UNIT_PERCENT,

    HID_END_COLLECTION};

const unsigned int hid_descriptor_plant_sensor_len = sizeof(hid_descriptor_plant_sensor);