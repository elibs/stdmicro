#ifndef __LED_H
#define __LED_H

#include "pico/stdlib.h"

#define LED_PIN 25

void blink(int count, uint delay = 250);

void hang(void);

#endif
