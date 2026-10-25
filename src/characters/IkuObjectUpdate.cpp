// Manual complete-body hypothesis from JP1.06a632C30; not canonical exact.
// Evidence and remaining unknowns: docs/IKU_OBJECT_UPDATE_2026_10_25.md.
#include "characters/IkuObjectUpdate.hpp"
#include <math.h>
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define I(o) AT(this,int,o)
#define H AT(this,float *,0x340)
#define P AT(this,IkuObjectUpdateView *,0x348)
#define A AT(this,IkuObjectUpdateView *,0x170)
#define D(x) static_cast<double>(x)
#define RND(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
#define RETIRE() do {--I(0x330);return;} while(0)
#define MOVE() reinterpret_cast<IkuUpdateMotionView *>(reinterpret_cast<unsigned char *>(this)+4)->set_components(H[0],H[1])
#define STEP() do {F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8);} while(0)
#define SCALE(v) F(0x120)=F(0x11c)=static_cast<float>(v)
#define ENTRY(p) (I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==p)
#define SPAWN(a,l,p) spawn_unparented(a,F(0xec),F(0xf0),B(0x104),l,reinterpret_cast<const unsigned *>(p),3)
#define PACKET(p,a,b,c) do {p[0]=a;p[1]=b;p[2]=c;} while(0)
#define FADE(t,d) do {if(B(0x113)<t)RETIRE();B(0x113)-=d;} while(0)
#define COLORFADE(d) do {if(B(0x113)<d)RETIRE();B(0x112)-=d;B(0x111)-=d;B(0x113)-=d;} while(0)
#define WARMCOLOR(d) do {if(B(0x111)<d){B(0x111)=0;B(0x112)=0;FADE(d,d);}else{B(0x111)-=d;B(0x112)-=d;}} while(0)
#define OUTSIDE(xh,xl,yh,yl) (F(0xec)>xh || F(0xec)<xl || F(0xf0)>yh || F(0xf0)<yl)
void IkuObjectUpdateView::update_action_state()
{
 // Each packet is consumed by a real object request. Names are provisional.
 float p312[3],p24[3],p384[3],p192[3],p468[3],p360[3],p96[3],p336[3],p556[3],p168[3],p420[3],p48[3],p288[3],p456[3],p504[3],p144[3],p264[3],p568[3],p444[3],p72[3],p240[3],p120[3],p216[3],p408[3],p492[3],p396[3],p372[3],p540[3],p348[3],p324[3],p300[3],p276[3],p252[3],p228[3],p432[3],p480[3],p204[3],p516[3],p180[3],p156[3],p132[3],p108[3],p528[3],p84[3],p60[3],p36[3],p580[3],p12[3];
 switch(S(0x13c)) {
 case 800:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,0,3))RETIRE();
   MOVE();
   if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();
   if(S(0x142)>180 || I(0x180)!=0 || F(0xf0)<=0.0) {
    F(0x12c)=RND(360);next_sequence_block();F(0xf4)=F(0xf8)=0;return;
   }break;
  case 1:SCALE(F(0x11c)+D(0.05f));break;
  }
  STEP();if(advance_frame())--I(0x330);if(ENTRY(2))--I(0x330);return;
 case 801:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,3,5))RETIRE();H[1]-=0.5;if(H[1]<2.0f)H[1]=2;MOVE();
   if(advance_six(15)){F(0x12c)=RND(360);select_sequence(2);F(0xf4)=F(0xf8)=0;return;}
   if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>14){I(0x180)=0;S(0x364)=0;}
   if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();
   if(I(0x144)>59){P->dispatch_character_wave_handle(2);p312[1]=15;p312[2]=1;int angle=0;do{p312[0]=angle+45.0;SPAWN(801,1,p312);angle+=90;}while(angle<360);RETIRE();}break;
  case 1:
   if(emit_repeated(0,0,3))RETIRE();H[1]-=D(0.7f);if(H[1]<1.0f)H[1]=1;MOVE();
   if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();
   if(I(0x144)>59 || C(0x184)<1){F(0x12c)=RND(360);select_sequence(2);F(0xf4)=F(0xf8)=0;return;}break;
  case 2:SCALE(F(0x11c)+D(0.05f));break;
  case 3:
   if(I(0x144)%10==0)H[0]=-H[0];advance_six(0);advance_phase(1);
   if(I(0x180)==4 || I(0x180)==8){PACKET(p24,RND(360),0,2);SPAWN(801,1,p24);I(0x180)=0;RETIRE();}
   if(I(0x180)!=0){PACKET(p384,RND(360),0,2);SPAWN(801,1,p384);I(0x180)=0;B(0x184)=0;}
   if(emit_repeated(0,3,5))RETIRE();MOVE();if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();break;
  case 4:
   if(AT(this,void *,0x34c)==0){B(0x113)=0;S(0x364)-=5;if(S(0x364)<1){S(0x364)=0;RETIRE();}set_secondary_flags(0,1);set_secondary_alpha(B(0x364));}
   else{F(0xec)=RND(40)+AT(AT(this,void *,0x34c),float,0xec)-20.0;F(0xf0)=RND(40)+AT(AT(this,void *,0x34c),float,0xf0)-20.0;}break;
  case 5: {
   if(emit_repeated(0,2,4))RETIRE();advance_six(5);if(advance_phase(3))RETIRE();
   if(I(0x180)!=0){if(C(0x184)<1)RETIRE();if(++S(0x364)>3){S(0x364)=0;I(0x180)=0;}}
   if(I(0x144)%5==0){PACKET(p192,-atan2_degrees(F(0xf8),F(0xf4)),0,6);SPAWN(801,1,p192);}
   double next_y=D(F(0xf8))+F(0xf0);if(next_y<=stage_surface_height() && F(0xf8)<0.0)F(0xf8)*=-1.0;
   if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1280.0f)RETIRE();break;
  }
  case 6:if(I(0x144)>9){B(0x184)=0;WARMCOLOR(10);}break;
  }
  STEP();if(advance_frame())--I(0x330);if(ENTRY(3))--I(0x330);return;
 case 802:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   if(emit_repeated(0,2,5))RETIRE();double y=F(0xf0);if(y<stage_surface_height()){next_sequence_block();return;}
   F(0x12c)+=38.0;advance_six(0);if(I(0x144)>89){B(0x184)=0;next_sequence_block();return;}
   if(I(0x180)!=0){if(C(0x184)<1){next_sequence_block();return;}if(++S(0x366)>5){I(0x180)=0;S(0x366)=0;}}
   if(I(0x144)%20==0){double y_now=F(0xf0);if(y_now-stage_surface_height()<=200.0){int angle=0;do{p468[0]=angle+30.0+RND(30);p468[1]=20;p468[2]=2;int layer=(p468[0]<0.0 || p468[0]>180.0f)?-1:1;spawn_unparented(802,F(0xec),stage_surface_height(),B(0x104),layer,reinterpret_cast<const unsigned *>(p468),3);angle+=60;}while(angle<360);}}
   H[1]-=0.5;if(H[1]<=3.0f)H[1]=3;MOVE();STEP();break;
  }
  case 1:F(0x12c)+=38.0;SCALE(F(0x11c)*D(0.85f));FADE(7,7);STEP();break;
  case 2:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;break;
  case 3:
   F(0x12c)-=25.0;if(AT(this,void *,0x34c)){void *related=AT(this,void *,0x34c);F(0xec)=AT(related,float,0xec);F(0xf0)=AT(related,float,0xf0);if(AT(related,short,0x13e)==0){if(I(0x144)%10==0){PACKET(p360,F(0x124),0,4);SPAWN(802,1,p360);}break;}SCALE(F(0x11c)-D(0.02f));}FADE(11,10);break;
  case 4:F(0x12c)-=25.0;SCALE(F(0x11c)+D(0.05f));F(0xf4)*=D(0.95f);FADE(11,10);STEP();break;
  case 5:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);F(0xec)+=C(0x104)*F(0xf4)*0.25;F(0xf0)+=F(0xf8);break;
  }
  if(advance_frame())--I(0x330);return;
 case 810:
  if(I(0x180)==5 || (AT(P,short,0x13c)!=500 && AT(P,short,0x13c)!=501))RETIRE();position_relative(130,125);
  if(S(0x13e)==1 && AT(P,short,0x140)>11){select_sequence(2);return;}
  if(AT(P,short,0x186)>0 && S(0x13e)<2)return;if(advance_frame())--I(0x330);return;
 case 811:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){F(0x370)+=3.0;if(F(0x370)>=90.0f)F(0x370)=90;double wave=lookup_orientation_sine_quantized_abs(F(0x370));SCALE(wave+wave);if(I(0x144)>4)FADE(15,15);}
  else if(S(0x13e)==1){if(AT(P,short,0x13c)!=520 && AT(P,short,0x13c)!=521)RETIRE();position_relative(0,0);}
  if(AT(P,short,0x186)==0 && advance_frame())--I(0x330);if(ENTRY(2))--I(0x330);return;
 case 812:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   short owner_action=AT(P,short,0x13c);if(owner_action>49 && owner_action<150){int n=0;do{float y=C(0x104)*n*30+F(0xf0)+RND(15);float x=static_cast<float>(static_cast<unsigned>(selector_random_roll(30)-15))+F(0xec);emit_fighter_effect_433cc0(201,x,y,B(0x104),1);++n;}while(n<30);RETIRE();}
   F(0xf0)-=160.0;double y=F(0xf0);
   if(stage_surface_height()>y)goto iku_ground_clamp;
   goto iku_ground_advance;
  }
  case 1:
   if(AT(P,short,0x13c)!=540)RETIRE();F(0x370)-=120.0;if(F(0x370)<0.0)F(0x370)=0;F(0xf0)=AT(P,float,0xf0)+320.0+F(0x370);F(0xec)=AT(P,float,0xec);advance_six(0);
   if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>9){S(0x364)=0;I(0x180)=0;}
   if(I(0x144)>=20){F(0x11c)*=D(0.95f);if(I(0x144)>24)FADE(15,15);}break;
  case 2:if(AT(P,short,0x13c)!=540)RETIRE();F(0xf0)=AT(P,float,0xf0);F(0xec)=AT(P,float,0xec);advance_six(0);advance_phase(5);if(I(0x144)>19)COLORFADE(15);break;
  case 3:if(AT(P,short,0x13c)!=540)RETIRE();F(0xf0)=AT(P,float,0xf0);F(0xec)=AT(P,float,0xec);if(I(0x144)>19)COLORFADE(15);break;
  case 4:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*D(0.2f);SCALE(F(0x11c)*D(0.99f));if(I(0x144)>11)FADE(6,5);break;
  }
  if(advance_frame())--I(0x330);return;
 case 813:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   if(emit_repeated(0,3,5))RETIRE();short a=AT(P,short,0x13c);if(a!=560 && a!=561 && a!=562 && a!=563)S(0x364)=1;
   advance_six(0);advance_phase(3);if(I(0x144)%5==0){PACKET(p96,H[0],0,2);SPAWN(813,1,p96);}if(I(0x144)%2==0){PACKET(p336,RND(360),RND(10)+2.0,4);SPAWN(813,1,p336);}
   if(I(0x144)>24 && AT(P,signed char,0x750)!=0 && S(0x364)==0){B(0x184)=0;I(0x180)=0;select_sequence(3);F(0xf4)=F(0xf8)=0;return;}if(I(0x144)>179)RETIRE();MOVE();STEP();break;
  }
  case 1:SCALE(F(0x11c)+D(0.01f));break;
  case 2:if(I(0x144)>19)WARMCOLOR(10);break;
  case 3:
   if(emit_repeated(0,3,5) || I(0x144)>179)RETIRE();advance_six(0);advance_phase(3);
   if(I(0x144)<11){B(0x184)=0;if(AT(P,signed char,0x607)>3)I(0x144)=10;
    if(I(0x144)==10){H[0]=-atan2_degrees(AT(A,float,0xf0)+100.0-F(0xf0),C(0x104)*(AT(A,float,0xec)-F(0xec)));B(0x184)=1;PACKET(p556,RND(360),0,1);SPAWN(813,1,p556);
     if(AT(P,signed char,0x607)>3){PACKET(p556,H[0]+20.0,H[1],5);SPAWN(813,1,p556);PACKET(p556,H[0]-20.0,H[1],5);SPAWN(813,1,p556);}
    }
   }else{MOVE();if(I(0x144)%5==0){PACKET(p168,H[0],0,2);SPAWN(813,1,p168);}if(I(0x144)%2==0){PACKET(p420,RND(360),RND(10)+2.0,4);SPAWN(813,1,p420);}}
   STEP();break;
  case 4:H[1]*=D(0.9f);MOVE();F(0x11c)+=D(0.1f);F(0x120)*=D(0.9f);if(I(0x144)>24){if(B(0x113)<5)RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;}STEP();break;
  case 5:
   if(emit_repeated(0,1,2) || I(0x144)>179)RETIRE();advance_six(0);advance_phase(1);MOVE();if(I(0x144)%5==0){PACKET(p48,H[0],0,2);SPAWN(813,1,p48);}if(I(0x144)%10==0){PACKET(p288,RND(360),RND(10)+2.0,4);SPAWN(813,1,p288);}STEP();break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(2))RETIRE();if(ENTRY(3))--I(0x330);return;
 case 815: {
  int y_offset;
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,3,5) || AT(P,short,0x13c)!=505)RETIRE();
   if((AT(P,short,0x13e)==0 && AT(P,short,0x140)>12) || (AT(P,short,0x13e)==1 && AT(P,short,0x140)>6)){S(0x366)=1;B(0x184)=0;goto iku815_fade;}y_offset=120;goto iku815_follow;
  case 1:
   if(emit_repeated(0,3,5) || AT(P,short,0x13c)!=505)RETIRE();
   if(AT(P,short,0x13e)==1 && (AT(P,short,0x140)>=13 || AT(P,short,0x140)>=7)){S(0x366)=1;B(0x184)=0;goto iku815_fade;}y_offset=120;goto iku815_follow;
  case 2:MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;goto iku815_finish;
  case 3:
   if(emit_repeated(0,3,5) || AT(P,short,0x13c)!=506)RETIRE();
   if((AT(P,short,0x13e)==0 && AT(P,short,0x140)>12) || (AT(P,short,0x13e)==1 && AT(P,short,0x140)>6)){S(0x366)=1;B(0x184)=0;goto iku815_fade;}y_offset=195;goto iku815_follow;
  case 4:
   if(emit_repeated(0,3,5) || AT(P,short,0x13c)!=506)RETIRE();
   if(AT(P,short,0x13e)==1 && (AT(P,short,0x140)>=13 || AT(P,short,0x140)>6)){S(0x366)=1;B(0x184)=0;goto iku815_fade;}y_offset=195;goto iku815_follow;
  default:goto iku815_finish;
  }
 iku815_follow:
  position_relative(150,y_offset);advance_six(0);if(I(0x180)!=0 && ++S(0x364)>5){I(0x180)=0;S(0x364)=0;}
 iku815_fade:
  if(S(0x366)==1){SCALE(F(0x11c)*D(0.85f));if(B(0x113)<20)RETIRE();B(0x113)-=20;B(0x111)-=20;B(0x112)-=20;}
 iku815_finish:
  if(advance_frame())--I(0x330);if(ENTRY(2))RETIRE();if(ENTRY(3))--I(0x330);return;
 }
 case 816:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 6: {
   if(emit_repeated(0,3,5))RETIRE();double y=F(0xf0);if(y<stage_surface_height()){select_sequence(1);return;}F(0x12c)+=38.0;advance_six(0);
   if(I(0x180)!=0 || (AT(P,signed char,0x609)+6)*10<=I(0x144)){int angle=0;do{PACKET(p456,angle+30.0+RND(30),20,2);int layer=(!(p456[0]>=0.0 && p456[0]<=180.0f))?-1:1;SPAWN(816,layer,p456);angle+=60;}while(angle<360);select_sequence(1);return;}
   if(I(0x144)%20==0){double y_now=F(0xf0);if(y_now-stage_surface_height()<=200.0){int angle=0;do{PACKET(p504,angle+30.0+RND(30),20,2);int layer=(!(p504[0]>=0.0 && p504[0]<=180.0f))?-1:1;spawn_unparented(816,F(0xec),stage_surface_height(),B(0x104),layer,reinterpret_cast<const unsigned *>(p504),3);angle+=60;}while(angle<360);}}
   H[1]-=0.5;if(H[1]<=1.5f)H[1]=1.5f;MOVE();STEP();break;
  }
  case 1:F(0x12c)+=38.0;SCALE(F(0x11c)*D(0.85f));FADE(7,7);STEP();break;
  case 2:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;break;
  case 3:
   F(0x12c)-=25.0;if(AT(this,void *,0x34c)){void *related=AT(this,void *,0x34c);F(0xec)=AT(related,float,0xec);F(0xf0)=AT(related,float,0xf0);if(AT(related,short,0x13e)==0 || AT(related,short,0x13e)==6){if(I(0x144)%10==0){PACKET(p144,F(0x12c),0,4);SPAWN(816,1,p144);}break;}SCALE(F(0x11c)-D(0.02f));}FADE(11,10);break;
  case 4:F(0x12c)-=25.0;SCALE(F(0x11c)+D(0.05f));F(0xf4)*=D(0.95f);FADE(11,10);STEP();break;
  case 5:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);F(0xec)+=C(0x104)*F(0xf4)*0.25;F(0xf0)+=F(0xf8);break;
  }
  if(advance_frame())--I(0x330);return;
 case 817:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:SCALE(F(0x11c)*D(0.9f));if(I(0x144)>9){if(B(0x113)<15)RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x112)-=15;}break;
  case 2:
   F(0x11c)*=D(0.99f);F(0x120)-=D(0.001f);advance_six(0);advance_phase(0);F(0x370)*=D(0.95f);if(F(0x370)<=D(0.05f))F(0x370)=0.05f;
   if(I(0x144)>9){if(B(0x113)<15)RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x112)-=15;}break;
  case 3:SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.85f);if(F(0x370)<=D(0.05f))F(0x370)=0.05f;if(I(0x144)>2){if(B(0x113)<25)RETIRE();B(0x113)-=25;B(0x111)-=25;B(0x112)-=25;}break;
  case 4:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*D(0.2f);SCALE(F(0x11c)*D(0.99f));if(I(0x144)>11)FADE(6,5);break;
  case 5:
   F(0xf8)=6;F(0xf0)+=6.0;if(emit_repeated(0,0,0))S(0x364)=1;F(0x11c)*=D(0.95f);F(0x120)+=0.5;
   if(F(0x11c)<=0.01f && S(0x364)==0){PACKET(p264,0,H[1],8);SPAWN(817,1,p264);RETIRE();}break;
  case 6:
   F(0xf0)*=D(0.85f);F(0x11c)*=D(0.99f);F(0x120)*=D(0.95f);
   if(I(0x144)>44){--I(0x330);PACKET(p568,0,0,2);spawn_unparented(817,F(0xec),0,B(0x104),1,reinterpret_cast<const unsigned *>(p568),3);p568[2]=3;spawn_unparented(817,F(0xec),0,B(0x104),-1,reinterpret_cast<const unsigned *>(p568),3);p568[2]=7;spawn_unparented(817,F(0xec),0,B(0x104),1,reinterpret_cast<const unsigned *>(p568),3);int angle=0;do{PACKET(p568,angle+22.5+F(0x370),30,4);int layer=(!(p568[0]>=0.0 && p568[0]<=180.0f))?-1:1;SPAWN(817,layer,p568);angle+=45;}while(angle<360);P->dispatch_character_wave_handle(13);return;}break;
  case 7:
   if(I(0x144)%4==0)F(0x12c)=RND(360);SCALE(F(0x11c)*D(0.95f));F(0x370)*=D(0.95f);if(F(0x370)<=D(0.05f))F(0x370)=0.05f;
   if(I(0x144)>9){if(B(0x113)<15)RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x112)-=15;}break;
  case 8:
   if(emit_repeated(0,0,0) || AT(A,short,0x174)<1)RETIRE();
   if(AT(P,signed char,0x60a)*40+180<=I(0x144) || (AT(P,int,0x6c0)==0 && H[1]==0.0) || (AT(P,int,0x6c4)==0 && H[1]==1.0)){
    PACKET(p444,0,0,6);IkuObjectUpdateView *owner=H[1]==0.0?A:P;spawn_unparented(817,AT(owner,float,0xec),640,B(0x104),1,reinterpret_cast<const unsigned *>(p444),3);RETIRE();}break;
  case 9:if(B(0x113)<246)B(0x113)+=10;else B(0x113)=255;if(AT(this,void *,0x34c)==0)RETIRE();SCALE(F(0x11c)+D(0.02f));break;
  }
  if(advance_frame())--I(0x330);return;
 case 818:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(I(0x144)==12){turn_heading(0,360,100);signed char skill=AT(P,signed char,0x60b);
    if(skill<2){if(H[0]>30.0)H[0]=30;if(H[0]<-30.0)H[0]=-30;}
    else if(skill<4){if(H[0]>45.0f)H[0]=45;if(H[0]<-45.0f)H[0]=-45;}
    else{if(H[0]>60.0)H[0]=60;if(H[0]<-60.0)H[0]=-60;}
    H[1]=25;MOVE();B(0x184)=1;
   }
   if(I(0x144)>11 && AT(P,signed char,0x60b)>3 && F(0xf8)<0.0 && F(0xf0)<=0.0){F(0xf8)=-F(0xf8);F(0xf4)*=0.5;}
   advance_six(0);advance_phase(1);
   if(I(0x180)==4 || I(0x180)==8){PACKET(p72,RND(360),0,2);SPAWN(801,1,p72);I(0x180)=0;RETIRE();}
   if(I(0x180)!=0){PACKET(p240,RND(360),0,2);SPAWN(801,1,p240);I(0x180)=0;B(0x184)=0;}
   if(emit_repeated(0,3,5))RETIRE();if(OUTSIDE(1480.0f,-200.0,1060.0f,-100.0))RETIRE();break;
  case 1:
   if(AT(this,void *,0x34c)==0){B(0x113)=0;S(0x364)-=5;if(S(0x364)<1){S(0x364)=0;RETIRE();}set_secondary_flags(0,1);set_secondary_alpha(B(0x364));}
   else{float x_random=RND(60);void *related=AT(this,void *,0x34c);F(0xec)=x_random+AT(related,float,0xec)-30.0;F(0xf0)=RND(60)+AT(related,float,0xf0)-30.0;
    if(I(0x144)%3==0 && AT(related,int,0x144)>11){PACKET(p120,RND(360),RND(7)+4.0,2);SPAWN(818,1,p120);}}
   break;
  case 2:H[1]*=D(0.9f);MOVE();if(I(0x144)>24){if(B(0x113)<5)RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;}break;
  case 3:SCALE(F(0x11c)*D(0.7f));if(F(0x11c)<D(0.1f)){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}break;
  case 4:SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.95f);if(I(0x144)>11){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}break;
  }
  STEP();if(advance_frame())--I(0x330);return;
 case 823:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   if(emit_repeated(0,2,3))RETIRE();SCALE(F(0x11c)+D(0.005f));
   if(AT(this,void *,0x34c)){
    if(I(0x144)%60==0){PACKET(p216,0,0,1);spawn_parented(823,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p216),3);}
    void *related=AT(this,void *,0x34c);F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(-AT(related,float,0x12c))*50.0*AT(related,float,0x11c)*H[1]+AT(related,float,0xec);
    double sine=lookup_orientation_sine_quantized_abs(-AT(related,float,0x12c));related=AT(this,void *,0x34c);F(0xf0)=sine*50.0*AT(related,float,0x11c)*H[1]+AT(related,float,0xf0);
    if(AT(related,signed char,0x184)>0){if(I(0x144)%5==0){PACKET(p408,RND(360),RND(7)+4.0,3);SPAWN(823,1,p408);}break;}
   }
   SCALE(F(0x11c)*D(0.9f));if(F(0x11c)<=0.5f){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}break;
  }
  case 1:
   if(AT(this,void *,0x34c)==0)RETIRE();F(0xec)=AT(AT(this,void *,0x34c),float,0xec);F(0xf0)=AT(AT(this,void *,0x34c),float,0xf0);SCALE(F(0x11c)+D(0.02f));
   if(I(0x144)>14){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}break;
  case 2: {
   if(emit_repeated(0,0,0))B(0x184)=0;
   bool end=advance_six(10)!=0;if(!end){if(I(0x144)>=360)end=true;else{short action=AT(P,short,0x13c);if((action==570 || action==571 || action==572 || action==573) && AT(P,short,0x140)==0 && AT(P,short,0x13e)==0)end=true;}}
   if(end)B(0x184)=0;
   if(I(0x180)!=0){if(S(0x364)<11){++S(0x364);return;}if(C(0x184)>0){if(++S(0x364)>19){S(0x364)=0;I(0x180)=0;}}}
   if(C(0x184)==0){F(0x120)*=D(0.9f);if(F(0x120)<=0.5f){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}}
   else{F(0x12c)+=H[0];F(0x11c)+=D(0.05f);if(F(0x11c)>=5.0f)F(0x11c)=5;publish_bounds(static_cast<int>(F(0x11c)*-50.0),10,static_cast<int>(F(0x11c)*50.0),-10,static_cast<short>(F(0x12c)),0,0);F(0xec)+=C(0x104)*4;}
   break;
  }
  case 3:H[1]*=D(0.9f);MOVE();SCALE(F(0x11c)*D(0.9f));if(I(0x144)>24){if(B(0x113)<5)RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;}STEP();break;
  }
  if(advance_frame())--I(0x330);return;
 case 850:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   H[1]-=1.0;if(H[1]<1.0f){H[1]=1;P->dispatch_character_wave_handle(2);p492[1]=0;p492[2]=1;int angle=0;do{p492[0]=static_cast<float>(angle);SPAWN(850,1,p492);angle+=45;}while(angle<360);p492[2]=4;SPAWN(850,1,p492);P->dispatch_character_wave_handle(51);RETIRE();}
   MOVE();if(I(0x144)%5==0){PACKET(p396,0,0,5);SPAWN(850,1,p396);}if(advance_six(15)){F(0x12c)=RND(360);select_sequence(2);F(0xf4)=F(0xf8)=0;return;}
   if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>14){I(0x180)=0;S(0x364)=0;}
   if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();break;
  case 1: {
   if(H[1]<1.0f)H[1]=1;H[1]=(1.0-F(0x378))*250.0;F(0x378)*=D(0.96f);H[0]+=4.0;advance_six(0);advance_phase(2);
   float *heading=H;F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(-heading[0])*H[1]+F(0x374);
   if(I(0x144)<60 && C(0x184)>0)break;select_sequence(2);int n=6;do{PACKET(p372,RND(360),RND(6)+6.0,3);SPAWN(850,1,p372);--n;}while(n!=0);F(0x12c)=RND(360);break;
  }
  case 2:SCALE(F(0x11c)+D(0.05f));break;
  case 3:MOVE();H[1]*=D(0.95f);if(I(0x144)>=15){SCALE(F(0x11c)*D(0.99f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 4:SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.9f);if(I(0x144)>=15){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 5:if(I(0x144)>=6){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  }
  STEP();if(advance_frame())--I(0x330);if(ENTRY(3))--I(0x330);return;
 case 851:
  if(I(0x180)==5 || AT(P,short,0x13c)!=601)RETIRE();position_relative(130,125);if(S(0x13e)==1 && AT(P,short,0x140)>11){select_sequence(2);return;}
  if(AT(P,short,0x186)>0 && S(0x13e)<2)return;if(advance_frame())--I(0x330);return;
 case 852:
  switch(S(0x13e)) {
  case 0: {
   F(0xf0)-=160.0;double y=F(0xf0);
   if(stage_surface_height()>y)goto iku_ground_clamp;
   goto iku_ground_advance;
  }
  case 1:
   if(AT(P,short,0x13c)!=602)RETIRE();F(0x370)-=120.0;if(F(0x370)<0.0)F(0x370)=0;F(0xf0)=AT(P,float,0xf0)+320.0+F(0x370);F(0xec)=AT(P,float,0xec);advance_six(0);
   if(I(0x144)>=20){F(0x11c)*=D(0.95f);if(I(0x144)>24)FADE(15,15);}break;
  case 2:
   if(AT(P,short,0x13c)!=602)RETIRE();if(AT(P,short,0x13e)<2){advance_six(0);advance_phase(0);F(0xf0)=AT(P,float,0xf0);F(0xec)=AT(P,float,0xec);if(I(0x180)!=0 && ++S(0x364)>4){S(0x364)=0;B(0x184)=1;I(0x180)=0;}}else COLORFADE(15);break;
  case 3:if(AT(P,short,0x13c)!=602)RETIRE();if(AT(P,short,0x13e)>1)COLORFADE(15);else{F(0xf0)=AT(P,float,0xf0);F(0xec)=AT(P,float,0xec);}break;
  case 4:MOVE();H[1]*=D(0.9f);if(!(H[1]>=0.5f))H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*D(0.2f);SCALE(F(0x11c)*D(0.99f));if(I(0x144)>11)FADE(6,5);break;
  case 5:SCALE(F(0x11c)*D(0.9f));if(I(0x144)>4){if(B(0x113)<11)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 6:SCALE(F(0x11c)+D(0.15f));if(B(0x113)<16)RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x112)-=15;break;
  }
  if(advance_frame())--I(0x330);return;
 case 853:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(S(0x364)<2 && AT(P,short,0x174)<1)S(0x364)=2;
   if(S(0x364)==0){SCALE(F(0x11c)+D(0.1f));if(F(0x11c)>=1.0){S(0x364)=1;int angle=0;do{PACKET(p540,angle+22.5+F(0x370),40,4);int layer=(!(p540[0]>=0.0 && p540[0]<=180.0f))?-1:1;SPAWN(853,layer,p540);angle+=45;}while(angle<360);PACKET(p540,0,0,2);spawn_parented(853,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p540),3);p540[2]=1;SPAWN(853,1,p540);}}
   if(S(0x364)==1){F(0xf8)+=D(0.1f);if(F(0xf8)>2.0f)F(0xf8)=2;if(I(0x144)%2==0){F(0x12c)=RND(360);SCALE(RND(10)*D(0.1f)+2.0);}if(I(0x144)>159)S(0x364)=2;}
   if(S(0x364)==2){SCALE(F(0x11c)*D(0.9f));COLORFADE(15);}F(0xf0)+=F(0xf8);break;
  case 1:
   F(0x11c)*=D(0.99f);if(AT(P,short,0x13c)!=603)RETIRE();if(AT(P,short,0x13e)<2){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+360.0;}
   if(S(0x140)==4){if(B(0x113)<15)RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x112)-=15;}break;
  case 2:
   if(AT(this,void *,0x34c)==0)S(0x364)=1;else{void *related=AT(this,void *,0x34c);F(0xec)=AT(related,float,0xec);F(0xf0)=AT(related,float,0xf0);if(AT(related,short,0x364)==2)S(0x364)=1;}
   if(S(0x364)==0){if(I(0x144)%7==0){PACKET(p348,0,0,3);SPAWN(853,1,p348);}SCALE((1.0-F(0x370))+1.0);F(0x370)*=D(0.9f);int lo=static_cast<int>(F(0x11c)*-80.0);int hi=static_cast<int>(F(0x11c)*80.0);publish_bounds(lo,hi,hi,lo,0,0,0);
    if(AT(this,void *,0x34c)){if(AT(AT(this,void *,0x34c),short,0x364)==1){advance_six(0);if(I(0x180)!=0 && ++S(0x366)>4){S(0x366)=0;B(0x184)=1;I(0x180)=0;}}else S(0x364)=1;}}
   if(S(0x364)==1){B(0x184)=0;SCALE(F(0x11c)*D(0.9f));COLORFADE(15);}break;
  case 3:SCALE(F(0x11c)+D(0.3f));COLORFADE(20);break;
  case 4:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*D(0.2f);SCALE(F(0x11c)*D(0.99f));if(I(0x144)>11)FADE(6,5);break;
  }
  if(advance_frame())--I(0x330);return;
 case 856:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   advance_six(0);advance_phase(3);if(I(0x144)%5==0){PACKET(p324,H[0],0,2);SPAWN(856,1,p324);}if(I(0x144)%2==0){PACKET(p300,RND(360),RND(10)+2.0,4);SPAWN(856,1,p300);}
   if(I(0x144)>29){B(0x184)=0;I(0x180)=0;select_sequence(3);S(0x386)=0;F(0xf4)=F(0xf8)=0;return;}MOVE();STEP();break;
  case 1:SCALE(F(0x11c)+D(0.01f));break;
  case 2:if(I(0x144)>19)WARMCOLOR(10);break;
  case 3:
   if(I(0x144)>179)RETIRE();advance_six(0);advance_phase(3);
   if(I(0x144)<6){B(0x184)=0;if(I(0x144)==5){H[0]=-atan2_degrees(AT(A,float,0xf0)+100.0-F(0xf0),C(0x104)*(AT(A,float,0xec)-F(0xec)));B(0x184)=1;PACKET(p276,RND(360),0,1);SPAWN(856,1,p276);}}
   else{MOVE();if(I(0x144)%5==0){PACKET(p252,H[0],0,2);SPAWN(856,1,p252);}if(I(0x144)%2==0){PACKET(p228,RND(360),RND(10)+2.0,4);SPAWN(856,1,p228);}if(I(0x144)>29 && S(0x364)<2){++S(0x364);B(0x184)=0;I(0x180)=0;select_sequence(3);S(0x386)=0;F(0xf4)=F(0xf8)=0;return;}}
   STEP();break;
  case 4:H[1]*=D(0.9f);MOVE();F(0x11c)+=D(0.1f);F(0x120)*=D(0.9f);if(I(0x144)>24){if(B(0x113)<5)RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;}STEP();break;
  case 5:if(I(0x144)>5){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(2))RETIRE();if(ENTRY(3))--I(0x330);return;
 case 857:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){F(0xf0)=AT(P,float,0xf0);F(0xec)=AT(P,float,0xec);if(AT(P,short,0x7b0)<1)S(0x364)=1;
   if(S(0x364)==1)FADE(11,10);
   else{
    if(I(0x144)%10==0){PACKET(p432,RND(360),0,1);unsigned char facing;if(static_cast<unsigned>(selector_random_roll(100))<51)facing=static_cast<unsigned char>(-C(0x104));else facing=B(0x104);spawn_unparented(857,F(0xec),F(0xf0)+100.0,facing,1,reinterpret_cast<const unsigned *>(p432),3);}
    double owner_y=AT(P,float,0xf0);if(P->stage_surface_height()==owner_y){if(B(0x113)<246)B(0x113)+=10;else B(0x113)=255;
     if(I(0x144)%60==0){int angle=0;do{PACKET(p480,angle+30.0+RND(30),12,2);int layer=(!(p480[0]>=0.0 && p480[0]<=180.0f))?-1:1;SPAWN(815,layer,p480);angle+=60;}while(angle<360);}}
    else if(B(0x113)<11)B(0x113)=0;else B(0x113)-=10;
   }
  }else if(S(0x13e)==1){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;F(0x12c)+=15.0;SCALE(F(0x11c)+D(0.05f));FADE(16,15);}
  if(advance_frame())--I(0x330);return;
 case 859:
  if(AT(P,short,0x174)<1 && S(0x364)==0)S(0x364)=1;
  switch(S(0x13e)) {
  case 1:
   if(AT(P,short,0x13c)!=609 && S(0x364)==0)S(0x364)=1;
   if(S(0x364)!=1){position_relative(0,275);SCALE(F(0x11c)*D(0.9f));}
   else{SCALE(F(0x11c)*D(0.9f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}break;
  case 2:
   position_relative(0,100);++S(0x368);
   if(S(0x364)<2 && (S(0x368)>299 || AT(P,short,0x174)<1 || AT(A,short,0x174)<1 || (AT(P,short,0x13c)>599 && AT(P,short,0x13c)<690 && (AT(P,short,0x13c)!=609 || AT(P,short,0x13e)<1)))){S(0x364)=2;B(0x184)=0;}
   if(S(0x364)==0){if(I(0x144)%4==0){F(0x12c)=RND(360);SCALE(RND(75)*D(0.01f)+0.75);PACKET(p204,RND(360),RND(15)+10.0,4);SPAWN(859,1,p204);}
    if(I(0x180)==6){B(0x184)=1;I(0x180)=0;++S(0x366);}if(I(0x180)!=0)S(0x366)+=15;
    if(S(0x366)>14){S(0x366)=0;B(0x184)=0;S(0x364)=1;S(0x36a)=0;return;}}
   if(S(0x364)==1){F(0x11c)-=D(0.1f);if(F(0x11c)<0.5f)F(0x11c)=1;F(0x120)=F(0x11c);B(0x184)=0;
    if(++S(0x36a)>39){P->dispatch_character_wave_handle(0);S(0x36a)=0;S(0x364)=0;S(0x366)=0;B(0x184)=1;I(0x180)=0;PACKET(p516,0,0,6);spawn_parented(859,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p516),3);p516[2]=5;spawn_parented(859,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p516),3);p516[2]=9;spawn_parented(859,F(0xec),F(0xf0),B(0x104),-1,reinterpret_cast<const unsigned *>(p516),3);return;}}
   if(S(0x364)==2){B(0x184)=0;SCALE(F(0x11c)*D(0.95f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 3:
   if(S(0x364)<2 && AT(this,void *,0x34c)){
    if(AT(AT(this,void *,0x34c),short,0x364)==2){S(0x364)=2;return;}
    F(0xec)=AT(AT(this,void *,0x34c),float,0xec);float height=stage_surface_height();void *related=AT(this,void *,0x34c);F(0xf0)=height;
    if(!(AT(related,float,0xf0)>=150.0f)){SCALE((150.0-AT(related,float,0xf0))/150.0+1.0);B(0x113)=255;}
    else{SCALE(1.0);if(!(AT(related,float,0xf0)<=405.0))B(0x113)=0;else B(0x113)=static_cast<unsigned char>(405.0-AT(related,float,0xf0));}}
   if(S(0x364)==2){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 4:MOVE();H[1]*=D(0.98f);if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();if(I(0x144)>9){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}STEP();break;
  case 5:
   if(AT(this,void *,0x34c)==0 || AT(AT(this,void *,0x34c),short,0x364)!=0)RETIRE();F(0xec)=AT(AT(this,void *,0x34c),float,0xec);F(0xf0)=AT(AT(this,void *,0x34c),float,0xf0);if(S(0x142)==0 && S(0x140)==4)F(0x12c)=RND(360);break;
  case 6:SCALE(F(0x11c)+D(0.35f));if(I(0x144)>9){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 7:MOVE();if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();if(I(0x180)!=0 || F(0xf0)<=0.0 || S(0x364)==1){F(0x12c)=RND(360);next_sequence_block();F(0xf4)=F(0xf8)=0;return;}STEP();break;
  case 8:SCALE(F(0x11c)+D(0.05f));break;
  case 9:
   if(AT(this,void *,0x34c)==0)S(0x364)=1;else{void *related=AT(this,void *,0x34c);F(0xec)=AT(related,float,0xec);F(0xf0)=AT(related,float,0xf0);if(AT(related,short,0x364)!=0)S(0x364)=1;}
   if(S(0x364)!=0){SCALE(F(0x11c)*D(0.995f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}
   else{if(B(0x113)<251)B(0x113)+=5;else B(0x113)=255;SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*3.0f)*D(0.3f)+D(1.2f));}break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(1))--I(0x330);if(ENTRY(2))--I(0x330);if(ENTRY(9))--I(0x330);return;
 case 860:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(S(0x364)==0){if(I(0x144)>1){float dx=F(0xec)-F(0x370);float dy=F(0xf0)-F(0x374);float norm=dx*dx+dy*dy;float radius=sqrt_float_value(norm);F(0xf4)=(dy*C(0x104)*7.0+dx*2.0)/radius;F(0xf8)=(dy*2.0-C(0x104)*dx*7.0)/radius;H[0]=-atan2_degrees(F(0xf8),C(0x104)*F(0xf4));}
    advance_six(0);advance_phase(3);if(I(0x144)>7 && I(0x144)%8==0){PACKET(p180,H[0],0,2);SPAWN(860,1,p180);}if(I(0x144)>299){S(0x364)=1;return;}}
   if(S(0x364)==1){SCALE(F(0x11c)*D(0.99f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}F(0xec)+=F(0xf4);F(0xf0)+=F(0xf8);break;
  case 1:SCALE(F(0x11c)+D(0.01f));break;
  case 2:advance_six(0);advance_phase(3);if(I(0x144)>=0)WARMCOLOR(10);break;
  case 3:H[1]*=D(0.9f);MOVE();if(I(0x144)>9){SCALE(F(0x11c)*D(0.98f));if(B(0x113)<5)RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;}F(0xec)+=F(0xf4);F(0xf0)+=F(0xf8);break;
  case 4:
   if(S(0x364)==0){SCALE(F(0x11c)+D(0.1f));if(F(0x11c)>=1.0)S(0x364)=1;}
   if(S(0x364)==1 && I(0x144)%2==0){F(0x12c)=RND(360);SCALE(RND(10)*D(0.1f)+2.0);}
   if(S(0x364)<=1){if((AT(P,short,0x13c)==610 || AT(P,short,0x13c)==660) && AT(P,short,0x13e)<2){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+275.0;}else S(0x364)=2;}
   if(S(0x364)==2){SCALE(F(0x11c)*D(0.9f));COLORFADE(15);}break;
  case 5:SCALE(F(0x11c)+0.5);COLORFADE(15);break;
  case 6:advance_six(0);advance_phase(0);if(I(0x144)>3)B(0x184)=0;SCALE(F(0x11c)*D(0.95f));COLORFADE(15);break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(2))--I(0x330);return;
 case 898:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){if(S(0x140)==4){F(0x11c)*=D(0.995f);F(0x120)*=D(0.9995f);FADE(6,5);}}
  else if(S(0x13e)==1){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;if(I(0x144)==2)SCALE(1.0);if(I(0x144)>30){FADE(5,5);if(B(0x112)>14){B(0x112)-=15;B(0x111)-=15;}}SCALE(F(0x11c)*D(0.95f));}
  else if(S(0x13e)==2){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;if(I(0x144)>10){FADE(5,5);if(B(0x112)>4){B(0x112)-=5;B(0x111)-=5;}}SCALE(F(0x11c)+D(0.01f));}
  if(advance_frame())--I(0x330);return;
 case 899:
  if(S(0x13e)==4){
   if(S(0x364)==0){F(0xec)=C(0x104)*166+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+137.0;if(AT(P,short,0x13c)!=408)RETIRE();if(AT(P,short,0x140)>7){S(0x364)=1;SCALE(1.5);return;}}
   if(S(0x364)>0){SCALE(F(0x11c)*D(0.85f));if(F(0x11c)<=0.01)RETIRE();}
  }else if(S(0x13e)==5){F(0xec)=C(0x104)*166+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+137.0;if(I(0x144)>5){SCALE(F(0x11c)*D(0.85f));if(F(0x11c)<=0.01)RETIRE();}if(AT(P,short,0x13c)!=408 && AT(P,short,0x13c)!=322)RETIRE();}
  else if(S(0x13e)==6){if(S(0x364)==1){F(0xec)=C(0x104)*96+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+129.0;if(AT(P,short,0x13c)!=300 || AT(P,short,0x140)>5)S(0x364)=1;}
   else{SCALE(F(0x11c)*D(0.95f));if(B(0x113)<15)RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x112)-=15;}}
  if(advance_frame())--I(0x330);return;
 case 900:
  if(AT(P,short,0x174)<1 && S(0x364)==0)S(0x364)=1;
  switch(S(0x13e)) {
  case 0: {
   SCALE(F(0x11c)+D(0.005f));
   if(AT(this,void *,0x34c)){
    if(I(0x144)%60==0){PACKET(p156,0,0,1);spawn_parented(900,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p156),3);}
    void *related=AT(this,void *,0x34c);F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(-AT(related,float,0x12c))*50.0*AT(related,float,0x11c)*H[1]+AT(related,float,0xec);
    double sine=lookup_orientation_sine_quantized_abs(-AT(related,float,0x12c));related=AT(this,void *,0x34c);F(0xf0)=sine*50.0*AT(related,float,0x11c)*H[1]+AT(related,float,0xf0);
    if(AT(related,signed char,0x184)!=0){if(I(0x144)%5==0){PACKET(p132,RND(360),RND(7)+4.0,3);SPAWN(900,1,p132);}if(I(0x144)%10==0 && g_match_identifier==3){PACKET(p108,AT(AT(this,void *,0x34c),float,0x12c)+90.0,0,7);SPAWN(900,1,p108);}break;}
   }
   SCALE(F(0x11c)*D(0.9f));if(F(0x11c)<=0.5f){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}break;
  }
  case 1:
   if(AT(this,void *,0x34c)==0)RETIRE();F(0xec)=AT(AT(this,void *,0x34c),float,0xec);F(0xf0)=AT(AT(this,void *,0x34c),float,0xf0);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=15){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}break;
  case 2:
   F(0x12c)+=H[0];
   switch(g_match_identifier){
   case 0:F(0x11c)+=D(0.025f);if(F(0x11c)>=2.5f)F(0x11c)=2.5f;break;
   case 1:F(0x11c)+=D(0.04f);if(F(0x11c)>=4.0f)F(0x11c)=4;break;
   case 2:F(0x11c)+=D(0.06f);if(F(0x11c)>=6.0f)F(0x11c)=6;break;
   case 3:F(0x11c)+=D(0.05f);if(F(0x11c)>=7.0)F(0x11c)=7;break;
   }
   advance_six(0);advance_phase(0);if(S(0x364)==1 || AT(P,short,0x174)<1)B(0x184)=0;
   publish_bounds(static_cast<int>(F(0x11c)*-50.0),10,static_cast<int>(F(0x11c)*50.0),-10,static_cast<short>(F(0x12c)),0,0);
   if(I(0x180)!=0 && C(0x184)>0 && ++S(0x366)>9){S(0x366)=0;I(0x180)=0;}
   if(C(0x184)==0 || I(0x144)>299){B(0x184)=0;F(0x120)*=D(0.9f);if(F(0x120)<=D(0.1f)){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}}
   F(0xec)=lookup_orientation_cosine_quantized_abs(-H[1])*(C(0x104)*3)+F(0xec);F(0xf0)=lookup_orientation_sine_quantized_abs(-H[1])*3.0+F(0xf0);break;
  case 3:H[1]*=D(0.9f);MOVE();SCALE(F(0x11c)*D(0.9f));if(I(0x144)>24){if(B(0x113)<5)RETIRE();B(0x113)-=5;B(0x112)-=5;B(0x111)-=5;}STEP();break;
  case 4:if(AT(this,void *,0x34c)==0)RETIRE();F(0xec)=AT(AT(this,void *,0x34c),float,0xec);F(0xf0)=AT(AT(this,void *,0x34c),float,0xf0);F(0x11c)*=D(0.95f);break;
  case 5:if(AT(P,short,0x13c)!=710 && S(0x364)==0)S(0x364)=1;if(S(0x364)==1){SCALE(F(0x11c)*D(0.9f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}else{position_relative(100,145);SCALE(F(0x11c)*D(0.9f));}break;
  case 6:SCALE(F(0x11c)+D(0.3f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;break;
  case 7:if(I(0x180)!=0 || I(0x144)>59){B(0x184)=0;if(B(0x113)<15)RETIRE();B(0x113)-=15;B(0x112)-=15;B(0x111)-=15;}break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(5))--I(0x330);
  if(S(0x13e)==4 && S(0x142)==0 && S(0x140)==3){p528[0]=RND(10)*D(0.1f)+1.0;if(static_cast<unsigned>(selector_random_roll(100))<51)p528[0]*=-1.0;p528[1]=-atan2_degrees(AT(A,float,0xf0)+100.0-F(0xf0),C(0x104)*(AT(A,float,0xec)-F(0xec)));p528[2]=2;SPAWN(900,1,p528);PACKET(p528,0,0,6);SPAWN(900,1,p528);}return;
 case 910:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x174)<1)RETIRE();
   if(H[1]==0.0){int limit,period;switch(g_match_identifier){case 0:limit=2;period=45;break;case 1:limit=3;period=30;break;case 2:limit=4;period=30;break;case 3:limit=5;period=30;break;}
    if(I(0x144)%period==0){if(limit<=S(0x364))RETIRE();++S(0x364);PACKET(p84,0,45,4);unsigned char facing=static_cast<unsigned>(selector_random_roll(100))>50?static_cast<unsigned char>(-1):1;float y=A->stage_surface_height();spawn_unparented(910,AT(A,float,0xec),y,facing,1,reinterpret_cast<const unsigned *>(p84),3);}}
   if(H[1]==1.0){int limit,period;switch(g_match_identifier){case 0:limit=4;period=25;break;case 1:limit=6;period=20;break;case 2:limit=8;period=15;break;case 3:limit=10;period=13;break;}
    if(I(0x144)%period==0){if(limit<=S(0x364))RETIRE();++S(0x364);PACKET(p60,0,15,4);unsigned char facing=static_cast<unsigned>(selector_random_roll(100))>50?static_cast<unsigned char>(-1):1;float y=stage_surface_height();float x=RND(600)+F(0xec)-300.0;spawn_unparented(910,x,y,facing,1,reinterpret_cast<const unsigned *>(p60),3);}}
   if(H[1]==2.0f){int limit,period;switch(g_match_identifier){case 0:limit=3;period=40;break;case 1:limit=4;period=40;break;case 2:limit=6;period=40;break;case 3:limit=8;period=40;break;}
    if(I(0x144)%period==0){if(limit<=S(0x364))RETIRE();++S(0x364);PACKET(p36,0,45,4);unsigned char facing=static_cast<unsigned>(selector_random_roll(100))>50?static_cast<unsigned char>(-1):1;float x=RND(1280);spawn_unparented(910,x,0,facing,1,reinterpret_cast<const unsigned *>(p36),3);}}
   break;
  case 1:F(0x11c)*=D(0.98f);F(0x120)-=D(0.001f);advance_six(0);advance_phase(0);F(0x370)*=D(0.95f);if(F(0x370)<=D(0.05f))F(0x370)=0.05f;if(I(0x144)>9){if(B(0x113)<15)RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x112)-=15;}break;
  case 2:SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.85f);if(F(0x370)<=D(0.05f))F(0x370)=0.05f;if(I(0x144)>2){if(B(0x113)<20)RETIRE();B(0x113)-=20;B(0x111)-=20;B(0x112)-=20;}break;
  case 3:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*D(0.2f);SCALE(F(0x11c)*D(0.99f));if(I(0x144)>11)FADE(6,5);break;
  case 4:
   F(0xf0)*=D(0.85f);F(0x11c)*=D(0.99f);F(0x120)*=D(0.95f);
   if(H[1]<=static_cast<float>(I(0x144))){--I(0x330);PACKET(p580,0,0,5);spawn_unparented(910,F(0xec),0,B(0x104),1,reinterpret_cast<const unsigned *>(p580),3);p580[2]=1;spawn_unparented(910,F(0xec),0,B(0x104),1,reinterpret_cast<const unsigned *>(p580),3);p580[2]=2;spawn_unparented(910,F(0xec),0,B(0x104),-1,reinterpret_cast<const unsigned *>(p580),3);
    int angle=0;do{PACKET(p580,angle+22.5+F(0x370),30,3);int layer=(!(p580[0]>=0.0 && p580[0]<=180.0f))?-1:1;SPAWN(910,layer,p580);angle+=45;}while(angle<360);
    if(g_match_identifier==3){int n=7;do{PACKET(p580,-10.0-RND(160),RND(25)+10.0,7);SPAWN(910,1,p580);--n;}while(n!=0);}P->dispatch_character_wave_handle(13);return;}
   break;
  case 5:if(I(0x144)%4==0)F(0x12c)=RND(360);SCALE(F(0x11c)*D(0.95f));F(0x370)*=D(0.95f);if(F(0x370)<=D(0.05f))F(0x370)=0.05f;if(I(0x144)>9){if(B(0x113)<15)RETIRE();B(0x113)-=15;B(0x111)-=15;B(0x112)-=15;}break;
  case 6:if(B(0x113)<246)B(0x113)+=10;else B(0x113)=255;if(AT(this,void *,0x34c)==0)RETIRE();SCALE(F(0x11c)+D(0.02f));break;
  case 7:
   if(AT(P,short,0x174)<1 && S(0x364)==0)S(0x364)=1;if(I(0x144)>59)S(0x364)=1;MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;
   if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();if(I(0x180)!=0 || S(0x364)==1){F(0x12c)=RND(360);next_sequence_block();F(0xf4)=F(0xf8)=0;return;}STEP();break;
  case 8:SCALE(F(0x11c)+D(0.05f));break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(2))--I(0x330);return;
 case 920:
  if(AT(P,short,0x174)<1 && S(0x364)==0)S(0x364)=1;
  switch(S(0x13e)) {
  case 1:
   if(AT(P,short,0x13c)!=730 && S(0x364)==0)S(0x364)=1;
   if(S(0x364)!=1){position_relative(0,275);SCALE(F(0x11c)*D(0.9f));}
   else{SCALE(F(0x11c)*D(0.9f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x112)-=10;B(0x111)-=10;}break;
  case 2:
   if(AT(P,short,0x13c)==730)position_relative(0,100);else S(0x364)=1;
   if(S(0x364)==0){if(I(0x144)%4==0){F(0x12c)=RND(360);SCALE(RND(75)*D(0.01f)+0.75);PACKET(p12,RND(360),RND(15)+10.0,4);SPAWN(920,1,p12);}
    if(I(0x180)==6){B(0x184)=1;I(0x180)=0;++S(0x366);}if(I(0x180)==4){B(0x184)=1;I(0x180)=0;S(0x366)+=2;}if(I(0x180)==8){B(0x184)=1;I(0x180)=0;S(0x366)+=20;}
    if(I(0x180)!=0 && ++S(0x366)>9){S(0x366)=0;I(0x180)=0;B(0x184)=1;}
    float lifetime;switch(g_match_identifier){case 0:lifetime=360;break;case 1:lifetime=480;break;case 2:lifetime=540;break;case 3:lifetime=600;break;}
    if(static_cast<float>(S(0x366)+I(0x144))>=lifetime || AT(P,short,0x13c)!=730)S(0x364)=1;
   }else{B(0x184)=0;SCALE(F(0x11c)*D(0.95f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 3:
   if(S(0x364)!=0){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}
   else if(AT(this,void *,0x34c)){
    if(AT(AT(this,void *,0x34c),short,0x364)==1){S(0x364)=1;return;}
    F(0xec)=AT(AT(this,void *,0x34c),float,0xec);float height=stage_surface_height();void *related=AT(this,void *,0x34c);F(0xf0)=height;
    if(!(AT(related,float,0xf0)>=150.0f)){SCALE((150.0-AT(related,float,0xf0))/150.0+1.0);B(0x113)=255;}
    else{SCALE(1.0);if(!(AT(related,float,0xf0)<=405.0))B(0x113)=0;else B(0x113)=static_cast<unsigned char>(405.0-AT(related,float,0xf0));}}
   break;
  case 4:MOVE();H[1]*=D(0.98f);if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();if(I(0x144)>9){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}STEP();break;
  case 5:
   if(AT(this,void *,0x34c)==0 || AT(AT(this,void *,0x34c),short,0x364)!=0)RETIRE();F(0xec)=AT(AT(this,void *,0x34c),float,0xec);F(0xf0)=AT(AT(this,void *,0x34c),float,0xf0);if(S(0x142)==0 && S(0x140)==4)F(0x12c)=RND(360);break;
  case 6:SCALE(F(0x11c)+D(0.35f));if(I(0x144)>9){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 7:MOVE();if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();if(I(0x180)!=0 || F(0xf0)<=0.0 || S(0x364)==1){F(0x12c)=RND(360);next_sequence_block();F(0xf4)=F(0xf8)=0;return;}STEP();break;
  case 8:SCALE(F(0x11c)+D(0.05f));break;
  case 9:
   if(AT(this,void *,0x34c)==0)S(0x364)=1;else{void *related=AT(this,void *,0x34c);F(0xec)=AT(related,float,0xec);F(0xf0)=AT(related,float,0xf0);S(0x364)=AT(related,short,0x364);}
   if(S(0x364)!=0){SCALE(F(0x11c)*D(0.995f));if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}
   else{if(B(0x113)<251)B(0x113)+=5;else B(0x113)=255;SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*3.0f)*D(0.3f)+D(1.2f));}break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(1))--I(0x330);if(ENTRY(9))--I(0x330);return;
 case 930:
  if(AT(P,short,0x174)<1 && S(0x364)==0)S(0x364)=1;
  switch(S(0x13e)) {
  case 0:MOVE();if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();if(I(0x180)!=0 || F(0xf0)<=0.0 || S(0x364)==1){F(0x12c)=RND(360);next_sequence_block();F(0xf4)=F(0xf8)=0;return;}STEP();break;
  case 1:SCALE(F(0x11c)+D(0.05f));break;
  case 2:
   if(S(0x364)==0){F(0x120)+=D(0.01f);if(F(0x120)>0.25f)F(0x120)=0.25f;if(I(0x144)>59){P->dispatch_character_wave_handle(1);next_sequence_block();B(0x184)=1;F(0x120)=2;return;}}
   else{F(0x120)*=D(0.98f);if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  case 3:if(S(0x364)!=0){B(0x184)=0;F(0x120)*=D(0.98f);if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}else{advance_six(0);advance_phase(0);if(I(0x144)>29)S(0x364)=1;}break;
  case 4:SCALE(F(0x11c)+0.5);if(I(0x144)>9){if(B(0x113)<10)RETIRE();B(0x113)-=10;B(0x111)-=10;B(0x112)-=10;}break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(2))--I(0x330);return;
 case 980:update_ping_pong_motion();if(advance_frame())--I(0x330);return;
 case 995:
  if(S(0x13e)==0){F(0x370)-=15.0;B(0x111)=AT(P,unsigned char,0x7b2);B(0x110)=AT(P,unsigned char,0x7b2);set_sprite_uv_size(0,F(0x370));if(AT(P,short,0x78c)>0)FADE(5,5);}
  else if(static_cast<unsigned>(S(0x13e)-1)<2){B(0x111)=AT(P,unsigned char,0x7b2);B(0x110)=AT(P,unsigned char,0x7b2);if(AT(P,short,0x78c)>0)FADE(5,5);F(0xf0)+=30.0;if(F(0xf0)>800.0)RETIRE();}
  if(advance_frame())--I(0x330);return;
 case 998:
  F(0x12c)+=20.0;SCALE(F(0x11c)+D(0.05f));
  if(AT(P,short,0x13c)>153 && AT(P,short,0x13c)<158){F(0xec)=C(0x104)*58+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+87.0;}
  if(AT(P,short,0x13c)>149 && AT(P,short,0x13c)<154){F(0xec)=C(0x104)*71+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+137.0;}
  if(AT(P,short,0x13c)==158){F(0xec)=C(0x104)*43+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+136.0;}
  if(S(0x13e)==1)FADE(10,10);if(advance_frame())--I(0x330);if(ENTRY(1))AT(P,unsigned char,0x751)=0;return;
 }
 return;
iku_ground_clamp:
 F(0xf0)=stage_surface_height();
iku_ground_advance:
 advance_six(0);
 if(I(0x180)!=0 && C(0x184)>0 && ++S(0x364)>9){S(0x364)=0;I(0x180)=0;}
 if(I(0x144)>=30){F(0x11c)*=D(0.95f);if(I(0x144)>24)FADE(15,15);}
 if(advance_frame())--I(0x330);return;
}
#undef OUTSIDE
#undef WARMCOLOR
#undef COLORFADE
#undef FADE
#undef PACKET
#undef SPAWN
#undef ENTRY
#undef SCALE
#undef STEP
#undef MOVE
#undef RETIRE
#undef RND
#undef D
#undef A
#undef P
#undef H
#undef I
#undef C
#undef B
#undef S
#undef F
#undef AT
}
