// Source hypothesis for the complete ReimuObject496540 void update root.
// Original Japanese1.06a only; canonical equality remains unaccepted.
#include "ReimuObjectActionStateStaging.hpp"
#include "CharacterObjectEffects.hpp"
#include "CharacterObjectRuntime.hpp"
#include <math.h>

namespace th105 {

// Match-mode switches retain target-observed 3,2,1,0 physical block order.
// docs/REIMU_OBJECT_SELECTOR_ORDER_2026_10_21.md; whole root remains nonexact.

//902 publishes two interleaved float rectangles at owner+7A8..7C4.
// A member view preserves VC8's float rounding and owner-pointer reloads;
// raw float-pointer stores erase those target-observed operations.
// The preceding bytes are unmodeled owner state, not an asserted base layout.
struct ReimuOwnerBoundaryView {
    unsigned char unknown_000[0x7a8];
    float x_lower_0;
    float x_lower_1;
    float x_upper_0;
    float x_upper_1;
    float y_upper_0;
    float y_upper_1;
    float y_lower_0;
    float y_lower_1;
};

typedef char ReimuOwnerBoundary_x_lower_0_offset[
    offsetof(ReimuOwnerBoundaryView, x_lower_0) == 0x7a8 ? 1 : -1];
typedef char ReimuOwnerBoundary_x_lower_1_offset[
    offsetof(ReimuOwnerBoundaryView, x_lower_1) == 0x7ac ? 1 : -1];
typedef char ReimuOwnerBoundary_x_upper_0_offset[
    offsetof(ReimuOwnerBoundaryView, x_upper_0) == 0x7b0 ? 1 : -1];
typedef char ReimuOwnerBoundary_x_upper_1_offset[
    offsetof(ReimuOwnerBoundaryView, x_upper_1) == 0x7b4 ? 1 : -1];
typedef char ReimuOwnerBoundary_y_upper_0_offset[
    offsetof(ReimuOwnerBoundaryView, y_upper_0) == 0x7b8 ? 1 : -1];
typedef char ReimuOwnerBoundary_y_upper_1_offset[
    offsetof(ReimuOwnerBoundaryView, y_upper_1) == 0x7bc ? 1 : -1];
typedef char ReimuOwnerBoundary_y_lower_0_offset[
    offsetof(ReimuOwnerBoundaryView, y_lower_0) == 0x7c0 ? 1 : -1];
typedef char ReimuOwnerBoundary_y_lower_1_offset[
    offsetof(ReimuOwnerBoundaryView, y_lower_1) == 0x7c4 ? 1 : -1];

// This caller-side float view follows869/901 consumers; the original lookup
// C++ return types remain unproved.
float __cdecl lookup_orientation_sine_quantized_abs(float angle);
float __cdecl lookup_orientation_cosine_quantized_abs(float angle);
int __cdecl selector_random_roll(int limit);
unsigned int __cdecl mt19937_next_u32();
float __fastcall stage_surface_height_at_x(Fighter *fighter);
float __cdecl atan2_degrees(float y, float x);
extern int g_match_identifier;

// The already-matched465190 wrapper forwards seven32-bit argument words.
// Its sixth word carries the copied-parameter pointer to the owned manager.
class ReimuObjectOwnerSpawnView {
public:
    void dispatch_character_wave_handle(unsigned int index);
    void dispatch_indexed_event_member(unsigned int index);
    int spawn_owned_object_via_manager(
        int action, float x, float y, int facing, int variant,
        int copied_words, int copied_word_count);
};

// Source grouping hypothesis: keep the real4963A0 body visible to496540.
// The helper remains independently canonical; original TU ownership is unknown.
unsigned char CharacterObjectRuntime::advance_state_six_counter_conditional(
    int limit)
{
    if (phase_state_180 != 6) {
        goto return_zero;
    }
    ++state_six_counter_384;
    if (limit <= 0 || state_six_counter_384 < limit) {
        ++phase_index_184;
        phase_state_180 = 0;
        goto return_zero;
    }
    return 1;

return_zero:
    return 0;
}

// Ordinary local exits preserve observed state330 write-before-x87-pop paths.
// docs/REIMU_OBJECT_LOCAL_EXITS_2026_10_21.md.
void ReimuObjectActionStateStagingView::dispatch_action_state()
{
    float packet_822_health[4];
    float packet_822_phase[4];
    float packet_869_sequence[3];
    float packet_869_owner[3];
    float dead_sequence_zero[3];
    float completed_sequence_zero[4];
    float dead_sequence_one[3];
    float health_packet[3];
    float exhausted_packet[3];
    float packet_902_retirement[3];
    float packet_903_health[3];
    float packet_903_burst[3];
    float packet_908_sequence_6[3];
    float packet_908_sequence_7[3];
    unsigned retiring_action;
    const unsigned *retiring_packet;
    int retiring_words;
    switch (action_13c) {
    case 800:
        if (phase_state_180 == 5 || (sequence_13e == 0 &&
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 3)))
            goto retire;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                replace_secondary_animation(993, 10.0f, 10, 1, 2);
            phase_index_184 = 1;
            state_364 = 0;
        }
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1) {
            scale_x_11c = 2.0f;
            scale_y_120 = scale_x_11c;
        }
        if (sequence_13e == 0) {
            ++state_364;
            heading_12c = parameters_340[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(
                    state_364 * static_cast<double>(0.1f) + parameters_340[1]));
        }
        if (sequence_13e < 2) {
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
        }
        if (sequence_13e == 1) {
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = static_cast<float>(scale_y_120 * static_cast<double>(0.65f));
            if (alpha_113 < 5)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 5);
        }
        if (sequence_13e == 2) {
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.4f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.4f));
            if (alpha_113 < 25)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 25);
        }
        if (phase_state_180 != 0 && sequence_13e == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
            next_sequence_block();
            float copied[3] = {-heading_12c, 0.0f, 2.0f};
            reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->
                spawn_owned_object_via_manager(800, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<int>(copied), 3);
            return;
        }
        goto bounded_projectile_advance;

    case 801:
        if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -240.0 ||
                phase_state_180 == 5 || (sequence_13e < 2 &&
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        emit_repeated_effects_for_owner_state(0, 3, 8)))
            goto retire;
        heading_12c = static_cast<float>(heading_12c + 18.0);
        switch (sequence_13e) {
        case 0:
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (scale_x_11c < 1.0) {
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            } else {
                scale_x_11c = 1.0f;
                scale_y_120 = scale_x_11c;
                next_sequence_block();
            }
            break;
        case 1:
            parameters_340[1] = static_cast<float>(parameters_340[1] + static_cast<double>(0.35f));
            if (parameters_340[3] == 0.0f)
                state_36c = 1;
            if (state_36c == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    turn_heading_toward_related(0.0f, 2.5f, 100.0f);
                if (counter_144 % 5 == 0) {
                    float copied[3] = {heading_12c, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        spawn_unparented_related_object(801, x_ec, y_f0,
                            static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                }
            } else {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    turn_heading_toward_related(0.0f, 0.5f, 100.0f);
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (phase_state_180 != 0) {
                parameters_340[1] = 2.0f;
                ++state_368;
                if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10)) {
                    select_sequence(2);
                    return;
                }
                if (phase_state_180 == 0)
                    state_368 = 0;
                if (phase_index_184 == 0) {
                    select_sequence(2);
                    return;
                }
                if (state_368 > 5) {
                    state_368 = 0;
                    phase_state_180 = 0;
                }
            }
            if (counter_144 > 60)
                next_sequence_block();
            break;
        case 2:
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = velocity_x_f4;
            if (alpha_113 < 10) {
                alpha_113 = 0;
                --state_330;
            } else {
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.15f));
                scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.15f));
            }
            break;
        case 3:
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = velocity_x_f4;
            if (alpha_113 < 15) {
                alpha_113 = 0;
                --state_330;
            } else {
                alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            }
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
            goto retire_801_811;
        return;

retire_801_811:
        --state_330;
        return;

    case 804:
        if (phase_state_180 == 5 || (sequence_13e < 2 &&
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 5)))
            goto retire;
        if (sequence_13e == 0) {
            if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    replace_secondary_animation(993, 4.0f, 30, 1, 2);
                state_364 = 0;
            }
            heading_12c = parameters_340[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], 35.0f);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (phase_state_180 == 1 || phase_state_180 == 9) {
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(parameters_340[0], 2.0f);
                ++state_364;
                if (state_364 > 3) {
                    state_364 = 0;
                    phase_state_180 = 0;
                }
            }
            if (phase_state_180 == 2 || phase_state_180 == 4) {
                select_sequence(2);
                phase_index_184 = 0;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                velocity_x_f4 = static_cast<float>(8.0 -
                    static_cast<float>(mt19937_next_u32() % 20u) * static_cast<double>(0.1f));
                velocity_y_f8 = static_cast<float>(
                    static_cast<float>(mt19937_next_u32() % 25u) * static_cast<double>(0.1f) + 5.0);
            }
        }
        if (sequence_13e == 1) {
            if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    replace_secondary_animation(993, 4.0f, 30, 1, 2);
                state_364 = 0;
            }
            heading_12c = parameters_340[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], 35.0f);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (phase_state_180 == 2 || phase_state_180 == 1 || phase_state_180 == 9) {
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(parameters_340[0], 2.0f);
                ++state_364;
                if (state_364 > 3) {
                    state_364 = 0;
                    phase_state_180 = 0;
                }
            }
            if ((phase_state_180 == 2 || phase_state_180 == 4) &&
                    static_cast<signed char>(phase_index_184) <= 0) {
                select_sequence(2);
                phase_index_184 = 0;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                velocity_x_f4 = static_cast<float>(8.0 -
                    static_cast<float>(mt19937_next_u32() % 20u) * static_cast<double>(0.1f));
                velocity_y_f8 = static_cast<float>(
                    static_cast<float>(mt19937_next_u32() % 25u) * static_cast<double>(0.1f) + 5.0);
            }
        }
        if (sequence_13e == 2) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - 0.25);
            if (y_f0 + velocity_y_f8 < 0.0)
                velocity_y_f8 = -velocity_y_f8;
            heading_12c = static_cast<float>(heading_12c + 40.0);
            if (alpha_113 < 5)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 5);
        }
        if (sequence_13e < 2) {
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
        }
        if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -120.0)
            goto retire;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
            --state_330;
        return;

    case 807:
        if ((sequence_13e == 0 && reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 3, 10)) ||
                (sequence_13e == 1 && reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 0)))
            goto retire;
        if (sequence_13e == 0 || sequence_13e == 1) {
            heading_12c = static_cast<float>(heading_12c + 10.0);
            if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(20))
                phase_index_184 = 0;
            if (counter_144 < 10 || static_cast<signed char>(phase_index_184) > 0) {
                velocity_x_f4 = 20.0f;
            } else {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - 1.5);
                if (velocity_x_f4 < 1.5f) {
                    velocity_x_f4 = 1.5f;
                    if (alpha_113 <= 15)
                        goto retire;
                    alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
                    phase_index_184 = 0;
                }
            }
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        goto advance_and_retire_on_completion;

    case 808:
        if (sequence_13e == 0) {
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(1, 2, 5))
                goto retire;
            velocity_y_f8 = 5.0f;
            heading_12c = static_cast<float>(heading_12c + 5.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            if (counter_144 == 5 && y_f0 < 960.0) {
                float copied[3] = {0.0f, 0.0f, 0.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(808, x_ec, static_cast<float>(y_f0 + 80.0),
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 1.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(808, x_ec, static_cast<float>(y_f0 + 80.0),
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
            }
            if (counter_144 > 10) {
                if (alpha_113 <= 15)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
                phase_index_184 = 0;
            }
        }
        if (sequence_13e == 1) {
            velocity_y_f8 = 3.0f;
            heading_12c = static_cast<float>(heading_12c + 5.0);
            if (counter_144 > 10) {
                if (alpha_113 <= 15)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
                phase_index_184 = 0;
            }
        }
        y_f0 += velocity_y_f8;
        goto advance_and_retire_on_completion;

    case 810:
        if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -240.0 ||
                phase_state_180 == 5 || (sequence_13e < 3 &&
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        emit_repeated_effects_for_owner_state(0, 2, 8)))
            goto retire;
        heading_12c = static_cast<float>(heading_12c + 18.0);
        if (sequence_13e == 0) {
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (scale_x_11c < 1.0) {
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            } else {
                scale_x_11c = 1.0f;
                scale_y_120 = scale_x_11c;
                next_sequence_block();
            }
        }
        if (sequence_13e == 1) {
            parameters_340[1] = static_cast<float>(parameters_340[1] - 1.5);
            if (parameters_340[1] <= 0.0) {
                parameters_340[1] = 0.0f;
                ++state_364;
                if (state_364 > 15) {
                    next_sequence_block();
                    return;
                }
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (phase_state_180 != 0) {
                parameters_340[1] = 2.0f;
                ++state_368;
                if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(20))
                    phase_index_184 = 0;
                if (phase_index_184 == 0 || phase_state_180 == 4)
                    goto select_sequence_three;
                if (state_368 > 5) {
                    state_368 = 0;
                    phase_state_180 = 0;
                }
            }
        }
        if (sequence_13e == 2) {
            parameters_340[1] = static_cast<float>(parameters_340[1] + 0.75);
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                turn_heading_toward_related(0.0f, 2.0f, 100.0f);
            if (counter_144 % 5 == 0) {
                float copied[3] = {heading_12c, 0.0f, 4.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(810, x_ec, y_f0,
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (phase_state_180 != 0) {
                parameters_340[1] = 2.0f;
                ++state_368;
                if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(20))
                    phase_index_184 = 0;
                if (phase_index_184 == 0 || phase_state_180 == 4)
                    goto select_sequence_three;
                if (state_368 > 5) {
                    state_368 = 0;
                    phase_state_180 = 0;
                }
            }
            if (counter_144 > 60 || static_cast<signed char>(phase_index_184) < 1)
                next_sequence_block();
        }
        if (sequence_13e == 3) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = velocity_x_f4;
            if (alpha_113 < 10) {
                alpha_113 = 0;
                --state_330;
            } else {
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.15f));
                scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.15f));
            }
        }
        if (sequence_13e == 4) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = velocity_x_f4;
            if (alpha_113 < 15) {
                alpha_113 = 0;
                --state_330;
            } else {
                alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            }
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
            --state_330;
        return;

    case 811:
        if (phase_state_180 == 5)
            goto retire;
        if (sequence_13e == 0) {
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 1, 4))
                goto retire;
            if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    replace_secondary_animation(990, 20.0f, 10, 1, 2);
                phase_index_184 = 1;
                state_364 = 0;
            }
            heading_12c = parameters_340[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(15))
                phase_index_184 = 0;
            if (counter_144 % 4 == 0) {
                float copied[3] = {heading_12c, 5.0f, 5.0f};
                const float request_y = static_cast<float>(
                    static_cast<float>(static_cast<unsigned int>(selector_random_roll(32))) + y_f0 - 16.0);
                const float request_x = static_cast<float>(
                    static_cast<float>(static_cast<unsigned int>(selector_random_roll(32))) + x_ec - 16.0);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(811, request_x, request_y,
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
            }
            if (phase_index_184 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                select_sequence(2);
                scale_y_120 = 2.0f;
                float copied[3] = {0.0f, 0.0f, 3.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(811, x_ec, y_f0,
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                copied[2] = 4.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(811, x_ec, y_f0,
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                copied[2] = 4.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(811, x_ec, y_f0,
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                return;
            }
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
        }
        if (sequence_13e == 1) {
            if (!parent_object_34c)
                goto retire;
            heading_12c = parent_object_34c->parameters_340[0];
            x_ec = parent_object_34c->x_ec;
            y_f0 = parent_object_34c->y_f0;
            if (parent_object_34c->sequence_13e == 2)
                goto retire_801_811;
        }
        if (sequence_13e == 2) {
            parameters_340[1] = static_cast<float>(parameters_340[1] - 1.5);
            if (parameters_340[1] < 2.0f)
                parameters_340[1] = 2.0f;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.01f));
            scale_y_120 = static_cast<float>(scale_y_120 * static_cast<double>(0.85f));
            if (scale_y_120 < 0.02f)
                goto retire;
        }
        if (sequence_13e == 3) {
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.02f));
            scale_y_120 = scale_x_11c;
        }
        if (sequence_13e == 3 || sequence_13e == 4) {
            if (channel_111 < 40) {
                channel_111 = 0;
                if (alpha_113 < 40)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 40);
            } else {
                channel_111 = static_cast<unsigned char>(channel_111 - 40);
            }
        }
        if (sequence_13e == 5) {
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.02f));
            scale_y_120 = static_cast<float>(scale_y_120 * static_cast<double>(0.95f));
            if (alpha_113 <= 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
        }
        if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -120.0)
            goto retire;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
            --state_330;
        return;

    case 812:
        if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -240.0 ||
                phase_state_180 == 5 || (sequence_13e < 2 &&
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        emit_repeated_effects_for_owner_state(0, 2, 8)) ||
                (sequence_13e == 2 && reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 4)))
            goto retire;
        heading_12c = static_cast<float>(heading_12c + 18.0);
        switch (sequence_13e) {
        case 0:
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (scale_x_11c < 1.0) {
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            } else {
                scale_x_11c = 1.0f;
                scale_y_120 = scale_x_11c;
                next_sequence_block();
            }
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            break;
        case 1:
            parameters_340[1] = static_cast<float>(parameters_340[1] - 1.5);
            if (parameters_340[1] <= 0.0) {
                parameters_340[1] = 0.0f;
                ++state_364;
                if (counter_144 % 3 == 0) {
                    float copied[3] = {heading_12c, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        spawn_unparented_related_object(812, x_ec, y_f0,
                            static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (state_364 > 3) {
                    float copied[4];
                    copied[0] = parameters_340[0];
                    copied[1] = 0.0f;
                    copied[2] = 3.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        spawn_unparented_related_object(812, x_ec, y_f0,
                            static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                    for (float sector = 0.0f; sector < 8.0f; sector = static_cast<float>(sector + 1.0)) {
                        copied[0] = parameters_340[0];
                        copied[1] = 0.0f;
                        copied[2] = 2.0f;
                        copied[3] = static_cast<float>(sector * 45.0 + copied[0]);
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                            spawn_unparented_related_object(812, x_ec, y_f0,
                                static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 4);
                    }
                    --state_330;
                    return;
                }
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(30);
            if (phase_state_180 != 0)
                goto select_sequence_three;
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            break;
        case 2:
            parameters_340[1] = static_cast<float>(parameters_340[1] + 0.5);
            if (counter_144 % 5 == 0) {
                float copied[3] = {heading_12c, 0.0f, 4.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(812, x_ec, y_f0,
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            velocity_x_f4 = static_cast<float>(lookup_orientation_cosine_quantized_abs(parameters_340[3]) *
                state_370 + velocity_x_f4);
            velocity_y_f8 = static_cast<float>(lookup_orientation_sine_quantized_abs(parameters_340[3]) *
                state_370 + velocity_y_f8);
            state_370 = static_cast<float>(state_370 - 0.25);
            if (state_370 < 0.0f)
                state_370 = 0.0f;
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(3);
            if (phase_state_180 != 0) {
                select_sequence(3);
                return;
            }
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            break;
        case 3: case 4:
            if (alpha_113 < 15) {
                alpha_113 = 0;
                --state_330;
            } else {
                alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            }
            break;
        }
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
            --state_330;
        return;

    case 815:
        if (phase_state_180 == 5)
            goto retire;
        if (sequence_13e == 0 && counter_144 == 15) {
            float copied[3] = {0.0f, 0.0f, 4.0f};
            reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->
                spawn_owned_object_via_manager(815, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, reinterpret_cast<int>(copied), 3);
            reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(5);
            goto retire;
        }
        if (sequence_13e == 1) {
            scale_x_11c = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.1f) + scale_x_11c);
            scale_y_120 = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.1f) + scale_y_120);
            if (alpha_113 < 15)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
        }
        if (sequence_13e == 2 && counter_144 == 15) {
            select_sequence(1);
            return;
        }
        if (sequence_13e == 0 || sequence_13e == 2) {
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 -= velocity_y_f8;
        }
        if ((sequence_13e == 3 && (counter_144 > 120 || phase_index_184 == 0)) || sequence_13e == 4) {
            phase_index_184 = 0;
            if (alpha_113 < 10)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            channel_111 = static_cast<unsigned char>(channel_111 - 10);
            channel_112 = static_cast<unsigned char>(channel_112 - 10);
        }
        if (sequence_13e == 3) {
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->emit_repeated_effects_for_owner_state(1, 5, 10))
                goto retire;
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            if (static_cast<signed char>(phase_index_184) > 0) {
                if (phase_state_180 == 4 || phase_state_180 == 8)
                    phase_state_180 = 0;
                if (phase_state_180 != 0) {
                    ++state_364;
                    if (state_364 >= 6) {
                        state_364 = 0;
                        phase_state_180 = 0;
                    }
                }
            }
        }
        if (sequence_13e == 4 && counter_144 == 5) {
            float copied[3] = {0.0f, 0.0f, 3.0f};
            reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->
                spawn_owned_object_via_manager(815, x_ec, y_f0,
                    static_cast<unsigned char>(facing_104), 1, reinterpret_cast<int>(copied), 3);
        }
        if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -120.0)
            goto retire;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
            --state_330;
        return;

    case 816:
        if (phase_state_180 == 5)
            goto retire;
        switch (sequence_13e) {
        case 0:
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->emit_repeated_effects_for_owner_state(0, 1, 5))
                goto retire;
            if (state_364 == 0) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.5);
                if (counter_144 % 3 == 0) {
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        816, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (velocity_x_f4 > -1.0f)
                    velocity_x_f4 = -1.0f;
                alpha_113 = alpha_113 <= 235 ? static_cast<unsigned char>(alpha_113 + 20) : 255;
                if (alpha_113 == 255) {
                    phase_index_184 = 1;
                    state_364 = 1;
                }
            }
            if (state_364 == 1) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 + 2.5);
                if (velocity_x_f4 > -0.5f)
                    velocity_x_f4 = -0.5f;
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
                if (phase_state_180 == 1 ||
                        (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 525 &&
                         *reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 526) ||
                        *reinterpret_cast<short *>(fighter_owner_348 + 0x13e) >= 3)
                    phase_index_184 = 0;
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            }
            if (phase_index_184 == 0 && state_364 > 0) {
                if (state_364 == 1) {
                    velocity_x_f4 = 0.0f;
                    ++state_364;
                    float copied[3] = {0.0f, 0.0f, 2.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        816, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (alpha_113 < 40)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 40);
            }
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            break;
        case 4:
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->emit_repeated_effects_for_owner_state(0, 1, 5))
                goto retire;
            if (state_364 == 0) {
                if (velocity_y_f8 < 0.0f) {
                    velocity_y_f8 = static_cast<float>(velocity_y_f8 + 2.5);
                    if (velocity_y_f8 > -0.5f)
                        velocity_y_f8 = -0.5f;
                }
                if (velocity_y_f8 > 0.0f) {
                    velocity_y_f8 = static_cast<float>(velocity_y_f8 - 2.5);
                    if (velocity_y_f8 < 0.5f)
                        velocity_y_f8 = 0.5f;
                }
                if (counter_144 % 3 == 0) {
                    float copied[3] = {-heading_12c, 0.0f, 7.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        816, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                alpha_113 = alpha_113 <= 235 ? static_cast<unsigned char>(alpha_113 + 20) : 255;
                if (alpha_113 == 255) {
                    phase_index_184 = 1;
                    state_364 = 1;
                }
            }
            if (state_364 == 1) {
                if (velocity_y_f8 < 0.0f) {
                    velocity_y_f8 = static_cast<float>(velocity_y_f8 + 2.5);
                    if (velocity_y_f8 > -1.0f)
                        velocity_y_f8 = -1.0f;
                }
                if (velocity_y_f8 > 0.0f) {
                    velocity_y_f8 = static_cast<float>(velocity_y_f8 - 2.5);
                    if (velocity_y_f8 < 1.0f)
                        velocity_y_f8 = 1.0f;
                }
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
                if (phase_state_180 == 1 ||
                        (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 525 &&
                         *reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 526) ||
                        *reinterpret_cast<short *>(fighter_owner_348 + 0x13e) >= 3)
                    phase_index_184 = 0;
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            }
            if (phase_index_184 == 0 && state_364 > 0) {
                if (state_364 == 1) {
                    velocity_x_f4 = 0.0f;
                    ++state_364;
                    float copied[3] = {-heading_12c, 0.0f, 6.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        816, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (alpha_113 < 40)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 40);
            }
            y_f0 += velocity_y_f8;
            break;
        case 2: case 6:
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.02f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.02f));
            if (alpha_113 < 10)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        case 3: case 7:
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.01f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.01f));
            if (alpha_113 < 10)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            channel_111 = static_cast<unsigned char>(channel_111 - 10);
            channel_112 = static_cast<unsigned char>(channel_112 - 10);
            break;
        }
        goto advance_with_sequence_four_retirement;

    case 817: {
        if (phase_state_180 == 5)
            goto retire;
        switch (sequence_13e) {
        case 0:
            if (counter_144 >= 30) {
                const CharacterObjectEffectEmitter *target = reinterpret_cast<CharacterObjectEffectEmitter *>(this)->target_170;
                const float dx = target->x_ec - x_ec;
                if (fabs(dx) <= 120.0 && fabs(static_cast<float>(target->y_f0 - y_f0)) <= 10.0) {
                    select_sequence(6);
                    float copied[3] = {0.0f, 0.0f, 4.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                        817, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    for (int remaining = 14; remaining != 0; --remaining) {
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(25))) + 15.0);
                        copied[2] = 8.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                            817, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                    }
                    return;
                }
                const int remainder = counter_144 % 30;
                if (remainder == 0 || remainder == 2 || remainder == 4) {
                    float copied[3];
                    copied[0] = static_cast<float>(45.0 - static_cast<float>(static_cast<unsigned int>(selector_random_roll(270))));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(40)));
                    copied[2] = 3.0f;
                    const double origin_y = y_f0 + 50.0;
                    const double origin_x = x_ec + 100.0;
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->spawn_owned_object_via_manager(
                        817,
                        static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))),
                        static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(100)))),
                        static_cast<unsigned char>(facing_104), 1, reinterpret_cast<int>(copied), 3);
                }
            }

            if (counter_144 >= (static_cast<int>(*reinterpret_cast<signed char *>(fighter_owner_348 + 0x60d)) + 3) * 60)
                goto retire;
            if ((*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 530 ||
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 531) &&
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13e) == 0)
                goto retire;
            break;
        case 1:
            scale_x_11c = static_cast<float>(scale_x_11c + 0.5);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.5);
            if (channel_112 < 20) {
                if (alpha_113 < 20)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 20);
                channel_111 = channel_112 = 0;
            } else {
                channel_111 = static_cast<unsigned char>(channel_111 - 20);
                channel_112 = static_cast<unsigned char>(channel_112 - 20);
            }
            break;
        case 2: {
            const float jitter = static_cast<float>(
                static_cast<float>(static_cast<unsigned int>(selector_random_roll(100))) * static_cast<double>(0.01f));
            scale_x_11c = static_cast<float>(jitter + 1.0);
            scale_y_120 = scale_x_11c;
            if (!parent_object_34c)
                goto retire;
            x_ec = parent_object_34c->x_ec;
            y_f0 = parent_object_34c->y_f0;
            if (parent_object_34c->sequence_13e != 0 && parent_object_34c->sequence_13e != 9)
                goto retire;
            break;
        }
        case 3: {
            if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 3)
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(992, 4.0f, 60, 1, 2);
            parameters_340[0] += static_cast<float>(
                static_cast<unsigned int>(selector_random_roll(360)) - 180u);
            parameters_340[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(60)) + 40u);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->set_secondary_animation_alpha(static_cast<unsigned char>(state_370));
            if (!(state_370 >= 5.0f))
                goto retire;
            state_370 = static_cast<float>(state_370 - 5.0);
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            break;
        }
        case 4:
            if (!parent_object_34c)
                goto retire;
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            if (phase_state_180 != 0) {
                ++state_364;
                if (state_364 >= 6) {
                    state_364 = 0;
                    phase_state_180 = 0;
                }
            }
            if (static_cast<signed char>(phase_index_184) > 0 && parent_object_34c->state_364 != 1) {
                const float jitter = static_cast<float>(
                    static_cast<float>(static_cast<unsigned int>(selector_random_roll(10))) * static_cast<double>(0.01f));
                scale_x_11c = static_cast<float>(jitter + 1.0);
                scale_y_120 = scale_x_11c;
            } else {
                phase_index_184 = 0;
                scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.9f));
                scale_y_120 += state_370;
                state_370 = static_cast<float>(state_370 - static_cast<double>(0.1f));
                if (state_370 < 0.0f)
                    state_370 = 0.0f;
                alpha_113 = alpha_113 < 10 ? 0 : static_cast<unsigned char>(alpha_113 - 10);
            }
            break;
        case 6: case 7: {
            const float jitter = static_cast<float>(
                static_cast<float>(static_cast<unsigned int>(selector_random_roll(10))) * static_cast<double>(0.01f));
            scale_x_11c = static_cast<float>(jitter + 1.0);
            scale_y_120 = scale_x_11c;
            if (counter_144 < 40) {
                if (counter_144 % 10 == 0) {
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(16);
                    float copied[3] = {0.0f, 0.0f, 1.0f};
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->spawn_owned_object_via_manager(
                        817, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1, reinterpret_cast<int>(copied), 3);
                }
            } else {
                state_364 = 1;
                if (counter_144 >= 55) {
                    if (alpha_113 < 20)
                        goto retire;
                    alpha_113 = static_cast<unsigned char>(alpha_113 - 20);
                    channel_111 = static_cast<unsigned char>(channel_111 - 20);
                    channel_112 = static_cast<unsigned char>(channel_112 - 20);
                }
            }
            break;
        }
        case 8: {
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.9f));
            heading_12c += state_374;
            state_374 = static_cast<float>(state_374 * static_cast<double>(0.98f));
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            const signed char decrement = static_cast<signed char>(state_370);
            if (channel_112 >= decrement) {
                channel_111 = static_cast<unsigned char>(channel_111 - decrement);
                channel_112 = static_cast<unsigned char>(channel_112 - static_cast<unsigned char>(state_370));
            } else {
                if (alpha_113 < decrement)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - decrement);
                channel_111 = channel_112 = 0;
            }
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            break;
        }
        case 9:
            if (velocity_x_f4 > 0.0f) {
                velocity_x_f4 = static_cast<float>(velocity_x_f4 - 0.5);
                if (velocity_x_f4 < 0.0f)
                    velocity_x_f4 = 0.0f;
            } else {
                const CharacterObjectEffectEmitter *target = reinterpret_cast<CharacterObjectEffectEmitter *>(this)->target_170;
                const float dx = target->x_ec - x_ec;
                if (fabs(dx) <= 120.0 && fabs(static_cast<float>(target->y_f0 - y_f0)) <= 10.0) {
                    select_sequence(6);
                    float copied[3] = {0.0f, 0.0f, 4.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                        817, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    for (int remaining = 14; remaining != 0; --remaining) {
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(25))) + 15.0);
                        copied[2] = 8.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                            817, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                    }
                    return;
                }
                const int remainder = counter_144 % 30;
                if (remainder == 0 || remainder == 2 || remainder == 4) {
                    float copied[3];
                    copied[0] = static_cast<float>(45.0 - static_cast<float>(static_cast<unsigned int>(selector_random_roll(270))));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(40)));
                    copied[2] = 3.0f;
                    const double origin_y = y_f0 + 50.0;
                    const double origin_x = x_ec + 100.0;
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->spawn_owned_object_via_manager(
                        817,
                        static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))),
                        static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(100)))),
                        static_cast<unsigned char>(facing_104), 1, reinterpret_cast<int>(copied), 3);
                }
            }

            if (counter_144 >= (static_cast<int>(*reinterpret_cast<signed char *>(fighter_owner_348 + 0x60d)) + 3) * 60)
                goto retire;
            if ((*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 530 ||
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 531) &&
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13e) == 0)
                goto retire;
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            break;
        }
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1)
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
            --state_330;
        return;

    }

    case 821:
        if (phase_state_180 == 5 || (sequence_13e == 0 &&
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->emit_repeated_effects_for_owner_state(0, 0, 3)))
            goto retire;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(993, 4.0f, 5, 1, 2);
            phase_index_184 = 1;
            state_364 = 0;
        }
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1) {
            scale_x_11c = 2.0f;
            scale_y_120 = scale_x_11c;
        }
        if (sequence_13e == 0) {
            heading_12c = parameters_340[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(3);
            if (static_cast<signed char>(phase_index_184) <= 0 && phase_state_180 != 1) {
                float copied[3] = {-heading_12c, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    821, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                next_sequence_block();
                velocity_x_f4 = static_cast<float>(-velocity_x_f4 * 0.5);
                const float launch = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(60))) * static_cast<double>(0.1f));
                velocity_y_f8 = static_cast<float>(launch + 7.0);
                return;
            }
            if (y_f0 <= 0.0f) {
                float copied[3] = {-heading_12c, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    821, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                next_sequence_block();
                velocity_x_f4 = static_cast<float>(velocity_x_f4 * 0.25);
                const float launch = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(60))) * static_cast<double>(0.1f));
                velocity_y_f8 = static_cast<float>(launch + 7.0);
                return;
            }
        }
        if (sequence_13e <= 1) {
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
        }
        if (sequence_13e == 1) {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - 0.25);
            heading_12c = static_cast<float>(heading_12c + 35.0);
            if (alpha_113 < 5)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 5);
        }
        if (sequence_13e == 2) {
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.02f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.02f));
            if (alpha_113 < 10)
                goto clear_alpha_and_retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
        }
        if (sequence_13e == 3) {
            heading_12c = static_cast<float>(heading_12c - 35.0);
            x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0xec);
            y_f0 = static_cast<float>(*reinterpret_cast<float *>(fighter_owner_348 + 0xf0) + 100.0);
            // Target821 keeps these owner exits separate. The first two
            // retire through the shared812/821/822 tail; the last is private.
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 530 &&
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 531) {
                --state_330;
                return;
            }
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13e) == 3 &&
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x140) >= 4) {
                --state_330;
                return;
            }
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13e) >= 4) {
                --state_330;
                return;
            }
        }
        if (sequence_13e == 4) {
            x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0xec);
            y_f0 = static_cast<float>(*reinterpret_cast<float *>(fighter_owner_348 + 0xf0) + 100.0);
            heading_12c = static_cast<float>(heading_12c + 10.0);
        }
        goto bounded_projectile_advance;

    case 822:
        if (phase_state_180 == 5)
            goto retire;
        switch (sequence_13e) {
        case 0:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0) {
                packet_822_health[0] = 0.0f;
                packet_822_health[1] = 0.0f;
                packet_822_health[2] = 2.0f;
                packet_822_health[3] = 0.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    822, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(packet_822_health), 4);
                packet_822_health[2] = 3.0f;
                retiring_action = 822;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_822_health);
                retiring_words = 4;
                goto emit_retiring_world;
            }
            if (frame_140 == 0) {
                parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.85f));
                if (parameters_340[1] < 0.5f)
                    parameters_340[1] = 0.5f;
                if (counter_144 >= 15)
                    phase_index_184 = 0;
                if (parameters_340[3] <= counter_144) {
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    next_sequence_frame();
                    phase_index_184 = 1;
                    phase_state_180 = 0;
                    parameters_340[1] = 5.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 360.0f, 100.0f);
                    const float heading = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(30))) - 15.0 + parameters_340[0]);
                    parameters_340[0] = heading;
                    heading_12c = heading;
                    float copied[4] = {heading, 0.0f, 1.0f, 0.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                        822, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1,
                        reinterpret_cast<const unsigned *>(copied), 4);
                    return;
                }
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            }
            if (frame_140 == 1) {
                if (frame_timer_142 == 0)
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(992, 10.0f, 10, 1, 2);
                if (phase_state_180 != 0) {
                    packet_822_phase[0] = 0.0f;
                    packet_822_phase[1] = 0.0f;
                    packet_822_phase[2] = 2.0f;
                    packet_822_phase[3] = 0.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        822, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(packet_822_phase), 4);
                    packet_822_phase[2] = 3.0f;
                    retiring_action = 822;
                    retiring_packet = reinterpret_cast<const unsigned *>(packet_822_phase);
                    retiring_words = 4;
                    goto emit_retiring_world;
                }
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 0.1f, 100.0f);
                heading_12c = parameters_340[0];
                parameters_340[1] = static_cast<float>(parameters_340[1] + 1.5);
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
                if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 < -400.0 || y_f0 > 1080.0)
                    goto retire;
            }
            break;
        case 1:
            if (!parent_object_34c)
                goto retire;
            x_ec = parent_object_34c->x_ec;
            y_f0 = parent_object_34c->y_f0;
            heading_12c = parent_object_34c->heading_12c;
            scale_x_11c = static_cast<float>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(counter_144 * 10.0)) * static_cast<double>(0.1f) + 1.0);
            scale_y_120 = scale_x_11c;
            alpha_113 = alpha_113 <= 205 ? static_cast<unsigned char>(alpha_113 + 50) : 255;
            break;
        case 2: case 3:
            scale_x_11c = sequence_13e == 2 ?
                static_cast<float>(scale_x_11c - static_cast<double>(0.05f)) :
                static_cast<float>(scale_x_11c + static_cast<double>(0.2f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 20)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 20);
            channel_112 = static_cast<unsigned char>(channel_112 - 20);
            channel_111 = static_cast<unsigned char>(channel_111 - 20);
            break;
        case 4:
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c;
            heading_12c += state_370;
            if (frame_timer_142 == 0) {
                // Target publishes the last packet word after the first RNG call.
                float copied[4];
                copied[0] = 0.0f;
                copied[1] = 0.0f;
                copied[2] = static_cast<unsigned int>(selector_random_roll(100)) < 50u ? 5.0f : 6.0f;
                copied[3] = 0.0f;
                const double origin_y = y_f0 + 100.0;
                const double origin_x = x_ec + 100.0;
                // Actual arguments retain VC8's metadata/direction/Y/X preparation order.
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    822,
                    static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))),
                    static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))),
                    static_cast<unsigned char>(1 - 2 * (static_cast<unsigned int>(selector_random_roll(100)) > 50u)),
                    1, reinterpret_cast<const unsigned *>(copied), 4);
            }
            if (state_370 > 0.0f) {
                state_370 = static_cast<float>(state_370 - static_cast<double>(0.1f));
                if (state_370 < static_cast<double>(0.1f))
                    state_370 = 0.1f;
            }
            if (state_370 < 0.0f) {
                state_370 = static_cast<float>(state_370 + static_cast<double>(0.1f));
                if (state_370 > static_cast<double>(-0.1f))
                    state_370 = -0.1f;
            }
            if (channel_112 < 15) {
                --state_330;
                return;
            }
            channel_112 = static_cast<unsigned char>(channel_112 - 15);
            channel_111 = static_cast<unsigned char>(channel_111 - 15);
            alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
            velocity_y_f8 = static_cast<float>(velocity_y_f8 + static_cast<double>(0.1f));
            break;
        case 5: case 6:
            scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.99f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.005f));
            if (alpha_113 < 4)
                goto retire;
            channel_112 = static_cast<unsigned char>(channel_112 - 4);
            channel_111 = static_cast<unsigned char>(channel_111 - 4);
            alpha_113 = static_cast<unsigned char>(alpha_113 - 4);
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.1f));
            if (velocity_x_f4 < 1.0f)
                velocity_y_f8 = 1.0f;
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
            --state_330;
        return;

    case 825: {
        const short owner_action = *reinterpret_cast<short *>(fighter_owner_348 + 0x13c);
        if (sequence_13e == 0) {
            if (owner_action != 560 && owner_action != 561 && owner_action != 565 && owner_action != 566 && owner_action != 614)
                goto retire;
            x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0xec);
            y_f0 = *reinterpret_cast<float *>(fighter_owner_348 + 0xf0);
        }
        if (sequence_13e == 1 && owner_action != 614 && owner_action != 565 && owner_action != 566)
            goto retire;
        if (owner_action != 560 && owner_action != 561 && owner_action != 565 && owner_action != 566 && owner_action != 614)
            return;
        if (*reinterpret_cast<short *>(fighter_owner_348 + 0x186) != 0)
            return;
        if (sequence_13e == 1) {
            heading_12c = parameters_340[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], 35.0f);
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = static_cast<float>(scale_y_120 * static_cast<double>(0.85f));
        }
        goto advance_with_sequence_one_retirement;
    }

    case 848:
        switch (sequence_13e) {
        case 1:
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.025f));
            scale_y_120 = scale_x_11c;
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 302 ||
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x140) == 0)
                goto retire;
            break;
        case 3:
            heading_12c = static_cast<float>(heading_12c + 6.0);
            if (state_364 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->position_relative_to_owner_offsets(150, 65);
                if (counter_144 % 3 == 0) {
                    float copied[3] = {heading_12c, 0.0f, 4.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        848, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 306 ||
                        (*reinterpret_cast<short *>(fighter_owner_348 + 0x13e) == 0 &&
                         *reinterpret_cast<short *>(fighter_owner_348 + 0x140) == 0) ||
                        *reinterpret_cast<short *>(fighter_owner_348 + 0x13e) == 2) {
                    state_364 = 1;
                    return;
                }
            } else {
                if (alpha_113 < 20)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 20);
            }
            break;
        case 4:
            heading_12c = static_cast<float>(heading_12c - 5.0);
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.05f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 20)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 20);
            break;
        case 5:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 308)
                goto retire;
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->position_relative_to_owner_offsets(0, 0);
            break;
        }
        if (*reinterpret_cast<short *>(fighter_owner_348 + 0x186) != 0)
            return;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            goto retire;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && (sequence_13e == 2 || sequence_13e == 6))
            goto retire;
        return;

    case 850:
        if (phase_state_180 == 5)
            goto retire;
        if (phase_state_180 == 6) {
            phase_state_180 = 0;
            phase_index_184 = 1;
        }
        if (phase_state_180 != 0 && frame_140 < 2) {
            publish_battle_layout_scalar(2.0f);
            frame_timer_142 = 0;
            frame_140 = 2;
            angle_x_124 = 0.0f;
            angle_y_128 = 0.0f;
            heading_12c = 0.0f;
            scale_x_11c = 4.0f;
            scale_y_120 = 4.0f;
            float copied[3] = {0.0f, 0.0f, static_cast<float>(sequence_13e)};
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                860, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                reinterpret_cast<const unsigned *>(copied), 3);
            for (int remaining = 4; remaining != 0; --remaining) {
                copied[0] = static_cast<float>(mt19937_next_u32() % 360u);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    861, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
            }
            return;
        }
        if (frame_140 == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(
                0.0f, static_cast<float>(state_370 + 1.0), 100.0f);
            state_370 = static_cast<float>(state_370 + static_cast<double>(0.05f));
            if (state_370 >= 2.5f)
                state_370 = 2.5f;
            state_366 = static_cast<short>(state_366 + 15);
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            if (scale_x_11c > 1.0f) {
                scale_x_11c = 1.0f;
                scale_y_120 = 1.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(
                    static_cast<unsigned short>(993 - sequence_13e), 40.0f, 15, 1, 2);
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(state_366 * static_cast<double>(0.01f)));
        }
        if (frame_140 == 1) {
            state_366 = static_cast<short>(state_366 + 75);
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 2.0f, 100.0f);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(state_366 * static_cast<double>(0.01f)));
        }
        if (frame_140 == 2) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 0.0f;
            state_366 = 0;
            scale_x_11c = static_cast<float>(scale_x_11c - static_cast<double>(0.2f));
            scale_y_120 = static_cast<float>(scale_y_120 - static_cast<double>(0.2f));
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            if (scale_x_11c < 0.0f) {
                --state_330;
                return;
            }
        }
        reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
            set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(state_366 * static_cast<double>(0.01f)));
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        heading_12c = static_cast<float>(heading_12c + 10.0);
        if (x_ec > 1480.0 || x_ec < -200.0 || y_f0 > 1580.0 || y_f0 < -640.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 851:
        if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 604) {
            x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0xec);
            y_f0 = *reinterpret_cast<float *>(fighter_owner_348 + 0xf0);
        }
        if (phase_state_180 != 0) {
            state_364 = static_cast<short>(state_364 + 1);
            if (state_364 > 2) {
                state_364 = 0;
                phase_state_180 = 0;
            }
        }
        if (sequence_13e == 1) {
            if (counter_144 == 60) {
                float copied = 2.0f;
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->spawn_owned_object_via_manager(
                    851, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<int>(&copied), 1);
            }
            if (counter_144 > 60) {
                phase_index_184 = 0;
                state_368 = static_cast<short>(state_368 + 4);
                if (state_368 > 90)
                    goto retire;
                scale_x_11c = static_cast<float>(scale_x_11c * 0.75);
            }
        }
        if (sequence_13e == 2) {
            scale_x_11c = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.05f) + scale_x_11c);
            scale_y_120 = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.05f) + scale_y_120);
            if (alpha_113 <= 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
        }
        goto advance_and_retire_on_completion;

    case 852:
        if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 609) {
            x_ec = static_cast<float>(facing_104 * 228 + *reinterpret_cast<float *>(fighter_owner_348 + 0xec));
            y_f0 = static_cast<float>(*reinterpret_cast<float *>(fighter_owner_348 + 0xf0) + 93.0);
        }
        if (sequence_13e < 2) {
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 609 ||
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13e) > 1 || phase_index_184 == 0) {
                *reinterpret_cast<short *>(fighter_owner_348 + 0x738) = 1;
                scale_x_11c = 3.0f;
                scale_y_120 = 3.0f;
                select_sequence(2);
                return;
            }
            if (counter_144 % 10 == 0) {
                float copied[3] = {0.0f, 0.0f, 3.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    852, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
            }
        }
        heading_12c = static_cast<float>(heading_12c - 2.0);
        if (phase_state_180 == 6) {
            phase_index_184 = static_cast<unsigned char>(phase_index_184 + 1);
            phase_state_180 = 0;
        }
        if (phase_state_180 != 0) {
            state_364 = static_cast<short>(state_364 + 1);
            if (state_364 > 5) {
                state_364 = 0;
                phase_state_180 = 0;
            }
        }
        if (sequence_13e == 2) {
            scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.8f));
            scale_y_120 = static_cast<float>(scale_y_120 * static_cast<double>(0.8f));
            if (alpha_113 < 15)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
        }
        if (sequence_13e == 3) {
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            if (alpha_113 < 20)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 20);
        }
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 3)
            goto retire;
        return;

    case 853:
        if (phase_state_180 == 5)
            goto retire;
        reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
        if (frame_timer_142 == 0 && frame_140 == 1) {
            phase_state_180 = 0;
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(
                static_cast<unsigned short>(993 - sequence_13e), 40.0f, 15, 1, 2);
        }
        if (phase_state_180 != 0 && frame_140 < 2) {
            publish_battle_layout_scalar(2.0f);
            frame_timer_142 = 0;
            frame_140 = 2;
            angle_x_124 = 0.0f;
            angle_y_128 = 0.0f;
            heading_12c = 0.0f;
            scale_x_11c = 4.0f;
            scale_y_120 = 4.0f;
            float copied[3] = {0.0f, 0.0f, static_cast<float>(sequence_13e)};
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                860, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                reinterpret_cast<const unsigned *>(copied), 3);
            for (int remaining = 4; remaining != 0; --remaining) {
                copied[0] = static_cast<float>(mt19937_next_u32() % 360u);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    861, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
            }
            return;
        }
        if (frame_140 == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 2.0f, 100.0f);
            state_366 = static_cast<short>(state_366 - 50);
            if (state_366 < 0) {
                state_366 = 0;
                frame_140 = 1;
                frame_timer_142 = 0;
                scale_x_11c = 1.5f;
                scale_y_120 = 1.5f;
                return;
            }
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            if (scale_x_11c > 1.5f) {
                scale_x_11c = 1.5f;
                scale_y_120 = 1.5f;
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(state_366 * static_cast<double>(0.01f)));
        }
        if (frame_140 == 1) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 4.5f, 100.0f);
            state_366 = static_cast<short>(state_366 + 75);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(state_366 * static_cast<double>(0.01f)));
        }
        if (frame_140 == 2) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 0.0f;
            state_366 = 0;
            scale_x_11c = static_cast<float>(scale_x_11c - static_cast<double>(0.2f));
            scale_y_120 = static_cast<float>(scale_y_120 - static_cast<double>(0.2f));
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            if (scale_x_11c < 0.0f) {
                --state_330;
                return;
            }
        }
        reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
            set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(state_366 * static_cast<double>(0.01f)));
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        heading_12c = static_cast<float>(heading_12c + 10.0);
        if (x_ec > 1680.0 || x_ec < -400.0 || y_f0 > 1480.0 || y_f0 < -520.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 854:
        if (phase_state_180 == 5)
            goto retire;
        if (phase_state_180 == 6) {
            phase_state_180 = 0;
            phase_index_184 = 1;
        }
        if (phase_state_180 != 0 && frame_140 < 2) {
            publish_battle_layout_scalar(2.0f);
            frame_timer_142 = 0;
            frame_140 = 2;
            angle_x_124 = 0.0f;
            angle_y_128 = 0.0f;
            heading_12c = 0.0f;
            scale_x_11c = 4.0f;
            scale_y_120 = 4.0f;
            return;
        }
        if (frame_140 == 0) {
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.1f));
            if (scale_x_11c > 1.0f) {
                scale_x_11c = 1.0f;
                scale_y_120 = 1.0f;
                frame_timer_142 = 0;
                frame_140 = 1;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(
                    static_cast<unsigned short>(993 - sequence_13e), 40.0f, 15, 1, 2);
            }
        }
        if (frame_140 < 2) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 0.25f, 50.0f);
            state_366 = static_cast<short>(state_366 + 50);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(state_366 * static_cast<double>(0.01f) + 10.0));
        }
        if (frame_140 == 2) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 0.0f;
            state_366 = 0;
            scale_x_11c = static_cast<float>(scale_x_11c - static_cast<double>(0.2f));
            scale_y_120 = static_cast<float>(scale_y_120 - static_cast<double>(0.2f));
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            if (scale_x_11c < 0.0f) {
                --state_330;
                return;
            }
        }
        reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
            set_oriented_components_f0_f4(parameters_340[0], static_cast<float>(state_366 * static_cast<double>(0.01f)));
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        heading_12c = static_cast<float>(heading_12c + 10.0);
        if (x_ec > 1480.0 || x_ec < -200.0 || y_f0 > 1280.0 || y_f0 < -320.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 855:
        if (phase_state_180 == 5)
            goto retire;
        if (phase_state_180 == 6)
            phase_state_180 = 0;
        state_36a = static_cast<short>(state_36a + 5);
        if (state_36a > 90)
            state_36a = 90;
        scale_y_120 = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(state_36a)));
        scale_x_11c = static_cast<float>(4.0 - lookup_orientation_sine_quantized_abs(static_cast<float>(state_36a)) * 3.0);
        if (state_364 == 0) {
            velocity_x_f4 = 1.5f;
            velocity_y_f8 = 0.0f;
            if (counter_144 > 10) {
                scale_x_11c = 1.0f;
                scale_y_120 = scale_x_11c;
                state_368 = 0;
                state_366 = 0;
                state_364 = 1;
            }
        }
        if (state_364 == 1) {
            phase_index_184 = 1;
            if (phase_state_180 == 6)
                phase_state_180 = 0;
            if (phase_state_180 != 0) {
                state_368 = static_cast<short>(state_368 + 1);
                if (state_368 > 10) {
                    state_368 = 0;
                    phase_state_180 = 0;
                }
            }
            state_366 = static_cast<short>(state_366 + 1);
            if (state_366 > 300)
                state_364 = 2;
        }
        if (state_364 == 2) {
            phase_index_184 = 0;
            if (alpha_113 < 8)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 8);
            channel_112 = static_cast<unsigned char>(channel_112 - 8);
            channel_111 = static_cast<unsigned char>(channel_111 - 8);
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (x_ec > 1480.0 || x_ec < -200.0 || y_f0 > 1280.0 || y_f0 < -320.0) {
            --state_330;
            return;
        }
        goto advance_and_retire_on_completion;

    case 856:
        if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 606) {
            x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0xec);
            y_f0 = *reinterpret_cast<float *>(fighter_owner_348 + 0xf0);
        }
        if (phase_state_180 != 0) {
            state_364 = static_cast<short>(state_364 + 1);
            if (state_364 > 2) {
                state_364 = 0;
                phase_state_180 = 0;
            }
        }
        if (sequence_13e == 1) {
            if (counter_144 == 120 || (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 606 && counter_144 <= 119)) {
                counter_144 = 121;
                float copied = 2.0f;
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->spawn_owned_object_via_manager(
                    856, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<int>(&copied), 1);
            }
            if (counter_144 > 120) {
                phase_index_184 = 0;
                state_368 = static_cast<short>(state_368 + 4);
                if (state_368 > 90)
                    goto retire;
                scale_x_11c = static_cast<float>(scale_x_11c * 0.75);
            }
        }
        if (sequence_13e == 2) {
            scale_x_11c = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.05f) + scale_x_11c);
            scale_y_120 = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.05f) + scale_y_120);
            if (alpha_113 <= 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
        }
        goto advance_and_retire_on_completion;

    case 858:
        if (phase_state_180 == 5)
            goto retire;
        if (phase_state_180 == 6) {
            phase_state_180 = 0;
            phase_index_184 = static_cast<unsigned char>(phase_index_184 + 1);
        }
        if (phase_state_180 == 4 && static_cast<signed char>(phase_index_184) > 0)
            phase_state_180 = 0;
        if (sequence_13e == 0) {
            if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0)
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(parameters_340[0], 15.0f);
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - 0.5);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                state_364 = static_cast<short>(state_364 + 1);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                velocity_y_f8 = -velocity_y_f8;
                if (velocity_y_f8 > 17.5f)
                    velocity_y_f8 = 17.5f;
                phase_state_180 = 0;
                if (state_364 >= 2 && frame_140 == 0) {
                    set_sequence_frame(1);
                    phase_index_184 = 0;
                    counter_144 = 0;
                    return;
                }
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(992, 60.0f, 20, 1, 2);
            }
            if ((x_ec > 1260.0f && facing_104 == 1) || (x_ec < 20.0f && facing_104 == -1)) {
                facing_104 = static_cast<signed char>(-facing_104);
                phase_state_180 = 0;
            }
            if (frame_140 == 0 && phase_index_184 == 0) {
                next_sequence_frame();
                counter_144 = 0;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
            }
            if (frame_140 == 1 && counter_144 >= 30) {
                scale_x_11c = static_cast<float>(scale_x_11c - static_cast<double>(0.1f));
                scale_y_120 = static_cast<float>(scale_y_120 - static_cast<double>(0.1f));
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                if (scale_x_11c < 0.0f)
                    goto retire;
            }
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            heading_12c = static_cast<float>(heading_12c + 10.0);
        }
        if (sequence_13e == 1) {
            if (alpha_113 < 12)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 12);
            channel_112 = static_cast<unsigned char>(channel_112 - 12);
            channel_111 = static_cast<unsigned char>(channel_111 - 12);
        }
        if (sequence_13e == 2) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.25);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.25);
            if (alpha_113 < 20)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 20);
            channel_112 = static_cast<unsigned char>(channel_112 - 20);
            channel_111 = static_cast<unsigned char>(channel_111 - 20);
        }
        if (x_ec > 1480.0 || x_ec < -200.0 || y_f0 > 1280.0 || y_f0 < -320.0)
            goto retire;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (sequence_13e == 0 && frame_timer_142 == 0 && frame_140 == 1)
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
        return;

    case 859:
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 &&
                sequence_13e == 0) {
            phase_index_184 = 99;
            state_364 = 0;
        }
        if (sequence_13e == 0) {
            velocity_x_f4 = 0.0f;
            velocity_y_f8 = 0.0f;
        }
        if (sequence_13e == 1)
            velocity_x_f4 = static_cast<float>(velocity_x_f4 + static_cast<double>(0.05f));
        if (phase_state_180 == 6) {
            ++phase_index_184;
            phase_state_180 = 0;
        }
        if (phase_state_180 != 0) {
            ++state_364;
            if (state_364 > 5) {
                state_364 = 0;
                phase_state_180 = 0;
            }
        }
        heading_12c = static_cast<float>(heading_12c - 1.0);
        x_ec = static_cast<float>(static_cast<float>(facing_104) * velocity_x_f4 + x_ec);
        y_f0 += velocity_y_f8;
        if (x_ec > 1680.0 || x_ec < -400.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 860: {
        const double pulse = lookup_orientation_sine_quantized_abs(
            static_cast<float>(counter_144 * 6));
        scale_x_11c = static_cast<float>(pulse * 2.0 + 1.0);
        scale_y_120 = scale_x_11c;
        if (alpha_113 < 25)
            goto retire;
        alpha_113 = static_cast<unsigned char>(alpha_113 - 25);
        goto advance_with_sequence_retirement;
    }
    case 861: {
        const float *const parameters = parameters_340;
        heading_12c = parameters[0];
        reinterpret_cast<CharacterObjectRuntime *>(
            reinterpret_cast<unsigned char *>(this) + 4)->set_oriented_components_f0_f4(
                parameters[0], parameters[1]);
        scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
        scale_y_120 = static_cast<float>(scale_y_120 * static_cast<double>(0.8f));
        if (alpha_113 < 10)
            goto retire;
        alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
        x_ec = static_cast<float>(static_cast<float>(facing_104) * velocity_x_f4 + x_ec);
        y_f0 += velocity_y_f8;
        goto advance_with_sequence_retirement;
    }
    case 866:
        if (phase_state_180 != 0) {
            state_366 = static_cast<short>(state_366 + 1);
            if (state_366 > 15) {
                state_366 = 0;
                phase_state_180 = 0;
            }
        }
        if (sequence_13e <= 1) {
            switch (state_364) {
            case 0: {
                const unsigned char *const owner = fighter_owner_348;
                if (*reinterpret_cast<const short *>(owner + 0x13c) == 616) {
                    const short owner_sequence = *reinterpret_cast<const short *>(owner + 0x13e);
                    if (owner_sequence <= 2) {
                        x_ec = *reinterpret_cast<const float *>(owner + 0xec);
                    } else if (owner_sequence <= 5) {
                        if (owner_sequence == 3 && *reinterpret_cast<const short *>(owner + 0x140) == 1 &&
                                *reinterpret_cast<const short *>(owner + 0x142) == 0) {
                            scale_x_11c = 1.05f;
                            scale_y_120 = 0.95f;
                        }
                        if (scale_x_11c > 1.0f)
                            scale_x_11c = static_cast<float>(scale_x_11c - static_cast<double>(0.005f));
                        if (scale_y_120 < 1.0f)
                            scale_y_120 = static_cast<float>(scale_y_120 + static_cast<double>(0.005f));
                        if (*reinterpret_cast<const short *>(owner + 0x13e) == 5) {
                            if (state_368 % 30 == 0) {
                                float copied[3];
                                copied[2] = 2.0f;
                                for (float beam = 0.0f; beam < 8.0f; beam += 1.0f) {
                                    copied[0] = static_cast<float>(beam * 45.0);
                                    copied[1] = 30.0f;
                                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                        866, x_ec, stage_surface_height_at_x(reinterpret_cast<Fighter *>(this)),
                                        static_cast<unsigned char>(facing_104), 1,
                                        reinterpret_cast<const unsigned *>(copied), 3);
                                }
                            }
                            phase_index_184 = 99;
                            heading_12c = static_cast<float>(heading_12c + 2.0);
                        }
                        x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0xec);
                        y_f0 = static_cast<float>(*reinterpret_cast<float *>(fighter_owner_348 + 0xf0) - 150.0);
                        state_368 = static_cast<short>(state_368 + 1);
                    } else {
                        state_364 = 1;
                        phase_index_184 = 0;
                    }
                } else {
                    state_364 = 1;
                    phase_index_184 = 0;
                }
                break;
            }
            case 1:
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_112 = static_cast<unsigned char>(channel_112 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                break;
            }
        }
        if (sequence_13e == 2) {
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.01f));
            scale_y_120 = scale_x_11c;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            parameters_340[1] = static_cast<float>(parameters_340[1] - 1.5);
            if (parameters_340[1] < 0.5f)
                parameters_340[1] = 0.5f;
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 = static_cast<float>(velocity_y_f8 * static_cast<double>(0.2f) + y_f0);
            if (alpha_113 < 5)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 5);
        }
        goto advance_and_retire_on_completion;

    case 869:
        if (phase_state_180 == 5)
            goto retire;
        switch (sequence_13e) {
        case 0:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 669) {
                state_37c = static_cast<float>(state_37c - 0.5);
                if (state_37c <= -15.0)
                    state_37c = -15.0f;
                parameters_340[0] += state_37c;
                state_370 = static_cast<float>(state_370 + static_cast<double>(0.05f));
                if (state_370 >= 1.0f)
                    state_370 = 1.0f;
                heading_12c = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(counter_144 * 4.0)) * state_374);
                const float *const parameters = parameters_340;
                x_ec = static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0]) * parameters[1] +
                    *reinterpret_cast<float *>(fighter_owner_348 + 0xec));
                y_f0 = static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0]) * parameters_340[1] * state_370 +
                    (*reinterpret_cast<float *>(fighter_owner_348 + 0xf0) + 100.0));
                if (*reinterpret_cast<short *>(fighter_owner_348 + 0x13e) >= 2) {
                    packet_869_sequence[0] = 0.0f;
                    packet_869_sequence[1] = 0.0f;
                    packet_869_sequence[2] = 2.0f;
                    retiring_action = 869;
                    retiring_packet = reinterpret_cast<const unsigned *>(packet_869_sequence);
                    retiring_words = 3;
                    goto emit_retiring_world;
                }
            } else {
                state_37c = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(counter_144)) * 10.0);
                parameters_340[0] += state_37c;
                heading_12c = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(counter_144 * 4.0)) * state_374);
                const float *const parameters = parameters_340;
                x_ec = static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0]) * parameters[1] +
                    *reinterpret_cast<float *>(fighter_owner_348 + 0xec));
                y_f0 = static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0]) * parameters_340[1] * state_370 +
                    (*reinterpret_cast<float *>(fighter_owner_348 + 0xf0) + 100.0));
                if (lookup_orientation_sine_quantized_abs(parameters_340[0]) < 0.0)
                    direction_33c = 255;
                else
                    direction_33c = 1;
                parameters_340[1] += state_378;
                state_378 = static_cast<float>(state_378 - static_cast<double>(0.4f));
                if (state_378 < 0.0f)
                    state_378 = 0.0f;
            }
            if (state_364 == 0 && parameters_340[3] < *reinterpret_cast<short *>(fighter_owner_348 + 0x7ca)) {
                state_364 = 1;
                float copied[3] = {0.0f, 0.0f, 1.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                    869, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 2.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    869, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(23);
            }
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x7c8) <= 0 &&
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 669) {
                packet_869_owner[0] = 0.0f;
                packet_869_owner[1] = 0.0f;
                packet_869_owner[2] = 2.0f;
                retiring_action = 869;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_869_owner);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            break;
        case 1:
            if (!parent_object_34c)
                goto retire;
            x_ec = parent_object_34c->x_ec;
            y_f0 = parent_object_34c->y_f0;
            alpha_113 = static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(parent_object_34c->counter_144 * 3.0)) * 127.0 + 127.0);
            channel_112 = static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(parent_object_34c->counter_144 * 3.0)) * 127.0 + 127.0);
            channel_111 = static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(parent_object_34c->counter_144 * 3.0)) * 127.0 + 127.0);
            break;
        case 2:
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.15f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 15)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
            channel_111 = static_cast<unsigned char>(channel_111 - 15);
            channel_112 = static_cast<unsigned char>(channel_112 - 15);
            break;
        case 3:
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            x_ec += static_cast<float>(facing_104) * velocity_x_f4;
            y_f0 += velocity_y_f8;
            if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -200.0) {
                --state_330;
                return;
            }
            break;
        case 4:
            scale_x_11c = static_cast<float>(scale_x_11c + 0.5);
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        case 5:
            heading_12c += state_370;
            state_370 = static_cast<float>(state_370 * static_cast<double>(0.95f));
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.15f));
            scale_y_120 = static_cast<float>(scale_y_120 * static_cast<double>(0.97f));
            if (counter_144 < 15 || alpha_113 < 15)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 15);
            break;
        }
        goto advance_and_retire_on_completion;

    case 980:
        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
            update_ping_pong_motion_and_periodic_spawn();
        goto advance_and_retire_on_completion;

    case 998:
        heading_12c = static_cast<float>(heading_12c + 5.0);
        if (sequence_13e == 0) {
            // The owner is reread after the virtual sequence operation below.
            const unsigned char *const owner = fighter_owner_348;
            if (*reinterpret_cast<const short *>(owner + 0x13c) > 153 &&
                    *reinterpret_cast<const short *>(owner + 0x13c) < 158) {
                x_ec = static_cast<float>(facing_104 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                y_f0 = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 60.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) > 149 &&
                    *reinterpret_cast<const short *>(owner + 0x13c) < 154) {
                x_ec = static_cast<float>(facing_104 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                y_f0 = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 94.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) == 158) {
                x_ec = static_cast<float>(facing_104 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                y_f0 = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 100.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) < 150 ||
                    *reinterpret_cast<const short *>(owner + 0x13c) > 158) {
                next_sequence_block();
                fighter_owner_348[0x751] = 0;
            }
        }
        if (sequence_13e == 1) {
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
        }
        goto advance_and_retire_on_completion;

    case 900: {
        switch (sequence_13e) {
        case 0:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0) {
                dead_sequence_zero[0] = 0.0f;
                dead_sequence_zero[1] = 0.0f;
                dead_sequence_zero[2] = 2.0f;
                retiring_packet = reinterpret_cast<const unsigned *>(dead_sequence_zero);
                retiring_words = 3;
                retiring_action = 900;
                goto emit_retiring_world;
            }
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (counter_144 >= 40) {
                completed_sequence_zero[0] = parameters_340[0];
                completed_sequence_zero[1] = 0.0f;
                completed_sequence_zero[2] = 3.0f;
                const int match_identifier = g_match_identifier;
                if (match_identifier == 3)
                    completed_sequence_zero[3] = 50.0f;
                else if (match_identifier == 2)
                    completed_sequence_zero[3] = 25.0f;
                else if (match_identifier == 1)
                    completed_sequence_zero[3] = 15.0f;
                else if (match_identifier == 0)
                    completed_sequence_zero[3] = 8.0f;
                retiring_packet = reinterpret_cast<const unsigned *>(completed_sequence_zero);
                retiring_words = 4;
                retiring_action = 900;
                goto emit_retiring_world;
            }
            break;
        case 1:
            if (phase_state_180 != 0 || *reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0) {
                dead_sequence_one[0] = 0.0f;
                dead_sequence_one[1] = 0.0f;
                dead_sequence_one[2] = 2.0f;
                retiring_packet = reinterpret_cast<const unsigned *>(dead_sequence_one);
                retiring_words = 3;
                retiring_action = 900;
                goto emit_retiring_world;
            }
            parameters_340[1] = static_cast<float>(parameters_340[1] + static_cast<double>(0.4f));
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 < -200.0 || y_f0 > 900.0)
                goto retire;
            break;
        case 2:
            scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.9f));
            scale_y_120 = scale_x_11c;
            if (counter_144 >= 5) {
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_110 = static_cast<unsigned char>(channel_110 - 10);
            }
            break;
        case 3:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0)
                goto retire;
            if (counter_144 % 6 == 0) {
                float copied[3] = {parameters_340[0], 0.0f, 1.0f};
                const float radius = static_cast<float>(state_370 * 40.0);
                if (state_370 == 0.0f) {
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        900, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                } else {
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        900, static_cast<float>(lookup_orientation_cosine_quantized_abs(
                            static_cast<float>(90.0 - copied[0])) * radius * static_cast<float>(facing_104) + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(
                            static_cast<float>(90.0 - copied[0])) * radius + y_f0),
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        900, static_cast<float>(lookup_orientation_cosine_quantized_abs(
                            static_cast<float>(-copied[0] - 90.0)) * radius * static_cast<float>(facing_104) + x_ec),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(
                            static_cast<float>(-copied[0] - 90.0)) * radius + y_f0),
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                state_370 = static_cast<float>(state_370 + 1.0);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(0);
            }
            if (parameters_340[3] <= state_370)
                goto retire;
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        goto advance_and_retire_on_completion;

    }

    case 901:
        switch (sequence_13e) {
        case 0: {
            parameters_340[0] = static_cast<float>(parameters_340[0] + 3.0);
            parameters_340[1] += state_370;
            state_370 = static_cast<float>(state_370 * static_cast<double>(0.9f));
            if (lookup_orientation_sine_quantized_abs(-parameters_340[0]) > 0.0)
                direction_33c = 255;
            else
                direction_33c = 1;
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0 || value_174 <= -1500) {
                float copied[3] = {0.0f, 0.0f, 4.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[1] = 0.75f;
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                for (int particle = 0; particle < 8; ++particle) {
                    copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(20)) + 5.0);
                    copied[2] = 5.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                --state_330;
                return;
            }
            heading_12c = static_cast<float>(heading_12c + 2.0);
            x_ec = static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters_340[0]) *
                parameters_340[1] * static_cast<float>(facing_104) + *reinterpret_cast<float *>(fighter_owner_348 + 0xec));
            y_f0 = static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters_340[0]) *
                parameters_340[1] * static_cast<double>(0.2f) + (*reinterpret_cast<float *>(fighter_owner_348 + 0xf0) + 100.0));
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x730) == 1) {
                float copied[4] = {0.0f, 0.75f, 3.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[0] = parameters_340[0];
                copied[1] = static_cast<float>(value_174 * 0.25);
                copied[2] = 1.0f;
                copied[3] = parameters_340[3];
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 4);
                --state_330;
                return;
            }
            break;
        }
        case 1: {
            const unsigned *final_packet;
            if (phase_state_180 == 6) {
                phase_index_184 = static_cast<unsigned char>(phase_index_184 + 1);
                phase_state_180 = 0;
                value_174 = static_cast<short>(value_174 - 20);
            }
            const float intensity = static_cast<float>((value_174 + 1000) / 1000.0);
            const unsigned char color = static_cast<unsigned char>(static_cast<int>(intensity * 255.0));
            channel_111 = color;
            channel_110 = color;
            if (phase_state_180 != 0 && state_366 == 0) {
                state_366 = 1;
                value_174 = static_cast<short>(value_174 - 500);
            }
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0 || value_174 <= -1000) {
                health_packet[0] = 0.0f;
                health_packet[1] = 0.0f;
                health_packet[2] = 4.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(health_packet), 3);
                for (int particle = 0; particle < 8; ++particle) {
                    health_packet[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    health_packet[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(20)) + 5.0);
                    health_packet[2] = 5.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(health_packet), 3);
                }
                health_packet[1] = 0.75f;
                health_packet[2] = 3.0f;
                final_packet = reinterpret_cast<const unsigned *>(health_packet);
                goto emit_901_burst_tail;
            }
            heading_12c += state_370;
            if ((static_cast<float>(facing_104) * velocity_x_f4 > 0.0 && x_ec > 1240.0f) ||
                    (static_cast<float>(facing_104) * velocity_x_f4 < 0.0 && x_ec < 40.0f))
                facing_104 = static_cast<signed char>(-facing_104);
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - 0.5);
            if (y_f0 <= 80.0f && velocity_y_f8 < 0.0f) {
                if (parameters_340[3] > state_364) {
                    state_364 = static_cast<short>(state_364 + 1);
                    state_366 = 0;
                    value_174 = static_cast<short>(value_174 - 250);
                    phase_index_184 = 1;
                    phase_state_180 = 0;
                    velocity_y_f8 = static_cast<float>(-velocity_y_f8 * static_cast<double>(0.95f));
                    float copied[3] = {0.0f, 0.0f, 6.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        901, x_ec, stage_surface_height_at_x(reinterpret_cast<Fighter *>(this)),
                        static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                } else {
                    exhausted_packet[0] = 0.0f;
                    exhausted_packet[1] = 0.0f;
                    exhausted_packet[2] = 4.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(exhausted_packet), 3);
                    for (int particle = 0; particle < 8; ++particle) {
                        exhausted_packet[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        exhausted_packet[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(20)) + 5.0);
                        exhausted_packet[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            901, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(exhausted_packet), 3);
                    }
                    exhausted_packet[1] = 0.75f;
                    exhausted_packet[2] = 3.0f;
                    final_packet = reinterpret_cast<const unsigned *>(exhausted_packet);
                    goto emit_901_burst_tail;
                }
            }
            break;
        emit_901_burst_tail:
            retiring_action = 901;
            retiring_packet = final_packet;
            retiring_words = 3;
            goto emit_retiring_world;
        }
        case 3:
            scale_x_11c += parameters_340[1];
            scale_y_120 = scale_x_11c;
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.95f));
            if (counter_144 >= 5) {
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_112 = static_cast<unsigned char>(channel_112 - 10);
            }
            break;
        case 4:
            scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.9f));
            scale_y_120 = scale_x_11c;
            if (counter_144 >= 5) {
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_112 = static_cast<unsigned char>(channel_112 - 10);
            }
            break;
        case 5:
            scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.99f));
            scale_y_120 = scale_x_11c;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.95f));
            if (counter_144 >= 5) {
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_112 = static_cast<unsigned char>(channel_112 - 10);
            }
            break;
        case 6:
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.05f));
            scale_y_120 = scale_x_11c;
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.95f));
            if (counter_144 >= 0) {
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_112 = static_cast<unsigned char>(channel_112 - 10);
            }
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        return;

    case 902:
        switch (sequence_13e) {
        case 0:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0)
                state_364 = 2;
            if (state_364 == 0) {
                state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.2f) + 5.0);
                scale_x_11c = static_cast<float>((1.0 - state_370) * state_374);
                scale_y_120 = scale_x_11c;
                state_370 = static_cast<float>(state_370 * static_cast<double>(0.95f));
                reinterpret_cast<ReimuOwnerBoundaryView *>(fighter_owner_348)->x_lower_0 = static_cast<float>(x_ec - scale_x_11c * 45.0);
                reinterpret_cast<ReimuOwnerBoundaryView *>(fighter_owner_348)->x_upper_0 = static_cast<float>(scale_x_11c * 45.0 + x_ec);
                reinterpret_cast<ReimuOwnerBoundaryView *>(fighter_owner_348)->y_upper_0 = static_cast<float>(scale_x_11c * 45.0 + y_f0);
                reinterpret_cast<ReimuOwnerBoundaryView *>(fighter_owner_348)->y_lower_0 = static_cast<float>(y_f0 - scale_x_11c * 45.0);
            }
fade_902:
            if (state_364 == 2) {
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = scale_x_11c;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_110 = static_cast<unsigned char>(channel_110 - 10);
            }
            break;
        case 1:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0)
                state_364 = 2;
            if (state_364 == 0) {
                state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(counter_144 * 2.0)) * 0.5 + 10.0);
                scale_x_11c = static_cast<float>((1.0 - state_370) * state_374);
                scale_y_120 = scale_x_11c;
                state_370 = static_cast<float>(state_370 * static_cast<double>(0.95f));
                reinterpret_cast<ReimuOwnerBoundaryView *>(fighter_owner_348)->x_lower_1 = static_cast<float>(x_ec - scale_x_11c * 45.0);
                reinterpret_cast<ReimuOwnerBoundaryView *>(fighter_owner_348)->x_upper_1 = static_cast<float>(scale_x_11c * 45.0 + x_ec);
                reinterpret_cast<ReimuOwnerBoundaryView *>(fighter_owner_348)->y_upper_1 = static_cast<float>(scale_x_11c * 45.0 + y_f0);
                reinterpret_cast<ReimuOwnerBoundaryView *>(fighter_owner_348)->y_lower_1 = static_cast<float>(y_f0 - scale_x_11c * 45.0);
            }
            goto fade_902;
        case 2:
            if (phase_state_180 != 0 || *reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0) {
                packet_902_retirement[0] = 0.0f;
                packet_902_retirement[1] = 0.0f;
                packet_902_retirement[2] = 3.0f;
                retiring_action = 902;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_902_retirement);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            heading_12c = atan2_degrees(velocity_y_f8,
                static_cast<float>(static_cast<float>(facing_104) * velocity_x_f4));
            if (state_364 == 0) {
                if (velocity_y_f8 > 0.0 && y_f0 > *reinterpret_cast<float *>(fighter_owner_348 + 0x7b8)) {
                    velocity_y_f8 = -velocity_y_f8;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    y_f0 = *reinterpret_cast<float *>(fighter_owner_348 + 0x7c0);
                    state_364 = 1;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (velocity_y_f8 < 0.0 && y_f0 < *reinterpret_cast<float *>(fighter_owner_348 + 0x7c0)) {
                    velocity_y_f8 = -velocity_y_f8;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    y_f0 = *reinterpret_cast<float *>(fighter_owner_348 + 0x7b8);
                    state_364 = 1;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (static_cast<float>(facing_104) * velocity_x_f4 > 0.0 && x_ec > *reinterpret_cast<float *>(fighter_owner_348 + 0x7b0)) {
                    velocity_x_f4 = -velocity_x_f4;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0x7a8);
                    state_364 = 1;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (static_cast<float>(facing_104) * velocity_x_f4 < 0.0 && x_ec < *reinterpret_cast<float *>(fighter_owner_348 + 0x7a8)) {
                    velocity_x_f4 = -velocity_x_f4;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0x7b0);
                    state_364 = 1;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
            }
            if ((g_match_identifier == 3 || g_match_identifier == 2) && state_364 == 1) {
                if (velocity_y_f8 > 0.0 && y_f0 > *reinterpret_cast<float *>(fighter_owner_348 + 0x7bc)) {
                    velocity_y_f8 = -velocity_y_f8;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    y_f0 = *reinterpret_cast<float *>(fighter_owner_348 + 0x7c4);
                    state_364 = 2;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (velocity_y_f8 < 0.0 && y_f0 < *reinterpret_cast<float *>(fighter_owner_348 + 0x7c4)) {
                    velocity_y_f8 = -velocity_y_f8;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    y_f0 = *reinterpret_cast<float *>(fighter_owner_348 + 0x7bc);
                    state_364 = 2;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (static_cast<float>(facing_104) * velocity_x_f4 > 0.0 && x_ec > *reinterpret_cast<float *>(fighter_owner_348 + 0x7b4)) {
                    velocity_x_f4 = -velocity_x_f4;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0x7ac);
                    state_364 = 2;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (static_cast<float>(facing_104) * velocity_x_f4 < 0.0 && x_ec < *reinterpret_cast<float *>(fighter_owner_348 + 0x7ac)) {
                    velocity_x_f4 = -velocity_x_f4;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0x7b4);
                    state_364 = 2;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
            }
            if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 < -200.0 || y_f0 > 900.0)
                goto retire;
            break;
        case 3:
            scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.9f));
            scale_y_120 = scale_x_11c;
            if (counter_144 >= 5) {
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            }
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        goto advance_and_retire_on_completion;

    case 903:
        if (phase_state_180 == 5)
            goto retire;
        switch (sequence_13e) {
        case 0: case 1: case 2:
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            heading_12c = static_cast<float>(heading_12c + 10.0);
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0) {
                packet_903_health[0] = 0.0f;
                packet_903_health[1] = 0.0f;
                packet_903_health[2] = static_cast<float>(sequence_13e + 6.0);
                retiring_action = 903;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_903_health);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            if (state_364 == 0) {
                parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.95f));
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
                if (counter_144 >= 40) {
                    phase_index_184 = 1;
                    phase_state_180 = 0;
                    velocity_x_f4 = 0.0f;
                    velocity_y_f8 = 0.0f;
                    state_364 = 1;
                    counter_144 = 0;
                }
                if (counter_144 % 10 == 0) {
                    float copied[3];
                    copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(30)) * static_cast<double>(0.1f) + 2.0);
                    copied[2] = static_cast<float>(sequence_13e + 3.0);
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        903, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
            }
            if (state_364 == 1 && *reinterpret_cast<short *>(fighter_owner_348 + 0x13c) == 740 &&
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13e) == 6) {
                const int axis = selector_random_roll(2);
                const float width = static_cast<float>(static_cast<unsigned int>(selector_random_roll(120)) * static_cast<double>(0.1f));
                if (g_match_identifier == 1) {
                    for (float sector = 0.0f; sector < 2.0f; sector += 1.0f) {
                        packet_903_burst[0] = static_cast<float>(sector * 180.0);
                        if (axis == 0)
                            packet_903_burst[0] = static_cast<float>(packet_903_burst[0] + 90.0);
                        packet_903_burst[1] = width;
                        packet_903_burst[2] = static_cast<float>(sequence_13e);
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            904, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(packet_903_burst), 3);
                    }
                } else if (g_match_identifier == 2) {
                    for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                        packet_903_burst[0] = static_cast<float>(sector * 90.0);
                        packet_903_burst[1] = width;
                        packet_903_burst[2] = static_cast<float>(sequence_13e);
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            904, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(packet_903_burst), 3);
                    }
                } else if (g_match_identifier == 3) {
                    for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                        packet_903_burst[0] = static_cast<float>(sector * 90.0);
                        packet_903_burst[1] = width;
                        packet_903_burst[2] = static_cast<float>(sequence_13e);
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            904, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(packet_903_burst), 3);
                    }
                }
                packet_903_burst[0] = 0.0f;
                packet_903_burst[1] = 0.5f;
                packet_903_burst[2] = static_cast<float>(sequence_13e + 6.0);
                retiring_action = 903;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_903_burst);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            break;
        case 3: case 4: case 5:
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.99f));
            scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.9f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        case 6: case 7: case 8:
            scale_x_11c += parameters_340[1];
            scale_y_120 = scale_x_11c;
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.92f));
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (x_ec > 1680.0 || x_ec < -400.0 || y_f0 > 1480.0 || y_f0 < -520.0) {
            --state_330;
            return;
        }
        goto advance_and_retire_on_completion;

    case 904:
        if (phase_state_180 == 5)
            goto retire;
        switch (sequence_13e) {
        case 0: case 1: case 2:
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            heading_12c = static_cast<float>(heading_12c + 10.0);
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0 ||
                    static_cast<signed char>(phase_index_184) <= 0) {
                float copied[3];
                for (int particle = 0; particle < 4; ++particle) {
                    copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(100)) * static_cast<double>(0.1f) + 5.0);
                    copied[2] = static_cast<float>(sequence_13e + 3.0);
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        904, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                goto retire;
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            parameters_340[1] = static_cast<float>(parameters_340[1] + static_cast<double>(0.15f));
            if (counter_144 % 10 == 0) {
                float copied[3];
                copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(30)) * static_cast<double>(0.1f) + 2.0);
                copied[2] = static_cast<float>(sequence_13e + 3.0);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    903, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
            }
            break;
        case 3: case 4: case 5:
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.98f));
            scale_x_11c = static_cast<float>(scale_x_11c * static_cast<double>(0.9f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (x_ec > 1680.0 || x_ec < -400.0 || y_f0 > 1480.0 || y_f0 < -520.0) {
            --state_330;
            return;
        }
        goto advance_and_retire_on_completion;

    case 905:
        switch (sequence_13e) {
        case 0:
            heading_12c += parameters_340[1];
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 7500 && state_364 != 2) {
                state_364 = 2;
                float copied[3] = {heading_12c, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    905, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    905, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_indexed_event_member(38);
            }
            if (state_364 == 0) {
                state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.2f) + 1.0);
                scale_x_11c = static_cast<float>((1.0 - state_370) * state_374);
                scale_y_120 = scale_x_11c;
                state_370 = static_cast<float>(state_370 * static_cast<double>(0.95f));
                if (*reinterpret_cast<short *>(fighter_owner_348 + 0x736) == 0) {
                    counter_144 = 0;
                    state_364 = 1;
                }
            }
            if (state_364 == 1 && *reinterpret_cast<short *>(fighter_owner_348 + 0x738) == 0) {
                // Four packets remain alive through the shared second spawn/wave.
                // docs/REIMU_OBJECT_905_PACKET_JOIN_2026_10_21.md.
                float mode0_packet[3], mode1_packet[3];
                float mode2_packet[3], mode3_packet[3];
                float *completed_packet = 0;
                switch (g_match_identifier) {
                case 3:
                    if (counter_144 % 150 == 0) {
                        mode3_packet[0] = heading_12c;
                        mode3_packet[1] = 2.0f;
                        mode3_packet[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            905, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(mode3_packet), 3);
                        mode3_packet[2] = 5.0f;
                        completed_packet = mode3_packet;
                    }
                    break;
                case 2:
                    if (counter_144 % 210 == 0) {
                        mode2_packet[0] = heading_12c;
                        mode2_packet[1] = 2.0f;
                        mode2_packet[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            905, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(mode2_packet), 3);
                        mode2_packet[2] = 5.0f;
                        completed_packet = mode2_packet;
                    }
                    break;
                case 1:
                    if (counter_144 % 240 == 0) {
                        mode1_packet[0] = heading_12c;
                        mode1_packet[1] = 2.0f;
                        mode1_packet[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            905, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(mode1_packet), 3);
                        mode1_packet[2] = 5.0f;
                        completed_packet = mode1_packet;
                    }
                    break;
                case 0:
                    if (counter_144 % 270 == 0) {
                        mode0_packet[0] = heading_12c;
                        mode0_packet[1] = 2.0f;
                        mode0_packet[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            905, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(mode0_packet), 3);
                        mode0_packet[2] = 5.0f;
                        completed_packet = mode0_packet;
                    }
                    break;
                }
                if (completed_packet) {
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        905, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(completed_packet), 3);
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                }
            }
            if (state_364 == 2) {
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = scale_x_11c;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_110 = static_cast<unsigned char>(channel_110 - 10);
            }
            break;
        case 2:
            if (channel_111 < 5) {
                channel_111 = 0;
                channel_112 = 0;
            } else {
                channel_111 = static_cast<unsigned char>(channel_111 - 5);
                channel_112 = static_cast<unsigned char>(channel_112 - 5);
            }
            break;
        case 3:
            heading_12c = static_cast<float>(heading_12c + 8.0);
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.2f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        case 4:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 7500)
                state_364 = 1;
            parameters_340[1] = static_cast<float>(parameters_340[1] + static_cast<double>(0.1f));
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            heading_12c = static_cast<float>(heading_12c + 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            if (phase_state_180 != 0) {
                if (state_366 >= 10) {
                    state_366 = 0;
                    phase_state_180 = 0;
                    phase_index_184 = 1;
                }
                state_366 = static_cast<short>(state_366 + 1);
            }
            if (state_364 == 1) {
                phase_index_184 = 0;
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.05f));
                scale_y_120 = scale_x_11c;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            }
            if (x_ec >= 1800.0 || x_ec < -520.0f || y_f0 > 1400.0f || y_f0 < -800.0)
                goto retire;
            break;
        case 5:
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        goto advance_with_sequence_three_retirement;

    case 906:
        switch (sequence_13e) {
        case 0:
            heading_12c += parameters_340[1];
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 5000 && state_364 != 2) {
                state_364 = 2;
                float copied[3] = {heading_12c, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_indexed_event_member(38);
            }
            if (state_364 == 0) {
                state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.2f) + 1.0);
                scale_x_11c = static_cast<float>((1.0 - state_370) * state_374);
                scale_y_120 = scale_x_11c;
                state_370 = static_cast<float>(state_370 * static_cast<double>(0.95f));
                if (*reinterpret_cast<short *>(fighter_owner_348 + 0x736) == 0) {
                    counter_144 = 0;
                    state_364 = 1;
                }
            }
            if (state_364 == 1 && *reinterpret_cast<short *>(fighter_owner_348 + 0x738) == 1) {
                switch (g_match_identifier) {
                case 3:
                    if (counter_144 % 135 == 0) {
                        float copied[3];
                        for (float sector = 0.0f; sector < 8.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 45.0 + heading_12c);
                            copied[1] = 10.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        copied[0] = heading_12c;
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 2:
                    if (counter_144 % 165 == 0) {
                        float copied[3];
                        for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 90.0 + heading_12c);
                            copied[1] = 10.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        copied[0] = heading_12c;
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 1:
                    if (counter_144 % 195 == 0) {
                        float copied[3];
                        for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 90.0 + heading_12c);
                            copied[1] = 10.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        copied[0] = heading_12c;
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 0:
                    if (counter_144 % 225 == 0) {
                        float copied[3];
                        for (float sector = 0.0f; sector < 2.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 180.0 + heading_12c);
                            copied[1] = 10.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        copied[0] = heading_12c;
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            906, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                }
            }
            if (state_364 == 2) {
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = scale_x_11c;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_110 = static_cast<unsigned char>(channel_110 - 10);
            }
            break;
        case 2:
            if (channel_111 < 5) {
                channel_111 = 0;
                channel_112 = 0;
            } else {
                channel_111 = static_cast<unsigned char>(channel_111 - 5);
                channel_112 = static_cast<unsigned char>(channel_112 - 5);
            }
            break;
        case 3:
            heading_12c = static_cast<float>(heading_12c + 8.0);
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.2f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        case 4:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 5000)
                state_364 = 2;
            if (state_364 == 0) {
                if (alpha_113 < 250)
                    alpha_113 = static_cast<unsigned char>(alpha_113 + 5);
                else {
                    alpha_113 = 255;
                    phase_index_184 = 1;
                    state_364 = 1;
                }
            }
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.05f));
            if (scale_x_11c > 1.0f)
                scale_x_11c = 1.0f;
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.95f));
            if (parameters_340[1] <= 4.0f)
                parameters_340[1] = 4.0f;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            if (phase_state_180 != 0) {
                if (state_366 >= 10) {
                    state_366 = 0;
                    phase_state_180 = 0;
                    phase_index_184 = 1;
                }
                state_366 = static_cast<short>(state_366 + 1);
            }
            if (state_364 == 2) {
                phase_index_184 = 0;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_112 = static_cast<unsigned char>(channel_112 - 10);
            }
            if (x_ec >= 1800.0 || x_ec < -520.0f || y_f0 > 1400.0f || y_f0 < -800.0)
                state_364 = 2;
            break;
        case 5:
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 3)
            goto retire;
        return;

    case 907:
        switch (sequence_13e) {
        case 0:
            heading_12c += parameters_340[1];
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 2500 && state_364 != 2) {
                state_364 = 2;
                float copied[3] = {heading_12c, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    907, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    907, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_indexed_event_member(38);
            }
            if (state_364 == 0) {
                state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.2f) + 1.0);
                scale_x_11c = static_cast<float>((1.0 - state_370) * state_374);
                scale_y_120 = scale_x_11c;
                state_370 = static_cast<float>(state_370 * static_cast<double>(0.95f));
                if (*reinterpret_cast<short *>(fighter_owner_348 + 0x736) == 0) {
                    counter_144 = 0;
                    state_364 = 1;
                }
            }
            if (state_364 == 1 && *reinterpret_cast<short *>(fighter_owner_348 + 0x738) == 2) {
                switch (g_match_identifier) {
                case 3:
                    if (counter_144 % 170 == 0) {
                        const unsigned char *const followed = followed_actor_170;
                        const float aim_x = static_cast<float>(
                            (*reinterpret_cast<const float *>(followed + 0xec) - static_cast<double>(x_ec)) * facing_104);
                        const float aim_y = static_cast<float>(
                            *reinterpret_cast<const float *>(followed + 0xf0) + 100.0 - y_f0);
                        const float base_angle = -atan2_degrees(aim_y, aim_x);
                        float copied[3];
                        for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 90.0 + base_angle);
                            copied[1] = 6.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                907, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 2:
                    if (counter_144 % 200 == 0) {
                        const unsigned char *const followed = followed_actor_170;
                        const float aim_x = static_cast<float>(
                            (*reinterpret_cast<const float *>(followed + 0xec) - static_cast<double>(x_ec)) * facing_104);
                        const float aim_y = static_cast<float>(
                            *reinterpret_cast<const float *>(followed + 0xf0) + 100.0 - y_f0);
                        const float base_angle = -atan2_degrees(aim_y, aim_x);
                        float copied[3];
                        for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 90.0 + base_angle - 90.0);
                            copied[1] = 6.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                907, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 1:
                    if (counter_144 % 210 == 0) {
                        const unsigned char *const followed = followed_actor_170;
                        const float aim_x = static_cast<float>(
                            (*reinterpret_cast<const float *>(followed + 0xec) - static_cast<double>(x_ec)) * facing_104);
                        const float aim_y = static_cast<float>(
                            *reinterpret_cast<const float *>(followed + 0xf0) + 100.0 - y_f0);
                        atan2_degrees(aim_y, aim_x);
                        float copied[3];
                        for (float sector = 0.0f; sector < 2.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 180.0 + heading_12c);
                            copied[1] = 6.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                907, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 0:
                    if (counter_144 % 225 == 0) {
                        const unsigned char *const followed = followed_actor_170;
                        const float aim_x = static_cast<float>(
                            (*reinterpret_cast<const float *>(followed + 0xec) - static_cast<double>(x_ec)) * facing_104);
                        const float aim_y = static_cast<float>(
                            *reinterpret_cast<const float *>(followed + 0xf0) + 100.0 - y_f0);
                        const float base_angle = -atan2_degrees(aim_y, aim_x);
                        float copied[3];
                        for (float sector = 0.0f; sector < 1.0f; sector += 1.0f) {
                            copied[0] = base_angle;
                            copied[1] = 6.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                907, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                }
            }
            if (state_364 == 2) {
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = scale_x_11c;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_110 = static_cast<unsigned char>(channel_110 - 10);
            }
            break;
        case 2:
            if (channel_111 < 5) {
                channel_111 = 0;
                channel_112 = 0;
            } else {
                channel_111 = static_cast<unsigned char>(channel_111 - 5);
                channel_112 = static_cast<unsigned char>(channel_112 - 5);
            }
            break;
        case 3:
            heading_12c = static_cast<float>(heading_12c + 8.0);
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.2f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        case 4:
            heading_12c = static_cast<float>(heading_12c + 8.0);
            if (state_364 <= 1 && *reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 2500) {
                state_364 = 2;
                phase_index_184 = 0;
            }
            if (state_364 == 0) {
                if (alpha_113 <= 245)
                    alpha_113 = static_cast<unsigned char>(alpha_113 + 10);
                else {
                    alpha_113 = 255;
                    phase_index_184 = 1;
                    state_364 = 1;
                }
            }
            if (state_364 == 1) {
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
                if ((static_cast<float>(facing_104) * velocity_x_f4 < 0.0 && x_ec < 0.0) ||
                        (static_cast<float>(facing_104) * velocity_x_f4 > 0.0 && x_ec > 1280.0f)) {
                    velocity_x_f4 = -velocity_x_f4;
                    phase_index_184 = 1;
                    phase_state_180 = 0;
                    next_sequence_block();
                    return;
                }
                if ((velocity_y_f8 < 0.0 && y_f0 < 0.0) || (velocity_y_f8 > 0.0 && y_f0 > 900.0)) {
                    velocity_y_f8 = -velocity_y_f8;
                    phase_index_184 = 1;
                    phase_state_180 = 0;
                    next_sequence_block();
                    return;
                }
            }
            if (state_364 == 2) {
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            }
            break;
        case 5:
            heading_12c = static_cast<float>(heading_12c - 8.0);
            if (state_364 <= 1 && *reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 2500) {
                state_364 = 2;
                phase_index_184 = 0;
            }
            if (state_364 == 0) {
                if (alpha_113 <= 245)
                    alpha_113 = static_cast<unsigned char>(alpha_113 + 10);
                else {
                    alpha_113 = 255;
                    phase_index_184 = 1;
                    state_364 = 1;
                }
            }
            if (state_364 == 1)
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            if (state_364 == 2) {
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            }
            if (x_ec > 1680.0 || x_ec < -400.0 || y_f0 > 1300.0f || y_f0 < -300.0f)
                goto retire;
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        goto advance_with_sequence_three_retirement;

    case 908:
        switch (sequence_13e) {
        case 0:
            heading_12c += parameters_340[1];
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0 && state_364 != 2) {
                state_364 = 2;
                float copied[3] = {heading_12c, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_indexed_event_member(38);
            }
            if (state_364 == 0) {
                state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(counter_144 * 3.0)) * static_cast<double>(0.2f) + 1.0);
                scale_x_11c = static_cast<float>((1.0 - state_370) * state_374);
                scale_y_120 = scale_x_11c;
                state_370 = static_cast<float>(state_370 * static_cast<double>(0.95f));
                if (*reinterpret_cast<short *>(fighter_owner_348 + 0x736) == 0) {
                    counter_144 = 0;
                    state_364 = 1;
                }
            }
            if (state_364 == 1 && *reinterpret_cast<short *>(fighter_owner_348 + 0x738) == 3) {
                if (state_366 > 0) {
                    if (state_366 % 2 == 0) {
                        float copied[3] = {state_374, 4.0f, 6.0f};
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(1);
                        state_374 += state_366;
                    }
                    state_366 = static_cast<short>(state_366 - 1);
                }
                if (state_368 > 0) {
                    if (state_368 % 2 == 1) {
                        float copied[3] = {state_378, 4.0f, 7.0f};
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        state_378 -= state_368;
                    }
                    state_368 = static_cast<short>(state_368 - 1);
                }
                switch (g_match_identifier) {
                case 3:
                    if (counter_144 % 240 == 60 || counter_144 % 240 == 80 || counter_144 % 240 == 100 || counter_144 % 240 == 120) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(7)) + 3.0);
                        copied[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (counter_144 % 240 == 70 || counter_144 % 240 == 90 || counter_144 % 240 == 110 || counter_144 % 240 == 130) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(3)) + 2.0);
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (counter_144 % 150 == 0) {
                        state_366 = 60;
                        state_368 = 60;
                        state_374 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        state_378 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    }
                    break;
                case 2:
                    if (counter_144 % 240 == 60 || counter_144 % 240 == 80 || counter_144 % 240 == 100) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(7)) + 3.0);
                        copied[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (counter_144 % 240 == 70 || counter_144 % 240 == 90 || counter_144 % 240 == 110) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(3)) + 2.0);
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (counter_144 % 150 == 0) {
                        state_366 = 60;
                        state_374 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    }
                    break;
                case 1:
                    if (counter_144 % 240 == 60 || counter_144 % 240 == 80 || counter_144 % 240 == 100) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(7)) + 3.0);
                        copied[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (counter_144 % 240 == 70 || counter_144 % 240 == 90) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(3)) + 2.0);
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (counter_144 % 240 == 0) {
                        state_366 = 60;
                        state_374 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    }
                    break;
                case 0:
                    if (counter_144 % 240 == 60 || counter_144 % 240 == 80) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(7)) + 3.0);
                        copied[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (counter_144 % 240 == 70 || counter_144 % 240 == 90) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(3)) + 2.0);
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                }
            }
            if (state_364 == 2) {
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.1f));
                scale_y_120 = scale_x_11c;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
                channel_111 = static_cast<unsigned char>(channel_111 - 10);
                channel_110 = static_cast<unsigned char>(channel_110 - 10);
            }
            break;
        case 2:
            if (channel_111 < 5) {
                channel_111 = 0;
                channel_112 = 0;
            } else {
                channel_111 = static_cast<unsigned char>(channel_111 - 5);
                channel_112 = static_cast<unsigned char>(channel_112 - 5);
            }
            break;
        case 3:
            heading_12c = static_cast<float>(heading_12c + 8.0);
            scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.2f));
            scale_y_120 = scale_x_11c;
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        case 4:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0 || value_174 <= -800)
                state_364 = 1;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            heading_12c = static_cast<float>(heading_12c + 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (static_cast<signed char>(phase_index_184) <= 0)
                state_364 = 1;
            if (state_364 == 1) {
                phase_index_184 = 0;
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.05f));
                scale_y_120 = scale_x_11c;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            }
            goto bounds_908;
        case 5:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0 || value_174 <= -1200)
                state_364 = 1;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            heading_12c = static_cast<float>(heading_12c - 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (static_cast<signed char>(phase_index_184) <= 0)
                state_364 = 1;
            if (state_364 == 1) {
                phase_index_184 = 0;
                scale_x_11c = static_cast<float>(scale_x_11c + static_cast<double>(0.05f));
                scale_y_120 = scale_x_11c;
                if (alpha_113 < 10)
                    goto retire;
                alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            }
            goto bounds_908;
        case 6:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0)
                state_364 = 1;
            parameters_340[1] = static_cast<float>(parameters_340[1] + 0.25);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            heading_12c = static_cast<float>(heading_12c + 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(3);
            if (static_cast<signed char>(phase_index_184) <= 0)
                state_364 = 1;
            if (state_364 == 1) {
                packet_908_sequence_6[0] = heading_12c;
                packet_908_sequence_6[1] = 0.5f;
                packet_908_sequence_6[2] = 8.0f;
                retiring_action = 908;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_908_sequence_6);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            goto bounds_908;
        case 7:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x174) <= 0)
                state_364 = 1;
            parameters_340[1] = static_cast<float>(parameters_340[1] + 0.25);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            heading_12c = static_cast<float>(heading_12c - 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(3);
            if (static_cast<signed char>(phase_index_184) <= 0)
                state_364 = 1;
            if (state_364 == 1) {
                packet_908_sequence_7[0] = heading_12c;
                packet_908_sequence_7[1] = 0.5f;
                packet_908_sequence_7[2] = 9.0f;
                retiring_action = 908;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_908_sequence_7);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            goto bounds_908;
        bounds_908:
            if (x_ec >= 1500.0f || x_ec < -220.0 || y_f0 > 1100.0f || y_f0 < -500.0)
                goto retire;
            break;
        case 8: case 9:
            if (sequence_13e == 8)
                heading_12c = static_cast<float>(heading_12c + 10.0);
            else
                heading_12c = static_cast<float>(heading_12c - 10.0);
            scale_x_11c += parameters_340[1];
            scale_y_120 = scale_x_11c;
            parameters_340[1] = static_cast<float>(parameters_340[1] * static_cast<double>(0.9f));
            if (alpha_113 < 10)
                goto retire;
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 3)
            --state_330;
        return;

    case 951: {
        alpha_113 = fighter_owner_348[0x113];
        if (sequence_13e == 0 || sequence_13e == 3)
            y_f0 = *reinterpret_cast<float *>(fighter_owner_348 + 0xf0);
        else
            y_f0 = stage_surface_height_at_x(reinterpret_cast<Fighter *>(fighter_owner_348));
        x_ec = *reinterpret_cast<float *>(fighter_owner_348 + 0xec);
        *reinterpret_cast<short *>(fighter_owner_348 + 0x7a4) = 1;
        const short owner_sequence = *reinterpret_cast<short *>(fighter_owner_348 + 0x13e);
        const short owner_frame = *reinterpret_cast<short *>(fighter_owner_348 + 0x140);
        const short owner_action = *reinterpret_cast<short *>(fighter_owner_348 + 0x13c);
        if (owner_sequence == 0 && owner_frame == 0 &&
                ((owner_action >= 70 && owner_action <= 88) || owner_action == 181 ||
                owner_action == 180 || owner_action == 145 || (owner_action >= 100 && owner_action <= 111))) {
            --state_330;
            *reinterpret_cast<short *>(fighter_owner_348 + 0x7a4) = 0;
            return;
        }
        if (sequence_13e == 0 && (owner_action == 96 || owner_action == 97) && owner_sequence == 3) {
            next_sequence_block();
            heading_12c = 0.0f;
            return;
        }
        if (sequence_13e == 1 && (owner_action == 199 || owner_action == 198 || owner_action == 197 ||
                owner_action == 796 || owner_action == 771) && owner_sequence == 0 && owner_frame == 3) {
            next_sequence_block();
            return;
        }
        if (sequence_13e == 3 && (owner_action == 199 || owner_action == 198 || owner_action == 197 ||
                owner_action == 796) && owner_sequence == 2) {
            --state_330;
            *reinterpret_cast<short *>(fighter_owner_348 + 0x7a4) = 0;
            return;
        }
        if (sequence_13e == 0 || sequence_13e == 3)
            heading_12c = static_cast<float>(heading_12c - 35.0);
        if (sequence_13e == 1 && frame_140 == 4)
            return;
        goto advance_and_retire_on_completion;
    }
    case 999:
        switch (sequence_13e) {
        case 0: case 1: case 2: case 3:
            *reinterpret_cast<float *>(fighter_owner_348 + 0xec) = x_ec;
            if (x_ec > 1480.0f || x_ec < -200.0)
                goto retire;
            if (sequence_13e >= 1)
                velocity_y_f8 -= acceleration_y_100;
            break;
        case 4: {
            velocity_y_f8 = static_cast<float>(velocity_y_f8 - static_cast<double>(0.35f));
            const double projected_y = static_cast<double>(velocity_y_f8) + y_f0;
            if (stage_surface_height_at_x(reinterpret_cast<Fighter *>(this)) >= projected_y) {
                *reinterpret_cast<short *>(fighter_owner_348 + 0x78c) = 1;
                y_f0 = stage_surface_height_at_x(reinterpret_cast<Fighter *>(this));
                velocity_x_f4 = 0.0f;
                velocity_y_f8 = 0.0f;
                acceleration_y_100 = 0.0f;
                select_sequence(5);
                return;
            }
            break;
        }
        case 6:
            if (*reinterpret_cast<short *>(fighter_owner_348 + 0x78e) == 1) {
                next_sequence_block();
                facing_104 = 1;
                return;
            }
            break;
        case 7: case 8:
            if (sequence_13e >= 8)
                velocity_y_f8 -= acceleration_y_100;
            break;
        }
        x_ec += static_cast<float>(facing_104) * velocity_x_f4;
        y_f0 += velocity_y_f8;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --state_330;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 &&
                sequence_13e == 1) {
            velocity_x_f4 = 15.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.2f;
        }
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 &&
                sequence_13e == 8) {
            velocity_x_f4 = 15.0f;
            velocity_y_f8 = 15.0f;
            acceleration_y_100 = 0.2f;
        }
        return;

    default:
        reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch();
        return;
    }

emit_retiring_world:
    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
        retiring_action, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
        retiring_packet, retiring_words);
    goto retire;

advance_with_sequence_three_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 3)
        --state_330;
    return;

advance_with_sequence_one_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1)
        --state_330;
    return;

advance_with_sequence_four_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 4)
        --state_330;
    return;

select_sequence_three:
    select_sequence(3);
    return;

bounded_projectile_advance:
    if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -120.0)
        goto retire;
advance_with_sequence_two_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
        --state_330;
    return;

advance_with_sequence_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1)
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
        --state_330;
    return;

advance_and_retire_on_completion:
    if (!reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        return;
    goto retire;
clear_alpha_and_retire:
    alpha_113 = 0;
retire:
    --state_330;
    return;
}

} // namespace th105
