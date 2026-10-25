#pragma once
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
// Pointer-only primary call view; the concrete owner is not recovered.
class AliceFighterActionStateView : public AnimationSequenceObjectView {
public:
 unsigned char resolve_stage_surface_landing_transition();
 unsigned char advance_frame_and_dispatch();
 int has_crossed_stage_surface_while_descending();
 void zero_velocity_acceleration();
 unsigned char try_dispatch_directional_action_208_210(int);
 void dispatch_indexed_event_member(unsigned);
 void dispatch_character_wave_handle(unsigned);
 void emit_fighter_effect_433cc0(int,float,float,int,int);
 void adjust_counter_482(short,int);
 int add_phase_scaled_counter_558(int);
 void face_opponent_and_flip_horizontal_velocity();
 int spawn_owned_object_via_manager(int,float,float,int,int,const void *,int);
 void publish_texture_state(signed char,short);
 void dispatch_indexed_sequence_window_45c8b0(signed char,int,int);
 void advance_secondary_event_effect_cycle();
 void finalize_sequence_entry(int);
 void copy_action_word_176_to_174();
 void update_common_action_state();
 void dispatch_action_state();
};
struct AliceFighterScratchView { void reset(); };
float __fastcall alice_stage_surface_height_at_x(AliceFighterActionStateView *);
int __fastcall is_y_at_or_below_stage_surface(void *);
extern int g_match_identifier;
unsigned __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int);
float __cdecl atan2_degrees(float,float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
}
