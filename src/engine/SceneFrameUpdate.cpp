#include "input/InputCluster.hpp"
#include <list>
#include <vector>

namespace th105 {
extern InputStateTableStorage g_frame_input_state;
extern CInputManagerEx g_frame_player_input;
extern std::vector<CInputManagerEx> g_frame_result_inputs;
extern CInputManagerCluster g_combined_menu_input;
extern float g_scene_fade_value, g_scene_fade_delta;
void __cdecl update_profile_ui_selection();

void __cdecl update_scene_runtime()
{
    g_frame_input_state.update_input_state_table();
    g_frame_player_input.update_player_input_counters_from_raw();
    for (unsigned int i = 0; i < g_frame_result_inputs.size(); ++i)
        g_frame_result_inputs[i].update_player_input_counters_from_raw();
    g_combined_menu_input.update_player_input_counters_from_raw();
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
    update_profile_ui_selection();
}
}
