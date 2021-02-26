#ifndef __FONT_SIZE_H
#define __FONT_SIZE_H

struct FontSize
{
public:
    unsigned int pt;

    operator unsigned int(void) const;
};

#endif
