#include "engine/RenderModeManager.hpp"

namespace th105 {

extern float g_scene_fade_value;
extern unsigned g_scene_fade_color;
bool __cdecl render_profile_ui_frame();

unsigned char __cdecl render_scene_fade_overlay()
{
    if (g_scene_fade_value > 0.0f) {
        if (!g_render_mode_manager.begin_frame())
            return false;

        const unsigned alpha = static_cast<unsigned>(
            static_cast<unsigned char>(g_scene_fade_color >> 24) *
            g_scene_fade_value);
        g_render_mode_manager.draw_rect(
            0.0f,
            0.0f,
            640.0f,
            480.0f,
            (g_scene_fade_color & 0x00ffffffu) | (alpha << 24),
            1);
        g_render_mode_manager.finish_frame();
    }

    return render_profile_ui_frame() != 0;
}

} // namespace th105
