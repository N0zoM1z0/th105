#include "ScoreData.hpp"

#include "battle/GameMode.hpp"
#include "input/InputSelection.hpp"

#include <vector>

namespace th105 {

void ScoreData::record_sequence_result_42c060(
    int range_selector,
    int key_00,
    int key_08)
{
    if (get_game_mode() != 0 || get_session_setup_option() == 2) {
        return;
    }

    ObservedRecordRange16 *range =
        reinterpret_cast<ObservedRecordRange16 *>(
            reinterpret_cast<unsigned char *>(this) + 0x198) +
        range_selector;
    for (ObservedRecord24 *record = range->begin_04;
         record != range->end_08;
         ++record) {
        if (record->key_00 == key_00 && record->key_08 == key_08) {
            ++record->sequence_result_count_0c;
            return;
        }
    }
}

void ScoreData::update_observed_record_statistics(
    int range_selector,
    int key_00,
    int key_08,
    int observed_value)
{
    if (get_game_mode() != 0 || get_session_setup_option() == 2) {
        return;
    }

    std::vector<ObservedRecord24> *records =
        reinterpret_cast<std::vector<ObservedRecord24> *>(
            reinterpret_cast<unsigned char *>(this) + 0x198) +
        range_selector;
    for (std::vector<ObservedRecord24>::iterator record = records->begin();
         record != records->end();
         ++record) {
        if (record->key_00 == key_00 && record->key_08 == key_08) {
            ++record->update_count_10;
            if (record->maximum_observed_14 < observed_value) {
                record->maximum_observed_14 = observed_value;
            }
            return;
        }
    }
}

} // namespace th105
