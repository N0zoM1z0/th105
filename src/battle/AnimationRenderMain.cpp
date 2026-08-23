#include "AnimationRenderVirtuals.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

void AnimationRenderObjectView::render_main()
{
    if (aux_renderer_154)
        aux_renderer_154->render_auxiliary();

    prepare_render_transform();

    AnimationRenderFrameView *const frame = frame_150;
    switch (frame->render_mode_14) {
    case 0:
        g_render_mode_manager.set_blend_mode(1);
        sprite_004.set_color(sprite_004.color_10c);
        break;
    case 1:
        g_render_mode_manager.set_blend_mode(1);
        sprite_004.set_color(sprite_004.color_10c);
        break;
    case 2:
        g_render_mode_manager.set_blend_mode(frame->mode_values_18[0]);
        sprite_004.set_color(frame->mode_values_18[1]);
        sprite_004.multiply_color(sprite_004.color_10c);
        break;
    default:
        break;
    }

    render_color_mode();

    if (aux_renderer_154) {
        g_render_mode_manager.apply_render_mode(1, 0);
        g_battle_render_pass += 2;
    }
}

} // namespace th105
