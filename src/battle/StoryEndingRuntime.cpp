#include "assets/String28.hpp"

#include <stddef.h>

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);

namespace th105 {

int __cdecl resolve_scenario_event_name(String28 value);
extern "C" const char scenario_ending_path_format[];

struct ScoreDataStoryProgressView {
    void record_story_event_42e750(int event_id, int selected_column);
};

ScoreDataStoryProgressView *__cdecl get_score_data_story_progress();

struct StoryEndingSubobjectView {
    virtual void slot_00();
    unsigned char reserved_004[0x520];
    void load_story_page_4583e0(const char *path);
    int advance_until_ready_454f10();
};

typedef char StoryEndingSubobjectView_size[
    sizeof(StoryEndingSubobjectView) == 0x524 ? 1 : -1];

struct BattlePhaseEndingView {
    String28 character_name_000;
    unsigned char reserved_01c[0x4c];
    StoryEndingSubobjectView script_068;
    unsigned char reserved_58c[4];
    int selected_column_590;

    void load_story_ending_page_45a3a0();
};

void BattlePhaseEndingView::load_story_ending_page_45a3a0()
{
    get_score_data_story_progress()->record_story_event_42e750(
        resolve_scenario_event_name(
            String28(character_name_000, 0, static_cast<unsigned int>(-1))),
        selected_column_590);

    char path[260];
    wsprintfA(path, scenario_ending_path_format, character_name_000.c_str());
    script_068.load_story_page_4583e0(path);
    script_068.advance_until_ready_454f10();
}

typedef char BattlePhaseEndingView_script_offset[
    offsetof(BattlePhaseEndingView, script_068) == 0x68 ? 1 : -1];
typedef char BattlePhaseEndingView_column_offset[
    offsetof(BattlePhaseEndingView, selected_column_590) == 0x590 ? 1 : -1];

} // namespace th105
