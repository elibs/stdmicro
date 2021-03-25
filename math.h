#ifndef __STD_MICRO_MATH_H
#define __STD_MICRO_MATH_H

inline int ceil(float val)
{
    if (int(val) != val)
    {
        if (val > 0)
        {
            return val + 1;
        }
        return val - 1;
    }
    
    return val;
}

#endif
