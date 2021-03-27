#ifndef __STD_MICRO_GPIO_H
#define __STD_MICRO_GPIO_H

namespace stdmicro
{

class GPIO
{
public:
    /**
     * GPIO direction. It is worth noting that this can realistically be an
     * input or output, but some microcontrollers may allow bidirectional
     * communications, so we haven't ruled them out.
     */
    enum Direction
    {
        Input,
        Output,
        Bidirectional
    };

    /**
     * The function of the GPIO pin.
     *
     * GPCK: GPIO Clock
     * I2C: i2c interface
     * PIO: Programmable Input/Output
     * PWM: Pulse-width modulation
     * SIO: Single-cycle Input/Output
     * SPI: Serial Peripheral Interface
     * UART: Universal Asynchronous Receiver-Transmitter
     * USB: Universal Serial Bus
     * XIP: Execute In Place
     */
    enum Function
    {
        None,
        GPCK,
        I2C,
        PIO,
        PIO0,
        PIO1,
        PWM,
        SIO,
        SPI,
        UART,
        USB,
        XIP
    };

    /**
     * Set the function of the GPIO pin
     */
    virtual void function(Function purpose) const = 0;

    /**
     * Set the GPIO to a value (high, or low). Depending on the function of the
     * GPIO, it is possible that it will stay that way, or just be there for a
     * cycle.
     *
     * @param up True to put the GPIO high, false to put it low.
     */
    virtual void put(bool up) const = 0;

    /**
     * Pull the pin high
     */
    virtual void pullUp(void) const = 0;

    /**
     * Pull the pin low
     */
    virtual void pullDown(void) const = 0;

    /**
     * Set the direction of the pin (input, or output).
     */
    virtual void direction(Direction dir) const = 0;

    /**
     * Retireve the direction of the pin.
     */
    virtual Direction direction(void) const = 0;

    /**
     * @returns True if the pin is currently high, false otherwise.
     */
    virtual operator bool(void) const = 0;

    /**
     * @returns True if the pin is pulled high, false otherwise.
     */
    virtual bool isPulledUp(void) const = 0;

    /**
     * @returns True if the pin is pulled low, false otherwise.
     */
    virtual bool isPulledDown(void) const = 0;
};

} // stdmicro

#endif
