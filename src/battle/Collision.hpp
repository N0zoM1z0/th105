#pragma once

namespace th105 {

struct CollisionExtents {
    unsigned char unknown_00[0x1c];
    int extent_1c;
    int extent_20;
    int extent_24;
    int extent_28;

    void reset_collision_extents();
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
