#include "ui/MenuPractice.hpp"
#include "input/InputManager.hpp"
extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned int);
extern "C" bool __cdecl is_menu_initial_press(int, int, int, int);
namespace th105 {
bool CMenuPractice::update()
{
    if (owner_284->menu_state_084)
        return true;
    guide_008.update();
    HoldCounters *input = &g_active_menu_input->hold;
    if (cursors_25c[0].update()) {
        dispatch_indexed_event(39);
        configure_subcursor(cursors_25c[0].selection);
    } else if (cursors_25c[1].update() && !input->vertical) {
        dispatch_indexed_event(39);
        int category = cursors_25c[0].selection;
        if (category >= 1 && category <= 7)
            settings_004->category_value_00c[category] = cursors_25c[1].selection;
    } else if (input->buttons[0] == 1) {
        dispatch_indexed_event(40);
        int category = cursors_25c[0].selection;
        if (category == 8)
            owner_284->menu_state_084 = 1;
        else if (category == 9)
            owner_284->menu_state_084 = 2;
        else
            return false;
    } else if (input->buttons[1] == 1 || is_menu_initial_press(1, 0, 0, 0)) {
        dispatch_indexed_event(41);
        return false;
    }
    for (int category = 2; category < 8; ++category) {
        std::vector<UiDesignObject *> &group = groups_1bc[category];
        for (unsigned int i = 0; i < group.size(); ++i) {
            if (i == static_cast<unsigned int>(settings_004->category_value_00c[category]))
                group[i]->set_color(0xffffffffu);
            else
                group[i]->set_color(0xff808080u);
        }
    }
    return true;
}
}
