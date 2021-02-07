#ifndef __FONT_FACE_H
#define __FONT_FACE_H

typedef em (*glyph)(EmBox*);

class FontFace
{
public:
    virtual ~FontFace(void)
    {
    }

    virtual glyph operator[](int c) const = 0;

protected:
    static em None(EmBox* box)
    {
        return 0;
    }
};

#endif
