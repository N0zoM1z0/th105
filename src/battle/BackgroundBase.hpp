#pragma once

#include "battle/EffectSprite.hpp"

#include <stddef.h>
#include <vector>

namespace th105 {

// Current RTTI/vtable and exact lifetime code close this as the common
// polymorphic background/render entry.  The base vtable owns the scalar
// deleting destructor followed by five pure-virtual phase/render slots.
struct BackgroundBase {
    virtual ~BackgroundBase();
    virtual void slot_04() = 0;
    virtual void slot_08() = 0;
    virtual void slot_0c() = 0;
    virtual void slot_10() = 0;
    virtual void render_sprite(CSpriteEx *sprite) = 0;

    std::vector<unsigned> handles_a_04;
    std::vector<CSpriteEx> sprites_a_14;
    std::vector<unsigned> handles_b_24;
    std::vector<CSpriteEx> sprites_b_34;
    float value_44;
    float value_48;
    float value_4c;
    float value_50;
    float value_54;
    float value_58;

    BackgroundBase();
    void set_transition_4654f0(int state, float value);
};

typedef char BackgroundBase_handles_a_offset_must_be_0x04[
    offsetof(BackgroundBase, handles_a_04) == 0x04 ? 1 : -1];
typedef char BackgroundBase_sprites_a_offset_must_be_0x14[
    offsetof(BackgroundBase, sprites_a_14) == 0x14 ? 1 : -1];
typedef char BackgroundBase_handles_b_offset_must_be_0x24[
    offsetof(BackgroundBase, handles_b_24) == 0x24 ? 1 : -1];
typedef char BackgroundBase_sprites_b_offset_must_be_0x34[
    offsetof(BackgroundBase, sprites_b_34) == 0x34 ? 1 : -1];
typedef char BackgroundBase_value_44_offset_must_be_0x44[
    offsetof(BackgroundBase, value_44) == 0x44 ? 1 : -1];
typedef char BackgroundBase_size_must_be_0x5c[
    sizeof(BackgroundBase) == 0x5c ? 1 : -1];

} // namespace th105
