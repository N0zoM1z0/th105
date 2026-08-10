#include "ProfileMenu.hpp"

#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);
extern "C" th105::ProfileMenuController g_profile_menu_controller;

namespace th105 {

bool CProfileMenu::update_primary()
{
    HoldCounters *input = &g_active_menu_input->hold;
    guides_5a4[0].visible = true;

    if (cursor_39c.update())
        dispatch_indexed_event(0x27);

    if (input->buttons[0] == 1) {
        dispatch_indexed_event(0x28);
        substate_344 = 0;
        switch (cursor_39c.selection) {
        case 0:
            state_340 = 2;
            return true;
        case 1:
            state_340 = 3;
            return true;
        case 2:
            state_340 = 1;
            label_37c->enabled = true;
            g_profile_menu_controller.set_mode(1);
            return true;
        case 3:
            state_340 = 4;
            return true;
        case 4:
            state_340 = 5;
            return true;
        case 5:
            state_340 = 6;
            return true;
        case 6:
            return false;
        default:
            goto keep_open;
        }
    }

    if (input->buttons[1] != 1 &&
        !is_menu_initial_press(1, 0, 0, 0))
        goto keep_open;
    dispatch_indexed_event(0x29);
    return false;

keep_open:
    return true;
}

} // namespace th105
