#pragma once
namespace th105 {
extern float g_update_left,g_update_right,g_update_top;
extern int g_match_identifier;
// Pointer-only primary call view. Never construct or embed.
class YuyukoObjectUpdateView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual int select_sequence(short);virtual void slot10();
 virtual unsigned char next_sequence_block();virtual void slot18();
 virtual int set_sequence_frame(short);virtual void slot20();virtual void slot24();
 virtual void update_action_state();
 unsigned char emit_repeated(int,int,int);unsigned char advance_frame();
 unsigned char advance_six(int);unsigned char advance_phase(int);
 void replace_secondary(int,float,int,int,int);void set_secondary_alpha(unsigned char);
 void *position_relative(int,int);float stage_surface_height();
 void dispatch_character_wave_handle(unsigned);void turn_heading(float,float,float);
 void publish_bounds(int,int,int,int,short,short,short);void update_ping_pong_motion();
 void emit_fighter_effect_433cc0(int,float,float,int,int);
 void *spawn_unparented(int,float,float,unsigned char,int,const unsigned *,int);
 void *spawn_parented(int,float,float,unsigned char,int,const unsigned *,int);
};
class YuyukoUpdateMotionView {public:void set_components(float,float);};
int __cdecl selector_random_roll(int);
float __cdecl lookup_orientation_sine_quantized_abs(float);
float __cdecl lookup_orientation_cosine_quantized_abs(float);
float __cdecl lookup_orientation_cosine(int);
float __cdecl atan2_degrees(float,float);
float __cdecl square_float_value(float);float __cdecl sqrt_float_value(float);
}
