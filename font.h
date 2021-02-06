#ifndef __FONT_H
#define __FONT_H

#include "common.h"
#include "canvas.h"

#define MAX_EM 2000.0

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
    return 0.353 * value;
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

    inline void set(size_t x, size_t y)
    {
        if (x > mDimensions || y > mDimensions)
        {
            return;
        }

        mCanvas->set(x, y, 0);
    }

    inline void clear(size_t x, size_t y)
    {
        if (x > mDimensions || y > mDimensions)
        {
            return;
        }

        mCanvas->set(x, y, 1);
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


    void draw(EmBox* box)
    {
        points x;
        points y;
        points t0;
        points t1;
        points t2;
        points t3;
        for(points i = 0.0; i < MAX_EM; ++i)
        {
            t0 = i / MAX_EM;
            switch (mSize)
            {
            case 2:
                t1 = 1.0 - t0;
                x = t1 * mCoords[0].x + t0 * mCoords[1].x;
                y = t1 * mCoords[0].y + t0 * mCoords[1].y;
                break;
            case 3:
                t1 = square(1.0 - t0);
                t2 = 2.0 * (1.0 - t0) * t0;
                t3 = square(t0);
                x = t1 * mCoords[0].x + t2 * mCoords[1].x + t3 * mCoords[2].x;
                y = t1 * mCoords[0].y + t2 * mCoords[1].y + t3 * mCoords[2].y;
                break;
            case 4:
                t1 = cube(1.0 - t0);
                t2 = 3.0 * square(1.0 - t0) * t0;
                t3 = 3.0 * (1.0 - t0) * square(t0);
                t0 = cube(t0);
                x = t1 * mCoords[0].x + t2 * mCoords[1].x + t3 * mCoords[2].x + t0 * mCoords[3].x;
                y = t1 * mCoords[0].y + t2 * mCoords[1].y + t3 * mCoords[2].y + t0 * mCoords[3].y;
                break;
            default:
                return;
            }

            box->set(x, y);
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

    size_t write(char* str)
    {
        EmBoxHolder* bounds = new EmBoxHolder(mFontSize, mCanvas);

        size_t i;
        em delta;
        glyph g;
        for (i = 0; str[i]; ++i)
        {
            g = (*mFontFace)[str[i]];
            delta = (*g)(bounds);
            bounds->progressX(delta);
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
