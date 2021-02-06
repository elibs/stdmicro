#include "led.h"
#include "hardware/gpio.h"

void blink(int count, uint delay)
{
    while (count--)
    {
        gpio_put(LED_PIN, true);
        sleep_ms(delay);
        gpio_put(LED_PIN, false);
        sleep_ms(delay);
    }
}

void hang(void)
{
    gpio_put(LED_PIN, true);
    while (1)
    {
        sleep_ms(1000);
    }
}
