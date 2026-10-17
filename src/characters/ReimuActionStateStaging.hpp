#pragma once

#include <stddef.h>

namespace th105 {

// Verified entry phase of Reimu's 81550-byte +0x28 root @ 0x478FA0.
// This staging helper is not the target root or an original function boundary.
// Its bool reports whether the entry phase completes the update; false means
// the still-unreconstructed action switch must run. No root implementation or
// exact credit is claimed. Numeric field labels preserve unresolved meanings.
struct ReimuPreludePeerView {
    unsigned char reserved_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char reserved_0f4[0x80];
    short word_174;
    unsigned char reserved_176[0x316];
    short word_48c;
};

class ReimuActionStatePreludeView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual int set_action(short action);
    virtual int set_sequence(int sequence);
    virtual void slot_10();
    virtual unsigned char next_sequence_block();

    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction, int arg5, int arg6, int arg7);
    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction, int arg5,
        const float *parameters, int parameter_count);
    bool run_checked_prelude();
    // True completes the entry/low path; false hands action>300 to later source.
    bool run_checked_low_dispatch();
    // Entry, low table and middle/high actions through619; later actions remain pending.
    bool run_checked_action_dispatch();
    void update_common_action_state();
    void publish_texture_state(signed char texture_index, short duration);
    void set_word_48a(short value);
    void dispatch_indexed_sequence_window_45c8b0(signed char relative_index, int outcome, int source_token);
    void advance_secondary_event_effect_cycle();
    // True handles action0..10; false leaves other actions to later phases.
    bool try_run_checked_low_action();
    // True handles actions71..78; this is another staging phase.
    bool try_run_checked_recovery_action();
    // Actions88/89/145 and197..204, without an original boundary claim.
    bool try_run_checked_movement_attack_action();
    // Remaining low-table actions and direct action300.
    bool try_run_checked_late_low_action();
    void adjust_counter_482(short amount, int floor_value);
    int add_scaled_counter(int value);
    void dispatch_character_wave_handle(unsigned int index);
    unsigned char try_dispatch_directional_action_208_210(int option);
    unsigned char is_at_stage_surface();
    void face_opponent_and_flip_horizontal_velocity();
    void emit_fighter_effect(int code, float x, float y, int direction, int trailing);
    signed char classify_fighter_x_boundary();
    void publish_battle_layout_scalar(float value);
    void dispatch_indexed_event_member(unsigned int event);
    unsigned char resolve_stage_surface_landing_transition();
    unsigned char advance_frame_and_dispatch();
    int has_crossed_stage_surface_while_descending();
    void zero_velocity_acceleration();

    unsigned char reserved_004[0xe8];
    float x_ec;
    float y_f0;
    float velocity_x_f4;
    float velocity_y_f8;
    float acceleration_x_fc;
    float acceleration_y_100;
    signed char facing_104;
    unsigned char reserved_105[3];
    float field_108;
    float field_10c;
    unsigned char byte_110;
    unsigned char byte_111;
    unsigned char byte_112;
    unsigned char byte_113;
    unsigned char reserved_114[8];
    float scale_11c;
    float scale_120;
    unsigned char reserved_124[8];
    float angle_12c;
    unsigned char reserved_130[0xc];
    short action_13c;
    short sequence_13e;
    short frame_index_140;
    short frame_timer_142;
    int frame_counter_144;
    unsigned char reserved_148[0x28];
    ReimuPreludePeerView *peer_170;
    short word_174;
    unsigned char reserved_176[6];
    unsigned char byte_17c;
    unsigned char reserved_17d[3];
    int state_180;
    unsigned char byte_184;
    unsigned char reserved_185;
    short word_186;
    unsigned char reserved_188[0x2f6];
    unsigned char byte_47e;
    unsigned char byte_47f;
    unsigned char reserved_480[2];
    short word_482;
    unsigned char reserved_484[0xc];
    unsigned char byte_490;
    unsigned char reserved_491[0x17];
    short word_4a8;
    unsigned char reserved_4aa[2];
    short word_4ac;
    short word_4ae;
    unsigned char reserved_4b0[8];
    int field_4b8;
    unsigned char reserved_4bc[0x14];
    float scale_4d0;
    unsigned char reserved_4d4[0x84];
    short counter_558;
    signed char phase_55a;
    unsigned char reserved_55b[0xae];
    signed char byte_609;
    signed char byte_60a;
    signed char byte_60b;
    unsigned char reserved_60c[0xa0];
    float field_6ac;
    unsigned char reserved_6b0[4];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    unsigned char reserved_6cc[0x60];
    unsigned char byte_72c;
    unsigned char reserved_72d[3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    short word_738;
    unsigned char reserved_73a[2];
    float field_73c;
    float field_740;
    float field_744;
    unsigned char reserved_748[8];
    unsigned char byte_750;
    unsigned char byte_751;
    unsigned char reserved_752[0x4e];
    short word_7a0;
    short word_7a2;
    short word_7a4;
    unsigned char reserved_7a6[0x22];
    short timer_7c8;
    short count_7ca;
    short latch_7cc;
};

typedef char ReimuPrelude_x_offset[(offsetof(ReimuActionStatePreludeView, x_ec) == 0xec) ? 1 : -1];
typedef char ReimuPrelude_y_offset[(offsetof(ReimuActionStatePreludeView, y_f0) == 0xf0) ? 1 : -1];
typedef char ReimuPrelude_facing_offset[(offsetof(ReimuActionStatePreludeView, facing_104) == 0x104) ? 1 : -1];
typedef char ReimuPrelude_action_offset[(offsetof(ReimuActionStatePreludeView, action_13c) == 0x13c) ? 1 : -1];
typedef char ReimuPrelude_peer_offset[(offsetof(ReimuActionStatePreludeView, peer_170) == 0x170) ? 1 : -1];
typedef char ReimuPrelude_word174_offset[(offsetof(ReimuActionStatePreludeView, word_174) == 0x174) ? 1 : -1];
typedef char ReimuPrelude_state_offset[(offsetof(ReimuActionStatePreludeView, state_180) == 0x180) ? 1 : -1];
typedef char ReimuPrelude_gate_offset[(offsetof(ReimuActionStatePreludeView, word_186) == 0x186) ? 1 : -1];
typedef char ReimuHigh_offset[(offsetof(ReimuActionStatePreludeView, byte_60b) == 0x60b) ? 1 : -1];
typedef char ReimuVisual_offsets[(offsetof(ReimuActionStatePreludeView, byte_110) == 0x110 && offsetof(ReimuActionStatePreludeView, byte_113) == 0x113 && offsetof(ReimuActionStatePreludeView, scale_11c) == 0x11c && offsetof(ReimuActionStatePreludeView, scale_120) == 0x120 && offsetof(ReimuActionStatePreludeView, byte_184) == 0x184 && offsetof(ReimuActionStatePreludeView, byte_60a) == 0x60a) ? 1 : -1];
typedef char ReimuLateMid_offset[(offsetof(ReimuActionStatePreludeView, byte_609) == 0x609) ? 1 : -1];
typedef char ReimuCharge_offsets[(offsetof(ReimuActionStatePreludeView, byte_17c) == 0x17c) ? 1 : -1];
typedef char ReimuShot_offsets[(offsetof(ReimuActionStatePreludeView, field_6c4) == 0x6c4 && offsetof(ReimuActionStatePreludeView, field_744) == 0x744) ? 1 : -1];
typedef char ReimuProjectile_offsets[(offsetof(ReimuActionStatePreludeView, byte_47f) == 0x47f && offsetof(ReimuActionStatePreludeView, scale_4d0) == 0x4d0 && offsetof(ReimuActionStatePreludeView, counter_558) == 0x558 && offsetof(ReimuActionStatePreludeView, phase_55a) == 0x55a && offsetof(ReimuActionStatePreludeView, field_6c0) == 0x6c0 && offsetof(ReimuActionStatePreludeView, word_738) == 0x738 && offsetof(ReimuPreludePeerView, y_f0) == 0xf0) ? 1 : -1];
typedef char ReimuMid_input_offsets[(offsetof(ReimuActionStatePreludeView, field_6bc) == 0x6bc && offsetof(ReimuActionStatePreludeView, byte_750) == 0x750) ? 1 : -1];
typedef char ReimuPrelude_effect_offset[(offsetof(ReimuActionStatePreludeView, byte_751) == 0x751) ? 1 : -1];
typedef char ReimuPrelude_initial_words_offset[(offsetof(ReimuActionStatePreludeView, word_7a0) == 0x7a0 && offsetof(ReimuActionStatePreludeView, word_7a2) == 0x7a2) ? 1 : -1];
typedef char ReimuPrelude_counter_offsets[(offsetof(ReimuActionStatePreludeView, timer_7c8) == 0x7c8 && offsetof(ReimuActionStatePreludeView, count_7ca) == 0x7ca && offsetof(ReimuActionStatePreludeView, latch_7cc) == 0x7cc) ? 1 : -1];
typedef char ReimuPrelude_peer_offsets[(offsetof(ReimuPreludePeerView, word_174) == 0x174 && offsetof(ReimuPreludePeerView, word_48c) == 0x48c) ? 1 : -1];

typedef char ReimuStage_velocity_offsets[(offsetof(ReimuActionStatePreludeView, velocity_x_f4) == 0xf4 && offsetof(ReimuActionStatePreludeView, velocity_y_f8) == 0xf8) ? 1 : -1];
typedef char ReimuStage_acceleration_offsets[(offsetof(ReimuActionStatePreludeView, acceleration_x_fc) == 0xfc && offsetof(ReimuActionStatePreludeView, acceleration_y_100) == 0x100) ? 1 : -1];
typedef char ReimuStage_animation_offsets[(offsetof(ReimuActionStatePreludeView, sequence_13e) == 0x13e && offsetof(ReimuActionStatePreludeView, frame_index_140) == 0x140 && offsetof(ReimuActionStatePreludeView, frame_timer_142) == 0x142 && offsetof(ReimuActionStatePreludeView, frame_counter_144) == 0x144) ? 1 : -1];
typedef char ReimuStage_low_gate_offsets[(offsetof(ReimuActionStatePreludeView, byte_47e) == 0x47e && offsetof(ReimuActionStatePreludeView, field_6b8) == 0x6b8) ? 1 : -1];

typedef char ReimuStage_recovery_offsets[(offsetof(ReimuActionStatePreludeView, angle_12c) == 0x12c && offsetof(ReimuActionStatePreludeView, byte_490) == 0x490 && offsetof(ReimuActionStatePreludeView, field_6ac) == 0x6ac && offsetof(ReimuActionStatePreludeView, word_730) == 0x730 && offsetof(ReimuActionStatePreludeView, word_732) == 0x732 && offsetof(ReimuActionStatePreludeView, word_7a4) == 0x7a4) ? 1 : -1];

typedef char ReimuStage_movement_attack_offsets[(offsetof(ReimuPreludePeerView, x_ec) == 0xec && offsetof(ReimuActionStatePreludeView, field_108) == 0x108 && offsetof(ReimuActionStatePreludeView, field_10c) == 0x10c && offsetof(ReimuActionStatePreludeView, word_4a8) == 0x4a8 && offsetof(ReimuActionStatePreludeView, word_4ac) == 0x4ac && offsetof(ReimuActionStatePreludeView, field_6b4) == 0x6b4 && offsetof(ReimuActionStatePreludeView, byte_72c) == 0x72c) ? 1 : -1];

typedef char ReimuStage_late_low_offsets[(offsetof(ReimuActionStatePreludeView, word_482) == 0x482 && offsetof(ReimuActionStatePreludeView, word_4ae) == 0x4ae && offsetof(ReimuActionStatePreludeView, field_4b8) == 0x4b8 && offsetof(ReimuActionStatePreludeView, field_6c8) == 0x6c8 && offsetof(ReimuActionStatePreludeView, word_734) == 0x734 && offsetof(ReimuActionStatePreludeView, word_736) == 0x736 && offsetof(ReimuActionStatePreludeView, field_73c) == 0x73c && offsetof(ReimuActionStatePreludeView, field_740) == 0x740) ? 1 : -1];

// Both original bodies return an m32 table load in ST0. Float versus double
// source spelling remains unresolved; retain the existing ABI-compatible view.
double __cdecl lookup_orientation_sine_quantized_abs(float phase);
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
unsigned int __cdecl mt19937_next_u32();
int __stdcall selector_random_range(int lower, int upper);
float __cdecl atan2_degrees(float y, float x);
float __cdecl sqrt_float_value(float value);
int __cdecl selector_random_roll(int limit);

// The original reset receiver is the sprite subobject at fighter+4.
struct ReimuRecoverySpriteView {
    void reset_fighter_action_scratch();
};

float __fastcall reimu_stage_surface_height_at_x(ReimuActionStatePreludeView *fighter);

} // namespace th105
