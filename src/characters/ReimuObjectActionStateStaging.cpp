#include "ReimuObjectOwnerView.hpp"
// Source hypothesis for the complete ReimuObject496540 void update root.
// The isolated17-slot owner view preserves target-observed float lifetimes.
// Original nominal/lifecycle identities and full canonical equality stay open.
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

} // namespace th105
using namespace th105;
void th105::reimu_object_model::ReimuObject::dispatch_action_state()
{
    th105::ReimuObjectActionStateStagingView &_root_state =
        *reinterpret_cast<th105::ReimuObjectActionStateStagingView *>(this);
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
    switch (_root_state.action_13c) {
    case 800:
        if (_root_state.phase_state_180 == 5 || (_root_state.sequence_13e == 0 &&
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 3)))
            goto retire;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                replace_secondary_animation(993, 10.0f, 10, 1, 2);
            _root_state.phase_index_184 = 1;
            _root_state.state_364 = 0;
        }
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 1) {
            effect_000.reset_one_118 = 2.0f;
            effect_000.reset_one_11c = effect_000.reset_one_118;
        }
        if (_root_state.sequence_13e == 0) {
            ++_root_state.state_364;
            effect_000.reset_zero_128 = reinterpret_cast<float *>(copied_words_340)[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(
                    _root_state.state_364 * static_cast<double>(0.1f) + reinterpret_cast<float *>(copied_words_340)[1]));
        }
        if (_root_state.sequence_13e < 2) {
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        }
        if (_root_state.sequence_13e == 1) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c * static_cast<double>(0.65f));
            if (_root_state.alpha_113 < 5)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 5);
        }
        if (_root_state.sequence_13e == 2) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.4f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.4f));
            if (_root_state.alpha_113 < 25)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 25);
        }
        if (_root_state.phase_state_180 != 0 && _root_state.sequence_13e == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
            next_sequence_block();
            float copied[3] = {-effect_000.reset_zero_128, 0.0f, 2.0f};
            reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->
                spawn_owned_object_via_manager(800, effect_000.object_x_0e8, effect_000.object_y_0ec,
                    static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<int>(copied), 3);
            return;
        }
        goto bounded_projectile_advance;

    case 801:
        if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec > 1000.0 || effect_000.object_y_0ec < -240.0 ||
                _root_state.phase_state_180 == 5 || (_root_state.sequence_13e < 2 &&
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        emit_repeated_effects_for_owner_state(0, 3, 8)))
            goto retire;
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 18.0);
        switch (_root_state.sequence_13e) {
        case 0:
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (effect_000.reset_one_118 < 1.0) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            } else {
                effect_000.reset_one_118 = 1.0f;
                effect_000.reset_one_11c = effect_000.reset_one_118;
                next_sequence_block();
            }
            break;
        case 1:
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + static_cast<double>(0.35f));
            if (reinterpret_cast<float *>(copied_words_340)[3] == 0.0f)
                _root_state.state_36c = 1;
            if (_root_state.state_36c == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    turn_heading_toward_related(0.0f, 2.5f, 100.0f);
                if (_root_state.counter_144 % 5 == 0) {
                    float copied[3] = {effect_000.reset_zero_128, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        spawn_unparented_related_object(801, effect_000.object_x_0e8, effect_000.object_y_0ec,
                            static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                }
            } else {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    turn_heading_toward_related(0.0f, 0.5f, 100.0f);
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (_root_state.phase_state_180 != 0) {
                reinterpret_cast<float *>(copied_words_340)[1] = 2.0f;
                ++_root_state.state_368;
                if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10)) {
                    select_sequence(2);
                    return;
                }
                if (_root_state.phase_state_180 == 0)
                    _root_state.state_368 = 0;
                if (_root_state.phase_index_184 == 0) {
                    select_sequence(2);
                    return;
                }
                if (_root_state.state_368 > 5) {
                    _root_state.state_368 = 0;
                    _root_state.phase_state_180 = 0;
                }
            }
            if (_root_state.counter_144 > 60)
                next_sequence_block();
            break;
        case 2:
            effect_000.motion_0f0.velocity_x = 0.0f;
            effect_000.motion_0f0.velocity_y = effect_000.motion_0f0.velocity_x;
            if (_root_state.alpha_113 < 10) {
                _root_state.alpha_113 = 0;
                --_root_state.state_330;
            } else {
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.15f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.15f));
            }
            break;
        case 3:
            effect_000.motion_0f0.velocity_x = 0.0f;
            effect_000.motion_0f0.velocity_y = effect_000.motion_0f0.velocity_x;
            if (_root_state.alpha_113 < 15) {
                _root_state.alpha_113 = 0;
                --_root_state.state_330;
            } else {
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            }
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
            goto retire_801_811;
        return;

retire_801_811:
        --_root_state.state_330;
        return;

    case 804:
        if (_root_state.phase_state_180 == 5 || (_root_state.sequence_13e < 2 &&
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 5)))
            goto retire;
        if (_root_state.sequence_13e == 0) {
            if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    replace_secondary_animation(993, 4.0f, 30, 1, 2);
                _root_state.state_364 = 0;
            }
            effect_000.reset_zero_128 = reinterpret_cast<float *>(copied_words_340)[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], 35.0f);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (_root_state.phase_state_180 == 1 || _root_state.phase_state_180 == 9) {
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], 2.0f);
                ++_root_state.state_364;
                if (_root_state.state_364 > 3) {
                    _root_state.state_364 = 0;
                    _root_state.phase_state_180 = 0;
                }
            }
            if (_root_state.phase_state_180 == 2 || _root_state.phase_state_180 == 4) {
                select_sequence(2);
                _root_state.phase_index_184 = 0;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                effect_000.motion_0f0.velocity_x = static_cast<float>(8.0 -
                    static_cast<float>(mt19937_next_u32() % 20u) * static_cast<double>(0.1f));
                effect_000.motion_0f0.velocity_y = static_cast<float>(
                    static_cast<float>(mt19937_next_u32() % 25u) * static_cast<double>(0.1f) + 5.0);
            }
        }
        if (_root_state.sequence_13e == 1) {
            if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    replace_secondary_animation(993, 4.0f, 30, 1, 2);
                _root_state.state_364 = 0;
            }
            effect_000.reset_zero_128 = reinterpret_cast<float *>(copied_words_340)[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], 35.0f);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (_root_state.phase_state_180 == 2 || _root_state.phase_state_180 == 1 || _root_state.phase_state_180 == 9) {
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], 2.0f);
                ++_root_state.state_364;
                if (_root_state.state_364 > 3) {
                    _root_state.state_364 = 0;
                    _root_state.phase_state_180 = 0;
                }
            }
            if ((_root_state.phase_state_180 == 2 || _root_state.phase_state_180 == 4) &&
                    static_cast<signed char>(_root_state.phase_index_184) <= 0) {
                select_sequence(2);
                _root_state.phase_index_184 = 0;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                effect_000.motion_0f0.velocity_x = static_cast<float>(8.0 -
                    static_cast<float>(mt19937_next_u32() % 20u) * static_cast<double>(0.1f));
                effect_000.motion_0f0.velocity_y = static_cast<float>(
                    static_cast<float>(mt19937_next_u32() % 25u) * static_cast<double>(0.1f) + 5.0);
            }
        }
        if (_root_state.sequence_13e == 2) {
            effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y - 0.25);
            if (effect_000.object_y_0ec + effect_000.motion_0f0.velocity_y < 0.0)
                effect_000.motion_0f0.velocity_y = -effect_000.motion_0f0.velocity_y;
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 40.0);
            if (_root_state.alpha_113 < 5)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 5);
        }
        if (_root_state.sequence_13e < 2) {
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        }
        if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec > 1000.0 || effect_000.object_y_0ec < -120.0)
            goto retire;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
            --_root_state.state_330;
        return;

    case 807:
        if ((_root_state.sequence_13e == 0 && reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 3, 10)) ||
                (_root_state.sequence_13e == 1 && reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 0)))
            goto retire;
        if (_root_state.sequence_13e == 0 || _root_state.sequence_13e == 1) {
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
            if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(20))
                _root_state.phase_index_184 = 0;
            if (_root_state.counter_144 < 10 || static_cast<signed char>(_root_state.phase_index_184) > 0) {
                effect_000.motion_0f0.velocity_x = 20.0f;
            } else {
                effect_000.motion_0f0.velocity_x = static_cast<float>(effect_000.motion_0f0.velocity_x - 1.5);
                if (effect_000.motion_0f0.velocity_x < 1.5f) {
                    effect_000.motion_0f0.velocity_x = 1.5f;
                    if (_root_state.alpha_113 <= 15)
                        goto retire;
                    _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
                    _root_state.phase_index_184 = 0;
                }
            }
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        goto advance_and_retire_on_completion;

    case 808:
        if (_root_state.sequence_13e == 0) {
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(1, 2, 5))
                goto retire;
            effect_000.motion_0f0.velocity_y = 5.0f;
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 5.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            if (_root_state.counter_144 == 5 && effect_000.object_y_0ec < 960.0) {
                float copied[3] = {0.0f, 0.0f, 0.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(808, effect_000.object_x_0e8, static_cast<float>(effect_000.object_y_0ec + 80.0),
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 1.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(808, effect_000.object_x_0e8, static_cast<float>(effect_000.object_y_0ec + 80.0),
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
            }
            if (_root_state.counter_144 > 10) {
                if (_root_state.alpha_113 <= 15)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
                _root_state.phase_index_184 = 0;
            }
        }
        if (_root_state.sequence_13e == 1) {
            effect_000.motion_0f0.velocity_y = 3.0f;
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 5.0);
            if (_root_state.counter_144 > 10) {
                if (_root_state.alpha_113 <= 15)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
                _root_state.phase_index_184 = 0;
            }
        }
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        goto advance_and_retire_on_completion;

    case 810:
        if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec > 1000.0 || effect_000.object_y_0ec < -240.0 ||
                _root_state.phase_state_180 == 5 || (_root_state.sequence_13e < 3 &&
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        emit_repeated_effects_for_owner_state(0, 2, 8)))
            goto retire;
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 18.0);
        if (_root_state.sequence_13e == 0) {
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (effect_000.reset_one_118 < 1.0) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            } else {
                effect_000.reset_one_118 = 1.0f;
                effect_000.reset_one_11c = effect_000.reset_one_118;
                next_sequence_block();
            }
        }
        if (_root_state.sequence_13e == 1) {
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] - 1.5);
            if (reinterpret_cast<float *>(copied_words_340)[1] <= 0.0) {
                reinterpret_cast<float *>(copied_words_340)[1] = 0.0f;
                ++_root_state.state_364;
                if (_root_state.state_364 > 15) {
                    next_sequence_block();
                    return;
                }
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (_root_state.phase_state_180 != 0) {
                reinterpret_cast<float *>(copied_words_340)[1] = 2.0f;
                ++_root_state.state_368;
                if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(20))
                    _root_state.phase_index_184 = 0;
                if (_root_state.phase_index_184 == 0 || _root_state.phase_state_180 == 4)
                    goto select_sequence_three;
                if (_root_state.state_368 > 5) {
                    _root_state.state_368 = 0;
                    _root_state.phase_state_180 = 0;
                }
            }
        }
        if (_root_state.sequence_13e == 2) {
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + 0.75);
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                turn_heading_toward_related(0.0f, 2.0f, 100.0f);
            if (_root_state.counter_144 % 5 == 0) {
                float copied[3] = {effect_000.reset_zero_128, 0.0f, 4.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(810, effect_000.object_x_0e8, effect_000.object_y_0ec,
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (_root_state.phase_state_180 != 0) {
                reinterpret_cast<float *>(copied_words_340)[1] = 2.0f;
                ++_root_state.state_368;
                if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(20))
                    _root_state.phase_index_184 = 0;
                if (_root_state.phase_index_184 == 0 || _root_state.phase_state_180 == 4)
                    goto select_sequence_three;
                if (_root_state.state_368 > 5) {
                    _root_state.state_368 = 0;
                    _root_state.phase_state_180 = 0;
                }
            }
            if (_root_state.counter_144 > 60 || static_cast<signed char>(_root_state.phase_index_184) < 1)
                next_sequence_block();
        }
        if (_root_state.sequence_13e == 3) {
            effect_000.motion_0f0.velocity_x = 0.0f;
            effect_000.motion_0f0.velocity_y = effect_000.motion_0f0.velocity_x;
            if (_root_state.alpha_113 < 10) {
                _root_state.alpha_113 = 0;
                --_root_state.state_330;
            } else {
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.15f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.15f));
            }
        }
        if (_root_state.sequence_13e == 4) {
            effect_000.motion_0f0.velocity_x = 0.0f;
            effect_000.motion_0f0.velocity_y = effect_000.motion_0f0.velocity_x;
            if (_root_state.alpha_113 < 15) {
                _root_state.alpha_113 = 0;
                --_root_state.state_330;
            } else {
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            }
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
            --_root_state.state_330;
        return;

    case 811:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        if (_root_state.sequence_13e == 0) {
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 1, 4))
                goto retire;
            if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    replace_secondary_animation(990, 20.0f, 10, 1, 2);
                _root_state.phase_index_184 = 1;
                _root_state.state_364 = 0;
            }
            effect_000.reset_zero_128 = reinterpret_cast<float *>(copied_words_340)[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(15))
                _root_state.phase_index_184 = 0;
            if (_root_state.counter_144 % 4 == 0) {
                float copied[3] = {effect_000.reset_zero_128, 5.0f, 5.0f};
                // Prepare facing and outgoing fields before the coordinate RNG calls.
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(811,
                        static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(32))) + effect_000.object_x_0e8 - 16.0),
                        static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(32))) + effect_000.object_y_0ec - 16.0),
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
            }
            if (_root_state.phase_index_184 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                select_sequence(2);
                effect_000.reset_one_11c = 2.0f;
                float copied[3] = {0.0f, 0.0f, 3.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(811, effect_000.object_x_0e8, effect_000.object_y_0ec,
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                copied[2] = 4.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(811, effect_000.object_x_0e8, effect_000.object_y_0ec,
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                copied[2] = 4.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(811, effect_000.object_x_0e8, effect_000.object_y_0ec,
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                return;
            }
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        }
        if (_root_state.sequence_13e == 1) {
            if (!_root_state.parent_object_34c)
                goto retire;
            effect_000.reset_zero_128 = _root_state.parent_object_34c->parameters_340[0];
            effect_000.object_x_0e8 = _root_state.parent_object_34c->x_ec;
            effect_000.object_y_0ec = _root_state.parent_object_34c->y_f0;
            if (_root_state.parent_object_34c->sequence_13e == 2)
                goto retire_801_811;
        }
        if (_root_state.sequence_13e == 2) {
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] - 1.5);
            if (reinterpret_cast<float *>(copied_words_340)[1] < 2.0f)
                reinterpret_cast<float *>(copied_words_340)[1] = 2.0f;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.01f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c * static_cast<double>(0.85f));
            if (effect_000.reset_one_11c < 0.02f)
                goto retire;
        }
        if (_root_state.sequence_13e == 3) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.02f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
        }
        if (_root_state.sequence_13e == 3 || _root_state.sequence_13e == 4) {
            if (_root_state.channel_111 < 40) {
                _root_state.channel_111 = 0;
                if (_root_state.alpha_113 < 40)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 40);
            } else {
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 40);
            }
        }
        if (_root_state.sequence_13e == 5) {
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.02f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c * static_cast<double>(0.95f));
            if (_root_state.alpha_113 <= 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
        }
        if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec > 1000.0 || effect_000.object_y_0ec < -120.0)
            goto retire;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
            --_root_state.state_330;
        return;

    case 812:
        if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec > 1000.0 || effect_000.object_y_0ec < -240.0 ||
                _root_state.phase_state_180 == 5 || (_root_state.sequence_13e < 2 &&
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        emit_repeated_effects_for_owner_state(0, 2, 8)) ||
                (_root_state.sequence_13e == 2 && reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    emit_repeated_effects_for_owner_state(0, 0, 4)))
            goto retire;
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 18.0);
        switch (_root_state.sequence_13e) {
        case 0:
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (effect_000.reset_one_118 < 1.0) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            } else {
                effect_000.reset_one_118 = 1.0f;
                effect_000.reset_one_11c = effect_000.reset_one_118;
                next_sequence_block();
            }
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            break;
        case 1:
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] - 1.5);
            if (reinterpret_cast<float *>(copied_words_340)[1] <= 0.0) {
                reinterpret_cast<float *>(copied_words_340)[1] = 0.0f;
                ++_root_state.state_364;
                if (_root_state.counter_144 % 3 == 0) {
                    float copied[3] = {effect_000.reset_zero_128, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        spawn_unparented_related_object(812, effect_000.object_x_0e8, effect_000.object_y_0ec,
                            static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (_root_state.state_364 > 3) {
                    float copied[4];
                    copied[0] = reinterpret_cast<float *>(copied_words_340)[0];
                    copied[1] = 0.0f;
                    copied[2] = 3.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                        spawn_unparented_related_object(812, effect_000.object_x_0e8, effect_000.object_y_0ec,
                            static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                    for (float sector = 0.0f; sector < 8.0f; sector = static_cast<float>(sector + 1.0)) {
                        copied[0] = reinterpret_cast<float *>(copied_words_340)[0];
                        copied[1] = 0.0f;
                        copied[2] = 2.0f;
                        copied[3] = static_cast<float>(sector * 45.0 + copied[0]);
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                            spawn_unparented_related_object(812, effect_000.object_x_0e8, effect_000.object_y_0ec,
                                static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 4);
                    }
                    --_root_state.state_330;
                    return;
                }
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(30);
            if (_root_state.phase_state_180 != 0)
                goto select_sequence_three;
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            break;
        case 2:
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + 0.5);
            if (_root_state.counter_144 % 5 == 0) {
                float copied[3] = {effect_000.reset_zero_128, 0.0f, 4.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
                    spawn_unparented_related_object(812, effect_000.object_x_0e8, effect_000.object_y_0ec,
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.motion_0f0.velocity_x = static_cast<float>(lookup_orientation_cosine_quantized_abs(reinterpret_cast<float *>(copied_words_340)[3]) *
                this->state_370 + effect_000.motion_0f0.velocity_x);
            effect_000.motion_0f0.velocity_y = static_cast<float>(lookup_orientation_sine_quantized_abs(reinterpret_cast<float *>(copied_words_340)[3]) *
                this->state_370 + effect_000.motion_0f0.velocity_y);
            this->state_370 = static_cast<float>(this->state_370 - 0.25);
            if (this->state_370 < 0.0f)
                this->state_370 = 0.0f;
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(3);
            if (_root_state.phase_state_180 != 0) {
                select_sequence(3);
                return;
            }
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            break;
        case 3: case 4:
            if (_root_state.alpha_113 < 15) {
                _root_state.alpha_113 = 0;
                --_root_state.state_330;
            } else {
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            }
            break;
        }
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
            --_root_state.state_330;
        return;

    case 815:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        if (_root_state.sequence_13e == 0 && _root_state.counter_144 == 15) {
            float copied[3] = {0.0f, 0.0f, 4.0f};
            reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->
                spawn_owned_object_via_manager(815, effect_000.object_x_0e8, effect_000.object_y_0ec,
                    static_cast<unsigned char>(effect_000.object_facing_100), 1, reinterpret_cast<int>(copied), 3);
            reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(5);
            goto retire;
        }
        if (_root_state.sequence_13e == 1) {
            effect_000.reset_one_118 = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.1f) + effect_000.reset_one_118);
            effect_000.reset_one_11c = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.1f) + effect_000.reset_one_11c);
            if (_root_state.alpha_113 < 15)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
        }
        if (_root_state.sequence_13e == 2 && _root_state.counter_144 == 15) {
            select_sequence(1);
            return;
        }
        if (_root_state.sequence_13e == 0 || _root_state.sequence_13e == 2) {
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec -= effect_000.motion_0f0.velocity_y;
        }
        if ((_root_state.sequence_13e == 3 && (_root_state.counter_144 > 120 || _root_state.phase_index_184 == 0)) || _root_state.sequence_13e == 4) {
            _root_state.phase_index_184 = 0;
            if (_root_state.alpha_113 < 10)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 10);
        }
        if (_root_state.sequence_13e == 3) {
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->emit_repeated_effects_for_owner_state(1, 5, 10))
                goto retire;
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            if (static_cast<signed char>(_root_state.phase_index_184) > 0) {
                if (_root_state.phase_state_180 == 4 || _root_state.phase_state_180 == 8)
                    _root_state.phase_state_180 = 0;
                if (_root_state.phase_state_180 != 0) {
                    ++_root_state.state_364;
                    if (_root_state.state_364 >= 6) {
                        _root_state.state_364 = 0;
                        _root_state.phase_state_180 = 0;
                    }
                }
            }
        }
        if (_root_state.sequence_13e == 4 && _root_state.counter_144 == 5) {
            float copied[3] = {0.0f, 0.0f, 3.0f};
            reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->
                spawn_owned_object_via_manager(815, effect_000.object_x_0e8, effect_000.object_y_0ec,
                    static_cast<unsigned char>(effect_000.object_facing_100), 1, reinterpret_cast<int>(copied), 3);
        }
        if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec > 1000.0 || effect_000.object_y_0ec < -120.0)
            goto retire;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
            --_root_state.state_330;
        return;

    case 816:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        switch (_root_state.sequence_13e) {
        case 0:
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->emit_repeated_effects_for_owner_state(0, 1, 5))
                goto retire;
            if (_root_state.state_364 == 0) {
                effect_000.motion_0f0.velocity_x = static_cast<float>(effect_000.motion_0f0.velocity_x + 2.5);
                if (_root_state.counter_144 % 3 == 0) {
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        816, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (effect_000.motion_0f0.velocity_x > -1.0f)
                    effect_000.motion_0f0.velocity_x = -1.0f;
                _root_state.alpha_113 = _root_state.alpha_113 <= 235 ? static_cast<unsigned char>(_root_state.alpha_113 + 20) : 255;
                if (_root_state.alpha_113 == 255) {
                    _root_state.phase_index_184 = 1;
                    _root_state.state_364 = 1;
                }
            }
            if (_root_state.state_364 == 1) {
                effect_000.motion_0f0.velocity_x = static_cast<float>(effect_000.motion_0f0.velocity_x + 2.5);
                if (effect_000.motion_0f0.velocity_x > -0.5f)
                    effect_000.motion_0f0.velocity_x = -0.5f;
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
                if (_root_state.phase_state_180 == 1 ||
                        (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 525 &&
                         *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 526) ||
                        *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) >= 3)
                    _root_state.phase_index_184 = 0;
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            }
            if (_root_state.phase_index_184 == 0 && _root_state.state_364 > 0) {
                if (_root_state.state_364 == 1) {
                    effect_000.motion_0f0.velocity_x = 0.0f;
                    ++_root_state.state_364;
                    float copied[3] = {0.0f, 0.0f, 2.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        816, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (_root_state.alpha_113 < 40)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 40);
            }
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            break;
        case 4:
            if (reinterpret_cast<CharacterObjectEffectEmitter *>(this)->emit_repeated_effects_for_owner_state(0, 1, 5))
                goto retire;
            if (_root_state.state_364 == 0) {
                if (effect_000.motion_0f0.velocity_y < 0.0f) {
                    effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y + 2.5);
                    if (effect_000.motion_0f0.velocity_y > -0.5f)
                        effect_000.motion_0f0.velocity_y = -0.5f;
                }
                if (effect_000.motion_0f0.velocity_y > 0.0f) {
                    effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y - 2.5);
                    if (effect_000.motion_0f0.velocity_y < 0.5f)
                        effect_000.motion_0f0.velocity_y = 0.5f;
                }
                if (_root_state.counter_144 % 3 == 0) {
                    float copied[3] = {-effect_000.reset_zero_128, 0.0f, 7.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        816, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                _root_state.alpha_113 = _root_state.alpha_113 <= 235 ? static_cast<unsigned char>(_root_state.alpha_113 + 20) : 255;
                if (_root_state.alpha_113 == 255) {
                    _root_state.phase_index_184 = 1;
                    _root_state.state_364 = 1;
                }
            }
            if (_root_state.state_364 == 1) {
                if (effect_000.motion_0f0.velocity_y < 0.0f) {
                    effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y + 2.5);
                    if (effect_000.motion_0f0.velocity_y > -1.0f)
                        effect_000.motion_0f0.velocity_y = -1.0f;
                }
                if (effect_000.motion_0f0.velocity_y > 0.0f) {
                    effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y - 2.5);
                    if (effect_000.motion_0f0.velocity_y < 1.0f)
                        effect_000.motion_0f0.velocity_y = 1.0f;
                }
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
                if (_root_state.phase_state_180 == 1 ||
                        (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 525 &&
                         *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 526) ||
                        *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) >= 3)
                    _root_state.phase_index_184 = 0;
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            }
            if (_root_state.phase_index_184 == 0 && _root_state.state_364 > 0) {
                if (_root_state.state_364 == 1) {
                    effect_000.motion_0f0.velocity_x = 0.0f;
                    ++_root_state.state_364;
                    float copied[3] = {-effect_000.reset_zero_128, 0.0f, 6.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        816, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (_root_state.alpha_113 < 40)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 40);
            }
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            break;
        case 2: case 6:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.02f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.02f));
            if (_root_state.alpha_113 < 10)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        case 3: case 7:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.01f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.01f));
            if (_root_state.alpha_113 < 10)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 10);
            break;
        }
        goto advance_with_sequence_four_retirement;

    case 817: {
        if (_root_state.phase_state_180 == 5)
            goto retire;
        switch (_root_state.sequence_13e) {
        case 0:
            if (_root_state.counter_144 >= 30) {
                const CharacterObjectEffectEmitter *target = reinterpret_cast<CharacterObjectEffectEmitter *>(this)->target_170;
                const float dx = target->x_ec - effect_000.object_x_0e8;
                if (fabs(dx) <= 120.0 && fabs(static_cast<float>(target->y_f0 - effect_000.object_y_0ec)) <= 10.0) {
                    select_sequence(6);
                    float copied[3] = {0.0f, 0.0f, 4.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                        817, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    for (int remaining = 14; remaining != 0; --remaining) {
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(25))) + 15.0);
                        copied[2] = 8.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                            817, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                    }
                    return;
                }
                const int remainder = _root_state.counter_144 % 30;
                if (remainder == 0 || remainder == 2 || remainder == 4) {
                    float copied[3];
                    copied[0] = static_cast<float>(45.0 - static_cast<float>(static_cast<unsigned int>(selector_random_roll(270))));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(40)));
                    copied[2] = 3.0f;
                    const double origin_y = effect_000.object_y_0ec + 50.0;
                    const double origin_x = effect_000.object_x_0e8 + 100.0;
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->spawn_owned_object_via_manager(
                        817,
                        static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))),
                        static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(100)))),
                        static_cast<unsigned char>(effect_000.object_facing_100), 1, reinterpret_cast<int>(copied), 3);
                }
            }

            if (_root_state.counter_144 >= (static_cast<int>(*reinterpret_cast<signed char *>(_root_state.fighter_owner_348 + 0x60d)) + 3) * 60)
                goto retire;
            if ((*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 530 ||
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 531) &&
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) == 0)
                goto retire;
            break;
        case 1:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + 0.5);
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + 0.5);
            if (_root_state.channel_112 < 20) {
                if (_root_state.alpha_113 < 20)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 20);
                _root_state.channel_111 = _root_state.channel_112 = 0;
            } else {
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 20);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 20);
            }
            break;
        case 2: {
            const float jitter = static_cast<float>(
                static_cast<float>(static_cast<unsigned int>(selector_random_roll(100))) * static_cast<double>(0.01f));
            effect_000.reset_one_118 = static_cast<float>(jitter + 1.0);
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (!_root_state.parent_object_34c)
                goto retire;
            effect_000.object_x_0e8 = _root_state.parent_object_34c->x_ec;
            effect_000.object_y_0ec = _root_state.parent_object_34c->y_f0;
            if (_root_state.parent_object_34c->sequence_13e != 0 && _root_state.parent_object_34c->sequence_13e != 9)
                goto retire;
            break;
        }
        case 3: {
            if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 3)
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(992, 4.0f, 60, 1, 2);
            reinterpret_cast<float *>(copied_words_340)[0] += static_cast<float>(
                static_cast<unsigned int>(selector_random_roll(360)) - 180u);
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(60)) + 40u);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->set_secondary_animation_alpha(static_cast<unsigned char>(this->state_370));
            if (!(this->state_370 >= 5.0f))
                goto retire;
            this->state_370 = static_cast<float>(this->state_370 - 5.0);
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            break;
        }
        case 4:
            if (!_root_state.parent_object_34c)
                goto retire;
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            if (_root_state.phase_state_180 != 0) {
                ++_root_state.state_364;
                if (_root_state.state_364 >= 6) {
                    _root_state.state_364 = 0;
                    _root_state.phase_state_180 = 0;
                }
            }
            if (static_cast<signed char>(_root_state.phase_index_184) > 0 && _root_state.parent_object_34c->state_364 != 1) {
                const float jitter = static_cast<float>(
                    static_cast<float>(static_cast<unsigned int>(selector_random_roll(10))) * static_cast<double>(0.01f));
                effect_000.reset_one_118 = static_cast<float>(jitter + 1.0);
                effect_000.reset_one_11c = effect_000.reset_one_118;
            } else {
                _root_state.phase_index_184 = 0;
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.9f));
                effect_000.reset_one_11c += this->state_370;
                this->state_370 = static_cast<float>(this->state_370 - static_cast<double>(0.1f));
                if (this->state_370 < 0.0f)
                    this->state_370 = 0.0f;
                _root_state.alpha_113 = _root_state.alpha_113 < 10 ? 0 : static_cast<unsigned char>(_root_state.alpha_113 - 10);
            }
            break;
        case 6: case 7: {
            const float jitter = static_cast<float>(
                static_cast<float>(static_cast<unsigned int>(selector_random_roll(10))) * static_cast<double>(0.01f));
            effect_000.reset_one_118 = static_cast<float>(jitter + 1.0);
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.counter_144 < 40) {
                if (_root_state.counter_144 % 10 == 0) {
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(16);
                    float copied[3] = {0.0f, 0.0f, 1.0f};
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->spawn_owned_object_via_manager(
                        817, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), -1, reinterpret_cast<int>(copied), 3);
                }
            } else {
                _root_state.state_364 = 1;
                if (_root_state.counter_144 >= 55) {
                    if (_root_state.alpha_113 < 20)
                        goto retire;
                    _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 20);
                    _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 20);
                    _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 20);
                }
            }
            break;
        }
        case 8: {
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.9f));
            effect_000.reset_zero_128 += this->state_374;
            this->state_374 = static_cast<float>(this->state_374 * static_cast<double>(0.98f));
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            const signed char decrement = static_cast<signed char>(this->state_370);
            if (_root_state.channel_112 >= decrement) {
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - decrement);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - static_cast<unsigned char>(this->state_370));
            } else {
                if (_root_state.alpha_113 < decrement)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - decrement);
                _root_state.channel_111 = _root_state.channel_112 = 0;
            }
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            break;
        }
        case 9:
            if (effect_000.motion_0f0.velocity_x > 0.0f) {
                effect_000.motion_0f0.velocity_x = static_cast<float>(effect_000.motion_0f0.velocity_x - 0.5);
                if (effect_000.motion_0f0.velocity_x < 0.0f)
                    effect_000.motion_0f0.velocity_x = 0.0f;
            } else {
                const CharacterObjectEffectEmitter *target = reinterpret_cast<CharacterObjectEffectEmitter *>(this)->target_170;
                const float dx = target->x_ec - effect_000.object_x_0e8;
                if (fabs(dx) <= 120.0 && fabs(static_cast<float>(target->y_f0 - effect_000.object_y_0ec)) <= 10.0) {
                    select_sequence(6);
                    float copied[3] = {0.0f, 0.0f, 4.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                        817, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    for (int remaining = 14; remaining != 0; --remaining) {
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(25))) + 15.0);
                        copied[2] = 8.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                            817, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                    }
                    return;
                }
                const int remainder = _root_state.counter_144 % 30;
                if (remainder == 0 || remainder == 2 || remainder == 4) {
                    float copied[3];
                    copied[0] = static_cast<float>(45.0 - static_cast<float>(static_cast<unsigned int>(selector_random_roll(270))));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(40)));
                    copied[2] = 3.0f;
                    const double origin_y = effect_000.object_y_0ec + 50.0;
                    const double origin_x = effect_000.object_x_0e8 + 100.0;
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->spawn_owned_object_via_manager(
                        817,
                        static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))),
                        static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(100)))),
                        static_cast<unsigned char>(effect_000.object_facing_100), 1, reinterpret_cast<int>(copied), 3);
                }
            }

            if (_root_state.counter_144 >= (static_cast<int>(*reinterpret_cast<signed char *>(_root_state.fighter_owner_348 + 0x60d)) + 3) * 60)
                goto retire;
            if ((*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 530 ||
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 531) &&
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) == 0)
                goto retire;
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            break;
        }
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 1)
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
            --_root_state.state_330;
        return;

    }

    case 821:
        if (_root_state.phase_state_180 == 5 || (_root_state.sequence_13e == 0 &&
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->emit_repeated_effects_for_owner_state(0, 0, 3)))
            goto retire;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(993, 4.0f, 5, 1, 2);
            _root_state.phase_index_184 = 1;
            _root_state.state_364 = 0;
        }
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 1) {
            effect_000.reset_one_118 = 2.0f;
            effect_000.reset_one_11c = effect_000.reset_one_118;
        }
        if (_root_state.sequence_13e == 0) {
            effect_000.reset_zero_128 = reinterpret_cast<float *>(copied_words_340)[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(3);
            if (static_cast<signed char>(_root_state.phase_index_184) <= 0 && _root_state.phase_state_180 != 1) {
                float copied[3] = {-effect_000.reset_zero_128, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    821, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                next_sequence_block();
                effect_000.motion_0f0.velocity_x = static_cast<float>(-effect_000.motion_0f0.velocity_x * 0.5);
                const float launch = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(60))) * static_cast<double>(0.1f));
                effect_000.motion_0f0.velocity_y = static_cast<float>(launch + 7.0);
                return;
            }
            if (effect_000.object_y_0ec <= 0.0f) {
                float copied[3] = {-effect_000.reset_zero_128, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    821, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                next_sequence_block();
                effect_000.motion_0f0.velocity_x = static_cast<float>(effect_000.motion_0f0.velocity_x * 0.25);
                const float launch = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(60))) * static_cast<double>(0.1f));
                effect_000.motion_0f0.velocity_y = static_cast<float>(launch + 7.0);
                return;
            }
        }
        if (_root_state.sequence_13e <= 1) {
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        }
        if (_root_state.sequence_13e == 1) {
            effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y - 0.25);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 35.0);
            if (_root_state.alpha_113 < 5)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 5);
        }
        if (_root_state.sequence_13e == 2) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.02f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.02f));
            if (_root_state.alpha_113 < 10)
                goto clear_alpha_and_retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
        }
        if (_root_state.sequence_13e == 3) {
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 35.0);
            effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec);
            effect_000.object_y_0ec = static_cast<float>(*reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0) + 100.0);
            // Target821 keeps these owner exits separate. The first two
            // retire through the shared812/821/822 tail; the last is private.
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 530 &&
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 531) {
                --_root_state.state_330;
                return;
            }
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) == 3 &&
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x140) >= 4) {
                --_root_state.state_330;
                return;
            }
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) >= 4) {
                --_root_state.state_330;
                return;
            }
        }
        if (_root_state.sequence_13e == 4) {
            effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec);
            effect_000.object_y_0ec = static_cast<float>(*reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0) + 100.0);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
        }
        goto bounded_projectile_advance;

    case 822:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        switch (_root_state.sequence_13e) {
        case 0:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0) {
                packet_822_health[0] = 0.0f;
                packet_822_health[1] = 0.0f;
                packet_822_health[2] = 2.0f;
                packet_822_health[3] = 0.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    822, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(packet_822_health), 4);
                packet_822_health[2] = 3.0f;
                retiring_action = 822;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_822_health);
                retiring_words = 4;
                goto emit_retiring_world;
            }
            if (_root_state.frame_140 == 0) {
                reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.85f));
                if (reinterpret_cast<float *>(copied_words_340)[1] < 0.5f)
                    reinterpret_cast<float *>(copied_words_340)[1] = 0.5f;
                if (_root_state.counter_144 >= 15)
                    _root_state.phase_index_184 = 0;
                if (reinterpret_cast<float *>(copied_words_340)[3] <= _root_state.counter_144) {
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    next_sequence_frame();
                    _root_state.phase_index_184 = 1;
                    _root_state.phase_state_180 = 0;
                    reinterpret_cast<float *>(copied_words_340)[1] = 5.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 360.0f, 100.0f);
                    const float heading = static_cast<float>(static_cast<float>(static_cast<unsigned int>(selector_random_roll(30))) - 15.0 + reinterpret_cast<float *>(copied_words_340)[0]);
                    reinterpret_cast<float *>(copied_words_340)[0] = heading;
                    effect_000.reset_zero_128 = heading;
                    float copied[4] = {heading, 0.0f, 1.0f, 0.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                        822, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), -1,
                        reinterpret_cast<const unsigned *>(copied), 4);
                    return;
                }
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            }
            if (_root_state.frame_140 == 1) {
                if (_root_state.frame_timer_142 == 0)
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(992, 10.0f, 10, 1, 2);
                if (_root_state.phase_state_180 != 0) {
                    packet_822_phase[0] = 0.0f;
                    packet_822_phase[1] = 0.0f;
                    packet_822_phase[2] = 2.0f;
                    packet_822_phase[3] = 0.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        822, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(packet_822_phase), 4);
                    packet_822_phase[2] = 3.0f;
                    retiring_action = 822;
                    retiring_packet = reinterpret_cast<const unsigned *>(packet_822_phase);
                    retiring_words = 4;
                    goto emit_retiring_world;
                }
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 0.1f, 100.0f);
                effect_000.reset_zero_128 = reinterpret_cast<float *>(copied_words_340)[0];
                reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + 1.5);
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
                if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec < -400.0 || effect_000.object_y_0ec > 1080.0)
                    goto retire;
            }
            break;
        case 1:
            if (!_root_state.parent_object_34c)
                goto retire;
            effect_000.object_x_0e8 = _root_state.parent_object_34c->x_ec;
            effect_000.object_y_0ec = _root_state.parent_object_34c->y_f0;
            effect_000.reset_zero_128 = _root_state.parent_object_34c->heading_12c;
            effect_000.reset_one_118 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(_root_state.counter_144 * 10.0)) * static_cast<double>(0.1f) + 1.0);
            effect_000.reset_one_11c = effect_000.reset_one_118;
            _root_state.alpha_113 = _root_state.alpha_113 <= 205 ? static_cast<unsigned char>(_root_state.alpha_113 + 50) : 255;
            break;
        case 2: case 3:
            effect_000.reset_one_118 = _root_state.sequence_13e == 2 ?
                static_cast<float>(effect_000.reset_one_118 - static_cast<double>(0.05f)) :
                static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.2f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 20)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 20);
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 20);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 20);
            break;
        case 4:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            effect_000.reset_zero_128 += this->state_370;
            if (_root_state.frame_timer_142 == 0) {
                // Target publishes the last packet word after the first RNG call.
                float copied[4];
                copied[0] = 0.0f;
                copied[1] = 0.0f;
                copied[2] = static_cast<unsigned int>(selector_random_roll(100)) < 50u ? 5.0f : 6.0f;
                copied[3] = 0.0f;
                const double origin_y = effect_000.object_y_0ec + 100.0;
                const double origin_x = effect_000.object_x_0e8 + 100.0;
                // Actual arguments retain VC8's metadata/direction/Y/X preparation order.
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    822,
                    static_cast<float>(origin_x - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))),
                    static_cast<float>(origin_y - static_cast<float>(static_cast<unsigned int>(selector_random_roll(200)))),
                    static_cast<unsigned char>(1 - 2 * (static_cast<unsigned int>(selector_random_roll(100)) > 50u)),
                    1, reinterpret_cast<const unsigned *>(copied), 4);
            }
            if (this->state_370 > 0.0f) {
                this->state_370 = static_cast<float>(this->state_370 - static_cast<double>(0.1f));
                if (this->state_370 < static_cast<double>(0.1f))
                    this->state_370 = 0.1f;
            }
            if (this->state_370 < 0.0f) {
                this->state_370 = static_cast<float>(this->state_370 + static_cast<double>(0.1f));
                if (this->state_370 > static_cast<double>(-0.1f))
                    this->state_370 = -0.1f;
            }
            if (_root_state.channel_112 < 15) {
                --_root_state.state_330;
                return;
            }
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 15);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 15);
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
            effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y + static_cast<double>(0.1f));
            break;
        case 5: case 6:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.99f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.005f));
            if (_root_state.alpha_113 < 4)
                goto retire;
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 4);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 4);
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 4);
            effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y - static_cast<double>(0.1f));
            if (effect_000.motion_0f0.velocity_x < 1.0f)
                effect_000.motion_0f0.velocity_y = 1.0f;
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
            --_root_state.state_330;
        return;

    case 825: {
        const short owner_action = *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c);
        if (_root_state.sequence_13e == 0) {
            if (owner_action != 560 && owner_action != 561 && owner_action != 565 && owner_action != 566 && owner_action != 614)
                goto retire;
            effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec);
            effect_000.object_y_0ec = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0);
        }
        if (_root_state.sequence_13e == 1 && owner_action != 614 && owner_action != 565 && owner_action != 566)
            goto retire;
        if (owner_action != 560 && owner_action != 561 && owner_action != 565 && owner_action != 566 && owner_action != 614)
            return;
        if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x186) != 0)
            return;
        if (_root_state.sequence_13e == 1) {
            effect_000.reset_zero_128 = reinterpret_cast<float *>(copied_words_340)[0];
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], 35.0f);
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c * static_cast<double>(0.85f));
        }
        goto advance_with_sequence_one_retirement;
    }

    case 848:
        switch (_root_state.sequence_13e) {
        case 1:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.025f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 302 ||
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x140) == 0)
                goto retire;
            break;
        case 3:
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 6.0);
            if (_root_state.state_364 == 0) {
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->position_relative_to_owner_offsets(150, 65);
                if (_root_state.counter_144 % 3 == 0) {
                    float copied[3] = {effect_000.reset_zero_128, 0.0f, 4.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        848, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 306 ||
                        (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) == 0 &&
                         *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x140) == 0) ||
                        *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) == 2) {
                    _root_state.state_364 = 1;
                    return;
                }
            } else {
                if (_root_state.alpha_113 < 20)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 20);
            }
            break;
        case 4:
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 5.0);
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.05f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 20)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 20);
            break;
        case 5:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 308)
                goto retire;
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->position_relative_to_owner_offsets(0, 0);
            break;
        }
        if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x186) != 0)
            return;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            goto retire;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && (_root_state.sequence_13e == 2 || _root_state.sequence_13e == 6))
            goto retire;
        return;

    case 850:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        if (_root_state.phase_state_180 == 6) {
            _root_state.phase_state_180 = 0;
            _root_state.phase_index_184 = 1;
        }
        if (_root_state.phase_state_180 != 0 && _root_state.frame_140 < 2) {
            publish_battle_layout_scalar(2.0f);
            _root_state.frame_timer_142 = 0;
            _root_state.frame_140 = 2;
            effect_000.reset_zero_120 = 0.0f;
            effect_000.reset_zero_124 = 0.0f;
            effect_000.reset_zero_128 = 0.0f;
            effect_000.reset_one_118 = 4.0f;
            effect_000.reset_one_11c = 4.0f;
            float copied[3] = {0.0f, 0.0f, static_cast<float>(_root_state.sequence_13e)};
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                860, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                reinterpret_cast<const unsigned *>(copied), 3);
            for (int remaining = 4; remaining != 0; --remaining) {
                copied[0] = static_cast<float>(mt19937_next_u32() % 360u);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    861, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
            }
            return;
        }
        if (_root_state.frame_140 == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(
                0.0f, static_cast<float>(this->state_370 + 1.0), 100.0f);
            this->state_370 = static_cast<float>(this->state_370 + static_cast<double>(0.05f));
            if (this->state_370 >= 2.5f)
                this->state_370 = 2.5f;
            _root_state.state_366 = static_cast<short>(_root_state.state_366 + 15);
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            if (effect_000.reset_one_118 > 1.0f) {
                effect_000.reset_one_118 = 1.0f;
                effect_000.reset_one_11c = 1.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(
                    static_cast<unsigned short>(993 - _root_state.sequence_13e), 40.0f, 15, 1, 2);
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(_root_state.state_366 * static_cast<double>(0.01f)));
        }
        if (_root_state.frame_140 == 1) {
            _root_state.state_366 = static_cast<short>(_root_state.state_366 + 75);
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 2.0f, 100.0f);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(_root_state.state_366 * static_cast<double>(0.01f)));
        }
        if (_root_state.frame_140 == 2) {
            effect_000.motion_0f0.velocity_x = 0.0f;
            effect_000.motion_0f0.velocity_y = 0.0f;
            _root_state.state_366 = 0;
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 - static_cast<double>(0.2f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c - static_cast<double>(0.2f));
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            if (effect_000.reset_one_118 < 0.0f) {
                --_root_state.state_330;
                return;
            }
        }
        reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
            set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(_root_state.state_366 * static_cast<double>(0.01f)));
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
        if (effect_000.object_x_0e8 > 1480.0 || effect_000.object_x_0e8 < -200.0 || effect_000.object_y_0ec > 1580.0 || effect_000.object_y_0ec < -640.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 851:
        if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 604) {
            effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec);
            effect_000.object_y_0ec = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0);
        }
        if (_root_state.phase_state_180 != 0) {
            _root_state.state_364 = static_cast<short>(_root_state.state_364 + 1);
            if (_root_state.state_364 > 2) {
                _root_state.state_364 = 0;
                _root_state.phase_state_180 = 0;
            }
        }
        if (_root_state.sequence_13e == 1) {
            if (_root_state.counter_144 == 60) {
                float copied = 2.0f;
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->spawn_owned_object_via_manager(
                    851, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<int>(&copied), 1);
            }
            if (_root_state.counter_144 > 60) {
                _root_state.phase_index_184 = 0;
                _root_state.state_368 = static_cast<short>(_root_state.state_368 + 4);
                if (_root_state.state_368 > 90)
                    goto retire;
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * 0.75);
            }
        }
        if (_root_state.sequence_13e == 2) {
            effect_000.reset_one_118 = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.05f) + effect_000.reset_one_118);
            effect_000.reset_one_11c = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.05f) + effect_000.reset_one_11c);
            if (_root_state.alpha_113 <= 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
        }
        goto advance_and_retire_on_completion;

    case 852:
        if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 609) {
            effect_000.object_x_0e8 = static_cast<float>(effect_000.object_facing_100 * 228 + *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec));
            effect_000.object_y_0ec = static_cast<float>(*reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0) + 93.0);
        }
        if (_root_state.sequence_13e < 2) {
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 609 ||
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) > 1 || _root_state.phase_index_184 == 0) {
                *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x738) = 1;
                effect_000.reset_one_118 = 3.0f;
                effect_000.reset_one_11c = 3.0f;
                select_sequence(2);
                return;
            }
            if (_root_state.counter_144 % 10 == 0) {
                float copied[3] = {0.0f, 0.0f, 3.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    852, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
            }
        }
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 2.0);
        if (_root_state.phase_state_180 == 6) {
            _root_state.phase_index_184 = static_cast<unsigned char>(_root_state.phase_index_184 + 1);
            _root_state.phase_state_180 = 0;
        }
        if (_root_state.phase_state_180 != 0) {
            _root_state.state_364 = static_cast<short>(_root_state.state_364 + 1);
            if (_root_state.state_364 > 5) {
                _root_state.state_364 = 0;
                _root_state.phase_state_180 = 0;
            }
        }
        if (_root_state.sequence_13e == 2) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.8f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c * static_cast<double>(0.8f));
            if (_root_state.alpha_113 < 15)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
        }
        if (_root_state.sequence_13e == 3) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            if (_root_state.alpha_113 < 20)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 20);
        }
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 3)
            goto retire;
        return;

    case 853:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
        if (_root_state.frame_timer_142 == 0 && _root_state.frame_140 == 1) {
            _root_state.phase_state_180 = 0;
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(
                static_cast<unsigned short>(993 - _root_state.sequence_13e), 40.0f, 15, 1, 2);
        }
        if (_root_state.phase_state_180 != 0 && _root_state.frame_140 < 2) {
            publish_battle_layout_scalar(2.0f);
            _root_state.frame_timer_142 = 0;
            _root_state.frame_140 = 2;
            effect_000.reset_zero_120 = 0.0f;
            effect_000.reset_zero_124 = 0.0f;
            effect_000.reset_zero_128 = 0.0f;
            effect_000.reset_one_118 = 4.0f;
            effect_000.reset_one_11c = 4.0f;
            float copied[3] = {0.0f, 0.0f, static_cast<float>(_root_state.sequence_13e)};
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                860, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                reinterpret_cast<const unsigned *>(copied), 3);
            for (int remaining = 4; remaining != 0; --remaining) {
                copied[0] = static_cast<float>(mt19937_next_u32() % 360u);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    861, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
            }
            return;
        }
        if (_root_state.frame_140 == 0) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 2.0f, 100.0f);
            _root_state.state_366 = static_cast<short>(_root_state.state_366 - 50);
            if (_root_state.state_366 < 0) {
                _root_state.state_366 = 0;
                _root_state.frame_140 = 1;
                _root_state.frame_timer_142 = 0;
                effect_000.reset_one_118 = 1.5f;
                effect_000.reset_one_11c = 1.5f;
                return;
            }
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            if (effect_000.reset_one_118 > 1.5f) {
                effect_000.reset_one_118 = 1.5f;
                effect_000.reset_one_11c = 1.5f;
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(_root_state.state_366 * static_cast<double>(0.01f)));
        }
        if (_root_state.frame_140 == 1) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 4.5f, 100.0f);
            _root_state.state_366 = static_cast<short>(_root_state.state_366 + 75);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(_root_state.state_366 * static_cast<double>(0.01f)));
        }
        if (_root_state.frame_140 == 2) {
            effect_000.motion_0f0.velocity_x = 0.0f;
            effect_000.motion_0f0.velocity_y = 0.0f;
            _root_state.state_366 = 0;
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 - static_cast<double>(0.2f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c - static_cast<double>(0.2f));
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            if (effect_000.reset_one_118 < 0.0f) {
                --_root_state.state_330;
                return;
            }
        }
        reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
            set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(_root_state.state_366 * static_cast<double>(0.01f)));
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
        if (effect_000.object_x_0e8 > 1680.0 || effect_000.object_x_0e8 < -400.0 || effect_000.object_y_0ec > 1480.0 || effect_000.object_y_0ec < -520.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 854:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        if (_root_state.phase_state_180 == 6) {
            _root_state.phase_state_180 = 0;
            _root_state.phase_index_184 = 1;
        }
        if (_root_state.phase_state_180 != 0 && _root_state.frame_140 < 2) {
            publish_battle_layout_scalar(2.0f);
            _root_state.frame_timer_142 = 0;
            _root_state.frame_140 = 2;
            effect_000.reset_zero_120 = 0.0f;
            effect_000.reset_zero_124 = 0.0f;
            effect_000.reset_zero_128 = 0.0f;
            effect_000.reset_one_118 = 4.0f;
            effect_000.reset_one_11c = 4.0f;
            return;
        }
        if (_root_state.frame_140 == 0) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.1f));
            if (effect_000.reset_one_118 > 1.0f) {
                effect_000.reset_one_118 = 1.0f;
                effect_000.reset_one_11c = 1.0f;
                _root_state.frame_timer_142 = 0;
                _root_state.frame_140 = 1;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(
                    static_cast<unsigned short>(993 - _root_state.sequence_13e), 40.0f, 15, 1, 2);
            }
        }
        if (_root_state.frame_140 < 2) {
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->turn_heading_toward_related(0.0f, 0.25f, 50.0f);
            _root_state.state_366 = static_cast<short>(_root_state.state_366 + 50);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(_root_state.state_366 * static_cast<double>(0.01f) + 10.0));
        }
        if (_root_state.frame_140 == 2) {
            effect_000.motion_0f0.velocity_x = 0.0f;
            effect_000.motion_0f0.velocity_y = 0.0f;
            _root_state.state_366 = 0;
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 - static_cast<double>(0.2f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c - static_cast<double>(0.2f));
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            if (effect_000.reset_one_118 < 0.0f) {
                --_root_state.state_330;
                return;
            }
        }
        reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
            set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], static_cast<float>(_root_state.state_366 * static_cast<double>(0.01f)));
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
        if (effect_000.object_x_0e8 > 1480.0 || effect_000.object_x_0e8 < -200.0 || effect_000.object_y_0ec > 1280.0 || effect_000.object_y_0ec < -320.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 855:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        if (_root_state.phase_state_180 == 6)
            _root_state.phase_state_180 = 0;
        _root_state.state_36a = static_cast<short>(_root_state.state_36a + 5);
        if (_root_state.state_36a > 90)
            _root_state.state_36a = 90;
        effect_000.reset_one_11c = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(_root_state.state_36a)));
        effect_000.reset_one_118 = static_cast<float>(4.0 - lookup_orientation_sine_quantized_abs(static_cast<float>(_root_state.state_36a)) * 3.0);
        if (_root_state.state_364 == 0) {
            effect_000.motion_0f0.velocity_x = 1.5f;
            effect_000.motion_0f0.velocity_y = 0.0f;
            if (_root_state.counter_144 > 10) {
                effect_000.reset_one_118 = 1.0f;
                effect_000.reset_one_11c = effect_000.reset_one_118;
                _root_state.state_368 = 0;
                _root_state.state_366 = 0;
                _root_state.state_364 = 1;
            }
        }
        if (_root_state.state_364 == 1) {
            _root_state.phase_index_184 = 1;
            if (_root_state.phase_state_180 == 6)
                _root_state.phase_state_180 = 0;
            if (_root_state.phase_state_180 != 0) {
                _root_state.state_368 = static_cast<short>(_root_state.state_368 + 1);
                if (_root_state.state_368 > 10) {
                    _root_state.state_368 = 0;
                    _root_state.phase_state_180 = 0;
                }
            }
            _root_state.state_366 = static_cast<short>(_root_state.state_366 + 1);
            if (_root_state.state_366 > 300)
                _root_state.state_364 = 2;
        }
        if (_root_state.state_364 == 2) {
            _root_state.phase_index_184 = 0;
            if (_root_state.alpha_113 < 8)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 8);
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 8);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 8);
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (effect_000.object_x_0e8 > 1480.0 || effect_000.object_x_0e8 < -200.0 || effect_000.object_y_0ec > 1280.0 || effect_000.object_y_0ec < -320.0) {
            --_root_state.state_330;
            return;
        }
        goto advance_and_retire_on_completion;

    case 856:
        if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 606) {
            effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec);
            effect_000.object_y_0ec = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0);
        }
        if (_root_state.phase_state_180 != 0) {
            _root_state.state_364 = static_cast<short>(_root_state.state_364 + 1);
            if (_root_state.state_364 > 2) {
                _root_state.state_364 = 0;
                _root_state.phase_state_180 = 0;
            }
        }
        if (_root_state.sequence_13e == 1) {
            if (_root_state.counter_144 == 120 || (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 606 && _root_state.counter_144 <= 119)) {
                _root_state.counter_144 = 121;
                float copied = 2.0f;
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->spawn_owned_object_via_manager(
                    856, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<int>(&copied), 1);
            }
            if (_root_state.counter_144 > 120) {
                _root_state.phase_index_184 = 0;
                _root_state.state_368 = static_cast<short>(_root_state.state_368 + 4);
                if (_root_state.state_368 > 90)
                    goto retire;
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * 0.75);
            }
        }
        if (_root_state.sequence_13e == 2) {
            effect_000.reset_one_118 = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.05f) + effect_000.reset_one_118);
            effect_000.reset_one_11c = static_cast<float>(lookup_orientation_cosine_quantized_abs(
                static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.05f) + effect_000.reset_one_11c);
            if (_root_state.alpha_113 <= 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
        }
        goto advance_and_retire_on_completion;

    case 858:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        if (_root_state.phase_state_180 == 6) {
            _root_state.phase_state_180 = 0;
            _root_state.phase_index_184 = static_cast<unsigned char>(_root_state.phase_index_184 + 1);
        }
        if (_root_state.phase_state_180 == 4 && static_cast<signed char>(_root_state.phase_index_184) > 0)
            _root_state.phase_state_180 = 0;
        if (_root_state.sequence_13e == 0) {
            if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0)
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], 15.0f);
            effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y - 0.5);
            if (static_cast<unsigned char>(has_crossed_stage_surface_while_descending())) {
                _root_state.state_364 = static_cast<short>(_root_state.state_364 + 1);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
                effect_000.motion_0f0.velocity_y = -effect_000.motion_0f0.velocity_y;
                if (effect_000.motion_0f0.velocity_y > 17.5f)
                    effect_000.motion_0f0.velocity_y = 17.5f;
                _root_state.phase_state_180 = 0;
                if (_root_state.state_364 >= 2 && _root_state.frame_140 == 0) {
                    set_sequence_frame(1);
                    _root_state.phase_index_184 = 0;
                    _root_state.counter_144 = 0;
                    return;
                }
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->replace_secondary_animation(992, 60.0f, 20, 1, 2);
            }
            if ((effect_000.object_x_0e8 > 1260.0f && effect_000.object_facing_100 == 1) || (effect_000.object_x_0e8 < 20.0f && effect_000.object_facing_100 == -1)) {
                effect_000.object_facing_100 = static_cast<signed char>(-effect_000.object_facing_100);
                _root_state.phase_state_180 = 0;
            }
            if (_root_state.frame_140 == 0 && _root_state.phase_index_184 == 0) {
                next_sequence_frame();
                _root_state.counter_144 = 0;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
            }
            if (_root_state.frame_140 == 1 && _root_state.counter_144 >= 30) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 - static_cast<double>(0.1f));
                effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c - static_cast<double>(0.1f));
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                if (effect_000.reset_one_118 < 0.0f)
                    goto retire;
            }
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
        }
        if (_root_state.sequence_13e == 1) {
            if (_root_state.alpha_113 < 12)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 12);
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 12);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 12);
        }
        if (_root_state.sequence_13e == 2) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + 0.25);
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + 0.25);
            if (_root_state.alpha_113 < 20)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 20);
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 20);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 20);
        }
        if (effect_000.object_x_0e8 > 1480.0 || effect_000.object_x_0e8 < -200.0 || effect_000.object_y_0ec > 1280.0 || effect_000.object_y_0ec < -320.0)
            goto retire;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.sequence_13e == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 1)
            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->release_secondary_animation_renderer();
        return;

    case 859:
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 &&
                _root_state.sequence_13e == 0) {
            _root_state.phase_index_184 = 99;
            _root_state.state_364 = 0;
        }
        if (_root_state.sequence_13e == 0) {
            effect_000.motion_0f0.velocity_x = 0.0f;
            effect_000.motion_0f0.velocity_y = 0.0f;
        }
        if (_root_state.sequence_13e == 1)
            effect_000.motion_0f0.velocity_x = static_cast<float>(effect_000.motion_0f0.velocity_x + static_cast<double>(0.05f));
        if (_root_state.phase_state_180 == 6) {
            ++_root_state.phase_index_184;
            _root_state.phase_state_180 = 0;
        }
        if (_root_state.phase_state_180 != 0) {
            ++_root_state.state_364;
            if (_root_state.state_364 > 5) {
                _root_state.state_364 = 0;
                _root_state.phase_state_180 = 0;
            }
        }
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 1.0);
        effect_000.object_x_0e8 = static_cast<float>(static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x + effect_000.object_x_0e8);
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (effect_000.object_x_0e8 > 1680.0 || effect_000.object_x_0e8 < -400.0)
            goto retire;
        goto advance_and_retire_on_completion;

    case 860: {
        const double pulse = lookup_orientation_sine_quantized_abs(
            static_cast<float>(_root_state.counter_144 * 6));
        effect_000.reset_one_118 = static_cast<float>(pulse * 2.0 + 1.0);
        effect_000.reset_one_11c = effect_000.reset_one_118;
        if (_root_state.alpha_113 < 25)
            goto retire;
        _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 25);
        goto advance_with_sequence_retirement;
    }
    case 861: {
        const float *const parameters = reinterpret_cast<float *>(copied_words_340);
        effect_000.reset_zero_128 = parameters[0];
        reinterpret_cast<CharacterObjectRuntime *>(
            reinterpret_cast<unsigned char *>(this) + 4)->set_oriented_components_f0_f4(
                parameters[0], parameters[1]);
        effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
        effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c * static_cast<double>(0.8f));
        if (_root_state.alpha_113 < 10)
            goto retire;
        _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
        effect_000.object_x_0e8 = static_cast<float>(static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x + effect_000.object_x_0e8);
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        goto advance_with_sequence_retirement;
    }
    case 866:
        if (_root_state.phase_state_180 != 0) {
            _root_state.state_366 = static_cast<short>(_root_state.state_366 + 1);
            if (_root_state.state_366 > 15) {
                _root_state.state_366 = 0;
                _root_state.phase_state_180 = 0;
            }
        }
        if (_root_state.sequence_13e <= 1) {
            switch (_root_state.state_364) {
            case 0: {
                const unsigned char *const owner = _root_state.fighter_owner_348;
                if (*reinterpret_cast<const short *>(owner + 0x13c) == 616) {
                    const short owner_sequence = *reinterpret_cast<const short *>(owner + 0x13e);
                    if (owner_sequence <= 2) {
                        effect_000.object_x_0e8 = *reinterpret_cast<const float *>(owner + 0xec);
                    } else if (owner_sequence <= 5) {
                        if (owner_sequence == 3 && *reinterpret_cast<const short *>(owner + 0x140) == 1 &&
                                *reinterpret_cast<const short *>(owner + 0x142) == 0) {
                            effect_000.reset_one_118 = 1.05f;
                            effect_000.reset_one_11c = 0.95f;
                        }
                        if (effect_000.reset_one_118 > 1.0f)
                            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 - static_cast<double>(0.005f));
                        if (effect_000.reset_one_11c < 1.0f)
                            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c + static_cast<double>(0.005f));
                        if (*reinterpret_cast<const short *>(owner + 0x13e) == 5) {
                            if (_root_state.state_368 % 30 == 0) {
                                float copied[3];
                                copied[2] = 2.0f;
                                for (float beam = 0.0f; beam < 8.0f; beam += 1.0f) {
                                    copied[0] = static_cast<float>(beam * 45.0);
                                    copied[1] = 30.0f;
                                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                        866, effect_000.object_x_0e8, stage_surface_height_at_x(reinterpret_cast<Fighter *>(this)),
                                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                        reinterpret_cast<const unsigned *>(copied), 3);
                                }
                            }
                            _root_state.phase_index_184 = 99;
                            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 2.0);
                        }
                        effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec);
                        effect_000.object_y_0ec = static_cast<float>(*reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0) - 150.0);
                        _root_state.state_368 = static_cast<short>(_root_state.state_368 + 1);
                    } else {
                        _root_state.state_364 = 1;
                        _root_state.phase_index_184 = 0;
                    }
                } else {
                    _root_state.state_364 = 1;
                    _root_state.phase_index_184 = 0;
                }
                break;
            }
            case 1:
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                break;
            }
        }
        if (_root_state.sequence_13e == 2) {
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.01f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] - 1.5);
            if (reinterpret_cast<float *>(copied_words_340)[1] < 0.5f)
                reinterpret_cast<float *>(copied_words_340)[1] = 0.5f;
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec = static_cast<float>(effect_000.motion_0f0.velocity_y * static_cast<double>(0.2f) + effect_000.object_y_0ec);
            if (_root_state.alpha_113 < 5)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 5);
        }
        goto advance_and_retire_on_completion;

    case 869:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        switch (_root_state.sequence_13e) {
        case 0:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 669) {
                this->state_37c = static_cast<float>(this->state_37c - 0.5);
                if (this->state_37c <= -15.0)
                    this->state_37c = -15.0f;
                reinterpret_cast<float *>(copied_words_340)[0] += this->state_37c;
                this->state_370 = static_cast<float>(this->state_370 + static_cast<double>(0.05f));
                if (this->state_370 >= 1.0f)
                    this->state_370 = 1.0f;
                effect_000.reset_zero_128 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(_root_state.counter_144 * 4.0)) * this->state_374);
                const float *const parameters = reinterpret_cast<float *>(copied_words_340);
                effect_000.object_x_0e8 = static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0]) * parameters[1] +
                    *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec));
                effect_000.object_y_0ec = static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0]) * reinterpret_cast<float *>(copied_words_340)[1] * this->state_370 +
                    (*reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0) + 100.0));
                if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) >= 2) {
                    packet_869_sequence[0] = 0.0f;
                    packet_869_sequence[1] = 0.0f;
                    packet_869_sequence[2] = 2.0f;
                    retiring_action = 869;
                    retiring_packet = reinterpret_cast<const unsigned *>(packet_869_sequence);
                    retiring_words = 3;
                    goto emit_retiring_world;
                }
            } else {
                this->state_37c = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(_root_state.counter_144)) * 10.0);
                reinterpret_cast<float *>(copied_words_340)[0] += this->state_37c;
                effect_000.reset_zero_128 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(_root_state.counter_144 * 4.0)) * this->state_374);
                const float *const parameters = reinterpret_cast<float *>(copied_words_340);
                effect_000.object_x_0e8 = static_cast<float>(lookup_orientation_cosine_quantized_abs(-parameters[0]) * parameters[1] +
                    *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec));
                effect_000.object_y_0ec = static_cast<float>(lookup_orientation_sine_quantized_abs(-parameters[0]) * reinterpret_cast<float *>(copied_words_340)[1] * this->state_370 +
                    (*reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0) + 100.0));
                if (lookup_orientation_sine_quantized_abs(reinterpret_cast<float *>(copied_words_340)[0]) < 0.0)
                    _root_state.direction_33c = 255;
                else
                    _root_state.direction_33c = 1;
                reinterpret_cast<float *>(copied_words_340)[1] += this->state_378;
                this->state_378 = static_cast<float>(this->state_378 - static_cast<double>(0.4f));
                if (this->state_378 < 0.0f)
                    this->state_378 = 0.0f;
            }
            if (_root_state.state_364 == 0 && reinterpret_cast<float *>(copied_words_340)[3] < *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x7ca)) {
                _root_state.state_364 = 1;
                float copied[3] = {0.0f, 0.0f, 1.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_parented_related_object(
                    869, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 2.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    869, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(23);
            }
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x7c8) <= 0 &&
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) != 669) {
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
            if (!_root_state.parent_object_34c)
                goto retire;
            effect_000.object_x_0e8 = _root_state.parent_object_34c->x_ec;
            effect_000.object_y_0ec = _root_state.parent_object_34c->y_f0;
            _root_state.alpha_113 = static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(_root_state.parent_object_34c->counter_144 * 3.0)) * 127.0 + 127.0);
            _root_state.channel_112 = static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(_root_state.parent_object_34c->counter_144 * 3.0)) * 127.0 + 127.0);
            _root_state.channel_111 = static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(
                static_cast<float>(_root_state.parent_object_34c->counter_144 * 3.0)) * 127.0 + 127.0);
            break;
        case 2:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.15f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 15)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
            _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 15);
            _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 15);
            break;
        case 3:
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
            effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
            if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec > 1000.0 || effect_000.object_y_0ec < -200.0) {
                --_root_state.state_330;
                return;
            }
            break;
        case 4:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + 0.5);
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        case 5:
            effect_000.reset_zero_128 += this->state_370;
            this->state_370 = static_cast<float>(this->state_370 * static_cast<double>(0.95f));
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.15f));
            effect_000.reset_one_11c = static_cast<float>(effect_000.reset_one_11c * static_cast<double>(0.97f));
            if (_root_state.counter_144 < 15 || _root_state.alpha_113 < 15)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 15);
            break;
        }
        goto advance_and_retire_on_completion;

    case 980:
        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->
            update_ping_pong_motion_and_periodic_spawn();
        goto advance_and_retire_on_completion;

    case 998:
        effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 5.0);
        if (_root_state.sequence_13e == 0) {
            // The owner is reread after the virtual sequence operation below.
            const unsigned char *const owner = _root_state.fighter_owner_348;
            if (*reinterpret_cast<const short *>(owner + 0x13c) > 153 &&
                    *reinterpret_cast<const short *>(owner + 0x13c) < 158) {
                effect_000.object_x_0e8 = static_cast<float>(effect_000.object_facing_100 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                effect_000.object_y_0ec = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 60.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) > 149 &&
                    *reinterpret_cast<const short *>(owner + 0x13c) < 154) {
                effect_000.object_x_0e8 = static_cast<float>(effect_000.object_facing_100 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                effect_000.object_y_0ec = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 94.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) == 158) {
                effect_000.object_x_0e8 = static_cast<float>(effect_000.object_facing_100 * 57 +
                    *reinterpret_cast<const float *>(owner + 0xec));
                effect_000.object_y_0ec = static_cast<float>(*reinterpret_cast<const float *>(owner + 0xf0) + 100.0);
            }
            if (*reinterpret_cast<const short *>(owner + 0x13c) < 150 ||
                    *reinterpret_cast<const short *>(owner + 0x13c) > 158) {
                next_sequence_block();
                _root_state.fighter_owner_348[0x751] = 0;
            }
        }
        if (_root_state.sequence_13e == 1) {
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
        }
        goto advance_and_retire_on_completion;

    case 900: {
        switch (_root_state.sequence_13e) {
        case 0:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0) {
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
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (_root_state.counter_144 >= 40) {
                completed_sequence_zero[0] = reinterpret_cast<float *>(copied_words_340)[0];
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
            if (_root_state.phase_state_180 != 0 || *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0) {
                dead_sequence_one[0] = 0.0f;
                dead_sequence_one[1] = 0.0f;
                dead_sequence_one[2] = 2.0f;
                retiring_packet = reinterpret_cast<const unsigned *>(dead_sequence_one);
                retiring_words = 3;
                retiring_action = 900;
                goto emit_retiring_world;
            }
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + static_cast<double>(0.4f));
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec < -200.0 || effect_000.object_y_0ec > 900.0)
                goto retire;
            break;
        case 2:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.9f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.counter_144 >= 5) {
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_110 = static_cast<unsigned char>(_root_state.channel_110 - 10);
            }
            break;
        case 3:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0)
                goto retire;
            if (_root_state.counter_144 % 6 == 0) {
                float copied[3] = {reinterpret_cast<float *>(copied_words_340)[0], 0.0f, 1.0f};
                const float radius = static_cast<float>(this->state_370 * 40.0);
                if (this->state_370 == 0.0f) {
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        900, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                } else {
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        900, static_cast<float>(lookup_orientation_cosine_quantized_abs(
                            static_cast<float>(90.0 - copied[0])) * radius * static_cast<float>(effect_000.object_facing_100) + effect_000.object_x_0e8),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(
                            static_cast<float>(90.0 - copied[0])) * radius + effect_000.object_y_0ec),
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        900, static_cast<float>(lookup_orientation_cosine_quantized_abs(
                            static_cast<float>(-copied[0] - 90.0)) * radius * static_cast<float>(effect_000.object_facing_100) + effect_000.object_x_0e8),
                        static_cast<float>(lookup_orientation_sine_quantized_abs(
                            static_cast<float>(-copied[0] - 90.0)) * radius + effect_000.object_y_0ec),
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                this->state_370 = static_cast<float>(this->state_370 + 1.0);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(0);
            }
            if (reinterpret_cast<float *>(copied_words_340)[3] <= this->state_370)
                goto retire;
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        goto advance_and_retire_on_completion;

    }

    case 901:
        switch (_root_state.sequence_13e) {
        case 0: {
            reinterpret_cast<float *>(copied_words_340)[0] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[0] + 3.0);
            reinterpret_cast<float *>(copied_words_340)[1] += this->state_370;
            this->state_370 = static_cast<float>(this->state_370 * static_cast<double>(0.9f));
            if (lookup_orientation_sine_quantized_abs(-reinterpret_cast<float *>(copied_words_340)[0]) > 0.0)
                _root_state.direction_33c = 255;
            else
                _root_state.direction_33c = 1;
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0 || _root_state.value_174 <= -1500) {
                float copied[3] = {0.0f, 0.0f, 4.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[1] = 0.75f;
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                for (int particle = 0; particle < 8; ++particle) {
                    copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(20)) + 5.0);
                    copied[2] = 5.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                --_root_state.state_330;
                return;
            }
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 2.0);
            effect_000.object_x_0e8 = static_cast<float>(lookup_orientation_cosine_quantized_abs(-reinterpret_cast<float *>(copied_words_340)[0]) *
                reinterpret_cast<float *>(copied_words_340)[1] * static_cast<float>(effect_000.object_facing_100) + *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec));
            effect_000.object_y_0ec = static_cast<float>(lookup_orientation_sine_quantized_abs(-reinterpret_cast<float *>(copied_words_340)[0]) *
                reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.2f) + (*reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0) + 100.0));
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x730) == 1) {
                float copied[4] = {0.0f, 0.75f, 3.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[0] = reinterpret_cast<float *>(copied_words_340)[0];
                copied[1] = static_cast<float>(_root_state.value_174 * 0.25);
                copied[2] = 1.0f;
                copied[3] = reinterpret_cast<float *>(copied_words_340)[3];
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 4);
                --_root_state.state_330;
                return;
            }
            break;
        }
        case 1: {
            const unsigned *final_packet;
            if (_root_state.phase_state_180 == 6) {
                _root_state.phase_index_184 = static_cast<unsigned char>(_root_state.phase_index_184 + 1);
                _root_state.phase_state_180 = 0;
                _root_state.value_174 = static_cast<short>(_root_state.value_174 - 20);
            }
            const float intensity = static_cast<float>((_root_state.value_174 + 1000) / 1000.0);
            const unsigned char color = static_cast<unsigned char>(static_cast<int>(intensity * 255.0));
            _root_state.channel_111 = color;
            _root_state.channel_110 = color;
            if (_root_state.phase_state_180 != 0 && _root_state.state_366 == 0) {
                _root_state.state_366 = 1;
                _root_state.value_174 = static_cast<short>(_root_state.value_174 - 500);
            }
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0 || _root_state.value_174 <= -1000) {
                health_packet[0] = 0.0f;
                health_packet[1] = 0.0f;
                health_packet[2] = 4.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(health_packet), 3);
                for (int particle = 0; particle < 8; ++particle) {
                    health_packet[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    health_packet[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(20)) + 5.0);
                    health_packet[2] = 5.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(health_packet), 3);
                }
                health_packet[1] = 0.75f;
                health_packet[2] = 3.0f;
                final_packet = reinterpret_cast<const unsigned *>(health_packet);
                goto emit_901_burst_tail;
            }
            effect_000.reset_zero_128 += this->state_370;
            if ((static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x > 0.0 && effect_000.object_x_0e8 > 1240.0f) ||
                    (static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x < 0.0 && effect_000.object_x_0e8 < 40.0f))
                effect_000.object_facing_100 = static_cast<signed char>(-effect_000.object_facing_100);
            effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y - 0.5);
            if (effect_000.object_y_0ec <= 80.0f && effect_000.motion_0f0.velocity_y < 0.0f) {
                if (reinterpret_cast<float *>(copied_words_340)[3] > _root_state.state_364) {
                    _root_state.state_364 = static_cast<short>(_root_state.state_364 + 1);
                    _root_state.state_366 = 0;
                    _root_state.value_174 = static_cast<short>(_root_state.value_174 - 250);
                    _root_state.phase_index_184 = 1;
                    _root_state.phase_state_180 = 0;
                    effect_000.motion_0f0.velocity_y = static_cast<float>(-effect_000.motion_0f0.velocity_y * static_cast<double>(0.95f));
                    float copied[3] = {0.0f, 0.0f, 6.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        901, effect_000.object_x_0e8, stage_surface_height_at_x(reinterpret_cast<Fighter *>(this)),
                        static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                } else {
                    exhausted_packet[0] = 0.0f;
                    exhausted_packet[1] = 0.0f;
                    exhausted_packet[2] = 4.0f;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(exhausted_packet), 3);
                    for (int particle = 0; particle < 8; ++particle) {
                        exhausted_packet[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        exhausted_packet[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(20)) + 5.0);
                        exhausted_packet[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            901, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
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
            effect_000.reset_one_118 += reinterpret_cast<float *>(copied_words_340)[1];
            effect_000.reset_one_11c = effect_000.reset_one_118;
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.95f));
            if (_root_state.counter_144 >= 5) {
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 10);
            }
            break;
        case 4:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.9f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.counter_144 >= 5) {
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 10);
            }
            break;
        case 5:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.99f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.95f));
            if (_root_state.counter_144 >= 5) {
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 10);
            }
            break;
        case 6:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.05f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.95f));
            if (_root_state.counter_144 >= 0) {
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 10);
            }
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        return;

    case 902:
        switch (_root_state.sequence_13e) {
        case 0:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0)
                _root_state.state_364 = 2;
            if (_root_state.state_364 == 0) {
                this->state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.2f) + 5.0);
                effect_000.reset_one_118 = static_cast<float>((1.0 - this->state_370) * this->state_374);
                effect_000.reset_one_11c = effect_000.reset_one_118;
                this->state_370 = static_cast<float>(this->state_370 * static_cast<double>(0.95f));
                reinterpret_cast<ReimuOwnerBoundaryView *>(_root_state.fighter_owner_348)->x_lower_0 = static_cast<float>(effect_000.object_x_0e8 - effect_000.reset_one_118 * 45.0);
                reinterpret_cast<ReimuOwnerBoundaryView *>(_root_state.fighter_owner_348)->x_upper_0 = static_cast<float>(effect_000.reset_one_118 * 45.0 + effect_000.object_x_0e8);
                reinterpret_cast<ReimuOwnerBoundaryView *>(_root_state.fighter_owner_348)->y_upper_0 = static_cast<float>(effect_000.reset_one_118 * 45.0 + effect_000.object_y_0ec);
                reinterpret_cast<ReimuOwnerBoundaryView *>(_root_state.fighter_owner_348)->y_lower_0 = static_cast<float>(effect_000.object_y_0ec - effect_000.reset_one_118 * 45.0);
            }
fade_902:
            if (_root_state.state_364 == 2) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = effect_000.reset_one_118;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_110 = static_cast<unsigned char>(_root_state.channel_110 - 10);
            }
            break;
        case 1:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0)
                _root_state.state_364 = 2;
            if (_root_state.state_364 == 0) {
                this->state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(_root_state.counter_144 * 2.0)) * 0.5 + 10.0);
                effect_000.reset_one_118 = static_cast<float>((1.0 - this->state_370) * this->state_374);
                effect_000.reset_one_11c = effect_000.reset_one_118;
                this->state_370 = static_cast<float>(this->state_370 * static_cast<double>(0.95f));
                reinterpret_cast<ReimuOwnerBoundaryView *>(_root_state.fighter_owner_348)->x_lower_1 = static_cast<float>(effect_000.object_x_0e8 - effect_000.reset_one_118 * 45.0);
                reinterpret_cast<ReimuOwnerBoundaryView *>(_root_state.fighter_owner_348)->x_upper_1 = static_cast<float>(effect_000.reset_one_118 * 45.0 + effect_000.object_x_0e8);
                reinterpret_cast<ReimuOwnerBoundaryView *>(_root_state.fighter_owner_348)->y_upper_1 = static_cast<float>(effect_000.reset_one_118 * 45.0 + effect_000.object_y_0ec);
                reinterpret_cast<ReimuOwnerBoundaryView *>(_root_state.fighter_owner_348)->y_lower_1 = static_cast<float>(effect_000.object_y_0ec - effect_000.reset_one_118 * 45.0);
            }
            goto fade_902;
        case 2: {
            if (_root_state.phase_state_180 != 0 || *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0) {
                packet_902_retirement[0] = 0.0f;
                packet_902_retirement[1] = 0.0f;
                packet_902_retirement[2] = 3.0f;
                retiring_action = 902;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_902_retirement);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            double directed_x_heading = effect_000.object_facing_100;
            directed_x_heading *= effect_000.motion_0f0.velocity_x;
            effect_000.reset_zero_128 = atan2_degrees(effect_000.motion_0f0.velocity_y, static_cast<float>(directed_x_heading));
            if (_root_state.state_364 == 0) {
                if (effect_000.motion_0f0.velocity_y > 0.0 && effect_000.object_y_0ec > *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7b8)) {
                    effect_000.motion_0f0.velocity_y = -effect_000.motion_0f0.velocity_y;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    effect_000.object_y_0ec = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7c0);
                    _root_state.state_364 = 1;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (effect_000.motion_0f0.velocity_y < 0.0 && effect_000.object_y_0ec < *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7c0)) {
                    effect_000.motion_0f0.velocity_y = -effect_000.motion_0f0.velocity_y;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    effect_000.object_y_0ec = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7b8);
                    _root_state.state_364 = 1;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                double directed_x_primary_right = effect_000.object_facing_100;
                directed_x_primary_right *= effect_000.motion_0f0.velocity_x;
                if (directed_x_primary_right > 0.0 && effect_000.object_x_0e8 > *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7b0)) {
                    effect_000.motion_0f0.velocity_x = -effect_000.motion_0f0.velocity_x;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7a8);
                    _root_state.state_364 = 1;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                double directed_x_primary_left = effect_000.object_facing_100;
                directed_x_primary_left *= effect_000.motion_0f0.velocity_x;
                if (directed_x_primary_left < 0.0 && effect_000.object_x_0e8 < *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7a8)) {
                    effect_000.motion_0f0.velocity_x = -effect_000.motion_0f0.velocity_x;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7b0);
                    _root_state.state_364 = 1;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
            }
            if ((g_match_identifier == 3 || g_match_identifier == 2) && _root_state.state_364 == 1) {
                if (effect_000.motion_0f0.velocity_y > 0.0 && effect_000.object_y_0ec > *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7bc)) {
                    effect_000.motion_0f0.velocity_y = -effect_000.motion_0f0.velocity_y;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    effect_000.object_y_0ec = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7c4);
                    _root_state.state_364 = 2;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                if (effect_000.motion_0f0.velocity_y < 0.0 && effect_000.object_y_0ec < *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7c4)) {
                    effect_000.motion_0f0.velocity_y = -effect_000.motion_0f0.velocity_y;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    effect_000.object_y_0ec = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7bc);
                    _root_state.state_364 = 2;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                double directed_x_secondary_right = effect_000.object_facing_100;
                directed_x_secondary_right *= effect_000.motion_0f0.velocity_x;
                if (directed_x_secondary_right > 0.0 && effect_000.object_x_0e8 > *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7b4)) {
                    effect_000.motion_0f0.velocity_x = -effect_000.motion_0f0.velocity_x;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7ac);
                    _root_state.state_364 = 2;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                double directed_x_secondary_left = effect_000.object_facing_100;
                directed_x_secondary_left *= effect_000.motion_0f0.velocity_x;
                if (directed_x_secondary_left < 0.0 && effect_000.object_x_0e8 < *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7ac)) {
                    effect_000.motion_0f0.velocity_x = -effect_000.motion_0f0.velocity_x;
                    float copied[3] = {0.0f, 0.0f, 3.0f};
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                    effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0x7b4);
                    _root_state.state_364 = 2;
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        902, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
            }
            if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec < -200.0 || effect_000.object_y_0ec > 900.0)
                goto retire;
            break;
        }
        case 3:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.9f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.counter_144 >= 5) {
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            }
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        goto advance_and_retire_on_completion;

    case 903:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        switch (_root_state.sequence_13e) {
        case 0: case 1: case 2:
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0) {
                packet_903_health[0] = 0.0f;
                packet_903_health[1] = 0.0f;
                packet_903_health[2] = static_cast<float>(_root_state.sequence_13e + 6.0);
                retiring_action = 903;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_903_health);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            if (_root_state.state_364 == 0) {
                reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.95f));
                reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                    set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
                if (_root_state.counter_144 >= 40) {
                    _root_state.phase_index_184 = 1;
                    _root_state.phase_state_180 = 0;
                    effect_000.motion_0f0.velocity_x = 0.0f;
                    effect_000.motion_0f0.velocity_y = 0.0f;
                    _root_state.state_364 = 1;
                    _root_state.counter_144 = 0;
                }
                if (_root_state.counter_144 % 10 == 0) {
                    float copied[3];
                    copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(30)) * static_cast<double>(0.1f) + 2.0);
                    copied[2] = static_cast<float>(_root_state.sequence_13e + 3.0);
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        903, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
            }
            if (_root_state.state_364 == 1 && *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c) == 740 &&
                    *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e) == 6) {
                const int axis = selector_random_roll(2);
                const float width = static_cast<float>(static_cast<unsigned int>(selector_random_roll(120)) * static_cast<double>(0.1f));
                if (g_match_identifier == 1) {
                    for (float sector = 0.0f; sector < 2.0f; sector += 1.0f) {
                        packet_903_burst[0] = static_cast<float>(sector * 180.0);
                        if (axis == 0)
                            packet_903_burst[0] = static_cast<float>(packet_903_burst[0] + 90.0);
                        packet_903_burst[1] = width;
                        packet_903_burst[2] = static_cast<float>(_root_state.sequence_13e);
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            904, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(packet_903_burst), 3);
                    }
                } else if (g_match_identifier == 2) {
                    for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                        packet_903_burst[0] = static_cast<float>(sector * 90.0);
                        packet_903_burst[1] = width;
                        packet_903_burst[2] = static_cast<float>(_root_state.sequence_13e);
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            904, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(packet_903_burst), 3);
                    }
                } else if (g_match_identifier == 3) {
                    for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                        packet_903_burst[0] = static_cast<float>(sector * 90.0);
                        packet_903_burst[1] = width;
                        packet_903_burst[2] = static_cast<float>(_root_state.sequence_13e);
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            904, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(packet_903_burst), 3);
                    }
                }
                packet_903_burst[0] = 0.0f;
                packet_903_burst[1] = 0.5f;
                packet_903_burst[2] = static_cast<float>(_root_state.sequence_13e + 6.0);
                retiring_action = 903;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_903_burst);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            break;
        case 3: case 4: case 5:
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.99f));
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.9f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        case 6: case 7: case 8:
            effect_000.reset_one_118 += reinterpret_cast<float *>(copied_words_340)[1];
            effect_000.reset_one_11c = effect_000.reset_one_118;
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.92f));
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (effect_000.object_x_0e8 > 1680.0 || effect_000.object_x_0e8 < -400.0 || effect_000.object_y_0ec > 1480.0 || effect_000.object_y_0ec < -520.0) {
            --_root_state.state_330;
            return;
        }
        goto advance_and_retire_on_completion;

    case 904:
        if (_root_state.phase_state_180 == 5)
            goto retire;
        switch (_root_state.sequence_13e) {
        case 0: case 1: case 2:
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0 ||
                    static_cast<signed char>(_root_state.phase_index_184) <= 0) {
                float copied[3];
                for (int particle = 0; particle < 4; ++particle) {
                    copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(100)) * static_cast<double>(0.1f) + 5.0);
                    copied[2] = static_cast<float>(_root_state.sequence_13e + 3.0);
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        904, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(copied), 3);
                }
                goto retire;
            }
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + static_cast<double>(0.15f));
            if (_root_state.counter_144 % 10 == 0) {
                float copied[3];
                copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(30)) * static_cast<double>(0.1f) + 2.0);
                copied[2] = static_cast<float>(_root_state.sequence_13e + 3.0);
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    903, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
            }
            break;
        case 3: case 4: case 5:
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.98f));
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 * static_cast<double>(0.9f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (effect_000.object_x_0e8 > 1680.0 || effect_000.object_x_0e8 < -400.0 || effect_000.object_y_0ec > 1480.0 || effect_000.object_y_0ec < -520.0) {
            --_root_state.state_330;
            return;
        }
        goto advance_and_retire_on_completion;

    case 905:
        switch (_root_state.sequence_13e) {
        case 0:
            effect_000.reset_zero_128 += reinterpret_cast<float *>(copied_words_340)[1];
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 7500 && _root_state.state_364 != 2) {
                _root_state.state_364 = 2;
                float copied[3] = {effect_000.reset_zero_128, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    905, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    905, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_indexed_event_member(38);
            }
            if (_root_state.state_364 == 0) {
                this->state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.2f) + 1.0);
                effect_000.reset_one_118 = static_cast<float>((1.0 - this->state_370) * this->state_374);
                effect_000.reset_one_11c = effect_000.reset_one_118;
                this->state_370 = static_cast<float>(this->state_370 * static_cast<double>(0.95f));
                if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x736) == 0) {
                    _root_state.counter_144 = 0;
                    _root_state.state_364 = 1;
                }
            }
            if (_root_state.state_364 == 1 && *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x738) == 0) {
                // Four packets remain alive through the shared second spawn/wave.
                // docs/REIMU_OBJECT_905_PACKET_JOIN_2026_10_21.md.
                float mode0_packet[3], mode1_packet[3];
                float mode2_packet[3], mode3_packet[3];
                float *completed_packet = 0;
                switch (g_match_identifier) {
                case 3:
                    if (_root_state.counter_144 % 150 == 0) {
                        mode3_packet[0] = effect_000.reset_zero_128;
                        mode3_packet[1] = 2.0f;
                        mode3_packet[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            905, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(mode3_packet), 3);
                        mode3_packet[2] = 5.0f;
                        completed_packet = mode3_packet;
                    }
                    break;
                case 2:
                    if (_root_state.counter_144 % 210 == 0) {
                        mode2_packet[0] = effect_000.reset_zero_128;
                        mode2_packet[1] = 2.0f;
                        mode2_packet[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            905, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(mode2_packet), 3);
                        mode2_packet[2] = 5.0f;
                        completed_packet = mode2_packet;
                    }
                    break;
                case 1:
                    if (_root_state.counter_144 % 240 == 0) {
                        mode1_packet[0] = effect_000.reset_zero_128;
                        mode1_packet[1] = 2.0f;
                        mode1_packet[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            905, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(mode1_packet), 3);
                        mode1_packet[2] = 5.0f;
                        completed_packet = mode1_packet;
                    }
                    break;
                case 0:
                    if (_root_state.counter_144 % 270 == 0) {
                        mode0_packet[0] = effect_000.reset_zero_128;
                        mode0_packet[1] = 2.0f;
                        mode0_packet[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            905, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(mode0_packet), 3);
                        mode0_packet[2] = 5.0f;
                        completed_packet = mode0_packet;
                    }
                    break;
                }
                if (completed_packet) {
                    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                        905, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                        reinterpret_cast<const unsigned *>(completed_packet), 3);
                    reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                }
            }
            if (_root_state.state_364 == 2) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = effect_000.reset_one_118;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_110 = static_cast<unsigned char>(_root_state.channel_110 - 10);
            }
            break;
        case 2:
            if (_root_state.channel_111 < 5) {
                _root_state.channel_111 = 0;
                _root_state.channel_112 = 0;
            } else {
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 5);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 5);
            }
            break;
        case 3:
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 8.0);
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.2f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        case 4:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 7500)
                _root_state.state_364 = 1;
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + static_cast<double>(0.1f));
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            if (_root_state.phase_state_180 != 0) {
                if (_root_state.state_366 >= 10) {
                    _root_state.state_366 = 0;
                    _root_state.phase_state_180 = 0;
                    _root_state.phase_index_184 = 1;
                }
                _root_state.state_366 = static_cast<short>(_root_state.state_366 + 1);
            }
            if (_root_state.state_364 == 1) {
                _root_state.phase_index_184 = 0;
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.05f));
                effect_000.reset_one_11c = effect_000.reset_one_118;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            }
            if (effect_000.object_x_0e8 >= 1800.0 || effect_000.object_x_0e8 < -520.0f || effect_000.object_y_0ec > 1400.0f || effect_000.object_y_0ec < -800.0)
                goto retire;
            break;
        case 5:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        goto advance_with_sequence_three_retirement;

    case 906:
        switch (_root_state.sequence_13e) {
        case 0:
            effect_000.reset_zero_128 += reinterpret_cast<float *>(copied_words_340)[1];
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 5000 && _root_state.state_364 != 2) {
                _root_state.state_364 = 2;
                float copied[3] = {effect_000.reset_zero_128, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_indexed_event_member(38);
            }
            if (_root_state.state_364 == 0) {
                this->state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.2f) + 1.0);
                effect_000.reset_one_118 = static_cast<float>((1.0 - this->state_370) * this->state_374);
                effect_000.reset_one_11c = effect_000.reset_one_118;
                this->state_370 = static_cast<float>(this->state_370 * static_cast<double>(0.95f));
                if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x736) == 0) {
                    _root_state.counter_144 = 0;
                    _root_state.state_364 = 1;
                }
            }
            if (_root_state.state_364 == 1 && *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x738) == 1) {
                switch (g_match_identifier) {
                case 3:
                    if (_root_state.counter_144 % 135 == 0) {
                        float copied[3];
                        for (float sector = 0.0f; sector < 8.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 45.0 + effect_000.reset_zero_128);
                            copied[1] = 10.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        copied[0] = effect_000.reset_zero_128;
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 2:
                    if (_root_state.counter_144 % 165 == 0) {
                        float copied[3];
                        for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 90.0 + effect_000.reset_zero_128);
                            copied[1] = 10.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        copied[0] = effect_000.reset_zero_128;
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 1:
                    if (_root_state.counter_144 % 195 == 0) {
                        float copied[3];
                        for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 90.0 + effect_000.reset_zero_128);
                            copied[1] = 10.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        copied[0] = effect_000.reset_zero_128;
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 0:
                    if (_root_state.counter_144 % 225 == 0) {
                        float copied[3];
                        for (float sector = 0.0f; sector < 2.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 180.0 + effect_000.reset_zero_128);
                            copied[1] = 10.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        copied[0] = effect_000.reset_zero_128;
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            906, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                }
            }
            if (_root_state.state_364 == 2) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = effect_000.reset_one_118;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_110 = static_cast<unsigned char>(_root_state.channel_110 - 10);
            }
            break;
        case 2:
            if (_root_state.channel_111 < 5) {
                _root_state.channel_111 = 0;
                _root_state.channel_112 = 0;
            } else {
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 5);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 5);
            }
            break;
        case 3:
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 8.0);
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.2f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        case 4:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 5000)
                _root_state.state_364 = 2;
            if (_root_state.state_364 == 0) {
                if (_root_state.alpha_113 < 250)
                    _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 + 5);
                else {
                    _root_state.alpha_113 = 255;
                    _root_state.phase_index_184 = 1;
                    _root_state.state_364 = 1;
                }
            }
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.05f));
            if (effect_000.reset_one_118 > 1.0f)
                effect_000.reset_one_118 = 1.0f;
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.95f));
            if (reinterpret_cast<float *>(copied_words_340)[1] <= 4.0f)
                reinterpret_cast<float *>(copied_words_340)[1] = 4.0f;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_phase_counter_conditional(0);
            if (_root_state.phase_state_180 != 0) {
                if (_root_state.state_366 >= 10) {
                    _root_state.state_366 = 0;
                    _root_state.phase_state_180 = 0;
                    _root_state.phase_index_184 = 1;
                }
                _root_state.state_366 = static_cast<short>(_root_state.state_366 + 1);
            }
            if (_root_state.state_364 == 2) {
                _root_state.phase_index_184 = 0;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 10);
            }
            if (effect_000.object_x_0e8 >= 1800.0 || effect_000.object_x_0e8 < -520.0f || effect_000.object_y_0ec > 1400.0f || effect_000.object_y_0ec < -800.0)
                _root_state.state_364 = 2;
            break;
        case 5:
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 3)
            goto retire;
        return;

    case 907:
        switch (_root_state.sequence_13e) {
        case 0:
            effect_000.reset_zero_128 += reinterpret_cast<float *>(copied_words_340)[1];
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 2500 && _root_state.state_364 != 2) {
                _root_state.state_364 = 2;
                float copied[3] = {effect_000.reset_zero_128, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    907, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    907, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_indexed_event_member(38);
            }
            if (_root_state.state_364 == 0) {
                this->state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.2f) + 1.0);
                effect_000.reset_one_118 = static_cast<float>((1.0 - this->state_370) * this->state_374);
                effect_000.reset_one_11c = effect_000.reset_one_118;
                this->state_370 = static_cast<float>(this->state_370 * static_cast<double>(0.95f));
                if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x736) == 0) {
                    _root_state.counter_144 = 0;
                    _root_state.state_364 = 1;
                }
            }
            if (_root_state.state_364 == 1 && *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x738) == 2) {
                switch (g_match_identifier) {
                case 3:
                    if (_root_state.counter_144 % 170 == 0) {
                        const unsigned char *const followed = _root_state.followed_actor_170;
                        const float aim_x = static_cast<float>(
                            (*reinterpret_cast<const float *>(followed + 0xec) - static_cast<double>(effect_000.object_x_0e8)) * effect_000.object_facing_100);
                        const float aim_y = static_cast<float>(
                            *reinterpret_cast<const float *>(followed + 0xf0) + 100.0 - effect_000.object_y_0ec);
                        const float base_angle = -atan2_degrees(aim_y, aim_x);
                        float copied[3];
                        for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 90.0 + base_angle);
                            copied[1] = 6.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                907, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 2:
                    if (_root_state.counter_144 % 200 == 0) {
                        const unsigned char *const followed = _root_state.followed_actor_170;
                        const float aim_x = static_cast<float>(
                            (*reinterpret_cast<const float *>(followed + 0xec) - static_cast<double>(effect_000.object_x_0e8)) * effect_000.object_facing_100);
                        const float aim_y = static_cast<float>(
                            *reinterpret_cast<const float *>(followed + 0xf0) + 100.0 - effect_000.object_y_0ec);
                        const float base_angle = -atan2_degrees(aim_y, aim_x);
                        float copied[3];
                        for (float sector = 0.0f; sector < 4.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 90.0 + base_angle - 90.0);
                            copied[1] = 6.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                907, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 1:
                    if (_root_state.counter_144 % 210 == 0) {
                        const unsigned char *const followed = _root_state.followed_actor_170;
                        const float aim_x = static_cast<float>(
                            (*reinterpret_cast<const float *>(followed + 0xec) - static_cast<double>(effect_000.object_x_0e8)) * effect_000.object_facing_100);
                        const float aim_y = static_cast<float>(
                            *reinterpret_cast<const float *>(followed + 0xf0) + 100.0 - effect_000.object_y_0ec);
                        atan2_degrees(aim_y, aim_x);
                        float copied[3];
                        for (float sector = 0.0f; sector < 2.0f; sector += 1.0f) {
                            copied[0] = static_cast<float>(sector * 180.0 + effect_000.reset_zero_128);
                            copied[1] = 6.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                907, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                case 0:
                    if (_root_state.counter_144 % 225 == 0) {
                        const unsigned char *const followed = _root_state.followed_actor_170;
                        const float aim_x = static_cast<float>(
                            (*reinterpret_cast<const float *>(followed + 0xec) - static_cast<double>(effect_000.object_x_0e8)) * effect_000.object_facing_100);
                        const float aim_y = static_cast<float>(
                            *reinterpret_cast<const float *>(followed + 0xf0) + 100.0 - effect_000.object_y_0ec);
                        const float base_angle = -atan2_degrees(aim_y, aim_x);
                        float copied[3];
                        for (float sector = 0.0f; sector < 1.0f; sector += 1.0f) {
                            copied[0] = base_angle;
                            copied[1] = 6.0f;
                            copied[2] = 4.0f;
                            reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                                907, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                                reinterpret_cast<const unsigned *>(copied), 3);
                        }
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                }
            }
            if (_root_state.state_364 == 2) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = effect_000.reset_one_118;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_110 = static_cast<unsigned char>(_root_state.channel_110 - 10);
            }
            break;
        case 2:
            if (_root_state.channel_111 < 5) {
                _root_state.channel_111 = 0;
                _root_state.channel_112 = 0;
            } else {
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 5);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 5);
            }
            break;
        case 3:
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 8.0);
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.2f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        case 4:
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 8.0);
            if (_root_state.state_364 <= 1 && *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 2500) {
                _root_state.state_364 = 2;
                _root_state.phase_index_184 = 0;
            }
            if (_root_state.state_364 == 0) {
                if (_root_state.alpha_113 <= 245)
                    _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 + 10);
                else {
                    _root_state.alpha_113 = 255;
                    _root_state.phase_index_184 = 1;
                    _root_state.state_364 = 1;
                }
            }
            if (_root_state.state_364 == 1) {
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
                if ((static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x < 0.0 && effect_000.object_x_0e8 < 0.0) ||
                        (static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x > 0.0 && effect_000.object_x_0e8 > 1280.0f)) {
                    effect_000.motion_0f0.velocity_x = -effect_000.motion_0f0.velocity_x;
                    _root_state.phase_index_184 = 1;
                    _root_state.phase_state_180 = 0;
                    next_sequence_block();
                    return;
                }
                if ((effect_000.motion_0f0.velocity_y < 0.0 && effect_000.object_y_0ec < 0.0) || (effect_000.motion_0f0.velocity_y > 0.0 && effect_000.object_y_0ec > 900.0)) {
                    effect_000.motion_0f0.velocity_y = -effect_000.motion_0f0.velocity_y;
                    _root_state.phase_index_184 = 1;
                    _root_state.phase_state_180 = 0;
                    next_sequence_block();
                    return;
                }
            }
            if (_root_state.state_364 == 2) {
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            }
            break;
        case 5:
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 8.0);
            if (_root_state.state_364 <= 1 && *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 2500) {
                _root_state.state_364 = 2;
                _root_state.phase_index_184 = 0;
            }
            if (_root_state.state_364 == 0) {
                if (_root_state.alpha_113 <= 245)
                    _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 + 10);
                else {
                    _root_state.alpha_113 = 255;
                    _root_state.phase_index_184 = 1;
                    _root_state.state_364 = 1;
                }
            }
            if (_root_state.state_364 == 1)
                reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(0);
            if (_root_state.state_364 == 2) {
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            }
            if (effect_000.object_x_0e8 > 1680.0 || effect_000.object_x_0e8 < -400.0 || effect_000.object_y_0ec > 1300.0f || effect_000.object_y_0ec < -300.0f)
                goto retire;
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        goto advance_with_sequence_three_retirement;

    case 908:
        switch (_root_state.sequence_13e) {
        case 0:
            effect_000.reset_zero_128 += reinterpret_cast<float *>(copied_words_340)[1];
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0 && _root_state.state_364 != 2) {
                _root_state.state_364 = 2;
                float copied[3] = {effect_000.reset_zero_128, 0.0f, 2.0f};
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                copied[2] = 3.0f;
                reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                    908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(copied), 3);
                reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_indexed_event_member(38);
            }
            if (_root_state.state_364 == 0) {
                this->state_374 = static_cast<float>(lookup_orientation_sine_quantized_abs(
                    static_cast<float>(_root_state.counter_144 * 3.0)) * static_cast<double>(0.2f) + 1.0);
                effect_000.reset_one_118 = static_cast<float>((1.0 - this->state_370) * this->state_374);
                effect_000.reset_one_11c = effect_000.reset_one_118;
                this->state_370 = static_cast<float>(this->state_370 * static_cast<double>(0.95f));
                if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x736) == 0) {
                    _root_state.counter_144 = 0;
                    _root_state.state_364 = 1;
                }
            }
            if (_root_state.state_364 == 1 && *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x738) == 3) {
                if (_root_state.state_366 > 0) {
                    if (_root_state.state_366 % 2 == 0) {
                        float copied[3] = {this->state_374, 4.0f, 6.0f};
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(1);
                        this->state_374 += _root_state.state_366;
                    }
                    _root_state.state_366 = static_cast<short>(_root_state.state_366 - 1);
                }
                if (_root_state.state_368 > 0) {
                    if (_root_state.state_368 % 2 == 1) {
                        float copied[3] = {this->state_378, 4.0f, 7.0f};
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        this->state_378 -= _root_state.state_368;
                    }
                    _root_state.state_368 = static_cast<short>(_root_state.state_368 - 1);
                }
                switch (g_match_identifier) {
                case 3:
                    if (_root_state.counter_144 % 240 == 60 || _root_state.counter_144 % 240 == 80 || _root_state.counter_144 % 240 == 100 || _root_state.counter_144 % 240 == 120) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(7)) + 3.0);
                        copied[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (_root_state.counter_144 % 240 == 70 || _root_state.counter_144 % 240 == 90 || _root_state.counter_144 % 240 == 110 || _root_state.counter_144 % 240 == 130) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(3)) + 2.0);
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (_root_state.counter_144 % 150 == 0) {
                        _root_state.state_366 = 60;
                        _root_state.state_368 = 60;
                        this->state_374 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        this->state_378 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    }
                    break;
                case 2:
                    if (_root_state.counter_144 % 240 == 60 || _root_state.counter_144 % 240 == 80 || _root_state.counter_144 % 240 == 100) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(7)) + 3.0);
                        copied[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (_root_state.counter_144 % 240 == 70 || _root_state.counter_144 % 240 == 90 || _root_state.counter_144 % 240 == 110) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(3)) + 2.0);
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (_root_state.counter_144 % 150 == 0) {
                        _root_state.state_366 = 60;
                        this->state_374 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    }
                    break;
                case 1:
                    if (_root_state.counter_144 % 240 == 60 || _root_state.counter_144 % 240 == 80 || _root_state.counter_144 % 240 == 100) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(7)) + 3.0);
                        copied[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (_root_state.counter_144 % 240 == 70 || _root_state.counter_144 % 240 == 90) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(3)) + 2.0);
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (_root_state.counter_144 % 240 == 0) {
                        _root_state.state_366 = 60;
                        this->state_374 = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                    }
                    break;
                case 0:
                    if (_root_state.counter_144 % 240 == 60 || _root_state.counter_144 % 240 == 80) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(7)) + 3.0);
                        copied[2] = 4.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    if (_root_state.counter_144 % 240 == 70 || _root_state.counter_144 % 240 == 90) {
                        float copied[3];
                        copied[0] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(360)));
                        copied[1] = static_cast<float>(static_cast<unsigned int>(selector_random_roll(3)) + 2.0);
                        copied[2] = 5.0f;
                        reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
                            908, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
                            reinterpret_cast<const unsigned *>(copied), 3);
                        reinterpret_cast<ReimuObjectOwnerSpawnView *>(_root_state.fighter_owner_348)->dispatch_character_wave_handle(19);
                    }
                    break;
                }
            }
            if (_root_state.state_364 == 2) {
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.1f));
                effect_000.reset_one_11c = effect_000.reset_one_118;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 10);
                _root_state.channel_110 = static_cast<unsigned char>(_root_state.channel_110 - 10);
            }
            break;
        case 2:
            if (_root_state.channel_111 < 5) {
                _root_state.channel_111 = 0;
                _root_state.channel_112 = 0;
            } else {
                _root_state.channel_111 = static_cast<unsigned char>(_root_state.channel_111 - 5);
                _root_state.channel_112 = static_cast<unsigned char>(_root_state.channel_112 - 5);
            }
            break;
        case 3:
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 8.0);
            effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.2f));
            effect_000.reset_one_11c = effect_000.reset_one_118;
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        case 4:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0 || _root_state.value_174 <= -800)
                _root_state.state_364 = 1;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (static_cast<signed char>(_root_state.phase_index_184) <= 0)
                _root_state.state_364 = 1;
            if (_root_state.state_364 == 1) {
                _root_state.phase_index_184 = 0;
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.05f));
                effect_000.reset_one_11c = effect_000.reset_one_118;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            }
            goto bounds_908;
        case 5:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0 || _root_state.value_174 <= -1200)
                _root_state.state_364 = 1;
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(10);
            if (static_cast<signed char>(_root_state.phase_index_184) <= 0)
                _root_state.state_364 = 1;
            if (_root_state.state_364 == 1) {
                _root_state.phase_index_184 = 0;
                effect_000.reset_one_118 = static_cast<float>(effect_000.reset_one_118 + static_cast<double>(0.05f));
                effect_000.reset_one_11c = effect_000.reset_one_118;
                if (_root_state.alpha_113 < 10)
                    goto retire;
                _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            }
            goto bounds_908;
        case 6:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0)
                _root_state.state_364 = 1;
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + 0.25);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(3);
            if (static_cast<signed char>(_root_state.phase_index_184) <= 0)
                _root_state.state_364 = 1;
            if (_root_state.state_364 == 1) {
                packet_908_sequence_6[0] = effect_000.reset_zero_128;
                packet_908_sequence_6[1] = 0.5f;
                packet_908_sequence_6[2] = 8.0f;
                retiring_action = 908;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_908_sequence_6);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            goto bounds_908;
        case 7:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x174) <= 0)
                _root_state.state_364 = 1;
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] + 0.25);
            reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this) + 4)->
                set_oriented_components_f0_f4(reinterpret_cast<float *>(copied_words_340)[0], reinterpret_cast<float *>(copied_words_340)[1]);
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 2.0);
            reinterpret_cast<CharacterObjectRuntime *>(this)->advance_state_six_counter_conditional(3);
            if (static_cast<signed char>(_root_state.phase_index_184) <= 0)
                _root_state.state_364 = 1;
            if (_root_state.state_364 == 1) {
                packet_908_sequence_7[0] = effect_000.reset_zero_128;
                packet_908_sequence_7[1] = 0.5f;
                packet_908_sequence_7[2] = 9.0f;
                retiring_action = 908;
                retiring_packet = reinterpret_cast<const unsigned *>(packet_908_sequence_7);
                retiring_words = 3;
                goto emit_retiring_world;
            }
            goto bounds_908;
        bounds_908:
            if (effect_000.object_x_0e8 >= 1500.0f || effect_000.object_x_0e8 < -220.0 || effect_000.object_y_0ec > 1100.0f || effect_000.object_y_0ec < -500.0)
                goto retire;
            break;
        case 8: case 9:
            if (_root_state.sequence_13e == 8)
                effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 + 10.0);
            else
                effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 10.0);
            effect_000.reset_one_118 += reinterpret_cast<float *>(copied_words_340)[1];
            effect_000.reset_one_11c = effect_000.reset_one_118;
            reinterpret_cast<float *>(copied_words_340)[1] = static_cast<float>(reinterpret_cast<float *>(copied_words_340)[1] * static_cast<double>(0.9f));
            if (_root_state.alpha_113 < 10)
                goto retire;
            _root_state.alpha_113 = static_cast<unsigned char>(_root_state.alpha_113 - 10);
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 3)
            --_root_state.state_330;
        return;

    case 951: {
        _root_state.alpha_113 = _root_state.fighter_owner_348[0x113];
        if (_root_state.sequence_13e == 0 || _root_state.sequence_13e == 3)
            effect_000.object_y_0ec = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xf0);
        else
            effect_000.object_y_0ec = stage_surface_height_at_x(reinterpret_cast<Fighter *>(_root_state.fighter_owner_348));
        effect_000.object_x_0e8 = *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec);
        *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x7a4) = 1;
        const short owner_sequence = *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13e);
        const short owner_frame = *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x140);
        const short owner_action = *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x13c);
        if (owner_sequence == 0 && owner_frame == 0 &&
                ((owner_action >= 70 && owner_action <= 88) || owner_action == 181 ||
                owner_action == 180 || owner_action == 145 || (owner_action >= 100 && owner_action <= 111))) {
            --_root_state.state_330;
            *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x7a4) = 0;
            return;
        }
        if (_root_state.sequence_13e == 0 && (owner_action == 96 || owner_action == 97) && owner_sequence == 3) {
            next_sequence_block();
            effect_000.reset_zero_128 = 0.0f;
            return;
        }
        if (_root_state.sequence_13e == 1 && (owner_action == 199 || owner_action == 198 || owner_action == 197 ||
                owner_action == 796 || owner_action == 771) && owner_sequence == 0 && owner_frame == 3) {
            next_sequence_block();
            return;
        }
        if (_root_state.sequence_13e == 3 && (owner_action == 199 || owner_action == 198 || owner_action == 197 ||
                owner_action == 796) && owner_sequence == 2) {
            --_root_state.state_330;
            *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x7a4) = 0;
            return;
        }
        if (_root_state.sequence_13e == 0 || _root_state.sequence_13e == 3)
            effect_000.reset_zero_128 = static_cast<float>(effect_000.reset_zero_128 - 35.0);
        if (_root_state.sequence_13e == 1 && _root_state.frame_140 == 4)
            return;
        goto advance_and_retire_on_completion;
    }
    case 999:
        switch (_root_state.sequence_13e) {
        case 0: case 1: case 2: case 3:
            *reinterpret_cast<float *>(_root_state.fighter_owner_348 + 0xec) = effect_000.object_x_0e8;
            if (effect_000.object_x_0e8 > 1480.0f || effect_000.object_x_0e8 < -200.0)
                goto retire;
            if (_root_state.sequence_13e >= 1)
                effect_000.motion_0f0.velocity_y -= effect_000.motion_0f0.acceleration_y;
            break;
        case 4: {
            effect_000.motion_0f0.velocity_y = static_cast<float>(effect_000.motion_0f0.velocity_y - static_cast<double>(0.35f));
            const double projected_y = static_cast<double>(effect_000.motion_0f0.velocity_y) + effect_000.object_y_0ec;
            if (stage_surface_height_at_x(reinterpret_cast<Fighter *>(this)) >= projected_y) {
                *reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x78c) = 1;
                effect_000.object_y_0ec = stage_surface_height_at_x(reinterpret_cast<Fighter *>(this));
                effect_000.motion_0f0.velocity_x = 0.0f;
                effect_000.motion_0f0.velocity_y = 0.0f;
                effect_000.motion_0f0.acceleration_y = 0.0f;
                select_sequence(5);
                return;
            }
            break;
        }
        case 6:
            if (*reinterpret_cast<short *>(_root_state.fighter_owner_348 + 0x78e) == 1) {
                next_sequence_block();
                effect_000.object_facing_100 = 1;
                return;
            }
            break;
        case 7: case 8:
            if (_root_state.sequence_13e >= 8)
                effect_000.motion_0f0.velocity_y -= effect_000.motion_0f0.acceleration_y;
            break;
        }
        effect_000.object_x_0e8 += static_cast<float>(effect_000.object_facing_100) * effect_000.motion_0f0.velocity_x;
        effect_000.object_y_0ec += effect_000.motion_0f0.velocity_y;
        if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
            --_root_state.state_330;
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 &&
                _root_state.sequence_13e == 1) {
            effect_000.motion_0f0.velocity_x = 15.0f;
            effect_000.motion_0f0.velocity_y = 15.0f;
            effect_000.motion_0f0.acceleration_y = 0.2f;
        }
        if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 &&
                _root_state.sequence_13e == 8) {
            effect_000.motion_0f0.velocity_x = 15.0f;
            effect_000.motion_0f0.velocity_y = 15.0f;
            effect_000.motion_0f0.acceleration_y = 0.2f;
        }
        return;

    default:
        reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch();
        return;
    }

emit_retiring_world:
    reinterpret_cast<CharacterObjectEffectEmitter *>(this)->spawn_unparented_related_object(
        retiring_action, effect_000.object_x_0e8, effect_000.object_y_0ec, static_cast<unsigned char>(effect_000.object_facing_100), 1,
        retiring_packet, retiring_words);
    goto retire;

advance_with_sequence_three_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --_root_state.state_330;
    if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 3)
        --_root_state.state_330;
    return;

advance_with_sequence_one_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --_root_state.state_330;
    if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 1)
        --_root_state.state_330;
    return;

advance_with_sequence_four_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --_root_state.state_330;
    if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 4)
        --_root_state.state_330;
    return;

select_sequence_three:
    select_sequence(3);
    return;

bounded_projectile_advance:
    if (effect_000.object_x_0e8 > 1380.0 || effect_000.object_x_0e8 < -100.0 || effect_000.object_y_0ec > 1000.0 || effect_000.object_y_0ec < -120.0)
        goto retire;
advance_with_sequence_two_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --_root_state.state_330;
    if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
        --_root_state.state_330;
    return;

advance_with_sequence_retirement:
    if (reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        --_root_state.state_330;
    if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 1)
        --_root_state.state_330;
    if (_root_state.counter_144 == 0 && _root_state.frame_timer_142 == 0 && _root_state.frame_140 == 0 && _root_state.sequence_13e == 2)
        --_root_state.state_330;
    return;

advance_and_retire_on_completion:
    if (!reinterpret_cast<CharacterObjectRuntime *>(this)->advance_frame_and_dispatch())
        return;
    goto retire;
clear_alpha_and_retire:
    _root_state.alpha_113 = 0;
retire:
    --_root_state.state_330;
    return;
}
