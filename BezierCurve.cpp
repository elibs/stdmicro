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

template<typename T>
inline void swap(T& a, T& b)
{
    T c(a);
    a = b;
    b = c;
}

void drawLine(EmBox* box, coord a, coord b)
{
    points x;
    points y;
    if (a.x == b.x)
    {
        x = a.y;
        y = b.y;
        if (y < x)
        {
            swap(x, y);
        }

        for (; x < y; ++x)
        {
            box->set(a.x, x);
        }
    }
    else if (a.y == b.y)
    {
        x = a.x;
        y = b.x;
        if (y < x)
        {
            swap(x, y);
        }

        for (; x < y; ++x)
        {
            box->set(x, a.y);
        }
    }
    else
    {
        const points t0 = (b.y - a.y) / (b.x - a.x);
        const points t1 = a.y - (t0 * a.x);

        if (abs(a.x - b.x) >= abs(a.y - b.y))
        {
            if (a.x < b.x)
            {
                x = a.x;
                y = b.x;
            }
            else
            {
                y = a.x;
                x = b.x;
            }

            for (; x < y; ++x)
            {
                box->set(x, (t0 * x) + t1);
            }
        }
        else
        {
            // y = mx + b -> x = (y - b) / m;
            if (a.y < b.y)
            {
                x = a.y;
                y = b.y;
            }
            else
            {
                y = a.y;
                x = b.y;
            }

            for (; x < y; ++x)
            {
                box->set((x - t1) / t0, x);
            }
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
    for(points i = 0.0; i < divisor; ++i)
    {
        t0 = i / divisor;
        dt = 1.0 - t0;
        t1 = square(dt);
        t2 = 2.0 * (dt) * t0;
        t3 = square(t0);
        x = t1 * mCoords[0].x + t2 * mCoords[1].x + t3 * mCoords[2].x;
        y = t1 * mCoords[0].y + t2 * mCoords[1].y + t3 * mCoords[2].y;

        drawLine(box, prev, {x, y});
        prev = {x, y};
    }

    drawLine(box, prev, mCoords[mSize - 1]);
}
