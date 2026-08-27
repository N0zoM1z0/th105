#include "battle/BackgroundDerived.hpp"
#include "battle/BattleBackgroundLayout.hpp"
#include "engine/RenderModeManager.hpp"
namespace th105 {
extern float __cdecl lookup_orientation_sine(int angle);

void BG16::slot_0c()
{
    g_render_mode_manager.set_blend_mode(2);

    sprites_b_34[0].reset_transform();
    sprites_b_34[0].rotate_xyz(
        0.0f, 0.0f,
        static_cast<float>(static_cast<double>(state_64) / 5.0),
        0.0f, 0.0f, 0.0f);
    {
        CSpriteEx &sprite = sprites_b_34[0];
        sprite.scale_x(3.5f);
        sprite.scale_y(0.21875f);
        sprite.scale_z(1.0f);
    }
    sprites_b_34[0].translate(value_44, value_48, 0.0f);
    g_battle_background_layout.place_sprite(&sprites_b_34[0], 1.0f, 1.0f);
    sprites_b_34[0].finalize_render();

    sprites_b_34[1].reset_transform();
    sprites_b_34[1].rotate_xyz(
        0.0f, 0.0f,
        static_cast<float>(-static_cast<float>(state_64) / 5.0f),
        0.0f, 0.0f, 0.0f);
    {
        CSpriteEx &sprite = sprites_b_34[1];
        sprite.scale_x(4.0f);
        sprite.scale_y(0.25f);
        sprite.scale_z(1.0f);
    }
    sprites_b_34[1].translate(value_44, value_48, 0.0f);
    g_battle_background_layout.place_sprite(&sprites_b_34[1], 1.0f, 1.0f);
    sprites_b_34[1].finalize_render();

    g_render_mode_manager.set_mode(2);

    float x_positions[4];
    float y_positions[4];
    float base_scales[4];
    x_positions[0]=190.0f; x_positions[1]=546.0f; x_positions[2]=852.0f; x_positions[3]=1209.0f;
    y_positions[0]=511.0f; y_positions[1]=582.0f; y_positions[2]=582.0f; y_positions[3]=511.0f;
    base_scales[0]=1.2f; base_scales[1]=0.80000001f; base_scales[2]=0.80000001f; base_scales[3]=1.2f;

    for (int i = 0; i < 4; ++i) {
        sprites_b_34[3].reset_transform();
        float scale = static_cast<float>(
            static_cast<double>(lookup_orientation_sine(i * 90 + state_64 * (i + 4))) *
                static_cast<double>(0.1f) +
            static_cast<double>(base_scales[i]));
        {
            CSpriteEx &sprite = sprites_b_34[3];
            sprite.scale_x(scale);
            sprite.scale_y(scale);
            sprite.scale_z(1.0f);
        }
        sprites_b_34[3].translate(
            x_positions[i] - 700.0f,
            y_positions[i] - 860.0f,
            0.0f);
        sprites_b_34[3].translate(value_44, value_48, 0.0f);
        g_battle_background_layout.place_sprite(&sprites_b_34[3], 1.0f, 1.0f);
        sprites_b_34[3].finalize_render();
    }

    g_render_mode_manager.set_mode(1);
    g_render_mode_manager.set_blend_mode(1);
}
}
