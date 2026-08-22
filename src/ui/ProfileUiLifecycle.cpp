#include "ProfileUiInfrastructure.hpp"
#include "ProfileMenu.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"

#include "../engine/RenderModeManager.hpp"
#include "../input/InputManager.hpp"

#include <list>

namespace th105 {

struct UiSelectionMenu {
    void **vtable;
};

typedef void (__thiscall *UiSelectionRenderCallback)(UiSelectionMenu *);

struct CNetworkBase;
struct ProfileNameListShutdownView {
    void shutdown();
};

extern "C" CInputManager *g_active_menu_input;
extern "C" ProfileNameList g_profile_name_list;
extern CNetworkBase *get_network_session();
extern PlayerSlotRecord *get_player_slot_record(unsigned slot);
extern void draw_profile_overlay(unsigned char alpha);
extern "C" void __cdecl trim_profile_ui_menu_stack();

extern unsigned g_ui_selection_state;
extern unsigned char g_ui_selection_snapshot;
extern unsigned char g_ui_selection_fade;
extern unsigned char g_profile_network_pair;
extern std::list<UiSelectionMenu *> g_ui_selection_menu_stack;
extern ProfileRenderListView g_profile_menu_background;
extern ProfileRenderListView g_profile_overlay_list;
extern ProfileRenderListView g_profile_footer_background;
extern ProfileRenderListView g_profile_player_list;
extern UiDesignObject *g_profile_player_buttons[2];
extern unsigned int g_profile_back_texture;
extern unsigned int g_profile_cursor_texture;
extern unsigned int g_profile_list_seat_texture;
extern unsigned int g_profile_message_texture;

static UiSprite94 *network_profile_sprite(CNetworkBase *session, unsigned offset)
{
    return reinterpret_cast<UiSprite94 *>(
        reinterpret_cast<unsigned char *>(session) + offset);
}

static UiSprite94 *player_profile_sprite(PlayerSlotRecord *player)
{
    return reinterpret_cast<UiSprite94 *>(
        reinterpret_cast<unsigned char *>(player) + 4);
}

bool __cdecl render_profile_ui_frame()
{
    if (g_ui_selection_fade &&
        (g_ui_selection_snapshot < g_ui_selection_state ||
         g_ui_selection_snapshot <= 0)) {
        bool result = g_render_mode_manager.begin_frame();
        if (!result)
            return result;

        g_render_mode_manager.set_blend_mode(1);
        unsigned int color =
            (static_cast<unsigned int>(g_ui_selection_fade) << 24) |
            0x00ffffffu;
        draw_profile_overlay(g_ui_selection_fade);
        g_profile_menu_background.set_color(color);
        g_profile_menu_background.render();

        UiSprite94 *players[2];
        if (get_network_session() && g_profile_network_pair) {
            players[0] = network_profile_sprite(get_network_session(), 636);
            players[1] = network_profile_sprite(get_network_session(), 784);
        } else {
            players[0] = player_profile_sprite(get_player_slot_record(0));
            players[1] = player_profile_sprite(get_player_slot_record(1));
        }

        int index = 0;
        do {
            UiSprite94 *player = players[index];
            player->set_color(color);
            UiDesignObject *anchor = g_profile_player_buttons[index];
            player->render(
                static_cast<float>(anchor->x + 88.0),
                static_cast<float>(anchor->y + 10.0));
            player->set_color(0xffffffffu);
            ++index;
        } while (index < 2);

        if (g_ui_selection_state != 0) {
            UiSelectionMenu *menu = g_ui_selection_menu_stack.back();
            reinterpret_cast<UiSelectionRenderCallback>(menu->vtable[3])(menu);
        }
        g_render_mode_manager.finish_frame();
    }
    return true;
}

unsigned char __cdecl shutdown_profile_ui()
{
    g_ui_selection_snapshot = 0;
    trim_profile_ui_menu_stack();
    reinterpret_cast<ProfileNameListShutdownView *>(&g_profile_name_list)
        ->shutdown();
    g_profile_overlay_list.clear();
    g_profile_menu_background.clear();
    g_profile_player_list.clear();
    g_profile_footer_background.clear();
    g_title_resource_manager.release_title_resource_handle(g_profile_back_texture);
    g_title_resource_manager.release_title_resource_handle(
        g_profile_list_seat_texture);
    g_title_resource_manager.release_title_resource_handle(
        g_profile_cursor_texture);
    return g_title_resource_manager.release_title_resource_handle(
        g_profile_message_texture);
}

} // namespace th105
