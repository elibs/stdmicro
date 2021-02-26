#include "FontCommon.h"
#include "FontSize.h"


FontSize::operator unsigned int(void) const
{
    const unsigned int dpi = 125;
    return (dpi * pt) / 72; //(72 * MAX_EM) / (125 * pt);
}
