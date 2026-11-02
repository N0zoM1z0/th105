#pragma once
#include "EffectSprite.hpp"

namespace th105 {



struct FighterCutinResource {
    unsigned handle_00;
    CSprite sprite_04;
    int selector_98;
    int state_9c;

    void load_for_character(int character_key, int selector);
};

struct FighterFaceResource {
    unsigned handle_00;
    CSprite sprite_04;
};

typedef char CheckFighterCutinResourceSize[
    sizeof(FighterCutinResource) == 0xa0 ? 1 : -1];
typedef char CheckCSpriteSize[
    sizeof(CSprite) == 0x94 ? 1 : -1];
typedef char CheckFighterFaceResourceSize[
    sizeof(FighterFaceResource) == 0x98 ? 1 : -1];

} // namespace th105
