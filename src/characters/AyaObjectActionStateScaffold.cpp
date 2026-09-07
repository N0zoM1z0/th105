#include "battle/EffectSprite.hpp"
#include "characters/AnimationSequenceVirtuals.hpp"
#include "characters/CharacterObjectEffects.hpp"
#include "characters/CharacterObjectRuntime.hpp"

#include <stddef.h>

namespace th105 {

class AyaObjectActionStateScaffoldView;
float __fastcall aya_stage_surface_height_at_x(AyaObjectActionStateScaffoldView *object);
int __fastcall aya_is_y_at_or_below_stage_surface(AyaObjectActionStateScaffoldView *object);
int __cdecl selector_random_roll(int limit);
unsigned int __cdecl mt19937_next_u32(void);
extern int g_match_identifier;
float __cdecl lookup_orientation_sine(int angle);
double __cdecl lookup_orientation_sine_quantized_abs(float phase);
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);

class FighterOwnedObjectSpawnView {
public:
    int spawn_owned_object_via_manager(
        int object_id, float x, float y,
        int direction, int arg5, int arg6, int arg7);
};

// Partial semantic reconstruction for AyaObject's RTTI-owned primary-vtable
// +0x28 update root @ 0x0061A290.
//
// This is deliberately not the 19,522-byte target root and is not source-present
// or exact credit. Each accepted case below is checked against the target's
// physical action-owner map, raw PE instructions, and canonical-exact callees.
// Unknown actions return false until their complete logical source is reviewed.

class AyaObjectActionStateScaffoldView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short action, int sequence);
    virtual int set_action_and_finalize(short action);
    virtual int select_sequence(int sequence);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short frame);
    virtual unsigned char next_sequence_frame();
    virtual int previous_sequence_frame();
    virtual void update_slot_28();
    virtual void render_main();
    virtual void render_to_battle_scene();
    virtual void prepare_render_transform();
    virtual void render_color_mode();
    virtual void initialize_action_entry();

    bool try_dispatch_verified_update_action(int action);
    int has_crossed_stage_surface_while_descending();

    CEffectSprite sprite_004;
    unsigned int state_130;
    unsigned char layout_absolute_134;
    unsigned char render_to_battle_135;
    unsigned char unknown_136[2];
    float battle_y_offset_138;
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    short sequence_frame_count_148;
    unsigned char unknown_14a[2];
    short frame_limit_14c;
    unsigned char unknown_14e[2];
    AnimationSequenceFrame *frame_150;
    void *aux_renderer_154;
    AnimationSequenceFrame *frame_158;
    AnimationSequenceBlock *sequence_15c;
    AnimationSequenceTree *sequence_tree_160;
    unsigned int *wave_handles_164;
    void *owner_168;
    CharacterObjectEffectEmitter *related_16c;
    CharacterObjectEffectEmitter *target_170;
    short state_174;
    unsigned char unknown_176[6];
    unsigned char state_17c;
    unsigned char unknown_17d[3];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[0x1ab];
    int lifetime_330;
    unsigned char unknown_334[0x0c];
    float *heading_340;
    short state_344;
    unsigned char unknown_346[2];
    CharacterObjectEffectEmitter *fighter_owner_348;
    CharacterObjectEffectEmitter *related_34c;
    unsigned char unknown_350[0x14];
    short state_364;
    short state_366;
    short state_368;
    short state_36a;
    short state_36c;
    unsigned char unknown_36e[2];
    float state_370;
    float state_374;
    float state_378;
    float state_37c;
    float state_380;
    short state_six_counter_384;
    short phase_counter_386;

    CharacterObjectRuntime *motion_core()
    {
        return reinterpret_cast<CharacterObjectRuntime *>(
            reinterpret_cast<unsigned char *>(this) + 4);
    }

    CharacterObjectEffectEmitter *effect_emitter()
    {
        return reinterpret_cast<CharacterObjectEffectEmitter *>(this);
    }

private:
    void expire()
    {
        --lifetime_330;
    }

    void advance_and_expire()
    {
        if (motion_core()->advance_frame_and_dispatch())
            expire();
    }

    bool outside_common_bounds() const
    {
        return sprite_004.object_x_0e8 > 1380.0f
            || sprite_004.object_x_0e8 < -100.0f
            || sprite_004.object_y_0ec > 1000.0f
            || sprite_004.object_y_0ec < -160.0f;
    }

    void advance_position()
    {
        sprite_004.object_x_0e8 +=
            static_cast<float>(sprite_004.object_facing_100) * motion_core()->component_f0;
        sprite_004.object_y_0ec += motion_core()->component_f4;
    }
};

typedef char AyaObjectActionStateScaffold_action_offset[
    offsetof(AyaObjectActionStateScaffoldView, action_id_13c) == 0x13c ? 1 : -1];
typedef char AyaObjectActionStateScaffold_related_34c_offset[
    offsetof(AyaObjectActionStateScaffoldView, related_34c) == 0x34c ? 1 : -1];
typedef char AyaObjectActionStateScaffold_state_174_offset[
    offsetof(AyaObjectActionStateScaffoldView, state_174) == 0x174 ? 1 : -1];
typedef char AyaObjectActionStateScaffold_phase_state_offset[
    offsetof(AyaObjectActionStateScaffoldView, phase_state_180) == 0x180 ? 1 : -1];
typedef char AyaObjectActionStateScaffold_lifetime_offset[
    offsetof(AyaObjectActionStateScaffoldView, lifetime_330) == 0x330 ? 1 : -1];
typedef char AyaObjectActionStateScaffold_heading_offset[
    offsetof(AyaObjectActionStateScaffoldView, heading_340) == 0x340 ? 1 : -1];
typedef char AyaObjectActionStateScaffold_owner_offset[
    offsetof(AyaObjectActionStateScaffoldView, fighter_owner_348) == 0x348 ? 1 : -1];
typedef char AyaObjectActionStateScaffold_size[
    sizeof(AyaObjectActionStateScaffoldView) == 0x388 ? 1 : -1];

bool AyaObjectActionStateScaffoldView::try_dispatch_verified_update_action(int action)
{
    switch (action) {
    case 800:
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        if (sequence_index_13e == 0) {
            if (effect_emitter()->emit_repeated_effects_for_owner_state(0, 0, 5)) {
                expire();
                return true;
            }
            motion_core()->advance_phase_counter_conditional(1);
            if (phase_state_180 || time_counter_144 >= 60) {
                next_sequence_block();
                return true;
            }
            if (outside_common_bounds()) {
                expire();
                return true;
            }
        }
        if (sequence_index_13e == 1) {
            float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.05);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            heading_340[1] = static_cast<float>(heading_340[1] - 1.0);
            if (heading_340[1] < 1.0f)
                heading_340[1] = 1.0f;
        }
        motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
        advance_position();
        advance_and_expire();
        return true;

    case 801: {
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        if (sequence_index_13e == 0) {
            if (effect_emitter()->emit_repeated_effects_for_owner_state(0, 3, 7)) {
                expire();
                return true;
            }
            if (!(time_counter_144 % 2)) {
                float payload[3] = {heading_340[0], 0.0f, 2.0f};
                effect_emitter()->spawn_unparented_related_object(
                    801, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (phase_state_180 == 6 && ++state_six_counter_384 < 5) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180) {
                next_sequence_block();
                return true;
            }
            heading_340[0] = static_cast<float>(heading_340[0] + heading_340[1]);
            motion_core()->set_oriented_components_f0_f4(heading_340[0], 40.0f);
            sprite_004.reset_zero_128 = heading_340[0];
            advance_position();
        }
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence_index_13e == 1) {
            sprite_004.reset_one_118 = static_cast<float>(
                sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_11c = static_cast<float>(
                sprite_004.reset_one_11c + 0.1000000014901161);
            if (alpha < 5) {
                expire();
                return true;
            }
            alpha -= 5;
        }
        if (sequence_index_13e == 2) {
            if (alpha < 20) {
                expire();
                return true;
            }
            alpha -= 20;
        }
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140
            && sequence_index_13e == 2) {
            expire();
        }
        return true;
    }

    case 804:
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        if (sequence_index_13e == 0) {
            if (effect_emitter()->emit_repeated_effects_for_owner_state(0, 3, 10)) {
                expire();
                return true;
            }
            if (phase_state_180 == 6 && ++state_six_counter_384 < 10) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180) {
                next_sequence_block();
                return true;
            }
            if (outside_common_bounds()) {
                expire();
                return true;
            }
            if (time_counter_144 > 60) {
                next_sequence_block();
                return true;
            }
        }
        motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
        heading_340[1] = static_cast<float>(heading_340[1] - 1.0);
        if (heading_340[1] < 1.0f)
            heading_340[1] = 1.0f;
        advance_position();
        advance_and_expire();
        return true;

    case 807: {
        if (phase_state_180 == 5
            || (!sequence_index_13e
                && effect_emitter()->emit_repeated_effects_for_owner_state(0, 0, 10))) {
            expire();
            return true;
        }
        if (sequence_index_13e == 0) {
            if (phase_state_180 == 6 && ++state_six_counter_384 < 5) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180) {
                select_sequence(2);
                return true;
            }
            if (!(time_counter_144 % 5)) {
                float payload[3] = {0.0f, 0.0f, 1.0f};
                reinterpret_cast<FighterOwnedObjectSpawnView *>(fighter_owner_348)
                    ->spawn_owned_object_via_manager(
                        807, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                        static_cast<unsigned char>(sprite_004.object_facing_100),
                        1, reinterpret_cast<int>(payload), 3);
            }
        }
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence_index_13e == 1) {
            if (alpha <= 15) {
                expire();
                return true;
            }
            alpha -= 15;
            sprite_004.reset_zero_128 =
                static_cast<float>(sprite_004.reset_zero_128 + 10.0);
            sprite_004.reset_one_118 = static_cast<float>(
                sprite_004.reset_one_118 + 0.05000000074505806);
            sprite_004.reset_one_11c = static_cast<float>(
                sprite_004.reset_one_11c + 0.05000000074505806);
        }
        if (sequence_index_13e == 0) {
            motion_core()->component_f0 =
                static_cast<float>(motion_core()->component_f0 - 0.6000000238418579);
            sprite_004.reset_zero_128 =
                static_cast<float>(sprite_004.reset_zero_128 + 40.0);
        }
        if (sequence_index_13e == 2) {
            motion_core()->component_f0 =
                static_cast<float>(motion_core()->component_f0 * 0.8999999761581421);
        }
        advance_position();
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140
            && sequence_index_13e == 2) {
            expire();
        }
        return true;
    }

    case 810: {
        if (phase_state_180 == 5
            || (sequence_index_13e < 3
                && effect_emitter()->emit_repeated_effects_for_owner_state(0, 5, 10))) {
            expire();
            return true;
        }
        short const sequence = sequence_index_13e;
        if (sequence == 0 || sequence == 2) {
            if (phase_state_180 == 6 && ++state_six_counter_384 < 10) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180) {
                select_sequence(3);
                return true;
            }
            if (outside_common_bounds()) {
                expire();
                return true;
            }
            if (frame_timer_142 > 60
                || (sequence == 2
                    && (!aya_is_y_at_or_below_stage_surface(this)
                        || aya_stage_surface_height_at_x(this)
                            > sprite_004.object_y_0ec))) {
                select_sequence(3);
                return true;
            }
        }
        if (sequence == 1) {
            if (phase_state_180 == 6 && ++state_six_counter_384 < 20) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180) {
                select_sequence(2);
                return true;
            }
            if (has_crossed_stage_surface_while_descending()) {
                select_sequence(2);
                sprite_004.object_y_0ec = aya_stage_surface_height_at_x(this);
                heading_340[0] = 0.0f;
                heading_340[1] = 6.0f;
                sprite_004.reset_zero_128 = heading_340[0];
                float payload[3] = {heading_340[0], 0.0f, 3.0f};
                effect_emitter()->spawn_unparented_related_object(
                    810, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (sprite_004.object_x_0e8 > 1380.0f
                || sprite_004.object_x_0e8 < -100.0f
                || sprite_004.object_y_0ec > 1000.0f) {
                expire();
                return true;
            }
            if (frame_timer_142 > 60 || phase_state_180)
                select_sequence(2);
        }
        if (sequence_index_13e == 3) {
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.05000000074505806);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            heading_340[1] = static_cast<float>(heading_340[1] - 1.0);
            if (heading_340[1] < 1.0f)
                heading_340[1] = 1.0f;
        }
        motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
        advance_position();
        advance_and_expire();
        return true;
    }

    case 811: {
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        if (sequence_index_13e == 0) {
            if (effect_emitter()->emit_repeated_effects_for_owner_state(0, 0, 7)) {
                expire();
                return true;
            }
            if (!(time_counter_144 % 3)) {
                float payload[3] = {heading_340[0], 0.0f, 2.0f};
                effect_emitter()->spawn_unparented_related_object(
                    811, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (phase_state_180 == 6 && ++state_six_counter_384 < 15) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180)
                next_sequence_block();
            heading_340[0] = static_cast<float>(heading_340[0] - 1.0);
            heading_340[1] = static_cast<float>(heading_340[1] - 0.5);
            if (heading_340[1] < 15.0f)
                heading_340[1] = 15.0f;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            sprite_004.reset_zero_128 = heading_340[0];
            advance_position();
        }
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence_index_13e == 1) {
            sprite_004.reset_one_118 = static_cast<float>(
                sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_11c = static_cast<float>(
                sprite_004.reset_one_11c + 0.1000000014901161);
            if (alpha < 5) {
                expire();
                return true;
            }
            alpha -= 5;
        }
        if (sequence_index_13e == 2) {
            if (alpha < 20) {
                expire();
                return true;
            }
            alpha -= 20;
        }
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140
            && sequence_index_13e == 2) {
            expire();
        }
        return true;
    }

    case 812: {
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence_index_13e == 1) {
            if (alpha < 20) {
                expire();
                return true;
            }
            alpha -= 20;
            sprite_004.object_x_0e8 = static_cast<float>(
                static_cast<double>(sprite_004.object_x_0e8)
                + 8 * static_cast<signed char>(sprite_004.object_facing_100));
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + 10.0);
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
        } else if (sequence_index_13e == 2) {
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            heading_340[1] = static_cast<float>(heading_340[1] - 0.5);
            if (heading_340[1] < 0.5f)
                heading_340[1] = 0.5f;
            bool const negative_counter = time_counter_144 < 0;
            advance_position();
            sprite_004.object_y_0ec = static_cast<float>(
                sprite_004.object_y_0ec + motion_core()->component_f4 * 0.25);
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + state_374);
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.01999999955296516);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            if (!negative_counter) {
                if (alpha <= 5) {
                    expire();
                    return true;
                }
                alpha -= 5;
            }
        } else if (sequence_index_13e == 0) {
            if (!frame_index_140
                && effect_emitter()->emit_repeated_effects_for_owner_state(0, 0, 4)) {
                expire();
                return true;
            }
            if (phase_state_180 == 6 && ++state_six_counter_384 < 10) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            state_364 += 10;
            if (state_364 > 90)
                state_364 = 90;
            heading_340[0] = static_cast<float>(heading_340[0] + 5.0);
            float const stage_phase = static_cast<float>(state_364);
            state_378 = static_cast<float>(
                lookup_orientation_sine_quantized_abs(stage_phase) * heading_340[1]);
            float const oriented_phase = static_cast<float>(
                static_cast<double>(heading_340[0])
                * static_cast<signed char>(sprite_004.object_facing_100));
            sprite_004.object_x_0e8 = static_cast<float>(
                lookup_orientation_cosine_quantized_abs(oriented_phase) * state_378
                + state_370);
            sprite_004.object_y_0ec = static_cast<float>(
                lookup_orientation_sine_quantized_abs(oriented_phase) * state_378
                + state_374);
            sprite_004.reset_zero_128 = static_cast<float>(
                -heading_340[0]
                - 90 * static_cast<signed char>(sprite_004.object_facing_100));
            state_370 = static_cast<float>(
                static_cast<double>(state_370)
                + 8 * static_cast<signed char>(sprite_004.object_facing_100));
        }
        if (sprite_004.object_x_0e8 > 1580.0f
            || sprite_004.object_x_0e8 < -300.0f
            || sprite_004.object_y_0ec > 1200.0f
            || sprite_004.object_y_0ec < -300.0f) {
            expire();
            return true;
        }
        advance_and_expire();
        return true;
    }

    case 815: {
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        CharacterObjectEffectEmitter *const owner = fighter_owner_348;
        short const owner_action = *reinterpret_cast<short *>(
            reinterpret_cast<unsigned char *>(owner) + 0x13c);
        short const owner_sequence = *reinterpret_cast<short *>(
            reinterpret_cast<unsigned char *>(owner) + 0x13e);
        if (owner_action >= 520 && owner_action <= 524) {
            if (owner_sequence > 1 && sequence_index_13e <= 1) {
                select_sequence(2);
                return true;
            }
        } else if (sequence_index_13e <= 1) {
            select_sequence(2);
            return true;
        }
        if (sequence_index_13e < 2) {
            if (owner_action >= 520 && owner_action <= 523) {
                sprite_004.object_x_0e8 = owner->x_ec;
                sprite_004.object_y_0ec = static_cast<float>(
                    static_cast<double>(owner->y_f0) + 90.0);
            }
        }
        advance_and_expire();
        return true;
    }

    case 816: {
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        CharacterObjectEffectEmitter *const owner = fighter_owner_348;
        short const owner_action = *reinterpret_cast<short *>(
            reinterpret_cast<unsigned char *>(owner) + 0x13c);
        short const owner_sequence = *reinterpret_cast<short *>(
            reinterpret_cast<unsigned char *>(owner) + 0x13e);
        if (owner_action < 525 || owner_action > 529) {
            if (sequence_index_13e < 2) {
                select_sequence(2);
                return true;
            }
        } else if (sequence_index_13e < 2) {
            if (owner_action == 529) {
                if (owner_sequence == 0 || owner_sequence >= 16) {
                    select_sequence(2);
                    return true;
                }
            } else if (owner_sequence >= 3) {
                select_sequence(2);
                return true;
            }
            if (owner_action >= 525 && owner_action <= 528) {
                sprite_004.object_x_0e8 = owner->x_ec;
                sprite_004.object_y_0ec = static_cast<float>(
                    static_cast<double>(owner->y_f0) + 90.0);
            } else if (owner_action == 529) {
                sprite_004.object_x_0e8 = owner->x_ec;
                sprite_004.object_y_0ec = owner->y_f0 + heading_340[1];
            }
        }
        advance_and_expire();
        return true;
    }

    case 817: {
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence_index_13e == 0) {
            if (effect_emitter()->emit_repeated_effects_for_owner_state(0, 4, 3)) {
                expire();
                return true;
            }
            if (!(time_counter_144 % 2)) {
                float payload[3] = {heading_340[0], 0.0f, 2.0f};
                effect_emitter()->spawn_unparented_related_object(
                    817, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (phase_state_180 == 6 && ++state_six_counter_384 < 10) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            motion_core()->advance_phase_counter_conditional(3);
            if (time_counter_144 >= 10)
                phase_index_184 = 0;
            if (!phase_index_184) {
                heading_340[1] = static_cast<float>(
                    heading_340[1] * 0.8500000238418579);
                if (alpha < 10) {
                    expire();
                    return true;
                }
                alpha -= 10;
            }
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            advance_position();
        } else if (sequence_index_13e == 1) {
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + 10.0);
            if (alpha < 15) {
                expire();
                return true;
            }
            alpha -= 15;
        } else if (sequence_index_13e == 2) {
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + state_370);
            state_370 = static_cast<float>(state_370 * 0.949999988079071);
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            if (alpha < 20) {
                expire();
                return true;
            }
            alpha -= 20;
        }
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140
            && sequence_index_13e == 2) {
            expire();
        }
        return true;
    }

    case 820: {
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        short sequence = sequence_index_13e;
        if (sequence == 0 || sequence == 4) {
            if (effect_emitter()->emit_repeated_effects_for_owner_state(0, 5, 10)) {
                expire();
                return true;
            }
        }
        if (sequence == 0) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + 10.0);
            sprite_004.object_x_0e8 = owner->x_ec;
            sprite_004.object_y_0ec = owner->y_f0;
            if (!(time_counter_144 % 5)) {
                float payload[3] = {
                    0.0f,
                    0.0f,
                    static_cast<float>((mt19937_next_u32() & 1u) + 2u),
                };
                effect_emitter()->spawn_unparented_related_object(
                    820, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            short const owner_action = *reinterpret_cast<short *>(
                reinterpret_cast<unsigned char *>(owner) + 0x13c);
            short const owner_sequence = *reinterpret_cast<short *>(
                reinterpret_cast<unsigned char *>(owner) + 0x13e);
            if (owner_action != 540 || owner_sequence > 1)
                next_sequence_block();
        }

        sequence = sequence_index_13e;
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence == 1) {
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + 10.0);
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.2000000029802322);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            if (alpha <= 15) {
                expire();
                return true;
            }
            alpha -= 15;
        }
        if (sequence == 2 || sequence == 3) {
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + 30.0);
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + state_370);
            sprite_004.reset_one_118 = scale;
            state_370 = static_cast<float>(state_370 - 0.05000000074505806);
            if (state_370 < 0.0099999998f)
                state_370 = 0.0099999998f;
            sprite_004.reset_one_11c = sprite_004.reset_one_118;
            if (alpha <= 15) {
                expire();
                return true;
            }
            alpha -= 15;
        }
        if (sequence == 4 || sequence == 6) {
            if (phase_state_180 == 6 && ++state_six_counter_384 < 20) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (frame_timer_142 > 30
                || phase_state_180
                || aya_stage_surface_height_at_x(this) >= sprite_004.object_y_0ec) {
                select_sequence(5);
                return true;
            }
            if (sprite_004.object_x_0e8 > 1380.0f
                || sprite_004.object_x_0e8 < -100.0f
                || sprite_004.object_y_0ec > 1000.0f) {
                expire();
                return true;
            }
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            advance_position();
        }
        if (sequence == 5) {
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.05000000074505806);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            heading_340[1] = static_cast<float>(heading_340[1] - 3.0);
            if (heading_340[1] < 1.0f)
                heading_340[1] = 1.0f;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            advance_position();
        }
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140
            && sequence_index_13e == 6) {
            expire();
        }
        return true;
    }

    case 821: {
        if (phase_state_180 == 5) { expire(); return true; }
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        short sequence = sequence_index_13e;
        if (sequence == 0) {
            state_36c += 6;
            if (state_36c >= 90) state_36c = 90;
            state_370 = static_cast<float>(state_370 + 0.05000000074505806);
            float const scale = static_cast<float>(lookup_orientation_sine(state_36c) + 1.0 + state_370);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
        }
        if (sequence == 1) {
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            heading_340[1] = static_cast<float>(heading_340[1] - 0.5);
            if (heading_340[1] < 0.5f) heading_340[1] = 0.5f;
            bool const negative_counter = time_counter_144 < 0;
            advance_position();
            sprite_004.object_y_0ec = static_cast<float>(sprite_004.object_y_0ec + motion_core()->component_f4 * 0.25);
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + state_374);
            float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.01999999955296516);
            sprite_004.reset_one_118 = scale; sprite_004.reset_one_11c = scale;
            if (!negative_counter) { if (alpha <= 5) { expire(); return true; } alpha -= 5; }
        }
        if (sequence == 2) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            short const owner_action = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13c);
            short const owner_sequence = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13e);
            if (owner_action != 545 || owner_sequence == 2) { expire(); return true; }
            sprite_004.object_x_0e8 = static_cast<float>(static_cast<double>(owner->x_ec) + 20 * static_cast<signed char>(sprite_004.object_facing_100));
            sprite_004.object_y_0ec = owner->y_f0;
        }
        if (sequence == 3) {
            motion_core()->component_f0 = static_cast<float>(motion_core()->component_f0 - 0.5);
            if (motion_core()->component_f0 < 10.0f) motion_core()->component_f0 = 10.0f;
            if (phase_state_180 == 5 || sprite_004.object_x_0e8 > 1480.0f || sprite_004.object_x_0e8 < -200.0f || effect_emitter()->emit_repeated_effects_for_owner_state(0, 2, 5)) { expire(); return true; }
            if (phase_state_180 == 6 && ++state_six_counter_384 < 20) { ++phase_index_184; phase_state_180 = 0; }
            if (phase_state_180 || time_counter_144 >= 90 || !aya_is_y_at_or_below_stage_surface(this) || aya_stage_surface_height_at_x(this) > sprite_004.object_y_0ec) {
                phase_index_184 = 0; next_sequence_block();
            } else { advance_position(); }
        }
        sequence = sequence_index_13e;
        if (sequence == 4) advance_position();
        if (sequence == 5) {
            float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.2000000029802322);
            sprite_004.reset_one_118 = scale; sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + 15.0);
            if (alpha <= 20) { expire(); return true; } alpha -= 20;
        }
        if (sequence == 6) {
            float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.1500000059604645);
            sprite_004.reset_one_118 = scale; sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + 25.0);
            if (alpha <= 10) { expire(); return true; } alpha -= 10;
        }
        if (motion_core()->advance_frame_and_dispatch()) expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 1) expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 5) expire();
        return true;
    }

    case 822: {
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence_index_13e == 0) {
            if (effect_emitter()->emit_repeated_effects_for_owner_state(0, 4, 3)) {
                expire();
                return true;
            }
            if (!(time_counter_144 % 2)) {
                float payload[3] = {heading_340[0], 0.0f, 2.0f};
                effect_emitter()->spawn_unparented_related_object(
                    822, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (phase_state_180 == 6) {
                ++state_six_counter_384;
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (!phase_index_184) {
                heading_340[1] = static_cast<float>(
                    heading_340[1] * 0.8500000238418579);
                if (alpha < 10) {
                    expire();
                    return true;
                }
                alpha -= 10;
            }
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            advance_position();
            if (sprite_004.object_x_0e8 > 1480.0f
                || sprite_004.object_x_0e8 < -200.0f
                || sprite_004.object_y_0ec > 1480.0f
                || sprite_004.object_y_0ec < -400.0f) {
                expire();
                return true;
            }
        } else if (sequence_index_13e == 1) {
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + 10.0);
            if (alpha < 15) {
                expire();
                return true;
            }
            alpha -= 15;
        } else if (sequence_index_13e == 2) {
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + state_370);
            state_370 = static_cast<float>(state_370 * 0.949999988079071);
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            if (alpha < 20) {
                expire();
                return true;
            }
            alpha -= 20;
        }
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140
            && sequence_index_13e == 2) {
            expire();
        }
        return true;
    }

    case 825:
        if (phase_state_180 == 5) {
            expire();
            return true;
        }
        if (sequence_index_13e == 0) {
            motion_core()->component_f0 = static_cast<float>(
                (static_cast<double>(heading_340[0] - sprite_004.object_x_0e8) / 1280.0)
                * 40.0 * static_cast<double>(sprite_004.object_facing_100));
            motion_core()->component_f4 = static_cast<float>(
                (static_cast<double>(heading_340[1] - sprite_004.object_y_0ec) / 1280.0) * 40.0);
            if (state_174 < 0) {
                select_sequence(2);
                motion_core()->component_f0 = 0.0f;
                motion_core()->component_f4 = 0.0f;
                return true;
            }
            if (time_counter_144 >= 120) {
                next_sequence_block();
                motion_core()->component_f0 = 30.0f;
                motion_core()->component_f4 = -30.0f;
                return true;
            }
        } else if (sequence_index_13e == 1) {
            if (state_174 < 0 || time_counter_144 >= 15
                || static_cast<signed char>(phase_index_184) <= 0) {
                select_sequence(2);
                motion_core()->component_f0 =
                    static_cast<float>(motion_core()->component_f0 * 0.1f);
                motion_core()->component_f4 =
                    static_cast<float>(motion_core()->component_f4 * 0.1f);
                return true;
            }
        } else if (sequence_index_13e == 2) {
            motion_core()->component_f4 =
                static_cast<float>(motion_core()->component_f4 + 0.5);
            motion_core()->component_f0 =
                static_cast<float>(motion_core()->component_f0 + 0.25);
            if (sprite_004.object_x_0e8 > 1380.0f
                || sprite_004.object_x_0e8 < -100.0f
                || sprite_004.object_y_0ec > 1000.0f
                || sprite_004.object_y_0ec < -200.0f) {
                expire();
                return true;
            }
        }
        advance_position();
        advance_and_expire();
        return true;

    case 826: {
        short const sequence = sequence_index_13e;
        if (sequence == 0) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            short const owner_action = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13c);
            if (owner_action == 565 || owner_action == 567) {
                short const owner_frame = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x140);
                short const owner_sequence = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13e);
                if (!owner_frame && !owner_sequence) { expire(); return true; }
            } else {
                if (owner_action >= 50 && owner_action <= 149) { expire(); return true; }
                if (owner_action >= 500 && owner_action <= 700) { expire(); return true; }
            }
            if (!phase_index_184) { expire(); return true; }
            float const owner_y = owner->y_f0;
            float const stage_height = aya_stage_surface_height_at_x(this);
            if (stage_height >= owner_y && heading_340[0] == 1.0f) { expire(); return true; }
            if (stage_height < owner_y && heading_340[0] == 0.0f) { expire(); return true; }
            sprite_004.object_x_0e8 = owner->x_ec;
            sprite_004.object_y_0ec = static_cast<float>(static_cast<double>(owner->y_f0) + 100.0);
            float payload[3];
            payload[0] = static_cast<float>(selector_random_roll(100) - 50);
            payload[1] = static_cast<float>(selector_random_roll(100) - 50);
            payload[2] = 1.0f;
            if (!(time_counter_144 % 20)) {
                effect_emitter()->spawn_unparented_related_object(
                    861, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (phase_state_180 == 6) {
                if (++state_six_counter_384 >= 5) { expire(); return true; }
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180) {
                if (++state_364 >= 6) { phase_state_180 = 0; state_364 = 0; }
            }
        }
        if (sequence_index_13e == 1) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            sprite_004.object_x_0e8 = owner->x_ec;
            reinterpret_cast<unsigned char *>(this)[0x113] -= 10;
            sprite_004.object_y_0ec = static_cast<float>(static_cast<double>(owner->y_f0) + 100.0);
            float const scale = static_cast<float>(sprite_004.reset_one_118 + state_370);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + 20.0);
            state_370 = static_cast<float>(state_370 - 0.02999999932944775);
            if (state_370 < 0.0099999998f) state_370 = 0.0099999998f;
        }
        advance_and_expire();
        return true;
    }

    case 850: {
        float velocity_x = motion_core()->component_f0;
        if (sequence_index_13e < 2) {
            velocity_x = static_cast<float>(velocity_x - 0.4000000059604645);
            motion_core()->component_f0 = velocity_x;
            if (velocity_x < 1.0f)
                motion_core()->component_f0 = 1.0f;
            if (!(time_counter_144 % 10)) {
                effect_emitter()->emit_fighter_effect_433cc0(
                    129, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1);
            }
            if (time_counter_144 % 10 == 5) {
                effect_emitter()->emit_fighter_effect_433cc0(
                    129, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(-sprite_004.object_facing_100), 1);
            }
        } else {
            velocity_x = static_cast<float>(velocity_x - 0.2000000029802322);
            motion_core()->component_f0 = velocity_x;
            if (velocity_x < 0.0f)
                motion_core()->component_f0 = 0.0f;
        }
        if (sequence_index_13e == 1) {
            if (phase_state_180 == 6) {
                ++state_six_counter_384;
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180) {
                if (++state_364 >= 6) {
                    phase_index_184 = 1;
                    phase_state_180 = 0;
                    state_364 = 0;
                }
            }
            if (time_counter_144 > 90)
                next_sequence_block();
        }
        sprite_004.object_x_0e8 +=
            static_cast<float>(sprite_004.object_facing_100) * motion_core()->component_f0;
        advance_and_expire();
        return true;
    }

    case 851: {
        if (sequence_index_13e < 2) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            sprite_004.object_x_0e8 = owner->x_ec;
            sprite_004.object_y_0ec = owner->y_f0;
            int const facing_offset =
                100 * static_cast<signed char>(sprite_004.object_facing_100);
            if (!(time_counter_144 % 10)) {
                effect_emitter()->emit_fighter_effect_433cc0(
                    129,
                    static_cast<float>(
                        static_cast<double>(sprite_004.object_x_0e8) - facing_offset),
                    sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1);
            }
            if (time_counter_144 % 10 == 5) {
                effect_emitter()->emit_fighter_effect_433cc0(
                    129,
                    static_cast<float>(
                        static_cast<double>(sprite_004.object_x_0e8) + facing_offset),
                    sprite_004.object_y_0ec,
                    static_cast<unsigned char>(-sprite_004.object_facing_100), 1);
            }
        }
        if (sequence_index_13e != 1) {
            advance_and_expire();
            return true;
        }
        if (phase_state_180 == 6) {
            ++state_six_counter_384;
            ++phase_index_184;
            phase_state_180 = 0;
        }
        if (!(time_counter_144 % 5)) {
            phase_index_184 = 1;
            phase_state_180 = 0;
        }
        CharacterObjectEffectEmitter *const owner = fighter_owner_348;
        short const owner_action = *reinterpret_cast<short *>(
            reinterpret_cast<unsigned char *>(owner) + 0x13c);
        short const owner_sequence = *reinterpret_cast<short *>(
            reinterpret_cast<unsigned char *>(owner) + 0x13e);
        if (owner_action != 601) {
            next_sequence_block();
            return true;
        }
        if (owner_sequence <= 1) {
            advance_and_expire();
            return true;
        }
        next_sequence_block();
        return true;
    }

    case 852: {
        short const sequence = sequence_index_13e;
        if (sequence == 0) {
            if (!(time_counter_144 % 12)) {
                float payload[3] = {static_cast<float>(20 - selector_random_roll(40)), static_cast<float>(selector_random_roll(10) + 50), 2.0f};
                float const x = sprite_004.object_facing_100 == 1 ? -100.0f : 1380.0f;
                float const y = static_cast<float>(selector_random_roll(640));
                effect_emitter()->spawn_unparented_related_object(852, x, y, static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (!(time_counter_144 % 40)) {
                float payload[3] = {static_cast<float>(15 - selector_random_roll(30)), static_cast<float>(selector_random_roll(10) + 35), 3.0f};
                float const x = sprite_004.object_facing_100 == 1 ? -100.0f : 1380.0f;
                float const y = static_cast<float>(selector_random_roll(640));
                effect_emitter()->spawn_unparented_related_object(852, x, y, static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (!(time_counter_144 % 15)) {
                float payload[3] = {0.0f, 0.0f, 1.0f};
                float const y = static_cast<float>(selector_random_roll(640) - 180);
                float const x = sprite_004.object_facing_100 == 1 ? static_cast<float>(-400 - selector_random_roll(128)) : static_cast<float>(selector_random_roll(128) + 1680);
                effect_emitter()->spawn_unparented_related_object(852, x, y, static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (time_counter_144 >= 240) { state_374 = static_cast<float>(state_374 - 0.5); if (state_374 < 0.0f) state_374 = 0.0f; }
            else { state_374 = static_cast<float>(state_374 + 0.5); if (state_374 > 7.0f) state_374 = 7.0f; }
            if (time_counter_144 == 240) { expire(); return true; }
            if (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(target_170) + 0x174) <= 0) { expire(); return true; }
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            if (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x174) <= 0) { expire(); return true; }
            CharacterObjectEffectEmitter *const owner_target = owner->target_170;
            signed char const nested_facing = *reinterpret_cast<signed char *>(reinterpret_cast<unsigned char *>(owner_target) + 0x104);
            float const rate = sprite_004.object_facing_100 == -1 ? static_cast<float>(-static_cast<double>(nested_facing) * state_374) : static_cast<float>(static_cast<double>(nested_facing) * state_374);
            *reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(owner) + 0x6ac) = rate;
        }
        if (sequence_index_13e == 1) {
            motion_core()->set_oriented_components_f0_f4(-10.0f, 100.0f);
            sprite_004.reset_zero_128 = -10.0f;
            if ((sprite_004.object_facing_100 == 1 && sprite_004.object_x_0e8 > 1880.0f) || (sprite_004.object_facing_100 == -1 && sprite_004.object_x_0e8 < -600.0f)) { expire(); return true; }
        }
        if (sequence_index_13e == 2 || sequence_index_13e == 3) {
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + state_370);
            if (time_counter_144 == 120) { expire(); return true; }
        }
        advance_position();
        if (motion_core()->advance_frame_and_dispatch()) expire();
        return true;
    }

    case 853: {
        if (phase_state_180 == 5) { expire(); return true; }
        if (sequence_index_13e == 0) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + 10.0);
            sprite_004.object_x_0e8 = owner->x_ec;
            sprite_004.object_y_0ec = owner->y_f0;
            if (!(time_counter_144 % 5)) {
                float payload[3] = {0.0f, 0.0f, static_cast<float>((mt19937_next_u32() & 1u) + 2u)};
                effect_emitter()->spawn_unparented_related_object(853, sprite_004.object_x_0e8, sprite_004.object_y_0ec, static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
            short const owner_action = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13c);
            short const owner_sequence = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13e);
            if (owner_action != 603 || owner_sequence > 1) next_sequence_block();
        }
        short sequence = sequence_index_13e;
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence == 1) {
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + 10.0);
            float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.300000011920929);
            sprite_004.reset_one_118 = scale; sprite_004.reset_one_11c = scale;
            if (alpha <= 15) { expire(); return true; } alpha -= 15;
        }
        if (sequence == 2 || sequence == 3) {
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + 30.0);
            sprite_004.reset_one_118 = static_cast<float>(sprite_004.reset_one_118 + state_370);
            state_370 = static_cast<float>(state_370 - 0.05000000074505806);
            if (state_370 < 0.0099999998f) state_370 = 0.0099999998f;
            sprite_004.reset_one_11c = sprite_004.reset_one_118;
            if (alpha <= 15) { expire(); return true; } alpha -= 15;
        }
        if (sequence == 4) {
            if (phase_state_180 == 6 && ++state_six_counter_384 < 20) { ++phase_index_184; phase_state_180 = 0; }
            motion_core()->advance_phase_counter_conditional(3);
            if (time_counter_144 > 60 || phase_state_180 || aya_stage_surface_height_at_x(this) >= sprite_004.object_y_0ec) { select_sequence(5); return true; }
            if (sprite_004.object_x_0e8 > 1380.0f || sprite_004.object_x_0e8 < -100.0f || sprite_004.object_y_0ec > 1000.0f) { expire(); return true; }
            advance_position();
        }
        if (sequence == 5) {
            float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.05000000074505806);
            sprite_004.reset_one_118 = scale; sprite_004.reset_one_11c = scale;
            heading_340[1] = static_cast<float>(heading_340[1] - 3.0); if (heading_340[1] < 1.0f) heading_340[1] = 1.0f;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]); advance_position();
        }
        if (sequence == 6) {
            if (phase_state_180 == 6 && ++state_six_counter_384 < 5) { ++phase_index_184; phase_state_180 = 0; }
            if (time_counter_144 > 60 || phase_state_180 || aya_stage_surface_height_at_x(this) >= sprite_004.object_y_0ec) {
                select_sequence(7);
            } else {
                if (sprite_004.object_x_0e8 > 1380.0f || sprite_004.object_x_0e8 < -100.0f || sprite_004.object_y_0ec > 1000.0f || aya_stage_surface_height_at_x(this) >= sprite_004.object_y_0ec) { expire(); return true; }
                advance_position();
            }
        }
        sequence = sequence_index_13e;
        if (sequence == 7) {
            float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.05000000074505806);
            sprite_004.reset_one_118 = scale; sprite_004.reset_one_11c = scale;
            heading_340[1] = static_cast<float>(heading_340[1] - 3.0); if (heading_340[1] < 1.0f) heading_340[1] = 1.0f;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]); advance_position();
        }
        if (sequence == 8) {
            sprite_004.reset_one_118 = static_cast<float>(sprite_004.reset_one_118 + 0.2000000029802322);
            sprite_004.reset_one_11c = static_cast<float>(sprite_004.reset_one_11c + 0.1000000014901161);
        }
        if (motion_core()->advance_frame_and_dispatch()) expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140 && (sequence_index_13e == 6 || sequence_index_13e == 7)) { expire(); return true; }
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 8) expire();
        return true;
    }

    case 854: {
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence_index_13e == 0) {
            if (!(time_counter_144 % 2)) {
                float payload[3] = {heading_340[0], 0.0f, 2.0f};
                effect_emitter()->spawn_unparented_related_object(
                    854, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (phase_state_180 == 6) {
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180)
                next_sequence_block();
            heading_340[0] = static_cast<float>(heading_340[0] + heading_340[1]);
            motion_core()->set_oriented_components_f0_f4(heading_340[0], 40.0f);
            sprite_004.reset_zero_128 = heading_340[0];
            advance_position();
        }
        if (sequence_index_13e == 1) {
            sprite_004.reset_one_118 = static_cast<float>(
                sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_11c = static_cast<float>(
                sprite_004.reset_one_11c + 0.1000000014901161);
            if (alpha < 5) {
                expire();
                return true;
            }
            alpha -= 5;
        }
        if (sequence_index_13e == 2) {
            if (alpha < 20) {
                expire();
                return true;
            }
            alpha -= 20;
        }
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140
            && sequence_index_13e == 2) {
            expire();
        }
        return true;
    }

    case 855:
        if (sequence_index_13e == 1) {
            if (!(time_counter_144 % 5)) {
                effect_emitter()->emit_fighter_effect_433cc0(
                    127, sprite_004.object_x_0e8, 0.0f,
                    static_cast<unsigned char>(sprite_004.object_facing_100), -1);
            }
            if (phase_state_180 == 6) {
                ++state_six_counter_384;
                ++phase_index_184;
                phase_state_180 = 0;
            }
            if (phase_state_180) {
                ++state_364;
                motion_core()->component_f0 = 0.0f;
                if (state_364 > 3) {
                    phase_state_180 = 0;
                    motion_core()->component_f0 = 30.0f;
                    state_364 = 0;
                }
            }
            if (static_cast<signed char>(phase_index_184) <= 0)
                next_sequence_block();
        }
        if (sequence_index_13e == 2) {
            phase_index_184 = 0;
            sprite_004.reset_one_11c =
                static_cast<float>(sprite_004.reset_one_11c * 0.8999999761581421);
            sprite_004.reset_one_118 =
                static_cast<float>(sprite_004.reset_one_118 + 0.2000000029802322);
        }
        if (sprite_004.object_x_0e8 < -300.0f
            || sprite_004.object_x_0e8 >= 1680.0f) {
            expire();
            return true;
        }
        sprite_004.object_x_0e8 +=
            static_cast<float>(sprite_004.object_facing_100) * motion_core()->component_f0;
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        return true;

    case 856: {
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        if (sequence_index_13e == 0) {
            if (!(time_counter_144 % 2)) {
                float payload[3] = {heading_340[0], 0.0f, 2.0f};
                effect_emitter()->spawn_unparented_related_object(
                    854, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (phase_state_180 == 6) { ++phase_index_184; phase_state_180 = 0; }
            if (phase_state_180) next_sequence_block();
            heading_340[0] = static_cast<float>(heading_340[0] + heading_340[1]);
            motion_core()->set_oriented_components_f0_f4(heading_340[0], 40.0f);
            sprite_004.reset_zero_128 = heading_340[0];
            advance_position();
        }
        if (sequence_index_13e == 1) {
            sprite_004.reset_one_118 = static_cast<float>(sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_11c = static_cast<float>(sprite_004.reset_one_11c + 0.1000000014901161);
            if (alpha < 5) { expire(); return true; }
            alpha -= 5;
        }
        if (sequence_index_13e == 2) {
            if (alpha < 20) { expire(); return true; }
            alpha -= 20;
        }
        if (motion_core()->advance_frame_and_dispatch()) expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 2) expire();
        return true;
    }

    case 861: {
        if (sequence_index_13e == 0) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            short const owner_action = *reinterpret_cast<short *>(
                reinterpret_cast<unsigned char *>(owner) + 0x13c);
            if (owner_action >= 50 && owner_action <= 149) {
                expire();
                return true;
            }
            if (!phase_index_184) {
                expire();
                return true;
            }
            float const owner_y = owner->y_f0;
            float const stage_height = aya_stage_surface_height_at_x(this);
            if (stage_height >= owner_y && heading_340[0] == 1.0f) {
                expire();
                return true;
            }
            if (stage_height < owner_y && heading_340[0] == 0.0f) {
                expire();
                return true;
            }
            sprite_004.object_x_0e8 = owner->x_ec;
            sprite_004.object_y_0ec = static_cast<float>(
                static_cast<double>(owner->y_f0) + 100.0);
            float payload[3];
            payload[0] = static_cast<float>(selector_random_roll(100) - 50);
            payload[1] = static_cast<float>(selector_random_roll(100) - 50);
            payload[2] = 1.0f;
            if (!(time_counter_144 % 15)) {
                effect_emitter()->spawn_unparented_related_object(
                    861, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                    static_cast<unsigned char>(sprite_004.object_facing_100), 1,
                    reinterpret_cast<const unsigned *>(payload), 3);
            }
        }
        if (phase_state_180) {
            if (++state_364 >= 6) {
                phase_state_180 = 0;
                state_364 = 0;
            }
        }
        if (sequence_index_13e == 1) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            sprite_004.object_x_0e8 = owner->x_ec;
            reinterpret_cast<unsigned char *>(this)[0x113] -= 10;
            sprite_004.object_y_0ec = static_cast<float>(
                static_cast<double>(owner->y_f0) + 100.0);
            float const scale = static_cast<float>(
                sprite_004.reset_one_118 + state_370);
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = static_cast<float>(
                sprite_004.reset_zero_128 + 20.0);
            state_370 = static_cast<float>(state_370 - 0.02999999932944775);
            if (state_370 < 0.0099999998f)
                state_370 = 0.0099999998f;
        }
        advance_and_expire();
        return true;
    }

    case 862: {
        CharacterObjectEffectEmitter *const owner = fighter_owner_348;
        short const owner_action = *reinterpret_cast<short *>(
            reinterpret_cast<unsigned char *>(owner) + 0x13c);
        short const owner_sequence = *reinterpret_cast<short *>(
            reinterpret_cast<unsigned char *>(owner) + 0x13e);
        if (owner_action == 612 || owner_action == 662) {
            if (owner_sequence > 1 && sequence_index_13e <= 1) {
                select_sequence(2);
                return true;
            }
        } else if (sequence_index_13e <= 1) {
            select_sequence(2);
            return true;
        }
        if (sequence_index_13e < 2) {
            if (owner_action == 612 || owner_action == 662) {
                sprite_004.object_x_0e8 = owner->x_ec;
                sprite_004.object_y_0ec = static_cast<float>(
                    static_cast<double>(owner->y_f0) + 90.0);
            }
        }
        if (motion_core()->advance_frame_and_dispatch())
            expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140
            && sequence_index_13e == 3) {
            expire();
        }
        return true;
    }

    case 900: {
        switch (sequence_index_13e) {
        case 0: {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            short const owner_action = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13c);
            short const owner_sequence = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13e);
            if (owner_action != 710 || (owner_sequence != 1 && owner_sequence != 2)) { expire(); return true; }
            if (!*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x186))
                sprite_004.object_x_0e8 = static_cast<float>(static_cast<double>(heading_340[1]) * sprite_004.object_facing_100 + sprite_004.object_x_0e8);
            owner->x_ec = sprite_004.object_x_0e8;
            owner->y_f0 = sprite_004.object_y_0ec;
            if (sprite_004.object_x_0e8 > 0.0f && sprite_004.object_x_0e8 < 1280.0f && owner_sequence == 2)
                reinterpret_cast<AyaObjectActionStateScaffoldView *>(owner)->select_sequence(1);
            if (((sprite_004.object_x_0e8 >= 1280.0f && sprite_004.object_facing_100 == 1) || (sprite_004.object_x_0e8 <= 0.0f && sprite_004.object_facing_100 == -1)) && !state_364) {
            switch (g_match_identifier) {
            case 0: {
                float i = 0.0f; do { float payload[3] = {static_cast<float>(i * 20.0f + 170.0f), 6.0f, 3.0f}; effect_emitter()->spawn_unparented_related_object(900, sprite_004.object_x_0e8, static_cast<float>(sprite_004.object_y_0ec + 100.0), static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3); i += 1.0f; } while (i < 2.0f); break; }
            case 1: {
                float i = 0.0f; do { float payload[3] = {static_cast<float>(i * 20.0f + 150.0f), 6.0f, 3.0f}; effect_emitter()->spawn_unparented_related_object(900, sprite_004.object_x_0e8, static_cast<float>(sprite_004.object_y_0ec + 100.0), static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3); i += 1.0f; } while (i < 4.0f); break; }
            case 2: {
                float i = 0.0f; do { float payload[3] = {static_cast<float>(i * 20.0f + 140.0f), 6.0f, 3.0f}; effect_emitter()->spawn_unparented_related_object(900, sprite_004.object_x_0e8, static_cast<float>(sprite_004.object_y_0ec + 100.0), static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3); i += 1.0f; } while (i < 5.0f); break; }
            case 3: {
                float i = 0.0f; do { float payload[3] = {static_cast<float>(i * 20.0f + 120.0f), 6.0f, 3.0f}; effect_emitter()->spawn_unparented_related_object(900, sprite_004.object_x_0e8, static_cast<float>(sprite_004.object_y_0ec + 100.0), static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3); i += 1.0f; } while (i < 6.0f); break; }
            default: break;
            }
                if (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13e) == 1)
                    reinterpret_cast<AyaObjectActionStateScaffoldView *>(owner)->next_sequence_block();
                state_364 = 1;
            }
            if (sprite_004.object_x_0e8 < 2000.0f && sprite_004.object_x_0e8 > -720.0f) break;
            short &owner_state_730 = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x730);
            if (!owner_state_730) { owner_state_730 = 1; if (static_cast<unsigned int>(g_match_identifier) <= 1u) owner_state_730 = 3; }
            if (owner_state_730 == 2) owner_state_730 = 3;
            expire(); return true;
        }
        case 1:
        case 2:
            if (!related_34c) { expire(); return true; }
            sprite_004.object_x_0e8 = related_34c->x_ec;
            sprite_004.object_y_0ec = static_cast<float>(static_cast<double>(related_34c->y_f0) + 100.0);
            break;
        case 3:
            motion_core()->advance_phase_counter_conditional(2);
            if (phase_state_180 == 6 && ++state_six_counter_384 < 5) { ++phase_index_184; phase_state_180 = 0; }
            if (phase_state_180 || *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x174) <= 0) { next_sequence_block(); return true; }
            if (sprite_004.object_x_0e8 > 1380.0f || sprite_004.object_x_0e8 < -100.0f || sprite_004.object_y_0ec > 1000.0f || sprite_004.object_y_0ec < -160.0f) { expire(); return true; }
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            advance_position();
            break;
        case 4: {
            float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.05000000074505806);
            sprite_004.reset_one_118 = scale; sprite_004.reset_one_11c = scale;
            heading_340[1] = static_cast<float>(heading_340[1] - 1.0); if (heading_340[1] < 1.0f) heading_340[1] = 1.0f;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]); advance_position();
            break;
        }
        case 5: {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            owner->x_ec = sprite_004.object_x_0e8; owner->y_f0 = sprite_004.object_y_0ec;
            sprite_004.object_x_0e8 = static_cast<float>(static_cast<double>(sprite_004.object_facing_100) * motion_core()->component_f0 + sprite_004.object_x_0e8);
            sprite_004.object_y_0ec = static_cast<float>(sprite_004.object_y_0ec - motion_core()->component_f4);
            motion_core()->component_f0 = static_cast<float>(motion_core()->component_f0 - 0.75); if (motion_core()->component_f0 < 10.0f) motion_core()->component_f0 = 10.0f;
            if (time_counter_144 >= 20) { *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x730) = 1; expire(); return true; }
            break;
        }
        default: break;
        }
        if (motion_core()->advance_frame_and_dispatch()) expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 5) expire();
        return true;
    }

    case 901: {
        if (phase_state_180 == 5) { expire(); return true; }
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        switch (sequence_index_13e) {
        case 0:
            if (!(time_counter_144 % 10)) {
                float payload[3] = {heading_340[0], 0.0f, 1.0f};
                effect_emitter()->spawn_unparented_related_object(901, sprite_004.object_x_0e8, sprite_004.object_y_0ec, static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
            heading_340[0] = static_cast<float>(state_370 + state_374 - 90.0);
            state_374 = static_cast<float>(state_374 - 2.0);
            if (state_374 < 0.0f) state_374 = 0.0f;
            if (phase_state_180 == 6 && ++state_six_counter_384 < 5) { ++phase_index_184; phase_state_180 = 0; }
            motion_core()->advance_phase_counter_conditional(5);
            if (phase_state_180 || *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x174) <= 0) next_sequence_block();
            heading_340[1] = static_cast<float>(heading_340[1] - 0.5);
            if (heading_340[1] < 5.0f) heading_340[1] = 5.0f;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            sprite_004.reset_zero_128 = heading_340[0];
            advance_position();
            if (state_374 == 0.0f && ++state_364 >= 300) {
                if (sprite_004.object_x_0e8 > 1380.0f || sprite_004.object_x_0e8 < -100.0f || sprite_004.object_y_0ec > 1000.0f || sprite_004.object_y_0ec < -160.0f) { expire(); return true; }
            }
            break;
        case 1:
            if (alpha < 20) { expire(); return true; }
            alpha -= 20;
            break;
        case 2:
            sprite_004.reset_one_118 = static_cast<float>(sprite_004.reset_one_118 + 0.1000000014901161);
            sprite_004.reset_one_11c = static_cast<float>(sprite_004.reset_one_11c + 0.1000000014901161);
            if (alpha < 5) { expire(); return true; }
            alpha -= 5;
            break;
        case 3:
            if (!(time_counter_144 % 10)) {
                float payload[3] = {heading_340[0], 0.0f, 1.0f};
                effect_emitter()->spawn_unparented_related_object(901, sprite_004.object_x_0e8, sprite_004.object_y_0ec, static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (phase_state_180 == 6 && ++state_six_counter_384 < 20) { ++phase_index_184; phase_state_180 = 0; }
            motion_core()->advance_phase_counter_conditional(5);
            if (phase_state_180 || *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x174) <= 0) next_sequence_block();
            heading_340[1] = static_cast<float>(heading_340[1] - 0.5);
            if (heading_340[1] < 5.0f) heading_340[1] = 5.0f;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            sprite_004.reset_zero_128 = heading_340[0];
            advance_position();
            if (sprite_004.object_x_0e8 > 1380.0f || sprite_004.object_x_0e8 < -100.0f || sprite_004.object_y_0ec > 1000.0f || sprite_004.object_y_0ec < -160.0f) { expire(); return true; }
            break;
        default:
            break;
        }
        if (motion_core()->advance_frame_and_dispatch()) expire();
        if (!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e == 3) expire();
        return true;
    }

    case 902: {
        if (sequence_index_13e >= 2) {
            motion_core()->component_f0 = static_cast<float>(motion_core()->component_f0 - 0.2000000029802322);
            if (motion_core()->component_f0 < 0.0f) motion_core()->component_f0 = 0.0f;
        } else {
            motion_core()->component_f0 = static_cast<float>(motion_core()->component_f0 - 0.4000000059604645);
            if (motion_core()->component_f0 < 3.0f) motion_core()->component_f0 = 3.0f;
            if (sprite_004.object_facing_100 == 1 && sprite_004.object_x_0e8 >= 1240.0f) sprite_004.object_facing_100 = -1;
            if (sprite_004.object_facing_100 == -1 && sprite_004.object_x_0e8 <= 40.0f) sprite_004.object_facing_100 = 1;
            if (!(time_counter_144 % 3)) {
                state_370 = static_cast<float>(state_370 - 16.0);
                if (state_370 <= -180.0f) state_370 = static_cast<float>(state_370 + 360.0);
                float payload[3] = {state_370, 15.0f, 1.0f};
                int const spawn_side = (state_370 < 0.0f || state_370 > 180.0f) ? -1 : 1;
                effect_emitter()->spawn_unparented_related_object(821, sprite_004.object_x_0e8, sprite_004.object_y_0ec, static_cast<unsigned char>(sprite_004.object_facing_100), spawn_side, reinterpret_cast<const unsigned *>(payload), 3);
            }
        }
        if (sequence_index_13e == 1) {
            if (phase_state_180 == 6) { ++state_six_counter_384; ++phase_index_184; phase_state_180 = 0; }
            if (phase_state_180) {
                if (++state_364 > 3) { phase_state_180 = 0; motion_core()->component_f0 = 30.0f; state_364 = 0; }
                else motion_core()->component_f0 = 0.0f;
            }
            if (static_cast<signed char>(phase_index_184) <= 0) next_sequence_block();
            short const owner_state = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x174);
            switch (g_match_identifier) {
            case 0:
                if (time_counter_144 > 180 || owner_state <= 0) { phase_index_184 = 0; next_sequence_block(); }
                break;
            case 1:
                if (!(time_counter_144 <= 320 && owner_state > 0)) { phase_index_184 = 0; next_sequence_block(); }
                break;
            case 2:
                if (time_counter_144 > 500 || owner_state <= 0) { phase_index_184 = 0; next_sequence_block(); }
                break;
            case 3:
                if (!(time_counter_144 <= 600 && owner_state > 0)) { phase_index_184 = 0; next_sequence_block(); }
                break;
            default:
                break;
            }
        }
        sprite_004.object_x_0e8 = static_cast<float>(static_cast<double>(sprite_004.object_facing_100) * motion_core()->component_f0 + sprite_004.object_x_0e8);
        advance_and_expire();
        return true;
    }

    case 903: {
        unsigned char &alpha = reinterpret_cast<unsigned char *>(this)[0x113];
        switch (sequence_index_13e) {
        case 0:
            sprite_004.object_x_0e8 = static_cast<float>(sprite_004.object_x_0e8 + 40 * static_cast<signed char>(sprite_004.object_facing_100));
            sprite_004.object_y_0ec = static_cast<float>(sprite_004.object_y_0ec + 8.0);
            if (sprite_004.object_x_0e8 > 1380.0f || sprite_004.object_x_0e8 < -100.0f) { expire(); return true; }
            break;
        case 1:
        case 6:
            if (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x174) <= 0) { expire(); return true; }
            if (phase_state_180 == 6) { ++state_six_counter_384; ++phase_index_184; phase_state_180 = 0; }
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            advance_position();
            if (time_counter_144 >= 180) { expire(); return true; }
            break;
        case 2: {
            if (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x174) <= 0) { expire(); return true; }
            if (phase_state_180 == 6) { ++state_six_counter_384; ++phase_index_184; phase_state_180 = 0; }
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            bool const initial_phase = state_364 == 0;
            advance_position();
            sprite_004.reset_one_118 = static_cast<float>(sprite_004.reset_one_118 + 0.02500000037252903);
            sprite_004.reset_one_11c = static_cast<float>(sprite_004.reset_one_11c * 0.949999988079071);
            if (initial_phase) {
                if (time_counter_144 >= 180) state_364 = 1;
            } else {
                sprite_004.reset_one_11c = static_cast<float>(sprite_004.reset_one_11c * 0.949999988079071);
                if (alpha < 20) { expire(); return true; }
                alpha -= 20;
                reinterpret_cast<unsigned char *>(this)[0x111] -= 20;
                reinterpret_cast<unsigned char *>(this)[0x110] -= 20;
            }
            break;
        }
        case 3: {
            if (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(fighter_owner_348) + 0x174) <= 0) { expire(); return true; }
            if (phase_state_180 == 6) { ++state_six_counter_384; ++phase_index_184; phase_state_180 = 0; }
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            bool const initial_phase = state_364 == 0;
            advance_position();
            sprite_004.reset_one_118 = static_cast<float>(sprite_004.reset_one_118 + 0.05000000074505806);
            sprite_004.reset_one_11c = static_cast<float>(sprite_004.reset_one_11c * 0.9800000190734863);
            if (initial_phase) {
                if (time_counter_144 >= 180) state_364 = 1;
            } else {
                sprite_004.reset_one_11c = static_cast<float>(sprite_004.reset_one_11c * 0.949999988079071);
                if (alpha < 20) { expire(); return true; }
                alpha -= 20;
                reinterpret_cast<unsigned char *>(this)[0x111] -= 20;
                reinterpret_cast<unsigned char *>(this)[0x110] -= 20;
            }
            break;
        }
        case 4:
        case 5: {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            short const owner_action = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13c);
            short const owner_sequence = *reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(owner) + 0x13e);
            if (owner_action != 740 || (owner_sequence != 1 && owner_sequence != 2)) { expire(); return true; }
            sprite_004.object_x_0e8 = owner->x_ec;
            sprite_004.object_y_0ec = static_cast<float>(static_cast<double>(owner->y_f0) + 100.0);
            sprite_004.reset_zero_128 = static_cast<float>(sprite_004.reset_zero_128 + (sequence_index_13e == 4 ? 1.0 : -1.0));
            alpha = alpha > 245 ? 255 : static_cast<unsigned char>(alpha + 10);
            break;
        }
        case 7:
            if (phase_state_180) { next_sequence_block(); return true; }
            motion_core()->component_f4 = static_cast<float>(motion_core()->component_f4 - 0.2000000029802322);
            if (state_370 > motion_core()->component_f4) motion_core()->component_f4 = state_370;
            advance_position();
            if (sprite_004.object_x_0e8 > 1380.0f || sprite_004.object_x_0e8 < -100.0f || sprite_004.object_y_0ec > 1000.0f || sprite_004.object_y_0ec < -160.0f) { expire(); return true; }
            break;
        case 8:
            sprite_004.reset_one_118 = static_cast<float>(sprite_004.reset_one_118 * 0.9200000166893005);
            sprite_004.reset_one_11c = sprite_004.reset_one_118;
            if (alpha < 20 || time_counter_144 < 5) { expire(); return true; }
            alpha -= 20;
            reinterpret_cast<unsigned char *>(this)[0x111] -= 20;
            reinterpret_cast<unsigned char *>(this)[0x110] -= 20;
            break;
        case 9:
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            advance_position();
            if (!(time_counter_144 % 3)) {
                float payload[3] = {
                    static_cast<float>(-70.0 - selector_random_roll(40)),
                    static_cast<float>(selector_random_roll(60) * 0.1000000014901161 + 4.0),
                    7.0f,
                };
                effect_emitter()->spawn_unparented_related_object(903, sprite_004.object_x_0e8, sprite_004.object_y_0ec, static_cast<unsigned char>(sprite_004.object_facing_100), 1, reinterpret_cast<const unsigned *>(payload), 3);
            }
            if (sprite_004.object_x_0e8 > 1380.0f || sprite_004.object_x_0e8 < -100.0f || sprite_004.object_y_0ec > 1000.0f || sprite_004.object_y_0ec < -160.0f || time_counter_144 >= 60) { expire(); return true; }
            break;
        default:
            break;
        }
        advance_and_expire();
        return true;
    }

    case 980:
        // This ten-byte physical owner is independently shared by ReimuObject,
        // AliceObject, YoumuObject and AyaObject +0x28 roots.
        effect_emitter()->update_ping_pong_motion_and_periodic_spawn();
        advance_and_expire();
        return true;

    case 990: {
        float const scale = static_cast<float>(sprite_004.reset_one_118 + 0.30000001192092896);
        sprite_004.reset_one_118 = scale;
        sprite_004.reset_one_11c = scale;
        advance_and_expire();
        return true;
    }

    case 997:
        if (sequence_index_13e == 0
            && (sprite_004.object_x_0e8 > 1480.0f
                || sprite_004.object_x_0e8 < -200.0f)) {
            expire();
            return true;
        }
        advance_position();
        advance_and_expire();
        return true;

    case 998: {
        sprite_004.reset_zero_128 =
            static_cast<float>(sprite_004.reset_zero_128 + 15.0);
        if (sequence_index_13e == 0) {
            CharacterObjectEffectEmitter *const owner = fighter_owner_348;
            short const owner_action = *reinterpret_cast<short *>(
                reinterpret_cast<unsigned char *>(owner) + 0x13c);
            if (owner_action >= 154 && owner_action <= 157) {
                sprite_004.object_x_0e8 = owner->x_ec
                    + 57.0f * static_cast<float>(sprite_004.object_facing_100);
                sprite_004.object_y_0ec = owner->y_f0 + 60.0f;
            }
            if (owner_action >= 150 && owner_action <= 153) {
                sprite_004.object_x_0e8 = owner->x_ec
                    + 57.0f * static_cast<float>(sprite_004.object_facing_100);
                sprite_004.object_y_0ec = owner->y_f0 + 94.0f;
            }
            if (owner_action == 158) {
                sprite_004.object_x_0e8 = owner->x_ec
                    + 57.0f * static_cast<float>(sprite_004.object_facing_100);
                sprite_004.object_y_0ec = owner->y_f0 + 100.0f;
            }
            if (owner_action < 150 || owner_action > 158) {
                next_sequence_block();
                reinterpret_cast<unsigned char *>(owner)[0x751] = 0;
            }
        }
        if (sequence_index_13e == 1) {
            unsigned char const alpha =
                reinterpret_cast<unsigned char *>(this)[0x113];
            if (alpha < 10) {
                expire();
                return true;
            }
            reinterpret_cast<unsigned char *>(this)[0x113] = alpha - 10;
        }
        advance_and_expire();
        return true;
    }

    default:
        return false;
    }
}

} // namespace th105
