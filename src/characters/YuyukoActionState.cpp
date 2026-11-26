#include "characters/YuyukoActionState.hpp"
// Complete JP1.06a55D850 candidate, not selected or exact.
// See docs/YUYUKO_ACTION_STATE_2026_10_28.md.
namespace th105 {
void YuyukoActionStateView::dispatch_action_state_vslot28()
{
    word_7a0=0;word_7a2=90;
    if(action_id_13c>149 && action_id_13c<159 && !byte_751) {
        byte_751=1;
        if(action_id_13c>149 && action_id_13c<154)spawn(998,static_cast<float>(57*facing()+static_cast<double>(x_ec)),static_cast<float>(y_f0+94.0),static_cast<unsigned char>(facing_104),1,0,0);
        if(action_id_13c>153 && action_id_13c<158)spawn(998,static_cast<float>(57*facing()+static_cast<double>(x_ec)),static_cast<float>(y_f0+60.0),static_cast<unsigned char>(facing_104),1,0,0);
        if(action_id_13c==158)spawn(998,static_cast<float>(57*facing()+static_cast<double>(x_ec)),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,0,0);
    }
    if(word_186 || peer()->word_48c)return;
    switch(action_id_13c) {
case 0:
    landing();if(velocity_x_f4==0.0f)byte_47e=0;idle_motion();break;
case 1:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:
    landing();idle_motion();break;
case 3:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:landing();velocity_x_f4=4.0f;break;
case 5:landing();velocity_x_f4=-4.0f;break;
case 6:{
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !byte_47e)zero_motion();
        }
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
            }
        }
        advance();
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_x_f4=0.0f;velocity_y_f8=12.0f;acceleration_y_100=0.4f;byte_47e=0;}

    return;
}
case 7:{
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !byte_47e)zero_motion();
        }
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
            }
        }
        advance();
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_x_f4=4.0f;velocity_y_f8=12.0f;acceleration_y_100=0.4f;byte_47e=0;}

    return;
}
case 8:{
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !byte_47e)zero_motion();
        }
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
            }
        }
        advance();
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_x_f4=-4.0f;velocity_y_f8=12.0f;acceleration_y_100=0.4f;byte_47e=0;}

    return;
}
case 9:
    if(acceleration_y_100==0.0f)acceleration_y_100=0.6f;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;}
    break;
case 10:
    landing();zero_motion();if(advance()){if(!field_6b8){set_action_and_finalize(0);return;}set_action_and_finalize(2);}return;
case 197: {
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){y_f0=yuyuko_surface(this);zero_motion();select_sequence(3);return;}}
    if(advance()) {
        if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);
    }
    if(sequence_index_13e==3 && frame_index_140==2 && !frame_timer_142)ground_face();
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_y_f8=8.0f;velocity_x_f4=11.5f;acceleration_y_100=0.5f;}
    return;
}
case 198: {
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){y_f0=yuyuko_surface(this);zero_motion();select_sequence(3);return;}}
    if(advance()) {
        if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);
    }
    if(sequence_index_13e==3 && frame_index_140==2 && !frame_timer_142)ground_face();
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_y_f8=8.0f;velocity_x_f4=-11.5f;acceleration_y_100=0.5f;}
    return;
}
case 199:
    landing();
    if(advance()) {
        if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(2);if(field_6b8>0)set_action_and_finalize(1);
    }
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)ground_face();return;
case 200:
    landing();byte_47e=1;
    if(velocity_x_f4>6.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<6.0f)velocity_x_f4=6.0f;}
    advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        if(field_6b8<0){if(field_6b4*facing()>0){set_action_and_finalize(212);return;}set_action_and_finalize(211);return;}
        short ticks=++word_730;
        if((field_6b4*facing()<=0 && ticks>5) || ticks>60){set_action_and_finalize(204);return;}
    }
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_x_f4=15.0f;dash_effects(false,80.0,true);}return;
case 201:
    if(!sequence_index_13e || sequence_index_13e==4)landing();
    if(!static_cast<unsigned char>(yuyuko_on_surface(this)) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<4) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);select_sequence(4);return;}
    }
    if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_x_f4=-10.0f;velocity_y_f8=2.0f;acceleration_y_100=0.2f;dash_effects(true,80.0,false);}return;
case 202: {
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    advance();
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){word_730=0;velocity_x_f4=7.5f;velocity_y_f8=3.5f;acceleration_y_100=0.45f;dash_effects(false,110.0,true);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==5)flip();return;
}
case 203:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<2 && time_counter_144%5==0)dash_dust(true);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1){velocity_x_f4=-7.5f;velocity_y_f8=3.5f;acceleration_y_100=0.45f;dash_effects(true,120.0,false);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2)flip();return;
case 204:
    landing();velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
    if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}
    if(advance()){set_action_and_finalize(0);byte_47e=0;}return;
case 208:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(yuyuko_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(!(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))return;
            velocity_x_f4=0.0f;velocity_y_f8=18.5f;acceleration_y_100=0.55f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);

    return;
}
case 209:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(yuyuko_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(!(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))return;
            velocity_x_f4=10.0f;velocity_y_f8=13.5f;acceleration_y_100=0.5f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);

    return;
}
case 210:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(yuyuko_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(!(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))return;
            velocity_x_f4=-10.0f;velocity_y_f8=13.5f;acceleration_y_100=0.5f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);

    return;
}
case 211:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(yuyuko_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(!(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))return;
            velocity_x_f4=2.0f;velocity_y_f8=18.5f;acceleration_y_100=0.55f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);

    return;
}
case 212:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(yuyuko_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(!(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))return;
            velocity_x_f4=10.0f;velocity_y_f8=13.5f;acceleration_y_100=0.5f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);

    return;
}
case 214: {
    if(advance()){set_action_and_finalize(9);return;}
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)) {
        event(31);
        if(field_740>=135.0f || field_740<=-135.0f){select_sequence(6);return;}
        if(field_740>45.0f || field_740<-45.0f){select_sequence(4);return;}
    }
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==9))select_sequence(5);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==10)){set_action_and_finalize(9);return;}
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==11)){set_action_and_finalize(9);return;}
    if(field_6b8>0) {
        if(field_6b4*facing_104>0)word_732=-45;
        else if(field_6b4*facing_104<0)word_732=-135;
        else word_732=-90;
    } else if(field_6b8<0) {
        if(field_6b4*facing_104>0)word_732=45;
        else if(field_6b4*facing_104<0)word_732=135;
        else word_732=90;
    } else {
        if(field_6b4*facing_104>0)word_732=0;
        else if(field_6b4*facing_104<0)word_732=180;
    }
    if(sequence_index_13e==9 || sequence_index_13e==10 || sequence_index_13e==11)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e>0 && sequence_index_13e<9) {
        ++word_736;
        word_734=static_cast<short>(word_732-static_cast<int>(field_740));
        if(word_734>180)word_734-=360;
        if(word_734<-180)word_734+=360;
        if(field_740>180.0f)field_740=static_cast<float>(field_740-360.0);
        if(field_740<-180.0f)field_740=static_cast<float>(field_740+360.0);
        if(word_734>0) {
            if(!field_4b8)field_740=static_cast<float>(field_740+6.0);
            else field_740=static_cast<float>(field_740+5.0);
        }
        if(word_734<0) {
            if(!field_4b8)field_740=static_cast<float>(field_740-6.0);
            else field_740=static_cast<float>(field_740-5.0);
        }
        velocity_x_f4=static_cast<float>(yuyuko_cosine(field_740)*field_73c);
        velocity_y_f8=static_cast<float>(yuyuko_sine(field_740)*field_73c);
        if(y_f0>680.0f && velocity_y_f8>0.0f)velocity_y_f8=0.0f;
        if(!field_4b8)counter(4,1);else counter(8,1);
        if((sequence_index_13e==1 || sequence_index_13e==2) && (field_740>60.0f || field_740<-60.0f)){select_sequence(3);return;}
        if(sequence_index_13e==4 || sequence_index_13e==5) {
            if(field_740<=45.0f && field_740>=-45.0f){select_sequence(1);return;}
            if(field_740>=135.0f || field_740<=-135.0f){select_sequence(6);return;}
        }
        if((sequence_index_13e==6 || sequence_index_13e==7) && field_740<120.0f && field_740>-120.0f){select_sequence(8);return;}
        if((field_6c8==0 && word_736>10) || word_482<=0) {
            if((field_6c8==0 && word_736>10) || word_482<=0) {
                if(sequence_index_13e==1 || sequence_index_13e==2)release_flight(9);
                if(sequence_index_13e==3) {
                    word_730=frame_index_140;
                    if(static_cast<unsigned char>(facing_104)==1) {
                        if(x_ec>peer()->x_ec) {
                            facing_104=-1;velocity_x_f4=-velocity_x_f4;
                            select_sequence(9);
                            set_sequence_frame(static_cast<unsigned short>(word_730));
                        } else {
                            select_sequence(9);
                            set_sequence_frame(static_cast<unsigned short>(word_730));
                        }
                    } else {
                        if(x_ec<peer()->x_ec) {
                            facing_104=-facing_104;velocity_x_f4=-velocity_x_f4;
                            select_sequence(9);
                            set_sequence_frame(static_cast<unsigned short>(word_730));
                        } else {
                            select_sequence(9);
                            set_sequence_frame(static_cast<unsigned short>(word_730));
                        }
                    }
                }
                if(sequence_index_13e==4 || sequence_index_13e==5)release_flight(10);
                if(sequence_index_13e==6 || sequence_index_13e==7)release_flight(11);
                if(sequence_index_13e==8) {
                    word_730=frame_index_140;
                    if(static_cast<unsigned char>(facing_104)==1) {
                        if(x_ec>peer()->x_ec) {
                            facing_104=-1;velocity_x_f4=-velocity_x_f4;
                            select_sequence(11);
                            set_sequence_frame(static_cast<unsigned short>(word_730));return;
                        }
                        select_sequence(11);
                        set_sequence_frame(static_cast<unsigned short>(word_730));return;
                    }
                    if(x_ec<peer()->x_ec) {
                        facing_104=-facing_104;velocity_x_f4=-velocity_x_f4;
                        select_sequence(11);
                        set_sequence_frame(static_cast<unsigned short>(word_730));return;
                    }
                    select_sequence(11);
                    set_sequence_frame(static_cast<unsigned short>(word_730));return;
                }
                return;
            }
        }
    }
    if(static_cast<unsigned char>(crossed())) {
        y_f0=yuyuko_surface(this);velocity_y_f8=0.0f;acceleration_y_100=0.0f;
        if(sequence_index_13e<9){reset_action_scratch();set_action_and_finalize(215);}
        else {set_action_and_finalize(10);zero_motion();}
    }
    return;

}

case 215:
    landing();
    if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(yuyuko_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(!(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))return;
            velocity_x_f4=0.0f;velocity_y_f8=18.5f;acceleration_y_100=0.55f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);

    return;
}
case 221:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(yuyuko_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(!(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))return;
            velocity_x_f4=10.0f;velocity_y_f8=13.5f;acceleration_y_100=0.5f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);

    return;
}
case 222:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(yuyuko_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(!(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))return;
            velocity_x_f4=-10.0f;velocity_y_f8=13.5f;acceleration_y_100=0.5f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);

    return;
}
case 223:
    landing();byte_47e=1;
    if(velocity_x_f4>6.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<6.0f)velocity_x_f4=6.0f;}
    advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);short ticks=++word_730;if((field_6b4*facing()<=0 && ticks>15)||ticks>60){set_action_and_finalize(204);return;}}
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_x_f4=7.5f;dash_effects(false,80.0,true);}return;
case 224:
    if(!sequence_index_13e || sequence_index_13e==4)landing();
    if(!static_cast<unsigned char>(yuyuko_on_surface(this)) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<4) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);select_sequence(4);return;}
    }
    if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_x_f4=-10.0f;velocity_y_f8=2.0f;acceleration_y_100=0.2f;dash_effects(true,80.0,false);}return;
case 225:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==1){velocity_x_f4=-7.5f;velocity_y_f8=3.5f;acceleration_y_100=0.45f;dash_effects(true,120.0,false);}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9)flip();
    }return;

case 226: {
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    if(advance())set_action_and_finalize(9);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){word_730=0;velocity_x_f4=7.5f;velocity_y_f8=3.5f;acceleration_y_100=0.45f;dash_effects(false,110.0,true);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==5)flip();return;
}
case 300:
    landing();if(directional(0))return;
    if(byte_47e)decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)mode848(1.0f);if(!frame_timer_142 && frame_index_140==3){event(28);byte_47e=0;}}return;
case 301:
    landing();if(directional(0))return;
    if(byte_47e)decelerate(0.5,true);
    if(frame_index_140>=5)decelerate(static_cast<double>(0.15f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2){velocity_x_f4=4.0f;byte_47e=0;mode848(3.0f);}if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);byte_47e=0;}}return;
case 302:
    landing();if(directional(1))return;
    if(byte_47e)decelerate(0.5,true);
    if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142) {
            if(frame_index_140==4){if(byte_750){charge_flash(-43,162.0);return;}mode848(4.0f);velocity_x_f4=10.0f;byte_47e=0;}
            if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(0);
        }
        if(frame_index_140>=6)decelerate(static_cast<double>(1.2f),false);
    }
    if(sequence_index_13e==1) {
        if(!frame_timer_142) {
            if(frame_index_140==1){velocity_x_f4=10.0f;byte_47e=0;mode848(4.0f);}
            if(!frame_timer_142 && frame_index_140==2)dispatch_character_wave_handle(0);
        }
        if(frame_index_140>=3)decelerate(static_cast<double>(1.2f),false);
    }return;
case 303:
    landing();if(directional(0))return;
    if(byte_47e>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==1){event(28);mode848(2.0f);}return;
case 304:
    landing();if(directional(1))return;
    if(byte_47e>0)decelerate(static_cast<double>(0.6f),true);
    if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(2);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142) {
            if(frame_index_140==3)mode848(5.0f);
            if(!frame_timer_142 && frame_index_140==3){if(byte_750){charge_flash(-20,50.0);return;}velocity_x_f4=2.0f;event(29);}
        }
        if(frame_index_140>=5)decelerate(static_cast<double>(0.15f),true);
    }
    if(sequence_index_13e==1) {
        if(!frame_timer_142) {
            if(frame_index_140==1){velocity_x_f4=2.0f;event(29);}
            if(!frame_timer_142 && frame_index_140==1)mode848(5.0f);
        }
        if(frame_index_140>=3)decelerate(static_cast<double>(0.15f),true);
    }return;
case 305:
    landing();if(directional(1))return;decelerate(static_cast<double>(0.2f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==1)mode848(10.0f,-40,120.0);if(!frame_timer_142 && frame_index_140==2)event(28);}return;
case 306:

        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
        set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2)event(28);if(!frame_timer_142 && frame_index_140==2)mode848(6.0f);}return;
case 307:
    if(!field_6bc)byte_750=0;
    velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<2.0f)velocity_x_f4=2.0f;

        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
        set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==1){velocity_x_f4=12.5f;velocity_y_f8=10.0f;acceleration_y_100=0.5f;}
        if(!frame_timer_142 && frame_index_140==2)mode848(7.0f);
        if(!frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(0);
        if(!frame_timer_142 && frame_index_140==8)acceleration_y_100=0.6f;
    }return;
case 308:
    if(!field_6bc)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
        set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==4)mode848(8.0f);
        if(!frame_timer_142 && frame_index_140==5)event(29);
        if(!frame_timer_142 && frame_index_140==6)field_180=0;
        if(!frame_timer_142 && frame_index_140==7)field_180=0;
        if(!frame_timer_142 && frame_index_140==8)field_180=0;
    }return;
case 309:

        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
        set_action_and_finalize(10);y_f0=yuyuko_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==2){velocity_x_f4=static_cast<float>(velocity_x_f4*0.5);velocity_y_f8=5.0f;acceleration_y_100=0.5f;event(29);}
        if(!frame_timer_142 && frame_index_140==7)acceleration_y_100=0.5f;
    }return;
case 310:
    if(field_180 && ++word_730>5){field_180=0;word_730=0;}
    if(sequence_index_13e==1) {
        if(!time_counter_144)velocity_x_f4=15.0f;
        if(time_counter_144%8==0)event(27);
        if(field_180 && ++word_730>5){field_180=0;word_730=0;}
        if(time_counter_144>30){next_sequence_block();velocity_y_f8=6.0f;velocity_x_f4=static_cast<float>(velocity_x_f4*0.5);}
    }
    if(sequence_index_13e==2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;y_f0=yuyuko_surface(this);set_action_and_finalize(9);return;}}
    if(advance())set_action_and_finalize(9);return;
case 320:
    landing();if(directional(0))return;
    if(byte_47e)decelerate(0.5,true);
    if(frame_index_140>=5)decelerate(static_cast<double>(0.15f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2){velocity_x_f4=4.0f;byte_47e=0;mode848(3.0f);}if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);byte_47e=0;}}return;
case 321:
    landing();if(directional(1))return;
    if(frame_index_140>3)decelerate(static_cast<double>(0.3f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)velocity_x_f4=4.5f;if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);byte_47e=0;mode848(12.0f);}}return;
case 322:
    landing();if(directional(1))return;
    if(frame_index_140>=4)decelerate(static_cast<double>(0.2f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3)velocity_x_f4=4.0f;if(!frame_timer_142 && frame_index_140==4)dispatch_character_wave_handle(0);}return;

case 400:{
        landing();if(sequence_index_13e<2 && !field_6c0)byte_750=0;
        {
        if(word_730>0) {
            ++word_730;
            if(!sequence_index_13e) {if(word_730%10==1 && word_732<3){
        field_180=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(word_734+(word_732+3)*n*5-static_cast<float>(10*(word_732+3)));
            p[1]=1.0f;p[2]=static_cast<float>(word_732);spawn_offset(800,60,160.0,p,3);
        }
        p[2]=static_cast<float>(word_732+16.0);spawn_offset(800,60,160.0,p,3);
        dispatch_character_wave_handle(1);++word_732;
    }}
            else if(word_730%10==1 && word_732<4){
        field_180=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(word_734+(word_732+2)*n*5-static_cast<float>(10*(word_732+2)));
            p[1]=1.0f;p[2]=static_cast<float>(word_732);spawn_offset(800,60,160.0,p,3);
        }
        p[2]=static_cast<float>(word_732+16.0);spawn_offset(800,60,160.0,p,3);
        dispatch_character_wave_handle(1);++word_732;
    }
        }
    }if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e) {
            if(!frame_timer_142 && frame_index_140==5 && byte_750)fan_charge();
            if(!frame_timer_142 && frame_index_140==6)aim_fan();
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2)aim_fan();

    return;
}
case 401:{
        landing();if(sequence_index_13e<2 && !field_6c0)byte_750=0;
        {
        if(word_730>0) {
            ++word_730;
            if(!sequence_index_13e) {if(word_730%10==1 && word_732<3){
        field_180=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(word_734+(word_732+3)*n*5-static_cast<float>(10*(word_732+3)));
            p[1]=1.0f;p[2]=static_cast<float>(word_732);spawn_offset(800,60,160.0,p,3);
        }

        dispatch_character_wave_handle(1);++word_732;
    }}
            else if(word_730%10==1 && word_732<3){
        field_180=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(word_734+(word_732+2)*n*5-static_cast<float>(10*(word_732+2)));
            p[1]=1.0f;p[2]=static_cast<float>(word_732);spawn_offset(800,60,160.0,p,3);
        }

        dispatch_character_wave_handle(1);++word_732;
    }
        }
    }if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e) {
            if(!frame_timer_142 && frame_index_140==5 && byte_750)fan_charge();
            if(!frame_timer_142 && frame_index_140==6)aim_fan();
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2)aim_fan();

    return;
}
case 402:
    if(frame_index_140<=1 || frame_index_140>=7)landing();
    if(!field_6c0)byte_750=0;
    if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(word_730==1) {
        if(word_732%3==0 && word_734<4) {
            float p[3];
            for(int n=0;n<30;n+=10){p[0]=static_cast<float>(-20*word_734);p[1]=static_cast<float>(n+10.0);p[2]=static_cast<float>(word_734+12.0);spawn(800,x_ec,static_cast<float>(yuyuko_sine(static_cast<float>(20*word_734))*150.0+y_f0+50.0),static_cast<unsigned char>(facing_104),1,p,3);}
            for(int n=4;n;--n){p[0]=static_cast<float>(yuyuko_random(360));p[1]=static_cast<float>(static_cast<float>(yuyuko_random(50))*static_cast<double>(0.1f)+5.0);p[2]=static_cast<float>(word_734+4.0);spawn(800,x_ec,static_cast<float>(yuyuko_sine(static_cast<float>(20*word_734))*150.0+y_f0+50.0),static_cast<unsigned char>(facing_104),1,p,3);}
            ++word_734;
        }
        ++word_732;
    }
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)velocity_x_f4=-15.0f;if(!frame_timer_142 && frame_index_140==3){field_180=1;counter(200,45);phase_counter(50);word_730=1;dispatch_character_wave_handle(1);}}return;
case 404:{
        if(sequence_index_13e==2)landing();if(!field_6c0)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            word_730=0;select_sequence(2);byte_47f=0;
            y_f0=yuyuko_surface(this);zero_motion();return;
        }
        {
        if(word_730>0) {
            ++word_730;
            if(!sequence_index_13e) {if(word_730%10==1 && word_732<3){
        field_180=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(word_734+(word_732+3)*n*5-static_cast<float>(10*(word_732+3)));
            p[1]=1.0f;p[2]=static_cast<float>(word_732);spawn_offset(800,60,160.0,p,3);
        }
        p[2]=static_cast<float>(word_732+16.0);spawn_offset(800,60,160.0,p,3);
        dispatch_character_wave_handle(1);++word_732;
    }}
            else if(word_730%10==1 && word_732<4){
        field_180=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(word_734+(word_732+2)*n*5-static_cast<float>(10*(word_732+2)));
            p[1]=1.0f;p[2]=static_cast<float>(word_732);spawn_offset(800,60,160.0,p,3);
        }
        p[2]=static_cast<float>(word_732+16.0);spawn_offset(800,60,160.0,p,3);
        dispatch_character_wave_handle(1);++word_732;
    }
        }
    }if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e) {
            if(!frame_timer_142 && frame_index_140==5 && byte_750)fan_charge();
            if(!frame_timer_142 && frame_index_140==6)aim_fan();
            if(!frame_timer_142 && frame_index_140==14)acceleration_y_100=0.6f;
        }
        if(sequence_index_13e==1) {
            if(!frame_timer_142 && frame_index_140==2)aim_fan();
            if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.6f;
        }

    return;
}
case 406:{
        if(sequence_index_13e==2)landing();if(!field_6c0)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            word_730=0;select_sequence(2);byte_47f=0;
            y_f0=yuyuko_surface(this);zero_motion();return;
        }
        {
        if(word_730>0) {
            ++word_730;
            if(!sequence_index_13e) {if(word_730%10==1 && word_732<3){
        field_180=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(word_734+(word_732+3)*n*5-static_cast<float>(10*(word_732+3)));
            p[1]=1.0f;p[2]=static_cast<float>(word_732);spawn_offset(800,60,160.0,p,3);
        }
        p[2]=static_cast<float>(word_732+16.0);spawn_offset(800,60,160.0,p,3);
        dispatch_character_wave_handle(1);++word_732;
    }}
            else if(word_730%10==1 && word_732<4){
        field_180=1;phase_counter(10);float p[3];
        for(int n=0;n<5;++n) {
            p[0]=static_cast<float>(word_734+(word_732+2)*n*5-static_cast<float>(10*(word_732+2)));
            p[1]=1.0f;p[2]=static_cast<float>(word_732);spawn_offset(800,60,160.0,p,3);
        }
        p[2]=static_cast<float>(word_732+16.0);spawn_offset(800,60,160.0,p,3);
        dispatch_character_wave_handle(1);++word_732;
    }
        }
    }if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e) {
            if(!frame_timer_142 && frame_index_140==5 && byte_750)fan_charge();
            if(!frame_timer_142 && frame_index_140==6)aim_fan();
            if(!frame_timer_142 && frame_index_140==14)acceleration_y_100=0.6f;
        }
        if(sequence_index_13e==1) {
            if(!frame_timer_142 && frame_index_140==2)aim_fan();
            if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.6f;
        }

    return;
}
case 408:
    landing();decelerate(0.5,false);if(!field_6bc)byte_750=0;
    if(advance()){set_action_and_finalize(0);byte_47e=0;}
    if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==4){mode848(4.0f);byte_47e=0;}if(!frame_timer_142 && frame_index_140==4)dispatch_character_wave_handle(0);}if(frame_index_140>=6)decelerate(1.0,false);}return;
case 409: {
    velocity_y_f8-=acceleration_y_100;double next_y=velocity_y_f8+static_cast<double>(y_f0);
    if(yuyuko_surface(this)>=next_y && velocity_y_f8<0.0f){set_action_and_finalize(10);zero_motion();y_f0=yuyuko_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
}
case 410:
    landing();if(!field_6c4)byte_750=0;
    if(!sequence_index_13e && word_730==1) {
        if(word_732%5==0 && word_734<=5){dispatch_character_wave_handle(2);field_180=1;phase_counter(10);float p[3]={static_cast<float>(-135-10*word_734),8.0f,1.0f};spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++word_734;}
        ++word_732;
    }
    if(sequence_index_13e==1 && word_730==1) {
        if(word_732%3==0 && word_734<=8){dispatch_character_wave_handle(2);field_180=1;phase_counter(10);float p[3]={static_cast<float>(-120-7*word_734),8.0f,1.0f};spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++word_734;}
        ++word_732;
    }
    if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==5 && byte_750){effect(62,x_ec,static_cast<float>(y_f0+155.0),static_cast<unsigned char>(facing_104),1);next_sequence_block();}if(!frame_timer_142 && frame_index_140==7){word_730=1;counter(200,60);}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){word_730=1;counter(200,60);}return;
case 411:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){phase_counter(50);dispatch_character_wave_handle(3);field_180=1;counter(200,60);float p[3]={0.0f,15.0f,3.0f};spawn_offset(801,120,150.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,120,150.0,p,3);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4){phase_counter(50);dispatch_character_wave_handle(3);field_180=1;counter(200,60);float p[3]={0.0f,15.0f,3.0f};spawn_offset(801,120,150.0,p,3);}return;
case 412:
    if(!sequence_index_13e || sequence_index_13e==5)landing();
    if(sequence_index_13e>=1 && sequence_index_13e<=4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);select_sequence(5);return;}}
    if(advance())set_action_and_finalize(0);
    if(!time_counter_144) {
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_y_f8=10.0f;acceleration_y_100=0.3f;}
        if(!time_counter_144) {
            if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)) {
                float p[3];
                for(float n=0.0f;n<6.0f;n=static_cast<float>(n+1.0)) {p[0]=static_cast<float>(n*60.0);p[1]=6.0f;p[2]=1.0f;circle801(p);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;circle801(p);}
                velocity_y_f8=static_cast<float>(velocity_y_f8*0.25);counter(200,60);phase_counter(30);dispatch_character_wave_handle(3);acceleration_y_100=0.0f;field_180=1;
            }
            if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==3))acceleration_y_100=0.3f;
        }
    }return;
case 414:{
        if(sequence_index_13e==2)landing();
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            select_sequence(2);acceleration_y_100=0.0f;byte_47f=0;
            y_f0=yuyuko_surface(this);zero_motion();return;
        }

        if(!field_6c4)byte_750=0;
        if(!sequence_index_13e && word_730==1) {
            if(word_732%5==0 && word_734<=5) {
                dispatch_character_wave_handle(2);field_180=1;phase_counter(10);
                float p[3]={static_cast<float>(-135-10*word_734),8.0f,1.0f};
                spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++word_734;
            }
            ++word_732;
        }
        if(sequence_index_13e==1 && word_730==1) {
            if(word_732%3==0 && word_734<=10) {
                dispatch_character_wave_handle(2);field_180=1;phase_counter(10);
                float p[3]={static_cast<float>(-120-7*word_734),8.0f,1.0f};
                spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++word_734;
            }
            ++word_732;
        }
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e) {
            if(!frame_timer_142 && frame_index_140==5 && byte_750){effect(62,x_ec,static_cast<float>(y_f0+155.0),static_cast<unsigned char>(facing_104),1);next_sequence_block();}
            if(!frame_timer_142 && frame_index_140==7){word_730=1;counter(200,60);}
            if(!frame_timer_142 && frame_index_140==15)acceleration_y_100=0.5f;
        }
        if(sequence_index_13e==1) {
            if(!frame_timer_142 && frame_index_140==3){word_730=1;counter(200,60);}
            if(!frame_timer_142 && frame_index_140==13)acceleration_y_100=0.5f;
        }

    return;
}
case 415:
    if(sequence_index_13e==2)landing();if(!field_6c4)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            select_sequence(2);acceleration_y_100=0.0f;byte_47f=0;
            y_f0=yuyuko_surface(this);zero_motion();return;
        }

    if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==6){phase_counter(50);dispatch_character_wave_handle(3);field_180=1;counter(200,60);float p[3]={0.0f,15.0f,3.0f};spawn_offset(801,120,150.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,120,150.0,p,3);}
        if(!frame_timer_142 && frame_index_140==15)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1) {
        if(!frame_timer_142 && frame_index_140==4){phase_counter(50);dispatch_character_wave_handle(3);field_180=1;counter(200,60);float p[3]={0.0f,15.0f,3.0f};spawn_offset(801,120,150.0,p,3);}
        if(!frame_timer_142 && frame_index_140==13)acceleration_y_100=0.5f;
    }return;
case 416:{
        if(sequence_index_13e==2)landing();
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            select_sequence(2);acceleration_y_100=0.0f;byte_47f=0;
            y_f0=yuyuko_surface(this);zero_motion();return;
        }

        if(!field_6c4)byte_750=0;
        if(!sequence_index_13e && word_730==1) {
            if(word_732%5==0 && word_734<=5) {
                dispatch_character_wave_handle(2);field_180=1;phase_counter(10);
                float p[3]={static_cast<float>(10*(word_734+12)),8.0f,1.0f};
                spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++word_734;
            }
            ++word_732;
        }
        if(sequence_index_13e==1 && word_730==1) {
            if(word_732%3==0 && word_734<=10) {
                dispatch_character_wave_handle(2);field_180=1;phase_counter(10);
                float p[3]={static_cast<float>(7*(-30-word_734)),8.0f,1.0f};
                spawn_offset(801,57,200.0,p,3);p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn_offset(801,57,200.0,p,3);++word_734;
            }
            ++word_732;
        }
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e) {
            if(!frame_timer_142 && frame_index_140==5 && byte_750){effect(62,x_ec,static_cast<float>(y_f0+155.0),static_cast<unsigned char>(facing_104),1);next_sequence_block();}
            if(!frame_timer_142 && frame_index_140==7){word_730=1;counter(200,60);phase_counter(30);}
            if(!frame_timer_142 && frame_index_140==15)acceleration_y_100=0.5f;
        }
        if(sequence_index_13e==1) {
            if(!frame_timer_142 && frame_index_140==3){word_730=1;counter(200,60);phase_counter(30);}
            if(!frame_timer_142 && frame_index_140==13)acceleration_y_100=0.5f;
        }

    return;
}
case 418:
    if(sequence_index_13e==1 || (!sequence_index_13e && frame_index_140>=3)) {
        velocity_y_f8-=acceleration_y_100;decelerate(0.5,false);
        if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=yuyuko_surface(this);zero_motion();return;}
    }
    if((!sequence_index_13e && frame_index_140<=2) || sequence_index_13e==2)landing();
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==3){velocity_x_f4=15.0f;velocity_y_f8=10.0f;acceleration_y_100=0.5f;}
        if(!frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(0);
        if(!frame_timer_142 && frame_index_140==4)mode848(7.0f);
    }return;

case 500:
    landing();byte_17c=0;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spread810(-20.0);return;
case 501:
    landing();byte_17c=0;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spread810(-110.0);return;
case 502:

        if(sequence_index_13e==2)landing();byte_17c=0;
        if(sequence_index_13e<2)velocity_y_f8-=acceleration_y_100;
        if((!sequence_index_13e && frame_index_140>=11 && static_cast<unsigned char>(crossed())) ||
           (sequence_index_13e==1 && frame_index_140>=11 && static_cast<unsigned char>(crossed()))) {
            select_sequence(2);zero_motion();y_f0=yuyuko_surface(this);return;
        }
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}

    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==4)spread810(-20.0);if(!frame_timer_142 && frame_index_140==11)acceleration_y_100=0.4f;}return;
case 503:

        if(sequence_index_13e==2)landing();byte_17c=0;
        if(sequence_index_13e<2)velocity_y_f8-=acceleration_y_100;
        if((!sequence_index_13e && frame_index_140>=11 && static_cast<unsigned char>(crossed())) ||
           (sequence_index_13e==1 && frame_index_140>=11 && static_cast<unsigned char>(crossed()))) {
            select_sequence(2);zero_motion();y_f0=yuyuko_surface(this);return;
        }
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}

    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==4)spread810(-110.0);if(!frame_timer_142 && frame_index_140==11)acceleration_y_100=0.4f;}return;
case 505:
    landing();byte_17c=4;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)shot811(-60.0f);return;
case 506:
    landing();byte_17c=4;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)shot811(-45.0f);return;
case 507:

        if(sequence_index_13e==2)landing();byte_17c=4;
        if(sequence_index_13e<2)velocity_y_f8-=acceleration_y_100;
        if((!sequence_index_13e && frame_index_140>=11 && static_cast<unsigned char>(crossed())) ||
           (sequence_index_13e==1 && frame_index_140>=11 && static_cast<unsigned char>(crossed()))) {
            select_sequence(2);zero_motion();y_f0=yuyuko_surface(this);return;
        }
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}

    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==4)shot811(-60.0f);if(!frame_timer_142 && frame_index_140==11)acceleration_y_100=0.4f;}return;
case 508:

        if(sequence_index_13e==2)landing();byte_17c=4;
        if(sequence_index_13e<2)velocity_y_f8-=acceleration_y_100;
        if((!sequence_index_13e && frame_index_140>=11 && static_cast<unsigned char>(crossed())) ||
           (sequence_index_13e==1 && frame_index_140>=11 && static_cast<unsigned char>(crossed()))) {
            select_sequence(2);zero_motion();y_f0=yuyuko_surface(this);return;
        }
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}

    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==4)shot811(-45.0f);if(!frame_timer_142 && frame_index_140==11)acceleration_y_100=0.4f;}return;
case 510:{
        landing();byte_17c=8;if(word_730==1)arc812_emit(16.0f,12.0,16.0);
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){phase_counter(50);counter(200,120);dispatch_character_wave_handle(10);word_730=1;}

    return;
}
case 511:{
        landing();byte_17c=8;if(word_730==1)arc812_emit(30.0f,10.0,20.0);
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){phase_counter(50);counter(200,120);dispatch_character_wave_handle(10);word_730=1;}

    return;
}
case 512:{
        if(sequence_index_13e==1)landing();
        if(!sequence_index_13e && static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);next_sequence_block();word_730=0;}
        byte_17c=8;if(word_730==1)arc812_emit(16.0f,12.0,16.0);
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==3){phase_counter(50);counter(200,120);dispatch_character_wave_handle(10);word_730=1;}if(!frame_timer_142 && frame_index_140==11)acceleration_y_100=0.5f;}

    return;
}
case 513:{
        if(sequence_index_13e==1)landing();
        if(!sequence_index_13e && static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);next_sequence_block();word_730=0;}
        byte_17c=8;if(word_730==1)arc812_emit(30.0f,10.0,20.0);
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==3){phase_counter(50);counter(200,120);dispatch_character_wave_handle(10);word_730=1;}if(!frame_timer_142 && frame_index_140==11)acceleration_y_100=0.5f;}

    return;
}
case 520:
    landing();byte_17c=1;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6)spread815(5,10.0,true);return;
case 521:
    landing();byte_17c=1;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6)spread815(8,16.0,false);return;
case 522:{
        if(sequence_index_13e==2)landing();byte_17c=1;
        if(sequence_index_13e<=1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=yuyuko_surface(this);zero_motion();return;}}
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==6)spread815(5,10.0,false);if(!frame_timer_142 && frame_index_140==17)acceleration_y_100=0.4f;}

    return;
}
case 523:{
        if(sequence_index_13e==2)landing();byte_17c=1;
        if(sequence_index_13e<=1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=yuyuko_surface(this);zero_motion();return;}}
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==6)spread815(8,16.0,false);if(!frame_timer_142 && frame_index_140==17)acceleration_y_100=0.4f;}

    return;
}
case 525:
    landing();byte_17c=5;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){field_180=1;float p[3]={0.0f,20.0f,12.0f};spawn_offset(816,95,145.0,p,3);p[2]=1.0f;dispatch_character_wave_handle(16);phase_counter(50);counter(200,120);}return;
case 526:
    landing();byte_17c=5;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){field_180=1;float p[3]={0.0f,20.0f,12.0f};spawn_offset(816,95,145.0,p,3);p[2]=1.0f;dispatch_character_wave_handle(16);phase_counter(50);counter(200,120);}return;
case 540:
    landing();byte_17c=2;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))ring820(4.0f);return;
case 541:
    landing();byte_17c=2;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))ring820(0.0f);return;
case 545:{
        landing();byte_17c=6;if(!field_6c0)byte_750=0;
        if(advance())set_action_and_finalize(0);
        if(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1) {
            phase_counter(50);counter(200,120);dispatch_character_wave_handle(18);field_180=1;
            float p[3]={0.0f,10.0f,0.0f};spawn_offset(821,55,180.0,p,3);
        }
        if(sequence_index_13e==1){int time=time_counter_144;if((time>=24 && !byte_750) || time>=20*(byte_60a+3))next_sequence_block();}

    return;
}
case 546:{
        landing();byte_17c=6;if(!field_6c4)byte_750=0;
        if(advance())set_action_and_finalize(0);
        if(!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1) {
            phase_counter(50);counter(200,120);dispatch_character_wave_handle(18);field_180=1;
            float p[3]={-90.0f,10.0f,0.0f};spawn_offset(821,55,180.0,p,3);
        }
        if(sequence_index_13e==1){int time=time_counter_144;if((time>=24 && !byte_750) || time>=20*(byte_60a+3))next_sequence_block();}

    return;
}
case 560:{
        landing();byte_17c=3;if(!field_6c0)byte_750=0;
        if(sequence_index_13e==1) {
            velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<9.0f)velocity_x_f4=9.0f;
            if(time_counter_144>=25 || (peer()->x_ec-x_ec)*static_cast<double>(facing())<=120.0){next_sequence_block();return;}
            if(time_counter_144%2==0) {
                float p[3]={static_cast<float>(yuyuko_random(360)),static_cast<float>(static_cast<float>(yuyuko_random(50))*static_cast<double>(0.1f)+5.0),1.0f};
                double base=x_ec+50.0;
                spawn(825,static_cast<float>(base-static_cast<float>(yuyuko_random(100))),
                      static_cast<float>(static_cast<float>(yuyuko_random(200))+y_f0),
                      static_cast<unsigned char>(facing_104),1,p,3);
            }
        }
        if(sequence_index_13e==2){decelerate(0.5,false);if(frame_index_140<=4 && time_counter_144%4==0){float p[3]={0.0f,0.0f,0.0f};spawn_offset(825,56,127.0,p,3);}}
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)) {
            velocity_x_f4=15.0f;counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);
            effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
        }
        if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)dispatch_character_wave_handle(11);

    return;
}
case 561:{
        landing();byte_17c=3;if(!field_6c0)byte_750=0;
        if(sequence_index_13e==1) {
            velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<11.0f)velocity_x_f4=11.0f;
            if(time_counter_144>=40 || (peer()->x_ec-x_ec)*static_cast<double>(facing())<=120.0){next_sequence_block();return;}
            if(time_counter_144%2==0) {
                float p[3]={static_cast<float>(yuyuko_random(360)),static_cast<float>(static_cast<float>(yuyuko_random(50))*static_cast<double>(0.1f)+5.0),1.0f};
                double base=x_ec+50.0;
                spawn(825,static_cast<float>(base-static_cast<float>(yuyuko_random(100))),
                      static_cast<float>(static_cast<float>(yuyuko_random(200))+y_f0),
                      static_cast<unsigned char>(facing_104),1,p,3);
            }
        }
        if(sequence_index_13e==2){decelerate(0.5,false);if(frame_index_140<=4 && time_counter_144%4==0){float p[3]={0.0f,0.0f,0.0f};spawn_offset(825,56,127.0,p,3);}}
        if(advance())set_action_and_finalize(0);
        if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)) {
            velocity_x_f4=15.0f;dispatch_character_wave_handle(14);counter(200,120);phase_counter(50);
            effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
        }
        if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)dispatch_character_wave_handle(11);

    return;
}
case 562: {
    if(sequence_index_13e==5)landing();byte_17c=3;
    velocity_y_f8-=acceleration_y_100;double next_y=velocity_y_f8+static_cast<double>(y_f0);
    if(yuyuko_surface(this)>=next_y && velocity_y_f8<0.0f && sequence_index_13e<5){select_sequence(5);acceleration_y_100=0.0f;byte_47f=0;y_f0=yuyuko_surface(this);zero_motion();return;}
    if(sequence_index_13e<2 && !field_6c4)byte_750=0;
    if(word_730>0 && (sequence_index_13e==2 || sequence_index_13e==3)) {
        if(word_730%4==1) {
            phase_counter(10);field_180=1;
            float dx=static_cast<float>((peer()->x_ec-x_ec)*static_cast<double>(facing()));
            word_734=static_cast<short>(-static_cast<short>(static_cast<int>(yuyuko_atan(peer()->y_f0-y_f0,dx))));
            if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;
            dispatch_character_wave_handle(9);
            if(word_738==1){double base=word_734+30.0;float first[3];first[0]=static_cast<float>(base-static_cast<float>(yuyuko_random_u32()%60u));first[1]=15.0f;first[2]=static_cast<float>(yuyuko_random(4));spawn_offset(808,44,85.0,first,3);}
            else{double base=word_734+30.0;float second[3];second[0]=static_cast<float>(base-static_cast<float>(yuyuko_random_u32()%60u));second[1]=15.0f;second[2]=static_cast<float>(yuyuko_random(4));spawn_offset(808,44,85.0,second,3);}
        }
        ++word_730;
    }
    if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>4 && (!byte_750 || time_counter_144>25))next_sequence_block();
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)) {
        if(byte_750==1)effect(62,static_cast<float>(x_ec-static_cast<float>(23*facing())),static_cast<float>(y_f0+107.0),static_cast<unsigned char>(facing_104),1);
        float p[3]={0.0f,0.0f,4.0f};spawn_offset(808,-23,107.0,p,3);
    }
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){word_730=1;counter(200,120);}
    if(sequence_index_13e==3 && ((time_counter_144>10 && !byte_750) || time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;return;
}
case 565:{
        if(frame_index_140>=7)landing();byte_17c=7;
        velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142) {
            if(frame_index_140==1)velocity_x_f4=-20.0f;
            if(!frame_timer_142 && frame_index_140==2){dispatch_character_wave_handle(17);counter(200,120);phase_counter(50);petal826(45,26.0);}
            if(!frame_timer_142 && frame_index_140==3)petal826(58,217.0);
            if(!frame_timer_142 && frame_index_140==4)petal826(5,266.0);
            if(!frame_timer_142 && frame_index_140==5)petal826(-64,234.0);
            if(!frame_timer_142 && frame_index_140==6)petal826(-90,132.0);
        }

    return;
}
case 566:{
        if(frame_index_140>=7)landing();byte_17c=7;
        velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142) {
            if(frame_index_140==1)velocity_x_f4=-20.0f;
            if(!frame_timer_142 && frame_index_140==2){dispatch_character_wave_handle(17);counter(200,120);phase_counter(50);petal826(45,26.0);}
            if(!frame_timer_142 && frame_index_140==3)petal826(58,217.0);
            if(!frame_timer_142 && frame_index_140==4)petal826(5,266.0);
            if(!frame_timer_142 && frame_index_140==5)petal826(-64,234.0);
            if(!frame_timer_142 && frame_index_140==6)petal826(-90,132.0);
        }

    return;
}
case 567:
    if(sequence_index_13e==2)landing();else{velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);select_sequence(2);return;}}
    byte_17c=7;velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;
    if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==2){velocity_x_f4=-20.0f;velocity_y_f8=10.0f;acceleration_y_100=0.35f;dispatch_character_wave_handle(17);counter(200,120);phase_counter(50);petal826(80,40.0);}
        if(!frame_timer_142 && frame_index_140==3)petal826(95,230.0);
        if(!frame_timer_142 && frame_index_140==4)petal826(20,290.0);
        if(!frame_timer_142 && frame_index_140==5)petal826(-80,250.0);
        if(!frame_timer_142 && frame_index_140==6)petal826(-110,160.0);
    }
    if(sequence_index_13e==1 && time_counter_144>=50)set_action_and_finalize(9);return;
case 599:
    if(word_730>0 && frame_index_140<7 && word_730<12) {
        unsigned angle=yuyuko_random_u32()%35u;word_734=static_cast<short>(angle);
        float p[3]={static_cast<float>(-20-static_cast<int>(angle)),static_cast<float>(static_cast<short>(yuyuko_random_u32()%5u+10)),0.0f};
        spawn(807,static_cast<float>(20*facing()*(word_730+1)+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),1,p,3);
        p[0]=static_cast<float>(yuyuko_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        spawn(801,static_cast<float>(20*facing()*(word_730+1)+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),1,p,3);
        if(word_730==1){dispatch_character_wave_handle(0);counter(200,120);}++word_730;
    }
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)word_730=1;return;

case 600:
    landing();texture(2,2);if(sequence_index_13e==2 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2))time_counter_144=0;
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2)spell_flash(0,125.0,2);if(!frame_timer_142 && frame_index_140==4)ring_spell(850,false);}return;
case 601:
    landing();texture(2,2);if(sequence_index_13e==1 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(851,105,146.0,p,3);dispatch_character_wave_handle(51);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2)spell_flash(-40,150.0,1);return;
case 651:
    if(sequence_index_13e==4)landing();if(sequence_index_13e<=2)texture(2,2);
    if(sequence_index_13e==2 || sequence_index_13e==3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yuyuko_surface(this);select_sequence(4);return;}}
    if(sequence_index_13e==1 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(851,105,146.0,p,3);dispatch_character_wave_handle(51);}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2){field_73c=velocity_x_f4;field_740=velocity_y_f8;zero_motion();spell_flash(-40,150.0,1);}if(!frame_timer_142 && frame_index_140==3){velocity_x_f4=field_73c;velocity_y_f8=field_740;}}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==1)acceleration_y_100=0.2f;return;
case 602:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==7){float p[3]={0.0f,25.0f,0.0f};spawn_offset(852,85,140.0,p,3);dispatch_character_wave_handle(52);}if(!frame_timer_142 && frame_index_140==2)spell_flash(-80,145.0,2);}return;
case 603:
    landing();texture(2,2);if(sequence_index_13e==2 && word_732>=60){next_sequence_block();return;}
    if(word_730==1){if(word_732%30==0 && field_740<6.0f){ring_spell(853,true);field_740=static_cast<float>(field_740+5.0);}++word_732;}
    if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2))time_counter_144=0;
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2)spell_flash(0,125.0,4);if(!frame_timer_142 && frame_index_140==4)word_730=1;}return;
case 604:
    landing();texture(2,2);if(sequence_index_13e==1 && time_counter_144>=24){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){float p[3]={0.0f,0.0f,4.0f};spawn(854,peer()->x_ec,0.0f,static_cast<unsigned char>(facing_104),1,p,3);dispatch_character_wave_handle(54);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1)spell_flash(10,130.0,5);return;
case 605:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==7){float p[3]={0.0f,25.0f,0.0f};spawn_offset(855,85,140.0,p,3);dispatch_character_wave_handle(52);}if(!frame_timer_142 && frame_index_140==2)spell_flash(-80,145.0,4);}return;
case 606:
    landing();texture(2,2);if(sequence_index_13e==2 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2))time_counter_144=0;
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2)spell_flash(0,125.0,2);if(!frame_timer_142 && frame_index_140==4){float p[3];for(float n=0.0f;n<12.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*30.0);p[1]=4.0f;p[2]=12.0f;orbit_spell(856,p,false);}dispatch_character_wave_handle(10);}}return;
case 607:
    landing();texture(2,2);
    if(sequence_index_13e==1){if(time_counter_144%15==0 && word_730<=3)pair857(false);if(time_counter_144>=60){next_sequence_block();return;}}
    if(sequence_index_13e==2 && time_counter_144>=0){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){spell_flash(-40,153.0,4);float p[3]={0.0f,0.0f,14.0f};spawn(857,static_cast<float>(x_ec-20*facing()),y_f0,static_cast<unsigned char>(facing_104),-1,p,3);}return;
case 657:
    if(sequence_index_13e==5)landing();if(sequence_index_13e<=2)texture(2,2);
    if(sequence_index_13e==3 || sequence_index_13e==4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();y_f0=yuyuko_surface(this);return;}}
    if(sequence_index_13e==1){if(time_counter_144%15==0 && word_730<=3)pair857(true);if(time_counter_144>=60){next_sequence_block();return;}}
    if(sequence_index_13e==2 && time_counter_144>=0){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==2))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){spell_flash(-40,153.0,4);float p[3]={0.0f,0.0f,14.0f};spawn(857,static_cast<float>(x_ec-20*facing()),y_f0,static_cast<unsigned char>(facing_104),-1,p,3);}
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2)acceleration_y_100=0.25f;return;

case 608:
    landing();texture(2,2);if(sequence_index_13e==2 && time_counter_144>=32){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){dispatch_character_wave_handle(13);field_180=1;float p[3];for(int angle=0;angle<360;angle+=40){p[0]=static_cast<float>(angle);p[1]=600.0f;p[2]=1.0f;spawn(858,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),static_cast<unsigned char>(facing_104),1,p,3);}}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(0,150.0,3);return;
case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){event(55);effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);effect(141,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1);effect(142,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);}return;
case 696:
    landing();decelerate(0.5,true);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e){if(!frame_timer_142){if(frame_index_140==4){mode848(4.0f);velocity_x_f4=10.0f;byte_47e=0;}if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(0);}if(frame_index_140>=6)decelerate(static_cast<double>(1.2f),false);}return;
case 707:
    if(velocity_x_f4>12.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<12.0f)velocity_x_f4=12.0f;}
    if(advance()){set_action_and_finalize(700);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){velocity_x_f4=15.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);if(time_counter_144>30){next_sequence_block();return;}}
    if(sequence_index_13e==2)decelerate(0.5,false);return;
case 708:
    if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!static_cast<unsigned char>(yuyuko_on_surface(this))) {
        if(time_counter_144%5==0)dash_dust(true);
        velocity_y_f8=static_cast<float>(velocity_y_f8-0.5);double next_y=velocity_y_f8+static_cast<double>(y_f0);
        if(yuyuko_surface(this)>=next_y && velocity_y_f8<0.0f){velocity_y_f8=0.0f;y_f0=yuyuko_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(700);return;}
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){velocity_x_f4=-14.0f;velocity_y_f8=4.0f;dash_effects(true,80.0,false);}return;
case 709:
    if(!sequence_index_13e){velocity_y_f8-=acceleration_y_100;double next_y=velocity_y_f8+static_cast<double>(y_f0);if(yuyuko_surface(this)>=next_y && velocity_y_f8<0.0f){next_sequence_block();y_f0=yuyuko_surface(this);velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e==1){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<=0.0f){velocity_x_f4=0.0f;if(++word_730>=2){next_sequence_block();velocity_x_f4=-5.0f;velocity_y_f8=5.0f;}}}
    if(sequence_index_13e==2 || sequence_index_13e==3){velocity_y_f8=static_cast<float>(velocity_y_f8-0.25);double next_y=velocity_y_f8+static_cast<double>(y_f0);if(yuyuko_surface(this)>=next_y && velocity_y_f8<0.0f){zero_motion();y_f0=yuyuko_surface(this);next_sequence_block();return;}}
    if(advance())set_action_and_finalize(700);return;
case 710: {
    if(sequence_index_13e==1) {
        float p[3];
        switch(g_match_identifier) {
        case 3:if(!time_counter_144 || time_counter_144==60 || time_counter_144==120)difficulty900(p,false);if(time_counter_144>=180){next_sequence_block();return;}break;
        case 2:if(!time_counter_144 || time_counter_144==60)difficulty900(p,false);if(time_counter_144>=150){next_sequence_block();return;}break;
        case 1:if(!time_counter_144)difficulty900(p,true);if(time_counter_144>=120){next_sequence_block();return;}break;
        case 0:if(!time_counter_144)difficulty900(p,true);if(time_counter_144>=90){next_sequence_block();return;}break;
        }
    }
    if(advance())set_action_and_finalize(700);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(900,50,170.0,p,3);p[2]=5.0f;spawn_offset(900,50,170.0,p,3);}return;
}
case 720: {
    if(!sequence_index_13e && frame_index_140==2 && velocity_y_f8>0.0f){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<1.0f)velocity_y_f8=1.0f;}
    if(sequence_index_13e==1) {
        float p[3];
        switch(g_match_identifier) {
        case 3:difficulty901(p,5,10.0);break;
        case 2:difficulty901(p,10,12.0);break;
        case 1:difficulty901(p,15,15.0);break;
        case 0:difficulty901(p,20,20.0);break;
        default:goto difficulty901_done;
        }
        if(time_counter_144>=210){next_sequence_block();return;}
    }
difficulty901_done:
    if(sequence_index_13e==2 || sequence_index_13e==3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(4);zero_motion();y_f0=yuyuko_surface(this);return;}}
    if(advance())set_action_and_finalize(700);
    if(!time_counter_144){if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))zero_motion();if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==3)){double y=y_f0;if(yuyuko_surface(this)>=y)set_action_and_finalize(700);else acceleration_y_100=0.2f;}}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){velocity_y_f8=static_cast<float>(static_cast<float>(yuyuko_random(13))+2.0);acceleration_y_100=0.25f;}return;
}
case 725:
    fade_alpha();if(advance())set_action_and_finalize(700);
    if(!time_counter_144){if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))dispatch_character_wave_handle(55);if(!time_counter_144){if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==3)){x_ec=static_cast<float>(static_cast<float>(yuyuko_random(300))+250.0+x_ec);dispatch_character_wave_handle(55);}if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==4))return;}}
    // Native 56B556..56B574 falls through to 726 except entry 4.
case 726:
    fade_alpha();if(advance())set_action_and_finalize(700);
    if(!time_counter_144){if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1))dispatch_character_wave_handle(55);if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==3)){double x=x_ec;x_ec=static_cast<float>(x-(static_cast<float>(yuyuko_random(300))+250.0));dispatch_character_wave_handle(55);}}return;
case 730:
    if(sequence_index_13e>=1){velocity_y_f8-=acceleration_y_100;if(++word_730>=60){zero_motion();set_action_and_finalize(731);return;}}
    if(advance())set_action_and_finalize(700);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){facing_104=-1;velocity_x_f4=static_cast<float>((640.0-x_ec)/60.0*-1.0);velocity_y_f8=18.5f;acceleration_y_100=0.5f;}return;
case 731:
    x_ec=640.0f;
    if(!sequence_index_13e && frame_index_140<=2 && time_counter_144%5==0){
        float p[3]={static_cast<float>(yuyuko_random(360)),static_cast<float>(static_cast<float>(yuyuko_random(250))+50.0),3.0f};
        spawn(922,static_cast<float>(yuyuko_cosine(-p[0])*p[1]*facing_104+x_ec),
              static_cast<float>(yuyuko_cosine(-p[0])*p[1]+(static_cast<double>(y_f0)+100.0)),
              static_cast<unsigned char>(facing_104),-1,p,3);
    }
    if(sequence_index_13e==1 && time_counter_144>=120){next_sequence_block();return;}
    if(sequence_index_13e==2){y_f0=static_cast<float>(yuyuko_sine(static_cast<float>(time_counter_144*3.0))*field_744+field_740);field_744=static_cast<float>(field_744+static_cast<double>(0.1f));if(field_744>=60.0f)field_744=60.0f;}
    if(advance())set_action_and_finalize(700);
    if((!time_counter_144 && !frame_timer_142 && !frame_index_140 && sequence_index_13e==1)){finish_story_state();float p[3]={0.0f,0.0f,4.0f};spawn_offset(922,0,100.0,p,3);p[2]=0.0f;spawn(922,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);dispatch_character_wave_handle(17);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,2.0f};spawn(922,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1,p,3);dispatch_character_wave_handle(18);}return;
case 770:
    if(advance())set_action_and_finalize(700);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7)finish_story_state();return;
case 795:
    if(!sequence_index_13e){velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.3f));if(static_cast<unsigned char>(crossed())){select_sequence(1);event(30);y_f0=yuyuko_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:
    if(sequence_index_13e<=1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);event(30);y_f0=yuyuko_surface(this);velocity_y_f8=0.0f;return;}}
    if(advance())set_action_and_finalize(0);return;
case 798:
    if(sequence_index_13e<=1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);event(30);y_f0=yuyuko_surface(this);velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;x_ec=800.0f;}if(x_ec<800.0f)x_ec=800.0f;}
    if(advance())set_action_and_finalize(700);return;
default:common_update();return;
    }
    advance();
}
}
