#include "AngleRatio.hpp"

#include <stdlib.h>

// Preserve strict single-precision rounding without exception-sensitive
// scheduling. See docs/ANGLE_RATIO_EVIDENCE_2026_09_12.md.
#pragma float_control(except, off, push)

namespace th105 {

extern float g_orientation_cosine_table[3600];

float __cdecl lookup_orientation_ratio_quantized_abs(int angle)
{
    int scaled = angle * 5;
    scaled += scaled;
    float const denominator = g_orientation_cosine_table[abs(scaled) % 3600];
    if (denominator != 0.0f) {
        scaled = angle * 5 - 450;
        scaled += scaled;
        float const numerator = g_orientation_cosine_table[abs(scaled) % 3600];
        return numerator / denominator;
    }
    return 0.0f;
}

} // namespace th105

#pragma float_control(pop)
