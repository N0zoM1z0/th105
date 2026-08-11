#include "CharacterObjectEffects.hpp"

namespace th105 {

unsigned char CharacterObjectEffectEmitter::emit_repeated_effects_for_owner_state(
    int mode,
    int effect_200_count,
    int effect_201_count)
{
    if (mode == 0) {
        short const owner_state = owner_348->state_13c;
        if (owner_state <= 49 || owner_state >= 150) {
            return 0;
        }
    } else {
        if (mode != 1) {
            return 0;
        }
        short const owner_state = owner_348->state_13c;
        if (owner_state > 70) {
            if (owner_state < 150) {
                // Accepted mode-one owner action window.
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    }

    if (effect_200_count > 0) {
        int count = effect_200_count;
        do {
            emit_fighter_effect_433cc0(200, x_ec, y_f0, facing_104, 1);
        } while (--count != 0);
    }
    if (effect_201_count > 0) {
        int count = effect_201_count;
        do {
            emit_fighter_effect_433cc0(201, x_ec, y_f0, facing_104, 1);
        } while (--count != 0);
    }
    return 1;
}

} // namespace th105
