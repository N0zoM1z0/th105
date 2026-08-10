#include <stdlib.h>

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

} // namespace th105
