#include "characters/KomachiActionState.hpp"
// Canonical JP1.06a 0x005E20E0 Komachi Fighter +0x28 action-state root.
// See docs/KOMACHI_ACTION_STATE_2026_10_28.md.
namespace th105 {
void KomachiActionStateView::dispatch_action_state_vslot28() {

word_7a0 = 0;
word_7a2 = 106;

if (byte_72c == 2 && byte_55a > 0) {
    const short record_id = cards_55c[0].record_id_00;
    switch (record_id) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
        card_expiration();
        break;
    case 5:
    case 6:
    case 7:
    case 8:
        card_expiration();
        break;
    }
}
if (field_7a8 > 0)
    --field_7a8;
else
    field_7a8 = 0;
if (word_186 || peer()->word_48c)
    return;

switch(action_id_13c){

case 0:
    landing();
    if (velocity_x_f4 == 0.0f)
        byte_47e = 0;
    idle_motion();
    break;

case 1:
    landing();
    idle_motion();
    if (advance() && !frame_index_140)
        set_action_and_finalize(2);
    return;

case 2:
    landing();
    idle_motion();
    break;

case 3:
    landing();
    idle_motion();
    if (advance() && !frame_index_140)
        set_action_and_finalize(0);
    return;

case 4:
    landing();
    velocity_x_f4 = 4.5f;
    break;

case 5:
    landing();
    velocity_x_f4 = -4.5f;
    break;

case 6:
    normal_jump(0.0f);
    return;

case 7:
    normal_jump(4.5f);
    return;

case 8:
    normal_jump(-4.5f);
    return;

case 9:
    if (acceleration_y_100 == 0.0f)
        acceleration_y_100 = 0.6f;
    velocity_y_f8 -= acceleration_y_100;
    if (static_cast<unsigned char>(crossed())) {
        set_action_and_finalize(10);
        y_f0 = komachi_surface(this);
        zero_motion();
        return;
    }
    break;

case 10:
    landing();
    zero_motion();
    if (advance()) {
        if (!field_6b8)
            set_action_and_finalize(0);
        else
            set_action_and_finalize(2);
    }
    return;

case 197:recovery_jump(14.5f);return;
case 198:recovery_jump(-14.5f);return;
case 199:
    landing();if(advance()){if(byte_72c==2){set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
    if(!sequence_index_13e && frame_index_140==12 && !frame_timer_142)face_peer();return;

case 200:
    landing();byte_47e=1;if(velocity_x_f4>10.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<10.0f)velocity_x_f4=10.0f;}advance();
    if(sequence_index_13e==1){
        if(!(time_counter_144%5))dash_dust(false);
        if(field_6b8<0){if(field_6b4*facing()>0)set_action_and_finalize(212);else set_action_and_finalize(211);return;}
        ++word_730;if((field_6b4*facing()<=0 && word_730>5) || word_730>45){set_action_and_finalize(204);return;}
    }
    if(entry(1)){velocity_x_f4=10.0f;dash_effects(false,80.0,true);}return;
case 201:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!komachi_on_surface(this) && !(time_counter_144%5))dash_dust(true);
    if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;y_f0=komachi_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if(entry(1)){velocity_x_f4=-12.0f;velocity_y_f8=4.0f;acceleration_y_100=0.4f;dash_effects(true,80.0,false);}return;
case 202:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=komachi_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && !(time_counter_144%5))dash_dust(false);advance();
    if(entry(1)){velocity_x_f4=11.0f;velocity_y_f8=-1.0f;acceleration_y_100=0.5f;dash_effects(false,110.0,true);}if(entry(2))flip();return;
case 203:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=komachi_surface(this);frame_timer_142=0;set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && !(time_counter_144%5))dash_dust(true);advance();
    if(entry(1)){velocity_x_f4=-11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(true,120.0,false);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3)flip();return;
case 204:
    landing();velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}if(advance()){set_action_and_finalize(0);zero_motion();byte_47e=0;}return;
case 208:{
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);zero_motion();return;}
    if(komachi_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=0.0f;velocity_y_f8=20.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,ufacing(),1);return;}
case 209:{
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);zero_motion();return;}
    if(komachi_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=8.0f;velocity_y_f8=16.0f;acceleration_y_100=0.6f;byte_47e=0;effect(63,x_ec,y_f0,ufacing(),1);return;}
case 210:{
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);zero_motion();return;}
    if(komachi_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=-8.0f;velocity_y_f8=16.0f;acceleration_y_100=0.6f;byte_47e=0;effect(63,x_ec,y_f0,ufacing(),1);return;}
case 211:{
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);zero_motion();return;}
    if(komachi_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=2.0f;velocity_y_f8=20.0f;acceleration_y_100=0.65f;byte_47e=0;effect(63,x_ec,y_f0,ufacing(),1);return;}
case 212:{
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);zero_motion();return;}
    if(komachi_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=8.0f;velocity_y_f8=16.0f;acceleration_y_100=0.6f;byte_47e=0;effect(63,x_ec,y_f0,ufacing(),1);return;}

case 214:
    if(advance()){set_action_and_finalize(9);return;}if(entry(1))event(31);if(entry(6)){set_action_and_finalize(9);return;}
    if(field_6b8>0){
        if(field_6b4*facing_104>0)word_732=-45;
        else if(field_6b4*facing_104<0)word_732=-135;
        else word_732=-90;
    }else if(field_6b8<0){
        if(field_6b4*facing_104>0)word_732=45;
        else if(field_6b4*facing_104<0)word_732=135;
        else word_732=90;
    }else{
        if(field_6b4*facing_104>0)word_732=0;
        else if(field_6b4*facing_104<0)word_732=180;
    }
    if(sequence_index_13e==5 || sequence_index_13e==6)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e>0 && sequence_index_13e<5){
        ++word_736;word_734=static_cast<short>(word_732-static_cast<int>(field_740));
        if(word_734>180)word_734-=360;if(word_734<-180)word_734+=360;
        if(word_734>0){if(!field_4b8)field_740=static_cast<float>(field_740+1.5);else field_740=static_cast<float>(field_740+0.5);}
        if(word_734<0){if(!field_4b8)field_740=static_cast<float>(field_740-1.5);else field_740=static_cast<float>(field_740-0.5);}
        velocity_x_f4=static_cast<float>(komachi_cosine(field_740)*field_73c);
        velocity_y_f8=static_cast<float>(komachi_sine(field_740)*field_73c);
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
                   static_cast<float>(komachi_cosine(field_740)*100.0*facing_104+x_ec),
                   static_cast<float>(komachi_sine(field_740)*100.0+y_f0+100.0),
                   static_cast<unsigned char>(facing_104),1);
        }
        if((!field_6c8 && word_736>10) || word_482<=0){
            if((!field_6c8 && word_736>10) || word_482<=0){
                reset_action_scratch();
                if(sequence_index_13e==1 || sequence_index_13e==2){
                    unsigned char direction=ufacing();double x=x_ec;
                    if(direction==1){if(peer()->x_ec<x){facing_104=-1;velocity_x_f4=-velocity_x_f4;select_sequence(6);}else select_sequence(5);}
                    else if(peer()->x_ec>x){facing_104=static_cast<signed char>(-direction);velocity_x_f4=-velocity_x_f4;select_sequence(6);}
                    else select_sequence(5);
                }
                if(sequence_index_13e==3 || sequence_index_13e==4){
                    unsigned char direction=ufacing();double x=x_ec;
                    if(direction==1){if(peer()->x_ec<x){facing_104=-1;velocity_x_f4=-velocity_x_f4;select_sequence(5);}else select_sequence(6);}
                    else if(peer()->x_ec>x){facing_104=static_cast<signed char>(-direction);velocity_x_f4=-velocity_x_f4;select_sequence(5);}
                    else select_sequence(6);
                }
                return;
            }
        }
    }
    if(static_cast<unsigned char>(crossed())){y_f0=komachi_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;
        if(sequence_index_13e<5){reset_action_scratch();set_action_and_finalize(215);}
        else{set_action_and_finalize(10);zero_motion();}}
    return;


case 215:
    landing();if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:high_jump(0.0f,20.0f,0.65f,true,true);return;
case 221:high_jump(8.0f,16.0f,0.6f,true,true);return;
case 222:high_jump(-8.0f,16.0f,0.6f,true,true);return;
case 223:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1){if(!(time_counter_144%5))dash_dust(false);++word_730;if((field_6b4*facing()<=0 && word_730>15) || word_730>45){set_action_and_finalize(204);return;}}
    if(entry(1)){velocity_x_f4=5.0f;dash_effects(false,80.0,true);}return;
case 224:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!komachi_on_surface(this) && !(time_counter_144%5))dash_dust(true);
    if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;y_f0=komachi_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if(entry(1) && !word_730){word_730=1;velocity_x_f4=-10.0f;velocity_y_f8=4.0f;acceleration_y_100=0.4f;dash_effects(true,80.0,false);}return;
case 225:
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=komachi_surface(this);set_action_and_finalize(10);return;}}
    if(sequence_index_13e>=2 && !(time_counter_144%5))dash_dust(true);if(advance())set_action_and_finalize(9);
    if(entry(1)){velocity_x_f4=-11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(true,120.0,false);}if(entry(3))flip();return;
case 226:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=komachi_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e==1 && !(time_counter_144%5))dash_dust(false);if(advance())set_action_and_finalize(9);
    if(entry(1)){velocity_x_f4=11.0f;velocity_y_f8=-1.0f;acceleration_y_100=0.5f;dash_effects(false,110.0,true);}if(entry(3))flip();return;

case 300:
    landing();if(directional(0))return;if(byte_47e)decelerate(0.5,true);if(velocity_x_f4>0.0f)decelerate(0.5,false);
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==2){event(27);byte_47e=0;}return;
case 301:landing();if(!directional(0))normal301();return;
case 302:
    landing();if(directional(1))return;if(!field_6bc)byte_750=0;
    if(advance()){set_action_and_finalize(0);return;}if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==4 && byte_750){charge(246,90.0);return;}if(!frame_timer_142 && frame_index_140==1){event(29);velocity_x_f4=20.0f;}if(frame_index_140>=2)decelerate(5.0,false);}
    if(sequence_index_13e==1){if(!frame_timer_142 && frame_index_140==1)ring817();decelerate(5.0,false);}return;
case 303:
    landing();if(directional(0))return;if(byte_47e>0)decelerate(static_cast<double>(0.6f),true);if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==2)event(27);return;
case 304:
    landing();if(directional(1))return;if(!field_6bc)byte_750=0;if(byte_47e)decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){if(byte_750){charge(-45,40.0);return;}event(29);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1)ring817();return;
case 305:
    landing();if(directional(1))return;if(frame_index_140>=2)decelerate(0.75,false);if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==2)event(28);return;
case 306:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(advance())set_action_and_finalize(9);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)event(28);return;
case 307:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(advance())set_action_and_finalize(9);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)event(29);return;
case 308:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(advance())set_action_and_finalize(9);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5)event(29);return;
case 309:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=komachi_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==5){if(velocity_y_f8<8.0f)velocity_y_f8=8.0f;acceleration_y_100=0.5f;}if(!frame_timer_142 && frame_index_140==6)event(29);}return;
case 310:
    if(!sequence_index_13e){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;y_f0=komachi_surface(this);next_sequence_block();return;}}
    if(sequence_index_13e==1){landing();decelerate(0.5,false);}if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)event(29);return;
case 320:
    landing();if(directional(0))return;if(frame_index_140>=7)velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3)velocity_x_f4=10.0f;if(!frame_timer_142){if(frame_index_140==5){event(28);byte_47e=0;}if(!frame_timer_142 && frame_index_140==7)velocity_x_f4=static_cast<float>(velocity_x_f4*0.25);}}return;
case 321:
    landing();if(directional(1))return;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)event(29);return;
case 322:
    landing();if(directional(1))return;if(byte_47e)decelerate(0.5,true);if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==8){event(29);velocity_x_f4=15.0f;}if(!frame_timer_142 && frame_index_140==10)velocity_x_f4=0.0f;}return;


case 400:ground800(false,-20.0f,10.0f);return;
case 401:ground800(true,-40.0f,-20.0f);return;
case 402:
    landing();if(!field_6c0)byte_750=0;
    if(word_730==1 && !sequence_index_13e)stream800(8,20.0,-5,160.0,false,false);
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)start800(-80.0f,-45.0f,false);return;
case 404:
    if(sequence_index_13e==2)landing();if(!field_6c0)byte_750=0;velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);byte_47f=0;y_f0=komachi_surface(this);zero_motion();return;}
    if(word_730==1){if(!sequence_index_13e)stream800(6,15.0,105,162.0,false,false);if(sequence_index_13e==1)stream800(10,25.0,105,162.0,false,false);}
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3 && byte_750==1){charge(-20,145.0);return;}
        if(!frame_timer_142 && frame_index_140==8)start800(-30.0f,10.0f,false);
        if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==6)start800(-30.0f,10.0f,false);if(!frame_timer_142 && frame_index_140==10)acceleration_y_100=0.5f;}return;
case 405:
    if(sequence_index_13e==2)landing();if(!field_6c0)byte_750=0;velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e<2){if(static_cast<unsigned char>(crossed())){select_sequence(2);byte_47f=0;y_f0=komachi_surface(this);zero_motion();return;}}
    if(word_730==1 && !sequence_index_13e)stream800(10,0.0,100,160.0,false,true);
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==6){phase_counter(30);field_744=0.0f;word_730=1;counter(200,45);}if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.5f;}return;
case 406:
    if(sequence_index_13e==2)landing();if(!field_6c0)byte_750=0;velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);acceleration_y_100=0.0f;byte_47f=0;y_f0=komachi_surface(this);zero_motion();return;}
    if(word_730==1){if(!sequence_index_13e)stream800(6,15.0,75,110.0,false,false);if(sequence_index_13e==1)stream800(10,25.0,75,110.0,false,false);}
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==3 && byte_750==1){charge(-20,190.0);return;}if(!frame_timer_142 && frame_index_140==6)start800(20.0f,50.0f,true);if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;}
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==3)start800(20.0f,40.0f,true);if(!frame_timer_142 && frame_index_140==7)acceleration_y_100=0.5f;}return;
case 408:landing();decelerate(0.5,false);if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)event(29);return;
case 409:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();y_f0=komachi_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){phase_counter(50);counter(200,60);dispatch_character_wave_handle(1);aim(-40.0f,40.0f);float p[3]={field_744,3.0f,0.0f};spawn_offset(801,87,184.0,p,3);}return;

case 411:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==7 && byte_750){charge(-100,164.0);return;}if(!frame_timer_142 && frame_index_140==10)fan801(10.0,7.0,24.0f,35.0,120.0,false,-10.0f,10.0f);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4)fan801(10.0,7.0,24.0f,35.0,120.0,true,-10.0f,10.0f);return;
case 412:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==13){
        phase_counter(50);field_7a8=10;counter(200,60);dispatch_character_wave_handle(15);
        float p[3]={0.0f,85.0f,4.0f};spawn(801,static_cast<float>(84*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);
        p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(80)))-40.0);p[1]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(80)))-40.0);spawn(801,static_cast<float>(84*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);
        p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(80)))-40.0);p[1]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(80)))-40.0);spawn(801,static_cast<float>(84*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);
    }return;
case 414:
    if(sequence_index_13e==2)landing();velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);byte_47f=0;y_f0=komachi_surface(this);zero_motion();return;}
    if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==5){phase_counter(50);counter(200,60);dispatch_character_wave_handle(1);aim(-40.0f,40.0f);float p[3]={field_744,3.0f,0.0f};spawn_offset(801,65,175.0,p,3);}
        if(!frame_timer_142 && frame_index_140==10)acceleration_y_100=0.5f;
    }return;
case 415:
    if(sequence_index_13e==2)landing();velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);byte_47f=0;y_f0=komachi_surface(this);zero_motion();return;}
    if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(9);if(entry(2))set_action_and_finalize(9);
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2 && byte_750){charge(-70,170.0);return;}if(!frame_timer_142 && frame_index_140==4)fan801(15.0,10.0,24.0f,0.0,140.0,false,-10.0f,10.0f);if(!frame_timer_142 && frame_index_140==9)acceleration_y_100=0.5f;}
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==3)fan801(15.0,10.0,24.0f,0.0,140.0,true,-10.0f,10.0f);if(!frame_timer_142 && frame_index_140==8)acceleration_y_100=0.5f;}return;
case 416:
    if(sequence_index_13e==2)landing();velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e<2 && static_cast<unsigned char>(crossed())){select_sequence(2);byte_47f=0;y_f0=komachi_surface(this);zero_motion();return;}
    if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(9);if(entry(2))set_action_and_finalize(9);
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==4 && byte_750){charge(-104,224.0);return;}if(!frame_timer_142 && frame_index_140==7){velocity_x_f4=-5.0f;velocity_y_f8=7.5f;acceleration_y_100=0.5f;fan801(10.0,5.0,16.0f,0.0,100.0,false,40.0f,70.0f);}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4){velocity_x_f4=-5.0f;velocity_y_f8=7.5f;acceleration_y_100=0.5f;fan801(10.0,5.0,16.0f,0.0,100.0,true,40.0f,70.0f);}return;
case 418:
    landing();decelerate(0.5,false);if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==8){event(29);byte_47e=0;}return;


case 500:
    landing();field_17c=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10){float p[3]={0.0f,10.0f,0.0f};spawn(810,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);skill_cost(10);}return;
case 501:
    landing();field_17c=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10){float p[3]={0.0f,20.0f,0.0f};spawn(810,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);skill_cost(10);}return;
case 505:ground811(0.0f,3.0f);return;
case 506:ground811(2.0f,5.0f);return;
case 507:
    if(sequence_index_13e==2)landing();
    if(sequence_index_13e<=1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=komachi_surface(this);zero_motion();return;}}
    field_17c=4;if(advance())set_action_and_finalize(0);if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==7)shot811(0.0f,3.0f);if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.25f;}return;
case 508:
    if(sequence_index_13e==2)landing();
    if(sequence_index_13e<=1){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=komachi_surface(this);zero_motion();return;}}
    field_17c=4;if(advance())set_action_and_finalize(0);if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==6)shot811(1.0f,4.0f);if(!frame_timer_142 && frame_index_140==11)acceleration_y_100=0.25f;}return;
case 510:
    landing();field_17c=8;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10){
        float p[3]={0.0f,10.0f,0.0f};if(byte_60c>=4)p[2]=2.0f;
        if(facing_104==1)spawn(812,static_cast<float>(komachi_boundary_6fbd24+100.0),y_f0,-1,1,p,3);
        else spawn(812,static_cast<float>(komachi_boundary_6fbd1c-100.0),y_f0,static_cast<signed char>(-facing_104),1,p,3);
        skill_cost(10);
    }return;
case 511:
    landing();field_17c=8;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10){
        float p[3]={0.0f,10.0f,0.0f};if(byte_60c>=4)p[2]=2.0f;
        if(facing_104==-1)spawn(812,static_cast<float>(komachi_boundary_6fbd24+100.0),y_f0,-1,1,p,3);
        else spawn(812,static_cast<float>(komachi_boundary_6fbd1c-100.0),y_f0,facing_104,1,p,3);
        skill_cost(10);
    }return;
case 520:stream815(20.0);return;
case 521:stream815(25.0);return;
case 525:
    landing();field_17c=5;
    if(sequence_index_13e==1 && sweep817(1.0f,10.0,40))return;
    if(sequence_index_13e==3 && sweep817(1.5f,20.0,40))return;
    if(advance())set_action_and_finalize(0);if(entry(3)){set_action_and_finalize(0);return;}
    if(entry(1)){sweep_entry();if(byte_609>=4)select_sequence(3);}return;
case 526:
    landing();field_17c=5;decelerate(0.25,false);
    if(sequence_index_13e==1 && sweep817(1.0f,10.0,65))return;
    if(sequence_index_13e==3 && sweep817(1.5f,20.0,65))return;
    if(advance())set_action_and_finalize(0);if(entry(3)){set_action_and_finalize(0);return;}
    if(entry(1)){sweep_entry();if(byte_609>=4){select_sequence(3);return;}}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5)velocity_x_f4=10.0f;return;
case 540:{
    field_17c=2;if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(9);
    if(entry(2)){
        if(peer()->action_id_13c<=599){
            float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,0,100.0,p,3);
            p[1]=1.0f;spawn(820,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            p[1]=0.0f;p[2]=2.0f;spawn_offset(820,0,100.0,p,3);
            p[1]=1.0f;spawn(820,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            if(byte_606!=4){peer()->word_4a8=15;peer()->word_4ac=15;}
            if(komachi_on_surface(this)){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(p[0]>=0.0f && p[0]<=180.0f)spawn(817,x_ec,y_f0,facing_104,1,p,3);
                    else spawn(817,x_ec,y_f0,facing_104,-1,p,3);}
            }
            if(komachi_on_surface(peer())){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,peer()->x_ec,peer()->y_f0,facing_104,-1,p,3);
                    else spawn(817,peer()->x_ec,peer()->y_f0,facing_104,1,p,3);}
            }
            field_73c=x_ec;field_740=y_f0;x_ec=peer()->x_ec;y_f0=peer()->y_f0;peer()->x_ec=field_73c;peer()->y_f0=field_740;
        }
        dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);word_738=1;
    }
    if(entry(3) && !komachi_on_surface(this)){select_sequence(4);return;}
    if(entry(4)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,0.0f};spawn(820,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);p[1]=1.0f;spawn(820,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);}
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)acceleration_y_100=0.5f;return;}
case 541:{
    field_17c=2;if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(9);
    if(entry(2)){
        if(peer()->action_id_13c<=599){
            float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,0,100.0,p,3);
            p[1]=1.0f;spawn(820,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            p[1]=0.0f;p[2]=2.0f;spawn_offset(820,0,100.0,p,3);
            p[1]=1.0f;spawn(820,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            if(komachi_on_surface(this)){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(p[0]>=0.0f && p[0]<=180.0f)spawn(817,x_ec,y_f0,facing_104,1,p,3);
                    else spawn(817,x_ec,y_f0,facing_104,-1,p,3);}
            }
            if(komachi_on_surface(peer())){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,peer()->x_ec,peer()->y_f0,facing_104,-1,p,3);
                    else spawn(817,peer()->x_ec,peer()->y_f0,facing_104,1,p,3);}
            }
            if(byte_606==4){
                float ring[3]={0.0f,0.0f,4.0f};
                for(float n=0.0f;n<6.0f;n=static_cast<float>(n+1.0)){
                    float angle=static_cast<float>(-n*60.0);
                    spawn(820,
                          static_cast<float>(komachi_cosine(angle)*200.0*facing_104+x_ec),
                          static_cast<float>(komachi_sine(angle)*200.0+(static_cast<double>(y_f0)+100.0)),
                          static_cast<unsigned char>(facing_104),1,ring,3);
                }
            }else{peer()->word_4a8=15;peer()->word_4ac=15;}
            field_73c=x_ec;field_740=y_f0;x_ec=peer()->x_ec;y_f0=peer()->y_f0;peer()->x_ec=field_73c;peer()->y_f0=field_740;
        }
        dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);word_738=1;
    }
    if(entry(3) && !komachi_on_surface(this)){select_sequence(4);return;}
    if(entry(4)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,0.0f};spawn(820,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);p[1]=1.0f;spawn(820,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);}
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)acceleration_y_100=0.5f;return;}
case 542:{
    field_17c=2;if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(9);
    if(entry(2)){
        if(peer()->action_id_13c<=599){
            float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,0,100.0,p,3);
            p[1]=1.0f;spawn(820,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            p[1]=0.0f;p[2]=2.0f;spawn_offset(820,0,100.0,p,3);
            p[1]=1.0f;spawn(820,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            if(komachi_on_surface(this)){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(p[0]>=0.0f && p[0]<=180.0f)spawn(817,x_ec,y_f0,facing_104,1,p,3);
                    else spawn(817,x_ec,y_f0,facing_104,-1,p,3);}
            }
            if(komachi_on_surface(peer())){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,peer()->x_ec,peer()->y_f0,facing_104,-1,p,3);
                    else spawn(817,peer()->x_ec,peer()->y_f0,facing_104,1,p,3);}
            }
            if(byte_60a!=4){peer()->word_4a8=15;peer()->word_4ac=15;}
            field_73c=x_ec;field_740=y_f0;x_ec=peer()->x_ec;y_f0=peer()->y_f0;peer()->x_ec=field_73c;peer()->y_f0=field_740;
        }
        dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);word_738=1;
    }
    if(entry(3) && !komachi_on_surface(this)){select_sequence(4);return;}
    if(entry(4)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,0.0f};spawn(820,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);p[1]=1.0f;spawn(820,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);}
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)acceleration_y_100=0.5f;return;}
case 543:{
    field_17c=2;if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(9);
    if(entry(2)){
        if(peer()->action_id_13c<=599){
            float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,0,100.0,p,3);
            p[1]=1.0f;spawn(820,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            p[1]=0.0f;p[2]=2.0f;spawn_offset(820,0,100.0,p,3);
            p[1]=1.0f;spawn(820,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            if(komachi_on_surface(this)){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(p[0]>=0.0f && p[0]<=180.0f)spawn(817,x_ec,y_f0,facing_104,1,p,3);
                    else spawn(817,x_ec,y_f0,facing_104,-1,p,3);}
            }
            if(komachi_on_surface(peer())){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,peer()->x_ec,peer()->y_f0,facing_104,-1,p,3);
                    else spawn(817,peer()->x_ec,peer()->y_f0,facing_104,1,p,3);}
            }
            if(byte_606==4){
                float ring[3]={0.0f,0.0f,4.0f};
                for(float n=0.0f;n<6.0f;n=static_cast<float>(n+1.0)){
                    float angle=static_cast<float>(-n*60.0);
                    spawn(820,
                          static_cast<float>(komachi_cosine(angle)*200.0*facing_104+x_ec),
                          static_cast<float>(komachi_sine(angle)*200.0+(static_cast<double>(y_f0)+100.0)),
                          static_cast<unsigned char>(facing_104),1,ring,3);
                }
            }else{peer()->word_4a8=15;peer()->word_4ac=15;}
            field_73c=x_ec;field_740=y_f0;x_ec=peer()->x_ec;y_f0=peer()->y_f0;peer()->x_ec=field_73c;peer()->y_f0=field_740;
        }
        dispatch_character_wave_handle(13);counter(200,120);phase_counter(50);word_738=1;
    }
    if(entry(3) && !komachi_on_surface(this)){select_sequence(4);return;}
    if(entry(4)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,0.0f};spawn(820,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);p[1]=1.0f;spawn(820,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);}
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)acceleration_y_100=0.5f;return;}
case 545:ground821(field_6c0);return;
case 546:ground821(field_6c4);return;
case 550:movement822(field_6c0,field_6c4,false);return;
case 551:movement822(field_6c4,field_6c0,true);return;

case 560:ground825(field_6c0);return;
case 561:ground825(field_6c4);return;
case 562:{
    if(sequence_index_13e==5)landing();field_17c=3;velocity_y_f8-=acceleration_y_100;double y=velocity_y_f8+static_cast<double>(y_f0);
    if(komachi_surface(this)>=y && velocity_y_f8<0.0f && sequence_index_13e<5){select_sequence(5);acceleration_y_100=0.0f;byte_47f=0;y_f0=komachi_surface(this);zero_motion();return;}
    if(sequence_index_13e<2 && !field_6c4)byte_750=0;
    if(word_730>0 && (sequence_index_13e==2 || sequence_index_13e==3)){
        if(word_730%4==1){phase_counter(10);field_180=1;aim_short();dispatch_character_wave_handle(9);if(word_738==1)burst808();else burst808();}++word_730;
    }
    if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>4 && (!byte_750||time_counter_144>25))next_sequence_block();
    if(entry(1)){if(byte_750==1){int direction=ufacing();effect(62,static_cast<float>(x_ec-23*static_cast<signed char>(direction)),static_cast<float>(y_f0+107.0),static_cast<unsigned char>(direction),1);}
        float p[3]={0.0f,0.0f,4.0f};spawn_offset(808,-23,107.0,p,3);}
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){word_730=1;counter(200,120);}
    if(sequence_index_13e==3 && ((time_counter_144>10 && !byte_750)||time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;return;}
case 565:ground827(field_6c0);return;
case 566:ground827(field_6c4);return;
case 567:{
    if(sequence_index_13e==5)landing();field_17c=7;velocity_y_f8-=acceleration_y_100;double y=velocity_y_f8+static_cast<double>(y_f0);
    if(komachi_surface(this)>=y && velocity_y_f8<0.0f && sequence_index_13e<5){select_sequence(5);acceleration_y_100=0.0f;byte_47f=0;y_f0=komachi_surface(this);zero_motion();return;}
    if(sequence_index_13e<2 && !field_6c4)byte_750=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){aim_short();dispatch_character_wave_handle(29);field_180=1;counter(200,60);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};if(word_738==1)spawn_offset(824,48,104.0,p,3);else spawn_offset(824,48,104.0,p,3);}
    if(advance())set_action_and_finalize(0);if(entry(1)){float p[3]={0.0f,0.0f,4.0f};spawn_offset(824,-48,104.0,p,3);}
    if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>10 && (!byte_750||time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;return;}

case 599:
    if(word_730>0 && frame_index_140<7 && word_730<12){
        word_734=static_cast<short>(komachi_random_u32()%35u);
        float p[3]={static_cast<float>(-20-word_734),static_cast<float>(static_cast<short>(komachi_random_u32()%5u+10)),0.0f};
        spawn(807,static_cast<float>(20*facing()*(word_730+1)+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);
        p[0]=static_cast<float>(komachi_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        spawn(801,static_cast<float>(20*facing()*(word_730+1)+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);
        if(word_730==1){dispatch_character_wave_handle(0);counter(200,120);}++word_730;
    }
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)word_730=1;return;

case 600:
    if((!sequence_index_13e && frame_index_140>=10) || sequence_index_13e==1 || sequence_index_13e==4)landing();texture(4,2);
    if(sequence_index_13e==1){
        velocity_x_f4=field_fc+velocity_x_f4;if(velocity_x_f4>25.0f)velocity_x_f4=17.5f;
        if(field_180 && ++word_730>=10){word_730=0;byte_184=1;field_180=0;}
        if(!(time_counter_144%2))spell_ground_particles(850,90,-45.0,5.0,1.0f);
        if(time_counter_144>=50){byte_184=1;field_180=0;next_sequence_block();return;}
    }
    if(sequence_index_13e==2 && frame_index_140<=1){decelerate(1.0,false);spell_ground_particles(850,60,-10.0,10.0,1.0f);}
    if(sequence_index_13e==3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=komachi_surface(this);next_sequence_block();return;}}
    if(advance()){set_action_and_finalize(0);zero_motion();return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,100.0,1);if(!frame_timer_142 && frame_index_140==11){velocity_x_f4=5.0f;field_fc=1.0f;dispatch_character_wave_handle(50);}}
    if(entry(3)){velocity_x_f4=-10.0f;velocity_y_f8=8.0f;acceleration_y_100=0.75f;}return;
case 601:
    texture(4,2);landing();if(!sequence_index_13e && field_180==1){grab_peer();return;}
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(-117,114.0,5);if(!frame_timer_142 && frame_index_140==7){float p[3];ring817_at(p,120);}}
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3)dispatch_character_wave_handle(51);
        if(!frame_timer_142 && frame_index_140==14){field_73c=static_cast<float>(peer()->word_174*0.5);if(field_73c<=1.0f)field_73c=0.0f;
            forward_hit_quantity(static_cast<int>(field_73c),850,1,0);peer()->field_18c=24.0f;peer()->field_190=15.0f;peer()->set_action_and_finalize(74);
            dispatch_character_wave_handle(52);layout(10.0f);float p[3];ring817_at(p,120);}
    }return;
case 602:
    texture(4,2);landing();
    if(word_730==1 && !sequence_index_13e){if(!(word_732%5)){field_180=1;aim(-10.0f,10.0f);dispatch_character_wave_handle(14);
        if(word_734<5){float p[3]={static_cast<float>(field_744-static_cast<double>(word_734)*18.0+25.0),7.0f,0.0f};spawn_offset(852,90,180.0,p,3);++word_734;}}++word_732;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,140.0,1);if(!frame_timer_142 && frame_index_140==4)word_730=1;}return;
case 603:
    if((!sequence_index_13e && frame_index_140>=10) || sequence_index_13e==1 || sequence_index_13e==4)landing();texture(4,2);
    if(sequence_index_13e==1){
        velocity_x_f4=static_cast<float>(velocity_x_f4+static_cast<double>(0.1f));if(velocity_x_f4>4.0f)velocity_x_f4=3.0f;
        if(!(time_counter_144%2))spell_ground_particles(853,90,-45.0,5.0,3.0f);
        if(!(time_counter_144%4) && time_counter_144<=120){float p[3]={static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(12)))+6.0),static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(8)))+2.0),0.0f};
            if(facing_104==1)spawn(853,static_cast<float>(komachi_boundary_6fbd1c-50.0),static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(300)))+(static_cast<double>(y_f0)+20.0)),1,1,p,3);
            else spawn(853,static_cast<float>(komachi_boundary_6fbd24+50.0),static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(300)))+(static_cast<double>(y_f0)+20.0)),facing_104,1,p,3);}
        if(time_counter_144>=150){next_sequence_block();return;}
    }
    if(sequence_index_13e==2 && frame_index_140<=1){decelerate(static_cast<double>(0.1f),false);spell_ground_particles(853,60,-10.0,10.0,3.0f);}
    if(sequence_index_13e==3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=komachi_surface(this);next_sequence_block();return;}}
    if(advance()){set_action_and_finalize(0);zero_motion();}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2)spell_flash(0,100.0,3);
    if(entry(3)){velocity_x_f4=-3.0f;velocity_y_f8=8.0f;acceleration_y_100=0.75f;}return;
case 604:
    texture(4,2);landing();if(!sequence_index_13e && field_180==1){grab_peer();return;}
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(-117,114.0,5);if(!frame_timer_142 && frame_index_140==6){float p[3];ring817_at(p,120);}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3)dispatch_character_wave_handle(51);
    if(sequence_index_13e==2){
        if(!time_counter_144 && !frame_timer_142 && !frame_index_140){
            float p[3];
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*45.0);p[1]=0.0f;p[2]=0.0f;spawn_offset(854,0,100.0,p,3);}
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(n*45.0);p[1]=0.0f;p[2]=1.0f;spawn(854,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);}dispatch_character_wave_handle(55);
        }
        if(word_730==1){
            KomachiActionStateView *other=peer();field_73c=static_cast<float>(other->word_174);field_740=static_cast<float>(word_174);other->word_174=static_cast<short>(static_cast<int>(field_740));word_174=static_cast<short>(static_cast<int>(field_73c));
            layout(3.0f);float p[3];ring817_at(p,120);
            p[0]=0.0f;p[1]=0.0f;p[2]=5.0f;spawn(854,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            for(int n=6;n;--n){p[0]=static_cast<float>(komachi_random(360));p[1]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(75)))*static_cast<double>(0.1f)+10.0);p[2]=4.0f;spawn(854,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);}
            p[0]=0.0f;p[1]=0.0f;p[2]=5.0f;spawn_offset(854,0,100.0,p,3);
            for(int n=6;n;--n){p[0]=static_cast<float>(komachi_random(360));p[1]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(75)))*static_cast<double>(0.1f)+10.0);p[2]=4.0f;spawn(854,x_ec,y_f0,ufacing(),1,p,3);}
            dispatch_character_wave_handle(56);word_730=2;word_732=0;
        }
        if(word_730==2 && ++word_732>=30){peer()->field_18c=5.0f;peer()->field_190=10.0f;peer()->set_action_and_finalize(71);next_sequence_block();}
    }return;
case 605:
    texture(4,2);landing();
    if(word_730==1 && !sequence_index_13e){if(!(word_732%5)){dispatch_character_wave_handle(14);if(word_734<6){float p[3]={static_cast<float>(15.0-static_cast<double>(word_734)*60.0),7.0f,0.0f};spawn_offset(855,90,180.0,p,3);++word_734;}}++word_732;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==2)spell_flash(0,140.0,3);if(!frame_timer_142 && frame_index_140==4)word_730=1;}return;
case 606:
    texture(4,2);landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==7)spell_flash(-102,164.0,4);if(!frame_timer_142 && frame_index_140==10){float p[3]={0.0f,-80.0f,0.0f};spawn(856,peer()->x_ec,1000.0f,ufacing(),1,p,3);dispatch_character_wave_handle(53);}}return;
case 611:
    texture(4,2);landing();if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==5)spell_flash(-97,122.0,3);if(!frame_timer_142 && frame_index_140==10){float p[3]={0.0f,10.0f,0.0f};spawn(861,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);
        p[2]=4.0f;spawn(861,static_cast<float>(200*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),-1,p,3);dispatch_character_wave_handle(10);}}return;


case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){event(55);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),ufacing(),1);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),ufacing(),1);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),ufacing(),1);
        effect(141,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1);effect(142,x_ec,y_f0,ufacing(),-1);}return;
case 696:landing();normal301();return;
case 710:
    if(sequence_index_13e==1){
        if(time_counter_144>=120)next_sequence_block();
        if(!(time_counter_144%word_736)){
            dispatch_character_wave_handle(1);float p[3]={0.0f,static_cast<float>(static_cast<double>(word_730)+word_730),0.0f};
            field_744=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(150)))+50.0);
            double x_offset=komachi_cosine(static_cast<float>(komachi_random(360)))*field_744;
            field_73c=static_cast<float>(x_offset+peer()->x_ec);
            if(field_73c<-50.0f)field_73c=-50.0f;
            if(field_740<-150.0f)field_740=-150.0f;
            double y_offset=komachi_sine(static_cast<float>(komachi_random(360)))*field_744;
            field_740=static_cast<float>(y_offset+peer()->y_f0);
            spawn(900,field_73c,field_740,ufacing(),1,p,3);++word_730;
        }
    }
    if(advance())set_action_and_finalize(700);
    if(entry(1)){switch(g_match_identifier){case 3:case 2:word_736=10;break;case 1:word_736=15;break;case 0:word_736=20;break;}}return;
case 711:
    if(word_730>0)++word_732;if(advance())set_action_and_finalize(700);
    if(!frame_timer_142 && frame_index_140==10){dispatch_character_wave_handle(18);word_730=1;float p[3];ring817_at(p,112);
        p[2]=6.0f;spawn(900,static_cast<float>(112*facing()+static_cast<double>(x_ec)),y_f0,ufacing(),1,p,3);}return;
case 720:
    if(sequence_index_13e==1 && time_counter_144>=120)next_sequence_block();if(advance())set_action_and_finalize(700);
    if(entry(1)){
        dispatch_character_wave_handle(19);float p[3];
        for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
            if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,x_ec,y_f0,ufacing(),-1,p,3);else spawn(817,x_ec,y_f0,ufacing(),1,p,3);}
        p[0]=0.0f;p[1]=10.0f;p[2]=0.0f;spawn(901,peer()->x_ec,y_f0,ufacing(),1,p,3);
        p[2]=4.0f;spawn(901,peer()->x_ec,y_f0,ufacing(),-1,p,3);
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==3){
        float p[3];
        switch(g_match_identifier){
        case 3:p[0]=0.0f;p[1]=-80.0f;p[2]=13.0f;spawn(901,peer()->x_ec,1000.0f,facing_104,1,p,3);break;
        case 2:p[0]=0.0f;p[1]=-70.0f;p[2]=12.0f;spawn(901,peer()->x_ec,1000.0f,facing_104,1,p,3);break;
        case 1:p[0]=0.0f;p[1]=-60.0f;p[2]=11.0f;spawn(901,peer()->x_ec,1000.0f,facing_104,1,p,3);break;
        case 0:p[0]=0.0f;p[1]=-50.0f;p[2]=10.0f;spawn(901,peer()->x_ec,1000.0f,facing_104,1,p,3);break;
        }
        dispatch_character_wave_handle(53);
    }return;
case 730:
    if (sequence_index_13e == 1 && time_counter_144 >= 120)
        next_sequence_block();
    if (advance())
        set_action_and_finalize(700);
    if (entry(1)) {
        dispatch_character_wave_handle(12);
        float base_angle = static_cast<float>(komachi_random(360));
        float jitter = static_cast<float>(
            static_cast<double>(static_cast<float>(komachi_random(20))) - 10.0);
        float coord;
        float packet[3];
        switch (g_match_identifier) {
        case 3:
            for (float n = 0.0f; n < 8.0f; n = static_cast<float>(n + 1.0)) {
                coord = static_cast<float>(n * 45.0 + base_angle);
                packet[0] = static_cast<float>(n * 45.0 + base_angle + jitter + 180.0);
                packet[1] = 6.0f;
                packet[2] = 0.0f;
                spawn(902,
                      komachi_cosine(-coord) * 500.0 * facing_104 + fighter_170->x_ec,
                      komachi_sine(-coord) * 500.0 + fighter_170->y_f0 + 100.0,
                      static_cast<unsigned char>(facing_104), 1, packet, 3);
            }
            for (float n = 0.0f; n < 8.0f; n = static_cast<float>(n + 1.0)) {
                double angle = n * 45.0 + base_angle + 22.5;
                coord = static_cast<float>(angle + 180.0);
                packet[0] = static_cast<float>(angle + jitter);
                packet[1] = 4.0f;
                packet[2] = 0.0f;
                spawn(902,
                      komachi_cosine(-coord) * 500.0 * facing_104 + fighter_170->x_ec,
                      komachi_sine(-coord) * 500.0 + fighter_170->y_f0 + 100.0,
                      static_cast<unsigned char>(facing_104), 1, packet, 3);
            }
            break;
        case 2:
            for (float n = 0.0f; n < 12.0f; n = static_cast<float>(n + 1.0)) {
                double angle = n * 30.0 + base_angle;
                coord = static_cast<float>(angle + 180.0);
                packet[0] = static_cast<float>(angle + jitter);
                packet[1] = 5.0f;
                packet[2] = 0.0f;
                spawn(902,
                      komachi_cosine(-coord) * 500.0 * facing_104 + fighter_170->x_ec,
                      komachi_sine(-coord) * 500.0 + fighter_170->y_f0 + 100.0,
                      static_cast<unsigned char>(facing_104), 1, packet, 3);
            }
            break;
        case 1:
            for (float n = 0.0f; n < 8.0f; n = static_cast<float>(n + 1.0)) {
                double angle = n * 45.0 + base_angle;
                coord = static_cast<float>(angle + 180.0);
                packet[0] = static_cast<float>(angle + jitter);
                packet[1] = 5.0f;
                packet[2] = 0.0f;
                spawn(902,
                      komachi_cosine(-coord) * 500.0 * facing_104 + fighter_170->x_ec,
                      komachi_sine(-coord) * 500.0 + fighter_170->y_f0 + 100.0,
                      static_cast<unsigned char>(facing_104), 1, packet, 3);
            }
            break;
        case 0:
            for (float n = 0.0f; n < 6.0f; n = static_cast<float>(n + 1.0)) {
                double angle = n * 60.0 + base_angle;
                coord = static_cast<float>(angle + 180.0);
                packet[0] = static_cast<float>(angle + jitter);
                packet[1] = 5.0f;
                packet[2] = 0.0f;
                spawn(902,
                      komachi_cosine(-coord) * 500.0 * facing_104 + fighter_170->x_ec,
                      komachi_sine(-coord) * 500.0 + fighter_170->y_f0 + 100.0,
                      static_cast<unsigned char>(facing_104), 1, packet, 3);
            }
            break;
        }
    }
    return;
case 732:
    if(sequence_index_13e==3)landing();if(advance())set_action_and_finalize(704);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,0.0f};spawn(930,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);
        p[1]=1.0f;spawn(930,x_ec,static_cast<float>(y_f0+100.0),ufacing(),-1,p,3);}
    if(entry(2)){
        if(peer()->action_id_13c<=599){
            float p[3]={0.0f,0.0f,1.0f};spawn_offset(930,0,100.0,p,3);
            p[1]=1.0f;spawn(930,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            p[1]=0.0f;p[2]=2.0f;spawn_offset(930,0,100.0,p,3);
            p[1]=1.0f;spawn(930,peer()->x_ec,static_cast<float>(peer()->y_f0+100.0),ufacing(),1,p,3);
            if(komachi_on_surface(this)){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(p[0]>=0.0f && p[0]<=180.0f)spawn(817,x_ec,y_f0,facing_104,1,p,3);
                    else spawn(817,x_ec,y_f0,facing_104,-1,p,3);}
            }
            if(komachi_on_surface(peer())){
                for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(komachi_random(40)))+(static_cast<double>(angle)+30.0));p[1]=13.0f;p[2]=2.0f;
                    if(!(p[0]>=0.0f && p[0]<=180.0f))spawn(817,peer()->x_ec,peer()->y_f0,ufacing(),-1,p,3);
                    else spawn(817,peer()->x_ec,peer()->y_f0,ufacing(),1,p,3);}
            }
            field_73c=x_ec;field_740=y_f0;x_ec=peer()->x_ec;y_f0=peer()->y_f0;peer()->x_ec=field_73c;peer()->y_f0=field_740;
        }
        dispatch_character_wave_handle(13);word_738=1;
    }
    if(entry(3)){if(komachi_on_surface(this))set_action_and_finalize(700);else set_action_and_finalize(704);}
    if(entry(4)){set_action_and_finalize(700);return;}
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)acceleration_y_100=0.5f;return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8){byte_655=1;finalize(-1);texture(2,-1);copy_health();word_76c=0;word_76a=1;word_766=0;word_768=0;word_764=0;event(23);}return;
case 795:
    if(!sequence_index_13e){velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.3f));if(static_cast<unsigned char>(crossed())){select_sequence(1);event(30);y_f0=komachi_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:
    if(sequence_index_13e<=2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(3);event(30);y_f0=komachi_surface(this);velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;x_ec=480.0f;}if(x_ec>480.0f)x_ec=480.0f;}
    if(advance())set_action_and_finalize(0);return;
case 798:
    if(sequence_index_13e<=2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(3);event(30);y_f0=komachi_surface(this);velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;x_ec=800.0f;}if(x_ec<800.0f)x_ec=800.0f;}
    if(advance())set_action_and_finalize(700);return;

default:common_update();return;
}
advance();
}
}
