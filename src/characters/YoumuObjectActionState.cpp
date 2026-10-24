// JP1.06a 53CEA0: complete compiling hypothesis; not selected or exact.
// See docs/YOUMU_OBJECT_UPDATE_2026_10_25.md for reviewed facts and open questions.
#include "characters/YoumuObjectActionState.hpp"
#include <math.h>
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define I(o) AT(this,int,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define H AT(this,float *,0x340)
#define P AT(this,YoumuObjectUpdateView *,0x348)
#define A AT(this,YoumuObjectUpdateView *,0x170)
#define D(v) static_cast<double>(v)
#define MOTION reinterpret_cast<YoumuUpdateMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define MOVE() MOTION->set_components(H[0],H[1])
#define STEP() { F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8); }
#define FRAME_EXIT() { if(advance_frame()) --I(0x330); return; }
#define RETIRE() { --I(0x330); return; }
#define SPAWN(a,l,c) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define SPAWN_AT(a,x,y,l,c) spawn_unparented(a,x,y,B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define OUTSIDE(xhi,xlo,yhi,ylo) (F(0xEC)>xhi || F(0xEC)<xlo || F(0xF0)>yhi || F(0xF0)<ylo)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
extern int g_match_identifier;
#define RADIAL_901(final_kind,hard_only) { \
 if(AT(P,short,0x174)<=0) RETIRE(); \
 if(I(0x144)%2==0 && S(0x364)<8) { \
  if(S(0x364)==0) F(0x370)=H[0]+90.0; \
  if(S(0x364)==1) F(0x370)=H[0]-90.0; \
  if(S(0x364)==2) F(0x370)=H[0]; \
  if(S(0x364)==3) F(0x370)=H[0]+180.0; \
  if(S(0x364)==4) F(0x370)=H[0]+45.0; \
  if(S(0x364)==5) F(0x370)=H[0]+135.0; \
  if(S(0x364)==6) F(0x370)=H[0]-45.0; \
  if(S(0x364)==7) F(0x370)=H[0]-135.0; \
  if(S(0x364)%2==0) P->dispatch_character_wave_handle(1); \
  payload[0]=90.0+F(0x370); payload[1]=0.5f; payload[2]=2; \
  SPAWN_AT(901,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x370))*100.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x370))*100.0+F(0xF0)),1,3); \
  ++S(0x364); \
 } \
 if(I(0x144)>=H[1]) { \
  payload[0]=0; payload[1]=0; payload[2]=0; SPAWN(901,1,3); \
  float fragments[3]; \
  for(int n=0;n<6;++n) { fragments[0]=random_float(360); fragments[1]=random_float(50)*D(0.1f)+10.0; fragments[2]=1; spawn_unparented(901,F(0xEC),F(0xF0),B(0x104),1,reinterpret_cast<const unsigned *>(fragments),3); } \
  payload[1]=0.5f; payload[2]=final_kind; SPAWN(901,1,3); payload[2]=1; SPAWN(901,1,3); \
  if(!(hard_only) || g_match_identifier==3) { \
   for(int n=0;n<4;++n) { fragments[0]=random_float(360); fragments[1]=random_float(50)*D(0.1f)+5.0; fragments[2]=7; spawn_unparented(901,F(0xEC),F(0xF0),B(0x104),1,reinterpret_cast<const unsigned *>(fragments),3); } \
  } \
  P->dispatch_character_wave_handle(4); RETIRE(); \
 } \
}
void YoumuObjectUpdateView::update_action_state()
{
 float payload[5];
 switch(S(0x13C)) {
 case 800:
  if(I(0x180)==5) RETIRE();
  if(S(0x13E)==0) {
   if(AT(P,short,0x13C)>=50 && AT(P,short,0x13C)<150) RETIRE();
   MOVE(); STEP();
   if(I(0x144)%2==0) {
    P->dispatch_character_wave_handle(0);
    payload[0]=0; payload[1]=0; payload[2]=2; payload[3]=0; payload[4]=H[4];
    SPAWN(800,1,5); payload[2]=3; SPAWN(800,1,5); ++S(0x364);
   }
   if(S(0x364)>=H[3]) RETIRE();
  }
  if(S(0x13E)==1) {
   if(S(0x140)==0) {
    if(emit_repeated(0,0,3)) RETIRE();
    H[1]+=0.5;
    if(I(0x180)!=0) { next_sequence_frame(); B(0x184)=0; }
    if(OUTSIDE(1380.0f,-100.0,1200.0f,-120.0)) RETIRE();
    MOVE(); STEP();
   } else {
    F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)-D(0.01f));
    if(B(0x113)<15) RETIRE();
    B(0x111)-=15; B(0x112)-=15; B(0x113)-=15;
   }
  }
  if(S(0x13E)==2) {
   F(0x370)+=5.0; if(F(0x370)>90.0f) F(0x370)=90;
   F(0x374)-=D(0.005f);
   F(0x120)=F(0x11C)=static_cast<float>(static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x370)))+F(0x374));
   if(I(0x144)<18) { if(emit_repeated(0,0,3)) RETIRE(); }
   else { if(B(0x113)<15) RETIRE(); B(0x111)-=15; B(0x112)-=15; B(0x113)-=15; }
   if(I(0x144)==18) { payload[0]=0; payload[1]=5; payload[2]=1; payload[3]=0; payload[4]=H[4]; SPAWN(800,1,5); }
  }
  if(S(0x13E)==3) {
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+0.25);
   if(B(0x113)<20) RETIRE(); B(0x113)-=20; B(0x111)-=20; B(0x112)-=20;
  }
  FRAME_EXIT();
 case 801:
  if(I(0x180)==5) RETIRE();
  if(S(0x13E)==0) {
   if(S(0x140)==0) {
    if(emit_repeated(0,0,3)) RETIRE(); H[1]+=0.5;
    if(I(0x180)!=0) { next_sequence_frame(); B(0x184)=0; }
    if(OUTSIDE(1380.0f,-100.0,1200.0f,-120.0)) RETIRE();
    MOVE(); STEP();
   } else {
    F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)-D(0.01f));
    if(B(0x113)<15) RETIRE(); B(0x111)-=15; B(0x112)-=15; B(0x113)-=15;
   }
  }
  if(S(0x13E)==1) {
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.9f));
   if(I(0x144)==0) { payload[0]=H[0]; payload[1]=6; payload[2]=0; SPAWN(801,1,3); }
   if(I(0x144)>=0) { if(B(0x113)<15) RETIRE(); B(0x111)-=15; B(0x112)-=15; B(0x113)-=15; }
  }
  if(S(0x13E)==2) {
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+0.25);
   if(B(0x113)<40) RETIRE(); B(0x113)-=40; B(0x111)-=40; B(0x112)-=40;
  }
  FRAME_EXIT();
 case 810:
  B(0x17C)=0; if(I(0x180)==5) RETIRE();
  if(S(0x13E)==0) {
   if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
   if(S(0x140)==5) {
    --S(0x364);
    if(C(0x184)==0 || S(0x364)<=0 || ((AT(P,short,0x13C)==500 || AT(P,short,0x13C)==501) && AT(P,short,0x140)==0)) { next_sequence_frame(); return; }
   }
   if(emit_repeated(0,0,0)) RETIRE(); F(0x12C)+=30.0;
  }
  if(S(0x13E)==1) {
   if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
   if(S(0x140)==5) {
    --S(0x364);
    if(I(0x180)!=0 && ++S(0x366)>=6) { S(0x366)=0; I(0x180)=0; }
    if(C(0x184)==0 || S(0x364)<=0 || ((AT(P,short,0x13C)==500 || AT(P,short,0x13C)==501) && AT(P,short,0x140)==0)) { set_sequence_frame(7); return; }
    if(I(0x144)>=15) { next_sequence_frame(); return; }
   }
   if(S(0x140)==6) {
    --S(0x364);
    if(I(0x180)!=0 && ++S(0x366)>=6) { S(0x366)=0; I(0x180)=0; }
    if(C(0x184)==0 || S(0x364)<=0 || ((AT(P,short,0x13C)==500 || AT(P,short,0x13C)==501) && AT(P,short,0x140)==0)) { next_sequence_frame(); return; }
   }
   if(emit_repeated(0,0,0)) RETIRE(); F(0x12C)+=30.0;
  }
  F(0xF4)*=D(0.95f); if(F(0xF4)<D(0.1f)) F(0xF4)=0.1f;
  F(0xEC)+=C(0x104)*F(0xF4);
  if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) --I(0x330);
  return;
 case 811:
  B(0x17C)=1; if(I(0x180)==5) RETIRE();
  if(S(0x13E)==0) {
   if(AT(P,short,0x13C)!=520 && AT(P,short,0x13C)!=521) RETIRE();
   F(0xEC)=C(0x104)*AT(P,float,0xF4)+AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF8)+AT(P,float,0xF0);
  }
  if(S(0x13E)==1) {
   if(AT(P,short,0x13C)!=520 && AT(P,short,0x13C)!=521) RETIRE();
   F(0xEC)=C(0x104)*AT(P,float,0xF4)+AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF8)+AT(P,float,0xF0);
  }
  if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) --I(0x330);
  return;
 case 812:
  B(0x17C)=2; if(I(0x180)==5) RETIRE();
  if(S(0x13E)==0) {
   if(AT(P,short,0x13C)!=540) RETIRE();
   if(AT(P,short,0x13E)==0) { F(0xEC)=C(0x104)*AT(P,float,0xF4)+AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF8)+AT(P,float,0xF0); }
  }
  if(S(0x13E)==1) {
   if(AT(P,short,0x13C)!=540) RETIRE();
   if(AT(P,short,0x13E)==1) { F(0xEC)=C(0x104)*AT(P,float,0xF4)+AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF8)+AT(P,float,0xF0); }
  }
  if(S(0x13E)==0) {
   if(AT(P,short,0x13C)!=540) RETIRE();
   if(AT(P,short,0x13E)==2 || AT(P,short,0x13E)==7) { F(0xEC)=C(0x104)*AT(P,float,0xF4)+AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF8)+AT(P,float,0xF0); }
  }
  if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==2) --I(0x330);
  return;
 case 813:
  if(S(0x13E)==0) {
   if(B(0x113)<8) RETIRE();
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.99f)); F(0xF8)-=D(0.15f); B(0x113)-=8;
  } else if(S(0x13E)==1) {
   if(B(0x113)<20) RETIRE(); F(0x12C)+=15.0;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.05f)); B(0x113)-=20;
  }
  STEP(); FRAME_EXIT();
 case 815:
  B(0x17C)=4; if(I(0x180)==5) RETIRE();
  if(S(0x13E)<2) {
   if(emit_repeated(0,3,5)) RETIRE();
   if(I(0x180)==6) {
    if(++S(0x384)>=10) { B(0x184)=0; select_sequence(2); return; }
    ++B(0x184); I(0x180)=0;
   }
   if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>=7) { S(0x364)=0; I(0x180)=0; }
   F(0xF4)-=0.5; if(F(0xF4)<5.0f) F(0xF4)=5;
   if(C(0x184)<=0 || I(0x144)>=120) { select_sequence(2); return; }
  }
  if(S(0x13E)==2) { F(0xF4)-=D(0.2f); if(F(0xF4)<0.0f) F(0xF4)=0; }
  if(S(0x13E)>=3 && S(0x13E)<=4) {
   if(emit_repeated(0,3,5)) RETIRE();
   if(I(0x180)==6) {
    if(++S(0x384)>=10) { B(0x184)=0; select_sequence(5); return; }
    ++B(0x184); I(0x180)=0;
   }
   if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>=7) { S(0x364)=0; I(0x180)=0; }
   F(0xF4)-=0.5; if(F(0xF4)<5.0f) F(0xF4)=5;
   if(C(0x184)<=0 || I(0x144)>=120) { select_sequence(5); return; }
  }
  if(S(0x13E)==5) { F(0xF4)-=D(0.2f); if(F(0xF4)<0.0f) F(0xF4)=0; }
  if(F(0xEC)>1500.0f || F(0xEC)<-300.0f) RETIRE();
  STEP(); if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==3) --I(0x330);
  return;
 case 817:
  if(S(0x364)) {
   if(F(0xF4)<0.0f) F(0xF4)=0;
   F(0xF4)*=D(0.98f); F(0xEC)+=C(0x104)*F(0xF4);
   if(B(0x113)<10) RETIRE(); F(0x120)*=D(0.92f); F(0x11C)+=D(0.05f); B(0x113)-=10;
  } else {
   if((AT(P,short,0x13C)!=545 && AT(P,short,0x13C)!=546) || AT(P,short,0x140)>6) { S(0x364)=1; F(0xF4)=AT(P,float,0xF4); }
   F(0xEC)=AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF0);
  }
  FRAME_EXIT();
 case 818:
  switch(S(0x13E)) {
  case 0:
   if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
   publish_bounds_descriptor(static_cast<int>(F(0x11C)*-80.0),static_cast<int>(F(0x120)*80.0),static_cast<int>(F(0x11C)*80.0),static_cast<int>(F(0x120)*-80.0),0,0,0);
   if(B(0x113)<8) RETIRE(); B(0x113)-=8; if(B(0x113)<=64) B(0x184)=0;
   F(0x11C)+=H[1]; H[1]-=D(0.15f); if(H[1]<0.02f) H[1]=0.02f; F(0x120)=F(0x11C); break;
  case 1:
   if(B(0x113)<10) RETIRE(); B(0x113)-=10; F(0x12C)+=F(0x370); F(0x370)*=D(0.98f); F(0x11C)+=D(0.1f); F(0x120)*=D(0.85f); break;
  case 2:
   MOVE(); H[1]*=D(0.9f); F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.98f));
   if(B(0x113)<10) RETIRE(); B(0x113)-=10; break;
  }
  STEP(); FRAME_EXIT();
 case 820:
  B(0x17C)=8; if(I(0x180)==5) RETIRE();
  if(S(0x13E)==0) {
   if(I(0x180)==0) {
    if(AT(P,short,0x13C)>=50 && AT(P,short,0x13C)<150) {
     for(int n=0;n<3;++n) emit_fighter_effect(201,F(0xEC),F(0xF0),B(0x104),1);
     RETIRE();
    }
    if(OUTSIDE(1380.0f,-100.0,800.0,-120.0)) RETIRE();
    MOVE();
   } else {
    F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)-D(0.01f));
    if(B(0x113)<15) RETIRE(); B(0x111)-=15; B(0x112)-=15; B(0x113)-=15;
   }
  }
  STEP(); if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) --I(0x330);
  return;
 case 821:
  if(I(0x180)==5 || (AT(P,short,0x13C)!=565 && AT(P,short,0x13C)!=566)) RETIRE();
  position_relative(150,115); if(advance_frame()) --I(0x330);
  if(S(0x142)==0 && S(0x140)==3) F(0x11C)=6;
  return;
 case 823:
  if(I(0x180)==5) RETIRE();
  switch(S(0x13E)) {
  case 0:
   if(emit_repeated(0,1,5)) RETIRE(); advance_six(4);
   if(OUTSIDE(1480.0f,-200.0,1300.0f,-200.0)) RETIRE();
   if(I(0x144)%3==0) {
    payload[0]=random_float(360); payload[1]=random_float(60)*D(0.1f)+5.0; payload[2]=3; SPAWN(823,1,3);
   }
   if(C(0x184)<=0) {
    payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(823,1,3);
    for(int n=0;n<6;++n) { payload[0]=random_float(360); payload[1]=random_float(60)*D(0.1f)+3.0; payload[2]=1; SPAWN(823,1,3); }
    RETIRE();
   }
   F(0x120)=F(0x11C)=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(I(0x144)*6.0))*D(0.2f)+D(0.8f));
   MOVE(); STEP(); break;
  case 1:
   F(0x370)*=D(0.9f); if(F(0x370)<=0.02f) F(0x370)=0.02f;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+F(0x370));
   if(I(0x144)>=2) { if(B(0x113)<20) RETIRE(); B(0x113)-=20; }
   break;
  case 2:
   F(0x11C)+=D(0.01f); F(0x120)*=D(0.95f);
   if(B(0x113)<20) RETIRE(); B(0x113)-=20; break;
  case 3:
   MOVE(); H[1]*=D(0.9f); if(B(0x113)<10) RETIRE(); B(0x113)-=10; STEP(); break;
  case 4:
   MOVE(); H[1]*=D(0.9f); if(B(0x113)<10) RETIRE(); B(0x113)-=10; STEP(); break;
  }
  FRAME_EXIT();
 case 850:
  if(I(0x180)==5) RETIRE();
  if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) --I(0x330);
  return;
 case 851:
  if(I(0x180)==5 || AT(P,short,0x13C)!=601) RETIRE();
  F(0xEC)=C(0x104)*AT(P,float,0xF4)+AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF8)+AT(P,float,0xF0);
  if(AT(P,short,0x186)==0) { if(advance_frame()) --I(0x330); }
  return;
 case 852:
  if(S(0x13E)==0) {
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.4f));
   if(I(0x144)>=5) { if(B(0x113)<=25) RETIRE(); B(0x113)-=25; B(0x111)-=25; B(0x110)-=25; }
  } else if(S(0x13E)==1) {
   F(0x12C)+=F(0x370); F(0x370)*=D(0.98f); if(F(0x370)<=D(0.1f)) F(0x370)=0.1f;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x374)+F(0x11C)); F(0x374)*=D(0.9f);
   if(B(0x113)<=5) RETIRE(); B(0x113)-=5;
  }
  FRAME_EXIT();
 case 853:
  if(I(0x180)==5) RETIRE();
  if(S(0x13E)==1) {
   MOTION->set_components(H[0],100); F(0x11C)+=D(0.2f); F(0x120)-=D(0.1f);
   if(F(0x120)<=0.0f) RETIRE(); STEP();
  }
  if(S(0x13E)==3) {
   F(0x11C)+=D(0.1f); F(0x120)*=D(0.98f);
   if(I(0x144)>=5) { if(B(0x113)<10) RETIRE(); B(0x113)-=10; }
  }
  if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==2) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==3) --I(0x330);
  return;
 case 854:
  if(I(0x180)==5 || AT(P,short,0x13C)!=604) RETIRE();
  F(0xEC)=C(0x104)*AT(P,float,0xF4)+AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF8)+AT(P,float,0xF0);
  if(AT(P,short,0x186)==0) { if(advance_frame()) --I(0x330); }
  return;
 case 855:
  switch(S(0x13E)) {
  case 0:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.4f));
   if(I(0x144)>=15) { if(B(0x113)<=20) RETIRE(); B(0x113)-=20; B(0x111)-=20; B(0x110)-=20; }
   break;
  case 1:
   F(0x12C)+=F(0x370); F(0x370)*=D(0.98f); if(F(0x370)<=D(0.1f)) F(0x370)=0.1f;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x374)+F(0x11C)); F(0x374)*=D(0.9f);
   if(B(0x113)<=5) RETIRE(); B(0x113)-=5; break;
  case 2:
   MOTION->set_components(H[0],6); F(0x11C)+=D(0.05f); F(0x120)*=D(0.99f);
   if(I(0x144)>=10) { if(B(0x113)<=5) RETIRE(); B(0x113)-=5; }
   STEP(); break;
  }
  FRAME_EXIT();
 case 856:
  switch(S(0x13E)) {
  case 0:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(S(0x140)>=1) { if(B(0x113)<15) RETIRE(); B(0x113)-=15; } break;
  case 1:
   F(0xF8)-=D(0.2f); F(0xF4)*=D(0.98f); F(0x12C)+=F(0x370); F(0x370)*=D(0.95f);
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.001f));
   if(B(0x113)<5) RETIRE(); STEP(); B(0x113)-=5; break;
  case 2:
   F(0x120)+=F(0x370); F(0x370)*=D(0.95f); F(0x11C)*=D(0.9f);
   if(I(0x144)>=5) { if(B(0x113)<15) RETIRE(); B(0x113)-=15; } break;
  case 4:
   advance_six(0); F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(B(0x113)<10) RETIRE(); B(0x113)-=10; break;
  case 5:
   if(AT(P,short,0x174)<=0) RETIRE();
   if(I(0x144)>=H[1]) {
    payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(856,1,3); payload[2]=0;
    SPAWN_AT(856,static_cast<float>(F(0xEC)+100.0-random_float(200)),static_cast<float>(random_float(400)+F(0xF0)),1,3);
    RETIRE();
   }
   break;
  }
  if(advance_frame()) --I(0x330);
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==1) {
   for(int n=0;n<6;++n) { payload[0]=random_float(360); payload[1]=random_float(50)*D(0.1f)+5.0; payload[2]=1; SPAWN(856,1,3); }
  }
  return;
 case 857:
  switch(S(0x13E)) {
  case 0: case 1: case 2:
   if(S(0x364)%20==0 && S(0x13E)<2) { payload[0]=0; payload[1]=0; payload[2]=3; SPAWN_AT(857,static_cast<float>(C(0x104)*110+F(0xEC)),F(0xF0),1,3); }
   ++S(0x364); advance_six(0); advance_phase(0);
   if(I(0x180)!=0 && ++S(0x366)>=5) { S(0x366)=0; B(0x184)=1; I(0x180)=0; }
   if(S(0x13E)<2) {
    payload[0]=random_float(40)-100.0; payload[1]=random_float(25)+5.0; payload[2]=4;
    SPAWN_AT(857,static_cast<float>(C(0x104)*(random_float(150)+25.0)+F(0xEC)),static_cast<float>(F(0xF0)+50.0),1,3);
    position_relative(50,0);
    if(S(0x13E)==1) {
     if(AT(P,short,0x13C)!=607 || AT(P,short,0x140)>=10) goto next_block_857_902;
     else position_relative(50,0);
    }
   }
   break;
  case 3:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(B(0x113)<15) RETIRE(); B(0x113)-=15; break;
  case 4:
   F(0xF8)-=D(0.4f); F(0xF4)*=D(0.99f); F(0x12C)+=F(0x370); F(0x370)*=D(0.98f);
   if(I(0x144)>=60) { if(B(0x113)<10) RETIRE(); B(0x113)-=10; } STEP(); break;
  }
  if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==3) --I(0x330);
  return;
 case 899:
  A=AT(P,YoumuObjectUpdateView *,0x170);
  if(S(0x13E)!=1 && S(0x13E)!=4 && S(0x13E)!=6 && S(0x13E)!=7 && (AT(P,short,0x13C)==602 || AT(P,short,0x13C)==605)) {
   S(0x174)=0; AT(P,short,0x7E6)=0; select_sequence(6); S(0x364)=0; S(0x344)=1; return;
  }
  switch(S(0x13E)) {
  case 0:
   B(0x113)=AT(P,unsigned char,0x113); B(0x17C)=255; AT(P,unsigned char,0x7E5)=0; B(0x104)=AT(P,unsigned char,0x104);
   if(AT(P,short,0x13C)==720 && (AT(P,short,0x13E)==1 || AT(P,short,0x13E)==2)) {
    F(0xF4)+=1.5; F(0xF8)=0;
    if(F(0xEC)>1380.0f || F(0xEC)<-100.0) F(0xF4)=0;
   } else if(AT(P,short,0x7E8)==0) {
    if(C(0x104)==1) F(0xF4)=(AT(P,float,0xEC)-100.0-F(0xEC))*D(0.025f);
    if(C(0x104)==-1) F(0xF4)=(AT(P,float,0xEC)+100.0-F(0xEC))*D(-0.025f);
    F(0xF8)=(AT(P,float,0xF0)+200.0-F(0xF0))*D(0.025f);
   } else {
    if(C(0x104)==1) F(0xF4)=(AT(A,float,0xEC)-100.0-F(0xEC))*D(0.025f);
    if(C(0x104)==-1) F(0xF4)=(AT(A,float,0xEC)+100.0-F(0xEC))*D(-0.025f);
    F(0xF8)=(AT(A,float,0xF0)+200.0-F(0xF0))*D(0.025f);
   }
   S(0x364)+=2; if(S(0x364)>=360) S(0x364)-=360;
   F(0x120)=F(0x11C)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x364)))*D(0.2f)+1.0);
   if(S(0x364)%10==0) {
    payload[0]=0; payload[1]=0; payload[2]=1;
    SPAWN_AT(899,static_cast<float>(random_float(50)-25.0+F(0xEC)),static_cast<float>(random_float(50)-25.0+F(0xF0)),-1,3);
   }
   if(AT(P,short,0x7E6)==1) { S(0x174)=0; AT(P,short,0x7E6)=0; select_sequence(2); S(0x364)=0; P->dispatch_character_wave_handle(1); return; }
   if(AT(P,short,0x7E6)==2) {
    S(0x174)=0; I(0x180)=0; B(0x33C)=1; B(0x184)=1;
    H[0]=-atan2_degrees(static_cast<float>(AT(A,float,0xF0)-F(0xF0)+100.0),static_cast<float>(C(0x104)*(AT(A,float,0xEC)-F(0xEC))));
    if(H[0]>10.0f) H[0]=10; if(H[0]<-10.0f) H[0]=-10; H[1]=40;
    AT(P,short,0x7E6)=0; select_sequence(3); B(0x17C)=255; S(0x364)=0; P->dispatch_character_wave_handle(2); return;
   }
   if(AT(P,short,0x7E6)==3) { S(0x174)=0; AT(P,short,0x7E6)=0; select_sequence(5); S(0x364)=0; P->dispatch_character_wave_handle(1); return; }
   if(AT(P,short,0x7E6)==4) {
    S(0x174)=0; AT(P,short,0x7E6)=0; B(0x33C)=1; B(0x184)=1; I(0x180)=0;
    H[0]=-atan2_degrees(static_cast<float>(AT(A,float,0xF0)-F(0xF0)+100.0),static_cast<float>(C(0x104)*(AT(A,float,0xEC)-F(0xEC))));
    if(H[0]>10.0f) H[0]=10; if(H[0]<-10.0f) H[0]=-10; H[1]=40;
    select_sequence(8); B(0x17C)=3; S(0x364)=0; P->dispatch_character_wave_handle(2); return;
   }
   if(AT(P,short,0x7E6)==5) { S(0x174)=0; AT(P,short,0x7E6)=0; select_sequence(9); S(0x364)=0; P->dispatch_character_wave_handle(1); return; }
   if(AT(P,short,0x7E6)==6) { S(0x174)=0; AT(P,short,0x7E6)=0; select_sequence(10); F(0x370)=0; S(0x364)=0; P->dispatch_character_wave_handle(1); return; }
   if(AT(P,short,0x7E6)==10) { select_sequence(11); S(0x364)=0; return; }
   break;
  case 1:
   if(B(0x113)<13) RETIRE(); B(0x113)-=13; F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.94f)); F(0xF8)-=D(0.1f); break;
  case 2:
   AT(P,short,0x7E6)=0; AT(P,unsigned char,0x7E5)=1; F(0xF4)*=0.5; F(0xF8)*=0.5;
   if(I(0x144)>=10 && I(0x144)%5==0 && S(0x364)<11) {
    P->dispatch_character_wave_handle(0);
    payload[0]=static_cast<float>(S(0x364)*20); payload[1]=0; payload[2]=1;
    SPAWN_AT(801,static_cast<float>(lookup_orientation_cosine_quantized_abs(-payload[0])*50.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-payload[0])*50.0+F(0xF0)),1,3);
    payload[0]=S(0x364)*20+180.0;
    SPAWN_AT(801,static_cast<float>(lookup_orientation_cosine_quantized_abs(-payload[0])*50.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-payload[0])*50.0+F(0xF0)),1,3);
    ++S(0x364);
   }
   if((AT(P,short,0x13C)>=50 && AT(P,short,0x13C)<150) || I(0x144)>=90) { AT(P,unsigned char,0x7E5)=0; select_sequence(0); S(0x364)=0; return; }
   break;
  case 3:
   AT(P,short,0x7E6)=0; advance_six(0);
   if(S(0x174)<0) { B(0x184)=0; H[1]=0; F(0xF4)=0; F(0xF8)=0; select_sequence(0); B(0x33C)=255; AT(P,unsigned char,0x7E5)=0; return; }
   if(I(0x144)>=14 || F(0xEC)>1380.0f || F(0xEC)<-100.0) {
    H[1]-=4.0;
    if(H[1]<=0.0f) { F(0xF4)=0; F(0xF8)=0; select_sequence(0); B(0x33C)=255; AT(P,unsigned char,0x7E5)=0; return; }
   } else { payload[0]=H[1]; payload[1]=0; payload[2]=4; SPAWN(899,1,3); }
   MOVE(); break;
  case 4:
   if(B(0x113)<20) RETIRE(); B(0x113)-=20; F(0x12C)+=15.0; F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.05f)); break;
  case 5:
   AT(P,short,0x7E6)=0; AT(P,unsigned char,0x7E5)=1; F(0xF4)*=0.5; F(0xF8)*=0.5;
   if(I(0x144)>=30 && I(0x144)%5==0 && S(0x364)<18) {
    P->dispatch_character_wave_handle(0);
    payload[0]=static_cast<float>(S(0x364)*25); payload[1]=0; payload[2]=1;
    SPAWN_AT(801,static_cast<float>(lookup_orientation_cosine_quantized_abs(-payload[0])*50.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-payload[0])*50.0+F(0xF0)),1,3);
    payload[0]=S(0x364)*25+180.0;
    SPAWN_AT(801,static_cast<float>(lookup_orientation_cosine_quantized_abs(-payload[0])*50.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-payload[0])*50.0+F(0xF0)),1,3);
    ++S(0x364);
   }
   if((AT(P,short,0x13C)>=50 && AT(P,short,0x13C)<150) || I(0x144)>=90) { AT(P,unsigned char,0x7E5)=0; select_sequence(0); S(0x364)=0; return; }
   break;
  case 6:
   AT(P,short,0x7E6)=0; AT(P,unsigned char,0x7E5)=1; B(0x33C)=1;
   if(AT(P,short,0x13C)!=602 && AT(P,short,0x13C)!=605) { AT(P,unsigned char,0x7E5)=0; I(0x114)=0; select_sequence(0); B(0x33C)=255; S(0x364)=0; return; }
   if(AT(P,short,0x7EA)>0) { B(0x33C)=255; B(0x113)=128; select_sequence(7); return; }
   B(0x104)=AT(P,unsigned char,0x104);
   if(C(0x104)==1) F(0xF4)=(AT(P,float,0xEC)-F(0xEC))*D(0.1f);
   if(C(0x104)==-1) F(0xF4)=(AT(P,float,0xEC)-F(0xEC))*D(-0.1f);
   F(0xF8)=(AT(P,float,0xF0)+100.0-F(0xF0))*D(0.1f); break;
  case 7:
   AT(P,short,0x7E6)=0; AT(P,unsigned char,0x7E5)=1;
   if(AT(P,short,0x7EA)<=0) { AT(P,unsigned char,0x7E5)=0; S(0x344)=0; I(0x114)=0; B(0x113)=255; select_sequence(0); S(0x364)=0; return; }
   I(0x114)=1; apply_owner_record(10); return;
  case 8:
   AT(P,short,0x7E6)=0; advance_six(0);
   if(I(0x180)==1) AT(P,short,0x7E8)=180;
   if(I(0x144)>=14 || F(0xEC)>1380.0f || F(0xEC)<-100.0 || S(0x174)<=(-1-AT(P,signed char,0x607))*500) {
    B(0x184)=0; H[1]=0; F(0xF4)=0; F(0xF8)=0; select_sequence(0); B(0x33C)=255; AT(P,unsigned char,0x7E5)=0; return;
   }
   payload[0]=H[1]; payload[1]=0; payload[2]=1; SPAWN(813,1,3);
   if(I(0x144)%2==0) {
    payload[0]=random_float(360); payload[1]=0; payload[2]=0;
    SPAWN_AT(813,static_cast<float>(50.0+F(0xEC)-random_float(100)),static_cast<float>(F(0xF0)+50.0-random_float(100)),1,3);
   }
   MOVE(); break;
  case 9:
   AT(P,short,0x7E6)=0; AT(P,unsigned char,0x7E5)=1; F(0xF4)*=0.5; F(0xF8)*=0.5;
   if(I(0x144)>=10) {
    F(0xF4)=0; F(0xF8)=0;
    if(S(0x364)<5) {
     if(I(0x144)%7==0) {
      payload[0]=static_cast<float>(S(0x364)*20); payload[1]=0.5f; if(AT(P,signed char,0x60B)>2) payload[1]=0.6f;
      payload[2]=0; SPAWN(818,1,3); ++S(0x364);
     }
     if(I(0x144)%10==0) { payload[0]=random_float(360); payload[1]=0; payload[2]=1; SPAWN(818,1,3); }
     if(I(0x144)%2==0) { payload[0]=random_float(360); payload[1]=random_float(60)*D(0.1f)+10.0; payload[2]=2; SPAWN(818,1,3); }
    }
   }
   if((AT(P,short,0x13C)>=50 && AT(P,short,0x13C)<150) || I(0x144)>=120) { AT(P,unsigned char,0x7E5)=0; select_sequence(0); S(0x364)=0; return; }
   break;
  case 10:
   AT(P,short,0x7E6)=0; AT(P,unsigned char,0x7E5)=1; F(0xF4)*=0.5; F(0xF8)*=0.5;
   if(I(0x144)>=5) {
    F(0xF4)=0; F(0xF8)=0;
    int limit;
    if(AT(P,signed char,0x60F)<=3) limit=3;
    if(AT(P,signed char,0x60F)<=1) limit=2;
    if(AT(P,signed char,0x60F)>=4) limit=4;
    if(S(0x364)<=limit && I(0x144)%7==0) {
     payload[0]=30.0-F(0x370); payload[1]=15; payload[2]=0; SPAWN(823,1,3);
     ++S(0x364); F(0x370)+=10.0; P->dispatch_character_wave_handle(0);
    }
   }
   if((AT(P,short,0x13C)>=50 && AT(P,short,0x13C)<150) || I(0x144)>=150) { AT(P,unsigned char,0x7E5)=0; select_sequence(0); S(0x364)=0; return; }
   break;
  case 11:
   B(0x17C)=255; AT(P,unsigned char,0x7E5)=0; B(0x104)=255;
   F(0xF4)=((640.0-F(0xEC))/30.0)*-1.0; F(0xF8)=(350.0-F(0xF0))/30.0;
   if(F(0xF4)>30.0) F(0xF4)=30; if(F(0xF4)<-30.0) F(0xF4)=-30;
   if(F(0xF8)>30.0) F(0xF8)=30; if(F(0xF8)<-30.0) F(0xF8)=-30;
   S(0x364)+=2; if(S(0x364)>=360) S(0x364)-=360;
   F(0x120)=F(0x11C)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x364)))*D(0.2f)+1.0);
   if(S(0x364)%10==0) {
    payload[0]=0; payload[1]=0; payload[2]=1;
    SPAWN_AT(899,static_cast<float>(random_float(50)-25.0+F(0xEC)),static_cast<float>(random_float(50)-25.0+F(0xF0)),-1,3);
   }
   if(AT(P,short,0x13C)!=740) { AT(P,short,0x7E6)=0; select_sequence(0); return; }
   if(AT(P,short,0x13E)==2) { next_sequence_block(); return; }
   break;
  case 12: {
   S(0x364)+=2; if(S(0x364)>=360) S(0x364)-=360;
   F(0x120)=F(0x11C)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x364)))*D(0.2f)+1.0);
   if(S(0x364)%10==0) {
    payload[0]=0; payload[1]=0; payload[2]=1;
    SPAWN_AT(899,static_cast<float>(random_float(50)-25.0+F(0xEC)),static_cast<float>(random_float(50)-25.0+F(0xF0)),-1,3);
   }
   if(AT(P,short,0x13C)!=740) { AT(P,short,0x7E6)=0; select_sequence(0); return; }
   F(0xF4)=C(0x104)*((AT(P,float,0xEC)-F(0xEC))/30.0); F(0xF8)=(AT(P,float,0xF0)-F(0xF0))/30.0;
   if(F(0xF4)>30.0) F(0xF4)=30; if(F(0xF4)<-30.0) F(0xF4)=-30;
   if(F(0xF8)>30.0) F(0xF8)=30; if(F(0xF8)<-30.0) F(0xF8)=-30;
   // Neither target switch assigns these locals for unsupported identifiers.
   // The source shape and out-of-range behavior remain under review.
   int period; float count;
   switch(g_match_identifier) { case 0: period=150; count=8; break; case 1: period=120; count=12; break; case 2: period=90; count=16; break; case 3: period=90; count=20; break; }
   if(I(0x144)%period==0) {
    for(float n=0;n<count;n+=1.0) { payload[0]=n*360.0/count; payload[1]=random_float(15)*D(0.1f)+3.0; payload[2]=3; SPAWN(930,1,3); }
    payload[2]=7; SPAWN(930,1,3); P->dispatch_character_wave_handle(1);
   }
   switch(g_match_identifier) { case 0: period=180; break; case 1: case 2: case 3: period=120; break; }
   if(I(0x144)%period==0) {
    payload[0]=random_float(80)-40.0; payload[1]=0; payload[2]=0;
    SPAWN_AT(930,AT(A,float,0xEC),static_cast<float>(AT(A,float,0xF0)+100.0),1,3); P->dispatch_character_wave_handle(50);
   }
   break;
  }
  }
  STEP(); FRAME_EXIT();
 case 848:
  if(S(0x13E)==0) { if(AT(P,short,0x13C)!=302) RETIRE(); position_relative(0,0); }
  else if(S(0x13E)==1) { if(AT(P,short,0x13C)!=304) RETIRE(); position_relative(0,0); }
  if(AT(P,short,0x186)==0 && advance_frame()) RETIRE();
  if(S(0x142)==0 && S(0x140)==0) --I(0x330);
  return;
 case 900:
  switch(S(0x13E)) {
  case 0:
   F(0x11C)+=D(0.01f);
   if(S(0x364)==0) {
    if(AT(P,short,0x174)<=0) { S(0x364)=2; return; }
    F(0x120)+=D(0.1f); if(F(0x120)>=1.0f) { F(0x120)=1; S(0x364)=1; B(0x184)=1; }
   }
   if(S(0x364)==1) {
    if(AT(P,short,0x174)<=0 || I(0x144)>=90) { S(0x364)=2; return; }
    publish_bounds_descriptor(0,10,static_cast<int>(F(0x11C)*330.0),-10,static_cast<short>(static_cast<int>(H[0])),0,0);
    advance_six(0); advance_phase(0);
    if(I(0x180)!=0 && ++S(0x366)>=10) { S(0x366)=0; B(0x184)=1; I(0x180)=0; }
    if(S(0x368)==0 && AT(P,short,0x13C)==710 && AT(P,short,0x730)==1) {
     S(0x368)=1;
     float x=static_cast<float>(C(0x104)*F(0x11C)*300.0*lookup_orientation_cosine_quantized_abs(-H[0])+F(0xEC));
     float y=static_cast<float>(F(0x11C)*300.0*lookup_orientation_sine_quantized_abs(-H[0])+F(0xF0));
     payload[0]=-atan2_degrees(static_cast<float>(AT(A,float,0xF0)+100.0-y),static_cast<float>(C(0x104)*(AT(A,float,0xEC)-x)));
     payload[1]=2; payload[2]=1; SPAWN_AT(900,x,y,1,3);
     payload[1]=0.5f; payload[2]=4; SPAWN_AT(900,x,y,1,3);
     payload[1]=0.75f; payload[2]=4; SPAWN_AT(900,x,y,1,3);
     if(g_match_identifier!=0) {
      F(0x374)=random_float(9); float count=18; if(g_match_identifier==1) count=10;
      double const step=360.0/count;
      for(float n=0;n<count;n+=1.0) { payload[0]=n*step+F(0x374); payload[1]=5; payload[2]=2; SPAWN_AT(900,x,y,1,3); }
      payload[2]=3; SPAWN_AT(900,x,y,1,3);
     }
    }
   }
   if(S(0x364)==2) { B(0x184)=0; F(0x120)*=D(0.98f); if(B(0x113)<15) RETIRE(); B(0x113)-=15; }
   break;
  case 1:
   F(0x11C)+=D(0.1f);
   if(S(0x364)==0) {
    if(AT(P,short,0x174)<=0) { S(0x364)=2; return; }
    F(0x120)+=D(0.2f); if(F(0x120)>=1.0f) { F(0x120)=1; S(0x364)=1; B(0x184)=1; }
   }
   if(S(0x364)==1) {
    if(AT(P,short,0x174)<=0 || I(0x144)>=90) { S(0x364)=2; return; }
    publish_bounds_descriptor(0,10,static_cast<int>(F(0x11C)*330.0),-10,static_cast<short>(static_cast<int>(H[0])),0,0);
    advance_six(0); advance_phase(0);
    if(I(0x180)!=0) { S(0x364)=2; B(0x184)=0; }
   }
   if(S(0x364)==2) { B(0x184)=0; F(0x120)*=D(0.99f); if(B(0x113)<5) RETIRE(); B(0x113)-=5; }
   MOVE(); STEP(); break;
  case 2:
   if(S(0x140)==0) {
    if(AT(P,short,0x174)<=0) { next_sequence_frame(); B(0x184)=0; }
    H[1]+=D(0.01f);
    if(I(0x180)!=0) { next_sequence_frame(); B(0x184)=0; }
    if(OUTSIDE(1380.0f,-100.0,1200.0f,-120.0)) RETIRE();
    MOVE(); STEP();
   } else {
    F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)-D(0.01f));
    if(B(0x113)<15) RETIRE(); B(0x111)-=15; B(0x112)-=15; B(0x113)-=15;
   }
   break;
  case 3:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.95f));
   if(B(0x113)<15) RETIRE(); B(0x111)-=15; B(0x112)-=15; B(0x113)-=15; break;
  case 4:
   F(0x11C)+=H[1]; H[1]*=D(0.95f); F(0x120)=F(0x11C);
   if(B(0x113)<10) RETIRE(); B(0x113)-=10; B(0x111)-=10; B(0x112)-=10; break;
  case 5:
   MOVE(); H[1]-=0.5; if(H[1]<0.5f) H[1]=0.5f;
   F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8)*0.25; F(0x12C)=F(0x374)+F(0x12C);
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.02f));
   if(I(0x144)>=0) { if(B(0x113)<=5) RETIRE(); B(0x113)-=5; } break;
  }
  FRAME_EXIT();
 case 901:
  switch(S(0x13E)) {
  case 0:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.35f));
   if(B(0x113)<15) RETIRE(); B(0x113)-=15; break;
  case 1:
   F(0xF8)-=D(0.2f); F(0xF4)*=D(0.98f); F(0x12C)+=F(0x370); F(0x370)*=D(0.95f);
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.001f)); if(B(0x113)<5) RETIRE(); B(0x113)-=5; STEP(); break;
  case 2:
   MOVE(); STEP(); F(0x11C)+=D(0.1f); F(0x120)*=D(0.98f);
   if(I(0x144)>=10) { if(B(0x113)<20) RETIRE(); B(0x113)-=20; } break;
  case 3: case 4:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+H[1]); H[1]*=D(0.95f); advance_six(0);
   if(B(0x113)<10) RETIRE(); B(0x113)-=10; break;
  case 5: RADIAL_901(3,0); break;
  case 6:
   if(AT(P,short,0x174)<=0) RETIRE();
   if(I(0x144)%S(0x366)==0 && S(0x364)<S(0x368)) {
    payload[0]=random_float(360); payload[1]=20; payload[2]=5; SPAWN(901,1,3);
    ++S(0x364); if(S(0x364)>=S(0x368)) RETIRE();
   }
   turn_heading(0,360,100); MOVE(); STEP(); break;
  case 7:
   if(S(0x140)==0) {
    if(AT(P,short,0x174)<=0) { next_sequence_frame(); B(0x184)=0; }
    H[1]*=D(0.98f); if(H[1]<1.0f) H[1]=1;
    if(I(0x180)!=0) { next_sequence_frame(); B(0x184)=0; }
    if(OUTSIDE(1380.0f,-100.0,1200.0f,-120.0)) RETIRE(); MOVE(); STEP();
   } else {
    F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)-D(0.01f));
    if(B(0x113)<15) RETIRE(); B(0x111)-=15; B(0x112)-=15; B(0x113)-=15;
   }
   break;
  case 8: RADIAL_901(4,1); break;
  }
  FRAME_EXIT();
 case 902:
  switch(S(0x13E)) {
  case 0:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(S(0x140)>0) { if(B(0x113)<15) RETIRE(); B(0x113)-=15; } break;
  case 1:
   F(0xF8)-=D(0.1f); F(0xF4)*=D(0.98f); F(0x12C)+=F(0x370); F(0x370)*=D(0.98f);
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.001f));
   if(I(0x144)>=120 || C(0x184)<=0) { if(B(0x113)<5) RETIRE(); B(0x113)-=5; } STEP(); break;
  case 2:
   F(0x120)+=F(0x370); F(0x370)*=D(0.95f); F(0x11C)*=D(0.98f);
   if(I(0x144)>=5) { if(B(0x113)<5) RETIRE(); B(0x113)-=5; } break;
  case 3:
   F(0x11C)+=H[1]; H[1]*=D(0.95f); F(0x120)*=D(0.99f);
   if(I(0x144)>=10) { if(B(0x113)<10) RETIRE(); B(0x113)-=10; } break;
  case 4:
   advance_six(0); F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(B(0x113)<10) RETIRE(); B(0x113)-=10; break;
  case 5:
   if(AT(P,short,0x174)<=0) RETIRE();
   if(I(0x144)%4==0) {
    payload[0]=10.0-random_float(45); payload[1]=0; payload[2]=2;
    F(0x370)=F(0xF0)+20.0-random_float(40);
    spawn_unparented(902,static_cast<float>(random_float(100)+F(0xEC)-50.0),F(0x370),B(0x104),static_cast<unsigned char>(F(0x370)<=F(0xF0)?1:-1),reinterpret_cast<const unsigned *>(payload),3);
   }
   if(I(0x144)%5==0) {
    payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(902,1,3); payload[2]=0;
    SPAWN_AT(902,static_cast<float>(F(0xEC)+100.0-random_float(200)),static_cast<float>(random_float(200)+F(0xF0)),1,3);
   }
   if(I(0x144)%10==0) {
    payload[0]=0; payload[1]=random_float(15)*D(0.01f)+D(0.2f); payload[2]=3;
    SPAWN_AT(902,static_cast<float>(F(0xEC)+100.0-random_float(200)),F(0xF0),1,3);
   }
   MOVE(); STEP(); if(F(0xEC)<-100.0 || F(0xEC)>1380.0f) RETIRE(); break;
  case 6: case 7: case 8:
   if(S(0x364)%20==0 && (S(0x13E)==6 || S(0x13E)==7)) {
    payload[0]=0; payload[1]=0; payload[2]=9; SPAWN_AT(902,static_cast<float>(C(0x104)*110+F(0xEC)),F(0xF0),1,3);
   }
   ++S(0x364); advance_six(0); advance_phase(0);
   if(I(0x180)!=0 && ++S(0x366)>=15) { S(0x366)=0; B(0x184)=1; I(0x180)=0; }
   if(S(0x13E)==7) {
    if(I(0x144)%5==0) {
     payload[0]=random_float(20)-90.0; payload[1]=random_float(15)+20.0; payload[2]=10;
     SPAWN_AT(902,static_cast<float>(C(0x104)*(random_float(150)+25.0)+F(0xEC)),static_cast<float>(F(0xF0)+50.0),1,3);
    }
    if(I(0x144)>=H[1] || AT(P,short,0x174)<=0) goto next_block_857_902;
   }
   break;
  case 9:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(B(0x113)<15) RETIRE(); B(0x113)-=15; break;
  case 10:
   F(0xF8)-=D(0.4f); if(F(0xF8)<-3.0f) F(0xF8)=-3;
   F(0xF4)*=D(0.99f);
   if(F(0x370)>0.0f && F(0x370)<0.5f) F(0x370)=0.5f;
   if(F(0x370)<0.0f && F(0x370)>-0.5f) F(0x370)=-0.5f;
   F(0x12C)+=F(0x370); F(0x370)*=D(0.98f);
   if(I(0x144)>=300 || C(0x184)<=0 || AT(P,short,0x174)<=0) { B(0x184)=0; if(B(0x113)<5) RETIRE(); B(0x113)-=5; } STEP(); break;
  }
  if(advance_frame()) --I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==9) RETIRE();
  if(S(0x13E)==0 && S(0x142)==0 && S(0x140)==1) {
   for(int n=0;n<3;++n) { payload[0]=-random_float(90)-45.0; payload[1]=random_float(70)*D(0.1f)+10.0; payload[2]=1; SPAWN(902,1,3); }
  }
  return;
 case 930:
  switch(S(0x13E)) {
  case 0:
   if(S(0x364)!=0) { F(0x120)*=D(0.99f); if(B(0x113)<15) RETIRE(); B(0x113)-=15; }
   else {
    if(AT(P,short,0x174)<=0) { S(0x364)=1; return; }
    F(0x11C)+=D(0.2f); F(0x120)+=D(0.005f);
    if(I(0x144)>=60) {
     payload[0]=F(0x12C); payload[1]=0; payload[2]=6; SPAWN(930,1,3);
     P->dispatch_character_wave_handle(51); F(0x120)=3; B(0x184)=1; next_sequence_block(); return;
    }
   }
   break;
  case 1:
   F(0xF8)*=D(0.9f); F(0xF4)*=D(0.98f);
   if(I(0x144)>=10 || AT(P,short,0x174)<=0) {
    AT(P,unsigned char,0x7FC)=0; if(B(0x113)<15) RETIRE(); B(0x113)-=15;
   } else { AT(P,unsigned char,0x7FC)=1; AT(P,float,0x7F0)=F(0xEC); AT(P,float,0x7F4)=F(0xF0); AT(P,float,0x7F8)=F(0x12C); }
   break;
  case 2:
   if(S(0x140)==0) {
    if(I(0x144)>=300 || C(0x184)<=0 || AT(P,short,0x174)<=0) { next_sequence_frame(); B(0x184)=0; return; }
   } else {
    B(0x184)=0; F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.95f)); F(0xF4)=0; F(0xF8)=0;
    if(B(0x113)<5) RETIRE(); B(0x113)-=5;
   }
   if(F(0xEC)<-100.0 || F(0xEC)>1380.0f || F(0xF0)<-200.0 || F(0xF0)>1000.0) RETIRE(); STEP(); break;
  case 3:
   if(S(0x364)==0) {
    if(g_match_identifier!=0 && AT(P,unsigned char,0x7FC)!=0) {
     float const dx=F(0xEC)-AT(P,float,0x7F0),dy=F(0xF0)-AT(P,float,0x7F4);
     double const yy=square_float_value(dy);
     double const distance=square_float_value(dx)+yy;
     double const sine_y=lookup_orientation_sine_quantized_abs(AT(P,float,0x7F8))*dy;
     float const projected=static_cast<float>(lookup_orientation_cosine_quantized_abs(AT(P,float,0x7F8))*dx+sine_y);
     if(distance-square_float_value(projected)<=2500.0) {
      float count=dx; if(g_match_identifier==1) count=3; if(g_match_identifier==2) count=5; if(g_match_identifier==3) count=7;
      payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(930,1,3);
      for(int n=0;static_cast<float>(n)<count;++n) { payload[0]=random_float(360); payload[1]=random_float(20)*D(0.1f)+3.0; payload[2]=2; SPAWN(930,1,3); }
      RETIRE();
     }
    }
    if(I(0x144)>=300 || C(0x184)<=0 || AT(P,short,0x174)<=0) {
     payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(930,1,3); F(0x11C)=2; S(0x364)=1; F(0x120)=2;
    }
   } else {
    B(0x184)=0; F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.95f)); F(0xF4)=0; F(0xF8)=0;
    if(B(0x113)<5) RETIRE(); B(0x113)-=5;
   }
   if(F(0xEC)<-100.0 || F(0xEC)>1380.0f || F(0xF0)<-200.0 || F(0xF0)>1000.0) RETIRE(); STEP(); break;
  case 4:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(B(0x113)<10) RETIRE(); B(0x113)-=10; break;
  case 6:
   F(0x11C)+=0.5; F(0x120)+=F(0x370); F(0x370)*=D(0.95f);
   if(B(0x113)<5 || I(0x144)<15) RETIRE(); B(0x113)-=5; break;
  case 7:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(B(0x113)<15) RETIRE(); B(0x113)-=15; break;
  }
  FRAME_EXIT();
 case 980:
  update_ping_pong_motion(); FRAME_EXIT();
 case 999:
  switch(S(0x13E)) {
  case 0: case 1: case 2:
   AT(P,float,0xEC)=F(0xEC);
   if(F(0xEC)>1480.0f || F(0xEC)<-200.0) RETIRE();
   if(S(0x13E)>=1) F(0xF8)-=F(0x100); break;
  case 3: {
   F(0xF8)-=D(0.1f); double const next_y=F(0xF8)+D(F(0xF0));
   if(next_y<=stage_surface_height_at_x()) {
    AT(P,short,0x78C)=1; F(0xF0)=stage_surface_height_at_x(); F(0xF4)=0; F(0xF8)=0; F(0x100)=0; select_sequence(4); return;
   }
   break;
  }
  case 5:
   if(AT(P,short,0x78E)==1) { next_sequence_block(); B(0x104)=1; return; } break;
  case 6: case 7:
   if(S(0x13E)>=7) F(0xF8)-=F(0x100); break;
  }
  STEP(); if(advance_frame()) --I(0x330);
  if(I(0x144)==0) {
   if(S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) { F(0xF4)=17.5f; F(0xF8)=15; F(0x100)=0.2f; }
   if(S(0x142)==0 && S(0x140)==0 && S(0x13E)==7) { F(0xF4)=10; F(0xF8)=14; F(0x100)=0.05f; }
  }
  return;
 default: advance_frame(); return;
 }
next_block_857_902:
 B(0x184)=0; next_sequence_block(); return;
}
#undef RADIAL_901
#undef AT
#undef F
#undef I
#undef S
#undef B
#undef C
#undef H
#undef P
#undef A
#undef D
#undef MOTION
#undef MOVE
#undef STEP
#undef FRAME_EXIT
#undef RETIRE
#undef SPAWN
#undef SPAWN_AT
#undef OUTSIDE
}
