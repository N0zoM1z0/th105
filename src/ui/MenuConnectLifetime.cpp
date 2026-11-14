// Actual member destruction uses the independently exact-backed IColor/CNumber lifetimes.
#include "ui/CNumberLifetime.hpp"
#include "ui/MenuConnectStateRuntime.hpp"
#include "ui/Title.hpp"
#include "config/GameConfig.hpp"
#include "input/InputSelection.hpp"
#include <deque>
#include <string>
namespace th105 {

// Pointer-only view of the existing global; no storage is constructed here.
struct ConnectProfileListView { void shutdown(); };
extern ConnectProfileListView g_connect_profile_list;
class CMenuConnectLifetime : public Menu {
public:
    CMenuConnectLifetime();
    virtual ~CMenuConnectLifetime();
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
    DesignTextureHandle texture_060;
    CTile tile_064;
    CNumberLifetime number_108;
    CSprite sprite_1d4;
    CSprite sprite_268;
    DesignTextureHandle texture_2fc;
    CTile tile_300;
    std::deque<std::string> rows_3a4;
    unsigned int reserved_3b8;
    MenuCursorState cursor_3bc;
    unsigned char reserved_3d0[0x28];
    MenuCursorState cursor_3f8;
    MenuCursorState cursor_40c;
    unsigned short address_parts_420[4];
    unsigned int port_428;
    std::string endpoint_42c;
    wchar_t endpoint_wide_448[260];
    unsigned char reserved_650[0x5F8];
    GameConfig *config_c48;
    GuideOverlay guides_c4c[8];
};

typedef char ConnectDequeString_size_must_be_0x14[
    sizeof(std::deque<std::string>) == 0x14 ? 1 : -1];
typedef char CMenuConnectLifetime_size_must_be_0x118c[
    sizeof(CMenuConnectLifetime) == 0x118C ? 1 : -1];

CMenuConnectLifetime::~CMenuConnectLifetime()
{
    g_connect_profile_list.shutdown();
    g_title_resource_manager.release_title_resource_handle(texture_060);
    g_title_resource_manager.release_title_resource_handle(texture_2fc);
    design_00c.virtual_cleanup();
}
}
