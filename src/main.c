#include <stdio.h>

#include "pico/stdlib.h"

#include "sensors.h"

int main()
{
    stdio_init_all();

    sensors_init();

    while (true)
        ;
}
