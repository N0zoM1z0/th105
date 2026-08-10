#include "MenuCursor.hpp"

namespace th105 {

bool MenuCursorState::update()
{
    if (input_counter == 0)
        return false;

    int input = *input_counter;
    if (input != 1) {
        int repeat_remainder = input % 6;
        if (repeat_remainder != 0 || input <= 30) {
            if (input != -1 &&
                (repeat_remainder != 0 || input >= -30))
                return false;
            selection = (item_count - 1 + selection) % item_count;
        } else {
            selection = (selection + 1) % item_count;
        }
    } else {
        selection = (selection + 1) % item_count;
    }

    if (selection >= window_start + page_size)
        window_start = selection - page_size + 1;
    if (selection < window_start)
        window_start = selection;
    return true;
}

void MenuCursorState::move_page_backward()
{
    if (input_counter == 0 || page_size <= 0 || item_count < page_size)
        return;

    selection -= page_size;
    if (selection < 0) {
        if (window_start == 0) {
            selection += item_count;
            window_start = item_count - page_size;
        } else {
            selection = 0;
            window_start = 0;
        }
    } else {
        window_start -= page_size;
    }
    if (window_start < 0)
        window_start += item_count;
    if (selection >= window_start + page_size)
        window_start = selection - page_size + 1;
    if (selection < window_start)
        window_start = selection;
}

void MenuCursorState::move_page_forward()
{
    if (input_counter == 0 || page_size <= 0 || item_count < page_size)
        return;

    selection += page_size;
    window_start += page_size;
    if (selection >= item_count) {
        if (window_start < item_count)
            selection = item_count - 1;
        else {
            selection -= window_start;
            window_start = 0;
        }
    }
    if (window_start >= item_count)
        window_start -= item_count;
    if (selection >= window_start + page_size)
        window_start = selection - page_size + 1;
    if (selection < window_start)
        window_start = selection;
}

} // namespace th105
