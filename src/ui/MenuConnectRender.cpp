#include "ui/CNumberRuntime.hpp"
#include "ui/MenuConnectStateRuntime.hpp"
#include "ui/Title.hpp"
#include "ui/UiPrimitives.hpp"
#include "config/GameConfig.hpp"
#include <deque>
#include <string>
namespace th105 {
extern "C" void __stdcall render_menu_list(bool);
extern UiDesignObject *g_profile_message_main;
struct ConnectRenderHandle { unsigned int value; };
class CMenuConnectRenderView : public Menu {
public:
    virtual void render();
private:
    void render_footer();
    CNetworkBase *network_004;
    signed char state_008;
    unsigned char substate_009, reserved_00a[2];
    TitleDesignResource design_00c;
    UiDesignObject *items_040[7];
    unsigned char reserved_05c[4];
    ConnectRenderHandle texture_060;
    CTile tile_064;
    CNumber number_108;
    CSprite sprite_1d4;
    CSprite sprite_268;
    ConnectRenderHandle texture_2fc;
    CTile tile_300;
    std::deque<std::string> rows_3a4;
    unsigned int reserved_3b8;
    MenuCursorState cursor_3bc;
    unsigned char reserved_3d0[0x20];
    int list_index_3f0;
    unsigned char reserved_3f4[4];
    MenuCursorState cursor_3f8;
    MenuCursorState cursor_40c;
    unsigned short address_parts_420[4];
    unsigned int port_428;
    MenuString28 endpoint_42c;
    wchar_t endpoint_wide_448[260];
    unsigned char reserved_650[0x5f8];
    GameConfig *config_c48;
    GuideOverlay guides_c4c[8];
};
typedef char ConnectRenderSize[sizeof(CMenuConnectRenderView)==0x118c?1:-1];
void CMenuConnectRenderView::render()
{
    if (state_008 == 6) {
        render_menu_list(true);
    } else {
        render_menu_list(false);
        UiDesignObject *item = items_040[cursor_3bc.selection];
        render_cursor(item->x, static_cast<float>(item->y + 8.0), 256.0f);
    }
    design_00c.render();
    render_footer();
    switch (state_008) {
        case 1: if (!substate_009) {
            float x = static_cast<float>(g_profile_message_main->x + 192.0);
            float y = static_cast<float>(g_profile_message_main->y + 32.0);
            number_108.render(port_428, x, y, 5, 0);
            sprite_1d4.render(static_cast<float>(x - 14 * (4 - cursor_3f8.selection)), y);
        } break;
        case 2: if (!substate_009) {
            float x = static_cast<float>(g_profile_message_main->x + 32.0);
            float y = static_cast<float>(g_profile_message_main->y + 32.0);
            sprite_268.render(x, y);
            double first_x = x + 42.0;
            for (int i = 0; i < 4; ++i)
                number_108.render(address_parts_420[i], static_cast<float>(i * 49.0 + first_x), y, 3, 0);
            number_108.render(port_428, static_cast<float>(x + 266.0), y, 5, 0);
            int selected = cursor_3f8.selection;
            int column = 2 * selected + (selected >= 3) + (selected >= 6) + (selected >= 9) + (selected >= 12);
            sprite_1d4.render(static_cast<float>(column * 7.0 + (x + 14.0)), y);
        } break;
        case 3: case 4: if (!substate_009) {
            float x = static_cast<float>(g_profile_message_main->x + 300.0 - 256.0);
            float y = static_cast<float>(g_profile_message_main->y + 40.0);
            tile_300.render(x, y, 0, list_index_3f0);
        } break;
        default: break;
    }
    for (int i = 0; i < 8; ++i)
        guides_c4c[i].render();
}
}
