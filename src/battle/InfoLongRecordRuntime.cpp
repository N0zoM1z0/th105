#include "InfoLongRecordRuntime.hpp"
#include "../engine/RenderModeManager.hpp"

namespace th105 {

void InfoLongRecord154Runtime::update_4327c0()
{
    if (!active_14c) {
        if (alpha_primary_130 > 0) {
            x_134 -= 10.0;
            alpha_primary_130 -= 5;
            if (alpha_secondary_131 > 0)
                alpha_secondary_131 -= 5;
        }
        return;
    }

    int timer = timer_12c;
    if (timer < 80) {
        if (velocity_y_140 > 0.0f && timer >= 40) {
            y_138 -= velocity_y_140;
            velocity_y_140 -= 0.75;
        }
        if (alpha_primary_130 < 0xff)
            alpha_primary_130 += 12;
        if (alpha_secondary_131 < 0xff)
            alpha_secondary_131 += 25;
        if (velocity_x_13c > 0.0f && timer >= 30)
            velocity_x_13c -= 1.200000047683716f;
        if (scale_144 > 1.0f) {
            scale_144 -= 0.20000000298023224f;
            if (scale_144 < 1.0f)
                scale_144 = 1.0f;
        }
    }

    int next = timer + 1;
    int lifetime = lifetime_150;
    timer_12c = next;
    if (lifetime > 0 && next > lifetime + 80)
        active_14c = 0;
}

void InfoLongRecord154Runtime::render_4325c0()
{
    if (!active_14c && alpha_primary_130 == 0)
        return;

    g_render_mode_manager.set_blend_mode(1);
    InfoLongSprite94 *primary = &primary_004;
    primary->set_color(
        (static_cast<unsigned>(alpha_primary_130) << 24) | 0x00ffffff);
    InfoLongSprite94 *secondary = &secondary_098;
    secondary->set_color(
        (static_cast<unsigned>(alpha_secondary_131) << 24) | 0x00ffffff);

    float scale = scale_144;
    secondary->scale_x_088 = scale;
    secondary->scale_y_08c = scale;

    if (!mirrored_132) {
        primary->move_1c(x_134, y_138);
        secondary->move_1c(
            static_cast<float>(x_134 + 20.0),
            static_cast<float>(y_138 + 20.0));
    } else {
        primary->move_1c(
            static_cast<float>(440.0 - x_134), y_138);
        secondary->move_1c(
            static_cast<float>(620.0 - x_134),
            static_cast<float>(y_138 + 20.0));
    }
}

} // namespace th105
