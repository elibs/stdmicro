#ifndef __FONT_H
#define __FONT_H

#include "common.h"
#include "canvas.h"
#include "led.h"

#define MAX_EM 2048.0

/**
 * An em is a unit equal to the font's point size.
 *
 * Points, are a size, measured in seventy-seconds of an inch (approximately
 * 0.353mm), and are used to determine the dimensions of the point square (or,
 * em square), in which each character being rendered fits. 
 */
typedef float em;
typedef float points;

constexpr points operator "" _pt(unsigned long long value)
{
    return 1.73 * value;
}

class EmBox
{
public:
    EmBox(points dimensions, Canvas* canvas):
        mX(0),
        mY(0),
        mCanvas(canvas),
        mDimensions(dimensions)
    {
    }

    virtual ~EmBox(void)
    {
    }

    inline void set(points x, points y)
    {
        if (x > 1 || y > 1)
        {
            hang();
            return;
        }

        mCanvas->set(mX + (x * mDimensions), mY + mDimensions - (y * mDimensions), 0);
    }

    inline void clear(points x, points y)
    {
        if (x > 1 || y > 1)
        {
            hang();
            return;
        }

        mCanvas->set(mX + (x * mDimensions), mY + mDimensions - (y * mDimensions), 1);
    }

protected:
    size_t mX;
    size_t mY;
    Canvas* mCanvas;
    points mDimensions;
};

class EmBoxHolder: public EmBox
{
public:
    EmBoxHolder(points dimensions, Canvas* canvas):
        EmBox(dimensions, canvas)
    {
    }

    virtual ~EmBoxHolder(void)
    {
    }

    inline void progressX(size_t delta)
    {
        mX += delta;
        if (mX >= mCanvas->width())
        {
            mX = 0;
            progressY(mDimensions);
        }
    }

    inline void progressY(size_t delta)
    {
        mY += delta;
        if (mY >= mCanvas->height())
        {
            mY = 0;
        }
    }
};

struct coord
{
    points x;
    points y;
};

class BezierCurve
{
public:
    BezierCurve(coord a, coord b):
        mSize(2),
        mCoords{a, b, {}, {}}
    {
    }

    BezierCurve(coord a, coord mid1, coord b):
        mSize(3),
        mCoords{a, mid1, b, {}}
    {
    }

    BezierCurve(coord a, coord mid1, coord mid2, coord b):
        mSize(4),
        mCoords{a, mid1, mid2, b}
    {
    }

    coord anchorEndDelta(void) const
    {
        switch (mSize)
        {
        case 3:
            return {
                -mCoords[1].x + mCoords[2].x,
                -mCoords[1].y + mCoords[2].y
            };
        default:
            return {0, 0};
        }
    }

    void draw(EmBox* box)
    {
        points x;
        points y;
        points t0;
        points t1;
        if (mSize == 2)
        {
            for (points i = 0; i < MAX_EM; ++i)
            {
                t0 = i / MAX_EM;
                t1 = 1.0 - t0;
                x = t1 * mCoords[0].x + t0 * mCoords[1].x;
                y = t1 * mCoords[0].y + t0 * mCoords[1].y;
                box->set(x / MAX_EM, y / MAX_EM);
            }

            return;
        }

        points t2;
        points t3;
        coord prev = mCoords[0];
        const float divisor = 20;
        BezierCurve curve(prev, prev);
        for(points i = 0.0; i < divisor; ++i)
        {
            t0 = i / divisor;
            switch (mSize)
            {
            case 3:
                t1 = square(1.0 - t0);
                t2 = 2.0 * (1.0 - t0) * t0;
                t3 = square(t0);
                x = t1 * mCoords[0].x + t2 * mCoords[1].x + t3 * mCoords[2].x;
                y = t1 * mCoords[0].y + t2 * mCoords[1].y + t3 * mCoords[2].y;
                curve.mCoords[0] = prev;
                curve.mCoords[1] = {x, y};
                curve.draw(box);
                prev = {x, y};
                break;
            case 4:
                t1 = cube(1.0 - t0);
                t2 = 3.0 * square(1.0 - t0) * t0;
                t3 = 3.0 * (1.0 - t0) * square(t0);
                t0 = cube(t0);
                x = t1 * mCoords[0].x + t2 * mCoords[1].x + t3 * mCoords[2].x + t0 * mCoords[3].x;
                y = t1 * mCoords[0].y + t2 * mCoords[1].y + t3 * mCoords[2].y + t0 * mCoords[3].y;
                curve.mCoords[0] = prev;
                curve.mCoords[1] = {x, y};
                curve.draw(box);
                prev = {x, y};
                break;
            default:
                return;
            }

            box->set(x / MAX_EM, y / MAX_EM);
        }
    }

private:
    size_t mSize;
    coord mCoords[4];

    inline points square(points v)
    {
        return v * v;
    }

    inline points cube(points v)
    {
        return v * v * v;
    }
};

typedef em (*glyph)(EmBox*);

class FontFace
{
public:
    virtual ~FontFace(void)
    {
    }

    virtual glyph operator[](int c) const = 0;
};

class Font
{
public:
    Font(FontFace* face, points fontSize):
        mX(0),
        mY(0),
        mCanvas(NULL),
        mFontFace(face),
        mFontSize(fontSize)
    {
    }

    ~Font(void)
    {
        // We don't own the canvas! Don't delete it!!!
    }

    inline void setCanvas(Canvas* canvas)
    {
        mCanvas = canvas;
        reset();
    }

    inline void reset(void)
    {
        mX = 0;
        mY = 0;
    }

    inline void setFontSize(points size)
    {
        mFontSize = size;
    }

    size_t write(const char* str)
    {
        EmBoxHolder bounds(mFontSize, mCanvas);

        size_t i;
        em delta;
        glyph g;
        for (i = 0; str[i]; ++i)
        {
            g = (*mFontFace)[str[i]];
            delta = (*g)(&bounds);
            bounds.progressX((delta / MAX_EM) * mFontSize);
            blink(i + 1);
        }

        return i;
    }
private:
    size_t mX;
    size_t mY;
    Canvas* mCanvas;
    FontFace* mFontFace;
    points mFontSize;
};

#endif
