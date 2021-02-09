#ifndef __EM_BOX_H
#define __EM_BOX_H

#include "Canvas.h"
#include "FontCommon.h"

class EmBox
{
public:
    EmBox(points dimensions, Canvas* canvas);

    virtual ~EmBox(void);

    int maxSegments(void) const;

    void set(points x, points y);

protected:
    size_t mX;
    size_t mY;
    Canvas* mCanvas;
    points mDimensions;
    int mSegments;
    points mMult;
};

#endif
