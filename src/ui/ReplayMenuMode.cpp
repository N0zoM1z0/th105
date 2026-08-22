#include "ReplayMenu.hpp"
#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned index);

namespace th105 {

unsigned char CMenuReplay::update_mode_state()
{
    int *axis = &g_active_menu_input->hold.horizontal;
    if (mode_cursor_fc.update())
        dispatch_indexed_event(0x27);

    if (axis[2] == 1) {
        dispatch_indexed_event(0x28);
        switch (mode_cursor_fc.selection) {
        case 0:
            if (replay_list_08.item_count()) {
                state_04 = 1;
                items_f0[1]->set_color(0xff808080u);
                items_f0[2]->set_color(0xff808080u);
            }
            break;
        case 1:
            if (replay_list_08.item_count()) {
                state_04 = 2;
                state_05 = 0;
                items_f0[0]->set_color(0xff808080u);
                items_f0[2]->set_color(0xff808080u);
            }
            break;
        case 2:
            return 0;
        }
    } else if (axis[3] == 1) {
        dispatch_indexed_event(0x29);
        return 0;
    }
    return 1;
}

} // namespace th105
