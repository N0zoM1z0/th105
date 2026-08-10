#include "MenuSelect.hpp"

extern "C" void __stdcall render_menu_list(bool alternate);
extern "C" const char menu_select_design_path[];
extern "C" unsigned char *g_active_menu_input;

namespace th105 {

CMenuSelect::CMenuSelect()
{
    g_scene_mode = 3;
    design_08.load(menu_select_design_path);

    if (g_active_menu_input != 0)
        cursor_5c.input_counter =
            reinterpret_cast<int *>(g_active_menu_input + 0x3C);
    else
        cursor_5c.input_counter = 0;
    cursor_5c.selection = 0;
    cursor_5c.window_start = 0;
    cursor_5c.page_size = 0;
    cursor_5c.item_count = 8;

    int object_id = 100;
    UiDesignObject **item = items_3c;
    do {
        design_08.bind_object_alt(item, object_id);
        (*item)->enabled = true;
        object_id += 10;
        ++item;
    } while (object_id < 180);

    initialize_profile_menu();
    state_04 = 0;
    guides_74[0].load(5);
    guides_74[1].load(11);
    g_scene_mode = 22;
}

CMenuSelect::~CMenuSelect()
{
    design_08.virtual_cleanup();
}

bool CMenuSelect::update()
{
    GuideOverlay *guide = guides_74;
    int count = 2;
    do {
        guide->update();
        guide->visible = false;
        ++guide;
        --count;
    } while (count != 0);

    switch (state_04) {
    case 0:
        return update_primary_selection();
    case 1:
        return update_player_assignment();
    default:
        return true;
    }
}

void CMenuSelect::render()
{
    if (state_04 == 1) {
        render_menu_list(true);
    } else {
        render_menu_list(false);
        UiDesignObject *item = items_3c[cursor_5c.selection];
        render_cursor(item->x, item->y + 8.0f, 256.0f);
    }

    design_08.render();
    guides_74[0].render();
    guides_74[1].render();
}

} // namespace th105
