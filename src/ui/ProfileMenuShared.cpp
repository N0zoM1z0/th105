#include "ProfileMenu.hpp"
#include "ProfileUiInfrastructure.hpp"

#include "../input/InputManager.hpp"

extern "C" void __cdecl dispatch_indexed_event(unsigned int index);
extern "C" bool __cdecl is_menu_initial_press(
    unsigned char key, bool modifier_a, bool modifier_b, bool modifier_c);
extern "C" unsigned char profile_editor_records[];

namespace th105 {

extern "C" CInputManager *g_active_menu_input;
extern "C" ProfileNameList g_profile_name_list;
extern MenuCursorState g_profile_global_cursor;
extern MenuCursorState g_profile_message_cursor;
extern unsigned int g_profile_message_texture;
extern ProfileSpriteView g_profile_message_sprite;
extern UiDesignObject *g_profile_message_main;
extern UiDesignObject *g_profile_message_choice_a;
extern UiDesignObject *g_profile_message_choice_b;
extern UiDesignObject *g_profile_message_choice_c;
extern UiDesignObject *g_profile_message_choice_d;

void Menu::show_profile_result(const char *message)
{
    g_title_resource_manager.release_title_resource_handle(
        g_profile_message_texture);

    g_profile_message_texture =
        g_title_resource_manager.create_text_texture(
            message, profile_editor_records, 512, 32, 0, 0).value;

    g_profile_message_sprite.set_texture(
        g_profile_message_texture, 0, 0, 307, 18);
    g_profile_message_main->enabled = true;
}

void Menu::show_profile_message(const char *message, bool alternate)
{
    g_title_resource_manager.release_title_resource_handle(
        g_profile_message_texture);

    g_profile_message_texture =
        g_title_resource_manager.create_text_texture(
            message, profile_editor_records, 512, 32, 0, 0).value;

    g_profile_message_sprite.set_texture(
        g_profile_message_texture, 0, 0, 307, 18);
    g_profile_message_main->enabled = true;
    g_profile_message_choice_b->enabled = !alternate;
    g_profile_message_choice_c->enabled =
        g_profile_message_choice_b->enabled;
    g_profile_message_choice_a->enabled = alternate;
    g_profile_message_choice_d->enabled = alternate;
    g_profile_message_cursor.selection = !alternate;
}

int Menu::select_profile(MenuString28 *selected, MenuString28 *alternate)
{
    int const horizontal = g_active_menu_input->hold.horizontal;
    if (horizontal == 1) {
        dispatch_indexed_event(0x27);
        g_profile_global_cursor.move_page_forward();
    } else if (horizontal == -1) {
        dispatch_indexed_event(0x27);
        g_profile_global_cursor.move_page_backward();
    } else if (g_profile_global_cursor.update()) {
        dispatch_indexed_event(0x27);
    }

    if (g_active_menu_input->hold.buttons[0] == 1) {
        dispatch_indexed_event(0x28);
        MenuString28 *row =
            g_profile_name_list.row_at(g_profile_global_cursor.selection);
        MenuString28 &chosen = selected->assign(*row, 0, ~0u);
        alternate->assign(chosen, 0, ~0u);
        g_profile_name_list.trim_item_text(alternate);
        return 1;
    }

    if (g_active_menu_input->hold.buttons[1] == 1 ||
        is_menu_initial_press(1, false, false, false)) {
        dispatch_indexed_event(0x29);
        return 2;
    }
    return 0;
}

} // namespace th105
