#include "Led.h"
#include "Font.h"
#include "Path.h"
#include "DejaVuSans.h"
#include "DejaVuSerif.h"
#include "Frequencies.h"

#include "hardware/processor/rp2040/RP2040_I2C.h"
#include "hardware/processor/rp2040/RP2040_SPI.h"
#include "hardware/processor/rp2040/RP2040_GPIO.h"

#include "hardware/display/eink/gd7965/GD7965.h"
#include "hardware/RTC/ds3231/DS3231.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/xosc.h"

// // Just for a note:
//      Name      GPIO // PIN
#define POWER          // 36 // 3.3v
#define GROUND         // 3  // GND

#define MISO_PIN  4    // 6  // ???   // Unused? (display won't write us back)
#define CS_PIN    5    // 7  // CS    // chip select (low active)
#define SCK_PIN   2    // 4  // SCK   // communications clock
#define MOSI_PIN  3    // 5  // DIN   // should be the data out (from us) pin

#define BUSY_PIN  6    // 9  // BUSY  // low for busy
#define RESET_PIN 7    // 10 // RESET // low for reset
#define DC_PIN    8    // 11 // DC    // Data (high), Command (low)

#define LED_PIN   25

int m_i2a(char* out, unsigned int i, unsigned int base = 10);

/**
 * Ancient code I wrote _way_ ago, probably should be rewritten, but was good
 * enough for a quick sprintf for RTC drawing examples.
 *
 * Can be found on dreamincode.net
 */
void mysprintf(char *out, const char *fmt, ...)
{
    char* args = (char*)(&fmt + 1);
    char* s;
    while(*fmt)
    {
        if(*fmt == '%')
        {
            switch(*++fmt)
            {
                case('%'):
                    *out = '%';
                    break;
                case('c'):
                    *out = *(char*)args;
                    args += sizeof(char*);
                    break;
                case('d'):
                case('i'):
                    out += m_i2a(out, *(int*)args) - 1;
                    args += sizeof(int*);
                    break;
                case('x'):
                    out += m_i2a(out, *(int*)args, 16) - 1;
                    args += sizeof(int*);
                    break;
                case('o'):
                    break;
                case('p'):
                    break;
                case('s'):
                    s = (char*)(*(char**)args);
                    while (*s)
                    {
                        *out++ = *s++;
                    }
                    args += sizeof(char**);
                    if (*out == '\0')
                    {
                        --out;
                    }
                    break;
                case('u'):
                    break;
                default:
                    break;
            }
        }
        else
        {
            *out = *fmt;
        }
        out++;
        fmt++;
    }
    *out = '\0';
}

int m_i2a(char* out, unsigned int num, unsigned int base)
{
    bool neg = false;
    const char* table = "0123456789abcdef";
    if((num & (1 << 31)) && base == 10)
    {
        *out++ = '-';
        neg = num *= -1;
    }
    int digits;
    int numc = num;
    for(digits = numc == 0 ? 1 : 0; numc != 0; digits++, numc /= base);
    for(int i = 0; i < digits; i++)
    {
        unsigned int p = 1;
        for(int j = 1; j < digits - i; j++, p *= base);
        *out++ = table[((num / p) % base)];
    }
    return digits + (neg ? 1 : 0);
}

/**
 * This example of how to fall to dormant mode until a GPIO is pulled to a
 * specific state is courtesy of raspberrypi/pico-extras, modified slightly to
 * simplify for this use case.
 *
 * Github:
 * https://github.com/raspberrypi/pico-extras
 *
 * The associated license information:
 *
 * Copyright 2020 (c) 2020 Raspberry Pi (Trading) Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
 *    disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
 *    disclaimer in the documentation and/or other materials provided with the distribution.
 * 
 * 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
void sleep_goto_dormant_until_pin(uint gpio_pin, bool edge, bool high) {
    bool low = !high;
    bool level = !edge;

    // Configure the appropriate IRQ at IO bank 0
    assert(gpio_pin < NUM_BANK0_GPIOS);

    uint32_t event = 0;

    if (level && low) event = IO_BANK0_DORMANT_WAKE_INTE0_GPIO0_LEVEL_LOW_BITS;
    if (level && high) event = IO_BANK0_DORMANT_WAKE_INTE0_GPIO0_LEVEL_HIGH_BITS;
    if (edge && high) event = IO_BANK0_DORMANT_WAKE_INTE0_GPIO0_EDGE_HIGH_BITS;
    if (edge && low) event = IO_BANK0_DORMANT_WAKE_INTE0_GPIO0_EDGE_LOW_BITS;

    gpio_set_dormant_irq_enabled(gpio_pin, event, true);

    xosc_dormant();
    // Execution stops here until woken up

    // Clear the irq so we can go back to dormant mode again if we want
    gpio_acknowledge_irq(gpio_pin, event);
}

int main()
{
    RP2040_GPIO led(LED_PIN, GPIO::SIO, GPIO::Output);

    RP2040_I2C i2c(i2c1, I2CPins{.sck = 10, .sda = 11}, 100_KHz);
    DS3231 rtc(&i2c);

    /**
     * Example of how to write out the date and time to a RTC device.
     */
    //rtc.write({
    //    .second = 0,
    //    .minute = 11,
    //    .hour = 9 + 12,
    //    .dayOfMonth = 11,
    //    .month = 3,
    //    .year = 2021,
    //    .dayOfWeek = 4,
    //    .isDaylightSavingsTime = 0
    //});

    blink(&led, 1);
    RP2040_SPI spi(spi0, {
        .cs = CS_PIN,
        .miso = MISO_PIN,
        .mosi = MOSI_PIN,
        .sck = SCK_PIN
    }, 20_MHz);
    blink(&led, 2, 100);
    RP2040_GPIO displayResetPin(RESET_PIN, GPIO::SIO, GPIO::Output);
    blink(&led, 2, 100);
    RP2040_GPIO displayBusyPin(BUSY_PIN, GPIO::SIO, GPIO::Input);
    blink(&led, 2, 100);
    RP2040_GPIO displayDataCmdPin(DC_PIN, GPIO::SIO, GPIO::Output);
    blink(&led, 2, 100);

    GD7965 eink(&spi, &displayDataCmdPin, &displayBusyPin, &displayResetPin);
    blink(&led, 2);

    Canvas c(800, 480);
    DejaVuSans dvs;
    Font f(&dvs, 16_pt);
    f.setCanvas(&c);

    f.write("Test   ");
    eink.init();
    eink.draw(c.get(), c.size());

    eink.powerOff();
    blink(&led, 3);

    char timestampbuf[50];

    tm t;
    rtc.read(t);
    mysprintf(timestampbuf, "Date: %d-%d-%d@%d:%d:%d %s", t.year, t.month, t.dayOfMonth, t.hour > 12 ? t.hour - 12 : t.hour, t.minute, t.second, t.hour > 12 ? "PM" : "AM");

    f.write(timestampbuf);
    eink.restart();
    eink.draw(c.get(), c.size());
    eink.powerOff();

    Canvas c2(800, 120);
    f.setCanvas(&c2);

    rtc.enableInterrupt();
    rtc.clearAlarm(0);
    rtc.clearAlarm(1);
    rtc.disableAlarm(0);
    rtc.disableAlarm(1);

    RTC::AlarmError err = rtc.setAlarm(1, t, RTC::EACH_MINUTE | RTC::EACH_HOUR | RTC::EACH_DAY);
    if (err != RTC::E_ALL_GOOD)
    {
        blink(&led, 4, 10000);
        panic("Wat");
    }

    RP2040_GPIO alarm(15, GPIO::SIO, GPIO::Input);
    alarm.pullUp();
    int draw = 0;
    while (true)
    {
        rtc.read(t);
        for (int i = 0; i < 50; ++i)
        {
            timestampbuf[i] = '\0';
        }
        mysprintf(timestampbuf, " %d: %d-%d-%d@%d:%d:%d %s\n%d", ++draw, t.year, t.month, t.dayOfMonth, t.hour > 12 ? t.hour - 12 : t.hour, t.minute, t.second, t.hour > 12 ? "PM" : "AM");
        f.write(timestampbuf);
        eink.restart();
        eink.drawPartial(c2.get(), c2.size(), 0, 100, c2.width(), c2.height());
        eink.powerOff();

        sleep_goto_dormant_until_pin(15, true, false);
        
        rtc.clearAlarm(1);
        alarm.pullUp();
        c2.clear();
        f.reset();
    }

    // Finally, blink the LED to say we are done.
    blink(&led, 10, 100);
    while (true)
    {
        sleep_ms(1000);
    }
}
