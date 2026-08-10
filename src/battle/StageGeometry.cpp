#include "Collision.hpp"

#pragma data_seg(".data")
float stage_surface_heights[0x500] = {0.0f};
#pragma data_seg()

namespace th105 {

signed char Fighter::classify_fighter_x_boundary()
{
    if (x_ec - 40.0 <= 0.0) {
        return 1;
    }
    if (x_ec + 40.0 >= 1280.0) {
        return -1;
    }
    return 0;
}

int Fighter::test_proposed_x_against_stage_height(float x_delta)
{
    x_delta += x_ec;

    if (x_delta <= 0.0) {
        x_delta = stage_surface_heights[0];
    } else {
        const int index = static_cast<int>(x_delta + 0.5);
        if (index >= 0x500) {
            x_delta = stage_surface_heights[0x4ff];
        } else {
            x_delta = stage_surface_heights[index];
        }
    }

    if (y_f0 + 5.0 < x_delta) {
        return 1;
    }
    return 0;
}

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
