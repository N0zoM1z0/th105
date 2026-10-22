#include "AnimationAuxiliarySprite.hpp"
#include "BattleRenderHelpers.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

extern unsigned char g_battle_render_pass;

void AuxiliarySpriteRuntimeView::render_auxiliary()
{
    if (g_battle_render_pass > 250) {
        g_battle_render_pass = 0;
        g_render_mode_manager.apply_render_mode(4, 0);
    }
    g_render_mode_manager.apply_render_mode(1, 1);
    g_render_mode_manager.apply_render_mode(
        2, static_cast<unsigned char>(g_battle_render_pass + 2));

    sprite_000.reset_transform();
    sprite_000.scale_x(static_cast<float>(facing_104));

    float const scale_y = field_fc;
    float const pivot_y = frame_y_f4;
    sprite_000.scale_x(
        field_f8, static_cast<float>(facing_104) * frame_x_f0);
    sprite_000.scale_y(scale_y, pivot_y);
    sprite_000.scale_z(1.0f, 0.0f);
    sprite_000.rotate_xyz(
        0.0f, 0.0f, static_cast<float>(facing_104) * angle_100,
        frame_x_f0 * static_cast<float>(facing_104), frame_y_f4, 0.0f);
    sprite_000.translate(
        x_e8 - static_cast<float>(facing_104) * frame_x_f0,
        -y_ec - frame_y_f4, 0.0f);

    g_battle_background_layout.transform_sprite(&sprite_000);
    sprite_000.finalize_render();
    g_render_mode_manager.apply_render_mode(
        3, static_cast<unsigned char>(g_battle_render_pass + 1));
}

} // namespace th105
