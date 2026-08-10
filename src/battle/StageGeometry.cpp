#include "Collision.hpp"

#pragma data_seg(".data")
float stage_surface_heights[0x500] = {0.0f};
#pragma data_seg()

namespace th105 {

float __fastcall stage_surface_height_at_x(Fighter *fighter)
{
    float result;
    const float x = fighter->x_ec;
    if (x <= 0.0f) {
        result = stage_surface_heights[0];
    } else {
        const int index = static_cast<int>(x + 0.5);
        if (index >= 0x500) {
            result = stage_surface_heights[0x4ff];
        } else {
            result = stage_surface_heights[index];
        }
    }
    return result;
}

} // namespace th105
