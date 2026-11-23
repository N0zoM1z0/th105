#pragma once

#include <stddef.h>

namespace th105 {
// Pointer-only ABI views, not complete allocations.
class SakuyaObjectUpdateView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual int select_sequence(short);
 virtual void slot10();virtual unsigned char next_sequence_block();
 virtual void slot18();virtual int set_sequence_frame(short);
 virtual unsigned char next_sequence_frame();virtual void slot24();virtual void update_action_state();
 unsigned char emit_repeated(int,int,int);
 void replace_secondary(int,float,int,int,int);
 void release_secondary();
 void set_secondary_alpha(unsigned char);
 void dispatch_character_wave_handle(unsigned);
 float stage_surface_height();
 void turn_heading(float,float,float);
 void *spawn_parented(int,float,float,int,int,const unsigned *,int);
 void *spawn_unparented(int,float,float,int,int,const unsigned *,int);
 int spawn_owned(int,float,float,int,int,const unsigned *,int);
 void update_ping_pong_motion();

 unsigned char unknown_004[0xe8];
 float x_ec;
 float y_f0;
 float velocity_x_f4;
 float velocity_y_f8;
 unsigned char unknown_0fc[0x14];
 unsigned char channel_110;
 unsigned char channel_111;
 unsigned char unknown_112;
 unsigned char alpha_113;
 unsigned char unknown_114[0x8];
 float scale_x_11c;
 float scale_y_120;
 float field_124;
 float field_128;
 float angle_12c;
 unsigned char unknown_130[0xc];
 short action_id_13c;
 short sequence_id_13e;
 short frame_index_140;
 short frame_counter_142;
 int time_counter_144;
 unsigned char unknown_148[0x38];
 int phase_state_180;
 signed char phase_index_184;
 unsigned char unknown_185[0x1ab];
 int lifetime_330;
 unsigned char unknown_334[0xc];
 float *parameters_340;
 short field_344;
 unsigned char unknown_346[0x2];
 SakuyaObjectUpdateView *owner_348;
 SakuyaObjectUpdateView *parent_object_34c;
 unsigned char unknown_350[0x14];
 short field_364;
 short field_366;
 short field_368;
 short field_36a;
 short field_36c;
 unsigned char unknown_36e[0x2];
 float field_370;
 float field_374;
};

typedef char CheckSakuyaUpdate_x_ec[
    offsetof(SakuyaObjectUpdateView, x_ec) == 0xec ? 1 : -1];
typedef char CheckSakuyaUpdate_y_f0[
    offsetof(SakuyaObjectUpdateView, y_f0) == 0xf0 ? 1 : -1];
typedef char CheckSakuyaUpdate_velocity_x_f4[
    offsetof(SakuyaObjectUpdateView, velocity_x_f4) == 0xf4 ? 1 : -1];
typedef char CheckSakuyaUpdate_velocity_y_f8[
    offsetof(SakuyaObjectUpdateView, velocity_y_f8) == 0xf8 ? 1 : -1];
typedef char CheckSakuyaUpdate_channel_110[
    offsetof(SakuyaObjectUpdateView, channel_110) == 0x110 ? 1 : -1];
typedef char CheckSakuyaUpdate_channel_111[
    offsetof(SakuyaObjectUpdateView, channel_111) == 0x111 ? 1 : -1];
typedef char CheckSakuyaUpdate_alpha_113[
    offsetof(SakuyaObjectUpdateView, alpha_113) == 0x113 ? 1 : -1];
typedef char CheckSakuyaUpdate_scale_x_11c[
    offsetof(SakuyaObjectUpdateView, scale_x_11c) == 0x11c ? 1 : -1];
typedef char CheckSakuyaUpdate_scale_y_120[
    offsetof(SakuyaObjectUpdateView, scale_y_120) == 0x120 ? 1 : -1];
typedef char CheckSakuyaUpdate_field_124[
    offsetof(SakuyaObjectUpdateView, field_124) == 0x124 ? 1 : -1];
typedef char CheckSakuyaUpdate_field_128[
    offsetof(SakuyaObjectUpdateView, field_128) == 0x128 ? 1 : -1];
typedef char CheckSakuyaUpdate_angle_12c[
    offsetof(SakuyaObjectUpdateView, angle_12c) == 0x12c ? 1 : -1];
typedef char CheckSakuyaUpdate_action_id_13c[
    offsetof(SakuyaObjectUpdateView, action_id_13c) == 0x13c ? 1 : -1];
typedef char CheckSakuyaUpdate_sequence_id_13e[
    offsetof(SakuyaObjectUpdateView, sequence_id_13e) == 0x13e ? 1 : -1];
typedef char CheckSakuyaUpdate_frame_index_140[
    offsetof(SakuyaObjectUpdateView, frame_index_140) == 0x140 ? 1 : -1];
typedef char CheckSakuyaUpdate_frame_counter_142[
    offsetof(SakuyaObjectUpdateView, frame_counter_142) == 0x142 ? 1 : -1];
typedef char CheckSakuyaUpdate_time_counter_144[
    offsetof(SakuyaObjectUpdateView, time_counter_144) == 0x144 ? 1 : -1];
typedef char CheckSakuyaUpdate_phase_state_180[
    offsetof(SakuyaObjectUpdateView, phase_state_180) == 0x180 ? 1 : -1];
typedef char CheckSakuyaUpdate_phase_index_184[
    offsetof(SakuyaObjectUpdateView, phase_index_184) == 0x184 ? 1 : -1];
typedef char CheckSakuyaUpdate_lifetime_330[
    offsetof(SakuyaObjectUpdateView, lifetime_330) == 0x330 ? 1 : -1];
typedef char CheckSakuyaUpdate_parameters_340[
    offsetof(SakuyaObjectUpdateView, parameters_340) == 0x340 ? 1 : -1];
typedef char CheckSakuyaUpdate_field_344[
    offsetof(SakuyaObjectUpdateView, field_344) == 0x344 ? 1 : -1];
typedef char CheckSakuyaUpdate_owner_348[
    offsetof(SakuyaObjectUpdateView, owner_348) == 0x348 ? 1 : -1];
typedef char CheckSakuyaUpdate_parent_object_34c[
    offsetof(SakuyaObjectUpdateView, parent_object_34c) == 0x34c ? 1 : -1];
typedef char CheckSakuyaUpdate_field_364[
    offsetof(SakuyaObjectUpdateView, field_364) == 0x364 ? 1 : -1];
typedef char CheckSakuyaUpdate_field_366[
    offsetof(SakuyaObjectUpdateView, field_366) == 0x366 ? 1 : -1];
typedef char CheckSakuyaUpdate_field_368[
    offsetof(SakuyaObjectUpdateView, field_368) == 0x368 ? 1 : -1];
typedef char CheckSakuyaUpdate_field_36a[
    offsetof(SakuyaObjectUpdateView, field_36a) == 0x36a ? 1 : -1];
typedef char CheckSakuyaUpdate_field_36c[
    offsetof(SakuyaObjectUpdateView, field_36c) == 0x36c ? 1 : -1];
typedef char CheckSakuyaUpdate_field_370[
    offsetof(SakuyaObjectUpdateView, field_370) == 0x370 ? 1 : -1];
typedef char CheckSakuyaUpdate_field_374[
    offsetof(SakuyaObjectUpdateView, field_374) == 0x374 ? 1 : -1];

int __cdecl selector_random_roll(int);
float __cdecl atan2_degrees(float,float);
float __cdecl square_float_value(float);
float __cdecl sqrt_float_value(float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
extern float sakuya_update_left, sakuya_update_top, sakuya_update_right, sakuya_update_bottom;
extern int g_match_identifier;
}
