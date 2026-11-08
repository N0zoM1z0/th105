#include "input/InputCluster.hpp"
#include <list>
#include <vector>

namespace th105 {
struct UiSelectionMenuFrameView {
    virtual ~UiSelectionMenuFrameView();
    virtual void update();
    virtual bool is_ready();
};
extern InputStateTableStorage g_frame_input_state;
extern CInputManagerEx g_frame_player_input;
extern std::vector<CInputManagerEx> g_frame_result_inputs;
extern CInputManagerCluster g_combined_menu_input;
extern float g_scene_fade_value, g_scene_fade_delta;
extern unsigned g_ui_selection_state;
extern unsigned char g_ui_selection_snapshot, g_ui_selection_fade;
extern unsigned char g_ui_selection_active;
extern int g_scene_mode;
extern std::list<UiSelectionMenuFrameView *> g_ui_selection_menu_stack;
extern "C" CInputManager *g_active_menu_input;
extern "C" bool __cdecl is_menu_initial_press(int, int, int, int);
void __cdecl pop_profile_ui_menu_43ff40();

// Full source hypothesis includes the UI tail physically shared at 0x4400D0.
void __cdecl update_scene_runtime()
{
    g_frame_input_state.update_input_state_table();
    g_frame_player_input.update_player_input_counters_from_raw();
    for (unsigned int i = 0; i < g_frame_result_inputs.size(); ++i)
        g_frame_result_inputs[i].update_player_input_counters_from_raw();
    g_combined_menu_input.merge_menu_input_sources();
    if (g_scene_fade_delta != 0.0f) {
        g_scene_fade_value += g_scene_fade_delta;
        if (g_scene_fade_value > 1.0f) {
            g_scene_fade_value = 1.0f;
            g_scene_fade_delta = 0.0f;
        } else if (g_scene_fade_value < 0.0f) {
            g_scene_fade_value = 0.0f;
            g_scene_fade_delta = 0.0f;
        }
    }
    if (g_ui_selection_state != g_ui_selection_snapshot) {
        if (g_ui_selection_fade != 255)
            g_ui_selection_fade += 15;
    } else if (g_ui_selection_fade != 0) {
        g_ui_selection_fade -= 15;
    }
    if (g_ui_selection_state != 0) {
        if (g_ui_selection_active) {
            if (!g_active_menu_input->hold.vertical && !g_active_menu_input->hold.buttons[0] &&
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
