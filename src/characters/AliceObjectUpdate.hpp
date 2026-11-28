#pragma once

#include <stddef.h>

namespace th105 {

class AliceObjectUpdateView;

struct AliceUpdateMotionView {
    unsigned char base_000;
    void set_components(float angle, float magnitude);
    int selector_random_range(int a, int b);
};

struct AliceUpdateOwnerView {
    unsigned char pad_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char pad_0f4[0x10];
    signed char facing_104;
    unsigned char pad_105[0x37];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    unsigned char pad_142[0x2e];
    AliceUpdateOwnerView *target_170;
    short word_174;
    unsigned char pad_176[0xa];
    int field_180;
    unsigned char pad_184[0x480];
    signed char byte_604;
    unsigned char pad_605[0x2];
    signed char byte_607;
    signed char byte_608;
    unsigned char pad_609[0x4];
    signed char byte_60d;
    unsigned char pad_60e[0x1];
    unsigned char byte_60f;
    unsigned char pad_610[0xa4];
    int input_x_6b4;
    int input_y_6b8;
    unsigned int input_a_6bc;
    unsigned int input_b_6c0;
    unsigned int input_c_6c4;
    unsigned char pad_6c8[0x89];
    unsigned char byte_751;
    unsigned char pad_752[0x3a];
    short word_78c;
    short word_78e;
    unsigned char pad_790[0x14];
    short word_7a4;
    short word_7a6;
    unsigned char pad_7a8[0x4];
    short word_7ac;
    unsigned char pad_7ae[0x2];
    float doll_x_7b0[4];
    float doll_y_7c0[4];
    unsigned char byte_7d0;
    unsigned char doll_flag_7d1[4];

    void dispatch_character_wave_handle(unsigned index);
    void publish_battle_layout_scalar(float value);
    void dispatch_indexed_event_member(unsigned index);
};

// Pointer-only primary call view; do not instantiate as a recovered allocation.
class AliceObjectUpdateView {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void set_action(short action_id);
    virtual int select_sequence(short sequence_id);
    virtual void slot10();
    virtual unsigned char next_sequence_block();
    virtual void slot18();
    virtual int select_frame(short frame_id);
    virtual unsigned char next_sequence_frame();
    virtual void slot24();
    virtual void update_action_state();

    unsigned char advance_frame();
    unsigned char advance_six(int limit);
    unsigned char advance_phase(int limit);
    unsigned char emit_repeated(int mode, int count200, int count201);
    void replace_secondary(int, float, int, int, int);
    void release_secondary();
    void release_auxiliary();
    void turn_heading(float bias, float max_step, float y_offset);
    float stage_surface_height();
    int has_crossed_stage_surface_while_descending();
    void publish_battle_layout_scalar(float value);
    void emit_effect(int effect_code, float x, float y, unsigned char direction, int trailing);
    unsigned char update_owner_tracking_and_proximity();
    unsigned char update_flight_state(short expected_state);
    void *spawn_unparented(int action_id, float x, float y, signed char facing, signed char layer, const void *payload, int count);
    void *spawn_parented(int action_id, float x, float y, signed char facing, signed char layer, const void *payload, int count);
    void publish_bounds_descriptor(int x1, int y1, int x2, int y2, short m10, short m12, short m14);
    void *position_relative_to_owner(int, int);
    void update_ping_pong_motion();
    __forceinline bool retire_on_collision5() {
        if (field_180 == 5) { --lifetime_330; return true; }
        return false;
    }
    __forceinline bool emit_or_retire(int mode, int c1, int c2) {
        if (emit_repeated(mode, c1, c2)) { --lifetime_330; return true; }
        return false;
    }
    __forceinline bool is_oob() const {
        return x_ec > 1380.0f || x_ec < -100.0 || y_f0 > 1000.0 || y_f0 < -160.0;
    }
    __forceinline bool is_vx_over5() const {
        return velocity_x_f4 > 5.0f;
    }

    AliceUpdateMotionView motion_004;
    unsigned char pad_005[0xe7];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    unsigned char pad_0fc[0x4];
    float acceleration_y_100;
    signed char facing_104;
    unsigned char pad_105[0xb];
    unsigned char byte_110;
    unsigned char byte_111;
    unsigned char byte_112;
    unsigned char byte_113;
    unsigned char pad_114[0x8];
    float scale_x_11c;
    float scale_y_120;
    unsigned char pad_124[0x8];
    float rotation_12c;
    unsigned char pad_130[0x5];
    unsigned char byte_135;
    unsigned char pad_136[0x6];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    unsigned char pad_148[0x28];
    AliceUpdateOwnerView *target_170;
    short word_174;
    unsigned char pad_176[0x2];
    int field_178;
    unsigned char byte_17c;
    unsigned char pad_17d[0x3];
    int field_180;
    signed char byte_184;
    unsigned char pad_185[0x1ab];
    int lifetime_330;
    unsigned char pad_334[0x8];
    signed char layer_33c;
    unsigned char pad_33d[0x3];
    float *params_340;
    unsigned char pad_344[0x4];
    AliceUpdateOwnerView *owner_348;
    AliceObjectUpdateView *related_34c;
    unsigned char pad_350[0x14];
    short word_364;
    short word_366;
    short word_368;
    short word_36a;
    short word_36c;
    unsigned char pad_36e[0x2];
    float field_370;
    float field_374;
    float field_378;
    float field_37c;
    float field_380;
    unsigned char pad_384[0x4];
    short word_388;
};

#define ALICE_OBJ_CHECK(T, M, OFF) \
    typedef char Check_##T##_##M[offsetof(T, M) == (OFF) ? 1 : -1]

ALICE_OBJ_CHECK(AliceUpdateOwnerView, x_ec, 0x0ec);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, y_f0, 0x0f0);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, facing_104, 0x104);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, action_id_13c, 0x13c);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, sequence_index_13e, 0x13e);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, frame_index_140, 0x140);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, target_170, 0x170);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, word_174, 0x174);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, field_180, 0x180);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, byte_604, 0x604);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, byte_607, 0x607);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, byte_608, 0x608);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, byte_60d, 0x60d);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, byte_60f, 0x60f);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, input_x_6b4, 0x6b4);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, input_y_6b8, 0x6b8);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, input_a_6bc, 0x6bc);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, input_b_6c0, 0x6c0);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, input_c_6c4, 0x6c4);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, byte_751, 0x751);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, word_78c, 0x78c);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, word_78e, 0x78e);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, word_7a4, 0x7a4);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, word_7a6, 0x7a6);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, word_7ac, 0x7ac);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, doll_x_7b0, 0x7b0);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, doll_y_7c0, 0x7c0);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, byte_7d0, 0x7d0);
ALICE_OBJ_CHECK(AliceUpdateOwnerView, doll_flag_7d1, 0x7d1);

ALICE_OBJ_CHECK(AliceObjectUpdateView, motion_004, 0x004);
ALICE_OBJ_CHECK(AliceObjectUpdateView, x_ec, 0x0ec);
ALICE_OBJ_CHECK(AliceObjectUpdateView, y_f0, 0x0f0);
ALICE_OBJ_CHECK(AliceObjectUpdateView, velocity_x_f4, 0x0f4);
ALICE_OBJ_CHECK(AliceObjectUpdateView, velocity_y_f8, 0x0f8);
ALICE_OBJ_CHECK(AliceObjectUpdateView, acceleration_y_100, 0x100);
ALICE_OBJ_CHECK(AliceObjectUpdateView, facing_104, 0x104);
ALICE_OBJ_CHECK(AliceObjectUpdateView, byte_110, 0x110);
ALICE_OBJ_CHECK(AliceObjectUpdateView, byte_111, 0x111);
ALICE_OBJ_CHECK(AliceObjectUpdateView, byte_112, 0x112);
ALICE_OBJ_CHECK(AliceObjectUpdateView, byte_113, 0x113);
ALICE_OBJ_CHECK(AliceObjectUpdateView, scale_x_11c, 0x11c);
ALICE_OBJ_CHECK(AliceObjectUpdateView, scale_y_120, 0x120);
ALICE_OBJ_CHECK(AliceObjectUpdateView, rotation_12c, 0x12c);
ALICE_OBJ_CHECK(AliceObjectUpdateView, byte_135, 0x135);
ALICE_OBJ_CHECK(AliceObjectUpdateView, action_id_13c, 0x13c);
ALICE_OBJ_CHECK(AliceObjectUpdateView, sequence_index_13e, 0x13e);
ALICE_OBJ_CHECK(AliceObjectUpdateView, frame_index_140, 0x140);
ALICE_OBJ_CHECK(AliceObjectUpdateView, frame_timer_142, 0x142);
ALICE_OBJ_CHECK(AliceObjectUpdateView, time_counter_144, 0x144);
ALICE_OBJ_CHECK(AliceObjectUpdateView, target_170, 0x170);
ALICE_OBJ_CHECK(AliceObjectUpdateView, word_174, 0x174);
ALICE_OBJ_CHECK(AliceObjectUpdateView, field_178, 0x178);
ALICE_OBJ_CHECK(AliceObjectUpdateView, byte_17c, 0x17c);
ALICE_OBJ_CHECK(AliceObjectUpdateView, field_180, 0x180);
ALICE_OBJ_CHECK(AliceObjectUpdateView, byte_184, 0x184);
ALICE_OBJ_CHECK(AliceObjectUpdateView, lifetime_330, 0x330);
ALICE_OBJ_CHECK(AliceObjectUpdateView, layer_33c, 0x33c);
ALICE_OBJ_CHECK(AliceObjectUpdateView, params_340, 0x340);
ALICE_OBJ_CHECK(AliceObjectUpdateView, owner_348, 0x348);
ALICE_OBJ_CHECK(AliceObjectUpdateView, related_34c, 0x34c);
ALICE_OBJ_CHECK(AliceObjectUpdateView, word_364, 0x364);
ALICE_OBJ_CHECK(AliceObjectUpdateView, word_366, 0x366);
ALICE_OBJ_CHECK(AliceObjectUpdateView, word_368, 0x368);
ALICE_OBJ_CHECK(AliceObjectUpdateView, word_36a, 0x36a);
ALICE_OBJ_CHECK(AliceObjectUpdateView, word_36c, 0x36c);
ALICE_OBJ_CHECK(AliceObjectUpdateView, field_370, 0x370);
ALICE_OBJ_CHECK(AliceObjectUpdateView, field_374, 0x374);
ALICE_OBJ_CHECK(AliceObjectUpdateView, field_378, 0x378);
ALICE_OBJ_CHECK(AliceObjectUpdateView, field_37c, 0x37c);
ALICE_OBJ_CHECK(AliceObjectUpdateView, field_380, 0x380);
ALICE_OBJ_CHECK(AliceObjectUpdateView, word_388, 0x388);

#undef ALICE_OBJ_CHECK

int __cdecl selector_random_roll(int);
float __cdecl lookup_orientation_sine_quantized_abs(float);
float __cdecl lookup_orientation_cosine_quantized_abs(float);
float __cdecl lookup_orientation_sine(int);
float __cdecl lookup_orientation_cosine(int);
float __cdecl lookup_orientation_ratio_quantized_abs(int);
float __cdecl atan2_degrees(float, float);
float __cdecl absolute_scalar_float(float);
float __cdecl square_float_value(float);
int __cdecl square_int_value(int);
float __cdecl sqrt_float_value(float);
extern int g_match_identifier;

} // namespace th105
