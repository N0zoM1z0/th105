#pragma once

#include <stddef.h>
#include <vector>

namespace th105 {

struct ObservedRecord24 {
    int key_00;
    unsigned char unknown_04[0x04];
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
    unsigned char unknown_000[0x198];
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

typedef char ScoreData_records_offset[
    offsetof(ScoreData, records_198) == 0x198 ? 1 : -1];
typedef char ScoreData_record_vector_size[
    sizeof(std::vector<ObservedRecord24>) == 0x10 ? 1 : -1];

ScoreData *get_score_data();

} // namespace th105
