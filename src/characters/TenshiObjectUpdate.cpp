// Complete manual JP1.06a64CD50 source hypothesis; not canonically exact.
// Evidence: docs/TENSHI_OBJECT_UPDATE_2026_10_25.md.
#include "TenshiObjectUpdate.hpp"
#include <math.h>
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define I(o) AT(this,int,o)
#define H AT(this,float *,0x340)
#define P AT(this,TenshiObjectUpdateView *,0x348)
#define A AT(this,TenshiObjectUpdateView *,0x170)
#define T AT(this,TenshiObjectUpdateView *,0x34c)
#define AUX AT(this,void *,0x154)
#define MOTION reinterpret_cast<TenshiUpdateMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define D(v) static_cast<double>(v)
#define RND(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
#define RETIRE() do{--I(0x330);return;}while(0)
#define MOVE() MOTION->set_components(H[0],H[1])
#define STEP() do{F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8);}while(0)
#define SCALE(v) F(0x120)=F(0x11c)=static_cast<float>(v)
#define FADE(t,d) do{if(B(0x113)<t)RETIRE();B(0x113)-=d;}while(0)
#define ENTRY(n) (I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==n)
#define OUTSIDE(xh,xl,yh,yl) (F(0xec)>xh || F(0xec)<xl || F(0xf0)>yh || F(0xf0)<yl)
#define PACKET(p,a,b,c) do{p[0]=a;p[1]=b;p[2]=c;}while(0)
#define SPAWN(a,l,p) spawn_unparented(a,F(0xec),F(0xf0),B(0x104),l,reinterpret_cast<const unsigned *>(p),3)
void TenshiObjectUpdateView::update_action_state()
{
 float p12[3],p24[3],p36[3],p48[3],p60[3],p72[3],p84[3],p96[3],p108[3],p120[3],p132[3],p144[3],p156[3],p168[3],p180[3],p192[3],p204[3],p216[3],p228[3],p244[4],p256[3],p268[3],p280[3],p292[3],p304[3],p316[3],p328[3],p340[3],p352[3],p364[3],p384[5],p396[3],p408[3],p420[3],p432[3],p444[3],p456[3],p468[3],p480[3],p492[3],p504[3],p520[4],p532[3],p544[3],p556[3],p568[3],p584[3],p596[3],p608[3],p620[3],p632[3],p644[3],p656[3];
 switch(S(0x13c)) {
 case 800:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,1,4))RETIRE();MOVE();F(0x12c)=H[0];if(I(0x180)!=0){next_sequence_block();float vx=RND(50)*D(0.1f);F(0xf4)=-vx-2.0;float vy=RND(50)*D(0.1f);F(0xf8)=vy+4.0;return;}STEP();break;
  case 1:F(0xf8)-=D(0.4f);F(0x12c)+=12.0;FADE(11,10);STEP();break;
  case 2:SCALE(F(0x11c)-D(0.005f));if(S(0x140)>0){FADE(21,20);B(0x112)-=20;B(0x111)-=20;}break;
  case 3:
   F(0x370)+=6.0;if(F(0x370)>90.0f)F(0x370)=90;SCALE((lookup_orientation_cosine_quantized_abs(F(0x370))*D(0.2f)+D(0.01f))+F(0x11c));FADE(11,10);B(0x112)-=10;B(0x111)-=10;break;
  case 4:
   if(emit_repeated(0,2,5))RETIRE();MOVE();H[1]+=2.0;if(H[1]>=17.5f)H[1]=17.5f;F(0x12c)=H[0];
   if(I(0x180)!=0){advance_six(15);if(C(0x184)>0){H[1]=3;if(S(0x364)>4){S(0x364)=0;I(0x180)=0;if(C(0x184)<4){short frame=S(0x140);next_sequence_block();set_sequence_frame(frame);return;}}++S(0x364);}else{FADE(10,10);H[1]=1;}}
   STEP();break;
  case 5:
   if(emit_repeated(0,2,5))RETIRE();MOVE();H[1]+=2.0;if(H[1]>=17.5f)H[1]=17.5f;F(0x12c)=H[0];
   if(I(0x180)!=0){advance_six(15);if(C(0x184)<1){FADE(10,10);H[1]=1;}else{H[1]=3;if(S(0x364)>4){S(0x364)=0;I(0x180)=0;}++S(0x364);}}
   STEP();break;
  }
  if(F(0xec)>1380.0f || F(0xec)<-100.0 || F(0xf0)>1260.0f || F(0xf0)<-200.0)RETIRE();break;
 case 801:
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,0,5))RETIRE();advance_six(5);
   if(C(0x184)<1){PACKET(p456,0,0,1);SPAWN(801,1,p456);p456[2]=2;SPAWN(801,1,p456);p456[2]=3;int count=6;do{p456[0]=RND(360);p456[1]=RND(10)+5.0;SPAWN(801,1,p456);}while(--count!=0);RETIRE();}
   if(OUTSIDE(1380.0f,-100.0,960.0,-200.0))RETIRE();break;
  case 1:SCALE(F(0x11c)+D(0.1f));FADE(15,15);B(0x111)-=15;B(0x110)-=15;break;
  case 2:SCALE(F(0x11c)*D(0.85f));FADE(15,15);B(0x111)-=15;B(0x110)-=15;break;
  case 3:H[1]*=D(0.95f);MOVE();if(I(0x144)>19){FADE(10,10);B(0x111)-=10;B(0x110)-=10;}break;
  case 4:
   if(S(0x364)==0){short owner_action=AT(P,short,0x13c);if(owner_action!=410 && owner_action!=411 && owner_action!=414 && owner_action!=415){S(0x364)=2;return;}MOVE();H[1]-=3.0;
    if(H[1]<0.0){H[1]=0;S(0x364)=1;float n=0;do{float heading=n*36.0+18.0;p584[0]=lookup_orientation_sine_quantized_abs(heading)*10.0;double c=lookup_orientation_cosine_quantized_abs(heading);p584[1]=c+c+20.0;p584[2]=0;
      if(!(heading<=90.0f) && !(heading>=270.0f)){unsigned char facing=B(0x104);spawn_unparented(801,(lookup_orientation_cosine_quantized_abs(-heading)*20.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(-heading)*45.0+F(0xf0),facing,1,reinterpret_cast<const unsigned *>(p584),3);}else{unsigned char facing=B(0x104);spawn_unparented(801,(lookup_orientation_cosine_quantized_abs(-heading)*20.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(-heading)*45.0+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p584),3);}
      p584[2]=2;if(!(heading<=90.0f) && !(heading>=270.0f)){unsigned char facing=B(0x104);spawn_unparented(801,(lookup_orientation_cosine_quantized_abs(-heading)*20.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(-heading)*45.0+F(0xf0),facing,1,reinterpret_cast<const unsigned *>(p584),3);}else{unsigned char facing=B(0x104);spawn_unparented(801,(lookup_orientation_cosine_quantized_abs(-heading)*20.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(-heading)*45.0+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p584),3);}n+=1.0;
     }while(n<10.0f);P->dispatch_character_wave_handle(1);return;
    }
    F(0x370)+=C(0x104)*F(0xf4);F(0x374)+=F(0xf8);F(0xec)=AT(P,float,0xec)+F(0x370);F(0xf0)=AT(P,float,0xf0)+F(0x374);
   }
   if(S(0x364)==1){short owner_action=AT(P,short,0x13c);if(owner_action!=410 && owner_action!=411 && owner_action!=414 && owner_action!=415){S(0x364)=2;return;}F(0xec)=AT(P,float,0xec)+F(0x370);F(0xf0)=AT(P,float,0xf0)+F(0x374);F(0xf4)=F(0xf8)=0;
    if((AT(P,short,0x13c)==410 || AT(P,short,0x13c)==411 || AT(P,short,0x13c)==414 || AT(P,short,0x13c)==415) && AT(P,short,0x13e)==3)S(0x364)=2;
   }if(S(0x364)==2){F(0xf4)=F(0xf8)=0;FADE(10,10);}break;
  }STEP();break;
 case 810:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   MOVE();signed char level=AT(P,signed char,0x604);int limit=20;if(level>=2)limit=25;if(level>=4)limit=35;if(I(0x144)>=limit)RETIRE();
   if(I(0x144)%5==0){
    PACKET(p644,RND(20)-75.0,20,1);double surface=stage_surface_height();unsigned char facing=B(0x104);
    spawn_unparented(810,RND(40)+F(0xec),(surface-RND(50))-25.0,facing,1,reinterpret_cast<const unsigned *>(p644),3);
    P->dispatch_character_wave_handle(10);p644[2]=6;facing=B(0x104);spawn_unparented(810,F(0xec),stage_surface_height(),facing,1,reinterpret_cast<const unsigned *>(p644),3);
    p644[1]=20;p644[2]=5;float n=0;do{p644[0]=RND(360);int layer=(p644[0]>=0.0 && p644[0]<=180.0f)?1:-1;facing=B(0x104);spawn_unparented(810,F(0xec),stage_surface_height(),facing,layer,reinterpret_cast<const unsigned *>(p644),3);n+=1.0;}while(n<5.0f);
    n=0;do{PACKET(p644,-RND(90)-45.0,RND(10)+8.0,RND(3)+2.0);facing=B(0x104);spawn_unparented(810,F(0xec),stage_surface_height(),facing,-1,reinterpret_cast<const unsigned *>(p644),3);n+=1.0;}while(n<5.0f);
   }STEP();break;
  }
  case 1:
   AT(AUX,float,0xe8)=F(0xec);AT(AUX,float,0xec)=stage_surface_height();F(0xf8)-=3.0;F(0xf4)-=0.5;if(F(0xf4)<0.25f)F(0xf4)=0.25f;if(F(0xf8)<-0.25f)F(0xf8)=-0.25f;
   if(I(0x144)>=20){if(B(0x113)>=5)B(0x113)-=5;else --I(0x330);}STEP();break;
  case 2:case 3:case 4:F(0x12c)+=F(0x374);F(0xf8)-=0.25;FADE(15,15);STEP();break;
  case 5:
   MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 6:if(I(0x144)>=3)RETIRE();break;
  }
  if(OUTSIDE(1380.0f,-100.0,1000.0,-100.0))RETIRE();if(advance_frame())RETIRE();return;
 case 811:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 2:case 3:case 4:
   F(0x12c)+=F(0x374);F(0xf8)-=0.25;if(F(0xf8)<0.0){double y=F(0xf0);if(y<=stage_surface_height())F(0xf8)*=-0.75;}FADE(15,15);STEP();break;
  case 5:
   MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 6:if(I(0x144)>=3)RETIRE();break;
  }
  if(OUTSIDE(1380.0f,-100.0,1000.0,-100.0))RETIRE();break;
 case 815:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   AT(AUX,float,0xe8)=F(0xec);AT(AUX,float,0xec)=stage_surface_height();F(0xf8)-=0.5;double y=F(0xf0);
   if(y<=stage_surface_height()){
    F(0xf0)=stage_surface_height();F(0xf4)=F(0xf8)=0;select_sequence(5);
    p316[1]=20;p316[2]=4;float n=0;do{p316[0]=n*45.0+RND(30);int layer=(p316[0]>=0.0 && p316[0]<=180.0f)?1:-1;unsigned char facing=B(0x104);spawn_unparented(815,F(0xec),stage_surface_height(),facing,layer,reinterpret_cast<const unsigned *>(p316),3);n+=1.0;}while(n<8.0f);
    publish_layout_scalar(10);P->dispatch_character_wave_handle(12);return;
   }STEP();break;
  }
  case 1:case 2:case 3:F(0x12c)+=F(0x374);F(0xf8)-=0.5;if(I(0x144)>=15)FADE(10,10);STEP();break;
  case 4:
   MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 5:case 6:
   AT(AUX,float,0xe8)=F(0xec);AT(AUX,float,0xec)=stage_surface_height();
   if(((AT(P,short,0x13c)==520 || AT(P,short,0x13c)==521) && AT(P,short,0x13e)==0 && AT(P,short,0x140)==0) || I(0x144)>=AT(P,signed char,0x605)*20+90){select_sequence(7);return;}STEP();break;
  case 7:AT(AUX,float,0xe8)=F(0xec);AT(AUX,float,0xec)=stage_surface_height();F(0xf8)=-1;FADE(10,10);STEP();break;
  }
  if(F(0xec)>1380.0f || F(0xec)<-100.0)RETIRE();break;
 case 816:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   if(AT(P,short,0x82e)<=0 || AT(A,short,0x174)<=0 || emit_repeated(0,0,0))S(0x364)=1;H[0]-=3.0;
   if(S(0x364)!=0){AT(P,int,0x834)=0;int count=3;do{PACKET(p444,RND(360),RND(10)+4.0,3);SPAWN(816,1,p444);}while(--count!=0);count=4;do{PACKET(p444,RND(360),RND(10)+4.0,4);SPAWN(816,1,p444);}while(--count!=0);RETIRE();}
   if(B(0x113)<=245)B(0x113)+=10;else{B(0x184)=1;B(0x113)=255;}if(I(0x180)!=0)I(0x180)=0;
   float *heading=H;F(0xec)=(lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1])*C(0x104)+AT(P,float,0xec);
   F(0xf0)=((lookup_orientation_sine_quantized_abs(-heading[0])*H[1]*F(0x370)+100.0)-F(0x374))+AT(P,float,0xf0);
   C(0x33c)=(static_cast<int>(H[0])%360<-180)?1:-1;F(0x374)*=D(0.95f);if(F(0x374)<=0.01f)F(0x374)=0;
   if(AT(P,short,0x830)==1){
    B(0x104)=AT(P,unsigned char,0x104);AT(P,short,0x830)=0;B(0x184)=1;I(0x180)=0;select_sequence(1);
    float direction=-atan2_degrees((AT(A,float,0xf0)+100.0)-F(0xf0),C(0x104)*(AT(A,float,0xec)-F(0xec)));float *h=H;h[0]=direction;if(h[0]>=45.0f)h[0]=45;if(h[0]<=-45.0f)h[0]=-45;h[1]=15;B(0x113)=255;B(0x33c)=1;--AT(P,int,0x834);return;
   }
   if(AT(P,short,0x830)==2){B(0x104)=AT(P,unsigned char,0x104);B(0x184)=1;I(0x180)=0;select_sequence(2);F(0x374)=1;F(0x378)=AT(P,float,0xec);F(0x37c)=AT(P,float,0xf0)+100.0;B(0x113)=255;B(0x33c)=1;--AT(P,int,0x834);return;}
   break;
  }
  case 1: {
   if(emit_repeated(0,2,5))RETIRE();advance_six(0);
   if(I(0x180)!=0){int count=3;do{PACKET(p396,RND(360),RND(10)+4.0,3);SPAWN(816,1,p396);}while(--count!=0);count=4;do{PACKET(p396,RND(360),RND(10)+4.0,4);SPAWN(816,1,p396);}while(--count!=0);RETIRE();}
   MOVE();STEP();if(OUTSIDE(1380.0f,-100.0,1000.0,-100.0))RETIRE();break;
  }
  case 2: {
   if(emit_repeated(0,2,5))RETIRE();H[0]-=10.0;advance_six(0);
   if(I(0x180)!=0){int count=3;do{PACKET(p408,RND(360),RND(10)+4.0,3);SPAWN(816,1,p408);}while(--count!=0);count=4;do{PACKET(p408,RND(360),RND(10)+4.0,4);SPAWN(816,1,p408);}while(--count!=0);RETIRE();}
   MOTION->set_components(0,5);float *heading=H;F(0x378)+=C(0x104)*F(0xf4);F(0x37c)+=F(0xf8);F(0x374)*=D(0.9f);F(0x370)=(1.0-F(0x374))*0.75+0.25;
   F(0xec)=(lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1])*C(0x104)+F(0x378);F(0xf0)=lookup_orientation_sine_quantized_abs(-heading[0])*H[1]*F(0x370)+F(0x37c);if(OUTSIDE(1580.0f,-300.0f,1200.0f,-300.0f))RETIRE();break;
  }
  case 3:case 4:
   F(0x12c)+=F(0x374);F(0xf8)-=0.25;if(F(0xf8)<0.0){double y=F(0xf0);if(y<=stage_surface_height())F(0xf8)*=-0.75;}FADE(10,10);STEP();break;
  }
  if(advance_frame())RETIRE();return;
 case 820:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 4:
   if(T==0){SCALE(F(0x11c)*D(0.9f));if(F(0x11c)<=D(0.1f))RETIRE();}
   else{F(0xec)=AT(T,float,0xec);F(0xf0)=AT(T,float,0xf0);if(AT(T,short,0x140)<2){if(I(0x144)%20==0){PACKET(p168,F(0x12c),0,2);spawn_parented(820,F(0xec),F(0xf0),B(0x104),B(0x33c),reinterpret_cast<const unsigned *>(p168),3);}}else{SCALE(F(0x11c)*D(0.98f));if(F(0x11c)<=0.5f){if(B(0x113)<15)RETIRE();B(0x111)-=15;B(0x110)-=15;B(0x113)-=15;}}}break;
  case 1:case 5:
   if(T==0){if(S(0x140)<2){set_sequence_frame(2);B(0x184)=0;}}
   else{F(0xec)=AT(T,float,0xec)+F(0x370);F(0xf0)=AT(T,float,0xf0)+F(0x374);if(S(0x140)==0){F(0x378)+=D(0.1f);F(0x120)=F(0x378)*F(0x37c);if(F(0x378)>=1.0){F(0x378)=1;F(0x120)=F(0x37c);next_sequence_frame();B(0x184)=1;return;}}if(S(0x140)==1)advance_six(0);}
   if(S(0x140)==2){if(B(0x111)<15){B(0x111)=B(0x110)=0;FADE(20,20);}else{B(0x111)-=15;B(0x110)-=15;}F(0x120)*=D(0.95f);if(F(0x120)<=0.01f)RETIRE();}break;
  case 2:
   if(T!=0){F(0xec)=AT(T,float,0xec);F(0xf0)=AT(T,float,0xf0);}SCALE(F(0x11c)+D(0.1f));if(B(0x111)<15){B(0x111)=B(0x110)=0;FADE(20,20);}else{B(0x111)-=15;B(0x110)-=15;}break;
  case 3:
   if(S(0x364)==0){if(AT(P,short,0x13c)!=540 && AT(P,short,0x13c)!=541){emit_repeated(0,3,5);S(0x364)=2;return;}MOVE();H[1]-=3.0;if(H[1]<0.0){H[1]=0;S(0x364)=1;return;}F(0x370)+=C(0x104)*F(0xf4);F(0x374)+=F(0xf8);F(0xec)=AT(P,float,0xec)+F(0x370);F(0xf0)=AT(P,float,0xf0)+F(0x374);}
   if(S(0x364)==1){
    if(AT(P,short,0x13c)!=540 && AT(P,short,0x13c)!=541){emit_repeated(0,3,5);S(0x364)=2;return;}
    F(0xec)=AT(P,float,0xec)+F(0x370);F(0xf0)=AT(P,float,0xf0)+F(0x374);
    if(I(0x144)%2==0 && F(0x378)<180.0f){
     PACKET(p544,lookup_orientation_sine_quantized_abs(F(0x378))*(-3.0),0,1);if(AT(P,signed char,0x606)>=4)p544[2]=5;
     if(!(F(0x378)<=90.0f)){unsigned char facing=B(0x104);spawn_parented(820,(lookup_orientation_cosine_quantized_abs(F(0x378))*20.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(F(0x378))*60.0+F(0xf0),facing,1,reinterpret_cast<const unsigned *>(p544),3);}else{unsigned char facing=B(0x104);spawn_parented(820,(lookup_orientation_cosine_quantized_abs(F(0x378))*20.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(F(0x378))*60.0+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p544),3);}
     PACKET(p544,lookup_orientation_sine_quantized_abs(F(0x378)+180.0)*(-3.0),0,1);if(AT(P,signed char,0x606)>=4)p544[2]=5;
     if(F(0x378)<=-90.0f || F(0x378)>=90.0f){unsigned char facing=B(0x104);spawn_parented(820,(lookup_orientation_cosine_quantized_abs(F(0x378)+180.0)*20.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(F(0x378)+180.0)*60.0+F(0xf0),facing,-1,reinterpret_cast<const unsigned *>(p544),3);}else{unsigned char facing=B(0x104);spawn_parented(820,(lookup_orientation_cosine_quantized_abs(F(0x378)+180.0)*20.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(F(0x378)+180.0)*60.0+F(0xf0),facing,1,reinterpret_cast<const unsigned *>(p544),3);}F(0x378)+=12.0;P->dispatch_character_wave_handle(13);
    }
   }if(S(0x364)==2)FADE(10,10);break;
  }
  if(advance_frame())RETIRE();return;
 case 821:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 1: {
   short action=AT(P,short,0x13c);
   if(action<545 || action>549){emit_repeated(0,2,5);int count=4;do{PACKET(p556,RND(360),RND(10)+4.0,4);SPAWN(821,1,p556);}while(--count!=0);count=5;do{PACKET(p556,RND(360),RND(10)+4.0,5);SPAWN(821,1,p556);}while(--count!=0);count=6;do{PACKET(p556,RND(360),RND(10)+4.0,6);SPAWN(821,1,p556);}while(--count!=0);RETIRE();}
   if(B(0x113)<=235)B(0x113)+=20;else B(0x113)=255;
   if(AT(P,short,0x13e)<2){F(0xec)=AT(P,float,0xec);F(0x370)+=F(0x374);F(0x374)*=D(0.85f);if(F(0x374)<2.0f)F(0x374)=2;F(0xf0)=(F(0x370)+100.0)*H[1]+(AT(P,float,0xf0)+100.0);}
   if(AT(P,short,0x13e)==2){F(0x370)=AT(P,float,0xec);float delta=F(0xf0)-(AT(P,float,0xf0)+100.0);F(0x374)=static_cast<float>(fabs(delta));B(0x113)=255;if(H[1]==1.0){select_sequence(2);F(0x378)=-90;return;}select_sequence(3);F(0x378)=90;return;}break;
  }
  case 2:case 3: {
   if(emit_repeated(0,2,5)){int count=4;do{PACKET(p532,RND(360),RND(10)+4.0,4);SPAWN(821,1,p532);}while(--count!=0);count=5;do{PACKET(p532,RND(360),RND(10)+4.0,5);SPAWN(821,1,p532);}while(--count!=0);count=6;do{PACKET(p532,RND(360),RND(10)+4.0,6);SPAWN(821,1,p532);}while(--count!=0);RETIRE();}
   F(0xec)=(lookup_orientation_cosine_quantized_abs(-F(0x378))*F(0x374))*C(0x104)+AT(P,float,0xec);
   F(0xf0)=lookup_orientation_sine_quantized_abs(-F(0x378))*F(0x374)+(AT(P,float,0xf0)+100.0);float delta=(AT(P,float,0xf0)+100.0)-F(0xf0);
   if(fabs(delta)<=50.0){int count=4;do{PACKET(p656,RND(360),RND(10)+4.0,4);SPAWN(821,1,p656);}while(--count!=0);count=5;do{PACKET(p656,RND(360),RND(10)+4.0,5);SPAWN(821,1,p656);}while(--count!=0);count=6;do{PACKET(p656,RND(360),RND(10)+4.0,6);SPAWN(821,1,p656);}while(--count!=0);
    if(H[1]==1.0){P->publish_layout_scalar(10);P->dispatch_character_wave_handle(15);count=8;do{PACKET(p656,RND(360),RND(10)+4.0,8);spawn_unparented(821,F(0xec),AT(P,float,0xf0)+100.0,B(0x104),1,reinterpret_cast<const unsigned *>(p656),3);}while(--count!=0);p656[2]=7;spawn_unparented(821,F(0xec),AT(P,float,0xf0)+100.0,B(0x104),1,reinterpret_cast<const unsigned *>(p656),3);}RETIRE();
   }advance_six(0);F(0x378)*=0.75;break;
  }
  case 4:case 5:case 6:F(0x12c)+=F(0x374);F(0xf8)-=0.25;if(F(0xf8)<0.0){double y=F(0xf0);if(y<=stage_surface_height())F(0xf8)*=-0.75;}FADE(10,10);STEP();break;
  case 7:SCALE(F(0x11c)+D(0.4f));FADE(10,10);break;
  case 8:MOVE();FADE(15,15);F(0x120)*=D(0.9f);F(0x11c)+=D(0.1f);STEP();break;
  }break;
 case 825:
  if(I(0x180)==5)RETIRE();if(S(0x13e)==0){H[1]*=D(0.98f);MOVE();SCALE(F(0x11c)+D(0.005f));FADE(8,8);STEP();return;}break;
 case 848:
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x13c)!=307)RETIRE();if(AT(P,short,0x186)==0){F(0x370)+=15.0;if(F(0x370)>=360.0f)F(0x370)=0;}C(0x33c)=(F(0x370)<=0.0 || F(0x370)>180.0f)?1:-1;
   if(AT(P,short,0x140)<7){F(0xec)=(lookup_orientation_cosine_quantized_abs(F(0x370))*H[1])*C(0x104)+AT(P,float,0xec);double y=lookup_orientation_sine_quantized_abs(F(0x370))*(H[1]*0.5)+(AT(P,float,0xf0)+100.0);F(0xf0)=lookup_orientation_cosine_quantized_abs(F(0x370))*H[1]*0.25+y;}
   else{F(0x11c)*=D(0.85f);F(0x120)+=D(0.1f);if(F(0x11c)<D(0.05f))RETIRE();}break;
  case 1:case 3:
   MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*D(0.15f);F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 2:
   if(S(0x364)==0){
    if(F(0x370)!=0.0){F(0x370)*=D(0.85f);if(F(0x370)<=0.01f)F(0x370)=0;}SCALE(1.0-F(0x370));short action=AT(P,short,0x13c);
    if(action==547 || action==548 || action==414 || action==415){position_relative(0,0);if(AT(P,short,0x13e)==3 && AT(P,short,0x140)>1)S(0x364)=1;}
    else if(action==404 || action==406){position_relative(0,0);if(AT(P,short,0x13e)==0 && AT(P,short,0x140)>14)S(0x364)=1;}else S(0x364)=1;
   }else{F(0x11c)+=D(0.1f);F(0x120)*=D(0.95f);FADE(11,10);}break;
  }
  if(AT(P,short,0x186)!=0)return;if(advance_frame())--I(0x330);if(ENTRY(1))--I(0x330);return;
 case 850:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0: {
   MOVE();if(I(0x144)>=80)RETIRE();
   if(I(0x144)%20==0){
    PACKET(p620,RND(20)-75.0,20,1);double surface=stage_surface_height();unsigned char facing=B(0x104);spawn_unparented(850,RND(10)+F(0xec),(surface-RND(50))-25.0,facing,1,reinterpret_cast<const unsigned *>(p620),3);
    P->dispatch_character_wave_handle(10);p620[2]=6;facing=B(0x104);spawn_unparented(850,static_cast<float>(C(0x104)*100)+F(0xec),stage_surface_height(),facing,1,reinterpret_cast<const unsigned *>(p620),3);
    p620[1]=20;p620[2]=5;float n=0;do{p620[0]=RND(360);int layer=(p620[0]>=0.0 && p620[0]<=180.0f)?1:-1;facing=B(0x104);spawn_unparented(850,F(0xec),stage_surface_height(),facing,layer,reinterpret_cast<const unsigned *>(p620),3);n+=1.0;}while(n<5.0f);
    n=0;do{PACKET(p620,-RND(90)-45.0,RND(10)+8.0,RND(3)+2.0);facing=B(0x104);spawn_unparented(850,F(0xec),stage_surface_height(),facing,-1,reinterpret_cast<const unsigned *>(p620),3);n+=1.0;}while(n<5.0f);
   }STEP();break;
  }
  case 1:
   AT(AUX,float,0xe8)=F(0xec);AT(AUX,float,0xec)=stage_surface_height();F(0xf8)-=3.0;F(0xf4)-=0.5;if(F(0xf4)<0.25f)F(0xf4)=0.25f;if(F(0xf8)<-0.25f)F(0xf8)=-0.25f;if(I(0x144)>=20){if(B(0x113)>=5)B(0x113)-=5;else --I(0x330);}STEP();break;
  case 2:case 3:case 4:F(0x12c)+=F(0x374);F(0xf8)-=0.25;FADE(15,15);STEP();break;
  case 5:MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 6:if(I(0x144)>=3)RETIRE();break;
  }
  if(OUTSIDE(1380.0f,-100.0,1000.0,-100.0))RETIRE();if(advance_frame())RETIRE();return;
 case 851:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   SCALE(F(0x11c)-D(0.005f));H[1]*=D(0.85f);FADE(5,5);B(0x111)-=5;B(0x110)-=5;if(H[1]<=D(0.1f))H[1]=0;
   if(I(0x144)==5){
    if(H[1]==0.0){PACKET(p596,0,0,1);spawn_unparented(851,F(0xec),F(0xf0),1,1,reinterpret_cast<const unsigned *>(p596),3);p596[2]=2;spawn_unparented(851,F(0xec),F(0xf0),1,1,reinterpret_cast<const unsigned *>(p596),3);p596[2]=3;spawn_unparented(851,F(0xec),F(0xf0),1,1,reinterpret_cast<const unsigned *>(p596),3);p596[2]=4;spawn_unparented(851,F(0xec),F(0xf0),1,1,reinterpret_cast<const unsigned *>(p596),3);int count=12;do{PACKET(p596,RND(360),RND(25)+10.0,5);spawn_unparented(851,F(0xec),F(0xf0),1,1,reinterpret_cast<const unsigned *>(p596),3);}while(--count!=0);}
    else{PACKET(p84,0,H[1],0);spawn_unparented(851,F(0xec),F(0xf0),1,1,reinterpret_cast<const unsigned *>(p84),3);}
   }break;
  case 1:SCALE(F(0x11c)+D(0.1f));FADE(10,10);B(0x111)-=10;B(0x110)-=10;break;
  case 2:SCALE(F(0x11c)+D(0.005f));if(I(0x144)>=30){FADE(10,10);B(0x111)-=10;B(0x110)-=10;}break;
  case 3:SCALE(F(0x11c)*D(0.99f));FADE(20,20);B(0x111)-=20;B(0x110)-=20;break;
  case 4:SCALE(F(0x11c)+D(0.2f));FADE(10,10);B(0x111)-=10;B(0x110)-=10;break;
  case 5:H[1]*=D(0.95f);MOVE();if(I(0x144)>=20){FADE(10,10);B(0x111)-=10;B(0x110)-=10;}break;
  }break;
 case 852:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 1:MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 2:MOVE();H[1]*=D(0.98f);F(0x12c)+=F(0x370);F(0x370)*=D(0.98f);SCALE(F(0x11c)+D(0.02f));FADE(5,4);STEP();break;
  case 3:SCALE(H[1]+F(0x11c));H[1]*=D(0.92f);if(H[1]<D(0.05f))H[1]=0.05f;FADE(7,6);break;
  case 4:if(AT(P,short,0x13c)!=602 || AT(P,short,0x13e)>1)RETIRE();position_relative(0,0);break;
  }
  if(OUTSIDE(1380.0f,-100.0,1000.0,-100.0))RETIRE();break;
 case 853:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x174)<=0 || AT(A,short,0x174)<=0)RETIRE();if(I(0x144)==120)P->publish_layout_scalar(3);if(I(0x144)==240){P->publish_layout_scalar(7);P->dispatch_character_wave_handle(18);}if(I(0x144)==420){P->publish_layout_scalar(10);P->dispatch_character_wave_handle(54);}
   if(I(0x144)==420 || I(0x144)==430 || I(0x144)==440 || I(0x144)==450 || I(0x144)==460 || I(0x144)==470){double y=AT(A,float,0xf0);if(A->stage_surface_height()==y){PACKET(p60,0,0,6);spawn_unparented(853,AT(A,float,0xec),0,B(0x104),1,reinterpret_cast<const unsigned *>(p60),3);}}
   if(I(0x144)==420 || I(0x144)==440 || I(0x144)==460){
    float n=0;do{PACKET(p608,RND(360),20,5);unsigned char facing=B(0x104);spawn_unparented(853,n*60.0+RND(40),20.0-RND(40),facing,1,reinterpret_cast<const unsigned *>(p608),3);n+=1.0;}while(n<22.0f);
    n=0;do{PACKET(p608,-RND(90)-45.0,RND(10)+5.0,2);unsigned char facing=B(0x104);spawn_unparented(853,n*90.0+RND(60),20.0-RND(40),facing,1,reinterpret_cast<const unsigned *>(p608),3);n+=1.0;}while(n<14.0);
    n=0;do{PACKET(p608,-RND(90)-45.0,RND(8)+4.0,3);unsigned char facing=B(0x104);spawn_unparented(853,n*120.0+RND(100),20.0-RND(40),facing,1,reinterpret_cast<const unsigned *>(p608),3);n+=1.0;}while(n<10.0f);
    n=0;do{PACKET(p608,-RND(90)-45.0,RND(6)+3.0,4);unsigned char facing=B(0x104);spawn_unparented(853,n*160.0+RND(120),20.0-RND(40),facing,1,reinterpret_cast<const unsigned *>(p608),3);n+=1.0;}while(n<8.0f);
    P->dispatch_character_wave_handle(18);P->publish_layout_scalar(10);
   }
   if(I(0x144)==480){
    double y=AT(A,float,0xf0);if(A->stage_surface_height()==y){PACKET(p36,0,0,7);spawn_unparented(853,AT(A,float,0xec),0,B(0x104),1,reinterpret_cast<const unsigned *>(p36),3);}
    float n=0;do{PACKET(p632,RND(360),20,5);unsigned char facing=B(0x104);spawn_unparented(853,n*60.0+RND(40),20.0-RND(40),facing,1,reinterpret_cast<const unsigned *>(p632),3);n+=1.0;}while(n<22.0f);
    n=0;do{PACKET(p632,-RND(90)-45.0,RND(10)+5.0,2);unsigned char facing=B(0x104);spawn_unparented(853,n*90.0+RND(60),20.0-RND(40),facing,1,reinterpret_cast<const unsigned *>(p632),3);n+=1.0;}while(n<14.0);
    n=0;do{PACKET(p632,-RND(90)-45.0,RND(8)+4.0,3);unsigned char facing=B(0x104);spawn_unparented(853,n*120.0+RND(100),20.0-RND(40),facing,1,reinterpret_cast<const unsigned *>(p632),3);n+=1.0;}while(n<10.0f);
    n=0;do{PACKET(p632,-RND(90)-45.0,RND(6)+3.0,4);float x=n*160.0+RND(120);float y=20.0-RND(40);AT(P,TenshiObjectFactoryView *,0x658)->spawn(0,AT(this,void *,0x16c),853,x,y,B(0x104),1,reinterpret_cast<const unsigned *>(p632),3);n+=1.0;}while(n<8.0f);
    P->dispatch_character_wave_handle(54);P->publish_layout_scalar(20);RETIRE();
   }break;
  case 2:case 3:case 4:F(0x12c)+=F(0x374);F(0xf8)-=0.25;if(F(0xf8)<0.0){double y=F(0xf0);if(y<=stage_surface_height())F(0xf8)*=-0.75;}FADE(15,15);STEP();break;
  case 5:MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 6:if(I(0x144)>=3)RETIRE();break;
  }
  if(OUTSIDE(1380.0f,-100.0,1000.0,-100.0))RETIRE();break;
 case 854:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:
   advance_six(0);F(0x11c)+=D(0.1f);advance_phase(10);MOVE();if(I(0x144)%5==0){PACKET(p12,H[0],0,2);SPAWN(854,1,p12);}
   if(I(0x180)==0){F(0x370)+=D(0.1f);if(F(0x370)>=1.0)F(0x370)=1;}else{F(0x370)=0.1f;if(++S(0x364)>4){S(0x364)=0;I(0x180)=0;}}
   if(I(0x144)%3==0){PACKET(p24,RND(360),RND(75)*D(0.1f)+5.0,4);unsigned char facing=B(0x104);float y=F(0xf0);double x=F(0xec)+100.0;spawn_unparented(854,x-RND(200),y,facing,1,reinterpret_cast<const unsigned *>(p24),3);}
   F(0xec)+=C(0x104)*F(0xf4)*F(0x370);F(0xf0)+=F(0xf8);break;
  case 1:F(0x120)*=D(0.95f);F(0x11c)+=F(0x370);F(0x370)*=D(0.95f);if(I(0x144)>=10){FADE(10,10);B(0x110)-=10;B(0x111)-=10;}break;
  case 2:F(0x11c)=F(0x120)=F(0x120)+F(0x370);F(0x370)*=D(0.9f);if(I(0x144)>=10){FADE(10,10);B(0x110)-=10;B(0x111)-=10;}break;
  case 3: {
   float *heading=H;F(0x12c)+=F(0x374);F(0x374)*=D(0.99f);F(0xec)=(lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1])*C(0x104)+AT(P,float,0xec);float *h=H;F(0xf0)=(AT(P,float,0xf0)+100.0)+lookup_orientation_sine_quantized_abs(-heading[0])*h[1];h[1]*=D(0.95f);
   if(S(0x364)==0){if(B(0x113)<=245)B(0x113)+=10;else{B(0x113)=255;S(0x364)=1;}}else if(h[1]<=75.0f){FADE(15,15);B(0x110)-=15;B(0x111)-=15;}break;
  }
  case 4:MOVE();H[1]*=D(0.9f);if(H[1]<D(0.1f))H[1]=0.1f;STEP();if(I(0x144)>=10)FADE(11,10);break;
  case 5:MOVE();H[1]*=D(0.9f);if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4)*D(0.15f);F(0xf0)+=F(0xf8);F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=15)FADE(6,5);break;
  case 6:
   advance_six(0);F(0x11c)+=D(0.01f);advance_phase(0);MOVE();if(I(0x144)%2==0){PACKET(p192,H[0],0,2);SPAWN(854,1,p192);}
   if(I(0x180)==0){F(0x370)+=D(0.1f);if(F(0x370)>=1.0)F(0x370)=1;}else{F(0x370)=0.1f;if(++S(0x364)>4){S(0x364)=0;I(0x180)=0;}}
   {PACKET(p420,RND(360),RND(75)*D(0.1f)+5.0,4);unsigned char facing=B(0x104);float y=F(0xf0);double x=F(0xec)+100.0;spawn_unparented(854,x-RND(200),y,facing,1,reinterpret_cast<const unsigned *>(p420),3);}
   {PACKET(p420,static_cast<float>(static_cast<unsigned>(selector_random_roll(90)+135)),RND(75)*D(0.1f)+5.0,8);unsigned char facing=B(0x104);float y=F(0xf0);double x=F(0xec)+100.0;spawn_unparented(854,x-RND(200),y,facing,1,reinterpret_cast<const unsigned *>(p420),3);}
   F(0xec)+=C(0x104)*F(0xf4)*F(0x370);F(0xf0)+=F(0xf8);break;
  case 7:MOVE();H[1]*=D(0.9f);if(H[1]<D(0.1f))H[1]=0.1f;F(0x11c)-=D(0.01f);STEP();if(I(0x144)>=2)FADE(11,10);break;
  case 8:MOVE();H[1]*=D(0.8f);if(H[1]<0.5f)H[1]=0.5f;STEP();F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=5)FADE(9,8);break;
  }
  if(OUTSIDE(1380.0f,-100.0,1000.0,-100.0))RETIRE();break;
 case 855:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:if(AT(P,short,0x13c)!=605)RETIRE();position_relative(0,0);if(AT(P,short,0x13e)==4){next_sequence_block();return;}break;
  case 1:
   if(AT(P,short,0x13c)!=605)RETIRE();position_relative(0,0);if(AT(P,short,0x13e)==4 && AT(P,short,0x140)>=3){P->publish_layout_scalar(10);int count=6;do{PACKET(p568,RND(360),RND(12)+4.0,2);SPAWN(855,1,p568);}while(--count!=0);count=8;do{PACKET(p568,RND(360),RND(12)+4.0,3);SPAWN(855,1,p568);}while(--count!=0);count=10;do{PACKET(p568,RND(360),RND(12)+4.0,4);SPAWN(855,1,p568);}while(--count!=0);RETIRE();}break;
  case 2:case 3:case 4:F(0x12c)+=F(0x374);F(0xf8)-=D(0.2f);if(I(0x144)>=30)FADE(15,15);STEP();break;
  }break;
 case 856:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:if(AT(P,int,0x838)<=0)RETIRE();F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0);break;
  case 1:MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);SCALE(F(0x11c)+D(0.02f));if(I(0x144)>=0)FADE(6,5);break;
  case 2:SCALE(F(0x11c)*D(0.98f));FADE(10,10);B(0x111)-=10;B(0x110)-=10;break;
  case 3:SCALE(F(0x11c)+D(0.2f));FADE(6,6);B(0x111)-=6;B(0x110)-=6;break;
  }break;
 case 857:
  switch(S(0x13e)) {
  case 1:F(0x12c)+=F(0x374);F(0x374)*=D(0.99f);MOVE();H[1]*=D(0.98f);if(I(0x144)>=15)FADE(10,10);if(OUTSIDE(1380.0f,-100.0,1080.0f,-280.0f))RETIRE();break;
  case 3:case 4:
   if(S(0x364)==0){
    F(0x12c)=H[0];F(0xec)=static_cast<float>(C(0x104)*90)+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+130.0;
    if((AT(P,short,0x13c)!=607 && AT(P,short,0x13c)!=657) || AT(P,short,0x13e)>=2){S(0x364)=1;return;}
    if(I(0x144)%2==0){double heading=H[0]+30.0;PACKET(p96,heading-RND(60),RND(40)+30.0,1);SPAWN(857,1,p96);}advance_six(0);advance_phase(0);if(I(0x180)!=0 && ++S(0x366)>=4){S(0x366)=0;I(0x180)=0;B(0x184)=1;}
   }
   if(S(0x364)==1){B(0x184)=0;F(0x120)*=D(0.97f);FADE(10,10);B(0x110)-=10;B(0x111)-=10;}break;
  case 5:
   if(T==0)S(0x364)=1;
   else{float heading=AT(AT(T,float *,0x340),float,0);H[0]=heading;if(AT(T,short,0x364)==0){if(I(0x144)%10==0){PACKET(p228,heading,0,6);SPAWN(857,1,p228);}}else S(0x364)=1;F(0xec)=AT(T,float,0xec);F(0xf0)=AT(T,float,0xf0);if(S(0x364)==0 && AT(T,short,0x364)==1){S(0x364)=1;return;}}
   if(S(0x364)==1){SCALE(F(0x11c)*D(0.98f));FADE(10,10);B(0x110)-=10;B(0x111)-=10;}break;
  case 6:SCALE(F(0x11c)+D(0.4f));FADE(10,10);B(0x110)-=10;B(0x111)-=10;break;
  }STEP();break;
 case 900:
  switch(S(0x13e)) {
  case 0:
   if(S(0x368)<3 && AT(P,short,0x174)<=0)S(0x364)=3;
   if(S(0x364)==0){
    if(B(0x113)<=215)B(0x113)+=40;else B(0x113)=255;if(F(0x11c)<1.0){F(0x11c)+=D(0.1f);if(F(0x11c)>1.0)F(0x11c)=1;}if(F(0x120)>1.0){F(0x120)-=D(0.2f);if(F(0x120)<1.0)F(0x120)=1;}
    if(I(0x144)>=20){F(0x11c)=F(0x120)=1;I(0x144)=0;F(0xf8)=0;F(0xf4)=RND(25)+15.0;P->dispatch_character_wave_handle(11);B(0x184)=1;I(0x180)=0;S(0x364)=1;}
   }
   if(S(0x364)==1){
    if(F(0xf4)>0.0 && (F(0xec)>1220.0f || F(0xec)<60.0)){F(0xf8)=F(0xf4);F(0xf4)=0;}F(0xf4)-=D(0.4f);if(F(0xf4)<0.0)F(0xf4)=0;F(0xf8)-=D(0.4f);if(F(0xf8)<0.0)F(0xf8)=0;advance_six(0);advance_phase(0);
    if(F(0xf4)>=3.0f || F(0xf8)>=3.0f){if(I(0x144)%3==0){PACKET(p48,RND(360),RND(40)*D(0.1f)+2.0,3);unsigned char facing=B(0x104);double y=F(0xf0)+20.0;double x=20.0+F(0xec);spawn_unparented(900,x-RND(40),y-RND(40),facing,-1,reinterpret_cast<const unsigned *>(p48),3);}}else B(0x184)=0;
    if(F(0xf4)<=0.0 && F(0xf8)<=0.0 && ++S(0x366)>=45){S(0x364)=2;S(0x366)=0;}STEP();
   }
   if(S(0x364)==2){
    // Native selector-zero/default paths leave the burst controls uninitialized.
    // 653294..6532A7 reloads interval/limit from a scratch home without a source initialization.
    float burst_count;int interval,max_bursts,lifetime;
    switch(g_update_selector){case 0:lifetime=60;break;case 1:burst_count=10;interval=60;lifetime=180;max_bursts=2;break;case 2:burst_count=12;interval=60;lifetime=240;max_bursts=4;break;case 3:burst_count=16;interval=60;lifetime=300;max_bursts=5;break;}
    if(I(0x144)%interval==0 && g_update_selector!=0 && S(0x368)<max_bursts){if(burst_count>0.0){float n=0;do{PACKET(p432,(n*360.0)/burst_count,4,1);SPAWN(900,1,p432);n+=1.0;}while(n<burst_count);}PACKET(p432,0,0,2);SPAWN(900,1,p432);P->dispatch_character_wave_handle(1);++S(0x368);}if(I(0x144)>=lifetime)S(0x364)=3;
   }
   if(S(0x364)==3){F(0x11c)*=D(0.95f);F(0x120)+=D(0.1f);FADE(10,10);}break;
  case 1:
   if(S(0x364)==0){if(OUTSIDE(1380.0f,-100.0,1000.0,-200.0))RETIRE();if(I(0x180)!=0 || AT(P,short,0x174)<=0){S(0x364)=1;F(0x11c)=F(0x120)=2;}STEP();break;}
  case 2:SCALE(F(0x11c)*D(0.95f));FADE(10,10);break;
  case 3:F(0x12c)+=F(0x370);F(0x370)*=D(0.96f);F(0xf4)*=D(0.95f);F(0xf8)+=D(0.1f);SCALE(F(0x11c)+D(0.01f));FADE(10,10);break;
  }break;
 case 920:
  switch(S(0x13e)) {
  case 0:F(0xf0)=stage_surface_height()-F(0x370);F(0x370)*=D(0.9f);if(F(0x370)<=D(0.05f) && F(0x370)>0.0){F(0x370)=0;I(0x144)=0;}if(F(0x370)==0.0 && I(0x144)>=30){next_sequence_block();F(0xf8)=RND(70)+10.0;I(0x144)=0;return;}break;
  case 1:if(I(0x144)>=20)B(0x184)=0;F(0xf8)*=D(0.9f);if(F(0xf8)<=D(0.05f)){next_sequence_block();B(0x184)=0;F(0xf8)=0;return;}AT(P,float,0x7c4+S(0x364)*4)=F(0xec);AT(P,float,0x7f4+S(0x364)*4)=F(0xf0);break;
  case 2:
   AT(P,float,0x7c4+S(0x364)*4)=F(0xec);AT(P,float,0x7f4+S(0x364)*4)=F(0xf0);if((AT(P,short,0x13c)==730 && AT(P,short,0x13e)==0) || AT(P,short,0x174)<=0 || I(0x144)>=150){next_sequence_block();AT(P,float,0x7c4+S(0x364)*4)=-1;AT(P,float,0x7f4+S(0x364)*4)=-1;return;}break;
  case 3:FADE(20,20);break;
  case 4: {
   if(AT(P,short,0x174)<=0)RETIRE();advance_six(0);int offset=0x7c4;
   do{double dy=square_float_value(F(0xf0)-AT(P,float,offset+0x30));double dx=square_float_value(F(0xec)-AT(P,float,offset));if(dx+dy<=10000.0){PACKET(p492,0,0,5);SPAWN(920,1,p492);p492[2]=7;SPAWN(920,1,p492);p492[2]=6;int count=2;do{p492[0]=RND(360);p492[1]=RND(10)+5.0;SPAWN(920,1,p492);}while(--count!=0);RETIRE();}offset+=4;}while(offset<0x7f4);
   if(C(0x184)<1 || F(0xf0)<=stage_surface_height()){PACKET(p480,0,0,5);SPAWN(920,1,p480);p480[2]=7;SPAWN(920,1,p480);p480[2]=6;int count=2;do{p480[0]=RND(360);p480[1]=RND(10)+5.0;SPAWN(920,1,p480);}while(--count!=0);RETIRE();}
   if(F(0xec)<-100.0 || F(0xec)>1380.0f || F(0xf0)>960.0)RETIRE();break;
  }
  case 5:SCALE(F(0x11c)+D(0.05f));FADE(10,10);B(0x111)-=10;B(0x110)-=10;break;
  case 6:H[1]*=D(0.95f);MOVE();if(I(0x144)>=5){FADE(10,10);B(0x111)-=10;B(0x110)-=10;}break;
  case 7:SCALE(F(0x11c)*D(0.9f));FADE(15,15);B(0x111)-=15;B(0x110)-=15;break;
  case 8:
   if(S(0x140)==0){if(AT(P,short,0x174)<=0 || AT(P,short,0x13c)!=731 || AT(P,short,0x13e)>1){set_sequence_frame(2);return;}MOVE();H[1]-=3.0;if(H[1]<0.0){H[1]=0;next_sequence_frame();return;}F(0x370)+=C(0x104)*F(0xf4);F(0x374)+=F(0xf8);F(0xec)=AT(P,float,0xec)+F(0x370);F(0xf0)=AT(P,float,0xf0)+F(0x374);}
   if(S(0x140)==1){if(AT(P,short,0x174)<=0 || AT(P,short,0x13c)!=731 || AT(P,short,0x13e)>1){set_sequence_frame(2);return;}TenshiObjectUpdateView *parent=P;F(0xec)=AT(parent,float,0xec)+F(0x370);F(0xf0)=AT(parent,float,0xf0)+F(0x374);int interval=2;switch(g_update_selector){case 0:interval=10;break;case 1:interval=4;break;case 3:interval=1;break;}
    if(I(0x144)%interval==0){parent->dispatch_character_wave_handle(1);PACKET(p292,RND(360),5,4);unsigned char facing=B(0x104);spawn_unparented(920,(lookup_orientation_cosine_quantized_abs(-p292[0])*50.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(-p292[0])*50.0+F(0xf0),facing,1,reinterpret_cast<const unsigned *>(p292),3);F(0x378)+=4.0;}
   }if(S(0x140)==2){F(0xf4)=F(0xf8)=0;FADE(10,10);}break;
  case 9:
   if(S(0x364)!=2 && AT(P,short,0x174)<=0)S(0x364)=2;
   if(S(0x364)==0){F(0xf4)*=D(0.99f);AT(AUX,float,0xe8)=F(0xec);double y=F(0xf8)+F(0xf0);if(y<=stage_surface_height()){P->dispatch_character_wave_handle(2);F(0xf0)=stage_surface_height();S(0x364)=2;F(0xf4)=F(0xf8)=0;PACKET(p144,AT(P,float,0x824),RND(70)+10.0,1);SPAWN(920,1,p144);if(AT(P,float,0x824)>10.0f)AT(P,float,0x824)=0;else AT(P,float,0x824)+=1.0;return;}}
   if(S(0x364)==2){F(0xf4)*=D(0.98f);F(0xf8)*=D(0.98f);SCALE(F(0x11c)*D(0.99f));FADE(10,10);}break;
  case 10:
   if(S(0x364)==0){if(T!=0){F(0xec)=AT(T,float,0xec);F(0xf0)=stage_surface_height();if(AT(T,float,0xf0)<=255.0){B(0x113)=static_cast<unsigned char>(static_cast<int>(255.0-AT(T,float,0xf0)));SCALE(((255.0-AT(T,float,0xf0))*0.5)/255.0+1.0);if(AT(T,short,0x364)==2){S(0x364)=1;break;}}else B(0x113)=0;}}
   else{F(0x11c)+=D(0.1f);F(0x120)+=D(0.1f);FADE(10,10);}break;
  default:break;
  }STEP();break;
 case 930:
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x174)<=0)RETIRE();advance_six(5);F(0xf8)-=D(0.075f);
   if(C(0x184)<1 || F(0xf0)<=stage_surface_height()){PACKET(p504,0,0,1);SPAWN(930,1,p504);p504[2]=3;SPAWN(930,1,p504);p504[2]=2;int count=9;do{p504[0]=RND(360);p504[1]=RND(10)+5.0;SPAWN(930,1,p504);}while(--count!=0);RETIRE();}break;
  case 1:SCALE(F(0x11c)+D(0.05f));FADE(5,5);B(0x111)-=5;B(0x110)-=5;break;
  case 2:H[1]*=D(0.95f);MOVE();if(I(0x144)>=20){FADE(10,10);B(0x111)-=10;B(0x110)-=10;}break;
  case 3:SCALE(F(0x11c)*D(0.9f));FADE(15,15);B(0x111)-=15;B(0x110)-=15;break;
  }STEP();break;
 case 940:
  switch(S(0x13e)) {
  case 0:
   if(AT(P,short,0x13c)!=750)RETIRE();position_relative(58,107);
   if(AT(P,short,0x738)==1 && I(0x144)%2==0){PACKET(p72,RND(360),RND(600)+100.0,1);spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p72),3);}
   if(AT(P,short,0x738)==2 && AT(P,short,0x732)==0){AT(P,short,0x732)=1;I(0x144)=0;S(0x364)=0;F(0x370)=0;PACKET(p244,0,0,14);switch(g_update_selector){case 0:p244[3]=1;break;case 1:p244[3]=3;break;case 2:p244[3]=4;break;case 3:p244[3]=5;break;}spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p244),4);}
   if(AT(P,short,0x738)==3 && AT(P,short,0x732)==0){AT(P,short,0x732)=1;I(0x144)=0;S(0x364)=0;F(0x370)=0;p384[0]=0;if(static_cast<unsigned>(selector_random_roll(100))<51)p384[0]=45;p384[1]=4;if(static_cast<unsigned>(selector_random_roll(100))<51)p384[1]=-4;p384[2]=15;p384[3]=100;switch(g_update_selector){case 0:p384[4]=180;break;case 1:p384[4]=300;break;case 2:case 3:p384[4]=360;break;}spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p384),5);P->dispatch_character_wave_handle(13);}
   if(AT(P,short,0x738)==4){
    if(g_update_selector==1)turn_heading(0,0.5f,100);else if(g_update_selector==2)turn_heading(0,0.75f,100);else if(g_update_selector==3)turn_heading(0,1,100);
    if(AT(P,short,0x732)==0){AT(P,short,0x732)=1;I(0x144)=0;S(0x364)=0;F(0x370)=F(0x374)=0;S(0x368)=360;H[0]=-atan2_degrees((AT(A,float,0xf0)+100.0)-F(0xf0),C(0x104)*(AT(A,float,0xec)-F(0xec)));}
    short spread=S(0x368);double heading=spread*0.5+H[0];PACKET(p120,heading-RND(spread),RND(30)+20.0,8);SPAWN(940,1,p120);S(0x368)=10;
   }
   if(AT(P,short,0x738)==5){turn_heading(0,0.2f,100);if(AT(P,short,0x732)==0){AT(P,short,0x732)=1;I(0x144)=0;PACKET(p216,H[0],0,13);spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p216),3);}}
   if(AT(P,short,0x738)==6){turn_heading(0,0.2f,100);if(AT(P,short,0x732)==0){AT(P,short,0x732)=1;I(0x144)=0;PACKET(p520,H[0],0,13);spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p520),3);if(g_update_selector==2 || g_update_selector==3){p520[3]=g_update_selector==2?1.0f:2.0f;PACKET(p520,0,0,14);spawn_parented(940,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p520),4);}}}
   F(0x12c)-=23.0;break;
  case 1: {
   F(0x12c)+=F(0x374);F(0x374)*=D(0.99f);if(T==0){FADE(30,30);B(0x110)-=30;B(0x111)-=30;return;}
   float *heading=H;F(0xec)=(lookup_orientation_cosine_quantized_abs(-heading[0])*heading[1])*C(0x104)+AT(T,float,0xec);float *h=H;F(0xf0)=lookup_orientation_sine_quantized_abs(-heading[0])*h[1]+AT(T,float,0xf0);h[1]*=D(0.95f);if(S(0x364)==0){if(B(0x113)<=245)B(0x113)+=10;else{B(0x113)=255;S(0x364)=1;}}else if(h[1]<=75.0f){FADE(15,15);B(0x110)-=15;B(0x111)-=15;}break;
  }
  case 2:
   advance_six(2);if(I(0x180)!=0 || F(0xf0)<=stage_surface_height() || AT(P,short,0x174)<=0 || AT(P,float,0x74c)>0.0){PACKET(p468,0,0,3);SPAWN(940,1,p468);p468[2]=5;SPAWN(940,1,p468);p468[2]=4;int count=2;do{p468[0]=RND(360);p468[1]=RND(10)+5.0;SPAWN(940,1,p468);}while(--count!=0);RETIRE();}if(F(0xec)<-100.0 || F(0xec)>1380.0f || F(0xf0)>960.0)RETIRE();break;
  case 3:SCALE(F(0x11c)+D(0.05f));FADE(5,5);B(0x111)-=5;B(0x110)-=5;break;
  case 4:H[1]*=D(0.95f);MOVE();if(I(0x144)>=20){FADE(10,10);B(0x111)-=10;B(0x110)-=10;}break;
  case 5:SCALE(F(0x11c)*D(0.9f));FADE(15,15);B(0x111)-=15;B(0x110)-=15;break;
  case 6:if(T==0)RETIRE();F(0xec)=AT(T,float,0xec);F(0xf0)=AT(T,float,0xf0);if(AT(T,short,0x140)>=2)SCALE(F(0x11c)*D(0.98f));break;
  case 7:
   if(S(0x140)<2 && (AT(P,short,0x174)<=0 || AT(P,float,0x74c)>0.0)){B(0x184)=0;set_sequence_frame(2);return;}
   if(T!=0){if(S(0x140)==0){F(0x120)+=D(0.05f);if(F(0x120)>=1.5f){F(0x120)=1.5f;next_sequence_frame();B(0x184)=1;return;}}if(S(0x140)==1)advance_six(0);}
   if(S(0x140)==2){if(B(0x111)<10)RETIRE();B(0x111)-=10;B(0x110)-=10;B(0x113)-=10;F(0x120)*=D(0.9f);}break;
  case 8:F(0x12c)+=F(0x374);F(0x374)*=D(0.99f);MOVE();H[1]*=D(0.98f);if(I(0x144)>=15)FADE(10,10);if(OUTSIDE(1380.0f,-100.0,1080.0f,-280.0f))RETIRE();break;
  case 9:case 10:
   if(T!=0){F(0x12c)=H[0];F(0xec)=(lookup_orientation_cosine_quantized_abs(-H[0])*100.0)*C(0x104)+AT(T,float,0xec);F(0xf0)=lookup_orientation_sine_quantized_abs(-H[0])*100.0+AT(T,float,0xf0);}
   if(S(0x364)==0){
    if(AT(P,short,0x174)<=0 || AT(P,float,0x74c)>0.0 || H[1]<static_cast<float>(I(0x144))){S(0x364)=1;return;}
    if(I(0x144)%2==0){double heading=H[0]+20.0;PACKET(p204,heading-RND(40),RND(40)+30.0,8);SPAWN(940,1,p204);}advance_six(0);advance_phase(0);if(I(0x180)!=0 && ++S(0x366)>=4){S(0x366)=0;I(0x180)=0;B(0x184)=1;}
   }if(S(0x364)==1){B(0x184)=0;F(0x120)*=D(0.97f);FADE(10,10);B(0x110)-=10;B(0x111)-=10;}break;
  case 11:
   if(T==0)S(0x364)=1;else{float heading=AT(T,float *,0x340)[0];H[0]=heading;if(AT(T,short,0x364)==0 && I(0x144)%10==0){PACKET(p180,heading,0,12);SPAWN(940,1,p180);}F(0xec)=AT(T,float,0xec);F(0xf0)=AT(T,float,0xf0);if(S(0x364)==0 && AT(T,short,0x364)==1){S(0x364)=1;return;}}
   if(S(0x364)==1){SCALE(F(0x11c)*D(0.95f));FADE(10,10);B(0x110)-=10;B(0x111)-=10;}break;
  case 12:SCALE(F(0x11c)+D(0.4f));FADE(10,10);B(0x110)-=10;B(0x111)-=10;break;
  case 13:turn_heading(0,0.2f,100);if(I(0x144)>=240)RETIRE();break;
  case 14:
   if(T==0)RETIRE();F(0xec)=AT(T,float,0xec);F(0xf0)=AT(T,float,0xf0);if(I(0x144)%10==0){if(H[3]<F(0x370))RETIRE();P->dispatch_character_wave_handle(1);float n=0;do{p156[0]=n*22.5-F(0x370)*3.0;F(0x374)=p156[0];p156[0]+=45.0;p156[1]=6.0-F(0x370);p156[2]=2;unsigned char facing=B(0x104);spawn_unparented(940,(lookup_orientation_cosine_quantized_abs(-F(0x374))*100.0)*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(-F(0x374))*100.0+F(0xf0),facing,1,reinterpret_cast<const unsigned *>(p156),3);n+=1.0;}while(n<16.0f);F(0x370)+=1.0;}break;
  case 15: {
   if(AT(P,short,0x174)<=0 || H[4]<=static_cast<float>(I(0x144)) || T==0)RETIRE();F(0xec)=AT(T,float,0xec);F(0xf0)=AT(T,float,0xf0);int interval;switch(g_update_selector){case 0:interval=20;break;case 1:interval=10;break;case 2:interval=6;break;case 3:interval=4;break;}
   if(I(0x144)%interval==0){float n=0;do{PACKET(p268,n*90.0-H[0],H[3],7);unsigned char facing=B(0x104);spawn_parented(940,(lookup_orientation_cosine_quantized_abs(-p268[0])*H[3])*C(0x104)+F(0xec),lookup_orientation_sine_quantized_abs(-p268[0])*H[3]+F(0xf0),facing,1,reinterpret_cast<const unsigned *>(p268),3);n+=1.0;}while(n<4.0f);float *heading=H;heading[0]+=heading[1];heading[3]+=6.0;}break;
  }
  case 18:SCALE(F(0x11c)+D(0.35f));FADE(10,10);B(0x110)-=10;B(0x111)-=10;break;
  }STEP();break;
 case 960:
  if(static_cast<unsigned short>(S(0x13e))<8){
   if(g_update_weather==14){if(B(0x112)<133){B(0x112)=B(0x111)=128;}else{B(0x112)-=5;B(0x111)-=5;}}else if(B(0x112)<251){B(0x112)+=5;B(0x111)+=5;}else B(0x112)=B(0x111)=255;
   if(S(0x36c)==0){
    if(AT(P,unsigned char,0x82c)==0){
     if(I(0x144)%8==0){p256[1]=20;p256[2]=4;p256[0]=RND(360);int layer=(p256[0]>=0.0 && p256[0]<=180.0f)?1:-1;spawn_unparented(815,F(0xec),0,B(0x104),layer,reinterpret_cast<const unsigned *>(p256),3);}
     if(F(0xf8)>0.0)F(0xf8)=0;F(0xf8)-=0.25;
     if(F(0xf0)<=0.0){float x=static_cast<float>(S(0x13e)*160);fill_stage_surface_range(x,159.0+x,0);F(0xf0)=F(0xf8)=0;
      if(AT(P,signed char,0x55a)==1){TenshiSequenceSlotsView *slots=reinterpret_cast<TenshiSequenceSlotsView *>(reinterpret_cast<unsigned char *>(P)+0x55c);if(AT(slots->subscript(0),short,0)>15 && AT(slots->subscript(0),short,0)<20 && g_update_mode==5){S(0x36c)=1;return;}RETIRE();}
     }
     {float x=static_cast<float>(S(0x13e)*160);fill_stage_surface_range(x,159.0+x,F(0xf0));}AT(P,float,0x7a4+S(0x13e)*4)=F(0xf0);
    }else{
     AT(AUX,float,0xec)=-AT(P,float,0x828);
     if(AT(P,float,0x7a4+S(0x13e)*4)<=F(0xf0)){
      if(AT(P,float,0x7a4+S(0x13e)*4)<F(0xf0)){
       if(S(0x364)==0){B(0x184)=0;S(0x364)=1;p328[1]=20;p328[2]=4;float n=0;do{p328[0]=n*45.0+RND(30);int layer=(p328[0]>=0.0 && p328[0]<=180.0f)?1:-1;unsigned char facing=B(0x104);spawn_unparented(815,F(0xec),stage_surface_height(),facing,layer,reinterpret_cast<const unsigned *>(p328),3);n+=1.0;}while(n<8.0f);}
       F(0xf8)=(AT(P,float,0x7a4+S(0x13e)*4)-F(0xf0))*0.5;if(F(0xf8)<-60.0)F(0xf8)=-60;if(F(0xf8)>-1.0f){F(0xf8)=0;S(0x364)=0;F(0xf0)=AT(P,float,0x7a4+S(0x13e)*4);}
      }
     }else{
      if(S(0x364)==0){I(0x180)=0;B(0x184)=1;S(0x364)=1;p364[1]=20;p364[2]=4;float n=0;do{p364[0]=n*45.0+RND(30);int layer=(p364[0]>=0.0 && p364[0]<=180.0f)?1:-1;unsigned char facing=B(0x104);spawn_unparented(815,F(0xec),stage_surface_height(),facing,layer,reinterpret_cast<const unsigned *>(p364),3);n+=1.0;}while(n<8.0f);}
      F(0xf8)=(AT(P,float,0x7a4+S(0x13e)*4)-F(0xf0))*0.5;if(F(0xf8)>60.0)F(0xf8)=60;if(F(0xf8)<1.0){B(0x184)=0;F(0xf8)=0;S(0x364)=0;F(0xf0)=AT(P,float,0x7a4+S(0x13e)*4);}
     }
     F(0xec)=static_cast<float>(S(0x13e)*160)+80.0;float x=static_cast<float>(S(0x13e)*160);fill_stage_surface_range(x,159.0+x,F(0xf0));
    }
   }
   if(S(0x36c)==1){F(0xf4)=0;if(AT(P,short,0x13c)==99 && AT(P,short,0x13e)>4)RETIRE();}
  }F(0xf0)+=F(0xf8);if(advance_frame())RETIRE();return;
 case 961:
  if(static_cast<unsigned short>(S(0x13e))<8){
   if(g_update_weather==14){if(B(0x112)<133){B(0x112)=B(0x111)=128;}else{B(0x112)-=5;B(0x111)-=5;}}else if(B(0x112)<251){B(0x112)+=5;B(0x111)+=5;}else B(0x112)=B(0x111)=255;
   if(AT(P,unsigned char,0x82c)==0){
    if(I(0x144)%8==0){p280[1]=20;p280[2]=4;p280[0]=RND(360);int layer=(p280[0]>=0.0 && p280[0]<=180.0f)?1:-1;spawn_unparented(815,F(0xec),0,B(0x104),layer,reinterpret_cast<const unsigned *>(p280),3);}
    if(F(0xf8)>0.0)F(0xf8)=0;F(0xf8)-=0.25;if(F(0xf0)<=0.0){float x=static_cast<float>(S(0x13e)*160);fill_stage_surface_range(x,159.0+x,0);RETIRE();}
    {float x=static_cast<float>(S(0x13e)*160);fill_stage_surface_range(x,159.0+x,F(0xf0));}AT(P,float,0x7a4+S(0x13e)*4)=F(0xf0);
   }else{
    if(AT(P,float,0x7a4+S(0x13e)*4)<=F(0xf0)){
     if(AT(P,float,0x7a4+S(0x13e)*4)<F(0xf0)){
      if(S(0x364)==0){B(0x184)=1;S(0x364)=1;p352[1]=20;p352[2]=4;float n=0;do{p352[0]=n*45.0+RND(30);int layer=(p352[0]>=0.0 && p352[0]<=180.0f)?1:-1;unsigned char facing=B(0x104);spawn_unparented(815,F(0xec),stage_surface_height(),facing,layer,reinterpret_cast<const unsigned *>(p352),3);n+=1.0;}while(n<8.0f);}
      F(0xf8)=(AT(P,float,0x7a4+S(0x13e)*4)-F(0xf0))*0.5;if(F(0xf8)<-60.0)F(0xf8)=-60;if(F(0xf8)>-1.0f){B(0x184)=0;F(0xf8)=0;S(0x364)=0;F(0xf0)=AT(P,float,0x7a4+S(0x13e)*4);}
     }
    }else{
     if(S(0x364)==0){I(0x180)=0;B(0x184)=1;S(0x364)=1;p304[1]=20;p304[2]=4;float n=0;do{p304[0]=n*45.0+RND(30);int layer=(p304[0]>=0.0 && p304[0]<=180.0f)?1:-1;unsigned char facing=B(0x104);spawn_unparented(815,F(0xec),stage_surface_height(),facing,layer,reinterpret_cast<const unsigned *>(p304),3);n+=1.0;}while(n<8.0f);}
     F(0xf8)=(AT(P,float,0x7a4+S(0x13e)*4)-F(0xf0))*0.5;if(F(0xf8)>60.0)F(0xf8)=60;if(F(0xf8)<1.0){B(0x184)=0;F(0xf8)=0;S(0x364)=0;F(0xf0)=AT(P,float,0x7a4+S(0x13e)*4);}
    }
    B(0x113)=F(0xf0)==0.0?0:255;F(0xec)=static_cast<float>(S(0x13e)*160)+80.0;float x=static_cast<float>(S(0x13e)*160);fill_stage_surface_range(x,159.0+x,F(0xf0));
   }
  }F(0xf0)+=F(0xf8);if(advance_frame())RETIRE();return;
 case 962:
  if(static_cast<unsigned short>(S(0x13e))<8){
   if(g_update_weather==14 && g_update_mode!=6){if(B(0x112)<133){B(0x112)=B(0x111)=128;}else{B(0x112)-=5;B(0x111)-=5;}}else if(B(0x112)<251){B(0x112)+=5;B(0x111)+=5;}else B(0x112)=B(0x111)=255;
   F(0xf0)=AT(P,float,0x7a4+S(0x13e)*4);F(0xec)=static_cast<float>(S(0x13e)*160)+80.0;{float x=static_cast<float>(S(0x13e)*160);fill_stage_surface_range(x,159.0+x,F(0xf0));}
   if(S(0x366)==0){if(AT(P,short,0x13c)==99 && AT(P,short,0x730)==0 && I(0x144)%8==0){p340[1]=20;p340[2]=4;p340[0]=RND(360);int layer=(p340[0]>=0.0 && p340[0]<=180.0f)?1:-1;spawn_unparented(815,F(0xec),0,B(0x104),layer,reinterpret_cast<const unsigned *>(p340),3);}if(AT(P,short,0x13c)!=99){S(0x366)=1;release_auxiliary();}}
  }break;
 case 980:update_ping_pong_motion();break;
 case 997:
  switch(S(0x13e)) {
  case 0:
   if(F(0xec)>g_update_right && C(0x104)*F(0xf4)>0.0)F(0xf4)*=-1.0;if(F(0xec)<g_update_left && C(0x104)*F(0xf4)<0.0)F(0xf4)*=-1.0;F(0xf8)-=0.25;F(0x108)=3;F(0x10c)=45;F(0x12c)-=48.0;if(!(F(0xf0)>0.0)){F(0xf4)=F(0xf8)=F(0xf0)=F(0x12c)=0;next_sequence_block();AT(P,short,0x840)=2;}STEP();break;
  case 2:
   F(0xf0)=stage_surface_height();if(AT(P,short,0x13c)==750)RETIRE();if(AT(P,short,0x732)==3 && S(0x364)==0){PACKET(p132,-90,0,4);spawn_parented(997,F(0xec),F(0xf0),B(0x104),1,reinterpret_cast<const unsigned *>(p132),3);}if(AT(P,short,0x732)==2 && I(0x144)%2==0){PACKET(p108,-75.0-RND(30),RND(30)+20.0,3);SPAWN(997,1,p108);}break;
  case 3:F(0x12c)+=F(0x374);F(0x374)*=D(0.99f);MOVE();H[1]*=D(0.98f);if(I(0x144)>=15)FADE(10,10);STEP();if(OUTSIDE(1380.0f,-100.0,1080.0f,-280.0f))RETIRE();break;
  case 4:case 5:if(T==0)RETIRE();F(0xec)=AT(T,float,0xec);F(0xf0)=AT(T,float,0xf0);if(AT(P,short,0x13c)==750)RETIRE();break;
  }break;
 case 998:
  if(S(0x13e)==0){short action=AT(P,short,0x13c);if(action>153 && action<158){F(0xec)=static_cast<float>(C(0x104)*57)+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+60.0;}if(action>149 && action<154){F(0xec)=static_cast<float>(C(0x104)*57)+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+94.0;}if(action==158){F(0xec)=static_cast<float>(C(0x104)*57)+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;}if(action<150 || action>158){next_sequence_block();AT(P,unsigned char,0x751)=0;}}
  if(S(0x13e)==1)FADE(10,10);break;
 default:advance_frame();return;
 }
 if(advance_frame())RETIRE();
}
#undef SPAWN
#undef PACKET
#undef OUTSIDE
#undef ENTRY
#undef FADE
#undef SCALE
#undef STEP
#undef MOVE
#undef RETIRE
#undef RND
#undef D
#undef MOTION
#undef AUX
#undef T
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
