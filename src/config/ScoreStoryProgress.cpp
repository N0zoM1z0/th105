#include <vector>
#include <stddef.h>

namespace th105 {

unsigned int __cdecl get_session_setup_option();
void *__cdecl get_network_session();

struct ScoreDataStoryProgressView {
    unsigned int unknown_00;
    unsigned int flags_04;
    unsigned char event_columns_08[15];
    unsigned char reserved_17[5];
    unsigned char primary_available_1c[15];
    unsigned char reserved_2b[5];
    unsigned char secondary_available_30[15];
    unsigned char reserved_3f[0x1d];
    std::vector<int> primary_indices_5c;
    std::vector<int> secondary_indices_6c;

    void record_story_event_42e750(int event_id, int selected_column);
    void refresh_story_progress_42e3f0();
    void persist_story_progress_42d3f0();
};

void ScoreDataStoryProgressView::refresh_story_progress_42e3f0()
{
    int completed = 0;
    for (int i = 0; i < 15; ++i) {
        if (event_columns_08[i])
            ++completed;
    }

    if (event_columns_08[0])
        primary_available_1c[5] = 1;
    if (event_columns_08[1])
        primary_available_1c[3] = 1;
    if (event_columns_08[5])
        primary_available_1c[8] = 1;
    if (event_columns_08[1] && event_columns_08[2])
        primary_available_1c[6] = 1;
    if (event_columns_08[0] && event_columns_08[2])
        primary_available_1c[4] = 1;
    if (event_columns_08[5])
        primary_available_1c[12] = 1;
    if (event_columns_08[0] && event_columns_08[3])
        primary_available_1c[10] = 1;
    if (completed >= 7) {
        primary_available_1c[7] = 1;
        primary_available_1c[11] = 1;
        primary_available_1c[9] = 1;
    }
    if (completed >= 13)
        primary_available_1c[13] = 1;
    if (event_columns_08[13])
        primary_available_1c[14] = 1;
    if (event_columns_08[14])
        flags_04 |= 0x100u;

    secondary_indices_6c.erase(
        secondary_indices_6c.begin(), secondary_indices_6c.end());
    primary_indices_5c.erase(
        primary_indices_5c.begin(), primary_indices_5c.end());

    for (int i = 0; i < 15; ++i) {
        if (primary_available_1c[i])
            primary_indices_5c.push_back(i);
        if (secondary_available_30[i])
            secondary_indices_6c.push_back(i);
    }

    if (primary_indices_5c.size() == 0) {
        primary_available_1c[0] = 1;
        primary_available_1c[1] = 1;
        primary_available_1c[2] = 1;
        for (int i = 0; i < 15; ++i) {
            if (primary_available_1c[i])
                primary_indices_5c.push_back(i);
        }
    }

    if (secondary_indices_6c.size() == 0) {
        for (int i = 0; i < 13; ++i) {
            secondary_available_30[i] = 1;
            secondary_indices_6c.push_back(i);
        }
    }
}

void ScoreDataStoryProgressView::record_story_event_42e750(
    int event_id, int selected_column)
{
    if (get_session_setup_option() == 2)
        return;
    if (get_network_session() != 0)
        return;

    flags_04 |= 1u << selected_column;
    if (event_id == 14)
        flags_04 |= 0x100u;
    event_columns_08[event_id] |=
        static_cast<unsigned char>(1u << selected_column);
    secondary_available_30[13] = 1;
    secondary_available_30[14] = 1;
    refresh_story_progress_42e3f0();
    persist_story_progress_42d3f0();
}

typedef char ScoreDataStoryProgress_primary_vector_offset[
    offsetof(ScoreDataStoryProgressView, primary_indices_5c) == 0x5c ? 1 : -1];
typedef char ScoreDataStoryProgress_secondary_vector_offset[
    offsetof(ScoreDataStoryProgressView, secondary_indices_6c) == 0x6c ? 1 : -1];

} // namespace th105
