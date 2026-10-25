#pragma once
namespace th105 {
extern int g_match_identifier;
extern float g_update_left,g_update_right,g_update_top;
// Pointer-only primary call view. Never construct or embed.
class YukariObjectUpdateView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual int select_sequence(short);
 virtual void slot10();virtual unsigned char next_sequence_block();
 virtual void slot18();virtual int set_sequence_frame(short);
 virtual unsigned char next_sequence_frame();virtual void slot24();
 virtual void update_action_state();
 unsigned char emit_repeated(int,int,int);
 void release_auxiliary();unsigned char advance_frame();
 unsigned char advance_six(int);unsigned char advance_phase(int);
 void *position_relative(int,int);float stage_surface_height();
 void replace_secondary(int,float,int,int,int);void release_secondary();
 void set_secondary_alpha(unsigned char);void publish_layout_scalar(float);
 void dispatch_character_wave_handle(unsigned);void turn_heading(float,float,float);
 void update_ping_pong_motion();
 void *spawn_unparented(int,float,float,int,int,const unsigned *,int);
 void *spawn_parented(int,float,float,int,int,const unsigned *,int);
};
class YukariUpdateMotionView {public:void set_components(float,float);};
int __cdecl selector_random_roll(int);
double __cdecl lookup_orientation_sine_quantized_abs(float);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
float __cdecl atan2_degrees(float,float);
float __cdecl square_float_value(float);
int __cdecl square_int_value(int);
float __cdecl lookup_orientation_sine(int);
}
