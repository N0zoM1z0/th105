#include "characters/TenshiObjectActionEntry.hpp"
// JP1.06a 0x00657150: complete source candidate, nonexact.
// Evidence and finite trials: docs/TENSHI_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {
#define FIELD(type,o) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define P FIELD(TenshiObjectEntryView *,0x348)
#define T FIELD(TenshiObjectEntryView *,0x34C)
#define AT(p,type,o) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define A(type,o) AT(FIELD(void *,0x154),type,o)
#define MOTION reinterpret_cast<TenshiEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,x,y,l) spawn_parented(a,x,y,B(0x104),l,reinterpret_cast<const unsigned *>(payload),3)
#define UNSPAWN(a,l) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),3)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void TenshiObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0;
 S(0x384)=0; F(0x37C)=0; S(0x386)=0; F(0x380)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800: {
  float payload[3]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { payload[0]=0; payload[1]=0; payload[2]=2; B(0x184)=1; UNSPAWN(800,1); payload[2]=3; UNSPAWN(800,1); }
  if(S(0x13E)==3) F(0x128)=60;
  if(S(0x13E)==4) { payload[0]=0; payload[1]=0; payload[2]=2; B(0x184)=6; UNSPAWN(800,1); payload[2]=3; UNSPAWN(800,1); } return;
 }
 case 801:
  SELECT();
  if(S(0x13E)==0) { MOVE(); double const heading=H[0]; B(0x184)=1; F(0x12C)=heading; F(0x120)=0.1f; }
  if(S(0x13E)==3) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); }
  if(S(0x13E)==4) { F(0x370)=F(0xEC)-AT(P,float,0xEC); F(0x374)=F(0xF0)-AT(P,float,0xF0); S(0x36C)=static_cast<unsigned>(selector_random_roll(100))<=50; } return;
 case 810:
  B(0x17C)=0; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1) {
   float scale=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5);
   replace_auxiliary(990); A(float,0xF8)=10; A(float,0xFC)=10; A(float,0xE8)=F(0xEC); A(float,0xEC)=stage_height(); A(unsigned char,0x104)=B(0x104); MOVE();
  }
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==4) { float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; }
  if(S(0x13E)==5) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==6) B(0x184)=1; return;
 case 811:
  B(0x17C)=4; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==4) { float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; }
  if(S(0x13E)==5) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==6) B(0x184)=1; return;
 case 815:
  B(0x17C)=1; SELECT();
  if(S(0x13E)==0) { MOVE(); B(0x184)=1; replace_auxiliary(990); A(float,0xF8)=10; A(float,0xFC)=10; A(float,0xE8)=F(0xEC); A(float,0xEC)=stage_height(); A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==1) { F(0x12C)=H[0]; float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; }
  if(S(0x13E)==4) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 case 816:
  B(0x17C)=5; SELECT();
  if(S(0x13E)==0) { B(0x113)=0; F(0x370)=0.25f; B(0x184)=1; F(0x374)=100; }
  if(S(0x13E)==3 || S(0x13E)==4) { float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; } return;
 case 820: {
  float payload[3]; B(0x17C)=2; SELECT();
  if(S(0x13E)==1) {
   F(0x37C)=1; F(0x11C)=32; payload[0]=0; payload[1]=0; payload[2]=0; SPAWN(820,F(0xEC),F(0xF0),B(0x33C));
   F(0x12C)=H[0]; F(0x120)=0; if(T) { B(0x184)=1; F(0x370)=F(0xEC)-AT(T,float,0xEC); F(0x374)=F(0xF0)-AT(T,float,0xF0); }
  }
  if(S(0x13E)==2) { F(0x120)=0; F(0x12C)=H[0]; if(T) { B(0x184)=1; F(0x370)=F(0xEC)-AT(T,float,0xEC); F(0x374)=F(0xF0)-AT(T,float,0xF0); } }
  if(S(0x13E)==3) { F(0x370)=F(0xEC)-AT(P,float,0xEC); F(0x374)=F(0xF0)-AT(P,float,0xF0); F(0x378)=5; }
  if(S(0x13E)==5) { F(0x11C)=32; F(0x37C)=2; payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(820,F(0xEC),F(0xF0),B(0x33C)); F(0x12C)=H[0]; F(0x120)=0; if(T) { B(0x184)=1; F(0x370)=F(0xEC)-AT(T,float,0xEC); F(0x374)=F(0xF0)-AT(T,float,0xF0); } } return;
 }
 case 821:
  B(0x17C)=6; SELECT();
  if(S(0x13E)==1) { B(0x184)=1; F(0x374)=15; B(0x113)=0; }
  if(S(0x13E)==4 || S(0x13E)==5 || S(0x13E)==6) { float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; }
  if(S(0x13E)==7) B(0x184)=1;
  if(S(0x13E)==8) F(0x12C)=H[0]; return;
 case 825:
  B(0x17C)=3; SELECT(); if(S(0x13E)==0) { F(0x120)=F(0x11C)=static_cast<float>(random_float(50)*static_cast<double>(0.01f)+0.5); F(0x12C)=random_float(360); } return;
 case 848:
  SELECT(); if(S(0x13E)==0) F(0x370)=H[0];
  if(S(0x13E)==1) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==2) { F(0x11C)=0; F(0x120)=0; F(0x370)=1; }
  if(S(0x13E)==3) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 case 850:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1) {
   float scale=random_float(25)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0);
   replace_auxiliary(990); A(float,0xF8)=10; A(float,0xFC)=10; A(float,0xE8)=F(0xEC); A(float,0xEC)=stage_height(); A(unsigned char,0x104)=B(0x104); MOVE();
  }
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==4) { float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; }
  if(S(0x13E)==5) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==6) B(0x184)=1; return;
 case 851:
  SELECT(); if(S(0x13E)==0) F(0x120)=F(0x11C)=static_cast<float>(H[1]+1.0);
  if(S(0x13E)==5) F(0x120)=F(0x11C)=static_cast<float>(random_float(15)*static_cast<double>(0.1f)+0.5); return;
 case 852:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==2) { F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+1.0); F(0x12C)=random_float(360); F(0x370)=random_float(10)-5.0; } return;
 case 853:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==4) { float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; }
  if(S(0x13E)==5) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==6 || S(0x13E)==7) B(0x184)=1; return;
 case 854:
  SELECT();
  if(S(0x13E)==0) { B(0x184)=5; F(0x12C)=H[0]; }
  if(S(0x13E)==1) F(0x370)=0.4f;
  if(S(0x13E)==2) { float scale=random_float(40)*static_cast<double>(0.01f); F(0x370)=scale+static_cast<double>(0.2f); }
  if(S(0x13E)==3) {
   S(0x344)=1; B(0x113)=0; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1;
   float * const input=H; F(0xEC)=lookup_orientation_cosine_quantized_abs(-input[0])*input[1]*FIELD(signed char,0x104)+AT(P,float,0xEC);
   F(0xF0)=lookup_orientation_sine_quantized_abs(-input[0])*H[1]+(AT(P,float,0xF0)+100.0);
  }
  if(S(0x13E)==4) F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+0.5);
  if(S(0x13E)==5) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==6) { B(0x184)=10; F(0x12C)=H[0]; }
  if(S(0x13E)==7) { F(0x120)=40; F(0x12C)=H[0]; }
  if(S(0x13E)==8) { if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 case 855:
  SELECT(); if(S(0x13E)==0) B(0x184)=1;
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==4) { float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; } return;
 case 856:
  SELECT(); if(S(0x13E)==1) { F(0x12C)=H[0]; float scale=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); MOVE(); F(0x374)=random_float(20)-10.0; } return;
 case 857: {
  float payload[3]; SELECT();
  if(S(0x13E)==1) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); F(0x12C)=random_float(360); if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==3) { F(0x12C)=H[0]; B(0x184)=1; F(0x120)=2; payload[0]=H[0]; payload[1]=0; payload[2]=5; SPAWN(857,F(0xEC),F(0xF0),1); }
  if(S(0x13E)==6) F(0x12C)=H[0]; return;
 }
 case 899: B(0x184)=1; SELECT(); if(S(0x13E)==1) F(0x12C)=random_float(360); return;
 case 900:
  SELECT(); if(S(0x13E)==0) { B(0x113)=0; F(0x11C)=0; F(0x120)=3; }
  if(S(0x13E)==1) { B(0x184)=1; MOVE(); }
  if(S(0x13E)==3) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(75)*static_cast<double>(0.01f)+0.75); MOVE(); } return;
 case 920: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { S(0x364)=static_cast<short>(static_cast<int>(H[0])); F(0x370)=200; B(0x184)=1; replace_auxiliary(990); A(float,0xF8)=4; A(float,0xFC)=4; A(float,0xE8)=F(0xEC); A(float,0xEC)=stage_height(); A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==1) { F(0x11C)=1.5f; F(0x120)=1.5f; S(0x364)=static_cast<short>(static_cast<int>(H[0])); B(0x184)=1; MOTION->set_components(-90,H[1]); replace_auxiliary(990); A(float,0xE8)=F(0xEC); A(float,0xEC)=stage_height(); A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==4) { MOVE(); double const heading=H[0]; B(0x184)=1; F(0x12C)=heading; F(0x120)=0.1f; }
  if(S(0x13E)==6) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); }
  if(S(0x13E)==8) { F(0x370)=F(0xEC)-AT(P,float,0xEC); F(0x374)=F(0xF0)-AT(P,float,0xF0); S(0x36C)=static_cast<unsigned>(selector_random_roll(100))<=50; }
  if(S(0x13E)==9) { MOVE(); payload[0]=0; payload[1]=0; payload[2]=10; SPAWN(920,F(0xEC),stage_height(),-1); replace_auxiliary(990); A(float,0xF8)=4; A(float,0xFC)=4; A(float,0xE8)=F(0xEC); A(float,0xEC)=stage_height(); A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==10) B(0x113)=0; return;
 }
 case 930:
  SELECT(); if(S(0x13E)==0) { MOVE(); B(0x184)=1; }
  if(S(0x13E)==2) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); } return;
 case 940: {
  float payload[3]; SELECT();
  if(S(0x13E)==1) {
   F(0x12C)=random_float(360); S(0x344)=1; B(0x113)=0; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1;
   float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5);
   float * const input=H; F(0xEC)=lookup_orientation_cosine_quantized_abs(-input[0])*input[1]*FIELD(signed char,0x104)+AT(P,float,0xEC);
   F(0xF0)=lookup_orientation_sine_quantized_abs(-input[0])*H[1]+AT(P,float,0xF0);
  }
  if(S(0x13E)==2) { MOVE(); F(0x12C)=H[0]; F(0x120)=0.1f; payload[0]=0; payload[1]=0; payload[2]=5; B(0x184)=1; UNSPAWN(940,1); }
  if(S(0x13E)==4) F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+0.5);
  if(S(0x13E)==7) { F(0x11C)=40; F(0x12C)=H[0]; F(0x120)=0; F(0x370)=1; payload[0]=H[0]; payload[1]=0; payload[2]=6; SPAWN(940,F(0xEC),F(0xF0),1); }
  if(S(0x13E)==8) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); F(0x12C)=random_float(360); if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==9) { F(0x12C)=H[0]; B(0x184)=1; payload[0]=H[0]; payload[1]=0; payload[2]=11; SPAWN(940,F(0xEC),F(0xF0),1); }
  if(S(0x13E)==12) F(0x12C)=H[0];
  if(S(0x13E)==13) { P->dispatch_character_wave_handle(56); I(0x144)=0; payload[0]=H[0]; payload[1]=180; payload[2]=9; SPAWN(940,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*100.0*FIELD(signed char,0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-H[0])*100.0+F(0xF0)),1); } return;
 }
 case 960: case 961:
  SELECT(); if(S(0x13E)<=7) { if(g_event_effect_id==14) { B(0x111)=128; B(0x112)=128; } replace_auxiliary(989); A(float,0xF8)=1.05f; A(float,0xFC)=1; A(float,0xE8)=F(0xEC); A(float,0xEC)=0; A(unsigned char,0x104)=B(0x104); } return;
 case 962: {
  float payload[3]; SELECT(); if(S(0x13E)<=7) {
   if(g_event_effect_id==14) { B(0x111)=128; B(0x112)=128; }
   replace_auxiliary(989); A(float,0xF8)=1.05f; A(float,0xFC)=1; A(float,0xE8)=F(0xEC); A(float,0xEC)=-AT(P,float,0x828); A(unsigned char,0x104)=B(0x104);
   payload[1]=20; payload[2]=4;
   for(float n=0;n<8;n+=1.0) { payload[0]=random_float(30)+n*45.0; if(payload[0]>=0 && payload[0]<=180) spawn_unparented(815,F(0xEC),stage_height(),B(0x104),1,reinterpret_cast<const unsigned *>(payload),3); else spawn_unparented(815,F(0xEC),stage_height(),B(0x104),-1,reinterpret_cast<const unsigned *>(payload),3); }
  } return;
 }
 case 980: continue_action_980(); return;
 case 997:
  F(0xF4)=5; F(0xF8)=20; SELECT();
  if(S(0x13E)==3) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); F(0x12C)=random_float(360); if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==4) F(0x12C)=-90; return;
 }
}
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT
#undef MOTION
#undef A
#undef AT
#undef T
#undef P
#undef H
#undef I
#undef B
#undef S
#undef F
#undef FIELD
}
