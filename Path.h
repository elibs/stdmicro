#ifndef __PATH_H
#define __PATH_H

#include "common.h"
#include "FontCommon.h"
#include "BezierCurve.h"

class Path
{
public:
    ~Path(void);

    static Path start(coord xy);

    Path* line(coord xy);

    Path* horizontal(em delta);

    Path* vertical(em delta);

    Path* quadratic(coord anchorDelta, coord shift);

    void close(Path* origin);

    void drawTo(EmBox* box);

private:
    coord mXY;
    BezierCurve* mCurve;
    Path* mNext;

    Path(coord xy, BezierCurve* curve = NULL);
};

#endif
