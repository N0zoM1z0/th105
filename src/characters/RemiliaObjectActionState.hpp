#ifndef TH105_REMILIA_OBJECT_UPDATE_HPP
#define TH105_REMILIA_OBJECT_UPDATE_HPP
namespace th105 {
// Pointer-only primary call view: never construct or embed this receiver.
class RemiliaObjectUpdateView {
public:
 virtual void slot00(); virtual void slot04(); virtual void slot08();
 virtual void select_sequence(short sequence);
 virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1c();
 virtual void dispatch_slot20(); virtual void slot24(); virtual void update_action_state();
 unsigned char emit_repeated(int mode,int count200,int count201);
 unsigned char advance_frame();
 unsigned char advance_phase(int limit);
 void replace_secondary(short key,float width,int subdivisions,int bands,int blend);
 void turn_heading(float bias,float max_step,float y_offset);
 void *position_relative(int x,int y);
 void dispatch_character_wave_handle(unsigned index);
 void *spawn_unparented(int action,float x,float y,unsigned char facing,int layer,const unsigned *words,int count);
 float stage_surface_height_at_x();
 void update_ping_pong_motion();
};
class RemiliaUpdateMotionView { public: void set_components(float angle,float magnitude); };
int __cdecl selector_random_roll(int limit);
float __cdecl atan2_degrees(float y,float x);
double __cdecl lookup_orientation_sine_quantized_abs(float angle);
double __cdecl lookup_orientation_cosine_quantized_abs(float angle);
}
#endif
