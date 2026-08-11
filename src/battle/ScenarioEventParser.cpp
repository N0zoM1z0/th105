#include "assets/CsvReader.hpp"
#include "assets/String28.hpp"
#include "battle/BattleController.hpp"
#include "battle/SpellData.hpp"

#include <list>

namespace th105 {

int __cdecl resolve_scenario_event_name(String28 value);

struct ScenarioEventDestinationView {
    int event_code_00;
    unsigned unknown_04;
    ShortDeque8 selected_values_08;
};

struct ScenarioEventParserView {
    unsigned char unknown_000[0x38];
    CsvReader reader_038;
    unsigned char unknown_068[0x528];
    int selected_column_590;
    unsigned unknown_594;
    std::list<int> source_values_598;
    std::list<int> destination_values_5a4;
};

typedef char ScenarioEventParserView_selected_column_offset_must_be_0x590[
    offsetof(ScenarioEventParserView, selected_column_590) == 0x590 ? 1 : -1];
typedef char ScenarioEventParserView_source_values_offset_must_be_0x598[
    offsetof(ScenarioEventParserView, source_values_598) == 0x598 ? 1 : -1];
typedef char ScenarioEventParserView_destination_values_offset_must_be_0x5a4[
    offsetof(ScenarioEventParserView, destination_values_5a4) == 0x5a4 ? 1 : -1];

void BattlePhaseBlock::parse_scenario_event_row_4591d0(void *destination)
{
    ScenarioEventParserView *state =
        reinterpret_cast<ScenarioEventParserView *>(this);
    ScenarioEventDestinationView *output =
        static_cast<ScenarioEventDestinationView *>(destination);

    state->reader_038.next_int();
    String28 event_name;
    state->reader_038.next_string(&event_name);
    output->event_code_00 = resolve_scenario_event_name(
        String28(event_name, 0, static_cast<unsigned int>(-1)));
    int row_count = state->reader_038.next_int();
    state->reader_038.advance_row();

    output->selected_values_08.clear_storage();
    state->destination_values_5a4.clear();
    state->source_values_598.clear();

    for (int row = 0; row < row_count; ++row) {
        int selected_value = 0;
        for (int column = 0; column < 4; ++column) {
            int value = state->reader_038.next_int();
            if (column == state->selected_column_590) {
                selected_value = value;
            }
        }

        short selected_short = static_cast<unsigned short>(selected_value);
        output->selected_values_08.push_back(&selected_short);
        state->source_values_598.push_back(state->reader_038.next_int());
        state->reader_038.advance_row();
    }

    if (&state->destination_values_5a4 != &state->source_values_598) {
        state->destination_values_5a4.assign(
            state->source_values_598.begin(),
            state->source_values_598.end());
    }
}

} // namespace th105
