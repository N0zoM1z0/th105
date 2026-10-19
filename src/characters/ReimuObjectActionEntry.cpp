// Original Japanese 1.06a ReimuObject vslot+3C, 0x004A1CE0.
// Complete source candidate; no exact claim. See docs/REIMU_OBJECT_ENTRY_2026_10_19.md.
#include "battle/EffectSprite.hpp"
#include "engine/AngleAtan2.hpp"
#include "characters/AnimationSequenceVirtuals.hpp"
#include "characters/CharacterObjectEffects.hpp"
#include "characters/CharacterObjectRuntime.hpp"

#include <stddef.h>

namespace th105 {

int __cdecl selector_random_roll(int limit);
unsigned int __cdecl mt19937_next_u32();
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
double __cdecl lookup_orientation_sine_quantized_abs(float phase);

class ReimuObjectActionEntryView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short action, int sequence);
    virtual int set_action_and_finalize(short action);
    // Slot +0x0C consumes the low word in a four-byte stack slot.
    // See docs/AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md for the 202-byte witness.
    virtual int select_sequence(short sequence);
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

    void continue_action_980_596370();

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
    unsigned char unknown_185[0x1bb];
    float *heading_340;
    short state_344;
    unsigned char unknown_346[2];
    unsigned char *fighter_owner_348;
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

    float &velocity_x_f4()
    {
        return *reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(this) + 0xf4);
    }
    float &velocity_y_f8()
    {
        return *reinterpret_cast<float *>(
            reinterpret_cast<unsigned char *>(this) + 0xf8);
    }
    CharacterObjectRuntime *motion_core()
    {
        return reinterpret_cast<CharacterObjectRuntime *>(
            reinterpret_cast<unsigned char *>(this) + 4);
    }
    CharacterObjectEffectEmitter *effect_emitter()
    {
        return reinterpret_cast<CharacterObjectEffectEmitter *>(this);
    }
};

typedef char ReimuObjectActionEntry_state174_offset[
    offsetof(ReimuObjectActionEntryView, state_174) == 0x174 ? 1 : -1];
typedef char ReimuObjectActionEntry_state344_offset[
    offsetof(ReimuObjectActionEntryView, state_344) == 0x344 ? 1 : -1];
typedef char ReimuObjectActionEntry_action_offset[
    offsetof(ReimuObjectActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char ReimuObjectActionEntry_heading_offset[
    offsetof(ReimuObjectActionEntryView, heading_340) == 0x340 ? 1 : -1];
typedef char ReimuObjectActionEntry_owner_offset[
    offsetof(ReimuObjectActionEntryView, fighter_owner_348) == 0x348 ? 1 : -1];
typedef char ReimuObjectActionEntry_state370_offset[
    offsetof(ReimuObjectActionEntryView, state_370) == 0x370 ? 1 : -1];
typedef char ReimuObjectActionEntry_size[
    sizeof(ReimuObjectActionEntryView) == 0x388 ? 1 : -1];

__forceinline static float unsigned_random_as_float(int limit)
{
    return static_cast<float>(
        static_cast<unsigned int>(selector_random_roll(limit)));
}

void ReimuObjectActionEntryView::initialize_action_entry()
{
    velocity_x_f4() = 0.0f;
    velocity_y_f8() = 0.0f;
    state_370 = 0.0f;
    state_374 = 0.0f;
    state_378 = 0.0f;
    state_37c = 0.0f;
    state_six_counter_384 = 0;
    state_380 = 0.0f;
    phase_counter_386 = 0;
    phase_index_184 = 0;
    state_364 = 0;
    state_366 = 0;
    state_368 = 0;
    state_36a = 0;
    state_36c = 0;

    float *shared_parameters;
    switch (action_id_13c) {
    case 800:
        phase_index_184 = 1;
        goto angle_and_positive_sequence;
    case 801:
        shared_parameters = heading_340;
        phase_index_184 = 3;
        if (shared_parameters[3] != 0.0f)
            phase_index_184 = 6;
        goto zero_scales_angle_and_positive_sequence;
    case 804:
        phase_index_184 = 5;
angle_and_positive_sequence:
        sprite_004.reset_zero_128 = heading_340[0];
        if (heading_340[2] > 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 807:
        sprite_004.reset_one_118 = 1.5f;
        phase_index_184 = 1;
        sprite_004.reset_one_11c = 1.5f;
        sprite_004.reset_zero_128 = 0.0f;
        sprite_004.reset_zero_120 = 75.0f;
        if (heading_340[2] > 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 808:
        sprite_004.reset_one_118 = 2.5f;
        phase_index_184 = 1;
        sprite_004.reset_one_11c = 2.5f;
        sprite_004.reset_zero_128 = 0.0f;
        sprite_004.reset_zero_120 = 75.0f;
        if (heading_340[2] > 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 810:
        shared_parameters = heading_340;
        state_17c = 0;
        phase_index_184 = 2;
zero_scales_angle_and_positive_sequence:
        sprite_004.reset_one_118 = 0.0f;
        sprite_004.reset_one_11c = 0.0f;
        sprite_004.reset_zero_128 = shared_parameters[0];
        if (shared_parameters[2] > 0.0f) {
            select_sequence(static_cast<int>(shared_parameters[2]));
            sprite_004.reset_one_118 = 1.0f;
            sprite_004.reset_one_11c = 1.0f;
        }
        return;
    case 811:
        state_17c = 4;
        phase_index_184 = 1;
        sprite_004.reset_zero_128 = heading_340[0];
        if (heading_340[2] > 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            float payload[3] = {sprite_004.reset_zero_128, 0.0f, 1.0f};
            effect_emitter()->spawn_parented_related_object(
                811, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1, reinterpret_cast<const unsigned *>(payload), 3);
        }
        if (sequence_index_13e == 4) {
            sprite_004.reset_one_118 = unsigned_random_as_float(20) * 0.01f + 1.0f;
            sprite_004.reset_one_11c = unsigned_random_as_float(20) * 0.01f + 1.0f;
        }
        return;
    case 812:
        state_17c = 8;
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            phase_index_184 = 1;
            sprite_004.reset_one_118 = 0.0f;
            sprite_004.reset_one_11c = 0.0f;
        }
        if (sequence_index_13e == 2) {
            phase_index_184 = 1;
            state_370 = 13.0f;
        }
        return;
    case 815:
        state_17c = 1;
        sprite_004.reset_zero_128 = -heading_340[0];
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 3) {
            phase_index_184 = 2;
            if (*reinterpret_cast<signed char *>(fighter_owner_348 + 0x605) >= 1)
                phase_index_184 = 3;
            if (*reinterpret_cast<signed char *>(fighter_owner_348 + 0x605) >= 4)
                phase_index_184 = 4;
        }
        return;
    case 816:
        state_17c = 5;
        sprite_004.reset_zero_128 = heading_340[0];
        if (heading_340[2] > 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            effect_emitter()->ping_pong_phase_113 = 0;
            velocity_x_f4() = -30.0f;
        }
        if (sequence_index_13e == 4) {
            effect_emitter()->ping_pong_phase_113 = 0;
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
        }
        return;
    case 817:
        state_17c = 9;
        if (heading_340[2] > 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            float payload[3] = {0.0f, 0.0f, 2.0f};
            effect_emitter()->spawn_parented_related_object(
                817, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1, reinterpret_cast<const unsigned *>(payload), 3);
        }
        if (sequence_index_13e == 3)
            state_370 = 255.0f;
        if (sequence_index_13e == 4) {
            phase_state_180 = 0;
            state_370 = 1.0f;
            phase_index_184 = 5;
        }
        if (sequence_index_13e == 8) {
            float const scale = unsigned_random_as_float(5) * 0.1f + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            state_370 = unsigned_random_as_float(10) + 5.0f;
            state_374 = unsigned_random_as_float(5) + 4.0f;
            if (static_cast<unsigned int>(selector_random_roll(100)) <= 50)
                state_374 = -state_374;
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
        }
        if (sequence_index_13e == 9) {
            velocity_x_f4() = heading_340[1];
            float payload[3] = {0.0f, 0.0f, 2.0f};
            effect_emitter()->spawn_parented_related_object(
                817, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1, reinterpret_cast<const unsigned *>(payload), 3);
        }
        return;
    case 821:
        state_17c = 6;
        phase_index_184 = 1;
        sprite_004.reset_zero_128 = heading_340[0];
        if (heading_340[2] > 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 822:
        state_17c = 10;
        sprite_004.reset_zero_128 = heading_340[0];
        if (heading_340[2] > 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0)
            phase_index_184 = *reinterpret_cast<signed char *>(fighter_owner_348 + 0x60e) >= 4;
        if (sequence_index_13e == 1)
            effect_emitter()->ping_pong_phase_113 = 0;
        if (sequence_index_13e == 4) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            float const scale = unsigned_random_as_float(100) * 0.01f + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            state_370 = unsigned_random_as_float(20) - 10.0f;
        }
        if (sequence_index_13e == 5 || sequence_index_13e == 6) {
            float const scaled_y = unsigned_random_as_float(40) * 0.1f;
            velocity_y_f8() = scaled_y + 2.0f;
            sprite_004.reset_one_11c = sprite_004.reset_one_118 =
                unsigned_random_as_float(50) * 0.01f + 0.5f;
        }
        return;
    case 825:
        phase_index_184 = 1;
        sprite_004.reset_zero_128 = -heading_340[0];
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 848:
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 3 || sequence_index_13e == 4) {
            sprite_004.reset_zero_120 = static_cast<float>(35 * sprite_004.object_facing_100);
            sprite_004.reset_zero_124 = 75.0f;
        }
        return;
    case 850:
        state_364 = 1;
        phase_index_184 = 1;
        sprite_004.reset_one_118 = 0.1f;
        sprite_004.reset_one_11c = 0.1f;
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 851:
        phase_index_184 = 99;
        if (heading_340[0] != 0.0f)
            select_sequence(static_cast<int>(heading_340[0]));
        return;
    case 852:
        phase_index_184 = 5;
        sprite_004.reset_one_118 = 2.0f;
        sprite_004.reset_one_11c = 2.0f;
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 853:
        sprite_004.reset_one_118 = 0.1f;
        state_364 = 1;
        sprite_004.reset_one_11c = 0.1f;
        state_366 = 1500;
        phase_index_184 = 1;
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 854:
        state_366 = 1500;
        state_364 = 1;
        phase_index_184 = 1;
        sprite_004.reset_one_118 = 0.1f;
        sprite_004.reset_one_11c = 0.1f;
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 855:
        sprite_004.reset_one_118 = 0.0f;
        sprite_004.reset_one_11c = 0.0f;
        return;
    case 856:
        if (heading_340[0] != 0.0f)
            select_sequence(static_cast<int>(heading_340[0]));
        if (sequence_index_13e == 0)
            phase_index_184 = 99;
        if (sequence_index_13e == 2)
            phase_index_184 = 1;
        return;
    case 858:
        phase_index_184 = 2;
        sprite_004.reset_zero_128 = heading_340[1];
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0)
            effect_emitter()->replace_secondary_animation(992, 60.0f, 20, 1, 2);
        return;
    case 859:
        sprite_004.reset_one_118 = 1.5f;
        phase_index_184 = 99;
        sprite_004.reset_one_11c = 1.5f;
        return;
    case 860:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 861: {
        float const speed = static_cast<float>(
            static_cast<float>(mt19937_next_u32() % 20) + 40.0f);
        heading_340[1] = speed;
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        return;
    }
    case 866:
        state_344 = 1;
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 2:
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            break;
        }
        return;
    case 869:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        state_344 = 1;
        switch (sequence_index_13e) {
        case 0:
            state_370 = 0.2f;
            state_374 = 360.0f;
            state_378 = 10.0f;
            break;
        case 2:
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            break;
        case 3:
            sprite_004.reset_zero_128 = heading_340[0];
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            phase_index_184 = 1;
            break;
        case 5:
            state_370 = 10.0f - unsigned_random_as_float(20);
            // The target writes +120 twice, with an RNG call between them.
            sprite_004.reset_one_11c = unsigned_random_as_float(10) * 0.1f + 0.5f;
            sprite_004.reset_one_11c = unsigned_random_as_float(10) * 0.1f + 0.5f;
            break;
        }
        return;
    case 900:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0: case 1: {
            sprite_004.reset_zero_128 = heading_340[0];
            float payload[3] = {0.0f, 0.0f, 2.0f};
            phase_index_184 = 1;
            effect_emitter()->spawn_unparented_related_object(
                900, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1, reinterpret_cast<const unsigned *>(payload), 3);
            break;
        }
        }
        return;
    case 901:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0:
            state_370 = 15.0f;
            break;
        case 1: {
            velocity_y_f8() = 15.0f;
            phase_index_184 = 1;
            velocity_x_f4() = static_cast<float>(
                lookup_orientation_cosine_quantized_abs(-heading_340[0]) * 5.0);
            velocity_y_f8() = static_cast<float>(
                lookup_orientation_sine_quantized_abs(-heading_340[0]) * 2.0 + velocity_y_f8());
            state_370 = unsigned_random_as_float(40) * 0.1f - 2.0f;
            state_174 = static_cast<short>(heading_340[1]);
            break;
        }
        case 5: {
            float const scale = unsigned_random_as_float(10) * 0.1f + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            break;
        }
        }
        return;
    case 902:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0: case 1:
            state_370 = 1.0f;
            break;
        case 2: {
            sprite_004.reset_zero_128 = heading_340[0];
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            float payload[3] = {0.0f, 0.0f, 3.0f};
            phase_index_184 = 1;
            effect_emitter()->spawn_unparented_related_object(
                902, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1, reinterpret_cast<const unsigned *>(payload), 3);
            break;
        }
        }
        return;
    case 903:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0: case 1: case 2: {
            sprite_004.reset_one_11c = sprite_004.reset_one_118 =
                unsigned_random_as_float(10) * 0.1f + 1.0f;
            phase_index_184 = 1;
            break;
        }
        case 3: case 4: case 5: {
            sprite_004.reset_one_11c = sprite_004.reset_one_118 =
                unsigned_random_as_float(15) * 0.1f + 0.5f;
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            break;
        }
        }
        return;
    case 904:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0: case 1: case 2: {
            sprite_004.reset_one_11c = sprite_004.reset_one_118 =
                unsigned_random_as_float(10) * 0.1f + 1.0f;
            phase_index_184 = 1;
            break;
        }
        case 3: case 4: case 5: {
            sprite_004.reset_one_11c = sprite_004.reset_one_118 =
                unsigned_random_as_float(15) * 0.1f + 0.5f;
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            break;
        }
        }
        return;
    case 905:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0:
            state_370 = 1.0f;
            break;
        case 2: case 5:
            sprite_004.reset_zero_128 = heading_340[0];
            break;
        case 3:
            sprite_004.reset_zero_128 = heading_340[0];
            break;
        case 4:
            sprite_004.reset_zero_128 = heading_340[0];
            heading_340[0] = -atan2_degrees(
                static_cast<float>((target_170->y_f0 + 100.0) - sprite_004.object_y_0ec),
                static_cast<float>(sprite_004.object_facing_100) *
                    (target_170->x_ec - sprite_004.object_x_0e8));
            phase_index_184 = 1;
            break;
        }
        return;
    case 906:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0:
            state_370 = 1.0f;
            break;
        case 2: case 5:
            goto shared_sequence_angle_2;
        case 3:
            goto shared_sequence_angle_3;
        case 4:
            effect_emitter()->ping_pong_phase_113 = 0;
            sprite_004.reset_zero_128 = heading_340[0];
            break;
        }
        return;
    case 907:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0:
            state_370 = 1.0f;
            break;
        case 2:
            sprite_004.reset_zero_128 = heading_340[0];
            break;
        case 3:
            sprite_004.reset_zero_128 = heading_340[0];
            break;
        case 4:
            sprite_004.reset_zero_128 = heading_340[0];
            motion_core()->set_oriented_components_f0_f4(heading_340[0], heading_340[1]);
            phase_index_184 = 1;
            break;
        }
        return;
    case 908:
        if (heading_340[2] != 0.0f)
            select_sequence(static_cast<int>(heading_340[2]));
        switch (sequence_index_13e) {
        case 0:
            state_370 = 1.0f;
            break;
        case 5:
            phase_index_184 = 1;
        case 2: case 8:
shared_sequence_angle_2:
            sprite_004.reset_zero_128 = heading_340[0];
            break;
        case 6:
            phase_index_184 = 1;
        case 3: case 9:
shared_sequence_angle_3:
            sprite_004.reset_zero_128 = heading_340[0];
            break;
        case 4: case 7:
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading_340[0];
            break;
        }
        return;
    case 951:
        sprite_004.reset_zero_104 = -45.0f;
        sprite_004.reset_zero_108 = 45.0f;
        return;
    case 980:
        continue_action_980_596370();
        return;
    case 998:
        sprite_004.reset_zero_128 = 0.0f;
        sprite_004.reset_zero_124 = 60.0f;
        return;
    case 999:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 4) {
            velocity_x_f4() = heading_340[0];
            velocity_y_f8() = heading_340[1];
        }
        return;
    default:
        return;
    }
}

} // namespace th105
