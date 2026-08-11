#include "BattleController.hpp"

#include "Collision.hpp"
#include "GameMode.hpp"

namespace th105 {

typedef void (__thiscall *FighterVslot44)(Fighter *fighter);

struct FighterPhaseContextSetupView {
    void begin_slot_4641f0(int slot);
    void configure_slot_463290(int slot, int value);
    Fighter *get_slot_character_463270(unsigned slot);
    unsigned char is_slot_active_463280(unsigned slot);
    void finish_slot_464240(int slot);
    void initialize_slot_464270(
        int slot,
        MatchSetup::Side *setup_side,
        int value);
};

struct GlobalBattleSetupStateView {
    void copy_roster_metadata_425cb0(
        int *first_a,
        int *first_b,
        int *second_a,
        int *second_b);
    void update_second_425f10();
};

struct BattleRendererSetupView {
    void refresh_roster_state_471470();
};

struct BattleObjectSetupManagerView {
    void reset_battle_render_state_and_signal_465f70();
};

struct BattleAudioSetupView {
    void set_stage_music_433860(int stage, int unused);
};

void __cdecl mt19937_seed_u32(unsigned seed);
void __cdecl set_session_setup_option(unsigned option);
void *__cdecl get_selected_input(unsigned side);
unsigned char __cdecl get_stage_for_character(int character_key);
unsigned char __cdecl get_bgm_for_character(int character_key);
extern "C" void __cdecl play_bgm(const char *path);
extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer,
    const char *format,
    ...);

inline FighterPhaseContextSetupView *fighter_phase_context_for_setup()
{
    return *reinterpret_cast<FighterPhaseContextSetupView **>(0x006e623c);
}

inline GlobalBattleSetupStateView *global_battle_setup_state()
{
    return reinterpret_cast<GlobalBattleSetupStateView *>(0x006e6260);
}

inline EffectSink *effect_sink_for_setup()
{
    return *reinterpret_cast<EffectSink **>(0x006e6250);
}

inline BattleObjectSetupManagerView *battle_object_setup_manager()
{
    return *reinterpret_cast<BattleObjectSetupManagerView **>(0x006e6240);
}

inline signed char current_phase_setup_slot()
{
    return *(reinterpret_cast<signed char *>(g_battle_phase_block) + 0x594);
}

void BattleController::prepare_match_roster_470060()
{
    if (get_session_setup_option() == 2) {
        get_player2_input()->load_battle_setup_slot(
            current_phase_setup_slot(), get_match_setup());
    } else if (get_session_setup_option() == 1) {
        get_player2_input()->save_battle_setup_slot(
            current_phase_setup_slot(), get_match_setup());
    }

    effect_sink_for_setup()->publish_roster_fighter_20(fighter_10);
    fighter_phase_context_for_setup()->begin_slot_4641f0(1);
    fighter_phase_context_for_setup()->configure_slot_463290(1, 2);
    fighter_10 =
        fighter_phase_context_for_setup()->get_slot_character_463270(1);

    if (!fighter_phase_context_for_setup()->is_slot_active_463280(1)) {
        fighter_10->reset_for_roster_45e040(fighter_0c);
        reinterpret_cast<FighterVslot44>(
            (*reinterpret_cast<void ***>(fighter_10))[17])(fighter_10);
        fighter_phase_context_for_setup()->finish_slot_464240(1);
    }

    fighter_0c->reset_for_roster_45e040(fighter_10);
    global_battle_setup_state()->copy_roster_metadata_425cb0(
        reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(fighter_0c) + 0xec),
        reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(fighter_0c) + 0xf0),
        reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(fighter_10) + 0xec),
        reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(fighter_10) + 0xf0));
    frame_counter_04 = 0;
    *reinterpret_cast<int *>(unknown_08) = 0;
    fighter_0c->value_174 = fighter_0c->maximum_176;
    reinterpret_cast<BattleRendererSetupView *>(post_sequence_context_8c)
        ->refresh_roster_state_471470();
    g_battle_phase_block->advance_scenario_script_page_458d10();
    dispatch_round_phase_34(0);
}

void BattleController::initialize_or_transition_46fe80(MatchSetup *setup)
{
    char path[260];

    if (static_cast<int>(get_game_mode()) == 0 &&
        get_session_setup_option() == 0) {
        set_session_setup_option(1);
    }

    if (get_session_setup_option() == 2) {
        get_player2_input()->load_battle_setup_slot(0, setup);
    }

    post_sequence_context_8c = reinterpret_cast<PostSequenceContextView *>(
        *reinterpret_cast<void **>(0x006e6248));
    if (g_battle_phase_block != 0) {
        g_battle_phase_block->initialize_character_story_script_458f10(
            setup->sides_08[0].character_key_00,
            get_selected_input(0),
            setup->match_identifier_00);
        g_battle_phase_block->parse_scenario_event_row_4591d0(
            &setup->sides_08[1]);
    }

    if (get_session_setup_option() == 1) {
        signed char character_key = *(
            reinterpret_cast<signed char *>(g_battle_phase_block) + 0x595);
        get_player2_input()->configure_session_input(
            character_key, static_cast<int>(get_game_mode()));
        get_player2_input()->save_battle_setup_slot(0, setup);
    }

    mt19937_seed_u32(setup->seed_48);
    int match_identifier = setup->match_identifier_00;
    BattleObjectSetupManagerView *object_manager =
        battle_object_setup_manager();
    *reinterpret_cast<int *>(0x006e4e34) = match_identifier;
    object_manager->reset_battle_render_state_and_signal_465f70();
    fighter_phase_context_for_setup()->initialize_slot_464270(
        0, &setup->sides_08[0], 0);
    fighter_phase_context_for_setup()->initialize_slot_464270(
        1, &setup->sides_08[1], 0);
    initialize_battle_fighter_pair_46a490();

    if (g_battle_phase_block != 0) {
        g_battle_phase_block->advance_scenario_script_page_458d10();
    } else {
        if (setup->sides_08[0].character_key_00 == 6) {
            setup->stage_04 = 16;
        } else {
            setup->stage_04 = get_stage_for_character(
                setup->sides_08[1].character_key_00);
        }
        setup->bgm_id_05 = get_bgm_for_character(
            setup->sides_08[1].character_key_00);
        reinterpret_cast<BattleAudioSetupView *>(&frame_counter_04)
            ->set_stage_music_433860(setup->stage_04, 0);
        wsprintfA(
            path,
            reinterpret_cast<const char *>(0x006ad598),
            setup->bgm_id_05);
        play_bgm(path);
        dispatch_round_phase_34(1);
    }

    *reinterpret_cast<unsigned char *>(0x006e4e2e) = 0;
    phase_a0 = 3;
    transition_a4 = 0;
    fighter_0c->terminal_delay_4e8 = 3;
    global_battle_setup_state()->update_second_425f10();
}

} // namespace th105
