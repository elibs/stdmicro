#ifndef __CANVAS_H
#define __CANVAS_H

#include "common.h"

typedef float mm;

class Canvas
{
public:
    Canvas(size_t width, size_t height):
        mWidth(width),
        mHeight(height),
        mSize((width / 8) * height),
        mBuffer(new unsigned char[(width / 8) * height])
    {
        clear();
    }

    ~Canvas(void)
    {
        delete mBuffer;
    }

    inline void set(size_t x, size_t y, unsigned char color)
    {
        if (color)
        {
            mBuffer[(y * (mWidth >> 3)) + (x >> 3)] |= 1 << (7 - (x & 0x07));
        }
        else
        {
            mBuffer[(y * (mWidth >> 3)) + (x >> 3)] &= ~(1 << (7 - (x & 0x07)));
        }
    }

    inline const unsigned char* get(void) const
    {
        return mBuffer;
    }

    inline size_t size(void) const
    {
        return mSize;
    }

    inline void clear(void)
    {
        for (size_t i = 0; i < mSize; ++i)
        {
            mBuffer[i] = 0xff;
        }
    }

    inline size_t width(void) const
    {
        return mWidth;
    }

    inline size_t height(void) const
    {
        return mHeight;
    }

private:
    size_t mWidth;
    size_t mHeight;
    size_t mSize;
    unsigned char* mBuffer;
};

#endif
