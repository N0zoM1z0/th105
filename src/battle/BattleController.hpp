#pragma once

#include "engine/CriticalSectionWrapper.hpp"

namespace th105 {

struct Fighter;
struct BattlePhaseBlock;
struct PostSequenceContextView;
struct MatchSetup;
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
    void update_local_practice_battle_controls_427190();
    void publish_synchronized_control_bits_427ac0();
    void save_battle_setup_slot(signed char slot, MatchSetup *setup);
    void load_battle_setup_slot(signed char slot, MatchSetup *setup);
    void configure_session_input(signed char character_key, int game_mode);
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
    virtual int unused_vslot_2c();
    virtual int unused_vslot_30();
    virtual void dispatch_round_phase_34(int phase);

    unsigned frame_counter_04;
    unsigned char unknown_08[0x04];
    Fighter *fighter_0c;
    Fighter *fighter_10;
    unsigned char unknown_14[0x70];
    int result_84;
    int phase_88;
    PostSequenceContextView *post_sequence_context_8c;
    unsigned char field_90;
    unsigned char transition_flag_91;
    unsigned char unknown_92[0x02];
    int outcome_band_94;
    int tally_second_98;
    int tally_third_9c;
    int phase_a0;
    unsigned char transition_a4;
    unsigned char unknown_a5[3];

    void initialize_or_transition_46fe80(MatchSetup *setup);
    void prepare_match_roster_470060();
    void initialize_round_state_4701c0();
    void publish_fighter_terminal_effect_470300(Fighter *fighter);
    void advance_round_resolution_470360();
    int run_active_simulation_frame_4704d0();
    int transition_battle_scene_470500(int argument);
    int reset_battle_round_470780();
    int dispatch_battle_state_frame_470940();
    void initialize_battle_fighter_pair_46a490();

    int run_battle_phase_and_info_callback();
};

struct BattlePhaseBlock {
    int run_458cd0();
    void advance_scenario_script_page_458d10();
    void initialize_character_story_script_458f10(
        int character_key,
        void *selected_input,
        int match_identifier);
    void parse_scenario_event_row_4591d0(void *destination);
};

extern BattlePhaseBlock *g_battle_phase_block;

typedef char BattleController_observed_prefix_must_be_0xa8[
    sizeof(BattleController) == 0xa8 ? 1 : -1];
typedef char SceneExitTransition_size_must_be_0x78[
    sizeof(SceneExitTransition) == 0x78 ? 1 : -1];

} // namespace th105
