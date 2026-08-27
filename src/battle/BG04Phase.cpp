#include "battle/BackgroundDerived.hpp"
#include "battle/BattleBackgroundLayout.hpp"
#include "battle/AnimationRenderVirtuals.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

struct BackgroundCameraView {
    unsigned char reserved_00[0x0c];
    float camera_x_0c;
};

void BG04::slot_08()
{
    g_render_mode_manager.set_blend_mode(1);
    g_render_mode_manager.set_mode(2);
    g_render_mode_manager.set_sampler_state(0, 2, 3);
    sprites_b_34[0].reset_transform();

    sprites_b_34[0].set_uv_size(
        static_cast<float>(
            static_cast<double>(state_64) * 0.25 -
            static_cast<double>(reinterpret_cast<BackgroundCameraView *>(&g_battle_background_layout)->camera_x_0c) / 2.5),
        0.0f);

    {
        CSpriteEx &sprite = sprites_b_34[0];
        sprite.scale_x(2.5f);
        sprite.scale_y(2.5f);
        sprite.scale_z(1.0f);
    }

    sprites_b_34[0].translate(value_44 - reinterpret_cast<BackgroundCameraView *>(&g_battle_background_layout)->camera_x_0c, value_48, 0.0f);
    g_battle_background_layout.place_sprite(&sprites_b_34[0], 1.0f, 1.0f);
    reinterpret_cast<SpriteRenderEffectView *>(&sprites_b_34[0])
        ->render_rgb(value_50, value_54, value_58);

    g_render_mode_manager.set_sampler_state(0, 2, 1);
    g_render_mode_manager.set_mode(1);
}

} // namespace th105
