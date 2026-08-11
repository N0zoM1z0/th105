#pragma once

#include "engine/CriticalSectionWrapper.hpp"

namespace th105 {

struct Fighter;
struct BattlePhaseBlock;

struct SynchronizedInputState {
    unsigned char unknown_00[0x4c];
    int pending_4c;

    unsigned char is_input_available_427680();
};

struct BattleInputGate {
    unsigned char unknown_000[0x104];
    SynchronizedInputState *input_104;
    unsigned char unknown_108[0x1c];
    CriticalSectionWrapper lock_124;
    unsigned char published_140;
    unsigned char consumed_141;

    unsigned char poll_synchronized_input_4708b0();
};

typedef char BattleInputGate_input_offset_must_be_0x104[
    offsetof(BattleInputGate, input_104) == 0x104 ? 1 : -1];
typedef char BattleInputGate_lock_offset_must_be_0x124[
    offsetof(BattleInputGate, lock_124) == 0x124 ? 1 : -1];
typedef char BattleInputGate_consumed_offset_must_be_0x141[
    offsetof(BattleInputGate, consumed_141) == 0x141 ? 1 : -1];

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

    int run_battle_phase_and_info_callback();
};

struct BattlePhaseBlock {
    int run_458cd0();
};

extern BattlePhaseBlock *g_battle_phase_block;

typedef char BattleController_observed_prefix_must_be_0xa0[
    sizeof(BattleController) == 0xa0 ? 1 : -1];

} // namespace th105
