#include "SelectScenario.hpp"
#include "UiSelectionState.hpp"
#include "MenuSelect.hpp"

#include "../input/InputSelection.hpp"

extern "C" void __cdecl play_bgm(const char *path);
extern "C" const char title_bgm_path[];
extern "C" float __cdecl lookup_orientation_cosine(int angle);
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);
extern "C" void __cdecl prepare_scenario_match(int player);
extern "C" void __cdecl start_scene_fade(int duration, int color);
extern "C" void __cdecl install_menu_object(void *object);
extern "C" void __cdecl _invalid_parameter_noinfo();
extern "C" int g_scene_mode;

namespace th105 {

extern MatchSetup *get_match_setup();
extern GameConfig *get_game_config();

int CSelectScenario::update()
{
    if (has_ui_selection_state_changed())
        return g_scene_mode == 2 ? 2 : 16;

    if (input_0c != 0 && input_0c->hold.buttons[2] == 1) {
        dispatch_indexed_event(0x28);
        install_menu_object(new CMenuSelect);
        return 16;
    }

    if (is_menu_initial_press(1, 0, 0, 0))
        return 2;
    return update_selection();
}

void CSelectScenario::on_scene_enter(int previous_scene)
{
    match_setup_08 = get_match_setup();
    if (previous_scene != 2)
        play_bgm(title_bgm_path);

    input_0c = reinterpret_cast<CInputManager *>(get_selected_input(0));

    player_cursor_2bc.item_count = scenario_count_3c;
    player_cursor_2bc.input_counter =
        input_0c == 0 ? 0 : &input_0c->hold.vertical;
    player_cursor_2bc.selection = 0;
    player_cursor_2bc.window_start = 0;
    player_cursor_2bc.page_size = 0;

    scenario_cursor_2d0.item_count = 4;
    scenario_cursor_2d0.input_counter =
        input_0c == 0 ? 0 : &input_0c->hold.horizontal;
    scenario_cursor_2d0.selection = 0;
    scenario_cursor_2d0.window_start = 0;
    scenario_cursor_2d0.page_size = 0;

    int index = 0;
    while (index < scenario_count_3c) {
        if (scenario_ids_2c.begin == 0 ||
            static_cast<unsigned int>(
                scenario_ids_2c.end - scenario_ids_2c.begin) <=
                static_cast<unsigned int>(index))
            _invalid_parameter_noinfo();
        if (match_setup_08->scenario_id == scenario_ids_2c.begin[index]) {
            player_cursor_2bc.selection = index;
            break;
        }
        ++index;
    }

    match_setup_08->game_type = get_game_config()->default_game_type;
    design_600[match_setup_08->game_type]->enabled = true;
    scenario_cursor_2d0.selection = match_setup_08->game_type;
    apply_scenario(match_setup_08->scenario_id);
}

int CSelectScenario::update_selection()
{
    int one = 1;
    guide_344.update();

    if (timer_338 != 0) {
        --timer_338;
        transition_33c = static_cast<float>(
            (1.0 - lookup_orientation_cosine(timer_338 * 18)) *
            0.5 * preview_alpha_340);
    }

    if (scenario_cursor_2d0.update()) {
        dispatch_indexed_event(0x27);
        match_setup_08->game_type = scenario_cursor_2d0.selection;
        design_600[0]->enabled = match_setup_08->game_type == 0;
        design_600[1]->enabled = match_setup_08->game_type == one;
        design_600[2]->enabled = match_setup_08->game_type == 2;
        design_600[3]->enabled = match_setup_08->game_type == 3;
    }

    if (player_cursor_2bc.update()) {
        dispatch_indexed_event(0x27);
        unsigned int index = player_cursor_2bc.selection;
        if (scenario_ids_2c.begin == 0 ||
            static_cast<unsigned int>(
                scenario_ids_2c.end - scenario_ids_2c.begin) <= index)
            _invalid_parameter_noinfo();
        match_setup_08->scenario_id = scenario_ids_2c.begin[index];
        apply_scenario(match_setup_08->scenario_id);
        timer_338 = 10;
        float transition;
        if (input_0c->hold.vertical < one)
            transition = transition_33c - 1.0;
        else
            transition = transition_33c + 1.0;
        transition_33c = transition;
        preview_alpha_340 = transition;
        return 16;
    }

    if (input_0c->hold.buttons[0] == one) {
        dispatch_indexed_event(0x28);
        prepare_scenario_match(0);
        start_scene_fade(1000, 0);
        return 6;
    }
    if (input_0c->hold.buttons[1] == one) {
        dispatch_indexed_event(0x29);
        return 2;
    }
    return 16;
}

} // namespace th105
