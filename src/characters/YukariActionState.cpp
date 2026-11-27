#include "characters/YukariActionState.hpp"
// Canonical exact JP 1.06a 0x0057B030 Yukari Fighter +0x28 action-state root.
// See docs/YUKARI_ACTION_STATE_2026_10_28.md.
namespace th105 {
void YukariActionStateView::dispatch_action_state_vslot28() {
word_7a0=0;word_7a2=100;
if(action_id_13c>149 && action_id_13c<159 && !byte_751) {
    byte_751=1;float p[1];
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
if(word_186 || fighter_170->word_48c)return;

switch(action_id_13c) {
case 0:
    landing();if(velocity_x_f4==0.0f)byte_47e=0;idle_motion();break;
case 1:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:
    landing();idle_motion();break;
case 3:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:landing();velocity_x_f4=4.5f;break;
case 5:landing();velocity_x_f4=-4.5f;break;
case 6:normal_jump(0.0f);return;
case 7:normal_jump(4.0f);return;
case 8:normal_jump(-4.0f);return;
case 9:
    if(acceleration_y_100==0.0f)acceleration_y_100=0.6f;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    break;
case 10:
    landing();zero_motion();if(advance()){if(!field_6b8){set_action_and_finalize(0);return;}set_action_and_finalize(2);}return;
case 71:
    if(entry(1))ensure_recovery_object();
    if(sequence_index_13e==1 && velocity_y_f8<2.0f){next_sequence_block();return;}
    velocity_y_f8-=acceleration_y_100;if(velocity_y_f8>0.0f)velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(2.0f);event(22);return;}
    if(word_730>0)--word_730;recovery_slide(1.0,true);advance();return;
case 72:
    if(sequence_index_13e==1 && velocity_y_f8<2.0f){next_sequence_block();return;}
    if(entry(1))ensure_recovery_object();velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(2.0f);event(22);return;}
    recovery_slide(1.0,false);advance();return;
case 73:
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(5.0f);event(22);return;}
    advance();if(recovery_entry_sequence())return;
    if(--word_730<0)word_730=0;recovery_slide(2.5,true);return;
case 74:
    if(entry(1))ensure_recovery_object();
    if(sequence_index_13e==1 && velocity_y_f8<2.0f){next_sequence_block();return;}
    if(classify_fighter_x_boundary() && velocity_x_f4<=-25.0f){set_action_and_finalize(76);return;}
    if(classify_fighter_x_boundary() && velocity_x_f4<=-15.0f){set_action_and_finalize(78);return;}
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(2.0f);event(22);return;}
    advance();return;
case 75:
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(5.0f);event(22);return;}
    if(classify_fighter_x_boundary() && velocity_x_f4<=-25.0f){set_action_and_finalize(76);return;}
    if(classify_fighter_x_boundary() && velocity_x_f4<=-15.0f){set_action_and_finalize(78);return;}
    advance();recovery_entry_sequence();return;
case 76:
    if(sequence_index_13e>0)field_12c=static_cast<float>(field_12c-30.0);
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){event(22);recovery_land(97);field_12c=0.0f;layout(4.0f);reset_action_scratch();return;}
    advance();if(entry(1)){facing_104=static_cast<signed char>(-facing_104);velocity_x_f4=-3.0f;velocity_y_f8=10.0f;acceleration_y_100=0.5f;ensure_recovery_object();}return;
case 77:
    field_12c=static_cast<float>(field_12c-30.0);velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){event(22);recovery_land(97);field_12c=0.0f;layout(2.0f);reset_action_scratch();return;}
    if(entry(1))ensure_recovery_object();advance();return;
case 78:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){event(22);recovery_land(97);layout(2.0f);return;}
    advance();if(entry(1)){facing_104=static_cast<signed char>(-facing_104);velocity_x_f4=-5.0f;velocity_y_f8=3.0f;acceleration_y_100=0.5f;ensure_recovery_object();}return;
case 88:
    if(static_cast<unsigned char>(crossed())){recovery_land(89);layout(5.0f);event(22);return;}
    advance();if(recovery_entry_sequence())return;
    if(--word_730<0)word_730=0;recovery_slide(2.5,true);return;
case 89:
    if(sequence_index_13e>0){field_12c=static_cast<float>(field_12c-40.0);velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){recovery_land(97);field_12c=0.0f;layout(2.0f);reset_action_scratch();event(22);return;}}
    advance();if(entry(1)){velocity_x_f4=static_cast<float>(word_730*0.0025f);velocity_y_f8=static_cast<float>(-word_732*0.0025f);acceleration_y_100=0.25f;word_7a0=0;word_7a2=85;field_108=static_cast<float>(word_7a0);field_10c=static_cast<float>(word_7a2);}return;
case 145:
    if(entry(1))ensure_recovery_object();
    if(sequence_index_13e==1 && velocity_y_f8<2.0f){next_sequence_block();return;}
    velocity_y_f8-=acceleration_y_100;if(velocity_y_f8>0.0f)velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){recovery_land(97);layout(2.0f);event(22);return;}
    if(word_730>0)--word_730;recovery_slide(1.0,true);advance();return;
case 197:
    if(!frame_timer_142 && !frame_index_140)packet981_pair();
    if(!frame_index_140 || frame_index_140>=22)landing();
    if(recover_action())return;
    if(!frame_timer_142 && frame_index_140==9)velocity_x_f4=30.0f;
    if(!frame_timer_142 && frame_index_140==10){velocity_x_f4=0.0f;packet981(3.0f);}
    if(!frame_timer_142 && frame_index_140==23)ground_face();return;
case 198:
    if(!frame_timer_142 && !frame_index_140)packet981_pair();
    if(!frame_index_140 || frame_index_140>=22)landing();
    if(recover_action())return;
    if(!frame_timer_142 && frame_index_140==9)velocity_x_f4=-30.0f;
    if(!frame_timer_142 && frame_index_140==10){velocity_x_f4=0.0f;packet981(3.0f);}
    if(!frame_timer_142 && frame_index_140==23)ground_face();return;
case 199:
    if(!frame_index_140 || frame_index_140>=22)landing();
    if(!frame_timer_142 && !frame_index_140)packet981_pair();
    if(recover_action())return;
    if(!frame_timer_142 && frame_index_140==10 && byte_55a>0) {
        if(byte_72c==2 && cards_55c[0].record_id_00>=16 && cards_55c[0].record_id_00<=19){byte_113=0;x_ec=640.0f;y_f0=200.0f;set_action_and_finalize(750);facing_104=1;return;}
        packet981(3.0f);
    }
    if(!frame_timer_142 && frame_index_140==23)ground_face();return;
case 200:
    landing();byte_47e=1;if(velocity_x_f4>8.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<8.0f)velocity_x_f4=8.0f;}
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){velocity_x_f4=11.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        if(field_6b8<0){if(field_6b4*facing_104>0)set_action_and_finalize(212);else set_action_and_finalize(211);return;}
        ++word_730;if((field_6b4*facing_104<=0 && word_730>5) || word_730>60)set_action_and_finalize(204);
    }return;
case 201:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!yukari_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;acceleration_y_100=0.0f;y_f0=yukari_surface(this);select_sequence(3);return;}}
    if(sequence_index_13e==5 && time_counter_144>=10) {
        if(facing_104==1){x_ec=1240.0f;y_f0=yukari_surface(this);}else{x_ec=40.0f;y_f0=yukari_surface(this);}
        if(time_counter_144==70){float p[3]={0.0f,0.0f,1.0f};spawn(849,static_cast<float>(200*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+70.0),static_cast<signed char>(-facing_104),-1,p,3);}
    }
    if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if(entry(1)){velocity_x_f4=-10.0f;velocity_y_f8=5.0f;acceleration_y_100=0.6f;dash_effects(true,80.0,false);}
    if(entry(4)){set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if(entry(5)){if(facing_104==1)dispatch_character_wave_handle(4);else dispatch_character_wave_handle(5);float p[3]={0.0f,0.0f,0.0f};spawn(849,x_ec,y_f0,facing_104,-1,p,3);}return;
case 202:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yukari_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    advance();if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){velocity_x_f4=9.0f;velocity_y_f8=5.0f;acceleration_y_100=0.45f;dash_effects(false,110.0,true);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3)flip();return;
case 203:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yukari_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);advance();
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==1){velocity_x_f4=-9.0f;velocity_y_f8=5.0f;acceleration_y_100=0.45f;dash_effects(true,120.0,false);}if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9)flip();}return;
case 204:
    landing();velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}if(advance()){set_action_and_finalize(0);byte_47e=0;}return;
case 208:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(yukari_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();if(!entry(1))return;
    velocity_x_f4=0.0f;velocity_y_f8=20.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 209:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(yukari_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();if(!entry(1))return;
    velocity_x_f4=9.0f;velocity_y_f8=15.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 210:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(yukari_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();if(!entry(1))return;
    velocity_x_f4=-9.0f;velocity_y_f8=15.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 211:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(yukari_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();if(!entry(1))return;
    velocity_x_f4=1.0f;velocity_y_f8=18.5f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 212:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(yukari_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();if(!entry(1))return;
    velocity_x_f4=10.0f;velocity_y_f8=15.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 214: {
    if(advance()){set_action_and_finalize(9);return;}
    if(entry(1))event(31);if(entry(6)){set_action_and_finalize(9);return;}
    if(field_6b8>0){if(field_6b4*facing_104>0)word_732=-45;else if(field_6b4*facing_104<0)word_732=-135;else word_732=-90;}
    else if(field_6b8<0){if(field_6b4*facing_104>0)word_732=45;else if(field_6b4*facing_104<0)word_732=135;else word_732=90;}
    else{if(field_6b4*facing_104>0)word_732=0;else if(field_6b4*facing_104<0)word_732=180;}
    if(sequence_index_13e==5 || sequence_index_13e==6)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e>0 && sequence_index_13e<5) {
        ++word_736;word_734=static_cast<short>(word_732-static_cast<int>(field_740));
        if(word_734>180)word_734-=360;if(word_734<-180)word_734+=360;
        if(word_734>0){if(!field_4b8)field_740=static_cast<float>(field_740+3.0);else field_740=static_cast<float>(field_740+1.0);}
        if(word_734<0){if(!field_4b8)field_740=static_cast<float>(field_740-3.0);else field_740=static_cast<float>(field_740-1.0);}
        velocity_x_f4=static_cast<float>(yukari_cosine(field_740)*field_73c);
        velocity_y_f8=static_cast<float>(yukari_sine(field_740)*field_73c);
        if(y_f0>680.0f && velocity_y_f8>0.0f)velocity_y_f8=0.0f;
        field_73c=static_cast<float>(field_73c+static_cast<double>(0.3f));if(field_73c>10.0f)field_73c=10.0f;
        if(!field_4b8)counter(5,1);else counter(10,1);
        field_12c=-field_740;if(velocity_x_f4<0.0f)field_12c=static_cast<float>(180.0-field_740);
        if(velocity_x_f4<0.0f && sequence_index_13e==1)select_sequence(3);
        if(velocity_x_f4>=0.0f && sequence_index_13e==3)select_sequence(1);
        if(velocity_x_f4<0.0f && sequence_index_13e==2)select_sequence(4);
        if(velocity_x_f4>=0.0f && sequence_index_13e==4)select_sequence(2);
        if(time_counter_144%5==1) {
            effect(125,
                static_cast<float>(yukari_cosine(field_740)*100.0*facing_104+x_ec),
                static_cast<float>(yukari_sine(field_740)*100.0+y_f0+100.0),
                static_cast<unsigned char>(facing_104),1);
        }
        // Native duplicates this gate without an intervening write/call.
        if((!field_6c8 && word_736>10) || word_482<=0) {
            if((!field_6c8 && word_736>10) || word_482<=0) {
                reset_action_scratch();
                if(sequence_index_13e==1 || sequence_index_13e==2) {
                    if(facing_104==1){
                        if(x_ec>fighter_170->x_ec){facing_104=-1;velocity_x_f4=-velocity_x_f4;select_sequence(6);}
                        else select_sequence(5);
                    }else{
                        if(x_ec<fighter_170->x_ec){facing_104=static_cast<signed char>(-facing_104);velocity_x_f4=-velocity_x_f4;select_sequence(6);}
                        else select_sequence(5);
                    }
                }
                if(sequence_index_13e==3 || sequence_index_13e==4) {
                    if(facing_104==1){
                        if(x_ec>fighter_170->x_ec){facing_104=-1;velocity_x_f4=-velocity_x_f4;select_sequence(5);return;}
                        select_sequence(6);return;
                    }
                    if(x_ec<fighter_170->x_ec){facing_104=static_cast<signed char>(-facing_104);velocity_x_f4=-velocity_x_f4;select_sequence(5);return;}
                    select_sequence(6);return;
                }
                return;
            }
        }
    }
    if(static_cast<unsigned char>(crossed())){
        y_f0=yukari_surface(this);velocity_y_f8=0.0f;
        if(sequence_index_13e<5){reset_action_scratch();set_action_and_finalize(215);}
        else{set_action_and_finalize(10);zero_motion();}
    }return;
}

case 215:
    landing();if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(yukari_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();if(!entry(1))return;
    velocity_x_f4=0.0f;velocity_y_f8=20.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 221:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(yukari_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();if(!entry(1))return;
    velocity_x_f4=9.0f;velocity_y_f8=15.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 222:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(yukari_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();if(!entry(1))return;
    velocity_x_f4=-9.0f;velocity_y_f8=15.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 223:
    landing();byte_47e=1;advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){velocity_x_f4=5.5f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);++word_730;if((field_6b4*facing_104<=0 && word_730>13) || word_730>60)set_action_and_finalize(204);}return;
case 224:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!yukari_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;acceleration_y_100=0.0f;y_f0=yukari_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if(entry(1)){velocity_x_f4=-10.0f;velocity_y_f8=5.0f;acceleration_y_100=0.6f;dash_effects(true,80.0,false);}return;
case 225:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(frame_index_140<=7 && time_counter_144%5==0)dash_dust(true);if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){velocity_x_f4=-9.0f;velocity_y_f8=5.0f;acceleration_y_100=0.45f;dash_effects(true,120.0,false);}return;
case 226:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yukari_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){velocity_x_f4=9.0f;velocity_y_f8=5.0f;acceleration_y_100=0.45f;dash_effects(false,110.0,true);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3)flip();return;

case 300:
    landing();if(directional(0))return;if(byte_47e)decelerate(0.5,true);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==2){event(27);byte_47e=0;}return;
case 301:
    landing();if(directional(0))return;if(byte_47e)decelerate(0.5,true);if(frame_index_140>=5)decelerate(static_cast<double>(0.2f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){velocity_x_f4=2.0f;byte_47e=0;packet848(0.0f,1);}if(!frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);byte_47e=0;}return;
case 302:
    landing();if(directional(1))return;if(byte_47e)decelerate(0.5,true);if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==2){if(byte_750){next_sequence_block();effect(62,static_cast<float>(x_ec-92*facing_104),static_cast<float>(y_f0+224.0),static_cast<unsigned char>(facing_104),1);return;}velocity_x_f4=10.0f;byte_47e=0;}
        if(!frame_timer_142 && frame_index_140==4){event(29);velocity_x_f4=0.0f;}
    }
    if(sequence_index_13e==1){if(!frame_timer_142 && frame_index_140==1){velocity_x_f4=20.0f;byte_47e=0;}if(!frame_timer_142 && frame_index_140==3){event(29);velocity_x_f4=0.0f;}}return;
case 303:
    landing();if(directional(0))return;if(static_cast<signed char>(byte_47e)>0)decelerate(static_cast<double>(0.6f),true);if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==3)event(27);return;
case 304:
    landing();if(directional(1))return;if(byte_47e)decelerate(0.5,true);if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==1)packet848(6.0f,-1);if(!frame_timer_142 && frame_index_140==4){event(29);velocity_x_f4=0.0f;}}
    if(sequence_index_13e==1){if(!frame_timer_142 && frame_index_140==1){velocity_x_f4=20.0f;byte_47e=0;}if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);velocity_x_f4=0.0f;}}return;
case 305:
    landing();if(directional(1))return;if(frame_index_140>4 && velocity_x_f4>0.0f)velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==2)packet848(2.0f,1);if(!frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(0);return;
case 306:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!frame_timer_142 && frame_index_140==2)packet848(1.0f,1);if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(0);return;
case 307:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(word_730==1){velocity_x_f4=static_cast<float>(velocity_x_f4*static_cast<double>(0.9f));if(velocity_x_f4<2.0f)velocity_x_f4=2.0f;}
    if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2)packet848(3.0f,1);if(!frame_timer_142 && frame_index_140==4){velocity_x_f4=15.0f;velocity_y_f8=0.0f;acceleration_y_100=0.0f;dispatch_character_wave_handle(0);word_730=1;}if(!frame_timer_142 && frame_index_140==10)acceleration_y_100=0.5f;}return;
case 308:
    if(sequence_index_13e==1){field_108=0.0f;field_10c=135.0f;field_12c=static_cast<float>(field_12c+35.0);if(static_cast<unsigned char>(crossed())){field_12c=0.0f;zero_motion();y_f0=yukari_surface(this);next_sequence_block();return;}if(time_counter_144%20==0)event(29);}
    if(sequence_index_13e==2)landing();if(advance())set_action_and_finalize(0);if(entry(1)){velocity_x_f4=7.5f;velocity_y_f8=-7.5f;}return;
case 309:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=yukari_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!frame_timer_142 && frame_index_140==2)packet848(2.0f,1);if(!frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(0);return;
case 310:
    if(field_180){if(++word_730>5){field_180=0;word_730=0;}}
    if(sequence_index_13e==1){velocity_y_f8=static_cast<float>(velocity_y_f8-acceleration_y_100*0.5);field_12c=static_cast<float>(field_12c+40.0);velocity_y_f8-=acceleration_y_100;if(time_counter_144%15==0)event(27);double next_y=y_f0+static_cast<double>(velocity_y_f8);if(yukari_surface(this)>=next_y && velocity_y_f8<0.0f){velocity_y_f8=0.0f;y_f0=yukari_surface(this);next_sequence_block();field_12c=0.0f;reset_action_scratch();return;}}
    if(sequence_index_13e==2)decelerate(1.0,false);if(advance())set_action_and_finalize(0);return;
case 320:
    landing();if(directional(0))return;if(byte_47e)decelerate(0.5,true);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==2){event(27);byte_47e=0;}return;
case 321:
    landing();if(directional(0))return;if(frame_index_140>1)decelerate(2.0,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){velocity_x_f4=5.0f;byte_47e=0;packet848(5.0f,1);}if(!frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);byte_47e=0;}return;
case 322:
    landing();if(directional(1))return;if(velocity_x_f4>0.0f)velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==2){velocity_x_f4=10.0f;byte_47e=0;}if(!frame_timer_142 && frame_index_140==3)event(29);if(!frame_timer_142 && frame_index_140==4)velocity_x_f4=0.0f;return;

case 400:ground800();return;
case 401:ground800();return;
case 402:
    landing();if(!field_6c0)byte_750=0;
    if(entry(0)){float p[3]={0.0f,0.0f,3.0f};spawn(800,x_ec,y_f0,facing_104,-1,p,3);}
    if(word_730==1){if(!sequence_index_13e && word_732%3==0 && field_740<5.0f){field_180=1;float p[3];for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){double a=field_740*5.0;p[0]=static_cast<float>(a+(field_744-20.0)+n*10.0-10.0);p[1]=10.0f;p[2]=1.0f;spawn(800,static_cast<float>((20.0+field_740*15.0)*facing_104+x_ec),static_cast<float>(y_f0-20.0),facing_104,1,p,3);}phase_counter(10);dispatch_character_wave_handle(2);field_740=static_cast<float>(field_740+1.0);}++word_732;}
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){word_730=1;counter(200,45);field_744=-60.0f;}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){word_730=1;counter(200,45);aim800(10.0f);}return;
case 404:
    if(sequence_index_13e==2)landing();velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){word_730=0;select_sequence(2);byte_47f=0;y_f0=yukari_surface(this);zero_motion();return;}
    if(!field_6c0)byte_750=0;fan800(104.0,true);
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2 && byte_750){charge800();return;}if(!frame_timer_142 && frame_index_140==3){word_730=1;aim800(30.0f);}if(!frame_timer_142 && frame_index_140==8)acceleration_y_100=0.6f;}
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==2){word_730=1;aim800(30.0f);}if(!frame_timer_142 && frame_index_140==7)acceleration_y_100=0.6f;}return;
case 406:
    if(sequence_index_13e==2)landing();velocity_y_f8-=acceleration_y_100;
    if(!sequence_index_13e && frame_index_140>=11 && static_cast<unsigned char>(crossed()) && sequence_index_13e<2){word_730=0;select_sequence(2);byte_47f=0;y_f0=yukari_surface(this);zero_motion();return;}
    if(entry(0)){float p[3]={0.0f,0.0f,3.0f};spawn(800,x_ec,static_cast<float>(y_f0+30.0),facing_104,-1,p,3);}
    if(!field_6c0)byte_750=0;
    if(word_730==1){if(!sequence_index_13e && word_732%3==0 && field_740<5.0f){if(field_740==0.0f)counter(200,45);field_180=1;float p[3];for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(field_744-field_740*10.0+n*10.0-10.0);p[1]=10.0f;p[2]=2.0f;spawn(800,static_cast<float>((field_740*15.0+20.0)*facing_104+x_ec),static_cast<float>(y_f0+40.0),facing_104,1,p,3);}phase_counter(10);dispatch_character_wave_handle(2);field_740=static_cast<float>(field_740+1.0);}++word_732;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==5){word_730=1;field_744=80.0f;}if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.6f;}return;
case 408:
    if(frame_index_140>=10){velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);landing();}else velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.1f));
    if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==2)packet848(1.0f,1);if(!frame_timer_142 && frame_index_140==5)event(29);return;
case 410:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){field_180=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);fan801(177,90.0,90.0f);}return;
case 411:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){field_180=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);split801(177,90.0);}return;
case 412:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){counter(200,60);field_180=1;phase_counter(50);dispatch_character_wave_handle(3);float p[4];for(float n=0.0f;n<5.0f;n=static_cast<float>(n+1.0)){p[0]=0.0f;p[1]=10.0f;p[2]=p[0];p[3]=static_cast<float>(n*5.0+10.0);spawn_offset(801,75,50.0,p,4);}}
    if(sequence_index_13e==1 && time_counter_144>20)next_sequence_block();return;
case 414:
    if(sequence_index_13e==1)landing();if(sequence_index_13e<1 && frame_index_140>=4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yukari_surface(this);select_sequence(1);return;}}
    if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){field_180=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);velocity_x_f4=-5.0f;velocity_y_f8=7.5f;acceleration_y_100=0.5f;fan801(75,85.0,90.0f);}return;
case 415:
    if(sequence_index_13e==1)landing();if(sequence_index_13e<1 && frame_index_140>=4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yukari_surface(this);select_sequence(1);return;}}
    if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){field_180=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);velocity_x_f4=-5.0f;velocity_y_f8=7.5f;acceleration_y_100=0.5f;split801(75,85.0);}return;
case 416:
    if(sequence_index_13e==1)landing();if(sequence_index_13e<1 && frame_index_140>=4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=yukari_surface(this);select_sequence(1);return;}}
    if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){field_180=1;counter(200,60);phase_counter(50);dispatch_character_wave_handle(3);velocity_x_f4=-5.0f;velocity_y_f8=7.5f;acceleration_y_100=0.5f;fan801(75,85.0,120.0f);}return;
case 418:
    landing();byte_47e=0;decelerate(0.5,false);if(!field_6bc)byte_750=0;if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==1)packet848(6.0f,-1);if(!frame_timer_142 && frame_index_140==3)event(29);}
    if(sequence_index_13e==1){if(!frame_timer_142 && frame_index_140==1){velocity_x_f4=20.0f;byte_47e=0;}if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(0);velocity_x_f4=0.0f;}}return;

case 500:ground810(field_6c0,3,300);return;
case 501:ground810(field_6c4,4,600);return;
case 502:air810(field_6c0,300);return;
case 503:air810(field_6c4,600);return;
case 505:ground811(field_6c0);return;
case 506:ground811(field_6c4);return;
case 510:ground812(field_6c0,200,120.0);return;
case 511:ground812(field_6c4,400,360.0);return;
case 520:
    if(!sequence_index_13e || sequence_index_13e==4)landing();byte_17c=1;
    if(!sequence_index_13e && byte_605>=4)word_4a8=2;
    if(sequence_index_13e>=1 && sequence_index_13e<=3){velocity_y_f8-=acceleration_y_100;if(sequence_index_13e==1){if(time_counter_144%12==0)event(29);field_12c=static_cast<float>(field_12c-40.0);if(velocity_y_f8<10.0f)velocity_y_f8=10.0f;if(field_180){if(++word_730>=6){field_180=0;word_730=0;}}}if(static_cast<unsigned char>(crossed())){reset_action_scratch();y_f0=yukari_surface(this);zero_motion();select_sequence(4);}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){counter(200,120);phase_counter(50);field_108=0.0f;field_10c=135.0f;if(byte_605>=4)word_4a8=5;float p[3]={0.0f,0.0f,1.0f};spawn_offset(815,0,135.0,p,3);velocity_y_f8=20.0f;acceleration_y_100=0.75f;dispatch_character_wave_handle(12);}
    if(entry(2))reset_action_scratch();return;
case 521:
    landing();byte_17c=1;
    if(sequence_index_13e==1 || sequence_index_13e==2){if(time_counter_144%12==0)event(29);field_12c=static_cast<float>(field_12c-40.0);if(field_180 && sequence_index_13e==1 && ++word_730>=6){field_180=0;word_730=0;}}
    decelerate(0.75,false);if(advance())set_action_and_finalize(0);
    if(entry(1)){counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(815,0,135.0,p,3);field_108=0.0f;field_10c=135.0f;velocity_x_f4=20.0f;dispatch_character_wave_handle(12);}
    if(entry(3))reset_action_scratch();return;
case 522:air802(12.0f,135.0f,37825.0f,225.0f,65025.0f);return;
case 523:air802(25.0f,330.0f,128500.0f,420.0f,190800.0f);return;
case 525:hold816(field_6c0,0.0f);return;
case 526:hold816(field_6c4,-45.0f);return;
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
    byte_17c=7;if(sequence_index_13e==3)landing();if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1))velocity_x_f4=30.0f;
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==1)opening826();if(!frame_timer_142 && frame_index_140==5){packet826(5.0f);dispatch_character_wave_handle(5);}}
    if(sequence_index_13e==1){if(!frame_index_140){if(field_6b4*facing_104>0)velocity_x_f4=6.0f;if(field_6b4*facing_104<0)velocity_x_f4=-6.0f;if(!field_6b4)velocity_x_f4=0.0f;if(time_counter_144>=15 && !byte_750)next_sequence_frame();}if(!frame_timer_142 && !frame_index_140)packet826(6.0f);if(!frame_timer_142 && frame_index_140==1)launch826(9.0f);}
    if(sequence_index_13e==2)falling826();return;
case 566:
    byte_17c=7;if(sequence_index_13e==3)landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==1)opening826();if(!frame_timer_142 && frame_index_140==5){packet826(5.0f);dispatch_character_wave_handle(5);}}
    if(sequence_index_13e==1){if(!frame_timer_142 && !frame_index_140)packet826(6.0f);
        if(!frame_index_140){if(frame_timer_142<75){if(field_6b4*facing_104>0)velocity_x_f4=6.0f;if(field_6b4*facing_104<0)velocity_x_f4=-6.0f;if(!field_6b4)velocity_x_f4=0.0f;if(frame_timer_142>=15 && !byte_750)frame_timer_142=75;}if(frame_timer_142==75)launch826(10.0f);}
        if(frame_index_140==1){velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>15.0f)velocity_x_f4=15.0f;interval_clear();}}
    if(sequence_index_13e==2)falling826();return;

case 600:simple_spell(850,2,-55,122.0,3,5,150,145.0,50);return;
case 601:simple_spell(851,3,0,100.0,3,4,75,135.0,51);return;
case 602:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2)spell_flash(34,152.0,1);
        if(!frame_timer_142 && frame_index_140==4 && field_6b4*facing_104<0){next_sequence_block();return;}
        if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,14.0f,0.0f};spawn(852,x_ec,0.0f,facing_104,1,p,3);dispatch_character_wave_handle(56);}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,14.0f,0.0f};spawn(852,x_ec,0.0f,static_cast<signed char>(-facing_104),1,p,3);dispatch_character_wave_handle(56);}return;
case 603:simple_spell(853,2,-55,122.0,4,5,150,145.0,50);return;
case 604:simple_spell(854,3,0,100.0,1,4,75,135.0,51);return;
case 605:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2)spell_flash(34,152.0,3);
        if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,20.0f,0.0f};spawn(855,static_cast<float>(100*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+115.0),1,1,p,3);
            p[0]=90.0f;spawn(855,static_cast<float>(100*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+115.0),1,1,p,3);
            p[0]=-90.0f;spawn(855,static_cast<float>(100*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+115.0),1,1,p,3);
            p[0]=180.0f;spawn(855,static_cast<float>(100*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+115.0),1,1,p,3);dispatch_character_wave_handle(56);}}return;
case 606:
    texture(2,2);if(sequence_index_13e==1 && time_counter_144>=40){next_sequence_block();return;}
    shower856();if(sequence_index_13e==2 && time_counter_144>=80){next_sequence_block();return;}
    if(advance()){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){spell_flash(-114,172.0,3);word_730=1;}return;
case 656:
    if(sequence_index_13e<=3)texture(2,2);if(sequence_index_13e==5)landing();
    if(sequence_index_13e==3 || sequence_index_13e==4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(5);y_f0=yukari_surface(this);zero_motion();return;}}
    if(sequence_index_13e==1 && time_counter_144>=40){next_sequence_block();return;}shower856();if(sequence_index_13e==2 && time_counter_144>=80){next_sequence_block();return;}
    if(advance()){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){spell_flash(-114,172.0,3);word_730=1;}
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==4)acceleration_y_100=0.25f;return;
case 607:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(word_730==1){if(word_732%5==0){if(word_734<4){dispatch_character_wave_handle(21);float p[3]={0.0f,0.0f,0.0f};
        if(!word_734)spawn(857,fighter_170->x_ec,static_cast<float>(fighter_170->y_f0+100.0),facing_104,1,p,3);
        else{float x=static_cast<float>(static_cast<float>(yukari_random(640))+fighter_170->x_ec);if(x>1200.0f)x=1200.0f;else if(x<80.0f)x=80.0f;float y=static_cast<float>(static_cast<float>(yukari_random(480))-140.0);if(y<-50.0f)y=-50.0f;else if(y>680.0f)y=680.0f;spawn(857,x,y,facing_104,1,p,3);}}++word_734;}++word_732;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==4)spell_flash(-8,141.0,2);if(!frame_timer_142 && frame_index_140==5)word_730=1;}return;
case 615:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==3)spell_flash(-43,150.0,5);if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,0.0f,0.0f};spawn(865,static_cast<float>(x_ec-150*facing_104),200.0f,facing_104,-2,p,3);dispatch_character_wave_handle(53);}}return;

case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){event(55);effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);effect(141,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1);effect(142,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);}return;
case 696:
    landing();if(frame_index_140>1)decelerate(2.0,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){velocity_x_f4=5.0f;byte_47e=0;}if(!frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);byte_47e=0;}return;
case 710:
    if(sequence_index_13e>=1 && sequence_index_13e<=3){velocity_x_f4=static_cast<float>(velocity_x_f4*static_cast<double>(0.98f));velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<0.0f && !word_730){velocity_y_f8=0.0f;word_730=1;}}
    if(sequence_index_13e==3){if(velocity_y_f8<0.0f)velocity_y_f8=0.0f;if(word_730==1){if(word_732>=390){next_sequence_block();acceleration_y_100=0.15f;return;}switch(g_match_identifier){case 3:difficulty900(60,2);break;case 2:difficulty900(72,2);break;case 1:difficulty900(72,3);break;case 0:difficulty900(90,0);break;}++word_732;}}
    if(sequence_index_13e==4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){next_sequence_block();return;}}
    if(advance())set_action_and_finalize(700);if(entry(1)){velocity_x_f4=static_cast<float>(static_cast<float>(yukari_random(10))-5.0);velocity_y_f8=10.0f;acceleration_y_100=0.25f;}return;
case 720:
    if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(700);if(entry(1))velocity_x_f4=30.0f;
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==1)opening910();if(!frame_timer_142 && frame_index_140==5){packet910(5.0f);dispatch_character_wave_handle(5);}}
    if(sequence_index_13e==1){if(!frame_index_140){if(!frame_timer_142){velocity_x_f4=static_cast<float>((fighter_170->x_ec-x_ec)*static_cast<double>(facing_104)/60.0);velocity_y_f8=0.0f;}if(frame_timer_142==60)velocity_x_f4=0.0f;switch(g_match_identifier){case 3:if(time_counter_144>=60){next_sequence_frame();velocity_x_f4=0.0f;}break;case 2:if(time_counter_144>=70){next_sequence_frame();velocity_x_f4=0.0f;}break;case 1:if(time_counter_144>=70){next_sequence_frame();velocity_x_f4=0.0f;}break;case 0:if(time_counter_144>=90){next_sequence_frame();velocity_x_f4=0.0f;}break;}}
        if(!frame_timer_142 && !frame_index_140)packet910(6.0f);if(!frame_timer_142 && frame_index_140==1)launch910(9.0f);}
    if(sequence_index_13e==2){if(!word_738){float p[3];switch(g_match_identifier){case 1:burst910(p,13,-60.0,60,70,5.0);break;case 2:burst910(p,18,-50.0,80,80,8.0);break;case 3:burst910(p,23,-40.0,100,100,10.0);break;}}falling826();}return;
case 721:
    if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==1)opening910();if(!frame_timer_142 && frame_index_140==5){packet910(5.0f);dispatch_character_wave_handle(5);}}
    if(sequence_index_13e==1){if(!frame_timer_142 && !frame_index_140){velocity_y_f8=0.0f;float choice=static_cast<float>(yukari_random(3));if(choice==0.0f)y_f0=0.0f;if(choice==1.0f)y_f0=200.0f;if(choice==2.0f)y_f0=400.0f;packet910(6.0f);}
        if(!frame_index_140){if(frame_timer_142<10)velocity_x_f4=7.0f;if(frame_timer_142==10)launch910(10.0f,7.0f);}if(frame_index_140==1)interval_clear();}
    if(sequence_index_13e==2)falling826();return;
case 730:
    velocity_x_f4=static_cast<float>(velocity_x_f4*static_cast<double>(0.98f));velocity_y_f8=static_cast<float>(static_cast<double>(0.98f)*velocity_y_f8);
    if(sequence_index_13e==1 && time_counter_144>=120){next_sequence_block();return;}
    if(advance()){set_action_and_finalize(704);word_7c0=static_cast<short>(yukari_random(60)+120);return;}
    if(entry(1)){switch(g_match_identifier){case 3:word_7be=270;break;case 2:word_7be=240;break;case 1:word_7be=210;break;case 0:word_7be=180;break;}}
    if(entry(3)){double y=y_f0;if(yukari_surface(this)>=y){zero_motion();set_action_and_finalize(700);word_7c0=static_cast<short>(yukari_random(60)+120);}}return;
case 740:
    landing();if(advance())set_action_and_finalize(700);if(entry(1)){set_action_and_finalize(0);return;}
    if(word_730==1){if(word_732%5==0){int limit;switch(g_match_identifier){case 3:limit=5;break;case 2:limit=4;break;case 1:case 0:limit=3;break;}
        // Native invalid-difficulty path reads an uninitialized local (588718).
        if(word_734<static_cast<short>(limit)){dispatch_character_wave_handle(21);float p[3]={0.0f,0.0f,0.0f};
            if(!word_734)spawn(930,fighter_170->x_ec,static_cast<float>(fighter_170->y_f0+100.0),facing_104,1,p,3);
            else{float x=static_cast<float>(static_cast<float>(yukari_random(640))+fighter_170->x_ec);if(x>1200.0f)x=1200.0f;else if(x<80.0f)x=80.0f;float y=static_cast<float>(static_cast<float>(yukari_random(480))-140.0);if(y<-50.0f)y=-50.0f;else if(y>680.0f)y=680.0f;spawn(930,x,y,facing_104,1,p,3);}}++word_734;}++word_732;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5)word_730=1;return;
case 741:
    landing();if(advance())set_action_and_finalize(700);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){switch(g_match_identifier){case 3:word_7c4=150;break;case 2:word_7c4=115;break;case 1:word_7c4=80;break;case 0:word_7c4=45;break;}word_7c6=0;}return;
case 750:
    x_ec=640.0f;y_f0=200.0f;
    if(!word_730){if(!sequence_index_13e)select_sequence(1);if(++word_732==60)finish_story_state();if(word_732>=60){unsigned char alpha=byte_113;if(alpha<=250)byte_113=static_cast<unsigned char>(alpha+5);else{byte_113=255;word_730=1;word_732=0;}}}
    if(word_730==1)++word_732;if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1 && !frame_index_140 && !frame_timer_142 && word_730==1 && word_732>=60)next_sequence_block();return;
case 770:
    if(advance())set_action_and_finalize(700);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)finish_story_state();return;
case 771:
    if(byte_113>=5){byte_113=static_cast<unsigned char>(byte_113-5);if(advance())set_action_and_finalize(700);}else{byte_113=0;x_ec=640.0f;y_f0=200.0f;facing_104=1;set_action_and_finalize(750);}return;
case 794:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==4){float p[3]={0.0f,0.0f,1.0f};spawn(899,x_ec,y_f0,facing_104,-1,p,3);p[1]=0.5f;p[2]=4.0f;spawn(899,x_ec,y_f0,facing_104,-1,p,3);p[2]=4.0f;p[1]=0.25f;spawn(899,x_ec,y_f0,facing_104,-1,p,3);dispatch_character_wave_handle(1);}if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,0.0f,5.0f};spawn(899,x_ec,y_f0,facing_104,1,p,3);dispatch_character_wave_handle(5);}}return;
case 795:
    if(!sequence_index_13e){velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.3f));if(static_cast<unsigned char>(crossed())){select_sequence(1);y_f0=yukari_surface(this);zero_motion();event(30);return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:
    velocity_x_f4=2.5f;if(sequence_index_13e==1 && x_ec>=480.0f){x_ec=480.0f;zero_motion();set_action_and_finalize(0);}else if(advance())set_action_and_finalize(0);return;
case 798:
    velocity_x_f4=2.5f;if(sequence_index_13e==1 && x_ec<=800.0f){x_ec=800.0f;zero_motion();set_action_and_finalize(700);}else if(advance())set_action_and_finalize(700);return;

default:common_update();return;
}
advance();
}
}
