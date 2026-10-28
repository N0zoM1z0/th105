#include "ui/MenuConnectStateRuntime.hpp"
#include "input/Input.hpp"
#include <deque>
#include <string>
namespace th105 {
extern "C" const char connect_endpoint_edit_prompt[];
extern UiDesignObject *g_profile_message_main;
struct ConnectHistoryButtons { int horizontal, vertical, confirm, cancel; };
extern "C" ConnectHistoryButtons *__cdecl connect_history_buttons();
class ConnectEndpointSelectionView : public CMenuConnectStateRuntimeView {
public:
    void begin_endpoint_edit();
    int update_history_selection();
    void parse_endpoint(const std::string &);
};
void ConnectEndpointSelectionView::begin_endpoint_edit()
{
    show_profile_result(connect_endpoint_edit_prompt);
    CInputManager *input = reinterpret_cast<CInputManager *>(get_combined_menu_input());
    MenuCursorState &first = field<MenuCursorState>(0x3f8);
    if (input != 0) first.input_counter = &input->hold.horizontal;
    else first.input_counter = 0;
    first.selection = 0;
    first.window_start = 0;
    first.item_count = 17;
    first.page_size = 0;
    MenuCursorState &second = field<MenuCursorState>(0x40c);
    if (input != 0) second.input_counter = &input->hold.vertical;
    else second.input_counter = 0;
    second.selection = 0;
    second.window_start = 0;
    second.page_size = 0;
    second.item_count = 10;
    second.selection = 9 - field<unsigned short>(0x420) / 100 % 10;
}
int ConnectEndpointSelectionView::update_history_selection()
{
    if (field<MenuCursorState>(0x3e4).update()) {
        dispatch_indexed_event(0x27);
        return 0;
    }
    if (connect_history_buttons()->confirm == 1) {
        g_profile_message_main->enabled = false;
        dispatch_indexed_event(0x28);
        parse_endpoint(field<std::deque<std::string> >(0x3a4)[field<int>(0x3f0)]);
        return 1;
    }
    if (connect_history_buttons()->cancel != 1 && !is_menu_initial_press(1,0,0,0))
        return 0;
    g_profile_message_main->enabled = false;
    dispatch_indexed_event(0x29);
    return 2;
}
}
