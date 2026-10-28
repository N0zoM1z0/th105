#include "characters/SakuyaActionState.hpp"
namespace th105 {
#define URAND(n) static_cast<float>(static_cast<unsigned>(sakuya_random(n)))
#define KNIFE(p,r,yoff,xoff) do {int facing=B(0x104);float y=sakuya_sine(-(p)[0])*(r)+F(0xf0)+(yoff);float x; if((xoff)==0.0)x=sakuya_cosine(-(p)[0])*(r)*C(0x104)+F(0xec);else x=(sakuya_cosine(-(p)[0])*(r)+(xoff))*C(0x104)+F(0xec);spawn(800,x,y,facing,1,p,3);}while(0)
#define AIM_KNIVES() do {float dx=(PF(0xec)-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);F(0x744)=-sakuya_atan(dy,dx);if(F(0x744)<-10.0)F(0x744)=-10.0;if(F(0x744)>10.0)F(0x744)=10.0;S(0x730)=1;counter(200,45);}while(0)
#define AIM_KNIVES_HIGH() do {float dx=(PF(0xec)-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);F(0x744)=-sakuya_atan(dy,dx);if(F(0x744)<40.0)F(0x744)=40.0;if(F(0x744)>60.0)F(0x744)=60.0;S(0x730)=1;counter(200,45);}while(0)
#define SPELL_FLASH(x,y,cost) do {S(0x48a)=40;S(0x7a4)=0;S(0x7a6)=0;event(23);effect(115,x,y,B(0x104),1);sequence_window(0,cost,60);secondary_cycle();}while(0)
#define FIELD(T,o) (*reinterpret_cast<T *>(raw+(o)))
#define F(o) FIELD(float,o)
#define I(o) FIELD(int,o)
#define U(o) FIELD(unsigned,o)
#define S(o) FIELD(short,o)
#define US(o) FIELD(unsigned short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define PEER FIELD(SakuyaActionStateView *,0x170)
#define PF(o) (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(PEER)+(o)))
#define PI(o) (*reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(PEER)+(o)))
#define PS(o) (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(PEER)+(o)))
#define PB(o) (*reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(PEER)+(o)))
#define MOTION reinterpret_cast<SakuyaActionScratch *>(raw+4)
#define ENTRY(n) (I(0x144)==0&&S(0x142)==0&&S(0x140)==0&&S(0x13e)==(n))
#define FRAME(n,f) (S(0x13e)==(n)&&S(0x142)==0&&S(0x140)==(f))
#define ADVANCE_TO(n) do {if(advance())set_action_and_finalize(n);}while(0)
#define SMOKE(dir) do {double base=F(0xec)+50.0;int facing=(dir);effect(124,base-static_cast<float>(sakuya_random_u32()%100u),static_cast<float>(sakuya_random_u32()%200u)+F(0xf0),facing,1);}while(0)
#define FALL_LAND() do {F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()))goto landed;}while(0)
void SakuyaActionStateView::dispatch_action_state_vslot28(){
 unsigned char *raw=reinterpret_cast<unsigned char *>(this);
S(0x7a0)=0;S(0x7a2)=94;
if(S(0x13c)>149&&S(0x13c)<159&&!B(0x751)){
 B(0x751)=1;
 if(S(0x13c)>149&&S(0x13c)<154)spawn(998,57*C(0x104)+F(0xec),F(0xf0)+94.0,B(0x104),1,0,0);
 if(S(0x13c)>153&&S(0x13c)<158)spawn(998,57*C(0x104)+F(0xec),F(0xf0)+60.0,B(0x104),1,0,0);
 if(S(0x13c)==158)spawn(998,57*C(0x104)+F(0xec),F(0xf0)+100.0,B(0x104),1,0,0);
}
if(S(0x7a6)>0){
 if(PS(0x174)<=0||S(0x174)<=0||sakuya_state_13c_in_32_95(this))S(0x7a6)=0;
 short action=S(0x13c);
 if(action>=600&&action<=689&&(action!=601||S(0x13e)<4))S(0x7a6)=0;
 if(!(S(0x7a6)%2))S(0x48a)=1;
 --S(0x7a6);
}
if(S(0x7a4)>0){
 if(PS(0x174)<=0||S(0x174)<=0){S(0x7a4)=0;PI(0x114)=0;}
 short action=S(0x13c);
 if(action>=600&&action<=689&&(action!=604||S(0x13e)<4)){S(0x7a4)=0;PI(0x114)=0;}
 S(0x4a8)=2;S(0x4ac)=2;S(0x48a)=2;PI(0x114)=1;
 --S(0x7a4);if(S(0x7a4)<=0)PI(0x114)=0;
}
if(S(0x186)||PS(0x48c))return;

switch(S(0x13c)){
case 0:{landing();if(F(0xf4)==0.0)B(0x47e)=0;goto idle_drift;}

case 1:{
 landing();
 if(B(0x47e)){
  if(F(0xf4)>0.0){F(0xf4)-=0.5;if(F(0xf4)<0.0){zero_motion();B(0x47e)=0;}}
  if(F(0xf4)<0.0){F(0xf4)+=0.5;if(F(0xf4)>0.0){zero_motion();B(0x47e)=0;}}
 }else zero_motion();
 if(advance()&&!S(0x140))set_action_and_finalize(2);return;
}

case 2:{landing();goto idle_drift;}

case 3:{
 landing();
 if(B(0x47e)){
  if(F(0xf4)>0.0){F(0xf4)-=0.5;if(F(0xf4)<0.0){zero_motion();B(0x47e)=0;}}
  if(F(0xf4)<0.0){F(0xf4)+=0.5;if(F(0xf4)>0.0){zero_motion();B(0x47e)=0;}}
 }else zero_motion();
 if(advance()&&!S(0x140))set_action_and_finalize(0);return;
}

case 4:{landing();F(0xf4)=6.0;advance();return;}

case 5:{landing();F(0xf4)=-6.0;advance();return;}

case 6:{
 if(!S(0x13e)){landing();if(!S(0x13e)&&!B(0x47e))zero_motion();}
 if(S(0x13e)>0){FALL_LAND();}
 advance();if(!ENTRY(1))return;
 F(0xf4)=0.0;F(0xf8)=15.0;F(0x100)=0.7f;B(0x47e)=0;return;
}

case 7:{
 if(!S(0x13e)){landing();if(!S(0x13e)&&!B(0x47e))zero_motion();}
 if(S(0x13e)>0){FALL_LAND();}
 advance();if(!ENTRY(1))return;
 F(0xf4)=5.0;F(0xf8)=15.0;F(0x100)=0.7f;B(0x47e)=0;return;
}

case 8:{
 if(!S(0x13e)){landing();if(!S(0x13e)&&!B(0x47e))zero_motion();}
 if(S(0x13e)>0){FALL_LAND();}
 advance();if(!ENTRY(1))return;
 F(0xf4)=-5.0;F(0xf8)=15.0;F(0x100)=0.7f;B(0x47e)=0;return;
}

case 9:{if(F(0x100)==0.0)F(0x100)=0.6f;FALL_LAND();advance();return;}

case 10:{landing();zero_motion();if(advance()){if(I(0x6b8))set_action_and_finalize(2);else set_action_and_finalize(0);}return;}

case 197:{
 if((!S(0x13e)&&S(0x140)<4)||S(0x13e)==2)landing();
 if(S(0x13e)<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(2);return;}}
 if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
 if(FRAME(2,1)){if(PF(0xec)<F(0xec))C(0x104)=-1;if(PF(0xec)>F(0xec))C(0x104)=1;}
 if(FRAME(0,4)){F(0xf8)=8.0;F(0xf4)=12.5;F(0x100)=0.7f;}return;
}

case 198:{
 if((!S(0x13e)&&S(0x140)<4)||S(0x13e)==2)landing();
 if(S(0x13e)<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(2);return;}}
 if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
 if(FRAME(2,3)){if(PF(0xec)<F(0xec))C(0x104)=-1;if(PF(0xec)>F(0xec))C(0x104)=1;}
 if(FRAME(0,4)){F(0xf8)=8.0;F(0xf4)=-12.5;F(0x100)=0.7f;}return;
}

case 199:{
 landing();if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
 if(FRAME(0,9)){if(PF(0xec)<F(0xec))C(0x104)=-1;if(PF(0xec)>F(0xec))C(0x104)=1;}return;
}

case 200:{
 landing();B(0x47e)=1;if(F(0xf4)>11.0){F(0xf4)-=0.75;if(F(0xf4)<11.0)F(0xf4)=11.0;}advance();
 if(S(0x13e)==1){if(!(I(0x144)%5)){SMOKE(B(0x104));}if(I(0x6b8)<0){if(I(0x6b4)*C(0x104)>0)set_action_and_finalize(212);else set_action_and_finalize(211);return;}short count=++S(0x730);if((I(0x6b4)*C(0x104)<=0&&count>5)||count>45){set_action_and_finalize(204);return;}}
 if(FRAME(0,3)){F(0xf4)=15.0;effect(125,80*C(0x104)+F(0xec),F(0xf0)+80.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+80.0,B(0x104),1);event(31);}return;
}

case 201:{
 if(!S(0x13e)||S(0x13e)==3)landing();
 if(S(0x13e)==3){F(0xf4)+=2.0;if(F(0xf4)>0.0)F(0xf4)=0.0;}
 if(FRAME(0,2))F(0xf4)=0.0;
 if(!static_cast<unsigned char>(sakuya_on_surface(this))){F(0xf4)+=10.0;if(F(0xf4)>-10.0)F(0xf4)=-10.0;if(!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}}
 if(S(0x13e)<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0;F(0x100)=0.0;F(0xf0)=sakuya_surface(this);select_sequence(3);return;}}
 if(advance()){set_action_and_finalize(0);F(0xf4)=0.0;return;}
 if(FRAME(0,2))F(0xf4)=-50.0;
 if(ENTRY(1)){F(0xf8)=4.0;F(0x100)=0.6f;F(0xf4)=-30.0;effect(125,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}return;
}

case 202:{
 F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()))goto dash_landed;
 if((S(0x13e)==1||S(0x13e)==2)&&!(I(0x144)%5)){SMOKE(B(0x104));}
 advance();if(FRAME(0,2)){S(0x730)=0;F(0xf4)=11.0;F(0xf8)=5.0;F(0x100)=0.6f;effect(125,80*C(0x104)+F(0xec),F(0xf0)+110.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+110.0,B(0x104),1);event(31);}
 if(ENTRY(2))flip();return;
}

case 203:{
 F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=sakuya_surface(this);set_action_and_finalize(10);return;}
 if(S(0x13e)<3&&!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}
 advance();if(!I(0x144)){if(ENTRY(1)){F(0xf4)=-11.0;F(0xf8)=5.0;F(0x100)=0.6f;effect(125,F(0xec),F(0xf0)+120.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+120.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}if(ENTRY(2))flip();}return;
}

case 204:{landing();F(0xf4)-=0.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}if(advance()){set_action_and_finalize(0);B(0x47e)=0;}return;}

case 208:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(sakuya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;
 F(0xf4)=0.0;F(0xf8)=20.0;F(0x100)=0.7f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 209:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(sakuya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;
 F(0xf4)=10.0;F(0xf8)=15.0;F(0x100)=0.7f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 210:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(sakuya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;
 F(0xf4)=-10.0;F(0xf8)=15.0;F(0x100)=0.7f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 211:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(sakuya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;
 F(0xf4)=2.5;F(0xf8)=20.0;F(0x100)=0.7f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 212:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(sakuya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;
 F(0xf4)=10.0;F(0xf8)=15.0;F(0x100)=0.7f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 214:{
 if(advance()){set_action_and_finalize(9);return;}
 if(!I(0x144)){
  if(ENTRY(1))event(31);
  if(ENTRY(6)){set_action_and_finalize(9);return;}
 }
 int vertical=I(0x6b8);int horizontal=I(0x6b4)*C(0x104);
 if(vertical>0)S(0x732)=horizontal>0?-45:(horizontal<0?-135:-90);
 else if(vertical<0)S(0x732)=horizontal>0?45:(horizontal<0?135:90);
 else if(horizontal>0)S(0x732)=0;
 else if(horizontal<0)S(0x732)=180;
 if(S(0x13e)==5||S(0x13e)==6)F(0xf8)-=F(0x100);
 if(S(0x13e)>0&&S(0x13e)<5){
  ++S(0x736);S(0x734)=static_cast<short>(S(0x732)-static_cast<int>(F(0x740)));
  if(S(0x734)>180)S(0x734)-=360;
  if(S(0x734)<-180)S(0x734)+=360;
  if(S(0x734)>0)F(0x740)+=I(0x4b8)?0.5:1.0;
  if(S(0x734)<0)F(0x740)-=I(0x4b8)?0.5:1.0;
  F(0xf4)=sakuya_cosine(F(0x740))*F(0x73c);
  F(0xf8)=sakuya_sine(F(0x740))*F(0x73c);
  if(F(0xf0)>680.0&&F(0xf8)>0.0)F(0xf8)=0.0;
  F(0x73c)+=static_cast<double>(0.3f);if(F(0x73c)>12.0)F(0x73c)=12.0;
  if(I(0x4b8))counter(10,1);else counter(5,1);
  F(0x12c)=-F(0x740);if(F(0xf4)<0.0)F(0x12c)=180.0-F(0x740);
  if(F(0xf4)<0.0&&S(0x13e)==1)select_sequence(3);
  if(0.0<=F(0xf4)&&S(0x13e)==3)select_sequence(1);
  if(F(0xf4)<0.0&&S(0x13e)==2)select_sequence(4);
  if(0.0<=F(0xf4)&&S(0x13e)==4)select_sequence(2);
  if(I(0x144)%5==1){int facing=B(0x104);float y=sakuya_sine(F(0x740))*100.0+F(0xf0)+100.0;float x=sakuya_cosine(F(0x740))*100.0*C(0x104)+F(0xec);effect(125,x,y,facing,1);}
  if(((!I(0x6c8)&&S(0x736)>10)||S(0x482)<=0)&&((!I(0x6c8)&&S(0x736)>10)||S(0x482)<=0)){
   MOTION->reset();
   if(S(0x13e)==1||S(0x13e)==2){
    if(B(0x104)==1){if(PF(0xec)<F(0xec)){C(0x104)=-1;F(0xf4)=-F(0xf4);select_sequence(6);}else select_sequence(5);}
    else if(PF(0xec)>F(0xec)){B(0x104)=-B(0x104);F(0xf4)=-F(0xf4);select_sequence(6);}else select_sequence(5);
   }
   if(S(0x13e)==3||S(0x13e)==4){
    if(B(0x104)==1){if(PF(0xec)<F(0xec)){C(0x104)=-1;F(0xf4)=-F(0xf4);select_sequence(5);}else select_sequence(6);}
    else if(PF(0xec)>F(0xec)){B(0x104)=-B(0x104);F(0xf4)=-F(0xf4);select_sequence(5);}
    else select_sequence(6);
   }return;
  }
 }
 if(static_cast<unsigned char>(crossed())){
  F(0xf0)=sakuya_surface(this);F(0x100)=0.0;F(0xf8)=0.0;
  if(S(0x13e)>=5){set_action_and_finalize(10);zero_motion();}
  else{MOTION->reset();set_action_and_finalize(215);}
 }return;
}

case 215:{landing();if(F(0xf4)>0.0){F(0xf4)-=0.75;if(F(0xf4)<0.0)F(0xf4)=0.0;}if(F(0xf4)<0.0){F(0xf4)+=0.75;if(F(0xf4)>0.0)F(0xf4)=0.0;}ADVANCE_TO(0);return;}

case 220:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(sakuya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;
 F(0xf4)=0.0;F(0xf8)=20.0;F(0x100)=0.7f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 221:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(sakuya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;
 F(0xf4)=10.0;F(0xf8)=15.0;F(0x100)=0.7f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 222:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(sakuya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;
 F(0xf4)=-10.0;F(0xf8)=15.0;F(0x100)=0.7f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 223:{
 landing();B(0x47e)=1;advance();
 if(S(0x13e)==1){if(!(I(0x144)%5)){SMOKE(B(0x104));}short count=++S(0x730);if((I(0x6b4)*C(0x104)<=0&&count>13)||count>45){set_action_and_finalize(204);return;}}
 if(FRAME(0,3)){F(0xf4)=7.5;effect(125,80*C(0x104)+F(0xec),F(0xf0)+80.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+80.0,B(0x104),1);event(31);}return;
}

case 224:{
 if(!S(0x13e)||S(0x13e)==3)landing();
 if(S(0x13e)==3){F(0xf4)+=2.0;if(F(0xf4)>0.0)F(0xf4)=0.0;}
 if(FRAME(0,2))F(0xf4)=0.0;
 if(!static_cast<unsigned char>(sakuya_on_surface(this))){F(0xf4)+=10.0;if(F(0xf4)>-10.0)F(0xf4)=-10.0;if(!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}}
 if(S(0x13e)<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0;F(0x100)=0.0;F(0xf0)=sakuya_surface(this);select_sequence(3);return;}}
 if(advance()){set_action_and_finalize(0);F(0xf4)=0.0;return;}
 if(FRAME(0,2))F(0xf4)=-50.0;
 if(ENTRY(1)){F(0xf8)=4.0;F(0x100)=0.6f;F(0xf4)=-30.0;effect(125,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}return;
}

case 225:{
 F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=sakuya_surface(this);set_action_and_finalize(10);return;}
 if(S(0x13e)<3&&!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}
 if(advance())set_action_and_finalize(9);if(!I(0x144)){if(ENTRY(1)){F(0xf4)=-11.0;F(0xf8)=5.0;F(0x100)=0.6f;effect(125,F(0xec),F(0xf0)+120.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+120.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}if(ENTRY(2))flip();}return;
}

case 226:{
 F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()))goto dash_landed;
 if((S(0x13e)==1||S(0x13e)==2)&&!(I(0x144)%5)){SMOKE(B(0x104));}
 if(advance())set_action_and_finalize(9);if(FRAME(0,2)){S(0x730)=0;F(0xf4)=11.0;F(0xf8)=5.0;F(0x100)=0.6f;effect(125,80*C(0x104)+F(0xec),F(0xf0)+110.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+110.0,B(0x104),1);event(31);}
 if(ENTRY(2))flip();return;
}

case 300:{landing();if(directional(0))return;if(B(0x47e)){F(0xf4)-=0.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3){event(27);B(0x47e)=0;}return;}

case 301:{landing();if(directional(0))return;if(B(0x47e)){F(0xf4)-=0.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}if(S(0x140)>3){F(0xf4)-=1.5;if(F(0xf4)<0.0)F(0xf4)=0.0;}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3){F(0xf4)=20.0;B(0x47e)=0;}if(!S(0x142)&&S(0x140)==4){F(0xf4)=5.0;event(28);}return;}

case 302:{
 if(directional(1))return;if(!S(0x13e)||S(0x13e)==2||S(0x13e)==4)landing();
 if(S(0x13e)==1){F(0xf8)-=F(0x100);if(I(0x144)>24)landing();}
 if(S(0x13e)==3){F(0xf8)-=F(0x100);F(0xf4)-=0.75;if(F(0xf4)<3.0)F(0xf4)=3.0;if(I(0x144)>23){F(0xf4)=5.0;F(0xf8)=-25.0;}}
 if(S(0x13e)<2){if(static_cast<unsigned char>(crossed())){event(29);F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(2);return;}}
 else if(S(0x13e)==3&&static_cast<unsigned char>(crossed())){event(29);F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(4);event(22);layout(2.0f);effect(58,135*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);return;}
 if(!I(0x6bc))B(0x750)=0;ADVANCE_TO(0);if(I(0x144))return;
 if(!S(0x142)&&!S(0x140)&&S(0x13e)==3)set_action_and_finalize(0);
 if(ENTRY(1)){F(0xf4)=15.0;F(0xf8)=4.0;F(0x100)=0.85f;}return;
}

case 303:{landing();if(directional(0))return;if(C(0x47e)>0){F(0xf4)-=static_cast<double>(0.6f);if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}ADVANCE_TO(2);if(!S(0x142)&&S(0x140)==4)event(28);return;}

case 304:{
 short seq=S(0x13e);if(seq==0||(seq==2&&I(0x144)>29)||seq==3||seq==4||(seq==6&&I(0x144)>29)||seq==7)landing();
 if(S(0x13e)==1||S(0x13e)==2){F(0xf8)-=F(0x100);F(0xf4)-=0.5;if(F(0xf4)<5.0)F(0xf4)=5.0;if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(3);return;}}
 if(S(0x13e)==5||S(0x13e)==6){F(0xf8)-=F(0x100);F(0xf4)-=0.5;if(F(0xf4)<7.0)F(0xf4)=7.0;if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(7);return;}}
 if(!I(0x6bc))B(0x750)=0;ADVANCE_TO(0);
 if(ENTRY(1)){F(0xf4)=13.5;F(0xf8)=12.5;F(0x100)=1.0;}
 if(!I(0x144)){if(ENTRY(4))set_action_and_finalize(0);if(ENTRY(5)){F(0xf4)=15.5;F(0xf8)=13.5;F(0x100)=1.0;}}
 if(FRAME(0,4)&&B(0x750)){select_sequence(4);effect(62,F(0xec)-17*C(0x104),F(0xf0)+72.0,B(0x104),1);return;}
 if(S(0x13e)==1&&!S(0x142)){if(S(0x140)==1){float request[3]={0.0f,1.0f,1.0f};spawn(849,F(0xec),F(0xf0),B(0x104),1,request,3);}if(!S(0x142)){if(S(0x140)==2)event(29);if(!S(0x142)&&S(0x140)==4)I(0x180)=0;}}
 if(S(0x13e)!=5)return;if(!S(0x142)&&S(0x140)==1){float request[3]={0.0f,1.0f,1.0f};spawn(849,F(0xec),F(0xf0),B(0x104),1,request,3);}if(S(0x142))return;if(S(0x140)==2)event(29);if(!S(0x142)&&S(0x140)==4)I(0x180)=0;return;
}

case 305:{landing();if(directional(1))return;if(S(0x140)>4){F(0xf4)-=1.0;if(F(0xf4)<0.0)F(0xf4)=0.0;}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3)event(28);return;}

case 306:{FALL_LAND();ADVANCE_TO(9);if(!S(0x142)&&S(0x140)==5)event(28);return;}

case 307:{if(!I(0x6bc))B(0x750)=0;FALL_LAND();ADVANCE_TO(9);if(ENTRY(1)){set_action_and_finalize(9);return;}if(FRAME(0,2))event(29);return;}

case 308:{if(!I(0x6bc))B(0x750)=0;FALL_LAND();ADVANCE_TO(9);if(ENTRY(1)){set_action_and_finalize(9);return;}if(S(0x13e)||S(0x142))return;if(S(0x140)==6){event(28);float request[3]={0.0f,0.0f,0.0f};spawn(849,F(0xec),F(0xf0),B(0x104),1,request,3);}if(!S(0x142)&&S(0x140)==9)F(0x100)=0.6f;return;}

case 309:{if(!I(0x6bc))B(0x750)=0;FALL_LAND();ADVANCE_TO(9);if(ENTRY(1)){set_action_and_finalize(9);return;}if(S(0x13e)||S(0x142))return;if(S(0x140)==2){F(0x100)=0.8f;F(0xf8)=12.0;}if(S(0x142))return;if(S(0x140)==4){float request[3]={0.0f,0.0f,1.0f};spawn(849,F(0xec),F(0xf0),B(0x104),1,request,3);}if(!S(0x142)&&S(0x140)==5)event(29);return;}

case 310:{
 if(I(0x180)&&++S(0x730)>5){I(0x180)=0;S(0x730)=0;}
 if(S(0x13e)==1){if(!I(0x144))F(0xf4)=15.0;if(!(I(0x144)%8))event(27);if(I(0x180)&&++S(0x730)>5){I(0x180)=0;S(0x730)=0;}if(I(0x144)>30){next_sequence_block();F(0xf8)=6.0;F(0xf4)*=0.5;}}
 if(S(0x13e)==2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0;F(0xf0)=sakuya_surface(this);set_action_and_finalize(9);return;}}ADVANCE_TO(9);return;
}

case 320:{landing();if(directional(0))return;if(S(0x140)>1){F(0xf4)-=2.0;if(F(0xf4)<0.0)F(0xf4)=0.0;}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==2){event(28);B(0x47e)=0;}return;}

case 321:{landing();if(directional(0))return;if(B(0x47e)){F(0xf4)-=0.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}if(S(0x140)>3){F(0xf4)-=1.5;if(F(0xf4)<0.0)F(0xf4)=0.0;}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3){F(0xf4)=20.0;B(0x47e)=0;}if(!S(0x142)&&S(0x140)==4){F(0xf4)=5.0;event(28);}return;}

case 322:{landing();if(directional(1))return;F(0xf4)-=0.5;if(F(0xf4)<0.0)F(0xf4)=0.0;ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3){event(29);B(0x47e)=0;}return;}

case 400:{
 landing();if(!I(0x6c0))B(0x750)=0;
 if(S(0x730)==1){int remainder=S(0x732)%3;if(!S(0x13e)){if(!remainder&&S(0x734)<5){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)-4.0+S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,40.0,125.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}}
 else if(!remainder&&S(0x734)<7){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)-4.0+S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,40.0,125.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}++S(0x732);}
 ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,F(0xec)-40*C(0x104),F(0xf0)+136.0,B(0x104),1);}if(!S(0x142)&&S(0x140)==6){AIM_KNIVES();}}
 if(FRAME(1,3)){AIM_KNIVES();}return;
}

case 401:{
 landing();if(!I(0x6c0))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==5&&B(0x750)){next_sequence_block();effect(62,F(0xec)-6*C(0x104),F(0xf0)+203.0,B(0x104),1);}if(!S(0x142)&&S(0x140)==7){dispatch_character_wave_handle(0);counter(200,60);I(0x180)=1;phase_counter(50);for(int i=0,y=0;y<100;++i,y+=20){float request[3];request[0]=2.0-i;request[1]=25.0f;request[2]=4.0f;spawn(800,77*C(0x104)+F(0xec),F(0xf0)+40.0+y,B(0x104),1,request,3);}}}
 if(FRAME(1,7)){dispatch_character_wave_handle(0);counter(200,60);I(0x180)=1;phase_counter(50);for(int i=0,y=0;y<105;++i,y+=15){float request[3];request[0]=3.0-i;request[1]=25.0f;request[2]=4.0f;spawn(800,77*C(0x104)+F(0xec),F(0xf0)+25.0+y,B(0x104),1,request,3);}}return;
}

case 402:{
 landing();if(!I(0x6c0))B(0x750)=0;
 if(S(0x730)==1){int remainder=S(0x732)%3;if(!S(0x13e)){if(!remainder&&S(0x734)<5){I(0x180)=1;for(int i=-50;i<-35;i+=5){float request[3];request[0]=i-S(0x734)*6;request[1]=5.0f;request[2]=0.0f;KNIFE(request,70.0,75.0,50.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}}
 else if(!remainder&&S(0x734)<5){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)-4.0+S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,40.0,125.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}++S(0x732);}
 ADVANCE_TO(2);if(ENTRY(1)){set_action_and_finalize(2);return;}if(FRAME(0,5)){S(0x730)=1;counter(200,45);}return;
}

case 404:{
 if(S(0x13e)==2)landing();if(!I(0x6c0))B(0x750)=0;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}
 if(S(0x730)==1){if(!S(0x13e)){if(!(S(0x732)%3)&&S(0x734)<5){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)+4.0-S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,80.0,100.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}}
 else if(S(0x13e)==1&&!(S(0x732)%3)&&S(0x734)<7){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)+4.0-S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,80.0,100.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}++S(0x732);}
 ADVANCE_TO(0);if(!I(0x144)&&((!S(0x142)&&!S(0x140)&&S(0x13e)==1)||(!S(0x142)&&!S(0x140)&&S(0x13e)==2))){set_action_and_finalize(9);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,30*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1);}if(!S(0x142)&&S(0x140)==5){F(0xf4)=-6.0;F(0xf8)=9.0;F(0x100)=0.7f;AIM_KNIVES();}}
 if(FRAME(1,2)){F(0xf4)=-6.0;F(0xf8)=9.0;F(0x100)=0.7f;AIM_KNIVES();}return;
}

case 405:{
 if(S(0x13e)==2)landing();if(!I(0x6c0))B(0x750)=0;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}
 if(S(0x730)==1){if(!S(0x13e)){if(!(S(0x732)%3)&&S(0x734)<5){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)+4.0-S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,80.0,100.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}}
 else if(!(S(0x732)%3)&&S(0x734)<5){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)+4.0-S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,80.0,100.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}++S(0x732);}
 ADVANCE_TO(0);if(!I(0x144)&&((!S(0x142)&&!S(0x140)&&S(0x13e)==1)||(!S(0x142)&&!S(0x140)&&S(0x13e)==2))){set_action_and_finalize(9);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,30*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1);}if(!S(0x142)&&S(0x140)==5){F(0xf4)=-6.0;F(0xf8)=9.0;F(0x100)=0.7f;AIM_KNIVES();}}
 if(FRAME(1,2)){F(0xf4)=-6.0;F(0xf8)=9.0;F(0x100)=0.7f;AIM_KNIVES();}return;
}

case 406:{
 if(S(0x13e)==2)landing();if(!I(0x6c0))B(0x750)=0;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}
 if(S(0x730)==1){if(!S(0x13e)){if(!(S(0x732)%3)&&S(0x734)<5){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)+4.0-S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,80.0,100.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}}
 else if(S(0x13e)==1&&!(S(0x732)%3)&&S(0x734)<7){I(0x180)=1;for(int i=0;i<15;i+=5){float request[3];request[0]=F(0x744)+4.0-S(0x734)*2+i-5.0;request[1]=5.0f;request[2]=0.0f;KNIFE(request,80.0,100.0,0.0);}phase_counter(10);dispatch_character_wave_handle(0);++S(0x734);}++S(0x732);}
 ADVANCE_TO(0);if(!I(0x144)&&((!S(0x142)&&!S(0x140)&&S(0x13e)==1)||(!S(0x142)&&!S(0x140)&&S(0x13e)==2))){set_action_and_finalize(9);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,30*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1);}if(!S(0x142)&&S(0x140)==5){F(0xf4)=-6.0;F(0xf8)=9.0;F(0x100)=0.7f;AIM_KNIVES_HIGH();}}
 if(FRAME(1,2)){F(0xf4)=-4.0;F(0xf8)=12.0;F(0x100)=0.7f;AIM_KNIVES_HIGH();}return;
}

case 408:{landing();if(S(0x140)>3)F(0xf4)-=0.5;if(F(0xf4)<0.0)F(0xf4)=0.0;if(I(0x180))S(0x730)=1;ADVANCE_TO(0);if(S(0x13e)||S(0x142))return;if(S(0x140)==2)event(29);if(S(0x142))return;if(S(0x140)==4)I(0x180)=0;if(S(0x142))return;if(S(0x140)==5)I(0x180)=0;if(!S(0x142)&&S(0x140)==6&&S(0x730)==1)I(0x180)=1;return;}

case 409:{F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=sakuya_surface(this);return;}ADVANCE_TO(9);return;}

case 410:{
 landing();if(!I(0x6c4))B(0x750)=0;
 if(!S(0x13e)&&S(0x730)>0){if(S(0x730)%2==1&&S(0x730)<14){F(0x73c)+=3.0;dispatch_character_wave_handle(1);float request[3];request[0]=30.0-F(0x73c);request[1]=20.0f;request[2]=0.0f;int facing=B(0x104);float y=sakuya_sine(-request[0])*80.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*80.0+20.0)*C(0x104)+F(0xec);spawn(803,x,y,facing,1,request,3);}++S(0x730);}
 ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
 if(FRAME(0,4)){S(0x730)=1;counter(200,60);I(0x180)=1;phase_counter(50);}
 if(FRAME(1,7)){dispatch_character_wave_handle(1);counter(200,60);I(0x180)=1;phase_counter(50);for(float i=0.0f;i<7.0;i+=1.0){float request[3];request[0]=3.0-i;request[1]=sakuya_absolute(i-3.0);request[1]=35.0-request[1];request[2]=0.0f;spawn(801,77*C(0x104)+F(0xec),F(0xf0)+25.0+i*15.0,B(0x104),1,request,3);}}return;
}

case 411:{
 landing();if(!I(0x6c4))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==5&&B(0x750)){next_sequence_block();effect(62,F(0xec)-6*C(0x104),F(0xf0)+203.0,B(0x104),1);}if(!S(0x142)&&S(0x140)==7){dispatch_character_wave_handle(2);counter(200,60);I(0x180)=1;phase_counter(50);for(float i=0.0f;i<5.0f;i+=1.0){float request[3];request[0]=2.0-i;float v=sakuya_absolute(request[0]);request[1]=30.0-(v+v);request[2]=0.0f;spawn(801,77*C(0x104)+F(0xec),F(0xf0)+40.0+i*20.0,B(0x104),1,request,3);}}}
 if(FRAME(1,7)){dispatch_character_wave_handle(2);counter(200,60);I(0x180)=1;phase_counter(50);for(float i=0.0f;i<7.0;i+=1.0){float request[3];request[0]=3.0-i;request[1]=sakuya_absolute(i-3.0);request[1]=35.0-request[1];request[2]=0.0f;spawn(801,77*C(0x104)+F(0xec),F(0xf0)+25.0+i*15.0,B(0x104),1,request,3);}}return;
}

case 412:{landing();if(S(0x13e)<2&&!I(0x6c4))S(0x738)=1;ADVANCE_TO(2);if(ENTRY(1))set_action_and_finalize(2);if(!FRAME(0,5))return;dispatch_character_wave_handle(2);I(0x180)=1;counter(200,60);phase_counter(50);for(float i=0.0f;i<5.0f;i+=1.0){float request[3];request[0]=0.0f;request[1]=sakuya_absolute(2.0-i);request[1]=40.0-request[1];request[2]=0.0f;spawn(802,100*C(0x104)+F(0xec),20.0+F(0xf0)+i*20.0,B(0x104),1,request,3);}return;}

case 414:{
 if(S(0x13e)==2)landing();F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}
 if(!I(0x6c4))B(0x750)=0;
 if(!S(0x13e)&&S(0x730)>0){if(S(0x730)%2==1&&S(0x730)<14){F(0x73c)+=3.0;dispatch_character_wave_handle(1);float request[3];request[0]=F(0x73c)+5.0;request[1]=20.0f;request[2]=3.0f;int facing=B(0x104);float y=sakuya_sine(-request[0])*80.0+F(0xf0)+100.0;float x=sakuya_cosine(-request[0])*80.0*C(0x104)+F(0xec);spawn(803,x,y,facing,1,request,3);}++S(0x730);}
 ADVANCE_TO(0);if(!I(0x144)&&((!S(0x142)&&!S(0x140)&&S(0x13e)==1)||(!S(0x142)&&!S(0x140)&&S(0x13e)==2))){set_action_and_finalize(9);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==5){S(0x730)=1;counter(200,60);I(0x180)=1;phase_counter(50);}if(!S(0x142)&&S(0x140)==7)F(0x100)=0.5f;}
 if(S(0x13e)!=1||S(0x142))return;if(S(0x140)==2){S(0x730)=1;counter(200,60);I(0x180)=1;phase_counter(50);}if(!S(0x142)&&S(0x140)==4)F(0x100)=0.5f;return;
}

case 415:{
 if(S(0x13e)==2)landing();F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}
 if(!I(0x6c4))B(0x750)=0;
 ADVANCE_TO(0);if(!I(0x144)&&((!S(0x142)&&!S(0x140)&&S(0x13e)==1)||(!S(0x142)&&!S(0x140)&&S(0x13e)==2))){set_action_and_finalize(9);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,F(0xec)-6*C(0x104),F(0xf0)+203.0,B(0x104),1);}
 if(!S(0x142)){if(S(0x140)==5){dispatch_character_wave_handle(2);counter(200,60);I(0x180)=1;phase_counter(50);for(float i=0.0f;i<5.0f;i+=1.0){float request[3];request[0]=2.0-i;float v=sakuya_absolute(request[0]);request[1]=30.0-(v+v);request[2]=0.0f;spawn(801,80*C(0x104)+F(0xec),F(0xf0)+60.0+i*20.0,B(0x104),1,request,3);}}if(!S(0x142)&&S(0x140)==7)F(0x100)=0.5f;}}
 if(S(0x13e)!=1||S(0x142))return;if(S(0x140)==2){dispatch_character_wave_handle(2);counter(200,60);I(0x180)=1;phase_counter(50);for(float i=0.0f;i<7.0;i+=1.0){float request[3];request[0]=3.0-i;request[1]=sakuya_absolute(i-3.0);request[1]=35.0-request[1];request[2]=0.0f;spawn(801,80*C(0x104)+F(0xec),F(0xf0)+60.0+i*20.0,B(0x104),1,request,3);}}if(!S(0x142)&&S(0x140)==4)F(0x100)=0.5f;return;
}

case 416:{
 if(S(0x13e)==2)landing();F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}
 if(!I(0x6c4))B(0x750)=0;
 ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(ENTRY(2)){set_action_and_finalize(9);return;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,F(0xec)-6*C(0x104),F(0xf0)+203.0,B(0x104),1);}if(!S(0x142)&&S(0x140)==6){dispatch_character_wave_handle(2);counter(200,60);I(0x180)=1;phase_counter(50);for(float i=0.0f;i<5.0f;i+=1.0){float request[3];request[0]=60.0-i*2.0;float v=sakuya_absolute(2.0-i);request[1]=30.0-(v+v);request[2]=0.0f;spawn(801,(i*20.0+10.0)*C(0x104)+F(0xec),i*6.0+F(0xf0)+30.0,B(0x104),1,request,3);}F(0xf4)=-5.0;F(0xf8)=10.0;F(0x100)=0.5f;}}
 if(FRAME(1,2)){dispatch_character_wave_handle(2);counter(200,60);I(0x180)=1;phase_counter(50);for(float i=0.0f;i<7.0;i+=1.0){float request[3];request[0]=60.0-i*2.0;float v=sakuya_absolute(2.0-i);request[1]=30.0-(v+v);request[2]=0.0f;spawn(801,(i*20.0+10.0)*C(0x104)+F(0xec),i*6.0+F(0xf0)+30.0,B(0x104),1,request,3);}F(0xf4)=-5.0;F(0xf8)=10.0;F(0x100)=0.5f;}return;
}

case 418:{landing();if(S(0x140)<5)F(0xf4)-=0.5;if(S(0x140)>6)F(0xf4)-=0.75;if(F(0xf4)<0.0)F(0xf4)=0.0;ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==4){event(29);F(0xf4)=20.0;B(0x47e)=0;}return;}

case 500:{
 if(!S(0x13e)||S(0x13e)==5)landing();
 B(0x17c)=0;
 if(S(0x13e)==1||S(0x13e)==2){F(0x73c)-=1.5;if(F(0x73c)<2.0)F(0x73c)=2.0;MOTION->set_oriented_components(-50.0f,F(0x73c));
 if(S(0x13e)==2){if(I(0x180)&&C(0x184)>0&&++S(0x730)>9){S(0x730)=0;I(0x180)=0;}if(I(0x144)>34)next_sequence_block();}
 }
 if(S(0x13e)==3||S(0x13e)==4){I(0x180)=1;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(5);return;}}
 ADVANCE_TO(0);if(!ENTRY(1))return;
 for(float i=0.0f;i<6.0f;i+=1.0){float request[3];request[0]=i*60.0;request[1]=150.0f;request[2]=2.0f;spawn(810,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);request[2]=3.0f;spawn(810,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);}
effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);counter(200,120);dispatch_character_wave_handle(10);phase_counter(50);F(0x73c)=22.0;F(0x100)=0.6f;MOTION->set_oriented_components(-50.0f,F(0x73c));return;
}

case 501:{
 if(!S(0x13e)||S(0x13e)==5)landing();
 B(0x17c)=0;
 if(S(0x13e)==1||S(0x13e)==2){F(0x73c)-=1.5;if(F(0x73c)<2.0)F(0x73c)=2.0;MOTION->set_oriented_components(-50.0f,F(0x73c));
 if(S(0x13e)==2){if(I(0x180)&&C(0x184)>0&&++S(0x730)>9){S(0x730)=0;I(0x180)=0;}if(I(0x144)>44)next_sequence_block();}
 }
 if(S(0x13e)==3||S(0x13e)==4){I(0x180)=1;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(5);return;}}
 ADVANCE_TO(0);if(!ENTRY(1))return;
 for(float i=0.0f;i<6.0f;i+=1.0){float request[3];request[0]=i*60.0;request[1]=200.0f;request[2]=2.0f;spawn(810,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);request[2]=3.0f;spawn(810,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);}
effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);F(0x73c)=30.0;F(0x100)=0.6f;MOTION->set_oriented_components(-50.0f,F(0x73c));return;
}

case 502:{
 if(S(0x13e)==5)landing();
 B(0x17c)=0;
 if(S(0x13e)==2){if(I(0x180)&&C(0x184)>0&&++S(0x730)>9){S(0x730)=0;I(0x180)=0;}if(I(0x144)>34)next_sequence_block();}
 if(S(0x13e)==3||S(0x13e)==4){I(0x180)=1;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(5);return;}if(S(0x13e)==4&&I(0x144)>19){set_action_and_finalize(9);return;}}
 ADVANCE_TO(0);if(!ENTRY(1))return;
 for(float i=0.0f;i<6.0f;i+=1.0){float request[3];request[0]=i*60.0;request[1]=150.0f;request[2]=2.0f;spawn(810,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);request[2]=3.0f;spawn(810,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);}
 if(static_cast<unsigned char>(crossed()))effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);F(0x100)=0.6f;return;
}

case 503:{
 if(S(0x13e)==5)landing();
 B(0x17c)=0;
 if(S(0x13e)==2){if(I(0x180)&&C(0x184)>0&&++S(0x730)>9){S(0x730)=0;I(0x180)=0;}if(I(0x144)>34)next_sequence_block();}
 if(S(0x13e)==3||S(0x13e)==4){I(0x180)=1;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);zero_motion();select_sequence(5);return;}if(S(0x13e)==4&&I(0x144)>29){set_action_and_finalize(9);return;}}
 ADVANCE_TO(0);if(!ENTRY(1))return;
 for(float i=0.0f;i<6.0f;i+=1.0){float request[3];request[0]=i*60.0;request[1]=150.0f;request[2]=2.0f;spawn(810,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);request[2]=3.0f;spawn(810,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);}
 if(static_cast<unsigned char>(crossed()))effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);F(0x100)=0.6f;return;
}

case 505:{landing();B(0x17c)=4;ADVANCE_TO(0);if(!ENTRY(1))return;float request[3];
for(float i=0.0f;i<3.0f;i+=1.0){request[0]=i*120.0;request[1]=14.0f;request[2]=0.0f;spawn(815,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);}
for(float i=0.0f;i<3.0f;i+=1.0){request[0]=i*120.0+60.0;request[1]=14.0f;request[2]=0.0f;spawn(815,F(0xec),F(0xf0)+118.0,static_cast<unsigned char>(-B(0x104)),1,request,3);}
request[0]=URAND(360);request[1]=15.0f;request[2]=2.0f;spawn(815,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);request[1]=15.0f;request[2]=3.0f;spawn(815,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);request[1]=-15.0f;request[2]=4.0f;spawn(815,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);return;}

case 506:{landing();B(0x17c)=4;ADVANCE_TO(0);if(!ENTRY(1))return;float request[3];
for(float i=0.0f;i<4.0f;i+=1.0){request[0]=i*90.0;request[1]=15.0f;request[2]=0.0f;spawn(815,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);}
for(float i=0.0f;i<4.0f;i+=1.0){request[0]=i*90.0+45.0;request[1]=15.0f;request[2]=0.0f;spawn(815,F(0xec),F(0xf0)+118.0,static_cast<unsigned char>(-B(0x104)),1,request,3);}
request[0]=URAND(360);request[1]=15.0f;request[2]=2.0f;spawn(815,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);request[1]=15.0f;request[2]=3.0f;spawn(815,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);request[1]=-15.0f;request[2]=4.0f;spawn(815,F(0xec),F(0xf0)+118.0,B(0x104),1,request,3);effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);return;}

case 520:{landing();B(0x17c)=1;if(!I(0x6c0))B(0x750)=0;
if(S(0x730)==1){float limit;if(C(0x605)==0)limit=3.0f;if(C(0x605)>0)limit=4.0f;if(C(0x605)>3)limit=5.0f;if(!(S(0x732)%2)&&(F(0x73c)<limit)){float request[3];request[1]=14.0-F(0x73c);request[2]=0.0f;for(float i=0.0f;i<3.0f;i+=1.0){request[0]=i*5.0-5.0-70.0-F(0x73c)*3.0;int facing=B(0x104);float y=sakuya_sine(-request[0])*70.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*70.0+15.0)*C(0x104)+F(0xec);spawn(811,x,y,facing,1,request,3);}F(0x73c)+=1.0;}++S(0x732);}
if(S(0x730)==2){float limit;if(C(0x605)==0)limit=3.0f;if(C(0x605)>0)limit=4.0f;if(C(0x605)>3)limit=5.0f;if(!(S(0x732)%2)&&(!(limit<=F(0x73c)))){float request[3];for(float i=0.0f;i<4.0f;i+=1.0){request[0]=-70.0-F(0x73c)*3.0-i*5.0;request[1]=14.0-F(0x73c);request[2]=0.0f;int facing=B(0x104);float y=sakuya_sine(-request[0])*70.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*70.0+15.0)*C(0x104)+F(0xec);spawn(811,x,y,facing,1,request,3);}F(0x73c)+=1.0;}++S(0x732);}
ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,15*C(0x104)+F(0xec),F(0xf0)+90.0,B(0x104),1);return;}if(S(0x140)==5){S(0x730)=1;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}}if(FRAME(1,2)){S(0x730)=2;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;}

case 521:{landing();B(0x17c)=1;if(!I(0x6c4))B(0x750)=0;
if(S(0x730)==1){float limit;if(C(0x605)==0)limit=3.0f;if(C(0x605)>0)limit=4.0f;if(C(0x605)>3)limit=5.0f;if(!(S(0x732)%2)&&(F(0x73c)<limit)){float request[3];request[1]=14.0-F(0x73c);request[2]=0.0f;for(float i=0.0f;i<3.0f;i+=1.0){request[0]=i*5.0-5.0-135.0-F(0x73c)*3.0;int facing=B(0x104);float y=sakuya_sine(-request[0])*70.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*70.0-20.0)*C(0x104)+F(0xec);spawn(811,x,y,facing,1,request,3);}F(0x73c)+=1.0;}++S(0x732);}
if(S(0x730)==2){float limit;if(C(0x605)==0)limit=3.0f;if(C(0x605)>0)limit=4.0f;if(C(0x605)>3)limit=5.0f;if(!(S(0x732)%2)&&(!(limit<=F(0x73c)))){float request[3];request[1]=14.0-F(0x73c);request[2]=0.0f;for(float i=0.0f;i<4.0f;i+=1.0){request[0]=i*5.0-5.0-135.0-F(0x73c)*3.0;int facing=B(0x104);float y=sakuya_sine(-request[0])*70.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*70.0-20.0)*C(0x104)+F(0xec);spawn(811,x,y,facing,1,request,3);}F(0x73c)+=1.0;}++S(0x732);}
ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,15*C(0x104)+F(0xec),F(0xf0)+90.0,B(0x104),1);return;}if(S(0x140)==5){S(0x730)=1;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}}if(FRAME(1,2)){S(0x730)=2;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;}

case 525:{landing();B(0x17c)=5;if(!I(0x6c0))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,15*C(0x104)+F(0xec),F(0xf0)+90.0,B(0x104),1);return;}if(S(0x140)==5){float request[4]={-45.0f,15.0f,0.0f,0.0f};int facing=B(0x104);float y=sakuya_sine(45.0f)*70.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*70.0-20.0)*C(0x104)+F(0xec);spawn(816,x,y,facing,1,request,4);dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}}if(FRAME(1,2)){float request[4]={-45.0f,15.0f,0.0f,1.0f};int facing=B(0x104);float y=sakuya_sine(45.0f)*70.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*70.0-20.0)*C(0x104)+F(0xec);spawn(816,x,y,facing,1,request,4);dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;}

case 526:{landing();B(0x17c)=5;if(!I(0x6c4))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
if(!S(0x13e)&&!S(0x142)){if(S(0x140)==4&&B(0x750)){next_sequence_block();effect(62,15*C(0x104)+F(0xec),F(0xf0)+90.0,B(0x104),1);return;}if(S(0x140)==5){float request[4]={-135.0f,15.0f,0.0f,0.0f};int facing=B(0x104);float y=sakuya_sine(135.0f)*70.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*70.0+15.0)*C(0x104)+F(0xec);spawn(816,x,y,facing,1,request,4);dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}}if(FRAME(1,2)){float request[4]={-135.0f,15.0f,0.0f,1.0f};int facing=B(0x104);float y=sakuya_sine(135.0f)*70.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*70.0+15.0)*C(0x104)+F(0xec);spawn(816,x,y,facing,1,request,4);dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;}

case 540:{
landing();B(0x17c)=2;if(!I(0x6c0))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
if(FRAME(0,7)){phase_counter(50);counter(200,120);I(0x180)=1;float request[3];request[2]=0.0f;F(0x73c)=C(0x606)<4?1.0f:1.15f;
{request[0]=2.0f;request[1]=F(0x73c)*30.0;int facing=B(0x104);float y=sakuya_sine(-2.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=5.0f;request[1]=F(0x73c)*27.0;int facing=B(0x104);float y=sakuya_sine(-5.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=5.5f;request[1]=F(0x73c)*24.0;int facing=B(0x104);float y=sakuya_sine(-5.5f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=4.0f;request[1]=F(0x73c)*21.0;int facing=B(0x104);float y=sakuya_sine(-4.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-2.0f;request[1]=F(0x73c)*30.0;int facing=B(0x104);float y=sakuya_sine(2.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-5.0f;request[1]=F(0x73c)*27.0;int facing=B(0x104);float y=sakuya_sine(5.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-5.5f;request[1]=F(0x73c)*24.0;int facing=B(0x104);float y=sakuya_sine(5.5f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-4.0f;request[1]=F(0x73c)*21.0;int facing=B(0x104);float y=sakuya_sine(4.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
dispatch_character_wave_handle(12);}if(S(0x13e)==1&&!S(0x140)&&!B(0x750)){select_sequence(0);S(0x140)=7;}return;}

case 541:{
landing();B(0x17c)=2;if(!I(0x6c0))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
if(FRAME(0,7)){phase_counter(50);counter(200,120);I(0x180)=1;float request[3];request[2]=0.0f;F(0x73c)=C(0x606)<4?1.0f:1.15f;
{request[0]=3.0f;request[1]=F(0x73c)*30.0;int facing=B(0x104);float y=sakuya_sine(-3.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=8.0f;request[1]=F(0x73c)*27.0;int facing=B(0x104);float y=sakuya_sine(-8.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=10.0f;request[1]=F(0x73c)*24.0;int facing=B(0x104);float y=sakuya_sine(-10.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=11.0f;request[1]=F(0x73c)*21.0;int facing=B(0x104);float y=sakuya_sine(-11.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-3.0f;request[1]=F(0x73c)*30.0;int facing=B(0x104);float y=sakuya_sine(3.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-8.0f;request[1]=F(0x73c)*27.0;int facing=B(0x104);float y=sakuya_sine(8.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-10.0f;request[1]=F(0x73c)*24.0;int facing=B(0x104);float y=sakuya_sine(10.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-11.0f;request[1]=F(0x73c)*21.0;int facing=B(0x104);float y=sakuya_sine(11.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
dispatch_character_wave_handle(12);}if(S(0x13e)==1&&!S(0x140)&&!B(0x750)){select_sequence(0);S(0x140)=7;}return;}

case 542:{
if(S(0x13e)==1)landing();F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<=0){select_sequence(1);B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}if(!I(0x6c4))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(S(0x13e)||S(0x142))return;if(S(0x140)==5){phase_counter(50);counter(200,120);I(0x180)=1;float request[3];request[2]=0.0f;F(0x73c)=C(0x606)<4?1.0f:1.15f;
{request[0]=2.0f;request[1]=F(0x73c)*30.0;int facing=B(0x104);float y=sakuya_sine(-2.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=5.0f;request[1]=F(0x73c)*27.0;int facing=B(0x104);float y=sakuya_sine(-5.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=5.5f;request[1]=F(0x73c)*24.0;int facing=B(0x104);float y=sakuya_sine(-5.5f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=4.0f;request[1]=F(0x73c)*21.0;int facing=B(0x104);float y=sakuya_sine(-4.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-2.0f;request[1]=F(0x73c)*30.0;int facing=B(0x104);float y=sakuya_sine(2.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-5.0f;request[1]=F(0x73c)*27.0;int facing=B(0x104);float y=sakuya_sine(5.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-5.5f;request[1]=F(0x73c)*24.0;int facing=B(0x104);float y=sakuya_sine(5.5f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-4.0f;request[1]=F(0x73c)*21.0;int facing=B(0x104);float y=sakuya_sine(4.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
dispatch_character_wave_handle(12);}if(!S(0x142)&&S(0x140)==7)F(0x100)=0.5f;return;}

case 543:{
if(S(0x13e)==1)landing();F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<=0){select_sequence(1);B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}if(!I(0x6c4))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(S(0x13e)||S(0x142))return;if(S(0x140)==5){phase_counter(50);counter(200,120);I(0x180)=1;float request[3];request[2]=0.0f;F(0x73c)=C(0x606)<4?1.0f:1.15f;
{request[0]=3.0f;request[1]=F(0x73c)*30.0;int facing=B(0x104);float y=sakuya_sine(-3.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=8.0f;request[1]=F(0x73c)*27.0;int facing=B(0x104);float y=sakuya_sine(-8.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=10.0f;request[1]=F(0x73c)*24.0;int facing=B(0x104);float y=sakuya_sine(-10.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=11.0f;request[1]=F(0x73c)*21.0;int facing=B(0x104);float y=sakuya_sine(-11.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-3.0f;request[1]=F(0x73c)*30.0;int facing=B(0x104);float y=sakuya_sine(3.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-8.0f;request[1]=F(0x73c)*27.0;int facing=B(0x104);float y=sakuya_sine(8.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-10.0f;request[1]=F(0x73c)*24.0;int facing=B(0x104);float y=sakuya_sine(10.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
{request[0]=-11.0f;request[1]=F(0x73c)*21.0;int facing=B(0x104);float y=sakuya_sine(11.0f)*200.0+F(0xf0)+100.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(812,x,y,facing,1,request,3);}
dispatch_character_wave_handle(12);}if(!S(0x142)&&S(0x140)==7)F(0x100)=0.5f;return;}

case 545:{
landing();B(0x17c)=6;if(!I(0x6c0))B(0x750)=0;ADVANCE_TO(0);if(!ENTRY(1))return;
phase_counter(50);counter(200,120);I(0x180)=1;float request[3]={0.0f,15.0f,0.0f};switch(B(0x60a)){
case 1:{
for(float i=0.0f;i<3.0f;i+=1.0){int facing=B(0x104);float y=i*40.0+F(0xf0)+60.0;float x=(sakuya_sine(i*45.0+45.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<2.0f;i+=1.0){int facing=B(0x104);float y=URAND(250)+F(0xf0);float x=(URAND(100)+50.0+0.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 2:{
for(float i=0.0f;i<4.0f;i+=1.0){int facing=B(0x104);float y=i*40.0+F(0xf0)+40.0;float x=(sakuya_sine(i*45.0+22.5)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<3.0f;i+=1.0){int facing=B(0x104);float y=URAND(250)+F(0xf0);float x=(URAND(100)+50.0+0.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 3:{
for(float i=0.0f;i<5.0f;i+=1.0){int facing=B(0x104);float y=i*40.0+F(0xf0);float x=(sakuya_sine(i*45.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<4.0f;i+=1.0){int facing=B(0x104);float y=URAND(250)+F(0xf0);float x=(URAND(100)+50.0+0.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 4:{
for(float i=0.0f;i<6.0f;i+=1.0){int facing=B(0x104);float y=(i*40.0+F(0xf0))-20.0;float x=(sakuya_sine(i*30.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<5.0f;i+=1.0){int facing=B(0x104);float y=URAND(250)+F(0xf0);float x=(URAND(100)+50.0+0.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
}dispatch_character_wave_handle(15);return;}

case 546:{
landing();B(0x17c)=6;if(!I(0x6c0))B(0x750)=0;ADVANCE_TO(0);if(!ENTRY(1))return;
phase_counter(50);counter(200,120);I(0x180)=1;float request[3]={0.0f,15.0f,0.0f};switch(B(0x60a)){
case 1:{
for(float i=0.0f;i<4.0;i+=1.0){request[0]=45.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0)+40.0;float x=(sakuya_sine(i*45.0+22.5)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<3.0;i+=1.0){request[0]=30.0-i*30.0;int facing=B(0x104);float y=i*40.0+F(0xf0)+60.0;float x=(sakuya_sine(30.0+60.0*i)*120.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 2:{
for(float i=0.0f;i<5.0;i+=1.0){request[0]=60.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0)+20.0;float x=(sakuya_sine(i*45.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<4.0;i+=1.0){request[0]=45.0-30.0*i;int facing=B(0x104);float y=40.0+F(0xf0)+i*40.0;float x=(sakuya_sine(i*60.0)*120.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 3:{
for(float i=0.0f;i<6.0;i+=1.0){request[0]=75.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0);float x=(sakuya_sine(i*36.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<5.0;i+=1.0){request[0]=60.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0)+20.0;float x=(sakuya_sine(i*45.0)*120.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 4:{
for(float i=0.0f;i<7.0;i+=1.0){request[0]=90.0-30.0*i;int facing=B(0x104);float y=(i*40.0+F(0xf0))-20.0;float x=(sakuya_sine(30.0*i)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<6.0;i+=1.0){request[0]=75.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0);float x=(sakuya_sine(i*36.0)*120.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
}dispatch_character_wave_handle(15);return;}

case 547:{
if(S(0x13e)==4)landing();B(0x17c)=6;if(!I(0x6c0))B(0x750)=0;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<4){B(0x47f)=0;zero_motion();F(0xf0)=sakuya_surface(this);select_sequence(4);return;}ADVANCE_TO(0);if(I(0x144))return;if(!S(0x142)&&!S(0x140)&&S(0x13e)==4){set_action_and_finalize(9);return;}if(S(0x142)||S(0x140)||S(0x13e)!=1)return;F(0xf4)=-10.0;F(0xf8)=5.0;F(0x100)=0.5f;
phase_counter(50);counter(200,120);I(0x180)=1;float request[3]={0.0f,15.0f,0.0f};switch(B(0x60a)){
case 1:{
for(float i=0.0f;i<3.0f;i+=1.0){int facing=B(0x104);float y=i*40.0+F(0xf0)+60.0;float x=(sakuya_sine(i*45.0+45.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<2.0f;i+=1.0){int facing=B(0x104);float y=URAND(250)+F(0xf0);float x=(URAND(100)+50.0+0.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 2:{
for(float i=0.0f;i<4.0f;i+=1.0){int facing=B(0x104);float y=i*40.0+F(0xf0)+40.0;float x=(sakuya_sine(i*45.0+22.5)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<3.0f;i+=1.0){int facing=B(0x104);float y=URAND(250)+F(0xf0);float x=(URAND(100)+50.0+0.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 3:{
for(float i=0.0f;i<5.0f;i+=1.0){int facing=B(0x104);float y=i*40.0+F(0xf0);float x=(sakuya_sine(i*45.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<4.0f;i+=1.0){int facing=B(0x104);float y=URAND(250)+F(0xf0);float x=(URAND(100)+50.0+0.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 4:{
for(float i=0.0f;i<6.0f;i+=1.0){int facing=B(0x104);float y=(i*40.0+F(0xf0))-20.0;float x=(sakuya_sine(i*30.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<5.0f;i+=1.0){int facing=B(0x104);float y=URAND(250)+F(0xf0);float x=(URAND(100)+50.0+0.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
}dispatch_character_wave_handle(15);return;}

case 548:{
if(S(0x13e)==4)landing();B(0x17c)=6;if(!I(0x6c0))B(0x750)=0;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<4){B(0x47f)=0;zero_motion();F(0xf0)=sakuya_surface(this);select_sequence(4);return;}ADVANCE_TO(0);if(I(0x144))return;if(!S(0x142)&&!S(0x140)&&S(0x13e)==4){set_action_and_finalize(9);return;}if(S(0x142)||S(0x140)||S(0x13e)!=1)return;F(0xf4)=-10.0;F(0xf8)=5.0;F(0x100)=0.5f;
phase_counter(50);counter(200,120);I(0x180)=1;float request[3]={0.0f,15.0f,0.0f};switch(B(0x60a)){
case 1:{
for(float i=0.0f;i<4.0;i+=1.0){request[0]=45.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0)+40.0;float x=(sakuya_sine(i*45.0+22.5)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<3.0;i+=1.0){request[0]=30.0-i*30.0;int facing=B(0x104);float y=i*40.0+F(0xf0)+60.0;float x=(sakuya_sine(30.0+60.0*i)*120.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 2:{
for(float i=0.0f;i<5.0;i+=1.0){request[0]=60.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0)+20.0;float x=(sakuya_sine(i*45.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<4.0;i+=1.0){request[0]=45.0-30.0*i;int facing=B(0x104);float y=40.0+F(0xf0)+i*40.0;float x=(sakuya_sine(i*60.0)*120.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 3:{
for(float i=0.0f;i<6.0;i+=1.0){request[0]=75.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0);float x=(sakuya_sine(i*36.0)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<5.0;i+=1.0){request[0]=60.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0)+20.0;float x=(sakuya_sine(i*45.0)*120.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
case 4:{
for(float i=0.0f;i<7.0;i+=1.0){request[0]=90.0-30.0*i;int facing=B(0x104);float y=(i*40.0+F(0xf0))-20.0;float x=(sakuya_sine(30.0*i)*150.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
for(float i=0.0f;i<6.0;i+=1.0){request[0]=75.0-30.0*i;int facing=B(0x104);float y=i*40.0+F(0xf0);float x=(sakuya_sine(i*36.0)*120.0-50.0)*C(0x104)+F(0xec);spawn(817,x,y,facing,1,request,3);}
break;}
}dispatch_character_wave_handle(15);return;}

case 560:{if(!S(0x13e)||S(0x13e)==4)landing();B(0x17c)=3;if(ENTRY(2)){F(0xf4)=0.0;F(0xf8)=0.0;}
if(S(0x13e)==1&&I(0x144)>9){float request[3]={10.0f,0.0f,6.0f};spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);request[0]=-10.0f;request[2]=7.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);next_sequence_block();F(0xf4)=750.0;F(0xf8)=30.0;if(C(0x607)>3)F(0xf8)=15.0;F(0x100)=0.25f;dispatch_character_wave_handle(13);return;}
if(S(0x13e)==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){next_sequence_block();zero_motion();F(0xf0)=sakuya_surface(this);return;}}ADVANCE_TO(0);
if(!I(0x144)){if(ENTRY(3)){float request[3]={0.0f,0.0f,8.0f};spawn(813,F(0xec),F(0xf0)+100.0,B(0x104),1,request,3);request[0]=10.0f;request[2]=9.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);request[0]=-10.0f;request[2]=10.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);}if(ENTRY(1)){phase_counter(50);counter(200,120);for(float i=0.0f;i<6.0f;i+=1.0){float request[3]={0.0f,0.0f,i};spawn(813,F(0xec)-8*C(0x104),F(0xf0)+115.0,B(0x104),1,request,3);}}}if(S(0x13e)>=3&&C(0x607)>=4)S(0x4a8)=2;return;}

case 561:{if(!S(0x13e)||S(0x13e)==4)landing();B(0x17c)=3;if(ENTRY(2)){F(0xf4)=0.0;F(0xf8)=0.0;}
if(S(0x13e)==1&&I(0x144)>9){float request[3]={10.0f,0.0f,6.0f};spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);request[0]=-10.0f;request[2]=7.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);next_sequence_block();F(0xf4)=-750.0;F(0xf8)=30.0;if(C(0x607)>3)F(0xf8)=15.0;F(0x100)=0.25f;dispatch_character_wave_handle(13);return;}
if(S(0x13e)==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){next_sequence_block();zero_motion();F(0xf0)=sakuya_surface(this);return;}}ADVANCE_TO(0);
if(!I(0x144)){if(ENTRY(3)){float request[3]={0.0f,0.0f,8.0f};spawn(813,F(0xec),F(0xf0)+100.0,B(0x104),1,request,3);request[0]=10.0f;request[2]=9.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);request[0]=-10.0f;request[2]=10.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);}if(ENTRY(1)){phase_counter(50);counter(200,120);for(float i=0.0f;i<6.0f;i+=1.0){float request[3]={0.0f,0.0f,i};spawn(813,F(0xec)-8*C(0x104),F(0xf0)+115.0,B(0x104),1,request,3);}}}if(S(0x13e)>=3&&C(0x607)>=4)S(0x4a8)=2;return;}

case 562:{if(S(0x13e)==5)landing();B(0x17c)=3;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<5){select_sequence(5);F(0x100)=0.0;B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}if(S(0x13e)<2&&!I(0x6c4))B(0x750)=0;
if(S(0x730)>0&&(S(0x13e)==2||S(0x13e)==3)){if(S(0x730)%4==1){phase_counter(10);I(0x180)=1;{float dx=(PF(0xec)-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);S(0x734)=-static_cast<short>(static_cast<int>(sakuya_atan(dy,dx)));if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;}dispatch_character_wave_handle(9);if(S(0x738)==1){float request[3];double angle=S(0x734)+30.0;request[0]=angle-static_cast<float>(sakuya_random_u32()%60u);request[1]=15.0f;request[2]=URAND(4);spawn(808,44*C(0x104)+F(0xec),F(0xf0)+85.0,B(0x104),1,request,3);}else{float request[3];double angle=S(0x734)+30.0;request[0]=angle-static_cast<float>(sakuya_random_u32()%60u);request[1]=15.0f;request[2]=URAND(4);spawn(808,44*C(0x104)+F(0xec),F(0xf0)+85.0,B(0x104),1,request,3);}}++S(0x730);}ADVANCE_TO(0);if(ENTRY(5)){set_action_and_finalize(9);return;}if(S(0x13e)==1&&I(0x144)>4&&(!B(0x750)||I(0x144)>25))next_sequence_block();if(ENTRY(1)){if(B(0x750)==1)effect(62,F(0xec)-23*C(0x104),F(0xf0)+107.0,B(0x104),1);float request[3]={0.0f,0.0f,4.0f};spawn(808,F(0xec)-23*C(0x104),F(0xf0)+107.0,B(0x104),1,request,3);}if(FRAME(2,2)){S(0x730)=1;counter(200,120);}if(S(0x13e)==3&&((I(0x144)>10&&!B(0x750))||I(0x144)>25))next_sequence_block();if(FRAME(4,5))F(0x100)=0.6f;return;}

case 565:{landing();B(0x17c)=7;if(!S(0x13e)&&I(0x180)==3){float request[3]={0.0f,20.0f,2.0f};spawn(818,F(0xec),F(0xf0)+200.0,1,1,request,3);S(0x48a)=60;next_sequence_block();dispatch_character_wave_handle(16);}ADVANCE_TO(0);if(!I(0x144)){if(ENTRY(1)){set_action_and_finalize(0);return;}if(ENTRY(2)){float request[3];request[1]=20.0f;request[2]=0.0f;
for(float i=0.0f;i<20.0f;i+=1.0){request[0]=i*18.0+176.0;int facing=B(0x104);float angle=-i*18.0;float y=sakuya_sine(angle)*300.0+PF(0xf0)+100.0;float x=sakuya_cosine(angle)*300.0*C(0x104)+PF(0xec);spawn(818,x,y,facing,1,request,3);}
for(float i=0.0f;i<20.0f;i+=1.0){request[0]=i*18.0+184.0;int facing=B(0x104);float angle=-i*18.0;float y=sakuya_sine(angle)*400.0+PF(0xf0)+100.0;float x=sakuya_cosine(angle)*400.0*C(0x104)+PF(0xec);spawn(818,x,y,facing,1,request,3);}
dispatch_character_wave_handle(2);F(0xec)=150*C(0x104)+PF(0xec);F(0xf0)=sakuya_surface(this);}}if(FRAME(0,4)){phase_counter(50);counter(200,120);}return;}

case 566:{landing();B(0x17c)=7;if(!S(0x13e)&&I(0x180)==3){float request[3]={0.0f,20.0f,2.0f};spawn(818,F(0xec),F(0xf0)+200.0,1,1,request,3);S(0x48a)=60;next_sequence_block();dispatch_character_wave_handle(16);}ADVANCE_TO(0);if(!I(0x144)){if(ENTRY(1)){set_action_and_finalize(0);return;}if(ENTRY(2)){float request[3];request[1]=20.0f;request[2]=0.0f;
for(float i=0.0f;i<20.0f;i+=1.0){request[0]=i*18.0+176.0;int facing=B(0x104);float angle=-i*18.0;float y=sakuya_sine(angle)*300.0+PF(0xf0)+100.0;float x=sakuya_cosine(angle)*300.0*C(0x104)+PF(0xec);spawn(818,x,y,facing,1,request,3);}
for(float i=0.0f;i<20.0f;i+=1.0){request[0]=i*18.0+184.0;int facing=B(0x104);float angle=-i*18.0;float y=sakuya_sine(angle)*400.0+PF(0xf0)+100.0;float x=sakuya_cosine(angle)*400.0*C(0x104)+PF(0xec);spawn(818,x,y,facing,1,request,3);}
dispatch_character_wave_handle(2);F(0xec)=150*C(0x104)+PF(0xec);F(0xf0)=sakuya_surface(this);}}if(FRAME(0,4)){phase_counter(50);counter(200,120);}return;}

case 567:{if(S(0x13e)==5)landing();B(0x17c)=7;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())&&S(0x13e)<5){select_sequence(5);F(0x100)=0.0;B(0x47f)=0;F(0xf0)=sakuya_surface(this);zero_motion();return;}if(S(0x13e)<2&&!I(0x6c4))B(0x750)=0;
if(FRAME(2,2)){{float dx=(PF(0xec)-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);S(0x734)=-static_cast<short>(static_cast<int>(sakuya_atan(dy,dx)));if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;}dispatch_character_wave_handle(29);I(0x180)=1;counter(200,60);phase_counter(50);float request[3]={0.0f,0.0f,0.0f};if(S(0x738)==1)spawn(824,48*C(0x104)+F(0xec),F(0xf0)+104.0,B(0x104),1,request,3);else spawn(824,48*C(0x104)+F(0xec),F(0xf0)+104.0,B(0x104),1,request,3);}ADVANCE_TO(0);if(ENTRY(1)){float request[3]={0.0f,0.0f,4.0f};spawn(824,F(0xec)-48*C(0x104),F(0xf0)+104.0,B(0x104),1,request,3);}if(ENTRY(5)){set_action_and_finalize(9);return;}if(S(0x13e)==1&&I(0x144)>10&&(!B(0x750)||I(0x144)>25))next_sequence_block();if(S(0x13e)==3&&I(0x144)>40)next_sequence_block();if(FRAME(4,5))F(0x100)=0.6f;return;}

case 599:{if(S(0x730)>0&&S(0x140)<7&&S(0x730)<12){S(0x734)=static_cast<short>(sakuya_random_u32()%35u);float request[3];request[0]=-20-S(0x734);request[1]=static_cast<short>(sakuya_random_u32()%5u+10);request[2]=0.0f;spawn(807,(S(0x730)+1)*C(0x104)*20+F(0xec),F(0xf0),B(0x104),1,request,3);request[0]=static_cast<float>(sakuya_random_u32()%360u);request[1]=0.0f;request[2]=1.0f;spawn(801,(S(0x730)+1)*C(0x104)*20+F(0xec),F(0xf0),B(0x104),1,request,3);if(S(0x730)==1){dispatch_character_wave_handle(0);counter(200,120);}++S(0x730);}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==5)S(0x730)=1;return;}

case 600:{landing();texture(5,2);if(S(0x13e)==1){if(I(0x144)>35){next_sequence_block();return;}if(!(I(0x144)%2)&&I(0x144)<31){float request[4];request[0]=I(0x144)*12+90.0;request[1]=15.0f;request[2]=0.0f;request[3]=90.0f;{int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(850,x,y,facing,1,request,4);}request[0]=I(0x144)*12+270.0;{int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(850,x,y,facing,1,request,4);}}}ADVANCE_TO(0);if(ENTRY(1))dispatch_character_wave_handle(50);if(FRAME(0,3)){SPELL_FLASH(F(0xec)-23*C(0x104),F(0xf0)+158.0,2);}return;}

case 601:{landing();texture(5,2);if(S(0x13e)==4&&I(0x144)>44)next_sequence_block();ADVANCE_TO(0);if(ENTRY(2)){SPELL_FLASH(26*C(0x104)+F(0xec),F(0xf0)+88.0,3);}if(ENTRY(4)){float request[3]={0.0f,0.0f,0.0f};spawn(851,640.0f,480.0f,1,-2,request,3);dispatch_character_wave_handle(52);S(0x7a6)=300;}return;}

case 602:{if(!S(0x13e)||S(0x13e)==4)landing();texture(5,2);if(S(0x13e)==1){if(!(I(0x144)%4)){float request[3]={0.0f,0.0f,0.0f};spawn(852,60*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);request[2]=1.0f;spawn(852,60*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);dispatch_character_wave_handle(54);}if(I(0x144)>90){next_sequence_block();return;}}
if(S(0x13e)==2||S(0x13e)==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);select_sequence(4);zero_motion();return;}}ADVANCE_TO(0);if(FRAME(0,4)){SPELL_FLASH(30*C(0x104)+F(0xec),F(0xf0)+85.0,3);}if(ENTRY(1)){F(0xf4)=0.5f;F(0xf8)=1.0f;F(0x100)=0.5f;}return;}

case 603:{landing();texture(5,2);if(S(0x13e)==1&&I(0x144)>=61){next_sequence_block();return;}ADVANCE_TO(0);if(ENTRY(1))dispatch_character_wave_handle(51);if(FRAME(0,3)){SPELL_FLASH(F(0xec)-23*C(0x104),F(0xf0)+158.0,4);}if(!ENTRY(1))return;float request[4];request[1]=15.0f;request[2]=0.0f;for(float i=0.0f;i<12.0f;i+=1.0){request[0]=30.0*i+15.0;request[3]=i*4.0+60.0;int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*20.0;float x=sakuya_cosine(-request[0])*20.0*C(0x104)+F(0xec);spawn(853,x,y,facing,1,request,4);}return;}

case 604:{landing();texture(5,2);if(S(0x13e)==1&&I(0x144)>59){next_sequence_block();SPELL_FLASH(26*C(0x104)+F(0xec),F(0xf0)+88.0,5);}if(S(0x13e)==4&&I(0x144)>44)next_sequence_block();ADVANCE_TO(0);if(ENTRY(4)){float request[3]={0.0f,0.0f,0.0f};spawn(854,640.0f,480.0f,1,-2,request,3);dispatch_character_wave_handle(53);S(0x48a)=40;S(0x7a4)=300;}return;}

case 605:{if(!S(0x13e)||S(0x13e)==4)landing();texture(5,2);if(S(0x13e)==1){if(!(I(0x144)%4)){float request[3]={0.0f,0.0f,0.0f};spawn(855,60*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);request[2]=1.0f;{int facing=B(0x104);double baseY=F(0xf0)+300.0;float y=baseY-URAND(400);spawn(855,F(0xec)-640*C(0x104),y,facing,1,request,3);}request[2]=2.0f;spawn(855,60*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);dispatch_character_wave_handle(54);}if(I(0x144)>90){next_sequence_block();return;}}
if(S(0x13e)==2||S(0x13e)==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);select_sequence(4);zero_motion();return;}}ADVANCE_TO(0);if(FRAME(0,4)){SPELL_FLASH(30*C(0x104)+F(0xec),F(0xf0)+85.0,3);}if(ENTRY(1)){F(0xf4)=0.5f;F(0xf8)=0.9f;F(0x100)=0.5f;}return;}

case 606:{landing();texture(5,2);if(S(0x13e)==1&&I(0x144)>=37){next_sequence_block();return;}ADVANCE_TO(0);if(S(0x13e)||S(0x142))return;if(S(0x140)==3){SPELL_FLASH(F(0xec)-23*C(0x104),F(0xf0)+158.0,2);}if(S(0x142)||S(0x140)!=8)return;dispatch_character_wave_handle(15);for(float i=0.0f;i<30.0;i+=1.0){float request[3]={i*12.0,6.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(856,x,y,facing,1,request,3);}return;}

case 607:{if(!S(0x13e)||S(0x13e)==4)landing();texture(5,2);if(S(0x13e)==1){if(!(I(0x144)%2)){float request[3];request[0]=URAND(60);request[0]-=30.0;if(!(I(0x144)%10)){request[1]=URAND(50)*static_cast<double>(0.1f)+15.0;request[2]=1.0f;dispatch_character_wave_handle(2);}else{request[1]=URAND(50)*static_cast<double>(0.1f)+10.0;request[2]=0.0f;}int facing=B(0x104);float y=F(0xf0)+110.0+sakuya_sine(-request[0])*200.0;float x=(sakuya_cosine(-request[0])*200.0-100.0)*C(0x104)+F(0xec);spawn(857,x,y,facing,1,request,3);}if(I(0x144)>90){next_sequence_block();return;}}if(S(0x13e)==2||S(0x13e)==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=sakuya_surface(this);select_sequence(4);zero_motion();return;}}ADVANCE_TO(0);if(FRAME(0,4)){SPELL_FLASH(30*C(0x104)+F(0xec),F(0xf0)+85.0,3);}if(ENTRY(1)){F(0xf4)=0.5f;F(0xf8)=0.9f;F(0x100)=0.5f;}return;}

case 608:{landing();texture(5,2);ADVANCE_TO(0);if(S(0x13e)||S(0x142))return;if(S(0x140)==3){SPELL_FLASH(F(0xec)-35*C(0x104),F(0xf0)+155.0,2);}if(S(0x142)||S(0x140)!=6)return;float request[4];request[0]=2.0f;if(I(0x6b8))request[0]=88.0f;request[1]=100.0f;request[2]=0.0f;request[3]=14.0f;spawn(858,100*C(0x104)+F(0xec),F(0xf0)+110.0,B(0x104),1,request,4);dispatch_character_wave_handle(15);return;}

case 609:{landing();texture(5,2);if(S(0x13e)==1&&I(0x144)>39)next_sequence_block();if(S(0x13e)==4&&I(0x144)>44)next_sequence_block();ADVANCE_TO(0);if(I(0x144))return;if(!S(0x142)&&!S(0x140)&&S(0x13e)==2){S(0x48a)=40;event(23);effect(115,26*C(0x104)+F(0xec),F(0xf0)+88.0,B(0x104),1);sequence_window(0,4,60);S(0x7a4)=0;S(0x7a6)=0;secondary_cycle();}if(!ENTRY(4))return;float request[3]={0.0f,25.0f,0.0f};
spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=-180.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=-60.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=-120.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=60.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=120.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=30.0f;request[1]=5.0f;request[2]=0.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=-150.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=-30.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=-90.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=90.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=150.0f;spawn(859,F(0xec),F(0xf0)+130.0,1,-1,request,3);
request[0]=URAND(360);request[1]=15.0f;request[2]=4.0f;spawn(859,F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);request[1]=15.0f;request[2]=5.0f;spawn(859,F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);request[1]=-15.0f;request[2]=6.0f;spawn(859,F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);dispatch_character_wave_handle(53);return;}

case 656:{texture(5,2);if(S(0x13e)==1&&I(0x144)>=37){next_sequence_block();return;}if(S(0x13e)<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=sakuya_surface(this);select_sequence(3);return;}}ADVANCE_TO(0);if(ENTRY(3)){set_action_and_finalize(9);return;}if(!S(0x13e)&&!S(0x142)){if(S(0x140)==3){SPELL_FLASH(F(0xec)-23*C(0x104),F(0xf0)+158.0,2);}if(!S(0x142)&&S(0x140)==8){for(float i=0.0f;i<30.0;i+=1.0){float request[3]={i*12.0,6.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(856,x,y,facing,1,request,3);}}}if(FRAME(2,1))F(0x100)=0.5f;return;}

case 695:{landing();ADVANCE_TO(0);if(!FRAME(0,8))return;event(55);effect(140,F(0xec),F(0xf0)+100.0,B(0x104),1);effect(140,F(0xec),F(0xf0)+100.0,B(0x104),1);effect(140,F(0xec),F(0xf0)+100.0,B(0x104),1);effect(141,F(0xec),F(0xf0)+100.0,B(0x104),-1);effect(142,F(0xec),F(0xf0),B(0x104),-1);return;}

case 696:{landing();F(0xf4)-=0.5;if(F(0xf4)<0.0)F(0xf4)=0.0;ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3){event(29);B(0x47e)=0;}return;}

case 707:{if(F(0xf4)>12.0){F(0xf4)-=0.5;if(F(0xf4)<12.0)F(0xf4)=12.0;}if(advance()){set_action_and_finalize(700);return;}if(FRAME(0,3)){F(0xf4)=15.0;effect(125,80*C(0x104)+F(0xec),F(0xf0)+80.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+80.0,B(0x104),1);event(31);}if(S(0x13e)==1){if(!(I(0x144)%5)){SMOKE(B(0x104));}if(I(0x144)>30){next_sequence_block();return;}}if(S(0x13e)==2){F(0xf4)-=0.5;if(!(F(0xf4)>=0.0))F(0xf4)=0.0;}return;}

case 708:{if(S(0x13e)==2){landing();F(0xf4)+=2.0;if(F(0xf4)>0.0)F(0xf4)=0.0;}if(!static_cast<unsigned char>(sakuya_on_surface(this))&&!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}if(S(0x13e)<2){F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0;F(0x100)=0.0;F(0xf0)=sakuya_surface(this);select_sequence(2);return;}}if(advance()){set_action_and_finalize(700);return;}if(ENTRY(1)){F(0xf4)=-14.0;F(0xf8)=4.0;effect(125,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}return;}

case 710:{landing();if(S(0x13e)==1&&I(0x144)>=91){next_sequence_block();return;}ADVANCE_TO(700);if(!FRAME(0,7))return;dispatch_character_wave_handle(15);switch(g_sakuya_action_match){
case 0:{for(float i=0.0f;i<15.0;i+=1.0){float request[3]={i*24.0,6.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}break;}
case 1:{for(float i=0.0f;i<20.0;i+=1.0){float request[3]={i*18.0,8.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}break;}
case 2:{for(float i=0.0f;i<30.0;i+=1.0){float request[3]={i*12.0,8.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}break;}
case 3:{for(float i=0.0f;i<30.0;i+=1.0){float request[3]={i*12.0,8.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}for(float i=0.0f;i<10.0;i+=1.0){float request[3]={i*12.0,6.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}break;}
}return;}

case 711:{if(S(0x13e)==4&&I(0x144)>90){next_sequence_block();return;}if(S(0x13e)>0){F(0xf8)-=F(0x100);if(S(0x13e)<5&&F(0xf8)<0.0){F(0xf8)=0.0;F(0xf4)=0.0;}if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=sakuya_surface(this);set_action_and_finalize(709);return;}}if(advance()){set_action_and_finalize(704);F(0x100)=0.25f;return;}if(ENTRY(1)){F(0xf4)=F(0x780);F(0xf8)=F(0x784);F(0x100)=F(0x788);}if(FRAME(3,7)){F(0x100)=0.0;dispatch_character_wave_handle(15);switch(g_sakuya_action_match){
case 0:{for(float i=0.0f;i<15.0;i+=1.0){float request[3]={i*24.0,6.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}break;}
case 1:{for(float i=0.0f;i<20.0;i+=1.0){float request[3]={i*18.0,8.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}break;}
case 2:{for(float i=0.0f;i<30.0;i+=1.0){float request[3]={i*12.0,8.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}break;}
case 3:{for(float i=0.0f;i<30.0;i+=1.0){float request[3]={i*12.0,8.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}for(float i=0.0f;i<10.0;i+=1.0){float request[3]={i*12.0,6.0f,0.0f};int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(900,x,y,facing,1,request,3);}break;}
}}if(FRAME(5,1))F(0x100)=0.25f;return;}

case 720:{landing();if(S(0x13e)==1&&I(0x144)>39)next_sequence_block();if(S(0x13e)==3&&I(0x144)>44)next_sequence_block();ADVANCE_TO(700);if(!ENTRY(3))return;dispatch_character_wave_handle(53);float request[3]={URAND(360),15.0f,4.0f};spawn(901,F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);request[1]=15.0f;request[2]=5.0f;spawn(901,F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);request[1]=-15.0f;request[2]=6.0f;spawn(901,F(0xec),F(0xf0)+130.0,B(0x104),1,request,3);switch(g_sakuya_action_match){
case 0:{request[1]=15.0f;request[2]=0.0f;float angle=URAND(360);for(float i=0.0f;i<4.0f;i+=1.0){request[0]=i*90.0+angle;spawn(901,F(0xec),F(0xf0)+130.0,1,-1,request,3);}return;}
case 1:{request[1]=15.0f;request[2]=0.0f;float angle=URAND(360);for(float i=0.0f;i<5.0f;i+=1.0){request[0]=i*72.0+angle;spawn(901,F(0xec),F(0xf0)+130.0,1,-1,request,3);}return;}
case 2:{request[1]=15.0f;request[2]=0.0f;float angle=URAND(360);for(float i=0.0f;i<6.0f;i+=1.0){request[0]=i*60.0+angle;spawn(901,F(0xec),F(0xf0)+130.0,1,-1,request,3);}return;}
case 3:{request[1]=15.0f;request[2]=0.0f;float angle=URAND(360);for(float i=0.0f;i<8.0f;i+=1.0){request[0]=i*45.0+angle;spawn(901,F(0xec),F(0xf0)+130.0,1,-1,request,3);}return;}
}return;}

case 721:{if(S(0x13e)==4&&I(0x144)>60){next_sequence_block();return;}if(S(0x13e)>0){F(0xf8)-=F(0x100);if(S(0x13e)<5&&F(0xf8)<0.0){F(0xf8)=0.0;F(0xf4)=0.0;}if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=sakuya_surface(this);set_action_and_finalize(709);return;}}if(S(0x730)==1&&!(I(0x144)%4)){float request[3];switch(g_sakuya_action_match){
case 0:if(F(0x740)<4.0f){float dx=(PF(0xec)-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);F(0x744)=-sakuya_atan(dy,dx);for(float i=0.0f;i<3.0f;i+=1.0){request[0]=i*15.0+(F(0x744)-15.0);request[1]=15.0-F(0x740);request[2]=7.0f;int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(901,x,y,facing,1,request,3);}F(0x740)+=1.0;}break;
case 1:if(F(0x740)<6.0f){float dx=(PF(0xec)-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);F(0x744)=-sakuya_atan(dy,dx);for(float i=0.0f;i<3.0f;i+=1.0){request[0]=i*15.0+(F(0x744)-15.0);request[1]=15.0-F(0x740);request[2]=7.0f;int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(901,x,y,facing,1,request,3);}F(0x740)+=1.0;}break;
case 2:if(F(0x740)<8.0f){float dx=(PF(0xec)-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);F(0x744)=-sakuya_atan(dy,dx);for(float i=0.0f;i<3.0f;i+=1.0){request[0]=i*15.0+(F(0x744)-15.0);request[1]=15.0-F(0x740);request[2]=7.0f;int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(901,x,y,facing,1,request,3);}F(0x740)+=1.0;}break;
case 3:if(F(0x740)<10.0f){float dx=(PF(0xec)-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);F(0x744)=-sakuya_atan(dy,dx);for(float i=0.0f;i<3.0f;i+=1.0){request[0]=(F(0x744)-15.0)+i*15.0;request[1]=15.0-F(0x740);request[2]=7.0f;int facing=B(0x104);float y=F(0xf0)+150.0+sakuya_sine(-request[0])*100.0;float x=sakuya_cosine(-request[0])*100.0*C(0x104)+F(0xec);spawn(901,x,y,facing,1,request,3);}F(0x740)+=1.0;}break;
}}if(advance()){set_action_and_finalize(704);F(0x100)=0.25f;return;}if(ENTRY(1)){F(0xf4)=F(0x780);F(0xf8)=F(0x784);F(0x100)=F(0x788);}if(FRAME(3,7)){F(0x100)=0.0;dispatch_character_wave_handle(1);S(0x730)=1;}if(FRAME(5,1))F(0x100)=0.25f;return;}

case 722:{if(!S(0x13e)||S(0x13e)==4)landing();if(ENTRY(2)){F(0xf4)=0.0;F(0xf8)=0.0;}
if(S(0x13e)==1&&I(0x144)>9){float request[3]={10.0f,0.0f,6.0f};spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);request[0]=-10.0f;request[2]=7.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);next_sequence_block();if(B(0x104)==1){if(F(0xec)>640.0)F(0xf4)=-250.0-URAND(450);else F(0xf4)=URAND(450)+250.0;}else{if(F(0xec)>640.0)F(0xf4)=URAND(450)+250.0;else F(0xf4)=-250.0-URAND(450);}F(0xf8)=30.0;F(0x100)=0.25f;dispatch_character_wave_handle(13);return;}
if(S(0x13e)==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){next_sequence_block();zero_motion();F(0xf0)=sakuya_surface(this);return;}}ADVANCE_TO(700);
if(!I(0x144)){if(ENTRY(3)){float request[3]={0.0f,0.0f,8.0f};spawn(813,F(0xec),F(0xf0)+100.0,B(0x104),1,request,3);request[0]=10.0f;request[2]=9.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);request[0]=-10.0f;request[2]=10.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);}if(ENTRY(1)){for(float i=0.0f;i<6.0f;i+=1.0){float request[3]={0.0f,0.0f,i};spawn(813,F(0xec)-8*C(0x104),F(0xf0)+115.0,B(0x104),1,request,3);}}}return;}

case 730:{landing();if(S(0x13e)==1){if(I(0x144)==40){dispatch_character_wave_handle(53);S(0x7a4)=60;PI(0x114)=1;float request[3]={0.0f,0.0f,0.0f};spawn(854,640.0f,480.0f,1,-2,request,3);}if(I(0x144)>99){next_sequence_block();return;}}if(S(0x13e)==4&&I(0x144)>74)next_sequence_block();ADVANCE_TO(700);if(!ENTRY(3))return;float request[3];request[0]=0.0f;switch(g_sakuya_action_match){
case 0:{request[2]=1.0f;for(float i=0.0f;i<6.0;i+=1.0){request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;int facing=B(0x104);float jitter=URAND(20);float y=(i*30.0+F(0xf0)+10.0+jitter)-10.0;float x=(URAND(200)+F(0xec))-100.0;spawn(920,x,y,facing,1,request,3);}for(float i=0.0f;i<5.0;i+=1.0){request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;int facing=B(0x104);float jitter=URAND(20);float y=(F(0xf0)+25.0+i*30.0+jitter)-10.0;float x=(URAND(200)+F(0xec))-50.0;spawn(920,x,y,facing,1,request,3);}break;}
case 1:{request[2]=1.0f;for(float i=0.0f;i<6.0;i+=1.0){request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;int facing=B(0x104);float jitter=URAND(20);float y=(jitter+i*30.0+F(0xf0)+10.0)-10.0;float x=(URAND(200)+F(0xec))-100.0;spawn(920,x,y,facing,1,request,3);}for(float i=0.0f;i<5.0;i+=1.0){request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;int facing=B(0x104);float jitter=URAND(20);float y=(i*30.0+F(0xf0)+25.0+jitter)-10.0;float x=(URAND(200)+F(0xec))-50.0;spawn(920,x,y,facing,1,request,3);}break;}
case 2:{request[2]=1.0f;for(float i=0.0f;i<8.0;i+=1.0){request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;int facing=B(0x104);float jitter=URAND(20);float y=(i*30.0+(F(0xf0)-20.0)+jitter)-10.0;float x=(URAND(200)+F(0xec))-100.0;spawn(920,x,y,facing,1,request,3);}for(float i=0.0f;i<7.0;i+=1.0){request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;int facing=B(0x104);float jitter=URAND(20);float y=(i*30.0+(F(0xf0)-5.0)+jitter)-10.0;float x=(URAND(200)+F(0xec))-50.0;spawn(920,x,y,facing,1,request,3);}break;}
case 3:{request[2]=0.0f;for(float i=0.0f;i<8.0;i+=1.0){request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;int facing=B(0x104);float jitter=URAND(20);float y=(i*30.0+(F(0xf0)-20.0)+jitter)-10.0;float x=(URAND(200)+F(0xec))-100.0;spawn(920,x,y,facing,1,request,3);}for(float i=0.0f;i<7.0;i+=1.0){request[1]=URAND(30)*static_cast<double>(0.1f)+3.0;int facing=B(0x104);float jitter=URAND(20);float y=(i*30.0+(F(0xf0)-5.0)+jitter)-10.0;float x=(URAND(200)+F(0xec))-50.0;spawn(920,x,y,facing,1,request,3);}break;}
}dispatch_character_wave_handle(55);return;}

case 740:{landing();if(S(0x13e)==1){int threshold;switch(g_sakuya_action_match){case 0:case 1:case 2:threshold=70;break;case 3:threshold=60;break;}if(I(0x144)>=threshold){next_sequence_block();dispatch_character_wave_handle(53);S(0x7a4)=60;PI(0x114)=1;float request[3]={0.0f,0.0f,0.0f};spawn(854,640.0f,480.0f,1,-2,request,3);return;}}
if(S(0x13e)==3){if(I(0x144)>59)next_sequence_block();if(!(I(0x144)%2)&&F(0x73c)<20.0f){float mode;switch(g_sakuya_action_match){case 0:mode=2.0f;break;case 1:case 2:mode=1.0f;break;case 3:mode=0.0f;break;}float request[3];request[0]=F(0x73c)*18.0;request[1]=3.0f;request[2]=mode;{int facing=B(0x104);float y=sakuya_sine(180.0-request[0])*350.0+PF(0xf0)+100.0;float x=sakuya_cosine(180.0-request[0])*350.0*C(0x104)+PF(0xec);spawn(930,x,y,facing,1,request,3);}dispatch_character_wave_handle(0);if(static_cast<unsigned>(g_sakuya_action_match)-2u<2u){request[0]=F(0x73c)*18.0+9.0;request[1]=3.0f;request[2]=mode;int facing=B(0x104);float y=sakuya_sine(180.0-request[0])*400.0+PF(0xf0)+100.0;float x=sakuya_cosine(180.0-request[0])*400.0*C(0x104)+PF(0xec);spawn(930,x,y,facing,1,request,3);}F(0x73c)+=1.0;}}if(S(0x13e)==4&&I(0x144)>7)next_sequence_block();ADVANCE_TO(700);return;}

case 770:{ADVANCE_TO(700);if(!FRAME(0,7))return;B(0x655)=1;finalize(-1);texture(2,-1);copy_action_word();S(0x76c)=0;S(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);return;}

case 795:{if(!S(0x13e)){F(0xf8)-=static_cast<double>(0.3f);if(static_cast<unsigned char>(crossed())){event(30);select_sequence(1);F(0xf0)=sakuya_surface(this);zero_motion();return;}}ADVANCE_TO(700);return;}

case 797:{if(S(0x13e)<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){event(30);select_sequence(3);F(0xec)=480.0f;F(0xf0)=sakuya_surface(this);zero_motion();return;}}ADVANCE_TO(0);return;}

case 798:{if(S(0x13e)==1&&I(0x144)>=60){next_sequence_block();return;}if(advance()){set_action_and_finalize(700);return;}if(FRAME(0,1)){float request[3]={10.0f,0.0f,6.0f};spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);request[0]=-10.0f;request[2]=7.0f;spawn(813,F(0xec),F(0xf0),B(0x104),1,request,3);dispatch_character_wave_handle(13);}return;}

default:common_update();return;
}
idle_drift:
 if(!B(0x47e)){zero_motion();advance();return;}
 if(F(0xf4)>0.0){F(0xf4)-=0.5;if(F(0xf4)<0.0){zero_motion();B(0x47e)=0;}}
 if(F(0xf4)<0.0){F(0xf4)+=0.5;if(F(0xf4)>0.0){zero_motion();B(0x47e)=0;advance();return;}}
 advance();return;
dash_landed:zero_motion();F(0xf0)=sakuya_surface(this);set_action_and_finalize(10);return;
landed:set_action_and_finalize(10);F(0xf0)=sakuya_surface(this);zero_motion();return;
}
}
