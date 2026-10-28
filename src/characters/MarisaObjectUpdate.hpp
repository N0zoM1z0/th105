#pragma once
namespace th105 {
class Fighter;
// Primary pointer-only receiver. No allocation or complete class-size claim.
class MarisaObjectUpdateView {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual int select_sequence(short);
 virtual void slot10(); virtual unsigned char next_sequence_block();
 virtual void slot18(); virtual int select_frame(short);
 virtual unsigned char next_sequence_frame(); virtual void slot24();
 virtual void update_action_state();
 unsigned char advance_frame();
 unsigned char advance_six(int);
 unsigned char advance_phase(int);
 unsigned char emit_repeated(int,int,int);
 void emit_effect(int,float,float,int,int);
 void *spawn_parented(int,float,float,int,int,const void *,int);
 void *spawn_unparented(int,float,float,int,int,const void *,int);
 float stage_surface_height();
 void set_secondary_alpha(unsigned char);
 void replace_secondary(int,float,int,int,int);
 void turn_heading(float,float,float);
 void update_ping_pong_motion();
 Fighter *position_relative_to_owner(int,int);
};
class MarisaSpawnOwnerView { public:
 void emit_effect(int,float,float,int,int);
 void dispatch_character_wave_handle(unsigned);
 int spawn_owned(int,float,float,int,int,const void *,int);
};
class MarisaUpdateMotionView { public: void set_components(float,float); };
unsigned __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int);
double __cdecl lookup_orientation_sine_quantized_abs(float);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
float __cdecl atan2_degrees(float,float);
float __cdecl square_float_value(float);
extern int g_match_identifier;
}
