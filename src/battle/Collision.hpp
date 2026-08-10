#pragma once

namespace th105 {

struct AttackCandidateFrame {
    unsigned char unknown_00[0x1c];
    short quantity_1c;
    unsigned char unknown_1e[0x02];
    short quantity_20;
    unsigned char unknown_22[0x2e];
    unsigned flags_50;
};

struct FighterFrame {
    unsigned char unknown_00[0x4c];
    unsigned flags_4c;
};

struct AttackCandidate {
    unsigned char unknown_000[0x180];
    unsigned result_180;
    unsigned char result_slot_184;
    unsigned char unknown_185[0x1b];
    unsigned char source_1a0;
    unsigned char unknown_1a1[3];
    AttackCandidateFrame *frame_1a4;

    float calculate_base_hit_quantity();
    int calculate_descriptor_scaled_quantity_1c();
    int calculate_descriptor_scaled_quantity_20();
};

struct ByteStrideRange {
    unsigned char unknown_00[0x04];
    unsigned char *begin_04;
    unsigned char *end_08;

    int count_0x88_byte_stride_entries();
};

struct Fighter {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_f4[0x10];
    unsigned char facing_104;
    unsigned char unknown_105[0x37];
    short state_13c;
    unsigned char unknown_13e[0x1a];
    FighterFrame *frame_158;
    unsigned char unknown_15c[0x18];
    short value_174;
    unsigned char unknown_176[0x0a];
    unsigned result_180;
    unsigned char unknown_184[0x1b0];
    signed char player_index_334;
    unsigned char unknown_335[0x147];
    short value_47c;
    unsigned char unknown_47e[0x04];
    short counter_482;
    short unknown_484;
    short floor_486;
    unsigned char unknown_488[0x09];
    unsigned char flag_491;
    unsigned char unknown_492[0x02];
    float scalar_494;
    short value_498;
    short value_49a;
    short value_49c;
    short field_49e;
    short value_4a0;
    short value_4a2;
    unsigned char unknown_4a4[0x02];
    short field_4a6;
    unsigned char unknown_4a8[0x06];
    short field_4ae;
    unsigned char unknown_4b0[0x08];
    int state_4b8;
    unsigned char unknown_4bc[0x1f8];
    int field_6b4;
    int field_6b8;
    int field_6bc;
    int field_6c0;
    int field_6c4;
    int field_6c8;
    int field_6cc;
    int field_6d0;
    int field_6d4;
    int field_6d8;
    int field_6dc;
    int field_6e0;
    int field_6e4;
    int field_6e8;
    int field_6ec;
    int field_6f0;
    int field_6f4;
    int field_6f8;
    int field_6fc;
    int field_700;
    int field_704;
    int field_708;
    unsigned char unknown_70c[0x18];
    int field_724;
    int field_728;

    void adjust_counter_482(short amount, int floor_value);
};

struct CollisionContext {
    unsigned char unknown_00[0x0c];
    Fighter *fighters[2];
    unsigned char unknown_14[0x08];
    int extent_1c;
    int extent_20;
    int extent_24;
    int extent_28;

    void reset_collision_extents();
    void accumulate_collision_extents(const int *first, const int *second);
    void accumulate_descriptor_extents(
        const struct CollisionAabb *first,
        const struct ShapeWords *descriptor,
        const struct CollisionAabb *second);
    void accumulate_descriptor_pair_extents(
        const struct CollisionAabb *first,
        const struct ShapeWords *first_descriptor,
        const struct CollisionAabb *second,
        const struct ShapeWords *second_descriptor);
    bool try_frame_flag_pair_outcome(
        AttackCandidate *candidate,
        Fighter *fighter);
    bool try_candidate_flag_outcome(
        AttackCandidate *candidate,
        Fighter *fighter);
    void emit_effect_at_collision_center(int effect_code, int direction);
    int test_descriptor_point_inside(
        const struct CollisionAabb *aabb,
        const struct ShapeWords *descriptor,
        int x,
        int y);
};

struct EffectSink {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void unknown_08();
    virtual void emit_effect(
        int effect_code,
        float x,
        float y,
        int direction,
        int one,
        int zero);
};

void __fastcall reset_fighter_fields_6bc_728(CollisionContext *context);
void __fastcall reset_fighter_fields_6b4_728(CollisionContext *context);
int __fastcall is_state_13c_in_32_95(Fighter *fighter);
int __fastcall is_positive_y_and_state_window(Fighter *fighter);
float __fastcall stage_surface_height_at_x(Fighter *fighter);
int __fastcall is_y_at_or_below_stage_surface(Fighter *fighter);

struct ActorPosition {
    unsigned char unknown_00[0xec];
    float x;
    float y;
    unsigned char unknown_f4[0x10];
    unsigned char facing;
};

struct LocalAabb {
    int left;
    int top;
    int right;
    int bottom;
};

struct CollisionAabb {
    int left;
    int top;
    int right;
    int bottom;
};

struct ShapeWords {
    int x0;
    int y0;
    int x1;
    int y1;
};

struct WorldAabb {
    float left;
    float top;
    float right;
    float bottom;
};

void __stdcall transform_local_aabb_to_world(
    const ActorPosition *actor,
    const LocalAabb *local,
    WorldAabb *world);

} // namespace th105
