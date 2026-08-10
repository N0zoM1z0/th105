#pragma once

namespace th105 {

struct AttackCandidateFrame {
    unsigned char unknown_00[0x50];
    unsigned flags_50;
};

struct FighterFrame {
    unsigned char unknown_00[0x4c];
    unsigned flags_4c;
};

struct AttackCandidate {
    unsigned char unknown_000[0x180];
    unsigned result_180;
    unsigned char unknown_184[0x20];
    AttackCandidateFrame *frame_1a4;
};

struct Fighter {
    unsigned char unknown_000[0x158];
    FighterFrame *frame_158;
    unsigned char unknown_15c[0x24];
    unsigned result_180;
    unsigned char unknown_184[0x2fe];
    short counter_482;
    short unknown_484;
    short floor_486;
    unsigned char unknown_488[0x30];
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
    bool try_frame_flag_pair_outcome(
        AttackCandidate *candidate,
        Fighter *fighter);
    int test_descriptor_point_inside(
        const struct CollisionAabb *aabb,
        const struct ShapeWords *descriptor,
        int x,
        int y);
};

void __fastcall reset_fighter_fields_6bc_728(CollisionContext *context);
void __fastcall reset_fighter_fields_6b4_728(CollisionContext *context);

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
