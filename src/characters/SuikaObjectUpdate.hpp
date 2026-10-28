#pragma once
namespace th105 {
class Fighter;
// Pointer-only primary call view; do not instantiate as a recovered allocation.
class SuikaObjectUpdateView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();virtual int select_sequence(short);
 virtual void slot10();virtual unsigned char next_sequence_block();virtual void slot18();virtual int select_frame(short);
 virtual unsigned char next_sequence_frame();virtual void slot24();virtual void update_action_state();
 unsigned char advance_frame();unsigned char advance_six(int);unsigned char advance_phase(int);unsigned char emit_repeated(int,int,int);
 void replace_secondary(int,float,int,int,int);void release_secondary();void release_auxiliary();
 void turn_heading(float,float,float);float stage_surface_height();int has_crossed_stage_surface_while_descending();
 void publish_battle_layout_scalar(float);
 void emit_effect(int,float,float,int,int);void forward_hit_quantity(int,int,short,signed char);
 void *spawn_unparented(int,float,float,int,int,const void*,int);void *spawn_parented(int,float,float,int,int,const void*,int);
 void publish_bounds_descriptor(int,int,int,int,short,short,short);
 Fighter *position_relative_to_owner(int,int);void update_ping_pong_motion();
};
class SuikaUpdateMotionView {public:void set_components(float,float);int selector_random_range(int,int);};
class SuikaUpdateOwnerView {public:void dispatch_character_wave_handle(unsigned);void publish_battle_layout_scalar(float);};
int __cdecl selector_random_roll(int);
double __cdecl lookup_orientation_sine_quantized_abs(float);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
float __cdecl lookup_orientation_sine(int);float __cdecl lookup_orientation_cosine(int);
float __cdecl lookup_orientation_ratio_quantized_abs(int);
float __cdecl square_float_value(float);float __cdecl atan2_degrees(float,float);float __cdecl absolute_scalar_float(float);
extern int g_match_identifier;
}
