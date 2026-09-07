#include <math.h>

namespace th105 {

float __cdecl sqrt_float_value(float value)
{
    return static_cast<float>(sqrt(static_cast<double>(value)));
}

} // namespace th105
