#pragma once
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
 unsigned char advance_frame();
 unsigned char advance_six(int);
 float stage_surface_height();
 void turn_heading(float,float,float);
 void *spawn_parented(int,float,float,int,int,const unsigned *,int);
 void *spawn_unparented(int,float,float,int,int,const unsigned *,int);
 int spawn_owned(int,float,float,int,int,const unsigned *,int);
 void update_ping_pong_motion();
};
class SakuyaUpdateMotionView { public: void set_components(float,float); };
int __cdecl selector_random_roll(int);
float __cdecl atan2_degrees(float,float);
float __cdecl square_float_value(float);
float __cdecl sqrt_float_value(float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
extern float sakuya_update_left, sakuya_update_top, sakuya_update_right, sakuya_update_bottom;
extern int g_match_identifier;
}
