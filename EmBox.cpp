#include "EmBox.h"
#include "Led.h"

EmBox::EmBox(points dimensions, Canvas* canvas):
    mX(0),
    mY(0),
    mCanvas(canvas),
    mDimensions(dimensions),
    mSegments(dimensions / 70),
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
    if (x < -MAX_EM || x > MAX_EM || y < -MAX_EM || y > MAX_EM)
    {
        hang();
        return;
    }

    mCanvas->set(mX + (x * mMult), mY + mDimensions - (y * mMult), 0);
}
