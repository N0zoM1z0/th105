#pragma once

#include "engine/Sprite.hpp"

namespace th105 {

// Accessed Character prefix at +0x3D0; no instance of this view is constructed.
struct FighterSequenceEffectView {
    unsigned resource_00;
    CSprite sprite_04;
    unsigned char unknown_98[4];
    int reset_count_9c;
    int reset_count_a0;
    float reset_y_a4;
    unsigned char reset_alpha_a8;

    void reset_and_set_color();
};

typedef char SequenceEffectSpriteOffset[offsetof(FighterSequenceEffectView, sprite_04) == 4 ? 1 : -1];
typedef char SequenceEffectCountOffset[offsetof(FighterSequenceEffectView, reset_count_9c) == 0x9c ? 1 : -1];
typedef char SequenceEffectSecondCountOffset[offsetof(FighterSequenceEffectView, reset_count_a0) == 0xa0 ? 1 : -1];
typedef char SequenceEffectYOffset[offsetof(FighterSequenceEffectView, reset_y_a4) == 0xa4 ? 1 : -1];
typedef char SequenceEffectAlphaOffset[offsetof(FighterSequenceEffectView, reset_alpha_a8) == 0xa8 ? 1 : -1];

} // namespace th105
