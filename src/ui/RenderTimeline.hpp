#pragma once

#include "battle/EffectSprite.hpp"

#include <deque>
#include <list>
#include <stddef.h>

namespace th105 {

struct RenderTimelineEntry {
    unsigned char reserved_00[0x14];
    std::deque<CSpriteEx> sprites_14;
    float translate_x_28;
    float translate_y_2c;
    float uv_width_30;
    float uv_height_34;
    float scale_x_38;
    float scale_y_3c;
    float rotation_z_40;
    unsigned char reserved_44[0x10];
    unsigned char alpha_54;
    unsigned char reserved_55;
    unsigned char color_56;
    unsigned char reserved_57;
    unsigned char color_58;
    unsigned char reserved_59;
    unsigned char color_5a;
    unsigned char reserved_5b[0x0d];
    int blend_mode_68;
    int sampler_one_6c;
    int sampler_two_70;
    unsigned frame_74;

    void render();
};

struct RenderTimelineList {
    unsigned char reserved_00[0x58];
    std::list<RenderTimelineEntry> entries_58;

    void render();
};

typedef char RenderTimelineEntry_deque_offset[
    offsetof(RenderTimelineEntry, sprites_14) == 0x14 ? 1 : -1];
typedef char RenderTimelineEntry_translate_offset[
    offsetof(RenderTimelineEntry, translate_x_28) == 0x28 ? 1 : -1];
typedef char RenderTimelineEntry_alpha_offset[
    offsetof(RenderTimelineEntry, alpha_54) == 0x54 ? 1 : -1];
typedef char RenderTimelineEntry_blend_offset[
    offsetof(RenderTimelineEntry, blend_mode_68) == 0x68 ? 1 : -1];
typedef char RenderTimelineEntry_frame_offset[
    offsetof(RenderTimelineEntry, frame_74) == 0x74 ? 1 : -1];
typedef char RenderTimelineList_entries_offset[
    offsetof(RenderTimelineList, entries_58) == 0x58 ? 1 : -1];

} // namespace th105
