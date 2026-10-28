#pragma once
#include "characters/AnimationSequenceVirtuals.hpp"
namespace th105 {
// Pointer-only inherited sequence view, not a recovered complete allocation.
class SakuyaActionStateView;
bool __fastcall sakuya_state_13c_in_32_95(SakuyaActionStateView *);
float __fastcall sakuya_surface(SakuyaActionStateView *);
int __fastcall sakuya_on_surface(SakuyaActionStateView *);
float __cdecl sakuya_absolute(float);
double __cdecl sakuya_sine(float);
double __cdecl sakuya_cosine(float);
float __cdecl sakuya_atan(float,float);
unsigned __cdecl sakuya_random_u32();
int __cdecl sakuya_random(int);
class SakuyaActionScratch {public:void reset();void set_oriented_components(float,float);};
class SakuyaActionStateView:public AnimationSequenceObjectView {
public:
 void dispatch_action_state_vslot28();
 unsigned char landing();
 unsigned char advance();
 int crossed();
 void zero_motion();
 void effect(int,float,float,int,int);
 int spawn(int,float,float,int,int,const void *,int);
 signed char x_boundary();
 void layout(float);
 void event(unsigned);
 void copy_action_word();
 void finalize(int);
 void sequence_window(signed char,int,int);
 void texture(signed char,short);
 void counter(short,int);
 void secondary_cycle();
 int phase_counter(int);
 void flip();
 unsigned char directional(int);
 void common_update();
 signed char shared_first(signed char,float);
 signed char shared_second(signed char,float);
};
extern int g_sakuya_action_match;
}
