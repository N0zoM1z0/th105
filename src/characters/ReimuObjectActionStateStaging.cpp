// Bounded source phase inside ReimuObject496540, original Japanese1.06a.
// No original function boundary, full-root implementation or exact claim.
#include "ReimuObjectActionStateStaging.hpp"
#include "CharacterObjectEffects.hpp"
#include "CharacterObjectRuntime.hpp"
#include <math.h>

namespace th105 {

double __cdecl lookup_orientation_sine_quantized_abs(float angle);
double __cdecl lookup_orientation_cosine_quantized_abs(float angle);
int __cdecl selector_random_roll(int limit);
unsigned int __cdecl mt19937_next_u32();

// The already-matched465190 wrapper forwards seven32-bit argument words.
// Its sixth word carries the copied-parameter pointer to the owned manager.
class ReimuObjectOwnerSpawnView {
public:
    void dispatch_character_wave_handle(unsigned int index);
    int spawn_owned_object_via_manager(
        int action, float x, float y, int facing, int variant,
        int copied_words, int copied_word_count);
};

bool ReimuObjectActionStateStagingView::try_update_scalar_actions()
{
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
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1)
            scale_x_11c = scale_y_120 = 2.0f;
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
            return true;
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
                scale_x_11c = scale_y_120 = 1.0f;
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
                    return true;
                }
                if (phase_state_180 == 0)
                    state_368 = 0;
                if (phase_index_184 == 0) {
                    select_sequence(2);
                    return true;
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
            velocity_x_f4 = velocity_y_f8 = 0.0f;
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
            velocity_x_f4 = velocity_y_f8 = 0.0f;
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
        goto advance_with_sequence_two_retirement;

    case 804:
        if (phase_state_180 == 5 || (sequence_13e < 2 &&
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 5)))
            goto retire;
        if (sequence_13e == 0 || sequence_13e == 1) {
            if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    replace_secondary_animation(993, 4.0f, 30, 1, 2);
                state_364 = 0;
            }
            heading_12c = parameters_340[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(parameters_340[0], 35.0f);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (phase_state_180 == 1 || phase_state_180 == 9 ||
                    (sequence_13e == 1 && phase_state_180 == 2)) {
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(parameters_340[0], 2.0f);
                ++state_364;
                if (state_364 > 3) {
                    state_364 = 0;
                    phase_state_180 = 0;
                }
            }
            if ((phase_state_180 == 2 || phase_state_180 == 4) &&
                    (sequence_13e == 0 || static_cast<signed char>(phase_index_184) < 1)) {
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
        goto bounded_projectile_advance;

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
                scale_x_11c = scale_y_120 = 1.0f;
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
                    return true;
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
            velocity_x_f4 = velocity_y_f8 = 0.0f;
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
            velocity_x_f4 = velocity_y_f8 = 0.0f;
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
        goto advance_with_sequence_two_retirement;

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
                return true;
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
                goto retire;
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
        goto bounded_projectile_advance;

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
                scale_x_11c = scale_y_120 = 1.0f;
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
                    goto retire;
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
            if (phase_state_180 != 0)
                goto select_sequence_three;
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
        goto advance_with_sequence_two_retirement;

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
            return true;
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
        goto bounded_projectile_advance;

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
                    return true;
                }
                const int remainder = counter_144 % 30;
                if (remainder == 0 || remainder == 2 || remainder == 4) {
                    float copied[3];
                    copied[0] = static_cast<float>(45.0 - static_cast<float>(static_cast<unsigned int>(selector_random_roll(270))));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(40)));
                    copied[2] = 3.0f;
                    const double origin_y = y_f0 + 50.0;
                    const double origin_x = x_ec + 100.0;
                    const float request_y = static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(100))));
                    const float request_x = static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200))));
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->spawn_owned_object_via_manager(
                        817, request_x, request_y, static_cast<unsigned char>(facing_104), 1, reinterpret_cast<int>(copied), 3);
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
            scale_x_11c = scale_y_120 = static_cast<float>(jitter + 1.0);
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
            const unsigned int turn = static_cast<unsigned int>(selector_random_roll(360)) - 180u;
            parameters_340[0] += static_cast<float>(turn);
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
                scale_x_11c = scale_y_120 = static_cast<float>(jitter + 1.0);
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
            scale_x_11c = scale_y_120 = static_cast<float>(jitter + 1.0);
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
                    return true;
                }
                const int remainder = counter_144 % 30;
                if (remainder == 0 || remainder == 2 || remainder == 4) {
                    float copied[3];
                    copied[0] = static_cast<float>(45.0 - static_cast<float>(static_cast<unsigned int>(selector_random_roll(270))));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(40)));
                    copied[2] = 3.0f;
                    const double origin_y = y_f0 + 50.0;
                    const double origin_x = x_ec + 100.0;
                    const float request_y = static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(100))));
                    const float request_x = static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200))));
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(fighter_owner_348)->spawn_owned_object_via_manager(
                        817, request_x, request_y, static_cast<unsigned char>(facing_104), 1, reinterpret_cast<int>(copied), 3);
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
        goto advance_with_sequence_retirement;

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
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1)
            scale_x_11c = scale_y_120 = 2.0f;
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
                return true;
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
                return true;
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
            if ((*reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 530 &&
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13c) != 531) ||
                    (*reinterpret_cast<short *>(fighter_owner_348 + 0x13e) == 3 &&
                     *reinterpret_cast<short *>(fighter_owner_348 + 0x140) >= 4) ||
                    *reinterpret_cast<short *>(fighter_owner_348 + 0x13e) >= 4)
                goto retire;
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
                float copied[4] = {0.0f, 0.0f, 2.0f, 0.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    822, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 4);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    822, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                    reinterpret_cast<const unsigned *>(copied), 4);
                goto retire;
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
                    parameters_340[0] = heading_12c = heading;
                    float copied[4] = {heading, 0.0f, 1.0f, 0.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                        822, x_ec, y_f0, static_cast<unsigned char>(facing_104), -1,
                        reinterpret_cast<const unsigned *>(copied), 4);
                    return true;
                }
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(parameters_340[0], parameters_340[1]);
            }
            if (frame_140 == 1) {
                if (frame_timer_142 == 0)
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(992, 10.0f, 10, 1, 2);
                if (phase_state_180 != 0) {
                    float copied[4] = {0.0f, 0.0f, 2.0f, 0.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        822, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 4);
                    copied[2] = 3.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        822, x_ec, y_f0, static_cast<unsigned char>(facing_104), 1,
                        reinterpret_cast<const unsigned *>(copied), 4);
                    goto retire;
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
            scale_x_11c = scale_y_120 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(counter_144 * 10.0)) * static_cast<double>(0.1f) + 1.0);
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
                float copied[4] = {0.0f, 0.0f, 0.0f, 0.0f};
                copied[2] = static_cast<unsigned int>(selector_random_roll(100)) < 50u ? 5.0f : 6.0f;
                const double origin_y = y_f0 + 100.0;
                const double origin_x = x_ec + 100.0;
                const unsigned char direction = static_cast<unsigned int>(selector_random_roll(100)) > 50u ? 255 : 1;
                const float request_y = static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200))));
                const float request_x = static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200))));
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    822, request_x, request_y, direction, 1, reinterpret_cast<const unsigned *>(copied), 4);
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
            if (channel_112 < 15)
                goto retire;
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
        goto advance_with_sequence_two_retirement;

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
            return true;
        if (*reinterpret_cast<short *>(fighter_owner_348 + 0x186) != 0)
            return true;
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
                    return true;
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
            return true;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            goto retire;
        if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && (sequence_13e == 2 || sequence_13e == 6))
            goto retire;
        return true;

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
            angle_x_124 = angle_y_128 = heading_12c = 0.0f;
            scale_x_11c = scale_y_120 = 4.0f;
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
            return true;
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
                scale_x_11c = scale_y_120 = 1.0f;
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
            velocity_x_f4 = velocity_y_f8 = 0.0f;
            state_366 = 0;
            scale_x_11c = static_cast<float>(scale_x_11c - static_cast<double>(0.2f));
            scale_y_120 = static_cast<float>(scale_y_120 - static_cast<double>(0.2f));
            alpha_113 = static_cast<unsigned char>(alpha_113 - 10);
            if (scale_x_11c < 0.0f)
                goto retire;
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
                scale_x_11c = scale_y_120 = 3.0f;
                select_sequence(2);
                return true;
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
        goto advance_with_sequence_three_retirement;

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
        scale_x_11c = scale_y_120 = static_cast<float>(pulse * 2.0 + 1.0);
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

    case 853: case 854: case 855: case 856: case 858:
    case 866: case 869:
    case 900: case 901: case 902: case 903: case 904: case 905: case 906: case 907: case 908:
    case 951: case 999:
        return false;
    default:
        reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch();
        return true;
    }

advance_with_sequence_three_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 3)
        --state_330;
    return true;

advance_with_sequence_one_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1)
        --state_330;
    return true;

advance_with_sequence_four_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 4)
        --state_330;
    return true;

select_sequence_three:
    select_sequence(3);
    return true;

bounded_projectile_advance:
    if (x_ec > 1380.0 || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -120.0)
        goto retire;
advance_with_sequence_two_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
        --state_330;
    return true;

advance_with_sequence_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 1)
        --state_330;
    if (counter_144 == 0 && frame_timer_142 == 0 && frame_140 == 0 && sequence_13e == 2)
        --state_330;
    return true;

advance_and_retire_on_completion:
    if (!reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        return true;
    goto retire;
clear_alpha_and_retire:
    alpha_113 = 0;
retire:
    --state_330;
    return true;
}

} // namespace th105
