#include "characters/MarisaObjectActionEntry.hpp"
// JP1.06a 0x004C8050: complete nonexact source.
// Evidence: docs/MARISA_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define P FIELD(MarisaObjectEntryView *,0x348)
#define T FIELD(MarisaObjectEntryView *,0x34C)
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define A(t,o) AT(FIELD(void *,0x154),t,o)
#define MOTION reinterpret_cast<MarisaEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define FRAME() select_frame(static_cast<int>(H[3]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,l,c) spawn_parented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define UNSPAWN(a,l,c) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
__forceinline static float modulo_float(unsigned n) { return static_cast<float>(mt19937_next_u32()%n); }
void MarisaObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0; F(0x37C)=0;
 S(0x384)=0; F(0x380)=0; S(0x386)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800:
  F(0x120)=F(0x11C)=2; B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)>1 && S(0x13E)<6) F(0x120)=F(0x11C)=1;
  if(S(0x13E)==7) { F(0x120)=F(0x11C)=static_cast<float>(random_float(200)*static_cast<double>(0.01f)+2.0); F(0x12C)=random_float(360); float const magnitude=random_float(15)*static_cast<double>(0.1f)+10.0; H[1]=magnitude; } return;
 case 801:
  B(0x184)=1; SELECT();
  if(S(0x13E)==0) replace_secondary(989,20,6,2,2);
  if(S(0x13E)==1) replace_secondary(989,20,6,2,2);
  if(S(0x13E)==2) { unsigned const roll=selector_random_roll(80); F(0x12C)=static_cast<float>(roll)+H[0]-40.0; }
  if(S(0x13E)==3) B(0x184)=3;
  if(S(0x13E)==4) B(0x184)=5;
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=static_cast<float>(random_float(200)*static_cast<double>(0.01f)+2.0); F(0x12C)=random_float(360); float const magnitude=random_float(15)*static_cast<double>(0.1f)+10.0; H[1]=magnitude; unsigned const heading=selector_random_roll(360); H[0]=static_cast<float>(heading); } return;
 case 802:
  B(0x184)=1; SELECT(); if(S(0x13E)==0) { F(0xF4)=6; F(0xF8)=12.5f; }
  if(S(0x13E)==2) { F(0x370)=random_float(10)-5.0; F(0x120)=F(0x11C)=static_cast<float>(random_float(200)*static_cast<double>(0.01f)+1.0); F(0x12C)=random_float(360); float const magnitude=random_float(15)*static_cast<double>(0.1f)+15.0; H[1]=magnitude; unsigned const heading=selector_random_roll(360); H[0]=static_cast<float>(heading); }
  if(S(0x13E)==3) { F(0x370)=random_float(10)-5.0; F(0x120)=F(0x11C)=static_cast<float>(random_float(200)*static_cast<double>(0.01f)+1.0); F(0x12C)=random_float(360); float const magnitude=random_float(15)*static_cast<double>(0.1f)+15.0; H[1]=magnitude; unsigned const heading=selector_random_roll(360); H[0]=static_cast<float>(heading); } return;
 case 803: F(0x108)=-40; B(0x184)=10; return;
 case 804: B(0x184)=1; return;
 case 809: F(0x11C)=H[1]; F(0x120)=H[1]; B(0x113)=128; SELECT(); F(0x12C)=H[0]; return;
 case 810: F(0x12C)=random_float(360); SELECT(); F(0x120)=F(0x11C)=static_cast<float>(random_float(50)*static_cast<double>(0.01f)+0.5); return;
 case 811: {
  float payload[4]; B(0x17C)=4; SELECT();
  if(S(0x13E)==0) {
   F(0x370)=5; B(0x184)=1;
   for(int n=0;n<16;++n) { payload[0]=80.0-random_float(160); payload[1]=random_float(250)*static_cast<double>(0.1f)+10.0; payload[2]=3; payload[3]=random_float(45); UNSPAWN(811,1,4); }
   payload[0]=0; payload[1]=0; payload[2]=4; payload[3]=0; UNSPAWN(811,1,4); MOVE(); F(0x12C)=H[0];
  }
  if(S(0x13E)==2) F(0x370)=1;
  if(S(0x13E)==3) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(100)*static_cast<double>(0.04f)+1.0); F(0x370)=random_float(20)-10.0; F(0x374)=random_float(20)+5.0; }
  if(S(0x13E)==4) F(0x370)=1;
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=static_cast<float>(modulo_float(100)*static_cast<double>(0.01f)+1.0); F(0x12C)=modulo_float(360); } return;
 }
 case 812: B(0x17C)=8; B(0x184)=4; SELECT(); return;
 case 817:
  B(0x17C)=9; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; MOVE(); }
  if(S(0x13E)==1 || S(0x13E)==6) B(0x184)=6;
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=static_cast<float>(modulo_float(100)*static_cast<double>(0.01f)+1.0); F(0x12C)=modulo_float(360); } return;
 case 820: {
  float payload[3]; B(0x17C)=2; B(0x184)=1; SELECT();
  if(S(0x13E)==0) { F(0xF8)=10; F(0xF4)=H[0]; payload[0]=0; payload[1]=0; payload[2]=7; SPAWN(820,-1,3); }
  if(S(0x13E)==1) { F(0xF8)=-25; F(0xF4)=5; payload[0]=0; payload[1]=0; payload[2]=7; SPAWN(820,-1,3); }
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=static_cast<float>(modulo_float(100)*static_cast<double>(0.01f)+1.0); F(0x12C)=modulo_float(360); } return;
 }
 case 821: {
  float payload[1]; B(0x17C)=6; B(0x184)=1; select_sequence(static_cast<int>(H[0]));
  if(S(0x13E)<=2) { F(0xF4)=6; F(0xF8)=4.5f; }
  if(S(0x13E)==5) { F(0xF8)=H[1]; payload[0]=7; UNSPAWN(821,1,1); payload[0]=8; UNSPAWN(821,-1,1); }
  if(S(0x13E)==6) F(0xF8)=0; return;
 }
 case 822: {
  float payload[3]; B(0x17C)=10; SELECT(); S(0x384)=0;
  if(S(0x13E)<=5) { payload[0]=0; payload[1]=0; payload[2]=12; SPAWN(822,-1,3); } else F(0x12C)=H[0];
  if(S(0x13E)==6) { B(0x184)=1; payload[0]=H[0]; payload[1]=0; payload[2]=7; SPAWN(822,-1,3); payload[2]=8; SPAWN(822,-1,3); } return;
 }
 case 825:
  B(0x17C)=3; B(0x184)=1; SELECT(); if(S(0x13E)<=3) replace_secondary(static_cast<unsigned short>(S(0x13E))+991,20,6,2,2); S(0x364)=0; return;
 case 826:
  B(0x17C)=7; B(0x184)=15; SELECT();
  if(S(0x13E)==0) { F(0x108)=-60; F(0x10C)=0; F(0x120)=1.2f; }
  if(S(0x13E)==6) { F(0x108)=-60; F(0x10C)=0; F(0x120)=1.8f; } return;
 case 827:
  F(0x374)=255; B(0x17C)=11; SELECT(); I(0x180)=0;
  if(S(0x13E)==6) B(0x184)=1;
  if(S(0x13E)==1) { F(0x11C)=0; F(0x120)=0; }
  if(S(0x13E)==5) { float product=random_float(150)*static_cast<double>(0.01f); F(0x120)=F(0x11C)=static_cast<float>(product+1.0); } return;
 case 848:
  F(0x12C)=H[0]; SELECT(); if(S(0x13E)==2) { F(0x12C)=H[0]; if(static_cast<unsigned>(selector_random_roll(100))<=49) F(0x374)=1; else F(0x374)=-1; } return;
 case 849:
  F(0x12C)=H[0]; SELECT(); if(S(0x13E)==2) F(0x120)=F(0x11C)=2;
  if(S(0x13E)==3 || S(0x13E)==4 || S(0x13E)==5) { B(0x17C)=5; B(0x184)=5; } return;
 case 850: B(0x184)=1; F(0x11C)=3; F(0x120)=1.5f; SELECT(); if(S(0x13E)==2) F(0x120)=F(0x11C)=2; return;
 case 851: F(0x11C)=10; F(0x120)=0; SELECT(); if(S(0x13E)==2) F(0x120)=F(0x11C)=2; return;
 case 852:
  F(0x11C)=4; F(0x120)=0; F(0x12C)=-30; SELECT(); if(S(0x13E)==2) F(0x120)=F(0x11C)=3;
  if(S(0x13E)==5) { F(0x11C)=1; F(0x120)=1; F(0x124)=modulo_float(20)-50.0; F(0x128)=modulo_float(20)+50.0; F(0x12C)=modulo_float(360); } return;
 case 853:
  F(0x11C)=4; F(0x120)=0; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0 || S(0x13E)==4) { replace_auxiliary(995); A(float,0xF8)=22; A(float,0xFC)=22; A(float,0xE8)=640; A(float,0xEC)=0; A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==2) F(0x120)=F(0x11C)=3;
  if(S(0x13E)==5) { F(0x11C)=1; F(0x120)=1; F(0x124)=FIELD(signed char,0x104)*H[0]; F(0x128)=modulo_float(20)+50.0; F(0x12C)=modulo_float(360); }
  if(S(0x13E)==10) { S(0x344)=1; F(0x370)=1; F(0x11C)=0; F(0x120)=0; F(0x124)=75; }
  if(S(0x13E)==11) { S(0x344)=1; F(0x120)=F(0x11C)=H[1]; F(0x124)=75; } return;
 case 854: F(0x11C)=10; B(0x184)=1; F(0x120)=1; F(0x12C)=H[0]; return;
 case 855: F(0x11C)=2; B(0x184)=1; F(0x120)=1; return;
 case 856: SELECT(); if(S(0x13E)==6) { I(0x180)=0; B(0x184)=1; } return;
 case 857: F(0x12C)=H[0]; SELECT(); return;
 case 858: S(0x344)=1; SELECT(); if(S(0x13E)==4) { B(0x184)=1; I(0x180)=0; } if(S(0x13E)==5) F(0x12C)=modulo_float(360); return;
 case 859: {
  float payload[4]; if(static_cast<unsigned>(selector_random_roll(100))<=50) F(0x370)=8; else F(0x370)=-8; SELECT(); FRAME();
  if(S(0x13E)<4) {
   if(S(0x140)==0) { F(0x12C)=random_float(360); payload[0]=0; payload[1]=0; payload[2]=4; payload[3]=S(0x13E); B(0x184)=1; I(0x180)=0; P->spawn_owned(859,F(0xEC),F(0xF0),B(0x104),1,reinterpret_cast<const unsigned *>(payload),4); }
   if(S(0x13E)<4 && S(0x140)==1) F(0x12C)=H[0];
  } return;
 }
 case 860: {
  float payload[4]; SELECT(); FRAME();
  if(S(0x13E)==0) { F(0x370)=5; payload[0]=0; payload[1]=0; payload[2]=3; payload[3]=0; B(0x184)=6; UNSPAWN(860,1,4); payload[2]=4; payload[3]=0; SPAWN(860,1,4); }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(100)*static_cast<double>(0.01f)+0.5); unsigned const heading=selector_random_roll(360); H[0]=static_cast<float>(heading); unsigned const magnitude=selector_random_roll(30)+10; H[1]=static_cast<float>(magnitude); F(0x370)=random_float(20)-10.0; F(0x374)=random_float(20)+5.0; }
  if(S(0x13E)==4) F(0x370)=5; return;
 }
 case 861:
  SELECT(); FRAME(); if(S(0x13E)<4) {
   if(S(0x140)==0) { F(0x12C)=random_float(360); B(0x184)=1; I(0x180)=0; S(0x364)=0; }
   if(S(0x13E)<4 && S(0x140)==1) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(100)*static_cast<double>(0.01f)+0.5); }
  } if(S(0x13E)==5) F(0x370)=0.75f; return;
 case 863: {
  float payload[4]; SELECT();
  if(S(0x13E)==0) { F(0xF8)=10; F(0xF4)=((AT(AT(P,void *,0x170),float,0xEC)-F(0xEC))/50.0)*FIELD(signed char,0x104); }
  if(S(0x13E)==1) { F(0xF8)=-25; F(0xF4)=5; }
  if(S(0x13E)==3) {
   I(0x180)=0; F(0x370)=1; B(0x184)=1;
   for(int n=0;n<3;++n) { payload[0]=-modulo_float(180); payload[1]=modulo_float(50)*static_cast<double>(0.1f)+15.0; payload[2]=5; payload[3]=random_float(15); if(payload[0]<0) S(0x364)=1; else S(0x364)=-1; spawn_unparented(863,static_cast<float>(static_cast<int>(FIELD(signed char,0x104)*I(0x144)*20)+F(0xEC)),F(0xF0),B(0x104),B(0x364),reinterpret_cast<const unsigned *>(payload),4); }
  }
  if(S(0x13E)==4) F(0x370)=1;
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=static_cast<float>(modulo_float(100)*static_cast<double>(0.01f)+1.0); F(0x12C)=modulo_float(360); } return;
 }
 case 865:
  SELECT(); if(S(0x13E)==8) { double const heading=H[0]; B(0x184)=1; F(0x12C)=heading; }
  if(S(0x13E)==19) { F(0x11C)=2; B(0x184)=1; if(T) F(0x12C)=lookup_orientation_sine_quantized_abs(static_cast<float>(-AT(AT(T,float *,0x340),float,0)-AT(P,float,0x7AC)))*-4.0; F(0x120)=0.1f; } return;
 case 869: {
  float payload[4]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1 || S(0x13E)==3 || S(0x13E)==5) F(0x11C)=10;
  if(S(0x13E)==2) F(0x11C)=10;
  if(S(0x13E)==4) F(0x11C)=6;
  if(S(0x13E)==6) F(0x11C)=4;
  if(S(0x13E)==10) { F(0x11C)=10; F(0x120)=0; }
  if(S(0x13E)==11) { payload[0]=H[0]; payload[1]=0; payload[2]=10; SPAWN(869,1,3); payload[1]=5; payload[2]=9; payload[3]=0.2f; SPAWN(869,1,4); payload[1]=15; payload[3]=0.4f; SPAWN(869,1,4); }
  if(S(0x13E)==12) F(0x120)=F(0x11C)=static_cast<float>(random_float(5)*static_cast<double>(0.1f)+0.5); return;
 }
 case 900: {
  float payload[4]; SELECT(); if(S(0x13E)<=3) { F(0x12C)=random_float(360); B(0x184)=1; F(0x370)=AT(FIELD(void *,0x170),float,0xEC); F(0x374)=AT(FIELD(void *,0x170),float,0xF0)+100.0; replace_secondary(static_cast<unsigned short>(S(0x13E)+991),30,10,1,2); payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+4; payload[3]=0; UNSPAWN(900,1,4); F(0x378)=random_float(10)-5.0; }
  if(S(0x13E)==12) { switch(g_match_identifier) { case 0: case 1:S(0x366)=120;break; case 2:S(0x366)=180;break; case 3:S(0x366)=240;break; } }
  if(S(0x13E)==13) { B(0x184)=0; F(0x120)=F(0x11C)=0.1f; }
  if(S(0x13E)>=14 && S(0x13E)<=17) { F(0x12C)=random_float(360); F(0x120)=F(0x11C)=static_cast<float>(random_float(50)*static_cast<double>(0.01f)+0.75); }
  if(S(0x13E)==18) B(0x184)=1; return;
 }
 case 901:
  SELECT(); if(S(0x13E)==8) { double const heading=H[0]; B(0x184)=1; F(0x12C)=heading; }
  if(S(0x13E)>=11 && S(0x13E)<=14) { F(0x12C)=random_float(360); B(0x184)=1; }
  if(S(0x13E)>=15 && S(0x13E)<=18) F(0x12C)=H[0];
  if(S(0x13E)==19) { F(0x11C)=2; B(0x184)=0; F(0x12C)=H[0]; F(0x120)=0.1f; } return;
 case 902: B(0x184)=1; SELECT(); if(S(0x13E)==1) { F(0x120)=F(0x11C)=static_cast<float>(modulo_float(100)*static_cast<double>(0.01f)+1.0); F(0x12C)=modulo_float(360); } return;
 case 910: {
  float payload[3]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1) { F(0xF4)=0; F(0xF8)=0; payload[0]=0; payload[1]=0; payload[2]=2; SPAWN(910,1,3); }
  if(S(0x13E)==3) { payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(910,1,3); }
  if(S(0x13E)==4) B(0x184)=15;
  if(S(0x13E)==5) { F(0x108)=0; F(0x10C)=95; F(0x12C)=H[0]; }
  if(S(0x13E)==6) { payload[0]=0; payload[1]=0; payload[2]=7; SPAWN(910,1,3); }
  if(S(0x13E)==8) { B(0x112)=0; B(0x111)=48; } return;
 }
 case 912: B(0x184)=1; F(0x12C)=H[0]; SELECT(); FRAME(); S(0x364)=0; return;
 case 913:
  B(0x113)=255; F(0x11C)=1; B(0x112)=255; B(0x111)=255; F(0x120)=1; B(0x110)=255; I(0x180)=0; B(0x184)=1; F(0x12C)=H[0]; SELECT(); FRAME();
  if(S(0x13E)<=3) { F(0x11C)=0.5f; F(0x120)=0.5f; F(0x370)=random_float(1)*16.0-8.0; MOVE(); } return;
 case 920: {
  float payload[4]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1 || S(0x13E)==3 || S(0x13E)==5) F(0x11C)=10;
  if(S(0x13E)==2) F(0x11C)=10;
  if(S(0x13E)==4) F(0x11C)=6;
  if(S(0x13E)==6) F(0x11C)=4;
  if(S(0x13E)==10) { F(0x11C)=10; F(0x120)=0; }
  if(S(0x13E)==11) { payload[0]=H[0]; payload[1]=0; payload[2]=10; SPAWN(920,1,3); payload[1]=5; payload[2]=9; payload[3]=0.2f; SPAWN(920,1,4); payload[1]=15; payload[3]=0.4f; SPAWN(920,1,4); }
  if(S(0x13E)==12) F(0x120)=F(0x11C)=static_cast<float>(random_float(5)*static_cast<double>(0.1f)+0.5); return;
 }
 case 921: F(0x12C)=random_float(360); SELECT(); B(0x184)=1; MOVE(); F(0x120)=F(0x11C)=static_cast<float>(random_float(50)*static_cast<double>(0.01f)+0.75); return;
 case 980: continue_action_980(); return;
 case 989: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { payload[0]=0; payload[1]=0; payload[2]=1; SPAWN(989,1,3); B(0x112)=0; B(0x111)=0; B(0x110)=0; }
  if(S(0x13E)==1) B(0x113)=0; return;
 }
 case 990: B(0x134)=0; return;
 case 998: F(0x12C)=0; F(0x128)=60; return;
 case 999: SELECT(); if(S(0x13E)==4) { F(0xF4)=H[0]; F(0xF8)=H[1]; } return;
 }
}
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef FRAME
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
