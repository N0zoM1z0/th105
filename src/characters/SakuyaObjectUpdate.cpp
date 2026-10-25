// Manual source hypothesis for JP1.06a SakuyaObject slot28, 4E0D30.
#include "SakuyaObjectUpdate.hpp"
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define I(o) AT(this,int,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define H AT(this,float *,0x340)
#define P AT(this,SakuyaObjectUpdateView *,0x348)
#define R AT(this,SakuyaObjectUpdateView *,0x34c)
#define A AT(this,SakuyaObjectUpdateView *,0x170)
#define D(x) static_cast<double>(x)
#define MOTION reinterpret_cast<SakuyaUpdateMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define MOVE() MOTION->set_components(H[0],H[1])
#define STEP() { F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8); }
#define RETIRE() {--I(0x330);return;}
#define FRAME_EXIT() {if(advance_frame())--I(0x330);return;}
#define OUTSIDE(xh,xl,yh,yl) (F(0xec)>xh || F(0xec)<xl || F(0xf0)>yh || F(0xf0)<yl)
#define ORDERED_OUTSIDE(xh,xl,yh,yl) (!(F(0xec)<=xh && F(0xec)>=xl && F(0xf0)<=yh && F(0xf0)>=yl))
#define CONTACT2468 (I(0x180)==2 || I(0x180)==4 || I(0x180)==6 || I(0x180)==8)
#define CONTACT24768 (I(0x180)==2 || I(0x180)==4 || I(0x180)==7 || I(0x180)==6 || I(0x180)==8)
#define WORDS(a) reinterpret_cast<const unsigned *>(a)
#define SPAWN(a,l,c) spawn_unparented(a,F(0xec),F(0xf0),B(0x104),l,WORDS(payload),c)
#define PARENTED(a,l,c) spawn_parented(a,F(0xec),F(0xf0),B(0x104),l,WORDS(payload),c)
#define random_float(limit) static_cast<float>(static_cast<unsigned>(selector_random_roll(limit)))
void SakuyaObjectUpdateView::update_action_state()
{
 switch(S(0x13c)) {
 case 800:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)<3) {
   if(S(0x140)<2 && emit_repeated(0,0,2))RETIRE();
   if(S(0x140)==0)MOVE();else F(0xf8)-=0.5;
   H[1]+=0.5;
   if(S(0x140)<2 && (I(0x180)==6 || I(0x180)==2 || I(0x180)==4 || I(0x180)==8)) {
    P->dispatch_character_wave_handle(3);set_sequence_frame(2);
    F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.1f))+5.0;
   }
   if(S(0x140)==2) {F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  }
  if(S(0x13e)==3 || S(0x13e)==7) {
   if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);if(AT(R,short,0x140)!=0)RETIRE();
   F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);
  }
  if(S(0x13e)>3 && S(0x13e)<7) {
   if(S(0x140)<2 && emit_repeated(0,0,4))RETIRE();
   if(S(0x142)==0 && S(0x140)==0)replace_secondary(994,4.0f,5,2,2);
   if(S(0x140)<2 && (I(0x180)==2 || I(0x180)==4 || I(0x180)==8)) {
    P->dispatch_character_wave_handle(3);set_sequence_frame(2);release_secondary();
    F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.1f))+5.0;
   }
   if(S(0x140)==2) {F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  }
  STEP();if(ORDERED_OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();
  if(advance_frame())--I(0x330);if(S(0x142)==0 && S(0x140)==2)--I(0x330);return;
 case 801:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)>=0 && S(0x13e)<3) {
   if(S(0x140)<2 && emit_repeated(0,0,4))RETIRE();
   if(S(0x142)==0 && S(0x140)==0)replace_secondary(994,4.0f,10,2,2);
   if(S(0x140)<2) {
    advance_six(10);
    if(CONTACT2468) {B(0x184)=0;set_sequence_frame(2);P->dispatch_character_wave_handle(3);I(0x144)=0;release_secondary();F(0xf4)=-F(0xf4)*0.5;F(0xf8)=static_cast<float>(random_float(30)*D(0.1f))+5.0;return;}
   }
   if(S(0x140)==2) {F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  } else if(S(0x13e)==3) {
   if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);if(AT(R,short,0x140)!=0)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);
  }
  STEP();if(ORDERED_OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();
  if(advance_frame())--I(0x330);if(S(0x142)==0 && S(0x140)==2)--I(0x330);return;
 case 802:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)>=0 && S(0x13e)<3) {
   if(S(0x142)==0 && S(0x140)==0)replace_secondary(994,4.0f,10,2,2);
   if(S(0x140)<3 && emit_repeated(0,2,5))RETIRE();
   if(S(0x140)<3) {
    advance_six(5);
    if(CONTACT2468) {B(0x184)=0;set_sequence_frame(4);P->dispatch_character_wave_handle(3);release_secondary();F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.05f))+5.0;}
    if(S(0x140)==0 || S(0x140)==2)MOVE();
    if(S(0x140)==1)MOTION->set_components(H[0],static_cast<float>(H[1]*D(0.05f)));
   }
   if(S(0x140)==4) {F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  } else if(S(0x13e)==3) {
   if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);if(AT(R,short,0x140)!=2)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);
  }
  STEP();if(ORDERED_OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();
  if(advance_frame())--I(0x330);if(S(0x142)==0 && S(0x140)==3)--I(0x330);
  if(S(0x13e)<3 && S(0x142)==0 && S(0x140)==2) {replace_secondary(994,4.0f,10,2,2);float payload[3]={H[0],0,3};PARENTED(802,-1,3);}return;
 case 803:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)) {
  case 0:case 1:
   if(S(0x140)==0 && emit_repeated(0,0,3))RETIRE();
   if(S(0x142)==0 && S(0x140)==0)replace_secondary(994,4.0f,10,2,2);
   if(S(0x140)==0) {
    if(CONTACT24768) {release_secondary();set_sequence_frame(1);P->dispatch_character_wave_handle(3);I(0x144)=0;F(0xf4)=-F(0xf4);F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;return;}
    if(C(0x184)<1) {float alpha=static_cast<float>(F(0x374)-20.0);F(0x374)=alpha;B(0x113)=static_cast<unsigned char>(alpha);if(F(0x374)<0)RETIRE();set_secondary_alpha(static_cast<unsigned char>(F(0x374)));}
    else if(S(0x13e)==0 && F(0xf8)<0 && F(0xf0)<=stage_surface_height()) {P->dispatch_character_wave_handle(3);F(0xf8)=-F(0xf8);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
   }break;
  case 2:
   if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);
   if(!(AT(R,short,0x140)<1 && AT(R,signed char,0x184)>0)) {if(B(0x113)<20)RETIRE();B(0x113)-=20;}
   goto step803;
  case 3:case 4:
   if(S(0x140)==0 && emit_repeated(0,0,3))RETIRE();
   if(S(0x142)==0 && S(0x140)==0)replace_secondary(994,4.0f,10,2,2);
   if(S(0x140)==0) {
    if(CONTACT24768) {release_secondary();next_sequence_frame();P->dispatch_character_wave_handle(3);I(0x144)=0;F(0xf4)=-F(0xf4);F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;return;}
    if(C(0x184)<1) {float alpha=static_cast<float>(F(0x374)-20.0);F(0x374)=alpha;B(0x113)=static_cast<unsigned char>(alpha);if(F(0x374)<0)RETIRE();set_secondary_alpha(static_cast<unsigned char>(F(0x374)));}
    else if(S(0x13e)==3) {
     if(C(0x104)*F(0xf4)>0 && F(0xec)>=sakuya_update_right) {P->dispatch_character_wave_handle(3);F(0xf4)=-F(0xf4);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(C(0x104)*F(0xf4)<0 && F(0xec)<=sakuya_update_left) {P->dispatch_character_wave_handle(3);F(0xf4)=-F(0xf4);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    }
   }break;
  default:goto step803;
  }
  if(S(0x140)==1) {F(0x12c)+=30.0;F(0xf8)-=0.5;if(F(0xf0)+F(0xf8)<=0 && F(0xf8)<0)F(0xf8)=-F(0xf8)*0.5;if(I(0x144)>29){if(B(0x113)<=20)RETIRE();B(0x113)-=20;}}
 step803:STEP();FRAME_EXIT();
 case 804:
  if(I(0x180)==5 || (AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150 && S(0x13e)==0))RETIRE();
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==0){B(0x184)=1;S(0x364)=0;}
  if(S(0x13e)==0) {
   if(S(0x140)==0){F(0x12c)-=30.0;H[1]-=2.5;if(H[1]<0)H[1]=0;}
   if(S(0x140)==1){if(S(0x142)==0){replace_secondary(994,6.0f,20,1,2);turn_heading(0,180.0f,100.0f);}H[1]+=2.5;F(0x12c)=H[0];MOVE();if(I(0x180)==6){++B(0x184);I(0x180)=0;}if(I(0x180)!=0){if(C(0x184)<1){next_sequence_block();F(0x120)=F(0x11c)=2.0f;}else I(0x180)=0;}}
   MOVE();STEP();if(S(0x140)==1){float payload[3]={H[0],0,2};P->spawn_owned(804,F(0xec),F(0xf0),B(0x104),-1,WORDS(payload),3);}
  }
  if(S(0x13e)==1){F(0x11c)+=D(0.1f);F(0x120)*=D(0.65f);MOVE();STEP();}
  if(ORDERED_OUTSIDE(1680.0,-400.0,960.0,-120.0))RETIRE();
  if(advance_frame())--I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1)--I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2)--I(0x330);return;
 case 805:
  if(I(0x180)==5 || (AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150 && S(0x140)<2))RETIRE();
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==0){B(0x184)=1;S(0x364)=25;S(0x366)=0;}
  if(S(0x13e)==0){S(0x366)+=S(0x364);S(0x364)-=5;if(S(0x364)<0)S(0x364)=0;
   SakuyaObjectUpdateView *owner=P;
   double cosine=lookup_orientation_cosine_quantized_abs(H[0]);
   F(0xec)=cosine*S(0x366)*C(0x104)+AT(owner,float,0xec);
   double owner_y=AT(owner,float,0xf0);
   F(0xf0)=owner_y-lookup_orientation_sine_quantized_abs(H[0])*S(0x366)+130.0;
   if(AT(P,short,0x13c)==540 && AT(P,short,0x13e)==2){next_sequence_block();replace_secondary(994,6.0f,10,1,2);}
   if(AT(P,short,0x13c)!=540)select_sequence(2);
   float payload[3]={H[0],0,3};P->spawn_owned(805,F(0xec),F(0xf0),B(0x104),-1,WORDS(payload),3);
  }
  if(S(0x13e)==1){MOVE();H[1]+=1.0;STEP();float payload[3]={H[0],0,3};P->spawn_owned(805,F(0xec),F(0xf0),B(0x104),-1,WORDS(payload),3);if(I(0x180)==6){++B(0x184);I(0x180)=0;}if(I(0x180)!=0){if(C(0x184)<1)next_sequence_block();else I(0x180)=0;}}
  if(S(0x13e)==2){release_secondary();if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  if(OUTSIDE(1380.0f,-100.0,960.0,-120.0))RETIRE();
  if(advance_frame())--I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==3)--I(0x330);return;
 case 810:
  if(S(0x13e)<2) {
   if(AT(P,short,0x13c)<500 || AT(P,short,0x13c)>503 || S(0x13e)>2){if(B(0x113)<=20)RETIRE();B(0x113)-=20;}
   else {F(0xec)=C(0x104)*AT(P,float,0xf4)+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf8)+AT(P,float,0xf0);}
   F(0x12c)+=10.0;
  }
#define ORBIT810() { \
 H[0]+=10.0;if(H[0]>360.0f)H[0]-=360.0; \
 double facing=C(0x104);SakuyaObjectUpdateView *owner=P; \
 double cosine=lookup_orientation_cosine_quantized_abs(H[0]);SakuyaObjectUpdateView *vertical_owner=P; \
 F(0xec)=facing*AT(owner,float,0xf4)+AT(owner,float,0xec)+cosine*F(0x370)*facing; \
 double sine=lookup_orientation_sine_quantized_abs(H[0]); \
 F(0xf0)=AT(vertical_owner,float,0xf0)+125.0+AT(vertical_owner,float,0xf8)+sine*F(0x370)*0.25; \
 if(!(H[0]>=0) || H[0]>180.0f)B(0x33c)=1;else B(0x33c)=255; \
}
  if(S(0x13e)==2){F(0x12c)-=40.0;F(0x370)+=15.0;if(F(0x370)>H[1])F(0x370)=H[1];
   if(AT(P,short,0x13c)<500 || AT(P,short,0x13c)>503 || AT(P,short,0x13e)>2){ORBIT810();if(B(0x113)<=20)RETIRE();B(0x113)-=20;}else {ORBIT810();}
  }
  if(S(0x13e)==3){F(0x12c)-=20.0;F(0x370)+=15.0;if(F(0x370)>H[1])F(0x370)=H[1];
   if(AT(P,short,0x13c)<500 || AT(P,short,0x13c)>503 || AT(P,short,0x13e)>2){ORBIT810();if(B(0x113)<=20)RETIRE();B(0x113)-=20;}else {ORBIT810();}
  }
#undef ORBIT810
  if(advance_frame())--I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1)--I(0x330);return;
 case 811:
  if(I(0x180)==5 || OUTSIDE(1680.0,-400.0,1000.0,-160.0f))RETIRE();
  if(S(0x13e)<3 && S(0x140)<2 && emit_repeated(0,0,3))RETIRE();
  if(S(0x13e)==0 || S(0x13e)==1 || S(0x13e)==2) {
   if(S(0x140)==0) {
    if(CONTACT24768){next_sequence_frame();P->dispatch_character_wave_handle(3);I(0x144)=0;F(0xf4)=-F(0xf4)*0.5;F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;return;}
    if(C(0x184)<1){F(0x374)-=20.0;B(0x113)=static_cast<unsigned char>(F(0x374));if(F(0x374)<0)RETIRE();}
    else if(S(0x13e)<2) {
     if(C(0x104)*F(0xf4)>0 && F(0xec)>=sakuya_update_right){F(0xf4)=-F(0xf4);P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(C(0x104)*F(0xf4)<0 && F(0xec)<=sakuya_update_left){F(0xf4)=-F(0xf4);P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(F(0xf8)>0 && F(0xf0)>=sakuya_update_top){F(0xf8)=-F(0xf8);P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    }
   }
   if(S(0x140)==1){F(0x12c)+=30.0;F(0xf8)-=0.5;if(F(0xf0)+F(0xf8)<=0 && F(0xf8)<0)F(0xf8)=-F(0xf8)*0.5;if(I(0x144)>29){if(B(0x113)<=20)RETIRE();B(0x113)-=20;}}
  }
  if(S(0x13e)==3){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);if(AT(R,signed char,0x184)<1){if(B(0x113)<20)RETIRE();B(0x113)-=20;}if(AT(R,short,0x140)>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 812:
  if(I(0x180)==5)RETIRE();
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==0)replace_secondary(994,6.0f,30,2,2);
  if(S(0x13e)==0){if(S(0x140)==0){if(emit_repeated(0,2,2))RETIRE();MOVE();advance_six(10);if(I(0x180)==2 || I(0x180)==4 || I(0x180)==7 || I(0x180)==8){release_secondary();next_sequence_frame();P->dispatch_character_wave_handle(3);I(0x144)=0;F(0xf4)=-F(0xf4)*0.25;F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;return;}}
   else{F(0xf8)-=D(0.35f);F(0x12c)-=30.0;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}}
  if(S(0x13e)==1){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);if(AT(R,short,0x140)>0)RETIRE();}
  STEP();if(OUTSIDE(1680.0,-400.0,1000.0,-160.0f))RETIRE();
  if(advance_frame())--I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1)--I(0x330);return;
 case 813:
  if(S(0x13e)<6){F(0xf8)-=D(0.1f);F(0xf0)+=F(0xf8);F(0xec)+=C(0x104)*F(0xf4);
   if(S(0x364)<5)F(0x12c)+=S(0x36a);if(S(0x364)>4)F(0x12c)-=S(0x36a);
   if(S(0x366)<5)F(0x124)+=S(0x36c);if(S(0x366)>4)F(0x124)-=S(0x36c);
   if(S(0x368)<5)F(0x128)+=S(0x36c);if(S(0x368)>4)F(0x128)-=S(0x36c);
   if(B(0x113)<=8)RETIRE();B(0x113)-=8;
  }
  if(S(0x13e)==6 || S(0x13e)==7){F(0xf4)*=D(0.9f);F(0xf0)+=F(0xf8);F(0xec)+=C(0x104)*F(0xf4);if(S(0x140)>0){if(B(0x113)<=10)RETIRE();B(0x113)-=10;}}
  if(S(0x13e)==8){F(0x370)-=D(0.2f);if(F(0x370)<0.001f)F(0x370)=0.01f;F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)+F(0x370));if(I(0x144)>4){if(B(0x113)<=10)RETIRE();B(0x113)-=10;}}
  if(S(0x13e)==9 || S(0x13e)==10){F(0xf4)*=D(0.9f);F(0xf0)+=F(0xf8);F(0xec)+=C(0x104)*F(0xf4);if(B(0x113)<=20)RETIRE();B(0x113)-=20;}
  FRAME_EXIT();
 case 815:
  switch(S(0x13e)) {
  case 0:
   if(emit_repeated(0,1,2))RETIRE();F(0x12c)+=20.0;
   if(S(0x140)<2){F(0x370)+=H[1];H[1]-=0.5;if(H[1]<=D(0.1f))H[1]=0.1f;F(0x374)+=C(0x104)*6;
    F(0xec)=S(0x364)+lookup_orientation_cosine_quantized_abs(F(0x374)+H[0])*F(0x370);
    F(0xf0)=S(0x366)+lookup_orientation_sine_quantized_abs(H[0]+F(0x374))*F(0x370);
    if(S(0x140)==1){if(S(0x142)==0){float child[3]={0,0,1};spawn_parented(815,F(0xec),F(0xf0),B(0x104),1,WORDS(child),3);child[1]=-15;child[2]=4;spawn_unparented(815,F(0xec),F(0xf0),B(0x104),1,WORDS(child),3);}
     if(CONTACT24768){set_sequence_frame(3);P->dispatch_character_wave_handle(3);I(0x144)=0;F(0xf4)=static_cast<float>(static_cast<unsigned>(selector_random_roll(16)-8));F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;return;}
     if(C(0x184)<1){set_sequence_frame(2);return;}
    }
   }
   if(S(0x140)==2 || S(0x140)==3){if(S(0x142)==0 && S(0x140)==2){F(0xf4)=static_cast<float>(static_cast<unsigned>(selector_random_roll(16)-8));F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;}F(0xf8)-=D(0.35f);F(0x12c)+=10.0;STEP();if(B(0x113)<=10)RETIRE();B(0x113)-=10;}break;
  case 1:
   F(0x12c)-=20.0;F(0x370)+=15.0;if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);if(AT(R,short,0x140)!=1)RETIRE();break;
  case 2:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;
   if(I(0x144)<4)F(0x120)+=0.5;else F(0x120)*=D(0.9f);
   if(I(0x144)>4){if(B(0x111)<10){B(0x111)=0;B(0x110)=0;if(B(0x113)<10)RETIRE();B(0x113)-=10;}else{B(0x111)-=10;B(0x110)-=10;}}break;
  case 3:case 4:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;F(0x120)=F(0x11c);F(0x12c)+=H[1];H[1]*=D(0.95f);
   if(I(0x144)>4){if(B(0x111)<10){B(0x111)=0;B(0x110)=0;if(B(0x113)<10)RETIRE();B(0x113)-=10;}else{B(0x111)-=10;B(0x110)-=10;}}break;
  }
  if(advance_frame())--I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1)--I(0x330);return;
 case 816:
  if(I(0x180)==5 || (S(0x13e)<3 && S(0x140)<2 && emit_repeated(1,3,5)))RETIRE();
  if(S(0x13e)==0 || S(0x13e)==1 || S(0x13e)==2){
   if(S(0x142)==0 && S(0x140)==0)replace_secondary(994,6.0f,40,2,2);
   if(S(0x140)==0){if(advance_six(15))B(0x184)=0;if(AT(P,signed char,0x609)<2 && I(0x180)!=0)B(0x184)=0;
    if(CONTACT24768 && C(0x184)<1){next_sequence_frame();P->dispatch_character_wave_handle(3);release_secondary();I(0x144)=0;F(0xf4)=-F(0xf4);F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;return;}
    if(C(0x184)<1 || OUTSIDE(1380.0f,-100.0,900.0,-200.0)){F(0x374)-=20.0;B(0x113)=static_cast<unsigned char>(F(0x374));if(F(0x374)<0)RETIRE();set_secondary_alpha(static_cast<unsigned char>(F(0x374)));}
    else if(S(0x13e)<3 && C(0x184)>1){
     if(C(0x104)*F(0xf4)>0 && F(0xec)>=sakuya_update_right){P->dispatch_character_wave_handle(3);F(0xf4)=-F(0xf4);if(I(0x180)==0)--B(0x184);I(0x180)=0;F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(C(0x104)*F(0xf4)<0 && F(0xec)<=sakuya_update_left){P->dispatch_character_wave_handle(3);F(0xf4)=-F(0xf4);if(I(0x180)==0)--B(0x184);I(0x180)=0;F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(F(0xf8)>0 && F(0xf0)>=sakuya_update_top){P->dispatch_character_wave_handle(3);F(0xf8)=-F(0xf8);if(I(0x180)==0)--B(0x184);I(0x180)=0;F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(F(0xf8)<0 && F(0xf0)<=sakuya_update_bottom){P->dispatch_character_wave_handle(3);F(0xf8)=-F(0xf8);if(I(0x180)==0)--B(0x184);I(0x180)=0;F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    }
   }
   if(S(0x140)==1){F(0x12c)+=30.0;F(0xf8)-=0.5;if(F(0xf0)+F(0xf8)<=0 && F(0xf8)<0)F(0xf8)=-F(0xf8)*0.5;if(I(0x144)>29){if(B(0x113)<=20)RETIRE();B(0x113)-=20;}}
  }
  if(S(0x13e)==3){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);if(AT(R,signed char,0x184)<1){if(B(0x113)<20)RETIRE();B(0x113)-=20;}if(AT(R,short,0x140)>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 817:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)>=0 && S(0x13e)<3){
   if(S(0x140)<2 && emit_repeated(0,2,5))RETIRE();
   if(S(0x142)==0 && S(0x140)==2){replace_secondary(994,4.0f,10,2,2);float payload[3]={H[0],0,3};PARENTED(817,-1,3);}
   if(S(0x140)<3){
    if(CONTACT2468){B(0x184)=0;P->dispatch_character_wave_handle(3);set_sequence_frame(4);release_secondary();F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.05f))+5.0;}
    if(S(0x140)==0 || S(0x140)==2)MOVE();
    if(S(0x140)==1){F(0xf4)=0;F(0xf8)=0;
     if((AT(P,short,0x13c)==545 && AT(P,short,0x13e)==0 && AT(P,short,0x140)==8) || (AT(P,short,0x13c)==546 && AT(P,short,0x13e)==0 && AT(P,short,0x140)==8) || (AT(P,short,0x13c)==547 && AT(P,short,0x13e)==0 && AT(P,short,0x140)==8) || (AT(P,short,0x13c)==548 && AT(P,short,0x13e)==0 && AT(P,short,0x140)==8)){next_sequence_frame();return;}}
   }
   if(S(0x140)==4){F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  }else if(S(0x13e)==3){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);if(AT(R,short,0x140)!=2)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);}
  STEP();if(ORDERED_OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();if(advance_frame())--I(0x330);if(S(0x142)==0 && S(0x140)==3)--I(0x330);return;
 case 818:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){
   if(S(0x140)<2 && emit_repeated(0,0,3))RETIRE();
   if(S(0x140)==0)MOVE();
   if(S(0x140)==1){if(AT(P,short,0x48c)<1){next_sequence_frame();S(0x344)=0;replace_secondary(994,4.0f,10,2,2);float payload[3]={H[0],0,1};PARENTED(818,-1,3);return;}MOTION->set_components(H[0],0);}
   if(S(0x140)==2){if(CONTACT2468){B(0x184)=0;set_sequence_frame(4);P->dispatch_character_wave_handle(3);release_secondary();F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.05f))+5.0;return;}if(I(0x180)!=0){next_sequence_frame();release_secondary();return;}MOVE();}
   if(S(0x140)==3){F(0xf4)=0;F(0xf8)=0;if(I(0x144)>19)RETIRE();}
   if(S(0x140)==4){F(0x12c)-=5.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  }else if(S(0x13e)==1){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);if(AT(R,short,0x140)!=2)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);}
  else if(S(0x13e)==2){F(0x11c)-=D(0.15f);if(F(0x11c)<1)F(0x11c)=1;F(0x120)=F(0x11c);if(I(0x144)>19)RETIRE();}
  STEP();if(ORDERED_OUTSIDE(1580.0f,-300.0f,1200.0f,-300.0f))RETIRE();if(advance_frame())RETIRE();
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1)RETIRE();if(S(0x142)==0 && S(0x140)==3)RETIRE();return;
 case 849:
  if(S(0x13e)==0){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0);if(AT(P,short,0x13c)!=308)RETIRE();}
  else if(S(0x13e)==1){F(0xec)=AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0);if(AT(P,short,0x13c)!=304 && AT(P,short,0x13c)!=309)RETIRE();}
  else if(S(0x13e)==2){MOVE();H[1]-=0.5;if(H[1]<0.5f)H[1]=0.5f;F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;F(0x12c)+=F(0x374);F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)+D(0.02f));if(I(0x144)>=0){if(B(0x113)<=5)RETIRE();B(0x113)-=5;}F(0xec)+=C(0x104)*F(0xf4);F(0xf0)+=F(0xf8)*0.25;}
  if(AT(P,short,0x186)!=0)return;if(advance_frame())--I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1)--I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==2)--I(0x330);return;
 case 850:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){H[1]-=2.0;if(H[1]<1){H[1]=1;next_sequence_block();}MOVE();}
  if(S(0x13e)==1){F(0x12c)+=40.0;MOVE();if(I(0x144)>=H[3]){next_sequence_block();float *words=H;words[0]=-atan2_degrees(static_cast<float>(AT(A,float,0xf0)+100.0-F(0xf0)),static_cast<float>(C(0x104)*(AT(A,float,0xec)-F(0xec))));F(0x12c)=words[0];float children[4]={words[0],0,4,0};spawn_parented(850,F(0xec),F(0xf0),B(0x104),-1,WORDS(children),4);children[2]=5;spawn_parented(850,F(0xec),F(0xf0),B(0x104),-1,WORDS(children),4);H[1]=35.0f;return;}}
  if(S(0x13e)==2){H[1]+=D(0.2f);MOVE();if(OUTSIDE(1680.0,-400.0,1300.0f,-360.0f))RETIRE();}
  if(S(0x13e)==4){if(!R)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);if(AT(R,short,0x140)>0)RETIRE();}
  if(S(0x13e)==5){if(!R)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);F(0x11c)+=D(0.1f);F(0x120)*=D(0.95f);if(AT(R,short,0x140)>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 851:
  F(0x12c)+=0.25;if(AT(P,short,0x7a6)<1 || S(0x364)!=0)S(0x364)=1;else if(B(0x113)<220)B(0x113)+=25;else B(0x113)=255;
  if(S(0x364)==1){if(B(0x113)>10)B(0x113)-=10;else RETIRE();}return;
 case 852:
  if(S(0x13e)==0){F(0x11c)+=D(0.1f);F(0x120)+=D(0.02f);}
  if(S(0x13e)==1 && ((AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150) || AT(P,short,0x13c)!=602 || I(0x144)>14))RETIRE();
  STEP();FRAME_EXIT();
 case 853:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){F(0x12c)+=40.0;H[1]-=1.0;if(H[1]<0.5f)H[1]=0.5f;MOVE();if(I(0x144)>=H[3]){--I(0x330);float children[4];children[1]=30;children[2]=1;children[3]=90;P->dispatch_character_wave_handle(13);
    float count=0;do{children[0]=(H[0]+15.0)-count*15.0;spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,WORDS(children),4);count+=1.0;}while(count<3.0f);
    children[2]=6;spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,WORDS(children),4);children[2]=7;spawn_unparented(853,F(0xec),F(0xf0),B(0x104),1,WORDS(children),4);}}
  if(S(0x13e)==1){MOVE();if(I(0x144)>=H[3]){next_sequence_block();float *words=H;words[0]=-atan2_degrees(static_cast<float>(AT(A,float,0xf0)+100.0-F(0xf0)),static_cast<float>(C(0x104)*(AT(A,float,0xec)-F(0xec))));words[1]=80.0f;F(0x12c)=words[0];return;}}
  if(S(0x13e)==2){MOVE();if(I(0x144)>179)RETIRE();}
  if(S(0x13e)==4){if(!R)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);if(AT(R,short,0x140)>0)RETIRE();}
  if(S(0x13e)==5){if(!R)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);F(0x11c)+=D(0.1f);F(0x120)*=D(0.95f);if(AT(R,short,0x140)>0)RETIRE();}
  if(S(0x13e)==6){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)-D(0.01f));if(B(0x113)<=20)RETIRE();B(0x113)-=20;B(0x110)-=20;B(0x111)-=20;}
  if(S(0x13e)==7){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)+D(0.2f));if(B(0x113)<=30)RETIRE();B(0x113)-=30;B(0x110)-=30;B(0x111)-=30;}
  STEP();FRAME_EXIT();
 case 854:
  if(AT(P,short,0x7a4)<1 || S(0x364)!=0)S(0x364)=1;else if(B(0x113)>219)B(0x113)=255;else B(0x113)+=25;
  if(S(0x364)==1){if(B(0x113)>10)B(0x113)-=10;else RETIRE();}return;
 case 855:
  if(S(0x13e)==0){F(0x11c)+=0.5;F(0x120)+=D(0.02f);}
  if(S(0x13e)==1){F(0x11c)+=0.5;F(0x120)*=D(0.98f);H[1]+=1.0;MOVE();if(I(0x144)>119 || F(0x120)<=D(0.1f))RETIRE();}
  if(S(0x13e)==2 && ((AT(P,short,0x13c)>49 && AT(P,short,0x13c)<150) || AT(P,short,0x13c)!=605 || I(0x144)>39))RETIRE();
  STEP();if(advance_frame())--I(0x330);if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1)--I(0x330);return;
 case 856:
  if(I(0x180)==5 || OUTSIDE(1680.0,-400.0,1000.0,-160.0f))RETIRE();
  if(S(0x13e)<3){
   if(S(0x140)==0){
    if(CONTACT24768){next_sequence_frame();P->dispatch_character_wave_handle(3);I(0x144)=0;F(0xf4)=-F(0xf4)*0.5;F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;return;}
    if(C(0x184)<1){F(0x374)-=20.0;B(0x113)=static_cast<unsigned char>(F(0x374));if(F(0x374)<0)RETIRE();}
    else if(S(0x13e)<1){
     if(C(0x104)*F(0xf4)>0 && F(0xec)>=sakuya_update_right){F(0xf4)=-F(0xf4);P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(C(0x104)*F(0xf4)<0 && F(0xec)<=sakuya_update_left){F(0xf4)=-F(0xf4);P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(F(0xf8)>0 && F(0xf0)>=sakuya_update_top){F(0xf8)=-F(0xf8);P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(F(0xf8)<0 && F(0xf0)<=0){F(0xf8)=-F(0xf8);P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    }
   }
   if(S(0x140)==1){F(0x12c)+=30.0;F(0xf8)-=0.5;if(F(0xf0)+F(0xf8)<=0 && F(0xf8)<0)F(0xf8)=-F(0xf8)*0.5;if(I(0x144)>29){if(B(0x113)<=20)RETIRE();B(0x113)-=20;}}
  }
  if(S(0x13e)==3){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);if(AT(R,signed char,0x184)<1){if(B(0x113)<20)RETIRE();B(0x113)-=20;}if(AT(R,short,0x140)>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 857:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){if(S(0x140)==0)MOVE();else F(0xf8)-=0.5;H[1]+=0.5;
   if(S(0x140)<2 && (I(0x180)==6 || I(0x180)==2 || I(0x180)==4 || I(0x180)==7)){set_sequence_frame(2);F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.1f))+5.0;}
   if(S(0x140)==2){F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  }
  if(S(0x13e)==1){if(S(0x140)==0)MOVE();else F(0xf8)-=0.5;H[1]+=0.5;
   if(S(0x140)<2){advance_six(0);if(I(0x180)==2 || I(0x180)==4 || I(0x180)==7){set_sequence_frame(2);F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.1f))+5.0;}}
   if(S(0x140)==2){F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  }
  if(S(0x13e)==2 || S(0x13e)==3){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);if(AT(R,short,0x140)!=0)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);}
  STEP();if(OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();FRAME_EXIT();
 case 858:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)==0){if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0)replace_secondary(994,4.0f,10,2,2);
   if(S(0x140)==0){
    if(C(0x104)*F(0xf4)>0 && F(0xec)>=sakuya_update_right && I(0x144)<151){float child[4]={0,0,2,0};spawn_unparented(858,1280.0f,F(0xf0),B(0x104),1,WORDS(child),4);P->dispatch_character_wave_handle(7);F(0xf4)=-F(0xf4);I(0x180)=0;B(0x184)=1;F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    if(C(0x104)*F(0xf4)<0 && F(0xec)<=sakuya_update_left && I(0x144)<151){float child[4]={0,0,2,0};spawn_unparented(858,0,F(0xf0),B(0x104),1,WORDS(child),4);P->dispatch_character_wave_handle(7);F(0xf4)=-F(0xf4);I(0x180)=0;B(0x184)=1;F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    if(F(0xf8)>0 && F(0xf0)>=sakuya_update_top && I(0x144)<151){float child[4]={0,0,2,0};spawn_unparented(858,F(0xec),F(0xf0),B(0x104),1,WORDS(child),4);P->dispatch_character_wave_handle(7);F(0xf8)=-F(0xf8);I(0x180)=0;B(0x184)=1;F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    if(F(0xf8)<0 && F(0xf0)<=0 && I(0x144)<151){float child[4]={0,0,2,0};spawn_unparented(858,F(0xec),F(0xf0),B(0x104),1,WORDS(child),4);P->dispatch_character_wave_handle(7);F(0xf8)=-F(0xf8);I(0x180)=0;B(0x184)=1;++S(0x364);F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    if(OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();
   }
   if(S(0x140)==1){F(0x12c)+=30.0;F(0xf8)-=0.5;if(F(0xf0)+F(0xf8)<=0 && F(0xf8)<0)F(0xf8)=-F(0xf8)*0.5;if(I(0x144)>29){if(B(0x113)<=20)RETIRE();B(0x113)-=20;}}
  }
  if(S(0x13e)==1){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);if(AT(R,short,0x140)>0)RETIRE();}
  if(S(0x13e)==2){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)-D(0.01f));if(B(0x113)<=20)RETIRE();B(0x113)-=20;}
  if(S(0x13e)==3){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)+D(0.1f));if(B(0x113)<=30)RETIRE();B(0x113)-=30;}
  STEP();FRAME_EXIT();
 case 859:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)){
  case 0:{
   F(0x12c)+=1.0;
   if(S(0x364)==0){F(0x11c)+=D(0.05f);if(!(F(0x11c)<1)){F(0x11c)=1;F(0x120)=1;S(0x364)=1;}F(0x120)=F(0x11c);}
   if(S(0x364)==1){++S(0x366);if(S(0x366)>299)S(0x364)=2;float radius=static_cast<float>(F(0x11c)*90.0);double y_square=square_float_value(static_cast<float>(AT(A,float,0xf0)+100.0-F(0xf0)));if(sqrt_float_value(static_cast<float>(square_float_value(AT(A,float,0xec)-F(0xec))+y_square))<radius)AT(A,short,0x186)=2;}
   if(S(0x364)==2){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)-D(0.025f));if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
   MOVE();H[1]*=D(0.9f);if(H[1]<1)H[1]=1;STEP();if(OUTSIDE(1480.0f,-200.0,1000.0,-260.0f))RETIRE();break;
  }
  case 1:F(0x12c)-=2.0;if(!R)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x11c)=AT(R,float,0x11c);F(0x120)=AT(R,float,0x120);B(0x113)=AT(R,unsigned char,0x113);break;
  case 2:F(0x12c)+=6.0;if(!R)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x11c)=AT(R,float,0x11c);F(0x120)=AT(R,float,0x120);B(0x113)=AT(R,unsigned char,0x113);break;
  case 3:F(0x12c)+=1.0;if(!R)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x11c)=AT(R,float,0x11c);F(0x120)=AT(R,float,0x120);B(0x113)=AT(R,unsigned char,0x113);break;
  case 4:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;if(I(0x144)<4)F(0x120)+=0.5;else F(0x120)*=D(0.9f);
   if(I(0x144)>4){if(B(0x111)<10){B(0x111)=0;B(0x110)=0;if(B(0x113)<10)RETIRE();B(0x113)-=10;}else{B(0x111)-=10;B(0x110)-=10;}}break;
  case 5:case 6:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;F(0x120)=F(0x11c);F(0x12c)+=H[1];H[1]*=D(0.95f);
   if(I(0x144)>4){if(B(0x111)<10){B(0x111)=0;B(0x110)=0;if(B(0x113)<10)RETIRE();B(0x113)-=10;}else{B(0x111)-=10;B(0x110)-=10;}}break;
  }
  FRAME_EXIT();
 case 900:
  if(I(0x180)==5 || OUTSIDE(1680.0,-400.0,1000.0,-160.0f))RETIRE();
  if(S(0x13e)<3){
   if(S(0x140)==0){advance_six(3);
    if(AT(P,short,0x174)<1 || CONTACT24768){next_sequence_frame();P->dispatch_character_wave_handle(3);I(0x144)=0;F(0xf4)=-F(0xf4)*0.5;F(0xf8)=static_cast<float>(random_float(40)*D(0.1f))+6.0;return;}
    if(C(0x184)<1){F(0x374)-=20.0;B(0x113)=static_cast<unsigned char>(F(0x374));if(F(0x374)<0)RETIRE();}
    else if(S(0x13e)==0 || (S(0x13e)==1 && (g_match_identifier==3 || g_match_identifier==2))){
     if(C(0x104)*F(0xf4)>0 && F(0xec)>=sakuya_update_right){F(0xf4)=-F(0xf4);if(S(0x13e)==0){F(0xf4)*=0.5;F(0xf8)*=0.5;}P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(C(0x104)*F(0xf4)<0 && F(0xec)<=sakuya_update_left){F(0xf4)=-F(0xf4);if(S(0x13e)==0){F(0xf4)*=0.5;F(0xf8)*=0.5;}P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(F(0xf8)>0 && F(0xf0)>=sakuya_update_top){F(0xf8)=-F(0xf8);if(S(0x13e)==0){F(0xf4)*=0.5;F(0xf8)*=0.5;}P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
     if(F(0xf8)<0 && F(0xf0)<=0){F(0xf8)=-F(0xf8);if(S(0x13e)==0){F(0xf4)*=0.5;F(0xf8)*=0.5;}P->dispatch_character_wave_handle(3);I(0x180)=0;next_sequence_block();F(0x12c)=-atan2_degrees(F(0xf8),F(0xf4));}
    }
   }
   if(S(0x140)==1){F(0x12c)+=30.0;F(0xf8)-=0.5;if(F(0xf0)+F(0xf8)<=0 && F(0xf8)<0)F(0xf8)=-F(0xf8)*0.5;if(I(0x144)>29){if(B(0x113)<=20)RETIRE();B(0x113)-=20;}}
  }
  if(S(0x13e)==3){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x12c)=AT(R,float,0x12c);if(AT(R,signed char,0x184)<1){if(B(0x113)<20)RETIRE();B(0x113)-=20;}if(AT(R,short,0x140)>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 901:
  if(I(0x180)==5)RETIRE();
  switch(S(0x13e)){
  case 0:{
   F(0x12c)+=1.0;
   if(S(0x364)==0){F(0x11c)+=D(0.05f);if(F(0x11c)>=1){F(0x11c)=1;F(0x120)=1;S(0x364)=1;}F(0x120)=F(0x11c);}
   if(S(0x364)==1){++S(0x366);if(S(0x366)>599 || S(0x368)>180)S(0x364)=2;float radius=static_cast<float>(F(0x11c)*90.0);double y_square=square_float_value(static_cast<float>(AT(A,float,0xf0)+100.0-F(0xf0)));if(sqrt_float_value(static_cast<float>(square_float_value(AT(A,float,0xec)-F(0xec))+y_square))<radius){++S(0x368);AT(A,short,0x186)=2;}}
   if(S(0x364)==2){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)-D(0.025f));if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
   MOVE();H[1]*=D(0.9f);if(H[1]<1.5f)H[1]=1.5f;STEP();if(OUTSIDE(1480.0f,-200.0,1000.0,-260.0f))RETIRE();break;
  }
  case 1:F(0x12c)-=2.0;if(!R)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x11c)=AT(R,float,0x11c);F(0x120)=AT(R,float,0x120);B(0x113)=AT(R,unsigned char,0x113);break;
  case 2:F(0x12c)+=6.0;if(!R)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x11c)=AT(R,float,0x11c);F(0x120)=AT(R,float,0x120);B(0x113)=AT(R,unsigned char,0x113);break;
  case 3:F(0x12c)+=1.0;if(!R)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);F(0x11c)=AT(R,float,0x11c);F(0x120)=AT(R,float,0x120);B(0x113)=AT(R,unsigned char,0x113);break;
  case 4:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;if(I(0x144)<4)F(0x120)+=0.5;else F(0x120)*=D(0.9f);
   if(I(0x144)>4){if(B(0x111)<10){B(0x111)=0;B(0x110)=0;if(B(0x113)<10)RETIRE();B(0x113)-=10;}else{B(0x111)-=10;B(0x110)-=10;}}break;
  case 5:case 6:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;F(0x120)=F(0x11c);F(0x12c)+=H[1];H[1]*=D(0.95f);
   if(I(0x144)>4){if(B(0x111)<10){B(0x111)=0;B(0x110)=0;if(B(0x113)<10)RETIRE();B(0x113)-=10;}else{B(0x111)-=10;B(0x110)-=10;}}break;
  case 7:
   if(S(0x140)<2){advance_six(10);if(AT(P,short,0x174)<1 || CONTACT2468){B(0x184)=0;set_sequence_frame(2);P->dispatch_character_wave_handle(3);I(0x144)=0;F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.1f))+5.0;return;}}
   if(S(0x140)==2){F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
   STEP();if(OUTSIDE(1480.0f,-200.0,1000.0,-260.0f))RETIRE();break;
  case 8:
   if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);if(AT(R,short,0x140)!=0)RETIRE();F(0xec)=AT(R,float,0xec);F(0xf0)=AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);break;
  }
  FRAME_EXIT();
 case 920:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)>=0 && S(0x13e)<3){
   if(S(0x140)<2){switch(g_match_identifier){case 0:advance_six(1);break;case 1:advance_six(10);break;case 2:case 3:advance_six(0);break;}
    if(AT(P,short,0x174)<1 || CONTACT2468){B(0x184)=0;P->dispatch_character_wave_handle(3);set_sequence_frame(2);release_secondary();F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.05f))+5.0;}
    if(S(0x13e)==0 || S(0x13e)==1){if(S(0x140)==0){if(AT(P,short,0x7a4)<1){MOTION->set_components(H[0],H[1]+F(0x374));F(0x374)*=D(0.85f);F(0x12c)=H[0];}
     else {F(0xf4)=0;F(0xf8)=0;if(AT(P,short,0x7a4)>30){F(0x12c)+=F(0x370);B(0x184)=0;}if(AT(P,short,0x7a4)==30){B(0x184)=1;I(0x180)=0;next_sequence_block();turn_heading(0,360.0f,100.0f);H[0]=(random_float(30)-15.0)+H[0];F(0x12c)=H[0];H[1]=static_cast<float>(random_float(30)*D(0.1f))+3.0;return;}}
    }else S(0x344)=0;}
    if(S(0x13e)==2){S(0x344)=0;MOVE();F(0x12c)=H[0];}
   }
   if(S(0x140)==2){S(0x344)=0;F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  }else if(S(0x13e)==3){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0x12c)=AT(R,float,0x12c);if(AT(R,short,0x140)>1)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);}
  STEP();if(F(0xec)>1780.0 || F(0xec)<-500.0 || F(0xf0)>1400.0f || !(F(0xf0)>=-560.0f))RETIRE();
  if(advance_frame())--I(0x330);if(S(0x142)==0 && S(0x140)==3)--I(0x330);return;
 case 930:
  if(I(0x180)==5)RETIRE();
  if(S(0x13e)>=0 && S(0x13e)<3){
   if(S(0x140)<2){if(S(0x13e)==0 || S(0x13e)==1)advance_six(0);else if(S(0x13e)==2)advance_six(1);
    if(AT(P,short,0x174)<1 || CONTACT2468){B(0x184)=0;P->dispatch_character_wave_handle(3);set_sequence_frame(2);release_secondary();F(0xf4)=-F(0xf4)*(0.5-random_float(30)*D(0.01f));F(0xf8)=static_cast<float>(random_float(30)*D(0.05f))+5.0;}
    if(S(0x13e)==0 || S(0x13e)==1){if(S(0x140)==0){if(AT(P,short,0x7a4)>0){B(0x184)=0;if(AT(P,short,0x7a4)==60){next_sequence_block();return;}if(AT(P,short,0x7a4)==1){B(0x184)=1;I(0x180)=0;}}}else S(0x344)=0;}
    if(S(0x13e)==2){S(0x344)=0;MOVE();F(0x12c)=H[0];}
   }
   if(S(0x140)==2){S(0x344)=0;F(0x12c)-=30.0;F(0xf8)-=0.5;if(B(0x113)<=10)RETIRE();B(0x113)-=10;}
  }else if(S(0x13e)==3){if(!R)RETIRE();B(0x104)=AT(R,unsigned char,0x104);F(0x12c)=AT(R,float,0x12c);if(AT(R,short,0x140)>1)RETIRE();F(0xec)=C(0x104)*AT(R,float,0xf4)+AT(R,float,0xec);F(0xf0)=AT(R,float,0xf8)+AT(R,float,0xf0);B(0x104)=AT(R,unsigned char,0x104);}
  if(AT(P,short,0x7a4)==0)STEP();
  if(!(F(0xec)<=1780.0 && F(0xec)>=-500.0 && F(0xf0)<=1400.0f && F(0xf0)>=-560.0f))RETIRE();
  if(advance_frame())--I(0x330);if(S(0x142)==0 && S(0x140)==3)--I(0x330);return;
 case 980:update_ping_pong_motion();FRAME_EXIT();
 case 998:
  if(S(0x13e)==0){if(AT(P,short,0x13c)>153 && AT(P,short,0x13c)<158){F(0xec)=C(0x104)*57+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+60.0;}if(AT(P,short,0x13c)>149 && AT(P,short,0x13c)<154){F(0xec)=C(0x104)*57+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+94.0;}if(AT(P,short,0x13c)==158){F(0xec)=C(0x104)*57+AT(P,float,0xec);F(0xf0)=AT(P,float,0xf0)+100.0;}if(AT(P,short,0x13c)<150 || AT(P,short,0x13c)>158){next_sequence_block();AT(P,unsigned char,0x751)=0;}}
  if(S(0x13e)==1){if(B(0x113)<10)RETIRE();B(0x113)-=10;}FRAME_EXIT();
 case 999:
  switch(S(0x13e)){
  case 0:case 1:case 2:AT(P,float,0xec)=F(0xec);if(F(0xec)>1480.0f || F(0xec)<-200.0)RETIRE();if(S(0x13e)>=1)F(0xf8)-=F(0x100);break;
  case 4:{F(0xf8)-=D(0.35f);float next_y=F(0xf0)+F(0xf8);if(next_y<=stage_surface_height()){AT(P,short,0x78c)=1;F(0xf0)=stage_surface_height();F(0xf4)=0;F(0xf8)=0;F(0x100)=0;select_sequence(5);return;}break;}
  case 6:if(AT(P,short,0x78e)==1){next_sequence_block();B(0x104)=1;return;}break;
  case 7:case 8:if(S(0x13e)>=8)F(0xf8)-=F(0x100);break;
  }
  STEP();if(advance_frame())--I(0x330);
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==1){F(0xf4)=15.0f;F(0xf8)=15.0f;F(0x100)=0.2f;}
  if(I(0x144)==0 && S(0x142)==0 && S(0x140)==0 && S(0x13e)==8){F(0xf4)=15.0f;F(0xf8)=15.0f;F(0x100)=0.2f;}return;
 default:advance_frame();return;
 }
}
#undef random_float
#undef AT
#undef F
#undef I
#undef S
#undef B
#undef C
#undef H
#undef P
#undef R
#undef A
#undef D
#undef MOTION
#undef MOVE
#undef STEP
#undef RETIRE
#undef FRAME_EXIT
#undef ORDERED_OUTSIDE
#undef OUTSIDE
#undef CONTACT2468
#undef CONTACT24768
#undef WORDS
#undef SPAWN
#undef PARENTED
}
