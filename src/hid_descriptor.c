#include <stdint.h>

// from USB HID Specification
const uint8_t hid_descriptor_plant_sensor[] = {
    // --- Combined Plant Sensor (Temperature + Humidity) ---
    0x05, 0x20, // USAGE_PAGE (Sensor)
    0x09, 0x01, // USAGE (Sensor) - Top-level Collection
    0xA1, 0x01, // COLLECTION (Application)

    // --- Report ID ---
    // The first byte of every data packet must match this ID.
    0x85, 0x01, //   REPORT_ID (1)

    // --- Temperature Field ---
    0x05, 0x20,       //   USAGE_PAGE (Sensor)
    0x09, 0x34,       //   USAGE (Environmental: Temperature Data)
    0x15, 0x64,       //   LOGICAL_MINIMUM (-10000)
    0x26, 0x10, 0x27, //   LOGICAL_MAXIMUM (10000) -> -100.00C to 100.00C
    0x75, 0x10,       //   REPORT_SIZE (16)
    0x95, 0x01,       //   REPORT_COUNT (1)
    0x55, 0x0E,       // UNIT_EXPONENT (-2, i.e. divide by 100)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)

    // --- Humidity Field ---
    0x09, 0x33,       // USAGE (Environmental: Humidity Data)
    0x15, 0x00,       // LOGICAL_MINIMUM (0)
    0x26, 0x10, 0x27, // LOGICAL_MAXIMUM (10000)  -> 0.00% to 100.00%
    0x75, 0x10,       // REPORT_SIZE (16)
    0x95, 0x01,       // REPORT_COUNT (1)
    0x55, 0x0E,       // UNIT_EXPONENT (-2, i.e. divide by 100)
    0x65, 0x03,       // UNIT (Percentage)
    0x81, 0x02,       // INPUT (Data, Var, Abs)

    0xC0 // END_COLLECTION
};

const unsigned int hid_descriptor_plant_sensor_len = sizeof(hid_descriptor_plant_sensor);