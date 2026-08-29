#include "RenderTimeline.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

void RenderTimelineEntry::render()
{
    if (alpha_54 == 0)
        return;

    CSpriteEx &sprite = sprites_14[frame_74 % sprites_14.size()];
    sprite.reset_transform();
    unsigned color = static_cast<unsigned>(colors_56[4])
        | (static_cast<unsigned>(colors_56[2]) << 8)
        | (static_cast<unsigned>(colors_56[0]) << 16)
        | (static_cast<unsigned>(alpha_54) << 24);
    sprite.set_color(color);
    sprite.set_uv_size(uv_width_30, uv_height_34);
    float y_scale = scale_y_3c;
    sprite.scale_x(scale_x_38);
    sprite.scale_y(y_scale);
    sprite.scale_z(1.0f);
    sprite.rotate_xyz(0.0f, 0.0f, rotation_z_40, 0.0f, 0.0f, 0.0f);
    sprite.translate(translate_x_28, translate_y_2c, 0.0f);
    g_render_mode_manager.set_blend_mode(blend_mode_68);
    g_render_mode_manager.set_sampler_state(0, 1, sampler_one_6c);
    g_render_mode_manager.set_sampler_state(0, 2, sampler_two_70);
    sprite.finalize_render();
}

} // namespace th105
