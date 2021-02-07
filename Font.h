#ifndef __FONT_H
#define __FONT_H

#include "common.h"
#include "Canvas.h"
#include "Led.h"
#include "EmBox.h"
#include "FontFace.h"

class EmBoxHolder: public EmBox
{
public:
    EmBoxHolder(points lineHeight, points dimensions, Canvas* canvas):
        EmBox(dimensions, canvas),
        mLineHeight(lineHeight)
    {
    }

    virtual ~EmBoxHolder(void)
    {
    }

    void progressX(em delta)
    {
        mX += delta * mDimensions;
        if (mX + mDimensions >= mCanvas->width())
        {
            mX = 0;
            progressY(mDimensions);
        }
    }

    void progressY(em delta)
    {
        mY += mLineHeight * delta;
    }

    void nextLine(void)
    {
        progressY(mDimensions);
    }

    void setX(size_t value)
    {
        mX = value;
    }

    void setY(size_t value)
    {
        mY = value;
    }

    size_t getX(void) const
    {
        return mX;
    }

    size_t getY(void) const
    {
        return mY;
    }

    void setCanvas(Canvas* canvas)
    {
        mCanvas = canvas;
    }

    void setFontSize(size_t dimensions)
    {
        mDimensions = dimensions;
    }

    bool offCanvas(void) const
    {
        return mY + mDimensions > mCanvas->height();
    }
private:
    points mLineHeight;
};

class Font
{
public:
    Font(FontFace* face, points fontSize):
        mFontFace(face),
        mBounds(1.15, fontSize, NULL)
    {
    }

    ~Font(void)
    {
        // We don't own the canvas! Don't delete it!!!
    }

    inline void setCanvas(Canvas* canvas)
    {
        mBounds.setCanvas(canvas);
        reset();
    }

    inline void reset(void)
    {
        mBounds.setX(0);
        mBounds.setY(0);
    }

    inline void setFontSize(points size)
    {
        mBounds.setFontSize(size);
    }

    size_t write(const char* str)
    {
        size_t i;
        em delta;
        glyph g;
        for (i = 0; str[i]; ++i)
        {
            if (mBounds.offCanvas())
            {
                break;
            }

            if (str[i] == '\n')
            {
                mBounds.nextLine();
                mBounds.setX(0);
                continue;
            }

            g = (*mFontFace)[str[i]];
            delta = (*g)(&mBounds);
            mBounds.progressX(delta / MAX_EM);
        }

        return i;
    }
private:
    FontFace* mFontFace;
    EmBoxHolder mBounds;
};

#endif
