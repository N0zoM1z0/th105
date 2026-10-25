// Complete manual JP1.06a56F700 source hypothesis; not canonically exact.
// Evidence: docs/YUYUKO_OBJECT_UPDATE_2026_10_25.md.
#include "YuyukoObjectUpdate.hpp"
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define I(o) AT(this,int,o)
#define H AT(this,float *,0x340)
#define P AT(this,YuyukoObjectUpdateView *,0x348)
#define A AT(this,YuyukoObjectUpdateView *,0x170)
#define T AT(this,YuyukoObjectUpdateView *,0x34c)
#define MOTION reinterpret_cast<YuyukoUpdateMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define D(v) static_cast<double>(v)
#define RND(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
#define RETIRE() do {--I(0x330);return;}while(0)
#define MOVE() MOTION->set_components(H[0],H[1])
#define STEP() do {F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8);}while(0)
#define SCALE(v) F(0x120)=F(0x11c)=static_cast<float>(v)
#define FADE(t,d) do {if(B(0x113)<t)RETIRE();B(0x113)-=d;}while(0)
#define COLORFADE(t,d) do {if(B(0x113)<t)RETIRE();B(0x113)-=d;B(0x112)-=d;B(0x111)-=d;}while(0)
#define ENTRY(n) (I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==n)
#define OUTSIDE(xh,xl,yh,yl) (F(0xec)>xh || F(0xec)<xl || F(0xf0)>yh || F(0xf0)<yl)
#define PACKET(p,a,b,c) do{p[0]=a;p[1]=b;p[2]=c;}while(0)
#define SPAWN(a,l,p) spawn_unparented(a,F(0xec),F(0xf0),B(0x104),l,reinterpret_cast<const unsigned *>(p),3)
void YuyukoObjectUpdateView::update_action_state()
{
 float p12[3],p24[3],p36[3],p48[3],p60[3],p72[3],p84[3],p96[3],p108[3],p120[3],p132[3],p144[3],p156[3],p168[3],p180[3],p192[3],p204[3],p216[3],p228[3],p240[3],p252[3],p264[3],p276[3],p288[3],p300[3],p312[3],p324[3],p336[3],p348[3],p360[3],p372[3],p384[3],p396[3],p408[3],p420[3],p432[3],p444[3],p456[3],p468[3],p480[3],p492[3],p504[3],p516[3],p528[3],p540[3],p552[3];
 switch(S(0x13c)) {
 case 800:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 1:case 2:case 3:
   if(emit_repeated(0,0,4))RETIRE();
   if(I(0x180)!=0 || I(0x144)>119){--I(0x330);int count=4;do{PACKET(p288,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(800,1,p288);}while(--count!=0);return;}
   if(F(0x11c)>=1.0)F(0x11c)+=D(0.01f);else{F(0x11c)+=D(0.02f);if(!(F(0x11c)<=1.0))F(0x11c)=1;}F(0x120)=F(0x11c);H[1]+=D(0.2f);MOVE();F(0x12c)=H[0];break;
  case 4:case 5:case 6:case 7:
   F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);break;
  case 8:case 9:case 10:case 11:
   F(0xf4)=F(0xf8)=0;if(T==0)RETIRE();F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*0.5+1.0);break;
  case 12:case 13:case 14:case 15:
   if(emit_repeated(0,0,4))RETIRE();
   if(I(0x180)!=0 || I(0x144)>59){--I(0x330);int count=3;do{PACKET(p456,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)-8));SPAWN(800,1,p456);}while(--count!=0);return;}
   H[1]*=D(0.92f);MOVE();F(0x12c)=H[0];break;
  case 16:case 17:case 18:case 19:SCALE(F(0x11c)*D(0.98f));if(I(0x144)>14)FADE(10,10);break;
  }
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();STEP();break;
 case 801:
  switch(S(0x13e)) {
  case 0:SCALE(F(0x11c)-D(0.03f));FADE(15,15);break;
  case 1:
   if(emit_repeated(0,0,4))RETIRE();if(I(0x144)==0)replace_secondary(990,20,10,1,2);
   SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*D(0.1f)+D(0.8f));F(0xf4)+=D(0.3f);
   if(F(0xf0)<=AT(AT(P,void *,0x170),float,0xf0)+100.0){F(0xf8)+=D(0.3f);if(F(0xf8)>8.0f)F(0xf8)=8;}
   else{F(0xf8)-=D(0.3f);if(F(0xf8)<-8.0f)F(0xf8)=-8;}advance_six(5);if(I(0x180)!=0)RETIRE();break;
  case 2:FADE(13,13);MOVE();F(0xf8)+=F(0x370);F(0x370)+=D(0.2f);break;
  case 3:
   if(emit_repeated(0,3,5))RETIRE();
   if(S(0x364)<2){SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*10.0)*D(0.1f)+D(0.9f));if(C(0x184)==0 || I(0x144)>=150 || ((AT(P,short,0x13c)==411 || AT(P,short,0x13c)==415) && AT(P,short,0x13e)==0 && AT(P,short,0x140)==0))S(0x364)=2;}
   advance_six(0);if(I(0x180)!=0 && ++S(0x366)>3 && C(0x184)>0){S(0x366)=0;I(0x180)=0;}
   if(I(0x144)%5==0){PACKET(p120,0,0,4);unsigned char facing=B(0x104);spawn_unparented(801,(RND(70)-35.0)+F(0xec),(RND(70)-35.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p120),3);}
   if(S(0x364)==0){H[1]-=0.5;if(H[1]<=0.0){H[1]=0;S(0x364)=1;}}
   if(S(0x364)==1){turn_heading(0,10,100);H[1]+=D(0.05f);if(H[1]>=3.0f)H[1]=3;}
   if(S(0x364)==2){B(0x184)=0;F(0xf4)=F(0xf8)=0;SCALE(F(0x11c)*D(0.9f));FADE(15,15);}MOVE();break;
  case 4:FADE(10,10);SCALE(F(0x11c)*D(0.97f));F(0xf8)+=0.5;break;
  case 5:
   if(emit_repeated(0,0,4))RETIRE();if(I(0x144)==0)replace_secondary(990,20,10,1,2);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*D(0.1f)+D(0.8f));advance_six(5);if(I(0x180)!=0)RETIRE();H[1]*=D(0.98f);MOVE();F(0x370)+=D(0.1f);F(0xf8)+=F(0x370);break;
  }
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();STEP();break;
 case 810:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)<4){if(emit_repeated(0,0,3))RETIRE();if(I(0x180)!=0 || I(0x144)>179){--I(0x330);int count=3;do{PACKET(p432,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(810,1,p432);}while(--count!=0);return;}H[1]+=D(0.2f);MOVE();F(0x12c)=H[0];}
  if(S(0x13e)>3 && S(0x13e)<8){F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);}
  if(S(0x13e)>7 && S(0x13e)<12){F(0xf4)=F(0xf8)=0;if(T==0)RETIRE();F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*0.5+1.0);}
  if(S(0x13e)==12){if(emit_repeated(0,0,4))RETIRE();if(I(0x144)%3==0){PACKET(p216,0,0,13);unsigned char facing=B(0x104);spawn_unparented(810,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p216),3);}
   if(F(0xec)>=g_update_right || F(0xec)<=g_update_left || F(0xf0)>=g_update_top){--I(0x330);P->dispatch_character_wave_handle(11);F(0x374)=-atan2_degrees((AT(A,float,0xf0)+100.0)-F(0xf0),C(0x104)*(AT(A,float,0xec)-F(0xec)));float pattern=RND(4);int offset=0;do{PACKET(p408,(static_cast<float>(offset)+F(0x374))-15.0,0,pattern);SPAWN(810,1,p408);offset+=15;}while(offset<45);return;}MOVE();
  }
  if(S(0x13e)==13){FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)-=D(0.1f);}
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();
 yuyuko810_move_frame:
  STEP();if(advance_frame())--I(0x330);return;
 case 811:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 1:case 2:case 3:
   if(emit_repeated(0,1,4))RETIRE();
   if(S(0x364)==0){if(F(0xf0)<=stage_surface_height()){S(0x364)=1;H[1]=0;}
    if(I(0x144)%5==0){PACKET(p24,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(811,1,p24);}if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0)){S(0x364)=1;H[1]=0;}MOVE();break;
   }
   if(S(0x366)==0){S(0x366)=1;++AT(T,short,0x366);int count=8;do{PACKET(p384,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(811,1,p384);}while(--count!=0);}
   F(0xf4)=F(0xf8)=0;SCALE(F(0x11c)*D(0.95f));if(!(F(0x11c)>0.3f))FADE(12,12);break;
  case 4:case 5:case 6:case 7:F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>=15)FADE(10,10);break;
  case 8:case 9:case 10:case 11:
   publish_bounds(static_cast<int>(F(0x11c)*-32.0),10,0,-10,static_cast<short>(static_cast<int>(F(0x12c))),0,0);
   if(T==0)RETIRE();advance_six(20);F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);
   F(0x11c)=sqrt_float_value(square_float_value(F(0xf0)-F(0x374))+square_float_value(F(0xec)-F(0x370)))*0.03125;F(0x12c)=-atan2_degrees(F(0xf0)-F(0x374),C(0x104)*(F(0xec)-F(0x370)));F(0x120)=1;
   if(C(0x184)<1)AT(T,short,0x364)=1;if(AT(T,short,0x364)==1){B(0x184)=0;FADE(10,10);}break;
  case 12:
   if(AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150){int count=4;do{emit_fighter_effect_433cc0(201,F(0xec),F(0xf0),B(0x104),1);}while(--count!=0);RETIRE();}
   if(I(0x144)%3==0){PACKET(p192,0,0,13);unsigned char facing=B(0x104);spawn_unparented(811,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p192),3);}
   if(F(0xec)>=g_update_right || F(0xec)<=g_update_left || F(0xf0)>=g_update_top){--I(0x330);P->dispatch_character_wave_handle(15);PACKET(p360,H[0],0,14);SPAWN(811,1,p360);return;}MOVE();break;
  case 13:FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)-=D(0.1f);break;
  case 14:
   if(S(0x364)==0 && ((AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150) || S(0x36c)<=S(0x366)))S(0x364)=1;
   if(S(0x364)>0){++S(0x364);SCALE(F(0x11c)*D(0.98f));if(S(0x364)>=15)FADE(10,10);}break;
  }
 yuyuko811_move_frame:
  STEP();if(advance_frame())--I(0x330);return;
 case 812:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,1,0))RETIRE();H[1]*=D(0.97f);MOVE();F(0xf8)*=0.25;
   if(I(0x144)>89){PACKET(p540,0,0,5);if(AT(P,signed char,0x60c)<4){p540[2]=4;if(AT(P,signed char,0x60c)<3)p540[2]=1;}SPAWN(812,1,p540);int count=2;do{PACKET(p540,RND(360),RND(50)*D(0.1f)+5.0,2);SPAWN(812,1,p540);}while(--count!=0);count=2;do{PACKET(p540,RND(360),RND(150)*D(0.1f)+5.0,3);SPAWN(812,1,p540);}while(--count!=0);RETIRE();}break;
  case 1:advance_six(0);if(I(0x144)>1)B(0x184)=0;SCALE(F(0x11c)*D(0.8f));if(I(0x144)>=10)FADE(6,6);break;
  case 2:F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);break;
  case 3:H[1]*=D(0.9f);MOVE();SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);break;
  case 4:advance_six(0);if(I(0x144)>=4){B(0x184)=0;SCALE(F(0x11c)*D(0.8f));}if(I(0x144)>=30)FADE(6,6);break;
  case 5:advance_six(0);if(I(0x144)>=10){B(0x184)=0;SCALE(F(0x11c)*D(0.8f));}if(I(0x144)>=30)FADE(6,6);break;
  }
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();STEP();break;
 case 815:
  B(0x17c)=1;
  if(S(0x13e)==0){short action=AT(P,short,0x13c);if(action>49 && action<150)RETIRE();
   if((action==520 || action==521 || action==522 || action==523) && AT(P,short,0x140)>0 && AT(P,short,0x140)<17 && S(0x364)==0){F(0xec)=C(0x104)*95+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+145.0;}
   else{S(0x364)=1;if(S(0x366)<10){SCALE(F(0x11c)*D(0.9f));++S(0x366);}else{SCALE(F(0x11c)+D(0.01f));if(B(0x113)<16)RETIRE();B(0x113)-=15;B(0x110)-=15;B(0x111)-=15;}}
  }
  if(S(0x13e)==1){if(S(0x140)<2){short action=AT(P,short,0x13c);
    if(action>49 && action<150){float n=0;do{unsigned char facing=B(0x104);emit_fighter_effect_433cc0(201,C(0x104)*n*130.0*lookup_orientation_cosine_quantized_abs(F(0x12c))+F(0xec),lookup_orientation_sine_quantized_abs(F(0x12c))*130.0+F(0xf0),facing,1);n+=1.0;}while(n<12.0f);RETIRE();}
    if(action!=520 && action!=521 && action!=522 && action!=523){I(0x144)=0;set_sequence_frame(2);return;}
    F(0xec)=C(0x104)*95+AT(P,float,0xec);F(0xf0)=145.0+AT(P,float,0xf0);if(AT(P,short,0x140)>14 || AT(P,short,0x140)==0){I(0x144)=0;set_sequence_frame(2);return;}
    F(0x370)+=3.0;if(F(0x370)>90.0f)F(0x370)=90;F(0x12c)=lookup_orientation_sine_quantized_abs(F(0x370))*H[0];
    if(S(0x140)>0){F(0x374)+=9.0;if(F(0x374)>90.0f)F(0x374)=90;float wave=lookup_orientation_sine_quantized_abs(F(0x374));F(0x120)=wave+wave;if(I(0x180)==6){++B(0x184);I(0x180)=0;}if(I(0x180)!=0 && ++S(0x364)>9){S(0x364)=0;I(0x180)=0;}}
   }else{F(0x120)*=D(0.85f);if(I(0x144)>19)RETIRE();}
  }break;
 case 816:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 1:case 2:case 3:
   if(emit_repeated(0,0,2))RETIRE();if(I(0x180)!=0 || I(0x144)>179){--I(0x330);int count=3;do{PACKET(p96,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(816,1,p96);}while(--count!=0);return;}
   H[1]-=D(0.02f);if(H[1]<2.0f)H[1]=2;MOVE();F(0x12c)=H[0];break;
  case 4:case 5:case 6:case 7:F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>=15)FADE(10,10);break;
  case 8:case 9:case 10:case 11:
   F(0xf4)=F(0xf8)=0;if(T==0)RETIRE();F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*0.5+1.0);B(0x113)=AT(T,unsigned char,0x113);break;
  case 12:
   if(emit_repeated(0,3,4))RETIRE();if(S(0x364)==0){if(!(F(0x11c)>=6.0f))F(0x11c)+=0.25;else F(0x11c)+=D(0.02f);}else F(0x11c)*=D(0.92f);F(0x120)=F(0x11c);
   advance_six(0);if(advance_phase(1)){S(0x364)=1;B(0x184)=0;}
   if(C(0x184)<0){SCALE(F(0x11c)*D(0.95f));FADE(10,10);}
   else{
    if(I(0x144)%2==0){PACKET(p552,0,F(0x11c),15);SPAWN(816,1,p552);}
    if(AT(P,signed char,0x609)<3){if(I(0x144)%3==0){PACKET(p552,lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*27.0)*45.0+180.0,4,16);spawn_unparented(816,C(0x104)*(F(0x11c)*100.0)+F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p552),3);PACKET(p552,lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*27.0+180.0)*45.0+180.0,4,16);spawn_unparented(816,C(0x104)*(F(0x11c)*100.0)+F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p552),3);}}
    else if(AT(P,signed char,0x609)<4){if(I(0x144)%2==0){PACKET(p552,lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*27.0)*45.0+180.0,7,16);spawn_unparented(816,C(0x104)*(F(0x11c)*100.0)+F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p552),3);PACKET(p552,lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*27.0+180.0)*45.0+180.0,7,16);spawn_unparented(816,C(0x104)*(F(0x11c)*100.0)+F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p552),3);}}
    else{PACKET(p552,lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*27.0)*45.0+180.0,10,16);spawn_unparented(816,C(0x104)*(F(0x11c)*100.0)+F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p552),3);PACKET(p552,lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*27.0+180.0)*45.0+180.0,10,16);spawn_unparented(816,C(0x104)*(F(0x11c)*100.0)+F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p552),3);}
   }
   publish_bounds(0,static_cast<int>(F(0x120)*5.0),static_cast<int>(F(0x11c)*100.0),static_cast<int>(F(0x120)*-5.0),static_cast<short>(static_cast<int>(F(0x12c))),0,0);break;
  case 13:SCALE(F(0x11c)*D(0.9f));if(F(0x11c)<=D(0.2f))FADE(10,10);break;
  case 14:SCALE(F(0x11c)+H[1]);H[1]*=D(0.85f);if(H[1]<=D(0.05f))H[1]=0.05f;if(I(0x144)>=10)FADE(10,10);break;
  case 15:F(0x11c)+=D(0.15f);F(0x120)*=D(0.9f);FADE(20,20);break;
  case 16:
   if(S(0x364)==0){if(emit_repeated(0,0,2))RETIRE();if(B(0x113)<236)B(0x113)+=20;else{B(0x113)=255;S(0x364)=1;B(0x184)=1;}}
   if(S(0x364)>0){++S(0x364);H[1]*=D(0.9f);if(C(0x184)<1 || S(0x364)>9){B(0x184)=0;FADE(10,10);}else if(emit_repeated(0,0,2))RETIRE();}
   if(H[1]<1.0)H[1]=1;MOVE();break;
  }
  if(OUTSIDE(1880.0,-600.0f,1060.0f,-100.0))RETIRE();STEP();break;
 case 820:
  B(0x17c)=2;
  if(S(0x13e)==0){if(emit_repeated(0,0,4))RETIRE();++S(0x36c);float *heading=H;heading[1]=150.0+lookup_orientation_cosine(I(0x144)*9)*150.0;F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(static_cast<float>(S(0x36c)*4)+heading[0])*H[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)*4)+H[0])*H[1]+F(0x374);if(I(0x144)>9)goto yuyuko820_next;}
  if(S(0x13e)==1){if(AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150){int count=4;do{emit_fighter_effect_433cc0(201,F(0xec),F(0xf0),B(0x104),1);}while(--count!=0);RETIRE();}
   F(0x378)*=D(0.94f);F(0x370)+=C(0x104)*(F(0x378)*7.5);F(0x374)+=F(0x378)*15.0;++S(0x36c);float *heading=H;F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(static_cast<float>(S(0x36c)*4)+heading[0])*heading[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)*4)+heading[0])*H[1]+F(0x374);
   if(I(0x144)%3==0){PACKET(p336,0,0,3);unsigned char facing=B(0x104);spawn_unparented(820,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p336),3);}advance_six(0);if(I(0x180)!=0 && ++S(0x364)>19){S(0x364)=0;I(0x180)=0;}
   if(AT(P,signed char,0x606)<4){if(I(0x144)>59){next_sequence_block();return;}}else if(I(0x144)>89)goto yuyuko820_next;
  }
  if(S(0x13e)==2){FADE(13,13);SCALE(F(0x11c)*D(0.94f));}
  if(S(0x13e)==3){FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)+=D(0.1f);}
  if(S(0x13e)==4){if(emit_repeated(0,0,4))RETIRE();++S(0x36c);float *heading=H;heading[1]=150.0+lookup_orientation_cosine(I(0x144)*9)*150.0;F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(static_cast<float>(S(0x36c)*4)+heading[0])*H[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)*4)+H[0])*H[1]+F(0x374);if(I(0x144)>9)goto yuyuko820_next;}
  if(S(0x13e)==5){if(AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150){int count=4;do{emit_fighter_effect_433cc0(201,F(0xec),F(0xf0),B(0x104),1);}while(--count!=0);RETIRE();}
   ++S(0x36c);float *heading=H;F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(static_cast<float>(S(0x36c)*4)+heading[0])*heading[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)*4)+heading[0])*H[1]+F(0x374);
   if(I(0x144)%3==0){PACKET(p168,0,0,3);unsigned char facing=B(0x104);spawn_unparented(820,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p168),3);}advance_six(0);if(I(0x180)!=0 && ++S(0x364)>19){S(0x364)=0;I(0x180)=0;}
   if(AT(P,short,0x13c)!=540 || AT(P,short,0x13e)==0 || AT(P,short,0x13e)==3 || (AT(P,signed char,0x606)<4?I(0x144)>=60:I(0x144)>=90)){select_sequence(2);return;}
  }STEP();break;
 yuyuko820_next:
  next_sequence_block();return;
 case 821:
  if(S(0x13e)==0){if((AT(P,short,0x13c)==545 || AT(P,short,0x13c)==546 || AT(P,short,0x13c)==547 || AT(P,short,0x13c)==548) && AT(P,short,0x13e)<3){
    if(I(0x144)%4==0){PACKET(p312,RND(360),RND(125)+50.0,3);spawn_parented(821,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p312),3);}
    if(I(0x144)%6==0 && F(0x370)<5.0f){PACKET(p48,(H[0]+144.0)-F(0x370)*72.0,6,1);spawn_parented(821,AT(P,signed char,0x104)*55+AT(P,float,0xec),AT(P,float,0xf0)+180.0,B(0x104),1,reinterpret_cast<const unsigned *>(p48),3);F(0x370)+=1.0;}
    if(AT(P,signed char,0x104)*AT(P,int,0x6b4)>0){F(0xf4)+=0.25;if(F(0xf4)>10.0f)F(0xf4)=10;}if(AT(P,signed char,0x104)*AT(P,int,0x6b4)<0){F(0xf4)-=0.25;if(F(0xf4)<-10.0f)F(0xf4)=-10;}
    if(AT(P,int,0x6b8)>0){F(0xf8)-=0.25;if(F(0xf8)<-10.0f)F(0xf8)=-10;}if(AT(P,int,0x6b8)<0){F(0xf8)+=0.25;if(F(0xf8)>10.0f)F(0xf8)=10;}
    if(AT(P,int,0x6b4)==0){if(F(0xf4)>0.0){F(0xf4)-=0.25;if(F(0xf4)<0.0)F(0xf4)=0;}if(F(0xf4)<0.0){F(0xf4)+=0.25;if(F(0xf4)>0.0)F(0xf4)=0;}}
    if(AT(P,int,0x6b8)==0){if(F(0xf8)>0.0){F(0xf8)-=0.25;if(F(0xf8)<0.0)F(0xf8)=0;}if(F(0xf8)<0.0){F(0xf8)+=0.25;if(F(0xf8)>0.0)F(0xf8)=0;}}
   }else S(0x364)=1;
   if(S(0x364)==0)SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*3.0)*D(0.2f)+D(0.8f));else{SCALE(F(0x11c)*D(0.9f));FADE(25,25);}
  }else if(S(0x13e)==1){if(emit_repeated(0,0,4))RETIRE();if(I(0x144)==0)replace_secondary(990,15,60,1,2);advance_six(20);
   if(C(0x184)<1){F(0xf4)*=D(0.95f);F(0xf8)*=D(0.95f);SCALE(F(0x11c)*D(0.95f));if(F(0x11c)<D(0.1f))RETIRE();F(0xf4)*=D(0.98f);F(0xf8)*=D(0.98f);F(0x370)-=25.0;if(F(0x370)<0.0)F(0x370)=0;set_secondary_alpha(static_cast<unsigned char>(F(0x370)));}
   else if(T==0){if(++S(0x364)>9)B(0x184)=0;F(0xf4)*=D(0.98f);F(0xf8)*=D(0.98f);}
   else{if(C(0x104)*(F(0xec)-AT(T,float,0xec))<0.0){F(0xf4)+=D(0.2f);if(F(0xf4)>6.0f)F(0xf4)=6;}if(C(0x104)*(F(0xec)-AT(T,float,0xec))>0.0){F(0xf4)-=D(0.2f);if(F(0xf4)<-6.0f)F(0xf4)=-6;}
    if(F(0xf0)-AT(T,float,0xf0)>0.0){F(0xf8)-=D(0.2f);if(F(0xf8)<-6.0f)F(0xf8)=-6;}if(!(F(0xf0)-AT(T,float,0xf0)>=0.0)){F(0xf8)+=D(0.2f);if(!(F(0xf8)<=6.0f))F(0xf8)=6;}
   }
  }else if(S(0x13e)==3){if(T==0)FADE(35,35);else{float *heading=H;float cosine=lookup_orientation_cosine_quantized_abs(heading[0]);float *motion=H;F(0xec)=cosine*heading[1]+AT(T,float,0xec);F(0xf0)=lookup_orientation_sine_quantized_abs(heading[0])*motion[1]+AT(T,float,0xf0);motion[1]*=D(0.95f);FADE(5,5);}}
  STEP();break;
 case 825:
  B(0x17c)=3;if(S(0x13e)==1){F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);}
  STEP();if(advance_frame())--I(0x330);if(ENTRY(1))--I(0x330);return;
 case 826:
  if(I(0x180)==5)RETIRE();if(S(0x13e)==0){SCALE(F(0x11c)*D(0.6f));if(I(0x144)>9)--I(0x330);}
  else if(static_cast<unsigned>(static_cast<int>(S(0x13e))-1)<4){F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);}
  if(F(0xec)<=1380.0f && F(0xec)>=-100.0 && F(0xf0)<=1060.0f && F(0xf0)>=-100.0)goto yuyuko810_move_frame;RETIRE();
 case 848:
  switch(S(0x13e)) {
  case 1:position_relative(0,0);if(AT(P,short,0x13c)!=300)RETIRE();break;
  case 2:position_relative(0,0);if(AT(P,short,0x13c)!=303)RETIRE();break;
  case 3:position_relative(30,120);if(AT(P,short,0x13c)!=301 && AT(P,short,0x13c)!=320)RETIRE();break;
  case 4:position_relative(20,100);if(AT(P,short,0x13c)!=302 && AT(P,short,0x13c)!=408 && AT(P,short,0x13c)!=696)RETIRE();break;
  case 5:position_relative(0,0);if(AT(P,short,0x13c)!=304)RETIRE();break;
  case 6:position_relative(0,0);if(AT(P,short,0x13c)!=306)RETIRE();break;
  case 7:position_relative(0,0);if(AT(P,short,0x13c)!=307 && AT(P,short,0x13c)!=418)RETIRE();break;
  case 8:position_relative(0,0);if(AT(P,short,0x13c)!=308)RETIRE();break;
  case 10:
   if(S(0x364)==0){if(I(0x144)%2==0){PACKET(p480,0,0,11);unsigned char facing=B(0x104);spawn_unparented(848,(RND(60)+F(0xec))-30.0,(RND(60)+F(0xf0))-30.0,facing,1,reinterpret_cast<const unsigned *>(p480),3);}
    B(0x104)=AT(P,unsigned char,0x104);F(0xf4)-=2.0;F(0xf8)+=D(0.2f);if(F(0xf4)<0.0)F(0xf4)=0;if(F(0xf8)>0.0)F(0xf8)=0;
    F(0x370)+=C(0x104)*F(0xf4);F(0x374)+=F(0xf8);F(0xec)=AT(P,float,0xec)+F(0x370);F(0xf0)=AT(P,float,0xf0)+F(0x374);if(AT(P,short,0x13c)!=305)S(0x364)=1;
   }else{SCALE(F(0x11c)*D(0.9f));if(++S(0x364)>15)RETIRE();}goto yuyuko848_frame;
  case 11:F(0xf8)+=D(0.35f);SCALE(F(0x11c)*D(0.98f));FADE(12,12);F(0xf0)+=F(0xf8);goto yuyuko848_frame;
  case 12:position_relative(30,120);if(AT(P,short,0x13c)!=321)RETIRE();break;
  default:goto yuyuko848_frame;
  }
  if(AT(P,short,0x140)==0)RETIRE();
 yuyuko848_frame:
  if(AT(P,short,0x186)!=0)return;if(advance_frame() || ENTRY(12))RETIRE();if(S(0x13e)<=9 && S(0x140)==0 && S(0x142)==0)--I(0x330);return;
 case 850:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 1:case 2:case 3:
   if(I(0x144)>89){--I(0x330);int count=3;do{PACKET(p144,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(850,1,p144);}while(--count!=0);return;}
   H[0]+=F(0x370);F(0x370)*=D(0.99f);H[1]*=D(0.99f);MOVE();F(0x12c)=H[0];break;
  case 4:case 5:case 6:case 7:F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);break;
  case 8:case 9:case 10:case 11:F(0xf4)=F(0xf8)=0;if(T==0)RETIRE();F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*0.5+1.0);break;
  }STEP();break;
 case 851:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==1){if(F(0xec)>1480.0f || F(0xec)<-200.0)RETIRE();if(C(0x184)>0){F(0xf4)+=D(0.05f);F(0xf8)=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3))*D(F(0x374))+lookup_orientation_sine_quantized_abs(-H[0])*5.0;}
   advance_six(10);if(C(0x184)<1){PACKET(p72,360,RND(7)+7.0,2);SPAWN(851,1,p72);RETIRE();}
  }else if(S(0x13e)==2){FADE(13,13);MOVE();F(0xf8)+=F(0x370);F(0x370)+=D(0.2f);}
  else if(S(0x13e)==4){if(S(0x364)==0){SCALE(1.0-F(0x370));F(0x370)*=D(0.85f);if(F(0x370)<=0.005f){F(0x370)=0;S(0x364)=1;}}
   if(S(0x364)==2)SCALE(F(0x11c)*D(0.8f));if(S(0x364)<2){if((AT(P,short,0x13c)==601 || AT(P,short,0x13c)==651) && AT(P,short,0x13e)==1)position_relative(105,146);else S(0x364)=2;
    if(I(0x144)%5==0){PACKET(p264,30.0-RND(60),RND(40)*D(0.1f)+2.0,1);SPAWN(851,1,p264);}}
  }STEP();break;
 case 852:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(F(0xec)>1480.0f || F(0xec)<-200.0)RETIRE();if(I(0x144)%2==0){PACKET(p240,RND(360),RND(10),1);SPAWN(852,1,p240);}advance_six(0);
   if(I(0x180)==1 || I(0x180)==7){F(0xec)=AT(A,float,0xec);F(0xf0)=AT(A,float,0xf0)+100.0;B(0x113)=0;B(0x33c)=255;select_sequence(4);P->dispatch_character_wave_handle(53);return;}
   if(C(0x184)<1){PACKET(p468,360,RND(7)+7.0,2);SPAWN(852,1,p468);RETIRE();}MOVE();break;
  case 1:FADE(13,13);MOVE();F(0x370)+=D(0.2f);F(0xf8)+=F(0x374);break;
  case 2:FADE(13,13);MOVE();F(0xf8)+=F(0x370);F(0x370)+=D(0.2f);break;
  case 3:
   F(0x370)+=F(0x374);if(T==0)FADE(5,5);else{float cosine=lookup_orientation_cosine_quantized_abs(-F(0x370));float *heading=H;F(0xec)=C(0x104)*cosine*heading[0]+AT(A,float,0xec);F(0xf0)=(lookup_orientation_sine_quantized_abs(-F(0x370))*heading[0]*D(0.2f)+AT(A,float,0xf0))+heading[1];
    if(!(F(0x370)>=0.0)){int angle=static_cast<int>(F(0x370));C(0x33c)=angle%360<-180?1:-1;}else{int angle=static_cast<int>(F(0x370));if(angle%360>=180)B(0x33c)=255;else if(angle%360>=0)B(0x33c)=1;}
    if(I(0x144)>=S(0x364) || AT(T,short,0x364)==1)FADE(5,5);else if(B(0x113)>245)B(0x113)=255;else B(0x113)+=10;
   }break;
  case 4:
   F(0xec)=AT(A,float,0xec);F(0xf0)=AT(A,float,0xf0)+100.0;F(0x11c)=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6))*0.25+1.0;F(0x120)=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6+45))*0.25+1.0;
   if(S(0x364)==0){if(AT(A,short,0x174)<1)S(0x364)=1;if(AT(A,short,0x174)>=7)AT(A,short,0x174)-=6;else if(AT(A,short,0x174)>0)AT(A,short,0x174)=1;
    if(B(0x113)<236)B(0x113)+=20;else B(0x113)=255;
    if(AT(A,short,0x174)<2 || emit_repeated(0,0,0) || I(0x144)>299 || (AT(P,short,0x13c)>599 && AT(P,short,0x13c)<690 && AT(P,short,0x13e)==0 && AT(P,short,0x140)==0))S(0x364)=1;
    if(I(0x144)%15==0){PACKET(p444,RND(175)+100.0,RND(150)+50.0,3);spawn_parented(852,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p444),3);}
   }
   if(S(0x364)==1){F(0x11c)*=D(0.98f);F(0x11c)=F(0x120);FADE(5,5);}break;
  }STEP();if(advance_frame())--I(0x330);return;
 case 853:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 1:case 2:case 3:
   if(I(0x144)<90){H[0]+=F(0x370);F(0x370)*=D(0.99f);H[1]*=D(0.99f);}else{H[1]+=D(0.3f);if(C(0x184)<1){--I(0x330);int count=3;do{PACKET(p420,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(853,1,p420);}while(--count!=0);return;}if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();}
   MOVE();F(0x12c)=H[0];break;
  case 4:case 5:case 6:case 7:F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);break;
  case 8:case 9:case 10:case 11:F(0xf4)=F(0xf8)=0;if(T==0)RETIRE();F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*0.5+1.0);break;
  }STEP();break;
 case 854:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 1:if(F(0xf0)>1000.0)RETIRE();if(C(0x184)>0){F(0xf8)+=D(0.05f);F(0xf4)=C(0x104)*(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*3))*D(F(0x374))+lookup_orientation_cosine_quantized_abs(-H[0])*5.0);}advance_six(10);break;
  case 2:FADE(13,13);MOVE();F(0xf8)+=F(0x370);F(0x370)+=D(0.2f);break;
  case 3:MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xf8)*=D(0.2f);F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 4:
   if(S(0x364)==0){SCALE(1.0-F(0x370));F(0x370)*=D(0.85f);if(F(0x370)<=0.005f){F(0x370)=0;S(0x364)=1;}}
   if(S(0x364)==2)SCALE(F(0x11c)*D(0.8f));if(S(0x364)<2){if(++S(0x366)>209 || emit_repeated(0,0,0)){S(0x364)=2;return;}if(AT(P,short,0x174)<1 || AT(A,short,0x174)<1)S(0x364)=2;
    if(I(0x144)%4==0 && I(0x144)>19){PACKET(p516,-60.0-RND(60),RND(120)*D(0.1f)+10.0,1);unsigned char facing=B(0x104);spawn_unparented(854,(F(0xec)+100.0)-RND(200),F(0xf0),facing,1,reinterpret_cast<const unsigned *>(p516),3);
     PACKET(p516,static_cast<float>(static_cast<unsigned>(selector_random_roll(6)+I(0x144)*5)),25,3);SPAWN(854,(p516[0]<0.0 || !(p516[0]<=180.0f))?-1:1,p516);}
   }
   if(AT(A,float,0xec)<F(0xec))F(0xf4)-=C(0x104)*D(0.1f);if(F(0xec)<AT(A,float,0xec))F(0xf4)+=C(0x104)*D(0.1f);if(F(0xf4)>2.0f)F(0xf4)=2;if(F(0xf4)<-2.0f)F(0xf4)=-2;break;
  }STEP();break;
 case 855:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(F(0xec)>1480.0f || F(0xec)<-200.0)RETIRE();if(I(0x144)%2==0){PACKET(p396,RND(360),RND(10),1);SPAWN(855,1,p396);}advance_six(0);
   if(I(0x180)==1 || I(0x180)==7){F(0xec)=AT(A,float,0xec);F(0xf0)=AT(A,float,0xf0)+100.0;B(0x113)=0;B(0x33c)=255;select_sequence(4);P->dispatch_character_wave_handle(53);float n=0;do{PACKET(p348,n*45.0,n*40.0+40.0,3);spawn_parented(855,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p348),3);n+=1.0;}while(n<8.0f);return;}
   if(C(0x184)<1){PACKET(p372,360,RND(7)+7.0,2);SPAWN(855,1,p372);RETIRE();}MOVE();break;
  case 1:FADE(13,13);MOVE();F(0x370)+=D(0.2f);F(0xf8)+=F(0x374);break;
  case 2:FADE(13,13);MOVE();F(0xf8)+=F(0x370);F(0x370)+=D(0.2f);break;
  case 3:
   H[0]+=2.0;if(T==0)FADE(5,5);else{F(0x378)*=D(0.95f);F(0x374)=200.0-F(0x378);F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(-H[0])*F(0x374)+AT(A,float,0xec);F(0xf0)=(lookup_orientation_sine_quantized_abs(-H[0])*F(0x374)*D(0.2f)+AT(A,float,0xf0))+100.0;
    if(!(H[0]>=0.0)){int angle=static_cast<int>(H[0]);C(0x33c)=angle%360<-180?1:-1;}else{int angle=static_cast<int>(H[0]);if(angle%360>=180)B(0x33c)=255;else if(angle%360>=0)B(0x33c)=1;}
    if(H[1]<=static_cast<float>(I(0x144)) || AT(T,short,0x364)==1){int count=6;do{PACKET(p504,RND(360),RND(50)*D(0.1f)+5.0,5);SPAWN(855,1,p504);}while(--count!=0);count=8;do{PACKET(p504,RND(360),RND(125)*D(0.1f)+5.0,6);SPAWN(855,1,p504);}while(--count!=0);RETIRE();}
    if(B(0x113)>245)B(0x113)=255;else B(0x113)+=10;
   }break;
  case 4:
   F(0xec)=AT(A,float,0xec);F(0xf0)=AT(A,float,0xf0)+100.0;F(0x11c)=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6))*0.25+1.0;F(0x120)=lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*6+45))*0.25+1.0;
   if(S(0x364)==0){if(B(0x113)<236)B(0x113)+=20;else B(0x113)=255;
    if(I(0x144)>359){P->dispatch_character_wave_handle(54);PACKET(p528,0,0,7);SPAWN(855,1,p528);p528[2]=8;SPAWN(855,1,p528);int count=16;do{PACKET(p528,RND(360),RND(25)+7.0,9);SPAWN(855,1,p528);}while(--count!=0);RETIRE();}
    if(AT(A,short,0x174)<1 || emit_repeated(0,0,0))S(0x364)=1;
   }if(S(0x364)==1){F(0x11c)*=D(0.98f);F(0x11c)=F(0x120);FADE(5,5);}break;
  case 5:F(0x12c)+=F(0x370);F(0x370)*=D(0.95f);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);if(I(0x144)>14)FADE(10,10);break;
  case 6:H[1]*=D(0.95f);MOVE();if(I(0x144)>14){SCALE(F(0x11c)*D(0.98f));FADE(10,10);}break;
  case 7:if(I(0x144)>1)B(0x184)=0;SCALE(F(0x11c)-D(0.005f));if(I(0x144)>19)FADE(2,2);break;
  case 8:SCALE(F(0x11c)+D(0.2f));FADE(15,15);break;
  case 9:F(0x12c)+=F(0x370);F(0x370)*=D(0.95f);H[1]*=D(0.8f);F(0xf8)+=F(0x374);if(I(0x144)>59){F(0x374)-=D(0.01f);FADE(2,2);}break;
  }goto yuyuko811_move_frame;
 case 856:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)<4){if(AT(P,short,0x174)<1){--I(0x330);int count=3;do{PACKET(p324,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(856,1,p324);}while(--count!=0);return;}
   if(I(0x180)!=0 || I(0x144)>179){--I(0x330);int count=3;do{PACKET(p300,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(856,1,p300);}while(--count!=0);return;}
   H[1]+=D(0.2f);MOVE();F(0x12c)=H[0];
  }
  if(S(0x13e)>3 && S(0x13e)<8){F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);}
  if(S(0x13e)>7 && S(0x13e)<12){F(0xf4)=F(0xf8)=0;if(T==0)RETIRE();F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*0.5+1.0);}
  if(S(0x13e)==12){if(AT(P,short,0x174)<1)RETIRE();if(I(0x144)%3==0){PACKET(p276,0,0,13);unsigned char facing=B(0x104);spawn_unparented(856,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p276),3);}
   if(F(0xec)>=g_update_right || F(0xec)<=g_update_left || F(0xf0)>=g_update_top){--I(0x330);P->dispatch_character_wave_handle(11);F(0x374)=-atan2_degrees((AT(A,float,0xf0)+100.0)-F(0xf0),C(0x104)*(AT(A,float,0xec)-F(0xec)));float pattern=RND(4);int n=0;do{PACKET(p252,(static_cast<float>(n)+F(0x374))-15.0,0,pattern);SPAWN(856,1,p252);n+=15;}while(n<45);return;}MOVE();
  }
  if(S(0x13e)==13){FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)-=D(0.1f);}
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();goto yuyuko810_move_frame;
 case 857:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 1:case 2:case 3:
   if(AT(P,short,0x174)<1)RETIRE();if(I(0x180)!=0 || I(0x144)>179){--I(0x330);int count=3;do{PACKET(p228,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(857,1,p228);}while(--count!=0);return;}
   H[1]-=D(0.02f);if(H[1]<2.0f)H[1]=2;MOVE();F(0x12c)=H[0];break;
  case 4:case 5:case 6:case 7:F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);break;
  case 8:case 9:case 10:case 11:F(0xf4)=F(0xf8)=0;if(T==0)RETIRE();F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*0.5+1.0);break;
  case 12:
   if(S(0x364)==0){if(AT(P,short,0x174)<1){B(0x184)=0;S(0x364)=1;}F(0x11c)+=0.5;if(F(0x11c)>=10.0f)F(0x11c)=10;F(0x120)=F(0x11c);advance_six(0);advance_phase(3);publish_bounds(0,static_cast<int>(F(0x120)*5.0),static_cast<int>(F(0x11c)*100.0),static_cast<int>(F(0x120)*-5.0),static_cast<short>(static_cast<int>(F(0x12c))),0,0);}
   if(S(0x364)==1){F(0x11c)*=D(0.98f);F(0x120)*=D(0.85f);FADE(10,10);}break;
  case 13:SCALE(F(0x11c)*D(0.98f));if(F(0x11c)<=0.55f)FADE(10,10);break;
  case 14:
   if((AT(P,short,0x13c)==607 || AT(P,short,0x13c)==657) && AT(P,short,0x13e)<2){if(S(0x364)==0){F(0x120)+=D(0.1f);if(F(0x120)>1.0){F(0x120)=1;if(I(0x144)>19)S(0x364)=1;}}if(S(0x364)==1){F(0x11c)=(1.0-F(0x370))*D(0.9f)+D(0.1f);F(0x370)*=D(0.9f);}position_relative(-20,0);}else S(0x364)=2;
   if(S(0x364)==2){F(0x11c)*=D(0.9f);FADE(10,10);}break;
  case 15:SCALE(F(0x11c)+H[1]);H[1]*=D(0.85f);if(H[1]<=D(0.05f))H[1]=0.05f;if(I(0x144)>9)FADE(10,10);break;
  }
  if(OUTSIDE(1880.0,-600.0f,1060.0f,-100.0))RETIRE();STEP();break;
 case 858:
  if(S(0x13e)==1){if(S(0x364)==0){if(B(0x113)<251)B(0x113)+=5;else{B(0x113)=255;B(0x184)=1;S(0x364)=1;}}
   else{advance_six(0);if(I(0x144)%3==0){PACKET(p204,0,0,3);unsigned char facing=B(0x104);spawn_unparented(858,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p204),3);}if(I(0x180)!=0 && ++S(0x366)>9){S(0x366)=0;I(0x180)=0;B(0x184)=1;}}
   H[1]-=2.0;if(AT(P,short,0x174)<1 || AT(A,short,0x174)<1){next_sequence_block();return;}++S(0x36c);float *heading=H;F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(static_cast<float>(S(0x36c)*6)+heading[0])*heading[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x36c)*6)+heading[0])*H[1]+F(0x374);if(H[1]<=100.0){next_sequence_block();return;}
  }
  if(S(0x13e)==2){FADE(13,13);SCALE(F(0x11c)*D(0.94f));}if(S(0x13e)==3){FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)+=D(0.1f);}STEP();if(advance_frame())--I(0x330);return;
 case 900:
  {
   switch(S(0x13e)) {
   case 0:
    if(S(0x364)==0){if(B(0x113)<246)B(0x113)+=10;else{B(0x113)=255;S(0x364)=1;B(0x184)=1;}}advance_six(0);advance_phase(0);if(AT(P,short,0x174)<1){select_sequence(2);return;}
    H[0]-=2.0;H[1]-=3.0;if(H[1]<=150.0f){if(g_match_identifier==0){select_sequence(2);S(0x364)=0;return;}H[1]=150;B(0x184)=1;next_sequence_block();F(0x37c)=-atan2_degrees((AT(A,float,0xf0)+100.0)-F(0x374),C(0x104)*(AT(A,float,0xec)-F(0x370)));}
    {float *heading=H;F(0xec)=lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(-heading[0])*H[1]+F(0x374);}
    if(I(0x144)%6==0){PACKET(p180,0,0,3);unsigned char facing=B(0x104);spawn_unparented(900,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p180),3);}break;
   case 1:
    advance_six(0);advance_phase(0);if(I(0x180)!=0 && ++S(0x364)>9){B(0x184)=1;S(0x364)=0;I(0x180)=0;}if(AT(P,short,0x174)<1){select_sequence(2);return;}
    F(0x380)+=0.5;if(F(0x380)>=5.0f)F(0x380)=5;MOTION->set_components(F(0x37c),F(0x380));F(0x370)+=C(0x104)*F(0xf4);F(0x374)+=F(0xf8);
    {float *heading=H;heading[0]-=4.0;F(0xec)=lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(-heading[0])*H[1]+F(0x374);}
    if(I(0x144)>299){select_sequence(2);return;}if(I(0x144)%6==0){PACKET(p156,0,0,3);unsigned char facing=B(0x104);spawn_unparented(900,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p156),3);}break;
   case 2:F(0xf4)=F(0xf8)=0;FADE(13,13);SCALE(F(0x11c)*D(0.96f));break;
   case 3:FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)+=D(0.1f);break;
   case 4:
    if(S(0x364)==0){if(B(0x113)<246)B(0x113)+=10;else{B(0x113)=255;S(0x364)=1;}}if(S(0x364)==1 && (AT(P,short,0x13c)!=710 || AT(P,short,0x13e)>1))S(0x364)=2;
    if(S(0x364)==2){SCALE(F(0x11c)*D(0.95f));FADE(13,13);}else position_relative(50,170);break;
   case 5:FADE(15,15);SCALE(F(0x11c)+D(0.2f));break;
   }STEP();break;
  }
 case 901:
  if(I(0x180)==5)RETIRE();
  {float *packet;
   switch(S(0x13e)) {
   case 0:
    if(AT(P,short,0x174)<1 || S(0x174)<-699){PACKET(p108,0,0,5);packet=p108;goto yuyuko901_finish;}
    if(I(0x144)%7==0){PACKET(p132,0,0,3);unsigned char facing=B(0x104);spawn_unparented(901,(RND(50)-25.0)+F(0xec),(RND(50)-25.0)+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p132),3);}
    if(F(0xec)>=g_update_right || F(0xec)<=g_update_left || F(0xf0)>=g_update_top || F(0xf0)<=0.0){if(F(0xec)>=g_update_right || F(0xec)<=g_update_left)F(0xf4)=-F(0xf4);if(F(0xf0)>=g_update_top || F(0xf0)<=0.0)F(0xf8)=-F(0xf8);H[0]=-atan2_degrees(F(0xf8),F(0xf4));P->dispatch_character_wave_handle(11);
     int n=0;do{PACKET(p492,(static_cast<float>(n)+H[0])-15.0,RND(50)*D(0.1f),0);SPAWN(902,1,p492);n+=15;}while(n<45);p492[2]=5;SPAWN(901,1,p492);p492[2]=4;packet=p492;goto yuyuko901_finish;
    }MOVE();H[1]+=D(0.05f);break;
   case 2:F(0xf4)=F(0xf8)=0;FADE(13,13);SCALE(F(0x11c)*D(0.96f));break;
   case 3:FADE(13,13);SCALE(F(0x11c)*D(0.94f));F(0xf8)-=D(0.1f);break;
   case 4:FADE(10,10);SCALE(F(0x11c)*D(0.98f));break;
   case 5:FADE(20,20);SCALE(F(0x11c)+D(0.3f));break;
   }if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();goto yuyuko810_move_frame;
  yuyuko901_finish:
   spawn_unparented(901,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(packet),3);RETIRE();
  }
 case 902:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)<4){if(AT(P,short,0x174)<1){int count=3;do{PACKET(p84,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(902,1,p84);}while(--count!=0);RETIRE();}
   if(I(0x180)!=0){--I(0x330);int count=3;do{PACKET(p60,RND(360),RND(50)*D(0.1f)+5.0,static_cast<float>(S(0x13e)+4));SPAWN(902,1,p60);}while(--count!=0);return;}H[1]+=D(0.05f);MOVE();F(0x12c)=H[0];
  }
  if(S(0x13e)>3 && S(0x13e)<8){F(0x12c)+=F(0x370);F(0xf4)*=D(0.97f);F(0xf8)-=D(0.15f);SCALE(F(0x11c)-D(0.01f));if(I(0x144)>14)FADE(10,10);}
  if(S(0x13e)>7 && S(0x13e)<12){F(0xf4)=F(0xf8)=0;if(T==0)RETIRE();F(0xec)=C(0x104)*AT(T,float,0xf4)+AT(T,float,0xec);F(0xf0)=AT(T,float,0xf8)+AT(T,float,0xf0);SCALE(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144))*6.0)*0.5+1.0);}
  if(OUTSIDE(1380.0f,-100.0,1060.0f,-100.0))RETIRE();STEP();break;
 case 920:
  if(S(0x13e)==0){if(AT(P,short,0x174)<1){select_sequence(2);F(0xf4)=F(0xf8)=0;return;}
   float *heading=H;F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(-heading[0])*H[1]+F(0x374);H[1]-=3.0;if(H[1]<100.0)H[1]=100;H[0]+=4.0;
   if(B(0x113)>251){B(0x113)=255;B(0x184)=1;next_sequence_block();return;}B(0x113)+=4;
  }else if(S(0x13e)==1){if(AT(P,short,0x174)<1){select_sequence(2);F(0xf4)=F(0xf8)=0;return;}
   if(I(0x144)%10==0){PACKET(p36,RND(360),RND(50)*D(0.1f)+5.0,4);SPAWN(800,1,p36);}advance_six(0);advance_phase(0);
   float *heading=H;F(0xec)=C(0x104)*lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1]+F(0x370);F(0xf0)=lookup_orientation_sine_quantized_abs(-heading[0])*H[1]+F(0x374);H[1]-=3.0;if(H[1]<100.0)H[1]=100;H[0]+=4.0;if(I(0x144)>119){next_sequence_block();return;}
  }else if(S(0x13e)==2){SCALE(F(0x11c)*D(0.99f));FADE(10,10);}break;
 case 922:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x13c)!=731)RETIRE();F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0);
   if(S(0x364)==0){F(0x11c)=(1.0-F(0x374))*D(0.95f)+D(0.05f);F(0x120)=(1.0-F(0x370))*D(0.95f)+D(0.05f);if(F(0x370)>0.0)F(0x370)*=D(0.9f);if(I(0x144)>19)F(0x370)=0;if(I(0x144)>29 && F(0x374)>0.0)F(0x374)*=D(0.9f);}
   if(I(0x144)%120==60){F(0x374)=0;PACKET(p12,0,0,1);SPAWN(922,-1,p12);}break;
  case 1:
   if(AT(P,short,0x13c)!=731)RETIRE();F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0);SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.95f);FADE(6,6);break;
  case 2:if(AT(P,short,0x13c)!=731 || AT(P,short,0x13e)!=0)RETIRE();SCALE(F(0x11c)+D(0.01f));break;
  case 3:
   {float *heading=H;float cosine=lookup_orientation_cosine_quantized_abs(-heading[0]);float *motion=H;F(0xec)=C(0x104)*cosine*heading[1];F(0xf0)=lookup_orientation_sine_quantized_abs(-heading[0])*motion[1]+100.0;motion[1]*=D(0.97f);}SCALE(F(0x11c)*D(0.99f));if(I(0x144)>=20)FADE(10,10);break;
  case 4:SCALE(F(0x11c)+F(0x370));F(0x370)*=D(0.95f);if(I(0x144)>=20)FADE(10,10);break;
  }break;
 case 980:update_ping_pong_motion();break;
 case 998:
  F(0x12c)+=5.0;
  if(S(0x13e)==0){if(AT(P,short,0x13c)>153 && AT(P,short,0x13c)<158){F(0xec)=C(0x104)*57+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+60.0;}
   if(AT(P,short,0x13c)>149 && AT(P,short,0x13c)<154){F(0xec)=C(0x104)*57+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+94.0;}
   if(AT(P,short,0x13c)==158){F(0xec)=C(0x104)*57+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;}
   if(AT(P,short,0x13c)<150 || AT(P,short,0x13c)>158){next_sequence_block();AT(P,unsigned char,0x751)=0;}}
  if(S(0x13e)==1)FADE(10,10);break;
 default:advance_frame();return;
 }
 if(advance_frame())--I(0x330);
}
#undef AT
#undef F
#undef S
#undef B
#undef C
#undef I
#undef H
#undef P
#undef A
#undef T
#undef MOTION
#undef D
#undef RND
#undef RETIRE
#undef MOVE
#undef STEP
#undef SCALE
#undef FADE
#undef COLORFADE
#undef ENTRY
#undef OUTSIDE
#undef PACKET
#undef SPAWN
}
