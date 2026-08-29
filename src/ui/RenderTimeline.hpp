#pragma once

#include "battle/EffectSprite.hpp"

#include <deque>
#include <list>
#include <stddef.h>

namespace th105 {

struct RenderTimelineEntry {
    std::deque<CSpriteEx> sprites_00;
    std::deque<CSpriteEx> sprites_14;
    float translate_x_28;
    float translate_y_2c;
    float uv_width_30;
    float uv_height_34;
    float scale_x_38;
    float scale_y_3c;
    float rotation_z_40;
    float translate_secondary_x_44;
    float translate_secondary_y_48;
    float uv_secondary_width_4c;
    float uv_secondary_height_50;
    unsigned char alpha_54;
    unsigned char flag_55;
    unsigned char colors_56[6];
    float scale_secondary_x_5c;
    float scale_secondary_y_60;
    float rotation_secondary_z_64;
    int blend_mode_68;
    int sampler_one_6c;
    int sampler_two_70;
    unsigned frame_74;
    int duration_78;

    RenderTimelineEntry();
    void render();
};

struct RenderTimelineList {
    unsigned char reserved_00[0x58];
    std::list<RenderTimelineEntry> entries_58;

    void render();
};

typedef char RenderTimelineEntry_deque_offset[
    offsetof(RenderTimelineEntry, sprites_14) == 0x14 ? 1 : -1];
typedef char RenderTimelineEntry_size[
    sizeof(RenderTimelineEntry) == 0x7c ? 1 : -1];
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
