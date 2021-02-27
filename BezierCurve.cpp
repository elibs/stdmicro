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

template<typename T>
inline T abs(T a)
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

inline void drawLine(EmBox* box, coord a, coord b)
{
    if (a.x == b.x && a.y == b.y)
    {
        return;
    }

    box->set(a.x, a.y);
    box->set(b.x, b.y);

    int x;
    int y;
    // NOTE: The value of `additive` is (72 * MAX_EM) / (DISPLAY_PPI * fontSizePt).
    //       72 appears magic, but is based on the definition of pt (points), where
    //       72pt == 1 inch on physical medium.
    //       So, 147 = (72 * 2048) / (125 * 8)
    //               = 147456 / 1000
    const int additive = 74; // 8pt -> 147, 12pt -> 98;
    if (a.x == b.x)
    {
        x = box->yToCanvas(a.y);
        y = box->yToCanvas(b.y);
        if (y < x)
        {
            swap(x, y);
        }

        int rawX = box->xToCanvas(a.x);
        for (; x < y; ++x)
        {
            box->setRaw(rawX, x);
        }
    }
    else if (a.y == b.y)
    {
        x = box->xToCanvas(a.x);
        y = box->xToCanvas(b.x);
        if (y < x)
        {
            swap(x, y);
        }

        int rawY = box->yToCanvas(a.y);
        for (; x < y; ++x)
        {
            box->setRaw(x, rawY);
        }
    }
    else
    {
        const points t0 = (b.y - a.y) / (b.x - a.x);
        const int t1 = a.y - (t0 * a.x);

        if (abs(a.x - b.x) >= abs(a.y - b.y))
        {
            x = a.x;
            y = b.x;
            if (y < x)
            {
                swap(x, y);
            }

            for (; x < y; x += additive)
            {
                box->set(x, (t0 * x) + t1);
            }
        }
        else
        {
            x = a.y;
            y = b.y;
            if (y < x)
            {
                swap(x, y);
            }
            // y = mx + b -> x = (y - b) / m;

            for (; x < y; x += additive)
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
    const int divisor = box->maxSegments();
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
