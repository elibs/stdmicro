#include "Led.h"
#include "Pins.h"
#include "GD7965.h"
#include "Font.h"
#include "Path.h"
#include "DejaVuSans.h"
#include "DejaVuSerif.h"
#include "Frequencies.h"

#include "RP2040_I2C.h"

#include "DS3231.h"

#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/spi.h"

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

int m_i2a(char* out, unsigned int i, unsigned int base = 10);

void mysprintf(char *out, const char *fmt, ...)
{
    char* args = (char*)(&fmt + 1);
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

int main()
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    RP2040_I2C i2c(i2c1, RP2040_I2C_Pins{.sck = 10, .sda = 11}, 100_KHz);
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

    blink(1);
    GD7965 eink(800, 480, spi0, {
        .spi = {
            .miso = MISO_PIN,
            .cs = CS_PIN,
            .sck = SCK_PIN,
            .mosi = MOSI_PIN
        },
        .dc = DC_PIN,
        .busy = BUSY_PIN,
        .reset = RESET_PIN
    });
    blink(2);

    Canvas c(800, 480);
    DejaVuSans dvs;
    Font f(&dvs, 16_pt);
    f.setCanvas(&c);

    eink.init();
    f.write("Test   ");
    eink.draw(c.get(), c.size());

    eink.powerOff();
    blink(3);

    char timestampbuf[50];

    tm t;
    rtc.read(t);
    mysprintf(timestampbuf, "Date: %d-%d-%d@%d:%d:%d %s", t.year, t.month, t.dayOfMonth, t.hour > 12 ? t.hour - 12 : t.hour, t.minute, t.second, t.hour > 12 ? "PM" : "AM");

    f.write(timestampbuf);
    eink.restart();
    eink.draw(c.get(), c.size());
    eink.powerOff();


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


    blink(7, 100);
    //for (int i = 8; i < 30 && offset != 0; ++i)
    //{
    //    f.setFontSize(1.73 * i);
        offset = f.write(str);
    //}
    blink(7, 100);

    eink.restart();
    eink.draw(c.get(), c.size());
    eink.powerOff();
    */

    // Finally, blink the LED to say we are done.
    blink(10, 100);
    while (1)
    {
        sleep_ms(1000);
    }
}
