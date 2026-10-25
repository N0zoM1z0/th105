#pragma once
namespace th105 {
// Primary pointer-only ABI view; never construct or embed.
class IkuObjectUpdateView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual int select_sequence(short);
 virtual void slot10();virtual unsigned char next_sequence_block();
 virtual void slot18();virtual void slot1c();virtual void slot20();virtual void slot24();
 virtual void update_action_state();
 unsigned char emit_repeated(int,int,int);
 void dispatch_character_wave_handle(unsigned);
 unsigned char advance_frame();unsigned char advance_six(int);unsigned char advance_phase(int);
 void *spawn_unparented(int,float,float,int,int,const unsigned *,int);
 void *spawn_parented(int,float,float,int,int,const unsigned *,int);
 float stage_surface_height();void set_sprite_uv_size(float,float);
 void turn_heading(float,float,float);void update_ping_pong_motion();
 void set_secondary_flags(unsigned char,unsigned char);void set_secondary_alpha(unsigned char);
 void *position_relative(int,int);void emit_fighter_effect_433cc0(int,float,float,int,int);
 void publish_bounds(int,int,int,int,short,short,short);
};
class IkuUpdateMotionView {public:void set_components(float,float);};
int __cdecl selector_random_roll(int);
double __cdecl lookup_orientation_sine_quantized_abs(float);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
float __cdecl atan2_degrees(float,float);
float __cdecl sqrt_float_value(float);
extern int g_match_identifier;
}
