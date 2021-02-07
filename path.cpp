#include "path.h"
#include "led.h"

Path::~Path(void)
{
    delete mCurve;
    delete mNext;
}

Path Path::start(coord xy)
{
    return Path(xy);
}

Path* Path::line(coord xy)
{
    coord next{mXY.x + xy.x, mXY.y + xy.y};
    mNext = new Path(next, new BezierCurve(mXY, next));
    return mNext;
}

Path* Path::horizontal(em delta)
{
    return line({delta, 0});
}

Path* Path::vertical(em delta)
{
    return line({0, delta});
}

Path* Path::quadratic(coord anchorDelta, coord shift)
{
    coord next{mXY.x + shift.x, mXY.y + shift.y};
    coord anchor{mXY.x + anchorDelta.x, mXY.y + anchorDelta.y};
    mNext = new Path(next, new BezierCurve(mXY, anchor, next));
    return mNext;
}

Path* Path::t(coord shift)
{
    coord anchorDelta = mCurve->anchorEndDelta();
    coord next{mXY.x + shift.x, mXY.y + shift.y};
    coord anchor{mXY.x + anchorDelta.x, mXY.y + anchorDelta.y};
    mNext = new Path(next, new BezierCurve(mXY, anchor, next));
    return mNext;
}

void Path::close(Path* origin)
{
    mNext = new Path(origin->mXY, new BezierCurve(mXY, origin->mXY));
}

void Path::drawTo(EmBox* box)
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

Path::Path(coord xy, BezierCurve* curve):
    mXY(xy),
    mCurve(curve),
    mNext(NULL)
{
}
