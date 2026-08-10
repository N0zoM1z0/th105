#include "MenuSelect.hpp"

#include "../input/InputSelection.hpp"

extern "C" void __cdecl select_input_slot(int slot, bool allow_duplicate);
extern "C" void __cdecl reload_selected_profiles();

namespace th105 {

bool CMenuSelect::update_player_assignment()
{
    guides_74[1].visible = true;

    int index = 0;
    UiDesignObject **item = items_3c;
    do {
        if (cursor_5c.selection == index)
            (*item)->set_color(0xFFFFFFFF);
        else
            (*item)->set_color(0xFF808080);
        ++index;
        ++item;
    } while (index < 8);

    MenuString28 selected;
    MenuString28 alternate;
    switch (select_profile(&selected, &alternate)) {
    case 1: {
        const char *profile = selected.c_str();
        if (get_player_slot_record(active_player_70)->load_profile(
                profile)) {
            if (active_player_70 == 0)
                get_player_slot_record(0)->set_profile_color(
                    0xA0, 0xA0, 0xFF);
            else
                get_player_slot_record(active_player_70)->set_profile_color(
                    0xFF, 0x80, 0x80);

            invalidate_selected_input(active_player_70);
            if (active_player_70 == 0)
                select_input_slot(0, false);
            else if (active_player_70 == 1)
                select_input_slot(1, true);
            reload_selected_profiles();
            state_04 = 0;
        }
        break;
    }
    case 2:
        state_04 = 0;
        break;
    }
    return true;
}

} // namespace th105
