#include <stdlib.h>
#include <math.h>

#pragma function(fabs)

extern "C" double __cdecl runtime_atan2(double y, double x);

namespace th105 {

float g_orientation_cosine_table[3600];
static volatile float const orientation_degree_scale = 180.0f;
static volatile float const orientation_pi = 3.1415927f;

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

double __cdecl atan2_degrees(float y, float x)
{
    x = static_cast<float>(runtime_atan2(y, x));
    volatile float *value = &x;
    *value = *value;
    *value = *value * orientation_degree_scale / orientation_pi;
    return *value;
}

double __cdecl lookup_orientation_sine_quantized_abs(float phase)
{
    float magnitude = phase * 10.0f - 900.0f;
    magnitude = static_cast<float>(fabs(static_cast<double>(magnitude)));
    int const index = static_cast<int>(magnitude + 0.5f);
    return g_orientation_cosine_table[index % 3600];
}

double __cdecl lookup_orientation_cosine_quantized_abs(float phase)
{
    float magnitude = phase * 10.0f;
    magnitude = static_cast<float>(fabs(static_cast<double>(magnitude)));
    int const index = static_cast<int>(magnitude + 0.5f);
    return g_orientation_cosine_table[index % 3600];
}

} // namespace th105
