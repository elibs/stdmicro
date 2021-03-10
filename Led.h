#ifndef __LED_H
#define __LED_H

#include "pico/stdlib.h"

#include "GPIO.h"

void blink(GPIO* led, int count, uint delay = 250);

#endif
