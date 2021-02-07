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

    BezierCurve(coord a, coord mid1, coord mid2, coord b);

    coord anchorEndDelta(void) const;

    void draw(EmBox* box);

private:
    size_t mSize;
    coord mCoords[4];

    inline points square(points v)
    {
        return v * v;
    }

    inline points cube(points v)
    {
        return v * v * v;
    }
};

#endif
