#include <stdlib.h>
#include <math.h>

#pragma function(fabs)

namespace th105 {

float g_orientation_cosine_table[3600];

float __cdecl lookup_orientation_sine(int angle)
{
    int scaled = angle * 5 - 450;
    scaled += scaled;
    return g_orientation_cosine_table[abs(scaled) % 3600];
}

float __cdecl lookup_orientation_cosine(int angle)
{
    int scaled = angle * 5;
    scaled += scaled;
    return g_orientation_cosine_table[abs(scaled) % 3600];
}

float __cdecl lookup_orientation_sine_quantized_abs(float phase)
{
    float magnitude = phase * 10.0f - 900.0f;
    magnitude = static_cast<float>(fabs(static_cast<double>(magnitude)));
    int const index = static_cast<int>(magnitude + 0.5f);
    return g_orientation_cosine_table[index % 3600];
}

float __cdecl lookup_orientation_cosine_quantized_abs(float phase)
{
    float magnitude = phase * 10.0f;
    magnitude = static_cast<float>(fabs(static_cast<double>(magnitude)));
    int const index = static_cast<int>(magnitude + 0.5f);
    return g_orientation_cosine_table[index % 3600];
}

} // namespace th105
