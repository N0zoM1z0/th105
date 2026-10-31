// JP1.06a practice menu construction; ordinary ownership and temporary result.
#include "ui/MenuPractice.hpp"
#include "input/InputManager.hpp"
#include "ui/MenuCursorBindings.cpp"
#include "ui/DesignObjectLookup.cpp"
namespace th105 {
extern "C" CInputManager *g_active_menu_input;
extern PracticeBattleSettingsView *g_practice_settings;
struct TitleResourceManagerValueView {
 TextureHandleResult load_texture_value(const char *, unsigned *, unsigned *);
};
extern TitleResourceManagerValueView g_title_resource_manager_value;
CMenuPractice::CMenuPractice(PracticeOwnerView *owner) : texture_0b4(0)
{
    owner_284 = owner;
    settings_004 = g_practice_settings;
    cursors_25c[0].bind_vertical(g_active_menu_input, 10, 0);
    design_160.load("data/menu/practice/practice.dat");
    int counts[10] = {0, 1, 6, 4, 4, 5, 2, 4, 0, 0};
    for (int category = 0; category < 10; ++category) {
        design_160.bind_object_alt(&category_items_194[category], category * 100 + 1000);
        category_items_194[category]->enabled = true;
        for (int i = 0; i < counts[category]; ++i) {
            UiDesignObject *object;
            design_160.find_object(&object, i + category * 100);
            groups_1bc[category].push_back(object);
            groups_1bc[category][i]->enabled = true;
        }
    }
    unsigned width, height;
    texture_0b4 = g_title_resource_manager_value.load_texture_value(
        "data/menu/practice/Weather_list.bmp", &width, &height).value;
    weather_tile_0b8.set_texture(texture_0b4, 0, 0, width, 24);
    guide_008.load(7);
    guide_008.visible = true;
    field_0b0 = 0;
    configure_subcursor(0);
    g_scene_mode = 22;
}
}
