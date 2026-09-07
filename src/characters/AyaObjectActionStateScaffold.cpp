#include "battle/EffectSprite.hpp"
#include "characters/AnimationSequenceVirtuals.hpp"
#include "characters/CharacterObjectEffects.hpp"
#include "characters/CharacterObjectRuntime.hpp"

#include <stddef.h>

namespace th105 {

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
    unsigned char unknown_34c[0x18];
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
