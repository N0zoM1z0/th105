#pragma once

#include "EffectSprite.hpp"

#include <stddef.h>
#include <vector>

namespace th105 {

struct AnimationSequenceTree;

//45CD70 allocates108h, constructs this CSpriteEx member at zero, and writes
// the frame offsets/scales/angle below. Youmu entry code accesses x/y/facing.
// Composition reproduces the observed CSpriteEx RTTI and ordinary lifetime;
// it does not claim recovery of the original wrapper's source declaration.
struct AuxiliarySpriteRuntimeView {
    void render_auxiliary();

    CSpriteEx sprite_000;
    float x_e8;
    float y_ec;
    float frame_x_f0;
    float frame_y_f4;
    float field_f8;
    float field_fc;
    float angle_100;
    signed char facing_104;
};

struct AnimationAuxiliarySpriteOwnerView {
    unsigned char unknown_000[0x130];
    std::vector<unsigned int> *texture_handles_130;
    unsigned char unknown_134[0x20];
    AuxiliarySpriteRuntimeView *aux_renderer_154;
    unsigned char unknown_158[8];
    AnimationSequenceTree *sequence_tree_160;

    void replace_auxiliary_sprite(short resource_id);
};

typedef char AuxiliarySpriteRuntimeView_size[
    sizeof(AuxiliarySpriteRuntimeView) == 0x108 ? 1 : -1];
typedef char AuxiliarySpriteRuntimeView_x_offset[
    offsetof(AuxiliarySpriteRuntimeView, x_e8) == 0xe8 ? 1 : -1];
typedef char AuxiliarySpriteRuntimeView_frame_x_offset[
    offsetof(AuxiliarySpriteRuntimeView, frame_x_f0) == 0xf0 ? 1 : -1];
typedef char AuxiliarySpriteRuntimeView_facing_offset[
    offsetof(AuxiliarySpriteRuntimeView, facing_104) == 0x104 ? 1 : -1];
typedef char AnimationAuxiliarySpriteOwnerView_textures_offset[
    offsetof(AnimationAuxiliarySpriteOwnerView, texture_handles_130) == 0x130 ? 1 : -1];
typedef char AnimationAuxiliarySpriteOwnerView_aux_offset[
    offsetof(AnimationAuxiliarySpriteOwnerView, aux_renderer_154) == 0x154 ? 1 : -1];
typedef char AnimationAuxiliarySpriteOwnerView_sequences_offset[
    offsetof(AnimationAuxiliarySpriteOwnerView, sequence_tree_160) == 0x160 ? 1 : -1];

} // namespace th105
