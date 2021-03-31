#include "Led.h"
#include "hardware/gpio.h"

#include "pico/stdlib.h" // for sleep_ms

void blink(stdmicro::GPIO* led, int count, unsigned int delay)
{
    while (count--)
    {
        led->put(true);
        sleep_ms(delay);
        led->put(false);
        sleep_ms(delay);
    }
}
