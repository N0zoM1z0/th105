#pragma once

#include "battle/Collision.hpp"

#include <stddef.h>

namespace th105 {

// Shared observed prefix used by all roster-owned CharacterObject families.
// Concrete character objects continue beyond +0x377.
struct CharacterObjectEffectEmitter {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char unknown_0fc[0x08];
    signed char facing_104;
    unsigned char unknown_105[0x0e];
    unsigned char ping_pong_phase_113;
    unsigned char unknown_114[0x08];
    float scale_x_11c;
    float scale_y_120;
    unsigned char unknown_124[0x08];
    float angle_12c;
    unsigned char unknown_130[0x0e];
    short update_mode_13e;
    unsigned char unknown_140[0x04];
    int time_counter_144;
    unsigned char unknown_148[0x24];
    void *related_16c;
    CharacterObjectEffectEmitter *target_170;
    unsigned char unknown_174[0x1bc];
    int lifetime_330;
    unsigned char unknown_334[0x08];
    unsigned char spawn_field_33c;
    unsigned char unknown_33d[0x03];
    float *heading_340;
    unsigned char unknown_344[0x04];
    Fighter *owner_348;
    unsigned char unknown_34c[0x18];
    unsigned short ping_pong_direction_364;
    unsigned char unknown_366[0x0a];
    float spawn_phase_370;
    float spawn_rate_374;

    void *spawn_unparented_related_object(
        int action_id,
        float x,
        float y,
        int facing,
        int field_33c,
        const unsigned *copied_words,
        int copied_word_count);
    void *spawn_parented_related_object(
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
    void update_ping_pong_motion_and_periodic_spawn();
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
typedef char CheckCharacterObjectEffectModeOffset[
    offsetof(CharacterObjectEffectEmitter, update_mode_13e) == 0x13e ? 1 : -1];
typedef char CheckCharacterObjectEffectLifetimeOffset[
    offsetof(CharacterObjectEffectEmitter, lifetime_330) == 0x330 ? 1 : -1];
typedef char CheckCharacterObjectEffectDirectionOffset[
    offsetof(CharacterObjectEffectEmitter, ping_pong_direction_364) == 0x364 ? 1 : -1];
typedef char CheckCharacterObjectEffectSpawnPhaseOffset[
    offsetof(CharacterObjectEffectEmitter, spawn_phase_370) == 0x370 ? 1 : -1];
typedef char CheckCharacterObjectEffectEmitterSize[
    sizeof(CharacterObjectEffectEmitter) == 0x378 ? 1 : -1];

} // namespace th105
