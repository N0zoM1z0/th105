#include "ReplayMenu.hpp"

#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" int g_next_scene_mode;
extern "C" const char menu_replay_design_path[];

namespace th105 {

CMenuReplay::CMenuReplay()
{
    g_scene_mode = 22;
    g_next_scene_mode = 3;
    design_bc.load(menu_replay_design_path);

    int index = 0;
    do {
        design_bc.bind_object_alt(&items_f0[index], index + 100);
        items_f0[index]->enabled = true;
        ++index;
    } while (index < 3);

    if (g_active_menu_input != 0)
        mode_cursor_fc.input_counter = &g_active_menu_input->hold.vertical;
    else
        mode_cursor_fc.input_counter = 0;
    mode_cursor_fc.selection = 0;
    mode_cursor_fc.window_start = 0;
    mode_cursor_fc.item_count = 3;
    mode_cursor_fc.page_size = 0;
    file_cursor_110.selection = 0;
    refresh_file_list();

    state_04 = 0;
    guides_124[0].load(5);
    guides_124[1].load(11);
}

CMenuReplay::~CMenuReplay()
{
    replay_list_08.shutdown();
    design_bc.virtual_cleanup();
}

void CMenuReplay::unknown_menu_method()
{
    g_scene_mode = 22;
}

} // namespace th105
