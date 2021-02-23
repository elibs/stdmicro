#ifndef __EM_BOX_H
#define __EM_BOX_H

#include "Canvas.h"
#include "FontCommon.h"

class EmBox
{
public:
    EmBox(points dimensions, Canvas* canvas);

    virtual ~EmBox(void);

    constexpr inline int maxSegments(void) const
    {
        return 5;
    }

    inline int xToCanvas(points x)
    {
        return mX + (x * mMult);
    }

    inline int yToCanvas(points y)
    {
        return mCY - (y * mMult);
    }

    inline void setRaw(int x, int y)
    {
        mCanvas->set(x, y);
    }

    inline void set(points x, points y)
    {
        mCanvas->set(mX + (x * mMult), mCY - (y * mMult));
    }

protected:
    size_t mX;
    size_t mY;
    float mCY;
    Canvas* mCanvas;
    points mDimensions;
    points mMult;
};

#endif
