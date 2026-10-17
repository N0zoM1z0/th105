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
    unsigned char reserved_0f0[0x84];
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
    bool run_checked_prelude();
    // True completes the entry/low path; false hands action>300 to later source.
    bool run_checked_low_dispatch();
    void update_common_action_state();
    // True handles action0..10; false leaves other actions to later phases.
    bool try_run_checked_low_action();
    // True handles actions71..78; this is another staging phase.
    bool try_run_checked_recovery_action();
    // Actions88/89/145 and197..204, without an original boundary claim.
    bool try_run_checked_movement_attack_action();
    // Remaining low-table actions and direct action300.
    bool try_run_checked_late_low_action();
    void adjust_counter_482(short amount, int floor_value);
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
    unsigned char reserved_110[0x1c];
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
    unsigned char reserved_176[0xa];
    int state_180;
    unsigned char reserved_184[2];
    short word_186;
    unsigned char reserved_188[0x2f6];
    unsigned char byte_47e;
    unsigned char reserved_47f[3];
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
    unsigned char reserved_4bc[0x1f0];
    float field_6ac;
    unsigned char reserved_6b0[4];
    int field_6b4;
    int field_6b8;
    unsigned char reserved_6bc[0xc];
    int field_6c8;
    unsigned char reserved_6cc[0x60];
    unsigned char byte_72c;
    unsigned char reserved_72d[3];
    short word_730;
    short word_732;
    short word_734;
    short word_736;
    unsigned char reserved_738[4];
    float field_73c;
    float field_740;
    unsigned char reserved_744[0xd];
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

// The original reset receiver is the sprite subobject at fighter+4.
struct ReimuRecoverySpriteView {
    void reset_fighter_action_scratch();
};

float __fastcall reimu_stage_surface_height_at_x(ReimuActionStatePreludeView *fighter);

} // namespace th105
