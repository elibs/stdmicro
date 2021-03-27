#ifndef __STD_MICRO_RP2040_GPIO_H
#define __STD_MICRO_RP2040_GPIO_H

#include "types.h"

#include "GPIO.h"

class RP2040_GPIO: public GPIO
{
public:
    RP2040_GPIO(size_t gpioPin, GPIO::Function func, GPIO::Direction dir);
    virtual ~RP2040_GPIO(void);

    virtual void put(bool up) const override;
    virtual void pullUp(void) const override;
    virtual void pullDown(void) const override;

    virtual void function(GPIO::Function func) const override;
    virtual void direction(GPIO::Direction dir) const override;
    virtual GPIO::Direction direction(void) const override;

    virtual operator bool(void) const override;
    virtual bool isPulledUp(void) const override;
    virtual bool isPulledDown(void) const override;
private:
    size_t mPin;

};

#endif
