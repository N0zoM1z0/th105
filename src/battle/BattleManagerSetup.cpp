#include "BattleManagerVirtuals.hpp"
#include "BattleController.hpp"
#include "GameMode.hpp"

namespace th105 {

struct FighterPhaseContextManagerSetupView {
    void initialize_slot_464270(int slot, MatchSetup::Side *side, int value);
};

struct BattleObjectManagerSetupView {
    void reset_battle_render_state_and_signal_465f70();
};

struct BattleAudioManagerSetupView {
    void set_stage_music_433860(int stage, int value);
};

extern FighterPhaseContextManagerSetupView *g_fighter_phase_context;
extern BattleObjectManagerSetupView *g_battle_object_manager;
extern unsigned char g_round_counter;
extern "C" const char arcade_bgm_path_format[];
extern "C" void __cdecl load_bgm_source(const char *path);
extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);
void __cdecl mt19937_seed_u32(unsigned seed);
int __cdecl selector_random_roll(int limit);

void CBattleManager::prepare_battle_setup_472110(MatchSetup *setup)
{
    char path[260];

    if (get_session_setup_option() == 2) {
        get_player2_input()->load_battle_setup_slot(0, setup);
    } else if (get_session_setup_option() == 1) {
        get_player2_input()->configure_session_input(
            1, static_cast<int>(get_game_mode()));
        get_player2_input()->save_battle_setup_slot(0, setup);
    }

    *reinterpret_cast<int *>(0x006fa894) = setup->match_identifier_00;
    mt19937_seed_u32(setup->seed_48);
    g_battle_object_manager->reset_battle_render_state_and_signal_465f70();
    reinterpret_cast<BattleAudioManagerSetupView *>(&frame_counter_04)
        ->set_stage_music_433860(setup->stage_04, 0);
    wsprintfA(path, arcade_bgm_path_format, setup->bgm_id_05);
    load_bgm_source(path);

    g_fighter_phase_context->initialize_slot_464270(
        0, &setup->sides_08[0], 0);
    g_fighter_phase_context->initialize_slot_464270(
        1, &setup->sides_08[1], 0);
    reinterpret_cast<BattleController *>(this)
        ->initialize_battle_fighter_pair_46a490();
    transition_state_5b0() = 0;
    g_round_counter = static_cast<unsigned char>(selector_random_roll(4) + 3);
}

} // namespace th105
