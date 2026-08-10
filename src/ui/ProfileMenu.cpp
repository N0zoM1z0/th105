#include "ProfileMenu.hpp"

#include "../input/InputManager.hpp"

extern "C" const char profile_menu_design_path[];
extern "C" unsigned char profile_editor_records[];
extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl reset_profile_menu_data();
extern "C" void __stdcall render_menu_list(bool alternate);

namespace th105 {

CProfileMenu::CProfileMenu()
{
    editor_3b0.initialize(profile_editor_records, 0x18);
    design_348.load(profile_menu_design_path);

    if (g_active_menu_input != 0)
        cursor_39c.input_counter = &g_active_menu_input->hold.vertical;
    else
        cursor_39c.input_counter = 0;
    cursor_39c.selection = 0;
    cursor_39c.window_start = 0;
    cursor_39c.item_count = 7;
    cursor_39c.page_size = 0;

    design_348.bind_object_alt(&label_37c, 20);
    int index = 0;
    do {
        design_348.bind_object_alt(&items_380[index], index + 100);
        items_380[index]->enabled = true;
        ++index;
    } while (index < 7);

    initialize_profile_menu();
    guides_5a4[0].load(8);
    guides_5a4[1].load(9);
    guides_5a4[2].load(10);
    guides_5a4[3].load(2);
    guides_5a4[4].load(11);
    state_340 = 0;
}

CProfileMenu::~CProfileMenu()
{
    design_348.virtual_cleanup();
    editor_3b0.shutdown();
    base_data_004.cleanup();
    reset_profile_menu_data();
}

void CProfileMenu::render()
{
    if (state_340 == 0 || state_340 == 1) {
        render_menu_list(false);
        UiDesignObject *item = items_380[cursor_39c.selection];
        render_cursor(item->x, item->y + 4.0f, 256.0f);
    } else {
        render_menu_list(true);
    }

    design_348.render();
    editor_3b0.render(label_37c->x + 116.0f, label_37c->y + 25.0f);

    GuideOverlay *guide = guides_5a4;
    int count = 5;
    do {
        guide->render();
        ++guide;
        --count;
    } while (count != 0);

    render_profile_menu_footer();
}

} // namespace th105
