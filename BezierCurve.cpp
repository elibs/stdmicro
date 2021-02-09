#include "BezierCurve.h"

BezierCurve::BezierCurve(coord a, coord b):
    mSize(2),
    mCoords{a, b, {}}
{
}

BezierCurve::BezierCurve(coord a, coord mid1, coord b):
    mSize(3),
    mCoords{a, mid1, b}
{
}

float abs(float a)
{
    if (a < 0)
    {
        return -a;
    }
    return a;
}

void drawLine(EmBox* box, coord a, coord b)
{
    points x;
    points y;
    if (a.x == b.x)
    {
        x = a.x;
        y = a.y;
        int dy = y < b.y ? 1 : -1;
        for (; y != b.y; y += dy)
        {
            box->set(x, y);
        }
    }
    else if (a.y == b.y)
    {
        x = a.x;
        y = a.y;
        int dx = x < b.x ? 1 : -1;
        for (; x != b.x; x += dx)
        {
            box->set(x, y);
        }
    }
    else
    {
        points dt;
        points t0 = abs(b.x - a.x);
        points t1 = abs(b.y - a.y);
        if (t0 < t1)
        {
            t0 = t1;
        }

        for (float i = 0; i < t0; ++i)
        {
            t1 = i / t0;
            dt = 1.0 - t1;
            x = dt * a.x + t1 * b.x;
            y = dt * a.y + t1 * b.y;
            box->set(x, y);
        }
    }
}

void BezierCurve::draw(EmBox* box)
{
    if (mSize == 2)
    {
        drawLine(box, mCoords[0], mCoords[1]);
        return;
    }

    points x;
    points y;
    points t0;
    points t1;
    points dt;
    points t2;
    points t3;
    coord prev = mCoords[0];
    const float divisor = box->maxSegments();
    BezierCurve curve(prev, prev);
    for(points i = 0.0; i < divisor; ++i)
    {
        t0 = i / divisor;
        dt = 1.0 - t0;
        t1 = square(dt);
        t2 = 2.0 * (dt) * t0;
        t3 = square(t0);
        x = t1 * mCoords[0].x + t2 * mCoords[1].x + t3 * mCoords[2].x;
        y = t1 * mCoords[0].y + t2 * mCoords[1].y + t3 * mCoords[2].y;

        curve.mCoords[0] = prev;
        curve.mCoords[1] = {x, y};
        curve.draw(box);
        prev = {x, y};
    }

    curve.mCoords[0] = prev;
    curve.mCoords[1] = mCoords[mSize - 1];
    curve.draw(box);
}
