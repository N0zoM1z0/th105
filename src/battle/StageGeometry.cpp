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

void __stdcall fill_stage_surface_range(
    float begin_x, float end_x, float height)
{
    int begin = static_cast<int>(begin_x);
    if (begin < 0)
        begin = 0;

    int end = static_cast<int>(end_x);
    if (end >= 0x500)
        end = 0x4ff;

    if (begin <= end) {
        for (int index = begin; index <= end; ++index)
            stage_surface_heights[index] = height;
    }
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
