// Manual source hypothesis for JP1.06a SakuyaObject slot28, 4E0D30.
#include "SakuyaObjectUpdate.hpp"
#include "characters/CharacterObjectRuntime.hpp"
namespace th105 {
#define AT(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) AT(this,float,o)
#define I(o) AT(this,int,o)
#define S(o) AT(this,short,o)
#define B(o) AT(this,unsigned char,o)
#define C(o) AT(this,signed char,o)
#define A AT(this,SakuyaObjectUpdateView *,0x170)
#define D(x) static_cast<double>(x)
#define CORE reinterpret_cast<CharacterObjectRuntime *>(this)
#define MOTION reinterpret_cast<CharacterObjectRuntime *>(reinterpret_cast<unsigned char *>(this)+4)
#define MOVE() MOTION->set_oriented_components_f0_f4(parameters_340[0],parameters_340[1])
#define STEP() { x_ec+=C(0x104)*velocity_x_f4;y_f0+=velocity_y_f8; }
#define RETIRE() {--lifetime_330;return;}
#define FRAME_EXIT() {if(CORE->advance_frame_and_dispatch())--lifetime_330;return;}
#define OUTSIDE(xh,xl,yh,yl) (x_ec>xh || x_ec<xl || y_f0>yh || y_f0<yl)
#define CONTACT2468 (phase_state_180==2 || phase_state_180==4 || phase_state_180==6 || phase_state_180==8)
#define CONTACT24768 (phase_state_180==2 || phase_state_180==4 || phase_state_180==7 || phase_state_180==6 || phase_state_180==8)
#define WORDS(a) reinterpret_cast<const unsigned *>(a)
#define SPAWN(a,l,c) spawn_unparented(a,x_ec,y_f0,B(0x104),l,WORDS(payload),c)
#define PARENTED(a,l,c) spawn_parented(a,x_ec,y_f0,B(0x104),l,WORDS(payload),c)
#define random_float(limit) static_cast<float>(static_cast<unsigned>(selector_random_roll(limit)))
void SakuyaObjectUpdateView::update_action_state()
{
 switch(action_id_13c) {
 case 800:
  if(phase_state_180==5)RETIRE();
  if(sequence_id_13e<=2) {
   if(frame_index_140<2 && emit_repeated(0,0,2))RETIRE();
   if(frame_index_140==0)MOVE();else velocity_y_f8-=0.5;
   parameters_340[1]+=0.5;
   if(frame_index_140<2 && (phase_state_180==6 || phase_state_180==2 || phase_state_180==4 || phase_state_180==8)) {
    owner_348->dispatch_character_wave_handle(3);set_sequence_frame(2);
    velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.1f))+5.0;
   }
   if(frame_index_140==2) {F(0x12c)-=30.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
  }
  if(sequence_id_13e==3 || sequence_id_13e==7) {
   if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);if(parent_object_34c->frame_index_140!=0)RETIRE();
   x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);
  }
  if(sequence_id_13e>=4 && sequence_id_13e<=6) {
   if(frame_index_140<2 && emit_repeated(0,0,4))RETIRE();
   if(frame_counter_142==0 && frame_index_140==0)replace_secondary(994,4.0f,5,2,2);
   if(frame_index_140<2 && (phase_state_180==2 || phase_state_180==4 || phase_state_180==8)) {
    owner_348->dispatch_character_wave_handle(3);set_sequence_frame(2);release_secondary();
    velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.1f))+5.0;
   }
   if(frame_index_140==2) {F(0x12c)-=30.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
  }
  STEP();if(OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(frame_counter_142==0 && frame_index_140==2)--lifetime_330;return;
 case 801:
  if(phase_state_180==5)RETIRE();
  switch(sequence_id_13e){case 0:case 1:case 2: {
   if(frame_index_140<2 && emit_repeated(0,0,4))RETIRE();
   if(frame_counter_142==0 && frame_index_140==0)replace_secondary(994,4.0f,10,2,2);
   if(frame_index_140<2) {
    CORE->advance_state_six_counter_conditional(10);
    if(CONTACT2468) {B(0x184)=0;set_sequence_frame(2);owner_348->dispatch_character_wave_handle(3);time_counter_144=0;release_secondary();velocity_x_f4=-velocity_x_f4*0.5;velocity_y_f8=static_cast<float>(random_float(30)*D(0.1f))+5.0;return;}
   }
   if(frame_index_140==2) {F(0x12c)-=30.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
  } break; case 3: {
   if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);if(parent_object_34c->frame_index_140!=0)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);
  }
  break;}
  STEP();if(OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(frame_counter_142==0 && frame_index_140==2)--lifetime_330;return;
 case 802:
  if(phase_state_180==5)RETIRE();
  switch(sequence_id_13e){case 0:case 1:case 2: {
   if(frame_counter_142==0 && frame_index_140==0)replace_secondary(994,4.0f,10,2,2);
   if(frame_index_140<=2 && emit_repeated(0,2,5))RETIRE();
   if(frame_index_140<=2) {
    CORE->advance_state_six_counter_conditional(5);
    if(CONTACT2468) {B(0x184)=0;set_sequence_frame(4);owner_348->dispatch_character_wave_handle(3);release_secondary();velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.05f))+5.0;}
    if(frame_index_140==0 || frame_index_140==2)MOVE();
    if(frame_index_140==1)MOTION->set_oriented_components_f0_f4(parameters_340[0],static_cast<float>(parameters_340[1]*D(0.05f)));
   }
   if(frame_index_140==4) {F(0x12c)-=30.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
  } break; case 3: {
   if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);if(parent_object_34c->frame_index_140!=2)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);
  }
  break;}
  STEP();if(OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(frame_counter_142==0 && frame_index_140==3)--lifetime_330;
  if(sequence_id_13e<=2 && frame_counter_142==0 && frame_index_140==2) {replace_secondary(994,4.0f,10,2,2);float payload[3]={parameters_340[0],0,3};PARENTED(802,-1,3);}return;
 case 803:
  if(phase_state_180==5)RETIRE();
  // VC8 shares the frame-index-1 update while retaining both alpha calls.
  switch(sequence_id_13e) {
  case 0:case 1:
   if(frame_index_140==0 && emit_repeated(0,0,3))RETIRE();
   if(frame_counter_142==0 && frame_index_140==0)replace_secondary(994,4.0f,10,2,2);
   if(frame_index_140==0) {
    if(CONTACT24768) {release_secondary();set_sequence_frame(1);owner_348->dispatch_character_wave_handle(3);time_counter_144=0;velocity_x_f4=-velocity_x_f4;velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);return;}
    if (C(0x184) <= 0) {
     float alpha = static_cast<float>(field_374 - 20.0);
     field_374 = alpha;
     alpha_113 = static_cast<unsigned char>(alpha);
     if (field_374 < 0) RETIRE();
     set_secondary_alpha(static_cast<unsigned char>(field_374));
    }
    else if(sequence_id_13e==0 && velocity_y_f8<0 && y_f0<=stage_surface_height()) {owner_348->dispatch_character_wave_handle(3);velocity_y_f8=-velocity_y_f8;phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
   }
   if (frame_index_140 == 1) {
    F(0x12c) += 30.0;
    velocity_y_f8 -= 0.5;
    if (y_f0 + velocity_y_f8 <= 0 && velocity_y_f8 < 0)
     velocity_y_f8 = -velocity_y_f8 * 0.5;
    if (time_counter_144 >= 30) {
     if (alpha_113 <= 20) RETIRE();
     alpha_113 -= 20;
    }
   }
   goto step803;
  case 2:
   if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);
   if(!(parent_object_34c->frame_index_140<=0 && AT(parent_object_34c,signed char,0x184)>0)) {if(alpha_113<20)RETIRE();alpha_113-=20;}
   goto step803;
  case 3:case 4:
   if(frame_index_140==0 && emit_repeated(0,0,3))RETIRE();
   if(frame_counter_142==0 && frame_index_140==0)replace_secondary(994,4.0f,10,2,2);
   if(frame_index_140==0) {
    if(CONTACT24768) {release_secondary();next_sequence_frame();owner_348->dispatch_character_wave_handle(3);time_counter_144=0;velocity_x_f4=-velocity_x_f4;velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);return;}
    if (C(0x184) <= 0) {
     float alpha = static_cast<float>(field_374 - 20.0);
     field_374 = alpha;
     alpha_113 = static_cast<unsigned char>(alpha);
     if (field_374 < 0) RETIRE();
     set_secondary_alpha(static_cast<unsigned char>(field_374));
    }
    else if(sequence_id_13e==3) {
     if(C(0x104)*velocity_x_f4>0 && x_ec>=sakuya_update_right) {owner_348->dispatch_character_wave_handle(3);velocity_x_f4=-velocity_x_f4;phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(C(0x104)*velocity_x_f4<0 && x_ec<=sakuya_update_left) {owner_348->dispatch_character_wave_handle(3);velocity_x_f4=-velocity_x_f4;phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    }
   }
   if (frame_index_140 == 1) {
    F(0x12c) += 30.0;
    velocity_y_f8 -= 0.5;
    if (y_f0 + velocity_y_f8 <= 0 && velocity_y_f8 < 0)
     velocity_y_f8 = -velocity_y_f8 * 0.5;
    if (time_counter_144 >= 30) {
     if (alpha_113 <= 20) RETIRE();
     alpha_113 -= 20;
    }
   }
   goto step803;
  default:goto step803;
  }
 step803:STEP();FRAME_EXIT();
 case 804:
  if(phase_state_180==5 || (AT(owner_348,short,0x13c)>49 && AT(owner_348,short,0x13c)<150 && sequence_id_13e==0))RETIRE();
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==0){B(0x184)=1;S(0x364)=0;}
  if(sequence_id_13e==0) {
   if(frame_index_140==0){F(0x12c)-=30.0;parameters_340[1]-=2.5;if(parameters_340[1]<0)parameters_340[1]=0;}
   if(frame_index_140==1){if(frame_counter_142==0){replace_secondary(994,6.0f,20,1,2);turn_heading(0,180.0f,100.0f);}parameters_340[1]+=2.5;F(0x12c)=parameters_340[0];MOVE();if(phase_state_180==6){++B(0x184);phase_state_180=0;}if(phase_state_180!=0){if(C(0x184)<=0){next_sequence_block();F(0x120)=F(0x11c)=2.0f;}else phase_state_180=0;}}
   MOVE();STEP();if(frame_index_140==1){float payload[3]={parameters_340[0],0,2};owner_348->spawn_owned(804,x_ec,y_f0,B(0x104),-1,WORDS(payload),3);}
  }
  if(sequence_id_13e==1){F(0x11c)+=D(0.1f);F(0x120)*=D(0.65f);MOVE();STEP();}
  if(OUTSIDE(1680.0,-400.0,960.0,-120.0))RETIRE();
  if(CORE->advance_frame_and_dispatch())--lifetime_330;
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==1)--lifetime_330;
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==2)--lifetime_330;return;
 case 805:
  if(phase_state_180==5 || (AT(owner_348,short,0x13c)>49 && AT(owner_348,short,0x13c)<150 && frame_index_140<2))RETIRE();
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==0){B(0x184)=1;S(0x364)=25;S(0x366)=0;}
  if(sequence_id_13e==0){S(0x366)+=S(0x364);S(0x364)-=5;if(S(0x364)<0)S(0x364)=0;
   SakuyaObjectUpdateView *owner=owner_348;
   double cosine=lookup_orientation_cosine_quantized_abs(parameters_340[0]);
   x_ec=cosine*S(0x366)*C(0x104)+AT(owner,float,0xec);
   double owner_y=AT(owner,float,0xf0);
   y_f0=owner_y-lookup_orientation_sine_quantized_abs(parameters_340[0])*S(0x366)+130.0;
   if(AT(owner_348,short,0x13c)==540 && AT(owner_348,short,0x13e)==2){next_sequence_block();replace_secondary(994,6.0f,10,1,2);}
   if(AT(owner_348,short,0x13c)!=540)select_sequence(2);
   float payload[3]={parameters_340[0],0,3};owner_348->spawn_owned(805,x_ec,y_f0,B(0x104),-1,WORDS(payload),3);
  }
  if(sequence_id_13e==1){MOVE();parameters_340[1]+=1.0;STEP();float payload[3]={parameters_340[0],0,3};owner_348->spawn_owned(805,x_ec,y_f0,B(0x104),-1,WORDS(payload),3);if(phase_state_180==6){++B(0x184);phase_state_180=0;}if(phase_state_180!=0){if(C(0x184)<=0)next_sequence_block();else phase_state_180=0;}}
  if(sequence_id_13e==2){release_secondary();if(alpha_113<11)RETIRE();alpha_113-=10;}
  if(OUTSIDE(1380.0f,-100.0,960.0,-120.0))RETIRE();
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==3)--lifetime_330;return;
 case 810:
  if(sequence_id_13e<2) {
   if(AT(owner_348,short,0x13c)<=499 || AT(owner_348,short,0x13c)>=504 || sequence_id_13e>=3){if(alpha_113<=20)RETIRE();alpha_113-=20;}
   else {x_ec=C(0x104)*AT(owner_348,float,0xf4)+AT(owner_348,float,0xec);y_f0=AT(owner_348,float,0xf8)+AT(owner_348,float,0xf0);}
   F(0x12c)+=10.0;
  }
#define ORBIT810() { \
 parameters_340[0]+=10.0;if(parameters_340[0]>360.0f)parameters_340[0]-=360.0; \
 double facing=C(0x104);SakuyaObjectUpdateView *owner=owner_348; \
 double cosine=lookup_orientation_cosine_quantized_abs(parameters_340[0]);SakuyaObjectUpdateView *vertical_owner=owner_348; \
 x_ec=facing*AT(owner,float,0xf4)+AT(owner,float,0xec)+cosine*F(0x370)*facing; \
 double sine=lookup_orientation_sine_quantized_abs(parameters_340[0]); \
 y_f0=AT(vertical_owner,float,0xf0)+125.0+AT(vertical_owner,float,0xf8)+sine*F(0x370)*0.25; \
 if(!(parameters_340[0]>=0) || parameters_340[0]>180.0f)B(0x33c)=1;else B(0x33c)=255; \
}
  if(sequence_id_13e==2){F(0x12c)-=40.0;F(0x370)+=15.0;if(F(0x370)>parameters_340[1])F(0x370)=parameters_340[1];
   if(AT(owner_348,short,0x13c)<=499 || AT(owner_348,short,0x13c)>=504 || AT(owner_348,short,0x13e)>=3){ORBIT810();if(alpha_113<=20)RETIRE();alpha_113-=20;}else {ORBIT810();}
  }
  if(sequence_id_13e==3){F(0x12c)-=20.0;F(0x370)+=15.0;if(F(0x370)>parameters_340[1])F(0x370)=parameters_340[1];
   if(AT(owner_348,short,0x13c)<=499 || AT(owner_348,short,0x13c)>=504 || AT(owner_348,short,0x13e)>=3){ORBIT810();if(alpha_113<=20)RETIRE();alpha_113-=20;}else {ORBIT810();}
  }
#undef ORBIT810
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==1)--lifetime_330;return;
 case 811:
  if(phase_state_180==5 || OUTSIDE(1680.0,-400.0,1000.0,-160.0f))RETIRE();
  if(sequence_id_13e<=2 && frame_index_140<2 && emit_repeated(0,0,3))RETIRE();
  if(sequence_id_13e==0 || sequence_id_13e==1 || sequence_id_13e==2) {
   if(frame_index_140==0) {
    if(CONTACT24768){next_sequence_frame();owner_348->dispatch_character_wave_handle(3);time_counter_144=0;velocity_x_f4=-velocity_x_f4*0.5;velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);return;}
    if(C(0x184)<=0){field_374-=20.0;alpha_113=static_cast<unsigned char>(field_374);if(field_374<0)RETIRE();}
    else if(sequence_id_13e<2) {
     if(C(0x104)*velocity_x_f4>0 && x_ec>=sakuya_update_right){velocity_x_f4=-velocity_x_f4;owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(C(0x104)*velocity_x_f4<0 && x_ec<=sakuya_update_left){velocity_x_f4=-velocity_x_f4;owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(velocity_y_f8>0 && y_f0>=sakuya_update_top){velocity_y_f8=-velocity_y_f8;owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    }
   }
   if(frame_index_140==1){F(0x12c)+=30.0;velocity_y_f8-=0.5;if(y_f0+velocity_y_f8<=0 && velocity_y_f8<0)velocity_y_f8=-velocity_y_f8*0.5;if(time_counter_144>=30){if(alpha_113<=20)RETIRE();alpha_113-=20;}}
  }
  if(sequence_id_13e==3){if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);if(AT(parent_object_34c,signed char,0x184)<=0){if(alpha_113<20)RETIRE();alpha_113-=20;}if(parent_object_34c->frame_index_140>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 812:
  if(phase_state_180==5)RETIRE();
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==0)replace_secondary(994,6.0f,30,2,2);
  if(sequence_id_13e==0){if(frame_index_140==0){if(emit_repeated(0,2,2))RETIRE();MOVE();CORE->advance_state_six_counter_conditional(10);if(phase_state_180==2 || phase_state_180==4 || phase_state_180==7 || phase_state_180==8){release_secondary();next_sequence_frame();owner_348->dispatch_character_wave_handle(3);time_counter_144=0;velocity_x_f4=-velocity_x_f4*0.25;velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);return;}}
   else{velocity_y_f8-=D(0.35f);F(0x12c)-=30.0;if(alpha_113<11)RETIRE();alpha_113-=10;}}
  if(sequence_id_13e==1){if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);if(parent_object_34c->frame_index_140>0)RETIRE();}
  STEP();if(OUTSIDE(1680.0,-400.0,1000.0,-160.0f))RETIRE();
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==1)--lifetime_330;return;
 case 813:
  if(sequence_id_13e<=5){velocity_y_f8-=D(0.1f);y_f0+=velocity_y_f8;x_ec+=C(0x104)*velocity_x_f4;
   if(S(0x364)<=4)F(0x12c)+=S(0x36a);if(S(0x364)>=5)F(0x12c)-=S(0x36a);
   if(S(0x366)<=4)F(0x124)+=S(0x36c);if(S(0x366)>=5)F(0x124)-=S(0x36c);
   if(S(0x368)<=4)F(0x128)+=S(0x36c);if(S(0x368)>=5)F(0x128)-=S(0x36c);
   if(alpha_113<=8)RETIRE();alpha_113-=8;
  }
  if(sequence_id_13e==6 || sequence_id_13e==7){velocity_x_f4*=D(0.9f);y_f0+=velocity_y_f8;x_ec+=C(0x104)*velocity_x_f4;if(frame_index_140>0){if(alpha_113<11)RETIRE();alpha_113-=10;}}
  if(sequence_id_13e==8){F(0x370)-=D(0.2f);if(F(0x370)<0.001f)F(0x370)=0.01f;F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)+F(0x370));if(time_counter_144>=5){if(alpha_113<11)RETIRE();alpha_113-=10;}}
  if(sequence_id_13e==9 || sequence_id_13e==10){velocity_x_f4*=D(0.9f);y_f0+=velocity_y_f8;x_ec+=C(0x104)*velocity_x_f4;if(alpha_113<=20)RETIRE();alpha_113-=20;}
  FRAME_EXIT();
 case 815:
  switch(sequence_id_13e) {
  case 0:
   if(emit_repeated(0,1,2))RETIRE();F(0x12c)+=20.0;
   if(frame_index_140<2){F(0x370)+=parameters_340[1];parameters_340[1]-=0.5;if(parameters_340[1]<=D(0.1f))parameters_340[1]=0.1f;field_374+=C(0x104)*6;
    x_ec=S(0x364)+lookup_orientation_cosine_quantized_abs(field_374+parameters_340[0])*F(0x370);
    y_f0=S(0x366)+lookup_orientation_sine_quantized_abs(parameters_340[0]+field_374)*F(0x370);
    if(frame_index_140==1){if(frame_counter_142==0){float child[3]={0,0,1};spawn_parented(815,x_ec,y_f0,B(0x104),1,WORDS(child),3);child[1]=-15;child[2]=4;spawn_unparented(815,x_ec,y_f0,B(0x104),1,WORDS(child),3);}
     if(CONTACT24768){set_sequence_frame(3);owner_348->dispatch_character_wave_handle(3);time_counter_144=0;velocity_x_f4=static_cast<float>(static_cast<unsigned>(selector_random_roll(16)-8));velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);return;}
     if(C(0x184)<=0){set_sequence_frame(2);return;}
    }
   }
   if(frame_index_140==2 || frame_index_140==3){if(frame_counter_142==0 && frame_index_140==2){velocity_x_f4=static_cast<float>(static_cast<unsigned>(selector_random_roll(16)-8));velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);}velocity_y_f8-=D(0.35f);F(0x12c)+=10.0;STEP();if(alpha_113<11)RETIRE();alpha_113-=10;}break;
  case 1:
   F(0x12c)-=20.0;F(0x370)+=15.0;if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;if(parent_object_34c->frame_index_140!=1)RETIRE();break;
  case 2:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;
   if(time_counter_144<=3)F(0x120)+=0.5;else F(0x120)*=D(0.9f);
   goto fade_815_channels;
  case 3:case 4:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;F(0x120)=F(0x11c);F(0x12c)+=parameters_340[1];parameters_340[1]*=D(0.95f);
 fade_815_channels:
   if (time_counter_144 >= 5) {
    if (channel_111 >= 10) {
     channel_111 -= 10;
     channel_110 -= 10;
    } else {
     channel_111 = 0;
     channel_110 = 0;
     if (alpha_113 < 10) RETIRE();
     alpha_113 -= 10;
    }
   }
   break;
  }
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==1)--lifetime_330;return;
 case 816:
  if(phase_state_180==5 || (sequence_id_13e<=2 && frame_index_140<2 && emit_repeated(1,3,5)))RETIRE();
  if(sequence_id_13e==0 || sequence_id_13e==1 || sequence_id_13e==2){
   if(frame_counter_142==0 && frame_index_140==0)replace_secondary(994,6.0f,40,2,2);
   if(frame_index_140==0){if(CORE->advance_state_six_counter_conditional(15))B(0x184)=0;
    if (AT(owner_348, signed char, 0x609) <= 1 && phase_state_180 != 0) B(0x184) = 0;
    if(CONTACT24768 && C(0x184)<=0){next_sequence_frame();owner_348->dispatch_character_wave_handle(3);release_secondary();time_counter_144=0;velocity_x_f4=-velocity_x_f4;velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);return;}
    if(C(0x184)<=0 || OUTSIDE(1380.0f,-100.0,900.0,-200.0)){field_374-=20.0;alpha_113=static_cast<unsigned char>(field_374);if(field_374<0)RETIRE();set_secondary_alpha(static_cast<unsigned char>(field_374));}
    else if(sequence_id_13e<=2 && C(0x184)>1){
     if(C(0x104)*velocity_x_f4>0 && x_ec>=sakuya_update_right){owner_348->dispatch_character_wave_handle(3);velocity_x_f4=-velocity_x_f4;if(phase_state_180==0)--B(0x184);phase_state_180=0;F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(C(0x104)*velocity_x_f4<0 && x_ec<=sakuya_update_left){owner_348->dispatch_character_wave_handle(3);velocity_x_f4=-velocity_x_f4;if(phase_state_180==0)--B(0x184);phase_state_180=0;F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(velocity_y_f8>0 && y_f0>=sakuya_update_top){owner_348->dispatch_character_wave_handle(3);velocity_y_f8=-velocity_y_f8;if(phase_state_180==0)--B(0x184);phase_state_180=0;F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(velocity_y_f8<0 && y_f0<=sakuya_update_bottom){owner_348->dispatch_character_wave_handle(3);velocity_y_f8=-velocity_y_f8;if(phase_state_180==0)--B(0x184);phase_state_180=0;F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    }
   }
   if(frame_index_140==1){F(0x12c)+=30.0;velocity_y_f8-=0.5;if(y_f0+velocity_y_f8<=0 && velocity_y_f8<0)velocity_y_f8=-velocity_y_f8*0.5;if(time_counter_144>=30){if(alpha_113<=20)RETIRE();alpha_113-=20;}}
  }
  if(sequence_id_13e==3){if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);if(AT(parent_object_34c,signed char,0x184)<=0){if(alpha_113<20)RETIRE();alpha_113-=20;}if(parent_object_34c->frame_index_140>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 817:
  if(phase_state_180==5)RETIRE();
  switch(sequence_id_13e){case 0:case 1:case 2:{
   if(frame_index_140<2 && emit_repeated(0,2,5))RETIRE();
   if(frame_counter_142==0 && frame_index_140==2){replace_secondary(994,4.0f,10,2,2);float payload[3]={parameters_340[0],0,3};PARENTED(817,-1,3);}
   if(frame_index_140<=2){
    if(CONTACT2468){B(0x184)=0;owner_348->dispatch_character_wave_handle(3);set_sequence_frame(4);release_secondary();velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.05f))+5.0;}
    if(frame_index_140==0 || frame_index_140==2)MOVE();
    if(frame_index_140==1){velocity_x_f4=0;velocity_y_f8=0;
     if((AT(owner_348,short,0x13c)==545 && AT(owner_348,short,0x13e)==0 && AT(owner_348,short,0x140)==8) || (AT(owner_348,short,0x13c)==546 && AT(owner_348,short,0x13e)==0 && AT(owner_348,short,0x140)==8) || (AT(owner_348,short,0x13c)==547 && AT(owner_348,short,0x13e)==0 && AT(owner_348,short,0x140)==8) || (AT(owner_348,short,0x13c)==548 && AT(owner_348,short,0x13e)==0 && AT(owner_348,short,0x140)==8)){next_sequence_frame();return;}}
   }
   if(frame_index_140==4){F(0x12c)-=30.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
  }break; case 3:{if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);if(parent_object_34c->frame_index_140!=2)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);}
  break;}
  STEP();if(OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();if(CORE->advance_frame_and_dispatch())--lifetime_330;if(frame_counter_142==0 && frame_index_140==3)--lifetime_330;return;
 case 818:
  if(phase_state_180==5)RETIRE();
  switch(sequence_id_13e){case 0:{
   if(frame_index_140<2 && emit_repeated(0,0,3))RETIRE();
   if(frame_index_140==0)MOVE();
   if(frame_index_140==1){if(AT(owner_348,short,0x48c)<=0){next_sequence_frame();field_344=0;replace_secondary(994,4.0f,10,2,2);float payload[3]={parameters_340[0],0,1};PARENTED(818,-1,3);return;}MOTION->set_oriented_components_f0_f4(parameters_340[0],0);}
   if(frame_index_140==2){if(CONTACT2468){B(0x184)=0;set_sequence_frame(4);owner_348->dispatch_character_wave_handle(3);release_secondary();velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.05f))+5.0;return;}if(phase_state_180!=0){next_sequence_frame();release_secondary();return;}MOVE();}
   if(frame_index_140==3){velocity_x_f4=0;velocity_y_f8=0;if(time_counter_144>=20)RETIRE();}
   if(frame_index_140==4){F(0x12c)-=5.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
  }break; case 1:{if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);if(parent_object_34c->frame_index_140!=2)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);}
  break; case 2:{F(0x11c)-=D(0.15f);if(F(0x11c)<1)F(0x11c)=1;F(0x120)=F(0x11c);if(time_counter_144>=20)RETIRE();}
  break;}
  STEP();if(OUTSIDE(1580.0f,-300.0f,1200.0f,-300.0f))RETIRE();if(CORE->advance_frame_and_dispatch())RETIRE();
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==1)RETIRE();if(frame_counter_142==0 && frame_index_140==3)RETIRE();return;
 case 849:
  switch(sequence_id_13e){case 0:{x_ec=AT(owner_348,float,0xec);y_f0=AT(owner_348,float,0xf0);if(AT(owner_348,short,0x13c)!=308)RETIRE();}
  break; case 1:{x_ec=AT(owner_348,float,0xec);y_f0=AT(owner_348,float,0xf0);if(AT(owner_348,short,0x13c)!=304 && AT(owner_348,short,0x13c)!=309)RETIRE();}
  break; case 2:{MOVE();parameters_340[1]-=0.5;if(parameters_340[1]<0.5f)parameters_340[1]=0.5f;x_ec+=C(0x104)*velocity_x_f4;y_f0+=velocity_y_f8*0.25;F(0x12c)+=field_374;F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)+D(0.02f));if(time_counter_144>=0){if(alpha_113<=5)RETIRE();alpha_113-=5;}x_ec+=C(0x104)*velocity_x_f4;y_f0+=velocity_y_f8*0.25;}
  break;}
  if(AT(owner_348,short,0x186)!=0)return;if(CORE->advance_frame_and_dispatch())--lifetime_330;
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==1)--lifetime_330;
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==2)--lifetime_330;return;
 case 850:
  if(phase_state_180==5)RETIRE();
  if(sequence_id_13e==0){parameters_340[1]-=2.0;if(parameters_340[1]<1){parameters_340[1]=1;next_sequence_block();}MOVE();}
  if(sequence_id_13e==1){F(0x12c)+=40.0;MOVE();if(time_counter_144>=parameters_340[3]){next_sequence_block();float *words=parameters_340;words[0]=-atan2_degrees(static_cast<float>(AT(A,float,0xf0)+100.0-y_f0),static_cast<float>(C(0x104)*(AT(A,float,0xec)-x_ec)));F(0x12c)=words[0];float children[4]={words[0],0,4,0};spawn_parented(850,x_ec,y_f0,B(0x104),-1,WORDS(children),4);children[2]=5;spawn_parented(850,x_ec,y_f0,B(0x104),-1,WORDS(children),4);parameters_340[1]=35.0f;return;}}
  if(sequence_id_13e==2){parameters_340[1]+=D(0.2f);MOVE();if(OUTSIDE(1680.0,-400.0,1300.0f,-360.0f))RETIRE();}
  if(sequence_id_13e==4){if(!parent_object_34c)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);if(parent_object_34c->frame_index_140>0)RETIRE();}
  if(sequence_id_13e==5){if(!parent_object_34c)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);F(0x11c)+=D(0.1f);F(0x120)*=D(0.95f);if(parent_object_34c->frame_index_140>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 851:
  F(0x12c)+=0.25;if(AT(owner_348,short,0x7a6)<=0 || S(0x364)!=0)S(0x364)=1;else if(alpha_113<220)alpha_113+=25;else alpha_113=255;
  if(S(0x364)==1){if(alpha_113>10)alpha_113-=10;else RETIRE();}return;
 case 852:
  if(sequence_id_13e==0){F(0x11c)+=D(0.1f);F(0x120)+=D(0.02f);}
  if(sequence_id_13e==1 && ((AT(owner_348,short,0x13c)>49 && AT(owner_348,short,0x13c)<150) || AT(owner_348,short,0x13c)!=602 || time_counter_144>=15))RETIRE();
  STEP();FRAME_EXIT();
 case 853:
  if(phase_state_180==5)RETIRE();
  if(sequence_id_13e==0){F(0x12c)+=40.0;parameters_340[1]-=1.0;if(parameters_340[1]<0.5f)parameters_340[1]=0.5f;MOVE();if(time_counter_144>=parameters_340[3]){--lifetime_330;float children[4];children[1]=30;children[2]=1;children[3]=90;owner_348->dispatch_character_wave_handle(13);
    float count=0;do{children[0]=(parameters_340[0]+15.0)-count*15.0;spawn_unparented(853,x_ec,y_f0,B(0x104),1,WORDS(children),4);count+=1.0;}while(count<3.0f);
    children[2]=6;spawn_unparented(853,x_ec,y_f0,B(0x104),1,WORDS(children),4);children[2]=7;spawn_unparented(853,x_ec,y_f0,B(0x104),1,WORDS(children),4);}}
  if(sequence_id_13e==1){MOVE();if(time_counter_144>=parameters_340[3]){next_sequence_block();float *words=parameters_340;words[0]=-atan2_degrees(static_cast<float>(AT(A,float,0xf0)+100.0-y_f0),static_cast<float>(C(0x104)*(AT(A,float,0xec)-x_ec)));words[1]=80.0f;F(0x12c)=words[0];return;}}
  if(sequence_id_13e==2){MOVE();if(time_counter_144>=180)RETIRE();}
  if(sequence_id_13e==4){if(!parent_object_34c)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);if(parent_object_34c->frame_index_140>0)RETIRE();}
  if(sequence_id_13e==5){if(!parent_object_34c)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);F(0x11c)+=D(0.1f);F(0x120)*=D(0.95f);if(parent_object_34c->frame_index_140>0)RETIRE();}
  if(sequence_id_13e==6){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)-D(0.01f));if(alpha_113<=20)RETIRE();alpha_113-=20;channel_110-=20;channel_111-=20;}
  if(sequence_id_13e==7){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)+D(0.2f));if(alpha_113<=30)RETIRE();alpha_113-=30;channel_110-=30;channel_111-=30;}
  STEP();FRAME_EXIT();
 case 854:
  if (AT(owner_348, short, 0x7a4) <= 0 || S(0x364) != 0) {
   S(0x364) = 1;
  } else if (alpha_113 < 220) {
   alpha_113 += 25;
  } else {
   alpha_113 = 255;
  }
  if (S(0x364) == 1) {
   if (alpha_113 > 10) alpha_113 -= 10;
   else RETIRE();
  }
  return;
 case 855:
  if(sequence_id_13e==0){F(0x11c)+=0.5;F(0x120)+=D(0.02f);}
  if(sequence_id_13e==1){F(0x11c)+=0.5;F(0x120)*=D(0.98f);parameters_340[1]+=1.0;MOVE();if(time_counter_144>=120 || F(0x120)<=D(0.1f))RETIRE();}
  if(sequence_id_13e==2 && ((AT(owner_348,short,0x13c)>49 && AT(owner_348,short,0x13c)<150) || AT(owner_348,short,0x13c)!=605 || time_counter_144>=40))RETIRE();
  STEP();if(CORE->advance_frame_and_dispatch())--lifetime_330;if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==1)--lifetime_330;return;
 case 856:
  if(phase_state_180==5 || OUTSIDE(1680.0,-400.0,1000.0,-160.0f))RETIRE();
  if(sequence_id_13e<=2){
   if(frame_index_140==0){
    if(CONTACT24768){next_sequence_frame();owner_348->dispatch_character_wave_handle(3);time_counter_144=0;velocity_x_f4=-velocity_x_f4*0.5;velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);return;}
    if(C(0x184)<=0){field_374-=20.0;alpha_113=static_cast<unsigned char>(field_374);if(field_374<0)RETIRE();}
    else if(sequence_id_13e<=0){
     if(C(0x104)*velocity_x_f4>0 && x_ec>=sakuya_update_right){velocity_x_f4=-velocity_x_f4;owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(C(0x104)*velocity_x_f4<0 && x_ec<=sakuya_update_left){velocity_x_f4=-velocity_x_f4;owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(velocity_y_f8>0 && y_f0>=sakuya_update_top){velocity_y_f8=-velocity_y_f8;owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(velocity_y_f8<0 && y_f0<=0){velocity_y_f8=-velocity_y_f8;owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    }
   }
   if(frame_index_140==1){F(0x12c)+=30.0;velocity_y_f8-=0.5;if(y_f0+velocity_y_f8<=0 && velocity_y_f8<0)velocity_y_f8=-velocity_y_f8*0.5;if(time_counter_144>=30){if(alpha_113<=20)RETIRE();alpha_113-=20;}}
  }
  if(sequence_id_13e==3){if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);if(AT(parent_object_34c,signed char,0x184)<=0){if(alpha_113<20)RETIRE();alpha_113-=20;}if(parent_object_34c->frame_index_140>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 857:
  if(phase_state_180==5)RETIRE();
  if(sequence_id_13e==0){if(frame_index_140==0)MOVE();else velocity_y_f8-=0.5;parameters_340[1]+=0.5;
   if(frame_index_140<2 && (phase_state_180==6 || phase_state_180==2 || phase_state_180==4 || phase_state_180==7)){set_sequence_frame(2);velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.1f))+5.0;}
   if(frame_index_140==2){F(0x12c)-=30.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
  }
  if(sequence_id_13e==1){if(frame_index_140==0)MOVE();else velocity_y_f8-=0.5;parameters_340[1]+=0.5;
   if(frame_index_140<2){CORE->advance_state_six_counter_conditional(0);if(phase_state_180==2 || phase_state_180==4 || phase_state_180==7){set_sequence_frame(2);velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.1f))+5.0;}}
   if(frame_index_140==2){F(0x12c)-=30.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
  }
  if(sequence_id_13e==2 || sequence_id_13e==3){if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);if(parent_object_34c->frame_index_140!=0)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);}
  STEP();if(OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();FRAME_EXIT();
 case 858:
  if(phase_state_180==5)RETIRE();
  if(sequence_id_13e==0){if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0)replace_secondary(994,4.0f,10,2,2);
   if(frame_index_140==0){
    if(C(0x104)*velocity_x_f4>0 && x_ec>=sakuya_update_right && time_counter_144<=150){float child[4]={0,0,2,0};spawn_unparented(858,1280.0f,y_f0,B(0x104),1,WORDS(child),4);owner_348->dispatch_character_wave_handle(7);velocity_x_f4=-velocity_x_f4;phase_state_180=0;B(0x184)=1;F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    if(C(0x104)*velocity_x_f4<0 && x_ec<=sakuya_update_left && time_counter_144<=150){float child[4]={0,0,2,0};spawn_unparented(858,0,y_f0,B(0x104),1,WORDS(child),4);owner_348->dispatch_character_wave_handle(7);velocity_x_f4=-velocity_x_f4;phase_state_180=0;B(0x184)=1;F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    if(velocity_y_f8>0 && y_f0>=sakuya_update_top && time_counter_144<=150){float child[4]={0,0,2,0};spawn_unparented(858,x_ec,y_f0,B(0x104),1,WORDS(child),4);owner_348->dispatch_character_wave_handle(7);velocity_y_f8=-velocity_y_f8;phase_state_180=0;B(0x184)=1;F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    if(velocity_y_f8<0 && y_f0<=0 && time_counter_144<=150){float child[4]={0,0,2,0};spawn_unparented(858,x_ec,y_f0,B(0x104),1,WORDS(child),4);owner_348->dispatch_character_wave_handle(7);velocity_y_f8=-velocity_y_f8;phase_state_180=0;B(0x184)=1;++S(0x364);F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    if(OUTSIDE(1380.0f,-100.0,1000.0,-160.0f))RETIRE();
   }
   if(frame_index_140==1){F(0x12c)+=30.0;velocity_y_f8-=0.5;if(y_f0+velocity_y_f8<=0 && velocity_y_f8<0)velocity_y_f8=-velocity_y_f8*0.5;if(time_counter_144>=30){if(alpha_113<=20)RETIRE();alpha_113-=20;}}
  }
  if(sequence_id_13e==1){if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);if(parent_object_34c->frame_index_140>0)RETIRE();}
  if(sequence_id_13e==2){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)-D(0.01f));if(alpha_113<=20)RETIRE();alpha_113-=20;}
  if(sequence_id_13e==3){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)+D(0.1f));if(alpha_113<=30)RETIRE();alpha_113-=30;}
  STEP();FRAME_EXIT();
 case 859:
  if(phase_state_180==5)RETIRE();
  switch(sequence_id_13e){
  case 0:{
   F(0x12c)+=1.0;
   if(S(0x364)==0){F(0x11c)+=D(0.05f);if(F(0x11c)>=1.0f){F(0x11c)=1;F(0x120)=1;S(0x364)=1;}F(0x120)=F(0x11c);}
   if(S(0x364)==1){++S(0x366);if(S(0x366)>=300)S(0x364)=2;float radius=static_cast<float>(F(0x11c)*90.0);double y_square=square_float_value(static_cast<float>(AT(A,float,0xf0)+100.0-y_f0));if(sqrt_float_value(static_cast<float>(square_float_value(AT(A,float,0xec)-x_ec)+y_square))<radius)AT(A,short,0x186)=2;}
   if(S(0x364)==2){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)-D(0.025f));if(alpha_113<11)RETIRE();alpha_113-=10;}
   MOVE();parameters_340[1]*=D(0.9f);if(parameters_340[1]<1)parameters_340[1]=1;STEP();if(OUTSIDE(1480.0f,-200.0,1000.0,-260.0f))RETIRE();break;
  }
  case 1:F(0x12c)-=2.0;if(!parent_object_34c)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x11c)=AT(parent_object_34c,float,0x11c);F(0x120)=AT(parent_object_34c,float,0x120);alpha_113=parent_object_34c->alpha_113;break;
  case 2:F(0x12c)+=6.0;if(!parent_object_34c)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x11c)=AT(parent_object_34c,float,0x11c);F(0x120)=AT(parent_object_34c,float,0x120);alpha_113=parent_object_34c->alpha_113;break;
  case 3:F(0x12c)+=1.0;if(!parent_object_34c)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x11c)=AT(parent_object_34c,float,0x11c);F(0x120)=AT(parent_object_34c,float,0x120);alpha_113=parent_object_34c->alpha_113;break;
  case 4:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;if(time_counter_144<=3)F(0x120)+=0.5;else F(0x120)*=D(0.9f);
   if(time_counter_144>=5){if(channel_111<=9){channel_111=0;channel_110=0;if(alpha_113<=9)RETIRE();alpha_113-=10;}else{channel_111-=10;channel_110-=10;}}break;
  case 5:case 6:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;F(0x120)=F(0x11c);F(0x12c)+=parameters_340[1];parameters_340[1]*=D(0.95f);
   if(time_counter_144>=5){if(channel_111<=9){channel_111=0;channel_110=0;if(alpha_113<=9)RETIRE();alpha_113-=10;}else{channel_111-=10;channel_110-=10;}}break;
  }
  FRAME_EXIT();
 case 900:
  if(phase_state_180==5 || OUTSIDE(1680.0,-400.0,1000.0,-160.0f))RETIRE();
  if(sequence_id_13e<=2){
   if(frame_index_140==0){CORE->advance_state_six_counter_conditional(3);
    if(AT(owner_348,short,0x174)<=0 || CONTACT24768){next_sequence_frame();owner_348->dispatch_character_wave_handle(3);time_counter_144=0;velocity_x_f4=-velocity_x_f4*0.5;velocity_y_f8=static_cast<float>(random_float(40)*D(0.1f)+6.0);return;}
    if(C(0x184)<=0){field_374-=20.0;alpha_113=static_cast<unsigned char>(field_374);if(field_374<0)RETIRE();}
    else if(sequence_id_13e==0 || (sequence_id_13e==1 && (g_match_identifier==3 || g_match_identifier==2))){
     if(C(0x104)*velocity_x_f4>0 && x_ec>=sakuya_update_right){velocity_x_f4=-velocity_x_f4;if(sequence_id_13e==0){velocity_x_f4*=0.5;velocity_y_f8*=0.5;}owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(C(0x104)*velocity_x_f4<0 && x_ec<=sakuya_update_left){velocity_x_f4=-velocity_x_f4;if(sequence_id_13e==0){velocity_x_f4*=0.5;velocity_y_f8*=0.5;}owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(velocity_y_f8>0 && y_f0>=sakuya_update_top){velocity_y_f8=-velocity_y_f8;if(sequence_id_13e==0){velocity_x_f4*=0.5;velocity_y_f8*=0.5;}owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
     if(velocity_y_f8<0 && y_f0<=0){velocity_y_f8=-velocity_y_f8;if(sequence_id_13e==0){velocity_x_f4*=0.5;velocity_y_f8*=0.5;}owner_348->dispatch_character_wave_handle(3);phase_state_180=0;next_sequence_block();F(0x12c)=-atan2_degrees(velocity_y_f8,velocity_x_f4);}
    }
   }
   if(frame_index_140==1){F(0x12c)+=30.0;velocity_y_f8-=0.5;if(y_f0+velocity_y_f8<=0 && velocity_y_f8<0)velocity_y_f8=-velocity_y_f8*0.5;if(time_counter_144>=30){if(alpha_113<=20)RETIRE();alpha_113-=20;}}
  }
  if(sequence_id_13e==3){if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x12c)=AT(parent_object_34c,float,0x12c);if(AT(parent_object_34c,signed char,0x184)<=0){if(alpha_113<20)RETIRE();alpha_113-=20;}if(parent_object_34c->frame_index_140>0)RETIRE();}
  STEP();FRAME_EXIT();
 case 901:
  if(phase_state_180==5)RETIRE();
  switch(sequence_id_13e){
  case 0:{
   F(0x12c)+=1.0;
   if(S(0x364)==0){F(0x11c)+=D(0.05f);if(F(0x11c)>=1){F(0x11c)=1;F(0x120)=1;S(0x364)=1;}F(0x120)=F(0x11c);}
   if(S(0x364)==1){++S(0x366);if(S(0x366)>=600 || S(0x368)>180)S(0x364)=2;float radius=static_cast<float>(F(0x11c)*90.0);double y_square=square_float_value(static_cast<float>(AT(A,float,0xf0)+100.0-y_f0));if(sqrt_float_value(static_cast<float>(square_float_value(AT(A,float,0xec)-x_ec)+y_square))<radius){++S(0x368);AT(A,short,0x186)=2;}}
   if(S(0x364)==2){F(0x120)=F(0x11c)=static_cast<float>(F(0x11c)-D(0.025f));if(alpha_113<11)RETIRE();alpha_113-=10;}
   MOVE();parameters_340[1]*=D(0.9f);if(parameters_340[1]<1.5f)parameters_340[1]=1.5f;STEP();if(OUTSIDE(1480.0f,-200.0,1000.0,-260.0f))RETIRE();break;
  }
  case 1:F(0x12c)-=2.0;if(!parent_object_34c)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x11c)=AT(parent_object_34c,float,0x11c);F(0x120)=AT(parent_object_34c,float,0x120);alpha_113=parent_object_34c->alpha_113;break;
  case 2:F(0x12c)+=6.0;if(!parent_object_34c)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x11c)=AT(parent_object_34c,float,0x11c);F(0x120)=AT(parent_object_34c,float,0x120);alpha_113=parent_object_34c->alpha_113;break;
  case 3:F(0x12c)+=1.0;if(!parent_object_34c)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;F(0x11c)=AT(parent_object_34c,float,0x11c);F(0x120)=AT(parent_object_34c,float,0x120);alpha_113=parent_object_34c->alpha_113;break;
  case 4:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;if(time_counter_144<=3)F(0x120)+=0.5;else F(0x120)*=D(0.9f);
   if(time_counter_144>=5){if(channel_111<=9){channel_111=0;channel_110=0;if(alpha_113<=9)RETIRE();alpha_113-=10;}else{channel_111-=10;channel_110-=10;}}break;
  case 5:case 6:
   F(0x11c)+=F(0x370);F(0x370)-=D(0.1f);if(F(0x370)<=0.02f)F(0x370)=0.02f;F(0x120)=F(0x11c);F(0x12c)+=parameters_340[1];parameters_340[1]*=D(0.95f);
   if(time_counter_144>=5){if(channel_111<=9){channel_111=0;channel_110=0;if(alpha_113<=9)RETIRE();alpha_113-=10;}else{channel_111-=10;channel_110-=10;}}break;
  case 7:
   if(frame_index_140<2){CORE->advance_state_six_counter_conditional(10);if(AT(owner_348,short,0x174)<=0 || CONTACT2468){B(0x184)=0;set_sequence_frame(2);owner_348->dispatch_character_wave_handle(3);time_counter_144=0;velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.1f))+5.0;return;}}
   if(frame_index_140==2){F(0x12c)-=30.0;velocity_y_f8-=0.5;if(alpha_113<11)RETIRE();alpha_113-=10;}
   STEP();if(OUTSIDE(1480.0f,-200.0,1000.0,-260.0f))RETIRE();break;
  case 8:
   if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);if(parent_object_34c->frame_index_140!=0)RETIRE();x_ec=parent_object_34c->x_ec;y_f0=parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);break;
  }
  FRAME_EXIT();
 case 920:
  if(phase_state_180==5)RETIRE();
  switch(sequence_id_13e){case 0:case 1:case 2:{
   if (frame_index_140 < 2) {
    switch (g_match_identifier) {
    case 2:
    case 3:
     CORE->advance_state_six_counter_conditional(0);
     break;
    case 1:
     CORE->advance_state_six_counter_conditional(10);
     break;
    case 0:
     CORE->advance_state_six_counter_conditional(1);
     break;
    }
    if(AT(owner_348,short,0x174)<=0 || CONTACT2468){B(0x184)=0;owner_348->dispatch_character_wave_handle(3);set_sequence_frame(2);release_secondary();velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.05f))+5.0;}
    if (sequence_id_13e == 0 || sequence_id_13e == 1) {
     if (frame_index_140 == 0) {
      if (AT(owner_348, short, 0x7a4) > 0) {
       velocity_x_f4 = 0;
       velocity_y_f8 = 0;
       if (AT(owner_348, short, 0x7a4) > 30) {
        F(0x12c) += F(0x370);
        B(0x184) = 0;
       }
       if (AT(owner_348, short, 0x7a4) == 30) {
        B(0x184) = 1;
        phase_state_180 = 0;
        next_sequence_block();
        turn_heading(0, 360.0f, 100.0f);
        parameters_340[0] = (random_float(30) - 15.0) + parameters_340[0];
        F(0x12c) = parameters_340[0];
        parameters_340[1] = static_cast<float>(random_float(30) * D(0.1f) + 3.0);
        return;
       }
      } else {
       MOTION->set_oriented_components_f0_f4(parameters_340[0], parameters_340[1] + field_374);
       field_374 *= D(0.85f);
       F(0x12c) = parameters_340[0];
      }
     } else {
      field_344 = 0;
     }
    }
    if(sequence_id_13e==2){field_344=0;MOVE();F(0x12c)=parameters_340[0];}
   }
   if (frame_index_140 == 2) {
    field_344 = 0;
    F(0x12c) -= 30.0;
    velocity_y_f8 -= 0.5;
    if (alpha_113 <= 10) RETIRE();
    alpha_113 -= 10;
   }
  }break; case 3:{if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);F(0x12c)=AT(parent_object_34c,float,0x12c);if(parent_object_34c->frame_index_140>1)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);}
  break;}
  STEP();if(x_ec>1780.0 || x_ec<-500.0 || y_f0>1400.0f || y_f0<-560.0f)RETIRE();
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(frame_counter_142==0 && frame_index_140==3)--lifetime_330;return;
 case 930:
  if(phase_state_180==5)RETIRE();
  switch(sequence_id_13e){case 0:case 1:case 2:{
   if (frame_index_140 < 2) {
    switch (sequence_id_13e) {
    case 0:
     CORE->advance_state_six_counter_conditional(0);
     break;
    case 1:
     CORE->advance_state_six_counter_conditional(0);
     break;
    case 2:
     CORE->advance_state_six_counter_conditional(1);
     break;
    }
    if(AT(owner_348,short,0x174)<=0 || CONTACT2468){B(0x184)=0;owner_348->dispatch_character_wave_handle(3);set_sequence_frame(2);release_secondary();velocity_x_f4=-velocity_x_f4*(0.5-random_float(30)*D(0.01f));velocity_y_f8=static_cast<float>(random_float(30)*D(0.05f))+5.0;}
    if(sequence_id_13e==0 || sequence_id_13e==1){if(frame_index_140==0){if(AT(owner_348,short,0x7a4)>0){B(0x184)=0;if(AT(owner_348,short,0x7a4)==60){next_sequence_block();return;}if(AT(owner_348,short,0x7a4)==1){B(0x184)=1;phase_state_180=0;}}}else field_344=0;}
    if(sequence_id_13e==2){field_344=0;MOVE();F(0x12c)=parameters_340[0];}
   }
   if (frame_index_140 == 2) {
    field_344 = 0;
    F(0x12c) -= 30.0;
    velocity_y_f8 -= 0.5;
    if (alpha_113 <= 10) RETIRE();
    alpha_113 -= 10;
   }
  }break; case 3:{if(!parent_object_34c)RETIRE();B(0x104)=AT(parent_object_34c,unsigned char,0x104);F(0x12c)=AT(parent_object_34c,float,0x12c);if(parent_object_34c->frame_index_140>1)RETIRE();x_ec=C(0x104)*parent_object_34c->velocity_x_f4+parent_object_34c->x_ec;y_f0=parent_object_34c->velocity_y_f8+parent_object_34c->y_f0;B(0x104)=AT(parent_object_34c,unsigned char,0x104);}
  break;}
  if(AT(owner_348,short,0x7a4)==0)STEP();
  if((x_ec>1780.0 || x_ec<-500.0 || y_f0>1400.0f || y_f0<-560.0f))RETIRE();
  if(CORE->advance_frame_and_dispatch())--lifetime_330;if(frame_counter_142==0 && frame_index_140==3)--lifetime_330;return;
 case 980:update_ping_pong_motion();FRAME_EXIT();
 case 998:
  if(sequence_id_13e==0){if(AT(owner_348,short,0x13c)>153 && AT(owner_348,short,0x13c)<158){x_ec=C(0x104)*57+AT(owner_348,float,0xec);y_f0=AT(owner_348,float,0xf0)+60.0;}if(AT(owner_348,short,0x13c)>149 && AT(owner_348,short,0x13c)<154){x_ec=C(0x104)*57+AT(owner_348,float,0xec);y_f0=AT(owner_348,float,0xf0)+94.0;}if(AT(owner_348,short,0x13c)==158){x_ec=C(0x104)*57+AT(owner_348,float,0xec);y_f0=AT(owner_348,float,0xf0)+100.0;}if(AT(owner_348,short,0x13c)<150 || AT(owner_348,short,0x13c)>158){next_sequence_block();AT(owner_348,unsigned char,0x751)=0;}}
  if(sequence_id_13e==1){if(alpha_113<=9)RETIRE();alpha_113-=10;}FRAME_EXIT();
 case 999:
  switch(sequence_id_13e){
  case 0:case 1:case 2:AT(owner_348,float,0xec)=x_ec;if(x_ec>1480.0f || x_ec<-200.0)RETIRE();if(sequence_id_13e>=1)velocity_y_f8-=F(0x100);break;
  case 4:{velocity_y_f8-=D(0.35f);double next_y=static_cast<double>(velocity_y_f8)+y_f0;if(next_y<=stage_surface_height()){AT(owner_348,short,0x78c)=1;y_f0=stage_surface_height();velocity_x_f4=0;velocity_y_f8=0;F(0x100)=0;select_sequence(5);return;}break;}
  case 6:if(AT(owner_348,short,0x78e)==1){next_sequence_block();B(0x104)=1;return;}break;
  case 7:case 8:if(sequence_id_13e>=8)velocity_y_f8-=F(0x100);break;
  }
  STEP();if(CORE->advance_frame_and_dispatch())--lifetime_330;
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==1){velocity_x_f4=15.0f;velocity_y_f8=15.0f;F(0x100)=0.2f;}
  if(time_counter_144==0 && frame_counter_142==0 && frame_index_140==0 && sequence_id_13e==8){velocity_x_f4=15.0f;velocity_y_f8=15.0f;F(0x100)=0.2f;}return;
 default:CORE->advance_frame_and_dispatch();return;
 }
}
#undef random_float
#undef AT
#undef F
#undef I
#undef S
#undef B
#undef C
#undef A
#undef D
#undef CORE
#undef MOTION
#undef MOVE
#undef STEP
#undef RETIRE
#undef FRAME_EXIT
#undef OUTSIDE
#undef CONTACT2468
#undef CONTACT24768
#undef WORDS
#undef SPAWN
#undef PARENTED
}
