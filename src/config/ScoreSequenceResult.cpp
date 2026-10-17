#include "ScoreData.hpp"

#include "battle/GameMode.hpp"
#include "input/InputSelection.hpp"

#include <stddef.h>
#include <vector>

namespace th105 {

typedef char ScoreSequenceRecord_size[sizeof(ObservedRecord24) == 0x18 ? 1 : -1];
typedef char ScoreSequenceRange_size[
    sizeof(std::vector<ObservedRecord24>) == 0x10 ? 1 : -1];
typedef char ScoreSequenceCount_offset[
    offsetof(ObservedRecord24, sequence_result_count_0c) == 0x0c ? 1 : -1];

void ScoreData::record_sequence_result_42c060(
    int range_selector, int key_00, int key_08)
{
    if (get_game_mode() != 0 || get_session_setup_option() == 2)
        return;

    std::vector<ObservedRecord24> *records =
        reinterpret_cast<std::vector<ObservedRecord24> *>(
            reinterpret_cast<unsigned char *>(this) + 0x198) + range_selector;
    for (std::vector<ObservedRecord24>::iterator record = records->begin();
         record != records->end(); ++record) {
        if (record->key_00 == key_00 && record->key_08 == key_08) {
            ++record->sequence_result_count_0c;
            return;
        }
    }
}

} // namespace th105
