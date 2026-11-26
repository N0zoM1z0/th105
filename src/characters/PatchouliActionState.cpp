#include "characters/PatchouliActionState.hpp"
// Complete JP1.06a50F200 candidate, not selected or exact.
// See docs/PATCHOULI_ACTION_STATE_2026_10_27.md.
namespace th105 {
void PatchouliActionStateView::dispatch_action_state_vslot28()
{
    word_7a0=0;word_7a2=103;
    if(word_7a4>0) {
        --word_7a4;
        if(action_id_13c>=600 && action_id_13c<=689 && (action_id_13c!=605 || sequence_index_13e<1))word_7a4=0;
        if(field_168->word_174<=0 || related_170->word_174<=0)word_7a4=0;
    }
    if(field_7b4>0.0f) {
        field_7b4=static_cast<float>(field_7b4-(static_cast<double>(0.4f)-byte_606*static_cast<double>(0.05f)));
        if(field_7b4<0.0f)field_7b4=0.0f;
        field_6ac=-field_7b4;
        if((x_ec<related_170->x_ec && related_170->facing_104==1) ||
           (x_ec>related_170->x_ec && related_170->facing_104==-1))field_6ac=field_7b4;
    }
    if(word_7b0>0)--word_7b0;
    if(action_id_13c>149 && action_id_13c<159 && !byte_751) {
        byte_751=1;
        if(action_id_13c>149 && action_id_13c<154)
            spawn(998,static_cast<float>(57*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+94.0),static_cast<unsigned char>(facing_104),1,0,0);
        if(action_id_13c>153 && action_id_13c<158)
            spawn(998,static_cast<float>(57*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+60.0),static_cast<unsigned char>(facing_104),1,0,0);
        if(action_id_13c==158)
            spawn(998,static_cast<float>(57*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,0,0);
    }
    if(action_id_13c==710 && sequence_index_13e==1) {
        ++word_734;
        switch(g_match_identifier) {
        case 3:
            field_740=static_cast<float>(field_740+static_cast<double>(0.05f));
            if(field_740>=5.0f)field_740=5.0f;
            field_73c=field_740+field_73c;field_744-=field_740;break;
        case 2:
            field_740=static_cast<float>(field_740+static_cast<double>(0.04f));
            if(field_740>=4.0f)field_740=4.0f;
            field_73c=field_740+field_73c;field_744-=field_740;break;
        case 1:
            field_740=static_cast<float>(field_740+static_cast<double>(0.03f));
            if(field_740>=4.0f)field_740=4.0f;
            field_73c=field_740+field_73c;field_744-=field_740;break;
        case 0:
            field_740=static_cast<float>(field_740+static_cast<double>(0.02f));
            if(field_740>=2.0f)field_740=2.0f;
            field_73c=field_740+field_73c;field_744-=field_740;break;
        }
        if(word_734%2==0 && (velocity_y_f8>0.0f || (velocity_y_f8<0.0f && y_f0>=100.0))) {
            float p[3]={static_cast<float>(static_cast<float>(patchouli_random(10))+field_73c-5.0),25.0f,0.0f};
            orbit900(p,field_73c);
            for(int n=2;n;--n) {
                p[0]=static_cast<float>(patchouli_random(360));p[1]=static_cast<float>(static_cast<float>(patchouli_random(4))+8.0);p[2]=4.0f;
                orbit900(p,field_73c);
            }
            if(g_match_identifier==3 || g_match_identifier==2) {
                float q[3]={static_cast<float>(static_cast<float>(patchouli_random(10))+field_744-5.0),25.0f,2.0f};
                orbit900(q,field_744);
                for(int n=2;n;--n) {
                    q[0]=static_cast<float>(patchouli_random(360));q[1]=static_cast<float>(static_cast<float>(patchouli_random(4))+8.0);q[2]=5.0f;
                    orbit900(q,field_744);
                }
            }
        }
    }
    if(word_186 || related_170->word_48c)return;
    switch(action_id_13c) {
case 0:
    landing();if(velocity_x_f4==0.0f)byte_47e=0;idle_motion();break;
case 1:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:
    landing();idle_motion();break;
case 3:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:
    landing();velocity_x_f4=4.0f;break;
case 5:
    landing();velocity_x_f4=-4.0f;break;
case 6:{
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !byte_47e)zero_motion();
        }
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
            }
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)next_sequence_block();
        advance();
        if(entry(1)){velocity_x_f4=0.0f;velocity_y_f8=13.0f;acceleration_y_100=0.4f;byte_47e=0;}
    return;}
case 7:{
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !byte_47e)zero_motion();
        }
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
            }
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)next_sequence_block();
        advance();
        if(entry(1)){velocity_x_f4=3.0f;velocity_y_f8=13.0f;acceleration_y_100=0.4f;byte_47e=0;}
    return;}
case 8:{
        if(!sequence_index_13e) {
            landing();
            if(!sequence_index_13e && !byte_47e)zero_motion();
        }
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
            }
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)next_sequence_block();
        advance();
        if(entry(1)){velocity_x_f4=-4.0f;velocity_y_f8=13.0f;acceleration_y_100=0.4f;byte_47e=0;}
    return;}
case 9:
    if(acceleration_y_100==0.0f)acceleration_y_100=0.6f;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;}
    break;
case 10:
    landing();zero_motion();
    if(advance()){if(field_6b8)set_action_and_finalize(2);else set_action_and_finalize(0);}
    return;
case 197:
    landing();
    if(advance()) {
        if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(0);
        if(field_6b8>0)set_action_and_finalize(1);
    }
    if(frame_timer_142)return;
    if(frame_index_140==6)ground_face();
    if(!frame_timer_142 && frame_index_140==6)velocity_x_f4=0.0f;
    return;
case 198:
    landing();
    if(advance()) {
        if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(0);
        if(field_6b8>0)set_action_and_finalize(1);
    }
    if(!frame_timer_142) {
        if(frame_index_140==6)ground_face();
        if(!frame_timer_142 && frame_index_140==6)velocity_x_f4=0.0f;
    }
    return;
case 199:
    landing();
    if(advance()) {
        if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(0);
        if(field_6b8>0)set_action_and_finalize(1);
    }
    if(!frame_timer_142 && frame_index_140==5)ground_face();
    return;
case 200:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        if(field_6b8<0) {
            if(field_6b4*facing_104<=0)set_action_and_finalize(211);else set_action_and_finalize(212);
            return;
        }
        ++word_730;
        if((field_6b4*facing_104<=0 && word_730>=5) || word_730>=60){set_action_and_finalize(204);return;}
    }
    if(entry(1)){velocity_x_f4=8.5f;dash_effects(false,80.0,true);}
    return;
case 201:
    if(sequence_index_13e==2) {
        landing();
        if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    }
    if(!static_cast<unsigned char>(patchouli_on_surface(this)) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<2) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=patchouli_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && frame_index_140==1 && !frame_timer_142) {
        velocity_x_f4=-10.0f;velocity_y_f8=3.0f;acceleration_y_100=0.3f;dash_effects(true,80.0,false);
    }return;
case 202:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=patchouli_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2) {
        velocity_x_f4=8.0f;velocity_y_f8=3.0f;acceleration_y_100=0.4f;dash_effects(false,110.0,true);
    }
    if(entry(2))flip();
    return;
case 203:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=patchouli_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1) {
        velocity_x_f4=-8.0f;velocity_y_f8=3.0f;acceleration_y_100=0.4f;dash_effects(true,120.0,false);
    }
    if(entry(2))flip();
    return;
case 204:
    landing();velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
    if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}
    if(advance()){set_action_and_finalize(0);byte_47e=0;}
    return;
case 208:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(patchouli_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(entry(1)) {
            velocity_x_f4=0.0f;velocity_y_f8=19.0f;acceleration_y_100=0.6f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }
    return;}
case 209:
case 212:
case 221:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(patchouli_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(entry(1)) {
            velocity_x_f4=8.5f;velocity_y_f8=15.0f;acceleration_y_100=0.6f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }
    return;}
case 210:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(patchouli_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(entry(1)) {
            velocity_x_f4=-8.5f;velocity_y_f8=15.0f;acceleration_y_100=0.6f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }
    return;}
case 211:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(patchouli_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(entry(1)) {
            velocity_x_f4=2.0f;velocity_y_f8=19.0f;acceleration_y_100=0.6f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }
    return;}
case 214: {
    if(advance()){set_action_and_finalize(9);return;}
    if(entry(1)) {
        event(31);
        if(field_740>=135.0f || field_740<=-135.0f){select_sequence(6);return;}
        if(field_740>45.0f || field_740<-45.0f){select_sequence(4);return;}
    }
    if(entry(9))select_sequence(5);
    if(entry(10) || entry(11)){set_action_and_finalize(9);return;}
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
            if(!field_4b8)field_740=static_cast<float>(field_740+5.0);
            else field_740=static_cast<float>(field_740+4.0);
        }
        if(word_734<0) {
            if(!field_4b8)field_740=static_cast<float>(field_740-5.0);
            else field_740=static_cast<float>(field_740-4.0);
        }
        velocity_x_f4=static_cast<float>(patchouli_cosine(field_740)*field_73c);
        velocity_y_f8=static_cast<float>(patchouli_sine(field_740)*field_73c);
        if(y_f0>680.0f && velocity_y_f8>0.0f)velocity_y_f8=0.0f;
        if(!field_4b8)counter(4,1);else counter(8,1);
        if((sequence_index_13e==1 || sequence_index_13e==2) && (field_740>60.0f || field_740<-60.0f)){select_sequence(3);return;}
        if(sequence_index_13e==4 || sequence_index_13e==5) {
            if(field_740<=45.0f && field_740>=-45.0f){select_sequence(1);return;}
            if(field_740>=135.0f || field_740<=-135.0f){select_sequence(6);return;}
        }
        if((sequence_index_13e==6 || sequence_index_13e==7) && field_740<120.0f && field_740>-120.0f){select_sequence(8);return;}
        int held=field_6c8;
        if(!((held || word_736<=10) && word_482>0)) {
            if(!((held || word_736<=10) && word_482>0)) {
                if(sequence_index_13e==1 || sequence_index_13e==2)release_flight(9);
                if(sequence_index_13e==3) {
                    word_730=frame_index_140;
                    if(static_cast<unsigned char>(facing_104)==1) {
                        if(x_ec>related_170->x_ec) {
                            facing_104=-1;velocity_x_f4=-velocity_x_f4;
                            select_sequence(9);
                            set_sequence_frame(static_cast<unsigned short>(word_730));
                        } else {
                            select_sequence(9);
                            set_sequence_frame(static_cast<unsigned short>(word_730));
                        }
                    } else {
                        if(x_ec<related_170->x_ec) {
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
                        if(x_ec>related_170->x_ec) {
                            facing_104=-1;velocity_x_f4=-velocity_x_f4;
                            select_sequence(11);
                            set_sequence_frame(static_cast<unsigned short>(word_730));return;
                        }
                        select_sequence(11);
                        set_sequence_frame(static_cast<unsigned short>(word_730));return;
                    }
                    if(x_ec<related_170->x_ec) {
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
        y_f0=patchouli_surface(this);velocity_y_f8=0.0f;acceleration_y_100=0.0f;
        if(sequence_index_13e<9){reset_action_scratch();set_action_and_finalize(215);}
        else {set_action_and_finalize(10);zero_motion();}
    }
    return;

}

case 215:
    landing();
    if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);
    return;
case 220:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(patchouli_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(entry(1)) {
            velocity_x_f4=0.0f;velocity_y_f8=19.0f;acceleration_y_100=0.6f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }
    return;}
case 222:{
        if(!sequence_index_13e)landing();
        if(static_cast<unsigned char>(crossed())) {
            set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;
        }
        if(static_cast<unsigned char>(patchouli_on_surface(this)) || velocity_y_f8>0.0f)word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
        advance();
        if(entry(1)) {
            velocity_x_f4=-8.5f;velocity_y_f8=15.0f;acceleration_y_100=0.6f;byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }
    return;}
case 223:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        ++word_730;
        if((field_6b4*facing_104<=0 && word_730>=15) || word_730>=60){set_action_and_finalize(204);return;}
    }
    if(entry(1)){velocity_x_f4=6.0f;dash_effects(false,80.0,true);}
    return;
case 224:
    if(sequence_index_13e==2) {
        landing();
        if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    }
    if(!static_cast<unsigned char>(patchouli_on_surface(this)) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<2) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=patchouli_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && frame_index_140==1 && !frame_timer_142) {
        velocity_x_f4=-10.0f;velocity_y_f8=3.0f;acceleration_y_100=0.3f;dash_effects(true,80.0,false);
    }return;
case 225:
    if(sequence_index_13e>0) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=patchouli_surface(this);set_action_and_finalize(10);return;}
    }
    if(sequence_index_13e>=2 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(entry(1)){velocity_x_f4=-11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(true,120.0,false);}
    return;
case 226:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=patchouli_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e==1 && time_counter_144%5==0)dash_dust(false);
    advance();
    if(!time_counter_144) {
        if(entry(1)){word_730=0;velocity_x_f4=8.0f;velocity_y_f8=3.0f;acceleration_y_100=0.4f;dash_effects(false,110.0,true);}
        if(entry(2))flip();
    }
    return;

case 300:
    landing();
    if(directional(0))return;
    if(byte_47e) {
        velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
        if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}
    }
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){event(27);byte_47e=0;}
    return;
case 301:
    landing();if(directional(0))return;
    if(byte_47e) {
        velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
        if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}
    }
    if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3) {
            if(byte_750==1) {
                next_sequence_block();int direction=static_cast<unsigned char>(facing_104);
                effect(62,static_cast<float>(x_ec-static_cast<double>(15*static_cast<signed char>(direction))),
                       static_cast<float>(y_f0+130.0),direction,1);return;
            }
            float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);
        }
        if(!frame_timer_142 && frame_index_140==5){event(27);byte_47e=0;}
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1){float p[3]={0.0f,0.0f,1.0f};spawn_offset(848,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==2){event(27);byte_47e=0;}
    }
    return;
case 302:
    landing();if(directional(1))return;
    if(!field_6bc)byte_750=0;
    velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4) {
            if(byte_750==1) {
                next_sequence_block();int direction=static_cast<unsigned char>(facing_104);
                effect(62,static_cast<float>(x_ec-static_cast<double>(65*static_cast<signed char>(direction))),
                       static_cast<float>(y_f0+165.0),direction,1);return;
            }
            velocity_x_f4=10.0f;
        }
        if(!frame_timer_142 && frame_index_140==6)event(29);
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1)velocity_x_f4=13.0f;
        if(!frame_timer_142 && frame_index_140==3) {
            event(29);float p[3];p[2]=0.0f;p[1]=12.0f;ring820_ground(p,77);
        }
    }
    return;
case 303:
    landing();if(directional(0))return;
    if(static_cast<signed char>(byte_47e)>0) {
        velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.6f));
        if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}
    }
    if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==3)event(27);
    return;
case 304:
    landing();if(directional(1))return;
    if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(2);
    if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e) {
        if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
        if(!frame_timer_142 && frame_index_140==3) {
            if(byte_750==1) {
                next_sequence_block();effect(62,x_ec,static_cast<float>(y_f0+50.0),static_cast<unsigned char>(facing_104),1);return;
            }
            velocity_x_f4=12.0f;event(29);
        }
    }
    if(sequence_index_13e==1) {
        if(!frame_timer_142) {
            if(frame_index_140==2){velocity_x_f4=15.0f;event(29);}
            if(!frame_timer_142 && frame_index_140==4)velocity_x_f4=0.0f;
        }
        if(frame_index_140>=2 && frame_index_140<=7) {
            velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<10.0f)velocity_x_f4=10.0f;
            if(time_counter_144%10==0){float p[3];p[2]=0.0f;p[1]=10.0f;ring820_ground(p,77);}
        }
        if(frame_index_140>=8) {
            velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.3f));
            if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
        }
    }
    return;
case 305:
    landing();if(directional(1))return;
    if(frame_index_140>=5){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5)event(29);
    return;
case 306:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;}
    if(field_180){if(++word_730>=2 && byte_184>0){field_180=0;word_730=0;}}
    if(advance())set_action_and_finalize(9);
    if(!frame_timer_142) {
        if(frame_index_140==1)event(27);
        if(!frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,6.0f};spawn_offset(848,63,53.0,p,3);}
    }
    return;
case 307:
    if(!field_6bc)byte_750=0;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())) {
        if(frame_index_140>=12){set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;}
        velocity_y_f8=0.0f;
    }
    if(advance())set_action_and_finalize(9);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(sequence_index_13e || frame_timer_142)return;
    if(frame_index_140==5){dispatch_character_wave_handle(18);float p[3]={-10.0f,20.0f,5.0f};spawn_offset(848,96,127.0,p,3);}
    if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.6f;
    return;
case 308:
    if(!field_6bc)byte_750=0;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3 && byte_750==1) {
            next_sequence_block();int direction=static_cast<unsigned char>(facing_104);
            effect(62,static_cast<float>(20*static_cast<signed char>(direction)+static_cast<double>(x_ec)),
                   static_cast<float>(y_f0+105.0),direction,1);return;
        }
        if(frame_index_140==3) {
            event(28);velocity_x_f4=-4.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;
            float p[3]={0.0f,0.0f,7.0f};spawn_offset(848,40,47.0,p,3);
        }
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1) {
        event(28);velocity_x_f4=-4.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;
        float p[3]={0.0f,1.0f,7.0f};spawn_offset(848,40,47.0,p,3);
    }
    return;
case 309:
    if(!field_6bc)byte_750=0;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=patchouli_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        dispatch_character_wave_handle(18);velocity_x_f4=static_cast<float>(velocity_x_f4*0.5);velocity_y_f8=3.0f;acceleration_y_100=0.0f;
        float p[3]={-85.0f,20.0f,12.0f};spawn_offset(848,34,122.0,p,3);
    }
    if(sequence_index_13e==1 && time_counter_144>=30){next_sequence_block();acceleration_y_100=0.5f;}
    return;
case 310:
    if(field_180){if(++word_730>5){field_180=0;word_730=0;}}
    if(sequence_index_13e==1) {
        if(!time_counter_144)velocity_x_f4=15.0f;
        if(time_counter_144%8==0)event(27);
        if(field_180){if(++word_730>5){field_180=0;word_730=0;}}
        if(time_counter_144>30){next_sequence_block();velocity_y_f8=6.0f;velocity_x_f4=static_cast<float>(velocity_x_f4*0.5);}
    }
    if(sequence_index_13e==2) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;y_f0=patchouli_surface(this);set_action_and_finalize(9);return;}
    }
    if(advance())set_action_and_finalize(9);
    return;
case 320:
    landing();if(directional(0))return;
    velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    if(field_180){if(++word_730>=5 && byte_184>0){field_180=0;word_730=0;}}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==4){event(28);velocity_x_f4=12.5f;byte_47e=0;}
        if(!frame_timer_142 && frame_index_140==5){float p[3]={0.0f,0.0f,9.0f};spawn_offset(848,122,133.0,p,3);}
    }
    return;
case 321:
    landing();if(directional(1))return;
    if(frame_index_140<=6){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    else {velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==6) {
            event(29);float p[3]={0.0f,0.0f,10.0f};spawn_offset(848,101,111.0,p,3);
            p[2]=0.0f;p[1]=12.0f;ring820_ground(p,101);
        }
        if(!frame_timer_142 && frame_index_140==7){velocity_x_f4=static_cast<float>(velocity_x_f4-10.0);byte_47e=0;}
    }
    return;
case 322:
    landing();if(directional(1))return;
    if(frame_index_140>5){velocity_x_f4=static_cast<float>(velocity_x_f4-3.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==4){velocity_x_f4=15.0f;float p[3]={0.0f,0.0f,0.0f};spawn_offset(819,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==5){event(29);byte_47e=0;}
    }
    return;
case 400:
    landing();if(!field_6c0)byte_750=0;
    ground_fan_tick(63,117.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        if(byte_750==1){charge_effect(-12,100.0);return;}
        aim(-10.0f,10.0f);word_730=1;counter(200,40);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1){aim(-10.0f,10.0f);word_730=1;counter(200,40);}
    return;
case 401:
    landing();if(!field_6c0)byte_750=0;
    ground_fan_tick(100,136.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4 && byte_750==1){charge_effect(-24,102.0);return;}
        if(frame_index_140==5){aim(-50.0f,-30.0f);word_730=1;counter(200,40);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){aim(-50.0f,-30.0f);word_730=1;counter(200,40);}
    return;
case 402:
    landing();if(!field_6c0)byte_750=0;
    ground_fan_tick(103,63.0);
    if(advance())set_action_and_finalize(2);
    if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        if(byte_750==1){charge_effect(55,132.0);return;}
        aim(-10.0f,10.0f);word_730=1;counter(200,40);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1){aim(-10.0f,10.0f);word_730=1;counter(200,40);}
    return;
case 404:
    air_fan_motion();air_fan_tick(70,115.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4) {
            if(byte_750==1){charge_effect(40,190.0);return;}
            aim(-10.0f,10.0f);word_730=1;counter(200,40);
        }
        if(!frame_timer_142 && frame_index_140==13)acceleration_y_100=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1){aim(-10.0f,10.0f);word_730=1;counter(200,40);}
        if(!frame_timer_142 && frame_index_140==10)acceleration_y_100=0.6f;
    }
    return;
case 406:
    air_fan_motion();air_fan_tick(50,70.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142) {
            if(frame_index_140==4 && byte_750==1){charge_effect(40,190.0);return;}
            if(frame_index_140==5){aim(40.0f,60.0f);word_730=1;counter(200,40);}
        }
        if(!frame_timer_142 && frame_index_140==11)acceleration_y_100=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==2){aim(40.0f,60.0f);word_730=1;counter(200,40);}
        if(!frame_timer_142 && frame_index_140==8)acceleration_y_100=0.6f;
    }
    return;
case 407:
    landing();if(!field_6c0)byte_750=0;
    if(word_730>0) {
        word_730=0;field_180=1;
        if(!sequence_index_13e) {
            float p[3];
            for(float n=0.0f;n<4.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(n*40.0-60.0);p[1]=15.0f;p[2]=2.0f;spawn_offset(800,63,117.0,p,3);
            }
        } else {
            float p[3];
            for(float n=0.0f;n<7.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(n*25.0-75.0);p[1]=15.0f;p[2]=2.0f;spawn_offset(800,63,117.0,p,3);
            }
        }
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        if(byte_750==1){charge_effect(-12,100.0);return;}
        aim(-10.0f,10.0f);word_730=1;dispatch_character_wave_handle(0);counter(200,40);phase_counter(30);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1) {
        aim(-10.0f,10.0f);word_730=1;dispatch_character_wave_handle(0);counter(200,40);phase_counter(30);
    }
    return;
case 408:
    if(directional(1))return;
    landing();
    if(frame_index_140>=7){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(field_180){if(++word_730>=5 && byte_184>0){field_180=0;word_730=0;}}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==4){event(28);float p[3]={-30.0f,20.0f,8.0f};spawn_offset(848,96,127.0,p,3);}
    return;
case 409:
    air_fan_motion();burst800(70,115.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4) {
            if(byte_750==1){charge_effect(40,190.0);return;}
            aim(-10.0f,10.0f);word_730=1;counter(200,40);dispatch_character_wave_handle(0);
        }
        if(!frame_timer_142 && frame_index_140==13)acceleration_y_100=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1){aim(-10.0f,10.0f);word_730=1;counter(200,40);dispatch_character_wave_handle(0);}
        if(!frame_timer_142 && frame_index_140==10)acceleration_y_100=0.6f;
    }
    return;
case 410:
    landing();if(sequence_index_13e<2 && !field_6c4)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5) {
        field_180=1;phase_counter(50);dispatch_character_wave_handle(1);
        // Packet initializations precede counter in the native call path.
        float p[3];p[1]=5.0f;p[2]=0.0f;counter(200,48);
        for(int angle=0;angle<315;angle+=45){p[0]=static_cast<float>(angle);spawn_offset(801,100,140.0,p,3);}
        p[2]=2.0f;spawn_offset(801,100,140.0,p,3);
    }
    return;
case 411:
    landing();if(!field_6c4)byte_750=0;
    pair801_tick(63,117.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        if(byte_750==1){charge_effect(-12,100.0);return;}
        word_730=1;counter(200,48);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1){word_730=1;counter(200,48);}
    return;
case 412:
    landing();if(!field_6c4)byte_750=0;
    if(advance())set_action_and_finalize(2);
    if(!sequence_index_13e && frame_index_140==5 && !frame_timer_142) {
        dispatch_character_wave_handle(7);float p[3]={10.0f,15.0f,9.0f};
        field_180=1;counter(200,48);phase_counter(50);spawn_offset(801,100,56.0,p,3);
    }
    return;
case 414:
    if(sequence_index_13e==1)landing();
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<=0) {
        select_sequence(1);byte_47f=0;y_f0=patchouli_surface(this);zero_motion();return;
    }
    if(sequence_index_13e<2 && !field_6c4)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(frame_timer_142)return;
    if(frame_index_140==5){field_180=1;counter(200,48);phase_counter(50);dispatch_character_wave_handle(1);circle801();}
    if(!frame_timer_142 && frame_index_140==15)acceleration_y_100=0.6f;
    return;
case 415:
    if(sequence_index_13e==2)landing();
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
        select_sequence(2);byte_47f=0;y_f0=patchouli_surface(this);zero_motion();return;
    }
    if(!field_6c4)byte_750=0;
    pair801_tick(70,115.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4) {
            if(byte_750==1){charge_effect(-12,100.0);return;}
            word_730=1;counter(200,48);
        }
        if(!frame_timer_142 && frame_index_140==13)acceleration_y_100=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1){word_730=1;counter(200,48);}
        if(!frame_timer_142 && frame_index_140==10)acceleration_y_100=0.6f;
    }
    return;
case 416:
    if(sequence_index_13e==1)landing();
    if(!sequence_index_13e) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){select_sequence(1);zero_motion();y_f0=patchouli_surface(this);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
        dispatch_character_wave_handle(1);velocity_x_f4=-4.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;
        field_180=1;counter(200,48);phase_counter(50);
        float p[3];p[1]=20.0f;p[2]=5.0f;
        for(int angle=30;angle<105;angle+=15){p[0]=static_cast<float>(angle);spawn_offset(801,40,45.0,p,3);}
        p[2]=2.0f;spawn_offset(801,40,45.0,p,3);
    }
    return;
case 418:
    if(directional(1))return;
    landing();velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==4){float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==5){event(29);byte_47e=0;}
    }
    return;
case 500:{
        landing();byte_17c=0;
        if(!field_6c0)byte_750=0;
        if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7) {
            if(byte_604<3)ground810_emit(15.0f,0.0f);
            else ground810_emit(15.0f,6.0f);
            phase_counter(50);counter(200,60);dispatch_character_wave_handle(3);
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2) {
            float p[3]={0.0f,15.0f,1.0f};spawn_offset(810,60,114.0,p,3);
            int direction=static_cast<unsigned char>(facing_104);
            effect(128,static_cast<float>(200*static_cast<signed char>(direction)+static_cast<double>(x_ec)),
                   y_f0,direction,-1);
            counter(200,60);phase_counter(50);velocity_x_f4=-10.0f;dispatch_character_wave_handle(3);
        }
    return;}
case 501:{
        landing();byte_17c=0;
        if(!field_6c4)byte_750=0;
        if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(0);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7) {
            if(byte_604<3)ground810_emit(25.0f,0.0f);
            else ground810_emit(25.0f,6.0f);
            phase_counter(50);counter(200,60);dispatch_character_wave_handle(3);
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2) {
            float p[3]={0.0f,25.0f,1.0f};spawn_offset(810,60,114.0,p,3);
            int direction=static_cast<unsigned char>(facing_104);
            effect(128,static_cast<float>(200*static_cast<signed char>(direction)+static_cast<double>(x_ec)),
                   y_f0,direction,-1);
            counter(200,60);phase_counter(50);velocity_x_f4=-10.0f;dispatch_character_wave_handle(3);
        }
    return;}
case 502:{
        if(sequence_index_13e==2)landing();
        byte_17c=0;
        if(sequence_index_13e<2) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();y_f0=patchouli_surface(this);return;}
        }
        if(!field_6c0)byte_750=0;
        if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(9);return;}
        if(entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
            if(byte_604<3){float ordinary[3]={60.0f,15.0f,0.0f};spawn_offset(810,40,45.0,ordinary,3);}
            else {float upgraded[3]={60.0f,15.0f,6.0f};spawn_offset(810,40,45.0,upgraded,3);}
            counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);
            velocity_x_f4=-6.0f;velocity_y_f8=8.0f;acceleration_y_100=0.45f;
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1) {
            float p[3]={60.0f,15.0f,0.0f};
            spawn_offset(810,40,45.0,p,3);counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);
            velocity_x_f4=-6.0f;velocity_y_f8=8.0f;acceleration_y_100=0.45f;
        }

return;}
case 503:{
        if(sequence_index_13e==2)landing();
        byte_17c=0;
        if(sequence_index_13e<2) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();y_f0=patchouli_surface(this);return;}
        }
        if(!field_6c0)byte_750=0;
        if(advance())set_action_and_finalize(0);
        if(entry(1)){set_action_and_finalize(9);return;}
        if(entry(2)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
            if(byte_604<3){float ordinary[3]={45.0f,15.0f,0.0f};spawn_offset(810,40,45.0,ordinary,3);}
            else {float upgraded[3]={45.0f,15.0f,6.0f};spawn_offset(810,40,45.0,upgraded,3);}
            counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);
            velocity_x_f4=-6.0f;velocity_y_f8=8.0f;acceleration_y_100=0.45f;
        }
        if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1) {
            float p[3]={45.0f,15.0f,0.0f};
            spawn_offset(810,40,45.0,p,3);counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);
            velocity_x_f4=-6.0f;velocity_y_f8=8.0f;acceleration_y_100=0.45f;
        }

return;}
case 505:
    byte_17c=5;landing();if(!field_6c0)byte_750=0;
    if(sequence_index_13e==1) {
        if(time_counter_144%3==0) {
            float p[3]={static_cast<float>(patchouli_sine(static_cast<float>(10*time_counter_144))*20.0+10.0),18.0f,0.0f};
            spawn_offset(811,66,117.0,p,3);
        }
        if(time_counter_144>=10*(byte_609+4) || (time_counter_144>=20 && !byte_750)){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){counter(200,60);phase_counter(50);field_180=1;dispatch_character_wave_handle(11);}
    return;
case 506:
    byte_17c=5;landing();if(!field_6c4)byte_750=0;
    if(sequence_index_13e==1) {
        if(time_counter_144%3==0) {
            float p[3]={static_cast<float>(patchouli_sine(static_cast<float>(10*time_counter_144))*20.0-45.0),20.0f,0.0f};
            spawn_offset(811,66,117.0,p,3);
        }
        if(time_counter_144>=10*(byte_609+4) || (time_counter_144>=20 && !byte_750)){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){counter(200,60);phase_counter(50);field_180=1;dispatch_character_wave_handle(11);}
    return;
case 520:
    landing();byte_17c=1;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=5)return;
    {
        float p[3]={0.0f,30.0f,4.0f};
        spawn(815,related_170->x_ec,patchouli_surface(related_170),static_cast<unsigned char>(facing_104),1,p,3);
        if(byte_605>=3) {
            p[1]=40.0f;p[2]=4.0f;
            spawn(815,related_170->x_ec-100.0,patchouli_surface(related_170),static_cast<unsigned char>(facing_104),1,p,3);
        }
        if(byte_605>=4) {
            p[1]=40.0f;p[2]=4.0f;
            spawn(815,related_170->x_ec+100.0,patchouli_surface(related_170),static_cast<unsigned char>(facing_104),1,p,3);
        }
        counter(200,60);phase_counter(50);
    }
    return;
case 521:
    landing();byte_17c=1;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=5)return;
    {
        float p[3]={0.0f,30.0f,4.0f};
        spawn(815,related_170->x_ec,patchouli_surface(related_170),static_cast<unsigned char>(facing_104),1,p,3);
        if(byte_605>=3) {
            p[1]=40.0f;p[2]=4.0f;
            spawn(815,related_170->x_ec+100.0,patchouli_surface(related_170),static_cast<unsigned char>(facing_104),1,p,3);
        }
        if(byte_605>=4) {
            p[1]=40.0f;p[2]=4.0f;
            spawn(815,related_170->x_ec-100.0,patchouli_surface(related_170),static_cast<unsigned char>(facing_104),1,p,3);
        }
        counter(200,60);phase_counter(50);
    }
    return;
case 525:
    landing();byte_17c=6;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        float p[3]={-10.0f,5.0f,0.0f};if(byte_60a>=4)p[2]=3.0f;
        spawn_offset(816,62,118.0,p,3);counter(200,60);phase_counter(50);dispatch_character_wave_handle(12);field_180=1;
    }
    return;
case 526:
    landing();byte_17c=6;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        float p[3]={-30.0f,5.0f,0.0f};if(byte_60a>=4)p[2]=3.0f;
        spawn_offset(816,62,118.0,p,3);counter(200,60);phase_counter(50);dispatch_character_wave_handle(12);field_180=1;
    }
    return;
case 540:{
        if(!sequence_index_13e || sequence_index_13e==4)landing();
        byte_17c=2;if(!field_6c0)byte_750=0;
        if(sequence_index_13e<4) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                zero_motion();select_sequence(4);y_f0=patchouli_surface(this);return;
            }
        }
        if(sequence_index_13e==1) {
            if(time_counter_144%5==0){float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,0,100.0,p,3);}
            if(time_counter_144%10==0) {
                double y=y_f0;
                if(y-patchouli_surface(this)<200.0) {
                    float p[3];p[2]=0.0f;p[1]=12.0f;ring820_surface(p);
                }
            }
            if(time_counter_144>=34){next_sequence_block();return;}
        }
        if(advance())set_action_and_finalize(0);
        if(entry(1)) {
            dispatch_character_wave_handle(6);phase_counter(50);counter(200,60);
            velocity_y_f8=7.0f;acceleration_y_100=0.4f;field_7b4=14.5f;
        }
    return;}
case 541:{
        if(!sequence_index_13e || sequence_index_13e==4)landing();
        byte_17c=2;if(!field_6c4)byte_750=0;
        if(sequence_index_13e<4) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                zero_motion();select_sequence(4);y_f0=patchouli_surface(this);return;
            }
        }
        if(sequence_index_13e==1) {
            if(time_counter_144%5==0){float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,0,100.0,p,3);}
            if(time_counter_144%10==0) {
                double y=y_f0;
                if(y-patchouli_surface(this)<500.0) {
                    float p[3];p[2]=0.0f;p[1]=12.0f;ring820_surface(p);
                }
            }
            if(time_counter_144>=34){next_sequence_block();return;}
        }
        if(advance())set_action_and_finalize(0);
        if(entry(1)) {
            dispatch_character_wave_handle(6);phase_counter(50);counter(200,60);
            velocity_y_f8=12.5f;acceleration_y_100=0.4f;field_7b4=18.5f;
        }
    return;}
case 545:
    landing();byte_17c=7;if(!field_6c0)byte_750=0;
    if(sequence_index_13e==1) {
        if(byte_750 && (field_6bc || field_6c4)){select_sequence(3);return;}
        if(time_counter_144>=120 || !byte_750){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(821,100,110.0,p,3);
        counter(200,60);phase_counter(50);dispatch_character_wave_handle(14);field_180=1;
    }
    return;
case 546:
    landing();byte_17c=7;if(!field_6c4)byte_750=0;
    if(sequence_index_13e==1) {
        if(byte_750 && (field_6bc || field_6c0)){select_sequence(3);return;}
        if(time_counter_144>=120 || !byte_750){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(821,100,110.0,p,3);
        counter(200,60);phase_counter(50);dispatch_character_wave_handle(14);field_180=1;
    }
    return;
case 560:
    landing();byte_17c=3;if(!field_6c0)byte_750=0;
    if(sequence_index_13e<=1) {
        if(word_730==1) {
            float limit=5.0f;
            if(byte_607<=3)limit=4.0f;
            if(byte_607<=2)limit=3.0f;
            if(byte_607<=0)limit=2.0f;
            if(word_732%7==0 && limit>=static_cast<double>(field_744)) {
                dispatch_character_wave_handle(word_732%7);
                if(field_744==0.0f) {
                    float p[3]={0.0f,40.0f,0.0f};orbit825(p);
                } else {
                    float p[3]={static_cast<float>(field_744*7.0),40.0f,0.0f};orbit825(p);
                    p[0]=static_cast<float>(field_744*-7.0);orbit825(p);
                }
                field_744=static_cast<float>(field_744+1.0);
            }
        }
        ++word_732;
        if((!byte_750 && time_counter_144>=10) || time_counter_144>=90){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2) {
        phase_counter(50);counter(200,60);field_180=1;word_730=1;
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==1){word_730=2;dispatch_character_wave_handle(8);}
    return;

case 561:
    landing();byte_17c=3;if(!field_6c4)byte_750=0;
    if(sequence_index_13e<=1) {
        if(word_730==1) {
            float limit=5.0f;
            if(byte_607<=3)limit=4.0f;
            if(byte_607<=2)limit=3.0f;
            if(byte_607<=0)limit=2.0f;
            if(word_732%7==0 && limit>=static_cast<double>(field_744)) {
                dispatch_character_wave_handle(word_732%7);
                if(field_744==0.0f) {
                    float p[3]={0.0f,40.0f,0.0f};orbit825(p);
                } else {
                    float p[3]={static_cast<float>(field_744*7.0),40.0f,0.0f};orbit825(p);
                    p[0]=static_cast<float>(field_744*-7.0);orbit825(p);
                }
                field_744=static_cast<float>(field_744+1.0);
            }
        }
        ++word_732;
        if((!byte_750 && time_counter_144>=10) || time_counter_144>=90){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2) {
        phase_counter(50);counter(200,60);field_180=1;word_730=1;
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==1){word_730=2;dispatch_character_wave_handle(8);}
    return;
case 565:
    landing();byte_17c=8;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        dispatch_character_wave_handle(16);aim(-45.0f,45.0f);
        float p[3]={field_744,15.0f,0.0f};spawn_offset(826,70,110.0,p,3);
        counter(200,60);phase_counter(50);field_180=1;
    }
    return;
case 566:
    landing();byte_17c=8;if(!field_6c4)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        dispatch_character_wave_handle(16);aim(-45.0f,45.0f);
        float p[3]={static_cast<float>(field_744+45.0),15.0f,0.0f};spawn_offset(826,70,110.0,p,3);
        p[0]=static_cast<float>(field_744-45.0);p[1]=15.0f;p[2]=0.0f;spawn_offset(826,70,110.0,p,3);
        counter(200,60);phase_counter(50);field_180=1;
    }
    return;
case 567:
    if(sequence_index_13e==1)landing();
    byte_17c=8;velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<=0) {
        select_sequence(1);byte_47f=0;y_f0=patchouli_surface(this);zero_motion();return;
    }
    if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==5) {
            dispatch_character_wave_handle(16);aim(-45.0f,45.0f);
            float p[3]={field_744,15.0f,0.0f};spawn_offset(826,60,110.0,p,3);
            counter(200,60);phase_counter(50);field_180=1;
        }
        if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;
    }
    return;
case 568:
    if(sequence_index_13e==1)landing();
    byte_17c=8;velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<=0) {
        select_sequence(1);byte_47f=0;y_f0=patchouli_surface(this);zero_motion();return;
    }
    if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==5) {
            dispatch_character_wave_handle(16);aim(-45.0f,45.0f);
            float p[3]={static_cast<float>(field_744+45.0),15.0f,0.0f};spawn_offset(826,60,110.0,p,3);
            p[0]=static_cast<float>(field_744-45.0);p[1]=15.0f;p[2]=0.0f;spawn_offset(826,60,110.0,p,3);
            counter(200,60);phase_counter(50);field_180=1;
        }
        if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;
    }
    return;
case 570:
    landing();byte_17c=13;if(!field_6c0)byte_750=0;
    if(!sequence_index_13e && word_730>0) {
        if(word_730%4==1 && word_730<35) {
            float p[3];p[1]=40.0f;p[2]=0.0f;p[0]=static_cast<float>(static_cast<float>(patchouli_random(30))+15.0);
            spawn(827,static_cast<float>(static_cast<float>(patchouli_random(300))+x_ec-150.0),
                  static_cast<float>(static_cast<float>(patchouli_random(75))+y_f0+150.0),static_cast<unsigned char>(facing_104),1,p,3);
        }
        ++word_730;
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        phase_counter(50);counter(200,60);field_180=1;word_730=1;dispatch_character_wave_handle(8);
    }
    return;
case 571:
    landing();byte_17c=13;if(!field_6c4)byte_750=0;
    if(!sequence_index_13e && word_730>0) {
        if(word_730%4==1 && word_730<35) {
            float p[3];p[1]=40.0f;p[2]=0.0f;p[0]=static_cast<float>(static_cast<float>(patchouli_random(30))+15.0);
            spawn(827,static_cast<float>(static_cast<float>(patchouli_random(300))+x_ec-150.0),
                  static_cast<float>(static_cast<float>(patchouli_random(75))+y_f0+150.0),static_cast<unsigned char>(facing_104),1,p,3);
        }
        ++word_730;
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        phase_counter(50);counter(200,60);field_180=1;word_730=1;dispatch_character_wave_handle(8);
    }
    return;
case 580:
    landing();byte_17c=4;
    if(word_730==1) {
        float limit=4.0f;
        if(byte_608==4)limit=7.0f;
        if(byte_608<=3)limit=6.0f;
        if(byte_608<=2)limit=5.0f;
        if(byte_608<=0)limit=4.0f;
        if(word_732%5==0 && limit>=static_cast<double>(field_744)) {
            float p[4]={0.0f,0.0f,0.0f,static_cast<float>(field_744*4.0)};
            spawn(830,
                  (patchouli_cosine(static_cast<float>(-field_744*140.0))*100.0+200.0)*facing_104+x_ec,
                  patchouli_sine(static_cast<float>(-field_744*140.0))*25.0,
                  static_cast<unsigned char>(facing_104),1,p,4);
            field_744=static_cast<float>(field_744+1.0);
        }
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
        phase_counter(50);counter(200,60);field_180=1;word_730=1;dispatch_character_wave_handle(9);
    }
    return;
case 581:
    landing();byte_17c=4;
    if(word_730==1) {
        // Native leaves the scratch cap undefined for skill levels greater than4.
        float limit;
        if(byte_608==4)limit=7.0f;
        if(byte_608<=3)limit=6.0f;
        if(byte_608<=2)limit=5.0f;
        if(byte_608<=0)limit=4.0f;
        if(word_732%5==0 && limit>=static_cast<double>(field_744)) {
            float p[4]={0.0f,0.0f,0.0f,static_cast<float>(field_744*4.0)};
            spawn(830,
                  (patchouli_cosine(static_cast<float>(-field_744*140.0))*100.0+450.0)*facing_104+x_ec,
                  patchouli_sine(static_cast<float>(-field_744*140.0))*25.0,
                  static_cast<unsigned char>(facing_104),1,p,4);
            field_744=static_cast<float>(field_744+1.0);
        }
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
        phase_counter(50);counter(200,60);field_180=1;word_730=1;dispatch_character_wave_handle(9);
    }
    return;
case 585:
case 586:
    landing();byte_17c=9;if(!field_6c0)byte_750=0;
    if(sequence_index_13e==1 && time_counter_144>=40){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
        layout(5.0f);dispatch_character_wave_handle(17);float p[3];p[0]=-95.0f;p[1]=100.0f;
        if(byte_60d>=4) {
            p[2]=3.0f;spawn_offset(831,-110,-480.0,p,3);
            int direction=static_cast<unsigned char>(-static_cast<unsigned char>(facing_104));
            float y=static_cast<float>(y_f0-480.0);
            float x=static_cast<float>(110*facing_104+static_cast<double>(x_ec));
            spawn(831,x,y,direction,1,p,3);
        } else {
            p[2]=0.0f;spawn_offset(831,-100,-320.0,p,3);
            int direction=static_cast<unsigned char>(-static_cast<unsigned char>(facing_104));
            float y=static_cast<float>(y_f0-320.0);
            float x=static_cast<float>(100*facing_104+static_cast<double>(x_ec));
            spawn(831,x,y,direction,1,p,3);
        }
        counter(200,60);phase_counter(50);field_180=1;
    }
    return;
case 599:
    if(word_730>0 && frame_index_140<7 && word_730<12) {
        word_734=static_cast<short>(patchouli_random_u32()%35u);
        float p[3];p[0]=static_cast<float>(-20-word_734);
        p[1]=static_cast<float>(static_cast<short>(patchouli_random_u32()%5u+10));p[2]=0.0f;
        int direction=static_cast<unsigned char>(facing_104);
        float x=static_cast<float>(20*static_cast<signed char>(direction)*(word_730+1)+static_cast<double>(x_ec));
        spawn(807,x,y_f0,direction,1,p,3);
        p[0]=static_cast<float>(patchouli_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        direction=static_cast<unsigned char>(facing_104);x=static_cast<float>(20*static_cast<signed char>(direction)*(word_730+1)+static_cast<double>(x_ec));
        spawn(801,x,y_f0,direction,1,p,3);
        if(word_730==1){dispatch_character_wave_handle(0);counter(200,60);}
        ++word_730;
    }
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5)word_730=1;
    return;
case 600:
    landing();texture(5,2);
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3)spell_flash(-33,170.0,3);
        if(!frame_timer_142) {
            if(frame_index_140==4){float p[3]={0.0f,0.0f,0.0f};spawn_offset(890,66,67.0,p,3);}
            if(!frame_timer_142 && frame_index_140==5) {
                float p[3]={0.0f,0.0f,0.0f};spawn_offset(850,-55,230.0,p,3);dispatch_character_wave_handle(50);
            }
        }
    }
    return;
case 601:
    landing();
    if(word_730>0) {
        ++word_730;field_73c=static_cast<float>(field_73c+0.5);
        if(word_730%2==1 && word_732<20) {
            float p[3]={static_cast<float>(patchouli_sine(static_cast<float>(10*word_730))*field_73c),25.0f,1.0f};
            spawn_offset(851,63,117.0,p,3);
            p[0]=static_cast<float>(patchouli_sine(static_cast<float>(10*word_730))*-field_73c);p[1]=25.0f;p[2]=1.0f;
            spawn_offset(851,63,117.0,p,3);
            p[2]=2.0f;spawn_offset(851,63,117.0,p,3);
            dispatch_character_wave_handle(2);++word_732;
        }
    }
    if(sequence_index_13e==1 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3)spell_flash(33,188.0,2);
        if(!frame_timer_142 && frame_index_140==4)word_730=1;
    }
    return;
case 602:
    if(!sequence_index_13e || sequence_index_13e==2)landing();
    if(entry(0))spell_flash(30,95.0,2);
    if(sequence_index_13e==1) {
        if(field_180){if(++word_730>=8){field_180=0;word_730=0;}}
        if(!frame_index_140 && !frame_timer_142)dispatch_character_wave_handle(52);
        velocity_y_f8-=acceleration_y_100;
        if(time_counter_144>=180){set_action_and_finalize(9);acceleration_y_100=0.5f;return;}
        if(time_counter_144%5==0){float p[3]={0.0f,0.0f,3.0f};spawn_offset(852,0,100.0,p,3);}
        if(static_cast<unsigned char>(crossed())){next_sequence_block();y_f0=patchouli_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {
        time_counter_144=0;velocity_x_f4=2.0f;velocity_y_f8=3.5f;acceleration_y_100=0.05f;
        float p[3]={0.0f,0.0f,0.0f};
        spawn(852,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1,p,3);
        p[0]=30.0f;p[1]=0.0f;p[2]=1.0f;orbit852(p,150.0);
        p[0]=-90.0f;p[1]=0.0f;p[2]=1.0f;orbit852(p,150.0);
        p[0]=150.0f;p[1]=0.0f;p[2]=1.0f;orbit852(p,150.0);
        for(float n=0.0f;n<4.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(n*90.0+45.0);p[1]=100.0f;p[2]=2.0f;orbit852(p,100.0);
        }
    }
    return;
case 603:
    landing();texture(5,2);
    if((sequence_index_13e==1 && time_counter_144>120) || (sequence_index_13e==2 && time_counter_144>60)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1))time_counter_144=0;
    if(!sequence_index_13e && frame_index_140==6 && !frame_timer_142) {
        word_48a=40;event(23);
        int direction=static_cast<unsigned char>(facing_104);
        effect(115,static_cast<float>(20*static_cast<signed char>(direction)+static_cast<double>(x_ec)),
               static_cast<float>(y_f0+240.0),direction,1);
        float p[3]={0.0f,0.0f,0.0f};
        // Native request adds20 in world X, not20*facing.
        spawn(853,static_cast<float>(x_ec+20.0),static_cast<float>(y_f0+240.0),static_cast<unsigned char>(facing_104),1,p,3);
        sequence_window(0,5,60);secondary_cycle();dispatch_character_wave_handle(53);
    }
    return;
case 604:
    landing();texture(5,2);
    if((sequence_index_13e==1 && time_counter_144>=90) || (sequence_index_13e==2 && time_counter_144>=90)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2)spell_flash(-10,85.0,4);
    if(entry(1)) {
        float p[3]={0.0f,0.0f,0.0f};spawn(854,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);
        p[1]=0.3f;p[2]=8.0f;spawn(854,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);
        dispatch_character_wave_handle(55);time_counter_144=0;
    }
    return;
case 605:
    landing();texture(5,2);
    if(sequence_index_13e==1 && time_counter_144>40){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {
        word_7a4=1200;dispatch_character_wave_handle(59);float p[3];
        for(float n=0.0f;n<5.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(72.0*n);p[1]=0.0f;p[2]=n;spawn_offset(855,0,100.0,p,3);
        }
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(-51,75.0,5);
    return;
case 606:
    landing();texture(5,2);
    if(sequence_index_13e==1 && time_counter_144>=32){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(30,95.0,3);
    if(entry(1)){float p[3]={0.0f,0.0f,0.0f};spawn_offset(856,0,210.0,p,3);dispatch_character_wave_handle(12);}
    return;
case 607:
    landing();texture(5,2);
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4)spell_flash(30,100.0,3);
        if(!frame_timer_142 && frame_index_140==9) {
            float p[3]={0.0f,0.0f,0.0f};
            spawn(857,x_ec,static_cast<float>(y_f0+210.0),static_cast<unsigned char>(facing_104),-1,p,3);
            p[0]=180.0f;p[2]=1.0f;
            spawn(857,x_ec,static_cast<float>(y_f0+210.0),static_cast<unsigned char>(facing_104),-1,p,3);
            dispatch_character_wave_handle(57);
        }
    }
    return;
case 610:
    landing();texture(5,2);
    if(sequence_index_13e==1 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){float p[3]={0.0f,0.0f,0.0f};spawn(860,x_ec,0.0f,static_cast<unsigned char>(facing_104),-1,p,3);dispatch_character_wave_handle(58);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2)spell_flash(13,86.0,3);
    return;
case 651:
    if(sequence_index_13e==3)landing();
    else {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=patchouli_surface(this);select_sequence(3);return;}
    }
    if(word_730>0) {
        ++word_730;field_73c=static_cast<float>(field_73c+0.5);
        if(word_730%2==1 && word_732<20) {
            float p[3]={static_cast<float>(patchouli_sine(static_cast<float>(10*word_730))*field_73c),25.0f,1.0f};
            spawn_offset(851,71,115.0,p,3);
            p[0]=static_cast<float>(patchouli_sine(static_cast<float>(10*word_730))*-field_73c);p[1]=25.0f;p[2]=1.0f;
            spawn_offset(851,71,115.0,p,3);
            p[2]=2.0f;spawn_offset(851,71,115.0,p,3);
            dispatch_character_wave_handle(2);++word_732;
        }
    }
    if(sequence_index_13e==1 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!time_counter_144) {
        if(entry(1))time_counter_144=0;
        if(entry(3)){set_action_and_finalize(9);return;}
    }
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3)spell_flash(41,192.0,2);
        if(!frame_timer_142 && frame_index_140==4)word_730=1;
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)acceleration_y_100=0.5f;
    return;
case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7) {
        event(55);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
        effect(141,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1);
        effect(142,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
    }
    return;
case 696:
    landing();
    if(byte_47e) {
        velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
        if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3){float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==5){event(27);byte_47e=0;}
    }
    return;
case 710:
    if(!sequence_index_13e || sequence_index_13e==2)landing();
    if(sequence_index_13e==1) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){next_sequence_block();y_f0=patchouli_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(700);
    if(entry(1)) {
        dispatch_character_wave_handle(11);field_73c=-90.0f;
        float dx=static_cast<float>((related_170->x_ec-x_ec)*static_cast<double>(facing_104));
        field_73c=static_cast<float>(-patchouli_atan(related_170->y_f0-y_f0,dx)-90.0);
        field_744=static_cast<float>(field_73c+180.0);
        velocity_x_f4=static_cast<float>(3.0-static_cast<float>(patchouli_random(6)));
        velocity_y_f8=static_cast<float>(static_cast<float>(patchouli_random(10))*static_cast<double>(0.1f)+5.5);
        acceleration_y_100=0.05f;
    }
    return;
case 720:
    if(sequence_index_13e==1 && velocity_y_f8<4.0f){next_sequence_block();return;}
    if(sequence_index_13e==1 || sequence_index_13e==2)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==3) {
        velocity_x_f4=static_cast<float>(velocity_x_f4*static_cast<double>(0.98f));
        velocity_y_f8=static_cast<float>(static_cast<double>(0.98f)*velocity_y_f8);
    }
    if(advance())set_action_and_finalize(700);
    if(entry(1)) {
        velocity_x_f4=static_cast<float>(3.0-static_cast<float>(patchouli_random(6)));
        velocity_y_f8=static_cast<float>(static_cast<float>(patchouli_random(10))*static_cast<double>(0.1f)+5.5);
        acceleration_y_100=0.1f;
    }
    return;
case 721:
    if(sequence_index_13e<=1) {
        if(entry(0)) {
            if(!(x_ec<640.0f))field_74c=static_cast<float>(580.0-static_cast<float>(patchouli_random(360)));
            else field_74c=static_cast<float>(static_cast<float>(patchouli_random(360))+700.0);
            field_748=static_cast<float>(static_cast<float>(patchouli_random(260))+60.0);
            if(!(field_74c<static_cast<double>(x_ec)))facing_104=1;else facing_104=-1;
        }
        velocity_x_f4=static_cast<float>((field_74c-x_ec)*static_cast<double>(0.02f)*facing_104);
        velocity_y_f8=static_cast<float>(static_cast<double>(0.02f)*(field_748-y_f0));
        if(velocity_x_f4>6.0f)velocity_x_f4=6.0f;
        if(velocity_y_f8>6.0f)velocity_y_f8=6.0f;
        float dy=field_748-y_f0;double vertical_square=patchouli_square(dy);
        float dx=field_74c-x_ec;
        if(patchouli_square(dx)+vertical_square<=900.0){next_sequence_block();return;}
    }
    if(sequence_index_13e==2) {
        velocity_x_f4=static_cast<float>(velocity_x_f4*static_cast<double>(0.98f));
        velocity_y_f8=static_cast<float>(static_cast<double>(0.98f)*velocity_y_f8);
    }
    if(advance()){set_action_and_finalize(720);select_sequence(3);}
    return;
case 730:
    if(sequence_index_13e==1 && time_counter_144>=32){next_sequence_block();return;}
    if(sequence_index_13e==1 || sequence_index_13e==2) {
        velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<0.0f)velocity_y_f8=0.0f;
        velocity_x_f4=static_cast<float>((640.0-x_ec)*static_cast<double>(-0.1f));
        if(velocity_x_f4>10.0f)velocity_x_f4=10.0f;
        if(velocity_x_f4<-10.0f)velocity_x_f4=-10.0f;
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){facing_104=-1;velocity_y_f8=15.0f;acceleration_y_100=0.5f;}
    return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7) {
        byte_655=1;finalize(-1);texture(2,-1);copy_health();
        word_76c=0;word_76a=1;word_766=0;word_768=0;word_764=0;event(23);
    }
    return;
case 795:
    if(!sequence_index_13e) {
        velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.3f));
        if(static_cast<unsigned char>(crossed())) {
            select_sequence(1);y_f0=patchouli_surface(this);zero_motion();event(30);return;
        }
    }
    if(advance())set_action_and_finalize(700);
    return;
case 797:
    if(!sequence_index_13e) {
        velocity_y_f8-=acceleration_y_100;
        if(y_f0<=150.0f) {
            dispatch_character_wave_handle(6);select_sequence(1);zero_motion();acceleration_y_100=0.2f;velocity_y_f8=4.0f;
            float p[3];p[2]=0.0f;p[1]=12.0f;ring820_surface(p);return;
        }
    }
    if(sequence_index_13e==1 || sequence_index_13e==2) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
            select_sequence(3);x_ec=480.0f;y_f0=patchouli_surface(this);event(30);zero_motion();return;
        }
    }
    if(advance())set_action_and_finalize(0);
    return;
case 798:
    if(!sequence_index_13e) {
        velocity_y_f8-=acceleration_y_100;
        if(y_f0<=150.0f) {
            dispatch_character_wave_handle(6);select_sequence(1);zero_motion();acceleration_y_100=0.2f;velocity_y_f8=4.0f;
            float p[3];p[2]=0.0f;p[1]=12.0f;ring820_surface(p);return;
        }
    }
    if(sequence_index_13e==1 || sequence_index_13e==2) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
            event(30);select_sequence(3);x_ec=800.0f;y_f0=patchouli_surface(this);zero_motion();return;
        }
    }
    if(advance())set_action_and_finalize(700);
    return;

    default:common_update();return;
    }
    advance();
}
}
