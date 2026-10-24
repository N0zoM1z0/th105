// JP1.06a 0x005DF0E0: complete source.
// See docs/UDONGE_OBJECT_ENTRY_2026_10_24.md.
#include "characters/UdongeObjectActionEntry.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define H FIELD(float *,0x340)
#define P FIELD(UdongeObjectEntryView *,0x348)
#define A FIELD(UdongeObjectEntryView *,0x170)
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define MOTION reinterpret_cast<UdongeEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,l,c) spawn_parented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define UNSPAWN(a,l,c) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define SCALE(n,factor,base) F(0x120)=F(0x11C)=static_cast<float>(random_float(n)*static_cast<double>(factor)+static_cast<double>(base))
#define ROUND_SCALE(n,factor,base) { float const product=random_float(n)*static_cast<double>(factor); F(0x120)=F(0x11C)=static_cast<float>(product+static_cast<double>(base)); }
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void UdongeObjectEntryView::initialize_action_entry()
{
 // This live float shares the observed inner-index/result storage lifetime.
 float input_scale;
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0;
 F(0x37C)=0; S(0x384)=0; F(0x380)=0; S(0x386)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800: {
  float payload[3]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { payload[0]=F(0x12C); payload[1]=0; payload[2]=3; B(0x184)=1; SPAWN(800,-1,3); }
  if(S(0x13E)==1) { P->dispatch_character_wave_handle(2); F(0x12C)=random_float(360); SCALE(20,0.1f,0.8f); for(int n=0;n<5;++n) { payload[0]=random_float(360); payload[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+10)); payload[2]=2; UNSPAWN(800,1,3); } }
  if(S(0x13E)==2) { SCALE(50,0.01f,0.5); }
  if(S(0x13E)==3) F(0x11C)=2;
  if(S(0x13E)==4) { payload[0]=F(0x12C); payload[1]=0; payload[2]=3; B(0x184)=0; SPAWN(800,-1,3); B(0x113)=128; } return;
 }
 case 801:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0 || S(0x13E)==7) B(0x184)=1;
  if(S(0x13E)==1 || S(0x13E)==10 || S(0x13E)==12) F(0x120)=F(0x11C)=0.2f;
  if(S(0x13E)==2) F(0x370)=0.4f;
  if(S(0x13E)==3) { ROUND_SCALE(100,0.01f,1.0); }
  if(S(0x13E)==5 || S(0x13E)==6) { F(0x12C)=random_float(360); F(0x124)=30.0-random_float(60); F(0x128)=30.0-random_float(60); F(0x370)=random_float(8)+4.0; float const product=random_float(8)*static_cast<double>(0.01f); F(0x374)=product+static_cast<double>(0.04f); ROUND_SCALE(100,0.01f,1.0); } return;
 case 802: B(0x184)=1; return;
 case 810:
  B(0x17C)=0; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; F(0x12C)=H[0]; }
  if(S(0x13E)==1) F(0x120)=F(0x11C)=0.2f;
  if(S(0x13E)==2) { ROUND_SCALE(100,0.01f,1.0); }
  if(S(0x13E)==3) { SCALE(40,0.01f,0.8f); F(0x12C)=random_float(360); }
  if(S(0x13E)==4) { SCALE(40,0.01f,0.8f); F(0x124)=H[0]; F(0x128)=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)+45)); F(0x12C)=random_float(360); }
  if(S(0x13E)==5) F(0x12C)=random_float(360);
  if(S(0x13E)==7 || S(0x13E)==6) { F(0x12C)=random_float(360); F(0x124)=30.0-random_float(60); F(0x128)=30.0-random_float(60); F(0x370)=random_float(8)+4.0; float const product=random_float(15)*static_cast<double>(0.01f); F(0x374)=product+static_cast<double>(0.1f); ROUND_SCALE(100,0.01f,1.0); } return;
 case 811:
  B(0x17C)=4; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; F(0x12C)=H[0]; }
  if(S(0x13E)==1 || S(0x13E)==6) B(0x184)=1;
  if(S(0x13E)==3) { SCALE(40,0.01f,0.8f); F(0x124)=H[0]; F(0x128)=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)+45)); F(0x12C)=random_float(360); }
  if(S(0x13E)==4) F(0x12C)=random_float(360);
  if(S(0x13E)==8 || S(0x13E)==10 || S(0x13E)==11) { B(0x184)=1; F(0x120)=F(0x11C)=0.2f; }
  if(S(0x13E)==9) { ROUND_SCALE(100,0.01f,1.0); } return;
 case 812:
  B(0x17C)=8; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; MOVE(); }
  if(S(0x13E)==1) { B(0x184)=1; MOVE(); F(0xF8)=F(0xF8)*0.25; }
  if(S(0x13E)==3) B(0x184)=1;
  if(S(0x13E)==4) { SCALE(40,0.01f,0.8f); F(0x124)=H[0]; F(0x128)=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)+45)); F(0x12C)=random_float(360); }
  if(S(0x13E)==5) F(0x12C)=random_float(360);
  if(S(0x13E)==7) { SCALE(40,0.01f,0.8f); F(0x12C)=random_float(360); } return;
 case 815: {
  float payload[3]; B(0x17C)=1; B(0x184)=10; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x11C)=4; F(0x120)=3; payload[0]=0; payload[1]=0; payload[2]=3; SPAWN(815,1,3); } return;
 }
 case 816:
  B(0x17C)=5; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0 || S(0x13E)==4) F(0x11C)=35;
  if(S(0x13E)==1) B(0x184)=7; return;
 case 817:
  F(0x128)=60; B(0x17C)=9; F(0x124)=FIELD(signed char,0x104)*H[0]; B(0x17C)=9; SELECT();
  if(S(0x13E)==0) B(0x184)=1;
  if(S(0x13E)==1) B(0x184)=3;
  if(S(0x13E)==2) { F(0x11C)=H[3]; F(0x120)=H[3]; }
  if(S(0x13E)==3) { B(0x184)=1; goto input3_scales; } return;
 case 820: B(0x17C)=2; goto entry_820_821;
 case 821: B(0x17C)=6;
 entry_820_821:
  SELECT(); if(S(0x13E)==3) { input_scale=H[0]-static_cast<double>(0.3f); goto heading_scale; } return;
 case 822:
  B(0x17C)=10; F(0x12C)=random_float(360); SELECT();
  if(S(0x13E)==0) B(0x184)=10;
  if(S(0x13E)==1) { if(static_cast<unsigned>(selector_random_roll(100))>=50) F(0x128)=180; SCALE(60,0.01f,0.7f); }
  if(S(0x13E)==3) { float const product1=random_float(100)*static_cast<double>(0.01f); F(0x11C)=product1+0.5; float const product2=random_float(50)*static_cast<double>(0.01f); F(0x120)=product2+0.5; } return;
 case 825: {
  float payload[3]; B(0x17C)=3; F(0x12C)=H[0]; F(0x100)=0; S(0x36C)=AT(P,signed char,0x607); SELECT();
  if(S(0x13E)==2) { F(0xF4)=-4; F(0xF8)=12.5f; F(0x100)=0.45f; }
  if(S(0x13E)==8) { payload[0]=F(0x12C); payload[1]=0; payload[2]=3; B(0x184)=1; SPAWN(800,-1,3); }
  if(S(0x13E)==9) B(0x184)=1;
  if(S(0x13E)==10) F(0x120)=F(0x11C)=0.2f; return;
 }
 case 826:
  F(0x100)=0; B(0x17C)=7; SELECT();
  if(S(0x13E)==1) B(0x184)=1;
  if(S(0x13E)<=4) { F(0x108)=0; F(0x10C)=80; }
  if(S(0x13E)==5) F(0x370)=0.71f;
  F(0x12C)=-H[0]*FIELD(signed char,0x104); return;
 case 848:
  SELECT(); if(S(0x13E)<=2) set_sequence_frame(static_cast<short>(H[1]));
  if(S(0x13E)==3) { F(0xF4)=12; F(0xF8)=7; }
  if(S(0x13E)==5) { F(0xF4)=H[0]; F(0xF8)=H[1]; } return;
 case 849: SELECT(); return;
 case 850: {
  float payload[3]; F(0x128)=60; SELECT();
  if(S(0x13E)==0) { B(0x184)=5; payload[1]=0; payload[2]=1; for(float n=0;n<4;n+=1.0) { payload[0]=n*90.0; SPAWN(850,1,3); } }
  if(S(0x13E)==2) { F(0x11C)=H[3]; F(0x120)=H[3]; } return;
 }
 case 852:
  SELECT(); if(S(0x13E)==0) { B(0x184)=1; F(0x12C)=H[0]; }
  if(S(0x13E)==1) F(0x120)=F(0x11C)=0.2f;
  if(S(0x13E)==2) { ROUND_SCALE(100,0.01f,1.0); }
  if(S(0x13E)==3) { SCALE(40,0.01f,0.8f); F(0x12C)=random_float(360); }
  if(S(0x13E)==4) { SCALE(40,0.01f,0.8f); F(0x124)=H[0]; F(0x128)=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)+45)); F(0x12C)=random_float(360); }
  if(S(0x13E)==5) F(0x12C)=random_float(360); return;
 case 853: {
  float payload[3]; F(0x128)=60; SELECT();
  if(S(0x13E)==0) { payload[1]=0; payload[2]=1; payload[0]=0; B(0x184)=1; SPAWN(853,1,3); }
  if(S(0x13E)==2) { input3_scales: F(0x11C)=H[3]; F(0x120)=H[3]; } return;
 }
 case 855: B(0x184)=1; SELECT(); return;
 case 856: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { payload[0]=0; payload[1]=0; payload[2]=2; B(0x184)=1; UNSPAWN(856,1,3); }
  if(S(0x13E)==2) F(0x370)=0.3f;
  if(S(0x13E)>=3 && S(0x13E)<=6) { F(0x12C)=random_float(360); F(0x370)=3.0-random_float(6); ROUND_SCALE(10,0.1f,0.5); MOVE(); }
  if(S(0x13E)==7) { ROUND_SCALE(10,0.1f,0.5); }
  if(S(0x13E)==8) { ROUND_SCALE(4,0.1f,0.8f); F(0x12C)=random_float(360); if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 }
 case 857: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { payload[0]=0; payload[1]=0; payload[2]=2; B(0x184)=1; UNSPAWN(857,1,3); for(int n=0;n<6;++n) { payload[0]=random_float(360); payload[1]=0; payload[2]=12; UNSPAWN(857,1,3); } }
  if(S(0x13E)==2) F(0x370)=0.4f;
  if(S(0x13E)>=3 && S(0x13E)<=6) { F(0x12C)=random_float(360); F(0x370)=3.0-random_float(6); ROUND_SCALE(10,0.1f,0.5); MOVE(); }
  if(S(0x13E)==7) { ROUND_SCALE(10,0.1f,0.5); }
  if(S(0x13E)==8) { ROUND_SCALE(4,0.1f,0.8f); F(0x12C)=random_float(360); if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; }
  if(S(0x13E)==9) B(0x184)=1;
  if(S(0x13E)==10) { F(0x12C)=H[0]; F(0x128)=75; }
  if(S(0x13E)==11) F(0x12C)=random_float(360);
  if(S(0x13E)==12) { F(0x12C)=H[0]; float const product1=random_float(5)*static_cast<double>(0.1f); F(0x11C)=product1+1.0; float const product2=random_float(10)*static_cast<double>(0.1f); F(0x120)=product2+1.0; } return;
 }
 case 858:
  SELECT(); switch(S(0x13E)) {
   case 0: MOVE(); return;
   case 1: return;
   case 2: F(0x12C)=random_float(360); SCALE(50,0.01f,1.0); F(0x370)=random_float(20)*static_cast<double>(0.1f)-1.0; return;
   case 3: F(0x120)=F(0x11C)=3; B(0x113)=0; return;
  } return;
 case 859: {
  float payload[3]; SELECT(); switch(S(0x13E)) {
   case 0: F(0x12C)=random_float(360); return;
   case 1: F(0x12C)=random_float(360); SCALE(50,0.01f,1.0); F(0x128)=random_float(60)-30.0; F(0x124)=random_float(60)-30.0; if(static_cast<unsigned>(selector_random_roll(100))>=50) F(0x128)=F(0x128)+180.0; return;
   case 3: SCALE(100,0.01f,1.0); F(0x12C)=random_float(360); return;
   case 4: B(0x113)=static_cast<signed char>(AT(P,float,0x7B4))*60; return;
   case 5: F(0x11C)=0.05f; return;
   case 6:
    payload[0]=0; payload[1]=0; payload[2]=7; B(0x184)=1; UNSPAWN(859,1,3); UNSPAWN(859,1,3); UNSPAWN(859,1,3);
    for(float n=0;n<4;++n) { float const angle=random_float(40)-n*60.0-20.0; for(input_scale=0;input_scale<8;++input_scale) { payload[0]=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)))+static_cast<double>(angle)-15.0; payload[1]=random_float(6)+input_scale*7.0+12.0; payload[2]=10; UNSPAWN(859,1,3); } } return;
   case 7: F(0x12C)=random_float(360); SCALE(50,0.01f,1.0); F(0x128)=random_float(60)-30.0; F(0x124)=random_float(60)-30.0; if(static_cast<unsigned>(selector_random_roll(100))>=50) F(0x128)=F(0x128)+180.0; return;
   case 10: SCALE(10,0.1f,1.0); F(0x12C)=random_float(360); F(0x370)=20.0-random_float(10); return;
  } return;
 }
 case 900: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; F(0x12C)=H[0]; payload[0]=0; payload[1]=0; payload[2]=5; UNSPAWN(900,1,3); }
  if(S(0x13E)==1) F(0x120)=F(0x11C)=0.2f;
  if(S(0x13E)==2) { ROUND_SCALE(100,0.01f,1.0); }
  if(S(0x13E)==3) { SCALE(40,0.01f,0.8f); F(0x12C)=random_float(360); }
  if(S(0x13E)==4) { SCALE(40,0.01f,0.8f); F(0x124)=H[0]; F(0x128)=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)+45)); F(0x12C)=random_float(360); }
  if(S(0x13E)==5) F(0x12C)=random_float(360);
  if(S(0x13E)==7 || S(0x13E)==6) { F(0x12C)=random_float(360); F(0x124)=30.0-random_float(60); F(0x128)=30.0-random_float(60); F(0x370)=random_float(8)+4.0; float const product=random_float(15)*static_cast<double>(0.01f); F(0x374)=product+static_cast<double>(0.1f); ROUND_SCALE(100,0.01f,1.0); }
  if(S(0x13E)==8) { F(0x12C)=random_float(360); F(0x370)=random_float(10)-5.0; } return;
 }
 case 910: {
  float payload[3]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1) { P->dispatch_character_wave_handle(2); F(0x12C)=random_float(360); SCALE(20,0.1f,0.8f); for(int n=0;n<5;++n) { payload[0]=random_float(360); payload[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+10)); payload[2]=2; UNSPAWN(800,1,3); } }
  if(S(0x13E)==2) { SCALE(50,0.01f,0.5); }
  if(S(0x13E)==3) F(0x11C)=2;
  if(S(0x13E)==4) { payload[0]=F(0x12C); payload[1]=0; payload[2]=3; B(0x184)=0; SPAWN(910,-1,3); payload[2]=1; UNSPAWN(910,-1,3); B(0x113)=128; } return;
 }
 case 911:
  SELECT(); if(S(0x13E)==0) { F(0x374)=-atan2_degrees(static_cast<float>(AT(A,float,0xF0)+100.0-F(0xF0)),static_cast<float>((AT(A,float,0xEC)-F(0xEC))*FIELD(signed char,0x104))); }
  if(S(0x13E)==3) { F(0x12C)=random_float(360); input_scale=H[0]-static_cast<double>(0.3f); heading_scale: B(0x113)=0; F(0x120)=F(0x11C)=input_scale; } return;
 case 912:
  F(0x12C)=H[0]; SELECT(); if(S(0x13E)==0 || S(0x13E)==4) F(0x11C)=35; return;
 case 920: {
  float payload[3]; SELECT();
  if(S(0x13E)==1) { MOVE(); B(0x113)=192; }
  if(S(0x13E)==14) { P->dispatch_character_wave_handle(2); F(0x12C)=H[0]; MOVE(); payload[0]=F(0x12C); payload[1]=0; payload[2]=15; B(0x184)=1; UNSPAWN(920,1,3); payload[0]=F(0x12C); payload[1]=0; payload[2]=17; SPAWN(920,-1,3); }
  if(S(0x13E)==15) { F(0x12C)=random_float(360); SCALE(20,0.1f,0.8f); for(int n=0;n<2;++n) { payload[0]=random_float(360); payload[1]=static_cast<float>(static_cast<unsigned>(selector_random_roll(15)+10)); payload[2]=16; UNSPAWN(920,1,3); } }
  if(S(0x13E)==16) { SCALE(50,0.01f,0.5); }
  if(S(0x13E)==17) F(0x11C)=2; return;
 }
 case 980: continue_action_980(); return;
 case 998: return;
 }
}
}
