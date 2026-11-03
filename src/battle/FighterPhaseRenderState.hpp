#pragma once

#include "battle/EffectSprite.hpp"
#include <list>
#include <stddef.h>

namespace th105 {

struct PhaseRenderEntry {
    CSpriteEx sprite;
    signed char blend_mode;
};

typedef char PhaseRenderEntry_sprite_size[(offsetof(PhaseRenderEntry, blend_mode) == 0xe8) ? 1 : -1];

struct FighterPhaseRenderState {
    std::list<PhaseRenderEntry> entries;
    signed char period_0c;
    unsigned char reserved_0d;
    signed short alpha_divisor_0e;
    unsigned color_mask_10;

    FighterPhaseRenderState();
    signed char set_period(signed char value);
    int set_color_mask(int value);
    void pop_front_if_any();
    void render_45aa00();
    void enqueue_45ad40(const CSpriteEx *source, signed char blend);
};

} // namespace th105
