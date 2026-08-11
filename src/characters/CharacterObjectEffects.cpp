#include "CharacterObjectEffects.hpp"

#include <math.h>

namespace th105 {

double __cdecl atan2_degrees(float y, float x);

namespace {

typedef void *(__thiscall *SpawnOwnedObject)(
    void *manager,
    CharacterObjectEffectEmitter *parent,
    void *related,
    int action_id,
    float x,
    float y,
    int facing,
    int field_33c,
    const unsigned *copied_words,
    int copied_word_count);

} // namespace

void CharacterObjectEffectEmitter::turn_heading_toward_related(
    float heading_bias,
    float max_step,
    float y_offset)
{
    y_offset = static_cast<float>(-atan2_degrees(
        target_170->y_f0 + y_offset - y_f0,
        (target_170->x_ec - x_ec) * static_cast<float>(facing_104)));
    double const desired_heading = y_offset + heading_bias;
    float delta = static_cast<float>(desired_heading - *heading_340);
    delta = static_cast<float>(static_cast<int>(delta) % 360);

    if (delta > 180.0f) {
        delta -= 360.0f;
    }
    if (delta < -180.0f) {
        delta += 360.0f;
    }

    float const absolute_delta = static_cast<float>(fabs(delta));
    if (absolute_delta <= max_step) {
        *heading_340 = desired_heading;
    } else if (delta < 0.0f) {
        *heading_340 -= max_step;
    } else if (delta > 0.0f) {
        *heading_340 += max_step;
    }
}

void *CharacterObjectEffectEmitter::spawn_unparented_related_object(
    int action_id,
    float x,
    float y,
    int facing,
    int field_33c,
    const unsigned *copied_words,
    int copied_word_count)
{
    void *manager = owner_348->owned_manager_658;
    SpawnOwnedObject const spawn =
        reinterpret_cast<SpawnOwnedObject>(
            (*reinterpret_cast<void ***>(manager))[1]);
    return spawn(
        manager,
        0,
        related_16c,
        action_id,
        x,
        y,
        facing,
        field_33c,
        copied_words,
        copied_word_count);
}

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
            emit_fighter_effect_433cc0(
                200,
                x_ec,
                y_f0,
                static_cast<unsigned char>(facing_104),
                1);
        } while (--count != 0);
    }
    if (effect_201_count > 0) {
        int count = effect_201_count;
        do {
            emit_fighter_effect_433cc0(
                201,
                x_ec,
                y_f0,
                static_cast<unsigned char>(facing_104),
                1);
        } while (--count != 0);
    }
    return 1;
}

} // namespace th105
