#pragma once
#include "EffectSprite.hpp"

// Nonpolymorphic0x12C animation state owner. Its0xE8 sprite member has its own
// CEffectSprite vptr; the following state is not part of that RTTI class.
// The nominal original owner name remains unknown. Constructor421FF0 resets
// the outer state only after the sprite member has completed construction.
struct AnimationSpriteState {
    AnimationSpriteState();
    CEffectSprite sprite_000;
    float object_x_0e8;
    float object_y_0ec;
    unsigned char unknown_0f0[0x10];
    signed char object_facing_100;
    unsigned char unknown_101[0x03];
    float reset_zero_104;
    float reset_zero_108;
    unsigned int color_10c;
    int reset_zero_110;
    unsigned char unknown_114[0x04];
    float reset_one_118;
    float reset_one_11c;
    float reset_zero_120;
    float reset_zero_124;
    float reset_zero_128;
};
typedef char AnimationSpriteState_size[sizeof(AnimationSpriteState) == 0x12c ? 1 : -1];
typedef char AnimationSpriteState_position_offset[offsetof(AnimationSpriteState, object_x_0e8) == 0xe8 ? 1 : -1];
typedef char AnimationSpriteState_facing_offset[offsetof(AnimationSpriteState, object_facing_100) == 0x100 ? 1 : -1];
