#include "BezierCurve.h"

BezierCurve::BezierCurve(coord a, coord b):
    mSize(2),
    mCoords{a, b, {}, {}}
{
}

BezierCurve::BezierCurve(coord a, coord mid1, coord b):
    mSize(3),
    mCoords{a, mid1, b, {}}
{
}

BezierCurve::BezierCurve(coord a, coord mid1, coord mid2, coord b):
    mSize(4),
    mCoords{a, mid1, mid2, b}
{
}

coord BezierCurve::anchorEndDelta(void) const
{
    switch (mSize)
    {
    case 3:
        return {
            -mCoords[1].x + mCoords[2].x,
            -mCoords[1].y + mCoords[2].y
        };
    default:
        return {0, 0};
    }
}

void BezierCurve::draw(EmBox* box)
{
    points x;
    points y;
    points t0;
    points t1;
    if (mSize == 2)
    {
        if (mCoords[0].x == mCoords[1].x)
        {
            x = mCoords[0].x / MAX_EM;
            y = mCoords[0].y;
            int dy = y < mCoords[1].y ? 1 : -1;
            for (; y != mCoords[1].y; y += dy)
            {
                box->set(x , y / MAX_EM);
            }
        }
        else if (mCoords[0].y == mCoords[1].y)
        {
            x = mCoords[0].x;
            y = mCoords[0].y / MAX_EM;
            int dx = x < mCoords[1].x ? 1 : -1;
            for (; x != mCoords[1].x; x += dx)
            {
                box->set(x / MAX_EM, y);
            }
        }
        else
        {
            points distance = 100;
            for (points i = 0; i < distance; ++i)
            {
                t0 = i / distance;
                t1 = 1.0 - t0;
                x = t1 * mCoords[0].x + t0 * mCoords[1].x;
                y = t1 * mCoords[0].y + t0 * mCoords[1].y;
                box->set(x / MAX_EM, y / MAX_EM);
            }
        }

        return;
    }

    points t2;
    points t3;
    coord prev = mCoords[0];
    const float divisor = 20;
    BezierCurve curve(prev, prev);
    for(points i = 0.0; i < divisor; ++i)
    {
        t0 = i / divisor;
        switch (mSize)
        {
        case 3:
            t1 = square(1.0 - t0);
            t2 = 2.0 * (1.0 - t0) * t0;
            t3 = square(t0);
            x = t1 * mCoords[0].x + t2 * mCoords[1].x + t3 * mCoords[2].x;
            y = t1 * mCoords[0].y + t2 * mCoords[1].y + t3 * mCoords[2].y;
            curve.mCoords[0] = prev;
            curve.mCoords[1] = {x, y};
            curve.draw(box);
            prev = {x, y};
            break;
        case 4:
            t1 = cube(1.0 - t0);
            t2 = 3.0 * square(1.0 - t0) * t0;
            t3 = 3.0 * (1.0 - t0) * square(t0);
            t0 = cube(t0);
            x = t1 * mCoords[0].x + t2 * mCoords[1].x + t3 * mCoords[2].x + t0 * mCoords[3].x;
            y = t1 * mCoords[0].y + t2 * mCoords[1].y + t3 * mCoords[2].y + t0 * mCoords[3].y;
            curve.mCoords[0] = prev;
            curve.mCoords[1] = {x, y};
            curve.draw(box);
            prev = {x, y};
            break;
        default:
            return;
        }

        box->set(x / MAX_EM, y / MAX_EM);
    }
}
