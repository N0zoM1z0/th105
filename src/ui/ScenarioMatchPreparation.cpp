#include <stddef.h>

namespace th105 {

struct ScenarioDeckStorage20 {
    unsigned char bytes_00[0x14];
};

struct ScenarioMatchRuntimeState {
    unsigned char flag_4c;
    unsigned char flag_4d;
    unsigned char unknown_4e[2];
    int deck_index_50;
    unsigned char flag_54;
    unsigned char flag_55;
    unsigned char flag_56;
    unsigned char unknown_57;
    ScenarioDeckStorage20 deck_58;
    void *current_deck_6c;
    int field_70;
    unsigned char flag_74;
    unsigned char flag_75;
    unsigned char flag_76;
    unsigned char unknown_77[0x15];
    int field_8c;
    unsigned random_90;
    unsigned char flag_94;
    unsigned char flag_95;
    unsigned char flag_96;
};

struct PlayerSlotRecordScenarioView {
    ScenarioDeckStorage20 *copy_deck(
        ScenarioDeckStorage20 *output, int index);
    void select_deck(unsigned char source);
};

extern ScenarioMatchRuntimeState g_scenario_match_runtime;
extern unsigned char g_scenario_deck_storage;
extern unsigned char g_player_slot_records[];
extern signed char g_selected_input_sources[];
unsigned __cdecl mt19937_next_u32();

void __cdecl prepare_scenario_match(int player)
{
    (void)player;
    unsigned char one = 1;
    g_scenario_match_runtime.flag_74 = one;
    g_scenario_match_runtime.flag_56 = one;

    int zero = 0;
    PlayerSlotRecordScenarioView *record =
        reinterpret_cast<PlayerSlotRecordScenarioView *>(g_player_slot_records);
    g_scenario_match_runtime.flag_54 = static_cast<unsigned char>(zero);
    g_scenario_match_runtime.flag_76 = 2;
    g_scenario_match_runtime.flag_55 = static_cast<unsigned char>(zero);
    g_scenario_match_runtime.flag_75 = static_cast<unsigned char>(zero);
    record->copy_deck(
        &g_scenario_match_runtime.deck_58,
        g_scenario_match_runtime.deck_index_50);

    record->select_deck(
        static_cast<unsigned char>(g_selected_input_sources[0]));
    g_scenario_match_runtime.current_deck_6c = &g_scenario_deck_storage;
    g_scenario_match_runtime.field_8c = zero;
    g_scenario_match_runtime.random_90 = mt19937_next_u32();
    g_scenario_match_runtime.flag_4c = static_cast<unsigned char>(zero);
    g_scenario_match_runtime.flag_4d = static_cast<unsigned char>(zero);
}

} // namespace th105
