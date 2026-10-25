#pragma once
namespace th105 {
// Pointer-only views; original nominal owners/layouts are unknown. Never instantiate.
class TenshiObjectUpdateView {
public:
 virtual void slot00();virtual void slot04();virtual void slot08();
 virtual int select_sequence(short);virtual void slot10();
 virtual unsigned char next_sequence_block();virtual void slot18();
 virtual int set_sequence_frame(short);virtual unsigned char next_sequence_frame();virtual void slot24();
 virtual void update_action_state();
 unsigned char emit_repeated(int,int,int);unsigned char advance_frame();
 unsigned char advance_six(int);unsigned char advance_phase(int);
 float stage_surface_height();void publish_layout_scalar(float);
 void dispatch_character_wave_handle(unsigned);void turn_heading(float,float,float);
 void *position_relative(int,int);void release_auxiliary();void update_ping_pong_motion();
 void *spawn_unparented(int,float,float,unsigned char,int,const unsigned *,int);
 void *spawn_parented(int,float,float,unsigned char,int,const unsigned *,int);
};
class TenshiUpdateMotionView {public:void set_components(float,float);};
class TenshiSequenceSlotsView {public:void *subscript(unsigned);};
class TenshiObjectFactoryView {public:
 virtual void slot00();
 virtual void *spawn(void *,void *,int,float,float,unsigned char,int,const unsigned *,int);
};
int __cdecl selector_random_roll(int);
float __cdecl lookup_orientation_sine_quantized_abs(float);
float __cdecl lookup_orientation_cosine_quantized_abs(float);
float __cdecl atan2_degrees(float,float);float __cdecl square_float_value(float);
void __stdcall fill_stage_surface_range(float,float,float);
extern float g_update_left,g_update_right,g_update_top;
extern int g_update_weather,g_update_selector;
extern unsigned char g_update_mode;
}
