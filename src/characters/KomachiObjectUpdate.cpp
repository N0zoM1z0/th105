// Manual complete-body hypothesis from JP1.06a raw instructions, 5F9420.
#include "characters/KomachiObjectUpdate.hpp"
#include <math.h>
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define I(o) AT(this,int,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define H AT(this,float *,0x340)
#define P AT(this,KomachiObjectUpdateView *,0x348)
#define A AT(this,KomachiObjectUpdateView *,0x170)
#define D(x) static_cast<double>(x)
#define RND(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
#define MOTION reinterpret_cast<KomachiUpdateMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define MOVE() MOTION->set_components(H[0],H[1])
#define STEP() {F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8);}
#define RETIRE() {--I(0x330);return;}
#define FRAME_EXIT() {if(advance_frame())--I(0x330);return;}
#define FADE(th,step) {if(B(0x113)<th)RETIRE();B(0x113)-=step;}
#define SCALE(expr) {float scale=expr;F(0x11c)=scale;F(0x120)=scale;}
#define SPAWN(a,l,p) spawn_unparented(a,F(0xec),F(0xf0),B(0x104),l,reinterpret_cast<const unsigned *>(p),3)
#define BURST(a,r,base,kind) {float n=0;do{burst_packet[0]=n*45.0+RND(40);burst_packet[1]=static_cast<float>(RND(r)*D(0.01f))+base;burst_packet[2]=kind;SPAWN(a,1,burst_packet);n+=1.0;}while(n<8.0f);}
#define TRAIL(a,kind) {trail_packet[0]=RND(360);trail_packet[1]=RND(20)*D(0.1f);trail_packet[2]=kind;float y=F(0xf0);float x=RND_OFFSET(100,50)+F(0xec);spawn_unparented(a,x,y,B(0x104),1,reinterpret_cast<const unsigned *>(trail_packet),3);}
#define RND_OFFSET(n,k) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)-k))
#define OUTSIDE(xh,xl,yh,yl) (F(0xec)>xh || F(0xec)<xl || F(0xf0)>yh || F(0xf0)<yl)
#define ORDERED_OUTSIDE(xh,xl,yh,yl) (!(F(0xec)<=xh && F(0xec)>=xl && F(0xf0)<=yh && F(0xf0)>=yl))
#define RETURN_ON_ENTRY_PHASE(p) (I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==p)
#define CURVED_FADE_VALUES() {if(S(0x364)<=I(0x144))FADE(10,10);SCALE(F(0x11c)*D(0.995f));F(0x370)+=0.25;H[0]-=D(0.2f);if(H[0]<D(0.2f))H[0]=0.2f;MOVE();F(0xf8)+=F(0x370);}
#define CURVED_FADE() {CURVED_FADE_VALUES();STEP();}
#define ORBIT_WAVE(face) {SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3))*D(0.2f)+1.0);MOVE();F(0x370)+=C(0x104)*F(0xf4);F(0x374)+=F(0xf8);double radius_wave=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*4));float radius_scale=I(0x144)*0.75;double facing=C(0x104);F(0x378)=radius_wave*radius_scale;F(0xec)=lookup_orientation_cosine_quantized_abs(static_cast<float>(C(0x104)*(-H[0]-90.0)))*F(0x378)*(face)+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(static_cast<float>(facing*(-H[0]-90.0)))*F(0x378)+F(0x374);}
#define ORBIT_WAVE_UNCAPTURED() {SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3))*D(0.2f)+1.0);MOVE();F(0x370)+=C(0x104)*F(0xf4);F(0x374)+=F(0xf8);double radius_wave=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*4));float radius_scale=I(0x144)*0.75;F(0x378)=radius_wave*radius_scale;F(0xec)=lookup_orientation_cosine_quantized_abs(static_cast<float>(C(0x104)*(-H[0]-90.0)))*F(0x378)+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(static_cast<float>(C(0x104)*(-H[0]-90.0)))*F(0x378)+F(0x374);}
void KomachiObjectUpdateView::update_action_state()
{
 float burst_packet[3],trail_packet[3],request_packet[3],motion_packet[3];
 switch(S(0x13c)) {
 case 800:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)<3 && emit_repeated(0,0,4))RETIRE();
  if(static_cast<unsigned short>(S(0x13e))<3) {
   F(0x12c)+=2.0;
   if(S(0x140)==0) {H[1]+=D(0.05f);MOVE();if(I(0x180)!=0){P->dispatch_character_wave_handle(3);F(0xf4)*=-0.5;float speed=RND(25)*D(0.1f);I(0x144)=0;F(0xf8)=speed+5.0;next_sequence_frame();return;}}
   if(S(0x140)==1) {F(0xf8)-=D(0.3f);if(I(0x144)>29)FADE(5,5);}
   STEP();
  }
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();
  if(advance_frame())RETIRE();
  if(RETURN_ON_ENTRY_PHASE(1))RETIRE();if(RETURN_ON_ENTRY_PHASE(2))RETIRE();return;
 case 801:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,3,5) || emit_owner_gated_pair())RETIRE();
   ORBIT_WAVE_UNCAPTURED();
   advance_six(0);
   if(I(0x180)!=0) {BURST(801,50,5.0,1);burst_packet[0]=F(0xf4);burst_packet[1]=F(0xf8);burst_packet[2]=0;SPAWN(826,1,burst_packet);RETIRE();}break;
  case 1: CURVED_FADE();break;
  case 2:
   if(emit_repeated(0,2,5))RETIRE();F(0x12c)-=40.0;advance_six(0);advance_phase(3);
   if(S(0x140)==0) {H[1]-=D(0.1f);if(H[1]<10.0f)H[1]=10.0f;if(I(0x180)!=0){next_sequence_frame();return;}if(I(0x144)%6==1){request_packet[0]=F(0x12c);request_packet[1]=0;request_packet[2]=3;SPAWN(801,1,request_packet);}}
   if(S(0x140)==1) {H[1]-=0.75;if(H[1]<0.5f)H[1]=0.5f;SCALE(F(0x11c)+D(0.1f));FADE(16,15);}
   MOVE();STEP();break;
  case 3:F(0x12c)-=10.0;FADE(16,15);break;
  case 4:SCALE(F(0x11c)+0.5);FADE(9,8);break;
  }
  if(OUTSIDE(1680.0,-400.0,1360.0f,-400.0))RETIRE();
  if(advance_frame())RETIRE();if(RETURN_ON_ENTRY_PHASE(1))RETIRE();if(RETURN_ON_ENTRY_PHASE(2))RETIRE();return;
 case 810:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   if(emit_repeated(0,2,5))RETIRE();if(I(0x144)%3==0)TRAIL(810,2);
   advance_six(0);
   if(I(0x180)!=0){BURST(810,150,15.0,3);RETIRE();}
   bool needs_fan=fabsf(F(0xec)-AT(A,float,0xec))<60.0 && F(0xf0)<AT(A,float,0xf0);
   if(!needs_fan){double y_before_height=F(0xf0);needs_fan=stage_surface_height()!=y_before_height;}
   if(needs_fan) {
    if(AT(P,signed char,0x604)<3){request_packet[0]=-90;request_packet[1]=0;request_packet[2]=1;SPAWN(810,1,request_packet);}
    if(AT(P,signed char,0x604)==3){request_packet[0]=-70;request_packet[1]=0;request_packet[2]=4;SPAWN(810,1,request_packet);request_packet[0]=-110;request_packet[2]=4;SPAWN(810,1,request_packet);}
    if(AT(P,signed char,0x604)==4){request_packet[0]=-70;request_packet[1]=0;request_packet[2]=4;SPAWN(810,1,request_packet);request_packet[0]=-110;request_packet[2]=4;SPAWN(810,1,request_packet);request_packet[0]=-50;request_packet[2]=4;SPAWN(810,1,request_packet);request_packet[0]=-130;request_packet[2]=4;SPAWN(810,1,request_packet);}RETIRE();
   }MOVE();break;
  }
  case 1:
   if(emit_repeated(0,2,5)||emit_owner_gated_pair())RETIRE();advance_six(0);
   if(I(0x144)%3==0){trail_packet[0]=RND(360);trail_packet[1]=RND(20)*D(0.1f);trail_packet[2]=2;float y=F(0xf0)+25.0;y-=RND(50);float x=RND_OFFSET(100,50)+F(0xec);spawn_unparented(810,x,y,B(0x104),1,reinterpret_cast<const unsigned *>(trail_packet),3);}
   if(I(0x180)!=0){BURST(810,150,15.0,3);RETIRE();}
   H[1]=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6))*3.0+5.0;MOVE();break;
  case 2:H[1]*=D(0.995f);MOVE();FADE(10,10);break;
  case 3:H[1]*=D(0.9f);MOVE();if(S(0x364)<=I(0x144)){SCALE(F(0x11c)*D(0.98f));FADE(5,5);}break;
  case 4:
   if(emit_repeated(0,1,5)||emit_owner_gated_pair())RETIRE();advance_six(0);
   if(I(0x144)%3==0){trail_packet[0]=RND(360);trail_packet[1]=RND(20)*D(0.1f);trail_packet[2]=2;float y=F(0xf0)+25.0;y-=RND(50);float x=RND_OFFSET(100,50)+F(0xec);spawn_unparented(810,x,y,B(0x104),1,reinterpret_cast<const unsigned *>(trail_packet),3);}
   if(I(0x180)!=0){BURST(810,150,15.0,3);RETIRE();}
   H[1]=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6))*3.0+5.0;MOVE();F(0x370)*=D(0.98f);F(0xf4)*=F(0x370);break;
  case 5:
   if(emit_repeated(0,1,2)||emit_owner_gated_pair())RETIRE();advance_six(0);
   if(I(0x144)%3==0){trail_packet[0]=RND(360);trail_packet[1]=RND(20)*D(0.1f);trail_packet[2]=2;float y=F(0xf0)+25.0;y-=RND(50);float x=RND_OFFSET(100,50)+F(0xec);spawn_unparented(810,x,y,B(0x104),1,reinterpret_cast<const unsigned *>(trail_packet),3);}
   if(I(0x180)!=0){BURST(810,150,15.0,3);RETIRE();}
   H[1]=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6))*3.0+5.0;MOVE();F(0x370)*=D(0.98f);F(0xf4)*=F(0x370);break;
  }
  if(OUTSIDE(1680.0,-400.0,1360.0f,-400.0))RETIRE();STEP();FRAME_EXIT();
 case 811:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)){case 0:advance_six(0);break;case 1:advance_six(0);break;case 2:advance_six(0);break;case 3:advance_six(0);break;case 4:advance_six(0);break;}
  if(advance_frame())RETIRE();
  if(RETURN_ON_ENTRY_PHASE(1)||RETURN_ON_ENTRY_PHASE(2)||RETURN_ON_ENTRY_PHASE(3)||RETURN_ON_ENTRY_PHASE(4)||RETURN_ON_ENTRY_PHASE(5))RETIRE();return;
 case 812:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   if(emit_repeated(0,2,5))RETIRE();if(I(0x144)%3==0)TRAIL(810,2);advance_six(0);
   if(I(0x180)==0){double y_before_height=F(0xf0);if(stage_surface_height()==y_before_height){MOVE();break;}}
   BURST(812,150,15.0,1);RETIRE();
  }
  case 1:H[1]*=D(0.9f);MOVE();if(S(0x364)<=I(0x144)){SCALE(F(0x11c)*D(0.98f));FADE(5,5);}break;
  case 2: {
   if(emit_repeated(0,2,5))RETIRE();if(I(0x144)%2==0)TRAIL(812,3);advance_six(0);advance_phase(3);
   if(I(0x180)==0){double y_before_height=F(0xf0);if(stage_surface_height()==y_before_height){MOVE();break;}}
   BURST(812,150,15.0,1);RETIRE();
  }
  case 3:if(B(0x113)<6)RETIRE();F(0xf8)+=F(0x370);B(0x113)-=6;break;
  }
  if(OUTSIDE(1680.0,-400.0,1360.0f,-400.0))RETIRE();STEP();FRAME_EXIT();
 case 815:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0) {
   if(emit_repeated(0,2,5)){BURST(815,50,5.0,2);RETIRE();}
   if(emit_owner_gated_pair())RETIRE();F(0xf8)-=0.5;if(F(0xf8)<-6.0f)F(0xf8)=-6.0f;advance_six(10);advance_phase(4);
   if(I(0x180)!=0 || I(0x144)>119){BURST(815,50,5.0,2);burst_packet[0]=F(0xf4);burst_packet[1]=F(0xf8);burst_packet[2]=0;SPAWN(826,1,burst_packet);RETIRE();}
  }else if(S(0x13e)==1){FADE(16,15);}else if(S(0x13e)==2){CURVED_FADE();}
  if(OUTSIDE(1380.0f,-100.0,1360.0f,-100.0))RETIRE();STEP();FRAME_EXIT();
 case 817:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){SCALE(F(0x11c)+D(0.015f));F(0x12c)-=34.0;FADE(10,10);H[1]*=D(0.85f);MOVE();STEP();}
  if(S(0x13e)==2){MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;}
  FRAME_EXIT();
 case 820:
  switch(S(0x13e)) {
  case 0:
   F(0x12c)+=2.0;
   if(S(0x364)==0){if(B(0x113)<236)B(0x113)+=20;else{B(0x113)=255;S(0x364)=1;}}
   if(S(0x364)<2){SCALE(F(0x11c)+D(0.005f));short action=AT(P,short,0x13c);if(action<540 || (action>544 && action!=731) || AT(P,short,0x738)==1){S(0x364)=2;return;}if(H[1]==0.0){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;}if(H[1]==1.0){F(0xec)=AT(A,float,0xec);F(0xf0)=AT(A,float,0xf0)+100.0;}}
   if(S(0x364)==2){SCALE(F(0x11c)+D(0.05f));FADE(10,10);}break;
  case 1:if(S(0x140)==0){SCALE(F(0x11c)+D(0.2f));}else{F(0x11c)+=D(0.02f);F(0x120)*=D(0.95f);FADE(10,10);}break;
  case 2:SCALE(F(0x11c)+D(0.3f));FADE(11,10);break;
  case 3:MOVE();H[1]*=D(0.9f);SCALE(F(0x11c)*D(0.99f));FADE(11,10);STEP();break;
  case 4:
   if(I(0x144)%10==0){trail_packet[0]=0;trail_packet[1]=0;trail_packet[2]=5;float y=(RND(50)-25.0)+F(0xf0);float x=(RND(50)-25.0)+F(0xec);spawn_unparented(820,x,y,B(0x104),-1,reinterpret_cast<const unsigned *>(trail_packet),3);}
   if(emit_repeated(0,1,1)){BURST(815,50,5.0,2);RETIRE();}if(emit_owner_gated_pair())RETIRE();F(0xf8)+=D(0.05f);
   if(I(0x180)!=0 || I(0x144)>29){BURST(815,50,5.0,2);RETIRE();}STEP();break;
  case 5:FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)-=D(0.1f);STEP();break;
  }FRAME_EXIT();
 case 821:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:SCALE(F(0x11c)*D(0.9f));if(I(0x144)<15)break;if(I(0x144)==15){request_packet[0]=H[0];request_packet[1]=0;request_packet[2]=1;SPAWN(821,1,request_packet);}FADE(10,10);break;
  case 1:advance_six(0);if(I(0x144)>3)B(0x184)=0;if(F(0x370)!=0.0){F(0x11c)=(1.0-F(0x370))*H[0];F(0x370)*=0.75;if(F(0x370)<=0.01f){F(0x370)=0;request_packet[0]=H[0];request_packet[1]=0;request_packet[2]=2;SPAWN(821,1,request_packet);request_packet[2]=3;SPAWN(821,1,request_packet);}}else{FADE(10,10);}break;
  case 2:
   F(0x370)+=2.0;F(0x370)+=(H[0]-F(0x11c))*10.0;set_sprite_uv_size(0,F(0x370));
   if(S(0x364)==0 && ((AT(P,signed char,0x60a)+6)*30<=I(0x144) || (AT(P,short,0x13e)==0 && AT(P,short,0x140)==0 && (AT(P,short,0x13c)==545 || AT(P,short,0x13c)==546))))S(0x364)=1;
   if(S(0x364)==1){FADE(5,5);F(0x11c)*=D(0.98f);}else if(fabsf(F(0xec)-AT(A,float,0xec))<=F(0x11c)*50.0)AT(A,float,0x4dc)=0.2f;break;
  case 3:
   F(0x370)+=8.0;F(0x370)+=(H[0]-F(0x11c))*30.0;set_sprite_uv_size(0,F(0x370));
   if(S(0x364)==0 && ((AT(P,signed char,0x60a)+6)*30<=I(0x144) || (AT(P,short,0x13e)==0 && AT(P,short,0x140)==0 && (AT(P,short,0x13c)==545 || AT(P,short,0x13c)==546))))S(0x364)=1;
   if(S(0x364)==1){FADE(5,5);F(0x11c)*=D(0.98f);}break;
  case 4:SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.85f);if(I(0x144)>=0)FADE(6,5);break;
  }FRAME_EXIT();
 case 822:
  if(S(0x13e)==0){B(0x33c)=lookup_orientation_sine_quantized_abs(H[0])<=0.0?1:255;H[0]+=F(0x370);H[1]*=D(0.95f);float *polar=H;F(0x374)+=F(0x378);F(0x378)+=D(0.1f);double cosine=lookup_orientation_cosine_quantized_abs(polar[0]);F(0xec)=C(0x104)*(polar[1]+50.0)*cosine+AT(P,float,0xec);double sine=lookup_orientation_sine_quantized_abs(polar[0]);F(0xf0)=(H[1]+50.0)*sine*0.25+AT(P,float,0xf0)+F(0x374);if(S(0x364)==0){if(B(0x113)>245){B(0x113)=255;S(0x364)=1;}else B(0x113)+=10;}else{FADE(7,7);}}
  FRAME_EXIT();
 case 825:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){if(emit_repeated(0,3,5)){BURST(825,50,5.0,1);RETIRE();}if(emit_owner_gated_pair())RETIRE();ORBIT_WAVE(facing);if(I(0x180)==6){++B(0x184);I(0x180)=0;}if(I(0x180)!=0){BURST(825,50,5.0,1);burst_packet[0]=F(0xf4);burst_packet[1]=F(0xf8);burst_packet[2]=0;SPAWN(826,1,burst_packet);RETIRE();}}
  else if(S(0x13e)==1){CURVED_FADE();}
  if(OUTSIDE(1480.0f,-200.0,1860.0,-600.0f))RETIRE();STEP();FRAME_EXIT();
 case 826:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){if(emit_repeated(0,0,0))RETIRE();if(I(0x144)<90){if(AT(P,int,0x7a8)!=0){select_sequence(1);request_packet[0]=0;request_packet[1]=0;request_packet[2]=2;SPAWN(826,1,request_packet);goto reset_motion_return;}}else{FADE(10,10);}SCALE(F(0x11c)*D(0.995f));F(0xf8)+=D(0.025f);H[0]*=D(0.95f);H[1]*=D(0.95f);F(0xec)+=C(0x104)*H[0];F(0xf0)+=H[1]+F(0xf8);}
  else if(S(0x13e)==1){if(I(0x144)<15)advance_six(0);else{B(0x184)=0;SCALE(F(0x11c)*D(0.95f));FADE(10,10);}}
  else if(S(0x13e)==2){SCALE(F(0x11c)+D(0.15f));FADE(20,20);}FRAME_EXIT();
 case 827:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){if(emit_owner_gated_pair())RETIRE();SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3))*D(0.2f)+1.0);KomachiObjectUpdateView *target=A;
   if((F(0xec)-AT(target,float,0xec))*C(0x104)<0.0){F(0xf4)+=D(0.2f);if(F(0xf4)>6.0f)F(0xf4)=6.0f;}
   if((F(0xec)-AT(target,float,0xec))*C(0x104)>0.0){F(0xf4)-=D(0.2f);if(F(0xf4)<-6.0f)F(0xf4)=-6.0f;}
   if(F(0xf0)-AT(target,float,0xf0)-100.0>0.0){F(0xf8)-=D(0.2f);if(F(0xf8)<-6.0f)F(0xf8)=-6.0f;}
   if(F(0xf0)-AT(target,float,0xf0)-100.0<0.0){F(0xf8)+=D(0.2f);if(F(0xf8)>6.0f)F(0xf8)=6.0f;}
   KomachiObjectUpdateView *owner=P;
   if((AT(owner,signed char,0x60b)+3)*60<=I(0x144) || ((AT(owner,short,0x13c)==565 || AT(owner,short,0x13c)==566) && AT(owner,short,0x13e)==0 && AT(owner,short,0x140)==0)){BURST(827,50,5.0,1);burst_packet[0]=F(0xf4);burst_packet[1]=F(0xf8);burst_packet[2]=0;SPAWN(826,1,burst_packet);RETIRE();}
   if(AT(target,short,0x174)<1 || AT(owner,short,0x174)<1){BURST(827,50,5.0,1);RETIRE();}STEP();
  }else if(S(0x13e)==1){CURVED_FADE_VALUES();STEP();}
  if(OUTSIDE(1680.0,-400.0,1360.0f,-400.0))RETIRE();
  if(advance_frame())RETIRE();if(RETURN_ON_ENTRY_PHASE(1))RETIRE();if(RETURN_ON_ENTRY_PHASE(2))RETIRE();return;
 case 850:
  if(I(0x180)==5)RETIRE();if(S(0x13e)==1){SCALE(F(0x11c)+F(0x370));F(0xf8)-=D(0.3f);F(0x370)-=D(0.3f);if(F(0x370)<D(0.05f))F(0x370)=0.05f;if(I(0x144)>29)FADE(15,15);STEP();}FRAME_EXIT();
 case 852:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){if(emit_owner_gated_pair())RETIRE();ORBIT_WAVE_UNCAPTURED();advance_six(0);advance_phase(2);if(I(0x180)!=0){BURST(852,50,5.0,1);burst_packet[0]=F(0xf4);burst_packet[1]=F(0xf8);burst_packet[2]=0;SPAWN(826,1,burst_packet);RETIRE();}}
  else if(S(0x13e)==1){CURVED_FADE_VALUES();STEP();}
  if(OUTSIDE(1680.0,-400.0,1360.0f,-400.0))RETIRE();
  if(advance_frame())RETIRE();if(RETURN_ON_ENTRY_PHASE(1))RETIRE();if(RETURN_ON_ENTRY_PHASE(2))RETIRE();return;
 case 853:
  if(S(0x13e)==0){F(0xf4)+=D(0.1f);F(0xf8)=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3))*H[1];advance_six(0);if(I(0x144)%3==0){trail_packet[0]=0;trail_packet[1]=0;trail_packet[2]=1;float y=(RND(50)-25.0)+F(0xf0);float x=(RND(50)-25.0)+F(0xec);spawn_unparented(853,x,y,B(0x104),-1,reinterpret_cast<const unsigned *>(trail_packet),3);}}
  else if(S(0x13e)==1){FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)-=D(0.1f);}
  else if(S(0x13e)==3){SCALE(F(0x11c)+F(0x370));F(0xf8)-=D(0.3f);F(0x370)-=D(0.3f);if(F(0x370)<D(0.05f))F(0x370)=0.05f;if(I(0x144)>29)FADE(15,15);}
  if(OUTSIDE(1480.0f,-200.0,1860.0,-600.0f))RETIRE();STEP();FRAME_EXIT();
 case 854:
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x13c)!=604)RETIRE();
   if(S(0x364)==0){
    H[0]+=2.0;float *polar=H;double cosine=lookup_orientation_cosine_quantized_abs(-polar[0]);F(0xec)=C(0x104)*cosine*polar[1]+AT(P,float,0xec);double sine=lookup_orientation_sine_quantized_abs(-polar[0]);F(0xf0)=(sine*H[1]+AT(P,float,0xf0))*D(0.2f)+100.0+F(0x370);B(0x33c)=!(lookup_orientation_sine_quantized_abs(H[0])>0.0)?1:255;
    H[1]+=F(0x374);F(0x374)*=D(0.95f);F(0x370)+=F(0xf8);if(F(0xf0)>=150.0f){F(0xf8)-=0.5;if(F(0xf8)<0.0){F(0xf4)=0;S(0x364)=1;}}
   }
   if(S(0x364)==1){H[0]+=2.0;float *polar=H;double cosine=lookup_orientation_cosine_quantized_abs(-polar[0]);F(0xec)=C(0x104)*cosine*polar[1]+AT(P,float,0xec);double sine=lookup_orientation_sine_quantized_abs(-polar[0]);F(0xf0)=(sine*H[1]+AT(P,float,0xf0))*D(0.2f)+100.0+F(0x370);B(0x33c)=!(lookup_orientation_sine_quantized_abs(H[0])>0.0)?1:255;++S(0x366);if(S(0x366)>44){S(0x364)=2;S(0x366)=0;}}
   if(S(0x364)==2){H[1]-=10.0;if(H[1]<0.0)H[1]=0;float *polar=H;double cosine=lookup_orientation_cosine_quantized_abs(-polar[0]);float *after_cosine=H;F(0xec)=C(0x104)*cosine*polar[1]+AT(P,float,0xec);double sine=lookup_orientation_sine_quantized_abs(-polar[0]);float radius=after_cosine[1];float owner_y=AT(P,float,0xf0);B(0x33c)=1;F(0xf0)=(sine*radius+owner_y)*D(0.2f)+100.0+F(0x370);if(after_cosine[1]==0.0)S(0x364)=3;}
   if(S(0x364)==3){float dy=AT(A,float,0xf0)+100.0-F(0xf0);float dx=AT(A,float,0xec)-F(0xec);H[0]=-atan2_degrees(dy,C(0x104)*dx);MOTION->set_components(H[0],20);double square=square_float_value(dx);if(square+square_float_value(dy)<=100.0){F(0xec)=AT(A,float,0xec);F(0xf0)=AT(A,float,0xf0)+100.0;if(AT(P,short,0x730)==0)AT(P,short,0x730)=1;RETIRE();}STEP();}break;
  case 1:
   if(AT(P,short,0x13c)!=604)RETIRE();
   if(S(0x364)==0){H[0]-=2.0;float *polar=H;double cosine=lookup_orientation_cosine_quantized_abs(-polar[0]);F(0xec)=C(0x104)*cosine*polar[1]+AT(A,float,0xec);double sine=lookup_orientation_sine_quantized_abs(-polar[0]);F(0xf0)=(sine*H[1]+AT(P,float,0xf0))*D(0.2f)+100.0+F(0x370);B(0x33c)=!(lookup_orientation_sine_quantized_abs(H[0])>0.0)?1:255;H[1]+=F(0x374);F(0x374)*=D(0.95f);F(0x370)+=F(0xf8);if(F(0xf0)>=150.0f){F(0xf8)-=0.5;if(F(0xf8)<0.0){F(0xf4)=0;S(0x364)=1;}}}
   if(S(0x364)==1){H[0]-=2.0;float *polar=H;double cosine=lookup_orientation_cosine_quantized_abs(-polar[0]);F(0xec)=C(0x104)*cosine*polar[1]+AT(A,float,0xec);double sine=lookup_orientation_sine_quantized_abs(-polar[0]);F(0xf0)=(sine*H[1]+AT(P,float,0xf0))*D(0.2f)+100.0+F(0x370);B(0x33c)=!(lookup_orientation_sine_quantized_abs(H[0])>0.0)?1:255;++S(0x366);if(S(0x366)>44){S(0x364)=2;S(0x366)=0;}}
   if(S(0x364)==2){H[1]-=10.0;if(H[1]<0.0)H[1]=0;float *polar=H;double cosine=lookup_orientation_cosine_quantized_abs(-polar[0]);F(0xec)=C(0x104)*cosine*polar[1]+AT(A,float,0xec);double sine=lookup_orientation_sine_quantized_abs(-polar[0]);F(0xf0)=(sine*H[1]+AT(P,float,0xf0))*D(0.2f)+100.0+F(0x370);B(0x33c)=!(lookup_orientation_sine_quantized_abs(H[0])>0.0)?1:255;if(H[1]==0.0)S(0x364)=3;}
   if(S(0x364)==3){float dy=AT(P,float,0xf0)+100.0-F(0xf0);float dx=AT(P,float,0xec)-F(0xec);H[0]=-atan2_degrees(dy,C(0x104)*dx);MOTION->set_components(H[0],20);double square=square_float_value(dx);if(square+square_float_value(dy)<=100.0){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;RETIRE();}STEP();}break;
  case 2:case 3:FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)-=D(0.1f);STEP();break;
  case 4:SCALE(F(0x11c)*D(0.98f));MOVE();H[1]*=D(0.95f);if(I(0x144)>29)FADE(15,15);STEP();break;
  case 5:SCALE(F(0x11c)+D(0.2f));FADE(15,15);break;
  }FRAME_EXIT();
 case 855:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){if(emit_owner_gated_pair())RETIRE();SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3))*D(0.2f)+1.0);KomachiObjectUpdateView *target=A;
   if((F(0xec)-AT(target,float,0xec))*C(0x104)<0.0){F(0xf4)+=D(0.2f);if(F(0xf4)>6.0f)F(0xf4)=6.0f;}
   if((F(0xec)-AT(target,float,0xec))*C(0x104)>0.0){F(0xf4)-=D(0.2f);if(F(0xf4)<-6.0f)F(0xf4)=-6.0f;}
   if(F(0xf0)-AT(target,float,0xf0)-100.0>0.0){F(0xf8)-=D(0.2f);if(F(0xf8)<-6.0f)F(0xf8)=-6.0f;}
   if(F(0xf0)-AT(target,float,0xf0)-100.0<0.0){F(0xf8)+=D(0.2f);if(F(0xf8)>6.0f)F(0xf8)=6.0f;}
   if(I(0x144)>899){BURST(855,50,5.0,1);burst_packet[0]=F(0xf4);burst_packet[1]=F(0xf8);burst_packet[2]=0;SPAWN(826,1,burst_packet);RETIRE();}
   if(AT(target,short,0x174)<1 || AT(P,short,0x174)<1){BURST(855,50,5.0,1);RETIRE();}STEP();
  }else if(S(0x13e)==1){CURVED_FADE_VALUES();STEP();}
  if(OUTSIDE(1680.0,-400.0,1360.0f,-400.0))RETIRE();
  if(advance_frame())RETIRE();if(RETURN_ON_ENTRY_PHASE(1))RETIRE();if(RETURN_ON_ENTRY_PHASE(2))RETIRE();return;
 case 856:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:{motion_packet[0]=RND(360);motion_packet[1]=RND(50)*D(0.01f)+5.0;motion_packet[2]=1;double y=F(0xf0)+30.0;double x=30.0+F(0xec);float spawn_y=y-RND(60);float spawn_x=x-RND(60);spawn_unparented(856,spawn_x,spawn_y,B(0x104),1,reinterpret_cast<const unsigned *>(motion_packet),3);
   if(I(0x144)%2==0){motion_packet[0]=H[0];motion_packet[1]=0;motion_packet[2]=4;SPAWN(856,1,motion_packet);}
   if(static_cast<unsigned char>(has_crossed_stage_surface_while_descending())==0){F(0xf0)+=F(0xf8);break;}
   P->publish_battle_layout_scalar(5);P->dispatch_character_wave_handle(54);float n=0;do{burst_packet[0]=-RND(160)-10.0;burst_packet[1]=RND(200)*D(0.01f)+20.0;burst_packet[2]=1;SPAWN(856,1,burst_packet);n+=1.0;}while(n<8.0f);burst_packet[0]=0;burst_packet[1]=0;burst_packet[2]=2;SPAWN(856,-1,burst_packet);RETIRE();}
  case 1:H[1]*=D(0.95f);MOVE();if(S(0x364)<=I(0x144)){SCALE(F(0x11c)*D(0.98f));FADE(5,5);}STEP();break;
  case 2:case 4:goto expanding_tail;
  case 3:H[1]*=D(0.95f);MOVE();F(0x12c)+=F(0x374);F(0x374)*=D(0.95f);SCALE(F(0x11c)+D(0.005f));FADE(5,5);STEP();break;
  }FRAME_EXIT();
 case 861:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:SCALE(F(0x11c)*D(0.9f));if(I(0x144)<15)break;if(I(0x144)==15){motion_packet[0]=0;motion_packet[1]=0;motion_packet[2]=1;SPAWN(861,1,motion_packet);}FADE(10,10);break;
  case 1:advance_six(0);if(I(0x144)>3)B(0x184)=0;if(F(0x370)!=0.0){F(0x11c)=1.0-F(0x370);F(0x370)*=0.75;if(F(0x370)<=0.01f){F(0x370)=0;request_packet[0]=0;request_packet[1]=0;request_packet[2]=2;SPAWN(861,1,request_packet);request_packet[2]=3;SPAWN(861,1,request_packet);}}else{FADE(10,10);}break;
  case 2:F(0x370)=(1.0-F(0x11c))*10.0+F(0x370)+2.0;set_sprite_uv_size(0,F(0x370));if(I(0x144)>479 || AT(A,short,0x174)<1)S(0x364)=1;if(S(0x364)==0){if(fabsf(F(0xec)-AT(A,float,0xec))<=100.0)AT(A,float,0x4dc)=0.1f;}else{FADE(5,5);F(0x11c)*=D(0.98f);}break;
  case 3:F(0x370)=(1.0-F(0x11c))*30.0+F(0x370)+8.0;set_sprite_uv_size(0,F(0x370));if(I(0x144)>=180){FADE(5,5);F(0x11c)*=D(0.98f);}break;
  case 4:goto expanding_tail;
  }FRAME_EXIT();
 case 900:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x174)<1){float n=0;do{motion_packet[0]=RND(360);motion_packet[1]=RND(10)+6.0;motion_packet[2]=1;SPAWN(900,1,motion_packet);n+=1.0;}while(n<4.0f);RETIRE();}
   if(B(0x113)<245)B(0x113)+=10;else B(0x113)=255;
   F(0xf8)=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*4.0)*F(0x370);
   SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*D(0.2f)+1.0);STEP();
   if(AT(P,short,0x13c)==711 && AT(P,short,0x730)==1)S(0x364)=1;
   if(S(0x364)==1){++S(0x366);if(H[1]+H[1]<=static_cast<float>(S(0x366))){B(0x184)=1;select_sequence(2);burst_packet[0]=0;burst_packet[1]=0;burst_packet[2]=3;B(0x113)=255;SPAWN(900,1,burst_packet);if(g_match_identifier==3){float n=0;do{burst_packet[0]=RND(360);burst_packet[1]=RND(16)+6.0;burst_packet[2]=4;SPAWN(900,1,burst_packet);n+=1.0;}while(n<4.0f);}goto reset_motion_return;}}break;
  case 1:H[1]-=0.5;if(H[1]<=D(0.2f))H[1]=0.2f;MOVE();FADE(10,10);STEP();break;
  case 2:if(I(0x144)<60)advance_six(0);else{B(0x184)=0;SCALE(F(0x11c)*D(0.95f));FADE(10,10);}break;
  case 3:SCALE(F(0x11c)+D(0.3f));FADE(20,20);break;
  case 4:F(0x370)*=D(0.7f);if(F(0x370)<=0.25f)F(0x370)=0.25f;turn_heading(0,0.5f,100);MOTION->set_components(H[0],H[1]*F(0x370));advance_six(2);if(C(0x184)<1 || AT(P,short,0x174)<1 || I(0x144)>179)S(0x364)=1;if(S(0x364)==1){B(0x184)=0;FADE(10,10);}STEP();if(OUTSIDE(1380.0f,-100.0,1060.0f,-200.0))RETIRE();break;
  case 5:H[1]-=0.5;if(H[1]<=D(0.2f))H[1]=0.2f;MOVE();FADE(10,10);STEP();break;
  case 6:SCALE(F(0x11c)+0.5);FADE(9,8);break;
  }FRAME_EXIT();
 case 901:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:SCALE(F(0x11c)*D(0.9f));if(I(0x144)>14){if(I(0x144)==15){motion_packet[0]=0;motion_packet[1]=0;motion_packet[2]=1;SPAWN(901,1,motion_packet);}FADE(10,10);}goto frame_exit;
  case 1:advance_six(0);if(I(0x144)>3)B(0x184)=0;if(F(0x370)==0.0){FADE(10,10);}else{float scale=1.0-F(0x370);F(0x11c)=scale+scale;F(0x370)*=0.75;if(F(0x370)<=0.01f){F(0x370)=0;request_packet[0]=0;request_packet[1]=0;request_packet[2]=2;SPAWN(901,1,request_packet);request_packet[2]=3;SPAWN(901,1,request_packet);}}goto frame_exit;
  case 2:F(0x370)=(2.0-F(0x11c))*10.0+F(0x370)+2.0;set_sprite_uv_size(0,F(0x370));if(AT(P,short,0x13c)!=720)S(0x364)=1;if(S(0x364)!=1){if(fabsf(F(0xec)-AT(A,float,0xec))<=F(0x11c)*100.0)AT(A,float,0x4dc)=0.1f;}else{FADE(5,5);F(0x11c)*=D(0.98f);}goto frame_exit;
  case 3:F(0x370)=(2.0-F(0x11c))*30.0+F(0x370)+8.0;set_sprite_uv_size(0,F(0x370));if(AT(P,short,0x13c)!=720)S(0x364)=1;if(S(0x364)==1){FADE(5,5);F(0x11c)*=D(0.98f);}goto frame_exit;
  case 4:goto expanding_tail;
  case 5:goto frame_exit;
  case 6:H[1]*=D(0.95f);MOVE();F(0x12c)+=F(0x374);F(0x374)*=D(0.95f);SCALE(F(0x11c)+D(0.005f));FADE(5,5);STEP();goto frame_exit;
  case 7:H[1]*=D(0.95f);MOVE();if(S(0x364)<=I(0x144)){SCALE(F(0x11c)*D(0.98f));FADE(5,5);}STEP();goto frame_exit;
  case 8:SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.85f);if(I(0x144)>=6)FADE(6,5);goto frame_exit;
  case 9:SCALE(F(0x11c)*D(0.98f));if(I(0x144)>=6)FADE(6,5);goto frame_exit;
  case 10:
   motion_packet[0]=RND(360);motion_packet[1]=RND(50)*D(0.01f)+5.0;motion_packet[2]=6;SPAWN(901,1,motion_packet);
   if(static_cast<unsigned char>(has_crossed_stage_surface_while_descending())!=0){P->dispatch_character_wave_handle(54);float n=0;do{burst_packet[0]=-RND(160)-10.0;burst_packet[1]=RND(200)*D(0.01f)+20.0;burst_packet[2]=7;SPAWN(901,1,burst_packet);n+=1.0;}while(n<8.0f);burst_packet[0]=0;burst_packet[1]=0;burst_packet[2]=8;SPAWN(901,-1,burst_packet);burst_packet[2]=9;SPAWN(901,-1,burst_packet);RETIRE();}break;
  case 11:
   motion_packet[0]=RND(360);motion_packet[1]=RND(50)*D(0.01f)+5.0;motion_packet[2]=6;SPAWN(901,1,motion_packet);
   if(static_cast<unsigned char>(has_crossed_stage_surface_while_descending())!=0){P->dispatch_character_wave_handle(54);float n=0;do{burst_packet[0]=-RND(160)-10.0;burst_packet[1]=RND(200)*D(0.01f)+20.0;burst_packet[2]=7;SPAWN(901,1,burst_packet);n+=1.0;}while(n<8.0f);burst_packet[0]=0;burst_packet[1]=0;burst_packet[2]=8;SPAWN(901,-1,burst_packet);burst_packet[2]=9;SPAWN(901,-1,burst_packet);RETIRE();}break;
  case 12:
   motion_packet[0]=RND(360);motion_packet[1]=RND(50)*D(0.01f)+5.0;motion_packet[2]=6;SPAWN(901,1,motion_packet);
   if(static_cast<unsigned char>(has_crossed_stage_surface_while_descending())!=0){P->dispatch_character_wave_handle(54);float n=0;do{burst_packet[0]=-RND(160)-10.0;burst_packet[1]=RND(200)*D(0.01f)+20.0;burst_packet[2]=7;SPAWN(901,1,burst_packet);n+=1.0;}while(n<8.0f);burst_packet[0]=0;burst_packet[1]=0;burst_packet[2]=8;SPAWN(901,-1,burst_packet);burst_packet[2]=9;SPAWN(901,-1,burst_packet);RETIRE();}break;
  case 13:
   motion_packet[0]=RND(360);motion_packet[1]=RND(50)*D(0.01f)+5.0;motion_packet[2]=6;SPAWN(901,1,motion_packet);
   if(static_cast<unsigned char>(has_crossed_stage_surface_while_descending())!=0){P->dispatch_character_wave_handle(54);float n=0;do{burst_packet[0]=-RND(160)-10.0;burst_packet[1]=RND(200)*D(0.01f)+20.0;burst_packet[2]=7;SPAWN(901,1,burst_packet);n+=1.0;}while(n<8.0f);burst_packet[0]=0;burst_packet[1]=0;burst_packet[2]=8;SPAWN(901,-1,burst_packet);burst_packet[2]=9;SPAWN(901,-1,burst_packet);RETIRE();}break;
  default:goto frame_exit;
  }F(0xf0)+=F(0xf8);FRAME_EXIT();
 case 902:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:advance_six(0);advance_phase(1);if(C(0x184)<1 || AT(P,short,0x174)<1 || S(0x364)<=I(0x144)){float n=0;do{motion_packet[0]=n*90.0+RND(40);motion_packet[1]=RND(150)*D(0.01f)+15.0;motion_packet[2]=1;SPAWN(902,1,motion_packet);n+=1.0;}while(n<4.0f);RETIRE();}MOVE();STEP();break;
  case 1:H[1]*=D(0.9f);MOVE();if(S(0x364)<=I(0x144)){SCALE(F(0x11c)*D(0.98f));FADE(5,5);}STEP();break;
  case 2:SCALE(F(0x11c)+D(0.15f));FADE(10,10);break;
  case 3:SCALE(F(0x11c)*D(0.95f));FADE(5,5);break;
  }FRAME_EXIT();
 case 930:
  switch(S(0x13e)) {
  case 0:F(0x12c)+=2.0;if(S(0x364)==0){if(B(0x113)<236)B(0x113)+=20;else{B(0x113)=255;S(0x364)=1;}}
   if(S(0x364)<2){SCALE(F(0x11c)+D(0.005f));if(AT(P,short,0x13c)!=732 || AT(P,short,0x738)==1){S(0x364)=2;return;}if(H[1]==0.0){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;}if(H[1]==1.0){F(0xec)=AT(A,float,0xec);F(0xf0)=AT(A,float,0xf0)+100.0;}}
   if(S(0x364)==2){SCALE(F(0x11c)+D(0.05f));FADE(10,10);}break;
  case 1:if(S(0x140)==0){SCALE(F(0x11c)+D(0.2f));}else{F(0x11c)+=D(0.02f);F(0x120)*=D(0.95f);FADE(10,10);}break;
  case 2:SCALE(F(0x11c)+D(0.3f));FADE(11,10);break;
  case 3:MOVE();H[1]*=D(0.9f);SCALE(F(0x11c)*D(0.99f));FADE(11,10);STEP();break;
  }FRAME_EXIT();
 case 980:update_ping_pong_motion();FRAME_EXIT();
 case 990:{KomachiObjectUpdateView *owner=P;F(0xec)=AT(owner,float,0xec)-C(0x104)*82;F(0xf0)=AT(owner,float,0xf0)+132.0;if(AT(owner,short,0x13c)!=600 || AT(owner,short,0x13e)!=1)RETIRE();FRAME_EXIT();}
 case 999:
  switch(S(0x13e)) {
  case 0:case 1:AT(P,float,0xec)=F(0xec);if(F(0xec)>1480.0f || F(0xec)<-200.0)RETIRE();if(S(0x13e)>=1)F(0xf8)-=F(0x100);break;
  case 2:{F(0xf8)-=D(0.35f);double next_y=D(F(0xf8))+F(0xf0);if(next_y<=stage_surface_height()){AT(P,short,0x78c)=1;F(0xf0)=stage_surface_height();F(0xf4)=0;F(0xf8)=0;F(0x100)=0;select_sequence(3);return;}break;}
  case 4:if(AT(P,short,0x78e)==1){next_sequence_block();B(0x104)=1;return;}break;
  case 5:case 6:if(S(0x13e)>=6)F(0xf8)-=F(0x100);break;
  }
  STEP();if(advance_frame())--I(0x330);
  if(RETURN_ON_ENTRY_PHASE(1)){F(0xf4)=15.0f;F(0xf8)=15.0f;F(0x100)=0.2f;}
  if(RETURN_ON_ENTRY_PHASE(6)){F(0xf4)=15.0f;F(0xf8)=15.0f;F(0x100)=0.2f;}return;
 default:advance_frame();return;
 }
frame_exit:
 FRAME_EXIT();
expanding_tail:
 SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.85f);if(I(0x144)>=0)FADE(6,5);FRAME_EXIT();
reset_motion_return:
 F(0xf4)=0;F(0xf8)=0;F(0x11c)=1;F(0x120)=1;return;
}
}
