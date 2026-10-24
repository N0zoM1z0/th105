// JP1.06a 0x0052D200: complete nonexact source.
// See docs/PATCHOULI_OBJECT_ENTRY_2026_10_24.md.
#include "characters/PatchouliObjectActionEntry.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define P FIELD(PatchouliObjectEntryView *,0x348)
#define T FIELD(PatchouliObjectEntryView *,0x34C)
#define AUX FIELD(PatchouliObjectEntryView *,0x154)
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define MOTION reinterpret_cast<PatchouliEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,l,c) spawn_parented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define UNSPAWN(a,l,c) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define SCALE(n,factor,base) F(0x120)=F(0x11C)=static_cast<float>(random_float(n)*static_cast<double>(factor)+static_cast<double>(base))
#define ROUND_SCALE(n,factor,base) { float const product=random_float(n)*static_cast<double>(factor); F(0x120)=F(0x11C)=static_cast<float>(product+static_cast<double>(base)); }
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void PatchouliObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0;
 S(0x384)=0; F(0x37C)=0; S(0x386)=0; F(0x380)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) B(0x184)=1;
  if(S(0x13E)==1) ROUND_SCALE(50,0.01f,1.0);
  if(S(0x13E)==2) B(0x184)=3; return;
 case 801:
  B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==2) F(0x370)=0.7f;
  if(S(0x13E)==6) MOVE();
  if(S(0x13E)==8) { F(0x370)=0.5f; MOVE(); ROUND_SCALE(50,0.01f,1.0); }
  if(S(0x13E)==9) { B(0x184)=6; MOVE(); }
  if(S(0x13E)==10) { ROUND_SCALE(50,0.01f,1.0); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==11) ROUND_SCALE(50,0.01f,1.0); return;
 case 810: {
  float payload[3]; B(0x184)=1; F(0x12C)=H[0]; B(0x17C)=0; SELECT();
  if(S(0x13E)==0 || S(0x13E)==6) { payload[0]=H[0]; payload[1]=0; payload[2]=4; UNSPAWN(810,1,3); }
  if(S(0x13E)==0 || S(0x13E)==1 || S(0x13E)==6) MOVE();
  if(S(0x13E)==5) { SCALE(70,0.01f,0.8f); F(0x370)=3.0-random_float(6); } return;
 }
 case 811:
  B(0x184)=1; F(0x12C)=H[0]; B(0x17C)=5; SELECT();
  if(S(0x13E)==0) { F(0x12C)=random_float(360); MOVE(); F(0x370)=random_float(10)-5.0; } return;
 case 815:
  F(0x370)=0.5f; F(0x12C)=H[0]; B(0x17C)=1; SELECT();
  if(S(0x13E)==0) { F(0x120)=1.75f; B(0x184)=3; replace_auxiliary(990); AT(AUX,float,0xE8)=F(0xEC); AT(AUX,float,0xEC)=stage_height(); AT(AUX,unsigned char,0x104)=B(0x104); F(0xF8)=60; B(0x184)=3; I(0x180)=0; }
  if(S(0x13E)==3) F(0x124)=85;
  if(S(0x13E)==5) { F(0x12C)=random_float(360); SCALE(50,0.01f,1.0); MOVE(); } return;
 case 816:
  B(0x17C)=6; SELECT();
  if(S(0x13E)==0 || S(0x13E)==3) { F(0x120)=F(0x11C)=0.1f; B(0x184)=1; MOVE(); F(0x370)=F(0xF4); F(0x374)=F(0xF8); F(0xF4)=0; F(0xF8)=0; }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); SCALE(75,0.01f,1.0); MOVE(); }
  if(S(0x13E)==5 || S(0x13E)==6) { SCALE(30,0.01f,0.9f); MOVE(); B(0x184)=1; } return;
 case 820:
  F(0x370)=random_float(10)+5.0; B(0x17C)=2; SELECT();
  if(S(0x13E)==1) { F(0x124)=random_float(80)+50.0; F(0x128)=random_float(80)-40.0; F(0x12C)=random_float(360); }
  if(S(0x13E)==2) B(0x184)=1; return;
 case 821:
  B(0x17C)=7; SELECT();
  if(S(0x13E)==1) { B(0x113)=0; F(0x120)=F(0x11C)=3; }
  if(S(0x13E)==2) F(0x12C)=H[0];
  if(S(0x13E)==3) B(0x184)=1;
  if(S(0x13E)==5) { SCALE(100,0.01f,0.5); }
  if(S(0x13E)==7) { F(0x12C)=random_float(360); SCALE(50,0.01f,1.0); }
  if(S(0x13E)==8) B(0x184)=1;
  if(S(0x13E)==9) { F(0x12C)=random_float(360); F(0x128)=random_float(150)-75.0; F(0x124)=random_float(150)-75.0; } return;
 case 825: {
  float payload[3]; F(0x12C)=H[0]; B(0x17C)=3; SELECT();
  if(S(0x13E)==0) { B(0x113)=0; F(0x370)=F(0xEC)-AT(P,float,0xEC); F(0x374)=F(0xF0)-AT(P,float,0xF0); payload[0]=H[0]; payload[1]=40; payload[2]=2; UNSPAWN(825,1,3); }
  if(S(0x13E)==2) { B(0x113)=0; F(0x370)=F(0xEC)-AT(P,float,0xEC); F(0x374)=F(0xF0)-AT(P,float,0xF0); B(0x184)=1; } return;
 }
 case 826: {
  float payload[3]; B(0x17C)=8; SELECT();
  if(S(0x13E)==0) { MOVE(); B(0x184)=3; if(AT(P,signed char,0x60C)>=2) B(0x184)=4; if(AT(P,signed char,0x60C)>=4) B(0x184)=5; payload[0]=F(0x12C); payload[1]=0; payload[2]=1; SPAWN(826,1,3); }
  if(S(0x13E)==2) F(0x12C)=H[0]; return;
 }
 case 827: {
  float payload[3]; F(0x12C)=H[0]; B(0x17C)=13; SELECT();
  if(S(0x13E)==0) { F(0xF8)=5; payload[0]=F(0x12C); payload[1]=0; payload[2]=3; B(0x184)=1; SPAWN(827,1,3); replace_auxiliary(990); AT(AUX,float,0xF8)=3; AT(AUX,float,0xFC)=2; AT(AUX,float,0xE8)=F(0xEC); AT(AUX,float,0xEC)=stage_height(); AT(AUX,unsigned char,0x104)=B(0x104); } return;
 }
 case 830: {
  float payload[4]; B(0x17C)=4; SELECT();
  if(S(0x13E)==0) { replace_auxiliary(990); AT(AUX,float,0xE8)=F(0xEC); AT(AUX,float,0xEC)=stage_height(); AT(AUX,unsigned char,0x104)=B(0x104); F(0xF8)=60; B(0x184)=1; payload[1]=15; payload[2]=3; payload[3]=0; for(float n=0;n<6;n+=1.0) { payload[0]=static_cast<float>(static_cast<unsigned>(selector_random_roll(40)-20))+n*60.0; UNSPAWN(830,1,4); } }
  if(S(0x13E)==2) { F(0x370)=random_float(10)-5.0; B(0x184)=1; F(0x12C)=random_float(360); MOVE(); SCALE(25,0.01f,1.0); }
  if(S(0x13E)==3) { F(0x12C)=random_float(360); ROUND_SCALE(60,0.01f,0.7f); }
  if(S(0x13E)==4) { F(0x12C)=random_float(360); ROUND_SCALE(10,0.1f,0.5); }
  if(S(0x13E)==5) { F(0x370)=random_float(14)-7.0; F(0x12C)=random_float(360); MOVE(); SCALE(100,0.01f,0.5); } return;
 }
 case 831: {
  float payload[3]; B(0x17C)=9; SELECT();
  if(S(0x13E)==0) { B(0x184)=1; replace_auxiliary(990); AT(AUX,float,0xE8)=F(0xEC); AT(AUX,float,0xEC)=static_cast<float>(F(0xF0)+320.0); AT(AUX,float,0xF8)=2; AT(AUX,float,0xFC)=2; AT(AUX,unsigned char,0x104)=B(0x104); F(0xF8)=80; payload[1]=15; payload[2]=1; for(float n=0;n<6;n+=1.0) { payload[0]=static_cast<float>(static_cast<unsigned>(selector_random_roll(40)-20))+n*60.0; spawn_unparented(831,F(0xEC),static_cast<float>(F(0xF0)+320.0),B(0x104),1,reinterpret_cast<const unsigned *>(payload),3); } }
  if(S(0x13E)==1) { F(0x12C)=random_float(360); ROUND_SCALE(60,0.01f,0.7f); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==2) { F(0x12C)=random_float(360); ROUND_SCALE(60,0.01f,0.7f); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==3) { B(0x184)=1; replace_auxiliary(990); AT(AUX,float,0xE8)=F(0xEC); AT(AUX,float,0xEC)=static_cast<float>(F(0xF0)+480.0); AT(AUX,float,0xF8)=3; AT(AUX,float,0xFC)=3; AT(AUX,unsigned char,0x104)=B(0x104); F(0xF8)=80; payload[1]=15; payload[2]=1; for(float n=0;n<6;n+=1.0) { payload[0]=static_cast<float>(static_cast<unsigned>(selector_random_roll(40)-20))+n*60.0; spawn_unparented(831,F(0xEC),static_cast<float>(F(0xF0)+480.0),B(0x104),1,reinterpret_cast<const unsigned *>(payload),3); } } return;
 }
 case 822:
  B(0x184)=3; replace_auxiliary(990); AT(AUX,float,0xE8)=F(0xEC); AT(AUX,float,0xEC)=0; AT(AUX,unsigned char,0x104)=B(0x104); return;
 case 823: B(0x184)=1; F(0x120)=F(0x11C)=2; return;
 case 848: {
  float payload[3]; SELECT();
  if(S(0x13E)==5) { F(0x120)=F(0x11C)=0.2f; F(0x370)=F(0xEC)-AT(P,float,0xEC); F(0x374)=F(0xF0)-AT(P,float,0xF0); B(0x184)=4; }
  if(S(0x13E)==7 && H[1]==1) F(0x120)=F(0x11C)=1.5f;
  if(S(0x13E)==8) { F(0x120)=F(0x11C)=0.2f; S(0x366)=0; F(0x370)=F(0xEC)-AT(P,float,0xEC); F(0x374)=F(0xF0)-AT(P,float,0xF0); B(0x184)=0; }
  if(S(0x13E)==9) S(0x364)=1;
  if(S(0x13E)==10) { S(0x364)=1; payload[0]=0; payload[1]=0; payload[2]=11; UNSPAWN(848,1,3); }
  if(S(0x13E)==11) { S(0x364)=1; F(0x128)=70; }
  if(S(0x13E)==12) { B(0x184)=0; S(0x364)=1; }
  if(S(0x13E)==13) { S(0x364)=1; F(0x370)=random_float(10)+5.0; F(0x124)=random_float(80)+50.0; F(0x128)=random_float(80)-40.0; F(0x12C)=random_float(360); } return;
 }
 case 850:
  B(0x184)=1; SELECT();
  if(S(0x13E)==0) { S(0x344)=1; F(0x120)=F(0x11C)=0; B(0x184)=1; }
  if(S(0x13E)==2) { B(0x184)=1; F(0x12C)=H[0]; }
  if(S(0x13E)==3) F(0x370)=0.5f;
  if(S(0x13E)==4) { ROUND_SCALE(10,0.1f,0.25); S(0x364)=selector_random_roll(40); }
  if(S(0x13E)==5) { MOVE(); F(0x370)=random_float(10)-5.0; }
  if(S(0x13E)==6) { ROUND_SCALE(10,0.1f,0.75); F(0x12C)=random_float(360); } return;
 case 851:
  B(0x184)=1; F(0x12C)=H[0]; SELECT(); if(S(0x13E)==1) MOVE();
  if(S(0x13E)==3) { F(0x370)=0.5f; MOVE(); ROUND_SCALE(50,0.01f,1.0); } return;
 case 852:
  F(0x120)=F(0x11C)=0; SELECT(); if(S(0x13E)==3) { ROUND_SCALE(75,0.01f,0.75); F(0x12C)=random_float(360); F(0x370)=random_float(10)+10.0; } return;
 case 853:
  F(0x12C)=H[0]; S(0x344)=1; SELECT();
  if(S(0x13E)==0) F(0x370)=1;
  if(S(0x13E)==4) { F(0x120)=0; if(H[1]==0) { F(0x378)=2; float product=random_float(5)*static_cast<double>(0.1f); F(0x370)=product+0.5; F(0x374)=1; } if(H[1]==1) { F(0x378)=-4; float product=random_float(2)*static_cast<double>(0.1f); F(0x370)=product+static_cast<double>(0.2f); F(0x374)=1; } }
  if(S(0x13E)==6) ROUND_SCALE(10,0.1f,0.5);
  if(S(0x13E)==7) ROUND_SCALE(125,0.01f,0.75); return;
 case 854: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { F(0x370)=1; F(0x120)=F(0x11C)=0; S(0x344)=1; payload[0]=0; payload[1]=0; payload[2]=1; SPAWN(854,-1,3); payload[2]=2; SPAWN(854,-1,3); F(0x124)=75; }
  if(S(0x13E)==1) { B(0x113)=0; F(0x370)=1; S(0x344)=1; F(0x120)=F(0x11C)=0; F(0x124)=75; }
  if(S(0x13E)==2) { S(0x344)=1; F(0x370)=1; F(0x120)=F(0x11C)=0; F(0x124)=75; }
  if(S(0x13E)==3) { B(0x113)=0; F(0x370)=1; B(0x111)=0; B(0x112)=0; ROUND_SCALE(20,0.1f,1.0); F(0x370)=random_float(4)+2.0; if(static_cast<unsigned>(selector_random_roll(100))<=50) F(0x370)=F(0x370)*-1.0; F(0x124)=75; }
  if(S(0x13E)==4) { if(T) { float *const input=H; F(0xEC)=lookup_orientation_cosine_quantized_abs(-input[0])*input[1]*FIELD(signed char,0x104)+AT(T,float,0xEC); F(0xF0)=lookup_orientation_sine_quantized_abs(-input[0])*H[1]*static_cast<double>(0.2f)+AT(T,float,0xF0); } F(0x120)=0.01f; F(0x11C)=0.01f; payload[0]=0; payload[1]=0; payload[2]=5; B(0x184)=99; SPAWN(854,B(0x33C),3); payload[2]=6; SPAWN(854,B(0x33C),3); }
  if(S(0x13E)==5 || S(0x13E)==6) F(0x120)=F(0x11C)=0.1f;
  if(S(0x13E)==7) ROUND_SCALE(125,0.01f,0.75);
  if(S(0x13E)==8) { F(0x124)=75; B(0x184)=1; }
  if(S(0x13E)==9) { B(0x113)=static_cast<unsigned char>(H[1]); B(0x112)=static_cast<unsigned char>(H[1]); B(0x111)=static_cast<unsigned char>(H[1]); B(0x110)=static_cast<unsigned char>(H[1]); F(0x120)=F(0x11C)=H[3]; F(0x124)=75; } return;
 }
 case 855:
  SELECT(); if(S(0x13E)<=4) { F(0x370)=F(0xEC); F(0x374)=F(0xF0); F(0x378)=1; }
  if(S(0x13E)>=5 && S(0x13E)<=9) { SCALE(10,0.1f,0.5); }
  if(S(0x13E)>=15 && S(0x13E)<=19) B(0x184)=1; return;
 case 856:
  SELECT(); if(S(0x13E)==0) F(0x120)=F(0x11C)=0.1f;
  if(S(0x13E)==2 || S(0x13E)==4) { F(0x12C)=random_float(360); SCALE(75,0.01f,1.0); MOVE(); }
  if(S(0x13E)==3) { MOVE(); F(0x120)=F(0x11C)=0.1f; }
  if(S(0x13E)==5) { MOVE(); B(0x184)=1; SCALE(20,0.01f,0.9f); } return;
 case 857:
  SELECT(); if(S(0x13E)==0 || S(0x13E)==1) { F(0x370)=F(0xEC); F(0x374)=F(0xF0); F(0x378)=8; replace_secondary(static_cast<unsigned short>(992+(S(0x13E)==1)),20,20,1,2); }
  if(S(0x13E)==2 || S(0x13E)==3) F(0x370)=1;
  if(S(0x13E)==4 || S(0x13E)==5) B(0x184)=1;
  if(S(0x13E)==6 || S(0x13E)==7) ROUND_SCALE(5,0.1f,1.0);
  if(S(0x13E)==8 || S(0x13E)==9) F(0x370)=1;
  if(S(0x13E)==10 || S(0x13E)==11) ROUND_SCALE(10,0.1f,0.5); return;
 case 860: SELECT(); if(S(0x13E)==0) { B(0x113)=0; F(0x370)=1; } return;
 case 861:
  S(0x344)=1; F(0x12C)=H[0]; SELECT(); if(S(0x13E)==0) { F(0x124)=random_float(180)-90.0; F(0x128)=random_float(180)-90.0; F(0x12C)=random_float(180)-90.0; } return;
 case 890: S(0x344)=1; return;
 case 900:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0 || S(0x13E)==2) { B(0x184)=1; F(0x12C)=random_float(360); MOVE(); F(0x370)=random_float(10)-5.0; switch(g_match_identifier) { case 3:S(0x36A)=90;break; case 2:S(0x36A)=85;break; case 1:S(0x36A)=75;break; case 0:S(0x36A)=60;break; } }
  if(S(0x13E)==1 || S(0x13E)==3) { MOVE(); F(0x12C)=random_float(360); F(0x370)=random_float(10)-5.0; SCALE(10,0.1f,0.75); }
  if(S(0x13E)==4 || S(0x13E)==5) { MOVE(); F(0x12C)=random_float(360); F(0x370)=random_float(10)-5.0; SCALE(10,0.1f,0.5); } return;
 case 910:
  SELECT(); if(S(0x13E)==0) F(0x120)=F(0x11C)=0.1f;
  if(S(0x13E)==2 || S(0x13E)==4) { F(0x12C)=random_float(360); SCALE(75,0.01f,1.0); MOVE(); }
  if(S(0x13E)==3) { MOVE(); F(0x120)=F(0x11C)=0.1f; }
  if(S(0x13E)==5) { MOVE(); B(0x184)=1; SCALE(20,0.01f,0.9f); } return;
 case 920:
  SELECT(); if(S(0x13E)==0) F(0x128)=90;
  if(S(0x13E)==7 || S(0x13E)==8) { MOVE(); SCALE(6,0.1f,0.75); }
  if(S(0x13E)==9 || S(0x13E)==10) { F(0x12C)=random_float(360); MOVE(); SCALE(6,0.1f,0.75); } return;
 case 980: continue_action_980(); return;
 case 998: F(0x12C)=0; F(0x128)=60; return;
 }
}
#undef ROUND_SCALE
#undef SCALE
#undef UNSPAWN
#undef SPAWN
#undef MOVE
#undef SELECT
#undef MOTION
#undef AT
#undef AUX
#undef T
#undef P
#undef H
#undef I
#undef B
#undef S
#undef F
#undef FIELD
}
