#pragma once
#include <stddef.h>
namespace th105 {
// Observed WeatherEffectObject state, shared by entry and update.
// This nonconstructing view is not the complete allocatable owner.
struct WeatherEffectState {
    unsigned char sprite_prefix_000[0xec];
    float x_0ec, y_0f0, velocity_x_0f4, velocity_y_0f8;
    unsigned char unknown_0fc[8];
    signed char facing_104;
    unsigned char unknown_105[0xe];
    unsigned char alpha_113;
    unsigned char unknown_114[8];
    float scale_x_11c, scale_y_120;
    unsigned char unknown_124[8];
    float angle_12c;
    unsigned char unknown_130[0xc];
    short action_13c;
    unsigned char unknown_13e[2];
    short frame_140, frame_142;
    int time_144;
    unsigned char unknown_148[0x10];
    unsigned state_158;
    unsigned char unknown_15c[0x14];
    int retiring_170, event_174;
    float drift_178, state_17c;
};
typedef char WeatherState_x_0ec[offsetof(WeatherEffectState,x_0ec)==0xec?1:-1];
typedef char WeatherState_y_0f0[offsetof(WeatherEffectState,y_0f0)==0xf0?1:-1];
typedef char WeatherState_velocity_x_0f4[offsetof(WeatherEffectState,velocity_x_0f4)==0xf4?1:-1];
typedef char WeatherState_velocity_y_0f8[offsetof(WeatherEffectState,velocity_y_0f8)==0xf8?1:-1];
typedef char WeatherState_facing_104[offsetof(WeatherEffectState,facing_104)==0x104?1:-1];
typedef char WeatherState_alpha_113[offsetof(WeatherEffectState,alpha_113)==0x113?1:-1];
typedef char WeatherState_scale_x_11c[offsetof(WeatherEffectState,scale_x_11c)==0x11c?1:-1];
typedef char WeatherState_scale_y_120[offsetof(WeatherEffectState,scale_y_120)==0x120?1:-1];
typedef char WeatherState_angle_12c[offsetof(WeatherEffectState,angle_12c)==0x12c?1:-1];
typedef char WeatherState_action_13c[offsetof(WeatherEffectState,action_13c)==0x13c?1:-1];
typedef char WeatherState_frame_140[offsetof(WeatherEffectState,frame_140)==0x140?1:-1];
typedef char WeatherState_frame_142[offsetof(WeatherEffectState,frame_142)==0x142?1:-1];
typedef char WeatherState_time_144[offsetof(WeatherEffectState,time_144)==0x144?1:-1];
typedef char WeatherState_state_158[offsetof(WeatherEffectState,state_158)==0x158?1:-1];
typedef char WeatherState_retiring_170[offsetof(WeatherEffectState,retiring_170)==0x170?1:-1];
typedef char WeatherState_event_174[offsetof(WeatherEffectState,event_174)==0x174?1:-1];
typedef char WeatherState_drift_178[offsetof(WeatherEffectState,drift_178)==0x178?1:-1];
typedef char WeatherState_state_17c[offsetof(WeatherEffectState,state_17c)==0x17c?1:-1];
typedef char WeatherState_size[sizeof(WeatherEffectState)==0x180?1:-1];
} // namespace th105
