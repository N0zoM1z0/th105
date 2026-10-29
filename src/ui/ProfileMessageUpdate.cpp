#include "MenuCursor.hpp"
#include "UiPrimitives.hpp"
#include "../input/InputManager.hpp"
namespace th105 {
extern "C" CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(int);
extern "C" bool __cdecl is_menu_initial_press(int,int,int,int);
extern UiDesignObject *g_profile_message_main;
extern UiDesignObject *g_profile_message_choice_a;
extern UiDesignObject *g_profile_message_choice_b;
extern UiDesignObject *g_profile_message_choice_c;
extern UiDesignObject *g_profile_message_choice_d;
extern MenuCursorState g_profile_message_cursor;
static void hide_message()
{
    g_profile_message_main->enabled = false;
    g_profile_message_choice_b->enabled = false;
    g_profile_message_choice_c->enabled = false;
    g_profile_message_choice_a->enabled = false;
    g_profile_message_choice_d->enabled = false;
}
extern "C" int __cdecl update_profile_message()
{
    if (g_profile_message_cursor.update()) {
        dispatch_indexed_event(0x27);
        if (g_profile_message_cursor.selection == 0) {
            g_profile_message_choice_b->enabled = false;
            g_profile_message_choice_c->enabled = false;
            g_profile_message_choice_a->enabled = true;
            g_profile_message_choice_d->enabled = true;
        } else {
            g_profile_message_choice_b->enabled = true;
            g_profile_message_choice_c->enabled = true;
            g_profile_message_choice_a->enabled = false;
            g_profile_message_choice_d->enabled = false;
        }
        return 0;
    }
    if (g_active_menu_input->hold.buttons[0] == 1) {
        dispatch_indexed_event(0x28);
        hide_message();
        return (g_profile_message_cursor.selection != 0) + 3;
    }
    if (g_active_menu_input->hold.buttons[1] == 1 ||
        is_menu_initial_press(1,0,0,0)) {
        dispatch_indexed_event(0x29);
        hide_message();
        return 2;
    }
    return 0;
}
}
