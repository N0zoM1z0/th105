// JP1.06a 0x4400D0: per-frame profile UI selection fade and menu-stack update.
#include "input/InputCluster.hpp"
#include <list>

namespace th105 {
struct UiSelectionMenuFrameView {
    virtual ~UiSelectionMenuFrameView();
    virtual void update();
    virtual bool is_ready();
};
extern unsigned g_ui_selection_state;
extern unsigned char g_ui_selection_snapshot, g_ui_selection_fade;
extern unsigned char g_ui_selection_active;
extern int g_scene_mode;
extern std::list<UiSelectionMenuFrameView *> g_ui_selection_menu_stack;
extern "C" CInputManager *g_active_menu_input;
extern "C" bool __cdecl is_menu_initial_press(int, int, int, int);
void __cdecl pop_profile_ui_menu_43ff40();

void __cdecl update_profile_ui_selection()
{
    if (g_ui_selection_state - g_ui_selection_snapshot != 0) {
        if (g_ui_selection_fade < 255)
            g_ui_selection_fade += 15;
    } else if (g_ui_selection_fade != 0) {
        g_ui_selection_fade -= 15;
    }
    if (g_ui_selection_state != 0) {
        if (g_ui_selection_active) {
            if (!g_active_menu_input->hold.buttons[0] && !g_active_menu_input->hold.buttons[1] &&
                !is_menu_initial_press(1, 0, 0, 0)) {
                pop_profile_ui_menu_43ff40();
                g_ui_selection_active = 0;
            }
        } else if (g_ui_selection_snapshot < g_ui_selection_state && g_scene_mode == 22) {
            if (!g_ui_selection_menu_stack.back()->is_ready())
                g_ui_selection_active = 1;
        }
    }
}
}
