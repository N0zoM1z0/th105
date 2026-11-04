#include "ui/MenuConfigUpdate.hpp"
#include "ui/UiPrimitives.hpp"
#include "input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {
void CMenuConfigUpdateView::update_secondary_for_primary(int primary)
{
    switch (primary) {
    case 0: {
        secondary_278.bind_horizontal(g_active_menu_input, 4, 0);
        int value = config_004->option_64;
        if (value > 3)
            value = 3;
        else if (value < 0)
            value = 0;
        secondary_278.selection = value;
        return;
    }
    case 1: {
        secondary_278.bind_horizontal(g_active_menu_input, 21, 0);
        int value = config_004->bgm_percent_68 / 5;
        if (value > 20)
            value = 20;
        else if (value < 0)
            value = 0;
        secondary_278.selection = value;
        sprites_b8[0].set_texture(
            texture_b4, 0, 0,
            static_cast<int>(grid_width_1e0 *
                static_cast<unsigned>(config_004->bgm_percent_68) / 100),
            grid_height_1e4);
        return;
    }
    case 2: {
        secondary_278.bind_horizontal(g_active_menu_input, 21, 0);
        int value = config_004->se_percent_6c / 5;
        if (value > 20)
            value = 20;
        else if (value < 0)
            value = 0;
        secondary_278.selection = value;
        sprites_b8[1].set_texture(
            texture_b4, 0, 0,
            static_cast<int>(grid_width_1e0 *
                static_cast<unsigned>(config_004->se_percent_6c) / 100),
            grid_height_1e4);
        return;
    }
    case 3:
        secondary_278.bind_horizontal(g_active_menu_input, 2, 0);
        secondary_278.selection = !config_004->windowed_70;
        return;
    case 4:
        secondary_278.bind_horizontal(g_active_menu_input, 2, 0);
        secondary_278.selection = !config_004->option_71;
        return;
    default:
        return;
    }
}
}
