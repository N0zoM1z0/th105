#include "ui/ProfileMenu.hpp"
#include "ui/ProfileMenuControllerRuntime.hpp"
#include "engine/RenderModeManager.hpp"
#include <cstring>
#include <windows.h>

namespace th105 {

void ProfileEditor168::render(float x, float y)
{
    ProfileMenuControllerRuntime &controller = g_profile_menu_controller;
    if (!controller.mode_a0f)
        return;

    const int cursor = controller.cursor_a10;
    const int composition_end = cursor + static_cast<int>(std::strlen(controller.composition_808));
    int display_length;
    if (static_cast<int>(std::strlen(controller.primary_008)) > composition_end)
        display_length = static_cast<int>(std::strlen(controller.primary_008));
    else
        display_length = composition_end;

    for (int index = 0; index < display_length; ++index) {
        const int left = static_cast<int>(x) + index * width_154 / 2;
        if (index >= cursor && index < composition_end) {
            const int top = static_cast<int>(y);
            RECT rect;
            SetRect(&rect, left, top, left + width_154 / 2, top + width_154 + 1);
            const int composition_index = index - cursor;
            const int attribute = controller.attributes_908[composition_index];
            unsigned color = 0;
            bool draw = true;
            switch (attribute) {
            case 0: color = 0xffffffffu; break;
            case 1: color = 0xff6060d0u; break;
            case 2: color = 0xff808080u; break;
            case 3: color = 0xff6060f0u; break;
            default: draw = false; break;
            }
            if (draw) {
                if (attribute == 0 || attribute == 3)
                    SetRect(&rect, left, top + width_154, left + width_154 / 2, top + width_154 + 1);
                g_render_mode_manager.draw_rect_int(reinterpret_cast<const int *>(&rect), color, 1);
            }
            if (texture_secondary_004)
                secondary_tile_0b0.render(static_cast<float>(left), y, composition_index, 0);
        } else if (texture_primary_000) {
            primary_tile_00c.render(static_cast<float>(left), y, index, 0);
        }
    }

    if (state_160 % 60 < 30) {
        const int left = static_cast<int>(x) + cursor * width_154 / 2;
        const int top = static_cast<int>(y);
        RECT rect;
        SetRect(&rect, left, top, left + 1, top + width_154 + 1);
        g_render_mode_manager.draw_rect_int(reinterpret_cast<const int *>(&rect), 0xffffffffu, 1);
    }
}

} // namespace th105
