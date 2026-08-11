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
    signed char facing_104;
    unsigned char unknown_105[0x67];
    void *related_16c;
    CharacterObjectEffectEmitter *target_170;
    unsigned char unknown_174[0x1cc];
    float *heading_340;
    unsigned char unknown_344[0x04];
    Fighter *owner_348;

    void *spawn_unparented_related_object(
        int action_id,
        float x,
        float y,
        int facing,
        int field_33c,
        const unsigned *copied_words,
        int copied_word_count);
    void turn_heading_toward_related(
        float heading_bias,
        float max_step,
        float y_offset);
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
typedef char CheckCharacterObjectEffectRelatedOffset[
    offsetof(CharacterObjectEffectEmitter, related_16c) == 0x16c ? 1 : -1];
typedef char CheckCharacterObjectEffectTargetOffset[
    offsetof(CharacterObjectEffectEmitter, target_170) == 0x170 ? 1 : -1];
typedef char CheckCharacterObjectEffectHeadingOffset[
    offsetof(CharacterObjectEffectEmitter, heading_340) == 0x340 ? 1 : -1];
typedef char CheckCharacterObjectEffectEmitterSize[
    sizeof(CharacterObjectEffectEmitter) == 0x34c ? 1 : -1];

} // namespace th105
