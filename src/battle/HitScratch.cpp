#include "Collision.hpp"

namespace th105 {

InfoManager *g_info_manager;

void CollisionContext::reset_hit_exchange_scratch(
    Fighter *owner,
    Fighter *target)
{
    target->value_47c = target->value_174;
    target->value_4a2 = 0;
    owner->value_498 = 0;
    owner->scalar_494 = 1.0f;
    owner->value_49a = 0;
    owner->value_49c = 0;
    owner->flag_491 = 0;
    g_info_manager->indexed_entries_16c[
        owner->player_index_334
    ].reset_info_manager_indexed_entry();
}

} // namespace th105
