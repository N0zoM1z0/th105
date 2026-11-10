#pragma once

#include <stddef.h>
#include <vector>
#include <map>
#include <set>

namespace th105 {

struct ObservedRecord24 {
    int key_00;
    int difficulty_04;
    int key_08;
    int sequence_result_count_0c;
    int update_count_10;
    int maximum_observed_14;
};

struct ObservedRecordRange16 {
    unsigned char unknown_00[0x04];
    ObservedRecord24 *begin_04;
    ObservedRecord24 *end_08;
    ObservedRecord24 *capacity_0c;
};

struct ScoreData {
    unsigned char initialized_00;
    unsigned char unknown_01[3];
    unsigned flags_04;
    unsigned char event_columns_08[20];
    unsigned char primary_available_1c[20];
    unsigned char secondary_available_30[20];
    std::set<unsigned> music_paths_44;
    std::set<unsigned> available_items_50;
    std::vector<int> primary_indices_5c;
    std::vector<int> secondary_indices_6c;
    std::vector<int> auxiliary_indices_7c;
    std::vector<int> auxiliary_indices_8c;
    std::map<int, int> common_counts_9c;
    std::map<int, int> character_counts_a8[20];
    std::vector<ObservedRecord24> records_198[20];

    void record_sequence_result_42c060(
        int range_selector,
        int key_00,
        int key_08);
    void update_observed_record_statistics(
        int range_selector,
        int key_00,
        int key_08,
        int observed_value);
};

typedef char ScoreData_music_offset[
    offsetof(ScoreData, music_paths_44) == 0x44 ? 1 : -1];
typedef char ScoreData_common_counts_offset[
    offsetof(ScoreData, common_counts_9c) == 0x9c ? 1 : -1];
typedef char ScoreData_character_counts_offset[
    offsetof(ScoreData, character_counts_a8) == 0xa8 ? 1 : -1];
typedef char ScoreData_records_offset[
    offsetof(ScoreData, records_198) == 0x198 ? 1 : -1];
typedef char ScoreData_record_vector_size[
    sizeof(std::vector<ObservedRecord24>) == 0x10 ? 1 : -1];

ScoreData *get_score_data();

} // namespace th105
