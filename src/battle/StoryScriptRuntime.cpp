#include "battle/BattleController.hpp"
#include "assets/CsvReader.hpp"
#include "assets/String28.hpp"
#include <stddef.h>
#include <string.h>

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);

namespace th105 {
const char * __cdecl character_key_to_name(int character_key);
extern "C" const char scenario_page_path_format[];
extern "C" const char scenario_csv_prefix[];
extern "C" const char scenario_story_suffix[];

struct StoryScriptSubobjectLayout {
    virtual void initialize_for_input(void *selected_input);
    unsigned char storage_004[0x520];
    void load_story_page_4583e0(const char *path);
    int advance_until_ready_454f10();
};
typedef char script_layout_size[(sizeof(StoryScriptSubobjectLayout)==0x524)?1:-1];

struct BattlePhaseScriptLayout {
    String28 character_name_000;
    unsigned char gap_01c[0x1c];
    CsvReader reader_038;
    StoryScriptSubobjectLayout script_068;
    void *selected_input_58c;
    int selected_column_590;
    signed char page_index_594;
    signed char story_character_595;
};
typedef char script_name_off[(offsetof(BattlePhaseScriptLayout, character_name_000)==0)?1:-1];
typedef char script_reader_off[(offsetof(BattlePhaseScriptLayout, reader_038)==0x38)?1:-1];
typedef char script_state_off[(offsetof(BattlePhaseScriptLayout, script_068)==0x68)?1:-1];
typedef char script_input_off[(offsetof(BattlePhaseScriptLayout, selected_input_58c)==0x58c)?1:-1];
typedef char script_col_off[(offsetof(BattlePhaseScriptLayout, selected_column_590)==0x590)?1:-1];
typedef char script_page_off[(offsetof(BattlePhaseScriptLayout, page_index_594)==0x594)?1:-1];
typedef char script_char_off[(offsetof(BattlePhaseScriptLayout, story_character_595)==0x595)?1:-1];

void BattlePhaseBlock::advance_scenario_script_page_458d10()
{
    BattlePhaseScriptLayout *state = reinterpret_cast<BattlePhaseScriptLayout *>(this);
    char path[260];
    wsprintfA(path, scenario_page_path_format,
        state->character_name_000.c_str(), state->page_index_594);
    state->script_068.load_story_page_4583e0(path);
    state->script_068.advance_until_ready_454f10();
    ++state->page_index_594;
}

void BattlePhaseBlock::initialize_character_story_script_458f10(
    int character_key, void *selected_input, int selected_column)
{
    BattlePhaseScriptLayout *state = reinterpret_cast<BattlePhaseScriptLayout *>(this);
    const char *name = character_key_to_name(character_key);
    state->character_name_000.assign(name, strlen(name));
    state->selected_input_58c = selected_input;
    state->selected_column_590 = selected_column;
    state->page_index_594 = 0;

    String28 full_path =
        scenario_csv_prefix + state->character_name_000 + scenario_story_suffix;
    state->reader_038.load(full_path.c_str());
    state->story_character_595 = static_cast<signed char>(state->reader_038.next_int());
    state->reader_038.advance_row();
    state->script_068.initialize_for_input(state->selected_input_58c);
}
}
