#pragma once

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

ScoreData *get_score_data();

} // namespace th105
