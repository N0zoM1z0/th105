#include "SpellData.hpp"

namespace th105 {

short SpellDataOwner::select_spell_record_id()
{
    if (!selection_ids_34.empty()) {
        short result = selection_ids_34.front();
        selection_ids_34.pop_front();
        return result;
    }
    return -1;
}

} // namespace th105
