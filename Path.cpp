#include "Path.h"
#include "common.h"

Path::~Path(void)
{
    delete mCurve;
    delete mNext;
}

Path Path::start(coord xy)
{
    return Path(xy);
}

Path* Path::line(coord next)
{
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

Path* Path::quadratic(coord anchor, coord next)
{
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
