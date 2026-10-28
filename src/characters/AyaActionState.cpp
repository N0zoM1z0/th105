#include "characters/AyaActionState.hpp"
namespace th105 {
#define URAND(n) static_cast<float>(static_cast<unsigned>(aya_random(n)))
#define JITTER_ANGLE(p,opposite) do {if(opposite)(p)[0]=URAND(40)*static_cast<double>(0.1f)+(F(0x740)+180.0)-2.0;else(p)[0]=URAND(40)*static_cast<double>(0.1f)+F(0x740)-2.0;}while(0)
#define WIDE_ANGLE(p,opposite) do {if(opposite)(p)[0]=URAND(30)+(F(0x740)+180.0)-15.0;else(p)[0]=URAND(30)+F(0x740)-15.0;}while(0)
#define ORBIT_SPAWN(p,radius,range,offset) do {double baseY=aya_sine(180.0-(p)[0])*(radius)+(F(0xf0)+100.0);double cosine=aya_cosine(180.0-(p)[0])*(radius);int facing=B(0x104);double baseX=cosine*static_cast<signed char>(facing)+F(0xec);float y=(URAND(range)+baseY)-(offset);float x=(URAND(range)+baseX)-(offset);spawn(903,x,y,facing,1,p,3);}while(0)
#define FIELD(T,o) (*reinterpret_cast<T *>(raw+(o)))
#define F(o) FIELD(float,o)
#define I(o) FIELD(int,o)
#define U(o) FIELD(unsigned,o)
#define S(o) FIELD(short,o)
#define US(o) FIELD(unsigned short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define PEER FIELD(AyaActionStateView *,0x170)
#define PF(o) (*reinterpret_cast<float *>(reinterpret_cast<unsigned char *>(PEER)+(o)))
#define PS(o) (*reinterpret_cast<short *>(reinterpret_cast<unsigned char *>(PEER)+(o)))
#define PB(o) (*reinterpret_cast<unsigned char *>(reinterpret_cast<unsigned char *>(PEER)+(o)))
#define MOTION reinterpret_cast<AyaActionScratch *>(raw+4)
#define ENTRY(n) (I(0x144)==0&&S(0x142)==0&&S(0x140)==0&&S(0x13e)==(n))
#define FRAME(n,f) (S(0x13e)==(n)&&S(0x142)==0&&S(0x140)==(f))
#define ADVANCE_TO(n) do {if(advance())set_action_and_finalize(n);}while(0)
#define CHOOSE_FOLLOWUP(up) do {if(C(0x104)*I(0x6b4)>0){if(I(0x6b8)<0)S(0x730)=1;if(I(0x6b8)>0)S(0x730)=(up)?-1:0;if(!I(0x6b8))S(0x730)=0;}if(!I(0x6b4)){if(I(0x6b8)<0)S(0x730)=2;if(I(0x6b8)>0)S(0x730)=(up)?-2:0;if(!I(0x6b8))S(0x730)=0;}if(C(0x104)*I(0x6b4)<0){B(0x104)=-B(0x104);if(I(0x6b8)<0)S(0x730)=1;if(I(0x6b8)>0)S(0x730)=(up)?-1:0;if(!I(0x6b8))S(0x730)=0;}}while(0)
#define AIM_SHORT() do {float dx=(static_cast<double>(PF(0xec))-F(0xec))*C(0x104);float dy=PF(0xf0)-F(0xf0);S(0x734)=static_cast<short>(-static_cast<int>(aya_atan(dy,dx)));}while(0)
#define SMOKE(dir) do {double base=F(0xec)+50.0;int facing=(dir);effect(124,base-static_cast<float>(aya_random_u32()%100u),static_cast<float>(aya_random_u32()%200u)+F(0xf0),facing,1);}while(0)
#define FALL_LAND() do {F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()))goto landed;}while(0)
void AyaActionStateView::dispatch_action_state_vslot28(){
 unsigned char *raw=reinterpret_cast<unsigned char *>(this);
 // Native two-word request homes retain the observed forwarded count of three.
 // The third-word meaning and original aggregate type remain unknown.
 float request530[2],request532[2];
 float *paired_request;
S(0x7a0)=0;S(0x7a2)=101;
if(S(0x13c)>149&&S(0x13c)<159&&!B(0x751)){
 B(0x751)=1;
 if(S(0x13c)>149&&S(0x13c)<154)spawn(998,57*C(0x104)+F(0xec),F(0xf0)+94.0,B(0x104),1,0,0);
 if(S(0x13c)>153&&S(0x13c)<158)spawn(998,57*C(0x104)+F(0xec),F(0xf0)+60.0,B(0x104),1,0,0);
 if(S(0x13c)==158)spawn(998,57*C(0x104)+F(0xec),F(0xf0)+100.0,B(0x104),1,0,0);
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

case 4:{landing();F(0xf4)=5.5;advance();return;}

case 5:{landing();F(0xf4)=-5.5;advance();return;}

case 6:{
 if(!S(0x13e)){landing();if(!S(0x13e)&&!B(0x47e))zero_motion();}
 if(S(0x13e)>0){FALL_LAND();}
 advance();if(!FRAME(1,0))return;
 F(0xf4)=0.0;F(0xf8)=18.0;F(0x100)=0.75f;B(0x47e)=0;return;
}

case 7:{
 if(!S(0x13e)){landing();if(!S(0x13e)&&!B(0x47e))zero_motion();}
 if(S(0x13e)>0){FALL_LAND();}
 advance();if(!FRAME(1,0))return;
 F(0xf4)=8.0;F(0xf8)=18.0;F(0x100)=0.75f;B(0x47e)=0;return;
}

case 8:{
 if(!S(0x13e)){landing();if(!S(0x13e)&&!B(0x47e))zero_motion();}
 if(S(0x13e)>0){FALL_LAND();}
 advance();if(!FRAME(1,0))return;
 F(0xf4)=-8.0;F(0xf8)=18.0;F(0x100)=0.75f;B(0x47e)=0;return;
}

case 9:{if(F(0x100)==0.0)F(0x100)=0.6f;FALL_LAND();advance();return;}

case 10:{landing();zero_motion();if(advance()){if(I(0x6b8))set_action_and_finalize(2);else set_action_and_finalize(0);}return;}

case 197:{
 if((!S(0x13e)&&S(0x140)<5)||S(0x13e)==2)landing();
 if(!S(0x142)&&S(0x140)==5)spawn(990,F(0xec),F(0xf0),B(0x104),1,0,0);
 if(S(0x13e)<2)F(0xf8)-=F(0x100);
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){F(0xf0)=aya_surface(this);zero_motion();select_sequence(2);return;}
 if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
 if(FRAME(2,2)){if(PF(0xec)<F(0xec))C(0x104)=-1;if(PF(0xec)>F(0xec))C(0x104)=1;}
 if(FRAME(0,5)){F(0xf8)=4.8f;F(0xf4)=15.0;F(0x100)=0.4f;}return;
}

case 198:{
 if((!S(0x13e)&&S(0x140)<5)||S(0x13e)==2)landing();
 if(!S(0x142)&&S(0x140)==5)spawn(990,F(0xec),F(0xf0),B(0x104),1,0,0);
 if(S(0x13e)<2)F(0xf8)-=F(0x100);
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){F(0xf0)=aya_surface(this);zero_motion();select_sequence(2);return;}
 if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
 if(FRAME(2,2)){if(PF(0xec)<F(0xec))C(0x104)=-1;if(PF(0xec)>F(0xec))C(0x104)=1;}
 if(FRAME(0,5)){F(0xf8)=4.8f;F(0xf4)=-15.0;F(0x100)=0.4f;}return;
}

case 199:{
 landing();if(!S(0x142)&&S(0x140)==5)spawn(990,F(0xec),F(0xf0),B(0x104),1,0,0);
 if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
 if(FRAME(0,17)){if(PF(0xec)<F(0xec))C(0x104)=-1;if(PF(0xec)>F(0xec))C(0x104)=1;}return;
}

case 200:{
 landing();B(0x47e)=1;if(F(0xf4)>10.0){F(0xf4)-=0.5;if(F(0xf4)<10.0)F(0xf4)=10.0;}advance();
 if(S(0x13e)==1){if(!(I(0x144)%5)){SMOKE(B(0x104));}if(I(0x6b8)<0){if(I(0x6b4)*C(0x104)<=0)set_action_and_finalize(211);else set_action_and_finalize(212);return;}short count=++S(0x730);if((I(0x6b4)*C(0x104)<=0&&count>5)||count>45){set_action_and_finalize(204);return;}}
 if(ENTRY(1)){F(0xf4)=18.5;effect(125,80*C(0x104)+F(0xec),F(0xf0)+80.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+80.0,B(0x104),1);event(31);}return;
}

case 201:{
 if(!S(0x13e)||S(0x13e)==3)landing();
 if(S(0x13e)==3){F(0xf4)+=2.0;if(F(0xf4)>0.0)F(0xf4)=0.0;}
 if(!static_cast<unsigned char>(aya_on_surface(this))&&!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}
 if(S(0x13e)<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0;F(0xf0)=aya_surface(this);select_sequence(3);return;}}
 if(advance()){set_action_and_finalize(0);F(0xf4)=0.0;return;}
 if(ENTRY(1)&&!S(0x730)){S(0x730)=1;F(0xf4)=-17.0;F(0xf8)=3.5;F(0x100)=0.75f;effect(125,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}return;
}

case 202:{
 F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()))goto dash_landed;
 if(S(0x13e)==1&&!(I(0x144)%5)){SMOKE(B(0x104));}advance();
 if(FRAME(0,2)){S(0x730)=0;F(0xf4)=12.0;F(0xf8)=4.0;F(0x100)=0.45f;effect(125,80*C(0x104)+F(0xec),F(0xf0)+110.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+110.0,B(0x104),1);event(31);}
 if(ENTRY(2))flip();return;
}

case 203:{
 F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()))goto dash_landed;
 if(S(0x13e)==1&&!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}advance();
 if(FRAME(0,3)){F(0xf4)=-12.0;F(0xf8)=4.0;F(0x100)=0.45f;effect(125,F(0xec),F(0xf0)+120.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+120.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}if(ENTRY(2))flip();return;
}

case 204:{landing();F(0xf4)-=1.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}if(advance()){set_action_and_finalize(0);B(0x47e)=0;}return;}

case 208:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(aya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;F(0xf4)=0.0;F(0xf8)=22.5;F(0x100)=0.85f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 209:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(aya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;F(0xf4)=10.0;F(0xf8)=18.0;F(0x100)=0.85f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 210:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(aya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;F(0xf4)=-10.0;F(0xf8)=18.0;F(0x100)=0.85f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 211:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(aya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;F(0xf4)=3.0;F(0xf8)=18.0;F(0x100)=0.85f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 212:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(aya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;F(0xf4)=12.0;F(0xf8)=18.0;F(0x100)=0.85f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 214:{
 if(advance()){set_action_and_finalize(9);return;}
 if(!I(0x144)){
  if(!S(0x142)&&!S(0x140)&&S(0x13e)==6){set_action_and_finalize(9);return;}
  if(ENTRY(1))event(31);
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
  if(S(0x734)>0)F(0x740)+=I(0x4b8)?1.0:2.0;
  if(S(0x734)<0)F(0x740)-=I(0x4b8)?1.0:2.0;
  F(0xf4)=aya_cosine(F(0x740))*F(0x73c);
  F(0xf8)=aya_sine(F(0x740))*F(0x73c);
  if(F(0xf0)>680.0&&F(0xf8)>0.0)F(0xf8)=0.0;
  F(0x73c)+=static_cast<double>(0.3f);if(F(0x73c)>12.0)F(0x73c)=12.0;
  if(I(0x4b8))counter(10,1);else counter(5,1);
  F(0x12c)=-F(0x740);if(F(0xf4)<0.0)F(0x12c)=180.0-F(0x740);
  if(F(0xf4)<0.0&&S(0x13e)==1)select_sequence(3);
  if(0.0<=F(0xf4)&&S(0x13e)==3)select_sequence(1);
  if(F(0xf4)<0.0&&S(0x13e)==2)select_sequence(4);
  if(0.0<=F(0xf4)&&S(0x13e)==4)select_sequence(2);
  if(I(0x144)%5==1){int facing=B(0x104);float y=aya_sine(F(0x740))*100.0+F(0xf0)+100.0;float x=aya_cosine(F(0x740))*100.0*C(0x104)+F(0xec);effect(125,x,y,facing,1);}
  if(!((I(0x6c8)||S(0x736)<=10)&&S(0x482)>0)){
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
  F(0xf0)=aya_surface(this);F(0xf8)=0.0;F(0x100)=0.0;
  if(S(0x13e)>=5){set_action_and_finalize(10);zero_motion();}
  else{MOTION->reset();set_action_and_finalize(215);}
 }return;
}

case 215:{landing();if(F(0xf4)>0.0){F(0xf4)-=0.75;if(F(0xf4)<0.0)F(0xf4)=0.0;}if(F(0xf4)<0.0){F(0xf4)+=0.75;if(F(0xf4)>0.0)F(0xf4)=0.0;}ADVANCE_TO(0);return;}

case 220:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(aya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;F(0xf4)=0.0;F(0xf8)=22.5;F(0x100)=0.85f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 221:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(aya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;F(0xf4)=10.0;F(0xf8)=18.0;F(0x100)=0.85f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 222:{
 if(!S(0x13e))landing();if(static_cast<unsigned char>(crossed()))goto landed;
 if(static_cast<unsigned char>(aya_on_surface(this))||F(0xf8)>0.0)S(0x4ae)=2;
 if(S(0x13e)>0){F(0xf8)-=F(0x100);if(F(0xf8)<-20.0)F(0xf8)=-20.0;}
 if(S(0x13e)==1&&F(0xf8)<4.0)select_sequence(2);
 advance();if(!ENTRY(1))return;F(0xf4)=-10.0;F(0xf8)=18.0;F(0x100)=0.85f;B(0x47e)=0;effect(63,F(0xec),F(0xf0),B(0x104),1);return;
}

case 223:{
 landing();B(0x47e)=1;advance();
 if(S(0x13e)==1){if(!(I(0x144)%5)){SMOKE(B(0x104));}short count=++S(0x730);if((I(0x6b4)*C(0x104)<=0&&count>15)||count>45){set_action_and_finalize(204);return;}}
 if(ENTRY(1)){F(0xf4)=7.0;effect(125,80*C(0x104)+F(0xec),F(0xf0)+80.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+80.0,B(0x104),1);event(31);}return;
}

case 224:{
 if(!S(0x13e)||S(0x13e)==3)landing();
 if(S(0x13e)==3){F(0xf4)+=2.0;if(F(0xf4)>0.0)F(0xf4)=0.0;}
 if(!static_cast<unsigned char>(aya_on_surface(this))&&!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}
 if(S(0x13e)<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0;F(0xf0)=aya_surface(this);select_sequence(3);return;}}
 if(advance()){set_action_and_finalize(0);F(0xf4)=0.0;return;}
 if(ENTRY(1)&&!S(0x730)){S(0x730)=1;F(0xf4)=-17.0;F(0xf8)=4.0;F(0x100)=0.75f;effect(125,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+80.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}return;
}

case 225:{
 F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()))goto dash_landed;
 if(S(0x13e)==2&&!(I(0x144)%5)){SMOKE(static_cast<unsigned char>(-B(0x104)));}ADVANCE_TO(9);
 if(ENTRY(1)){F(0xf4)=-12.0;F(0xf8)=4.0;F(0x100)=0.45f;effect(125,F(0xec),F(0xf0)+120.0,static_cast<unsigned char>(-B(0x104)),1);effect(126,F(0xec),F(0xf0)+120.0,static_cast<unsigned char>(-B(0x104)),1);event(31);}return;
}

case 226:{
 F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()))goto dash_landed;
 if(S(0x13e)==1&&!(I(0x144)%5)){SMOKE(B(0x104));}ADVANCE_TO(9);
 if(ENTRY(1)){S(0x730)=0;F(0xf4)=12.0;F(0xf8)=4.0;F(0x100)=0.45f;effect(125,80*C(0x104)+F(0xec),F(0xf0)+110.0,B(0x104),1);effect(126,F(0xec),F(0xf0)+110.0,B(0x104),1);event(31);}
 if(ENTRY(2))flip();return;
}

case 300:{landing();if(directional(0))return;if(B(0x47e)){F(0xf4)-=0.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==2){event(27);B(0x47e)=0;}return;}

case 301:{landing();if(directional(0))return;if(B(0x47e)){F(0xf4)-=0.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3){F(0xf4)=10.0;event(27);B(0x47e)=0;}if(S(0x140)>3){F(0xf4)-=1.0;if(F(0xf4)<0.0)F(0xf4)=0.0;}return;}

case 302:{
 landing();if(directional(1))return;if(S(0x140)<4&&!I(0x6bc))B(0x750)=0;
 if(!S(0x13e)){if(F(0xf4)>0.0)F(0xf4)-=1.5;if(F(0xf4)<0.0)F(0xf4)=0.0;if(!S(0x142)){if(S(0x140)==4)F(0xf4)=15.5;if(!S(0x142)&&S(0x140)==6)event(27);}}
 if(S(0x13e)==1){if(F(0xf4)>0.0)F(0xf4)-=1.5;if(F(0xf4)<0.0)F(0xf4)=0.0;if(!S(0x142)){if(S(0x140)==1)F(0xf4)=25.0;if(!S(0x142)&&S(0x140)==3)event(27);}}
 ADVANCE_TO(0);if(ENTRY(1))set_action_and_finalize(0);
 if(FRAME(0,4)&&B(0x750)==1){effect(62,7*C(0x104)+F(0xec),F(0xf0)+180.0,B(0x104),1);next_sequence_block();}return;
}

case 303:{landing();if(directional(0))return;if(C(0x47e)>0){F(0xf4)-=static_cast<double>(0.6f);if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}ADVANCE_TO(2);if(!S(0x142)&&S(0x140)==2)event(27);return;}

case 304:{
 landing();if(directional(1))return;if(S(0x140)<4&&!I(0x6bc))B(0x750)=0;
 if(advance()||ENTRY(1)){set_action_and_finalize(2);return;}
 if(!S(0x13e)){
  if(!S(0x142)&&S(0x140)==3){if(B(0x750)==1){next_sequence_block();effect(62,64*C(0x104)+F(0xec),F(0xf0)+108.0,B(0x104),1);return;}F(0xf4)=10.0;event(28);}
  if(!S(0x142)&&S(0x140)==5)F(0xf4)=5.0;
  if(S(0x140)>4){F(0xf4)-=0.75;if(F(0xf4)<0.0)F(0xf4)=0.0;}
 }
 if(S(0x13e)==1){if(!S(0x142)){if(S(0x140)==1){F(0xf4)=20.0;event(28);}if(!S(0x142)&&S(0x140)==3)F(0xf4)=10.0;}if(S(0x140)>=3){F(0xf4)-=0.75;if(F(0xf4)<0.0)F(0xf4)=0.0;}}return;
}

case 305:{landing();if(directional(1))return;F(0xf4)-=0.75;if(F(0xf4)<0.0)F(0xf4)=0.0;ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3)event(27);return;}

case 306:{FALL_LAND();ADVANCE_TO(9);if(!S(0x142)&&S(0x140)==2)event(27);return;}

case 307:{FALL_LAND();ADVANCE_TO(9);if(S(0x140)>2&&S(0x140)<8){MOTION->set_oriented_components(-20.0f,F(0x73c));F(0x73c)-=1.5;if(F(0x73c)<6.0)F(0x74c)=6.0;}if(!S(0x142)){if(S(0x140)==3)event(28);if(!S(0x142)&&S(0x140)==8)F(0x100)=0.6f;}return;}

case 308:{if(S(0x13e)==2)landing();if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;}ADVANCE_TO(0);if(FRAME(0,4)){dispatch_character_wave_handle(14);F(0xf4)=6.0;F(0xf8)=-18.0;}return;}

case 309:{if(!S(0x13e)){FALL_LAND();}ADVANCE_TO(0);if(ENTRY(1))set_action_and_finalize(9);if(!S(0x13e)&&!S(0x142)){if(S(0x140)==3){event(29);F(0xf8)=7.5;F(0x100)=0.75f;}if(!S(0x142)&&S(0x140)==7)F(0x100)=0.5f;}return;}

case 310:{
 if(I(0x180)&&++S(0x730)>5){I(0x180)=0;S(0x730)=0;}
 if(S(0x13e)==1){if(!I(0x144))F(0xf4)=15.0;if(!(I(0x144)%8))event(27);if(I(0x180)&&++S(0x730)>5){I(0x180)=0;S(0x730)=0;}if(I(0x144)>30){next_sequence_block();F(0xf8)=6.0;F(0xf4)*=0.5;}}
 if(S(0x13e)==2){F(0xf8)-=F(0x100);double nextY=static_cast<double>(F(0xf8))+F(0xf0);if(nextY<=aya_surface(this)&&F(0xf8)<0.0){F(0xf8)=0.0;F(0xf0)=aya_surface(this);set_action_and_finalize(9);return;}}
 ADVANCE_TO(9);return;
}

case 320:{landing();if(directional(0))return;if(B(0x47e)){F(0xf4)-=0.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==2){event(27);B(0x47e)=0;}return;}

case 321:{landing();if(directional(0))return;if(B(0x47e)){F(0xf4)-=0.5;if(F(0xf4)<0.0){F(0xf4)=0.0;B(0x47e)=0;}}ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==3){F(0xf4)=10.0;event(27);B(0x47e)=0;}if(S(0x140)>3){F(0xf4)-=1.0;if(F(0xf4)<0.0)F(0xf4)=0.0;}return;}

case 322:{landing();if(directional(1))return;if(!S(0x13e)){if(F(0xf4)>0.0)F(0xf4)-=1.5;if(F(0xf4)<0.0)F(0xf4)=0.0;if(!S(0x142)){if(S(0x140)==4)F(0xf4)=15.5;if(!S(0x142)&&S(0x140)==6)event(27);}}ADVANCE_TO(0);return;}

case 400:{
 landing();if(S(0x13e)<2&&!I(0x6c0))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==3&&B(0x750)==1){next_sequence_block();effect(62,F(0xec)+0.0,F(0xf0)+216.0,B(0x104),1);return;}
  if(S(0x140)==4){phase_counter(10);AIM_SHORT();if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;counter(200,45);I(0x180)=1;
   float packet[3]={static_cast<float>(S(0x734)),20.0f,0.0f};
   spawn(800,83*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);dispatch_character_wave_handle(0);
  }
 }
 if(FRAME(1,2)){phase_counter(30);AIM_SHORT();if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;counter(200,45);I(0x180)=1;
  float packet[3]={static_cast<float>(S(0x734)),20.0f,0.0f};
  spawn(800,83*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);
  packet[0]=S(0x734)+15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,83*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);
  packet[0]=S(0x734)-15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,83*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);dispatch_character_wave_handle(0);
 }return;
}

case 401:{
 landing();if(S(0x13e)<2&&!I(0x6c0))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==3&&B(0x750)==1){next_sequence_block();effect(62,F(0xec)+0.0,F(0xf0)+216.0,B(0x104),1);return;}
  if(S(0x140)==4){AIM_SHORT();if(S(0x734)<-60)S(0x734)=-60;if(S(0x734)>-30)S(0x734)=-30;counter(200,45);I(0x180)=1;phase_counter(10);
   float packet[3]={static_cast<float>(S(0x734)),20.0f,0.0f};
   spawn(800,83*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);dispatch_character_wave_handle(0);
  }
 }
 if(FRAME(1,2)){AIM_SHORT();if(S(0x734)>-30)S(0x734)=-30;if(S(0x734)<-60)S(0x734)=-60;counter(200,45);I(0x180)=1;phase_counter(30);
  float packet[3]={static_cast<float>(S(0x734)),20.0f,0.0f};
  spawn(800,83*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);
  packet[0]=S(0x734)+15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,83*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);
  packet[0]=S(0x734)-15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,83*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);dispatch_character_wave_handle(0);
 }return;
}

case 402:{landing();ADVANCE_TO(2);if(!S(0x142)&&S(0x140)==4){dispatch_character_wave_handle(1);phase_counter(30);I(0x180)=1;counter(200,45);float packet[3]={0.0f,20.0f,0.0f};spawn(807,100*C(0x104)+F(0xec),F(0xf0)+70.0,B(0x104),1,packet,3);}return;}

case 404:{
 if(S(0x13e)==2)landing();if(S(0x13e)<2&&!I(0x6c0))B(0x750)=0;
 if((!S(0x13e)&&S(0x140)>6)||(S(0x13e)==1&&S(0x140)>4))F(0xf8)-=F(0x100);
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;}
 ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}

 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==3&&B(0x750)==1){next_sequence_block();effect(62,F(0xec)-14*C(0x104),F(0xf0)+226.0,B(0x104),1);return;}
  if(S(0x140)==4){AIM_SHORT();if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;counter(200,45);I(0x180)=1;phase_counter(10);
   float packet[3]={static_cast<float>(S(0x734)),20.0f,0.0f};
   spawn(800,70*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);dispatch_character_wave_handle(0);
  }
 }
 if(FRAME(1,2)){AIM_SHORT();if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;counter(200,45);I(0x180)=1;phase_counter(30);
  float packet[3]={static_cast<float>(S(0x734)),20.0f,0.0f};
  spawn(800,70*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);
  packet[0]=S(0x734)+15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,70*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);
  packet[0]=S(0x734)-15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,70*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);dispatch_character_wave_handle(0);
 }return;
}

case 406:{
 if(S(0x13e)==2)landing();if(S(0x13e)<2&&!I(0x6c0))B(0x750)=0;
 if((!S(0x13e)&&S(0x140)>6)||(S(0x13e)==1&&S(0x140)>4))F(0xf8)-=F(0x100);
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;}
 ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}

 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==3&&B(0x750)==1){next_sequence_block();effect(62,F(0xec)-14*C(0x104),F(0xf0)+226.0,B(0x104),1);return;}
  if(S(0x140)==4){AIM_SHORT();if(S(0x734)<20)S(0x734)=20;if(S(0x734)>40)S(0x734)=40;counter(200,45);I(0x180)=1;phase_counter(10);
   float packet[3]={static_cast<float>(S(0x734)),20.0f,0.0f};
   spawn(800,70*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);dispatch_character_wave_handle(0);
  }
 }
 if(FRAME(1,2)){AIM_SHORT();if(S(0x734)<20)S(0x734)=20;if(S(0x734)>40)S(0x734)=40;counter(200,45);I(0x180)=1;phase_counter(30);
  float packet[3]={static_cast<float>(S(0x734)),20.0f,0.0f};
  spawn(800,70*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);
  packet[0]=S(0x734)+15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,70*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);
  packet[0]=S(0x734)-15.0;packet[1]=20.0f;packet[2]=0.0f;
  spawn(800,70*C(0x104)+F(0xec),F(0xf0)+126.0,B(0x104),1,packet,3);dispatch_character_wave_handle(0);
 }return;
}

case 408:{landing();F(0xf4)-=0.5;if(F(0xf4)<0.0)F(0xf4)=0.0;ADVANCE_TO(0);if(!S(0x142)&&S(0x140)==6)event(29);return;}

case 409:{F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=aya_surface(this);return;}ADVANCE_TO(9);return;}

case 410:{
 landing();if(S(0x13e)<2&&!I(0x6c4))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==4&&B(0x750)==1){next_sequence_block();effect(62,7*C(0x104)+F(0xec),F(0xf0)+180.0,B(0x104),1);}
  if(!S(0x142)&&S(0x140)==6){counter(200,60);I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(2);float packet[3]={-40.0f,4.0f,0.0f};spawn(801,110*C(0x104)+F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);}
 }
 if(FRAME(1,3)){counter(200,60);I(0x180)=1;phase_counter(50);AIM_SHORT();if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;dispatch_character_wave_handle(2);
  float packet[3]={50.0f,-4.0f,0.0f};spawn(801,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);
  packet[0]=-50.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(801,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);
 }return;
}

case 411:{
 landing();if(S(0x13e)<2&&!I(0x6c4))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}
 if(FRAME(0,6)){counter(200,60);I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(3);float packet[3]={0.0f,25.0f,0.0f};spawn(804,110*C(0x104)+F(0xec),F(0xf0),B(0x104),1,packet,3);}
 if(FRAME(1,3)){counter(200,60);I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(3);float packet[3]={0.0f,25.0f,0.0f};spawn(804,110*C(0x104)+F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
}

case 412:{
 landing();if(S(0x13e)<2&&!I(0x6c4))B(0x750)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==4&&B(0x750)==1){next_sequence_block();effect(62,7*C(0x104)+F(0xec),F(0xf0)+180.0,B(0x104),1);}
  if(!S(0x142)&&S(0x140)==6){counter(200,60);I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(2);float packet[3]={40.0f,-4.0f,0.0f};spawn(801,110*C(0x104)+F(0xec),F(0xf0)+50.0,B(0x104),1,packet,3);}
 }
 if(FRAME(1,3)){counter(200,60);I(0x180)=1;phase_counter(50);AIM_SHORT();if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;dispatch_character_wave_handle(2);
  float packet[3]={50.0f,-4.0f,0.0f};spawn(801,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);
  packet[0]=-50.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(801,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);
 }return;
}

case 414:{
 if(S(0x13e)==2)landing();
 if(S(0x13e)<2){if((!S(0x13e)&&S(0x140)>8)||(S(0x13e)==1&&S(0x140)>5))F(0xf8)-=F(0x100);if(!I(0x6c4))B(0x750)=0;if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();F(0xf0)=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(ENTRY(2)){set_action_and_finalize(9);return;}

 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==4&&B(0x750)==1){next_sequence_block();effect(62,7*C(0x104)+F(0xec),F(0xf0)+187.0,B(0x104),1);}
  if(!S(0x142)&&S(0x140)==6){counter(200,60);I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(2);float packet[3]={-50.0f,4.0f,0.0f};spawn(801,110*C(0x104)+F(0xec),F(0xf0)+156.0,B(0x104),1,packet,3);}
 }
 if(FRAME(1,3)){counter(200,60);I(0x180)=1;phase_counter(50);AIM_SHORT();if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;dispatch_character_wave_handle(2);
  float packet[3]={50.0f,-4.0f,0.0f};spawn(801,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);
  packet[0]=-50.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(801,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);
 }return;
}

case 415:{
 if(S(0x13e)==2)landing();if(S(0x13e)<2){if((!S(0x13e)&&S(0x140)>8)||(S(0x13e)==1&&S(0x140)>5))F(0xf8)-=F(0x100);if(!I(0x6c4))B(0x750)=0;if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();F(0xf0)=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}
 if(!S(0x142)&&S(0x140)==6){counter(200,60);I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(3);float packet[3]={0.0f,25.0f,0.0f};spawn(804,110*C(0x104)+F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
}

case 416:{
 if(S(0x13e)==2)landing();
 if(S(0x13e)<2){if((!S(0x13e)&&S(0x140)>8)||(S(0x13e)==1&&S(0x140)>5))F(0xf8)-=F(0x100);if(!I(0x6c4))B(0x750)=0;if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();F(0xf0)=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(ENTRY(2)){set_action_and_finalize(9);return;}

 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==4&&B(0x750)==1){next_sequence_block();effect(62,7*C(0x104)+F(0xec),F(0xf0)+187.0,B(0x104),1);}
  if(!S(0x142)&&S(0x140)==6){counter(200,60);I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(2);float packet[3]={50.0f,-4.0f,0.0f};spawn(801,110*C(0x104)+F(0xec),F(0xf0)+50.0,B(0x104),1,packet,3);}
 }
 if(FRAME(1,3)){counter(200,60);I(0x180)=1;phase_counter(50);AIM_SHORT();if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;dispatch_character_wave_handle(2);
  float packet[3]={50.0f,-4.0f,0.0f};spawn(801,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);
  packet[0]=-50.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(801,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);
 }return;
}

case 418:{
 if((!S(0x13e)&&S(0x140)<3)||S(0x13e)==2)landing();ADVANCE_TO(0);
 if(S(0x13e)<2){
  if(!S(0x13e)){
   if(S(0x140)<3){F(0xf4)-=1.0;if(F(0xf4)<0.0)F(0xf4)=0.0;}
   if(S(0x140)>2&&S(0x140)<9){MOTION->set_oriented_components(-20.0f,F(0x73c));F(0x73c)-=1.5;if(F(0x73c)<6.0)F(0x74c)=6.0;}
   if(!S(0x142)){if(S(0x140)==4)event(28);if(!S(0x142)&&S(0x140)==9)F(0x100)=0.5f;}
  }
  F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);F(0xf0)=aya_surface(this);F(0xf8)=0.0;}
 }
 if(S(0x13e)==2){F(0xf4)-=2.0;if(F(0xf4)<0.0)F(0xf4)=0.0;}return;
}

case 500:{landing();B(0x17c)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}if(FRAME(0,4)){dispatch_character_wave_handle(4);I(0x180)=1;counter(200,120);phase_counter(50);float packet[3]={0.0f,25.0f,0.0f};spawn(810,60*C(0x104)+F(0xec),F(0xf0),B(0x104),1,packet,3);}return;}

case 502:{if(S(0x13e)==1)landing();B(0x17c)=0;if(!S(0x13e)){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=aya_surface(this);zero_motion();return;}}ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(9);return;}if(FRAME(0,4)){dispatch_character_wave_handle(4);I(0x180)=1;counter(200,120);phase_counter(50);F(0xf4)=-4.0;F(0xf8)=6.0;F(0x100)=0.5f;float packet[3]={60.0f,20.0f,1.0f};spawn(810,53*C(0x104)+F(0xec),F(0xf0)+76.0,B(0x104),1,packet,3);}return;}

case 505:{
 landing();int count=4;B(0x17c)=4;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(FRAME(0,4)){dispatch_character_wave_handle(14);counter(200,120);I(0x180)=1;phase_counter(50);if(C(0x608)<4)count=3;if(C(0x608)<2)count=2;
  float packet[3];for(int angle=0;count>0;--count,angle-=20){packet[0]=angle+20.0;packet[1]=25.0f;packet[2]=0.0f;
   spawn(811,(aya_cosine(-packet[0])*100.0+100.0)*C(0x104)+F(0xec),aya_sine(-packet[0])*100.0+(F(0xf0)+100.0),B(0x104),1,packet,3);
  }
 }return;
}

case 506:{
 landing();int count=4;B(0x17c)=4;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}

 if(FRAME(0,4)){dispatch_character_wave_handle(14);counter(200,120);I(0x180)=1;phase_counter(50);if(C(0x608)<4)count=3;if(C(0x608)<2)count=2;
  float packet[3];for(int angle=0;count>0;--count,angle-=20){packet[0]=angle-30.0;packet[1]=25.0f;packet[2]=0.0f;
   spawn(811,(aya_cosine(-packet[0])*100.0+100.0)*C(0x104)+F(0xec),aya_sine(-packet[0])*100.0+(F(0xf0)+100.0),B(0x104),1,packet,3);
  }
 }return;
}

case 507:{
 if(S(0x13e)==2)landing();B(0x17c)=4;if(!S(0x13e)){if(S(0x140)>7)F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;}}ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}

 if(FRAME(0,4)){dispatch_character_wave_handle(14);counter(200,120);I(0x180)=1;phase_counter(50);int count=4;if(C(0x608)<4)count=3;if(C(0x608)<2)count=2;
  float packet[3];for(int angle=0;count>0;--count,angle-=20){packet[0]=angle+20.0;packet[1]=25.0f;packet[2]=0.0f;
   spawn(811,(aya_cosine(-packet[0])*100.0+47.0)*C(0x104)+F(0xec),aya_sine(-packet[0])*100.0+(F(0xf0)+121.0),B(0x104),1,packet,3);
  }
 }if(FRAME(0,8))F(0x100)=0.5f;return;
}

case 508:{
 if(S(0x13e)==2)landing();B(0x17c)=4;if(!S(0x13e)){if(S(0x140)>7)F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;}}ADVANCE_TO(0);if(ENTRY(1)||ENTRY(2)){set_action_and_finalize(9);return;}

 if(FRAME(0,4)){dispatch_character_wave_handle(14);counter(200,120);I(0x180)=1;phase_counter(50);int count=4;if(C(0x608)<4)count=3;if(C(0x608)<2)count=2;
  float packet[3];for(int angle=0;count>0;--count,angle+=20){packet[0]=angle+30.0;packet[1]=25.0f;packet[2]=0.0f;
   spawn(811,(aya_cosine(-packet[0])*100.0+47.0)*C(0x104)+F(0xec),aya_sine(-packet[0])*100.0+(F(0xf0)+121.0),B(0x104),1,packet,3);
  }
 }if(FRAME(0,8))F(0x100)=0.5f;return;
}

case 510:{landing();B(0x17c)=0;ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}if(FRAME(0,4)){dispatch_character_wave_handle(16);I(0x180)=1;counter(200,120);phase_counter(50);float packet[3]={0.0f,0.0f,1.0f};spawn(812,175*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1,packet,3);packet[1]=150.0f;packet[2]=0.0f;float n=0.0f;do{packet[0]=n*45.0;spawn(812,175*C(0x104)+F(0xec),F(0xf0)+130.0,B(0x104),1,packet,3);n+=1.0;}while(n<8.0);n=0.0f;do{packet[0]=n*60.0+30.0;packet[1]=15.0f;packet[2]=2.0f;spawn(812,175*C(0x104)+F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);n+=1.0;}while(n<6.0);}return;}

case 520:{
 if(!S(0x13e)||S(0x13e)==4||S(0x13e)==5)landing();B(0x17c)=1;
 if(S(0x13e)==1&&(I(0x180)==2||I(0x180)==7)){next_sequence_block();F(0xf4)=-8.0;F(0xf8)=12.5;return;}
 if(S(0x13e)==2||S(0x13e)==3){F(0xf4)+=static_cast<double>(0.15f);if(F(0xf4)>0.0)F(0xf4)=0.0;F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();F(0xf0)=aya_surface(this);return;}}
 if(S(0x13e)==4){F(0xf4)-=1.5;if(F(0xf4)<0.0)F(0xf4)=0.0;}
 ADVANCE_TO(0);if(ENTRY(1)){float packet=0.0f;spawn(815,F(0xec),F(0xf0)+45.0,B(0x104),1,&packet,1);effect(127,F(0xec),F(0xf0),B(0x104),-1);MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}
 if(S(0x13e)==1&&I(0x144)>20)select_sequence(4);if(ENTRY(5))set_action_and_finalize(0);return;
}

case 521:{
 if(!S(0x13e)||S(0x13e)==6)landing();B(0x17c)=1;
 if(S(0x13e)==1&&(I(0x180)==2||I(0x180)==7)){next_sequence_block();F(0xf4)=-8.0;F(0xf8)=12.5;return;}
 if(S(0x13e)>=2&&S(0x13e)<=5){if(S(0x13e)==2||S(0x13e)==3){F(0xf4)+=static_cast<double>(0.15f);if(F(0xf4)>0.0)F(0xf4)=0.0;}F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(6);zero_motion();F(0xf0)=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)){float packet=-45.0f;spawn(815,F(0xec),F(0xf0)+45.0,B(0x104),1,&packet,1);effect(127,F(0xec),F(0xf0),B(0x104),-1);MOTION->set_oriented_components(-45.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}
 if(S(0x13e)==1&&I(0x144)>20){I(0x180)=1;select_sequence(4);F(0x100)=0.6f;F(0xf8)*=0.5;F(0xf4)*=0.25;}return;
}

case 522:{
 if(S(0x13e)==6)landing();B(0x17c)=1;
 if(S(0x13e)==1&&(I(0x180)==2||I(0x180)==7)){next_sequence_block();F(0xf4)=-8.0;F(0xf8)=12.5;return;}
 if(S(0x13e)>=2&&S(0x13e)<=5){if(S(0x13e)==2||S(0x13e)==3){F(0xf4)+=static_cast<double>(0.15f);if(F(0xf4)>0.0)F(0xf4)=0.0;}F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(6);zero_motion();F(0xf0)=aya_surface(this);return;}}
 ADVANCE_TO(0);if(ENTRY(1)){float packet=0.0f;spawn(815,F(0xec),F(0xf0)+45.0,B(0x104),1,&packet,1);MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}
 if(S(0x13e)==1&&I(0x144)>20){I(0x180)=1;select_sequence(4);F(0xf4)*=0.5;}return;
}

case 523:{
 if(S(0x13e)==6)landing();B(0x17c)=1;
 if(S(0x13e)==1&&(I(0x180)==2||I(0x180)==7)){next_sequence_block();F(0xf4)=-8.0;F(0xf8)=12.5;return;}
 if(S(0x13e)>=1&&S(0x13e)<=5){if(S(0x13e)==2||S(0x13e)==3){F(0xf4)+=static_cast<double>(0.15f);if(F(0xf4)>0.0)F(0xf4)=0.0;}if(S(0x13e)>1)F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0;if(S(0x13e)>1)zero_motion();select_sequence(6);F(0xf0)=aya_surface(this);return;}}
 if(S(0x13e)==6){F(0xf4)-=1.5;if(F(0xf4)<0.0)F(0xf4)=0.0;}
 ADVANCE_TO(0);if(ENTRY(1)){float packet=45.0f;spawn(815,F(0xec),F(0xf0)+45.0,B(0x104),1,&packet,1);MOTION->set_oriented_components(45.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}
 if(S(0x13e)==1&&I(0x144)>20){select_sequence(4);F(0x100)=0.6f;F(0xf8)*=0.5;F(0xf4)*=0.25;}return;
}

case 525:{
 if(!S(0x13e)||S(0x13e)==3||S(0x13e)==4)landing();
 if(S(0x13e)==1){if(I(0x180)!=0&&I(0x180)!=3){next_sequence_block();return;}if(I(0x144)>29){select_sequence(3);F(0xf4)*=0.5;return;}if(I(0x144)>19&&(I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(0);set_action_and_finalize(529);return;}}
 if(S(0x13e)==2){if(I(0x144)>19){next_sequence_block();return;}if((I(0x6bc)||I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(0);set_action_and_finalize(529);return;}}
 if(S(0x13e)==3||S(0x13e)==4){F(0xf4)-=static_cast<double>(0.35f);if(F(0xf4)<0.0)F(0xf4)=0.0;}
 ADVANCE_TO(0);if(ENTRY(1)){float packet[3]={0.0f,0.0f,0.0f};spawn(816,F(0xec),F(0xf0)+45.0,B(0x104),1,packet,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);MOTION->set_oriented_components(0.0f,20.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}return;
}

case 526:{
 if(!S(0x13e)||S(0x13e)==5)landing();
 if(S(0x13e)==1){if(I(0x180)!=0&&I(0x180)!=3){next_sequence_block();return;}if(I(0x144)>29){select_sequence(3);F(0xf4)*=0.5;F(0xf8)*=0.5;return;}if(I(0x144)>19&&(I(0x6bc)||I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(S(0x13e)==2){if(I(0x144)>19){next_sequence_block();F(0xf4)*=0.5;F(0xf8)*=0.5;return;}if((I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(S(0x13e)==3||S(0x13e)==4){F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);F(0xf0)=aya_surface(this);zero_motion();return;}}
 ADVANCE_TO(0);if(ENTRY(1)){float packet[3]={-45.0f,0.0f,0.0f};spawn(816,F(0xec),F(0xf0)+45.0,B(0x104),1,packet,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);MOTION->set_oriented_components(-45.0f,20.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}return;
}

case 527:{
 if(S(0x13e)==5)landing();
 if(S(0x13e)==1){if(I(0x180)!=0&&I(0x180)!=3){next_sequence_block();return;}if(I(0x144)>29){select_sequence(3);F(0xf4)*=0.5;F(0xf8)*=0.5;return;}if(I(0x144)>19&&(I(0x6bc)||I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(S(0x13e)==2){if(I(0x144)>19){next_sequence_block();F(0xf4)*=0.5;F(0xf8)*=0.5;return;}if((I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(S(0x13e)==3||S(0x13e)==4){F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);F(0xf0)=aya_surface(this);zero_motion();return;}}
 ADVANCE_TO(0);if(ENTRY(1)){float packet[3]={0.0f,0.0f,0.0f};spawn(816,F(0xec),F(0xf0)+45.0,B(0x104),1,packet,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);MOTION->set_oriented_components(0.0f,20.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}return;
}

case 528:{
 if(S(0x13e)==5)landing();
 if(S(0x13e)==1){if(I(0x180)!=0&&I(0x180)!=3){next_sequence_block();return;}if(static_cast<unsigned char>(crossed()))goto followup528_grounded;if(I(0x144)>29){select_sequence(3);F(0xf4)*=0.5;F(0xf8)*=0.5;return;}if(I(0x144)>19&&(I(0x6bc)||I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(S(0x13e)==2){if(static_cast<unsigned char>(crossed()))goto followup528_grounded;if(I(0x144)>19){next_sequence_block();F(0xf4)*=0.5;F(0xf8)*=0.5;return;}if((I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(1);set_action_and_finalize(529);return;}}
 if(S(0x13e)==3||S(0x13e)==4){F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);F(0xf0)=aya_surface(this);zero_motion();return;}}if(S(0x13e)==5&&F(0xf4)>0.0){F(0xf4)-=0.75;if(F(0xf4)<0.0)F(0xf4)=0.0;}
 ADVANCE_TO(0);if(ENTRY(1)){float packet[3]={45.0f,0.0f,0.0f};spawn(816,F(0xec),F(0xf0)+45.0,B(0x104),1,packet,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);MOTION->set_oriented_components(45.0f,20.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(5);}return;
followup528_grounded:F(0xf8)=0.0;select_sequence(5);F(0xf0)=aya_surface(this);return;
}

case 529:{
 if(S(0x13e)==16||S(0x13e)==19)landing();
 short phase=S(0x13e);
 if(phase==2||phase==5||phase==8||phase==11||phase==14){
  if(I(0x144)>19){next_sequence_block();return;}
  if(((!S(0x738)&&C(0x609)>1)||(S(0x738)==1&&C(0x609)>3))&&(I(0x6bc)||I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(1);++S(0x738);set_action_and_finalize(529);return;}
 }
 if(phase==3||phase==6||phase==9||phase==12||phase==15){
  if(I(0x144)>4){select_sequence(static_cast<unsigned char>(aya_on_surface(this))?16:17);F(0xf4)*=0.5;if(F(0xf8)>0.0)F(0xf8)*=0.5;return;}
  if(!S(0x738)&&C(0x609)>3&&(I(0x6bc)||I(0x6c0)||I(0x6c4))){CHOOSE_FOLLOWUP(1);S(0x738)=1;set_action_and_finalize(529);return;}
 }
 if(phase<16&&static_cast<unsigned char>(crossed())){select_sequence(19);F(0xf0)=aya_surface(this);F(0xf8)=0.0;return;}
 if(S(0x13e)==16){F(0xf4)-=0.5;if(F(0xf4)<0.0)F(0xf4)=0.0;}
 if(S(0x13e)==17||S(0x13e)==18){F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(19);F(0xf0)=aya_surface(this);F(0xf8)=0.0;return;}}
 if(S(0x13e)==19){F(0xf4)-=1.0;if(F(0xf4)<0.0)F(0xf4)=0.0;}
 ADVANCE_TO(0);
 if(!I(0x144)){
  if(FRAME(1,0)){
   float packet[3];
   if(S(0x730)==0){packet[0]=0.0f;packet[1]=80.0f;packet[2]=0.0f;select_sequence(1);MOTION->set_oriented_components(0.0f,20.0f);}
   if(S(0x730)==1){packet[0]=-45.0f;packet[1]=100.0f;packet[2]=0.0f;select_sequence(4);MOTION->set_oriented_components(-45.0f,20.0f);}
   if(S(0x730)==2){packet[0]=-90.0f;packet[1]=120.0f;packet[2]=0.0f;select_sequence(10);MOTION->set_oriented_components(-90.0f,20.0f);}
   if(S(0x730)==-1){packet[0]=45.0f;packet[1]=100.0f;packet[2]=0.0f;select_sequence(7);MOTION->set_oriented_components(45.0f,20.0f);}
   if(S(0x730)==-2){packet[0]=90.0f;packet[1]=100.0f;packet[2]=0.0f;select_sequence(13);MOTION->set_oriented_components(90.0f,20.0f);}
   spawn(816,F(0xec),packet[2]+F(0xf0),B(0x104),1,packet,3);
   if(static_cast<unsigned char>(aya_on_surface(this)))effect(127,F(0xec),F(0xf0),B(0x104),-1);
   dispatch_character_wave_handle(5);
  }
  if(ENTRY(17)){set_action_and_finalize(0);zero_motion();}
 }return;
}

case 530:{
 if(S(0x13e)==4)landing();B(0x17c)=9;
 if(S(0x13e)==2||S(0x13e)==3){F(0xf4)-=3.0;if(F(0xf4)<3.0)F(0xf4)=3.0;F(0xf8)-=F(0x100);if(S(0x13e)==2&&S(0x140)<12&&F(0xf8)<=-1.0)F(0xf8)=-1.0;if(static_cast<unsigned char>(crossed())){select_sequence(4);F(0xf0)=aya_surface(this);zero_motion();return;}}
 ADVANCE_TO(0);if(ENTRY(2))F(0x100)=0.5f;if(FRAME(0,5)){F(0xf4)=40.0;F(0xf8)=10.0;effect(127,F(0xec),F(0xf0),B(0x104),-1);}
 if(FRAME(2,5)){request530[0]=15.0f;request530[1]=30.0f;paired_request=request530;goto paired_817_request;}return;
}

case 532:{
 if(S(0x13e)==4)landing();B(0x17c)=9;
 if(S(0x13e)==2||S(0x13e)==3){F(0xf4)-=3.0;if(F(0xf4)<3.0)F(0xf4)=3.0;F(0xf8)-=F(0x100);if(S(0x13e)==2&&S(0x140)<12&&F(0xf8)<=-1.0)F(0xf8)=-1.0;if(static_cast<unsigned char>(crossed())){select_sequence(4);F(0xf0)=aya_surface(this);zero_motion();return;}}
 ADVANCE_TO(0);if(ENTRY(2))F(0x100)=0.5f;if(FRAME(0,5)){F(0xf4)=40.0;F(0xf8)=10.0;effect(127,F(0xec),F(0xf0),B(0x104),-1);}
 if(FRAME(2,5)){request532[0]=15.0f;request532[1]=30.0f;paired_request=request532;goto paired_817_request;}return;
}

case 540:{
 B(0x17c)=2;
 if(FRAME(0,5)){float packet[3]={0.0f,0.0f,0.0f};dispatch_character_wave_handle(6);counter(200,120);I(0x180)=1;phase_counter(50);spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);}
 if(S(0x13e)==1){
  if(I(0x144)>60){select_sequence(5);F(0x100)=0.5f;return;}
  if(I(0x6b8)<0){
   if(I(0x6b4)*C(0x104)>0){
    select_sequence(2);dispatch_character_wave_handle(7);F(0xf4)=8.0;F(0xf8)=12.0;F(0x100)=0.5f;
    float packet[3]={135.0f,20.0f,4.0f};spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=5.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);
    if(C(0x606)>=4){packet[2]=6.0f;packet[0]=150.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[0]=120.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
   }
   if(I(0x6b4)*C(0x104)<0){
    dispatch_character_wave_handle(7);select_sequence(4);F(0xf4)=-8.0;F(0xf8)=12.0;F(0x100)=0.5f;
    float packet[3]={45.0f,20.0f,4.0f};spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=5.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);
    if(C(0x606)>=4){packet[2]=6.0f;packet[0]=30.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[0]=60.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
   }
   dispatch_character_wave_handle(7);select_sequence(3);F(0xf4)=0.0;F(0xf8)=12.0;F(0x100)=0.5f;
   float packet[3]={90.0f,20.0f,4.0f};spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=5.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);
   if(C(0x606)>=4){packet[2]=6.0f;packet[0]=105.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[0]=75.0f;spawn(820,F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
  }
 }
 if(S(0x13e)>1){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=aya_surface(this);return;}}
 ADVANCE_TO(9);if(ENTRY(3)||ENTRY(4)){set_action_and_finalize(9);return;}if(ENTRY(5))set_action_and_finalize(9);return;
}

case 545:{
 if(S(0x13e)==2)landing();B(0x17c)=6;
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){
  dispatch_character_wave_handle(23);layout(5.0f);float packet[3]={0.0f,0.0f,0.0f};spawn(821,F(0xec),F(0xf0),B(0x104),1,packet,3);
  for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}
  select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;
 }
 ADVANCE_TO(0);if(FRAME(0,4)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);MOTION->set_oriented_components(70.0f,25.0f);float packet[3]={70.0f,0.0f,2.0f};spawn(821,20*C(0x104)+F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
}

case 546:{
 if(S(0x13e)==2)landing();B(0x17c)=6;
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){
  dispatch_character_wave_handle(23);layout(5.0f);float packet[3]={0.0f,0.0f,5.0f};spawn(821,F(0xec),F(0xf0),B(0x104),-1,packet,3);packet[2]=6.0f;spawn(821,F(0xec),F(0xf0),B(0x104),-1,packet,3);
  for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}
  packet[0]=0.0f;packet[1]=17.5f;packet[2]=3.0f;spawn(821,F(0xec),0.0f,B(0x104),1,packet,3);spawn(821,F(0xec),0.0f,static_cast<unsigned char>(-B(0x104)),1,packet,3);
  if(C(0x60a)>3){packet[1]=30.0f;spawn(821,F(0xec),0.0f,B(0x104),1,packet,3);spawn(821,F(0xec),0.0f,static_cast<unsigned char>(-B(0x104)),1,packet,3);}
  select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();I(0x180)=1;return;
 }
 ADVANCE_TO(0);if(FRAME(0,4)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);MOTION->set_oriented_components(70.0f,25.0f);float packet[3]={70.0f,0.0f,2.0f};spawn(821,20*C(0x104)+F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
}

case 550:{
 B(0x17c)=10;if(!S(0x13e)||S(0x13e)==7)landing();
 if(S(0x13e)==2&&I(0x180)){next_sequence_block();zero_motion();return;}
 if(S(0x13e)>0&&S(0x13e)<7)F(0xf8)-=F(0x100);
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<7){select_sequence(7);F(0xf0)=aya_surface(this);zero_motion();return;}
 if(S(0x13e)==1||S(0x13e)==2){
  if(aya_absolute(F(0xec)-PF(0xec))<=100.0)S(0x730)=1;
  if(S(0x730)==1)F(0xf4)*=static_cast<double>(0.92f);
  if(C(0x104)*I(0x6b4)>0)F(0xf4)+=(static_cast<double>(C(0x60e))*static_cast<double>(0.1f)+0.25);
  if(C(0x104)*I(0x6b4)<0)F(0xf4)-=(static_cast<double>(C(0x60e))*static_cast<double>(0.1f)+0.25);
  if(F(0xf4)>10.0)F(0xf4)=10.0;if(F(0xf4)<-12.0)F(0xf4)=-12.0;
 }
 if(S(0x13e)==5||S(0x13e)==6){
  if(C(0x104)*I(0x6b4)>0)F(0xf4)+=0.25;if(C(0x104)*I(0x6b4)<0)F(0xf4)-=0.25;
  if(F(0xf4)>12.0)F(0xf4)=12.0;if(F(0xf4)<-12.0)F(0xf4)=-12.0;
  if(S(0x13e)==6||(S(0x13e)==5&&S(0x140)>2)){if(I(0x6c4)){set_action_and_finalize(554);select_sequence(6);return;}if(I(0x6c0)){set_action_and_finalize(554);return;}if(I(0x6bc)){set_action_and_finalize(554);select_sequence(3);return;}}
 }
 ADVANCE_TO(0);if(!I(0x144)){
  if(FRAME(1,0)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);F(0xf4)=10.0;F(0xf8)=25.0;F(0x100)=1.25f;spawn(990,F(0xec),F(0xf0),B(0x104),1,0,0);effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);}
  if(ENTRY(5)){F(0xf4)=-6.0;F(0xf8)=12.0;F(0x100)=0.5f;}
 }return;
}

case 551:{
 B(0x17c)=10;if(!S(0x13e)||S(0x13e)==7)landing();
 if(S(0x13e)==2&&I(0x180)){next_sequence_block();zero_motion();return;}
 if(S(0x13e)>0&&S(0x13e)<7)F(0xf8)-=F(0x100);
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<7){select_sequence(7);F(0xf0)=aya_surface(this);zero_motion();return;}
 if(S(0x13e)==1||S(0x13e)==2){
  if(aya_absolute(F(0xec)-PF(0xec))<=300.0)S(0x730)=1;
  if(S(0x730)==1)F(0xf4)*=static_cast<double>(0.92f);
  if(C(0x104)*I(0x6b4)>0)F(0xf4)+=(static_cast<double>(C(0x60e))*static_cast<double>(0.1f)+0.25);
  if(C(0x104)*I(0x6b4)<0)F(0xf4)-=(static_cast<double>(C(0x60e))*static_cast<double>(0.1f)+0.25);
  if(F(0xf4)>25.0)F(0xf4)=25.0;if(F(0xf4)<-12.0)F(0xf4)=-12.0;
 }
 if(S(0x13e)==5||S(0x13e)==6){
  if(C(0x104)*I(0x6b4)>0)F(0xf4)+=0.25;if(C(0x104)*I(0x6b4)<0)F(0xf4)-=0.25;
  if(F(0xf4)>12.0)F(0xf4)=12.0;if(F(0xf4)<-12.0)F(0xf4)=-12.0;
  if(S(0x13e)==6||(S(0x13e)==5&&S(0x140)>2)){if(I(0x6c4)){set_action_and_finalize(554);select_sequence(6);return;}if(I(0x6c0)){set_action_and_finalize(554);return;}if(I(0x6bc)){set_action_and_finalize(554);select_sequence(3);return;}}
 }
 ADVANCE_TO(0);if(!I(0x144)){
  if(FRAME(1,0)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);F(0xf4)=25.0;F(0xf8)=25.0;F(0x100)=1.0f;spawn(990,F(0xec),F(0xf0),B(0x104),1,0,0);effect(128,200*C(0x104)+F(0xec),F(0xf0),B(0x104),-1);}
  if(ENTRY(5)){F(0xf4)=-6.0;F(0xf8)=12.0;F(0x100)=0.5f;}
 }return;
}

case 552:{
 B(0x17c)=10;if(S(0x13e)==7)landing();
 if(S(0x13e)==2&&I(0x180)){next_sequence_block();zero_motion();return;}
 if(S(0x13e)>0&&S(0x13e)<7)F(0xf8)-=F(0x100);
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<7){select_sequence(7);F(0xf0)=aya_surface(this);zero_motion();return;}
 if(S(0x13e)==1||S(0x13e)==2){
  if(aya_absolute(F(0xec)-PF(0xec))<=100.0)S(0x730)=1;
  if(S(0x730)==1)F(0xf4)*=static_cast<double>(0.92f);
  if(C(0x104)*I(0x6b4)>0)F(0xf4)+=0.25;
  if(C(0x104)*I(0x6b4)<0)F(0xf4)-=0.25;
  if(F(0xf4)>25.0)F(0xf4)=25.0;if(F(0xf4)<-12.0)F(0xf4)=-12.0;
 }
 if(S(0x13e)==5||S(0x13e)==6){
  if(C(0x104)*I(0x6b4)>0)F(0xf4)+=0.25;if(C(0x104)*I(0x6b4)<0)F(0xf4)-=0.25;
  if(F(0xf4)>12.0)F(0xf4)=12.0;if(F(0xf4)<-12.0)F(0xf4)=-12.0;
  if(S(0x13e)==6){if(I(0x6c4)){set_action_and_finalize(554);select_sequence(6);return;}if(I(0x6c0)){set_action_and_finalize(554);return;}if(I(0x6bc)){set_action_and_finalize(554);select_sequence(3);return;}}
 }
 ADVANCE_TO(0);if(!I(0x144)){
  if(FRAME(1,0)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);F(0xf4)=10.0;F(0xf8)=25.0;F(0x100)=1.25f;spawn(990,F(0xec),F(0xf0),B(0x104),1,0,0);}
  if(ENTRY(5)){F(0xf4)=-6.0;F(0xf8)=12.0;F(0x100)=0.5f;}
 }return;
}

case 553:{
 B(0x17c)=10;if(S(0x13e)==7)landing();
 if(S(0x13e)==2&&I(0x180)){next_sequence_block();zero_motion();return;}
 if(S(0x13e)>0&&S(0x13e)<7)F(0xf8)-=F(0x100);
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<7){select_sequence(7);F(0xf0)=aya_surface(this);zero_motion();return;}
 if(S(0x13e)==1||S(0x13e)==2){
  if(aya_absolute(F(0xec)-PF(0xec))<=300.0)S(0x730)=1;
  if(S(0x730)==1)F(0xf4)*=static_cast<double>(0.92f);
  if(C(0x104)*I(0x6b4)>0)F(0xf4)+=0.25;
  if(C(0x104)*I(0x6b4)<0)F(0xf4)-=0.25;
  if(F(0xf4)>25.0)F(0xf4)=25.0;if(F(0xf4)<-12.0)F(0xf4)=-12.0;
 }
 if(S(0x13e)==5||S(0x13e)==6){
  if(C(0x104)*I(0x6b4)>0)F(0xf4)+=0.25;if(C(0x104)*I(0x6b4)<0)F(0xf4)-=0.25;
  if(F(0xf4)>12.0)F(0xf4)=12.0;if(F(0xf4)<-12.0)F(0xf4)=-12.0;
  if(S(0x13e)==6){if(I(0x6c4)){set_action_and_finalize(554);select_sequence(6);return;}if(I(0x6c0)){set_action_and_finalize(554);return;}if(I(0x6bc)){set_action_and_finalize(554);select_sequence(3);return;}}
 }
 ADVANCE_TO(0);if(!I(0x144)){
  if(FRAME(1,0)){counter(200,120);phase_counter(50);dispatch_character_wave_handle(15);F(0xf4)=25.0;F(0xf8)=25.0;F(0x100)=1.0f;spawn(990,F(0xec),F(0xf0),B(0x104),1,0,0);}
  if(ENTRY(5)){F(0xf4)=-6.0;F(0xf8)=12.0;F(0x100)=0.5f;}
 }return;
}

case 554:{
 if(S(0x13e)==2||S(0x13e)==5)landing();
 if(ENTRY(0)){zero_motion();B(0x47e)=0;S(0x730)=0;}
 if(!I(0x144)){if(FRAME(3,0)){B(0x47e)=0;S(0x730)=0;}if(ENTRY(6)){F(0xf4)*=0.25;F(0xf8)*=0.25;F(0x100)=0.0;}}
 B(0x17c)=10;
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){
  layout(5.0f);float packet[3];for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}
  select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;
 }
 if(S(0x13e)==3||S(0x13e)==4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(5);F(0xf0)=aya_surface(this);zero_motion();return;}}
 if(S(0x13e)==6){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(5);F(0xf0)=aya_surface(this);zero_motion();return;}}
 if(advance()){select_sequence(4);return;}
 if(ENTRY(3)||ENTRY(6)){set_action_and_finalize(0);return;}
 if(FRAME(0,4)){dispatch_character_wave_handle(15);MOTION->set_oriented_components(70.0f,25.0f);phase_counter(25);}
 if(FRAME(3,4)){dispatch_character_wave_handle(15);phase_counter(25);}
 if(FRAME(6,3)){
  float dx=(static_cast<double>(PF(0xec))-F(0xec))*C(0x104);F(0x744)=-aya_atan(PF(0xf0)-F(0xf0),dx);
  if(F(0x744)>75.0)F(0x744)=75.0;if(F(0x744)<-30.0)F(0x744)=-30.0;
  float packet[3]={F(0x744),15.0f,0.0f};spawn(822,47*C(0x104)+F(0xec),F(0xf0)+106.0,B(0x104),1,packet,3);
  MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(25);dispatch_character_wave_handle(19);I(0x180)=1;F(0xf8)=7.5;F(0xf4)=-7.5;F(0x100)=0.5f;
 }return;
}

case 560:{
 landing();B(0x17c)=3;
 if(S(0x730)==1){if(!(S(0x732)%4)&&S(0x732)*0.25<=C(0x607)+5){
  float packet[3];packet[0]=(static_cast<float>(static_cast<unsigned>(aya_random(400)))+F(0xec))-200.0;packet[1]=(F(0xf0)+175.0)+175.0;packet[2]=0.0f;
  int facing=B(0x104);float randomHeight=static_cast<float>(static_cast<unsigned>(aya_random(300)));float height=randomHeight+(F(0xf0)+300.0);
  spawn(825,1380.0-1480*(B(0x104)==1),height,facing,1,packet,3);
 }++S(0x732);}
 ADVANCE_TO(0);if(FRAME(0,1)){dispatch_character_wave_handle(17);S(0x730)=1;I(0x180)=1;counter(200,120);phase_counter(50);}return;
}

case 561:{
 landing();B(0x17c)=3;
 if(S(0x730)==1){if(!(S(0x732)%4)&&S(0x732)*0.25<=C(0x607)+5){
  float packet[3];packet[0]=(static_cast<float>(static_cast<unsigned>(aya_random(400)))+PF(0xec))-200.0;packet[1]=(PF(0xf0)+175.0)+175.0;packet[2]=0.0f;
  int facing=B(0x104);float randomHeight=static_cast<float>(static_cast<unsigned>(aya_random(300)));float height=randomHeight+(F(0xf0)+300.0);
  spawn(825,1380.0-1480*(B(0x104)==1),height,facing,1,packet,3);
 }++S(0x732);}
 ADVANCE_TO(0);if(FRAME(0,1)){dispatch_character_wave_handle(17);S(0x730)=1;I(0x180)=1;counter(200,120);phase_counter(50);}return;
}

case 565:{landing();ADVANCE_TO(0);if(FRAME(0,8)){double height=F(0xf0);float packet[3];packet[0]=!(aya_surface(this)>=height)?1.0f:0.0f;packet[1]=0.0f;packet[2]=0.0f;spawn(826,F(0xec)+0.0,F(0xf0)+100.0,B(0x104),1,packet,3);dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);}return;}

case 567:{if(advance()){set_action_and_finalize(9);F(0x100)=0.6f;}if(FRAME(0,8)){double height=F(0xf0);float packet[3];packet[0]=!(aya_surface(this)>=height)?1.0f:0.0f;packet[1]=0.0f;packet[2]=0.0f;spawn(826,F(0xec)+0.0,F(0xf0)+100.0,B(0x104),1,packet,3);dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);}return;}

case 600:{
 landing();texture(2,2);if(S(0x13e)==1&&I(0x144)>60){next_sequence_block();return;}ADVANCE_TO(0);
 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==3){S(0x48a)=40;event(23);effect(115,44*C(0x104)+F(0xec),F(0xf0)+138.0,B(0x104),1);sequence_window(0,3,60);secondary_cycle();}
  if(!S(0x142)&&S(0x140)==6){spawn(850,80*C(0x104)+F(0xec),F(0xf0),B(0x104),1,0,0);dispatch_character_wave_handle(9);}
 }return;
}

case 601:{
 landing();texture(2,2);if(S(0x13e)==1){layout(5.0f);if(I(0x144)>90){next_sequence_block();return;}}if(S(0x13e)==2&&I(0x144)>60){next_sequence_block();return;}ADVANCE_TO(0);
 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==3){S(0x48a)=40;event(23);effect(115,44*C(0x104)+F(0xec),F(0xf0)+138.0,B(0x104),1);sequence_window(0,5,60);secondary_cycle();}
  if(!S(0x142)&&S(0x140)==6){spawn(851,F(0xec),F(0xf0),B(0x104),1,0,0);dispatch_character_wave_handle(10);}
 }return;
}

case 602:{
 landing();texture(2,2);if(S(0x13e)==1){layout(2.0f);if(I(0x144)>30){next_sequence_block();return;}}if(advance()){set_action_and_finalize(0);texture(2,240);}
 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==3){S(0x48a)=40;event(23);effect(115,44*C(0x104)+F(0xec),F(0xf0)+138.0,B(0x104),1);sequence_window(0,4,60);secondary_cycle();}
  if(!S(0x142)&&S(0x140)==6){float packet[3]={0.0f,0.0f,0.0f};spawn(852,F(0xec),F(0xf0),B(0x104),1,packet,3);dispatch_character_wave_handle(11);}
 }return;
}

case 603:{
 texture(2,2);if(S(0x13e)==1&&I(0x144)>39){next_sequence_block();return;}
 if(S(0x13e)>1){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=aya_surface(this);return;}}
 ADVANCE_TO(9);
 if(!I(0x144)){
  if(FRAME(1,0)){S(0x48a)=40;event(23);effect(115,F(0xec),F(0xf0)+120.0,B(0x104),1);sequence_window(0,3,60);secondary_cycle();}
  if(ENTRY(3)){dispatch_character_wave_handle(24);float packet[3]={0.0f,0.0f,8.0f};spawn(853,F(0xec),F(0xf0),B(0x104),1,packet,3);
   for(int n=0;n<4;++n){packet[0]=static_cast<float>(static_cast<unsigned>(aya_random(60)))+60.0;packet[1]=static_cast<float>(static_cast<unsigned>(aya_random(10)))+15.0;packet[2]=4.0f;spawn(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}
   for(int n=0;n<8;++n){packet[0]=static_cast<float>(static_cast<unsigned>(aya_random(100)))+40.0;packet[1]=static_cast<float>(static_cast<unsigned>(aya_random(15)))+5.0;packet[2]=6.0f;spawn(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}
   F(0xf4)=0.0;F(0xf8)=17.5;F(0x100)=0.5f;
  }
 }
 if(FRAME(0,5)){float packet[3]={0.0f,0.0f,0.0f};dispatch_character_wave_handle(6);spawn(853,F(0xec),F(0xf0),B(0x104),1,packet,3);}return;
}

case 604:{landing();ADVANCE_TO(0);if(ENTRY(1)){set_action_and_finalize(0);return;}if(S(0x730)>0){if(S(0x730)==1){dispatch_character_wave_handle(2);float packet[3]={30.0f,-4.0f,0.0f};spawn(854,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);packet[0]=-30.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(854,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);}if(S(0x730)==6){dispatch_character_wave_handle(2);float packet[3]={45.0f,-4.0f,0.0f};spawn(854,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);packet[0]=-45.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(854,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);}if(S(0x730)==11){dispatch_character_wave_handle(2);float packet[3]={60.0f,-4.0f,0.0f};spawn(854,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);packet[0]=-60.0f;packet[1]=4.0f;packet[2]=0.0f;spawn(854,116*C(0x104)+F(0xec),F(0xf0)+105.0,B(0x104),1,packet,3);}++S(0x730);}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==2){S(0x48a)=40;event(23);effect(115,8*C(0x104)+F(0xec),F(0xf0)+176.0,B(0x104),1);sequence_window(0,2,60);secondary_cycle();}if(!S(0x142)&&S(0x140)==5)S(0x730)=1;}return;
}

case 605:{
 landing();texture(2,2);if(advance()){set_action_and_finalize(0);texture(2,60);}
 if(!S(0x13e)&&!S(0x142)){
  if(S(0x140)==3){S(0x48a)=40;event(23);effect(115,44*C(0x104)+F(0xec),F(0xf0)+138.0,B(0x104),1);sequence_window(0,2,60);secondary_cycle();}
  if(!S(0x142)&&S(0x140)==6){spawn(855,F(0xec)+0.0,F(0xf0)+100.0,B(0x104),1,0,0);dispatch_character_wave_handle(12);}
 }return;
}

case 606:{
 if(!S(0x13e)||S(0x13e)==4||S(0x13e)==9)landing();texture(2,2);
 if(S(0x13e)==1&&I(0x180)==1){float packet[3]={0.0f,0.0f,0.0f};spawn(856,F(0xec),F(0xf0),B(0x104),1,packet,3);select_sequence(5);zero_motion();shared_first(1,PF(0xec));shared_second(1,F(0xf0));F(0xec)=PF(0xec);F(0xf0)=PF(0xf0);return;}
 if(S(0x13e)==2||S(0x13e)==3){F(0xf4)-=0.5;if(F(0xf4)<5.0)F(0xf4)=5.0;F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(4);zero_motion();F(0xf0)=aya_surface(this);event(30);return;}}
 if(S(0x13e)==5){shared_first(1,PF(0xec));shared_second(1,F(0xf0));F(0xec)=PF(0xec);F(0xf0)=PF(0xf0);if(I(0x144)>59){F(0xf0)=PF(0xf0);next_sequence_block();return;}}
 if(S(0x13e)==6){
  if(F(0x73c)==0.0&&I(0x6b4)){F(0x73c)=static_cast<float>(I(0x6b4));F(0xf8)+=1.0;}
  if(F(0x73c)>0.0&&I(0x6b4)<0){F(0x73c)=static_cast<float>(I(0x6b4));F(0xf8)+=1.0;}
  if(F(0x73c)<0.0&&I(0x6b4)>0){F(0x73c)=static_cast<float>(I(0x6b4));F(0xf8)+=1.0;}
  if(F(0xf8)>15.0)F(0xf8)=15.0;F(0xf8)-=static_cast<double>(0.1f);if(F(0xf4)<-6.0)F(0xf4)=-6.0;
  if(static_cast<unsigned char>(crossed()))F(0xf8)=0.0;
  shared_first(1,PF(0xec));shared_second(1,F(0xf0));F(0xec)=PF(0xec);
  float packet[3];
  if(--S(0x730)<=0){
   if(!S(0x732)&&PF(0xec)<640.0)S(0x732)=1;
   if(F(0xf0)<960.0){
    dispatch_character_wave_handle(22);packet[0]=0.0f;packet[1]=120.0f;packet[2]=1.0f;double spawnY=F(0xf0)+300.0;
    if(!(S(0x732)%2)){spawn(856,1380.0f,spawnY-static_cast<float>(static_cast<unsigned>(aya_random(400))),-1,1,packet,3);++S(0x732);S(0x730)=static_cast<short>(30-S(0x732));if(S(0x730)<15)S(0x730)=15;}
    else{spawn(856,-100.0f,spawnY-static_cast<float>(static_cast<unsigned>(aya_random(400))),1,1,packet,3);++S(0x732);S(0x730)=static_cast<short>(30-S(0x732));if(S(0x730)<10)S(0x730)=10;}
   }
  }
  if(I(0x144)>19&&--S(0x734)<=0&&F(0xf0)<960.0){
   if(!(S(0x736)%2)){packet[0]=4.0-static_cast<float>(static_cast<unsigned>(aya_random(8)));packet[1]=S(0x736)+120.0;packet[2]=3.0f;spawn(856,1380.0f,static_cast<float>(static_cast<unsigned>(aya_random(200)))+F(0xf0),-1,1,packet,3);}
   else{packet[0]=4.0-static_cast<float>(static_cast<unsigned>(aya_random(8)));packet[1]=S(0x736)+120.0;packet[2]=3.0f;spawn(856,-100.0f,static_cast<float>(static_cast<unsigned>(aya_random(200)))+F(0xf0),1,1,packet,3);}
   ++S(0x736);S(0x734)=static_cast<short>(25-S(0x736));if(S(0x734)<10)S(0x734)=10;
  }
  if(I(0x144)>99&&!(I(0x144)%14)&&F(0xf0)<960.0){
   if(!(S(0x738)%2)){packet[0]=4.0-static_cast<float>(static_cast<unsigned>(aya_random(8)));packet[1]=static_cast<float>(static_cast<unsigned>(aya_random(50)))+150.0;packet[2]=2.0f;spawn(856,1380.0f,static_cast<float>(static_cast<unsigned>(aya_random(200)))+F(0xf0),-1,1,packet,3);}
   else{packet[0]=4.0-static_cast<float>(static_cast<unsigned>(aya_random(8)));packet[1]=static_cast<float>(static_cast<unsigned>(aya_random(50)))+150.0;packet[2]=2.0f;spawn(856,-100.0f,static_cast<float>(static_cast<unsigned>(aya_random(200)))+F(0xf0),1,1,packet,3);}++S(0x738);
  }
  if(I(0x144)>299){packet[0]=90.0f;packet[1]=30.0f;packet[2]=5.0f;spawn(856,640.0f,F(0xf0)+100.0,1,1,packet,3);packet[0]=-90.0f;spawn(856,640.0f,F(0xf0)+100.0,1,1,packet,3);packet[2]=4.0f;spawn(856,PF(0xec),F(0xf0)+100.0,1,1,packet,3);next_sequence_block();return;}
 }
 if(S(0x13e)==7){F(0xec)=PF(0xec);F(0xf8)=40.0;if(F(0xf0)>1280.0)F(0xf0)=1280.0;if(I(0x144)>39){F(0xf8)=-30.0;F(0x100)=0.5f;next_sequence_block();shared_first(0,PF(0xec));shared_second(0,F(0xf0));return;}}
 if(S(0x13e)==8){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=aya_surface(this);zero_motion();return;}}
 if(advance()){set_action_and_finalize(0);texture(2,60);}
 if(!I(0x144)){
  if(FRAME(1,0)){dispatch_character_wave_handle(21);F(0xf4)=60.0;F(0xf8)=16.0;F(0x100)=0.15f;float packet[3];for(int angle=0;angle<360;angle+=36){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}}
  if(!I(0x144)){if(FRAME(2,0)){F(0xf4)*=0.25;F(0xf8)=2.0;}if(ENTRY(5)){set_action_and_finalize(0);return;}}
 }
 if(FRAME(0,3)){S(0x48a)=40;event(23);effect(115,F(0xec)-80*C(0x104),F(0xf0)+130.0,B(0x104),1);sequence_window(0,5,60);secondary_cycle();}return;
}

case 611:{landing();texture(2,2);if(advance()){set_action_and_finalize(0);texture(2,60);}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==2){S(0x48a)=40;event(23);effect(115,32*C(0x104)+F(0xec),F(0xf0)+144.0,B(0x104),1);sequence_window(0,1,60);secondary_cycle();}if(!S(0x142)&&S(0x140)==8){float packet[3]={F(0xf0)==0.0?0.0f:1.0f,0.0f,0.0f};spawn(861,F(0xec)+0.0,F(0xf0)+100.0,B(0x104),1,packet,3);dispatch_character_wave_handle(13);}}return;
}

case 612:{
 if(!S(0x13e)||S(0x13e)==4||S(0x13e)==5)landing();if(S(0x13e)<2)texture(2,2);
 if(S(0x13e)==1){if(!(I(0x144)%5))effect(127,F(0xec),0.0f,B(0x104),-1);if(I(0x180)==2||I(0x180)==7||x_boundary()){next_sequence_block();F(0xf4)=-10.0;F(0xf8)=14.0;return;}}
 if(S(0x13e)==2||S(0x13e)==3){F(0xf4)+=static_cast<double>(0.15f);if(F(0xf4)>0.0)F(0xf4)=0.0;F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();F(0xf0)=aya_surface(this);return;}}if(S(0x13e)==4){F(0xf4)-=2.5;if(F(0xf4)<0.0)F(0xf4)=0.0;}
 ADVANCE_TO(0);if(FRAME(0,3)){S(0x48a)=40;event(23);effect(115,F(0xec)-77*C(0x104),F(0xf0)+144.0,B(0x104),1);sequence_window(0,3,60);secondary_cycle();}
 if(ENTRY(1)){float packet[2]={0.0f,0.0f};spawn(862,F(0xec),F(0xf0)+45.0,B(0x104),1,packet,1);effect(127,F(0xec),F(0xf0),B(0x104),-1);MOTION->set_oriented_components(0.0f,40.0f);dispatch_character_wave_handle(5);}
 if(S(0x13e)==1&&I(0x144)>20)select_sequence(4);if(ENTRY(5))set_action_and_finalize(0);return;
}

case 661:{texture(2,2);if(advance()){set_action_and_finalize(9);texture(2,60);F(0x100)=0.6f;}
 if(!S(0x13e)&&!S(0x142)){if(S(0x140)==2){S(0x48a)=40;event(23);effect(115,32*C(0x104)+F(0xec),F(0xf0)+144.0,B(0x104),1);sequence_window(0,1,60);secondary_cycle();}if(!S(0x142)&&S(0x140)==8){float packet[3]={F(0xf0)==0.0?0.0f:1.0f,0.0f,0.0f};spawn(861,F(0xec)+0.0,F(0xf0)+100.0,B(0x104),1,packet,3);dispatch_character_wave_handle(13);}}return;
}

case 662:{
 if(S(0x13e)==6)landing();if(S(0x13e)<2)texture(2,2);
 if(S(0x13e)==1){if(!(I(0x144)%5))effect(127,F(0xec),0.0f,B(0x104),-1);if(I(0x180)==2||I(0x180)==7||x_boundary()){next_sequence_block();F(0xf4)=-10.0;F(0xf8)=14.0;return;}}
 if(S(0x13e)>=2&&S(0x13e)<=5){if(S(0x13e)==2||S(0x13e)==3){F(0xf4)+=static_cast<double>(0.15f);if(F(0xf4)>0.0)F(0xf4)=0.0;}F(0xf8)-=0.5;if(static_cast<unsigned char>(crossed())){select_sequence(6);zero_motion();F(0xf0)=aya_surface(this);return;}}
 ADVANCE_TO(0);if(FRAME(0,3)){S(0x48a)=40;event(23);effect(115,F(0xec)-77*C(0x104),F(0xf0)+144.0,B(0x104),1);sequence_window(0,3,60);secondary_cycle();}
 if(ENTRY(1)){float packet[2]={0.0f,0.0f};spawn(862,F(0xec),F(0xf0)+45.0,B(0x104),1,packet,2);double height=F(0xf0);if(height-aya_surface(this)<=150.0)effect(127,F(0xec),aya_surface(this),B(0x104),-1);MOTION->set_oriented_components(0.0f,40.0f);dispatch_character_wave_handle(5);}
 if(S(0x13e)==1&&I(0x144)>20){select_sequence(4);F(0xf4)*=0.5;}return;
}

case 695:{landing();ADVANCE_TO(0);if(FRAME(0,7)){event(55);effect(140,F(0xec),F(0xf0)+100.0,B(0x104),1);effect(140,F(0xec),F(0xf0)+100.0,B(0x104),1);effect(140,F(0xec),F(0xf0)+100.0,B(0x104),1);effect(141,F(0xec),F(0xf0)+100.0,B(0x104),-1);effect(142,F(0xec),F(0xf0),B(0x104),-1);}return;}

case 696:{landing();ADVANCE_TO(0);if(FRAME(0,3))event(29);return;}

case 710:{
 if(!S(0x13e)||S(0x13e)==6)landing();
 if(S(0x13e)==1||S(0x13e)==2){
  if(S(0x730)==1){if(S(0x734)<=60)++S(0x734);else{F(0xf0)=PF(0xf0);B(0x104)=-B(0x104);float packet[3]={0.0f,35.0f,0.0f};spawn(900,static_cast<float>(-960*C(0x104)+640),F(0xf0),B(0x104),1,packet,3);dispatch_character_wave_handle(5);S(0x730)=2;}}
  if(S(0x730)==3){F(0xf4)=-60.0;if(x_boundary()==C(0x104)){float packet[3]={0.0f,0.0f,5.0f};spawn(900,F(0xec)-300*C(0x104),F(0xf0)+150.0,B(0x104),1,packet,3);S(0x730)=0;select_sequence(3);return;}}
 }
 if(S(0x13e)==3&&S(0x730)==1){F(0xf4)=10.0;F(0xf8)=-2.0;F(0x100)=0.45f;select_sequence(4);return;}
 if(S(0x13e)==4||S(0x13e)==5){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(6);F(0xf0)=aya_surface(this);zero_motion();return;}}
 if(advance()){set_action_and_finalize(700);return;}
 if(ENTRY(1)){dispatch_character_wave_handle(5);float packet[3]={0.0f,35.0f,0.0f};spawn(900,F(0xec),F(0xf0),B(0x104),1,packet,3);}
 if(FRAME(0,2)){float packet[3]={0.0f,0.0f,5.0f};spawn(821,F(0xec),F(0xf0),B(0x104),-1,packet,3);packet[2]=6.0f;spawn(821,F(0xec),F(0xf0),B(0x104),-1,packet,3);for(int angle=0;angle<480;angle+=60){packet[0]=angle+45.0;packet[1]=15.0f;packet[2]=1.0f;spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}}return;
}

case 720:{landing();if(advance()){set_action_and_finalize(700);return;}if(!S(0x142)&&S(0x140)==8){float packet[3];switch(g_aya_action_match){case 0:{float base=static_cast<float>(static_cast<unsigned>(aya_random(360)));float counter=0.0f;counter=0.0f;do{packet[0]=counter*120.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<3.0);counter=0.0f;do{packet[0]=counter*120.0+60.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,static_cast<unsigned char>(-B(0x104)),1,packet,3);counter+=1.0;}while(counter<3.0);break;}case 1:{float base=static_cast<float>(static_cast<unsigned>(aya_random(360)));float counter=0.0f;counter=0.0f;do{packet[0]=counter*90.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<4.0);counter=0.0f;do{packet[0]=counter*90.0+45.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,static_cast<unsigned char>(-B(0x104)),1,packet,3);counter+=1.0;}while(counter<4.0);break;}case 2:{float base=static_cast<float>(static_cast<unsigned>(aya_random(360)));float counter=0.0f;counter=0.0f;do{packet[0]=counter*72.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<5.0);counter=0.0f;do{packet[0]=counter*72.0+36.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,static_cast<unsigned char>(-B(0x104)),1,packet,3);counter+=1.0;}while(counter<5.0);break;}case 3:{float base=static_cast<float>(static_cast<unsigned>(aya_random(360)));float counter=0.0f;counter=0.0f;do{packet[0]=counter*60.0+base;packet[1]=10.0f;packet[2]=3.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<6.0);counter=0.0f;do{packet[0]=counter*60.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<6.0);counter=0.0f;do{packet[0]=counter*60.0+30.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,static_cast<unsigned char>(-B(0x104)),1,packet,3);counter+=1.0;}while(counter<6.0);break;}}dispatch_character_wave_handle(20);}return;}

case 721:{if(!S(0x13e)||S(0x13e)==5)landing();if(S(0x13e)==1||S(0x13e)==2){F(0xf8)-=F(0x100);F(0xf4)*=static_cast<double>(0.98f);if(F(0xf8)<0.0)F(0xf8)=0.0;}if(S(0x13e)==4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();F(0xf0)=aya_surface(this);return;}}
 if(advance()){set_action_and_finalize(700);return;}if(ENTRY(1)){F(0xf8)=17.5;F(0xf4)=static_cast<float>(static_cast<unsigned>(aya_random(10)))-5.0;F(0x100)=0.5f;}if(ENTRY(3))zero_motion();if(S(0x13e)==3&&!S(0x142)){if(S(0x140)==8){float packet[3];switch(g_aya_action_match){case 0:{float base=static_cast<float>(static_cast<unsigned>(aya_random(360)));float counter=0.0f;counter=0.0f;do{packet[0]=counter*120.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<3.0);counter=0.0f;do{packet[0]=counter*120.0+60.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,static_cast<unsigned char>(-B(0x104)),1,packet,3);counter+=1.0;}while(counter<3.0);break;}case 1:{float base=static_cast<float>(static_cast<unsigned>(aya_random(360)));float counter=0.0f;counter=0.0f;do{packet[0]=counter*90.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<4.0);counter=0.0f;do{packet[0]=counter*90.0+45.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,static_cast<unsigned char>(-B(0x104)),1,packet,3);counter+=1.0;}while(counter<4.0);break;}case 2:{float base=static_cast<float>(static_cast<unsigned>(aya_random(360)));float counter=0.0f;counter=0.0f;do{packet[0]=counter*72.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<5.0);counter=0.0f;do{packet[0]=counter*72.0+36.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,static_cast<unsigned char>(-B(0x104)),1,packet,3);counter+=1.0;}while(counter<5.0);break;}case 3:{float base=static_cast<float>(static_cast<unsigned>(aya_random(360)));float counter=0.0f;counter=0.0f;do{packet[0]=counter*60.0+base;packet[1]=10.0f;packet[2]=3.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<6.0);counter=0.0f;do{packet[0]=counter*60.0+base;packet[1]=10.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);counter+=1.0;}while(counter<6.0);counter=0.0f;do{packet[0]=counter*60.0+30.0+base;packet[1]=6.0f;packet[2]=0.0f;spawn(901,F(0xec),F(0xf0)+100.0,static_cast<unsigned char>(-B(0x104)),1,packet,3);counter+=1.0;}while(counter<6.0);break;}}dispatch_character_wave_handle(20);}if(!S(0x142)&&S(0x140)==15)F(0x100)=0.5f;}return;}

case 730:{landing();if(S(0x13e)==1&&I(0x144)>60){next_sequence_block();return;}ADVANCE_TO(700);if(!S(0x13e)){if(S(0x140)<5&&!(I(0x144)%3)){F(0x73c)-=16.0;if(F(0x73c)<=-180.0)F(0x73c)+=360.0;float packet[3]={F(0x73c),15.0f,1.0f};spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}if(!S(0x142)&&S(0x140)==6){float packet[3]={0.0f,15.0f,0.0f};spawn(902,80*C(0x104)+F(0xec),F(0xf0),B(0x104),1,packet,3);dispatch_character_wave_handle(10);}}return;}

case 740:{
 if(!S(0x13e)||S(0x13e)==5)landing();
 if(S(0x13e)==1){
  ++S(0x732);--S(0x734);
  if(S(0x734)<=0){
   S(0x738)-=5;if(S(0x738)<10)S(0x738)=10;S(0x734)=S(0x738);
   float packet[3];packet[1]=URAND(30)+60.0;if(packet[1]>=90.0)packet[1]=90.0f;packet[2]=1.0f;
   dispatch_character_wave_handle(22);++S(0x736);
   if(!(S(0x736)%2)){JITTER_ANGLE(packet,0);ORBIT_SPAWN(packet,1680.0,100,50.0);}
   else{JITTER_ANGLE(packet,1);ORBIT_SPAWN(packet,1680.0,100,50.0);}
   if(!(S(0x736)%3)){
    packet[1]=static_cast<double>(S(0x738))+static_cast<double>(S(0x738))+100.0;if(packet[1]>=100.0)packet[1]=100.0f;packet[2]=2.0f;
    if(static_cast<unsigned>(aya_random(100))<50){JITTER_ANGLE(packet,0);ORBIT_SPAWN(packet,1680.0,300,150.0);}
    else{JITTER_ANGLE(packet,1);ORBIT_SPAWN(packet,1680.0,300,150.0);}
   }
  }
  if(!S(0x730)){F(0xf4)=C(0x104)*(640.0-F(0xec))*static_cast<double>(0.2f);F(0xf8)=(250.0-F(0xf0))*static_cast<double>(0.2f);}
  if(S(0x738)==10){next_sequence_block();S(0x736)=0;S(0x738)=60;return;}
 }
 if(S(0x13e)==2){
  if(!(S(0x732)%60))FIELD(AyaActionStateView *,0x168)->dispatch_character_wave_handle(10);
  ++S(0x732);--S(0x734);--S(0x736);
  float dx=(static_cast<double>(PF(0xec))-F(0xec))*C(0x104);F(0x73c)=-aya_atan(PF(0xf0)-F(0xf0),dx);F(0x740)+=1.0;
  switch(g_aya_action_match){case 0:case 1:MOTION->set_oriented_components(F(0x73c),0.75f);break;case 2:MOTION->set_oriented_components(F(0x73c),1.0f);break;case 3:MOTION->set_oriented_components(F(0x73c),1.5f);break;}
  if(!(S(0x732)%20)){float packet[3];JITTER_ANGLE(packet,0);packet[1]=URAND(30)+60.0;packet[2]=6.0f;ORBIT_SPAWN(packet,1680.0,100,50.0);}
  if(g_aya_action_match==2){
   if(!(S(0x732)%360)){dispatch_character_wave_handle(0);float packet[3];WIDE_ANGLE(packet,0);packet[1]=30.0f;packet[2]=9.0f;ORBIT_SPAWN(packet,600.0,100,50.0);}
   if(S(0x732)%360==180){dispatch_character_wave_handle(0);float packet[3];WIDE_ANGLE(packet,1);packet[1]=30.0f;packet[2]=9.0f;ORBIT_SPAWN(packet,600.0,100,50.0);}
  }else if(g_aya_action_match==3){
   if(!(S(0x732)%180)){dispatch_character_wave_handle(0);float packet[3];WIDE_ANGLE(packet,0);packet[1]=30.0f;packet[2]=9.0f;ORBIT_SPAWN(packet,600.0,100,50.0);}
   if(S(0x732)%180==90){dispatch_character_wave_handle(0);float packet[3];WIDE_ANGLE(packet,1);packet[1]=30.0f;packet[2]=9.0f;ORBIT_SPAWN(packet,600.0,100,50.0);}
  }
  if(S(0x734)<=0){S(0x734)=10;dispatch_character_wave_handle(22);float packet[3];packet[1]=URAND(30)+120.0;packet[2]=3.0f;
   if(static_cast<unsigned>(aya_random(100))<50){JITTER_ANGLE(packet,0);ORBIT_SPAWN(packet,1680.0,300,150.0);}
   else{JITTER_ANGLE(packet,1);ORBIT_SPAWN(packet,1680.0,300,150.0);}
  }
  if(!S(0x736)){S(0x738)-=10;if(S(0x738)<5)S(0x738)=5;S(0x736)=S(0x738);float packet[3];packet[1]=static_cast<double>(S(0x738))+static_cast<double>(S(0x738))+100.0;if(packet[1]>=180.0)packet[1]=180.0f;packet[2]=2.0f;
   if(static_cast<unsigned>(aya_random(100))<50){JITTER_ANGLE(packet,0);ORBIT_SPAWN(packet,1680.0,300,150.0);}
   else{JITTER_ANGLE(packet,1);ORBIT_SPAWN(packet,1680.0,300,150.0);}
  }
 }
 ADVANCE_TO(0);
 if(ENTRY(1)){S(0x734)=60;S(0x736)=60;S(0x738)=60;F(0x740)=0.0;float packet[3]={0.0f,0.0f,0.0f};spawn(903,F(0xec),F(0xf0),B(0x104),1,packet,3);packet[2]=4.0f;spawn(903,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);packet[2]=5.0f;spawn(903,F(0xec),F(0xf0)+100.0,B(0x104),1,packet,3);C(0x104)=-1;dispatch_character_wave_handle(21);}return;
}

case 770:{ADVANCE_TO(700);if(FRAME(0,7)){B(0x655)=1;finalize(-1);texture(2,-1);copy_action_word();S(0x76c)=0;S(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);}return;}

case 791:{advance();if(FRAME(0,5))spawn(990,F(0xec),F(0xf0),B(0x104),1,0,0);if(!I(0x144)){if(FRAME(1,0))B(0x104)=PB(0x104);if(ENTRY(2)){float packet[3]={0.0f,0.0f,0.0f};spawn(997,F(0xec),F(0xf0),B(0x104),1,packet,3);for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}dispatch_character_wave_handle(5);}}return;}

case 795:{if(!S(0x13e)){F(0xf8)-=static_cast<double>(0.3f);if(static_cast<unsigned char>(crossed())){event(30);select_sequence(1);F(0xf0)=aya_surface(this);zero_motion();return;}}ADVANCE_TO(700);return;}

case 797:{
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){
  F(0xec)=480.0;layout(5.0f);float packet[3]={0.0f,0.0f,0.0f};
  spawn(821,F(0xec),F(0xf0),B(0x104),1,packet,3);dispatch_character_wave_handle(15);
  for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}
  select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;
 }ADVANCE_TO(0);return;
}

case 798:{
 if(static_cast<unsigned char>(crossed())&&S(0x13e)<2){
  F(0xec)=800.0;layout(5.0f);float packet[3]={0.0f,0.0f,0.0f};
  spawn(821,F(0xec),F(0xf0),B(0x104),1,packet,3);dispatch_character_wave_handle(15);
  for(int angle=0;angle<360;angle+=60){packet[0]=angle+30.0;packet[1]=15.0f;packet[2]=1.0f;spawn(821,F(0xec),F(0xf0),B(0x104),(packet[0]>=0.0&&packet[0]<=180.0)?1:-1,packet,3);}
  select_sequence(2);F(0xf0)=aya_surface(this);zero_motion();return;
 }ADVANCE_TO(700);return;
}

default:common_update();return;
}
paired_817_request:
 spawn(817,F(0xec)-130*C(0x104),F(0xf0)+50.0,static_cast<unsigned char>(-B(0x104)),1,paired_request,3);
 MOTION->set_oriented_components(0.0f,25.0f);counter(200,120);phase_counter(50);dispatch_character_wave_handle(19);return;
idle_drift:
 if(!B(0x47e)){zero_motion();advance();return;}
 if(F(0xf4)>0.0){F(0xf4)-=0.5;if(F(0xf4)<0.0){zero_motion();B(0x47e)=0;}}
 if(F(0xf4)<0.0){F(0xf4)+=0.5;if(F(0xf4)>0.0){zero_motion();B(0x47e)=0;advance();return;}}
 advance();return;
dash_landed:zero_motion();F(0xf0)=aya_surface(this);set_action_and_finalize(10);return;
landed:set_action_and_finalize(10);F(0xf0)=aya_surface(this);zero_motion();return;
}
}
