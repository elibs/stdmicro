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

    static em none(EmBox* box)
    {
        return 0;
    }
};

#endif
