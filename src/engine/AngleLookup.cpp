#include <stdlib.h>
#include <math.h>


#pragma float_control(except, off, push)

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
    magnitude = abs(magnitude);
    __declspec(align(64)) int index = static_cast<int>(magnitude + 0.5f);
    int divisor = 3600;
    return g_orientation_cosine_table[index % divisor];
}

float __cdecl lookup_orientation_cosine_quantized_abs(float phase)
{
    float magnitude = phase * 10.0f;
    magnitude = abs(magnitude);
    __declspec(align(64)) int index = static_cast<int>(magnitude + 0.5f);
    int divisor = 3600;
    return g_orientation_cosine_table[index % divisor];
}

} // namespace th105

#pragma float_control(pop)
