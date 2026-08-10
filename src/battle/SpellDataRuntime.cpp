#include "SpellData.hpp"

namespace th105 {

short SpellDataOwner::select_spell_record_id()
{
    if (selection_ids_34.live_count_10 != 0) {
        ShortDeque8 *selection = &selection_ids_34;
        short result = *selection->front_checked();
        if (selection->live_count_10 != 0) {
            ++selection->head_0c;
            if (selection->block_capacity_08 * 8 <= selection->head_0c) {
                selection->head_0c = 0;
            }
            --selection->live_count_10;
            if (selection->live_count_10 == 0) {
                selection->head_0c = 0;
            }
        }
        return result;
    }
    return -1;
}

} // namespace th105
