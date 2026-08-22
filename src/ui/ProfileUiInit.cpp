#include "ProfileUiInfrastructure.hpp"
#include "ProfileMenu.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"

#include "../input/InputManager.hpp"

#include <string.h>

namespace th105 {

struct ProfileUiEffectConfig {
    char text_000[256];
    unsigned char color_100[6];
    unsigned char alignment_106[2];
    int count_108;
    int duration_10c;
    unsigned char flag_110;
    unsigned char flag_111;
    unsigned char flag_112;
    unsigned char alignment_113;
    int interval_114;
    int mode_118;
    int state_11c;
    int option_120;
    int option_124;
};

typedef char ProfileUiEffectConfig_size_must_be_0x128[
    sizeof(ProfileUiEffectConfig) == 0x128 ? 1 : -1];

struct ProfileUiEffectOwnerView {
    void configure(const ProfileUiEffectConfig *config);
};

extern "C" unsigned char profile_editor_records[];
extern "C" CInputManager *g_active_menu_input;

extern ProfileRenderListView g_profile_overlay_list;
extern ProfileRenderListView g_profile_menu_background;
extern ProfileRenderListView g_profile_footer_background;
extern ProfileRenderListView g_profile_player_list;
extern UiDesignObject *g_profile_player_buttons[2];
extern UiDesignObject *g_profile_message_main;
extern UiDesignObject *g_profile_message_choice_a;
extern UiDesignObject *g_profile_message_choice_b;
extern UiDesignObject *g_profile_message_choice_c;
extern UiDesignObject *g_profile_message_choice_d;
extern UiDesignObject *g_profile_player_anchor;
extern MenuCursorState g_profile_message_cursor;
extern MenuCursorSpriteView g_menu_cursor_sprite;
extern ProfileSpriteView g_profile_character_background;
extern unsigned int g_profile_cursor_texture;
extern unsigned int g_profile_list_seat_texture;

extern "C" const char profile_ui_effect_label[];
extern "C" const char profile_menu_back_path[];
extern "C" const char profile_menu_profile_path[];
extern "C" const char profile_menu_window_path[];
extern "C" const char profile_menu_profile_edit_path[];
extern "C" const char profile_cursor_path[];
extern "C" const char profile_list_seat_path[];

bool __cdecl initialize_profile_ui(CInputManager *input)
{
    g_active_menu_input = input;

    ProfileUiEffectConfig config;
    config.duration_10c = 400;
    config.flag_110 = 0;
    config.flag_111 = 0;
    config.flag_112 = 0;
    config.option_120 = 0;
    config.option_124 = 0;
    config.mode_118 = 0;
    config.state_11c = 0;
    config.interval_114 = 100000;
    strcpy_s(config.text_000, 256, profile_ui_effect_label);
    config.count_108 = 14;
    config.duration_10c = 300;
    config.color_100[0] = 0xff;
    config.color_100[1] = 0xa0;
    config.color_100[2] = 0xff;
    config.color_100[3] = 0xa0;
    config.color_100[4] = 0xff;
    config.color_100[5] = 0xff;
    config.option_120 = 0;
    config.option_124 = 2;
    config.flag_111 = 1;
    reinterpret_cast<ProfileUiEffectOwnerView *>(profile_editor_records)
        ->configure(&config);

    g_profile_overlay_list.load(profile_menu_back_path);
    g_profile_menu_background.load(profile_menu_profile_path);
    g_profile_menu_background.bind_object_alt(&g_profile_player_buttons[0], 100);
    g_profile_menu_background.bind_object_alt(&g_profile_player_buttons[1], 101);
    g_profile_player_buttons[0]->enabled = true;
    g_profile_player_buttons[1]->enabled = true;

    g_profile_footer_background.load(profile_menu_window_path);
    g_profile_footer_background.bind_object_alt(&g_profile_message_main, 21);
    g_profile_footer_background.bind_object_alt(&g_profile_message_choice_c, 122);
    g_profile_footer_background.bind_object_alt(&g_profile_message_choice_d, 222);
    g_profile_footer_background.bind_object_alt(&g_profile_message_choice_a, 123);
    g_profile_footer_background.bind_object_alt(&g_profile_message_choice_b, 223);

    g_profile_player_list.load(profile_menu_profile_edit_path);
    g_profile_player_list.bind_object_alt(&g_profile_player_anchor, 100);
    g_profile_player_anchor->enabled = true;

    unsigned int token;
    unsigned int width;
    unsigned int height;
    g_profile_cursor_texture = *g_title_resource_manager.load_texture(
        &token, profile_cursor_path, &width, &height);
    g_menu_cursor_sprite.set_texture(
        g_profile_cursor_texture, 0, 0, width, height);

    g_profile_message_cursor.input_counter =
        g_active_menu_input ? &g_active_menu_input->hold.horizontal : 0;
    g_profile_message_cursor.selection = 0;
    g_profile_message_cursor.window_start = 0;
    g_profile_message_cursor.item_count = 2;
    g_profile_message_cursor.page_size = 0;

    g_profile_list_seat_texture = *g_title_resource_manager.load_texture(
        &token, profile_list_seat_path, &width, &height);
    g_profile_character_background.set_texture(
        g_profile_list_seat_texture, 0, 0, width, height);
    return true;
}

} // namespace th105
