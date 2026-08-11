#pragma once

#include "engine/CriticalSectionWrapper.hpp"

namespace th105 {

struct Fighter;
struct BattlePhaseBlock;
struct BattleInputGate;
struct BattleController;

struct SceneExitTransition {
    unsigned char storage_00[0x78];

    explicit SceneExitTransition(BattleController *controller);
};

bool __cdecl has_ui_selection_state_changed();
bool __cdecl is_menu_initial_press(
    int index,
    int unused_1,
    int unused_2,
    int unused_3);
unsigned __cdecl get_session_setup_option();
BattleInputGate *__cdecl get_player2_input();
void __cdecl dispatch_indexed_event(unsigned index);
void __cdecl install_menu_object(void *object);

struct SynchronizedInputState {
    unsigned char unknown_00[0x4c];
    int pending_4c;

    unsigned char is_input_available_427680();
};

struct FighterControlInput {
    unsigned char unknown_00[0x62];
    unsigned short control_low_bits_062;
};

struct BattleInputGate {
    FighterControlInput *first_control_input_000;
    FighterControlInput *second_control_input_004;
    unsigned char unknown_008[0x60];
    unsigned short first_control_low_bits_068;
    unsigned char unknown_06a[0x66];
    unsigned short second_control_low_bits_0d0;
    unsigned char unknown_0d2[0x1e];
    unsigned char publish_flags_0f0;
    unsigned char unknown_0f1[0x13];
    SynchronizedInputState *input_104;
    unsigned char unknown_108[0x1c];
    CriticalSectionWrapper lock_124;
    unsigned char published_140;
    unsigned char consumed_141;

    unsigned char poll_synchronized_input_4708b0();
    void queue_control_word(unsigned short packed_control_bits);
    void collect_battle_control_bits_42a560();
};

typedef char BattleInputGate_input_offset_must_be_0x104[
    offsetof(BattleInputGate, input_104) == 0x104 ? 1 : -1];
typedef char BattleInputGate_lock_offset_must_be_0x124[
    offsetof(BattleInputGate, lock_124) == 0x124 ? 1 : -1];
typedef char BattleInputGate_consumed_offset_must_be_0x141[
    offsetof(BattleInputGate, consumed_141) == 0x141 ? 1 : -1];
typedef char FighterControlInput_size_must_be_0x64[
    sizeof(FighterControlInput) == 0x64 ? 1 : -1];

struct BattleController {
    virtual int unused_vslot_00();
    virtual int unused_vslot_04();
    virtual int unused_vslot_08();
    virtual int unused_vslot_0c();
    virtual int run_phase_0_470940();
    virtual int run_phase_1_470940();
    virtual int run_phase_2_470940();
    virtual int run_phase_3_470940();
    virtual int run_phase_4_470940();
    virtual int run_phase_5_470940();
    virtual int run_phase_6_470940();

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
typedef char SceneExitTransition_size_must_be_0x78[
    sizeof(SceneExitTransition) == 0x78 ? 1 : -1];

} // namespace th105
