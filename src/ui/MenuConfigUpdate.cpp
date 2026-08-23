#include "MenuConfigUpdate.hpp"
#include "../input/InputManager.hpp"

#include <windows.h>

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    unsigned char key, bool modifier_a, bool modifier_b, bool modifier_c);

namespace th105 {

int apply_bgm_percent(int value);
int apply_se_percent(int value);
void close_config_menu();
extern int g_config_window_mode_state;
extern HWND g_main_window;

bool CMenuConfigUpdateView::update()
{
    guide_008.update();
    HoldCounters *input = &g_active_menu_input->hold;

    if (primary_264.update()) {
        dispatch_indexed_event(0x27);
        update_secondary_for_primary(primary_264.selection);
    } else if (secondary_278.update() && input->vertical == 0) {
        dispatch_indexed_event(0x27);
        switch (primary_264.selection) {
        case 0:
            config_004->option_64 = secondary_278.selection;
            break;
        case 1:
            config_004->bgm_percent_68 = 5 * secondary_278.selection;
            apply_bgm_percent(config_004->bgm_percent_68);
            sprites_b8[0].set_texture(
                texture_b4, 0, 0,
                static_cast<int>(
                    grid_width_1e0 * config_004->bgm_percent_68 / 100),
                grid_height_1e4);
            break;
        case 2:
            config_004->se_percent_6c = 5 * secondary_278.selection;
            apply_se_percent(config_004->se_percent_6c);
            sprites_b8[1].set_texture(
                texture_b4, 0, 0,
                static_cast<int>(
                    grid_width_1e0 * config_004->se_percent_6c / 100),
                grid_height_1e4);
            break;
        case 3:
            config_004->windowed_70 = !config_004->windowed_70;
            SendMessageA(g_main_window, 0x104, 0x0d, 0);
            break;
        case 4:
            config_004->option_71 = !config_004->option_71;
            break;
        default:
            break;
        }
    } else {
        if (input->buttons[0] == 1 && primary_264.selection == 5) {
            dispatch_indexed_event(0x28);
            close_config_menu();
            return false;
        }
        if (input->buttons[1] == 1 ||
            is_menu_initial_press(1, false, false, false)) {
            dispatch_indexed_event(0x29);
            close_config_menu();
            return false;
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (config_004->option_64 == i)
            option_objects_23c[i]->set_color(0xffffffffu);
        else
            option_objects_23c[i]->set_color(0xff808080u);
    }

    config_004->windowed_70 = (g_config_window_mode_state == 0);
    if (config_004->windowed_70) {
        window_objects_24c[2]->set_color(0xffffffffu);
        window_objects_24c[3]->set_color(0xff808080u);
    } else {
        window_objects_24c[2]->set_color(0xff808080u);
        window_objects_24c[3]->set_color(0xffffffffu);
    }
    if (config_004->option_71) {
        option_toggle_objects_25c[0]->set_color(0xffffffffu);
        option_toggle_objects_25c[1]->set_color(0xff808080u);
    } else {
        option_toggle_objects_25c[0]->set_color(0xff808080u);
        option_toggle_objects_25c[1]->set_color(0xffffffffu);
    }
    return true;
}

} // namespace th105
