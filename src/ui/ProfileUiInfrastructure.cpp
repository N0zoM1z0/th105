#include "ProfileMenu.hpp"
#include "UiPrimitives.hpp"
#include "ProfileUiInfrastructure.hpp"

#include "../engine/RenderModeManager.hpp"
#include "../input/InputManager.hpp"

namespace th105 {

extern "C" CInputManager *g_active_menu_input;
extern "C" ProfileNameList g_profile_name_list;
extern unsigned char g_round_counter;

static float &menu_cursor_scale_x(MenuCursorSpriteView &sprite)
{
    return *reinterpret_cast<float *>(
        reinterpret_cast<unsigned char *>(&sprite) + 0x88);
}

static float &menu_cursor_scale_y(MenuCursorSpriteView &sprite)
{
    return *reinterpret_cast<float *>(
        reinterpret_cast<unsigned char *>(&sprite) + 0x8c);
}

extern UiDesignObject *g_profile_message_main;
extern UiDesignObject *g_profile_message_choice_a;
extern UiDesignObject *g_profile_message_choice_b;
extern UiDesignObject *g_profile_message_choice_c;
extern UiDesignObject *g_profile_message_choice_d;
extern MenuCursorState g_profile_global_cursor;
extern ProfileRenderListView g_profile_overlay_list;
extern ProfileRenderListView g_profile_footer_background;
extern ProfileRenderListView g_profile_player_list;
extern ProfileSpriteView g_profile_message_sprite;
extern ProfileSpriteView g_profile_character_background;
extern ProfileTileView g_profile_tile;
extern UiDesignObject *g_profile_player_anchor;
extern MenuCursorSpriteView g_menu_cursor_sprite;

void hide_profile_message()
{
    g_profile_message_main->enabled = false;
    g_profile_message_choice_b->enabled = false;
    g_profile_message_choice_c->enabled = false;
    g_profile_message_choice_a->enabled = false;
    g_profile_message_choice_d->enabled = false;
}

void Menu::initialize_profile_menu()
{
    g_profile_name_list.reset();
    int item_count = g_profile_name_list.item_count();
    if (g_active_menu_input)
        g_profile_global_cursor.input_counter =
            &g_active_menu_input->hold.vertical;
    else
        g_profile_global_cursor.input_counter = 0;
    g_profile_global_cursor.selection = 0;
    g_profile_global_cursor.window_start = 0;
    g_profile_global_cursor.item_count = item_count;
    g_profile_global_cursor.page_size = 16;
}

void draw_profile_overlay(unsigned char alpha)
{
    g_render_mode_manager.draw_rect(
        0.0f,
        0.0f,
        640.0f,
        480.0f,
        (3 * alpha / 4) << 24,
        1);
    g_profile_overlay_list.set_color(
        (static_cast<unsigned int>(alpha) << 24) | 0x00ffffffu);
    g_profile_overlay_list.render();
}

void CProfileMenu::render_profile_menu_footer()
{
    if (g_profile_message_main->enabled) {
        g_profile_footer_background.render();
        g_profile_message_sprite.render(
            static_cast<float>(g_profile_message_main->x + 4.0),
            static_cast<float>(g_profile_message_main->y + 10.0));
    }
}

extern "C" void __stdcall render_menu_list(bool alternate)
{
    g_profile_character_background.render(352.0f, 88.0f);
    if (alternate) {
        menu_cursor_scale_x(g_menu_cursor_sprite) = 0.5f;
        menu_cursor_scale_y(g_menu_cursor_sprite) = 1.0f;
        float y = static_cast<float>(
            static_cast<double>(
                g_profile_global_cursor.selection -
                g_profile_global_cursor.window_start) *
                16.0 +
            128.0);
        g_menu_cursor_sprite.render(388.0f, y);
    }

    unsigned int i = 0;
    do {
        float row = static_cast<float>(i);
        float y = static_cast<float>(
            static_cast<double>(row) * 16.0 + 128.0);
        g_profile_name_list.render_item(
            392.0f,
            y,
            i + g_profile_global_cursor.window_start);
        ++i;
    } while (i < 16);
}

void Menu::render_profile_player_slot(
    PlayerSlotRecord *player, float x, float y)
{
    g_profile_player_list.render_offset(x, y);
    UiDesignObject *anchor = g_profile_player_anchor;
    reinterpret_cast<UiSprite94 *>(
        reinterpret_cast<unsigned char *>(player) + 4)->render(
            static_cast<float>(anchor->x + 88.0 + x),
            static_cast<float>(anchor->y + 10.0 + y));
}

void Menu::render_profile_tiles()
{
    int i = 0;
    signed char count = static_cast<signed char>(g_round_counter);
    if (count <= 0)
        return;
    do {
        if (i >= 32)
            break;
        float y = static_cast<float>(
            static_cast<double>(i % 16) * 16.0 + 125.0);
        float x = static_cast<float>(
            static_cast<double>(i / 16) * 260.0 + 60.0);
        g_profile_tile.render(x, y, 0, i);
        ++i;
        count = static_cast<signed char>(g_round_counter);
    } while (i < count);
}

} // namespace th105
