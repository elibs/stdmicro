#include "EmBox.h"
#include "Led.h"

EmBox::EmBox(points dimensions, Canvas* canvas):
    mX(0),
    mY(0),
    mCY(dimensions),
    mCanvas(canvas),
    mDimensions(dimensions),
    mMult(dimensions / MAX_EM)
{
}

EmBox::~EmBox(void)
{
}
