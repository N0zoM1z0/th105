#include "battle/GameMode.hpp"

#include <deque>

namespace th105 {

struct MatchRuntimeStateView {
    unsigned char flag_4c;
    unsigned char flag_4d;
    unsigned char reserved_4e[2];
    int deck_index_50;
    unsigned char flag_54;
    unsigned char flag_55;
    unsigned char flag_56;
    unsigned char reserved_57;
    std::deque<unsigned short> deck_58;
    void *current_deck_6c;
    int field_70;
    unsigned char flag_74;
    unsigned char flag_75;
    unsigned char flag_76;
    unsigned char reserved_77;
    std::deque<unsigned short> deck_78;
    void *alternate_deck_8c;
    unsigned random_90;
};

struct MatchPlayerSlotView {
    unsigned char reserved_000[0x138];
    unsigned char selected_deck_state_138[0x204];

    std::deque<unsigned short> *copy_deck(
        std::deque<unsigned short> *output, int index);
    int load_character_deck(
        std::deque<unsigned short> *output, int character);
    void select_deck(signed char source);
};

typedef char MatchPlayerSlotView_size_must_be_0x33c[
    sizeof(MatchPlayerSlotView) == 0x33c ? 1 : -1];

struct MatchNetworkDeckView {
    unsigned char reserved_000[0x1f0];
    unsigned char deck_1f0[8];
    unsigned char deck_1f8[8];
    int *selected_source_200;
    unsigned char reserved_204[4];
    int selected_value_208;
};

union MatchSelectedInputSourcesView {
    unsigned short word;
    struct {
        signed char first;
        signed char second;
    } bytes;
};

extern GameMode g_game_mode;
extern MatchSetup g_match_setup;
extern MatchRuntimeStateView g_scenario_match_runtime;
extern MatchPlayerSlotView g_player_slot_records[2];
extern MatchSelectedInputSourcesView g_selected_input_sources_view;
extern MatchNetworkDeckView *g_network_session;
extern int g_match_identifier_source;

unsigned __cdecl mt19937_next_u32();

unsigned __cdecl prepare_match_runtime_by_mode()
{
    const GameMode mode = g_game_mode;
    const unsigned char one = 1;

    g_scenario_match_runtime.flag_54 = 0;
    g_scenario_match_runtime.flag_74 = one;
    g_scenario_match_runtime.flag_56 = one;
    g_scenario_match_runtime.flag_76 =
        mode == GAME_MODE_PRACTICE ? 3 : 1;

    const int deck_index = g_scenario_match_runtime.deck_index_50;
    if (deck_index == g_scenario_match_runtime.field_70 &&
        g_scenario_match_runtime.flag_55 == g_scenario_match_runtime.flag_75) {
        g_scenario_match_runtime.flag_75 =
            static_cast<unsigned char>(
                one - g_scenario_match_runtime.flag_55);
    }

    switch (mode) {
    case GAME_MODE_VS_PLAYER:
    case GAME_MODE_PRACTICE:
        g_player_slot_records[0].copy_deck(
            &g_scenario_match_runtime.deck_58, deck_index);
        g_player_slot_records[1].load_character_deck(
            &g_scenario_match_runtime.deck_78,
            g_scenario_match_runtime.field_70);
        g_player_slot_records[0].select_deck(
            g_selected_input_sources_view.bytes.first);
        g_scenario_match_runtime.current_deck_6c =
            &g_player_slot_records[0].selected_deck_state_138;
        g_scenario_match_runtime.alternate_deck_8c = 0;
        break;

    case GAME_MODE_VS_COM:
        g_player_slot_records[0].copy_deck(
            &g_scenario_match_runtime.deck_58, deck_index);
        g_player_slot_records[0].select_deck(
            g_selected_input_sources_view.bytes.first);
        g_scenario_match_runtime.current_deck_6c =
            &g_player_slot_records[0].selected_deck_state_138;
        g_scenario_match_runtime.alternate_deck_8c = 0;
        break;

    case GAME_MODE_NETWORK_CLIENT:
        g_player_slot_records[0].copy_deck(
            &g_scenario_match_runtime.deck_58, deck_index);
        g_player_slot_records[0].select_deck(
            g_selected_input_sources_view.bytes.first);
        g_network_session->selected_value_208 =
            *g_network_session->selected_source_200;
        g_scenario_match_runtime.current_deck_6c =
            g_network_session->deck_1f0;
        g_scenario_match_runtime.alternate_deck_8c =
            g_network_session->deck_1f8;
        break;

    case GAME_MODE_NETWORK_WATCH:
        g_player_slot_records[0].select_deck(
            g_selected_input_sources_view.bytes.first);
        g_network_session->selected_value_208 =
            *g_network_session->selected_source_200;
        g_scenario_match_runtime.current_deck_6c =
            g_network_session->deck_1f0;
        g_scenario_match_runtime.alternate_deck_8c =
            g_network_session->deck_1f8;
        break;

    case GAME_MODE_NETWORK_SERVER:
        g_player_slot_records[0].copy_deck(
            &g_scenario_match_runtime.deck_58, deck_index);
        g_player_slot_records[1].copy_deck(
            &g_scenario_match_runtime.deck_78,
            g_scenario_match_runtime.field_70);
        g_player_slot_records[0].select_deck(
            g_selected_input_sources_view.bytes.first);
        g_scenario_match_runtime.current_deck_6c =
            &g_player_slot_records[0].selected_deck_state_138;
        if ((unsigned char)g_selected_input_sources_view.word == 0xff &&
            (unsigned char)(g_selected_input_sources_view.word >> 8) == 0xfe) {
            g_player_slot_records[1].select_deck(-1);
        } else {
            g_player_slot_records[1].select_deck(
                static_cast<signed char>(
                    g_selected_input_sources_view.word >> 8));
        }
        g_scenario_match_runtime.alternate_deck_8c =
            &g_player_slot_records[1].selected_deck_state_138;
        break;

    default:
        break;
    }

    g_scenario_match_runtime.random_90 = mt19937_next_u32();
    g_match_setup.match_identifier_00 = g_match_identifier_source;
    return g_scenario_match_runtime.random_90;
}

} // namespace th105
