#ifndef __BEZIER_CURVE_H
#define __BEZIER_CURVE_H

#include "FontCommon.h"
#include "EmBox.h"

struct coord
{
    points x;
    points y;
};

class BezierCurve
{
public:
    BezierCurve(coord a, coord b);

    BezierCurve(coord a, coord mid1, coord b);

    void draw(EmBox* box);

private:
    unsigned char mSize;
    coord mCoords[3];

    inline points square(points v)
    {
        return v * v;
    }
};

#endif
