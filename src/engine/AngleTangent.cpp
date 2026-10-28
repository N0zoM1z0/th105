#include "AngleTangent.hpp"

// Strict rounding with exception-sensitive scheduling disabled, as in the
// separately accepted integer-angle ratio. See ANGLE_TANGENT_2026_10_28.md.
#pragma float_control(except, off, push)

namespace th105 {

double __cdecl lookup_orientation_sine_quantized_abs(float);
double __cdecl lookup_orientation_cosine_quantized_abs(float);

float __cdecl lookup_orientation_tangent(float phase)
{
    float cosine = static_cast<float>(lookup_orientation_cosine_quantized_abs(phase));
    if (cosine == 0.0f)
        return 0.0f;
    return static_cast<float>(lookup_orientation_sine_quantized_abs(phase) / cosine);
}

} // namespace th105

#pragma float_control(pop)
