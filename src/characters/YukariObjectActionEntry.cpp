#include "characters/YukariObjectActionEntry.hpp"
// JP1.06a 0x005964C0: complete source candidate, nonexact.
// Evidence and finite trials: docs/YUKARI_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {
#define FIELD(type,offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this)+(offset)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define P FIELD(YukariObjectEntryView *,0x348)
#define AT(p,type,o) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define AUX(p,type,o) AT(AT(p,void *,0x154),type,o)
#define A(type,o) AUX(this,type,o)
#define MOTION reinterpret_cast<YukariEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() select_sequence(static_cast<int>(H[2]))
#define MAYSELECT() if(H[2]!=0.0f) SELECT()
#define SPAWN(a,x,y,layer,count) spawn_parented(a,x,y,B(0x104),layer,reinterpret_cast<const unsigned *>(payload),count)
#define UNSPAWN(a,x,y,layer,count) spawn_unparented(a,x,y,B(0x104),layer,reinterpret_cast<const unsigned *>(payload),count)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void YukariObjectEntryView::initialize_action_entry()
{
 F(0xF4)=0; F(0xF8)=0; F(0x370)=0; F(0x374)=0; F(0x378)=0; F(0x37C)=0;
 S(0x384)=0; F(0x380)=0; S(0x386)=0; B(0x184)=0;
 S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
 switch(S(0x13C)) {
 case 800:
  B(0x184)=1; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1) { replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=static_cast<float>(stage_height()-3.0); A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==2) { replace_auxiliary(990); A(float,0xE8)=F(0xEC); A(float,0xEC)=static_cast<float>(F(0xF0)-10.0); A(unsigned char,0x104)=B(0x104); }
  return;
 case 801:
  B(0x184)=1; F(0x12C)=H[0]; F(0x370)=255; SELECT();
  if(S(0x13E)==4) F(0x120)=F(0x11C)=static_cast<float>(MOTION->random_range(5,15)*static_cast<double>(0.1f));
  return;
 case 810:
  B(0x184)=1; B(0x17C)=0; SELECT();
  if(S(0x13E)==0) F(0xF0)=stage_height()+650.0;
  if(S(0x13E)==1 || S(0x13E)==2 || S(0x13E)==3) {
   F(0xF8)=-25; replace_auxiliary(990); A(float,0xE8)=F(0xEC); A(float,0xEC)=F(0xF0); A(unsigned char,0x104)=B(0x104);
  }
  return;
 case 811:
  B(0x184)=1; B(0x17C)=4; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1) {
   F(0xF8)=-25; replace_auxiliary(993);
   A(float,0xE8)=static_cast<float>(F(0xEC)-(lookup_orientation_cosine_quantized_abs(-H[0])*100.0-105.0)*FIELD(signed char,0x104));
   A(float,0xEC)=static_cast<float>(F(0xF0)-lookup_orientation_sine_quantized_abs(-H[0])*100.0);
   A(float,0xF8)=4; A(float,0xFC)=4; A(unsigned char,0x104)=B(0x104);
  }
  return;
 case 812: {
  float payload[3]; B(0x17C)=8; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x370)=1; F(0x11C)=0; F(0x120)=0; payload[0]=0; payload[1]=0; payload[2]=5; UNSPAWN(812,F(0xEC),F(0xF0),1,3); }
  if(S(0x13E)==1) F(0x370)=18;
  if(S(0x13E)==2) { B(0x184)=1; F(0x120)=4; }
  if(S(0x13E)==4) { F(0x370)=1; F(0x11C)=0; F(0x120)=0; payload[0]=0; payload[1]=0; payload[2]=5; UNSPAWN(812,F(0xEC),F(0xF0),1,3); }
  return;
 }
 case 815: B(0x17C)=1; SELECT(); return;
 case 816:
  B(0x184)=0; if(AT(P,signed char,0x609)>=3) B(0x184)=1;
  I(0x180)=0; B(0x17C)=5; SELECT(); return;
 case 820:
  B(0x17C)=2; B(0x184)=1; SELECT();
  if(S(0x13E)==0 || S(0x13E)==3) F(0x11C)=0;
  if(S(0x13E)==7) F(0x12C)=H[0];
  if(S(0x13E)==8) { F(0x124)=random_float(360); F(0x128)=random_float(360); F(0x12C)=random_float(360); }
  return;
 case 821:
  B(0x17C)=6; SELECT();
  if(S(0x13E)==2) B(0x184)=0;
  if(S(0x13E)==4) { F(0x12C)=H[0]; F(0x11C)=0.25f; F(0x120)=0.25f; }
  if(S(0x13E)==5) { F(0x12C)=H[0]; F(0x120)=F(0x11C)=static_cast<float>(MOTION->random_range(5,15)*static_cast<double>(0.1f)); }
  if(S(0x13E)==6) { F(0x370)=0.25f; F(0x12C)=H[0]; F(0x11C)=0.5f; F(0x120)=0.5f; }
  return;
 case 825:
  B(0x17C)=3; SELECT();
  if(S(0x13E)==0) { F(0x11C)=0; F(0x370)=0.2f; }
  if(S(0x13E)==1) {
   F(0x11C)=0; F(0x370)=0.1f; P->replace_auxiliary(993);
   AUX(P,float,0xE8)=F(0xEC); AUX(P,float,0xEC)=F(0xF0); AUX(P,float,0xF8)=2; AUX(P,float,0xFC)=2; AUX(P,unsigned char,0x104)=B(0x104);
  }
  if(S(0x13E)==2) {
   P->replace_auxiliary(990); AUX(P,float,0xE8)=F(0xEC); AUX(P,float,0xEC)=F(0xF0); AUX(P,float,0xF8)=4; AUX(P,float,0xFC)=2; AUX(P,unsigned char,0x104)=B(0x104);
  }
  return;
 case 826: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=AT(P,float,0xF0); A(float,0xF8)=10; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==4) { F(0x124)=85; F(0x12C)=random_float(360); F(0x370)=random_float(20)-10.0; }
  if(S(0x13E)==5) { replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=F(0xF0); A(float,0xF8)=2; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==9) {
   F(0x108)=0; F(0x10C)=135; B(0x184)=1; F(0xF4)=6; F(0xF8)=30; F(0x370)=-230;
   replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=AT(P,float,0xF0); A(float,0xF8)=10; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104);
   payload[0]=0; payload[1]=0; payload[2]=0; SPAWN(826,F(0xEC),static_cast<float>(F(0xF0)+130.0),1,3);
  }
  if(S(0x13E)==10) {
   F(0x108)=0; F(0x10C)=135; B(0x184)=1; F(0x370)=-250;
   replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=AT(P,float,0xF0); A(float,0xF8)=10; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104);
   payload[0]=0; payload[1]=0; payload[2]=0; SPAWN(826,F(0xEC),static_cast<float>(F(0xF0)+130.0),1,3);
  }
  return;
 }
 case 848: SELECT(); return;
 case 849:
  SELECT(); if(S(0x13E)==0) { F(0xF4)=-6; F(0xF8)=4; } if(S(0x13E)==1) F(0xF4)=6; return;
 case 850:
  F(0x12C)=H[0]; F(0x124)=-30*FIELD(signed char,0x104); F(0x128)=60; MAYSELECT();
  if(S(0x13E)==0) { F(0x11C)=0.2f; F(0x120)=0.2f; }
  if(S(0x13E)==2) F(0x120)=F(0x11C)=H[1]; return;
 case 851:
  MAYSELECT(); if(S(0x13E)==0) { F(0x370)=1; S(0x344)=1; F(0x11C)=0; F(0x120)=3; } return;
 case 852: MAYSELECT(); if(S(0x13E)==0) B(0x184)=1; return;
 case 853:
  F(0x12C)=H[0]; F(0x124)=-30*FIELD(signed char,0x104); F(0x128)=60; MAYSELECT();
  if(S(0x13E)==0) { F(0x11C)=0.2f; F(0x120)=0.2f; }
  if(S(0x13E)==2) F(0x120)=F(0x11C)=H[1];
  if(S(0x13E)==3) F(0x120)=F(0x11C)=H[1];
  if(S(0x13E)==4) { F(0x124)=75; F(0x12C)=0; B(0x113)=0; F(0x128)=0; } return;
 case 854:
  MAYSELECT(); if(S(0x13E)==0) { F(0x370)=1; B(0x184)=1; S(0x344)=1; F(0x11C)=0; F(0x120)=3; } return;
 case 855:
  MAYSELECT();
  if(S(0x13E)==1) F(0x120)=F(0x11C)=static_cast<float>(random_float(10)*static_cast<double>(0.1f)+0.5);
  if(S(0x13E)==3) { B(0x184)=1; MOTION->set_components(H[0],H[1]); }
  if(S(0x13E)==4) { F(0x11C)=random_float(10)*static_cast<double>(0.05f)+1.0; F(0x120)=random_float(10)*static_cast<double>(0.1f)+1.0; F(0x12C)=H[0]; } return;
 case 856:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x11C)=0; S(0x344)=1; F(0x120)=0; F(0x370)=random_float(75)*static_cast<double>(0.01f)+0.75; F(0x374)=1; F(0x378)=1; }
  if(S(0x13E)==1) {
   MOTION->set_components(H[0],H[1]); B(0x184)=1; replace_auxiliary(993); A(float,0xE8)=F(0xEC); A(float,0xEC)=F(0xF0); A(unsigned char,0x104)=B(0x104);
   F(0x11C)=1.5f; F(0x120)=random_float(5)*static_cast<double>(0.1f)+0.5;
  }
  if(S(0x13E)==2) F(0x370)=0.4f; return;
 case 857: {
  float payload[3]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x370)=1; F(0x11C)=0; F(0x120)=0; payload[0]=0; payload[1]=0; payload[2]=5; UNSPAWN(857,F(0xEC),F(0xF0),1,3); }
  if(S(0x13E)==1) F(0x370)=18;
  if(S(0x13E)==2) { B(0x184)=1; F(0x120)=4; }
  if(S(0x13E)==4) { F(0x370)=1; F(0x11C)=0; F(0x120)=0; payload[0]=0; payload[1]=0; payload[2]=5; UNSPAWN(857,F(0xEC),F(0xF0),1,3); } return;
 }
 case 865:
  B(0x184)=1; SELECT();
  if(S(0x13E)==0) F(0x370)=0.3f;
  if(S(0x13E)==1) { B(0x135)=1; replace_auxiliary(993); A(float,0xE8)=F(0xEC); A(float,0xEC)=F(0xF0); A(float,0xF8)=20; A(float,0xFC)=4; A(unsigned char,0x104)=B(0x104); } return;
 case 899:
  SELECT();
  if(S(0x13E)==0) {
   F(0x11C)=0; F(0x370)=0.1f; P->replace_auxiliary(993); AUX(P,float,0xE8)=F(0xEC); AUX(P,float,0xEC)=F(0xF0); AUX(P,float,0xF8)=2; AUX(P,float,0xFC)=2; AUX(P,unsigned char,0x104)=AT(P,unsigned char,0x104);
  }
  if(S(0x13E)==4) { F(0x124)=85; F(0x12C)=random_float(360); F(0x370)=random_float(20)-10.0; }
  if(S(0x13E)==5) { replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=F(0xF0); A(float,0xF8)=2; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104); } return;
 case 900:
  SELECT();
  if(S(0x13E)==0) { B(0x184)=1; F(0x378)=10; F(0x370)=F(0xEC); F(0x374)=F(0xF0); }
  if(S(0x13E)==1) { F(0x378)=12; B(0x184)=1; F(0x370)=F(0xEC); F(0x374)=F(0xF0); } return;
 case 910: {
  float payload[3]; SELECT();
  if(S(0x13E)==0) { replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=AT(P,float,0xF0); A(float,0xF8)=10; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==4) { F(0x124)=85; F(0x12C)=random_float(360); F(0x370)=random_float(20)-10.0; }
  if(S(0x13E)==5) { replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=F(0xF0); A(float,0xF8)=2; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104); }
  if(S(0x13E)==9) {
   F(0x108)=0; B(0x184)=1; F(0x10C)=135; F(0xF4)=0; F(0xF8)=20; F(0x370)=-230;
   replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=AT(P,float,0xF0); A(float,0xF8)=10; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104);
   payload[0]=0; payload[1]=0; payload[2]=0; SPAWN(910,F(0xEC),static_cast<float>(F(0xF0)+130.0),1,3);
  }
  if(S(0x13E)==10) {
   F(0x108)=0; B(0x184)=1; F(0x10C)=135; F(0x370)=-250;
   replace_auxiliary(992); A(float,0xE8)=F(0xEC); A(float,0xEC)=AT(P,float,0xF0); A(float,0xF8)=10; A(float,0xFC)=2; A(unsigned char,0x104)=B(0x104);
   payload[0]=0; payload[1]=0; payload[2]=0; SPAWN(910,F(0xEC),static_cast<float>(F(0xF0)+130.0),1,3);
  }
  if(S(0x13E)==12) {
   MOTION->set_components(H[0],H[1]); B(0x184)=1; F(0x120)=F(0x11C)=static_cast<float>(random_float(6)*static_cast<double>(0.1f)+0.75);
   for(int n=3;n!=0;--n) { payload[0]=-10.0-random_float(80); payload[1]=random_float(8)+5.0; payload[2]=13; UNSPAWN(910,F(0xEC),F(0xF0),1,3); }
  }
  if(S(0x13E)==13) { MOTION->set_components(H[0],H[1]); F(0x120)=F(0x11C)=static_cast<float>(random_float(6)*static_cast<double>(0.1f)+0.75); } return;
 }
 case 920:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x11C)=0; F(0x120)=0; F(0x370)=random_float(75)*static_cast<double>(0.01f)+0.75; F(0x374)=1; F(0x378)=1; }
  if(S(0x13E)==1) {
   MOTION->set_components(H[0],H[1]); B(0x184)=1; replace_auxiliary(993); A(float,0xE8)=F(0xEC); A(float,0xEC)=F(0xF0); A(unsigned char,0x104)=B(0x104);
   F(0x11C)=1.5f; F(0x120)=random_float(5)*static_cast<double>(0.1f)+0.5;
  }
  if(S(0x13E)==2) F(0x370)=0.4f; return;
 case 930: {
  float payload[3]; F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==0) { F(0x370)=1; F(0x11C)=0; F(0x120)=0; payload[0]=0; payload[1]=0; payload[2]=5; UNSPAWN(930,F(0xEC),F(0xF0),1,3); }
  if(S(0x13E)==1) F(0x370)=18;
  if(S(0x13E)==2) { B(0x184)=1; F(0x120)=4; }
  if(S(0x13E)==4) { F(0x370)=1; F(0x11C)=0; F(0x120)=0; payload[0]=0; payload[1]=0; payload[2]=5; UNSPAWN(930,F(0xEC),F(0xF0),1,3); } return;
 }
 case 940:
  F(0x12C)=H[0]; SELECT();
  if(S(0x13E)==1) { F(0x370)=1; F(0x374)=1; F(0x11C)=0; F(0x120)=0.1f; }
  if(S(0x13E)==3) { B(0x184)=1; MOTION->set_components(H[0],H[1]); } return;
 case 980: continue_action_980(); return;
 case 981:
  SELECT(); if(S(0x13E)==6) { F(0x124)=85; F(0x12C)=random_float(360); F(0x370)=random_float(20)-10.0; } return;
 case 998: F(0x124)=FIELD(signed char,0x104)*-30.0; F(0x128)=65; return;
 case 999: F(0x108)=60; B(0x134)=0; F(0x10C)=135; return;
 }
}
#undef UNSPAWN
#undef SPAWN
#undef MAYSELECT
#undef SELECT
#undef MOTION
#undef A
#undef AUX
#undef AT
#undef P
#undef H
#undef I
#undef B
#undef S
#undef F
#undef FIELD
}
