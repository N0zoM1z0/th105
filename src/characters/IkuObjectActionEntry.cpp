#include "characters/IkuObjectActionEntry.hpp"
// JP1.06a 0x0063B310: complete exact-first source candidate.
// Evidence: docs/IKU_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {
#define FIELD(type,offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this)+(offset)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define SKILL (*reinterpret_cast<signed char *>(FIELD(unsigned char *,0x348)+0x60F))
#define MOTION reinterpret_cast<IkuEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,x,y,layer) spawn_parented(a,x,y,B(0x104),layer,reinterpret_cast<const unsigned *>(payload),3)
#define UNSPAWN(a) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),1,reinterpret_cast<const unsigned *>(payload),3)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void IkuObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0; F(0x37C)=0;
 S(0x384)=0; F(0x380)=0; S(0x386)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800: B(0x184)=1; F(0x12C)=H[0]; SELECT(); return;
 case 801: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) B(0x184)=3;
  if(S(0x13E)==3) { payload[0]=0; payload[1]=0; payload[2]=4; B(0x184)=1; SPAWN(801,F(0xEC),F(0xF0),1); }
  if(S(0x13E)==4) { S(0x364)=255; replace_secondary(991,32,30,1,2); }
  if(S(0x13E)==5) { B(0x184)=1; MOVE(); }
  if(S(0x13E)==6) F(0x120)=0.5f; return;
 }
 case 802: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { payload[0]=-20; payload[1]=0; payload[2]=3; B(0x184)=3; SPAWN(802,F(0xEC),F(0xF0),1); }
  if(S(0x13E)==2) { F(0x12C)=H[0]; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==3) { F(0x124)=FIELD(signed char,0x104)*H[0]; F(0x128)=70; }
  if(S(0x13E)==4) { F(0x128)=70; F(0x12C)=H[0]; F(0x124)=FIELD(signed char,0x104)*-20.0; }
  if(S(0x13E)==5) { F(0x12C)=H[0]; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 }
 case 810: F(0x11C)=2; B(0x17C)=0; F(0x120)=0.75f; return;
 case 811: F(0x12C)=H[0]; SELECT(); if(S(0x13E)==0) S(0x344)=1; return;
 case 812:
  F(0x12C)=H[0]; B(0x184)=3; B(0x17C)=2; SELECT(); F(0x370)=1000;
  if(S(0x13E)==2) B(0x184)=1; return;
 case 813: {
  float payload[3]; F(0x12C)=H[0]; B(0x184)=1; B(0x17C)=3; SELECT();
  if(S(0x13E)==0) { payload[0]=random_float(360); payload[1]=0; payload[2]=1; UNSPAWN(813); } return;
 }
 case 815:
  B(0x17C)=4; SELECT();
  if(S(0x13E)==0 || S(0x13E)==3) B(0x184)=4;
  if(S(0x13E)==1 || S(0x13E)==4) B(0x184)=5;
  if(S(0x13E)==2) { F(0x12C)=H[0]; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 case 816: {
  float payload[3]; B(0x17C)=5; SELECT();
  if(S(0x13E)==0 || S(0x13E)==6) { payload[0]=0; payload[1]=0; payload[2]=3; B(0x184)=1; SPAWN(816,F(0xEC),F(0xF0),1); }
  if(S(0x13E)==2) { F(0x12C)=H[0]; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==3) F(0x128)=70;
  if(S(0x13E)==4) { F(0x128)=70; F(0x12C)=H[0]; F(0xF4)=-4; }
  if(S(0x13E)==5) { F(0x12C)=H[0]; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 }
 case 817: {
  float payload[3]; B(0x17C)=6; SELECT();
  if(S(0x13E)==0) F(0x370)=0.5f;
  if(S(0x13E)==2) { B(0x184)=1; F(0x120)=4; }
  if(S(0x13E)==3) F(0x370)=0.5f;
  if(S(0x13E)==6) { F(0x120)=30; payload[0]=0; payload[1]=0; payload[2]=9; SPAWN(817,F(0xEC),0,-1); }
  if(S(0x13E)==9) B(0x113)=0; return;
 }
 case 818: {
  float payload[3]; B(0x17C)=7; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0xF4)=H[0]; F(0xF8)=H[1]; payload[0]=0; payload[1]=0; payload[2]=1; SPAWN(818,F(0xEC),F(0xF0),1); payload[0]=0; payload[1]=0; payload[2]=3; UNSPAWN(818); }
  if(S(0x13E)==1) { S(0x364)=255; replace_secondary(990,15,30,1,2); }
  if(S(0x13E)==2) { float scale=random_float(5)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); }
  if(S(0x13E)==3) { payload[0]=0; payload[1]=0; payload[2]=4; UNSPAWN(818); }
  if(S(0x13E)==4) { float scale=random_float(10)*static_cast<double>(0.01f); F(0x370)=scale+0.25; F(0x124)=random_float(120)-60.0; F(0x128)=random_float(120)-60.0; } return;
 }
 case 823: {
  float payload[3]; F(0x12C)=H[0]; B(0x17C)=11; SELECT();
  if(S(0x13E)==2) {
   F(0x11C)=0; B(0x184)=2; if(SKILL>=2) B(0x184)=3; if(SKILL>=4) B(0x184)=4;
   payload[0]=0; payload[1]=1; payload[2]=0; SPAWN(823,F(0xEC),F(0xF0),1);
   payload[0]=0; payload[1]=-1; payload[2]=0; SPAWN(823,F(0xEC),F(0xF0),1);
  }
  if(S(0x13E)==3) { float scale=random_float(5)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); } return;
 }
 case 850:
  B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) B(0x184)=3;
  if(S(0x13E)==1) { F(0x370)=F(0xEC); F(0x374)=F(0xF0); F(0x378)=1; }
  if(S(0x13E)==3) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); }
  if(S(0x13E)==4) F(0x370)=1;
  if(S(0x13E)==5) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(60)*static_cast<double>(0.01f)+1.0); } return;
 case 851: F(0x11C)=2; F(0x120)=0.75f; return;
 case 852: {
  float payload[3]; B(0x184)=1; SELECT(); F(0x370)=1000;
  if(S(0x13E)==2) B(0x184)=1;
  if(S(0x13E)==5) { payload[0]=0; payload[1]=0; payload[2]=6; UNSPAWN(852); } return;
 }
 case 853:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x11C)=0; F(0x120)=0; }
  if(S(0x13E)==1) F(0x120)=4;
  if(S(0x13E)==2) { F(0x370)=1; B(0x184)=99; } return;
 case 856: {
  float payload[3]; F(0x12C)=H[0]; B(0x184)=1; SELECT();
  if(S(0x13E)==0) { payload[0]=random_float(360); payload[1]=0; payload[2]=1; UNSPAWN(856); } return;
 }
 case 857:
  S(0x344)=1; SELECT();
  if(S(0x13E)==1) { F(0x120)=F(0x11C)=static_cast<float>(random_float(5)*static_cast<double>(0.1f)+0.5); F(0x12C)=random_float(360); F(0x128)=random_float(90)-45.0; F(0x124)=random_float(90)-45.0; } return;
 case 859: {
  float payload[3]; SELECT();
  if(S(0x13E)==1) { B(0x184)=1; F(0x120)=4; }
  if(S(0x13E)==2) { I(0x180)=0; B(0x184)=1; payload[0]=0; payload[1]=0; payload[2]=3; SPAWN(859,F(0xEC),stage_height(),-1); payload[2]=5; SPAWN(859,F(0xEC),F(0xF0),1); payload[2]=6; SPAWN(859,F(0xEC),F(0xF0),1); payload[2]=9; SPAWN(859,F(0xEC),F(0xF0),-1); }
  if(S(0x13E)==3) B(0x113)=0;
  if(S(0x13E)==4) { float scale=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); }
  if(S(0x13E)==7) { float scale=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); F(0x12C)=random_float(360); B(0x184)=1; } return;
 }
 case 860:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x370)=F(0xEC); F(0x374)=F(0xF0); F(0x378)=45; F(0x37C)=H[0]; MOVE(); }
  if(S(0x13E)==2) B(0x184)=1;
  if(S(0x13E)==3) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); }
  if(S(0x13E)==4) { F(0x11C)=0; F(0x120)=0; }
  if(S(0x13E)==6) B(0x184)=1; return;
 case 898: SELECT(); if(S(0x13E)==1) { F(0x11C)=2; F(0x120)=2; } return;
 case 899: F(0x12C)=H[0]; if(H[2]>0.0f) SELECT(); return;
 case 900: {
  float payload[3]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==2) { F(0x11C)=0; payload[0]=0; payload[1]=1; payload[2]=0; B(0x184)=4; SPAWN(900,F(0xEC),F(0xF0),1); payload[0]=0; payload[1]=-1; payload[2]=0; SPAWN(900,F(0xEC),F(0xF0),1); }
  if(S(0x13E)==3) { float scale=random_float(5)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.75); }
  if(S(0x13E)==4) { F(0x120)=4; B(0x184)=1; F(0x11C)=0.25f; }
  if(S(0x13E)==5) { payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(900,F(0xEC),F(0xF0),1); }
  if(S(0x13E)==7) B(0x184)=1; return;
 }
 case 910: {
  float payload[3]; SELECT();
  if(S(0x13E)==1) { B(0x184)=1; F(0x120)=4; }
  if(S(0x13E)==2) F(0x370)=0.5f;
  if(S(0x13E)==4) { F(0x120)=30; payload[0]=0; payload[1]=0; payload[2]=6; SPAWN(910,F(0xEC),0,-1); }
  if(S(0x13E)==6) B(0x113)=0;
  if(S(0x13E)==7) { float scale=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); F(0x12C)=random_float(360); B(0x184)=1; } return;
 }
 case 920: {
  float payload[3]; SELECT();
  if(S(0x13E)==1) { B(0x184)=1; F(0x120)=4; }
  if(S(0x13E)==2) { B(0x184)=1; payload[0]=0; payload[1]=0; payload[2]=3; SPAWN(920,F(0xEC),stage_height(),-1); payload[2]=5; SPAWN(920,F(0xEC),F(0xF0),1); payload[2]=6; SPAWN(920,F(0xEC),F(0xF0),1); payload[2]=9; SPAWN(920,F(0xEC),F(0xF0),-1); }
  if(S(0x13E)==3) B(0x113)=0;
  if(S(0x13E)==4) { float scale=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); }
  if(S(0x13E)==7) { float scale=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(scale+0.5); F(0x12C)=random_float(360); B(0x184)=1; } return;
 }
 case 930:
  F(0x12C)=H[0]; SELECT(); if(S(0x13E)==0) B(0x184)=1;
  if(S(0x13E)==2) { B(0x184)=1; F(0x12C)+=90.0; F(0x11C)=15; F(0x120)=0; } return;
 case 980: continue_action_980(); return;
 case 995:
  B(0x134)=1; if(H[2]>0.0f) SELECT();
  if(S(0x13E)==1) { float scale=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(scale+1.0); } return;
 case 998: F(0x12C)=random_float(360); F(0x128)=60; return;
 }
}
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT
#undef MOTION
#undef SKILL
#undef H
#undef I
#undef B
#undef S
#undef F
#undef FIELD
}
