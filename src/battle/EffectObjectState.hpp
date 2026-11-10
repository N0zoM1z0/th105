#pragma once
#include <stddef.h>
namespace th105 {
// Nonconstructing context view. The complete context's nominal type is unknown.
struct EffectObjectContextState {
    unsigned char unknown_000[0xec];
    float x_0ec, y_0f0;
    unsigned char unknown_0f4[0x38];
    float angle_12c;
    unsigned char unknown_130[0xc];
    short action_13c, sequence_13e;
    unsigned char unknown_140[0x362];
    short value_4a2;
};
// Observed state shared by EffectObject entry and update. Never instantiated.
struct EffectObjectState {
    unsigned char sprite_prefix_000[0xec];
    float x_0ec, y_0f0, velocity_x_0f4, velocity_y_0f8;
    unsigned char unknown_0fc[8];
    signed char facing_104;
    unsigned char unknown_105[0xb];
    unsigned char blue_110, green_111, red_112, alpha_113;
    unsigned char unknown_114[8];
    float scale_x_11c, scale_y_120, angle_x_124, angle_y_128, angle_z_12c;
    unsigned char unknown_130[0xc];
    short action_13c, sequence_13e, frame_140, frame_142;
    int time_144;
    unsigned char unknown_148[0x10];
    unsigned state_158;
    unsigned char unknown_15c[8];
    EffectObjectContextState *context_164;
    unsigned char unknown_168[8];
    float state_170, state_174;
};
typedef char EffectState_size[sizeof(EffectObjectState)==0x178?1:-1];
typedef char EffectState_x[offsetof(EffectObjectState,x_0ec)==0xec?1:-1];
typedef char EffectState_facing[offsetof(EffectObjectState,facing_104)==0x104?1:-1];
typedef char EffectState_alpha[offsetof(EffectObjectState,alpha_113)==0x113?1:-1];
typedef char EffectState_scale[offsetof(EffectObjectState,scale_x_11c)==0x11c?1:-1];
typedef char EffectState_action[offsetof(EffectObjectState,action_13c)==0x13c?1:-1];
typedef char EffectState_time[offsetof(EffectObjectState,time_144)==0x144?1:-1];
typedef char EffectState_lifecycle[offsetof(EffectObjectState,state_158)==0x158?1:-1];
typedef char EffectState_context[offsetof(EffectObjectState,context_164)==0x164?1:-1];
typedef char EffectState_tail[offsetof(EffectObjectState,state_174)==0x174?1:-1];
typedef char EffectContext_action[offsetof(EffectObjectContextState,action_13c)==0x13c?1:-1];
typedef char EffectContext_value[offsetof(EffectObjectContextState,value_4a2)==0x4a2?1:-1];
} // namespace th105
