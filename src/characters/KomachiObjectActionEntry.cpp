#include "characters/KomachiObjectActionEntry.hpp"
// JP1.06a 0x00600390: complete source candidate, nonexact at seven bytes.
// Evidence and finite trials: docs/KOMACHI_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {
#define FIELD(type,offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this)+(offset)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define MOTION reinterpret_cast<KomachiEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),1,reinterpret_cast<const unsigned *>(payload),3)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void KomachiObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0;
 S(0x384)=0; F(0x37C)=0; S(0x386)=0; F(0x380)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 801:
  B(0x184)=1; SELECT();
  if(S(0x13E)==0) { replace_secondary(991,20,30,2,2); F(0x370)=F(0xEC); F(0x374)=F(0xF0); MOVE(); }
  if(S(0x13E)==1) { MOVE(); F(0x12C)=random_float(360); F(0x11C)=1.25f; F(0x120)=1.25f; }
  if(S(0x13E)==3) F(0x12C)=H[0];
  if(S(0x13E)==4) { F(0x128)=H[0]; F(0x124)=H[1]; } return;
 case 810:
  B(0x17C)=0; SELECT();
  if(S(0x13E)==0) B(0x184)=1;
  if(S(0x13E)==1 || S(0x13E)==4 || S(0x13E)==5) { B(0x184)=1; F(0x370)=2; }
  if(S(0x13E)==2) { float scale=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); F(0x12C)=random_float(360); }
  if(S(0x13E)==3) { float scale=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); S(0x364)=static_cast<short>(selector_random_roll(20)+10); F(0x12C)=random_float(360); } return;
 case 811: B(0x17C)=4;
 case 800: B(0x184)=1; SELECT(); return;
 case 812:
  B(0x17C)=8; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; F(0xF0)=stage_height(); }
  if(S(0x13E)==1) { float scale=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); S(0x364)=static_cast<short>(selector_random_roll(20)+10); F(0x12C)=random_float(360); }
  if(S(0x13E)==2) { B(0x184)=1; F(0xF0)=stage_height(); }
  if(S(0x13E)==3) { float scale=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); F(0x12C)=random_float(360); F(0x370)=random_float(25)*static_cast<double>(0.01f)+0.25; } return;
 case 815:
  B(0x17C)=1; B(0x184)=1;
  F(0x120)=F(0x11C)=static_cast<float>(random_float(40)*static_cast<double>(0.01f)+static_cast<double>(0.8f));
  F(0x12C)=static_cast<float>(mt19937_next_u32()%360); SELECT(); S(0x364)=0;
  if(S(0x13E)==0) MOVE();
  if(S(0x13E)==2) { MOVE(); F(0x12C)=random_float(360); F(0x11C)=1.25f; F(0x120)=1.25f; } return;
 case 817:
  B(0x17C)=5; SELECT();
  if(S(0x13E)==0) {
   float scale=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+H[0]);
   F(0x12C)=random_float(360); F(0x124)=random_float(30)-15.0; F(0x128)=random_float(20)+50.0;
  }
  if(S(0x13E)==2) { F(0x12C)=H[0]; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 case 820: {
  float payload[3]; B(0x17C)=2; SELECT();
  if(S(0x13E)==0) B(0x113)=0;
  if(S(0x13E)==1) { for(int n=12;n!=0;--n) { payload[0]=random_float(360); payload[1]=random_float(30)+10.0; payload[2]=3; SPAWN(820); } }
  if(S(0x13E)==3) F(0x120)=F(0x11C)=static_cast<float>(random_float(15)*static_cast<double>(0.1f)+0.5);
  if(S(0x13E)==4) B(0x184)=1;
  if(S(0x13E)==5) F(0xF8)=4; return;
 }
 case 821:
  B(0x17C)=6; SELECT();
  if(S(0x13E)==1) { B(0x184)=1; F(0x370)=1; }
  if(S(0x13E)==4) F(0x370)=0.35f;
  if(S(0x13E)==2 || S(0x13E)==3) F(0x11C)=H[0]; return;
 case 822:
  B(0x17C)=10; SELECT();
  if(S(0x13E)==0) { F(0x370)=10.0-random_float(20); F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+0.5); B(0x113)=0; } return;
 case 825:
  B(0x184)=1; B(0x17C)=3; SELECT();
  if(S(0x13E)==0) { replace_secondary(994,20,30,2,2); F(0x370)=F(0xEC); F(0x374)=F(0xF0); MOVE(); }
  S(0x364)=0;
  if(S(0x13E)==1) { MOVE(); F(0x12C)=random_float(360); F(0x11C)=1.25f; F(0x120)=1.25f; }
  if(S(0x13E)==3) F(0x12C)=H[0]; return;
 case 826:
  B(0x184)=1; SELECT();
  if(S(0x13E)==1) { MOVE(); F(0x12C)=random_float(360); }
  if(S(0x13E)==3) F(0x12C)=H[0]; return;
 case 827:
  SELECT(); if(S(0x13E)==0) { replace_secondary(993,20,30,2,2); MOVE(); }
  if(S(0x13E)==1) { MOVE(); F(0x12C)=random_float(360); F(0x11C)=1.25f; F(0x120)=1.25f; } return;
 case 850:
  SELECT(); if(S(0x13E)==1) { F(0x12C)=random_float(360); F(0x370)=0.5f; MOVE(); float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); } return;
 case 852:
  B(0x184)=1; SELECT();
  if(S(0x13E)==0) { replace_secondary(991,20,30,2,2); F(0x370)=F(0xEC); F(0x374)=F(0xF0); MOVE(); }
  if(S(0x13E)==1) { MOVE(); F(0x12C)=random_float(360); F(0x11C)=1.25f; F(0x120)=1.25f; } return;
 case 853:
  SELECT();
  if(S(0x13E)==0) { F(0xF4)=H[0]; B(0x184)=1; I(0x144)=static_cast<short>(selector_random_roll(360)); float scale=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); }
  if(S(0x13E)==3) { F(0x12C)=random_float(360); F(0x370)=0.5f; MOVE(); float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); } return;
 case 854:
  SELECT();
  if(S(0x13E)==0 || S(0x13E)==1) { F(0x374)=10; F(0xF8)=10; }
  if(S(0x13E)==2 || S(0x13E)==3) { F(0x12C)=random_float(360); F(0x370)=0.5f; MOVE(); float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); }
  if(S(0x13E)==4) { float scale=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); } return;
 case 855:
  SELECT(); if(S(0x13E)==0) { replace_secondary(993,20,30,2,2); MOVE(); }
  if(S(0x13E)==1) { MOVE(); F(0x12C)=random_float(360); F(0x11C)=1.25f; F(0x120)=1.25f; } return;
 case 856:
  SELECT(); if(S(0x13E)==0) { B(0x184)=1; F(0xF8)=H[1]; }
  if(S(0x13E)==1) { float scale=random_float(25)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); S(0x364)=static_cast<short>(selector_random_roll(20)+10); F(0x12C)=random_float(360); }
  if(S(0x13E)==2) F(0x370)=1;
  if(S(0x13E)==3) { float scale=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); S(0x364)=static_cast<short>(selector_random_roll(20)+10); F(0x12C)=random_float(360); F(0x374)=random_float(8)-4.0; }
  if(S(0x13E)==4) F(0x370)=0.6f; return;
 case 861:
  SELECT(); if(S(0x13E)==1) { B(0x184)=1; F(0x370)=1; }
  if(S(0x13E)==4) F(0x370)=0.5f; return;
 case 900:
  SELECT();
  if(S(0x13E)==0) { B(0x113)=0; F(0x370)=random_float(20)*static_cast<double>(0.1f)+2.0; if(static_cast<unsigned>(selector_random_roll(100))<50) F(0x370)=-F(0x370); }
  if(S(0x13E)==1) F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+0.5);
  if(S(0x13E)==2) B(0x184)=1;
  if(S(0x13E)==3) F(0x12C)=H[0];
  if(S(0x13E)==4) { B(0x184)=1; F(0x370)=1; }
  if(S(0x13E)==5) F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+0.5); return;
 case 901:
  SELECT();
  if(S(0x13E)==1) F(0x370)=1;
  if(S(0x13E)==2 || S(0x13E)==3) F(0x11C)=2;
  if(S(0x13E)==4) F(0x370)=0.6f;
  if(S(0x13E)==6) { float scale=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); S(0x364)=static_cast<short>(selector_random_roll(20)+10); F(0x12C)=random_float(360); F(0x374)=random_float(8)-4.0; }
  if(S(0x13E)==7) { float scale=random_float(25)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); S(0x364)=static_cast<short>(selector_random_roll(20)+10); F(0x12C)=random_float(360); }
  if(S(0x13E)>=10 && S(0x13E)<=13) { B(0x184)=1; F(0xF8)=H[1]; } return;
 case 902: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) {
   B(0x184)=1; F(0x12C)=H[0]; payload[0]=0; payload[1]=0; payload[2]=2; SPAWN(902); payload[2]=3; SPAWN(902);
   switch(g_match_identifier) { case 2: case 3: S(0x364)=480; break; case 1: S(0x364)=300; break; case 0: S(0x364)=240; break; }
  }
  if(S(0x13E)==1) { float scale=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); S(0x364)=static_cast<short>(selector_random_roll(20)+10); F(0x12C)=random_float(360); } return;
 }
 case 930: {
  float payload[3]; B(0x17C)=2; SELECT(); if(S(0x13E)==0) B(0x113)=0;
  if(S(0x13E)==1) { for(int n=12;n!=0;--n) { payload[0]=random_float(360); payload[1]=random_float(30)+10.0; payload[2]=3; SPAWN(930); } }
  if(S(0x13E)==3) F(0x120)=F(0x11C)=static_cast<float>(random_float(15)*static_cast<double>(0.1f)+0.5); return;
 }
 case 980: continue_action_980(); return;
 case 999: SELECT(); if(S(0x13E)==2) { F(0xF4)=H[0]; F(0xF8)=H[1]; } return;
 }
}
#undef SPAWN
#undef MOVE
#undef SELECT
#undef MOTION
#undef H
#undef I
#undef B
#undef S
#undef F
#undef FIELD
}
