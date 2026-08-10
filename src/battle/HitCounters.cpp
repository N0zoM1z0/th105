#include "Collision.hpp"

namespace th105 {

void Fighter::adjust_capped_counter_558(short amount)
{
    if (state_72c != 2 && state_55a < state_55b) {
        if (state_55a == state_55b - 2) {
            amount = static_cast<short>((amount * 2) / 3);
        } else if (state_55a == state_55b - 1) {
            amount = static_cast<short>(amount / 2);
        }

        int capped = static_cast<int>(counter_558) + amount;
        if (capped >= 500) {
            capped = 500;
        }
        counter_558 = static_cast<short>(capped);
    }
}

void Fighter::apply_deferred_counter_558(short amount)
{
    if (state_72c != 2) {
        short before = counter_558;
        if (before < amount) {
            if (state_55a > 0) {
                counter_558 = static_cast<short>(before - amount + 500);
                emit_fighter_effect_433cc0(
                    0xa0, x_ec, y_f0 + 100.0, facing_104, 1);
                advance_fighter_sequence_55c();
                return;
            }
            counter_558 = 0;
            return;
        }
        counter_558 = static_cast<short>(before - amount);
    }
}

} // namespace th105
