#include "battle/AnimationRenderVirtuals.hpp"
#include "battle/BackgroundDerived.hpp"
#include "battle/BattleBackgroundLayout.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

void BG02::slot_10()
{
    render_base_sprites_4659e0();

    const int base = 3 * (state_64 / 6 % 16);
    g_render_mode_manager.set_blend_mode(2);
    g_render_mode_manager.set_mode(2);

    sprites_b_34[base].reset_transform();
    {
        CSpriteEx &sprite = sprites_b_34[base];
        sprite.scale_x(2.0f);
        sprite.scale_y(2.0f);
        sprite.scale_z(1.0f);
    }
    sprites_b_34[base].translate(-332.0f, -472.0f, 0.0f);
    sprites_b_34[base].translate(value_44, value_48, 0.0f);
    g_battle_background_layout.place_sprite(
        &sprites_b_34[base], 1.0f, 1.0f);
    reinterpret_cast<SpriteRenderEffectView *>(&sprites_b_34[base])
        ->render_rgb(value_50, value_54, value_58);

    sprites_b_34[base + 1].reset_transform();
    {
        CSpriteEx &sprite = sprites_b_34[base + 1];
        sprite.scale_x(2.0f);
        sprite.scale_y(2.0f);
        sprite.scale_z(1.0f);
    }
    sprites_b_34[base + 1].translate(54.0f, -472.0f, 0.0f);
    g_battle_background_layout.place_sprite(
        &sprites_b_34[base + 1], 1.0f, 1.0f);
    reinterpret_cast<SpriteRenderEffectView *>(&sprites_b_34[base + 1])
        ->render_rgb(value_50, value_54, value_58);

    sprites_b_34[base + 2].reset_transform();
    {
        CSpriteEx &sprite = sprites_b_34[base + 2];
        sprite.scale_x(2.0f);
        sprite.scale_y(2.0f);
        sprite.scale_z(1.0f);
    }
    sprites_b_34[base + 2].translate(312.0f, -472.0f, 0.0f);
    sprites_b_34[base + 2].translate(value_44, value_48, 0.0f);
    g_battle_background_layout.place_sprite(
        &sprites_b_34[base + 2], 1.0f, 1.0f);
    reinterpret_cast<SpriteRenderEffectView *>(&sprites_b_34[base + 2])
        ->render_rgb(value_50, value_54, value_58);

    g_render_mode_manager.set_mode(1);
    g_render_mode_manager.set_blend_mode(1);
}

} // namespace th105
