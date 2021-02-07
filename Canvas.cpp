#include "Canvas.h"

Canvas::Canvas(size_t width, size_t height):
    mWidth(width),
    mHeight(height),
    mSize((width / 8) * height),
    mBuffer(new unsigned char[(width / 8) * height])
{
    clear();
}

Canvas::~Canvas(void)
{
    delete mBuffer;
}

void Canvas::set(size_t x, size_t y, unsigned char color)
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
