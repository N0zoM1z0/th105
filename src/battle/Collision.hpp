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
};

struct CollisionContext {
    unsigned char unknown_00[0x1c];
    int extent_1c;
    int extent_20;
    int extent_24;
    int extent_28;

    void reset_collision_extents();
    void accumulate_collision_extents(const int *first, const int *second);
    bool try_frame_flag_pair_outcome(
        AttackCandidate *candidate,
        Fighter *fighter);
};

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
