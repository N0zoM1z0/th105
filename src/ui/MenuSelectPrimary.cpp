#include "MenuSelect.hpp"
#include "ProfileSubmenus.hpp"

#include "../battle/GameMode.hpp"
#include "../input/InputManager.hpp"
#include "../input/InputSelection.hpp"

extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {
void __cdecl dispatch_indexed_event(unsigned index);
bool __cdecl is_menu_initial_press(unsigned char, bool, bool, bool);
void __cdecl install_menu_object(void *object);

bool CMenuSelect::update_primary_selection()
{
    guides_74[0].visible = true;
    HoldCounters *input = &g_active_menu_input->hold;

    if (cursor_5c.update())
        dispatch_indexed_event(0x27);

    UiDesignObject **item = items_3c;
    int count = 8;
    do {
        (*item)->set_color(0xFFFFFFFF);
        ++item;
        --count;
    } while (count != 0);

    if (input->buttons[0] == 1) {
        dispatch_indexed_event(0x28);
        reserved_05 = 0;

        switch (cursor_5c.selection) {
        case 0:
            state_04 = 1;
            active_player_70 = 0;
            return true;
        case 1:
            state_04 = 1;
            active_player_70 = 1;
            return true;
        case 2:
        {
            Menu *menu =
                new CProfileCharacterSelect(get_player_slot_record(0));
            install_menu_object(menu);
            active_player_70 = 0;
            return true;
        }
        case 3:
        {
            Menu *menu =
                new CProfileCharacterSelect(get_player_slot_record(1));
            install_menu_object(menu);
            active_player_70 = 1;
            return true;
        }
        case 4:
        {
            Menu *menu =
                new CProfileKeyConfig(get_player_slot_record(0), 0);
            install_menu_object(menu);
            return true;
        }
        case 5:
        {
            Menu *menu;
            if (get_game_mode() == GAME_MODE_NETWORK_SERVER)
                menu = new CProfileKeyConfig(get_player_slot_record(1), 1);
            else
                menu = new CProfileKeyConfig(get_player_slot_record(1), -1);
            install_menu_object(menu);
            return true;
        }
        case 6:
            g_scene_mode = 2;
            return true;
        case 7:
            return false;
        }
    } else if (input->buttons[1] == 1 ||
               is_menu_initial_press(1, 0, 0, 0)) {
        dispatch_indexed_event(0x29);
        return false;
    }
    return true;
}

} // namespace th105
