#include "led.h"
#include "pins.h"
#include "display.h"
#include "font.h"

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

class Path
{
public:
    ~Path(void)
    {
        delete mCurve;
        delete mNext;
    }

    static Path start(coord xy)
    {
        return Path(xy);
    }

    Path* line(coord xy)
    {
        coord next{mXY.x + xy.x, mXY.y + xy.y};
        mNext = new Path(next, new BezierCurve(mXY, next));
        return mNext;
    }

    Path* horizontal(em delta)
    {
        return line({delta, 0});
    }

    Path* vertical(em delta)
    {
        return line({0, delta});
    }

    Path* quadratic(coord anchorDelta, coord shift)
    {
        coord next{mXY.x + shift.x, mXY.y + shift.y};
        coord anchor{mXY.x + anchorDelta.x, mXY.y + anchorDelta.y};
        mNext = new Path(next, new BezierCurve(mXY, anchor, next));
        return mNext;
    }

    Path* t(coord shift)
    {
        coord anchorDelta = mCurve->anchorEndDelta();
        coord next{mXY.x + shift.x, mXY.y + shift.y};
        coord anchor{mXY.x + anchorDelta.x, mXY.y + anchorDelta.y};
        mNext = new Path(next, new BezierCurve(mXY, anchor, next));
        return mNext;
    }

    void close(Path* origin)
    {
        mNext = new Path(origin->mXY, new BezierCurve(mXY, origin->mXY));
    }

    void drawTo(EmBox* box)
    {
        for (Path* cursor = mNext; cursor; cursor = cursor->mNext)
        {
            if (!cursor->mCurve)
            {
                return;
            }

            cursor->mCurve->draw(box);
        }
    }

private:
    coord mXY;
    BezierCurve* mCurve;
    Path* mNext;

    Path(coord xy, BezierCurve* curve = NULL):
        mXY(xy),
        mCurve(curve),
        mNext(NULL)
    {
    }
};

class DejaVusSans: public FontFace
{
public:
    virtual ~DejaVusSans(void)
    {
    }

    glyph operator[](int c) const override
    {
        switch (c)
        {
            case 'A':
                return A;
            case 'B':
                return B;
            default:
                return None;
        }
    }
private:

    static em None(EmBox* box)
    {
        return 0;
    }

    static em A(EmBox* box)
    {
        // d="M700 1294
        // l-274 -743
        // h549
        // z
        // M586 1493
        // h229
        // l569 -1493
        // h-210
        // l-136 383
        // h-673
        // l-136 -383
        // h-213
        // z" />
        Path inner = Path::start({700, 1294});
        inner.line({-274, -743})->horizontal(549)->close(&inner);

        Path outer = Path::start({586, 1493});
        outer.horizontal(229)->line({569, -1493})->horizontal(-210)->line({-136, 383})->horizontal(-673)->line({-136, -383})->horizontal(-213)->close(&outer);

        inner.drawTo(box);
        outer.drawTo(box);

        return 1401.0 / MAX_EM;
    }

    static em B(EmBox* box)
    {
        // M403 713
        // v-547
        // h324
        // q163 0 241.5 67.5
        // t78.5 206.5
        // q0 140 -78.5 206.5
        // t-241.5 66.5
        // h-324
        // z
        //
        // M403 1327
        // v-450
        // h299
        // q148 0 220.5 55.5
        // t72.5 169.5
        // q0 113 -72.5 169
        // t-220.5 56
        // h-299
        // z
        //
        // M201 1493
        // h516
        // q231 0 356 -96
        // t125 -273
        // q0 -137 -64 -218
        // t-188 -101
        // q149 -32 231.5 -133.5 
        // t82.5 -253.5
        // q0 -200 -136 -309
        // t-387 -109
        // h-536v1493
        // z
        Path inner1 = Path::start({403, 713});
        inner1.vertical(-547)->horizontal(324)->quadratic({163, 0}, {241.5, 67.5})->t({78.5, 206.5})->quadratic({0, 140}, {-78.5, 206.5})->t({-241.5, 66.5})->horizontal(-324)->close(&inner1);

        Path inner2 = Path::start({403, 1327});
        inner2.vertical(-450)->horizontal(299)->quadratic({148, 0}, {220.5, 55.5})->t({72.5, 169.5})->quadratic({0, 113}, {-72.5, 169})->t({-220.5, 56})->horizontal(-299)->close(&inner2);

        Path outer = Path::start({201, 1493});
        outer.horizontal(516)->quadratic({231, 0}, {356, -96})->t({125, -273})->quadratic({0, -137}, {-64, -218})->t({-188, -101})->quadratic({149, -32}, {231.5, -133.5})->t({82.5, -253.5})->quadratic({0, -200}, {-136, -309})->t({-387, -109})->horizontal(-536)->vertical(1493)->close(&outer);

        inner1.drawTo(box);
        inner2.drawTo(box);
        outer.drawTo(box);

        return 1405.0 / MAX_EM;
    }
};

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
    blink(3);

    Canvas c(800, 840);
    blink(4, 100);
    // Flood it to black.
    for (int x = 0; x < c.width(); x += 8)
    {
        for (int y = 0; y < c.height(); ++y)
        {
            c.set(x, y, 0);
        }
    }

    //blink(4);
    //eink.clear();

    blink(4);
    eink.draw(c.get(), c.size());

    blink(5);
    eink.off();
    blink(6);

    eink.restart();
    blink(7);


    DejaVusSans dvs;
    Font f(&dvs, 16_pt);
    f.setCanvas(&c);
    f.write("A");

    f.setFontSize(72_pt);
    f.write("ABA");

    eink.draw(c.get(), c.size());

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
    eink.drawPartial(image, 8, 5, 5, 8, 8);
    blink(8);

    eink.off();

    // Finally, blink the LED to say we are done.
    blink(10, 100);
    sleep_ms(-1);
}
