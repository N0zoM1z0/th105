#ifndef TH105_YOUMU_OBJECT_UPDATE_HPP
#define TH105_YOUMU_OBJECT_UPDATE_HPP
namespace th105 {
// Pointer-only primary call view, never construct or embed.
class YoumuObjectUpdateView {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual int select_sequence(short sequence);
 virtual void slot10(); virtual unsigned char next_sequence_block();
 virtual void slot18(); virtual int set_sequence_frame(short frame);
 virtual unsigned char next_sequence_frame(); virtual void slot24();
 virtual void update_action_state();
 unsigned char emit_repeated(int mode,int count200,int count201);
 unsigned char advance_frame();
 unsigned char advance_phase(int limit);
 unsigned char advance_six(int limit);
 void turn_heading(float bias,float max_step,float y_offset);
 void *position_relative(int x,int y);
 void dispatch_character_wave_handle(unsigned index);
 void *spawn_unparented(int action,float x,float y,int facing,int layer,const unsigned *words,int count);
 float stage_surface_height_at_x();
 void update_ping_pong_motion();
 void publish_bounds_descriptor(int x1,int y1,int x2,int y2,short m10,short m12,short m14);
 void emit_fighter_effect(int code,float x,float y,int direction,int trailing);
 unsigned char apply_owner_record(unsigned index);
};
class YoumuUpdateMotionView { public: void set_components(float angle,float magnitude); };
int __cdecl selector_random_roll(int limit);
float __cdecl atan2_degrees(float y,float x);
float __cdecl square_float_value(float value);
double __cdecl lookup_orientation_sine_quantized_abs(float angle);
double __cdecl lookup_orientation_cosine_quantized_abs(float angle);
}
#endif
