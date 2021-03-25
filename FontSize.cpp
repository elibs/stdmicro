#include "FontCommon.h"
#include "FontSize.h"

FontSize::operator unsigned int(void) const
{
    const unsigned int dpi = 125;
    return (dpi * pt) / POINT_PER_INCH;
}
