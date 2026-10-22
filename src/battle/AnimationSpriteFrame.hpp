#pragma once

#include "EffectSprite.hpp"

#include <stddef.h>
#include <vector>

namespace th105 {

struct AnimationSpriteTransform {
    unsigned char unknown_00[0x08];
    float scale_x_08;
    float scale_y_0c;
    float scale_z_10;
    float angle_x_14;
    float angle_y_18;
    float angle_z_1c;
};

// Common prefix of the effect and attack animation frame records.
struct AnimationSpriteFrame {
    unsigned char unknown_00[0x04];
    short pivot_x_04;
    short pivot_y_06;
    short duration_08;
    short texture_index_0a;
    short texture_x_0c;
    short texture_y_0e;
    short texture_width_10;
    short texture_height_12;
    signed char render_mode_14;
    unsigned char unknown_15[0x03];
    AnimationSpriteTransform *transform_18;
};

// Nonconstructing ABI view: the first word is the owner's primary vptr.
struct AnimationSpriteFrameView {
    void apply_current_frame();

    void *primary_vptr_000;
    CEffectSprite sprite_004;
    std::vector<unsigned> *texture_handles_130;
    unsigned char unknown_134[0x1c];
    AnimationSpriteFrame *frame_150;
};

typedef char AnimationSpriteTransform_size_must_be_0x20[
    sizeof(AnimationSpriteTransform) == 0x20 ? 1 : -1];
typedef char AnimationSpriteFrame_prefix_must_be_0x1c[
    sizeof(AnimationSpriteFrame) == 0x1c ? 1 : -1];
typedef char AnimationSpriteFrame_mode_offset_must_be_0x14[
    offsetof(AnimationSpriteFrame, render_mode_14) == 0x14 ? 1 : -1];
typedef char AnimationSpriteFrame_transform_offset_must_be_0x18[
    offsetof(AnimationSpriteFrame, transform_18) == 0x18 ? 1 : -1];
typedef char AnimationSpriteFrameView_sprite_offset_must_be_0x04[
    offsetof(AnimationSpriteFrameView, sprite_004) == 0x04 ? 1 : -1];
typedef char AnimationSpriteFrameView_handles_offset_must_be_0x130[
    offsetof(AnimationSpriteFrameView, texture_handles_130) == 0x130 ? 1 : -1];
typedef char AnimationSpriteFrameView_frame_offset_must_be_0x150[
    offsetof(AnimationSpriteFrameView, frame_150) == 0x150 ? 1 : -1];

} // namespace th105
