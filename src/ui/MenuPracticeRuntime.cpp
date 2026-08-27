#include "MenuPractice.hpp"

#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {

static inline void bind_practice_horizontal_cursor(
    MenuCursorState *cursor, CInputManager *input, int count)
{
    if (input)
        cursor->input_counter = &input->hold.horizontal;
    else
        cursor->input_counter = 0;
    cursor->selection = 0;
    cursor->window_start = 0;
    cursor->item_count = count;
    cursor->page_size = 0;
}

void CMenuPractice::configure_subcursor(int category)
{
    MenuCursorState &cursor = cursors_25c[1];
    switch (category) {
    default:
        if (groups_1bc[category].size()) {
            bind_practice_horizontal_cursor(
                &cursor,
                g_active_menu_input,
                static_cast<int>(groups_1bc[category].size()));
            cursor.selection = settings_004->category_value_00c[category];
        } else {
            bind_practice_horizontal_cursor(&cursor, g_active_menu_input, 1);
        }
        break;
    case 1:
        bind_practice_horizontal_cursor(&cursor, g_active_menu_input, 15);
        cursor.selection = settings_004->category_value_00c[1];
        break;
    }
}

CMenuPractice::~CMenuPractice()
{
    g_title_resource_manager.release_title_resource_handle(texture_0b4);
    design_160.virtual_cleanup();
}

} // namespace th105
