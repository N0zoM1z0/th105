#pragma once

namespace th105 {

struct Fighter;

struct BattleInputGate {
    unsigned char poll_synchronized_input_4708b0();
};

struct BattleController {
    void *vtable_00;
    unsigned frame_counter_04;
    unsigned char unknown_08[0x04];
    Fighter *fighter_0c;
    Fighter *fighter_10;
    unsigned char unknown_14[0x70];
    int result_84;
    int phase_88;
    void *field_8c;
    unsigned char field_90;
    unsigned char transition_flag_91;
    unsigned char unknown_92[0x02];
    int field_94;
    int field_98;
    int field_9c;

    void initialize_or_transition_46fe80(int argument);
    int prepare_match_roster_470060();
    void *initialize_round_state_4701c0();
    int publish_fighter_terminal_effect_470300(Fighter *fighter);
    void *advance_round_resolution_470360();
    int run_active_simulation_frame_4704d0();
    int transition_battle_scene_470500(int argument);
    int reset_battle_round_470780();
    int dispatch_battle_state_frame_470940();
};

typedef char BattleController_observed_prefix_must_be_0xa0[
    sizeof(BattleController) == 0xa0 ? 1 : -1];

} // namespace th105
