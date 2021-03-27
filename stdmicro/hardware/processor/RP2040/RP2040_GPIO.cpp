#include "RP2040_GPIO.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"

namespace stdmicro::processor::RP2040
{

RP2040_GPIO::RP2040_GPIO(size_t pin, stdmicro::GPIO::Function func, stdmicro::GPIO::Direction dir):
    mPin(pin)
{
    gpio_init(mPin);
    function(func);
    direction(dir);
}

RP2040_GPIO::~RP2040_GPIO(void)
{
}

void RP2040_GPIO::function(stdmicro::GPIO::Function func) const
{

    gpio_function f;
    switch (func)
    {
    case None:
        f = GPIO_FUNC_NULL;
        break;
    case XIP:
        f = GPIO_FUNC_XIP;
        break;
    case SPI:
        f = GPIO_FUNC_SPI;
        break;
    case UART:
        f = GPIO_FUNC_UART;
        break;
    case I2C:
        f = GPIO_FUNC_I2C;
        break;
    case PWM:
        f = GPIO_FUNC_PWM;
        break;
    case SIO:
        f = GPIO_FUNC_SIO;
        break;
    case PIO:
        // fallthrough
    case PIO0:
        f = GPIO_FUNC_PIO0;
        break;
    case PIO1:
        f = GPIO_FUNC_PIO1;
        break;
    case GPCK:
        f = GPIO_FUNC_GPCK;
        break;
    case USB:
        f = GPIO_FUNC_USB;
        break;
    default:
        return;
    }
    gpio_set_function(mPin, f);
}

void RP2040_GPIO::direction(stdmicro::GPIO::Direction dir) const
{
    gpio_set_dir(mPin, dir == stdmicro::GPIO::Input ? GPIO_IN : GPIO_OUT);
}

stdmicro::GPIO::Direction RP2040_GPIO::direction(void) const
{
    int dir = gpio_get_dir(mPin);
    if (dir == 1) // out
    {
        return stdmicro::GPIO::Output;
    }
    return stdmicro::GPIO::Input;

}

void RP2040_GPIO::put(bool up) const
{
    gpio_put(mPin, up);
}

void RP2040_GPIO::pullUp(void) const
{
    gpio_pull_up(mPin);
}

void RP2040_GPIO::pullDown(void) const
{
    gpio_pull_down(mPin);
}

RP2040_GPIO::operator bool(void) const
{
    return gpio_get(mPin);
}

bool RP2040_GPIO::isPulledUp(void) const
{
    return gpio_is_pulled_up(mPin);
}

bool RP2040_GPIO::isPulledDown(void) const
{
    return gpio_is_pulled_down(mPin);
}

} // stdmicro::processor::RP2040
