#ifndef __LED_H
#define __LED_H

#include "GPIO.h"

void blink(GPIO* led, int count, unsigned int delay = 250);

#endif
