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
