#include "characters/SuikaObjectActionEntry.hpp"
// JP1.06a 0x005BD380: complete nonexact source; see docs/SUIKA_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define H FIELD(float *,0x340)
#define T FIELD(SuikaObjectEntryView *,0x34C)
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define MOTION reinterpret_cast<SuikaEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,l) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),3)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void SuikaObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0; F(0x37C)=0;
 S(0x384)=0; F(0x380)=0; S(0x386)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800:
  B(0x184)=1; SELECT();
  if(S(0x13E)==0) { F(0xF4)=H[0]; F(0xF8)=H[1]; }
  if(S(0x13E)==3) MOVE();
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+1.0); F(0x12C)=random_float(360); F(0x370)=random_float(40)*static_cast<double>(0.1f)-2.0; } return;
 case 801:
  B(0x184)=1; SELECT();
  if(S(0x13E)==0) { F(0xF4)=H[0]; F(0xF8)=H[1]; }
  if(S(0x13E)==1) MOVE();
  if(S(0x13E)==4) MOVE(); return;
 case 810: {
  float payload[3]; B(0x17C)=0; B(0x184)=1; F(0x12C)=H[0]; MOVE(); SELECT();
  if(S(0x13E)==1 || S(0x13E)==5) { payload[2]=3; for(float n=0;n<4;n+=1.0) { payload[0]=random_float(360); payload[1]=random_float(8)+4.0; SPAWN(810,1); } }
  if(S(0x13E)==2) { F(0x124)=random_float(360); F(0x128)=random_float(360); }
  if(S(0x13E)==3) { float product=random_float(100)*static_cast<double>(0.1f); F(0x370)=product-5.0; F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+1.0); } return;
 }
 case 811:
  B(0x17C)=1; B(0x184)=1; SELECT();
  if(S(0x13E)==0) { MOVE(); if(F(0xF4)>0) F(0x370)=-0.15f; else F(0x370)=0.15f; }
  if(S(0x13E)==1) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.05f)+1.0); }
  if(S(0x13E)==2) F(0x124)=80;
  if(S(0x13E)==3) { MOVE(); if(F(0xF4)>0) F(0x370)=-0.15f; else F(0x370)=0.15f; }
  if(S(0x13E)==4) { MOVE(); if(F(0xF4)>0) F(0x370)=-0.15f; else F(0x370)=0.15f; } return;
 case 812:
  B(0x17C)=2; B(0x184)=1; SELECT();
  if(S(0x13E)==0) { F(0xF4)=H[0]; F(0xF8)=H[1]; if(F(0xF8)>0) F(0x370)=-0.1f; else F(0x370)=0.1f; }
  if(S(0x13E)==2) MOVE(); return;
 case 813:
  B(0x17C)=3; B(0x184)=5; SELECT();
  if(S(0x13E)==0 || S(0x13E)==3) { F(0xF4)=H[0]; F(0xF8)=H[1]; }
  if(S(0x13E)==2 || S(0x13E)==5) F(0x12C)=random_float(360); return;
 case 815:
  B(0x17C)=4; B(0x184)=1; F(0x12C)=H[0]; MOVE(); SELECT();
  if(S(0x13E)==3) F(0x120)=F(0x11C)=H[3];
  if(S(0x13E)==4) { float product=random_float(100)*static_cast<double>(0.1f); F(0x370)=product-5.0; F(0x12C)=random_float(360); double const delta=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(delta+H[3]); }
  if(S(0x13E)==5) { float product=random_float(100)*static_cast<double>(0.1f); F(0x370)=product-5.0; F(0x12C)=random_float(360); double const delta=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(delta+H[3]); }
  if(S(0x13E)==10) { F(0xF4)=0; F(0xF8)=0; if(T) { float *const input=H; F(0xEC)=lookup_orientation_cosine_quantized_abs(input[0])*input[1]+AT(T,float,0xEC); F(0xF0)=lookup_orientation_sine_quantized_abs(input[0])*H[1]+AT(T,float,0xF0); } } return;
 case 816:
  B(0x17C)=5; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; MOVE(); if(F(0xF4)>0) F(0x370)=-0.15f; else F(0x370)=0.15f; }
  if(S(0x13E)==1) F(0xF8)=5;
  if(S(0x13E)==2) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.05f)+1.0); }
  if(S(0x13E)==3) F(0x124)=80; return;
 case 817:
  B(0x17C)=6; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1 || S(0x13E)==2 || S(0x13E)==4 || S(0x13E)==5) { if(S(0x13E)==5) B(0x113)=0; float product=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==3) B(0x184)=1; return;
 case 818:
  B(0x17C)=7; SELECT();
  if(S(0x13E)==0 || S(0x13E)==3) { F(0xF4)=H[0]; F(0xF8)=H[1]; }
  if(S(0x13E)==2 || S(0x13E)==5) F(0x12C)=random_float(360);
  if(S(0x13E)==7) { B(0x184)=1; MOVE(); F(0x120)=F(0x11C)=static_cast<float>(random_float(40)*static_cast<double>(0.01f)+static_cast<double>(0.9f)); } return;
 case 821: {
  float payload[3]; B(0x17C)=9; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; MOVE(); payload[0]=0; payload[1]=0; payload[2]=1; SPAWN(821,-1); }
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==8) { F(0x12C)=H[0]; float product=random_float(25)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=0.2f; }
  if(S(0x13E)==4) { F(0x12C)=H[0]; float product=random_float(25)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==5 || S(0x13E)==8) { F(0x370)=0.2f; F(0x374)=0.4f; }
  if(S(0x13E)==6) { B(0x184)=1; MOVE(); } return;
 }
 case 848: SELECT(); if(S(0x13E)==2) F(0x12C)=H[0]; return;
 case 850:
  S(0x344)=1; SELECT(); if(S(0x13E)==0) B(0x184)=1;
  if(S(0x13E)==1) { MOVE(); float product=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x12C)=random_float(360); } return;
 case 851: SELECT(); if(S(0x13E)==0) { B(0x113)=0; B(0x112)=0; B(0x111)=0; } return;
 case 852: SELECT(); return;
 case 853:
  SELECT(); if(S(0x13E)==1) { MOVE(); float product=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x12C)=random_float(360); } return;
 case 854:
  SELECT(); if(S(0x13E)==0) B(0x113)=0;
  if(S(0x13E)==1) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+0.5); } return;
 case 855: {
  float payload[3]; SELECT();
  if(S(0x13E)==1) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(15)*static_cast<double>(0.1f)+1.0); F(0x370)=random_float(10); if(static_cast<unsigned>(selector_random_roll(100))<=50) F(0x370)=F(0x370)*-1.0; S(0x364)=selector_random_roll(35)+45; MOVE(); }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==3) { B(0x184)=1; MOVE(); }
  if(S(0x13E)==5) MOVE();
  if(S(0x13E)==6) { B(0x184)=1; payload[2]=8; for(float n=0;n<4;n+=1.0) { payload[0]=random_float(360); payload[1]=random_float(8)+4.0; SPAWN(855,1); } }
  if(S(0x13E)==7) { F(0x124)=random_float(360); F(0x128)=random_float(360); }
  if(S(0x13E)==8) { float product=random_float(100)*static_cast<double>(0.1f); F(0x370)=product-5.0; F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+1.0); } return;
 }
 case 856:
  SELECT(); if(S(0x13E)==0) B(0x184)=1; if(S(0x13E)==1) B(0x184)=1;
  if(S(0x13E)==2) { float product=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(product+0.5); F(0x12C)=random_float(360); B(0x113)=0; }
  if(S(0x13E)==3) { float product=random_float(20)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+static_cast<double>(0.8f)); F(0x12C)=random_float(360); MOVE(); } return;
 case 857: {
  float payload[3]; SELECT();
  if(S(0x13E)==0 || S(0x13E)==9) { B(0x184)=1; MOVE(); payload[0]=0; payload[1]=0; payload[2]=1; SPAWN(857,-1); }
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==8) { F(0x12C)=H[0]; float product=random_float(25)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=0.2f; }
  if(S(0x13E)==4) { F(0x12C)=H[0]; float product=random_float(25)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==5 || S(0x13E)==8 || S(0x13E)==10) { F(0x370)=0.2f; F(0x374)=0.4f; }
  if(S(0x13E)==6) { B(0x184)=1; MOVE(); } return;
 }
 case 858:
  SELECT(); if(S(0x13E)==0) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(75)*static_cast<double>(0.01f)+0.75); F(0x370)=random_float(50)*static_cast<double>(0.1f)-2.5; }
  if(S(0x13E)==4) F(0x12C)=H[0]; return;
 case 900:
  SELECT(); if(S(0x13E)==0) { F(0x11C)=0; F(0x120)=0; F(0x12C)=random_float(360); }
  if(S(0x13E)==1) F(0x12C)=random_float(360);
  if(S(0x13E)==2) { B(0x184)=1; MOVE(); } return;
 case 901:
  SELECT(); if(S(0x13E)==0) { F(0x11C)=0; F(0x120)=0; F(0x12C)=random_float(360); }
  if(S(0x13E)==1) F(0x12C)=random_float(360);
  if(S(0x13E)==2) { B(0x184)=1; MOVE(); } return;
 case 910: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; MOVE(); payload[0]=0; payload[1]=0; payload[2]=1; SPAWN(910,-1); }
  if(S(0x13E)==2 || S(0x13E)==3 || S(0x13E)==8) { F(0x12C)=H[0]; float product=random_float(25)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=0.2f; }
  if(S(0x13E)==4) { F(0x12C)=H[0]; float product=random_float(25)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==5 || S(0x13E)==8) { F(0x370)=0.2f; F(0x374)=0.4f; }
  if(S(0x13E)==6) { B(0x184)=1; MOVE(); } return;
 }
 case 920: SELECT(); if(S(0x13E)==2) { F(0x12C)=random_float(360); F(0x370)=random_float(10)-5.0; } return;
 case 921: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; MOVE(); SELECT();
  if(S(0x13E)==1) { payload[2]=3; for(float n=0;n<4;n+=1.0) { payload[0]=random_float(360); payload[1]=random_float(8)+4.0; SPAWN(921,1); } }
  if(S(0x13E)==2) { F(0x124)=random_float(360); F(0x128)=random_float(360); }
  if(S(0x13E)==3) { float product=random_float(100)*static_cast<double>(0.1f); F(0x370)=product-5.0; F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+1.0); }
  if(S(0x13E)==4) { F(0x120)=F(0x11C)=static_cast<float>(random_float(30)*static_cast<double>(0.01f)+static_cast<double>(0.85f)); B(0x184)=1; } return;
 }
 case 930:
  SELECT(); if(S(0x13E)==1) { F(0x370)=random_float(60)*static_cast<double>(0.1f)-3.0; F(0x120)=F(0x11C)=static_cast<float>(random_float(75)*static_cast<double>(0.01f)+1.0); F(0x12C)=random_float(360); }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); float product=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==4) { F(0x120)=F(0x11C)=3; B(0x113)=0; } return;
 case 940:
  F(0x12C)=H[0]; MOVE(); SELECT(); if(S(0x13E)<=2) B(0x184)=1;
  if(S(0x13E)==4) { float product=random_float(100)*static_cast<double>(0.1f); F(0x370)=product-5.0; F(0x12C)=random_float(360); double const delta=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(delta+H[3]); }
  if(S(0x13E)==5) { float product=random_float(100)*static_cast<double>(0.1f); F(0x370)=product-5.0; F(0x12C)=random_float(360); double const delta=random_float(10)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(delta+H[3]); }
  if(S(0x13E)==10) { F(0xF4)=0; F(0xF8)=0; F(0x120)=F(0x11C)=static_cast<float>(random_float(15)*static_cast<double>(0.1f)+0.5); if(T) { float *const input=H; F(0xEC)=lookup_orientation_cosine_quantized_abs(input[0])*input[1]+AT(T,float,0xEC); F(0xF0)=lookup_orientation_sine_quantized_abs(input[0])*H[1]+AT(T,float,0xF0); } }
  if(S(0x13E)==14) { B(0x184)=1; F(0x370)=0.55f; F(0x11C)=0.1f; F(0x120)=0.1f; }
  if(S(0x13E)==16) { B(0x113)=0; F(0x370)=0.4f; F(0x11C)=0.1f; F(0x120)=0.1f; }
  if(S(0x13E)==17) { B(0x184)=1; F(0x11C)=2; }
  if(S(0x13E)==18) { F(0x11C)=0.1f; F(0x120)=0.1f; } return;
 case 980: continue_action_980(); return;
 case 998: F(0x12C)=0; F(0x128)=60; return;
 case 999:
  SELECT(); if(S(0x13E)==0) { F(0x12C)=random_float(360); float product=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==1) { F(0x12C)=random_float(360); float product=random_float(50)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); F(0x370)=random_float(10)-5.0; } return;
 }
}
#undef SPAWN
#undef MOVE
#undef SELECT
#undef MOTION
#undef AT
#undef T
#undef H
#undef B
#undef S
#undef F
#undef FIELD
}
