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

    inline void progressX(em delta)
    {
        mX += delta * mMult;
        if (mX + mDimensions >= mCanvas->width())
        {
            nextLine();
        }
    }

    inline void progressY(em delta)
    {
        mY += mLineHeight * delta;
        mCY = mY + mDimensions;
    }

    inline void nextLine(void)
    {
        mX = 0;
        progressY(mDimensions);
    }

    void setX(size_t value)
    {
        mX = value;
    }

    void setY(size_t value)
    {
        mY = value;
        mCY = mY + mDimensions;
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

    void setFontSize(points dimensions)
    {
        mDimensions = dimensions;
        mMult = dimensions / MAX_EM;
    }

    inline bool offCanvas(void) const
    {
        return mY + (mDimensions * 1.25) >= mCanvas->height();
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
                continue;
            }

            // Don't draw a space as the first character of a line.
            if (str[i] == ' ' && mBounds.getX() == 0)
            {
                continue;
            }

            g = (*mFontFace)[str[i]];
            mBounds.progressX((*g)(&mBounds));
        }

        return i;
    }
private:
    FontFace* mFontFace;
    EmBoxHolder mBounds;
};

#endif
