#include "SpellData.hpp"
#include <deque>
#include <cstring>

namespace th105 {
void SpellDataOwner::finalize_loaded_spell_data()
{
    std::memset(selected_value_by_index_48, 0, sizeof(selected_value_by_index_48));
    for (std::deque<short>::iterator it =
             loaded_spell_ids_20.begin();
         it != loaded_spell_ids_20.end();
         ++it) {
        int spell_id = *it;
        SpellRecordView *record = find_local_then_common_spell_record(spell_id);
        if (record != 0 && record->selector_1c == 1)
            selected_value_by_index_48[static_cast<unsigned short>(record->value_1e)] = static_cast<unsigned char>(*it);
    }
}
}
