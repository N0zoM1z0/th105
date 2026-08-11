#pragma once

namespace th105 {

struct Fighter;
struct String28;

// One-hop contracts reached directly from the BattleController island. These
// names are neutral reconstruction views; no original class ownership is
// claimed beyond the observed __thiscall receiver.
struct BattleControlBridgeView {
    int update_local_practice_battle_controls();
    int publish_synchronized_control_bits();
    int collect_battle_control_bits();
};

struct BattleSetupSlotsView {
    void save_battle_setup_slot(signed char slot, const void *setup);
    void load_battle_setup_slot(signed char slot, void *setup);
};

struct ScenarioBattleView {
    int advance_scenario_script_page();
    void initialize_character_story_script(
        signed char character_key,
        int argument0,
        int argument1);
    void parse_scenario_event_row(void *destination);
};

struct BattleMenuView {
    void *construct_battle_menu(unsigned selection);
};

struct BattleRenderStateView {
    int reset_battle_render_state_and_signal();
};

struct BattlePairContextView {
    int initialize_battle_fighter_pair();
};

unsigned char __stdcall dispatch_scenario_owned_string(String28 value);
unsigned int __thiscall update_fighter_scripted_input_state(Fighter *fighter);

} // namespace th105
