// JP1.06a AliceObject slot+3C @ 0x0050C1C0. Numeric states and offset views
// precede naming; complete callable and emitted metadata are compared together.
#include "AliceObjectActionEntry.hpp"
#include "engine/AngleAtan2.hpp"
#include <math.h>
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define P FIELD(AliceObjectEntryView *,0x348)
#define T FIELD(AliceObjectEntryView *,0x34C)
#define O FIELD(AliceObjectEntryView *,0x170)
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define MOTION reinterpret_cast<AliceEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,l,c) spawn_parented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define UNSPAWN(a,l,c) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define AIM() { \
 F(0x12C)=-atan2_degrees(static_cast<float>(AT(O,float,0xF0)+100.0-F(0xF0)),static_cast<float>(AT(O,float,0xEC)-F(0xEC))); \
 F(0x370)=(AT(T,float,0xEC)-F(0xEC))*(AT(T,float,0xEC)-F(0xEC)); \
 F(0x374)=(AT(T,float,0xF0)-F(0xF0))*(AT(T,float,0xF0)-F(0xF0)); \
 float const distance=static_cast<float>(sqrt(F(0x374)+F(0x370))); F(0x378)=distance; F(0x11C)=F(0x378)*0.00390625; \
}
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void AliceObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0;
 S(0x384)=0; F(0x37C)=0; S(0x386)=0; F(0x380)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800: B(0x184)=1; F(0x12C)=H[0]; SELECT(); return;
 case 801: {
  float payload[3]; if(H[2]>=2) SELECT();
  if(S(0x13E)==0) { F(0xF4)=40; F(0xF8)=10; }
  if(S(0x13E)==7) { payload[0]=0; payload[1]=0; payload[2]=6; SPAWN(803,1,3); }
  if(S(0x13E)==10) { payload[0]=0; payload[1]=0; payload[2]=12; B(0x184)=8; SPAWN(801,1,3); for(float n=0;n<=3;n+=1.0) { payload[0]=0; payload[1]=n*90.0; payload[2]=11; SPAWN(801,1,3); } }
  if(S(0x13E)==11) { F(0x12C)=H[1]; F(0x11C)=1; F(0x120)=0; }
  if(S(0x13E)==12) { F(0x11C)=0; F(0x120)=0; } return;
 }
 case 802: F(0xF4)=40; F(0xF8)=10; return;
 case 803: {
  float payload[3]; SELECT(); if(S(0x13E)==0) { F(0xF4)=40; F(0xF8)=0; payload[0]=0; payload[1]=0; payload[2]=6; SPAWN(803,1,3); }
  if(S(0x13E)==6 && T) AIM(); return;
 }
 case 804:
  B(0x184)=1; SELECT(); if(S(0x13E)>=7) { S(0x364)=selector_random_roll(15)+5; float product=random_float(15)*static_cast<double>(0.1f); F(0x120)=F(0x11C)=static_cast<float>(product+0.5); } return;
 case 805: {
  float payload[3]; if(H[2]>=2) SELECT();
  if(S(0x13E)==0) { F(0xF4)=40; F(0xF8)=0; payload[0]=0; payload[1]=0; payload[2]=7; SPAWN(805,1,3); }
  if(S(0x13E)==7 && T) AIM(); return;
 }
 case 806: B(0x184)=1; F(0x12C)=H[0]; SELECT(); return;
 case 807: F(0x11C)=4; F(0x120)=0.1f; F(0x12C)=H[0]; SELECT(); S(0x364)=0; return;
 case 810: {
  float payload[3]; B(0x17C)=0; SELECT();
  if(S(0x13E)==0) { B(0x184)=4; if(AT(P,signed char,0x604)>=2) B(0x184)=5; if(AT(P,signed char,0x604)>=4) ++B(0x184); payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(810,1,3); }
  if(S(0x13E)==4 && T) AIM();
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=2.5f; F(0x124)=random_float(5)+70.0; F(0x12C)=random_float(360); B(0x113)=0; } return;
 }
 case 811: {
  float payload[3]; B(0x184)=1; B(0x17C)=4; SELECT();
  if(S(0x13E)==0) { payload[0]=0; payload[1]=0; payload[2]=2; SPAWN(811,1,3); }
  if(S(0x13E)==2 && T) AIM();
  if(S(0x13E)==3) { F(0x120)=F(0x11C)=2; F(0x124)=random_float(5)+70.0; F(0x12C)=random_float(360); B(0x113)=0; } return;
 }
 case 815: {
  float payload[3]; B(0x17C)=1; B(0x184)=1; SELECT();
  if(S(0x13E)==0) MOVE();
  if(S(0x13E)==2) { payload[0]=0; payload[1]=0; payload[2]=3; UNSPAWN(815,1,3); payload[2]=4; UNSPAWN(815,1,3); }
  if(S(0x13E)==4) F(0x12C)=random_float(360); return;
 }
 case 816: {
  float payload[3]; B(0x17C)=5; B(0x184)=1; SELECT();
  if(S(0x13E)==0) { F(0xF4)=H[0]; F(0xF8)=H[1]; B(0x184)=AT(P,signed char,0x609)>=4; }
  if(S(0x13E)==2) { payload[0]=0; payload[1]=0; payload[2]=3; UNSPAWN(816,1,3); payload[2]=4; UNSPAWN(816,1,3); }
  if(S(0x13E)==4) F(0x12C)=random_float(360); return;
 }
 case 817: {
  float payload[3]; B(0x17C)=9; B(0x184)=1; SELECT();
  if(S(0x13E)==0 || S(0x13E)==9) { B(0x135)=1; F(0xF4)=H[0]; F(0xF8)=H[1]; }
  if(S(0x13E)==2) { payload[0]=0; payload[1]=0; payload[2]=3; UNSPAWN(817,1,3); payload[2]=4; UNSPAWN(817,1,3); }
  if(S(0x13E)==4) F(0x12C)=random_float(360); return;
 }
 case 820: {
  float payload[4]; B(0x17C)=2; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; F(0xF4)=H[0]; F(0xF8)=H[1]; payload[0]=0; payload[1]=0; payload[2]=6; payload[3]=0; SPAWN(820,1,4); }
  if(S(0x13E)==6 && T) AIM(); return;
 }
 case 821: {
  float payload[3]; B(0x17C)=6; B(0x184)=1; SELECT();
  if(S(0x13E)==0) { F(0xF4)=-2; F(0xF8)=0; }
  if(S(0x13E)==4) { payload[0]=0; payload[1]=0; payload[2]=5; spawn_unparented(821,static_cast<float>(F(0xEC)-FIELD(signed char,0x104)*140),F(0xF0),B(0x104),1,reinterpret_cast<const unsigned *>(payload),3); } return;
 }
 case 825: {
  float payload[3]; B(0x17C)=3; SELECT();
  if(S(0x13E)==0) { B(0x184)=4; if(AT(P,signed char,0x607)>=2) B(0x184)=5; if(AT(P,signed char,0x607)>=4) ++B(0x184); payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(810,1,3); }
  if(S(0x13E)==4 && T) AIM();
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=2.5f; F(0x124)=random_float(5)+70.0; F(0x12C)=random_float(360); B(0x113)=0; } return;
 }
 case 827: B(0x17C)=11; SELECT(); if(S(0x13E)==0 || S(0x13E)==3 || S(0x13E)==5 || S(0x13E)==6) B(0x184)=1; if(S(0x13E)==2 || S(0x13E)==4) F(0x370)=0.4f; return;
 case 830: F(0x374)=20; B(0x184)=1; return;
 case 831: {
  float payload[3]; B(0x17C)=7; B(0x184)=1; I(0x180)=0; SELECT(); if(S(0x13E)==5) { payload[0]=0; payload[1]=0; payload[2]=6; SPAWN(831,1,3); } if(S(0x13E)==6) { B(0x184)=0; F(0x11C)=50; F(0x120)=0.1f; } return;
 }
 case 834: {
  float payload[3]; B(0x184)=1; B(0x17C)=7; SELECT(); if(S(0x13E)==5) { payload[0]=0; payload[1]=0; payload[2]=6; SPAWN(834,1,3); } if(S(0x13E)==6) { B(0x184)=0; F(0x11C)=50; F(0x120)=0.1f; } return;
 }
 case 849: {
  float payload[3]; SELECT();
  if(S(0x13E)==1) { payload[0]=0; payload[1]=0; payload[2]=10; SPAWN(849,1,3); }
  if(S(0x13E)==5 || S(0x13E)==13) F(0x12C)=H[0];
  if(S(0x13E)==6) { payload[0]=0; payload[1]=0; payload[2]=10; SPAWN(849,1,3); }
  if(S(0x13E)==8) { for(int n=0;n<6;++n) { payload[0]=n*60.0+30.0; payload[1]=0; payload[2]=6; if(!(payload[0]<=90.0) && !(payload[0]>=270.0)) SPAWN(849,1,3); else SPAWN(849,-1,3); } }
  if(S(0x13E)==10 && T) AIM();
  if(S(0x13E)==11) { payload[0]=0; payload[1]=0; payload[2]=10; SPAWN(849,1,3); B(0x184)=1; I(0x180)=0; F(0x12C)=H[0]; }
  if(S(0x13E)==14) { payload[0]=0; payload[1]=0; payload[2]=10; SPAWN(849,1,3); }
  if(S(0x13E)==16) { for(int n=0;n<6;++n) { payload[0]=n*60.0+30.0; payload[1]=0; payload[2]=14; if(!(payload[0]<=90.0) && !(payload[0]>=270.0)) SPAWN(849,1,3); else SPAWN(849,-1,3); } }
  if(S(0x13E)==19) { payload[0]=0; payload[1]=0; payload[2]=10; SPAWN(849,1,3); }
  if(S(0x13E)==22) { F(0x120)=F(0x11C)=2; F(0x124)=random_float(5)+70.0; F(0x12C)=random_float(360); B(0x113)=0; } return;
 }
 case 850: {
  float payload[3]; B(0x184)=1; SELECT();
  if(S(0x13E)==0) { float const dx=AT(O,float,0xEC)-F(0xEC); float const magnitude=static_cast<float>(fabs(static_cast<double>(dx))); F(0xF4)=magnitude/42.0; if(F(0xF4)<2) F(0xF4)=2; F(0xF8)=20; }
  if(S(0x13E)==2) { payload[0]=0; payload[1]=0; payload[2]=3; UNSPAWN(850,-1,3); payload[2]=4; UNSPAWN(850,1,3); for(int angle=0;angle<360;angle+=45) { payload[0]=angle; payload[1]=30; payload[2]=5; UNSPAWN(850,1,3); } }
  if(S(0x13E)==5) F(0x12C)=random_float(360); return;
 }
 case 851: {
  float payload[4]; F(0x378)=20; F(0x37C)=100; SELECT();
  if(S(0x13E)==0) { F(0x370)=F(0xEC); F(0x374)=F(0xF0); payload[0]=0; payload[1]=0; payload[2]=4; payload[3]=0; SPAWN(851,1,4); }
  if(S(0x13E)==4 && T) AIM(); if(S(0x13E)==5) { F(0x120)=F(0x11C)=2; F(0x124)=70; } return;
 }
 case 852: {
  float payload[3]; B(0x184)=1; SELECT(); if(S(0x13E)==5) { payload[0]=0; payload[1]=0; payload[2]=6; SPAWN(852,1,3); }
  if(S(0x13E)==6) { P->dispatch_character_wave_handle(23); F(0x11C)=50; B(0x184)=0; F(0x120)=0.1f; }
  if(S(0x13E)==7) F(0x128)=70; return;
 }
 case 853: {
  float payload[3]; B(0x184)=1; SELECT();
  if(S(0x13E)==0) { float const dx=AT(O,float,0xEC)-F(0xEC); float const magnitude=static_cast<float>(fabs(static_cast<double>(dx))); F(0xF4)=magnitude/22.0; if(F(0xF4)<2) F(0xF4)=2; F(0xF8)=20; }
  if(S(0x13E)==2) { payload[0]=0; payload[1]=0; payload[2]=3; UNSPAWN(853,-1,3); payload[2]=4; UNSPAWN(853,1,3); for(int angle=0;angle<360;angle+=30) { payload[0]=angle; payload[1]=40; payload[2]=5; UNSPAWN(853,1,3); } }
  if(S(0x13E)==5) F(0x12C)=random_float(360); return;
 }
 case 854: {
  float payload[4]; F(0x378)=30; SELECT();
  if(S(0x13E)==0) { F(0x370)=F(0xEC); F(0x374)=F(0xF0); payload[0]=0; payload[1]=0; payload[2]=4; payload[3]=0; SPAWN(851,1,4); }
  if(S(0x13E)==4 && T) AIM();
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=2; F(0x124)=70; F(0x12C)=0; }
  if(S(0x13E)==6) { F(0x120)=F(0x11C)=2.5f; F(0x124)=70; F(0x12C)=0; } return;
 }
 case 855: {
  float payload[3]; B(0x184)=1; SELECT(); if(S(0x13E)==5) { payload[0]=0; payload[1]=0; payload[2]=6; SPAWN(855,1,3); }
  if(S(0x13E)==6) { P->dispatch_character_wave_handle(27); F(0x11C)=50; F(0x120)=0.1f; } return;
 }
 case 856: {
  float payload[4]; SELECT(); if(S(0x13E)==0) { payload[0]=0; payload[1]=0; payload[2]=7; SPAWN(856,1,3); }
  if(S(0x13E)==7 && T) AIM();
  if(S(0x13E)==8) { F(0x370)=(static_cast<int>(H[3])%2)*4-2.0; I(0x180)=0; B(0x184)=0; F(0x11C)=4; F(0x120)=0.1f; F(0x12C)=H[0]; payload[0]=0; payload[1]=0; payload[2]=9; payload[3]=0; SPAWN(856,1,4); } return;
 }
 case 857: {
  float payload[3]; SELECT(); if(S(0x13E)==0) { payload[0]=0; payload[1]=0; payload[2]=7; SPAWN(857,-1,3); }
  if(S(0x13E)==3) { F(0x370)=1; F(0x120)=F(0x11C)=0.25f; }
  if(S(0x13E)==2) { F(0x12C)=H[0]; F(0x120)=0; F(0x11C)=1.5f; } return;
 }
 case 858: {
  float payload[3]; SELECT(); if(S(0x13E)==1) { F(0xF4)=10; payload[0]=0; payload[1]=0; payload[2]=20; SPAWN(858,-1,3); payload[2]=24; SPAWN(858,-1,3); }
  if(S(0x13E)==21 || S(0x13E)==22) { F(0x12C)=H[0]; MOVE(); }
  if(S(0x13E)==23) { F(0x120)=F(0x11C)=2.5f; F(0x124)=random_float(5)+70.0; F(0x12C)=random_float(360); B(0x113)=0; }
  if(S(0x13E)>=26 && S(0x13E)<=32) { B(0x184)=1; F(0x12C)=H[0]; }
  if(S(0x13E)==33) { payload[0]=0; payload[1]=0; payload[2]=34; SPAWN(858,1,3); }
  if(S(0x13E)==34) { P->dispatch_character_wave_handle(23); B(0x184)=0; F(0x11C)=50; F(0x120)=0.1f; } return;
 }
 case 859: SELECT(); if(S(0x13E)==6) F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+0.5); return;
 case 900: {
  float payload[3]; B(0x17C)=1; B(0x184)=1; SELECT(); if(S(0x13E)==0) MOVE();
  if(S(0x13E)==3) { payload[0]=0; payload[1]=0; payload[2]=4; UNSPAWN(900,1,3); payload[2]=5; UNSPAWN(900,1,3); }
  if(S(0x13E)==5) F(0x12C)=random_float(360); return;
 }
 case 901: {
  float payload[3]; B(0x184)=1; SELECT(); if(S(0x13E)==0) { payload[0]=0; payload[1]=0; payload[2]=2; SPAWN(901,1,3); }
  if(S(0x13E)==2 && T) AIM();
  if(S(0x13E)==3 || S(0x13E)==4) { F(0x120)=F(0x11C)=2; F(0x124)=random_float(5)+70.0; F(0x12C)=random_float(360); B(0x113)=0; } return;
 }
 case 902:
  SELECT(); if(S(0x13E)==0) { B(0x184)=1; F(0x12C)=H[0]; MOTION->set_components(H[0],10); F(0x370)=F(0xEC); F(0x374)=F(0xF0); }
  if(S(0x13E)==5) F(0x12C)=H[0]; return;
 case 903: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; SELECT(); if(S(0x13E)<=6) { payload[0]=0; payload[1]=0; payload[2]=S(0x13E)+7.0; UNSPAWN(903,1,3); F(0x120)=0.5f; F(0x11C)=3; } return;
 }
 case 980: continue_action_980(); return;
 // Explicit no-op state has its own observed switch-table entry.
 case 998: return;
 case 999: SELECT(); if(S(0x13E)==0) { F(0xF4)=H[0]; F(0xF8)=H[1]; } return;
 }
}
#undef AIM
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT
#undef MOTION
#undef AT
#undef O
#undef T
#undef P
#undef H
#undef I
#undef B
#undef S
#undef F
#undef FIELD
}
