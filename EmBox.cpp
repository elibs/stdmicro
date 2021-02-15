#include "EmBox.h"
#include "Led.h"

EmBox::EmBox(points dimensions, Canvas* canvas):
    mX(0),
    mY(0),
    mCY(dimensions),
    mCanvas(canvas),
    mDimensions(dimensions),
    mSegments(dimensions / 24),
    mMult(dimensions / MAX_EM)
{
}

EmBox::~EmBox(void)
{
}

int EmBox::maxSegments(void) const
{
    return mSegments;
}

void EmBox::set(points x, points y)
{
    mCanvas->set(mX + (x * mMult), mCY - (y * mMult));
}
