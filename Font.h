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

    void progressX(size_t delta)
    {
        mX += delta;
        if (mX + mDimensions >= mCanvas->width())
        {
            mX = 0;
            progressY(mDimensions);
        }
    }

    void progressY(size_t delta)
    {
        mY += mLineHeight * delta;
        if (mY + mDimensions >= mCanvas->height())
        {
            mY = 0;
        }
    }

    void setX(size_t value)
    {
        mX = value;
    }

    void setY(size_t value)
    {
        mY = value;
    }
private:
    points mLineHeight;
};

class Font
{
public:
    Font(FontFace* face, points fontSize):
        mX(0),
        mY(0),
        mCanvas(NULL),
        mFontFace(face),
        mFontSize(fontSize)
    {
    }

    ~Font(void)
    {
        // We don't own the canvas! Don't delete it!!!
    }

    inline void setCanvas(Canvas* canvas)
    {
        mCanvas = canvas;
        reset();
    }

    inline void reset(void)
    {
        mX = 0;
        mY = 0;
    }

    inline void setFontSize(points size)
    {
        mFontSize = size;
    }

    size_t write(const char* str)
    {
        EmBoxHolder bounds(1.15, mFontSize, mCanvas);

        size_t i;
        em delta;
        glyph g;
        for (i = 0; str[i]; ++i)
        {
            if (str[i] == '\n')
            {
                bounds.progressY(mFontSize);
                bounds.setX(0);
                continue;
            }

            g = (*mFontFace)[str[i]];
            delta = (*g)(&bounds);
            bounds.progressX((delta / MAX_EM) * mFontSize);
        }

        return i;
    }
private:
    size_t mX;
    size_t mY;
    Canvas* mCanvas;
    FontFace* mFontFace;
    points mFontSize;
};

#endif
