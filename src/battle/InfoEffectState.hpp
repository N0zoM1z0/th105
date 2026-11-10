#pragma once

#include <stddef.h>

namespace th105 {

// Nonconstructing update view of the RTTI-owned InfoEffectObject storage.
// Unused sprite and animation members remain opaque; accessed fields are typed.
struct InfoEffectState {
    unsigned char sprite_prefix_000[0xec];
    float x_0ec;
    float y_0f0;
    unsigned char unknown_0f4[0x1c];
    unsigned char color_bgr_110[3];
    unsigned char alpha_113;
    unsigned char unknown_114[8];
    float scale_x_11c;
    float scale_y_120;
    unsigned char unknown_124[0x18];
    short action_13c;
    unsigned char unknown_13e[4];
    short frame_142;
    int time_144;
    unsigned char unknown_148[0x10];
    unsigned state_158;
    unsigned char unknown_15c[0x18];
    float fade_latch_174;
};

typedef char InfoEffectState_size[sizeof(InfoEffectState) == 0x178 ? 1 : -1];
typedef char InfoEffectState_x[offsetof(InfoEffectState, x_0ec) == 0xec ? 1 : -1];
typedef char InfoEffectState_alpha[offsetof(InfoEffectState, alpha_113) == 0x113 ? 1 : -1];
typedef char InfoEffectState_scale[offsetof(InfoEffectState, scale_x_11c) == 0x11c ? 1 : -1];
typedef char InfoEffectState_action[offsetof(InfoEffectState, action_13c) == 0x13c ? 1 : -1];
typedef char InfoEffectState_frame[offsetof(InfoEffectState, frame_142) == 0x142 ? 1 : -1];
typedef char InfoEffectState_time[offsetof(InfoEffectState, time_144) == 0x144 ? 1 : -1];
typedef char InfoEffectState_live[offsetof(InfoEffectState, state_158) == 0x158 ? 1 : -1];
typedef char InfoEffectState_latch[offsetof(InfoEffectState, fade_latch_174) == 0x174 ? 1 : -1];

} // namespace th105
