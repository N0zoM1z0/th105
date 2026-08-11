#pragma once

#include "battle/Collision.hpp"

#include <stddef.h>

namespace th105 {

// Shared observed prefix used by all roster-owned CharacterObject families.
// Concrete character objects continue beyond owner_348.
struct CharacterObjectEffectEmitter {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x10];
    unsigned char facing_104;
    unsigned char unknown_105[0x243];
    Fighter *owner_348;

    void emit_fighter_effect_433cc0(
        int effect_code,
        float x,
        float y,
        int direction,
        int trailing_value);
    unsigned char emit_repeated_effects_for_owner_state(
        int mode,
        int effect_200_count,
        int effect_201_count);
};

typedef char CheckCharacterObjectEffectOwnerOffset[
    offsetof(CharacterObjectEffectEmitter, owner_348) == 0x348 ? 1 : -1];
typedef char CheckCharacterObjectEffectEmitterSize[
    sizeof(CharacterObjectEffectEmitter) == 0x34c ? 1 : -1];

} // namespace th105
