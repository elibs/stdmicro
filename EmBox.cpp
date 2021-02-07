#include "EmBox.h"
#include "Led.h"

EmBox::EmBox(points dimensions, Canvas* canvas):
    mX(0),
    mY(0),
    mCanvas(canvas),
    mDimensions(dimensions)
{
}

EmBox::~EmBox(void)
{
}

em EmBox::maxSegments(void) const
{
    return mDimensions / 2.;
}

void EmBox::set(points x, points y)
{
    if (x > 1 || y > 1)
    {
        hang();
        return;
    }

    mCanvas->set(mX + (x * mDimensions), mY + mDimensions - (y * mDimensions), 0);
}

void EmBox::clear(points x, points y)
{
    if (x > 1 || y > 1)
    {
        hang();
        return;
    }

    mCanvas->set(mX + (x * mDimensions), mY + mDimensions - (y * mDimensions), 1);
}
