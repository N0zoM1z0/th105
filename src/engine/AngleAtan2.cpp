#include "AngleAtan2.hpp"
#include <math.h>

namespace th105 {

float __cdecl atan2_degrees(float y, float x)
{
    return atan2f(y, x) * 180.0f / 3.1415927f;
}

} // namespace th105
