#include "characters/SuikaActionState.hpp"
// Canonical JP1.06a 0x00598990 Suika Fighter +0x28 action-state root.
// See docs/SUIKA_ACTION_STATE_2026_10_28.md.

namespace th105 {
void SuikaActionStateView::dispatch_action_state_vslot28() {
    word_7a0=0;word_7a2=80;
    if(word_7a4>0){--word_7a4;if(fighter_170->word_174<=0 || word_174<=0)word_7a4=0;fighter_170->counter(2,30);}
    if(word_7a6>0){--word_7a6;if(fighter_170->word_174<=0 || word_174<=0)word_7a6=0;field_4c0=static_cast<float>(field_4c0*0.5);}
    if(word_186 || fighter_170->word_48c)return;
    switch(action_id_13c){
case 0:
    landing();if(velocity_x_f4==0.0f)byte_47e=0;idle_motion();break;
case 1:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:
    landing();idle_motion();break;
case 3:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:landing();velocity_x_f4=5.5f;break;
case 5:landing();velocity_x_f4=-5.5f;break;
case 6:if(!sequence_index_13e)landing();
if(!sequence_index_13e && !byte_47e)zero_motion();
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}}
advance();
if(entry(1)){velocity_x_f4=0.0f;velocity_y_f8=16.0f;acceleration_y_100=0.75f;byte_47e=0;}return;
case 7:if(!sequence_index_13e)landing();
if(!sequence_index_13e && !byte_47e)zero_motion();
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}}
advance();
if(entry(1)){velocity_x_f4=8.0f;velocity_y_f8=16.0f;acceleration_y_100=0.75f;byte_47e=0;}return;
case 8:if(!sequence_index_13e)landing();
if(!sequence_index_13e && !byte_47e)zero_motion();
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}}
advance();
if(entry(1)){velocity_x_f4=-8.0f;velocity_y_f8=16.0f;acceleration_y_100=0.75f;byte_47e=0;}return;
case 9:
    if(acceleration_y_100==0.0f)acceleration_y_100=0.6f;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
    break;
case 10:
    landing();zero_motion();if(advance()){if(!field_6b8)set_action_and_finalize(0);else set_action_and_finalize(2);}return;
case 197:
    landing();
    if(advance()){if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
    if(entry(1))velocity_x_f4=11.0f;
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){if(sequence_index_13e!=2)return;zero_motion();}
    if(sequence_index_13e==2 && frame_index_140==5 && !frame_timer_142)ground_face();return;
case 198:
    landing();
    if(advance()){if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
    if(entry(1))velocity_x_f4=-11.0f;
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){if(sequence_index_13e!=2)return;zero_motion();}
    if(sequence_index_13e==2 && frame_index_140==5 && !frame_timer_142)ground_face();return;
case 199:
    landing();if(advance()){if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
    if(!frame_timer_142 && frame_index_140==11)ground_face();return;
case 200:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1){
        if(time_counter_144%5==0)dash_dust(false);
        if(field_6b8<0){if(field_6b4*facing_104>0)set_action_and_finalize(212);else set_action_and_finalize(211);return;}
        ++word_730;if(field_6b4*facing_104<=0 || word_730>60){set_action_and_finalize(204);return;}
    }
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){velocity_x_f4=10.0f;dash_effects(false,80.0,true);}return;
case 201:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(true);++word_730;if((field_6b4*facing_104>=0 && word_730>=10) || word_730>60){set_action_and_finalize(205);return;}}
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){velocity_x_f4=-10.0f;dash_effects(true,80.0,true);}return;
case 202:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    if(sequence_index_13e==1 && time_counter_144>=16){next_sequence_block();flip();return;}
    advance();if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){word_730=0;velocity_x_f4=11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(false,110.0,true);}
    if(entry(2))flip();return;
case 203:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<2 && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e==1 && time_counter_144>=16){next_sequence_block();flip();return;}
    advance();if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){velocity_x_f4=-11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(true,120.0,false);}
    if(entry(3))flip();return;
case 204:
    landing();decelerate(0.5,true);if(advance()){set_action_and_finalize(0);byte_47e=0;}return;
case 205:
    landing();velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>0.0f){velocity_x_f4=0.0f;byte_47e=0;}
    if(advance()){set_action_and_finalize(0);byte_47e=0;}return;
case 208:if(!sequence_index_13e)landing();
if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
if(suika_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;}
if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
advance();
if(entry(1)){velocity_x_f4=0.0f;velocity_y_f8=21.0f;acceleration_y_100=0.75f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);}return;
case 209:if(!sequence_index_13e)landing();
if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
if(suika_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;}
if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
advance();
if(entry(1)){velocity_x_f4=10.0f;velocity_y_f8=16.0f;acceleration_y_100=0.7f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);}return;
case 210:
if(!sequence_index_13e)landing();
if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
if(suika_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;}
if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
advance();
if(entry(1)){velocity_x_f4=-10.0f;velocity_y_f8=16.0f;acceleration_y_100=0.7f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);}return;
case 211:
if(!sequence_index_13e)landing();
if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
if(suika_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;}
if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
advance();
if(entry(1)){velocity_x_f4=3.0f;velocity_y_f8=19.0f;acceleration_y_100=0.75f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);}return;
case 212:
if(!sequence_index_13e)landing();
if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
if(suika_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;}
if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
advance();
if(entry(1)){velocity_x_f4=10.0f;velocity_y_f8=16.0f;acceleration_y_100=0.7f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);}return;
case 214: {
    if(advance()){set_action_and_finalize(9);return;}
    if(entry(1))event(31);
    if(entry(6)){set_action_and_finalize(9);return;}
    if(field_6b8>0){if(field_6b4*facing_104>0)word_732=-45;else if(field_6b4*facing_104<0)word_732=-135;else word_732=-90;}
    else if(field_6b8<0){if(field_6b4*facing_104>0)word_732=45;else if(field_6b4*facing_104<0)word_732=135;else word_732=90;}
    else {if(field_6b4*facing_104>0)word_732=0;else if(field_6b4*facing_104<0)word_732=180;}
    if(sequence_index_13e==5 || sequence_index_13e==6)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e>0 && sequence_index_13e<5){
        ++word_736;
        word_734=static_cast<short>(word_732-static_cast<short>(static_cast<int>(field_740)));
        if(word_734>180)word_734=static_cast<short>(word_734-360);
        if(word_734<-180)word_734=static_cast<short>(word_734+360);
        // Native flight rates are 1.5 / 0.5, with distinct arithmetic branches.
        if(word_734>0){
            if(!field_4b8)field_740=static_cast<float>(field_740+1.5);
            else field_740=static_cast<float>(field_740+0.5);
        }
        if(word_734<0){
            if(!field_4b8)field_740=static_cast<float>(field_740-1.5);
            else field_740=static_cast<float>(field_740-0.5);
        }
        velocity_x_f4=static_cast<float>(suika_cosine(field_740)*field_73c);
        velocity_y_f8=static_cast<float>(suika_sine(field_740)*field_73c);
        if(y_f0>680.0f && velocity_y_f8>0.0f)velocity_y_f8=0.0f;
        field_73c=static_cast<float>(field_73c+static_cast<double>(0.3f));if(field_73c>12.0f)field_73c=12.0f;
        if(!field_4b8)counter(5,1);else counter(10,1);
        field_12c=-field_740;if(velocity_x_f4<0.0f)field_12c=static_cast<float>(180.0-field_740);
        if(velocity_x_f4<0.0f && sequence_index_13e==1)select_sequence(3);
        if(velocity_x_f4>=0.0f && sequence_index_13e==3)select_sequence(1);
        if(velocity_x_f4<0.0f && sequence_index_13e==2)select_sequence(4);
        if(velocity_x_f4>=0.0f && sequence_index_13e==4)select_sequence(2);
        if(time_counter_144%5==1){
            effect(125,
                static_cast<float>(suika_cosine(field_740)*100.0*facing_104+x_ec),
                static_cast<float>(suika_sine(field_740)*100.0+y_f0+100.0),
                facing_104,1);
        }
        // Native duplicates this gate without an intervening write/call.
        if((!field_6c8 && word_736>10) || word_482<=0){
            if((!field_6c8 && word_736>10) || word_482<=0){
                reset_action_scratch();
                if(sequence_index_13e==1 || sequence_index_13e==2){
                    if(facing_104==1){
                        if(x_ec>fighter_170->x_ec){facing_104=-1;velocity_x_f4=-velocity_x_f4;select_sequence(6);}
                        else select_sequence(5);
                    }else{
                        if(x_ec<fighter_170->x_ec){facing_104=-facing_104;velocity_x_f4=-velocity_x_f4;select_sequence(6);}
                        else select_sequence(5);
                    }
                }
                if(sequence_index_13e==3 || sequence_index_13e==4){
                    if(facing_104==1){
                        if(x_ec>fighter_170->x_ec){facing_104=-1;velocity_x_f4=-velocity_x_f4;select_sequence(5);return;}
                        select_sequence(6);return;
                    }
                    if(x_ec<fighter_170->x_ec){facing_104=-facing_104;velocity_x_f4=-velocity_x_f4;select_sequence(5);return;}
                    select_sequence(6);return;
                }
                return;
            }
        }
    }
    if(static_cast<unsigned char>(crossed())){
        y_f0=suika_surface(this);velocity_y_f8=0.0f;
        if(sequence_index_13e<5){reset_action_scratch();set_action_and_finalize(215);return;}
        set_action_and_finalize(10);zero_motion();return;
    }
    return;
}
case 215:
    landing();
    if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:if(!sequence_index_13e)landing();
if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
if(suika_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;}
if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
advance();
if(entry(1)){velocity_x_f4=0.0f;velocity_y_f8=21.0f;acceleration_y_100=0.75f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);}return;
case 221:
if(!sequence_index_13e)landing();
if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
if(suika_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;}
if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
advance();
if(entry(1)){velocity_x_f4=10.0f;velocity_y_f8=16.0f;acceleration_y_100=0.7f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);}return;
case 222:
if(!sequence_index_13e)landing();
if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}
if(suika_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;}
if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
advance();
if(entry(1)){velocity_x_f4=-10.0f;velocity_y_f8=16.0f;acceleration_y_100=0.7f;byte_47e=0;effect(63,x_ec,y_f0,facing_104,1);}return;
case 223:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);++word_730;if((field_6b4*facing_104<=0 && word_730>9) || word_730>60){set_action_and_finalize(204);return;}}
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){velocity_x_f4=5.0f;dash_effects(false,80.0,true);}return;
case 224:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(true);++word_730;if((field_6b4*facing_104>=0 && word_730>=10) || word_730>60){set_action_and_finalize(205);return;}}
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){velocity_x_f4=-10.0f;dash_effects(true,80.0,true);}return;
case 225:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<2 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){velocity_x_f4=-11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(true,120.0,false);}
    if(entry(3))flip();return;
case 226:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){word_730=0;velocity_x_f4=11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(false,110.0,true);}
    if(entry(2))flip();return;
case 300:
    landing();if(directional(0))return;decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3)velocity_x_f4=4.0f;
    if(!frame_timer_142 && frame_index_140==4){event(28);byte_47e=0;}return;
case 301:
    landing();if(directional(0))return;if(!field_6bc)byte_750=0;decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3 && byte_750){next_sequence_block();effect(62,static_cast<float>(x_ec-43*facing_104),static_cast<float>(y_f0+150.0),facing_104,1);return;}
        if(!frame_timer_142 && frame_index_140==6){event(29);byte_47e=0;}
    }
    if(sequence_index_13e==1){
        if(!frame_timer_142 && frame_index_140==2)velocity_x_f4=10.0f;
        if(!frame_timer_142 && frame_index_140==4){event(29);byte_47e=0;}
    }return;
case 302:
    landing();if(directional(1))return;if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3 && byte_750){next_sequence_block();effect(62,static_cast<float>(x_ec-16*facing_104),static_cast<float>(y_f0+135.0),facing_104,1);return;}
        if(!frame_timer_142 && frame_index_140==6){dispatch_character_wave_handle(0);float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);float p[3]={0.0f,0.0f,3.0f};spawn_offset(848,0,0.0,p,3);}return;
case 303:
    landing();if(directional(0))return;if(!field_6bc)byte_750=0;if(byte_47e>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3){event(28);velocity_x_f4=8.0f;byte_47e=0;}
        if(frame_index_140>=3)decelerate(static_cast<double>(0.8f),false);
    }
    if(sequence_index_13e==1){
        if(!frame_timer_142 && frame_index_140==2){
            dispatch_character_wave_handle(1);layout(5.0f);float p[3]={0.0f,0.0f,4.0f};spawn_offset(848,175,85.0,p,3);
            p[0]=-10.0f;p[2]=2.0f;spawn_offset(848,175,85.0,p,3);velocity_x_f4=9.5f;byte_47e=0;
        }
        if(frame_index_140>=2)decelerate(0.5,false);
    }return;
case 304:
    landing();if(directional(1))return;if(!field_6bc)byte_750=0;if(byte_47e>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e){
        if(frame_index_140>=6)decelerate(0.5,false);
        if(!frame_timer_142 && frame_index_140==4){
            if(byte_750){next_sequence_block();effect(62,static_cast<float>(34*facing_104+x_ec),static_cast<float>(y_f0+40.0),facing_104,1);return;}
            velocity_x_f4=15.0f;byte_47e=0;event(29);
        }
    }
    if(sequence_index_13e==1){if(frame_index_140>=3)decelerate(0.5,false);if(!frame_timer_142 && frame_index_140==1){velocity_x_f4=22.5f;byte_47e=0;event(29);}}return;
case 305:
    landing();if(directional(0))return;if(frame_index_140>16)decelerate(static_cast<double>(0.6f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5)event(28);
    if(!frame_timer_142 && frame_index_140==16){event(29);field_180=0;}return;
case 306:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(advance())set_action_and_finalize(9);if(!frame_timer_142 && frame_index_140==5)event(28);return;
case 307:
    if(!field_6bc)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(frame_index_140>=3){velocity_x_f4=static_cast<float>(velocity_x_f4+static_cast<double>(0.2f));if(velocity_x_f4>-2.0f)velocity_x_f4=-2.0f;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){
        dispatch_character_wave_handle(1);layout(5.0f);float p[3]={0.0f,0.0f,1.0f};spawn_offset(848,154,62.0,p,3);p[0]=10.0f;p[2]=2.0f;spawn_offset(848,154,62.0,p,3);
        velocity_x_f4=-12.5f;velocity_y_f8=6.0f;acceleration_y_100=0.5f;
    }return;
case 308:
    if(!field_6bc)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);velocity_y_f8=0.0f;acceleration_y_100=0.0f;return;}
    if(advance())set_action_and_finalize(9);
    if(!time_counter_144){if(frame_timer_142)return;if(!frame_index_140 && sequence_index_13e==1){set_action_and_finalize(9);return;}}
    if(!frame_timer_142 && frame_index_140==6){velocity_x_f4=-4.0f;velocity_y_f8=7.0f;acceleration_y_100=0.5f;event(29);}return;
case 309:
    if(!field_6bc)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==5){if(velocity_y_f8<0.0f)velocity_y_f8=0.0f;acceleration_y_100=-0.2f;}
        if(!sequence_index_13e){if(frame_timer_142)return;if(frame_index_140==5 || frame_index_140==7 || frame_index_140==9 || frame_index_140==11){event(27);field_180=0;byte_184=1;}}
        if(!frame_timer_142 && frame_index_140==13)acceleration_y_100=0.5f;
    }return;
case 310:
    if(field_180){++word_730;if(word_730>5){field_180=0;word_730=0;}}
    if(sequence_index_13e==1){
        if(!time_counter_144)velocity_x_f4=15.0f;if(time_counter_144%8==0)event(27);
        if(field_180){++word_730;if(word_730>5){field_180=0;word_730=0;}}
        if(time_counter_144>30){next_sequence_block();velocity_y_f8=6.0f;velocity_x_f4=static_cast<float>(velocity_x_f4*0.5);}
    }
    if(sequence_index_13e==2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;y_f0=suika_surface(this);set_action_and_finalize(9);return;}}
    if(advance())set_action_and_finalize(9);return;
case 320:
    landing();if(directional(0))return;if(frame_index_140>1)decelerate(2.0,false);
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5){event(28);byte_47e=0;}return;
case 321:
    landing();if(directional(1))return;if(frame_index_140>3)decelerate(0.5,false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){byte_47e=0;velocity_x_f4=16.5f;}
    if(!frame_timer_142 && frame_index_140==6)velocity_x_f4=0.0f;
    if(!frame_timer_142 && frame_index_140==6)event(29);return;
case 322:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(3);velocity_y_f8=0.0f;acceleration_y_100=0.0f;y_f0=suika_surface(this);}}
    if(sequence_index_13e==3)decelerate(static_cast<double>(0.8f),true);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){event(29);velocity_x_f4=15.0f;velocity_y_f8=6.0f;acceleration_y_100=0.9f;}return;
case 330:
    if(frame_index_140>=7)velocity_y_f8-=acceleration_y_100;else velocity_y_f8=static_cast<float>(velocity_y_f8-0.5);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(advance())set_action_and_finalize(9);if(!frame_timer_142 && frame_index_140==4)event(28);return;
case 331:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    switch(sequence_index_13e){case 1:{
        if(field_180 && byte_184>0){++word_730;if(word_730>5){word_730=0;field_180=0;}}
        if(time_counter_144%6==0)event(28);
        if(time_counter_144>=25){next_sequence_block();byte_184=1;field_180=0;velocity_y_f8=10.0f;velocity_x_f4=7.0f;acceleration_y_100=0.75f;return;}
    }break; case 2:{if(!frame_timer_142 && frame_index_140==2)event(29);}
    break; case 3: if(time_counter_144==45){set_action_and_finalize(9);return;} break;}
    if(advance())set_action_and_finalize(9);if(entry(4))acceleration_y_100=0.5f;return;
case 400:
    landing();if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==4 && byte_750){next_sequence_block();effect(62,static_cast<float>(x_ec-40*facing_104),static_cast<float>(y_f0+70.0),facing_104,1);return;}
        if(!frame_timer_142 && frame_index_140==6){float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,85,100.0,p,3);counter(200,45);phase_counter(30);field_180=1;dispatch_character_wave_handle(2);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && (frame_index_140==3 || frame_index_140==8 || frame_index_140==13)){
        if(frame_index_140==3){counter(200,45);phase_counter(30);}float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,85,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);
    }return;
case 401:
    landing();if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){counter(200,45);phase_counter(30);aim_float(-20.0f,20.0f);float p[3]={field_744,30.0f,3.0f};spawn_offset(800,85,100.0,p,3);field_180=1;dispatch_character_wave_handle(3);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){counter(200,45);phase_counter(30);aim_float(-20.0f,20.0f);float p[3]={field_744,30.0f,3.0f};spawn_offset(800,85,100.0,p,3);p[0]=static_cast<float>(field_744+10.0);spawn_offset(800,85,100.0,p,3);p[0]=static_cast<float>(field_744-10.0);spawn_offset(800,85,100.0,p,3);field_180=1;dispatch_character_wave_handle(3);}return;
case 402:
    landing();if(!field_6c0)byte_750=0;if(byte_47e>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==2 && byte_750){next_sequence_block();effect(62,static_cast<float>(28*facing_104+x_ec),static_cast<float>(y_f0+57.0),facing_104,1);return;}
        if(!frame_timer_142 && frame_index_140==3){event(29);byte_47e=0;}
        if(!frame_timer_142 && frame_index_140==4){counter(200,45);phase_counter(30);dispatch_character_wave_handle(1);effect(58,static_cast<float>(198*facing_104+x_ec),0.0f,facing_104,-1);layout(4.0f);}
    }
    if(sequence_index_13e==1){
        if(!frame_timer_142 && frame_index_140==1)velocity_x_f4=10.0f;
        if(!frame_timer_142 && frame_index_140==2){event(29);byte_47e=0;}
        if(!frame_timer_142 && frame_index_140==3){
            velocity_x_f4=0.0f;dispatch_character_wave_handle(1);counter(200,45);phase_counter(30);effect(58,static_cast<float>(198*facing_104+x_ec),0.0f,facing_104,-1);layout(7.0f);
            float p[3]={0.0f,0.0f,7.0f};spawn_offset(800,210,0.0,p,3);float n=0.0f;
            do{p[0]=static_cast<float>((n*60.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);p[2]=1.0f;
               if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;
               spawn_offset(811,40,0.0,p,3,static_cast<unsigned char>(word_730));n=static_cast<float>(n+1.0);
            }while(n<6.0f);
        }
        decelerate(static_cast<double>(0.7f),false);
    }return;
case 404:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !field_6c0)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);byte_47f=0;y_f0=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==4 && byte_750){next_sequence_block();effect(62,static_cast<float>(x_ec-35*facing_104),static_cast<float>(y_f0+80.0),facing_104,1);return;}
        if(!frame_timer_142 && frame_index_140==6){counter(200,45);phase_counter(30);float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3 || frame_index_140==8 || frame_index_140==13){if(frame_index_140==3){counter(200,45);phase_counter(30);}float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==16)acceleration_y_100=0.5f;
    }return;
case 405:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !field_6c0)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);byte_47f=0;y_f0=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(!frame_timer_142 && frame_index_140==6){counter(200,45);phase_counter(30);aim_float(-20.0f,20.0f);float p[3]={field_744,30.0f,3.0f};spawn_offset(800,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(3);}
        if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3){counter(200,45);phase_counter(30);aim_float(-20.0f,20.0f);float p[3]={field_744,30.0f,3.0f};spawn_offset(800,50,100.0,p,3);p[0]=static_cast<float>(field_744+10.0);spawn_offset(800,50,100.0,p,3);p[0]=static_cast<float>(field_744-10.0);spawn_offset(800,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(3);}
        if(!frame_timer_142 && frame_index_140==6)acceleration_y_100=0.5f;
    }return;
case 406:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !field_6c0)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);byte_47f=0;y_f0=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==4 && byte_750){next_sequence_block();effect(62,static_cast<float>(x_ec-40*facing_104),static_cast<float>(y_f0+70.0),facing_104,1);return;}
        if(!frame_timer_142 && frame_index_140==6){counter(200,45);phase_counter(30);float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3 || frame_index_140==8 || frame_index_140==13){if(frame_index_140==3){counter(200,45);phase_counter(30);}float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==16)acceleration_y_100=0.5f;
    }return;
case 408:
    landing();
    if(frame_index_140>=9)velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.7f));
    else{velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<10.0f)velocity_x_f4=10.0f;}
    if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==4)velocity_x_f4=15.0f;if(!frame_timer_142){if(frame_index_140==6)event(29);if(!frame_timer_142 && (frame_index_140==7 || frame_index_140==8 || frame_index_140==9))field_180=0;}}return;
case 409:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();y_f0=suika_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={10.0f,8.0f,0.0f};spawn_offset(801,85,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={10.0f,8.0f,0.0f};spawn_offset(801,85,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
    return;
case 411:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={30.0f,8.0f,0.0f};spawn_offset(801,85,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={30.0f,8.0f,0.0f};spawn_offset(801,85,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
    return;
case 412:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={10.0f,17.5f,0.0f};spawn_offset(801,18,88.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
    return;
case 414:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !field_6c0)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);byte_47f=0;y_f0=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={10.0f,8.0f,0.0f};spawn_offset(801,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={10.0f,8.0f,0.0f};spawn_offset(801,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==7)acceleration_y_100=0.5f;
    }return;
case 415:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !field_6c0)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);byte_47f=0;y_f0=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={30.0f,8.0f,0.0f};spawn_offset(801,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={30.0f,8.0f,0.0f};spawn_offset(801,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==7)acceleration_y_100=0.5f;
    }return;
case 416:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !field_6c0)byte_750=0;
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);byte_47f=0;y_f0=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={10.0f,0.0f,0.0f};spawn_offset(801,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={10.0f,0.0f,0.0f};spawn_offset(801,50,100.0,p,3);field_180=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==7)acceleration_y_100=0.5f;
    }return;
case 418:
    if(!sequence_index_13e || sequence_index_13e==5)landing();
    if(sequence_index_13e==2 && time_counter_144%15==0)event(28);
    if(sequence_index_13e<5){
        velocity_y_f8-=acceleration_y_100;
        if((sequence_index_13e==1 || sequence_index_13e==2) && field_180!=0 && field_180!=3){select_sequence(3);velocity_x_f4=-3.0f;velocity_y_f8=13.0f;acceleration_y_100=0.75f;field_180=1;return;}
        if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;acceleration_y_100=0.0f;y_f0=suika_surface(this);select_sequence(5);return;}
    }
    if(sequence_index_13e==5){
        if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
        if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+1.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    }
    if(advance())set_action_and_finalize(0);if(entry(1)){velocity_x_f4=12.0f;velocity_y_f8=9.0f;acceleration_y_100=0.5f;}return;
case 500:
    landing();byte_17c=0;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);
    if(entry(3) || entry(4)){set_action_and_finalize(0);return;}
    if(sequence_index_13e==1){
        if(word_730>=14 && (!byte_750 || word_730>=120)){
            if(byte_604<=1){next_sequence_block();return;}
            if(byte_604==2 || byte_604==3){select_sequence(3);return;}
            if(byte_604>=4){select_sequence(4);return;}
        }
        if(word_730==30){effect(62,static_cast<float>(x_ec-5*facing_104),static_cast<float>(y_f0+90.0),facing_104,1);word_732=1;}
        ++word_730;
    }
    if((sequence_index_13e==2 || sequence_index_13e==3 || sequence_index_13e==4) && !frame_timer_142 && frame_index_140==2){
        if(word_732==1){float p[4]={0.0f,25.0f,0.0f,120.0f};spawn_offset(810,140,70.0,p,4);
            effect(128,static_cast<float>(200*facing_104+x_ec),y_f0,facing_104,-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);layout(12.0f);}
        else{float p[4]={0.0f,8.0f,0.0f,static_cast<float>(byte_604*5.0+15.0)};spawn_offset(810,140,70.0,p,4);
            effect(128,static_cast<float>(200*facing_104+x_ec),y_f0,facing_104,-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);layout(8.0f);}
    }return;
case 501:
    landing();byte_17c=0;if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);
    if(entry(3)){set_action_and_finalize(0);return;}
    if(entry(4)){set_action_and_finalize(0);return;}
    if(sequence_index_13e==1){
        if(word_730>=14 && (!byte_750 || word_730>=120)){
            if(byte_604<=1){next_sequence_block();return;}
            if(byte_604==2 || byte_604==3){select_sequence(3);return;}
            if(byte_604>=4){select_sequence(4);return;}
        }
        if(word_730==30){effect(62,static_cast<float>(13*facing_104+x_ec),static_cast<float>(y_f0+142.0),facing_104,1);word_732=1;}
        ++word_730;
    }
    if((sequence_index_13e==2 || sequence_index_13e==3 || sequence_index_13e==4) && !frame_timer_142 && frame_index_140==4){
        if(word_732==1){float p[4]={-60.0f,25.0f,4.0f,120.0f};spawn_offset(810,80,166.0,p,4);
            effect(128,static_cast<float>(200*facing_104+x_ec),y_f0,facing_104,-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);layout(12.0f);}
        else{float p[4]={-60.0f,8.0f,4.0f,static_cast<float>(byte_604*5.0+15.0)};spawn_offset(810,80,166.0,p,4);
            effect(128,static_cast<float>(200*facing_104+x_ec),y_f0,facing_104,-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);layout(8.0f);}
    }return;
case 505:
    landing();byte_17c=4;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,7.0f};spawn_offset(815,-10,250.0,p,3);counter(200,120);phase_counter(50);}
    if(sequence_index_13e==1){if(word_730>=0 && (!byte_750 || word_730>=180)){next_sequence_block();return;}++word_730;}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)release_fragments811();return;
case 506:
    landing();byte_17c=4;if(!field_6c4)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,7.0f};spawn_offset(815,-10,250.0,p,3);counter(200,120);phase_counter(50);}
    if(sequence_index_13e==1){if(word_730>=0 && (!byte_750 || word_730>=180)){next_sequence_block();return;}++word_730;}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)release_fragments811();return;
case 507:
    if(sequence_index_13e==3)landing();byte_17c=4;if(!field_6c0)byte_750=0;
    if(sequence_index_13e<=2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);select_sequence(3);}}
    if(advance()){set_action_and_finalize(0);return;}if(entry(3)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,7.0f};spawn_offset(815,-10,250.0,p,3);counter(200,120);phase_counter(50);}
    if(sequence_index_13e==1){if(word_730>=0 && (!byte_750 || word_730>=180)){next_sequence_block();return;}++word_730;}
    if(sequence_index_13e==2){
        if(!frame_timer_142 && frame_index_140==2){release_fragments811();acceleration_y_100=0.5f;velocity_x_f4=-6.0f;velocity_y_f8=7.5f;}
        if(!frame_timer_142 && frame_index_140==8)acceleration_y_100=0.5f;
    }return;
case 508:
    if(sequence_index_13e==3)landing();byte_17c=4;if(!field_6c4)byte_750=0;
    if(sequence_index_13e<=2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);select_sequence(3);}}
    if(advance()){set_action_and_finalize(0);return;}if(entry(3)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,7.0f};spawn_offset(815,-10,250.0,p,3);counter(200,120);phase_counter(50);}
    if(sequence_index_13e==1){if(word_730>=0 && (!byte_750 || word_730>=180)){next_sequence_block();return;}++word_730;}
    if(sequence_index_13e==2){
        if(!frame_timer_142 && frame_index_140==2){release_fragments811();acceleration_y_100=0.5f;velocity_x_f4=-6.0f;velocity_y_f8=7.5f;}
        if(!frame_timer_142 && frame_index_140==8)acceleration_y_100=0.5f;
    }return;
case 520:
    if(!sequence_index_13e || sequence_index_13e==6)landing();byte_17c=1;
    velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==4 || sequence_index_13e==5){velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>-5.0f)velocity_x_f4=-5.0f;}
    if(static_cast<unsigned char>(crossed())){
        if(sequence_index_13e==3){dispatch_character_wave_handle(12);layout(6.0f);select_sequence(4);y_f0=suika_surface(this);velocity_x_f4=-12.5f;velocity_y_f8=5.5f;acceleration_y_100=0.35f;impact_fragments811();return;}
        if(sequence_index_13e==4 || sequence_index_13e==5){select_sequence(6);y_f0=suika_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){velocity_x_f4=3.0f;velocity_y_f8=12.5f;acceleration_y_100=0.25f;}
    if(entry(3)){velocity_x_f4=18.0f;velocity_y_f8=-18.0f;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;
case 521:
    if(!sequence_index_13e || sequence_index_13e==6)landing();byte_17c=1;
    velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==4 || sequence_index_13e==5){velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>-5.0f)velocity_x_f4=-5.0f;}
    if(static_cast<unsigned char>(crossed())){
        if(sequence_index_13e==3){dispatch_character_wave_handle(12);layout(6.0f);select_sequence(4);y_f0=suika_surface(this);velocity_x_f4=-12.5f;velocity_y_f8=5.5f;acceleration_y_100=0.35f;impact_fragments811();return;}
        if(sequence_index_13e==4 || sequence_index_13e==5){select_sequence(6);y_f0=suika_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){velocity_x_f4=8.0f;velocity_y_f8=12.5f;acceleration_y_100=0.25f;}
    if(entry(3)){velocity_x_f4=18.0f;velocity_y_f8=-18.0f;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;
case 522:
    if(sequence_index_13e==5)landing();byte_17c=1;
    velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==3 || sequence_index_13e==4){velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>-5.0f)velocity_x_f4=-5.0f;}
    if(static_cast<unsigned char>(crossed())){
        if(sequence_index_13e==2){dispatch_character_wave_handle(12);layout(6.0f);select_sequence(3);y_f0=suika_surface(this);velocity_x_f4=-12.5f;velocity_y_f8=5.5f;acceleration_y_100=0.35f;impact_fragments811();return;}
        if(sequence_index_13e==3 || sequence_index_13e==4){select_sequence(5);y_f0=suika_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(2)){velocity_x_f4=18.0f;velocity_y_f8=-18.0f;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;
case 523:
    if(sequence_index_13e==5)landing();byte_17c=1;
    velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==3 || sequence_index_13e==4){velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>-5.0f)velocity_x_f4=-5.0f;}
    if(static_cast<unsigned char>(crossed())){
        if(sequence_index_13e==2){dispatch_character_wave_handle(12);layout(6.0f);select_sequence(3);y_f0=suika_surface(this);velocity_x_f4=-12.5f;velocity_y_f8=5.5f;acceleration_y_100=0.35f;impact_fragments811();return;}
        if(sequence_index_13e==3 || sequence_index_13e==4){select_sequence(5);y_f0=suika_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(2)){velocity_x_f4=18.0f;velocity_y_f8=-18.0f;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;
case 525:
    landing();byte_17c=5;if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==6){
        layout(8.0f);float p[3];p[2]=2.0f;float n=0.0f;
        do{p[0]=static_cast<float>((n*60.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);
           if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;
           spawn_offset(816,103,0.0,p,3,static_cast<unsigned char>(word_730));n=static_cast<float>(n+1.0);
        }while(n<6.0f);
        p[2]=3.0f;spawn_offset(816,103,0.0,p,3,-1);p[2]=0.0f;
        float limit=static_cast<float>(byte_609+5.0);float m=0.0f;double count=limit;
        if(0.0<limit){do{p[0]=static_cast<float>(-static_cast<float>(suika_random(80))-20.0);p[1]=static_cast<float>(static_cast<float>(suika_random(18))+7.0);
            if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;
            spawn_offset(816,103,0.0,p,3);m=static_cast<float>(m+1.0);
        }while(m<count);}
        effect(127,x_ec,y_f0,facing_104,-1);dispatch_character_wave_handle(18);counter(200,120);phase_counter(50);
    }return;
case 526:
    landing();byte_17c=5;if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==6){
        layout(8.0f);float p[3];p[2]=2.0f;float n=0.0f;
        do{p[0]=static_cast<float>((n*60.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);
           if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;
           spawn_offset(816,103,0.0,p,3,static_cast<unsigned char>(word_730));n=static_cast<float>(n+1.0);
        }while(n<6.0f);
        p[2]=3.0f;spawn_offset(816,103,0.0,p,3,-1);p[2]=0.0f;
        float limit=static_cast<float>(byte_609+7.0);float m=0.0f;double count=limit;
        if(0.0<limit){do{p[0]=static_cast<float>(-static_cast<float>(suika_random(80))-20.0);p[1]=static_cast<float>(static_cast<float>(suika_random(20))+10.0);
            if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;
            spawn_offset(816,103,0.0,p,3);m=static_cast<float>(m+1.0);
        }while(m<count);}
        effect(127,x_ec,y_f0,facing_104,-1);dispatch_character_wave_handle(18);counter(200,120);phase_counter(50);
    }return;
case 530:
    landing();byte_17c=9;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){field_180=1;layout(8.0f);float p[3]={-80.0f,25.0f,0.0f};spawn_offset(821,100,0.0,p,3);effect(127,x_ec,y_f0,facing_104,-1);dispatch_character_wave_handle(23);counter(200,120);phase_counter(50);}return;
case 531:
    landing();byte_17c=9;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){field_180=1;layout(8.0f);float p[3]={-70.0f,35.0f,0.0f};spawn_offset(821,100,0.0,p,3);effect(127,x_ec,y_f0,facing_104,-1);dispatch_character_wave_handle(23);counter(200,120);phase_counter(50);}return;
case 540:
    landing();byte_17c=2;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){
        phase_counter(50);counter(200,120);field_180=1;float p[3];p[2]=0.0f;
        for(int n=0;n<byte_606+6;++n){
            p[0]=static_cast<float>(static_cast<float>(static_cast<float>(suika_random(50))*static_cast<double>(0.1f))+5.0);
            p[1]=static_cast<float>(static_cast<float>(suika_random(14))-7.0);
            spawn_offset(812,43,116.0,p,3);
        }dispatch_character_wave_handle(13);
    }return;
case 541:
    landing();byte_17c=2;if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){
        phase_counter(50);counter(200,120);field_180=1;float p[3];p[2]=2.0f;
        for(int n=0;n<byte_606+6;++n){
            p[0]=static_cast<float>(-static_cast<float>(suika_random(45))-10.0);p[1]=static_cast<float>(suika_random(6)+6u);
            spawn_offset(812,43,116.0,p,3);
        }dispatch_character_wave_handle(13);
    }return;
case 545:
    byte_17c=6;if(!field_6c0)byte_750=0;
    if(sequence_index_13e>=2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();y_f0=suika_surface(this);return;}}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3){phase_counter(50);counter(200,120);field_744=static_cast<float>(suika_random(45));field_73c=10.0f;field_740=15.0f;field_180=1;dispatch_character_wave_handle(19);}
        if(frame_index_140>=2){if(time_counter_144%2==0)mist817();if(frame_index_140==3){if(byte_113>=15)byte_113-=15;else byte_113=0;}}
    }
    if(sequence_index_13e==1){
        if(time_counter_144%2==0)mist817();
        if(!word_730){field_73c+=field_740;field_740=static_cast<float>(field_740-0.75);if(field_740<=0.0f){field_740=0.0f;word_730=1;}}
        if(word_730==1){
            field_740=static_cast<float>(field_740+static_cast<double>(0.15f));field_73c-=field_740;
            if(field_73c<=0.0f){
                byte_113=255;dispatch_character_wave_handle(20);field_73c=0.0f;next_sequence_block();velocity_x_f4=static_cast<float>(velocity_x_f4*static_cast<double>(0.3f));velocity_y_f8=12.0f;acceleration_y_100=0.5f;
                if(byte_60a>=4){
                    float p[3];float n=0.0f;do{p[0]=static_cast<float>(n*60.0);p[1]=15.0f;p[2]=3.0f;spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<6.0f);
                    n=0.0f;do{p[0]=static_cast<float>(n*60.0+30.0);p[1]=17.5f;p[2]=3.0f;spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<6.0f);return;
                }
                if(byte_60a<2)return;
                float p[3];float n=0.0f;do{p[0]=static_cast<float>(n*60.0);p[1]=15.0f;p[2]=3.0f;spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<6.0f);return;
            }
        }steer_cloud(static_cast<double>(0.05f));
    }return;
case 546:
    byte_17c=6;if(!field_6c0)byte_750=0;
    if(sequence_index_13e>=2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();y_f0=suika_surface(this);return;}}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){
        phase_counter(50);counter(200,120);field_744=static_cast<float>(suika_random(45));field_73c=10.0f;field_740=15.0f;field_180=1;dispatch_character_wave_handle(19);
        float n=0.0f;do{float p[3]={static_cast<float>(n*45.0+field_744),0.0f,0.0f};spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<8.0f);
    }
    if(sequence_index_13e==1){
        if(!word_730){field_73c+=field_740;field_740=static_cast<float>(field_740-0.75);if(field_740<=0.0f){field_740=0.0f;word_730=1;}}
        if(word_730==1){field_740=static_cast<float>(field_740+static_cast<double>(0.1f));field_73c-=field_740;
            if(field_73c<=0.0f){dispatch_character_wave_handle(20);field_73c=0.0f;next_sequence_block();zero_motion();
                float n=0.0f;do{float p[3]={static_cast<float>(n*45.0),15.0f,3.0f};spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<8.0f);return;
            }
        }steer_cloud(static_cast<double>(0.1f));
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==6)acceleration_y_100=0.5f;return;
case 547:
    if(sequence_index_13e==2)landing();byte_17c=2;
    if(sequence_index_13e<2){velocity_y_f8-=acceleration_y_100;double predicted=static_cast<double>(velocity_y_f8)+y_f0;if(suika_surface(this)>=predicted && velocity_y_f8<0.0f){zero_motion();select_sequence(2);y_f0=suika_surface(this);return;}}
    if(sequence_index_13e<=1 && !field_6c0)byte_750=0;if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==8 && byte_750==1){next_sequence_block();return;}
        if(!frame_timer_142 && frame_index_140==6){field_180=1;dispatch_character_wave_handle(7);velocity_x_f4=-4.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;spawn_offset(816,30,62.0,0,0);counter(200,120);phase_counter(50);}
    }return;
case 560:
    landing();byte_17c=3;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){float p[3]={7.0f,6.0f,0.0f};spawn_offset(813,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={7.0f,6.0f,3.0f};spawn_offset(813,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}return;
case 561:
    landing();byte_17c=3;if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){float p[3]={15.0f,6.0f,0.0f};spawn_offset(813,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={15.0f,6.0f,3.0f};spawn_offset(813,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}return;
case 562:
    if(sequence_index_13e==5)landing();byte_17c=3;
    velocity_y_f8-=acceleration_y_100;
    {double predicted=static_cast<double>(velocity_y_f8)+y_f0;if(suika_surface(this)>=predicted && velocity_y_f8<0.0f && sequence_index_13e<5){select_sequence(5);acceleration_y_100=0.0f;byte_47f=0;y_f0=suika_surface(this);zero_motion();return;}}
    if(sequence_index_13e<2 && !field_6c4)byte_750=0;shot808_burst(true,true);
    if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>4 && (!byte_750 || time_counter_144>25))next_sequence_block();
    if(entry(1)){if(byte_750==1)effect(62,static_cast<float>(x_ec-23*facing_104),static_cast<float>(y_f0+107.0),facing_104,1);float p[3]={0.0f,0.0f,4.0f};spawn_offset(808,-23,107.0,p,3);}
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){word_730=1;counter(200,120);}
    if(sequence_index_13e==3 && ((time_counter_144>10 && !byte_750) || time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;return;
case 565:
    landing();byte_17c=7;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){float p[3]={7.0f,10.0f,0.0f};spawn_offset(818,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={7.0f,10.0f,3.0f};spawn_offset(818,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}return;
case 566:
    landing();byte_17c=7;if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){float p[3]={15.0f,10.0f,0.0f};spawn_offset(818,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={15.0f,10.0f,3.0f};spawn_offset(818,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}return;
case 599:
    if(word_730>0 && frame_index_140<7 && word_730<12){
        word_734=static_cast<short>(suika_random_u32()%35u);
        float p[3];p[0]=static_cast<float>(-20-word_734);p[1]=static_cast<float>(static_cast<short>(static_cast<short>(suika_random_u32()%5u)+10));p[2]=0.0f;
        spawn(807,static_cast<float>((word_730+1)*facing_104*20+static_cast<double>(x_ec)),y_f0,facing_104,1,p,3);
        p[0]=static_cast<float>(suika_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        spawn(801,static_cast<float>((word_730+1)*facing_104*20+static_cast<double>(x_ec)),y_f0,facing_104,1,p,3);
        if(word_730==1){dispatch_character_wave_handle(0);counter(200,120);}++word_730;
    }
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)word_730=1;return;
case 600:
    if(!sequence_index_13e || sequence_index_13e==5)landing();texture(5,2);
    if(sequence_index_13e==2){velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.4f));if(velocity_y_f8<1.0f)velocity_y_f8=1.0f;++word_730;if(word_730>=70){next_sequence_block();return;}}
    if(sequence_index_13e==3 || sequence_index_13e==4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(5);y_f0=suika_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){spell_flash(0,100.0,2);float p[3]={0.0f,0.0f,0.0f};spawn_offset(850,0,100.0,p,3);dispatch_character_wave_handle(50);velocity_y_f8=10.0f;}
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2){velocity_y_f8=6.0f;velocity_x_f4=-8.0f;acceleration_y_100=0.5f;}return;
case 601:
    if(sequence_index_13e<=2)landing();texture(5,2);
    if(sequence_index_13e==2){
        if(field_180==1){
            if(x_ec>750.0f && facing_104==1)x_ec=750.0f;
            if(x_ec<550.0f && facing_104==-1)x_ec=550.0f;
            next_sequence_block();fighter_170->set_action_and_finalize(102);
            fighter_170->x_ec=static_cast<float>(510*facing_104+x_ec);fighter_170->y_f0=y_f0;fighter_170->zero_motion();return;
        }
        if(landing()){fighter_170->field_18c=0.0f;fighter_170->field_190=0.0f;fighter_170->set_action_and_finalize(53);}
    }
    if(advance())set_action_and_finalize(0);if(entry(3))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(50,160.0,2);
    if(sequence_index_13e==3 && !frame_timer_142){
        if(frame_index_140==2){layout(5.0f);fighter_170->x_ec=static_cast<float>(470*facing_104+x_ec);float p[3]={0.0f,0.0f,0.0f};spawn_offset(851,0,0.0,p,3);dispatch_character_wave_handle(55);}
        if(!frame_timer_142 && frame_index_140==3)fighter_170->x_ec=static_cast<float>(450*facing_104+x_ec);
        if(!frame_timer_142 && frame_index_140==4)fighter_170->x_ec=static_cast<float>(400*facing_104+x_ec);
        if(!frame_timer_142 && frame_index_140==5)fighter_170->x_ec=static_cast<float>(330*facing_104+x_ec);
        if(!frame_timer_142 && frame_index_140==6){fighter_170->consume_steps(1);
            if(fighter_170->word_174>0){fighter_170->set_action_and_finalize(53);fighter_170->facing_104=facing_104;}
            else{fighter_170->field_18c=-5.0f;fighter_170->field_190=12.0f;fighter_170->set_action_and_finalize(77);fighter_170->facing_104=-facing_104;}
        }
    }return;
case 602:
    if(frame_index_140==19)landing();texture(5,2);if(entry(0))spell_flash(20,50.0,2);
    if(frame_index_140>=6 && frame_index_140<=17){field_108=0.0f;field_10c=0.0f;scale_x_11c=static_cast<float>(2.0-field_73c);scale_y_120=scale_x_11c;field_73c=static_cast<float>(field_73c*0.75);}
    if(frame_index_140==18){scale_x_11c=static_cast<float>(scale_x_11c-static_cast<double>(0.1f));if(scale_x_11c<1.0f)scale_x_11c=1.0f;scale_y_120=scale_x_11c;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==6){
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(852,0,0.0,p,3,-1);float n=0.0f;
        do{p[0]=static_cast<float>((n*45.0-20.0)+static_cast<float>(suika_random(40)));p[1]=30.0f;p[2]=1.0f;if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;spawn_offset(811,40,0.0,p,3,static_cast<unsigned char>(word_730));n=static_cast<float>(n+1.0);}while(n<8.0f);
        dispatch_character_wave_handle(53);
    }
    if(!frame_timer_142 && frame_index_140==18)dispatch_character_wave_handle(54);
    if(!frame_timer_142 && frame_index_140==19){scale_x_11c=1.0f;scale_y_120=1.0f;}return;
case 603:
    if(!sequence_index_13e || sequence_index_13e==7)landing();texture(5,2);
    if(sequence_index_13e==1 || sequence_index_13e==2){
        velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(7);y_f0=suika_surface(this);velocity_y_f8=0.0f;acceleration_y_100=0.0f;return;}
        if(sequence_index_13e==2 && (field_180==1 || field_180==7)){zero_motion();next_sequence_block();fighter_170->zero_motion();fighter_170->set_action_and_finalize(107);sync_grab_peer();return;}
    }
    if(sequence_index_13e==3){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<1.0f)velocity_y_f8=1.0f;shared_first(1,x_ec);shared_second(1,y_f0);sync_grab_peer();}
    if(sequence_index_13e==4){shared_first(1,x_ec);shared_second(1,y_f0);if(word_730>=120){next_sequence_block();return;}++word_730;fighter_170->facing_104=facing_104;}
    if(sequence_index_13e==5 && frame_index_140>=4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(7);y_f0=suika_surface(this);zero_motion();return;}}
    if(sequence_index_13e==6){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=suika_surface(this);zero_motion();return;}}
    if(sequence_index_13e==7)decelerate(0.75,false);
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(0,100.0,5);
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2){velocity_y_f8=12.5f;acceleration_y_100=0.5f;}
    if(sequence_index_13e==4){switch(frame_index_140){
        case 0:pose_grab_peer(-135.0f,44,128.0);break;
        case 1:pose_grab_peer(-60.0f,50,85.0);break;
        case 2:pose_grab_peer(-10.0f,20,60.0);break;
        case 3:pose_grab_peer(45.0f,-28,50.0);break;
        case 4:pose_grab_peer(90.0f,-55,100.0);break;
        case 5:pose_grab_peer(135.0f,-50,140.0);break;
        case 6:pose_grab_peer(180.0f,-5,150.0);break;
    }}
    if(sequence_index_13e==5){
        if(!frame_timer_142){
            if(frame_index_140==2){shared_first(0,x_ec);shared_second(0,y_f0);fighter_170->facing_104=-facing_104;fighter_170->field_18c=36.0f;fighter_170->field_190=-18.0f;fighter_170->set_action_and_finalize(88);velocity_y_f8=6.0f;velocity_x_f4=-6.0f;acceleration_y_100=0.75f;dispatch_character_wave_handle(51);}
            if(!frame_timer_142 && frame_index_140==4)acceleration_y_100=0.5f;
        }
        switch(frame_index_140){
        case 0:pose_grab_peer(180.0f,21,140.0);break;
        case 1:pose_grab_peer(120.0f,85,85.0);fighter_170->facing_104=-facing_104;break;
        }
    }
    if(entry(1)){velocity_x_f4=10.0f;velocity_y_f8=10.0f;acceleration_y_100=0.6f;}
    if(entry(4)){dispatch_character_wave_handle(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(853,20,50.0,p,3);}return;
case 604:
    if(sequence_index_13e<=2)landing();texture(5,2);
    if(sequence_index_13e==2){
        if(field_180==1){
            if(x_ec>750.0f && facing_104==1)x_ec=750.0f;if(x_ec<550.0f && facing_104==-1)x_ec=550.0f;
            next_sequence_block();fighter_170->x_ec=static_cast<float>(510*facing_104+x_ec);fighter_170->y_f0=y_f0;fighter_170->zero_motion();fighter_170->set_action_and_finalize(102);return;
        }
        if(landing()){fighter_170->field_18c=0.0f;fighter_170->field_190=0.0f;fighter_170->set_action_and_finalize(53);}
    }
    if(advance())set_action_and_finalize(0);if(entry(3))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(50,160.0,4);
    if(sequence_index_13e==3){
        if(!frame_timer_142 && frame_index_140==2){layout(5.0f);fighter_170->x_ec=static_cast<float>(470*facing_104+x_ec);float p[3]={0.0f,0.0f,0.0f};spawn_offset(854,0,0.0,p,3);dispatch_character_wave_handle(55);}
        if(frame_index_140==2 && time_counter_144%4==0){float p[3]={0.0f,0.0f,1.0f};spawn(854,fighter_170->x_ec,static_cast<float>(fighter_170->y_f0+100.0),facing_104,1,p,3);}
        if(!frame_timer_142 && frame_index_140==3)fighter_170->x_ec=static_cast<float>(450*facing_104+x_ec);
        if(!frame_timer_142 && frame_index_140==4)fighter_170->x_ec=static_cast<float>(400*facing_104+x_ec);
        if(!frame_timer_142 && frame_index_140==5)fighter_170->x_ec=static_cast<float>(330*facing_104+x_ec);
        if(!frame_timer_142 && frame_index_140==6){word_7a4=600;
            if(fighter_170->word_174>0){fighter_170->set_action_and_finalize(53);fighter_170->facing_104=facing_104;}
            else{fighter_170->field_18c=-5.0f;fighter_170->field_190=12.0f;fighter_170->set_action_and_finalize(77);fighter_170->facing_104=-facing_104;}
        }
    }return;
case 605:
    texture(5,2);
    switch(sequence_index_13e){
    case 0:
        if(entry(0)){set_counter_48a(40);event(23);effect(115,static_cast<float>(20*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+50.0),facing_104,1);secondary_cycle();sequence_window(0,4,60);}
        if(frame_index_140>=6 && frame_index_140<=15){field_108=0.0f;field_10c=0.0f;scale_x_11c=static_cast<float>(3.0-field_73c);scale_y_120=scale_x_11c;field_73c=static_cast<float>(field_73c*0.75);}
        if(frame_index_140==3 && !frame_timer_142){byte_184=1;field_180=0;}break;
    case 1:
        velocity_x_f4=0.0f;if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}y_f0=suika_surface(this);
        if(!word_7a6){select_sequence(14);dispatch_character_wave_handle(54);return;}
        if(field_6b8>0){
            if(((uint_6f4>0 && uint_6f4<3) || field_6bc==2 || uint_6dc>0) || ((uint_6f8>0 && uint_6f8<3) || field_6c0==2 || uint_6e0>0) || ((uint_6fc>0 && uint_6fc<3) || field_6c4==2 || uint_6e4>0)){select_sequence(15);return;}
        }else{
            if((uint_6f4>0 && uint_6f4<3) || field_6bc==2 || uint_6dc>0){select_sequence(7);return;}
            else if((uint_6f8>0 && uint_6f8<3) || field_6c0==2 || uint_6e0>0){select_sequence(8);return;}
            else if((uint_6fc>0 && uint_6fc<3) || field_6c4==2 || uint_6e4>0){select_sequence(9);return;}
        }
        if(field_6b4>0){facing_104=1;velocity_x_f4=4.0f;select_sequence(2);return;}
        if(field_6b4<0){facing_104=-1;velocity_x_f4=4.0f;select_sequence(2);return;}
        if(field_6b8<0){velocity_x_f4=0.0f;velocity_y_f8=0.0f;field_73c=0.0f;if(field_6b4*facing_104>0)field_73c=1.0f;if(field_6b4*facing_104<0)field_73c=-1.0f;select_sequence(3);return;}break;
    case 2:
        velocity_x_f4=0.0f;if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){velocity_y_f8=0.0f;select_sequence(5);return;}y_f0=suika_surface(this);
        if(!word_7a6){select_sequence(14);dispatch_character_wave_handle(54);return;}
        if(!frame_timer_142 && frame_index_140==6){field_180=0;byte_184=1;}
        if((uint_6f4>0 && uint_6f4<3) || field_6bc==2 || uint_6dc>0){select_sequence(7);byte_184=1;field_180=0;return;}
        else if((uint_6f8>0 && uint_6f8<3) || field_6c0==2 || uint_6e0>0){select_sequence(8);byte_184=1;field_180=0;return;}
        else if((uint_6fc>0 && uint_6fc<3) || field_6c4==2 || uint_6e4>0){select_sequence(9);byte_184=1;field_180=0;return;}
        else{
            if(!field_6b4){velocity_x_f4=0.0f;select_sequence(1);return;}
            if(field_6b4>0){facing_104=1;velocity_x_f4=4.0f;}if(field_6b4<0){facing_104=-1;velocity_x_f4=4.0f;}
            if(field_6b8<0){field_73c=0.0f;velocity_x_f4=0.0f;velocity_y_f8=0.0f;if(field_6b4)field_73c=1.0f;if(field_6b4>0)facing_104=1;if(field_6b4<0)facing_104=-1;select_sequence(3);return;}
        }break;
    case 4:case 5:
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);select_sequence(6);dispatch_character_wave_handle(56);layout(4.0f);float p[3];giant_ring855(p,8.0f,45.0,30.0f,0);return;}
        if((uint_6f4>0 && uint_6f4<3) || field_6bc==2 || uint_6dc>0){select_sequence(10);byte_184=1;field_180=0;return;}
        else if((uint_6f8>0 && uint_6f8<3) || field_6c0==2 || uint_6e0>0){select_sequence(12);byte_184=1;field_180=0;velocity_y_f8=5.0f;acceleration_y_100=0.45f;return;}
        else if((uint_6fc>0 && uint_6fc<3) || field_6c4==2 || uint_6e4>0){select_sequence(16);byte_184=1;field_180=0;return;}break;
    case 6:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 7:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 8:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 9:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 10:case 16:case 17:
        velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);select_sequence(11);return;}break;
    case 11:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 12:
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);byte_184=1;field_180=0;dispatch_character_wave_handle(58);layout(10.0f);select_sequence(13);float p[3];giant_ring855(p,8.0f,45.0,30.0f,0);}break;
    case 13:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 14:
        if(!frame_index_140){scale_x_11c=static_cast<float>(scale_x_11c-static_cast<double>(0.03f));if(scale_x_11c<0.333f){scale_x_11c=0.333f;scale_y_120=0.333f;next_sequence_frame();return;}scale_y_120=scale_x_11c;}break;
    }
    if(advance()){select_sequence(1);return;}
    if(entry(1)){scale_x_11c=1.0f;scale_y_120=1.0f;}
    if(entry(4)){velocity_y_f8=10.0f;acceleration_y_100=0.3f;velocity_x_f4=static_cast<float>(field_73c*5.0);float p[3];giant_ring855(p,8.0f,45.0,30.0f,0);}
    if(entry(7)){select_sequence(1);return;}
    if(entry(8)){select_sequence(1);return;}
    if(entry(9)){select_sequence(1);return;}
    if(entry(10)){select_sequence(1);return;}
    if(entry(12)){select_sequence(1);return;}
    if(entry(14)){select_sequence(1);return;}
    if(entry(15)){set_action_and_finalize(0);scale_x_11c=1.0f;scale_y_120=1.0f;}
    if(entry(16)){select_sequence(1);return;}
    switch(sequence_index_13e){
    case 0:
        if(frame_index_140>=6)word_7a6=600;
        if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,0.0f,0.0f};spawn_offset(855,0,0.0,p,3,-1);giant_ring855(p,8.0f,45.0,30.0f,40);dispatch_character_wave_handle(53);}
        if(!frame_timer_142 && frame_index_140==16){scale_x_11c=1.0f;scale_y_120=1.0f;return;}break;
    case 1:if(!frame_timer_142 && frame_index_140==3){byte_184=1;field_180=0;}break;
    case 2:
        if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(56);layout(2.0f);float p[3];giant_ring855(p,6.0f,60.0,20.0f,70);}
        if(!frame_timer_142 && frame_index_140==7){dispatch_character_wave_handle(56);layout(2.0f);float p[3];giant_ring855(p,6.0f,60.0,20.0f,70);return;}break;
    case 3:if(!frame_timer_142 && frame_index_140==4){field_180=0;byte_184=1;}break;
    case 7:
        if(!frame_timer_142 && frame_index_140==10){byte_184=1;field_180=0;dispatch_character_wave_handle(57);layout(10.0f);float p[3];giant_ring855(p,8.0f,45.0,30.0f,420);}break;
    case 8:
        if(!frame_timer_142 && frame_index_140==6){byte_184=1;field_180=0;dispatch_character_wave_handle(58);layout(10.0f);float p[3];giant_ring855(p,8.0f,45.0,30.0f,310);}break;
    case 9:
        if(!frame_timer_142 && frame_index_140==7){byte_184=1;field_180=0;dispatch_character_wave_handle(57);layout(10.0f);float p[4];giant_ring855(p,8.0f,45.0,30.0f,240);p[0]=-65.0f;p[1]=20.0f;p[2]=5.0f;p[3]=180.0f;spawn_offset(855,250,460.0,p,4);}break;
    case 10:if(!frame_timer_142 && frame_index_140==4){byte_184=1;field_180=0;dispatch_character_wave_handle(57);}break;
    case 15:
        if(!frame_timer_142 && frame_index_140==7){dispatch_character_wave_handle(58);layout(10.0f);float p[3]={0.0f,7.0f,3.0f};spawn_offset(855,210,0.0,p,3);}break;
    case 16:
        if(!frame_timer_142 && frame_index_140==3){byte_184=1;field_180=0;velocity_y_f8=12.0f;acceleration_y_100=0.3f;velocity_x_f4=static_cast<float>(velocity_x_f4+4.0);if(velocity_x_f4>5.0f)velocity_x_f4=5.0f;dispatch_character_wave_handle(57);}break;
    }return;
case 606:
    texture(5,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==2)spell_flash(-20,135.0,1);
        if(!frame_timer_142 && frame_index_140==7){
            float p[3]={0.0f,0.0f,0.0f};spawn_offset(856,140,70.0,p,3);dispatch_character_wave_handle(19);
            p[0]=0.0f;p[1]=2.0f;p[2]=1.0f;spawn_offset(856,140,70.0,p,3);p[2]=3.0f;float n=0.0f;
            do{p[0]=static_cast<float>(n*45.0-20.0);p[1]=30.0f;if(p[0]<90.0f || p[0]>270.0f)word_730=-1;else word_730=1;spawn_offset(856,140,70.0,p,3,static_cast<unsigned char>(word_730));n=static_cast<float>(n+1.0);}while(n<8.0f);
        }
    }return;
case 607:
    landing();texture(5,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3)spell_flash(-50,130.0,4);
        if(!frame_timer_142 && frame_index_140==7){
            layout(8.0f);float p[3]={-82.0f,30.0f,0.0f};spawn_offset(857,100,0.0,p,3);effect(127,x_ec,y_f0,facing_104,-1);dispatch_character_wave_handle(59);
            p[2]=1.0f;float n=0.0f;
            do{p[0]=static_cast<float>(n*36.0+static_cast<float>(suika_random(20)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;spawn_offset(811,100,0.0,p,3,static_cast<unsigned char>(word_730));n=static_cast<float>(n+1.0);}while(n<10.0f);
        }
    }return;
case 608:
    if(!sequence_index_13e || sequence_index_13e==1)landing();texture(5,2);
    if(sequence_index_13e>=3 && sequence_index_13e<=11){shared_first(1,x_ec);shared_second(1,y_f0);}
    switch(sequence_index_13e){
    case 0:
        if(field_180==1){zero_motion();select_sequence(2);fighter_170->zero_motion();moving_grab_pose(0.0f,70.0,0.0);fighter_170->set_action_and_finalize(100);return;}break;
    case 3:case 4:
        velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){fighter_170->facing_104=-facing_104;zero_motion();select_sequence(5);layout(10.0f);y_f0=suika_surface(this);moving_grab_pose(0.0f,10.0,120.0);fighter_170->set_action_and_finalize(109);return;}break;
    case 6:case 7:
        velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){fighter_170->facing_104=-facing_104;zero_motion();select_sequence(8);layout(10.0f);y_f0=suika_surface(this);moving_grab_pose(0.0f,10.0,120.0);fighter_170->set_action_and_finalize(109);return;}break;
    case 9:case 10:
        velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(11);y_f0=suika_surface(this);fighter_170->set_action_and_finalize(107);moving_grab_pose(180.0f,21.0,140.0);return;}break;
    case 12:case 13:
        velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){y_f0=suika_surface(this);set_action_and_finalize(10);zero_motion();return;}break;
    }
    if(advance())set_action_and_finalize(0);
    if(entry(2)){set_action_and_finalize(0);return;}
    if(entry(12)){velocity_x_f4=-10.0f;velocity_y_f8=12.5f;acceleration_y_100=0.5f;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3)spell_flash(0,100.0,5);
        if(!frame_timer_142 && frame_index_140==7){double y=fighter_170->y_f0;if(suika_surface(fighter_170)==y)byte_184=1;else byte_184=0;}
    }
    if(sequence_index_13e==2){
        switch(frame_index_140){
        case 0:moving_grab_pose(0.0f,70.0,0.0);fighter_170->set_action_and_finalize(100);break;
        case 1:moving_grab_pose(0.0f,48.0,120.0);fighter_170->set_action_and_finalize(107);break;
        }
    }
    if(sequence_index_13e==3){
        switch(frame_index_140){
        case 0:fighter_170->field_12c=0.0f;fighter_170->x_ec=static_cast<float>(facing_104*(velocity_x_f4-25.0)+x_ec);fighter_170->y_f0=static_cast<float>(y_f0+143.0+velocity_y_f8);fighter_170->set_action_and_finalize(107);break;
        case 1:fighter_170->field_12c=0.0f;fighter_170->x_ec=static_cast<float>(facing_104*(velocity_x_f4-35.0)+x_ec);fighter_170->y_f0=static_cast<float>(y_f0+140.0+velocity_y_f8);fighter_170->set_action_and_finalize(107);break;
        }
    }
    if(sequence_index_13e==4 && !frame_index_140)moving_grab_vertical();
    if(sequence_index_13e==5){
        switch(frame_index_140){
        case 0:moving_grab_pose(0.0f,10.0,120.0);fighter_170->set_action_and_finalize(109);break;
        case 1:moving_grab_pose(-45.0f,55.0,117.0);fighter_170->set_action_and_finalize(109);break;
        case 2:
            moving_grab_pose(0.0f,83.0,0.0);fighter_170->word_186=20;fighter_170->set_action_and_finalize(97);fighter_170->select_sequence(3);fighter_170->zero_motion();
            if(!frame_timer_142){if(!word_4b2&&field_4b8==1)forward_hit_quantity(625,980,1,1);else forward_hit_quantity(500,980,1,1);grab_impact_effect(3,95);dispatch_character_wave_handle(5);}break;
        case 4:moving_grab_pose(0.0f,60.0,55.0);fighter_170->set_action_and_finalize(103);break;
        case 5:moving_grab_pose(0.0f,48.0,120.0);fighter_170->set_action_and_finalize(103);break;
        }
    }
    if(sequence_index_13e==6){
        switch(frame_index_140){
        case 0:fighter_170->field_12c=0.0f;fighter_170->x_ec=static_cast<float>(facing_104*(velocity_x_f4-25.0)+x_ec);fighter_170->y_f0=static_cast<float>(y_f0+143.0+velocity_y_f8);fighter_170->set_action_and_finalize(107);break;
        case 1:fighter_170->field_12c=0.0f;fighter_170->x_ec=static_cast<float>(facing_104*(velocity_x_f4-35.0)+x_ec);fighter_170->y_f0=static_cast<float>(y_f0+140.0+velocity_y_f8);fighter_170->set_action_and_finalize(107);break;
        }
    }
    if(sequence_index_13e==7 && !frame_index_140)moving_grab_vertical();
    if(sequence_index_13e==8){
        switch(frame_index_140){
        case 0:moving_grab_pose(0.0f,10.0,120.0);fighter_170->set_action_and_finalize(109);break;
        case 1:moving_grab_pose(-45.0f,55.0,117.0);fighter_170->set_action_and_finalize(109);break;
        case 2:
            moving_grab_pose(0.0f,83.0,0.0);fighter_170->word_186=20;fighter_170->set_action_and_finalize(97);fighter_170->select_sequence(3);fighter_170->zero_motion();
            if(!frame_timer_142){
                if(!word_4b2&&field_4b8==1)forward_hit_quantity(1250,980,1,1);else forward_hit_quantity(1000,980,1,1);grab_impact_effect(3,95);dispatch_character_wave_handle(5);
                float p[3];p[2]=1.0f;float n=0.0f;
                do{p[0]=static_cast<float>(n*36.0+static_cast<float>(suika_random(20)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;spawn_offset(811,95,0.0,p,3,static_cast<unsigned char>(word_730));n=static_cast<float>(n+1.0);}while(n<10.0f);
            }break;
        case 4:moving_grab_pose(0.0f,60.0,55.0);fighter_170->set_action_and_finalize(103);break;
        case 5:moving_grab_pose(0.0f,48.0,120.0);fighter_170->set_action_and_finalize(103);break;
        }
    }
    if(sequence_index_13e==9){
        fighter_170->facing_104=facing_104;shared_first(1,x_ec);shared_second(1,y_f0);
        fighter_170->x_ec=static_cast<float>(facing_104*(velocity_x_f4+45.0)+x_ec);fighter_170->y_f0=static_cast<float>(y_f0+120.0+velocity_y_f8);fighter_170->set_action_and_finalize(107);
    }
    if(sequence_index_13e==10){
        switch(frame_index_140){
        case 0:moving_grab_pose(-135.0f,44.0,128.0);break;
        case 1:moving_grab_pose(-60.0f,50.0,85.0);break;
        case 2:moving_grab_pose(-10.0f,20.0,60.0);break;
        case 3:moving_grab_pose(45.0f,-28.0,50.0);break;
        case 4:moving_grab_pose(90.0f,-55.0,100.0);break;
        case 5:moving_grab_pose(135.0f,-50.0,140.0);break;
        case 6:moving_grab_pose(180.0f,-5.0,150.0);break;
        }
    }
    if(sequence_index_13e==11){
        if(!frame_timer_142 && frame_index_140==2){
            fighter_170->facing_104=-facing_104;fighter_170->velocity_x_f4=0.0f;fighter_170->velocity_y_f8=0.0f;fighter_170->set_action_and_finalize(89);
            dispatch_character_wave_handle(51);layout(20.0f);dispatch_character_wave_handle(12);fighter_170->x_ec=static_cast<float>(60*facing_104+x_ec);fighter_170->y_f0=suika_surface(fighter_170);
            if(!word_4b2&&field_4b8==1)forward_hit_quantity(6875,980,1,1);else forward_hit_quantity(5500,980,1,1);grab_impact_effect(4,37);fighter_170->field_12c=0.0f;fighter_170->word_186=44;
            float p[3];p[2]=0.0f;float n=0.0f;
            do{p[0]=static_cast<float>(n*36.0+static_cast<float>(suika_random(20)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+45.0);if(p[0]<0.0f || p[0]>180.0f)word_730=-1;else word_730=1;spawn_offset(858,37,0.0,p,3,static_cast<unsigned char>(word_730));n=static_cast<float>(n+1.0);}while(n<10.0f);
            p[2]=3.0f;n=0.0f;
            do{p[0]=static_cast<float>(n*(-36.0)-static_cast<float>(suika_random(20)));p[1]=static_cast<float>(static_cast<float>(suika_random(25))+60.0);spawn_offset(858,37,0.0,p,3);n=static_cast<float>(n+1.0);}while(n<5.0f);
            p[2]=1.0f;spawn_offset(858,37,0.0,p,3);p[2]=2.0f;spawn_offset(858,37,0.0,p,3,-1);
        }
        switch(frame_index_140){
        case 0:fighter_170->set_action_and_finalize(107);moving_grab_pose(180.0f,21.0,140.0);break;
        case 1:fighter_170->set_action_and_finalize(107);moving_grab_pose(120.0f,85.0,85.0);fighter_170->facing_104=-facing_104;break;
        }
    }
    if(entry(3)){velocity_x_f4=2.0f;velocity_y_f8=11.0f;acceleration_y_100=0.75f;}
    if(entry(6)){velocity_x_f4=2.0f;velocity_y_f8=25.0f;acceleration_y_100=1.25f;}
    if(entry(9)){velocity_x_f4=2.0f;velocity_y_f8=60.0f;acceleration_y_100=1.75f;}
    if(entry(12)){shared_first(0,x_ec);shared_second(0,y_f0);fighter_170->word_186=0;return;}
    return;
case 650:
    texture(5,2);if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(600);select_sequence(1);spell_flash(0,100.0,2);float p[3]={0.0f,0.0f,0.0f};spawn_offset(850,0,100.0,p,3);dispatch_character_wave_handle(50);velocity_y_f8=10.0f;}return;
case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){event(55);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),facing_104,1);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),facing_104,1);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),facing_104,1);
        effect(141,x_ec,static_cast<float>(y_f0+100.0),facing_104,-1);effect(142,x_ec,y_f0,facing_104,-1);
    }return;
case 696:
    landing();decelerate(0.5,true);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){event(29);byte_47e=0;}return;
case 707:
    if(velocity_x_f4>12.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<12.0f)velocity_x_f4=12.0f;}
    if(advance()){set_action_and_finalize(700);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){velocity_x_f4=15.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);if(time_counter_144>30){next_sequence_block();return;}}
    if(sequence_index_13e==2)decelerate(0.5,false);return;
case 708:
    if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!suika_on_surface(this)){
        if(time_counter_144%5==0)dash_dust(true);
        velocity_y_f8=static_cast<float>(velocity_y_f8-0.5);double predicted=static_cast<double>(velocity_y_f8)+y_f0;
        if(suika_surface(this)>=predicted && velocity_y_f8<0.0f){velocity_y_f8=0.0f;y_f0=suika_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(700);return;}
    if(entry(1)){velocity_x_f4=-14.0f;velocity_y_f8=4.0f;dash_effects(true,80.0,false);}return;
case 710:
    if(advance()){set_action_and_finalize(700);return;}
    if(sequence_index_13e==1){if(time_counter_144%10==0)layout(4.0f);switch(g_match_identifier){
        case 3:case 2:if(time_counter_144>=240){next_sequence_block();return;}break;
        case 1:if(time_counter_144>=180){next_sequence_block();return;}break;
        case 0:if(time_counter_144>=120){next_sequence_block();return;}break;
    }}
    if(entry(1)){dispatch_character_wave_handle(15);float p[3]={0.0f,0.0f,0.0f};spawn_offset(900,0,100.0,p,3,-1);}return;
case 711:
    if(advance()){set_action_and_finalize(700);return;}
    if(sequence_index_13e==1){if(time_counter_144%10==0)layout(4.0f);switch(g_match_identifier){
        case 3:case 2:if(time_counter_144>=240){next_sequence_block();return;}break;
        case 1:if(time_counter_144>=180){next_sequence_block();return;}break;
        case 0:if(time_counter_144>=120){next_sequence_block();return;}break;
    }}
    if(entry(1)){dispatch_character_wave_handle(25);float p[3]={0.0f,0.0f,0.0f};spawn_offset(901,0,100.0,p,3,-1);}return;
case 720:
    landing();if(advance())set_action_and_finalize(700);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){
        layout(10.0f);float p[3];switch(g_match_identifier){
        case 3:p[0]=200.0f;p[1]=8.0f;p[2]=9.0f;spawn_offset(910,100,0.0,p,3);spawn(910,static_cast<float>(100*facing_104+x_ec),y_f0,static_cast<signed char>(-facing_104),1,p,3);effect(127,x_ec,y_f0,facing_104,-1);break;
        case 2:p[0]=121.0f;p[1]=8.0f;p[2]=9.0f;spawn_offset(910,100,0.0,p,3);spawn(910,static_cast<float>(100*facing_104+x_ec),y_f0,static_cast<signed char>(-facing_104),1,p,3);effect(127,x_ec,y_f0,facing_104,-1);break;
        case 1:p[0]=81.0f;p[1]=8.0f;p[2]=9.0f;spawn_offset(910,100,0.0,p,3);effect(127,x_ec,y_f0,facing_104,-1);break;
        case 0:p[0]=41.0f;p[1]=8.0f;p[2]=9.0f;spawn_offset(910,100,0.0,p,3);effect(127,x_ec,y_f0,facing_104,-1);break;
        }dispatch_character_wave_handle(59);
    }return;
case 730:
    switch(sequence_index_13e){
    case 0:
        if(frame_index_140>=6 && frame_index_140<=15){field_108=0.0f;field_10c=0.0f;scale_x_11c=static_cast<float>(3.0-field_73c);scale_y_120=scale_x_11c;field_73c=static_cast<float>(field_73c*0.75);}break;
    case 1:
        velocity_x_f4=0.0f;if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}y_f0=suika_surface(this);
        if((uint_6f4>0 && uint_6f4<3) || field_6bc==2 || uint_6dc>0){select_sequence(7);return;}
        else if((uint_6f8>0 && uint_6f8<3) || field_6c0==2 || uint_6e0>0){select_sequence(8);return;}
        else if((uint_6fc>0 && uint_6fc<3) || field_6c4==2 || uint_6e4>0){select_sequence(9);return;}
        else{
            if(word_76c==3){flip();velocity_x_f4=4.0f;select_sequence(2);return;}
            if(field_6b8<0){velocity_x_f4=0.0f;velocity_y_f8=0.0f;field_73c=0.0f;if(field_6b4*facing_104>0)field_73c=1.0f;if(field_6b4*facing_104<0)field_73c=-1.0f;select_sequence(3);return;}
        }break;
    case 2:
        switch(g_match_identifier){case 3:velocity_x_f4=5.0f;break;case 2:velocity_x_f4=4.5f;break;case 1:velocity_x_f4=4.0f;break;case 0:velocity_x_f4=3.0f;break;}
        if(classify_fighter_x_boundary()==1 && facing_104==-1)facing_104=1;
        if(classify_fighter_x_boundary()==-1 && facing_104==1)facing_104=-1;break;
    case 4:case 5:
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);select_sequence(6);dispatch_character_wave_handle(58);layout(10.0f);field_180=0;byte_184=1;float p[3];giant_ring920(920,p,8.0f,45.0,30.0f,0);return;}break;
    case 6:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 7:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 8:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 9:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 10:
        velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);select_sequence(11);return;}break;
    case 11:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 12:
        velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);byte_184=1;field_180=0;dispatch_character_wave_handle(58);layout(10.0f);select_sequence(13);float p[3];giant_ring920(920,p,8.0f,45.0,30.0f,0);}break;
    case 13:
        if(static_cast<double>(y_f0)>=suika_surface(this)+10.0){zero_motion();select_sequence(5);return;}break;
    case 14:
        if(!frame_index_140){scale_x_11c=static_cast<float>(scale_x_11c-static_cast<double>(0.03f));if(scale_x_11c<0.333f){scale_x_11c=0.333f;scale_y_120=0.333f;next_sequence_frame();return;}scale_y_120=scale_x_11c;}break;
    }
    if(advance()){set_action_and_finalize(700);scale_x_11c=1.0f;scale_y_120=1.0f;}
    if(entry(1)){scale_x_11c=1.0f;scale_y_120=1.0f;}
    if(entry(4)){
        velocity_y_f8=15.0f;acceleration_y_100=0.5f;velocity_x_f4=static_cast<float>(facing_104*(fighter_170->x_ec-x_ec)/60.0);
        if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
        switch(g_match_identifier){case 3:if(velocity_x_f4>=12.0f)velocity_x_f4=12.0f;break;case 2:if(velocity_x_f4>=10.0f)velocity_x_f4=10.0f;break;case 1:if(velocity_x_f4>=8.0f)velocity_x_f4=8.0f;break;case 0:if(velocity_x_f4>=6.0f)velocity_x_f4=6.0f;break;}
        float p[3];giant_ring920(920,p,8.0f,45.0,30.0f,0);
    }
    if(entry(7)){select_sequence(1);return;}
    if(entry(8)){select_sequence(1);return;}
    if(entry(9)){select_sequence(1);return;}
    if(entry(10)){select_sequence(1);return;}
    if(entry(12)){select_sequence(1);return;}
    if(entry(14)){select_sequence(1);return;}
    switch(sequence_index_13e){
    case 0:
        if(!frame_timer_142){
            if(frame_index_140==6){float p[3]={0.0f,0.0f,0.0f};spawn_offset(920,0,0.0,p,3,-1);giant_ring920(920,p,8.0f,45.0,30.0f,40);dispatch_character_wave_handle(53);}
            if(!frame_timer_142 && frame_index_140==16){scale_x_11c=1.0f;scale_y_120=1.0f;return;}
        }break;
    case 2:
        if(!frame_timer_142 && frame_index_140==2){field_180=0;byte_184=1;}
        if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(56);layout(2.0f);float p[3];giant_ring920(920,p,6.0f,60.0,20.0f,70);}
        if(!frame_timer_142 && frame_index_140==6){field_180=0;byte_184=1;}
        if(!frame_timer_142 && frame_index_140==7){dispatch_character_wave_handle(56);layout(2.0f);float p[3];giant_ring920(920,p,6.0f,60.0,20.0f,70);return;}
        break;
    case 7:
        if(!frame_timer_142 && frame_index_140==10){
            byte_184=1;field_180=0;dispatch_character_wave_handle(57);layout(10.0f);float p[4];giant_ring920(920,p,8.0f,45.0,30.0f,420);
            switch(g_match_identifier){
            case 1:{p[0]=0.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);return;}
            case 2:{
                p[0]=0.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);int n=10;
                do{p[0]=static_cast<float>(15.0-static_cast<float>(suika_random(30)));p[1]=static_cast<float>(static_cast<float>(suika_random(60))*static_cast<double>(0.1f)+6.0);p[2]=4.0f;p[3]=0.0f;spawn_offset(921,420,200.0,p,4);--n;}while(n);return;
            }
            case 3:{
                p[0]=0.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);int n=20;
                do{p[0]=static_cast<float>(35.0-static_cast<float>(suika_random(70)));p[1]=static_cast<float>(static_cast<float>(suika_random(60))*static_cast<double>(0.1f)+6.0);p[2]=4.0f;p[3]=0.0f;spawn_offset(921,420,200.0,p,4);--n;}while(n);return;
            }
            }
        }break;
    case 8:
        if(!frame_timer_142 && frame_index_140==6){byte_184=1;field_180=0;dispatch_character_wave_handle(58);layout(10.0f);float p[3];giant_ring920(855,p,8.0f,45.0,30.0f,310);return;}break;
    case 9:
        if(!frame_timer_142 && frame_index_140==7){
            byte_184=1;field_180=0;dispatch_character_wave_handle(57);layout(10.0f);float p[4];giant_ring920(855,p,8.0f,45.0,30.0f,240);
            switch(g_match_identifier){
            case 1:{p[0]=-65.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);return;}
            case 2:{
                p[0]=-65.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);int n=10;
                do{p[0]=static_cast<float>(static_cast<float>(suika_random(30))-80.0);p[1]=static_cast<float>(static_cast<float>(suika_random(60))*static_cast<double>(0.1f)+6.0);p[2]=4.0f;p[3]=0.0f;spawn_offset(921,420,200.0,p,4);--n;}while(n);return;
            }
            case 3:{
                p[0]=-65.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);int n=20;
                do{p[0]=static_cast<float>(static_cast<float>(suika_random(70))-100.0);p[1]=static_cast<float>(static_cast<float>(suika_random(60))*static_cast<double>(0.1f)+6.0);p[2]=4.0f;p[3]=0.0f;spawn_offset(921,420,200.0,p,4);--n;}while(n);return;
            }
            }
        }break;
    case 10:if(!frame_timer_142 && frame_index_140==4){byte_184=1;field_180=0;dispatch_character_wave_handle(57);return;}break;
    }return;
case 740:
    if(sequence_index_13e>=2 && sequence_index_13e<=4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();y_f0=suika_surface(this);return;}}
    if(sequence_index_13e==1){
        field_4c0=0.2f;if(time_counter_144%6==0)orbit_particle930();
        if(field_73c>0.0f){velocity_y_f8=field_73c;field_73c=static_cast<float>(field_73c*static_cast<double>(0.95f));if(field_73c<=static_cast<double>(0.1f)){field_73c=0.0f;velocity_y_f8=0.0f;}}
        if(field_73c==0.0f){++word_730;if(word_730>=10){field_73c=-1.0f;byte_184=1;float dx=static_cast<float>((fighter_170->x_ec-x_ec)*facing_104);field_744=-suika_atan(fighter_170->y_f0-y_f0,dx);word_730=0;}}
        if(field_73c==-1.0f){
            ++word_730;
            if(word_730<=600){
                if(field_180==6){byte_184=1;field_180=0;}
                if(field_180){++word_734;if(word_734>=5){word_734=0;byte_184=1;field_180=0;}}
                float dx=static_cast<float>((fighter_170->x_ec-x_ec)*facing_104);float desired=-suika_atan(fighter_170->y_f0-y_f0,dx);float delta=desired-field_744;
                if(suika_cosine(delta)<=0.0){field_740=static_cast<float>(field_740-static_cast<double>(0.05f));if(field_740<0.0f)field_740=0.0f;}
                else field_740=static_cast<float>(field_740+0.25);
                // No native initialized fallback is established outside difficulty0..3.
                float turn;int period;
                switch(g_match_identifier){
                case 3:turn=1.5f;period=4;if(field_740>=10.0f)field_740=10.0f;break;
                case 2:turn=1.25f;period=5;if(field_740>=8.0f)field_740=8.0f;break;
                case 1:turn=1.0f;period=7;if(field_740>=7.0)field_740=7.0f;break;
                case 0:turn=0.8f;period=10;if(field_740>=6.0f)field_740=6.0f;break;
                }
                float wrapped=static_cast<float>(static_cast<int>(delta)%360);if(wrapped>180.0f)wrapped=static_cast<float>(wrapped-360.0);if(wrapped<-180.0f)wrapped=static_cast<float>(wrapped+360.0);
                if(suika_absolute(wrapped)<=turn)field_744=desired;
                else{if(wrapped<0.0f)field_744-=turn;else if(wrapped>0.0f)field_744+=turn;}
                if(time_counter_144%period==0){dispatch_character_wave_handle(60);shot_particle930();}
            }else{byte_184=0;field_740=static_cast<float>(field_740-static_cast<double>(0.2f));field_748=static_cast<float>(field_748+static_cast<double>(0.05f));if(field_740<0.0f)field_740=0.0f;
                if(word_730>=690){burst999();byte_113=255;velocity_y_f8=15.0f;acceleration_y_100=0.2f;next_sequence_block();return;}
            }
            update_oriented_velocity();velocity_y_f8+=field_748;
        }
    }
    // Both native gravity/crossing passes are retained, with different call order.
    if(sequence_index_13e>=2 && sequence_index_13e<=4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(5);y_f0=suika_surface(this);return;}}
    if(advance())set_action_and_finalize(700);if(entry(1))field_73c=25.0f;
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3){burst999();dispatch_character_wave_handle(19);}
        if(frame_index_140>=2){if(time_counter_144%2==0)mist817();if(frame_index_140==3){if(byte_113>=15)byte_113-=15;else byte_113=0;}}
    }return;
case 750:
    if(sequence_index_13e==1){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<=0.0f){velocity_y_f8=0.0f;acceleration_y_100=0.0f;set_action_and_finalize(751);return;}}
    if(advance())set_action_and_finalize(700);if(entry(1)){velocity_x_f4=0.0f;velocity_y_f8=15.0f;acceleration_y_100=0.5f;}return;
case 751:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3];switch(g_match_identifier){
        case 3:p[0]=0.0f;p[1]=0.0f;p[2]=9.0f;spawn_offset(940,-10,250.0,p,3);p[2]=3.0f;spawn_offset(940,-10,250.0,p,3);p[2]=18.0f;spawn_offset(940,-10,250.0,p,3,-1);break;
        case 2:p[0]=0.0f;p[1]=0.0f;p[2]=8.0f;spawn_offset(940,-10,250.0,p,3);p[2]=3.0f;spawn_offset(940,-10,250.0,p,3);p[2]=18.0f;spawn_offset(940,-10,250.0,p,3,-1);break;
        case 1:p[0]=0.0f;p[1]=0.0f;p[2]=7.0f;spawn_offset(940,-10,250.0,p,3);p[2]=3.0f;spawn_offset(940,-10,250.0,p,3);p[2]=18.0f;spawn_offset(940,-10,250.0,p,3,-1);break;
        case 0:p[0]=0.0f;p[1]=0.0f;p[2]=7.0f;spawn_offset(940,-10,250.0,p,3);p[2]=3.0f;spawn_offset(940,-10,250.0,p,3);p[2]=18.0f;spawn_offset(940,-10,250.0,p,3,-1);break;
    }}
    if(sequence_index_13e==1){
        layout(2.0f);field_73c=static_cast<float>(field_73c+static_cast<double>(0.1f));switch(g_match_identifier){
        case 3:if(field_73c>=6.0f)field_73c=6.0f;break;
        case 2:if(field_73c>=5.0f)field_73c=5.0f;break;
        case 1:if(field_73c>=4.0f)field_73c=4.0f;break;
        case 0:if(field_73c>=3.0f)field_73c=3.0f;break;
        }
        field_6ac=field_73c;
        if((fighter_170->x_ec>x_ec && fighter_170->facing_104==1) || (fighter_170->x_ec<x_ec && fighter_170->facing_104==-1))field_6ac=-field_73c;
        if(time_counter_144>=300){next_sequence_block();return;}
    }
    if(sequence_index_13e==2 && !frame_timer_142){if(frame_index_140==2){flip();release_fragments811();}if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.2f;}
    if(sequence_index_13e==2 || sequence_index_13e==3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=suika_surface(this);select_sequence(4);return;}}return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){byte_655=1;finalize(-1);texture(2,-1);copy_health();word_76c=0;word_76a=1;word_766=0;word_768=0;word_764=0;event(23);}return;
case 795:
    if(!sequence_index_13e){
        if(time_counter_144%4==0)ending_smoke999();
        velocity_y_f8=static_cast<float>(-y_f0*static_cast<double>(0.1f));if(velocity_y_f8<-12.0f)velocity_y_f8=-12.0f;if(velocity_y_f8>-2.0f)velocity_y_f8=-2.0f;velocity_y_f8=-4.0f;
        x_ec=suika_sine_int(time_counter_144*3)*field_73c+field_740;field_73c=static_cast<float>(field_73c*static_cast<double>(0.9f));
        double y=y_f0;if(suika_surface(this)>=y){
            y_f0=suika_surface(this);next_sequence_block();velocity_y_f8=0.0f;x_ec=field_740;float n=0.0f;float p[3];
            do{p[0]=static_cast<float>((n*45.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(13))+12.0);p[2]=0.0f;spawn_offset(999,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<8.0f);
        }
    }
    if((sequence_index_13e==1 && time_counter_144>=120) || (sequence_index_13e==2 && word_734==1)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(700);return;
case 797:
    if(!sequence_index_13e && time_counter_144>=0){next_sequence_block();return;}
    if(sequence_index_13e==1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=suika_surface(this);zero_motion();ending_fragments811();return;}}
    if((!sequence_index_13e || sequence_index_13e==1) && time_counter_144%5==0)ending_smoke999();
    if(sequence_index_13e==3 && word_734==1){next_sequence_block();return;}if(advance())set_action_and_finalize(0);return;
case 798:
    if(!sequence_index_13e && time_counter_144>=0){next_sequence_block();return;}
    if(sequence_index_13e==1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){event(30);select_sequence(2);y_f0=suika_surface(this);zero_motion();ending_fragments811();return;}}
    if((!sequence_index_13e || sequence_index_13e==1) && time_counter_144%4==0)ending_smoke999();
    if(sequence_index_13e==3 && word_734==1){next_sequence_block();return;}if(advance())set_action_and_finalize(700);return;
    default:common_update();return;
    }
    advance();
}

}
