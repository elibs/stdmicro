#include "Led.h"
#include "hardware/gpio.h"

void blink(GPIO* led, int count, uint delay)
{
    while (count--)
    {
        led->put(true);
        sleep_ms(delay);
        led->put(false);
        sleep_ms(delay);
    }
}
