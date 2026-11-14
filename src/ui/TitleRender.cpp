#include "ui/UiPrimitives.hpp"
#include "ui/TitleScene.hpp"
#include "engine/RenderModeManager.hpp"
extern "C" float __cdecl lookup_orientation_cosine(int angle);
namespace th105 {
bool CTitle::render()
{
    if (!g_render_mode_manager.begin_frame())
        return false;
    design_1dc.render();
    g_render_mode_manager.set_mode(2);
    lookup_orientation_cosine(2 * menu_item_wave_counter);
    unsigned char green = static_cast<unsigned char>(
        static_cast<int>(lookup_orientation_cosine(2 * menu_item_wave_counter) * 70.0 + 185.0));
    unsigned char blue = static_cast<unsigned char>(
        static_cast<int>(lookup_orientation_cosine(2 * menu_item_wave_counter) * 70.0 + 185.0));
    color_a4.set_color(0xffff0000u | (static_cast<unsigned int>(green) << 8) | blue);
    color_a4.set_scale(1.5f, 1.0f);
    int selected = cursor_210.selection;
    UiDesignObject *item = menu_items_224[selected];
    color_a4.render(menu_item_wave_offsets[selected] + item->x,
                    static_cast<float>(item->y + 4.0));
    for (int i = 0; i < 12; ++i) {
        color_138.render(menu_item_wave_offsets[i] + menu_items_224[i]->x, menu_items_224[i]->y, 0, i);
    }
    g_render_mode_manager.set_mode(1);
    g_render_mode_manager.finish_frame();
    return true;
}
}
