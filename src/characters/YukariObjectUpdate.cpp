// Complete manual JP1.06a58DB80 source hypothesis; not canonically exact.
// Evidence, comparisons and remaining unknowns: docs/YUKARI_OBJECT_UPDATE_2026_10_25.md.
#include "YukariObjectUpdate.hpp"
#include <math.h>
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define I(o) AT(this,int,o)
#define H AT(this,float *,0x340)
#define P AT(this,YukariObjectUpdateView *,0x348)
#define A AT(this,YukariObjectUpdateView *,0x170)
#define AUX(p,t,o) AT(AT(p,void *,0x154),t,o)
#define X(t,o) AUX(this,t,o)
#define MOTION reinterpret_cast<YukariUpdateMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
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
void YukariObjectUpdateView::update_action_state()
{
 float p544[3],p568[3],p556[3],p36[3],p312[3],p448[3],p84[3],p460[3],p60[3],p300[3],p12[3],p144[3],p264[3],p72[3],p240[3],p120[3],p216[3],p24[3],p436[3],p192[3],p96[3],p168[3],p360[4],p344[4],p328[4],p376[4],p48[3],p532[3],p520[3],p288[3],p412[3],p252[3],p228[3],p204[3],p180[3],p592[3],p400[3],p156[3],p472[3],p108[3],p388[3],p580[3];
 float p484[3],p276[3],p132[3],p424[3],p508[3],p496[3];
 switch(S(0x13c)) {
 case 800:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(S(0x140)==0){if(emit_repeated(0,0,2))RETIRE();if(I(0x180)!=0){next_sequence_frame();F(0xf4)=F(0xf8)=0;return;}goto yukari800_motion;}
   goto yukari800_fade;
  case 1:
   if(S(0x140)==0){if(I(0x144)==5)release_auxiliary();if(emit_repeated(0,0,2))RETIRE();if(I(0x180)!=0){next_sequence_frame();F(0xf4)=F(0xf8)=0;return;}
 yukari800_motion:
    F(0x12c)=H[0];MOVE();
   }
 yukari800_fade:
   if(S(0x140)==1){SCALE(F(0x11c)*D(0.85f));if(B(0x113)<20){B(0x113)=0;RETIRE();}B(0x113)-=20;}break;
  case 2:
   if(S(0x140)==0){if(I(0x144)==5)release_auxiliary();if(emit_repeated(0,0,2))RETIRE();if(I(0x180)!=0){next_sequence_frame();F(0xf4)=F(0xf8)=0;return;}F(0x12c)=H[0];MOVE();}
   if(S(0x140)==1){SCALE(F(0x11c)*D(0.85f));if(B(0x113)>19)B(0x113)-=20;else{B(0x113)=0;RETIRE();}}break;
  case 3:
   if(AT(P,short,0x13c)==402 && AT(P,short,0x140)<11)position_relative(0,0);
   else if(AT(P,short,0x13c)==406 && AT(P,short,0x140)<=11)position_relative(0,30);
   else if(S(0x140)<21){set_sequence_frame(21);return;}break;
  }
  STEP();if(OUTSIDE(1380.0f,-100.0,800.0,-120.0))RETIRE();break;
 case 801:
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,0,5))RETIRE();MOVE();if(H[3]<=static_cast<float>(I(0x144))){next_sequence_block();SCALE(1.0);H[0]-=90.0;H[1]=10;return;}break;
  case 1:
   if(I(0x144)==0)replace_secondary(991,5,20,1,2);if(emit_repeated(0,0,5))RETIRE();advance_six(5);
   if(I(0x180)!=0){next_sequence_block();F(0xf4)=F(0xf8)=0;PACKET(p544,RND(360),0,3);SPAWN(801,1,p544);p544[2]=4;float n=0;do{p544[0]=RND(360);p544[1]=RND(20)+10.0;SPAWN(801,1,p544);n+=1.0;}while(n<8.0f);return;}
   H[1]+=1.0;if(H[1]>30.0)H[1]=30;MOVE();if(OUTSIDE(1680.0,-400.0,1400.0f,-520.0f))RETIRE();break;
  case 2:
   SCALE(F(0x11c)*D(0.98f));if(I(0x144)>9){release_secondary();COLORFADE(15,15);}
   else{F(0x370)-=25.0;if(F(0x370)<=0.0)F(0x370)=0;set_secondary_alpha(static_cast<unsigned char>(F(0x370)));}break;
  case 3:F(0x11c)+=D(0.3f);F(0x120)+=D(0.3f);COLORFADE(10,10);break;
  case 4:if(I(0x144)>19)COLORFADE(10,10);H[1]*=D(0.9f);MOVE();break;
  case 5:
   if(I(0x144)==0)replace_secondary(991,5,20,1,2);if(emit_repeated(0,0,5))RETIRE();MOVE();if(H[3]<=static_cast<float>(I(0x144))){select_sequence(7);I(0x144)=0;SCALE(1.0);H[0]+=90.0;H[1]=10;S(0x364)=0;return;}break;
  case 6:
   if(I(0x144)==0)replace_secondary(991,5,20,1,2);if(emit_repeated(0,0,5))RETIRE();MOVE();if(H[3]<=static_cast<float>(I(0x144))){select_sequence(8);I(0x144)=0;SCALE(1.0);H[0]-=90.0;H[1]=10;S(0x364)=0;return;}break;
  case 7:
   if(emit_repeated(0,0,5))RETIRE();advance_six(5);
   if(I(0x180)!=0){next_sequence_block();F(0xf4)=F(0xf8)=0;PACKET(p568,RND(360),0,3);SPAWN(801,1,p568);p568[2]=4;float n=0;do{p568[0]=RND(360);p568[1]=RND(20)+10.0;SPAWN(801,1,p568);n+=1.0;}while(n<8.0f);return;}
   if(H[3]<=static_cast<float>(I(0x144)) && S(0x364)==0){H[0]+=45.0;++S(0x364);}H[1]+=1.0;if(H[1]>30.0)H[1]=30;MOVE();if(OUTSIDE(1680.0,-400.0,1400.0f,-520.0f))RETIRE();break;
  case 8:
   if(emit_repeated(0,0,5))RETIRE();advance_six(5);
   if(I(0x180)!=0){next_sequence_block();F(0xf4)=F(0xf8)=0;PACKET(p556,RND(360),0,3);SPAWN(801,1,p556);p556[2]=4;float n=0;do{p556[0]=RND(360);p556[1]=RND(20)+10.0;SPAWN(801,1,p556);n+=1.0;}while(n<8.0f);return;}
   if(H[3]<=static_cast<float>(I(0x144)) && S(0x364)==0){S(0x364)=1;H[0]-=45.0;}H[1]+=1.0;if(H[1]>30.0)H[1]=30;MOVE();if(OUTSIDE(1680.0,-400.0,1400.0f,-520.0f))RETIRE();break;
  }
  STEP();break;
 case 810:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:if(AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150 && S(0x140)<21){set_sequence_frame(21);return;}if(S(0x142)==0 && S(0x140)==10){PACKET(p36,0,0,1);SPAWN(810,1,p36);}break;
  case 1:case 2:case 3:
   if(S(0x140)==0){F(0xf8)-=0.5;if(F(0xf8)+F(0xf0)<=stage_surface_height()){
     release_auxiliary();F(0xf8)=0;F(0xf0)=stage_surface_height();next_sequence_frame();P->publish_layout_scalar(5);P->dispatch_character_wave_handle(11);p312[2]=4;float n=0;
     do{p312[0]=n*60.0-20.0+RND(40);p312[1]=RND(8)+20.0;if(p312[0]<0.0 || p312[0]>180.0f)S(0x364)=-1;else S(0x364)=1;SPAWN(810,B(0x364),p312);n+=1.0;}while(n<6.0f);
    }}
   if(S(0x140)==1)FADE(5,5);STEP();break;
  case 4:H[1]*=D(0.9f);MOVE();FADE(10,10);F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;break;
  }
  if(!(F(0xec)<=1380.0f && F(0xec)>=-100.0 && F(0xf0)<=1000.0 && F(0xf0)>=-120.0))RETIRE();
  if(advance_frame())--I(0x330);if(ENTRY(1))--I(0x330);return;
 case 811:
  if(S(0x13e)==0){
   if(S(0x364)==0){SCALE(F(0x370)+F(0x11c));F(0x370)*=D(0.8f);if(F(0x370)<=0.01f)F(0x370)=0;
    if(I(0x144)==2){float n=0;do{PACKET(p448,n*10.0-30.0,35,1);unsigned packet_face=B(0x104);spawn_unparented(811,C(0x104)*(lookup_orientation_cosine_quantized_abs(-p448[0])*100.0-100.0)+F(0xec),lookup_orientation_sine_quantized_abs(-p448[0])*100.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p448),3);n+=1.0;}while(n<7.0);}
   }else{F(0x11c)*=D(0.85f);F(0x120)+=D(0.1f);if(F(0x11c)<=0.01f)RETIRE();}
   if(AT(P,short,0x13c)!=505 || (AT(P,short,0x13e)==0 && AT(P,short,0x140)>7) || (AT(P,short,0x13e)==1 && AT(P,short,0x140)>5))S(0x364)=1;
  }else if(S(0x13e)==1){MOVE();advance_six(0);
   if(I(0x144)>3 && S(0x364)==0){if(S(0x36c)==0)S(0x36c)=(C(0x184)!=0)+1;B(0x184)=0;H[1]*=0.25;if(H[1]<=0.01f){H[1]=0;B(0x184)=0;S(0x364)=1;I(0x144)=0;}if(AT(P,short,0x13c)!=505){S(0x364)=1;B(0x184)=0;I(0x144)=0;}}
   if(S(0x364)==1 && (I(0x144)>19 || AT(P,short,0x13c)!=505)){S(0x364)=2;if(I(0x144)>19 && AT(P,signed char,0x608)>3 && S(0x36c)==2){S(0x364)=3;B(0x184)=1;I(0x180)=0;}I(0x144)=0;}
   if(S(0x364)==2){H[1]=-40;if(I(0x144)>9)RETIRE();}
   if(S(0x364)==3){if(emit_repeated(0,1,2))RETIRE();MOTION->set_components(H[0],static_cast<float>(lookup_orientation_cosine_quantized_abs(-H[0])*10.0+20.0));advance_six(0);if(C(0x184)<1)FADE(5,5);if(F(0xec)>1680.0 || F(0xec)<-400.0)RETIRE();}
   STEP();
  }break;
 case 812:
  switch(S(0x13e)) {
  case 0:
   F(0x12c)+=3.0;
   if(I(0x144)<80){if(emit_repeated(0,2,5))RETIRE();if(I(0x144)%6==0){PACKET(p84,F(0x12c),F(0x11c),3);SPAWN(812,1,p84);}
    if(I(0x144)==40 || I(0x144)==45 || I(0x144)==50 || (I(0x144)==55 && AT(P,signed char,0x60c)>3)){
     PACKET(p460,RND(360),80.0-static_cast<float>(I(0x144)),1);unsigned packet_face=B(0x104);spawn_unparented(812,C(0x104)*lookup_orientation_cosine_quantized_abs(180.0f-p460[0])*1280.0+F(0xec),lookup_orientation_sine_quantized_abs(180.0f-p460[0])*1280.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p460),3);P->dispatch_character_wave_handle(22);
    }SCALE(1.0-F(0x370));F(0x370)*=D(0.9f);
   }else{SCALE(F(0x11c)+D(0.2f));COLORFADE(25,25);}break;
  case 1: {
   float width=static_cast<float>(18.0-F(0x370));F(0x11c)=width+width;F(0x120)*=D(0.95f);F(0x370)*=D(0.8f);if(B(0x111)<3){B(0x112)=0;B(0x111)=0;}else{B(0x112)-=3;B(0x111)-=3;}
   if(H[1]==static_cast<float>(I(0x144))){PACKET(p60,H[0],80,2);SPAWN(812,1,p60);}if(F(0x120)<=D(0.005f))RETIRE();break;
  }
  case 2:MOVE();F(0x11c)+=0.75;F(0x120)*=D(0.98f);if(I(0x144)>39){B(0x184)=0;COLORFADE(5,5);}STEP();break;
  case 3:F(0x12c)-=3.0;SCALE(F(0x11c)+D(0.1f));COLORFADE(10,10);break;
  case 4:
   F(0x12c)+=3.0;
   if(I(0x144)>79){SCALE(F(0x11c)+D(0.2f));COLORFADE(25,25);}
   else{if(emit_repeated(0,2,5))RETIRE();if(I(0x144)%6==0){PACKET(p300,F(0x12c),F(0x11c),3);SPAWN(812,1,p300);}
    if(I(0x144)==40 || I(0x144)==45 || I(0x144)==50 || I(0x144)==55 || I(0x144)==60 || (I(0x144)==65 && AT(P,signed char,0x60c)>3)){
     PACKET(p484,RND(360),80.0-static_cast<float>(I(0x144)),1);unsigned packet_face=B(0x104);spawn_unparented(812,C(0x104)*lookup_orientation_cosine_quantized_abs(180.0f-p484[0])*1280.0+F(0xec),lookup_orientation_sine_quantized_abs(180.0f-p484[0])*1280.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p484),3);P->dispatch_character_wave_handle(22);
    }SCALE(1.0-F(0x370));F(0x370)*=D(0.9f);
   }break;
  case 5:F(0x12c)-=6.0;SCALE(F(0x11c)+D(0.15f));COLORFADE(20,20);break;
  }
  break;
 case 815:
  if(S(0x13e)==0){F(0x12c)+=20.0;if(S(0x364)==0){if(AT(P,short,0x13c)==520 || AT(P,short,0x13c)==521){position_relative(0,135);if((AT(P,short,0x13c)==520 || AT(P,short,0x13c)==521) && AT(P,short,0x13e)>1){S(0x364)=1;return;}}else S(0x364)=1;}else FADE(20,20);}
  if(S(0x13e)==1){F(0x12c)-=20.0;if(S(0x364)==0){if(AT(P,short,0x13c)==520 || AT(P,short,0x13c)==521){position_relative(0,135);if((AT(P,short,0x13c)==520 || AT(P,short,0x13c)==521) && AT(P,short,0x13e)>1){S(0x364)=1;return;}}else S(0x364)=1;}else FADE(20,20);}break;
 case 816:
  F(0x12c)+=20.0;
  if(S(0x13e)==0 || S(0x13e)==2){
   if(AT(P,short,0x13c)!=525 && AT(P,short,0x13c)!=526)goto yukari816_next;
   if(I(0x180)!=0 && ++S(0x364)>9){S(0x364)=0;I(0x180)=0;B(0x184)=1;}
   if(AT(P,short,0x13e)==1 || (AT(P,short,0x13e)==2 && AT(P,short,0x140)<8))position_relative(0,135);
   if(AT(P,short,0x13e)==2 && AT(P,short,0x140)==8){I(0x180)=0;if(AT(P,signed char,0x609)>3)B(0x184)=5;if(AT(P,signed char,0x609)<4)B(0x184)=4;if(AT(P,signed char,0x609)<2)B(0x184)=3;I(0x144)=0;
 yukari816_next:
    next_sequence_block();return;}
  }
  if(S(0x13e)==1 || S(0x13e)==3){if(emit_repeated(0,3,5))RETIRE();MOVE();if(C(0x184)<1 || I(0x144)>119){B(0x184)=0;H[1]*=D(0.85f);FADE(10,10);}else{H[1]+=0.5;if(H[1]>15.0)H[1]=15;}advance_six(0);
   if(I(0x180)!=0){if(S(0x366)==0){H[1]=1;++S(0x366);STEP();break;}if(++S(0x366)>9){I(0x180)=0;S(0x366)=0;}}
  }STEP();break;
 case 820:
  if(OUTSIDE(1380.0f,-100.0,1000.0,-120.0))RETIRE();
  switch(S(0x13e)) {
  case 0:case 1:case 2:
   if(S(0x13e)<2 && emit_repeated(0,2,8))RETIRE();
   if(S(0x13e)==0){F(0x11c)+=D(0.1f);if(F(0x11c)>=1.0){F(0x11c)=1;next_sequence_block();return;}}
   if(S(0x13e)==1){if(I(0x180)==8){I(0x180)=0;B(0x184)=1;++AT(P,short,0x7a6);if(AT(P,signed char,0x606)>3)++AT(P,short,0x7a6);if(AT(P,short,0x7a6)>13)AT(P,short,0x7a6)=13;}if((AT(P,signed char,0x606)+4)*15<=I(0x144)){next_sequence_block();return;}}
   if(S(0x13e)==2){F(0x11c)*=D(0.85f);if(F(0x11c)<=0.01f)RETIRE();}break;
  case 3:
   if(S(0x364)<2 && emit_repeated(0,2,8)){AT(P,short,0x7a6)=0;RETIRE();}
   if(S(0x364)==0){F(0x11c)+=D(0.1f);if(F(0x11c)>=1.0){F(0x11c)=1;S(0x364)=1;I(0x144)=0;return;}}
   if(S(0x364)==1 && I(0x144)%5==0){if(AT(P,short,0x7a6)<1){S(0x364)=2;return;}P->dispatch_character_wave_handle(1);PACKET(p12,RND(360),12,7);SPAWN(820,1,p12);--AT(P,short,0x7a6);}
   if(S(0x364)==2){F(0x11c)*=D(0.85f);if(F(0x11c)<=0.01f)RETIRE();}break;
  case 4: // Native58FCCB retains its explicit cached-WORD comparison with5.
   if(S(0x13e)==5)F(0x11c)*=D(0.85f);break;
  case 7:
   if(emit_repeated(0,0,3))RETIRE();if(I(0x144)==0)replace_secondary(991,20,10,1,2);
   if(S(0x364)==0){H[1]-=0.5;if(H[1]<0.0){H[1]=0;S(0x364)=1;turn_heading(0,180,100);}}
   else{H[1]+=1.0;if(H[1]>30.0)H[1]=30;turn_heading(0,0.5f,100);}
   if(C(0x184)==0){--I(0x330);PACKET(p144,0,0,8);SPAWN(820,1,p144);return;}MOVE();STEP();break;
  case 8:
   if(B(0x113)<30)RETIRE();SCALE(F(0x11c)+D(0.2f));B(0x113)-=30;B(0x111)-=30;B(0x112)-=30;break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(3))RETIRE();if(ENTRY(6))--I(0x330);return;
 case 821:
  switch(S(0x13e)) {
  case 0:
   F(0x11c)=lookup_orientation_cosine_quantized_abs(static_cast<float>(I(0x144))*5.0)*0.25+0.75;F(0x120)=lookup_orientation_cosine_quantized_abs(static_cast<float>(I(0x144))*5.0+135.0f)*0.25+0.75;
   if(H[1]==1.0)F(0x12c)+=0.5;if(H[1]==2.0f)F(0x12c)-=0.5;
   if(I(0x144)%60==0){PACKET(p264,RND(360),static_cast<float>(static_cast<unsigned>(selector_random_roll(10)-5))*D(0.2f),4);spawn_parented(821,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p264),3);}
   if(S(0x36c)==1 && emit_repeated(0,2,4)){AT(P,short,0x7bc)=0;RETIRE();}
   if(AT(P,short,0x7bc)==0){next_sequence_block();return;}
   if(AT(P,short,0x174)<1 || AT(A,short,0x174)<1){AT(P,short,0x7bc)=0;next_sequence_block();return;}
   if(AT(P,short,0x7bc)==2){S(0x36c)=1;if(AT(P,short,0x13e)==0 && AT(P,short,0x140)==0 && AT(P,short,0x13c)>544 && AT(P,short,0x13c)<550){AT(P,short,0x7bc)=0;next_sequence_block();return;}
    float *heading=H;
    if(heading[1]==1.0){heading[0]=-atan2_degrees(AT(P,float,0x7b8)-F(0xf0),C(0x104)*(AT(P,float,0x7b0)-F(0xec)));AT(P,int,0x7ac)=I(0xec);AT(P,int,0x7b4)=I(0xf0);}
    if(heading[1]==2.0f){H[0]=-atan2_degrees(AT(P,float,0x7b4)-F(0xf0),C(0x104)*(AT(P,float,0x7ac)-F(0xec)));AT(P,int,0x7b0)=I(0xec);AT(P,int,0x7b8)=I(0xf0);}
    if(square_float_value(AT(P,float,0x7b4)-AT(P,float,0x7b8))+square_float_value(AT(P,float,0x7ac)-AT(P,float,0x7b0))<=square_int_value(10)){
     if(H[1]==2.0f){PACKET(p72,0,0,2);spawn_unparented(821,(AT(P,float,0x7b0)+F(0xec))*0.5,(AT(P,float,0x7b8)+F(0xf0))*0.5,B(0x104),1,reinterpret_cast<const unsigned *>(p72),3);AT(P,short,0x7bc)=0;P->dispatch_character_wave_handle(20);RETIRE();}RETIRE();
    }
    F(0x370)+=D(0.3f);double limit=2.0+AT(P,signed char,0x60a)*2.0;if(F(0x370)>=limit)F(0x370)=static_cast<float>(limit);MOTION->set_components(H[0],F(0x370));STEP();
   }break;
  case 1:if(H[1]==1.0)F(0x12c)+=10.0;if(H[1]==2.0f)F(0x12c)-=10.0;
  case 3:F(0x11c)*=D(0.85f);F(0x120)+=D(0.1f);if(F(0x11c)<=0.01f)RETIRE();break;
  case 2:
   advance_six(0);
   if(F(0x370)==1.0){if(C(0x184)<1 || ((AT(P,signed char,0x60a)>3)+2)*30<=I(0x144)){next_sequence_block();return;}
    if(I(0x180)!=0 && ++S(0x364)>4){S(0x364)=0;I(0x180)=0;}
    if(I(0x144)%3==0){PACKET(p240,RND(360),RND(20)+10.0,5);SPAWN(821,1,p240);}if(I(0x144)%7==0){PACKET(p120,RND(360),static_cast<float>(static_cast<unsigned>(selector_random_roll(20)-10)),6);spawn_parented(821,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p120),3);}
   }else{F(0x370)=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(I(0x144)*15)));if(F(0x370)==1.0){B(0x184)=10;I(0x144)=0;}}
   F(0x11c)=(lookup_orientation_cosine_quantized_abs(static_cast<float>(I(0x144))*50.0)*0.5+1.5)*F(0x370);F(0x120)=(lookup_orientation_cosine_quantized_abs(static_cast<float>(I(0x144))*50.0+135.0f)*0.5+1.5)*F(0x370);break;
  case 4:SCALE(F(0x11c)+D(0.01f));F(0x12c)+=H[1];if(AT(this,void *,0x34c)==0)RETIRE();I(0xec)=AT(AT(this,void *,0x34c),int,0xec);I(0xf0)=AT(AT(this,void *,0x34c),int,0xf0);FADE(3,2);break;
  case 5:if(I(0x144)>19)COLORFADE(10,10);H[1]*=D(0.85f);F(0x11c)*=D(0.9f);F(0x120)+=D(0.2f);MOVE();STEP();break;
  case 6:SCALE(F(0x370)+F(0x11c));F(0x370)*=D(0.95f);F(0x12c)+=H[1];FADE(11,10);break;
  }break;
 case 825:
  if(S(0x13e)==0){if(S(0x364)==0){short owner_action=AT(P,short,0x13c);if(owner_action==560 || owner_action==561 || owner_action==562 || owner_action==563){position_relative(0,100);if(AT(P,short,0x140)<5 && AT(P,short,0x13e)==0){F(0x11c)+=F(0x370);F(0x370)*=D(0.9f);}if(AT(P,short,0x140)==5 && AT(P,short,0x13e)==0)F(0x11c)*=D(0.8f);if(AT(P,short,0x140)==6 && AT(P,short,0x13e)==0)RETIRE();}else S(0x364)=1;}
   if(S(0x364)==1){F(0x11c)*=D(0.8f);if(F(0x11c)<=0.01f)RETIRE();}
  }else if(S(0x13e)==1){F(0x11c)+=F(0x370);F(0x370)*=D(0.9f);if(F(0x370)<=0.01f || (AT(P,short,0x13c)!=560 && AT(P,short,0x13c)!=562)){P->release_auxiliary();FADE(5,5);}}
  else if(S(0x13e)==2){if(I(0x144)>9)P->release_auxiliary();if(AT(P,short,0x13c)!=561 && AT(P,short,0x13c)!=563){P->release_auxiliary();if(S(0x140)<21){set_sequence_frame(21);return;}}}break;
 case 826:
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x186)==0)F(0x12c)+=20.0;
   if(AT(this,void *,0x34c)==0){release_auxiliary();F(0xec)=C(0x104)*AT(P,float,0xf4)+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+130.0f+AT(P,float,0xf8);if(AT(P,short,0x13c)!=565 && AT(P,short,0x13c)!=566)RETIRE();if(AT(P,short,0x13e)==3)FADE(20,20);}
   else{void *related=AT(this,void *,0x34c);F(0xec)=C(0x104)*AT(related,float,0xf4)+AT(related,float,0xec);F(0xf0)=AT(related,float,0xf0)+130.0f+AT(related,float,0xf8);X(float,0xec)=stage_surface_height();}break;
  case 1:case 6:if(AT(P,short,0x13c)==565 || AT(P,short,0x13c)==566){I(0xec)=AT(P,int,0xec);F(0xf0)=AT(P,float,0xf0);}break;
  case 2:I(0xec)=AT(P,int,0xec);I(0xf0)=AT(P,int,0xf0);if((AT(P,short,0x13c)!=565 && AT(P,short,0x13c)!=566) || AT(P,short,0x13e)!=0){next_sequence_block();return;}break;
  case 4:F(0x12c)+=F(0x370);F(0x370)*=D(0.95f);SCALE(F(0x11c)+H[1]);H[1]*=D(0.95f);FADE(5,5);break;
  case 5:F(0xf8)=-20;I(0xec)=AT(P,int,0xec);if(F(0xf0)<=AT(P,float,0xf0)-230.0)RETIRE();F(0xf0)+=F(0xf8);break;
  case 7:
   if(AT(P,short,0x13c)==565 || AT(P,short,0x13c)==566){I(0xec)=AT(P,int,0xec);F(0xf0)=P->stage_surface_height();}
   if((AT(P,short,0x13c)!=565 && AT(P,short,0x13c)!=566) || AT(P,short,0x13e)>1){next_sequence_block();return;}break;
  case 9:
   I(0xec)=AT(P,int,0xec);F(0xf8)-=0.5;F(0x12c)-=40.0;X(float,0xec)=stage_surface_height();goto yukari826_rise;
  case 10:
   I(0xec)=AT(P,int,0xec);F(0xf0)=AT(P,float,0xf0)+F(0x370);X(int,0xe8)=I(0xec);X(float,0xec)=stage_surface_height();F(0x370)+=20.0;if(F(0x370)>-115.0)F(0x370)=-115;
   if(AT(P,short,0x186)==0)F(0x12c)-=40.0;if(AT(P,short,0x13c)!=566)RETIRE();if(AT(P,short,0x13e)==1 && AT(P,short,0x140)==2){next_sequence_block();F(0xf8)=17.5f;}break;
  case 11:I(0xec)=AT(P,int,0xec);X(int,0xe8)=I(0xec);X(float,0xec)=stage_surface_height();F(0xf8)-=0.5;F(0x12c)-=40.0;
 yukari826_rise:
   F(0x370)+=F(0xf8);F(0xf0)=F(0x370)+AT(P,float,0xf0);AT(P,int,0x12c)=I(0x12c);
   if(F(0x370)>=0.0){P->select_sequence(2);AT(P,int,0xec)=I(0xec);AT(P,int,0xf0)=I(0xf0);AT(P,int,0xf8)=I(0xf8);AT(P,float,0x100)=1;RETIRE();}break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(4))RETIRE();if(ENTRY(9))--I(0x330);return;
 case 848:
  switch(S(0x13e)) {
  case 0:position_relative(0,0);if(AT(P,short,0x13c)!=301)RETIRE();break;
  case 1:position_relative(0,0);if(AT(P,short,0x13c)!=306 && AT(P,short,0x13c)!=408)RETIRE();break;
  case 2:position_relative(0,0);if(AT(P,short,0x13c)!=305 && AT(P,short,0x13c)!=309)RETIRE();break;
  case 3:position_relative(0,0);if(AT(P,short,0x13c)!=307)RETIRE();break;
  case 5:position_relative(0,0);if(AT(P,short,0x13c)!=321 && AT(P,short,0x13c)!=322)RETIRE();break;
  case 6:position_relative(0,0);if(AT(P,short,0x13c)!=304 && AT(P,short,0x13c)!=418)RETIRE();break;
  }
  if(AT(P,short,0x186)==0 && advance_frame())RETIRE();if(S(0x140)==0 && S(0x142)==0)--I(0x330);return;
 case 849:
  if(S(0x13e)==0){F(0xf8)-=D(0.1f);if(I(0x144)>59)FADE(10,10);}
  else if(S(0x13e)==1){if(AT(P,short,0x13c)!=201)RETIRE();F(0xf8)-=D(0.1f);if(F(0xf8)+F(0xf0)<=stage_surface_height()){--I(0x330);P->select_sequence(6);AT(P,unsigned char,0x104)=B(0x104);return;}}
  STEP();break;
 case 850:
  if(S(0x13e)==0){F(0x12c)-=10.0;if(AT(P,short,0x13c)==600){
    if(F(0x11c)!=1.0){SCALE(lookup_orientation_sine(I(0x144)*18));if(F(0x11c)==1.0){S(0x364)=1;B(0x184)=1;}}
    if(I(0x144)%5==0){PACKET(p216,F(0x12c),F(0x11c),2);SPAWN(850,1,p216);}
    if(AT(P,short,0x140)>6){I(0x180)=0;B(0x184)=1;next_sequence_block();return;}
    position_relative(150,145);advance_six(0);if(I(0x180)!=0 && ++S(0x366)>4){S(0x366)=0;I(0x180)=0;B(0x184)=1;}
   }else{next_sequence_block();B(0x184)=0;}
  }else if(S(0x13e)==1)goto yukari850_853_one;
  else if(S(0x13e)==2){SCALE(F(0x11c)+D(0.025f));F(0x12c)-=5.0;COLORFADE(10,10);MOTION->set_components(-30,3);STEP();}break;
 case 851:
  if(S(0x13e)<3 && ((AT(P,short,0x13c)>599 && AT(P,short,0x13c)<690 && AT(P,short,0x13e)==0 && AT(P,short,0x140)==0) || emit_repeated(0,0,0))){SCALE(1.0);F(0x12c)=0;select_sequence(3);return;}
  switch(S(0x13e)) {
  case 0:
   F(0x11c)=1.0-F(0x370);F(0x120)=F(0x370)+F(0x370)+1.0;F(0x370)*=D(0.8f);if(F(0x370)<=0.005f){F(0x370)=0;S(0x344)=0;}
   if(AT(P,short,0x13c)!=601){SCALE(1.0);select_sequence(3);return;}if(AT(P,short,0x140)==6){SCALE(1.0);next_sequence_block();return;}break;
  case 1:
   F(0xec)+=C(0x104)*25;{double distance=fabs(F(0xec)-AT(A,float,0xec));
    if(distance<=50.0){P->dispatch_character_wave_handle(52);next_sequence_block();B(0x184)=15;PACKET(p24,0,0,4);spawn_parented(851,F(0xec),F(0xf0),B(0x104),-1,reinterpret_cast<const unsigned *>(p24),3);return;}}
   if(F(0xec)>1480.0f || F(0xec)<-200.0){--I(0x330);AT(P,unsigned char,0x7a8)=0;}break;
  case 2:
   F(0x12c)-=30.0;F(0xec)+=C(0x104);if(C(0x184)<1){F(0x12c)=0;next_sequence_block();return;}advance_six(0);if(I(0x180)!=0 && ++S(0x364)>3){S(0x364)=0;I(0x180)=0;}break;
  case 3:F(0x11c)*=D(0.8f);F(0x120)+=D(0.1f);if(F(0x11c)<=0.01f){--I(0x330);AT(P,unsigned char,0x7a8)=0;return;}break;
  case 4:F(0x12c)-=30.0;if(AT(this,void *,0x34c)==0)RETIRE();I(0xec)=AT(AT(this,void *,0x34c),int,0xec);I(0xf0)=AT(AT(this,void *,0x34c),int,0xf0);if(AT(AT(this,void *,0x34c),short,0x13e)!=2)RETIRE();break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(3))F(0x12c)=0;return;
 case 852:
  if(AT(P,short,0x174)<1 && S(0x13e)<2){select_sequence(2);return;}
  if(static_cast<unsigned short>(S(0x13e))<3){STEP();
   if(H[0]==0.0){F(0xf0)=0;if(C(0x104)!=0 && F(0xec)>=g_update_right){F(0xec)=g_update_right;H[0]=-90;B(0x184)=1;I(0x180)=0;++S(0x364);}if(C(0x104)==-1 && F(0xec)<=g_update_left){F(0xec)=g_update_left;H[0]=-90;B(0x184)=1;I(0x180)=0;++S(0x364);}}
   if(H[0]==-90.0f){if(C(0x104)!=0)F(0xec)=g_update_right;if(C(0x104)==-1)F(0xec)=g_update_left;if(F(0xf0)>=g_update_top){F(0xf0)=g_update_top;H[0]=180;B(0x184)=1;I(0x180)=0;++S(0x364);}}
   if(H[0]==180.0f){F(0xf0)=g_update_top;if(C(0x104)==-1 && F(0xec)>=g_update_right){F(0xec)=g_update_right;H[0]=90;B(0x184)=1;I(0x180)=0;++S(0x364);}if(C(0x104)==1 && F(0xec)<=g_update_left){F(0xec)=g_update_left;H[0]=90;B(0x184)=1;I(0x180)=0;++S(0x364);}}
   if(H[0]==90.0f){if(C(0x104)==-1)F(0xec)=g_update_right;if(C(0x104)==1)F(0xec)=g_update_left;if(F(0xf0)<=0.0){F(0xf0)=0;H[0]=0;B(0x184)=1;I(0x180)=0;++S(0x364);}}
   if(S(0x13e)<2 && S(0x364)>4){select_sequence(2);return;}if(S(0x13e)==2){B(0x184)=0;COLORFADE(6,6);H[1]*=D(0.95f);}MOVE();I(0x12c)=AT(H,int,0);
  }break;
 case 853:
  switch(S(0x13e)) {
  case 0:
   F(0x12c)-=10.0;if(AT(P,short,0x13c)==603){
    if(F(0x11c)==1.0){F(0x370)+=D(0.2f);if(F(0x370)>8.0f)F(0x370)=8;AT(P,int,0x6ac)=I(0x370);if((F(0xec)<AT(A,float,0xec) && AT(A,signed char,0x104)==1) || (AT(A,float,0xec)<F(0xec) && AT(A,signed char,0x104)==-1))AT(P,float,0x6ac)=-F(0x370);}
    else{SCALE(lookup_orientation_sine(I(0x144)*18));if(F(0x11c)==1.0){S(0x364)=1;B(0x184)=1;}}
    if(I(0x144)%5==0){PACKET(p436,F(0x12c),F(0x11c),2);SPAWN(853,1,p436);p436[2]=3;SPAWN(853,1,p436);}
    if(I(0x144)%15==0){PACKET(p192,0,0,4);spawn_unparented(853,F(0xec),AT(P,float,0xf0),B(0x104),-1,reinterpret_cast<const unsigned *>(p192),3);}
    if(AT(P,short,0x140)>7){I(0x180)=0;B(0x184)=1;next_sequence_block();return;}
    position_relative(150,145);advance_six(0);if(I(0x180)!=0 && ++S(0x366)>4){S(0x366)=0;I(0x180)=0;B(0x184)=1;}
   }else{next_sequence_block();B(0x184)=0;}break;
  case 1:
 yukari850_853_one:
   F(0x12c)-=10.0;{int counter=I(0x144);if(counter==2){B(0x184)=0;counter=I(0x144);}if(counter>1)FADE(15,15);}break;
  case 2:SCALE(F(0x11c)+D(0.025f));F(0x12c)-=5.0;COLORFADE(10,10);MOTION->set_components(-30,10);STEP();break;
  case 3:SCALE(F(0x11c)-D(0.025f));F(0x12c)+=5.0;COLORFADE(10,10);MOTION->set_components(-30,-10);STEP();break;
  case 4:
   if(S(0x364)==0){if(B(0x113)<241)B(0x113)+=15;else{B(0x113)=255;S(0x364)=1;}if(AT(P,short,0x13c)!=603 || AT(P,short,0x140)>7)S(0x364)=2;}
   if(S(0x364)==1 && F(0x11c)<0.25f)FADE(10,10);if(S(0x364)==2)FADE(10,10);SCALE(F(0x11c)*D(0.9f));break;
  }break;
 case 854:
  if(S(0x13e)<3 && ((AT(P,short,0x13c)>599 && AT(P,short,0x13c)<690 && AT(P,short,0x13e)==0 && AT(P,short,0x140)==0) || emit_repeated(0,0,0))){SCALE(1.0);F(0x12c)=0;select_sequence(3);return;}
  switch(S(0x13e)) {
  case 0:
   F(0x11c)=1.0-F(0x370);F(0x120)=F(0x370)+F(0x370)+1.0;F(0x370)*=D(0.8f);if(F(0x370)<=0.005f){F(0x370)=0;S(0x344)=0;}
   if(AT(P,short,0x13c)!=604){SCALE(1.0);select_sequence(3);return;}if(AT(P,short,0x140)==6){SCALE(1.0);next_sequence_block();F(0xf4)=8;F(0xf8)=20;F(0x100)=0.75f;return;}break;
  case 1:case 2: {
   float horizontal=C(0x104)*F(0xf4);if((horizontal>0.0 && F(0xec)>=g_update_right) || (horizontal<0.0 && F(0xec)<=g_update_left)){F(0xf4)=-F(0xf4);P->dispatch_character_wave_handle(57);}
   if(F(0xf8)<0.0 && F(0xf0)<=stage_surface_height()){F(0xf8)*=-1.0;if(F(0xf8)<20.0f)F(0xf8)=20;if(F(0xf4)>30.0)F(0xf8)=30;B(0x184)=1;I(0x180)=0;P->dispatch_character_wave_handle(57);}
   F(0x12c)-=30.0;F(0xf8)-=F(0x100);STEP();if(I(0x144)>239){F(0x12c)=0;next_sequence_block();return;}break;
  }
  case 3:F(0x11c)*=D(0.8f);F(0x120)+=D(0.1f);if(F(0x11c)<=0.01f){--I(0x330);AT(P,unsigned char,0x7a8)=0;return;}break;
  case 4:F(0x12c)-=30.0;if(AT(this,void *,0x34c)==0)RETIRE();I(0xec)=AT(AT(this,void *,0x34c),int,0xec);I(0xf0)=AT(AT(this,void *,0x34c),int,0xf0);if(AT(AT(this,void *,0x34c),short,0x13e)!=2)RETIRE();break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(2)){PACKET(p96,0,0,4);spawn_parented(851,F(0xec),F(0xf0),B(0x104),-1,reinterpret_cast<const unsigned *>(p96),3);I(0x144)=0;}return;
 case 855:
  if(AT(P,short,0x174)<1 && (S(0x13e)==0 || S(0x13e)==3))RETIRE();
  switch(S(0x13e)) {
  case 0:
   MOVE();if(I(0x144)%2==0){PACKET(p168,RND(360),RND(30)*D(0.1f)+2.0,1);SPAWN(855,1,p168);}
   if(F(0xec)>=g_update_right && H[0]==0.0){PACKET(p360,90,6,3);p360[3]=1;spawn_unparented(855,g_update_right,F(0xf0),1,1,reinterpret_cast<const unsigned *>(p360),4);p360[0]=-90;spawn_unparented(855,g_update_right,F(0xf0),1,1,reinterpret_cast<const unsigned *>(p360),4);RETIRE();}
   if(F(0xec)<=g_update_left && H[0]==180.0f){PACKET(p344,90,6,3);p344[3]=-1;spawn_unparented(855,g_update_left,F(0xf0),1,1,reinterpret_cast<const unsigned *>(p344),4);p344[0]=-90;spawn_unparented(855,g_update_left,F(0xf0),1,1,reinterpret_cast<const unsigned *>(p344),4);RETIRE();}
   if(F(0xf0)>=g_update_top && H[0]==-90.0f){PACKET(p328,0,6,3);p328[3]=2;spawn_unparented(855,F(0xec),g_update_top,1,1,reinterpret_cast<const unsigned *>(p328),4);p328[0]=180;spawn_unparented(855,F(0xec),g_update_top,1,1,reinterpret_cast<const unsigned *>(p328),4);RETIRE();}
   if(F(0xf0)<=0.0 && H[0]==90.0f){PACKET(p376,0,6,3);p376[3]=-2;spawn_unparented(855,F(0xec),0,1,1,reinterpret_cast<const unsigned *>(p376),4);p376[0]=180;spawn_unparented(855,F(0xec),0,1,1,reinterpret_cast<const unsigned *>(p376),4);RETIRE();}STEP();break;
  case 1:H[1]*=D(0.98f);MOVE();SCALE(F(0x11c)*D(0.99f));FADE(8,8);STEP();break;
  case 3:
   if(I(0x144)>239)RETIRE();if(I(0x144)%5==0){PACKET(p48,RND(360),RND(50)*D(0.1f)+3.0,1);SPAWN(855,1,p48);}STEP();
   if(I(0x144)%5==0){if(H[3]==-2.0f)p532[0]=0;if(H[3]==2.0f)p532[0]=180;if(H[3]==-1.0f)p532[0]=90;if(H[3]==1.0)p532[0]=-90;p532[1]=0;p532[2]=4;SPAWN(855,1,p532);}
   if(H[3]==-2.0f){F(0xf0)=0;if(F(0xec)>=g_update_right && F(0xf4)>0.0){F(0xec)=g_update_right;F(0xf4)=-F(0xf4);B(0x184)=1;I(0x180)=0;}if(F(0xec)<=g_update_left && F(0xf4)<0.0){F(0xec)=g_update_left;F(0xf4)=-F(0xf4);B(0x184)=1;I(0x180)=0;}}
   if(H[3]==2.0f){F(0xf0)=g_update_top;if(F(0xec)>=g_update_right && F(0xf4)>0.0){F(0xec)=g_update_right;F(0xf4)=-F(0xf4);B(0x184)=1;I(0x180)=0;}if(F(0xec)<=g_update_left && F(0xf4)<0.0){F(0xec)=g_update_left;F(0xf4)=-F(0xf4);B(0x184)=1;I(0x180)=0;}}
   if(H[3]==1.0){F(0xec)=g_update_right;if(F(0xf0)>=g_update_top && F(0xf8)>0.0){F(0xf0)=g_update_top;F(0xf8)=-F(0xf8);B(0x184)=1;I(0x180)=0;}if(F(0xf0)<=0.0 && F(0xf8)<0.0){F(0xf0)=0;F(0xf8)=-F(0xf8);B(0x184)=1;I(0x180)=0;}}
   if(H[3]==-1.0f){F(0xec)=g_update_left;if(F(0xf0)>=g_update_top && F(0xf8)>0.0){F(0xf0)=g_update_top;F(0xf8)=-F(0xf8);B(0x184)=1;I(0x180)=0;}if(F(0xf0)<=0.0 && F(0xf8)<0.0){F(0xf0)=0;F(0xf8)=-F(0xf8);B(0x184)=1;I(0x180)=0;}}break;
  case 4:F(0x11c)+=D(0.025f);F(0x120)*=D(0.95f);FADE(15,15);{float *heading=H;if(heading[0]==0.0)F(0xf0)=0;if(heading[0]==180.0f)F(0xf0)=g_update_top;if(heading[0]==-90.0f)F(0xec)=g_update_right;if(heading[0]==90.0f)F(0xec)=g_update_left;}break;
  }break;
 case 856:
  if(S(0x13e)==0){if(AT(P,short,0x13c)==606 || AT(P,short,0x13c)==656){
    B(0x104)=AT(A,float,0xec)-F(0xec)<=0.0?-1:1;
    if(AT(P,short,0x13e)==2 && S(0x364)==0 && (++S(0x366),H[1]+H[1]<=static_cast<float>(S(0x366)))){PACKET(p520,RND(14)-7.0,RND(15)+60.0,1);SPAWN(856,1,p520);p520[2]=2;SPAWN(856,1,p520);P->dispatch_character_wave_handle(2);S(0x364)=1;}
   }else S(0x364)=1;
   if(S(0x364)==1){SCALE(F(0x11c)*D(0.95f));FADE(6,6);}else{F(0x120)=F(0x370)*(1.0-F(0x374));F(0x374)*=D(0.95f);if(I(0x144)>14){F(0x11c)=F(0x370)*(1.0-F(0x378));F(0x378)*=D(0.95f);}}
  }else if(S(0x13e)==1){if(S(0x364)==0){if(I(0x144)>19)release_auxiliary();if(AT(P,short,0x174)<1)S(0x364)=1;}else{release_auxiliary();F(0x120)*=D(0.9f);F(0x11c)+=D(0.05f);FADE(10,10);}if(OUTSIDE(1480.0f,-200.0,1100.0f,-150.0f))RETIRE();STEP();}
  else if(S(0x13e)==2){SCALE(F(0x370)+F(0x11c));F(0x370)*=D(0.9f);FADE(10,10);}break;
 case 857:
  switch(S(0x13e)) {
  case 0:
   F(0x12c)+=3.0;if(I(0x144)>79){SCALE(F(0x11c)+D(0.2f));COLORFADE(25,25);}else{
    if(I(0x144)%6==0){PACKET(p288,F(0x12c),F(0x11c),3);SPAWN(857,1,p288);}
    if(I(0x144)==40 || I(0x144)==45 || I(0x144)==50){PACKET(p412,RND(360),80.0-static_cast<float>(I(0x144)),1);unsigned packet_face=B(0x104);spawn_unparented(857,C(0x104)*lookup_orientation_cosine_quantized_abs(180.0f-p412[0])*1280.0+F(0xec),lookup_orientation_sine_quantized_abs(180.0f-p412[0])*1280.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p412),3);P->dispatch_character_wave_handle(22);}
    SCALE(1.0-F(0x370));F(0x370)*=D(0.9f);if(AT(P,short,0x174)<1)RETIRE();
   }break;
  case 1: {
   if(AT(P,short,0x174)<1)RETIRE();float width=static_cast<float>(18.0-F(0x370));F(0x11c)=width+width;F(0x120)*=D(0.95f);F(0x370)*=D(0.8f);
   if(B(0x111)<3){B(0x112)=0;B(0x111)=0;}else{B(0x112)-=3;B(0x111)-=3;}if(H[1]==static_cast<float>(I(0x144))){PACKET(p276,H[0],80,2);SPAWN(857,1,p276);}if(F(0x120)<=D(0.005f))RETIRE();break;
  }
  case 2:if(AT(P,short,0x174)<1){I(0x144)=40;B(0x184)=0;}MOVE();F(0x11c)+=0.75;if(F(0x11c)>=36.0f)F(0x11c)=36;F(0x120)*=D(0.98f);if(I(0x144)>39){B(0x184)=0;COLORFADE(5,5);}STEP();break;
  case 3:F(0x12c)-=3.0;SCALE(F(0x11c)+D(0.1f));COLORFADE(10,10);break;
  case 5:F(0x12c)-=6.0;SCALE(F(0x11c)+D(0.15f));COLORFADE(20,20);break;
  }break;
 case 865:
  if(S(0x13e)==0){if(S(0x364)==0){SCALE(F(0x370)+F(0x11c));F(0x370)*=D(0.8f);if(F(0x370)<=0.01f)F(0x370)=0;
    if(I(0x144)==4){PACKET(p252,0,0,1);spawn_unparented(865,F(0xec),0,B(0x104),-1,reinterpret_cast<const unsigned *>(p252),3);P->dispatch_character_wave_handle(55);P->dispatch_character_wave_handle(54);}
    if(I(0x144)==40){PACKET(p228,0,0,1);spawn_unparented(865,F(0xec),0,B(0x104),-1,reinterpret_cast<const unsigned *>(p228),3);}
    if(I(0x144)==76){PACKET(p204,0,0,1);spawn_unparented(865,F(0xec),0,B(0x104),-1,reinterpret_cast<const unsigned *>(p204),3);}
    if(I(0x144)==112){PACKET(p180,0,0,1);spawn_unparented(865,F(0xec),0,B(0x104),-1,reinterpret_cast<const unsigned *>(p180),3);}
   }else{F(0x11c)*=D(0.85f);F(0x120)+=D(0.1f);if(F(0x11c)<=0.01f)RETIRE();}if(AT(P,short,0x13c)!=615 || AT(P,short,0x140)>7)S(0x364)=1;
  }else if(S(0x13e)==1){F(0xf4)=30;int mod=I(0x144)%60;if(mod==0 || mod==10)P->publish_layout_scalar(4);if(F(0xec)>=2280.0f || F(0xec)<-1000.0)RETIRE();STEP();}break;
 case 899:
  switch(S(0x13e)) {
  case 0:F(0x11c)+=F(0x370);F(0x370)*=D(0.9f);if(I(0x144)>=60){P->release_auxiliary();FADE(5,5);}break;
  case 1:I(0xec)=AT(P,int,0xec);break;
  case 2:I(0xec)=AT(P,int,0xec);if(AT(P,short,0x13c)!=794 || AT(P,short,0x13e)==1){next_sequence_block();return;}break;
  case 4:F(0x12c)+=F(0x370);F(0x370)*=D(0.95f);SCALE(F(0x11c)+H[1]);H[1]*=D(0.95f);FADE(5,5);break;
  case 5:F(0xf8)-=D(0.3f);if(F(0xf8)<-5.0f)F(0xf8)=-5;if(F(0xf0)<=-230.0)RETIRE();F(0xf0)+=F(0xf8);break;
  }
  if(advance_frame())--I(0x330);if(ENTRY(4))--I(0x330);return;
 case 900:
  if(S(0x13e)==0){float *heading=H;F(0xec)=static_cast<float>(lookup_orientation_cosine_quantized_abs(-heading[0]))*heading[1]+F(0x370);F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(-heading[0]))*H[1]+F(0x374);
   if(S(0x364)!=0){B(0x184)=0;SCALE(F(0x11c)*D(0.9f));FADE(10,10);}
   else{advance_six(0);advance_phase(0);heading=H;heading[1]+=F(0x378);heading[0]+=C(0x104)*2;if(I(0x180)!=0 && ++S(0x366)>14){S(0x366)=0;I(0x180)=0;B(0x184)=1;}if(!(AT(P,short,0x174)>0 && !(H[1]>=1280.0f))){S(0x364)=1;B(0x184)=0;SCALE(4);}}
  }else if(S(0x13e)==1){float *heading=H;F(0xec)=static_cast<float>(lookup_orientation_cosine_quantized_abs(-heading[0]))*heading[1]+F(0x370);F(0xf0)=static_cast<float>(lookup_orientation_sine_quantized_abs(-heading[0]))*H[1]+F(0x374);
   if(S(0x364)!=0){B(0x184)=0;SCALE(F(0x11c)*D(0.9f));FADE(10,10);}
   else{advance_six(0);advance_phase(0);heading=H;heading[0]+=C(0x104)*2;heading[1]+=F(0x378);F(0x378)-=D(0.2f);if(F(0x378)<0.0)F(0x378)=0;if(F(0x378)==0.0 && ++S(0x36a)>39){S(0x36a)=0;F(0x378)=10;}if(I(0x180)!=0 && ++S(0x366)>14){S(0x366)=0;I(0x180)=0;B(0x184)=1;}if(!(AT(P,short,0x174)>0 && !(H[1]>=1280.0f))){S(0x364)=1;B(0x184)=0;SCALE(4);}}
  }
  if(advance_frame())--I(0x330);if(ENTRY(4))--I(0x330);return;
 case 910:
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x186)==0)F(0x12c)+=20.0;
   if(AT(this,void *,0x34c)!=0){void *related=AT(this,void *,0x34c);F(0xec)=C(0x104)*AT(related,float,0xf4)+AT(related,float,0xec);F(0xf0)=AT(related,float,0xf0)+130.0f+AT(related,float,0xf8);}
   else{release_auxiliary();F(0xec)=C(0x104)*AT(P,float,0xf4)+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+130.0f+AT(P,float,0xf8);if(AT(P,short,0x13c)!=720 && AT(P,short,0x13c)!=721)RETIRE();if(AT(P,short,0x13e)==3)FADE(20,20);}break;
  case 1:case 6:if(AT(P,short,0x13c)==720 || AT(P,short,0x13c)==721){I(0xec)=AT(P,int,0xec);F(0xf0)=AT(P,float,0xf0);}break;
  case 2:I(0xec)=AT(P,int,0xec);I(0xf0)=AT(P,int,0xf0);if((AT(P,short,0x13c)!=720 && AT(P,short,0x13c)!=721) || AT(P,short,0x13e)!=0){next_sequence_block();return;}break;
  case 4:F(0x12c)+=F(0x370);F(0x370)*=D(0.95f);SCALE(F(0x11c)+H[1]);H[1]*=D(0.95f);FADE(5,5);break;
  case 5:F(0xf8)=-20;I(0xec)=AT(P,int,0xec);if(F(0xf0)<=AT(P,float,0xf0)-230.0)RETIRE();F(0xf0)+=F(0xf8);break;
  case 7:
   if(AT(P,short,0x13c)==720 || AT(P,short,0x13c)==721){I(0xec)=AT(P,int,0xec);I(0xf0)=AT(P,int,0xf0);}
   if((AT(P,short,0x13c)!=720 && AT(P,short,0x13c)!=721) || AT(P,short,0x13e)>1){next_sequence_block();return;}break;
  case 9:
   I(0xec)=AT(P,int,0xec);F(0xf8)-=D(0.3f);F(0x12c)-=40.0;X(float,0xec)=stage_surface_height();F(0x370)+=F(0xf8);F(0xf0)=F(0x370)+AT(P,float,0xf0);AT(P,int,0x12c)=I(0x12c);
   if(F(0x370)>=0.0){P->select_sequence(2);AT(P,int,0xec)=I(0xec);AT(P,int,0xf0)=I(0xf0);AT(P,int,0xf8)=I(0xf8);AT(P,float,0x100)=0.3f;RETIRE();}break;
  case 10:
   I(0xec)=AT(P,int,0xec);F(0xf0)=AT(P,float,0xf0)+F(0x370);X(int,0xe8)=I(0xec);X(int,0xec)=AT(P,int,0xf0);F(0x370)+=20.0;if(F(0x370)>-115.0)F(0x370)=-115;if(AT(P,short,0x186)==0)F(0x12c)-=40.0;
   if(AT(P,short,0x13c)!=721)RETIRE();if(AT(P,short,0x13e)==1 && AT(P,short,0x140)==2){next_sequence_block();F(0xf8)=17.5f;}
   if(AT(P,short,0x13e)==1 && AT(P,short,0x140)==1){
    if(g_match_identifier==1){if(I(0x144)%6==0){PACKET(p592,-50.0-RND(50),RND(50)*D(0.1f)+5.0,12);spawn_unparented(910,C(0x104)*150+F(0xec),AT(P,float,0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p592),3);}}
    else if(g_match_identifier==2){if(I(0x144)%4==0){PACKET(p592,-50.0-RND(50),RND(80)*D(0.1f)+8.0,12);spawn_unparented(910,C(0x104)*150+F(0xec),AT(P,float,0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p592),3);}}
    else if(g_match_identifier==3){if(I(0x144)%2==0){PACKET(p592,-50.0-RND(50),RND(100)*D(0.1f)+10.0,12);spawn_unparented(910,C(0x104)*150+F(0xec),AT(P,float,0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p592),3);}}
   }break;
  case 11:
   if(AT(P,short,0x13c)!=721)RETIRE();I(0xec)=AT(P,int,0xec);X(int,0xe8)=I(0xec);F(0xf8)-=0.5;F(0x12c)-=40.0;F(0x370)+=F(0xf8);F(0xf0)=F(0x370)+AT(P,float,0xf0);AT(P,int,0x12c)=I(0x12c);
   if(F(0x370)>=0.0){P->select_sequence(2);AT(P,int,0xec)=I(0xec);AT(P,int,0xf0)=I(0xf0);AT(P,int,0xf8)=I(0xf8);AT(P,float,0x100)=1;RETIRE();}break;
  case 12:
   if(S(0x364)!=0)goto yukari910_fade;
   if(I(0x180)!=0 || AT(P,short,0x174)<1 || (F(0xf0)<=0.0 && F(0xf8)<0.0)){SCALE(3);S(0x364)=1;}
   F(0xf8)-=D(0.15f);STEP();goto yukari910_bounds;
  case 13:F(0xf8)-=D(0.15f);STEP();
 yukari910_fade:SCALE(F(0x11c)*D(0.9f));COLORFADE(10,10);
 yukari910_bounds:if(F(0xec)<-50.0 || F(0xec)>1330.0f)RETIRE();break;
  }
  if(advance_frame())--I(0x330);if(I(0x144)!=0)return;if(ENTRY(4))RETIRE();if(ENTRY(9))--I(0x330);return;
 case 920:
  if(S(0x13e)==0){if(I(0x144)<60){F(0x120)=F(0x370)*(1.0-F(0x374));F(0x374)*=D(0.95f);if(I(0x144)>14){F(0x11c)=F(0x370)*(1.0-F(0x378));F(0x378)*=D(0.95f);}}
   else{B(0x104)=AT(A,float,0xec)-F(0xec)<=0.0?-1:1;if(I(0x144)==60){PACKET(p400,0,RND(10)+30.0,1);SPAWN(920,1,p400);p400[2]=2;SPAWN(920,1,p400);P->dispatch_character_wave_handle(2);}SCALE(F(0x11c)*D(0.95f));FADE(6,6);}
  }else if(S(0x13e)==1){if(S(0x364)==0){if(I(0x144)>19)release_auxiliary();if(AT(P,short,0x174)<1)S(0x364)=1;}else{release_auxiliary();F(0x120)*=D(0.9f);F(0x11c)+=D(0.05f);FADE(10,10);}if(OUTSIDE(1480.0f,-200.0,1100.0f,-150.0f))RETIRE();STEP();}
  else if(S(0x13e)==2){SCALE(F(0x370)+F(0x11c));F(0x370)*=D(0.9f);FADE(10,10);}break;
 case 930:
  switch(S(0x13e)) {
  case 0:
   F(0x12c)+=3.0;if(I(0x144)>79){SCALE(F(0x11c)+D(0.2f));COLORFADE(25,25);}else{
    if(I(0x144)%6==0){PACKET(p156,F(0x12c),F(0x11c),3);SPAWN(930,1,p156);}
    switch(g_match_identifier){
    case 0:if(I(0x144)==50){PACKET(p472,RND(360),80.0-static_cast<float>(I(0x144)),1);unsigned packet_face=B(0x104);spawn_unparented(930,C(0x104)*lookup_orientation_cosine_quantized_abs(180.0f-p472[0])*1280.0+F(0xec),lookup_orientation_sine_quantized_abs(180.0f-p472[0])*1280.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p472),3);P->dispatch_character_wave_handle(22);}break;
    case 1:if(I(0x144)==45 || I(0x144)==50){PACKET(p496,RND(360),80.0-static_cast<float>(I(0x144)),1);unsigned packet_face=B(0x104);spawn_unparented(930,C(0x104)*lookup_orientation_cosine_quantized_abs(180.0f-p496[0])*1280.0+F(0xec),lookup_orientation_sine_quantized_abs(180.0f-p496[0])*1280.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p496),3);P->dispatch_character_wave_handle(22);}break;
    case 2:if(I(0x144)==40 || I(0x144)==45 || I(0x144)==50){PACKET(p508,RND(360),80.0-static_cast<float>(I(0x144)),1);unsigned packet_face=B(0x104);spawn_unparented(930,C(0x104)*lookup_orientation_cosine_quantized_abs(180.0f-p508[0])*1280.0+F(0xec),lookup_orientation_sine_quantized_abs(180.0f-p508[0])*1280.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p508),3);P->dispatch_character_wave_handle(22);}break;
    case 3:if(I(0x144)==40 || I(0x144)==45 || I(0x144)==50){PACKET(p424,RND(360),80.0-static_cast<float>(I(0x144)),1);unsigned packet_face=B(0x104);spawn_unparented(930,C(0x104)*lookup_orientation_cosine_quantized_abs(180.0f-p424[0])*1280.0+F(0xec),lookup_orientation_sine_quantized_abs(180.0f-p424[0])*1280.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p424),3);P->dispatch_character_wave_handle(22);}break;
    }
    SCALE(1.0-F(0x370));F(0x370)*=D(0.9f);if(AT(P,short,0x174)<1)RETIRE();
   }break;
  case 1: {
   if(AT(P,short,0x174)<1)RETIRE();float width=static_cast<float>(18.0-F(0x370));F(0x11c)=width+width;F(0x120)*=D(0.95f);F(0x370)*=D(0.8f);if(B(0x111)<3){B(0x112)=0;B(0x111)=0;}else{B(0x112)-=3;B(0x111)-=3;}if(H[1]==static_cast<float>(I(0x144))){PACKET(p132,H[0],80,2);SPAWN(930,1,p132);}if(F(0x120)<=D(0.005f))RETIRE();break;
  }
  case 2:if(AT(P,short,0x174)<1){I(0x144)=40;B(0x184)=0;}MOVE();F(0x11c)+=0.75;F(0x120)*=D(0.98f);if(I(0x144)>39){B(0x184)=0;COLORFADE(5,5);}STEP();break;
  case 3:F(0x12c)-=3.0;SCALE(F(0x11c)+D(0.1f));COLORFADE(10,10);break;
  case 4:
   F(0x12c)+=3.0;if(I(0x144)>79){SCALE(F(0x11c)+D(0.2f));COLORFADE(25,25);}else{if(emit_repeated(0,2,5))RETIRE();if(I(0x144)%6==0){PACKET(p108,F(0x12c),F(0x11c),3);SPAWN(812,1,p108);}
    if(I(0x144)==40 || I(0x144)==45 || I(0x144)==50 || I(0x144)==55 || I(0x144)==60){PACKET(p388,RND(360),80.0-static_cast<float>(I(0x144)),1);unsigned packet_face=B(0x104);spawn_unparented(812,C(0x104)*lookup_orientation_cosine_quantized_abs(180.0f-p388[0])*1280.0+F(0xec),lookup_orientation_sine_quantized_abs(180.0f-p388[0])*1280.0+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p388),3);P->dispatch_character_wave_handle(22);}
    SCALE(1.0-F(0x370));F(0x370)*=D(0.9f);if(emit_repeated(0,2,5))RETIRE();
   }break;
  case 5:F(0x12c)-=6.0;SCALE(F(0x11c)+D(0.15f));COLORFADE(20,20);break;
  }break;
 case 940:
  switch(S(0x13e)) {
  case 1:
   if(S(0x364)==0){if(AT(P,short,0x174)<1){S(0x364)=1;return;}F(0x11c)=(1.0-F(0x370))*15.0;F(0x370)*=D(0.95f);F(0x12c)=(1.0-F(0x374))*360.0+H[0];F(0x374)*=D(0.92f);
    if(I(0x144)>59){if(F(0x120)<2.0f)F(0x120)+=D(0.05f);if(F(0x120)>=2.0f){S(0x364)=0;F(0x120)=2;next_sequence_block();B(0x184)=1;return;}}
   }else{B(0x184)=0;F(0x120)*=D(0.9f);COLORFADE(5,5);}break;
  case 2:
   advance_six(0);advance_phase(0);if(S(0x364)!=0){B(0x184)=0;F(0x120)*=D(0.9f);COLORFADE(5,5);break;}
   if(AT(P,short,0x174)<1){S(0x364)=1;return;}
   {int counter=I(0x144);if(counter>29){int interval;switch(g_match_identifier){case 0:interval=20;break;case 1:interval=10;break;case 2:interval=8;break;case 3:interval=6;break;}
     if(counter%interval==0){float radius=static_cast<float>(counter-20)*10.0;if(radius<=1480.0f){P->dispatch_character_wave_handle(2);
       PACKET(p580,F(0x12c)+90.0+H[1]*0.5,3,3);unsigned packet_face=B(0x104);spawn_unparented(940,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x12c)))*radius+F(0xec),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x12c)))*radius+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p580),3);
       p580[0]=(F(0x12c)-90.0)-H[1]*0.5;packet_face=B(0x104);spawn_unparented(940,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x12c)))*radius+F(0xec),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x12c)))*radius+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p580),3);
       PACKET(p580,0,0,4);packet_face=B(0x104);spawn_unparented(940,static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x12c)))*radius+F(0xec),static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x12c)))*radius+F(0xf0),packet_face,1,reinterpret_cast<const unsigned *>(p580),3);
     }}if(I(0x144)>89)S(0x364)=1;
   }}break;
  case 3:F(0x11c)+=D(0.01f);if(I(0x180)!=0 || F(0xf0)<=0.0 || AT(P,short,0x174)<1){SCALE(2);select_sequence(4);return;}STEP();if(OUTSIDE(1480.0f,-200.0,1100.0f,-150.0f))RETIRE();break;
  case 4:SCALE(F(0x11c)*D(0.9f));COLORFADE(10,10);break;
  case 5:SCALE(F(0x11c)+D(0.2f));COLORFADE(10,10);break;
  }break;
 case 980:update_ping_pong_motion();break;
 case 981:
  if(S(0x13e)==0 || S(0x13e)==1){short owner_action=AT(P,short,0x13c);if((owner_action==199 || owner_action==198 || owner_action==197) && AT(P,short,0x140)<9){I(0xec)=AT(P,int,0xec);I(0xf0)=AT(P,int,0xf0);}if(S(0x13e)==1 && (AT(P,short,0x13c)==199 || AT(P,short,0x13c)==198 || AT(P,short,0x13c)==197) && AT(P,short,0x140)>8){next_sequence_block();return;}}
  if(S(0x13e)==3 || S(0x13e)==4){short owner_action=AT(P,short,0x13c);if((owner_action==199 || owner_action==198 || owner_action==197) && AT(P,short,0x140)>9 && AT(P,short,0x140)<23){I(0xec)=AT(P,int,0xec);F(0xf0)=AT(P,float,0xf0)+228.0;}if(S(0x13e)==4 && (AT(P,short,0x13c)==199 || AT(P,short,0x13c)==198 || AT(P,short,0x13c)==197) && AT(P,short,0x140)>21){next_sequence_block();return;}}
  if(S(0x13e)==6){F(0x12c)+=F(0x370);F(0x370)*=D(0.95f);SCALE(F(0x11c)+H[1]);H[1]*=D(0.95f);FADE(5,5);}
  if(advance_frame())--I(0x330);if(ENTRY(3))RETIRE();if(ENTRY(6))--I(0x330);return;
 case 998:
  F(0x12c)+=H[0];if(S(0x13e)==0){if(AT(P,short,0x13c)>153 && AT(P,short,0x13c)<158){F(0xec)=C(0x104)*60+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+80.0;}
   if(AT(P,short,0x13c)>149 && AT(P,short,0x13c)<154){F(0xec)=C(0x104)*80+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+130.0;}
   if(AT(P,short,0x13c)==158){F(0xec)=C(0x104)*75+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+140.0;}
   if(AT(P,short,0x13c)<150 || AT(P,short,0x13c)>158){next_sequence_block();AT(P,unsigned char,0x751)=0;}
  }if(S(0x13e)==1)FADE(10,10);break;
 case 999:
  B(0x113)=AT(P,unsigned char,0x113);if(S(0x13e)==0)I(0xf0)=AT(P,int,0xf0);if(S(0x13e)<3)I(0xec)=AT(P,int,0xec);AT(P,short,0x7a4)=1;
  if(AT(P,short,0x13e)==0){short owner_action=AT(P,short,0x13c);if(AT(P,short,0x140)==0 && ((owner_action>69 && owner_action<89) || owner_action==181 || owner_action==180 || owner_action==145)){--I(0x330);AT(P,short,0x7a4)=0;return;}
   if(AT(P,short,0x140)==0 && AT(P,short,0x13c)>99 && AT(P,short,0x13c)<112){--I(0x330);AT(P,short,0x7a4)=0;return;}
  }
  if(S(0x13e)==0 && (AT(P,short,0x13c)==96 || AT(P,short,0x13c)==97) && AT(P,short,0x13e)==3){next_sequence_block();F(0x12c)=0;return;}
  if((S(0x13e)==1 || S(0x13e)==2) && (AT(P,short,0x13c)==199 || AT(P,short,0x13c)==198 || AT(P,short,0x13c)==197 || AT(P,short,0x13c)==796 || AT(P,short,0x13c)==771) && AT(P,short,0x13e)==0 && AT(P,short,0x140)==1){select_sequence(3);return;}
  if(S(0x13e)==0)F(0x12c)-=35.0;if(advance_frame()){--I(0x330);AT(P,short,0x7a4)=0;}return;
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
#undef AUX
#undef X
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
