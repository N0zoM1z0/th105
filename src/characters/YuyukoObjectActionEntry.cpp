// JP1.06a 0x00578000: complete nonexact source.
// See docs/YUYUKO_OBJECT_ENTRY_2026_10_24.md.
#include "characters/YuyukoObjectActionEntry.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define P FIELD(YuyukoObjectEntryView *,0x348)
#define T FIELD(YuyukoObjectEntryView *,0x34C)
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define MOTION reinterpret_cast<YuyukoEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,l,c) spawn_parented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define UNSPAWN(a,l,c) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define SCALE(n,factor,base) F(0x120)=F(0x11C)=static_cast<float>(random_float(n)*static_cast<double>(factor)+static_cast<double>(base))
#define ROUND_SCALE(n,factor,base) { float const product=random_float(n)*static_cast<double>(factor); F(0x120)=F(0x11C)=static_cast<float>(product+static_cast<double>(base)); }
#define JITTER() { float const product=random_float(100)*static_cast<double>(0.1f); F(0x370)=product-5.0; }
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void YuyukoObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0;
 S(0x384)=0; F(0x37C)=0; S(0x386)=0; F(0x380)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { F(0x120)=F(0x11C)=0.1f; payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; SPAWN(800,-1,3); }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)>=12 && S(0x13E)<=15) { payload[0]=0; payload[1]=0; payload[2]=S(0x13E)-4; SPAWN(800,-1,3); } return;
 }
 case 801:
  SELECT();
  if(S(0x13E)==1) { MOVE(); B(0x184)=1; }
  if(S(0x13E)==2) { F(0xF8)=F(0xF0); F(0xF4)=0; }
  if(S(0x13E)==3) B(0x184)=3;
  if(S(0x13E)==4) F(0xF8)=2;
  if(S(0x13E)==5) { MOVE(); B(0x184)=1; } return;
 case 810: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; B(0x17C)=0; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; SPAWN(810,-1,3); }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)==13) F(0xF8)=5; return;
 }
 case 811: {
  float payload[3]; F(0x12C)=H[0]; B(0x17C)=4; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; SPAWN(811,1,3); }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)>=8 && S(0x13E)<=11) { B(0x184)=1; F(0x370)=F(0xEC); F(0x374)=F(0xF0); F(0x11C)=0; F(0x120)=2; }
  if(S(0x13E)==13) F(0xF8)=5;
  if(S(0x13E)==14) {
   if(AT(P,signed char,0x608)<=1) {
    for(float n=0;n<3;n+=1.0) { payload[0]=n*15.0-H[0]; payload[1]=20; payload[2]=n; SPAWN(811,1,3); } S(0x36C)=3;
   } else if(AT(P,signed char,0x608)<=3) {
    for(float n=0;n<4;n+=1.0) { payload[0]=n*15.0-H[0]; payload[1]=20; payload[2]=n; SPAWN(811,1,3); } S(0x36C)=4;
   } else {
    for(float n=0;n<5;n+=1.0) { payload[0]=n*15.0-H[0]; payload[1]=20; payload[2]=static_cast<int>(n)%4; SPAWN(811,1,3); } S(0x36C)=5;
   }
  } return;
 }
 case 812:
  F(0x12C)=H[0]; B(0x17C)=8; SELECT();
  if(S(0x13E)==1 || S(0x13E)==4 || S(0x13E)==5) B(0x184)=1;
  if(S(0x13E)==2) { JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)==3) { SCALE(10,0.1f,0.5); } return;
 case 815:
  B(0x184)=5; B(0x17C)=1; SELECT();
  if(S(0x13E)==1) { F(0x11C)=10; F(0x120)=0.1f; } return;
 case 816: {
  float payload[3]; B(0x184)=1; B(0x17C)=5; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { SCALE(4,0.1f,0.8f); payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; SPAWN(816,-1,3); }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  // The first request leaves payload[1] untouched in the original frame.
  if(S(0x13E)==12) { MOVE(); payload[0]=0; payload[2]=13; UNSPAWN(816,1,3); payload[1]=0.5f; payload[2]=14; UNSPAWN(816,1,3); }
  if(S(0x13E)==15) F(0x120)=F(0x11C)=H[1];
  if(S(0x13E)==16) { B(0x113)=0; B(0x184)=0; F(0x12C)=H[0]+180.0; payload[0]=0; payload[1]=0; payload[2]=8; SPAWN(816,-1,3); } return;
 }
 case 820:
  B(0x17C)=2; B(0x184)=3; F(0x370)=AT(P,float,0xEC)+FIELD(signed char,0x104)*50; F(0x374)=AT(P,float,0xF0)+170.0; F(0x378)=1; SELECT();
  if(S(0x13E)==3) F(0xF8)=5; return;
 case 821:
  B(0x17C)=6; SELECT();
  if(S(0x13E)==0) MOVE();
  if(S(0x13E)==1) { F(0x370)=255; B(0x184)=1; MOVE(); }
  if(S(0x13E)==3) { float *const input=H; F(0xEC)=lookup_orientation_cosine_quantized_abs(input[0])*input[1]+AT(T,float,0xEC); F(0xF0)=lookup_orientation_sine_quantized_abs(input[0])*H[1]+AT(T,float,0xF0); ROUND_SCALE(10,0.1f,0.5); } return;
 case 825:
  SELECT(); if(S(0x13E)==0) { F(0x124)=40; F(0x128)=FIELD(signed char,0x104)*-40; F(0x12C)=random_float(360); }
  if(S(0x13E)==1) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); } return;
 case 826: {
  float payload[3]; F(0x12C)=H[0]; B(0x17C)=7; SELECT();
  if(S(0x13E)==0) { for(int n=0;n<8;++n) { payload[0]=random_float(360); payload[1]=random_float(50)*static_cast<double>(0.1f)+5.0; payload[2]=1; UNSPAWN(826,1,3); } return; }
  if(S(0x13E)>=1 && S(0x13E)<=4) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); } return;
 }
 case 848:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==3) F(0x124)=FIELD(signed char,0x104)*60;
  if(S(0x13E)==4) F(0x124)=FIELD(signed char,0x104)*20;
  if(S(0x13E)==10) { F(0x370)=F(0xEC)-AT(P,float,0xEC); F(0x374)=F(0xF0)-AT(P,float,0xF0); F(0xF4)=25; F(0xF8)=-3; }
  if(S(0x13E)==11) { ROUND_SCALE(5,0.1f,0.75); }
  if(S(0x13E)==12) F(0x124)=FIELD(signed char,0x104)*70; return;
 case 850: {
  float payload[3]; B(0x184)=1; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; SPAWN(850,1,3); H[0]=H[0]+30.0; F(0x370)=2; }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  F(0x12C)=H[0]; return;
 }
 case 851:
  SELECT();
  if(S(0x13E)==1) { replace_secondary(990,20,10,1,2); F(0xF4)=H[1]; B(0x184)=1; I(0x144)=static_cast<short>(selector_random_roll(360)); ROUND_SCALE(50,0.01f,1.0); F(0x374)=random_float(5)+3.0; }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); ROUND_SCALE(50,0.01f,1.0); }
  if(S(0x13E)==4) { F(0x120)=F(0x11C)=0; F(0x370)=1; } return;
 case 852:
  SELECT(); if(S(0x13E)==0) B(0x184)=1;
  if(S(0x13E)==1) { F(0x12C)=random_float(360); ROUND_SCALE(50,0.01f,1.0); }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); ROUND_SCALE(50,0.01f,1.0); }
  if(S(0x13E)==3) { ROUND_SCALE(100,0.01f,1.0); S(0x364)=selector_random_roll(180)+60; F(0x370)=random_float(360); float const product=random_float(20)*static_cast<double>(0.1f); F(0x374)=product+1.0; if(static_cast<unsigned>(selector_random_roll(100))<50) F(0x374)=F(0x374)*-1.0; B(0x113)=0; }
  if(S(0x13E)==4) B(0x113)=0; return;
 case 853: {
  float payload[3]; B(0x184)=1; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; SPAWN(853,1,3); H[0]=H[0]+30.0; F(0x370)=2; }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  F(0x12C)=H[0]; return;
 }
 case 854:
  SELECT();
  if(S(0x13E)==1) { float const width=random_float(10)+10.0; int const divisions=selector_random_roll(10)+5; replace_secondary(990,width,divisions,1,2); F(0xF8)=H[1]; B(0x184)=1; I(0x144)=static_cast<short>(selector_random_roll(360)); ROUND_SCALE(100,0.01f,1.0); F(0x374)=random_float(5)+3.0; }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); ROUND_SCALE(50,0.01f,1.0); }
  if(S(0x13E)==3) { F(0x12C)=random_float(360); if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==4) { F(0x120)=F(0x11C)=0; F(0x370)=1; }
  if(S(0x13E)==5) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)==5) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); } return;
 case 855:
  SELECT(); if(S(0x13E)==0) B(0x184)=1;
  if(S(0x13E)==1) { F(0x12C)=random_float(360); ROUND_SCALE(50,0.01f,1.0); }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); ROUND_SCALE(50,0.01f,1.0); }
  if(S(0x13E)==3) { F(0x370)=random_float(360); float const product=random_float(20)*static_cast<double>(0.1f); F(0x374)=product+1.0; F(0x378)=200; if(static_cast<unsigned>(selector_random_roll(100))<50) F(0x374)=F(0x374)*-1.0; B(0x113)=0; }
  if(S(0x13E)==4) B(0x113)=0;
  if(S(0x13E)==5) { JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)==6) { MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)==7) B(0x184)=1;
  if(S(0x13E)==9) { JITTER(); MOVE(); SCALE(15,0.1f,1.0); } return;
 case 856: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; SPAWN(856,-1,3); }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)==13) F(0xF8)=5; return;
 }
 case 857: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { SCALE(4,0.1f,0.8f); payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; SPAWN(816,-1,3); }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); }
  if(S(0x13E)==12) { MOVE(); for(float n=0;n<6;n+=1.0) { payload[0]=static_cast<float>(static_cast<unsigned>(selector_random_roll(20)))+static_cast<double>(H[0])-10.0; payload[1]=random_float(20)+10.0; payload[2]=0; UNSPAWN(857,-1,3); } payload[0]=0; payload[2]=13; UNSPAWN(857,-1,3); payload[1]=0.5f; payload[2]=15; UNSPAWN(857,1,3); }
  if(S(0x13E)==14) { F(0x120)=F(0x11C)=0.1f; S(0x344)=1; F(0x370)=1; F(0x10C)=200; } return;
 }
 case 858:
  SELECT();
  if(S(0x13E)==1) { F(0x378)=1; F(0x370)=F(0xEC); F(0x374)=F(0xF0); B(0x184)=1; float *const input=H; F(0xEC)=lookup_orientation_cosine_quantized_abs(input[0]+S(0x36C)*4)*input[1]*FIELD(signed char,0x104)+F(0x370); F(0xF0)=lookup_orientation_sine_quantized_abs(input[0]+S(0x36C)*4)*H[1]+F(0x374); }
  if(S(0x13E)==3) { F(0xF8)=5; F(0x12C)=random_float(360); SCALE(4,0.1f,0.8f); } return;
 case 900:
  F(0x370)=AT(P,float,0xEC)+FIELD(signed char,0x104)*50; F(0x374)=AT(P,float,0xF0)+170.0; F(0x378)=1; SELECT();
  if(S(0x13E)==0) B(0x113)=0;
  if(S(0x13E)==3) F(0xF8)=5;
  if(S(0x13E)==4) B(0x113)=0;
  if(S(0x13E)==5) F(0x12C)=random_float(360); return;
 case 901:
  B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==3) F(0xF8)=5;
  if(S(0x13E)==5) F(0x12C)=random_float(360); return;
 case 902: {
  float payload[3]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)>=0 && S(0x13E)<=3) { payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+8; B(0x184)=1; SPAWN(902,-1,3); }
  if(S(0x13E)>=4 && S(0x13E)<=7) { JITTER(); JITTER(); MOVE(); SCALE(10,0.1f,0.5); } return;
 }
 case 920:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x370)=F(0xEC); F(0x374)=F(0xF0); float *const input=H; F(0xEC)=lookup_orientation_cosine_quantized_abs(-input[0])*input[1]*FIELD(signed char,0x104)+F(0x370); F(0xF0)=lookup_orientation_sine_quantized_abs(-input[0])*H[1]+F(0x374); B(0x113)=0; } return;
 case 922:
  SELECT(); if(S(0x13E)==0) { F(0x120)=F(0x11C)=0.05f; F(0x108)=0; F(0x10C)=100; F(0x374)=F(0x370)=1; }
  if(S(0x13E)==1) { F(0x370)=0.4f; F(0x108)=0; F(0x10C)=100; }
  if(S(0x13E)==3) { SCALE(15,0.1f,0.5); }
  if(S(0x13E)==4) { F(0x370)=0.6f; F(0x12C)=random_float(360); } return;
 case 980: continue_action_980(); return;
 case 998: F(0x12C)=0; F(0x128)=60; return;
 }
}
}
