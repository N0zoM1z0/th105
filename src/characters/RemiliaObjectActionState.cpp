// JP1.06a 0x00557690: complete source, currently nonexact.
// See docs/REMILIA_OBJECT_UPDATE_2026_10_25.md.
#include "characters/RemiliaObjectActionState.hpp"
#include <math.h>
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define I(o) AT(this,int,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define H AT(this,float *,0x340)
#define P AT(this,RemiliaObjectUpdateView *,0x348)
#define T AT(this,RemiliaObjectUpdateView *,0x34C)
#define A AT(this,RemiliaObjectUpdateView *,0x170)
#define D(v) static_cast<double>(v)
#define MOTION reinterpret_cast<RemiliaUpdateMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define MOVE() MOTION->set_components(H[0],H[1])
#define SPAWN(a,l,c) spawn_unparented(a,F(0xEC),F(0xF0),B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define SPAWN_AT(a,x,y,l,c) spawn_unparented(a,x,y,B(0x104),l,reinterpret_cast<const unsigned *>(payload),c)
#define OUTSIDE(xhi,xlo,yhi,ylo) (F(0xEC)>xhi || F(0xEC)<xlo || F(0xF0)>yhi || F(0xF0)<ylo)
#define ACTIVE_821(period) { \
 if(emit_repeated(0,3,5)) goto retire; \
 if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; } \
 advance_phase(5); int const state=I(0x180); \
 if(state==4 || state==8) B(0x184)=0; \
 if(state!=0 && ++S(0x364)>=3 && C(0x184)>0) { I(0x180)=0; S(0x364)=0; } \
 if(I(0x144)%period==0) { float payload[3]; payload[0]=F(0x12C); payload[1]=0; payload[2]=1; SPAWN(821,1,3); } \
 MOVE(); F(0x12C)=H[0]; \
}
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void RemiliaObjectUpdateView::update_action_state()
{
 switch(S(0x13C)) {
 case 800: {
  if(I(0x180)==5 || OUTSIDE(1380.0f,-100.0,1060.0f,-100.0)) goto retire;
  if(S(0x13E)==0) {
   if(emit_repeated(0,0,3)) goto retire;
   if(S(0x142)>=90 || I(0x180)!=0) {
    --I(0x330); float payload[3]; payload[2]=2;
    for(int n=0;n<3;++n) { payload[0]=random_float(360); payload[1]=random_float(5)+10.0; SPAWN(800,1,3); }
    payload[2]=3;
    for(int n=0;n<3;++n) { payload[0]=random_float(360); payload[1]=random_float(10)+5.0; SPAWN(800,1,3); }
    return;
   }
  }
  if(S(0x13E)==1) {
   if(!T) goto retire;
   F(0xEC)=AT(T,float,0xEC); F(0xF0)=AT(T,float,0xF0); B(0x104)=AT(T,unsigned char,0x104);
   F(0x12C)=AT(T,float,0x12C); F(0xF4)=AT(T,float,0xF4); F(0xF8)=AT(T,float,0xF8);
  }
  if(S(0x13E)==2 || S(0x13E)==3) { F(0xF8)-=0.5; if(B(0x113)<10) goto retire; B(0x113)-=10; }
  goto move_and_advance;
 }
 case 801: {
  if(I(0x180)==5) goto retire;
  if(S(0x13E)==0) {
   if(emit_repeated(0,2,2)) goto retire;
   if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==0) replace_secondary(991,20,20,1,2);
   if(I(0x180)==6 && ++S(0x384)<10) { ++B(0x184); I(0x180)=0; }
   advance_phase(1);
   int const state=I(0x180);
   if(state==4 || state==8) B(0x184)=0;
   if(state!=0) {
    H[1]=2; ++S(0x364);
    if(S(0x364)>=3) { if(C(0x184)<=0) goto burst_801; I(0x180)=0; S(0x364)=0; }
   }
   if(C(0x184)<=0) {
   burst_801:
    float payload[3]; payload[0]=0; payload[1]=0; payload[2]=1; SPAWN(801,1,3); goto retire;
   }
   H[1]+=0.5; if(H[1]>=6.0f) turn_heading(0,0.5f,100);
   if(H[1]>12.0f) H[1]=12;
   MOVE(); F(0x12C)=H[0];
  }
  if(S(0x13E)==1) { F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.9f)); if(I(0x144)>=10) { if(B(0x113)<10) goto retire; B(0x113)-=10; B(0x111)-=10; B(0x110)-=10; } }
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0)) goto retire;
  goto move_and_advance;
 }
 case 810:
  if(I(0x180)==5) goto retire;
  if(S(0x13E)==0) {
   H[1]*=D(0.9f); MOVE();
   if(I(0x144)>=15) { if(B(0x113)<10) goto retire; B(0x113)-=10; }
   F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8)*D(0.15f);
  }
  goto advance;
 case 811:
  if(AT(P,short,0x13C)!=505 && AT(P,short,0x13C)!=506) goto retire;
  switch(S(0x13E)) { case 0: if(AT(P,short,0x13E)==0) position_relative(0,0); break; case 1: if(AT(P,short,0x13E)==1) position_relative(0,0); break; case 2: if(AT(P,short,0x13E)==2) position_relative(0,0); break; }
  if(advance_frame()) --I(0x330);
  if(I(0x144)!=0) return;
  if(S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) --I(0x330);
  if(I(0x144)!=0) return;
  if(S(0x142)!=0 || S(0x140)!=0 || S(0x13E)!=2) return;
  goto retire;
 case 815: {
  if(I(0x180)==5) goto retire;
  switch(S(0x13E)) {
  case 0: {
   if(emit_repeated(0,1,2)) goto retire;
   float *const input=H;
   F(0x11C)=1.0f-F(0x370); F(0x370)*=D(0.85f); F(0x120)=F(0x11C);
   F(0x12C)=F(0x378)+F(0x374); F(0x374)*=D(0.95f); F(0x378)=F(0x37C)+F(0x378);
   if(static_cast<float>(I(0x144))>=input[3]) {
    P->dispatch_character_wave_handle(1); float payload[3]; payload[0]=0; payload[1]=15; payload[2]=1; SPAWN(815,1,3); payload[2]=2; SPAWN(815,1,3); payload[2]=3; SPAWN(815,1,3); goto retire;
   }
   MOTION->set_components(input[0],input[1]); H[1]*=D(0.95f);
   F(0xF4)=F(0x380)+F(0xF4); F(0x380)*=D(0.95f);
   F(0xEC)+=C(0x104)*F(0xF4)*0.25; F(0xF0)+=F(0xF8); break;
  }
  case 1:
   if(emit_repeated(0,1,2)) goto retire;
   if(I(0x180)==6 && ++S(0x384)<10) { ++B(0x184); I(0x180)=0; }
   advance_phase(3);
   if(I(0x180)!=0) { H[1]=2; ++S(0x364); if(S(0x364)>=3) { if(C(0x184)<=0) goto retire; I(0x180)=0; S(0x364)=0; } }
   if(C(0x184)<=0) goto retire;
   H[1]+=0.5; if(H[1]>=6.0f) turn_heading(0,0.5f,100); if(H[1]>12.0f) H[1]=12;
   MOVE(); F(0x12C)=H[0]; F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8); break;
  case 2:
   if(B(0x113)<5) goto retire;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x370)+F(0x11C)); F(0x370)*=D(0.9f);
   B(0x111)-=5; B(0x110)-=5; B(0x113)-=5; break;
  case 3:
   if(B(0x113)<5) goto retire;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x370)+F(0x11C)); F(0x12C)-=F(0x374);
   F(0x374)*=D(0.9f); F(0x370)=D(0.9f)*F(0x370);
   B(0x111)-=5; B(0x110)-=5; B(0x113)-=5; break;
  }
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0)) goto retire;
  goto advance;
 }
 case 816: {
  if(I(0x180)==5) goto retire;
  switch(S(0x13E)) {
  case 0:
   if((AT(P,short,0x13C)==525 || AT(P,short,0x13C)==526) && AT(P,short,0x13E)<3) position_relative(20,100);
   else { F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.9f)); goto fade_816; }
   break;
  case 1: case 2: {
   if(emit_repeated(0,0,2)) goto retire;
   if(I(0x144)==1 && (AT(P,short,0x13C)==525 || AT(P,short,0x13C)==526) && (AT(P,short,0x13E)==1 || AT(P,short,0x13E)==2)) {
    F(0x378)=H[0];
    float const wanted=-atan2_degrees(static_cast<float>(AT(A,float,0xF0)+100.0-F(0xF0)),static_cast<float>((AT(A,float,0xEC)-F(0xEC))*C(0x104)));
    float *const input=H;
    float const delta=static_cast<float>(wanted-input[0]); float diff=static_cast<float>(static_cast<int>(delta)%360);
    if(diff>180.0f) diff-=360.0;
    if(diff<-180.0f) diff=360.0+diff;
    float const magnitude=static_cast<float>(fabs(diff));
    if(magnitude<=20.0f) F(0x378)=wanted;
    else if(diff<0.0f) F(0x378)-=20.0;
    else if(diff>0.0f) F(0x378)+=20.0;
    float payload[4]; payload[0]=F(0x378); payload[1]=0; payload[3]=input[3]+1.0;
    if(S(0x13E)==1) { payload[2]=2; SPAWN_AT(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-input[0])*28.0+F(0xF0)),1,4); }
    else { payload[2]=1; SPAWN_AT(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-input[0])*28.0+F(0xF0)),1,4); }
    payload[2]=3;
    SPAWN_AT(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-H[0])*28.0+F(0xF0)),1,4);
    dispatch_slot20();
   }
   if(I(0x144)>=90) {
    float payload[4]; payload[0]=0; payload[1]=0; payload[2]=4; payload[3]=0;
    SPAWN_AT(816,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-H[0])*28.0+F(0xF0)),1,4);
    P->dispatch_character_wave_handle(17); goto retire;
   }
   break;
  }
  case 3: scale3_816: F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.9f)); if(I(0x144)>=4) goto fade_816; break;
  case 4: scale4_816: F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.9f)); if(I(0x144)>=4) { B(0x184)=0; goto fade_816; } break;
  fade_816:
   if(B(0x113)<30) goto retire; B(0x113)-=30; break;
  }
  goto advance;
 }
 case 817:
  if(I(0x180)==5 || OUTSIDE(1480.0f,-200.0,1160.0f,-400.0)) goto retire;
  if(S(0x13E)==0) {
   if(emit_repeated(0,1,4)) goto retire;
   if(I(0x180)==6) { ++B(0x184); I(0x180)=0; }
   if(C(0x184)<=0) { if(B(0x113)<15) goto retire; B(0x111)-=15; B(0x110)-=15; B(0x113)-=15; }
   else if(I(0x144)%2==0) { float payload[3]; payload[0]=F(0x12C); payload[1]=0; payload[2]=2; SPAWN(817,1,3); }
   MOVE(); F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8);
  }
  if(S(0x13E)==2) { F(0x11C)+=D(0.05f); F(0x120)*=D(0.95f); if(B(0x113)<15) goto retire; B(0x111)-=15; B(0x110)-=15; B(0x113)-=15; }
  goto advance;
 case 820:
  if(S(0x13E)==0) {
   if(AT(P,short,0x13C)!=540) goto retire;
   if(AT(P,short,0x13E)<4) position_relative(0,0);
   else { if(B(0x113)<=20) goto retire; goto fade_820; }
  } else if(S(0x13E)==1) {
   if(AT(P,short,0x13C)!=541) goto retire;
   if(AT(P,short,0x13E)>3) { if(B(0x113)<=20) goto retire; goto fade_820; }
   position_relative(0,0);
  }
  goto parent_hitstop_820;
 fade_820: B(0x113)-=20; B(0x111)-=20; B(0x110)-=20;
 parent_hitstop_820: if(AT(P,short,0x186)!=0) return; goto advance;
 case 821:
  if(I(0x180)==5) goto retire;
  if(S(0x13E)==0) ACTIVE_821(10);
  if(S(0x13E)==1) {
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.15f));
   if(I(0x144)>=10) { if(B(0x113)<10) goto retire; B(0x111)-=10; B(0x110)-=10; B(0x113)-=10; }
  }
  if(S(0x13E)==2) {
   float *const input=H; F(0x120)=F(0x11C)=static_cast<float>(input[1]+F(0x11C)); input[1]*=D(0.8f);
   if(B(0x113)<10) goto retire; B(0x111)-=10; B(0x110)-=10; B(0x113)-=10;
  }
  if(S(0x13E)==3) ACTIVE_821(7);
  if(S(0x13E)==4) ACTIVE_821(5);
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0)) goto retire;
  goto move_and_advance;
 case 825:
  if(S(0x13E)==0) {
   if((AT(P,short,0x13C)!=560 && AT(P,short,0x13C)!=561) || AT(P,short,0x13E)!=4) goto retire;
   position_relative(0,0);
  }
  goto advance;
 case 826: {
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0) || I(0x180)==5) goto retire;
  switch(S(0x13E)) {
  case 0:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(B(0x113)<15) goto retire;
   B(0x111)-=15; B(0x110)-=15; B(0x113)-=15; break;
  case 1:
   MOVE(); H[1]-=0.5; if(H[1]<0.5f) H[1]=0.5f;
   F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8)*0.25;
   F(0x12C)=F(0x374)+F(0x12C); F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.02f));
   if(I(0x144)>=0) { if(B(0x113)<=5) goto retire; B(0x113)-=5; } break;
  case 2: {
   RemiliaObjectUpdateView *const parent=P;
   if((AT(parent,short,0x13C)!=565 && AT(parent,short,0x13C)!=566) || AT(parent,short,0x13E)!=3) goto retire;
   F(0xEC)=C(0x104)*AT(parent,float,0xF4)+AT(parent,float,0xEC); F(0xF0)=AT(parent,float,0xF8)+AT(parent,float,0xF0); break;
  }
  case 3:
   F(0x12C)+=5.0; F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.05f));
   if(B(0x113)<=10) goto retire; B(0x113)-=10; break;
  case 4: {
   if(I(0x180)==6) { ++B(0x184); I(0x180)=0; }
   double const y=F(0xF0);
   if(y-stage_surface_height_at_x()>10.0) --I(0x330);
   else { double const next_y=F(0xF0); if(next_y-stage_surface_height_at_x()<-10.0 || C(0x184)<=0) --I(0x330); }
   MOVE(); H[1]-=3.0; if(H[1]<0.5f) H[1]=0.5f;
   F(0xEC)+=F(0xF4)*C(0x104); F(0xF0)=static_cast<float>(F(0xF8)+F(0xF0));
   float payload[3]; payload[0]=0; payload[1]=0; payload[2]=5;
   SPAWN_AT(826,static_cast<float>(random_float(40)+F(0xEC)-20.0),F(0xF0),1,3); break;
  }
  case 5: case 7:
   F(0x11C)+=D(0.05f); F(0x120)*=D(0.98f);
   if(I(0x144)>=0) { if(B(0x113)<=10) goto retire; B(0x113)-=10; B(0x111)-=10; B(0x110)-=10; } break;
  case 6: {
   if(I(0x180)==6) { ++B(0x184); I(0x180)=0; }
   double const y=F(0xF0);
   if(y-stage_surface_height_at_x()>10.0) --I(0x330);
   else { double const next_y=F(0xF0); if(next_y-stage_surface_height_at_x()<-10.0 || C(0x184)<=0) --I(0x330); }
   MOVE(); H[1]-=3.0; if(H[1]<0.5f) H[1]=0.5f;
   F(0xEC)+=F(0xF4)*C(0x104); F(0xF0)=static_cast<float>(F(0xF8)+F(0xF0));
   float payload[3]; payload[0]=0; payload[1]=0; payload[2]=7;
   SPAWN_AT(826,static_cast<float>(random_float(40)+F(0xEC)-20.0),F(0xF0),1,3); break;
  }
  }
  if(advance_frame()) --I(0x330);
  if(I(0x144)!=0) return;
  if(S(0x142)==0 && S(0x140)==0 && S(0x13E)==5) goto retire;
  if(I(0x144)!=0 || S(0x142)!=0 || S(0x140)!=0 || S(0x13E)!=7) return;
  goto retire;
 }
 case 848:
  switch(S(0x13E)) {
  case 0: position_relative(0,0); if(AT(P,short,0x13C)!=302 && AT(P,short,0x13C)!=322) goto retire; if(AT(P,short,0x140)==0) goto retire; break;
  case 1: case 2: position_relative(0,0); if(AT(P,short,0x13C)!=321) goto retire; if(AT(P,short,0x140)==0) goto retire; break;
  case 3: position_relative(0,0); if(AT(P,short,0x13C)!=303) goto retire; if(AT(P,short,0x140)==0) goto retire; break;
  case 4: position_relative(0,0); if(AT(P,short,0x13C)!=308 || AT(P,short,0x140)==0) goto retire; break;
  }
  if(AT(P,short,0x186)!=0) return;
  if(advance_frame()) goto retire;
  if(S(0x13E)>9 || S(0x140)!=0 || S(0x142)!=0) return;
  goto retire;
 case 850:
  if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
  if(I(0x180)!=0 && ++S(0x364)>=6) { I(0x180)=0; B(0x184)=1; S(0x364)=0; }
  if(S(0x13E)<=1) {
   if(AT(P,short,0x13C)!=600 || AT(P,short,0x13E)>=4) { select_sequence(2); B(0x184)=0; return; }
   F(0xEC)=AT(P,float,0xEC);
  }
  F(0xF0)=stage_surface_height_at_x(); goto advance;
 case 851:
  switch(S(0x13E)) {
  case 0: case 1:
   if(AT(P,short,0x13C)!=601) goto retire; position_relative(0,0); break;
  case 2: {
   if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
   MOVE(); float const angle=H[0]; F(0x12C)=angle;
   if(F(0xEC)>1680.0 || F(0xEC)<-400.0) goto retire;
   float payload[3]; payload[0]=angle; payload[1]=5; payload[2]=3; SPAWN(851,1,3); break;
  }
  case 3:
   if(B(0x113)<5) goto retire;
   B(0x113)-=5; B(0x111)-=5; B(0x110)-=5; F(0x120)*=D(0.95f); F(0x11C)+=D(0.01f);
   { float *const input=H; F(0x12C)=input[0]; input[1]=D(0.95f)*input[1]; }
   MOVE(); break;
  case 4:
   if(B(0x113)<5) goto retire;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x370)+F(0x11C));
   B(0x111)-=5; B(0x110)-=5; B(0x113)-=5; F(0x370)*=D(0.9f); break;
  }
  F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8);
  if(advance_frame()) --I(0x330);
  if(I(0x144)!=0 || S(0x142)!=0 || S(0x140)!=0 || S(0x13E)!=2) return;
  goto retire;
 case 852:
  if(S(0x13E)==0 || S(0x13E)==1) {
   if(B(0x113)<10) goto retire;
   B(0x113)-=10; B(0x111)-=10; B(0x110)-=10;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x370)+F(0x11C)); F(0x12C)-=F(0x374);
   F(0x374)*=D(0.9f); F(0x370)=D(0.9f)*F(0x370);
  }
  goto advance;
 case 853:
  if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
  if(I(0x180)!=0 && ++S(0x364)>=6) { I(0x180)=0; B(0x184)=1; S(0x364)=0; }
  if(S(0x13E)<=1) {
   if(AT(P,short,0x13C)!=603 || AT(P,short,0x13E)>=3) { select_sequence(2); B(0x184)=0; return; }
   F(0xEC)=AT(P,float,0xEC); F(0xF0)=stage_surface_height_at_x();
  }
  if(S(0x13E)==4) {
   F(0x120)=F(0x11C)=static_cast<float>(1.0f-F(0x370)); F(0x370)*=D(0.85f);
   if(S(0x364)==0) {
    if(AT(P,short,0x13C)==603 && AT(P,short,0x13E)<3) F(0xEC)=AT(P,float,0xEC);
    else S(0x364)=1;
   }
   if(S(0x364)==1) { if(B(0x113)<=20) goto retire; B(0x113)-=20; }
   F(0xF0)=stage_surface_height_at_x();
  }
  if(S(0x13E)==5) {
   if(S(0x140)==17) { if(B(0x113)<=10) goto retire; B(0x113)-=10; B(0x111)-=10; B(0x110)-=10; }
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.6f)); F(0xF0)=AT(P,float,0xF0)+200.0; F(0xEC)=AT(P,float,0xEC);
  }
  if(S(0x13E)==6) { F(0xF8)=static_cast<float>(F(0xF8)+0.25); F(0xF0)=static_cast<float>(F(0xF8)+F(0xF0)); if(F(0xF0)>=1400.0f) goto retire; }
  goto advance;
 case 854:
  switch(S(0x13E)) {
  case 0: case 1: if(AT(P,short,0x13C)!=604) goto retire; position_relative(0,0); break;
  case 2: {
   if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
   if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>=2) { S(0x364)=0; I(0x180)=0; }
   MOVE(); float const angle=H[0]; F(0x12C)=angle;
   if(F(0xEC)>1680.0 || F(0xEC)<-400.0) goto retire;
   float payload[3]; payload[0]=angle; payload[1]=5; payload[2]=3; SPAWN(854,1,3);
   if(I(0x144)%2==0) {
    double const y=F(0xF0);
    if(stage_surface_height_at_x()<=y) {
     double const next_y=F(0xF0);
     if(next_y-stage_surface_height_at_x()<=300.0) {
      float ground_payload[3]; ground_payload[0]=0; ground_payload[1]=0; ground_payload[2]=7;
      spawn_unparented(854,F(0xEC),stage_surface_height_at_x(),B(0x104),1,reinterpret_cast<const unsigned *>(ground_payload),3);
     }
    }
   } break;
  }
  case 3:
   if(B(0x113)<5) goto retire;
   B(0x113)-=5; B(0x111)-=5; B(0x110)-=5; F(0x120)*=D(0.95f); F(0x11C)+=D(0.01f);
   { float *const input=H; F(0x12C)=input[0]; input[1]=D(0.95f)*input[1]; }
   MOVE(); break;
  case 4:
   if(B(0x113)<5) goto retire;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x370)+F(0x11C)); B(0x111)-=5; F(0x370)*=D(0.9f); B(0x110)-=5; B(0x113)-=5; break;
  case 5:
   if(B(0x113)<5) goto retire;
   B(0x111)-=5; B(0x110)-=5; B(0x113)-=5;
   F(0x120)=F(0x11C)=static_cast<float>(F(0x370)+F(0x11C)); F(0x12C)-=F(0x374); F(0x374)*=D(0.9f); F(0x370)=D(0.9f)*F(0x370); break;
  case 6: if(!T) goto retire; F(0xEC)=AT(T,float,0xEC); F(0xF0)=AT(T,float,0xF0); break;
  case 7:
   if(B(0x113)<5) goto retire;
   F(0x11C)=F(0x370)+F(0x11C); F(0x120)*=D(0.95f); B(0x111)-=5; B(0x110)-=5; B(0x113)-=5; F(0x370)*=D(0.9f); break;
  }
  F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8);
  if(advance_frame()) --I(0x330);
  if(I(0x144)!=0 || S(0x142)!=0 || S(0x140)!=0 || S(0x13E)!=2) return;
  goto retire;
 case 855:
  if(S(0x13E)==0 || S(0x13E)==1) goto fade_855;
  if(S(0x13E)==2) {
   F(0x120)=F(0x11C)=static_cast<float>(1.0f-F(0x370)); F(0x370)*=D(0.9f);
   if(AT(P,short,0x13C)!=605 || AT(P,short,0x13E)>2) goto retire;
   position_relative(90,125);
  }
  goto advance;
 case 856:
  if(S(0x13E)==0 || S(0x13E)==1) goto fade_855;
  if(S(0x13E)==2) {
   F(0x120)=F(0x11C)=static_cast<float>(1.0f-F(0x370)); F(0x370)*=D(0.9f);
   if(AT(P,short,0x13C)!=606 || AT(P,short,0x13E)!=4) goto retire;
   position_relative(90,25);
  }
  goto advance;
 case 857: {
  switch(S(0x13E)) {
  case 0:
   if(AT(P,short,0x13C)!=607 || AT(P,short,0x13E)>=2) { F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.9f)); goto fade_816; }
   position_relative(20,100); break;
  case 1: case 2: {
   if(AT(P,short,0x174)<=0) goto retire;
   if(I(0x144)==1 && AT(P,short,0x13C)==607 && AT(P,short,0x13E)<=1 && H[3]<=45.0f) {
    F(0x378)=H[0];
    float const wanted=-atan2_degrees(static_cast<float>(AT(A,float,0xF0)+100.0-F(0xF0)),static_cast<float>((AT(A,float,0xEC)-F(0xEC))*C(0x104)));
    float *const input=H;
    float const delta=static_cast<float>(wanted-input[0]); float diff=static_cast<float>(static_cast<int>(delta)%360);
    if(diff>180.0f) diff-=360.0;
    if(diff<-180.0f) diff=360.0+diff;
    float const magnitude=static_cast<float>(fabs(diff));
    if(magnitude<=7.0) F(0x378)=wanted;
    else if(diff<0.0f) F(0x378)-=7.0;
    else if(diff>0.0f) F(0x378)+=7.0;
    float payload[4]; payload[0]=F(0x378); payload[1]=0; payload[3]=input[3]+1.0;
    if(S(0x13E)==1) { payload[2]=2; SPAWN_AT(857,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-input[0])*28.0+F(0xF0)),1,4); }
    else { payload[2]=1; SPAWN_AT(857,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-input[0])*28.0+F(0xF0)),1,4); }
    payload[2]=3; SPAWN_AT(857,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-H[0])*28.0+F(0xF0)),1,4);
    dispatch_slot20();
   }
   if(I(0x144)>=30) {
    float payload[4]; payload[0]=0; payload[1]=0; payload[2]=4; payload[3]=0;
    SPAWN_AT(857,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-H[0])*28.0+F(0xF0)),1,4);
    P->dispatch_character_wave_handle(17); goto retire;
   } break;
  }
  case 3: goto scale3_816;
  case 4: goto scale4_816;
  }
  goto advance;
 }
 case 900: {
  if(I(0x180)==5) goto retire;
  switch(S(0x13E)) {
  case 0:
   if((AT(P,short,0x13C)!=710 && AT(P,short,0x13C)!=711) || (AT(P,short,0x13C)==710 && AT(P,short,0x13E)>=2) || (AT(P,short,0x13C)==711 && AT(P,short,0x13E)>=3)) {
    F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.9f)); goto fade_816;
   }
   if(AT(P,short,0x13C)==710) position_relative(20,100);
   if(AT(P,short,0x13C)==711) position_relative(0,200);
   break;
  case 1: case 2: {
   if(AT(P,short,0x174)<=0) goto retire;
   if(I(0x144)==1 && ((AT(P,short,0x13C)==710 && AT(P,short,0x13E)<=1) || (AT(P,short,0x13C)==711 && AT(P,short,0x13E)<=2))) {
    F(0x378)=H[0];
    float const wanted=-atan2_degrees(static_cast<float>(AT(A,float,0xF0)+100.0-F(0xF0)),static_cast<float>((AT(A,float,0xEC)-F(0xEC))*C(0x104)));
    float *const input=H;
    float const delta=static_cast<float>(wanted-input[0]); float diff=static_cast<float>(static_cast<int>(delta)%360);
    if(diff>180.0f) diff-=360.0;
    if(diff<-180.0f) diff=360.0+diff;
    float const magnitude=static_cast<float>(fabs(diff));
    if(magnitude<=7.0) F(0x378)=wanted;
    else if(diff<0.0f) F(0x378)-=7.0;
    else if(diff>0.0f) F(0x378)+=7.0;
    float payload[4]; payload[0]=F(0x378); payload[1]=0; payload[3]=input[3]+1.0;
    if(S(0x13E)==1) { payload[2]=2; SPAWN_AT(900,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-input[0])*28.0+F(0xF0)),1,4); }
    else { payload[2]=1; SPAWN_AT(900,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-input[0])*28.0+F(0xF0)),1,4); }
    payload[2]=3; SPAWN_AT(900,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-H[0])*28.0+F(0xF0)),1,4);
    dispatch_slot20();
   }
   if(I(0x144)>=45) {
    float payload[4]; payload[0]=0; payload[1]=0; payload[2]=4; payload[3]=0;
    SPAWN_AT(900,static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*28.0*C(0x104)+F(0xEC)),static_cast<float>(lookup_orientation_sine_quantized_abs(-H[0])*28.0+F(0xF0)),1,4);
    P->dispatch_character_wave_handle(17); goto retire;
   } break;
  }
  case 3: goto scale3_816;
  case 4: goto scale4_816;
  }
  goto advance;
 }
 case 901: {
  if(OUTSIDE(1380.0f,-100.0,1360.0f,-100.0) || I(0x180)==5) goto retire;
  switch(S(0x13E)) {
  case 0:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.2f));
   if(B(0x113)<15) goto retire; B(0x111)-=15; B(0x110)-=15; B(0x113)-=15; break;
  case 1:
   MOVE(); H[1]-=0.5; if(H[1]<0.5f) H[1]=0.5f;
   F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8)*0.25;
   F(0x12C)=F(0x374)+F(0x12C); F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.02f));
   if(I(0x144)>=0) { if(B(0x113)<=5) goto retire; B(0x113)-=5; } break;
  case 2:
   if(AT(P,short,0x13C)!=720 || AT(P,short,0x13E)!=3) goto retire;
   goto parent_motion_901;
  case 3: case 10:
   F(0x12C)+=5.0; F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.05f));
   if(B(0x113)<=10) goto retire; B(0x113)-=10; break;
  case 4: {
   if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
   if(I(0x180)!=0 && ++S(0x364)>=5) { S(0x364)=0; B(0x184)=1; I(0x180)=0; }
   double const y=F(0xF0);
   if(y-stage_surface_height_at_x()>10.0) --I(0x330);
   else { double const next_y=F(0xF0); if(next_y-stage_surface_height_at_x()<-10.0) --I(0x330); }
   MOVE(); if(H[1]<0.5f) H[1]=0.5f;
   F(0xEC)+=F(0xF4)*C(0x104); F(0xF0)=static_cast<float>(F(0xF8)+F(0xF0));
   float payload[3]; payload[0]=0; payload[1]=0; payload[2]=5;
   SPAWN_AT(901,static_cast<float>(random_float(40)+F(0xEC)-20.0),F(0xF0),1,3); break;
  }
  case 5:
   F(0x11C)+=D(0.05f); F(0x120)*=D(0.98f);
   if(I(0x144)>=0) { if(B(0x113)<=10) goto retire; B(0x113)-=10; B(0x111)-=10; B(0x110)-=10; } break;
  case 6:
   F(0x12C)+=3.0;
   if(AT(P,short,0x13C)!=720 || AT(P,short,0x13E)>=4) S(0x364)=1;
   if(S(0x364)!=0) { if(B(0x113)<=15) goto retire; B(0x111)-=15; B(0x110)-=15; B(0x113)-=15; }
   else {
    if(B(0x113)<250) B(0x113)+=5; else B(0x113)=255;
    F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)+D(0.05f)); F(0xEC)=AT(P,float,0xEC);
   } break;
  case 7:
   if(I(0x180)==6 && ++S(0x384)<10) { ++B(0x184); I(0x180)=0; }
   if(I(0x144)%5==0) { float payload[3]; payload[0]=F(0x12C); payload[1]=0; payload[2]=8; SPAWN(901,1,3); }
   if(I(0x180)!=0) goto retire;
   F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8); break;
  case 8:
   if(B(0x113)<=15) goto retire; B(0x111)-=15; B(0x110)-=15; B(0x113)-=15; break;
  case 9:
   if(AT(P,short,0x13C)!=721 || AT(P,short,0x13E)!=4) goto retire;
  parent_motion_901:
   F(0xEC)=AT(P,float,0xF4)*C(0x104)+AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF8)+AT(P,float,0xF0); break;
  }
  if(advance_frame()) --I(0x330);
  if(I(0x144)!=0 || S(0x142)!=0 || S(0x140)!=0 || S(0x13E)!=6) return;
  goto retire;
 }
 case 902:
  if(I(0x180)==5) goto retire;
  switch(S(0x13E)) {
  case 0:
   if(AT(P,short,0x174)<=0 || I(0x144)>=120) goto burst_902;
   if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==0) replace_secondary(991,20,10,1,2);
   if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; }
   H[1]+=0.25; MOVE(); break;
  case 1:
   if(AT(P,short,0x174)<=0 || I(0x144)>=60) goto burst_902;
   if(S(0x364)==0) {
    if(B(0x113)<=245) B(0x113)+=10;
    else { B(0x113)=255; B(0x184)=1; S(0x364)=1; replace_secondary(991,20,10,1,2); }
   }
   if(I(0x180)==6) { ++S(0x384); ++B(0x184); I(0x180)=0; } break;
  case 2:
   F(0x120)=F(0x11C)=static_cast<float>((1.0f-F(0x370))*4.0); F(0x370)*=D(0.95f);
   if(I(0x144)>=15) { if(B(0x113)<5) goto retire; B(0x113)-=5; } break;
  case 3:
   MOVE(); H[1]*=D(0.95f);
   if(I(0x144)>=15) { F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.99f)); if(B(0x113)<5) goto retire; B(0x113)-=5; } break;
  case 4:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.95f)); if(B(0x113)<10) goto retire; B(0x113)-=10; break;
  case 5:
   if(I(0x180)==6 && ++S(0x384)<10) { ++B(0x184); I(0x180)=0; }
   if(AT(P,short,0x174)<=0 || I(0x144)>=240 || C(0x184)<=0) goto burst_902;
   MOVE(); F(0x12C)=H[0];
   if(OUTSIDE(1380.0f,-100.0,960.0,-200.0)) goto retire;
   break;
  }
  goto move_and_advance;
 case 903:
  if(I(0x180)==5) goto retire;
  switch(S(0x13E)) {
  case 0:
   if(S(0x364)==0) {
    F(0x11C)=static_cast<float>(F(0x11C)+D(0.3f)); if(F(0x11C)>=10.0f) F(0x11C)=10;
    F(0x120)=(1.0f-F(0x370))*D(0.8f)+D(0.2f); F(0x370)*=D(0.95f);
    if(AT(P,short,0x174)<=0) S(0x364)=1;
    if(AT(P,short,0x730)==2) { S(0x364)=1; float payload[3]; payload[0]=H[0]; payload[1]=40; payload[2]=1; SPAWN(903,1,3); }
    F(0xEC)=AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF0)+230.0;
   }
   if(S(0x364)==1) { if(B(0x113)<5) goto retire; B(0x110)-=5; B(0x111)-=5; B(0x113)-=5; }
   break;
  case 1:
   if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13E)==1) replace_secondary(991,60,10,1,2);
   if(AT(P,short,0x174)<=0) { B(0x184)=0; if(B(0x113)<25) goto retire; B(0x113)-=25; B(0x110)-=25; B(0x111)-=25; }
   else if(I(0x144)%2==0) { float payload[3]; payload[0]=random_float(360); payload[1]=random_float(11)+4.0; payload[2]=2; SPAWN(903,1,3); }
   MOVE(); goto bounds_903;
  case 2:
   MOVE(); H[1]*=D(0.95f); F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.99f));
   if(B(0x113)<15) goto retire; B(0x113)-=15; B(0x111)-=15; B(0x110)-=15; break;
  case 3:
   if(I(0x180)==6 && ++S(0x384)<2) { ++B(0x184); I(0x180)=0; }
   if(AT(P,short,0x174)<=0 || I(0x144)>=240 || C(0x184)<=0) { select_sequence(4); F(0xF4)=0; F(0xF8)=0; }
   MOVE(); F(0x12C)=H[0];
  bounds_903:
   if(OUTSIDE(1380.0f,-100.0,960.0,-200.0)) goto retire; break;
  case 4:
   F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.95f)); if(B(0x113)<10) goto retire; B(0x113)-=10; break;
  case 5:
   if(S(0x364)==0) {
    float *const input=H;
    double const horizontal=lookup_orientation_cosine_quantized_abs(-input[0])*input[1];
    float *const next_input=H;
    F(0xEC)=horizontal*C(0x104)+AT(P,float,0xEC);
    F(0xF0)=lookup_orientation_sine_quantized_abs(-input[0])*next_input[1]+(AT(P,float,0xF0)+230.0);
    next_input[1]*=D(0.9f); F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.99f));
    if(AT(P,short,0x13C)!=741) S(0x364)=1;
    if(I(0x144)>=20) { if(B(0x113)<5) goto retire; B(0x111)-=5; B(0x110)-=5; B(0x113)-=5; }
   }
   if(S(0x364)==1) {
    F(0x120)=F(0x11C)=static_cast<float>(F(0x11C)*D(0.99f)); if(B(0x113)<5) goto retire;
    B(0x113)-=5; B(0x111)-=5; B(0x110)-=5;
   } break;
  case 6:
   F(0x120)=F(0x11C)=static_cast<float>((1.0f-F(0x370))*4.0); F(0x370)*=D(0.95f);
   if(I(0x144)>=15) { if(B(0x113)<5) goto retire; B(0x113)-=5; } break;
  case 7:
   F(0x120)=F(0x11C)=static_cast<float>(1.0f-F(0x370)); F(0x370)*=D(0.95f);
   if(AT(P,short,0x730)!=1 || AT(P,short,0x13C)!=741) S(0x364)=1;
   if(S(0x364)!=0) { if(B(0x113)<5) goto retire; B(0x113)-=5; }
   else { if(B(0x113)<=235) B(0x113)+=20; else B(0x113)=255; F(0xEC)=AT(P,float,0xEC); F(0xF0)=AT(P,float,0xF0)+230.0; }
   break;
  }
  goto move_and_advance;
 case 980: update_ping_pong_motion(); goto advance;
 case 990:
  F(0xEC)=AT(P,float,0xEC)-C(0x104)*82; F(0xF0)=AT(P,float,0xF0)+132.0;
  if(AT(P,short,0x13C)!=600 || AT(P,short,0x13E)!=1) goto retire;
  goto advance;
 case 998:
  if(S(0x13E)==0) {
   if(AT(P,short,0x13C)>153 && AT(P,short,0x13C)<158) position_relative(55,55);
   if(AT(P,short,0x13C)>149 && AT(P,short,0x13C)<154) position_relative(35,95);
   if(AT(P,short,0x13C)==158) position_relative(85,90);
  }
  if(advance_frame()) { --I(0x330); AT(P,unsigned char,0x751)=0; } return;
 default: advance_frame(); return;
 }
 return;
 fade_855:
 if(B(0x113)<10) goto retire;
 B(0x113)-=10; B(0x111)-=10; B(0x110)-=10;
 F(0x120)=F(0x11C)=static_cast<float>(F(0x370)+F(0x11C)); F(0x12C)-=F(0x374);
 F(0x374)*=D(0.9f); F(0x370)=D(0.9f)*F(0x370); goto advance;
 burst_902: {
  float payload[3]; payload[0]=0; payload[1]=0; payload[2]=4; SPAWN(902,1,3); goto retire;
 }
 move_and_advance:
 F(0xEC)+=C(0x104)*F(0xF4); F(0xF0)+=F(0xF8);
 advance:
 if(advance_frame()) --I(0x330);
 return;
 retire:
 --I(0x330);
}
}
