#include "ReplayMenu.hpp"

#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {

struct ReplayHeaderServiceView;
ReplayHeaderServiceView *get_replay_header_service();

static inline void bind_replay_vertical_cursor(
    MenuCursorState *cursor, CInputManager *input, int count)
{
    if (input)
        cursor->input_counter = &input->hold.vertical;
    else
        cursor->input_counter = 0;
    cursor->selection = 0;
    cursor->window_start = 0;
    cursor->item_count = count;
    cursor->page_size = 16;
}

void CMenuReplay::refresh_file_list()
{
    unsigned int previous =
        static_cast<unsigned int>(file_cursor_110.selection);
    CFileList *const list = &replay_list_08;
    list->populate();

    if (list->item_count()) {
        int item_count = list->item_count();
        bind_replay_vertical_cursor(
            &file_cursor_110, g_active_menu_input, item_count);

        ReplayHeaderServiceView *service = get_replay_header_service();
        const std::string *current = reinterpret_cast<const std::string *>(
            reinterpret_cast<unsigned char *>(service) + 0x108);
        int found = list->find_row(current);
        if (found >= 0) {
            file_cursor_110.selection = found;
            if (found >= 16)
                file_cursor_110.window_start = found;
        }
    } else {
        bind_replay_vertical_cursor(&file_cursor_110, g_active_menu_input, 1);
    }

    if (previous < static_cast<unsigned int>(list->item_count())) {
        file_cursor_110.selection = static_cast<int>(previous);
        file_cursor_110.window_start = static_cast<int>(previous);
    }
}

} // namespace th105
