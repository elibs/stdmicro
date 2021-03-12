#include "Led.h"
#include "hardware/display/eink/gd7965/GD7965.h"
#include "Font.h"
#include "Path.h"
#include "DejaVuSans.h"
#include "DejaVuSerif.h"
#include "Frequencies.h"

#include "hardware/processor/rp2040/RP2040_I2C.h"
#include "hardware/processor/rp2040/RP2040_SPI.h"
#include "hardware/processor/rp2040/RP2040_GPIO.h"

#include "hardware/RTC/ds3231/DS3231.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"
#include "hardware/regs/io_bank0.h"
#include "hardware/xosc.h"

// Suggested that CPOL = 0 and CPHL = 0

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

    //rtc.write({
    //    .second = 5,
    //    .minute = 18,
    //    .hour = 17,
    //    .dayOfMonth = 26,
    //    .month = 2,
    //    .year = 2021,
    //    .dayOfWeek = 5,
    //    .dayOfYear = 57,
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

    RP2040_GPIO alarm(15, GPIO::SIO, GPIO::Input);
    int draw = 0;
    while (true)
    {
        rtc.read(t);
        mysprintf(timestampbuf, "Latest: %d-%d-%d@%d:%d:%d %s\n%d", t.year, t.month, t.dayOfMonth, t.hour > 12 ? t.hour - 12 : t.hour, t.minute, t.second, t.hour > 12 ? "PM" : "AM", ++draw);
        f.write(timestampbuf);
        eink.restart();
        eink.drawPartial(c2.get(), c2.size(), 0, 100, c2.width(), c2.height());
        eink.powerOff();

        rtc.read(t);
        t.second += 10;
        RTC::AlarmError err = rtc.setAlarm(0, t, 0x0e);
        if (err != RTC::E_ALL_GOOD)
        {
            blink(&led, 4, 10000);
            panic("Wat");
        }

        while (!alarm)
        {
            sleep_ms(100);
            blink(&led, 1);
        }
        
        blink(&led, 40);
        rtc.clearAlarm(1);
        c2.clear();
        f.reset();
    }


    /*
    size_t offset = 1;
    const char* str = R"__(# Chapter One of Stormlight Four

> _First, you must get a spren to approach.
> 
> The type of gemstone is relevant to this, as some spren are naturally more intrigued by certain gemstones. More importantly, it is essential to provide the spren with something it knows and loves. The spren must be made to feel calm. A good fire for a flamespren, for example, is a must._
> 
> -Lecture on Fabrial Mechanics as presented by Navani Kholin to the Coalition of Monarchs, Urithiru.

Lirin was impressed at how calm he felt as he checked the child’s gums for scurvy. Years of training as a surgeon served him well today. Breathing exercises-intended to keep his hands steady-worked just as well for harboring fugitives as they did for surgery.

"Here," he said to the child's mother, digging from his pocket a small carved carapace chit. "Show this to woman at the dining pavilion. She'll get you some juice for your son. Make certain he drinks it all, each morning."

"Very thank you," the woman said in a thick Herdazian accent. She gathered her son close, then looked to Lirin with haunted eyes. "If... if child... found..."

"I will make certain you're notified if we hear word of your other children," Lirin promised. "I'm sorry for your loss."

She nodded, wiped her cheeks, and carried the child toward the town. The morning fog obscured Hearthstone, so from the outside, it seemed a group of dark, shadowy lumps. Like tumors. Lirin could barely make out the tarps stretched between buildings, offering meager shelter for the many refugees pouring out of Herdaz. Entire streets were closed off, and phantom sounds-plates clinking, people talking-rose through the fog.

Those shanties would never last a storm, of course, but could be quickly torn down and stowed. There just wasn't enough housing otherwise. He glanced at the line of those waiting for admittance today. Storms. How many more could the town hold? The villages closer to the border must be filled to capacity, if so many were making their way to Hearthstone.

It had been over a year since the coming of the Everstorm and the fall of Alethkar. A year during which the country of Herdaz-Alethkar's small cousin to the north west-had somehow kept fighting. Two months ago, the enemy had finally decided to crush Herdaz for good, and that's when the refugees had started appearing. Like usual, the soldiers fought while the common people-their fields trampled-starved and were forced out of their homes, looking to escape the conflict.
    )__";


    blink(&led, 7, 100);
    //for (int i = 8; i < 30 && offset != 0; ++i)
    //{
    //    f.setFontSize(1.73 * i);
        offset = f.write(str);
    //}
    blink(&led, 7, 100);

    eink.restart();
    eink.draw(c.get(), c.size());
    eink.powerOff();
    */

    // Finally, blink the LED to say we are done.
    blink(&led, 10, 100);
    while (1)
    {
        sleep_ms(1000);
    }
}
