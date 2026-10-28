#include "characters/KomachiActionState.hpp"
// Complete JP 1.06a 5e20e0 candidate, not selected or exact.
// See docs/KOMACHI_ACTION_STATE_2026_10_28.md.
namespace th105 {
void KomachiActionStateView::dispatch_action_state_vslot28() {
#define B(o) at<unsigned char>(o)
#define C(o) at<signed char>(o)
#define S(o) at<short>(o)
#define I(o) at<int>(o)
#define F(o) at<float>(o)

S(0x7a0)=0;S(0x7a2)=106;
if(B(0x72c)==2 && C(0x55a)>0){
    switch(*reinterpret_cast<KomachiCardDeque *>(reinterpret_cast<unsigned char *>(this)+0x55c)->at(0)){
    case 0:case 1:case 2:case 3:case 4:card_expiration();break;
    case 5:case 6:case 7:case 8:card_expiration();break;
    }
}
if(I(0x7a8)>0)--I(0x7a8);else I(0x7a8)=0;
if(S(0x186) || peer()->at<short>(0x48c))return;

switch(action_id_13c){

case 0:landing();if(F(0xf4)==0.0f)B(0x47e)=0;idle_motion();advance();return;
case 1:landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:landing();idle_motion();advance();return;
case 3:landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:landing();F(0xf4)=4.5f;advance();return;
case 5:landing();F(0xf4)=-4.5f;advance();return;
case 6:normal_jump(0.0f);return;
case 7:normal_jump(4.5f);return;
case 8:normal_jump(-4.5f);return;
case 9:
    if(F(0x100)==0.0f)F(0x100)=0.6f;F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=komachi_surface(this);zero_motion();return;}advance();return;
case 10:landing();zero_motion();if(advance()){if(I(0x6b8))set_action_and_finalize(2);else set_action_and_finalize(0);}return;
case 197:recovery_jump(14.5f);return;
case 198:recovery_jump(-14.5f);return;
case 199:
    landing();if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
    if(!sequence_index_13e && frame_index_140==12 && !frame_timer_142)face_peer();return;

case 200:
    landing();B(0x47e)=1;if(F(0xf4)>10.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<10.0f)F(0xf4)=10.0f;}advance();
    if(sequence_index_13e==1){
        if(!(time_counter_144%5))dash_dust(false);
        if(I(0x6b8)<0){if(I(0x6b4)*facing()<=0)set_action_and_finalize(211);else set_action_and_finalize(212);return;}
        short ticks=++S(0x730);if((I(0x6b4)*facing()<=0 && ticks>5) || ticks>45){set_action_and_finalize(204);return;}
    }
    if(entry(1)){F(0xf4)=10.0f;dash_effects(false,80.0,true);}return;
case 201:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!komachi_on_surface(this) && !(time_counter_144%5))dash_dust(true);
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0xf0)=komachi_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(entry(1)){F(0xf4)=-12.0f;F(0xf8)=4.0f;F(0x100)=0.4f;dash_effects(true,80.0,false);}return;
case 202:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=komachi_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && !(time_counter_144%5))dash_dust(false);advance();
    if(entry(1)){F(0xf4)=11.0f;F(0xf8)=-1.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);}if(entry(2))flip();return;
case 203:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=komachi_surface(this);frame_timer_142=0;set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && !(time_counter_144%5))dash_dust(true);advance();
    if(entry(1)){F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3)flip();return;
case 204:
    landing();F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}if(advance()){set_action_and_finalize(0);zero_motion();B(0x47e)=0;}return;
case 208:high_jump(0.0f,20.0f,0.65f,true,false);return;
case 209:high_jump(8.0f,16.0f,0.6f,false,false);return;
case 210:high_jump(-8.0f,16.0f,0.6f,false,false);return;
case 211:high_jump(2.0f,20.0f,0.65f,false,false);return;
case 212:high_jump(8.0f,16.0f,0.6f,false,false);return;

case 214:
    if(advance()){set_action_and_finalize(9);return;}if(entry(1))event(31);if(entry(6)){set_action_and_finalize(9);return;}
    if(I(0x6b8)>0){int direction=I(0x6b4)*facing();S(0x732)=static_cast<short>(direction>0?-45:(direction<0?-135:-90));}
    else if(I(0x6b8)<0){int direction=I(0x6b4)*facing();S(0x732)=static_cast<short>(direction>0?45:(direction<0?135:90));}
    else{int direction=I(0x6b4)*facing();if(direction>0)S(0x732)=0;else if(direction<0)S(0x732)=180;}
    if(sequence_index_13e==5 || sequence_index_13e==6)F(0xf8)-=F(0x100);
    if(sequence_index_13e>0 && sequence_index_13e<5){
        ++S(0x736);S(0x734)=static_cast<short>(S(0x732)-static_cast<int>(F(0x740)));
        if(S(0x734)>180)S(0x734)-=360;if(S(0x734)<-180)S(0x734)+=360;
        if(S(0x734)>0){if(I(0x4b8))F(0x740)=static_cast<float>(F(0x740)+0.5);else F(0x740)=static_cast<float>(F(0x740)+1.5);}
        if(S(0x734)<0){if(I(0x4b8))F(0x740)=static_cast<float>(F(0x740)-0.5);else F(0x740)=static_cast<float>(F(0x740)-1.5);}
        F(0xf4)=static_cast<float>(komachi_cosine(F(0x740))*F(0x73c));
        F(0xf8)=static_cast<float>(komachi_sine(F(0x740))*F(0x73c));
        if(F(0xf0)>680.0f && F(0xf8)>0.0f)F(0xf8)=0.0f;
        F(0x73c)=static_cast<float>(F(0x73c)+static_cast<double>(0.3f));if(F(0x73c)>12.0f)F(0x73c)=12.0f;
        if(I(0x4b8))counter(10,1);else counter(5,1);
        F(0x12c)=-F(0x740);if(F(0xf4)<0.0f)F(0x12c)=static_cast<float>(180.0-F(0x740));
        if(F(0xf4)<0.0f && sequence_index_13e==1)select_sequence(3);
        if(F(0xf4)>=0.0f && sequence_index_13e==3)select_sequence(1);
        if(F(0xf4)<0.0f && sequence_index_13e==2)select_sequence(4);
        if(F(0xf4)>=0.0f && sequence_index_13e==4)select_sequence(2);
        if(time_counter_144%5==1){int direction=B(0x104);float y=static_cast<float>(komachi_sine(F(0x740))*100.0+F(0xf0)+100.0);float x=static_cast<float>(komachi_cosine(F(0x740))*100.0*facing()+F(0xec));effect(125,x,y,direction,1);}
        if(!((I(0x6c8) || S(0x736)<=10) && S(0x482)>0)){
            reset_action_scratch();
            if(sequence_index_13e==1 || sequence_index_13e==2){
                unsigned char direction=B(0x104);double x=F(0xec);
                if(direction==1){if(peer()->at<float>(0xec)<x){B(0x104)=255;F(0xf4)=-F(0xf4);select_sequence(6);}else select_sequence(5);}
                else if(peer()->at<float>(0xec)>x){B(0x104)=static_cast<unsigned char>(-direction);F(0xf4)=-F(0xf4);select_sequence(6);}
                else select_sequence(5);
            }
            if(sequence_index_13e==3 || sequence_index_13e==4){
                unsigned char direction=B(0x104);double x=F(0xec);
                if(direction==1){if(peer()->at<float>(0xec)<x){B(0x104)=255;F(0xf4)=-F(0xf4);select_sequence(5);}else select_sequence(6);}
                else if(peer()->at<float>(0xec)<=x)select_sequence(6);
                else{B(0x104)=static_cast<unsigned char>(-direction);F(0xf4)=-F(0xf4);select_sequence(5);}
            }
            return;
        }
    }
    if(static_cast<unsigned char>(crossed())){F(0xf0)=komachi_surface(this);F(0x100)=0.0f;F(0xf8)=0.0f;
        if(sequence_index_13e>=5){set_action_and_finalize(10);zero_motion();}
        else{reset_action_scratch();set_action_and_finalize(215);}}
    return;


case 215:
    landing();if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:high_jump(0.0f,20.0f,0.65f,true,true);return;
case 221:high_jump(8.0f,16.0f,0.6f,true,true);return;
case 222:high_jump(-8.0f,16.0f,0.6f,true,true);return;
case 223:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1){if(!(time_counter_144%5))dash_dust(false);short ticks=++S(0x730);if((I(0x6b4)*facing()<=0 && ticks>15) || ticks>45){set_action_and_finalize(204);return;}}
    if(entry(1)){F(0xf4)=5.0f;dash_effects(false,80.0,true);}return;
case 224:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!komachi_on_surface(this) && !(time_counter_144%5))dash_dust(true);
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0xf0)=komachi_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(entry(1) && !S(0x730)){S(0x730)=1;F(0xf4)=-10.0f;F(0xf8)=4.0f;F(0x100)=0.4f;dash_effects(true,80.0,false);}return;
case 225:
    if(sequence_index_13e>0){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=komachi_surface(this);set_action_and_finalize(10);return;}}
    if(sequence_index_13e>=2 && !(time_counter_144%5))dash_dust(true);if(advance())set_action_and_finalize(9);
    if(entry(1)){F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}if(entry(3))flip();return;
case 226:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=komachi_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e==1 && !(time_counter_144%5))dash_dust(false);if(advance())set_action_and_finalize(9);
    if(entry(1)){F(0xf4)=11.0f;F(0xf8)=-1.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);}if(entry(3))flip();return;

case 300:
    landing();if(directional(0))return;if(B(0x47e))decelerate(0.5,true);if(F(0xf4)>0.0f)decelerate(0.5,false);
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==2){event(27);B(0x47e)=0;}return;
case 301:landing();if(!directional(0))normal301();return;
case 302:
    landing();if(directional(1))return;if(!I(0x6bc))B(0x750)=0;
    if(advance() || entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==4 && B(0x750)){charge(246,90.0);return;}if(frame_index_140==1){event(29);F(0xf4)=20.0f;}}if(frame_index_140>=2)decelerate(5.0,false);}
    if(sequence_index_13e==1){if(!frame_timer_142 && frame_index_140==1)ring817();decelerate(5.0,false);}return;
case 303:
    landing();if(directional(0))return;if(C(0x47e)>0)decelerate(static_cast<double>(0.6f),true);if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==2)event(27);return;
case 304:
    landing();if(directional(1))return;if(!I(0x6bc))B(0x750)=0;if(B(0x47e))decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){if(B(0x750)){charge(-45,40.0);return;}event(29);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1)ring817();return;
case 305:
    landing();if(directional(1))return;if(frame_index_140>=2)decelerate(0.75,false);if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==2)event(28);return;
case 306:
    if(air_normal_land())return;if(advance())set_action_and_finalize(9);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)event(28);return;
case 307:
    if(air_normal_land())return;if(advance())set_action_and_finalize(9);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)event(29);return;
case 308:
    if(air_normal_land())return;if(advance())set_action_and_finalize(9);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5)event(29);return;
case 309:
    if(air_normal_land())return;if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==5){if(F(0xf8)<8.0f)F(0xf8)=8.0f;F(0x100)=0.5f;}if(!frame_timer_142 && frame_index_140==6)event(29);}return;
case 310:
    if(!sequence_index_13e){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0xf0)=komachi_surface(this);next_sequence_block();return;}}
    if(sequence_index_13e==1){landing();decelerate(0.5,false);}if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)event(29);return;
case 320:
    landing();if(directional(0))return;if(frame_index_140>=7)F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3)F(0xf4)=10.0f;if(!frame_timer_142){if(frame_index_140==5){event(28);B(0x47e)=0;}if(!frame_timer_142 && frame_index_140==7)F(0xf4)=static_cast<float>(F(0xf4)*0.25);}}return;
case 321:
    landing();if(directional(1))return;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)event(29);return;
case 322:
    landing();if(directional(1))return;if(B(0x47e))decelerate(0.5,true);if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==8){event(29);F(0xf4)=15.0f;}if(!frame_timer_142 && frame_index_140==10)F(0xf4)=0.0f;}return;


case 400:ground800(false,-20.0f,10.0f);return;
case 401:ground800(true,-40.0f,-20.0f);return;
case 402:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(S(0x730)==1 && !sequence_index_13e)stream800(8,20.0,-5,160.0,false,false);
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)start800(-80.0f,-45.0f,false);return;
case 404:
    if(sequence_index_13e==2)landing();if(!I(0x6c0))B(0x750)=0;F(0xf8)-=F(0x100);
    if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);B(0x47f)=0;F(0xf0)=komachi_surface(this);zero_motion();return;}
    if(S(0x730)==1){if(!sequence_index_13e)stream800(6,15.0,105,162.0,false,false);if(sequence_index_13e==1)stream800(10,25.0,105,162.0,false,false);}
    if(advance())set_action_and_finalize(0);if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142){if(frame_index_140==3 && B(0x750)==1){charge(-20,145.0);return;}if(frame_index_140==8)start800(-30.0f,10.0f,false);}
        if(!frame_timer_142 && frame_index_140==12)F(0x100)=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==6)start800(-30.0f,10.0f,false);if(!frame_timer_142 && frame_index_140==10)F(0x100)=0.5f;}return;
case 405:
    if(sequence_index_13e==2)landing();if(!I(0x6c0))B(0x750)=0;F(0xf8)-=F(0x100);
    if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);B(0x47f)=0;F(0xf0)=komachi_surface(this);zero_motion();return;}
    if(S(0x730)==1 && !sequence_index_13e)stream800(10,0.0,100,160.0,false,true);
    if(advance())set_action_and_finalize(0);if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==6){phase_counter(30);F(0x744)=0.0f;S(0x730)=1;counter(200,45);}if(!frame_timer_142 && frame_index_140==12)F(0x100)=0.5f;}return;
case 406:
    if(sequence_index_13e==2)landing();if(!I(0x6c0))B(0x750)=0;F(0xf8)-=F(0x100);
    if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);F(0x100)=0.0f;B(0x47f)=0;F(0xf0)=komachi_surface(this);zero_motion();return;}
    if(S(0x730)==1){if(!sequence_index_13e)stream800(6,15.0,75,110.0,false,false);if(sequence_index_13e==1)stream800(10,25.0,75,110.0,false,false);}
    if(advance())set_action_and_finalize(0);if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==3 && B(0x750)==1){charge(-20,190.0);return;}if(frame_index_140==6)start800(20.0f,50.0f,true);}if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;}
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==3)start800(20.0f,40.0f,true);if(!frame_timer_142 && frame_index_140==7)F(0x100)=0.5f;}return;
case 408:landing();decelerate(0.5,false);if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)event(29);return;
case 409:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=komachi_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){phase_counter(50);counter(200,60);dispatch_character_wave_handle(1);aim(-40.0f,40.0f);float p[3]={F(0x744),3.0f,0.0f};spawn_offset(801,87,184.0,p,3);}return;

case 411:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==7 && B(0x750)){charge(-100,164.0);return;}if(frame_index_140==10)fan801(10.0,7.0,24.0f,35.0,120.0,false,-10.0f,10.0f);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4)fan801(10.0,7.0,24.0f,35.0,120.0,true,-10.0f,10.0f);return;
case 412:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==13){
        phase_counter(50);I(0x7a8)=10;counter(200,60);dispatch_character_wave_handle(15);
        float p[3]={0.0f,85.0f,4.0f};spawn(801,static_cast<float>(84*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        p[0]=static_cast<float>(static_cast<double>(komachi_random(80))-40.0);p[1]=static_cast<float>(static_cast<double>(komachi_random(80))-40.0);spawn(801,static_cast<float>(84*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        p[0]=static_cast<float>(static_cast<double>(komachi_random(80))-40.0);p[1]=static_cast<float>(static_cast<double>(komachi_random(80))-40.0);spawn(801,static_cast<float>(84*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
    }return;
case 414:
    if(air_shot_landing(false))return;if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==5){phase_counter(50);counter(200,60);dispatch_character_wave_handle(1);aim(-40.0f,40.0f);float p[3]={F(0x744),3.0f,0.0f};spawn_offset(801,65,175.0,p,3);}
        if(!frame_timer_142 && frame_index_140==10)F(0x100)=0.5f;
    }return;
case 415:
    if(air_shot_landing(false))return;if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(9);if(entry(2))set_action_and_finalize(9);
    if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==2 && B(0x750)){charge(-70,170.0);return;}if(frame_index_140==4)fan801(15.0,10.0,24.0f,0.0,140.0,false,-10.0f,10.0f);}if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;}
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==3)fan801(15.0,10.0,24.0f,0.0,140.0,true,-10.0f,10.0f);if(!frame_timer_142 && frame_index_140==8)F(0x100)=0.5f;}return;
case 416:
    if(air_shot_landing(false))return;if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(9);if(entry(2))set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4 && B(0x750)){charge(-104,224.0);return;}if(frame_index_140==7){F(0xf4)=-5.0f;F(0xf8)=7.5f;F(0x100)=0.5f;fan801(10.0,5.0,16.0f,0.0,100.0,false,40.0f,70.0f);}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4){F(0xf4)=-5.0f;F(0xf8)=7.5f;F(0x100)=0.5f;fan801(10.0,5.0,16.0f,0.0,100.0,true,40.0f,70.0f);}return;
case 418:
    landing();decelerate(0.5,false);if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==8){event(29);B(0x47e)=0;}return;


case 500:
    landing();B(0x17c)=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10){float p[3]={0.0f,10.0f,0.0f};spawn(810,static_cast<float>(200*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);skill_cost(10);}return;
case 501:
    landing();B(0x17c)=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10){float p[3]={0.0f,20.0f,0.0f};spawn(810,static_cast<float>(200*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);skill_cost(10);}return;
case 505:ground811(0.0f,3.0f);return;
case 506:ground811(2.0f,5.0f);return;
case 507:air811(7,0.0f,3.0f,12);return;
case 508:air811(6,1.0f,4.0f,11);return;
case 510:
    landing();B(0x17c)=8;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10){
        float p[3]={0.0f,10.0f,0.0f};if(C(0x60c)>=4)p[2]=2.0f;
        if(B(0x104)==1)spawn(812,static_cast<float>(komachi_boundary_6fbd24+100.0),F(0xf0),-1,1,p,3);
        else spawn(812,static_cast<float>(komachi_boundary_6fbd1c-100.0),F(0xf0),static_cast<unsigned char>(-B(0x104)),1,p,3);
        skill_cost(10);
    }return;
case 511:
    landing();B(0x17c)=8;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10){
        float p[3]={0.0f,10.0f,0.0f};if(C(0x60c)>=4)p[2]=2.0f;
        if(B(0x104)==255)spawn(812,static_cast<float>(komachi_boundary_6fbd24+100.0),F(0xf0),-1,1,p,3);
        else spawn(812,static_cast<float>(komachi_boundary_6fbd1c-100.0),F(0xf0),B(0x104),1,p,3);
        skill_cost(10);
    }return;
case 520:stream815(20.0);return;
case 521:stream815(25.0);return;
case 525:
    landing();B(0x17c)=5;
    if(sequence_index_13e==1 && sweep817(1.0f,10.0,40))return;
    if(sequence_index_13e==3 && sweep817(1.5f,20.0,40))return;
    if(advance())set_action_and_finalize(0);if(entry(3)){set_action_and_finalize(0);return;}
    if(entry(1)){sweep_entry();if(C(0x609)>=4)select_sequence(3);}return;
case 526:
    landing();B(0x17c)=5;decelerate(0.25,false);
    if(sequence_index_13e==1 && sweep817(1.0f,10.0,65))return;
    if(sequence_index_13e==3 && sweep817(1.5f,20.0,65))return;
    if(advance())set_action_and_finalize(0);if(entry(3)){set_action_and_finalize(0);return;}
    if(entry(1)){sweep_entry();if(C(0x609)>=4){select_sequence(3);return;}}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5)F(0xf4)=10.0f;return;
case 540:swap820(0x606,false,true);return;
case 541:swap820(0x606,true,false);return;
case 542:swap820(0x60a,false,false);return;
case 543:swap820(0x606,true,false);return;
case 545:ground821(0x6c0);return;
case 546:ground821(0x6c4);return;
case 550:movement822(0x6c0,0x6c4,false);return;
case 551:movement822(0x6c4,0x6c0,true);return;

case 560:ground825(0x6c0);return;
case 561:ground825(0x6c4);return;
case 562:{
    if(sequence_index_13e==5)landing();B(0x17c)=3;F(0xf8)-=F(0x100);double y=F(0xf8)+static_cast<double>(F(0xf0));
    if(komachi_surface(this)>=y && F(0xf8)<0.0f && sequence_index_13e<5){select_sequence(5);F(0x100)=0.0f;B(0x47f)=0;F(0xf0)=komachi_surface(this);zero_motion();return;}
    if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(at<unsigned short>(0x730)>0 && (sequence_index_13e==2 || sequence_index_13e==3)){
        if(at<unsigned short>(0x730)%4==1){phase_counter(10);I(0x180)=1;aim_short();dispatch_character_wave_handle(9);if(S(0x738)==1)burst808();else burst808();}++S(0x730);
    }
    if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>4 && (!B(0x750)||time_counter_144>25))next_sequence_block();
    if(entry(1)){if(B(0x750)==1)effect(62,static_cast<float>(F(0xec)-23*facing()),static_cast<float>(F(0xf0)+107.0),B(0x104),1);
        float p[3]={0.0f,0.0f,4.0f};spawn_offset(808,-23,107.0,p,3);}
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){S(0x730)=1;counter(200,120);}
    if(sequence_index_13e==3 && ((time_counter_144>10 && !B(0x750))||time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.6f;return;}
case 565:ground827(0x6c0);return;
case 566:ground827(0x6c4);return;
case 567:{
    if(sequence_index_13e==5)landing();B(0x17c)=7;F(0xf8)-=F(0x100);double y=F(0xf8)+static_cast<double>(F(0xf0));
    if(komachi_surface(this)>=y && F(0xf8)<0.0f && sequence_index_13e<5){select_sequence(5);F(0x100)=0.0f;B(0x47f)=0;F(0xf0)=komachi_surface(this);zero_motion();return;}
    if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){aim_short();dispatch_character_wave_handle(29);I(0x180)=1;counter(200,60);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(824,48,104.0,p,3);}
    if(advance())set_action_and_finalize(0);if(entry(1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(824,-48,104.0,p,3);}
    if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>10 && (!B(0x750)||time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.6f;return;}

case 599:
    if(S(0x730)>0 && frame_index_140<7 && S(0x730)<12){
        S(0x734)=static_cast<short>(komachi_random_u32()%35u);
        float p[3]={static_cast<float>(-20-S(0x734)),static_cast<float>(static_cast<short>(komachi_random_u32()%5u+10)),0.0f};
        spawn(807,static_cast<float>(20*facing()*(S(0x730)+1)+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        p[0]=static_cast<float>(komachi_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        spawn(801,static_cast<float>(20*facing()*(S(0x730)+1)+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        if(S(0x730)==1){dispatch_character_wave_handle(0);counter(200,120);}++S(0x730);
    }
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)S(0x730)=1;return;

case 600:
    if((!sequence_index_13e && frame_index_140>=10) || sequence_index_13e==1 || sequence_index_13e==4)landing();texture(4,2);
    if(sequence_index_13e==1){
        F(0xf4)=F(0xfc)+F(0xf4);if(F(0xf4)>25.0f)F(0xf4)=17.5f;
        if(I(0x180) && ++S(0x730)>=10){S(0x730)=0;B(0x184)=1;I(0x180)=0;}
        if(!(time_counter_144%2))spell_ground_particles(850,90,-45.0,5.0,1.0f);
        if(time_counter_144>=50){B(0x184)=1;I(0x180)=0;next_sequence_block();return;}
    }
    if(sequence_index_13e==2 && frame_index_140<=1){decelerate(1.0,false);spell_ground_particles(850,60,-10.0,10.0,1.0f);}
    if(sequence_index_13e==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=komachi_surface(this);next_sequence_block();return;}}
    if(advance()){set_action_and_finalize(0);zero_motion();return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,100.0,1);if(!frame_timer_142 && frame_index_140==11){F(0xf4)=5.0f;F(0xfc)=1.0f;dispatch_character_wave_handle(50);}}
    if(entry(3)){F(0xf4)=-10.0f;F(0xf8)=8.0f;F(0x100)=0.75f;}return;
case 601:
    texture(4,2);landing();if(!sequence_index_13e && I(0x180)==1){grab_peer();return;}
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(-117,114.0,5);if(!frame_timer_142 && frame_index_140==7){float p[3];ring817_at(p,120);}}
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3)dispatch_character_wave_handle(51);
        if(!frame_timer_142 && frame_index_140==14){F(0x73c)=static_cast<float>(peer()->at<short>(0x174)*0.5);if(F(0x73c)<=1.0f)F(0x73c)=0.0f;
            forward_hit_quantity(static_cast<int>(F(0x73c)),850,1,0);peer()->at<float>(0x18c)=24.0f;peer()->at<float>(0x190)=15.0f;peer()->set_action_and_finalize(74);
            dispatch_character_wave_handle(52);layout(10.0f);float p[3];ring817_at(p,120);}
    }return;
case 602:
    texture(4,2);landing();
    if(S(0x730)==1 && !sequence_index_13e){if(!(S(0x732)%5)){I(0x180)=1;aim(-10.0f,10.0f);dispatch_character_wave_handle(14);
        if(at<unsigned short>(0x734)<5){float p[3]={static_cast<float>(F(0x744)-static_cast<double>(at<unsigned short>(0x734))*18.0+25.0),7.0f,0.0f};spawn_offset(852,90,180.0,p,3);++S(0x734);}}++S(0x732);}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,140.0,1);if(!frame_timer_142 && frame_index_140==4)S(0x730)=1;}return;
case 603:
    if((!sequence_index_13e && frame_index_140>=10) || sequence_index_13e==1 || sequence_index_13e==4)landing();texture(4,2);
    if(sequence_index_13e==1){
        F(0xf4)=static_cast<float>(F(0xf4)+static_cast<double>(0.1f));if(F(0xf4)>4.0f)F(0xf4)=3.0f;
        if(!(time_counter_144%2))spell_ground_particles(853,90,-45.0,5.0,3.0f);
        if(!(time_counter_144%4) && time_counter_144<=120){float p[3]={static_cast<float>(static_cast<double>(komachi_random(12))+6.0),static_cast<float>(static_cast<double>(komachi_random(8))+2.0),0.0f};
            int direction=B(0x104);if(direction==1){float y=static_cast<float>(static_cast<double>(komachi_random(300))+F(0xf0)+20.0);spawn(853,static_cast<float>(komachi_boundary_6fbd1c-50.0),y,1,1,p,3);}
            else{float y=static_cast<float>(static_cast<double>(komachi_random(300))+F(0xf0)+20.0);spawn(853,static_cast<float>(komachi_boundary_6fbd24+50.0),y,direction,1,p,3);}}
        if(time_counter_144>=150){next_sequence_block();return;}
    }
    if(sequence_index_13e==2 && frame_index_140<=1){decelerate(static_cast<double>(0.1f),false);spell_ground_particles(853,60,-10.0,10.0,3.0f);}
    if(sequence_index_13e==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=komachi_surface(this);next_sequence_block();return;}}
    if(advance()){set_action_and_finalize(0);zero_motion();}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2)spell_flash(0,100.0,3);
    if(entry(3)){F(0xf4)=-3.0f;F(0xf8)=8.0f;F(0x100)=0.75f;}return;
case 604:
    texture(4,2);landing();if(!sequence_index_13e && I(0x180)==1){grab_peer();return;}
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(-117,114.0,5);if(!frame_timer_142 && frame_index_140==6){float p[3];ring817_at(p,120);}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(51);
    if(sequence_index_13e==2){
        if(!time_counter_144 && !frame_timer_142 && !frame_index_140){
            float p[3];
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*45.0);p[1]=0.0f;p[2]=0.0f;spawn_offset(854,0,100.0,p,3);}
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*45.0);p[1]=0.0f;p[2]=1.0f;spawn(854,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),B(0x104),1,p,3);}dispatch_character_wave_handle(55);
        }
        if(S(0x730)==1){
            KomachiActionStateView *other=peer();F(0x73c)=static_cast<float>(other->at<short>(0x174));F(0x740)=static_cast<float>(S(0x174));other->at<short>(0x174)=static_cast<short>(static_cast<int>(F(0x740)));S(0x174)=static_cast<short>(static_cast<int>(F(0x73c)));
            layout(3.0f);float p[3];ring817_at(p,120);
            p[0]=0.0f;p[1]=0.0f;p[2]=5.0f;spawn(854,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),B(0x104),1,p,3);
            for(int n=6;n;--n){p[0]=static_cast<float>(komachi_random(360));p[1]=static_cast<float>(static_cast<double>(komachi_random(75))*static_cast<double>(0.1f)+10.0);p[2]=4.0f;spawn(854,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),B(0x104),1,p,3);}
            p[0]=0.0f;p[1]=0.0f;p[2]=5.0f;spawn_offset(854,0,100.0,p,3);
            for(int n=6;n;--n){p[0]=static_cast<float>(komachi_random(360));p[1]=static_cast<float>(static_cast<double>(komachi_random(75))*static_cast<double>(0.1f)+10.0);p[2]=4.0f;spawn(854,F(0xec),F(0xf0),B(0x104),1,p,3);}
            dispatch_character_wave_handle(56);S(0x730)=2;S(0x732)=0;
        }
        if(S(0x730)==2 && ++S(0x732)>=30){peer()->at<float>(0x18c)=5.0f;peer()->at<float>(0x190)=10.0f;peer()->set_action_and_finalize(71);next_sequence_block();}
    }return;
case 605:
    texture(4,2);landing();
    if(S(0x730)==1 && !sequence_index_13e){if(!(S(0x732)%5)){dispatch_character_wave_handle(14);if(at<unsigned short>(0x734)<6){float p[3]={static_cast<float>(15.0-static_cast<double>(at<unsigned short>(0x734))*60.0),7.0f,0.0f};spawn_offset(855,90,180.0,p,3);++S(0x734);}}++S(0x732);}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,140.0,3);if(!frame_timer_142 && frame_index_140==4)S(0x730)=1;}return;
case 606:
    texture(4,2);landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==7)spell_flash(-102,164.0,4);if(!frame_timer_142 && frame_index_140==10){float p[3]={0.0f,-80.0f,0.0f};spawn(856,peer()->at<float>(0xec),1000.0f,B(0x104),1,p,3);dispatch_character_wave_handle(53);}}return;
case 611:
    texture(4,2);landing();if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==5)spell_flash(-97,122.0,3);if(!frame_timer_142 && frame_index_140==10){float p[3]={0.0f,10.0f,0.0f};spawn(861,static_cast<float>(200*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        p[2]=4.0f;spawn(861,static_cast<float>(200*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),-1,p,3);dispatch_character_wave_handle(10);}}return;


case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){event(55);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(141,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1);effect(142,F(0xec),F(0xf0),B(0x104),-1);}return;
case 696:landing();normal301();return;
case 710:
    if(sequence_index_13e==1){
        if(time_counter_144>=120)next_sequence_block();
        if(!(time_counter_144%S(0x736))){
            dispatch_character_wave_handle(1);float p[3]={0.0f,static_cast<float>(static_cast<double>(S(0x730))+S(0x730)),0.0f};
            F(0x744)=static_cast<float>(static_cast<double>(komachi_random(150))+50.0);
            F(0x73c)=static_cast<float>(komachi_cosine(static_cast<float>(komachi_random(360)))*F(0x744)+peer()->at<float>(0xec));
            if(F(0x73c)<-50.0f)F(0x73c)=-50.0f;
            if(F(0x740)<-150.0f)F(0x740)=-150.0f;
            F(0x740)=static_cast<float>(komachi_sine(static_cast<float>(komachi_random(360)))*F(0x744)+peer()->at<float>(0xf0));
            spawn(900,F(0x73c),F(0x740),B(0x104),1,p,3);++S(0x730);
        }
    }
    if(advance())set_action_and_finalize(700);
    if(entry(1)){switch(g_match_identifier){case 0:S(0x736)=20;break;case 1:S(0x736)=15;break;case 2:case 3:S(0x736)=10;break;}}return;
case 711:
    if(S(0x730)>0)++S(0x732);if(advance())set_action_and_finalize(700);
    if(!frame_timer_142 && frame_index_140==10){dispatch_character_wave_handle(18);S(0x730)=1;float p[3];ring817_at(p,112);
        p[2]=6.0f;spawn(900,static_cast<float>(112*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);}return;
case 720:
    if(sequence_index_13e==1 && time_counter_144>=120)next_sequence_block();if(advance())set_action_and_finalize(700);
    if(entry(1)){
        dispatch_character_wave_handle(19);float p[3];
        for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(komachi_random(40))+angle+30.0);p[1]=13.0f;p[2]=2.0f;
            if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,F(0xec),F(0xf0),B(0x104),-1,p,3);else spawn(817,F(0xec),F(0xf0),B(0x104),1,p,3);}
        p[0]=0.0f;p[1]=10.0f;p[2]=0.0f;spawn(901,peer()->at<float>(0xec),F(0xf0),B(0x104),1,p,3);
        p[2]=4.0f;spawn(901,peer()->at<float>(0xec),F(0xf0),B(0x104),-1,p,3);
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3){
        float p[3];
        switch(g_match_identifier){
        case 0:p[0]=0.0f;p[1]=-50.0f;p[2]=10.0f;spawn(901,peer()->at<float>(0xec),1000.0f,B(0x104),1,p,3);dispatch_character_wave_handle(53);break;
        case 1:p[0]=0.0f;p[1]=-60.0f;p[2]=11.0f;spawn(901,peer()->at<float>(0xec),1000.0f,B(0x104),1,p,3);dispatch_character_wave_handle(53);break;
        case 2:p[0]=0.0f;p[1]=-70.0f;p[2]=12.0f;spawn(901,peer()->at<float>(0xec),1000.0f,B(0x104),1,p,3);dispatch_character_wave_handle(53);break;
        case 3:p[0]=0.0f;p[1]=-80.0f;p[2]=13.0f;spawn(901,peer()->at<float>(0xec),1000.0f,B(0x104),1,p,3);dispatch_character_wave_handle(53);break;
        default:dispatch_character_wave_handle(53);break;
        }
    }return;
case 730:
    if(sequence_index_13e==1 && time_counter_144>=120)next_sequence_block();if(advance())set_action_and_finalize(700);
    if(entry(1)){
        dispatch_character_wave_handle(12);float base=static_cast<float>(komachi_random(360));float jitter=static_cast<float>(static_cast<double>(komachi_random(20))-10.0);float p[3];
        switch(g_match_identifier){
        case 0:ring902(p,base,jitter,6,60.0,0.0,false,5.0f);break;
        case 1:ring902(p,base,jitter,8,45.0,0.0,false,5.0f);break;
        case 2:ring902(p,base,jitter,12,30.0,0.0,false,5.0f);break;
        case 3:ring902(p,base,jitter,8,45.0,0.0,true,6.0f);ring902(p,base,jitter,8,45.0,22.5,false,4.0f);break;
        }
    }return;
case 732:
    if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(704);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,0.0f};spawn(930,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1,p,3);
        p[1]=1.0f;spawn(930,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1,p,3);}
    if(entry(2)){
        if(peer()->action_id_13c<=599){
            float p[3]={0.0f,0.0f,1.0f};spawn_offset(930,0,100.0,p,3);
            p[1]=1.0f;spawn(930,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),B(0x104),1,p,3);
            p[1]=0.0f;p[2]=2.0f;spawn_offset(930,0,100.0,p,3);
            p[1]=1.0f;spawn(930,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),B(0x104),1,p,3);
            if(komachi_on_surface(this)){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(komachi_random(40))+angle+30.0);p[1]=13.0f;p[2]=2.0f;int layer=(p[0]>=0.0f && p[0]<=180.0f)?1:-1;spawn(817,F(0xec),F(0xf0),B(0x104),layer,p,3);}
            }
            if(komachi_on_surface(peer())){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(komachi_random(40))+angle+30.0);p[1]=13.0f;p[2]=2.0f;
                    if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,peer()->at<float>(0xec),peer()->at<float>(0xf0),B(0x104),-1,p,3);
                    else spawn(817,peer()->at<float>(0xec),peer()->at<float>(0xf0),B(0x104),1,p,3);}
            }
            KomachiActionStateView *other=peer();F(0x73c)=F(0xec);F(0x740)=F(0xf0);F(0xec)=other->at<float>(0xec);F(0xf0)=other->at<float>(0xf0);other->at<float>(0xec)=F(0x73c);peer()->at<float>(0xf0)=F(0x740);
        }
        dispatch_character_wave_handle(13);S(0x738)=1;
    }
    if(entry(3)){if(!komachi_on_surface(this))set_action_and_finalize(704);else set_action_and_finalize(700);}
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){if(sequence_index_13e==4)set_action_and_finalize(700);}
    else if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)F(0x100)=0.5f;return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8){B(0x655)=1;finalize(-1);texture(2,-1);copy_health();S(0x76c)=0;S(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);}return;
case 795:
    if(!sequence_index_13e){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.3f));if(static_cast<unsigned char>(crossed())){select_sequence(1);event(30);F(0xf0)=komachi_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:
    if(sequence_index_13e<=2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(3);event(30);F(0xf0)=komachi_surface(this);F(0xf8)=0.0f;return;}}
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f){F(0xf4)=0.0f;F(0xec)=480.0f;}if(F(0xec)>480.0f)F(0xec)=480.0f;}
    if(advance())set_action_and_finalize(0);return;
case 798:
    if(sequence_index_13e<=2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(3);event(30);F(0xf0)=komachi_surface(this);F(0xf8)=0.0f;return;}}
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f){F(0xf4)=0.0f;F(0xec)=800.0f;}if(F(0xec)<800.0f)F(0xec)=800.0f;}
    if(advance())set_action_and_finalize(700);return;

default:common_update();return;
}
#undef B
#undef C
#undef S
#undef I
#undef F
}
}
