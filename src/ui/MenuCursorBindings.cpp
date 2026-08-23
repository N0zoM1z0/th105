#include "MenuCursor.hpp"
#include "../input/InputManager.hpp"

namespace th105 {

void MenuCursorState::bind_horizontal(
    CInputManager *input, int count, int page)
{
    if (input)
        input_counter = &input->hold.horizontal;
    else
        input_counter = 0;
    selection = 0;
    window_start = 0;
    item_count = count;
    page_size = page;
}

void MenuCursorState::bind_vertical(
    CInputManager *input, int count, int page)
{
    if (input)
        input_counter = &input->hold.vertical;
    else
        input_counter = 0;
    selection = 0;
    window_start = 0;
    item_count = count;
    page_size = page;
}

} // namespace th105
