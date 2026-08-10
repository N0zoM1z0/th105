#include "Collision.hpp"

namespace th105 {

InfoManager *g_info_manager;

namespace {

struct InfoManagerCounterView;

typedef void (__thiscall *CounterStepCallback)(
    InfoManagerCounterView *manager,
    int mode,
    int player_index,
    int counter_steps);

struct InfoManagerCounterView {
    CounterStepCallback *vtable_00;
};

} // namespace

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

void Fighter::consume_counter_484_steps(char count)
{
    int requested_steps = static_cast<int>(count);
    int completed_steps = 0;

    if (requested_steps > 0) {
        do {
            if (unknown_484 <= 0) {
                return;
            }

            unknown_484 -= 200;
            if (unknown_484 < 0) {
                unknown_484 = 0;
            }

            counter_482 = unknown_484;
            floor_486 = 0;

            InfoManagerCounterView *manager =
                reinterpret_cast<InfoManagerCounterView *>(g_info_manager);
            manager->vtable_00[6](
                manager,
                1,
                player_index_334,
                unknown_484 / 200);

            ++completed_steps;
        } while (completed_steps < requested_steps);
    }
}

} // namespace th105
