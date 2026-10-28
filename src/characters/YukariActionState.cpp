#include "characters/YukariActionState.hpp"
// Complete JP1.06a57B030 candidate, not selected or exact.
// See docs/YUKARI_ACTION_STATE_2026_10_28.md.
namespace th105 {
#define B(o) at<unsigned char>(o)
#define C(o) at<signed char>(o)
#define S(o) at<short>(o)
#define U(o) at<unsigned>(o)
#define I(o) at<int>(o)
#define F(o) at<float>(o)
void YukariActionStateView::dispatch_action_state_vslot28() {
S(0x7a0)=0;S(0x7a2)=100;
if(action_id_13c>149 && action_id_13c<159 && !B(0x751)) {
    B(0x751)=1;float p[1];
    if(action_id_13c>149 && action_id_13c<154) {
        p[0]=10.0f;spawn_offset(998,80,130.0,p,1);
        p[0]=-10.0f;spawn_offset(998,80,130.0,p,1);
    }
    if(action_id_13c>153 && action_id_13c<158) {
        p[0]=10.0f;spawn_offset(998,60,80.0,p,1);
        p[0]=-10.0f;spawn_offset(998,60,80.0,p,1);
    }
    if(action_id_13c==158) {
        p[0]=10.0f;spawn_offset(998,75,140.0,p,1);
        p[0]=-10.0f;spawn_offset(998,75,140.0,p,1);
    }
}
if(S(0x186) || peer()->at<short>(0x48c))return;

switch(action_id_13c) {
case 0:
    landing();if(F(0xf4)==0.0f)B(0x47e)=0;idle_motion();advance();return;
case 1:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:
    landing();idle_motion();advance();return;
case 3:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:landing();F(0xf4)=4.5f;advance();return;
case 5:landing();F(0xf4)=-4.5f;advance();return;
case 6:normal_jump(0.0f);return;
case 7:normal_jump(4.0f);return;
case 8:normal_jump(-4.0f);return;
case 9:
    if(F(0x100)==0.0f)F(0x100)=0.6f;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=yukari_surface(this);zero_motion();return;}
    advance();return;
case 10:
    landing();zero_motion();if(advance()){if(!I(0x6b8)){set_action_and_finalize(0);return;}set_action_and_finalize(2);}return;
case 71:
    if(entry(1))ensure_recovery_object();
    if(sequence_index_13e==1 && F(0xf8)<2.0f){next_sequence_block();return;}
    F(0xf8)-=F(0x100);if(F(0xf8)>0.0f)F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(2.0f);event(22);return;}
    if(S(0x730)>0)--S(0x730);recovery_slide(1.0,true);advance();return;
case 72:
    if(sequence_index_13e==1 && F(0xf8)<2.0f){next_sequence_block();return;}
    if(entry(1))ensure_recovery_object();F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(2.0f);event(22);return;}
    recovery_slide(1.0,false);advance();return;
case 73:
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(5.0f);event(22);return;}
    advance();if(recovery_entry_sequence())return;
    if(--S(0x730)<0)S(0x730)=0;recovery_slide(2.5,true);return;
case 74:
    if(entry(1))ensure_recovery_object();
    if(sequence_index_13e==1 && F(0xf8)<2.0f){next_sequence_block();return;}
    if(classify_fighter_x_boundary() && F(0xf4)<=-25.0f){set_action_and_finalize(76);return;}
    if(classify_fighter_x_boundary() && F(0xf4)<=-15.0f){set_action_and_finalize(78);return;}
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(2.0f);event(22);return;}
    advance();return;
case 75:
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(5.0f);event(22);return;}
    if(classify_fighter_x_boundary() && F(0xf4)<=-25.0f){set_action_and_finalize(76);return;}
    if(classify_fighter_x_boundary() && F(0xf4)<=-15.0f){set_action_and_finalize(78);return;}
    advance();recovery_entry_sequence();return;
case 76:
    if(sequence_index_13e>0)F(0x12c)=static_cast<float>(F(0x12c)-30.0);
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){event(22);recovery_land(97);F(0x12c)=0.0f;layout(4.0f);reset_action_scratch();return;}
    advance();if(entry(1)){B(0x104)=static_cast<unsigned char>(-B(0x104));F(0xf4)=-3.0f;F(0xf8)=10.0f;F(0x100)=0.5f;ensure_recovery_object();}return;
case 77:
    F(0x12c)=static_cast<float>(F(0x12c)-30.0);F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){event(22);recovery_land(97);F(0x12c)=0.0f;layout(2.0f);reset_action_scratch();return;}
    if(entry(1))ensure_recovery_object();advance();return;
case 78:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){event(22);recovery_land(97);layout(2.0f);return;}
    advance();if(entry(1)){B(0x104)=static_cast<unsigned char>(-B(0x104));F(0xf4)=-5.0f;F(0xf8)=3.0f;F(0x100)=0.5f;ensure_recovery_object();}return;
case 88:
    if(static_cast<unsigned char>(crossed())){recovery_land(89);layout(5.0f);event(22);return;}
    advance();if(recovery_entry_sequence())return;
    if(--S(0x730)<0)S(0x730)=0;recovery_slide(2.5,true);return;
case 89:
    if(sequence_index_13e>0){F(0x12c)=static_cast<float>(F(0x12c)-40.0);F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){recovery_land(97);F(0x12c)=0.0f;layout(2.0f);reset_action_scratch();event(22);return;}}
    advance();if(entry(1)){F(0xf4)=static_cast<float>(S(0x730)*static_cast<double>(0.0025f));F(0xf8)=static_cast<float>(-S(0x732)*static_cast<double>(0.0025f));F(0x100)=0.25f;S(0x7a0)=0;S(0x7a2)=85;F(0x108)=static_cast<float>(S(0x7a0));F(0x10c)=static_cast<float>(S(0x7a2));}return;
case 145:
    if(entry(1))ensure_recovery_object();
    if(sequence_index_13e==1 && F(0xf8)<2.0f){next_sequence_block();return;}
    F(0xf8)-=F(0x100);if(F(0xf8)>0.0f)F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(2.0f);event(22);return;}
    if(S(0x730)>0)--S(0x730);recovery_slide(1.0,true);advance();return;
case 197:
    if(!frame_timer_142 && !frame_index_140)packet981_pair();
    if(!frame_index_140 || frame_index_140>=22)landing();
    if(recover_action())return;
    if(!frame_timer_142){if(frame_index_140==9)F(0xf4)=30.0f;if(!frame_timer_142 && frame_index_140==10){F(0xf4)=0.0f;packet981(3.0f);}if(!frame_timer_142 && frame_index_140==23)ground_face();}return;
case 198:
    if(!frame_timer_142 && !frame_index_140)packet981_pair();
    if(!frame_index_140 || frame_index_140>=22)landing();
    if(recover_action())return;
    if(!frame_timer_142){if(frame_index_140==9)F(0xf4)=-30.0f;if(!frame_timer_142 && frame_index_140==10){F(0xf4)=0.0f;packet981(3.0f);}if(!frame_timer_142 && frame_index_140==23)ground_face();}return;
case 199:
    if(!frame_index_140 || frame_index_140>=22)landing();
    if(!frame_timer_142 && !frame_index_140)packet981_pair();
    if(recover_action())return;
    if(!frame_timer_142) {
        if(frame_index_140==10 && C(0x55a)>0) {
            YukariCardDeque *deck=reinterpret_cast<YukariCardDeque *>(reinterpret_cast<unsigned char *>(this)+0x55c);
            if(B(0x72c)==2 && *deck->at(0)>=16 && *deck->at(0)<=19){B(0x113)=0;F(0xec)=640.0f;F(0xf0)=200.0f;set_action_and_finalize(750);B(0x104)=1;return;}
            packet981(3.0f);
        }
        if(!frame_timer_142 && frame_index_140==23)ground_face();
    }return;
case 200:
    landing();B(0x47e)=1;if(F(0xf4)>8.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<8.0f)F(0xf4)=8.0f;}
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=11.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        if(I(0x6b8)<0){if(I(0x6b4)*facing()<=0)set_action_and_finalize(211);else set_action_and_finalize(212);return;}
        short ticks=++S(0x730);if((I(0x6b4)*facing()<=0 && ticks>5) || ticks>60)set_action_and_finalize(204);
    }return;
case 201:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!yukari_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0x100)=0.0f;F(0xf0)=yukari_surface(this);select_sequence(3);return;}}
    if(sequence_index_13e==5 && time_counter_144>=10) {
        F(0xec)=B(0x104)==1?1240.0f:40.0f;F(0xf0)=yukari_surface(this);
        if(time_counter_144==70){float p[3]={0.0f,0.0f,1.0f};unsigned char d=B(0x104);spawn(849,static_cast<float>(200*d+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+70.0),static_cast<unsigned char>(-d),-1,p,3);}
    }
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(entry(1)){F(0xf4)=-10.0f;F(0xf8)=5.0f;F(0x100)=0.6f;dash_effects(true,80.0,false);}
    if(time_counter_144)return;
    if(!frame_timer_142 && !frame_index_140 && sequence_index_13e==4){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(!frame_timer_142 && !frame_index_140 && sequence_index_13e==5){if(B(0x104)==1)dispatch_character_wave_handle(4);else dispatch_character_wave_handle(5);float p[3]={0.0f,0.0f,0.0f};spawn(849,F(0xec),F(0xf0),B(0x104),-1,p,3);}return;
case 202:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yukari_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    advance();if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=9.0f;F(0xf8)=5.0f;F(0x100)=0.45f;dash_effects(false,110.0,true);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3)flip();return;
case 203:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yukari_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);advance();
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==1){F(0xf4)=-9.0f;F(0xf8)=5.0f;F(0x100)=0.45f;dash_effects(true,120.0,false);}if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9)flip();}return;
case 204:
    landing();F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}if(advance()){set_action_and_finalize(0);B(0x47e)=0;}return;
case 208:high_jump(0.0f,20.0f,0.65f);return;
case 209:
case 221:high_jump(9.0f,15.0f,0.65f);return;
case 210:high_jump(-9.0f,15.0f,0.65f);return;
case 211:high_jump(1.0f,18.5f,0.65f);return;
case 212:high_jump(10.0f,15.0f,0.65f);return;
case 214: {
    if(advance()){set_action_and_finalize(9);return;}
    if(entry(1))event(31);if(entry(6)){set_action_and_finalize(9);return;}
    int vertical=I(0x6b8),horizontal=I(0x6b4)*facing();
    if(vertical>0)S(0x732)=horizontal>0?-45:(horizontal<0?-135:-90);
    else if(vertical<0)S(0x732)=horizontal>0?45:(horizontal<0?135:90);
    else{if(horizontal>0)S(0x732)=0;else if(horizontal<0)S(0x732)=180;}
    if(sequence_index_13e==5 || sequence_index_13e==6)F(0xf8)-=F(0x100);
    bool retain=true;
    if(sequence_index_13e>0 && sequence_index_13e<5) {
        ++S(0x736);S(0x734)=static_cast<short>(S(0x732)-static_cast<int>(F(0x740)));
        if(S(0x734)>180)S(0x734)-=360;if(S(0x734)<-180)S(0x734)+=360;
        if(S(0x734)>0){if(I(0x4b8))F(0x740)=static_cast<float>(F(0x740)+1.0);else F(0x740)=static_cast<float>(F(0x740)+3.0);}
        if(S(0x734)<0){if(I(0x4b8))F(0x740)=static_cast<float>(F(0x740)-1.0);else F(0x740)=static_cast<float>(F(0x740)-3.0);}
        F(0xf4)=static_cast<float>(yukari_cosine(F(0x740))*F(0x73c));
        F(0xf8)=static_cast<float>(yukari_sine(F(0x740))*F(0x73c));
        if(F(0xf0)>680.0f && F(0xf8)>0.0f)F(0xf8)=0.0f;
        F(0x73c)=static_cast<float>(F(0x73c)+static_cast<double>(0.3f));if(F(0x73c)>10.0f)F(0x73c)=10.0f;
        if(I(0x4b8))counter(10,1);else counter(5,1);
        F(0x12c)=-F(0x740);if(F(0xf4)<0.0f)F(0x12c)=static_cast<float>(180.0-F(0x740));
        if(F(0xf4)<0.0f && sequence_index_13e==1)select_sequence(3);
        if(F(0xf4)>=0.0f && sequence_index_13e==3)select_sequence(1);
        if(F(0xf4)<0.0f && sequence_index_13e==2)select_sequence(4);
        if(F(0xf4)>=0.0f && sequence_index_13e==4)select_sequence(2);
        if(time_counter_144%5==1)effect(125,static_cast<float>(yukari_cosine(F(0x740))*100.0*facing()+F(0xec)),static_cast<float>(yukari_sine(F(0x740))*100.0+F(0xf0)+100.0),B(0x104),1);
        retain=(I(0x6c8) || S(0x736)<=10) && S(0x482)>0;
    }
    if(retain){if(static_cast<unsigned char>(crossed())){F(0xf0)=yukari_surface(this);F(0xf8)=0.0f;if(sequence_index_13e>=5){set_action_and_finalize(10);zero_motion();}else{reset_action_scratch();set_action_and_finalize(215);}}return;}
    reset_action_scratch();
    if(sequence_index_13e==1 || sequence_index_13e==2) {
        if(B(0x104)==1){if(peer()->at<float>(0xec)<F(0xec)){B(0x104)=255;F(0xf4)=-F(0xf4);select_sequence(6);goto yukari_release_second;}}
        else if(peer()->at<float>(0xec)>F(0xec)){B(0x104)=static_cast<unsigned char>(-B(0x104));F(0xf4)=-F(0xf4);select_sequence(6);goto yukari_release_second;}
        select_sequence(5);
    }
yukari_release_second:
    if(sequence_index_13e==3 || sequence_index_13e==4) {
        if(B(0x104)==1){if(peer()->at<float>(0xec)<F(0xec)){B(0x104)=255;F(0xf4)=-F(0xf4);select_sequence(5);return;}select_sequence(6);return;}
        if(peer()->at<float>(0xec)<=F(0xec)){select_sequence(6);return;}
        B(0x104)=static_cast<unsigned char>(-B(0x104));F(0xf4)=-F(0xf4);select_sequence(5);
    }return;
}

case 215:
    landing();if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:high_jump(0.0f,20.0f,0.65f);return;
case 222:high_jump(-9.0f,15.0f,0.65f);return;
case 223:
    landing();B(0x47e)=1;advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=5.5f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);short ticks=++S(0x730);if((I(0x6b4)*facing()<=0 && ticks>13) || ticks>60)set_action_and_finalize(204);}return;
case 224:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!yukari_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0x100)=0.0f;F(0xf0)=yukari_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(entry(1)){F(0xf4)=-10.0f;F(0xf8)=5.0f;F(0x100)=0.6f;dash_effects(true,80.0,false);}return;
case 225:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=yukari_surface(this);zero_motion();return;}
    if(frame_index_140<=7 && time_counter_144%5==0)dash_dust(true);if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){F(0xf4)=-9.0f;F(0xf8)=5.0f;F(0x100)=0.45f;dash_effects(true,120.0,false);}return;
case 226:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yukari_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=9.0f;F(0xf8)=5.0f;F(0x100)=0.45f;dash_effects(false,110.0,true);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3)flip();return;

case 300:
    landing();if(directional(0))return;if(B(0x47e))decelerate(0.5,true);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==2){event(27);B(0x47e)=0;}return;
case 301:
    landing();if(directional(0))return;if(B(0x47e))decelerate(0.5,true);if(frame_index_140>=5)decelerate(static_cast<double>(0.2f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3){F(0xf4)=2.0f;B(0x47e)=0;packet848(0.0f,1);}if(!frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);B(0x47e)=0;}}return;
case 302:
    landing();if(directional(1))return;if(B(0x47e))decelerate(0.5,true);if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2){if(B(0x750)){next_sequence_block();effect(62,static_cast<float>(F(0xec)-92*facing()),static_cast<float>(F(0xf0)+224.0),B(0x104),1);return;}F(0xf4)=10.0f;B(0x47e)=0;}
        if(!frame_timer_142 && frame_index_140==4){event(29);F(0xf4)=0.0f;}
    }
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==1){F(0xf4)=20.0f;B(0x47e)=0;}if(!frame_timer_142 && frame_index_140==3){event(29);F(0xf4)=0.0f;}}return;
case 303:
    landing();if(directional(0))return;if(C(0x47e)>0)decelerate(static_cast<double>(0.6f),true);if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==3)event(27);return;
case 304:
    landing();if(directional(1))return;if(B(0x47e))decelerate(0.5,true);if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==1)packet848(6.0f,-1);if(!frame_timer_142 && frame_index_140==4){event(29);F(0xf4)=0.0f;}}
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==1){F(0xf4)=20.0f;B(0x47e)=0;}if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);F(0xf4)=0.0f;}}return;
case 305:
    landing();if(directional(1))return;if(frame_index_140>4 && F(0xf4)>0.0f)F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)packet848(2.0f,1);if(!frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(0);}return;
case 306:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=yukari_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!frame_timer_142){if(frame_index_140==2)packet848(1.0f,1);if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(0);}return;
case 307:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=yukari_surface(this);zero_motion();return;}
    if(S(0x730)==1){F(0xf4)=static_cast<float>(F(0xf4)*static_cast<double>(0.9f));if(F(0xf4)<2.0f)F(0xf4)=2.0f;}
    if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)packet848(3.0f,1);if(!frame_timer_142 && frame_index_140==4){F(0xf4)=15.0f;F(0xf8)=0.0f;F(0x100)=0.0f;dispatch_character_wave_handle(0);S(0x730)=1;}if(!frame_timer_142 && frame_index_140==10)F(0x100)=0.5f;}return;
case 308:
    if(sequence_index_13e==1){F(0x108)=0.0f;F(0x10c)=135.0f;F(0x12c)=static_cast<float>(F(0x12c)+35.0);if(static_cast<unsigned char>(crossed())){F(0x12c)=0.0f;zero_motion();F(0xf0)=yukari_surface(this);next_sequence_block();return;}if(time_counter_144%20==0)event(29);}
    if(sequence_index_13e==2)landing();if(advance())set_action_and_finalize(0);if(entry(1)){F(0xf4)=7.5f;F(0xf8)=-7.5f;}return;
case 309:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=yukari_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!frame_timer_142){if(frame_index_140==2)packet848(2.0f,1);if(!frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(0);}return;
case 310:
    if(I(0x180)){if(++S(0x730)>5){I(0x180)=0;S(0x730)=0;}}
    if(sequence_index_13e==1){F(0xf8)=static_cast<float>(F(0xf8)-F(0x100)*0.5);F(0x12c)=static_cast<float>(F(0x12c)+40.0);F(0xf8)-=F(0x100);if(time_counter_144%15==0)event(27);double next_y=F(0xf0)+static_cast<double>(F(0xf8));if(!(yukari_surface(this)<next_y) && F(0xf8)<0.0f){F(0xf8)=0.0f;F(0xf0)=yukari_surface(this);next_sequence_block();F(0x12c)=0.0f;reset_action_scratch();return;}}
    if(sequence_index_13e==2)decelerate(1.0,false);if(advance())set_action_and_finalize(0);return;
case 320:
    landing();if(directional(0))return;if(B(0x47e))decelerate(0.5,true);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==2){event(27);B(0x47e)=0;}return;
case 321:
    landing();if(directional(0))return;if(frame_index_140>1)decelerate(2.0,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3){F(0xf4)=5.0f;B(0x47e)=0;packet848(5.0f,1);}if(!frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);B(0x47e)=0;}}return;
case 322:
    landing();if(directional(1))return;if(F(0xf4)>0.0f)F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2){F(0xf4)=10.0f;B(0x47e)=0;}if(!frame_timer_142){if(frame_index_140==3)event(29);if(!frame_timer_142 && frame_index_140==4)F(0xf4)=0.0f;}}return;

case 400:ground800();return;
case 401:ground800();return;
case 402:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(entry(0)){float p[3]={0.0f,0.0f,3.0f};spawn(800,F(0xec),F(0xf0),B(0x104),-1,p,3);}
    if(S(0x730)==1){if(!sequence_index_13e && S(0x732)%3==0 && !(F(0x740)>=5.0f)){I(0x180)=1;float p[3];for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(F(0x740)*5.0+F(0x744)-20.0+n*10.0-10.0);p[1]=10.0f;p[2]=1.0f;spawn(800,static_cast<float>((20.0+F(0x740)*15.0)*facing()+F(0xec)),static_cast<float>(F(0xf0)-20.0),B(0x104),1,p,3);}phase_counter(10);dispatch_character_wave_handle(2);F(0x740)=static_cast<float>(F(0x740)+1.0);}++S(0x732);}
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){S(0x730)=1;counter(200,45);F(0x744)=-60.0f;}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){S(0x730)=1;counter(200,45);aim800(10.0f);}return;
case 404:
    if(sequence_index_13e==2)landing();F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){S(0x730)=0;select_sequence(2);B(0x47f)=0;F(0xf0)=yukari_surface(this);zero_motion();return;}
    if(!I(0x6c0))B(0x750)=0;fan800(104.0,true);
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==2 && B(0x750)){charge800();return;}if(frame_index_140==3){S(0x730)=1;aim800(30.0f);}}if(!frame_timer_142 && frame_index_140==8)F(0x100)=0.6f;}
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==2){S(0x730)=1;aim800(30.0f);}if(!frame_timer_142 && frame_index_140==7)F(0x100)=0.6f;}return;
case 406:
    if(sequence_index_13e==2)landing();F(0xf8)-=F(0x100);
    if(!sequence_index_13e && frame_index_140>=11 && static_cast<unsigned char>(crossed()) && sequence_index_13e<2){S(0x730)=0;select_sequence(2);B(0x47f)=0;F(0xf0)=yukari_surface(this);zero_motion();return;}
    if(entry(0)){float p[3]={0.0f,0.0f,3.0f};spawn(800,F(0xec),static_cast<float>(F(0xf0)+30.0),B(0x104),-1,p,3);}
    if(!I(0x6c0))B(0x750)=0;
    if(S(0x730)==1){if(!sequence_index_13e && S(0x732)%3==0 && !(F(0x740)>=5.0f)){if(F(0x740)==0.0f)counter(200,45);I(0x180)=1;float p[3];for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(F(0x744)-F(0x740)*10.0+n*10.0-10.0);p[1]=10.0f;p[2]=2.0f;spawn(800,static_cast<float>((F(0x740)*15.0+20.0)*facing()+F(0xec)),static_cast<float>(F(0xf0)+40.0),B(0x104),1,p,3);}phase_counter(10);dispatch_character_wave_handle(2);F(0x740)=static_cast<float>(F(0x740)+1.0);}++S(0x732);}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==5){S(0x730)=1;F(0x744)=80.0f;}if(!frame_timer_142 && frame_index_140==12)F(0x100)=0.6f;}return;
case 408:
    if(frame_index_140<10)F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.1f));else{F(0xf4)=static_cast<float>(F(0xf4)-1.0);landing();}
    if(F(0xf4)<0.0f)F(0xf4)=0.0f;if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)packet848(1.0f,1);if(!frame_timer_142 && frame_index_140==5)event(29);}return;
case 410:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){I(0x180)=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);fan801(177,90.0,90.0f);}return;
case 411:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){I(0x180)=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);split801(177,90.0);}return;
case 412:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){counter(200,60);I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(3);float p[4];for(float n=0.0f;n<5.0f;n=static_cast<float>(n+1.0)){p[0]=0.0f;p[1]=10.0f;p[2]=p[0];p[3]=static_cast<float>(n*5.0+10.0);spawn_offset(801,75,50.0,p,4);}}
    if(sequence_index_13e==1 && time_counter_144>20)next_sequence_block();return;
case 414:
    if(sequence_index_13e==1)landing();if(sequence_index_13e<1 && frame_index_140>=4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yukari_surface(this);select_sequence(1);return;}}
    if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){I(0x180)=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);F(0xf4)=-5.0f;F(0xf8)=7.5f;F(0x100)=0.5f;fan801(75,85.0,90.0f);}return;
case 415:
    if(sequence_index_13e==1)landing();if(sequence_index_13e<1 && frame_index_140>=4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yukari_surface(this);select_sequence(1);return;}}
    if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){I(0x180)=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);F(0xf4)=-5.0f;F(0xf8)=7.5f;F(0x100)=0.5f;split801(75,85.0);}return;
case 416:
    if(sequence_index_13e==1)landing();if(sequence_index_13e<1 && frame_index_140>=4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yukari_surface(this);select_sequence(1);return;}}
    if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){I(0x180)=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);F(0xf4)=-5.0f;F(0xf8)=7.5f;F(0x100)=0.5f;fan801(75,85.0,120.0f);}return;
case 418:
    landing();B(0x47e)=0;decelerate(0.5,false);if(!I(0x6bc))B(0x750)=0;if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==1)packet848(6.0f,-1);if(!frame_timer_142 && frame_index_140==3)event(29);}
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==1){F(0xf4)=20.0f;B(0x47e)=0;}if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);F(0xf4)=0.0f;}}return;

case 500:ground810(0x6c0,3,300);return;
case 501:ground810(0x6c4,4,600);return;
case 502:air810(0x6c0,300);return;
case 503:air810(0x6c4,600);return;
case 505:ground811(0x6c0);return;
case 506:ground811(0x6c4);return;
case 510:ground812(0x6c0,200,120.0);return;
case 511:ground812(0x6c4,400,360.0);return;
case 520:
    if(!sequence_index_13e || sequence_index_13e==4)landing();B(0x17c)=1;
    if(!sequence_index_13e && C(0x605)>=4)S(0x4a8)=2;
    if(sequence_index_13e>=1 && sequence_index_13e<=3){F(0xf8)-=F(0x100);if(sequence_index_13e==1){if(time_counter_144%12==0)event(29);F(0x12c)=static_cast<float>(F(0x12c)-40.0);if(F(0xf8)<10.0f)F(0xf8)=10.0f;if(I(0x180)){if(++S(0x730)>=6){I(0x180)=0;S(0x730)=0;}}}if(static_cast<unsigned char>(crossed())){reset_action_scratch();F(0xf0)=yukari_surface(this);zero_motion();select_sequence(4);}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){counter(200,120);phase_counter(50);F(0x108)=0.0f;F(0x10c)=135.0f;if(C(0x605)>=4)S(0x4a8)=5;float p[3]={0.0f,0.0f,1.0f};spawn_offset(815,0,135.0,p,3);F(0xf8)=20.0f;F(0x100)=0.75f;dispatch_character_wave_handle(12);}
    if(entry(2))reset_action_scratch();return;
case 521:
    landing();B(0x17c)=1;
    if(sequence_index_13e==1 || sequence_index_13e==2){if(time_counter_144%12==0)event(29);F(0x12c)=static_cast<float>(F(0x12c)-40.0);if(I(0x180) && sequence_index_13e==1 && ++S(0x730)>=6){I(0x180)=0;S(0x730)=0;}}
    decelerate(0.75,false);if(advance())set_action_and_finalize(0);
    if(entry(1)){counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(815,0,135.0,p,3);F(0x108)=0.0f;F(0x10c)=135.0f;F(0xf4)=20.0f;dispatch_character_wave_handle(12);}
    if(entry(3))reset_action_scratch();return;
case 522:air802(12.0f,135.0f,37825.0f,225.0f,65025.0f);return;
case 523:air802(25.0f,330.0f,128500.0f,420.0f,190800.0f);return;
case 525:hold816(0x6c0,0.0f);return;
case 526:hold816(0x6c4,-45.0f);return;
case 540:projectile820(false,0.0f,13);return;
case 541:projectile820(false,3.0f,14);return;
case 542:projectile820(true,0.0f,13);return;
case 543:projectile820(true,3.0f,14);return;
case 545:projectile821(false);return;
case 546:projectile821(false);return;
case 547:projectile821(true);return;
case 548:projectile821(true);return;
case 560:ground825();return;
case 561:diving825();return;
case 562:ground825();return;
case 563:diving825();return;
case 565:
    B(0x17c)=7;if(sequence_index_13e==3)landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))F(0xf4)=30.0f;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==1)opening826();if(!frame_timer_142 && frame_index_140==5){packet826(5.0f);dispatch_character_wave_handle(5);}}
    if(sequence_index_13e==1){if(!frame_index_140){if(I(0x6b4)*facing()>0)F(0xf4)=6.0f;if(I(0x6b4)*facing()<0)F(0xf4)=-6.0f;if(!I(0x6b4))F(0xf4)=0.0f;if(time_counter_144>=15 && !B(0x750))next_sequence_frame();}if(!frame_timer_142){if(!frame_index_140)packet826(6.0f);if(!frame_timer_142 && frame_index_140==1)launch826(9.0f);}}
    if(sequence_index_13e==2)falling826();return;
case 566:
    B(0x17c)=7;if(sequence_index_13e==3)landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==1)opening826();if(!frame_timer_142 && frame_index_140==5){packet826(5.0f);dispatch_character_wave_handle(5);}}
    if(sequence_index_13e==1){if(!frame_timer_142 && !frame_index_140)packet826(6.0f);
        if(!frame_index_140){if(frame_timer_142<75){if(I(0x6b4)*facing()>0)F(0xf4)=6.0f;if(I(0x6b4)*facing()<0)F(0xf4)=-6.0f;if(!I(0x6b4))F(0xf4)=0.0f;if(frame_timer_142>=15 && !B(0x750))frame_timer_142=75;}if(frame_timer_142==75)launch826(10.0f);}
        if(frame_index_140==1){F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>15.0f)F(0xf4)=15.0f;interval_clear();}}
    if(sequence_index_13e==2)falling826();return;

case 600:simple_spell(850,2,-55,122.0,3,5,150,145.0,50);return;
case 601:simple_spell(851,3,0,100.0,3,4,75,135.0,51);return;
case 602:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2)spell_flash(34,152.0,1);
        if(!frame_timer_142){if(frame_index_140==4 && I(0x6b4)*facing()<0){next_sequence_block();return;}if(frame_index_140==6){float p[3]={0.0f,14.0f,0.0f};spawn(852,F(0xec),0.0f,B(0x104),1,p,3);dispatch_character_wave_handle(56);}}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,14.0f,0.0f};spawn(852,F(0xec),0.0f,static_cast<unsigned char>(-B(0x104)),1,p,3);dispatch_character_wave_handle(56);}return;
case 603:simple_spell(853,2,-55,122.0,4,5,150,145.0,50);return;
case 604:simple_spell(854,3,0,100.0,1,4,75,135.0,51);return;
case 605:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(34,152.0,3);
        if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,20.0f,0.0f};spawn(855,static_cast<float>(100*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+115.0),1,1,p,3);
            p[0]=90.0f;spawn(855,static_cast<float>(100*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+115.0),1,1,p,3);
            p[0]=-90.0f;spawn(855,static_cast<float>(100*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+115.0),1,1,p,3);
            p[0]=180.0f;spawn(855,static_cast<float>(100*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+115.0),1,1,p,3);dispatch_character_wave_handle(56);}}return;
case 606:
    texture(2,2);if(sequence_index_13e==1 && time_counter_144>=40){next_sequence_block();return;}
    shower856();if(sequence_index_13e==2 && time_counter_144>=80){next_sequence_block();return;}
    if(advance()){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){spell_flash(-114,172.0,3);S(0x730)=1;}return;
case 607:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(S(0x730)==1){if(S(0x732)%5==0){if(S(0x734)<4){dispatch_character_wave_handle(21);float p[3]={0.0f,0.0f,0.0f};float x,y;
        if(S(0x734)){x=static_cast<float>(static_cast<float>(yukari_random(640))+peer()->at<float>(0xec));if(x>1200.0f)x=1200.0f;else if(x<80.0f)x=80.0f;y=static_cast<float>(static_cast<float>(yukari_random(480))-140.0);if(y<-50.0f)y=-50.0f;else if(y>680.0f)y=680.0f;}
        else{y=static_cast<float>(peer()->at<float>(0xf0)+100.0);x=peer()->at<float>(0xec);}spawn(857,x,y,B(0x104),1,p,3);}++S(0x734);}++S(0x732);}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4)spell_flash(-8,141.0,2);if(!frame_timer_142 && frame_index_140==5)S(0x730)=1;}return;
case 615:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3)spell_flash(-43,150.0,5);if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,0.0f,0.0f};spawn(865,static_cast<float>(F(0xec)-150*facing()),200.0f,B(0x104),-2,p,3);dispatch_character_wave_handle(53);}}return;
case 656:
    if(sequence_index_13e<=3)texture(2,2);if(sequence_index_13e==5)landing();
    if(sequence_index_13e==3 || sequence_index_13e==4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(5);F(0xf0)=yukari_surface(this);zero_motion();return;}}
    if(sequence_index_13e==1 && time_counter_144>=40){next_sequence_block();return;}shower856();if(sequence_index_13e==2 && time_counter_144>=80){next_sequence_block();return;}
    if(advance()){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){spell_flash(-114,172.0,3);S(0x730)=1;}
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==4)F(0x100)=0.25f;return;

case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){event(55);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(141,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1);effect(142,F(0xec),F(0xf0),B(0x104),-1);}return;
case 696:
    landing();if(frame_index_140>1)decelerate(2.0,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3){F(0xf4)=5.0f;B(0x47e)=0;}if(!frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);B(0x47e)=0;}}return;
case 710:
    if(sequence_index_13e>=1 && sequence_index_13e<=3){F(0xf4)=static_cast<float>(F(0xf4)*static_cast<double>(0.98f));F(0xf8)-=F(0x100);if(F(0xf8)<0.0f && !S(0x730)){F(0xf8)=0.0f;S(0x730)=1;}}
    if(sequence_index_13e==3){if(F(0xf8)<0.0f)F(0xf8)=0.0f;if(S(0x730)==1){if(S(0x732)>=390){next_sequence_block();F(0x100)=0.15f;return;}switch(g_match_identifier){case 0:difficulty900(90,0);break;case 1:difficulty900(72,3);break;case 2:difficulty900(72,2);break;case 3:difficulty900(60,2);break;}++S(0x732);}}
    if(sequence_index_13e==4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){next_sequence_block();return;}}
    if(advance())set_action_and_finalize(700);if(entry(1)){F(0xf4)=static_cast<float>(static_cast<float>(yukari_random(10))-5.0);F(0xf8)=10.0f;F(0x100)=0.25f;}return;
case 720:
    if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(700);if(entry(1))F(0xf4)=30.0f;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==1)opening910();if(!frame_timer_142 && frame_index_140==5){packet910(5.0f);dispatch_character_wave_handle(5);}}
    if(sequence_index_13e==1){if(!frame_index_140){if(!frame_timer_142){F(0xf4)=static_cast<float>((peer()->at<float>(0xec)-F(0xec))*static_cast<double>(facing())/60.0);F(0xf8)=0.0f;}if(frame_timer_142==60)F(0xf4)=0.0f;switch(g_match_identifier){case 0:if(time_counter_144>=90){next_sequence_frame();F(0xf4)=0.0f;}break;case 1:case 2:if(time_counter_144>=70){next_sequence_frame();F(0xf4)=0.0f;}break;case 3:if(time_counter_144>=60){next_sequence_frame();F(0xf4)=0.0f;}break;}}
        if(!frame_timer_142){if(!frame_index_140)packet910(6.0f);if(!frame_timer_142 && frame_index_140==1)launch910(9.0f);}}
    if(sequence_index_13e==2){if(!S(0x738)){float p[3];switch(g_match_identifier){case 1:burst910(p,13,-60.0,60,70,5.0);break;case 2:burst910(p,18,-50.0,80,80,8.0);break;case 3:burst910(p,23,-40.0,100,100,10.0);break;}}falling826();}return;
case 721:
    if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==1)opening910();if(!frame_timer_142 && frame_index_140==5){packet910(5.0f);dispatch_character_wave_handle(5);}}
    if(sequence_index_13e==1){if(!frame_timer_142 && !frame_index_140){F(0xf8)=0.0f;float choice=static_cast<float>(yukari_random(3));if(choice==0.0f)F(0xf0)=0.0f;if(choice==1.0f)F(0xf0)=200.0f;if(choice==2.0f)F(0xf0)=400.0f;packet910(6.0f);}
        if(!frame_index_140){if(frame_timer_142<10)F(0xf4)=7.0f;if(frame_timer_142==10)launch910(10.0f,7.0f);}if(frame_index_140==1)interval_clear();}
    if(sequence_index_13e==2)falling826();return;
case 730:
    F(0xf4)=static_cast<float>(F(0xf4)*static_cast<double>(0.98f));F(0xf8)=static_cast<float>(static_cast<double>(0.98f)*F(0xf8));
    if(sequence_index_13e==1 && time_counter_144>=120){next_sequence_block();return;}
    if(advance()){set_action_and_finalize(704);S(0x7c0)=static_cast<short>(yukari_random(60)+120);return;}
    if(entry(1)){switch(g_match_identifier){case 0:S(0x7be)=180;break;case 1:S(0x7be)=210;break;case 2:S(0x7be)=240;break;case 3:S(0x7be)=270;break;}}
    if(entry(3)){double y=F(0xf0);if(yukari_surface(this)>=y){zero_motion();set_action_and_finalize(700);S(0x7c0)=static_cast<short>(yukari_random(60)+120);}}return;
case 740:
    landing();if(advance())set_action_and_finalize(700);if(entry(1)){set_action_and_finalize(0);return;}
    if(S(0x730)==1){if(S(0x732)%5==0){int limit;switch(g_match_identifier){case 0:case 1:limit=3;break;case 2:limit=4;break;case 3:limit=5;break;}
        // Native invalid-difficulty path reads an uninitialized local (588718).
        if(S(0x734)<static_cast<short>(limit)){dispatch_character_wave_handle(21);float p[3]={0.0f,0.0f,0.0f};float x,y;
            if(S(0x734)){x=static_cast<float>(static_cast<float>(yukari_random(640))+peer()->at<float>(0xec));if(x>1200.0f)x=1200.0f;else if(x<80.0f)x=80.0f;y=static_cast<float>(static_cast<float>(yukari_random(480))-140.0);if(y<-50.0f)y=-50.0f;else if(y>680.0f)y=680.0f;}
            else{y=static_cast<float>(peer()->at<float>(0xf0)+100.0);x=peer()->at<float>(0xec);}spawn(930,x,y,B(0x104),1,p,3);}++S(0x734);}++S(0x732);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5)S(0x730)=1;return;
case 741:
    landing();if(advance())set_action_and_finalize(700);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){switch(g_match_identifier){case 0:S(0x7c4)=45;break;case 1:S(0x7c4)=80;break;case 2:S(0x7c4)=115;break;case 3:S(0x7c4)=150;break;}S(0x7c6)=0;}return;
case 750:
    F(0xec)=640.0f;F(0xf0)=200.0f;
    if(!S(0x730)){if(!sequence_index_13e)select_sequence(1);if(++S(0x732)==60)finish_story_state();if(S(0x732)>=60){unsigned char alpha=B(0x113);if(alpha>250){B(0x113)=255;S(0x730)=1;S(0x732)=0;}else B(0x113)=static_cast<unsigned char>(alpha+5);}}
    if(S(0x730)==1)++S(0x732);if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1 && !frame_index_140 && !frame_timer_142 && S(0x730)==1 && S(0x732)>=60)next_sequence_block();return;
case 770:
    if(advance())set_action_and_finalize(700);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)finish_story_state();return;
case 771:
    if(B(0x113)<5){B(0x113)=0;F(0xec)=640.0f;F(0xf0)=200.0f;B(0x104)=1;set_action_and_finalize(750);}else{B(0x113)=static_cast<unsigned char>(B(0x113)-5);if(advance())set_action_and_finalize(700);}return;
case 794:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4){float p[3]={0.0f,0.0f,1.0f};spawn(899,F(0xec),F(0xf0),B(0x104),-1,p,3);p[1]=0.5f;p[2]=4.0f;spawn(899,F(0xec),F(0xf0),B(0x104),-1,p,3);p[2]=4.0f;p[1]=0.25f;spawn(899,F(0xec),F(0xf0),B(0x104),-1,p,3);dispatch_character_wave_handle(1);}if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,0.0f,5.0f};spawn(899,F(0xec),F(0xf0),B(0x104),1,p,3);dispatch_character_wave_handle(5);}}return;
case 795:
    if(!sequence_index_13e){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.3f));if(static_cast<unsigned char>(crossed())){select_sequence(1);F(0xf0)=yukari_surface(this);zero_motion();event(30);return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:
    F(0xf4)=2.5f;if(sequence_index_13e==1 && F(0xec)>=480.0f){F(0xec)=480.0f;zero_motion();set_action_and_finalize(0);}else if(advance())set_action_and_finalize(0);return;
case 798:
    F(0xf4)=2.5f;if(sequence_index_13e==1 && F(0xec)<=800.0f){F(0xec)=800.0f;zero_motion();set_action_and_finalize(700);}else if(advance())set_action_and_finalize(700);return;

default:common_update();return;
}
}
#undef B
#undef C
#undef S
#undef U
#undef I
#undef F
}
