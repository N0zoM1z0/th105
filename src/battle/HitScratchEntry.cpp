#include "Collision.hpp"

namespace th105 {

void HitExchangeIndexedEntry::reset_info_manager_indexed_entry()
{
    reset_state_14 = 10;
    unknown_18 = 0;
    unknown_10 = 0;
    reset_flag_1c = 0;
    release_owned_pointer_buffer(owned_tail_20);
}

} // namespace th105
