#ifndef __FONT_SIZE_H
#define __FONT_SIZE_H

struct FontSize
{
public:
    static const int POINT_PER_INCH = 72;
    unsigned int pt;

    operator unsigned int(void) const;
};

#endif
