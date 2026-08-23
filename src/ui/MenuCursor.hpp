#pragma once

namespace th105 {

struct CInputManager;

struct MenuCursorState {
    int item_count;
    int page_size;
    int *input_counter;
    int selection;
    int window_start;

    bool update();
    void bind_horizontal(CInputManager *input, int count, int page);
    void bind_vertical(CInputManager *input, int count, int page);
    void move_page_backward();
    void move_page_forward();
};

typedef char MenuCursorState_size_must_be_0x14[
    sizeof(MenuCursorState) == 0x14 ? 1 : -1];

} // namespace th105
