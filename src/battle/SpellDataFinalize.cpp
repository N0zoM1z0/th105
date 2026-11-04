#include "SpellData.hpp"
#include <deque>

namespace th105 {
typedef char SpellFinalizeDequeSize[sizeof(std::deque<short>) == sizeof(ShortDeque8) ? 1 : -1];
void SpellDataOwner::finalize_loaded_spell_data()
{
    unsigned *selected_values = reinterpret_cast<unsigned *>(selected_value_by_index_48);
    for (unsigned i = 0; i < 8; ++i)
        selected_values[i] = 0;
    for (std::deque<short>::iterator it =
             reinterpret_cast<std::deque<short> *>(&loaded_spell_ids_20)->begin();
         it != reinterpret_cast<std::deque<short> *>(&loaded_spell_ids_20)->end();
         ++it) {
        SpellRecordView *record = find_local_then_common_spell_record(*it);
        if (record != 0 && record->selector_1c == 1)
            selected_value_by_index_48[static_cast<unsigned short>(record->value_1e)] = static_cast<unsigned char>(*it);
    }
}
}
