#include "Led.h"
#include "Pins.h"
#include "Display.h"
#include "Font.h"
#include "Path.h"
#include "DejaVuSans.h"

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


int main() {
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    blink(1);
    Display eink(800, 480, spi0, {
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

    eink.init();
    eink.off();
    blink(3);

    Canvas c(800, 480);

    size_t offset = 1;
    const char* str = "1234567890 !@#$%^&*() Test\n";

    DejaVuSans dvs;
    Font f(&dvs, 16_pt);
    f.setCanvas(&c);

    blink(7, 100);
    for (int i = 8; i < 30 && offset != 0; ++i)
    {
        f.setFontSize(1.73 * i);
        offset = f.write(str);
    }
    blink(7, 100);

    eink.restart();
    eink.draw(c.get(), c.size());
    eink.off();

    /**
     * Very basic image, will be 8x8 and should be a triangle like so (stars indicating black):
     * ********
     * *******
     * ******
     * *****
     * ****
     * ***
     * **
     * *
     */
    unsigned char image[8] = {
        (unsigned char)0x00,
        (unsigned char)0x01,
        (unsigned char)0x03,
        (unsigned char)0x07,
        (unsigned char)0x0f,
        (unsigned char)0x1f,
        (unsigned char)0x3f,
        (unsigned char)0x7f
    };
    eink.restart();
    eink.drawPartial(image, 8, 5, 5, 8, 8);
    blink(8);

    eink.off();

    // Finally, blink the LED to say we are done.
    blink(10, 100);
    sleep_ms(-1);
}
