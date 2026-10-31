// Complete JP1.06a configuration-menu constructor. Full comparison remains nonexact.
// See docs/CONFIG_MENU_CONSTRUCTOR_2026_10_31.md.
#include "ui/Menu.hpp"
#include "ui/MenuConfigUpdate.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "ui/Title.hpp"
#include "ui/MenuCursorBindings.cpp"
#include "ui/DesignObjectLookup.cpp"
#include "config/GameConfig.hpp"
namespace th105 {
extern "C" CInputManager *g_active_menu_input;
struct TitleResourceManagerValueView {
    TextureHandleResult load_texture_value(const char *, unsigned *, unsigned *);
};
extern TitleResourceManagerValueView g_title_resource_manager_value;
class CMenuConfig : public Menu {
public:
    CMenuConfig();
    virtual ~CMenuConfig();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();
    ConfigStateView *config_004;
    GuideOverlay guide_008;
    bool option_b0;
    unsigned texture_b4;
    UiSprite94 sprites_b8[2];
    unsigned width_1e0, height_1e4;
    CDesignBase design_1e8;
    unsigned char unknown_21c[8];
    UiDesignObject *items_224[6];
    UiDesignObject *options_23c[4];
    UiDesignObject *window_24c[4];
    UiDesignObject *toggles_25c[2];
    MenuCursorState primary_264, secondary_278;
};
typedef char ConfigSize[sizeof(CMenuConfig)==0x28c?1:-1];
typedef char ConfigDesign[offsetof(CMenuConfig,design_1e8)==0x1e8?1:-1];
CMenuConfig::CMenuConfig() : texture_b4(0)
{
    config_004 = reinterpret_cast<ConfigStateView *>(get_game_config());
    design_1e8.load("data/menu/config/config.dat");
    primary_264.bind_vertical(g_active_menu_input, 6, 0);
    for(int i=0;i<6;++i) {
        design_1e8.bind_object_alt(&items_224[i],i+100);
        items_224[i]->enabled=true;
    }
    for(int i=0;i<4;++i) {
        design_1e8.bind_object_alt(&options_23c[i],i+200);
        options_23c[i]->enabled=true;
    }
    for(int i=0;i<2;++i) {
        design_1e8.bind_object_alt(&window_24c[i+2],i+500);
        window_24c[i+2]->enabled=true;
    }
    for(int i=0;i<2;++i) {
        design_1e8.bind_object_alt(&toggles_25c[i],i+600);
        toggles_25c[i]->enabled=true;
    }
    design_1e8.find_object(&window_24c[0],300);
    window_24c[0]->enabled=true;
    design_1e8.find_object(&window_24c[1],400);
    window_24c[1]->enabled=true;
    texture_b4=g_title_resource_manager_value.load_texture_value(
        "data/menu/config/mater.bmp",&width_1e0,&height_1e4).value;
    sprites_b8[0].set_texture(texture_b4,0,0,
        width_1e0*config_004->bgm_percent_68/100,height_1e4);
    sprites_b8[1].set_texture(texture_b4,0,0,
        width_1e0*config_004->se_percent_6c/100,height_1e4);
    guide_008.load(20);
    guide_008.visible=true;
    option_b0=false;
    secondary_278.bind_horizontal(g_active_menu_input,4,0);
    int selected=config_004->option_64;
    if(selected<=3) {
        if(selected<0)selected=0;
    } else selected=3;
    secondary_278.selection=selected;
}
}
