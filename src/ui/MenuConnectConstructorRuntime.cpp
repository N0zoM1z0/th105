#include "CNumberRuntime.hpp"
#include "MenuConnectStateRuntime.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"
#include "../config/GameConfig.hpp"
#include "../input/InputSelection.hpp"

#include <deque>
#include <string>

extern "C" unsigned char profile_editor_records[];
extern "C" const char connect_ctor_initial_text[];
extern "C" const char connect_ctor_design_path[];

namespace th105 {

struct ConnectTextureHandle {
    unsigned int value;
    ConnectTextureHandle() : value(0) {}
};

typedef char ConnectTextureHandle_size_must_be_0x04[
    sizeof(ConnectTextureHandle) == 0x04 ? 1 : -1];

class CMenuConnect : public Menu {
public:
    CMenuConnect();
    virtual ~CMenuConnect();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    void hide_profile_message_43f8d0();

    CNetworkBase *network_004;
    unsigned char state_008;
    unsigned char substate_009;
    unsigned char reserved_00a[2];
    TitleDesignResource design_00c;
    UiDesignObject *items_040[7];
    unsigned char reserved_05c[4];
    ConnectTextureHandle texture_060;
    UiTileA4 tile_064;
    CNumber number_108;
    UiSprite94 sprite_1d4;
    UiSprite94 sprite_268;
    ConnectTextureHandle texture_2fc;
    UiTileA4 tile_300;
    std::deque<std::string> rows_3a4;
    unsigned int reserved_3b8;
    MenuCursorState cursor_3bc;
    unsigned char reserved_3d0[0x28];
    MenuCursorState cursor_3f8;
    MenuCursorState cursor_40c;
    unsigned short address_parts_420[4];
    unsigned int port_428;
    MenuString28 endpoint_42c;
    wchar_t endpoint_wide_448[260];
    unsigned char reserved_650[0x5F8];
    GameConfig *config_c48;
    GuideOverlay guides_c4c[8];
};

typedef char ConnectDequeString_size_must_be_0x14[
    sizeof(std::deque<std::string>) == 0x14 ? 1 : -1];
typedef char CMenuConnect_size_must_be_0x118c[
    sizeof(CMenuConnect) == 0x118C ? 1 : -1];

CMenuConnect::CMenuConnect()
{
    network_004 = get_network_session();

    texture_060.value = g_title_resource_manager.create_text_texture(
        connect_ctor_initial_text,
        profile_editor_records,
        256,
        256,
        0,
        0).value;
    tile_064.set_texture(texture_060.value, 0, 0, 256, 16);

    number_108.initialize(texture_060.value, 1, 0, 15, 16, 10, 0.0f, 0, 0, 0);
    number_108.bind_value(&cursor_3bc.selection);

    sprite_1d4.set_texture_options(texture_060.value, 0, 16, 16, 16, 15, -13);
    sprite_268.set_texture(texture_060.value, 0, 32, 256, 16);

    design_00c.load(connect_ctor_design_path);
    for (int i = 0; i < 7; ++i) {
        design_00c.bind_object_alt(&items_040[i], i + 100);
        items_040[i]->enabled = true;
    }

    if (g_active_menu_input != 0)
        cursor_3bc.input_counter = &g_active_menu_input->hold.vertical;
    else
        cursor_3bc.input_counter = 0;
    cursor_3bc.selection = 0;
    cursor_3bc.window_start = 0;
    cursor_3bc.item_count = 7;
    cursor_3bc.page_size = 0;

    hide_profile_message_43f8d0();
    state_008 = 0;
    initialize_profile_menu();

    config_c48 = get_game_config();
    guides_c4c[0].load(8);
    guides_c4c[1].load(11);
    guides_c4c[2].load(0);
    guides_c4c[3].load(2);
    guides_c4c[4].load(1);
    guides_c4c[5].load(2);
    guides_c4c[6].load(5);
    guides_c4c[7].load(10);
    g_scene_mode = 22;
}

} // namespace th105
