#include "battle/EffectSprite.hpp"
#include "characters/AnimationSequenceVirtuals.hpp"
#include "characters/CharacterObjectEffects.hpp"
#include "characters/CharacterObjectRuntime.hpp"

#include <stddef.h>

namespace th105 {

int __cdecl selector_random_roll(int limit);
unsigned int __cdecl mt19937_next_u32();
double __cdecl atan2_degrees(float y, float x);
extern int g_match_identifier;

struct YoumuObjectAuxRendererView {
    unsigned char unknown_000[0xe8];
    float x_e8;
    float y_ec;
    unsigned char unknown_f0[0x08];
    float field_f8;
    float field_fc;
    unsigned char unknown_100[0x04];
    signed char facing_104;
};

class YoumuObjectActionEntryView {
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

    // ABI-only names for two current member helpers whose machine contracts
    // are closed but whose gameplay names are not yet independently proved.
    void rebuild_aux_renderer_45cd70(short resource_id);
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
    YoumuObjectAuxRendererView *aux_renderer_154;
    AnimationSequenceFrame *frame_158;
    AnimationSequenceBlock *sequence_15c;
    AnimationSequenceTree *sequence_tree_160;
    unsigned int *wave_handles_164;
    void *owner_168;
    CharacterObjectEffectEmitter *related_16c;
    CharacterObjectEffectEmitter *target_170;
    unsigned char unknown_174[8];
    unsigned char state_17c;
    unsigned char unknown_17d[3];
    int phase_state_180;
    unsigned char phase_index_184;
    unsigned char unknown_185[4];
    unsigned char state_189;
    unsigned char unknown_18a[0x1b6];
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

typedef char YoumuObjectActionEntry_action_offset[
    offsetof(YoumuObjectActionEntryView, action_id_13c) == 0x13c ? 1 : -1];
typedef char YoumuObjectActionEntry_frame_offset[
    offsetof(YoumuObjectActionEntryView, frame_150) == 0x150 ? 1 : -1];
typedef char YoumuObjectActionEntry_phase_offset[
    offsetof(YoumuObjectActionEntryView, phase_state_180) == 0x180 ? 1 : -1];
typedef char YoumuObjectActionEntry_heading_offset[
    offsetof(YoumuObjectActionEntryView, heading_340) == 0x340 ? 1 : -1];
typedef char YoumuObjectActionEntry_owner_offset[
    offsetof(YoumuObjectActionEntryView, fighter_owner_348) == 0x348 ? 1 : -1];
typedef char YoumuObjectActionEntry_state370_offset[
    offsetof(YoumuObjectActionEntryView, state_370) == 0x370 ? 1 : -1];
typedef char YoumuObjectActionEntry_state384_offset[
    offsetof(YoumuObjectActionEntryView, state_six_counter_384) == 0x384 ? 1 : -1];
typedef char YoumuObjectActionEntry_size[
    sizeof(YoumuObjectActionEntryView) == 0x388 ? 1 : -1];

__forceinline static float unsigned_random_as_float(int limit)
{
    return static_cast<float>(
        static_cast<unsigned int>(selector_random_roll(limit)));
}

void YoumuObjectActionEntryView::initialize_action_entry()
{
    velocity_x_f4() = 0.0f;
    velocity_y_f8() = 0.0f;
    state_370 = 0.0f;
    state_374 = 0.0f;
    state_378 = 0.0f;
    state_37c = 0.0f;
    state_380 = 0.0f;
    state_six_counter_384 = 0;
    phase_counter_386 = 0;
    phase_index_184 = 0;
    state_364 = 0;
    state_366 = 0;
    state_368 = 0;
    state_36a = 0;
    state_36c = 0;

    switch (action_id_13c) {
    case 800: {
        phase_index_184 = 1;
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1) {
            state_378 = static_cast<float>(-atan2_degrees(
                static_cast<float>((target_170->y_f0 - sprite_004.object_y_0ec) + 100.0),
                (target_170->x_ec - sprite_004.object_x_0e8) *
                    static_cast<float>(sprite_004.object_facing_100)));
            if (state_378 > heading_340[4] + 10.0f)
                state_378 = heading_340[4] + 10.0f;
            if (state_378 < heading_340[4] - 10.0f)
                state_378 = heading_340[4] - 10.0f;
            heading_340[0] = state_378;
            state_378 = 0.0f;
            sprite_004.reset_zero_128 = heading_340[0];
        }
        return;
    }

    case 801: {
        phase_index_184 = 1;
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            float payload[3] = {0.0f, 0.0f, 2.0f};
            effect_emitter()->spawn_unparented_related_object(
                801, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1, reinterpret_cast<const unsigned int *>(payload), 3);
        }
        return;
    }

    case 810: {
        sprite_004.reset_zero_124 = -60.0f;
        sprite_004.reset_zero_120 =
            static_cast<float>(30 * static_cast<int>(sprite_004.object_facing_100));
        state_17c = 0;
        phase_index_184 = 1;
        unsigned char *const owner = fighter_owner_348;
        if (*reinterpret_cast<signed char *>(owner + 0x604) == 0) {
            state_364 = 30;
            velocity_x_f4() = 2.0f;
        }
        if (*reinterpret_cast<signed char *>(owner + 0x604) >= 1) {
            state_364 = 50;
            velocity_x_f4() = 3.0f;
        }
        if (*reinterpret_cast<signed char *>(owner + 0x604) >= 4) {
            velocity_x_f4() = 4.0f;
            state_364 = 80;
            next_sequence_block();
            phase_index_184 = 2;
        }
        return;
    }

    case 811:
        state_17c = 1;
        select_sequence(static_cast<int>(heading_340[2]));
        return;
    case 812:
        state_17c = 2;
        select_sequence(static_cast<int>(heading_340[2]));
        return;

    case 813:
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            float const scale = unsigned_random_as_float(50) * 0.01f + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
        }
        if (sequence_index_13e == 1) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            sprite_004.reset_zero_120 =
                static_cast<float>(sprite_004.object_facing_100) * heading_340[0];
            sprite_004.reset_zero_124 = static_cast<float>(
                static_cast<unsigned int>(selector_random_roll(30) + 50));
        }
        return;

    case 815:
        state_17c = 4;
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0)
            phase_index_184 = 1;
        if (sequence_index_13e == 3)
            phase_index_184 = 2;
        velocity_x_f4() = heading_340[0];
        velocity_y_f8() = heading_340[1];
        return;

    case 817: {
        float const scale = heading_340[3];
        sprite_004.reset_one_118 = scale;
        sprite_004.reset_one_11c = scale;
        sprite_004.reset_zero_104 = 220.0f;
        return;
    }

    case 818:
        sprite_004.reset_zero_128 = heading_340[0];
        state_17c = 7;
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            sprite_004.reset_one_118 = 0.5f;
            sprite_004.reset_one_11c = 0.5f;
            phase_index_184 = 1;
        }
        if (sequence_index_13e == 1) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            state_370 = 6.0f - unsigned_random_as_float(12);
            sprite_004.reset_one_118 = 0.5f;
            sprite_004.reset_one_11c = 0.5f;
        }
        if (sequence_index_13e == 2) {
            float const scale = unsigned_random_as_float(10) * 0.1f + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
        }
        return;

    case 820:
        phase_index_184 = 1;
        goto action850_angle_and_select;
    case 821:
        sprite_004.reset_zero_128 = heading_340[0];
        goto action848_select;

    case 823: {
        sprite_004.reset_zero_128 = heading_340[0];
        state_17c = 11;
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            motion_core()->set_oriented_components_f0_f4(
                heading_340[0], heading_340[1]);
            float payload[3] = {0.0f, 0.0f, 1.0f};
            phase_index_184 = 1;
            effect_emitter()->spawn_unparented_related_object(
                823, sprite_004.object_x_0e8, sprite_004.object_y_0ec,
                static_cast<unsigned char>(sprite_004.object_facing_100),
                1, reinterpret_cast<const unsigned int *>(payload), 3);
        }
        if (sequence_index_13e == 1)
            state_370 = 0.25f;
        if (sequence_index_13e == 3) {
            float const scale = unsigned_random_as_float(10) * 0.1f + 0.25f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
        }
        if (sequence_index_13e == 4) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            float const scale = unsigned_random_as_float(5) * 0.1f + 1.0f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
        }
        return;
    }

    case 850:
        sprite_004.reset_one_118 = 2.0f;
        sprite_004.reset_one_11c = 2.0f;
action850_angle_and_select: {
        float *const heading = heading_340;
        void **const vtable = *reinterpret_cast<void ***>(this);
        sprite_004.reset_zero_128 = heading[0];
        typedef int (__thiscall *SelectSequenceFn)(YoumuObjectActionEntryView *, int);
        reinterpret_cast<SelectSequenceFn>(vtable[3])(this, static_cast<int>(heading[2]));
        return;
    }

    case 851: {
        double const sequence_value = heading_340[2];
        state_344 = 1;
        select_sequence(static_cast<int>(sequence_value));
        return;
    }

    case 852:
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1) {
            state_370 = unsigned_random_as_float(5) + 10.0f;
            float const scaled_random = unsigned_random_as_float(10) * 0.01f;
            state_374 = scaled_random + 0.4f;
        }
        return;

    case 853:
        state_344 = 1;
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 2)
            phase_index_184 = 1;
        if (sequence_index_13e == 3)
            sprite_004.reset_one_11c = 3.0f;
        return;

    case 854:
        state_344 = 1;
        select_sequence(static_cast<int>(heading_340[2]));
        return;

    case 848:
action848_select:
        select_sequence(static_cast<int>(heading_340[2]));
        return;


    case 855:
        state_344 = 1;
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1) {
            state_370 = unsigned_random_as_float(5) + 10.0f;
            float const scaled_random = unsigned_random_as_float(10) * 0.01f;
            state_374 = scaled_random + 0.6f;
        }
        if (sequence_index_13e == 2) {
            float const scaled_random = unsigned_random_as_float(10) * 0.1f;
            sprite_004.reset_one_11c = scaled_random + 1.0f;
            sprite_004.reset_one_118 =
                static_cast<float>(mt19937_next_u32()) + 0.75f;
        }
        return;

    case 856:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            float const scaled_random = unsigned_random_as_float(10) * 0.1f;
            float const scale = scaled_random + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            motion_core()->set_oriented_components_f0_f4(
                heading_340[0], heading_340[1]);
            state_370 = 3.0f - unsigned_random_as_float(6);
        }
        if (sequence_index_13e == 2) {
            sprite_004.reset_zero_128 = heading_340[0];
            state_370 = 0.2f;
            float const scaled_x = unsigned_random_as_float(15) * 0.1f;
            sprite_004.reset_one_118 = scaled_x + 0.5f;
            float const scaled_y = unsigned_random_as_float(5) * 0.1f;
            sprite_004.reset_one_11c = scaled_y + 0.1f;
            rebuild_aux_renderer_45cd70(991);
            aux_renderer_154->field_f8 = 10.0f;
            aux_renderer_154->field_fc = 10.0f;
            aux_renderer_154->x_e8 = sprite_004.object_x_0e8;
            aux_renderer_154->y_ec = sprite_004.object_y_0ec;
            aux_renderer_154->facing_104 = sprite_004.object_facing_100;
        }
        if (sequence_index_13e == 4)
            phase_index_184 = 1;
        return;

    case 857:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0)
            phase_index_184 = 1;
        if (sequence_index_13e == 4) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            float const scaled_random = unsigned_random_as_float(100) * 0.01f;
            float const scale = scaled_random + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            motion_core()->set_oriented_components_f0_f4(
                heading_340[0], heading_340[1]);
            state_370 = static_cast<float>(
                5.0 - unsigned_random_as_float(10));
        }
        return;

    case 899:
        sprite_004.reset_zero_128 = heading_340[0];
        select_sequence(static_cast<int>(heading_340[2]));
        state_189 = 1;
        if (sequence_index_13e == 1)
            velocity_y_f8() = 4.0f;
        if (sequence_index_13e == 4) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            sprite_004.reset_zero_120 =
                static_cast<float>(sprite_004.object_facing_100) * heading_340[0];
            sprite_004.reset_zero_124 = static_cast<float>(
                static_cast<unsigned int>(selector_random_roll(30) + 50));
        }
        return;

    case 900:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0 || sequence_index_13e == 1) {
            velocity_y_f8() = 0.0f;
            sprite_004.reset_zero_128 = heading_340[0];
        }
        if (sequence_index_13e == 2) {
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading_340[0];
        }
        if (sequence_index_13e == 5) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            float const scale = unsigned_random_as_float(50) * 0.01f + 0.75f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            state_374 = unsigned_random_as_float(50) * 0.1f - 2.5f;
        }
        return;

    case 901:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            float const scaled_random =
                static_cast<float>(unsigned_random_as_float(10) * 0.1f);
            float const scale = scaled_random + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            motion_core()->set_oriented_components_f0_f4(
                heading_340[0], heading_340[1]);
            state_370 =
                static_cast<float>(3.0 - unsigned_random_as_float(6));
        }
        if (sequence_index_13e == 2)
            sprite_004.reset_zero_128 = heading_340[0];
        if (sequence_index_13e == 3) {
            double const horizontal_random =
                unsigned_random_as_float(80) - 40.0;
            sprite_004.reset_zero_120 = static_cast<float>(
                horizontal_random *
                static_cast<double>(sprite_004.object_facing_100));
            sprite_004.reset_zero_124 = static_cast<float>(
                unsigned_random_as_float(80) - 40.0);
            phase_index_184 = 1;
        }
        if (sequence_index_13e == 4) {
            double const horizontal_random =
                unsigned_random_as_float(80) - 40.0;
            sprite_004.reset_zero_120 = static_cast<float>(
                horizontal_random *
                static_cast<double>(sprite_004.object_facing_100));
            sprite_004.reset_zero_124 = static_cast<float>(
                unsigned_random_as_float(80) - 40.0);
            phase_index_184 = 1;
        }
        if (sequence_index_13e == 6) {
            switch (g_match_identifier) {
            case 0:
                state_366 = 30;
                state_368 = 4;
                break;
            case 1:
                state_366 = 25;
                state_368 = 7;
                break;
            case 2:
                state_366 = 20;
                state_368 = 10;
                break;
            case 3:
                state_366 = 15;
                state_368 = 12;
                break;
            default:
                break;
            }
        }
        if (sequence_index_13e == 7) {
            phase_index_184 = 1;
            sprite_004.reset_zero_128 = heading_340[0];
        }
        return;

    case 902:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 1) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            float const scaled_random = unsigned_random_as_float(100) * 0.01f;
            float const scale = scaled_random + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            motion_core()->set_oriented_components_f0_f4(
                heading_340[0], heading_340[1]);
            unsigned int const decay_roll =
                static_cast<unsigned int>(selector_random_roll(6));
            phase_index_184 = 1;
            state_370 = 3.0f - static_cast<float>(decay_roll);
        }
        if (sequence_index_13e == 2) {
            sprite_004.reset_zero_128 = heading_340[0];
            state_370 = 0.2f;
            float const scaled_x = unsigned_random_as_float(15) * 0.1f;
            sprite_004.reset_one_118 = scaled_x + 0.5f;
            float const scaled_y = unsigned_random_as_float(5) * 0.1f;
            sprite_004.reset_one_11c = scaled_y + 0.1f;
            rebuild_aux_renderer_45cd70(991);
            aux_renderer_154->field_f8 = 10.0f;
            aux_renderer_154->field_fc = 10.0f;
            aux_renderer_154->x_e8 = sprite_004.object_x_0e8;
            aux_renderer_154->y_ec = sprite_004.object_y_0ec;
            aux_renderer_154->facing_104 = sprite_004.object_facing_100;
        }
        if (sequence_index_13e == 4)
            phase_index_184 = 1;
        if (sequence_index_13e == 6)
            phase_index_184 = 1;
        if (sequence_index_13e == 10) {
            sprite_004.reset_zero_128 = unsigned_random_as_float(360);
            float const scaled_random = unsigned_random_as_float(100) * 0.01f;
            float const scale = scaled_random + 0.5f;
            sprite_004.reset_one_118 = scale;
            sprite_004.reset_one_11c = scale;
            motion_core()->set_oriented_components_f0_f4(
                heading_340[0], heading_340[1]);
            unsigned int const decay_roll =
                static_cast<unsigned int>(selector_random_roll(10));
            state_370 = 5.0f - static_cast<float>(decay_roll);
            phase_index_184 = 1;
        }
        return;

    case 930:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            sprite_004.reset_zero_128 = heading_340[0];
            sprite_004.reset_one_118 = 20.0f;
            sprite_004.reset_one_11c = 0.1f;
        }
        if (sequence_index_13e == 2) {
            sprite_004.reset_zero_128 = heading_340[0];
            motion_core()->set_oriented_components_f0_f4(
                heading_340[0], heading_340[1]);
            phase_index_184 = 1;
        }
        if (sequence_index_13e == 3) {
            sprite_004.reset_zero_128 = heading_340[0];
            motion_core()->set_oriented_components_f0_f4(
                heading_340[0], heading_340[1]);
            phase_index_184 = 1;
        }
        if (sequence_index_13e == 6)
            state_370 = 0.5f;
        return;

    case 980:
        continue_action_980_596370();
        return;

    case 999:
        select_sequence(static_cast<int>(heading_340[2]));
        if (sequence_index_13e == 0) {
            velocity_x_f4() = heading_340[0];
            velocity_y_f8() = heading_340[1];
        }
        if (sequence_index_13e == 3)
            velocity_y_f8() = -3.0f;
        return;

    default:
        return;
    }
}

} // namespace th105
