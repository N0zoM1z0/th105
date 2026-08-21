#include "SystemEffectObject.hpp"

#include "ui/Title.hpp"

namespace th105 {
struct RenderModeManager {
    void set_mode(int mode);
};
extern RenderModeManager g_render_mode_manager;
}

SystemEffectObjectBase::~SystemEffectObjectBase()
{
    th105::g_title_resource_manager.release_title_resource_handle(
        resource_handle_138);
    resource_handle_138 = 0;
}

void SystemEffectObject::reset_state()
{
    switch (mode_13c) {
    case 0:
        timer_140 = 0;
        alpha_byte() = 0;
        break;
    case 1:
        timer_140 = 0;
        alpha_byte() = 0;
        break;
    case 2:
        timer_140 = 0;
        alpha_byte() = 0;
        break;
    }
}

void SystemEffectObject::update_state()
{
    unsigned char &alpha = alpha_byte();
    switch (mode_13c) {
    case 2:
        if (timer_140 == 0) {
            if (alpha <= 0xfc) {
                alpha = static_cast<unsigned char>(alpha + 3);
                return;
            }
            alpha = 0xff;
            timer_140 = 1;
            return;
        }
        ++timer_140;
        if (timer_140 < 180)
            return;
        if (alpha >= 3) {
            alpha = static_cast<unsigned char>(alpha - 3);
            return;
        }
        --state_000;
        return;

    case 1:
        effect_000.object_x_0e8 += 0.2f;
        if (timer_140 == 0) {
            if (alpha <= 0xf5) {
                alpha = static_cast<unsigned char>(alpha + 10);
                return;
            }
            alpha = 0xff;
            timer_140 = 1;
            return;
        }
        ++timer_140;
        if (timer_140 < 120)
            return;
        if (alpha >= 5) {
            alpha = static_cast<unsigned char>(alpha - 5);
            return;
        }
        --state_000;
        return;

    case 0:
        if (timer_140 == 0) {
            if (alpha <= 0xfc) {
                alpha = static_cast<unsigned char>(alpha + 3);
                return;
            }
            alpha = 0xff;
            timer_140 = 1;
            return;
        }
        ++timer_140;
        if (timer_140 < 120)
            return;
        if (alpha >= 3) {
            alpha = static_cast<unsigned char>(alpha - 3);
            return;
        }
        --state_000;
        return;
    }
}

void SystemEffectObjectBase::render_effect()
{
    th105::g_render_mode_manager.set_mode(2);
    effect_000.reset_transform();
    effect_000.scale_x(effect_000.reset_one_118, effect_000.reset_zero_104);
    effect_000.scale_y(effect_000.reset_one_11c, effect_000.reset_zero_108);
    effect_000.transform_six(
        effect_000.reset_zero_120,
        effect_000.reset_zero_124,
        effect_000.reset_zero_128,
        effect_000.reset_zero_104,
        effect_000.reset_zero_108,
        0.0f);
    effect_000.translate(
        effect_000.object_x_0e8, effect_000.object_y_0ec, 0.0f);
    IColor *color = &effect_000;
    color->set_color(effect_000.color_10c);
    effect_000.finalize_render();
    th105::g_render_mode_manager.set_mode(1);
}
