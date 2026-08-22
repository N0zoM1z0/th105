#include "ProfileMenu.hpp"
#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);

namespace th105 {
extern UiDesignObject *g_profile_message_main;
} // namespace th105

extern "C" int __cdecl update_profile_confirmation()
{
    th105::CInputManager *input = g_active_menu_input;
    if (input->hold.buttons[0] == 1) {
        dispatch_indexed_event(0x28);
        th105::g_profile_message_main->enabled = false;
        return 1;
    }
    if (input->hold.buttons[1] == 1 ||
        is_menu_initial_press(1, 0, 0, 0)) {
        dispatch_indexed_event(0x29);
        th105::g_profile_message_main->enabled = false;
        return 2;
    }
    return 0;
}
