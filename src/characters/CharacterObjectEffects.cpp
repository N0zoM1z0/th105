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

void *CharacterObjectEffectEmitter::spawn_parented_related_object(
    int action_id,
    float x,
    float y,
    int facing,
    int field_33c,
    const unsigned *copied_words,
    int copied_word_count)
{
    void *manager = owner_348->owned_manager_658;
    return reinterpret_cast<SpawnOwnedObject>(
        (*reinterpret_cast<void ***>(manager))[1])(
            manager,
            this,
            related_16c,
            action_id,
            x,
            y,
            facing,
            field_33c,
            copied_words,
            copied_word_count);
}

void CharacterObjectEffectEmitter::update_ping_pong_motion_and_periodic_spawn()
{
    float copied_words[3];

    switch (static_cast<int>(update_mode_13e)) {
    case 1: {
        float value;
        if (ping_pong_direction_364 == 0) {
            if (ping_pong_phase_113 <= 250u) {
                ping_pong_phase_113 += 5;
            } else {
                ping_pong_phase_113 = 0xff;
                ping_pong_direction_364 = 1;
            }
        } else {
            if (ping_pong_phase_113 < 4u) {
                goto expire;
            }
            ping_pong_phase_113 -= 4;
        }

        value = scale_x_11c + 0.0025f;
        scale_x_11c = value;
        scale_y_120 = value;
        angle_12c += 2.0f;
        velocity_x_f4 *= 0.99f;
        velocity_y_f8 += 0.01f;
        if (velocity_y_f8 > 2.0f) {
            velocity_y_f8 = 2.0f;
        }
        *heading_340 += 3.0f;
        spawn_phase_370 += 0.05f;
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        return;

    expire:
        --lifetime_330;
        return;
    }
    case 0:
        break;
    default:
        return;
    }

    float time = static_cast<float>(time_counter_144);
    if (time >= heading_340[1]) {
        --lifetime_330;
        return;
    }
    if (time_counter_144 % 2 == 0) {
        copied_words[0] = time * spawn_rate_374 + spawn_phase_370;
        copied_words[1] = 1.0f;
        copied_words[2] = 1.0f;
        spawn_unparented_related_object(
            980,
            x_ec,
            y_f0,
            static_cast<unsigned char>(facing_104),
            spawn_field_33c,
            reinterpret_cast<const unsigned *>(copied_words),
            3);
    }
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
