#include "characters/YuyukoActionState.hpp"
// Complete JP1.06a55D850 candidate, not selected or exact.
// See docs/YUYUKO_ACTION_STATE_2026_10_28.md.
namespace th105 {
#define B(o) at<unsigned char>(o)
#define C(o) at<signed char>(o)
#define S(o) at<short>(o)
#define U(o) at<unsigned>(o)
#define I(o) at<int>(o)
#define F(o) at<float>(o)
void YuyukoActionStateView::dispatch_action_state_vslot28()
{
    S(0x7a0)=0;S(0x7a2)=90;
    if(action_id_13c>149 && action_id_13c<159 && !B(0x751)) {
        B(0x751)=1;
        if(action_id_13c>149 && action_id_13c<154)spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+94.0),B(0x104),1,0,0);
        if(action_id_13c>153 && action_id_13c<158)spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+60.0),B(0x104),1,0,0);
        if(action_id_13c==158)spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+100.0),B(0x104),1,0,0);
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
case 4:landing();F(0xf4)=4.0f;advance();return;
case 5:landing();F(0xf4)=-4.0f;advance();return;
case 6:normal_jump(0.0f);return;
case 7:normal_jump(4.0f);return;
case 8:normal_jump(-4.0f);return;
case 9:
    if(F(0x100)==0.0f)F(0x100)=0.6f;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=yuyuko_surface(this);zero_motion();return;}
    advance();return;
case 10:
    landing();zero_motion();if(advance()){if(!I(0x6b8)){set_action_and_finalize(0);return;}set_action_and_finalize(2);}return;
case 197: {
    const bool forward=true;
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=yuyuko_surface(this);zero_motion();select_sequence(3);return;}}
    if(advance()) {
        if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);
    }
    if(sequence_index_13e==3 && frame_index_140==2 && !frame_timer_142)ground_face();
    if(entry(1)){F(0xf8)=8.0f;F(0xf4)=forward?11.5f:-11.5f;F(0x100)=0.5f;}
    return;
}
case 198: {
    const bool forward=false;
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=yuyuko_surface(this);zero_motion();select_sequence(3);return;}}
    if(advance()) {
        if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);
    }
    if(sequence_index_13e==3 && frame_index_140==2 && !frame_timer_142)ground_face();
    if(entry(1)){F(0xf8)=8.0f;F(0xf4)=forward?11.5f:-11.5f;F(0x100)=0.5f;}
    return;
}
case 199:
    landing();
    if(advance()) {
        if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(2);if(I(0x6b8)>0)set_action_and_finalize(1);
    }
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)ground_face();return;
case 200:
    landing();B(0x47e)=1;
    if(F(0xf4)>6.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<6.0f)F(0xf4)=6.0f;}
    advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        if(I(0x6b8)<0){if(I(0x6b4)*facing()>0){set_action_and_finalize(212);return;}set_action_and_finalize(211);return;}
        short ticks=++S(0x730);
        if((I(0x6b4)*facing()<=0 && ticks>5) || ticks>60){set_action_and_finalize(204);return;}
    }
    if(entry(1)){F(0xf4)=15.0f;dash_effects(false,80.0,true);}return;
case 201:
    if(!sequence_index_13e || sequence_index_13e==4)landing();
    if(!yuyuko_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<4) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);select_sequence(4);return;}
    }
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(entry(1)){F(0xf4)=-10.0f;F(0xf8)=2.0f;F(0x100)=0.2f;dash_effects(true,80.0,false);}return;
case 202: {
    bool recovery=false;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    if(advance() && recovery)set_action_and_finalize(9);
    if(entry(1)){S(0x730)=0;F(0xf4)=7.5f;F(0xf8)=3.5f;F(0x100)=0.45f;dash_effects(false,110.0,true);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==5)flip();return;
}
case 203:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<2 && time_counter_144%5==0)dash_dust(true);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1){F(0xf4)=-7.5f;F(0xf8)=3.5f;F(0x100)=0.45f;dash_effects(true,120.0,false);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2)flip();return;
case 204:
    landing();F(0xf4)=static_cast<float>(F(0xf4)-0.5);
    if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    if(advance()){set_action_and_finalize(0);B(0x47e)=0;}return;
case 208:high_jump(0.0f,18.5f,0.55f);return;
case 211:high_jump(2.0f,18.5f,0.55f);return;
case 214: {
    if(advance()){set_action_and_finalize(9);return;}
    if(entry(1)) {
        event(31);
        if(F(0x740)>=135.0f || F(0x740)<=-135.0f){select_sequence(6);return;}
        if(F(0x740)>45.0f || F(0x740)<-45.0f){select_sequence(4);return;}
    }
    if(entry(9))select_sequence(5);
    if(entry(10) || entry(11)){set_action_and_finalize(9);return;}
    int vertical=I(0x6b8),horizontal=I(0x6b4)*facing();
    if(vertical>0)S(0x732)=horizontal>0?-45:(horizontal<0?-135:-90);
    else if(vertical<0)S(0x732)=horizontal>0?45:(horizontal<0?135:90);
    else {if(horizontal>0)S(0x732)=0;else if(horizontal<0)S(0x732)=180;}
    if(sequence_index_13e==9 || sequence_index_13e==10 || sequence_index_13e==11)F(0xf8)-=F(0x100);
    bool retain=true;
    if(sequence_index_13e>0 && sequence_index_13e<9) {
        ++S(0x736);
        S(0x734)=static_cast<short>(S(0x732)-static_cast<int>(F(0x740)));
        if(S(0x734)>180)S(0x734)-=360;
        if(S(0x734)<-180)S(0x734)+=360;
        if(F(0x740)>180.0f)F(0x740)=static_cast<float>(F(0x740)-360.0);
        if(F(0x740)<-180.0f)F(0x740)=static_cast<float>(F(0x740)+360.0);
        if(S(0x734)>0) {
            if(I(0x4b8))F(0x740)=static_cast<float>(F(0x740)+5.0);
            else F(0x740)=static_cast<float>(F(0x740)+6.0);
        }
        if(S(0x734)<0) {
            if(I(0x4b8))F(0x740)=static_cast<float>(F(0x740)-5.0);
            else F(0x740)=static_cast<float>(F(0x740)-6.0);
        }
        F(0xf4)=static_cast<float>(yuyuko_cosine(F(0x740))*F(0x73c));
        F(0xf8)=static_cast<float>(yuyuko_sine(F(0x740))*F(0x73c));
        if(F(0xf0)>680.0f && F(0xf8)>0.0f)F(0xf8)=0.0f;
        if(I(0x4b8))counter(8,1);else counter(4,1);
        short seq=sequence_index_13e;
        if((seq==1 || seq==2) && (F(0x740)>60.0f || F(0x740)<-60.0f)){select_sequence(3);return;}
        if(seq==4 || seq==5) {
            if(F(0x740)<=45.0f && F(0x740)>=-45.0f){select_sequence(1);return;}
            if(F(0x740)>=135.0f || F(0x740)<=-135.0f){select_sequence(6);return;}
        }
        if((seq==6 || seq==7) && F(0x740)<120.0f && F(0x740)>-120.0f){select_sequence(8);return;}
        int held=I(0x6c8);
        retain=((held || S(0x736)<=10) && S(0x482)>0) ||
               ((held || S(0x736)<=10) && S(0x482)>0);
    }
    if(retain) {
        if(static_cast<unsigned char>(crossed())) {
            F(0xf0)=yuyuko_surface(this);F(0xf8)=0.0f;F(0x100)=0.0f;
            if(sequence_index_13e>=9){set_action_and_finalize(10);zero_motion();}
            else {reset_action_scratch();set_action_and_finalize(215);}
        }
        return;
    }
    if(sequence_index_13e==1 || sequence_index_13e==2)release_flight(9);
    if(sequence_index_13e==3) {
        S(0x730)=frame_index_140;
        if(B(0x104)==1) {
            if(peer()->at<float>(0xec)<F(0xec)) {
                B(0x104)=255;goto flight_frame_turn;
            }
        } else if(peer()->at<float>(0xec)>F(0xec)) {
            B(0x104)=static_cast<unsigned char>(-B(0x104));goto flight_frame_turn;
        }
        select_sequence(9);
        set_sequence_frame(static_cast<unsigned short>(S(0x730)));
        goto flight_frame_done;
flight_frame_turn:
        F(0xf4)=-F(0xf4);select_sequence(9);
        set_sequence_frame(static_cast<unsigned short>(S(0x730)));
    }
flight_frame_done:
    if(sequence_index_13e==4 || sequence_index_13e==5)release_flight(10);
    if(sequence_index_13e==6 || sequence_index_13e==7)release_flight(11);
    if(sequence_index_13e==8) {
        S(0x730)=frame_index_140;
        if(B(0x104)==1) {
            if(peer()->at<float>(0xec)<F(0xec)) {
                B(0x104)=255;F(0xf4)=-F(0xf4);
                select_sequence(11);
                set_sequence_frame(static_cast<unsigned short>(S(0x730)));return;
            }
            select_sequence(11);
            set_sequence_frame(static_cast<unsigned short>(S(0x730)));return;
        }
        if(peer()->at<float>(0xec)>F(0xec)) {
            B(0x104)=static_cast<unsigned char>(-B(0x104));F(0xf4)=-F(0xf4);
            select_sequence(11);
            set_sequence_frame(static_cast<unsigned short>(S(0x730)));return;
        }
        select_sequence(11);
        set_sequence_frame(static_cast<unsigned short>(S(0x730)));return;
    }
    return;
}

case 215:
    landing();
    if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:high_jump(0.0f,18.5f,0.55f);return;
case 209:
case 212:
case 221:high_jump(10.0f,13.5f,0.5f);return;
case 210:
case 222:high_jump(-10.0f,13.5f,0.5f);return;
case 223:
    landing();B(0x47e)=1;
    if(F(0xf4)>6.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<6.0f)F(0xf4)=6.0f;}
    advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);short ticks=++S(0x730);if((I(0x6b4)*facing()<=0 && ticks>15)||ticks>60){set_action_and_finalize(204);return;}}
    if(entry(1)){F(0xf4)=7.5f;dash_effects(false,80.0,true);}return;
case 224:
    if(!sequence_index_13e || sequence_index_13e==4)landing();
    if(!yuyuko_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<4) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);select_sequence(4);return;}
    }
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(entry(1)){F(0xf4)=-10.0f;F(0xf8)=2.0f;F(0x100)=0.2f;dash_effects(true,80.0,false);}return;
case 225:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==1){F(0xf4)=-7.5f;F(0xf8)=3.5f;F(0x100)=0.45f;dash_effects(true,120.0,false);}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9)flip();
    }return;

case 226: {
    bool recovery=true;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    if(advance() && recovery)set_action_and_finalize(9);
    if(entry(1)){S(0x730)=0;F(0xf4)=7.5f;F(0xf8)=3.5f;F(0x100)=0.45f;dash_effects(false,110.0,true);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==5)flip();return;
}
case 300:
    landing();if(directional(0))return;
    if(B(0x47e))decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)mode848(1.0f);if(!frame_timer_142 && frame_index_140==3){event(28);B(0x47e)=0;}}return;
case 301:
    landing();if(directional(0))return;
    if(B(0x47e))decelerate(0.5,true);
    if(frame_index_140>=5)decelerate(static_cast<double>(0.15f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2){F(0xf4)=4.0f;B(0x47e)=0;mode848(3.0f);}if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);B(0x47e)=0;}}return;
case 302:
    landing();if(directional(1))return;
    if(B(0x47e))decelerate(0.5,true);
    if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142) {
            if(frame_index_140==4){if(B(0x750)){charge_flash(-43,162.0);return;}mode848(4.0f);F(0xf4)=10.0f;B(0x47e)=0;}
            if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(0);
        }
        if(frame_index_140>=6)decelerate(static_cast<double>(1.2f),false);
    }
    if(sequence_index_13e==1) {
        if(!frame_timer_142) {
            if(frame_index_140==1){F(0xf4)=10.0f;B(0x47e)=0;mode848(4.0f);}
            if(!frame_timer_142 && frame_index_140==2)dispatch_character_wave_handle(0);
        }
        if(frame_index_140>=3)decelerate(static_cast<double>(1.2f),false);
    }return;
case 303:
    landing();if(directional(0))return;
    if(C(0x47e)>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==1){event(28);mode848(2.0f);}return;
case 304:
    landing();if(directional(1))return;
    if(C(0x47e)>0)decelerate(static_cast<double>(0.6f),true);
    if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(2);
    if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142) {
            if(frame_index_140==3)mode848(5.0f);
            if(!frame_timer_142 && frame_index_140==3){if(B(0x750)){charge_flash(-20,50.0);return;}F(0xf4)=2.0f;event(29);}
        }
        if(frame_index_140>=5)decelerate(static_cast<double>(0.15f),true);
    }
    if(sequence_index_13e==1) {
        if(!frame_timer_142) {
            if(frame_index_140==1){F(0xf4)=2.0f;event(29);}
            if(!frame_timer_142 && frame_index_140==1)mode848(5.0f);
        }
        if(frame_index_140>=3)decelerate(static_cast<double>(0.15f),true);
    }return;
case 305:
    landing();if(directional(1))return;decelerate(static_cast<double>(0.2f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==1)mode848(10.0f,-40,120.0);if(!frame_timer_142 && frame_index_140==2)event(28);}return;
case 306:
    if(air_landing())return;if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)event(28);if(!frame_timer_142 && frame_index_140==2)mode848(6.0f);}return;
case 307:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<2.0f)F(0xf4)=2.0f;
    if(air_landing())return;if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==1){F(0xf4)=12.5f;F(0xf8)=10.0f;F(0x100)=0.5f;}
        if(!frame_timer_142 && frame_index_140==2)mode848(7.0f);
        if(!frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(0);
        if(!frame_timer_142 && frame_index_140==8)F(0x100)=0.6f;
    }return;
case 308:
    if(!I(0x6bc))B(0x750)=0;if(air_landing())return;if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4)mode848(8.0f);
        if(!frame_timer_142 && frame_index_140==5)event(29);
        if(!frame_timer_142 && frame_index_140==6)I(0x180)=0;
        if(!frame_timer_142 && frame_index_140==7)I(0x180)=0;
        if(!frame_timer_142 && frame_index_140==8)I(0x180)=0;
    }return;
case 309:
    if(air_landing())return;if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2){F(0xf4)=static_cast<float>(F(0xf4)*0.5);F(0xf8)=5.0f;F(0x100)=0.5f;event(29);}
        if(!frame_timer_142 && frame_index_140==7)F(0x100)=0.5f;
    }return;
case 310:
    if(I(0x180) && ++S(0x730)>5){I(0x180)=0;S(0x730)=0;}
    if(sequence_index_13e==1) {
        if(!time_counter_144)F(0xf4)=15.0f;
        if(time_counter_144%8==0)event(27);
        if(I(0x180) && ++S(0x730)>5){I(0x180)=0;S(0x730)=0;}
        if(time_counter_144>30){next_sequence_block();F(0xf8)=6.0f;F(0xf4)=static_cast<float>(F(0xf4)*0.5);}
    }
    if(sequence_index_13e==2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0xf0)=yuyuko_surface(this);set_action_and_finalize(9);return;}}
    if(advance())set_action_and_finalize(9);return;
case 320:
    landing();if(directional(0))return;
    if(B(0x47e))decelerate(0.5,true);
    if(frame_index_140>=5)decelerate(static_cast<double>(0.15f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2){F(0xf4)=4.0f;B(0x47e)=0;mode848(3.0f);}if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);B(0x47e)=0;}}return;
case 321:
    landing();if(directional(1))return;
    if(frame_index_140>3)decelerate(static_cast<double>(0.3f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)F(0xf4)=4.5f;if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);B(0x47e)=0;mode848(12.0f);}}return;
case 322:
    landing();if(directional(1))return;
    if(frame_index_140>=4)decelerate(static_cast<double>(0.2f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3)F(0xf4)=4.0f;if(!frame_timer_142 && frame_index_140==4)dispatch_character_wave_handle(0);}return;

case 400:ground_fan(4,true);return;
case 401:ground_fan(3,false);return;
case 402:
    if(frame_index_140<=1 || frame_index_140>=7)landing();
    if(!I(0x6c0))B(0x750)=0;
    if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(S(0x730)==1) {
        if(S(0x732)%3==0 && S(0x734)<4) {
            float p[3];
            for(int n=0;n<30;n+=10){p[0]=static_cast<float>(-20*S(0x734));p[1]=static_cast<float>(n+10.0);p[2]=static_cast<float>(S(0x734)+12.0);spawn(800,F(0xec),static_cast<float>(yuyuko_sine(static_cast<float>(20*S(0x734)))*150.0+F(0xf0)+50.0),B(0x104),1,p,3);}
            for(int n=4;n;--n){p[0]=static_cast<float>(yuyuko_random(360));p[1]=static_cast<float>(static_cast<float>(yuyuko_random(50))*static_cast<double>(0.1f)+5.0);p[2]=static_cast<float>(S(0x734)+4.0);spawn(800,F(0xec),static_cast<float>(yuyuko_sine(static_cast<float>(20*S(0x734)))*150.0+F(0xf0)+50.0),B(0x104),1,p,3);}
            ++S(0x734);
        }
        ++S(0x732);
    }
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)F(0xf4)=-15.0f;if(!frame_timer_142 && frame_index_140==3){I(0x180)=1;counter(200,45);phase_counter(50);S(0x730)=1;dispatch_character_wave_handle(1);}}return;
case 404:air_fan();return;
case 406:air_fan();return;
case 408:
    landing();decelerate(0.5,false);if(!I(0x6bc))B(0x750)=0;
    if(advance()){set_action_and_finalize(0);B(0x47e)=0;}
    if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==4){mode848(4.0f);B(0x47e)=0;}if(!frame_timer_142 && frame_index_140==4)dispatch_character_wave_handle(0);}if(frame_index_140>=6)decelerate(1.0,false);}return;
case 409: {
    F(0xf8)-=F(0x100);double next_y=F(0xf8)+static_cast<double>(F(0xf0));
    if(yuyuko_surface(this)>=next_y && F(0xf8)<0.0f){set_action_and_finalize(10);zero_motion();F(0xf0)=yuyuko_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
}
case 410:
    landing();if(!I(0x6c4))B(0x750)=0;
    if(!sequence_index_13e && S(0x730)==1) {
        if(S(0x732)%5==0 && S(0x734)<=5){dispatch_character_wave_handle(2);I(0x180)=1;phase_counter(10);float p[3]={static_cast<float>(-135-10*S(0x734)),8.0f,1.0f};spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++S(0x734);}
        ++S(0x732);
    }
    if(sequence_index_13e==1 && S(0x730)==1) {
        if(S(0x732)%3==0 && S(0x734)<=8){dispatch_character_wave_handle(2);I(0x180)=1;phase_counter(10);float p[3]={static_cast<float>(-120-7*S(0x734)),8.0f,1.0f};spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++S(0x734);}
        ++S(0x732);
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==5 && B(0x750)){effect(62,F(0xec),static_cast<float>(F(0xf0)+155.0),B(0x104),1);next_sequence_block();}if(!frame_timer_142 && frame_index_140==7){S(0x730)=1;counter(200,60);}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){S(0x730)=1;counter(200,60);}return;
case 411:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){phase_counter(50);dispatch_character_wave_handle(3);I(0x180)=1;counter(200,60);float p[3]={0.0f,15.0f,3.0f};spawn_offset(801,120,150.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,120,150.0,p,3);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4){phase_counter(50);dispatch_character_wave_handle(3);I(0x180)=1;counter(200,60);float p[3]={0.0f,15.0f,3.0f};spawn_offset(801,120,150.0,p,3);}return;
case 412:
    if(!sequence_index_13e || sequence_index_13e==5)landing();
    if(sequence_index_13e>=1 && sequence_index_13e<=4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);select_sequence(5);return;}}
    if(advance())set_action_and_finalize(0);
    if(!time_counter_144) {
        if(entry(1)){F(0xf8)=10.0f;F(0x100)=0.3f;}
        if(!time_counter_144) {
            if(entry(2)) {
                float p[3];
                for(float n=0.0f;n<6.0f;n=static_cast<float>(n+1.0)) {p[0]=static_cast<float>(n*60.0);p[1]=6.0f;p[2]=1.0f;circle801(p);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;circle801(p);}
                F(0xf8)=static_cast<float>(F(0xf8)*0.25);counter(200,60);phase_counter(30);dispatch_character_wave_handle(3);F(0x100)=0.0f;I(0x180)=1;
            }
            if(entry(3))F(0x100)=0.3f;
        }
    }return;
case 414:air801(false);return;
case 415:
    if(sequence_index_13e==2)landing();if(!I(0x6c4))B(0x750)=0;if(land_air801())return;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==6){phase_counter(50);dispatch_character_wave_handle(3);I(0x180)=1;counter(200,60);float p[3]={0.0f,15.0f,3.0f};spawn_offset(801,120,150.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,120,150.0,p,3);}
        if(!frame_timer_142 && frame_index_140==15)F(0x100)=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==4){phase_counter(50);dispatch_character_wave_handle(3);I(0x180)=1;counter(200,60);float p[3]={0.0f,15.0f,3.0f};spawn_offset(801,120,150.0,p,3);}
        if(!frame_timer_142 && frame_index_140==13)F(0x100)=0.5f;
    }return;
case 416:air801(true);return;
case 418:
    if(sequence_index_13e==1 || (!sequence_index_13e && frame_index_140>=3)) {
        F(0xf8)-=F(0x100);decelerate(0.5,false);
        if(static_cast<unsigned char>(crossed())){select_sequence(2);F(0xf0)=yuyuko_surface(this);zero_motion();return;}
    }
    if((!sequence_index_13e && frame_index_140<=2) || sequence_index_13e==2)landing();
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3){F(0xf4)=15.0f;F(0xf8)=10.0f;F(0x100)=0.5f;}
        if(!frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(0);
        if(!frame_timer_142 && frame_index_140==4)mode848(7.0f);
    }return;

case 500:
    landing();B(0x17c)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spread810(-20.0);return;
case 501:
    landing();B(0x17c)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spread810(-110.0);return;
case 502:
    if(air810_motion(0))return;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4)spread810(-20.0);if(!frame_timer_142 && frame_index_140==11)F(0x100)=0.4f;}return;
case 503:
    if(air810_motion(0))return;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4)spread810(-110.0);if(!frame_timer_142 && frame_index_140==11)F(0x100)=0.4f;}return;
case 505:
    landing();B(0x17c)=4;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)shot811(-60.0f);return;
case 506:
    landing();B(0x17c)=4;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)shot811(-45.0f);return;
case 507:
    if(air810_motion(4))return;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4)shot811(-60.0f);if(!frame_timer_142 && frame_index_140==11)F(0x100)=0.4f;}return;
case 508:
    if(air810_motion(4))return;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==4)shot811(-45.0f);if(!frame_timer_142 && frame_index_140==11)F(0x100)=0.4f;}return;
case 510:ground812(16.0f,12.0,16.0);return;
case 511:ground812(30.0f,10.0,20.0);return;
case 512:air812(16.0f,12.0,16.0);return;
case 513:air812(30.0f,10.0,20.0);return;
case 520:
    landing();B(0x17c)=1;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6)spread815(5,10.0,true);return;
case 521:
    landing();B(0x17c)=1;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6)spread815(8,16.0,false);return;
case 522:air815(5,10.0);return;
case 523:air815(8,16.0);return;
case 525:
    landing();B(0x17c)=5;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){I(0x180)=1;float p[3]={0.0f,20.0f,12.0f};spawn_offset(816,95,145.0,p,3);p[2]=1.0f;dispatch_character_wave_handle(16);phase_counter(50);counter(200,120);}return;
case 526:
    landing();B(0x17c)=5;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){I(0x180)=1;float p[3]={0.0f,20.0f,12.0f};spawn_offset(816,95,145.0,p,3);p[2]=1.0f;dispatch_character_wave_handle(16);phase_counter(50);counter(200,120);}return;
case 540:
    landing();B(0x17c)=2;if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))ring820(4.0f);return;
case 541:
    landing();B(0x17c)=2;if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1))ring820(0.0f);return;
case 545:hold821(0x6c0,0.0f);return;
case 546:hold821(0x6c4,-90.0f);return;
case 560:rush825(9.0f,25,false);return;
case 561:rush825(11.0f,40,true);return;
case 562: {
    if(sequence_index_13e==5)landing();B(0x17c)=3;
    F(0xf8)-=F(0x100);double next_y=F(0xf8)+static_cast<double>(F(0xf0));
    if(!(yuyuko_surface(this)<next_y || F(0xf8)>=0.0f || sequence_index_13e>=5)){select_sequence(5);F(0x100)=0.0f;B(0x47f)=0;F(0xf0)=yuyuko_surface(this);zero_motion();return;}
    if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(S(0x730)>0 && (sequence_index_13e==2 || sequence_index_13e==3)) {
        if(S(0x730)%4==1) {
            phase_counter(10);I(0x180)=1;
            float dx=static_cast<float>((peer()->at<float>(0xec)-F(0xec))*static_cast<double>(facing()));
            S(0x734)=static_cast<short>(-static_cast<short>(static_cast<int>(yuyuko_atan(peer()->at<float>(0xf0)-F(0xf0),dx))));
            if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;
            dispatch_character_wave_handle(9);
            if(S(0x738)==1){double base=S(0x734)+30.0;float first[3];first[0]=static_cast<float>(base-static_cast<float>(yuyuko_random_u32()%60u));first[1]=15.0f;first[2]=static_cast<float>(yuyuko_random(4));spawn_offset(808,44,85.0,first,3);}
            else{double base=S(0x734)+30.0;float second[3];second[0]=static_cast<float>(base-static_cast<float>(yuyuko_random_u32()%60u));second[1]=15.0f;second[2]=static_cast<float>(yuyuko_random(4));spawn_offset(808,44,85.0,second,3);}
        }
        ++S(0x730);
    }
    if(advance())set_action_and_finalize(0);
    if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>4 && (!B(0x750) || time_counter_144>25))next_sequence_block();
    if(entry(1)) {
        if(B(0x750)==1)effect(62,static_cast<float>(F(0xec)-static_cast<double>(23*facing())),static_cast<float>(F(0xf0)+107.0),B(0x104),1);
        float p[3]={0.0f,0.0f,4.0f};spawn_offset(808,-23,107.0,p,3);
    }
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){S(0x730)=1;counter(200,120);}
    if(sequence_index_13e==3 && ((time_counter_144>10 && !B(0x750)) || time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.6f;return;
}
case 565:ground826();return;
case 566:ground826();return;
case 567:
    if(sequence_index_13e==2)landing();else{F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);select_sequence(2);return;}}
    B(0x17c)=7;F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>0.0f)F(0xf4)=0.0f;
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2){F(0xf4)=-20.0f;F(0xf8)=10.0f;F(0x100)=0.35f;dispatch_character_wave_handle(17);counter(200,120);phase_counter(50);petal826(80,40.0);}
        if(!frame_timer_142 && frame_index_140==3)petal826(95,230.0);
        if(!frame_timer_142 && frame_index_140==4)petal826(20,290.0);
        if(!frame_timer_142 && frame_index_140==5)petal826(-80,250.0);
        if(!frame_timer_142 && frame_index_140==6)petal826(-110,160.0);
    }
    if(sequence_index_13e==1 && time_counter_144>=50)set_action_and_finalize(9);return;
case 599:
    if(S(0x730)>0 && frame_index_140<7 && S(0x730)<12) {
        unsigned angle=yuyuko_random_u32()%35u;S(0x734)=static_cast<short>(angle);
        float p[3]={static_cast<float>(-20-static_cast<int>(angle)),static_cast<float>(static_cast<short>(yuyuko_random_u32()%5u+10)),0.0f};
        spawn(807,static_cast<float>(20*facing()*(S(0x730)+1)+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        p[0]=static_cast<float>(yuyuko_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        spawn(801,static_cast<float>(20*facing()*(S(0x730)+1)+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        if(S(0x730)==1){dispatch_character_wave_handle(0);counter(200,120);}++S(0x730);
    }
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)S(0x730)=1;return;

case 600:
    landing();texture(2,2);if(sequence_index_13e==2 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if(entry(2))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,125.0,2);if(!frame_timer_142 && frame_index_140==4)ring_spell(850,false);}return;
case 601:
    landing();texture(2,2);if(sequence_index_13e==1 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(851,105,146.0,p,3);dispatch_character_wave_handle(51);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2)spell_flash(-40,150.0,1);return;
case 602:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==7){float p[3]={0.0f,25.0f,0.0f};spawn_offset(852,85,140.0,p,3);dispatch_character_wave_handle(52);}if(!frame_timer_142 && frame_index_140==2)spell_flash(-80,145.0,2);}return;
case 603:
    landing();texture(2,2);if(sequence_index_13e==2 && S(0x732)>=60){next_sequence_block();return;}
    if(S(0x730)==1){if(S(0x732)%30==0 && F(0x740)<6.0f){ring_spell(853,true);F(0x740)=static_cast<float>(F(0x740)+5.0);}++S(0x732);}
    if(advance())set_action_and_finalize(0);if(entry(2))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,125.0,4);if(!frame_timer_142 && frame_index_140==4)S(0x730)=1;}return;
case 604:
    landing();texture(2,2);if(sequence_index_13e==1 && time_counter_144>=24){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){float p[3]={0.0f,0.0f,4.0f};spawn(854,peer()->at<float>(0xec),0.0f,B(0x104),1,p,3);dispatch_character_wave_handle(54);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1)spell_flash(10,130.0,5);return;
case 605:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==7){float p[3]={0.0f,25.0f,0.0f};spawn_offset(855,85,140.0,p,3);dispatch_character_wave_handle(52);}if(!frame_timer_142 && frame_index_140==2)spell_flash(-80,145.0,4);}return;
case 606:
    landing();texture(2,2);if(sequence_index_13e==2 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if(entry(2))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,125.0,2);if(!frame_timer_142 && frame_index_140==4){float p[3];for(float n=0.0f;n<12.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*30.0);p[1]=4.0f;p[2]=12.0f;orbit_spell(856,p,false);}dispatch_character_wave_handle(10);}}return;
case 607:
    landing();texture(2,2);
    if(sequence_index_13e==1){if(time_counter_144%15==0 && S(0x730)<=3)pair857(false);if(time_counter_144>=60){next_sequence_block();return;}}
    if(sequence_index_13e==2 && time_counter_144>=0){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if(entry(2))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){spell_flash(-40,153.0,4);float p[3]={0.0f,0.0f,14.0f};spawn(857,static_cast<float>(F(0xec)-20*facing()),F(0xf0),B(0x104),-1,p,3);}return;
case 608:
    landing();texture(2,2);if(sequence_index_13e==2 && time_counter_144>=32){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){dispatch_character_wave_handle(13);I(0x180)=1;float p[3];for(int angle=0;angle<360;angle+=40){p[0]=static_cast<float>(angle);p[1]=600.0f;p[2]=1.0f;spawn(858,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),B(0x104),1,p,3);}}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(0,150.0,3);return;
case 651:
    if(sequence_index_13e==4)landing();if(sequence_index_13e<=2)texture(2,2);
    if(sequence_index_13e==2 || sequence_index_13e==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=yuyuko_surface(this);select_sequence(4);return;}}
    if(sequence_index_13e==1 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(851,105,146.0,p,3);dispatch_character_wave_handle(51);}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2){F(0x73c)=F(0xf4);F(0x740)=F(0xf8);zero_motion();spell_flash(-40,150.0,1);}if(!frame_timer_142 && frame_index_140==3){F(0xf4)=F(0x73c);F(0xf8)=F(0x740);}}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==1)F(0x100)=0.2f;return;
case 657:
    if(sequence_index_13e==5)landing();if(sequence_index_13e<=2)texture(2,2);
    if(sequence_index_13e==3 || sequence_index_13e==4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();F(0xf0)=yuyuko_surface(this);return;}}
    if(sequence_index_13e==1){if(time_counter_144%15==0 && S(0x730)<=3)pair857(true);if(time_counter_144>=60){next_sequence_block();return;}}
    if(sequence_index_13e==2 && time_counter_144>=0){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if(entry(2))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){spell_flash(-40,153.0,4);float p[3]={0.0f,0.0f,14.0f};spawn(857,static_cast<float>(F(0xec)-20*facing()),F(0xf0),B(0x104),-1,p,3);}
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2)F(0x100)=0.25f;return;

case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){event(55);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(141,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1);effect(142,F(0xec),F(0xf0),B(0x104),-1);}return;
case 696:
    landing();decelerate(0.5,true);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==4){mode848(4.0f);F(0xf4)=10.0f;B(0x47e)=0;}if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(0);}if(frame_index_140>=6)decelerate(static_cast<double>(1.2f),false);}return;
case 707:
    if(F(0xf4)>12.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<12.0f)F(0xf4)=12.0f;}
    if(advance()){set_action_and_finalize(700);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=15.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);if(time_counter_144>30){next_sequence_block();return;}}
    if(sequence_index_13e==2)decelerate(0.5,false);return;
case 708:
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!yuyuko_on_surface(this)) {
        if(time_counter_144%5==0)dash_dust(true);
        F(0xf8)=static_cast<float>(F(0xf8)-0.5);double next_y=F(0xf8)+static_cast<double>(F(0xf0));
        if(yuyuko_surface(this)>=next_y && F(0xf8)<0.0f){F(0xf8)=0.0f;F(0xf0)=yuyuko_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(700);return;}
    if(entry(1)){F(0xf4)=-14.0f;F(0xf8)=4.0f;dash_effects(true,80.0,false);}return;
case 709:
    if(!sequence_index_13e){F(0xf8)-=F(0x100);double next_y=F(0xf8)+static_cast<double>(F(0xf0));if(yuyuko_surface(this)>=next_y && F(0xf8)<0.0f){next_sequence_block();F(0xf0)=yuyuko_surface(this);F(0xf8)=0.0f;return;}}
    if(sequence_index_13e==1){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<=0.0f){F(0xf4)=0.0f;if(++S(0x730)>=2){next_sequence_block();F(0xf4)=-5.0f;F(0xf8)=5.0f;}}}
    if(sequence_index_13e==2 || sequence_index_13e==3){F(0xf8)=static_cast<float>(F(0xf8)-0.25);double next_y=F(0xf8)+static_cast<double>(F(0xf0));if(yuyuko_surface(this)>=next_y && F(0xf8)<0.0f){zero_motion();F(0xf0)=yuyuko_surface(this);next_sequence_block();return;}}
    if(advance())set_action_and_finalize(700);return;
case 710: {
    if(sequence_index_13e==1) {
        float p[3];
        switch(g_match_identifier) {
        case 0:if(!time_counter_144)difficulty900(p,true);if(time_counter_144>=90){next_sequence_block();return;}break;
        case 1:if(!time_counter_144)difficulty900(p,true);if(time_counter_144>=120){next_sequence_block();return;}break;
        case 2:if(!time_counter_144 || time_counter_144==60)difficulty900(p,false);if(time_counter_144>=150){next_sequence_block();return;}break;
        case 3:if(!time_counter_144 || time_counter_144==60 || time_counter_144==120)difficulty900(p,false);if(time_counter_144>=180){next_sequence_block();return;}break;
        }
    }
    if(advance())set_action_and_finalize(700);
    if(entry(1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(900,50,170.0,p,3);p[2]=5.0f;spawn_offset(900,50,170.0,p,3);}return;
}
case 720: {
    if(!sequence_index_13e && frame_index_140==2 && F(0xf8)>0.0f){F(0xf8)-=F(0x100);if(F(0xf8)<1.0f)F(0xf8)=1.0f;}
    if(sequence_index_13e==1) {
        float p[3];
        switch(g_match_identifier) {
        case 0:difficulty901(p,20,20.0);break;
        case 1:difficulty901(p,15,15.0);break;
        case 2:difficulty901(p,10,12.0);break;
        case 3:difficulty901(p,5,10.0);break;
        default:goto difficulty901_done;
        }
        if(time_counter_144>=210){next_sequence_block();return;}
    }
difficulty901_done:
    if(sequence_index_13e==2 || sequence_index_13e==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(4);zero_motion();F(0xf0)=yuyuko_surface(this);return;}}
    if(advance())set_action_and_finalize(700);
    if(!time_counter_144){if(entry(1))zero_motion();if(entry(3)){float y=F(0xf0);if(yuyuko_surface(this)<y)F(0x100)=0.2f;else set_action_and_finalize(700);}}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){F(0xf8)=static_cast<float>(static_cast<float>(yuyuko_random(13))+2.0);F(0x100)=0.25f;}return;
}
case 725:
    fade_alpha();if(advance())set_action_and_finalize(700);
    if(!time_counter_144){if(entry(1))dispatch_character_wave_handle(55);if(!time_counter_144){if(entry(3)){F(0xec)=static_cast<float>(static_cast<float>(yuyuko_random(300))+250.0+F(0xec));dispatch_character_wave_handle(55);}if(entry(4))return;}}
    // Native 56B556..56B574 falls through to 726 except entry 4.
case 726:
    fade_alpha();if(advance())set_action_and_finalize(700);
    if(!time_counter_144){if(entry(1))dispatch_character_wave_handle(55);if(entry(3)){double x=F(0xec);F(0xec)=static_cast<float>(x-(static_cast<float>(yuyuko_random(300))+250.0));dispatch_character_wave_handle(55);}}return;
case 730:
    if(sequence_index_13e>=1){F(0xf8)-=F(0x100);if(++S(0x730)>=60){zero_motion();set_action_and_finalize(731);return;}}
    if(advance())set_action_and_finalize(700);
    if(entry(1)){B(0x104)=255;F(0xf4)=static_cast<float>((640.0-F(0xec))/60.0*-1.0);F(0xf8)=18.5f;F(0x100)=0.5f;}return;
case 731:
    F(0xec)=640.0f;
    if(!sequence_index_13e && frame_index_140<=2 && time_counter_144%5==0){float p[3]={static_cast<float>(yuyuko_random(360)),static_cast<float>(static_cast<float>(yuyuko_random(250))+50.0),3.0f};spawn(922,static_cast<float>(yuyuko_cosine(-p[0])*p[1]*facing()+F(0xec)),static_cast<float>(yuyuko_cosine(-p[0])*p[1]+F(0xf0)+100.0),B(0x104),-1,p,3);}
    if(sequence_index_13e==1 && time_counter_144>=120){next_sequence_block();return;}
    if(sequence_index_13e==2){F(0xf0)=static_cast<float>(yuyuko_sine(static_cast<float>(time_counter_144*3.0))*F(0x744)+F(0x740));F(0x744)=static_cast<float>(F(0x744)+static_cast<double>(0.1f));if(F(0x744)>=60.0f)F(0x744)=60.0f;}
    if(advance())set_action_and_finalize(700);
    if(entry(1)){finish_story_state();float p[3]={0.0f,0.0f,4.0f};spawn_offset(922,0,100.0,p,3);p[2]=0.0f;spawn(922,F(0xec),F(0xf0),B(0x104),-1,p,3);dispatch_character_wave_handle(17);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,2.0f};spawn(922,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1,p,3);dispatch_character_wave_handle(18);}return;
case 770:
    if(advance())set_action_and_finalize(700);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7)finish_story_state();return;
case 795:
    if(!sequence_index_13e){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.3f));if(static_cast<unsigned char>(crossed())){select_sequence(1);event(30);F(0xf0)=yuyuko_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:
    if(sequence_index_13e<=1){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);event(30);F(0xf0)=yuyuko_surface(this);F(0xf8)=0.0f;return;}}
    if(advance())set_action_and_finalize(0);return;
case 798:
    if(sequence_index_13e<=1){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);event(30);F(0xf0)=yuyuko_surface(this);F(0xf8)=0.0f;return;}}
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f){F(0xf4)=0.0f;F(0xec)=800.0f;}if(F(0xec)<800.0f)F(0xec)=800.0f;}
    if(advance())set_action_and_finalize(700);return;
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
