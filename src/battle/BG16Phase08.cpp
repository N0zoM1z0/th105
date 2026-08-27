#include "battle/BackgroundDerived.hpp"
#include "battle/BattleBackgroundLayout.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {
extern float __cdecl lookup_orientation_sine(int angle);

void BG16::slot_08()
{
    g_render_mode_manager.set_gate_states(1, 0);
    g_render_mode_manager.set_state_23(5);
    g_render_mode_manager.set_sampler_state(0, 1, 3);
    g_render_mode_manager.set_mode(2);
    g_render_mode_manager.set_blend_mode(2);

    float vertical_scale = static_cast<float>(
        (static_cast<double>(lookup_orientation_sine(2 * state_64)) + 6.0) *
        static_cast<double>(0.1f));

    sprites_b_34[2].reset_transform();
    {
        CSpriteEx &sprite = sprites_b_34[2];
        sprite.scale_x(2.0f);
        sprite.scale_y(vertical_scale);
        sprite.scale_z(1.0f);
    }
    sprites_b_34[2].translate(value_44, value_48, 0.1f);
    g_battle_background_layout.place_sprite(&sprites_b_34[2], 1.0f, 1.0f);
    sprites_b_34[2].finalize_render();

    sprites_b_34[2].reset_transform();
    {
        CSpriteEx &sprite = sprites_b_34[2];
        sprite.scale_x(-2.0f);
        sprite.scale_y(vertical_scale);
        sprite.scale_z(1.0f);
    }
    sprites_b_34[2].translate(value_44, value_48, 0.1f);
    g_battle_background_layout.place_sprite(&sprites_b_34[2], 1.0f, 1.0f);
    sprites_b_34[2].finalize_render();

    g_render_mode_manager.set_sampler_state(0, 1, 1);
    g_render_mode_manager.set_mode(1);
    g_render_mode_manager.set_blend_mode(1);
    g_render_mode_manager.set_state_23(8);
    g_render_mode_manager.set_gate_states(0, 0);
}
}
