#include "characters/RemiliaActionState.hpp"
// Canonical exact JP 1.06a 0x00545090 Remilia Fighter +0x28 action-state root.
// See docs/REMILIA_ACTION_STATE_2026_10_28.md.
namespace th105 {
void RemiliaActionStateView::dispatch_action_state_vslot28() {
word_7a0=0;word_7a2=76;
if(action_id_13c>149 && action_id_13c<159 && !byte_751) {
    byte_751=1;
    if(action_id_13c>149 && action_id_13c<154)spawn_offset(998,35,95.0,0,0);
    if(action_id_13c>153 && action_id_13c<158)spawn_offset(998,55,55.0,0,0);
    if(action_id_13c==158)spawn_offset(998,85,90.0,0,0);
}
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
case 4:landing();velocity_x_f4=6.5f;break;
case 5:landing();velocity_x_f4=-6.5f;break;
case 6:normal_jump(0.0f,19.0f);return;
case 7:normal_jump(7.0f,18.0f);return;
case 8:normal_jump(-7.0f,18.0f);return;
case 9:
    if(acceleration_y_100==0.0f)acceleration_y_100=0.6f;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    break;
case 10:
    landing();zero_motion();if(advance()){if(!field_6b8){set_action_and_finalize(0);return;}set_action_and_finalize(2);}return;
case 197:recovery_jump(15.5f,8.0f);return;
case 198:recovery_jump(-15.5f,8.0f);return;
case 199:recovery_jump(0.0f,6.0f);return;
case 200:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==1 || sequence_index_13e==2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(3);y_f0=remilia_surface(this);return;}}
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4-2.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(advance()){velocity_x_f4=0.0f;set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
    if(entry(1)){byte_47e=0;velocity_x_f4=15.0f;velocity_y_f8=25.0f;acceleration_y_100=2.5f;dash_effects(false,80.0,true);}return;
case 201:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==1 || sequence_index_13e==2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(3);y_f0=remilia_surface(this);return;}}
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4+4.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance()){velocity_x_f4=0.0f;set_action_and_finalize(0);if(field_6b8>0)set_action_and_finalize(1);}
    if(entry(1)){velocity_x_f4=-22.0f;velocity_y_f8=40.0f;acceleration_y_100=6.0f;dash_effects(false,80.0,true);}return;
case 202:
    if(sequence_index_13e==2)velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=remilia_surface(this);set_action_and_finalize(10);return;}
    if(advance())set_action_and_finalize(9);
    if(entry(1)){velocity_x_f4=30.0f;velocity_y_f8=-4.0f;dash_effects(false,110.0,true);}if(entry(2))flip();
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){velocity_x_f4=10.0f;velocity_y_f8=-4.0f;acceleration_y_100=0.5f;}return;
case 203:
    if(sequence_index_13e==2)velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=remilia_surface(this);set_action_and_finalize(10);return;}
    if(advance())set_action_and_finalize(9);
    if(entry(1)){velocity_x_f4=-30.0f;velocity_y_f8=2.0f;dash_effects(false,110.0,true);}if(entry(2)){velocity_x_f4=-10.0f;velocity_y_f8=2.0f;acceleration_y_100=0.5f;flip();}return;
case 204:
    landing();velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}if(advance()){set_action_and_finalize(0);byte_47e=0;}return;
case 208:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(remilia_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=0.0f;velocity_y_f8=23.0f;acceleration_y_100=1.0f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 209:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(remilia_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=14.0f;velocity_y_f8=17.5f;acceleration_y_100=0.9f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 210:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(remilia_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=-14.0f;velocity_y_f8=17.5f;acceleration_y_100=0.9f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 211:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(remilia_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=3.0f;velocity_y_f8=23.0f;acceleration_y_100=1.0f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 212:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(remilia_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=14.0f;velocity_y_f8=17.5f;acceleration_y_100=0.9f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 214:
    if(sequence_index_13e==1 || sequence_index_13e==2){if(y_f0>680.0f && velocity_y_f8>0.0f)velocity_y_f8=0.0f;if(frame_index_140>=8)velocity_y_f8-=acceleration_y_100;}
    if(sequence_index_13e==3 || sequence_index_13e==4)velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){y_f0=remilia_surface(this);velocity_y_f8=0.0f;if(sequence_index_13e==1 || sequence_index_13e==2){reset_action_scratch();set_action_and_finalize(215);}else{set_action_and_finalize(10);zero_motion();}return;}
    if(advance()){set_action_and_finalize(9);return;}if(entry(4)){set_action_and_finalize(9);return;}
    if(entry(1)){if(!field_4b8)counter(100,45);else counter(200,45);event(31);word_734=static_cast<short>(word_732-static_cast<int>(field_740));velocity_x_f4=static_cast<float>(remilia_cosine(field_740)*field_73c);velocity_y_f8=static_cast<float>(remilia_sine(field_740)*field_73c);field_12c=-field_740;if(velocity_x_f4<0.0f)field_12c=static_cast<float>(180.0-field_740);if(velocity_x_f4<0.0f && sequence_index_13e==1)select_sequence(2);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && !frame_timer_142 && frame_index_140==7){reset_action_scratch();velocity_x_f4=static_cast<float>(remilia_cosine(field_740)*4.0);velocity_y_f8=static_cast<float>(remilia_sine(field_740)*4.0);flip();}
    if(entry(2)){reset_action_scratch();select_sequence(3);}else if(entry(3))reset_action_scratch();return;

case 215:
    landing();if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-1.25);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(velocity_x_f4<0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4+1.25);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);return;
case 220:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(remilia_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=0.0f;velocity_y_f8=22.5f;acceleration_y_100=0.85f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 221:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(remilia_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=14.0f;velocity_y_f8=17.5f;acceleration_y_100=0.9f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 222:
    if(!sequence_index_13e)landing();
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(remilia_on_surface(this) || velocity_y_f8>0.0f)word_4ae=2;
    if(sequence_index_13e>0){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<-20.0f)velocity_y_f8=-20.0f;}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)select_sequence(2);
    advance();
    if(!entry(1))return;
    velocity_x_f4=-14.0f;velocity_y_f8=17.5f;acceleration_y_100=0.9f;byte_47e=0;effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);return;
case 223:
    landing();byte_47e=1;if(advance())set_action_and_finalize(0);
    if(entry(1) && !word_730){velocity_x_f4=8.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);++word_730;if((field_6b4*facing_104<=0 && word_730>15) || word_730>45){next_sequence_block();return;}}
    if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}return;
case 224:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!remilia_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;acceleration_y_100=0.0f;y_f0=remilia_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);velocity_x_f4=0.0f;acceleration_y_100=0.0f;return;}
    if(entry(1) && !word_730){word_730=1;velocity_x_f4=-15.0f;velocity_y_f8=4.5f;acceleration_y_100=0.5f;dash_effects(true,80.0,false);}return;
case 225:
    if(sequence_index_13e==2)velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=remilia_surface(this);set_action_and_finalize(10);return;}
    if(advance())set_action_and_finalize(9);
    if(entry(1)){velocity_x_f4=-30.0f;velocity_y_f8=2.0f;dash_effects(false,110.0,true);}if(entry(2)){velocity_x_f4=-10.0f;velocity_y_f8=2.0f;acceleration_y_100=0.5f;flip();}return;
case 226:
    if(sequence_index_13e==2)velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=remilia_surface(this);set_action_and_finalize(10);return;}
    if(advance())set_action_and_finalize(9);
    if(entry(1)){velocity_x_f4=30.0f;velocity_y_f8=-4.0f;dash_effects(false,110.0,true);}if(entry(2)){velocity_x_f4=10.0f;velocity_y_f8=-4.0f;acceleration_y_100=0.5f;flip();}return;

case 300:
    landing();if(directional(0))return;if(byte_47e)decelerate(0.5,true);if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==3){event(27);byte_47e=0;}return;
case 301:
    landing();if(directional(0))return;if(byte_47e)decelerate(0.5,true);if(frame_index_140>4)decelerate(4.0,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3)velocity_x_f4=20.0f;if(!frame_timer_142 && frame_index_140==4){velocity_x_f4=5.0f;event(27);byte_47e=0;}}return;
case 302:
    landing();if(directional(1))return;if(byte_47e)decelerate(0.5,true);if(!field_6bc)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==5){if(byte_750==1){next_sequence_block();effect(62,static_cast<float>(x_ec-28*facing_104),static_cast<float>(y_f0+160.0),static_cast<unsigned char>(facing_104),1);return;}velocity_x_f4=15.0f;packet848(0.0f);}
        if(!frame_timer_142 && frame_index_140==6){velocity_x_f4=10.0f;event(27);byte_47e=0;}if(frame_index_140>=6)decelerate(2.0,false);}
    if(sequence_index_13e==1){if(!frame_timer_142){if(frame_index_140==1){velocity_x_f4=15.0f;packet848(0.0f);}if(!frame_timer_142 && frame_index_140==3){velocity_x_f4=10.0f;event(27);byte_47e=0;}}if(frame_index_140>=3)decelerate(2.0,false);}return;
case 303:
    landing();if(directional(0))return;if(static_cast<signed char>(byte_47e)>0)decelerate(static_cast<double>(0.6f),true);if(advance())set_action_and_finalize(2);if(!frame_timer_142 && frame_index_140==2){event(28);packet848(3.0f);}return;
case 304:
    landing();if(directional(1))return;if(velocity_x_f4>0.0f)velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.9f));if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==4){velocity_x_f4=25.0f;event(29);}return;
case 306:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);if(!frame_timer_142 && frame_index_140==3)event(28);return;
case 307:
    if(!field_6bc)byte_750=0;
    if(sequence_index_13e>=2 || (!sequence_index_13e && frame_index_140>=6)){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}}
    if(!sequence_index_13e){if(field_180==7 || field_180==2){select_sequence(2);velocity_x_f4=-10.0f;velocity_y_f8=10.0f;acceleration_y_100=0.5f;return;}if(frame_index_140<=5 && static_cast<unsigned char>(crossed())){next_sequence_block();y_f0=remilia_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e==1){landing();decelerate(2.5,false);}if(advance())set_action_and_finalize(9);
    if(entry(1)){set_action_and_finalize(9);return;}if(entry(2)){set_action_and_finalize(0);zero_motion();return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3){velocity_x_f4=30.0f;velocity_y_f8=-10.0f;acceleration_y_100=0.6f;event(29);}if(!frame_timer_142 && frame_index_140==5){velocity_x_f4=4.0f;velocity_y_f8=-2.5f;}}return;
case 308:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);if(!frame_timer_142){if(frame_index_140==2)packet848(4.0f);if(!frame_timer_142 && frame_index_140==3)event(29);}return;
case 309:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);if(!frame_timer_142 && frame_index_140==3){event(29);velocity_x_f4=5.0f;velocity_y_f8=20.0f;acceleration_y_100=1.5f;}return;
case 310:
    interval_clear();if(sequence_index_13e==1){if(!time_counter_144)velocity_x_f4=15.0f;if(time_counter_144%8==0)event(27);interval_clear();if(time_counter_144>30){next_sequence_block();velocity_y_f8=6.0f;velocity_x_f4=static_cast<float>(velocity_x_f4*0.5);}}
    if(sequence_index_13e==2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){velocity_y_f8=0.0f;y_f0=remilia_surface(this);set_action_and_finalize(9);return;}}
    if(advance())set_action_and_finalize(9);return;
case 320:
    landing();if(directional(0))return;if(frame_index_140>1)decelerate(2.0,false);if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==2){event(28);byte_47e=0;}return;
case 321:
    landing();if(directional(0))return;if(frame_index_140>3)decelerate(1.5,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==2)packet848(1.0f);if(!frame_timer_142 && frame_index_140==3){event(28);byte_47e=0;}if(!frame_timer_142 && frame_index_140==7){event(28);field_180=0;velocity_x_f4=10.0f;packet848(2.0f);}}return;
case 322:
    landing();if(directional(1))return;if(byte_47e)decelerate(0.5,true);if(!field_6bc)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==5){velocity_x_f4=15.0f;packet848(0.0f);}if(!frame_timer_142 && frame_index_140==6){velocity_x_f4=10.0f;event(27);byte_47e=0;}if(frame_index_140>=6)decelerate(2.0,false);}return;
case 325:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=remilia_surface(this);acceleration_y_100=0.0f;velocity_y_f8=0.0f;return;}
    if(advance())set_action_and_finalize(9);if(!frame_timer_142 && frame_index_140==1)event(29);return;

case 400:
    landing();if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2 && byte_750==1){charge(-22,96.0);return;}
        if(!frame_timer_142 && frame_index_140==5){field_180=1;aim800(-5.0f,5.0f);counter(200,45);phase_counter(30);dispatch_character_wave_handle(0);float p[3];for(float n=0.0f;n<6.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(20)))+(field_744-10.0));p[1]=static_cast<float>(n+15.0);p[2]=0.0f;spawn_offset(800,70,108.0,p,3);}}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4)shot800(-5.0f,5.0f,10,30,15.0,10.0,70,108.0,false);return;
case 401:
    landing();if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2 && byte_750==1){charge(-22,96.0);return;}if(!frame_timer_142 && frame_index_140==5)shot800(-55.0f,-45.0f,6,20,10.0,15.0,60,162.0,false);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4)shot800(-55.0f,-45.0f,10,30,15.0,10.0,60,162.0,false);return;
case 402:
    landing();if(advance())set_action_and_finalize(2);if(!frame_timer_142 && frame_index_140==4)shot800(-55.0f,-45.0f,8,30,15.0,10.0,30,135.0,false);return;
case 404:air800(-5.0f,5.0f,43,112.0);return;
case 406:air800(35.0f,45.0f,37,86.0);return;
// Native passes count three from one written scalar; extra values are unrecovered.
case 408:
    landing();decelerate(0.5,false);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){float p=0.0f;spawn_offset(825,106,103.0,&p,3);}return;
case 409:
    velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();y_f0=remilia_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==3 && byte_750==1){charge(5,107.0);return;}if(!frame_timer_142 && frame_index_140==5)start801(36,102.0,0.0f);}
    if(sequence_index_13e==1){if(!frame_timer_142 && frame_index_140==3)start801(36,102.0,0.0f);if(!frame_timer_142 && frame_index_140==5)packet801(20.0f,12.0f,36,102.0);if(!frame_timer_142 && frame_index_140==7)packet801(-20.0f,12.0f,36,102.0);}return;
case 411:
    landing();if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7 && byte_750)charge(-140,160.0);return;
case 412:
    landing();if(advance())set_action_and_finalize(0);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)start801(83,180.0,-70.0f);return;
case 414:
    if(sequence_index_13e==2)landing();
    if(sequence_index_13e<2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=remilia_surface(this);zero_motion();return;}}
    if(sequence_index_13e<2 && !field_6c4)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3 && byte_750==1){charge(5,107.0);return;}
        if(!frame_timer_142 && frame_index_140==5)start801(36,102.0,0.0f);
        if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1){
        if(!frame_timer_142 && frame_index_140==3)start801(36,102.0,0.0f);
        if(!frame_timer_142 && frame_index_140==5)packet801(20.0f,12.0f,36,102.0);
        if(!frame_timer_142 && frame_index_140==7)packet801(-20.0f,12.0f,36,102.0);
        if(!frame_timer_142 && frame_index_140==10)acceleration_y_100=0.5f;
    }return;
case 415:
    if(sequence_index_13e==2)landing();
    if(sequence_index_13e<2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=remilia_surface(this);zero_motion();return;}}
    if(sequence_index_13e<2 && !field_6c4)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3 && byte_750==1){charge(5,107.0);return;}
        if(!frame_timer_142 && frame_index_140==5)start801(36,102.0,0.0f);
        if(!frame_timer_142 && frame_index_140==12)acceleration_y_100=0.5f;
    }
    if(sequence_index_13e==1){
        if(!frame_timer_142 && frame_index_140==3)start801(36,102.0,0.0f);
        if(!frame_timer_142 && frame_index_140==5)packet801(20.0f,12.0f,36,102.0);
        if(!frame_timer_142 && frame_index_140==7)packet801(-20.0f,12.0f,36,102.0);
        if(!frame_timer_142 && frame_index_140==10)acceleration_y_100=0.5f;
    }return;
case 416:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(2);y_f0=remilia_surface(this);zero_motion();return;}}
    if(!field_6c4)byte_750=0;if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==2 && byte_750){next_sequence_block();effect(62,static_cast<float>(x_ec-50*facing_104),static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);return;}
        if(!frame_timer_142 && frame_index_140==5){dispatch_character_wave_handle(1);velocity_x_f4=-4.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;float p[3]={60.0f,17.5f,0.0f};field_180=1;counter(200,60);phase_counter(50);spawn_offset(801,30,60.0,p,3);}}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(1);velocity_x_f4=-4.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;float p[3]={60.0f,17.5f,0.0f};field_180=1;counter(200,60);phase_counter(50);spawn_offset(801,30,60.0,p,3);p[0]=70.0f;p[1]=12.5f;p[2]=0.0f;spawn_offset(801,30,60.0,p,3);}return;
case 418:
    landing();decelerate(0.5,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==4){float p[3]={0.0f,0.0f,0.0f};spawn(819,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);}if(!frame_timer_142 && frame_index_140==5){event(29);byte_47e=0;}}return;

case 500:
    if((!sequence_index_13e && frame_index_140<=3) || sequence_index_13e==2)landing();byte_17c=0;velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){y_f0=remilia_surface(this);velocity_x_f4=20.0f;velocity_y_f8=0.0f;acceleration_y_100=0.0f;select_sequence(2);}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){ring810();velocity_x_f4=30.0f;velocity_y_f8=12.0f;acceleration_y_100=2.0f;counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);}
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){if(sequence_index_13e==2)set_action_and_finalize(9);}else if(sequence_index_13e==2)decelerate(2.0,false);return;
case 501:
    if((!sequence_index_13e && frame_index_140<=3) || sequence_index_13e==2 || sequence_index_13e==5)landing();byte_17c=0;velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){y_f0=remilia_surface(this);velocity_y_f8=0.0f;acceleration_y_100=0.0f;if(sequence_index_13e<=1)select_sequence(2);else if(sequence_index_13e<=4){velocity_x_f4=20.0f;select_sequence(5);}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){ring810();velocity_x_f4=17.5f;velocity_y_f8=12.0f;acceleration_y_100=2.0f;counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);}
    if(entry(2)){set_action_and_finalize(9);return;}if(entry(4)){field_180=0;byte_184=1;ring810();velocity_x_f4=27.5f;velocity_y_f8=15.0f;acceleration_y_100=2.0f;dispatch_character_wave_handle(10);}
    if(entry(5)){set_action_and_finalize(9);return;}if(sequence_index_13e==2 || sequence_index_13e==5)decelerate(2.0,false);return;
case 505:
case 506:
    landing();byte_17c=4;
    if((!sequence_index_13e || sequence_index_13e==1 || sequence_index_13e==2) && velocity_x_f4>0.0f)decelerate(static_cast<double>(0.4f),false);
    if(sequence_index_13e==3 && velocity_x_f4>0.0f && frame_index_140>=9)decelerate(static_cast<double>(0.7f),false);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(entry(2)){set_action_and_finalize(0);return;}
    if(entry(3)){set_action_and_finalize(0);return;}
    if(entry(4)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e){if(frame_index_140>=7 && (field_728&6)){initialize_fighter_phase_631e0(this);word_730=1;set_action_and_finalize(505);return;}
        if(!frame_timer_142){if(frame_index_140==4){velocity_x_f4=30.0f;effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);}if(!frame_timer_142 && frame_index_140==5){dispatch_character_wave_handle(21);velocity_x_f4=5.0f;counter(200,120);phase_counter(30);packet811(0.0f);}}}
    if(sequence_index_13e==1){if(frame_index_140>=8){if(field_728&2){initialize_fighter_phase_631e0(this);word_730=2;set_action_and_finalize(505);return;}if(field_728&4){initialize_fighter_phase_631e0(this);word_730=3;set_action_and_finalize(505);return;}}
        if(!frame_timer_142){if(frame_index_140==5){velocity_x_f4=30.0f;effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);packet811(1.0f);}if(!frame_timer_142 && frame_index_140==6){dispatch_character_wave_handle(21);velocity_x_f4=5.0f;phase_counter(30);}}}
    if(sequence_index_13e==2 && !frame_timer_142){if(frame_index_140==6){velocity_x_f4=20.0f;effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);packet811(2.0f);}if(!frame_timer_142 && frame_index_140==8){dispatch_character_wave_handle(22);velocity_x_f4=5.0f;phase_counter(30);}}
    if(sequence_index_13e==3 && !frame_timer_142){if(frame_index_140==7)velocity_x_f4=20.0f;if(!frame_timer_142 && frame_index_140==9){dispatch_character_wave_handle(22);phase_counter(30);}}return;
case 520:ground815(field_6c0,7.0f);return;
case 521:ground815(field_6c4,9.0f);return;
case 525:ground816(field_6c0);return;
case 526:ground816(field_6c4);return;
case 530:ground817(field_6c0,0.0);return;
case 531:ground817(field_6c4,20.0);return;
case 540:
    if(!sequence_index_13e || sequence_index_13e==6)landing();byte_17c=2;if(!field_6c0)byte_750=0;
    if(sequence_index_13e<6){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(6);y_f0=remilia_surface(this);return;}}
    if((sequence_index_13e==2 || sequence_index_13e==3) && byte_184>0 && field_180){if(++word_730>=4){word_730=0;field_180=0;}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){phase_counter(50);counter(200,120);dispatch_character_wave_handle(12);velocity_x_f4=10.0f;velocity_y_f8=12.5f;acceleration_y_100=0.4f;float p[3]={0.0f,0.0f,0.0f};spawn(820,x_ec,y_f0,facing_104,1,p,3);}
    if(entry(4))velocity_x_f4=static_cast<float>(velocity_x_f4*0.5);return;
case 541:
    if(!sequence_index_13e || sequence_index_13e==6)landing();byte_17c=2;if(!field_6c4)byte_750=0;
    if(sequence_index_13e<6){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(6);y_f0=remilia_surface(this);return;}}
    if((sequence_index_13e==2 || sequence_index_13e==3) && byte_184>0 && field_180){if(++word_730>=4){word_730=0;field_180=0;}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){phase_counter(50);counter(200,120);dispatch_character_wave_handle(12);velocity_x_f4=15.0f;velocity_y_f8=11.0f;acceleration_y_100=0.35f;float p[3]={0.0f,0.0f,1.0f};spawn(820,x_ec,y_f0,facing_104,1,p,3);}
    if(entry(4))velocity_x_f4=static_cast<float>(velocity_x_f4*0.5);return;
case 545:ground821(-70.0f);return;
case 546:ground821(-50.0f);return;
case 547:
    if(sequence_index_13e==2)landing();byte_17c=2;if(sequence_index_13e<2){velocity_y_f8-=acceleration_y_100;double y=velocity_y_f8+static_cast<double>(y_f0);if(remilia_surface(this)>=y && velocity_y_f8<0.0f){zero_motion();select_sequence(2);y_f0=remilia_surface(this);return;}}
    if(sequence_index_13e<=1 && !field_6c0)byte_750=0;if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){if(!frame_timer_142 && frame_index_140==8 && byte_750==1){next_sequence_block();return;}if(!frame_timer_142 && frame_index_140==6){field_180=1;dispatch_character_wave_handle(7);velocity_x_f4=-4.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;spawn(816,static_cast<float>(30*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+62.0),facing_104,1,0,0);counter(200,120);phase_counter(50);}}return;

case 560:
case 561:
    if(sequence_index_13e==5)landing();byte_17c=3;if(!field_6c0)byte_750=0;if(advance())set_action_and_finalize(0);
    if(entry(1)){word_730=1;counter(200,120);velocity_x_f4=-25.0f;velocity_y_f8=15.0f;acceleration_y_100=0.3f;dispatch_character_wave_handle(13);}
    if(entry(4)){
        aim800(10.0f,70.0f);set_oriented_components_f0_f4(field_744,50.0f);phase_counter(50);field_108=0.0f;field_10c=80.0f;field_12c=field_744;dispatch_character_wave_handle(14);
        float p[3]={field_12c,0.0f,0.0f};spawn(825,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);
    }else{
        if(sequence_index_13e==1 || sequence_index_13e==2)velocity_y_f8-=acceleration_y_100;
        if(sequence_index_13e==2){
            if(classify_fighter_x_boundary()){velocity_x_f4=0.0f;velocity_y_f8=0.0f;acceleration_y_100=0.0f;next_sequence_block();return;}
            if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(5);y_f0=remilia_surface(this);return;}
        }
        if(sequence_index_13e==4){
            if(static_cast<unsigned char>(crossed())){reset_action_scratch();y_f0=remilia_surface(this);velocity_y_f8=0.0f;next_sequence_block();}
            if(classify_fighter_x_boundary() || field_180==2 || field_180==7){reset_action_scratch();set_action_and_finalize(564);velocity_x_f4=-12.5f;velocity_y_f8=10.0f;acceleration_y_100=0.5f;return;}
            if(static_cast<int>(time_counter_144)>=45){reset_action_scratch();set_action_and_finalize(564);select_sequence(2);return;}
        }
        if(sequence_index_13e==5)decelerate(5.0,false);
    }return;
case 564:{
    if(sequence_index_13e==3)landing();if(!remilia_on_surface(this)){velocity_y_f8-=acceleration_y_100;velocity_x_f4=static_cast<float>(velocity_x_f4+0.5);if(velocity_x_f4>-2.0f)velocity_x_f4=-2.0f;}
    double y=y_f0+static_cast<double>(velocity_y_f8);if(remilia_surface(this)>=y && velocity_y_f8<0.0f){select_sequence(3);byte_47f=0;y_f0=remilia_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);return;}
case 565:diving826(20.0f);return;
case 566:diving826(40.0f);return;


case 599:
    if(word_730>0 && frame_index_140<7 && word_730<12){
        word_734=static_cast<short>(remilia_random_u32()%35u);
        float p[3]={static_cast<float>(-20-word_734),static_cast<float>(static_cast<short>(remilia_random_u32()%5u+10)),0.0f};
        spawn(807,static_cast<float>(20*facing_104*(word_730+1)+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),1,p,3);
        p[0]=static_cast<float>(remilia_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        spawn(801,static_cast<float>(20*facing_104*(word_730+1)+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),1,p,3);
        if(word_730==1){dispatch_character_wave_handle(0);counter(200,120);}++word_730;
    }
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)word_730=1;return;
case 600:
    if(entry(0))spell_flash(0,200.0,3);
    if(sequence_index_13e==6)landing();texture(6,2);
    if(sequence_index_13e==3 && time_counter_144>60){next_sequence_block();acceleration_y_100=0.4f;return;}
    if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3)hover(240.0);
    if(sequence_index_13e>=4 && sequence_index_13e<=5){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(6);y_f0=remilia_surface(this);return;}}
    if(advance())set_action_and_finalize(0);if(entry(1))velocity_y_f8=0.0f;
    if(entry(2)){float p[3]={0.0f,0.0f,0.0f};spawn(850,x_ec,remilia_surface(this),facing_104,1,p,3);dispatch_character_wave_handle(50);}return;
case 601:
    if(entry(0)){spell_flash(-14,190.0,2);dispatch_character_wave_handle(52);float p[3]={0.0f,0.0f,0.0f};spawn(851,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);}
    landing();texture(6,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==12){float p[3]={0.0f,60.0f,2.0f};spawn_offset(851,100,160.0,p,3);p[2]=4.0f;spawn_offset(851,100,160.0,p,3);dispatch_character_wave_handle(53);}return;
case 602:
    if(!sequence_index_13e || sequence_index_13e==6)landing();
    if(sequence_index_13e<=3){texture(6,2);if(sequence_index_13e==3 && ++word_730>=30){acceleration_y_100=0.5f;next_sequence_block();velocity_y_f8=static_cast<float>(velocity_y_f8*0.5);velocity_x_f4=static_cast<float>(0.5*velocity_x_f4);return;}}
    if(sequence_index_13e==2 || sequence_index_13e==3){float p[3]={0.0f,0.0f,static_cast<float>(remilia_random(2))};spawn_offset(852,75,145.0,p,3);}
    if(sequence_index_13e==4 || sequence_index_13e==5){velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.2f));if(velocity_x_f4<2.0f)velocity_x_f4=2.0f;velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=remilia_surface(this);select_sequence(6);return;}}
    contact_interval();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(-53,76.0,2);
    if(entry(1)){velocity_x_f4=15.0f;velocity_y_f8=15.0f;dispatch_character_wave_handle(54);}return;
case 603:
    if(sequence_index_13e==6)landing();texture(6,2);
    if(sequence_index_13e==2){
        if(!(time_counter_144%7)){float p[3]={0.0f,0.0f,6.0f};
            spawn(853,static_cast<float>((x_ec+400.0)-static_cast<double>(static_cast<float>(remilia_random(800)))),static_cast<float>((remilia_surface(this)+50.0)-static_cast<double>(static_cast<float>(remilia_random(100)))),facing_104,1,p,3);}
        if(time_counter_144>=120){next_sequence_block();return;}
    }
    if(sequence_index_13e==3 && time_counter_144>=24){next_sequence_block();acceleration_y_100=0.4f;return;}
    if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3)hover(320.0);
    if(sequence_index_13e>=4 && sequence_index_13e<=5){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(6);y_f0=remilia_surface(this);return;}}
    if(advance())set_action_and_finalize(0);if(entry(1))velocity_y_f8=0.0f;
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(0,200.0,5);
    if(entry(1)){float p[3]={0.0f,0.0f,0.0f};spawn(853,x_ec,remilia_surface(this),facing_104,1,p,3);
        p[2]=4.0f;spawn(853,x_ec,remilia_surface(this),facing_104,1,p,3);
        p[2]=5.0f;spawn_offset(853,0,200.0,p,3);dispatch_character_wave_handle(51);}return;
case 604:
    if(entry(0)){spell_flash(-14,190.0,4);dispatch_character_wave_handle(52);float p[3]={0.0f,0.0f,0.0f};spawn(854,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);}
    landing();texture(6,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==12){float p[3]={0.0f,100.0f,2.0f};spawn_offset(854,100,160.0,p,3);p[2]=4.0f;spawn_offset(854,100,160.0,p,3);p[2]=5.0f;spawn_offset(854,100,160.0,p,3);dispatch_character_wave_handle(53);}return;
case 605:
    if(!sequence_index_13e || sequence_index_13e==4)landing();
    if(sequence_index_13e<=1){texture(6,2);if(sequence_index_13e==1 && ++word_730>=45){acceleration_y_100=0.5f;next_sequence_block();velocity_y_f8=static_cast<float>(velocity_y_f8*0.5);velocity_x_f4=static_cast<float>(0.5*velocity_x_f4);return;}}
    if(sequence_index_13e==1){float p[3]={0.0f,0.0f,static_cast<float>(remilia_random(2))};spawn_offset(855,90,125.0,p,3);}
    if(sequence_index_13e==2 || sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.2f));if(velocity_x_f4<2.0f)velocity_x_f4=2.0f;velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=remilia_surface(this);select_sequence(4);return;}}
    contact_interval();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(-53,76.0,5);
    if(entry(1)){velocity_x_f4=27.5f;velocity_y_f8=15.0f;dispatch_character_wave_handle(55);float p[3]={0.0f,0.0f,2.0f};spawn_offset(855,90,125.0,p,3);}return;
case 606:
    if(sequence_index_13e>3 || (sequence_index_13e==3 && frame_index_140>=3))texture(6,2);
    if(sequence_index_13e==5)landing();if(advance())set_action_and_finalize(0);
    if(entry(1)){word_730=1;velocity_x_f4=-25.0f;velocity_y_f8=25.0f;acceleration_y_100=0.3f;dispatch_character_wave_handle(13);}
    if(entry(4)){velocity_x_f4=50.0f;velocity_y_f8=static_cast<float>(velocity_y_f8-25.0);dispatch_character_wave_handle(55);float p[3]={0.0f,0.0f,2.0f};spawn_offset(856,90,25.0,p,3);return;}
    if(sequence_index_13e==1 || sequence_index_13e==2)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==2){if(classify_fighter_x_boundary()){velocity_x_f4=0.0f;velocity_y_f8=0.0f;acceleration_y_100=0.0f;next_sequence_block();return;}if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(5);y_f0=remilia_surface(this);return;}}
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==3)spell_flash(-53,76.0,3);
    if(sequence_index_13e==4){float p[3]={0.0f,0.0f,static_cast<float>(remilia_random(2))};spawn_offset(856,90,125.0,p,3);
        if(static_cast<unsigned char>(crossed())){reset_action_scratch();y_f0=remilia_surface(this);velocity_y_f8=0.0f;next_sequence_block();}}
    if(sequence_index_13e==5)decelerate(5.0,false);return;
case 607:
    if(sequence_index_13e==1){if(time_counter_144>=120){next_sequence_block();return;}
        if(!(time_counter_144%15) && field_73c<4.0f){float p[4]={static_cast<float>(field_73c*90.0+field_744),0.0f,1.0f,0.0f};spawn_offset(857,20,100.0,p,4);
            if(field_73c==0.0f){p[2]=0.0f;spawn_offset(857,20,100.0,p,4);}owner_168->dispatch_character_wave_handle(16);field_73c=static_cast<float>(field_73c+1.0);}}
    if(advance())set_action_and_finalize(0);if(entry(1))aim_unbounded();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(-53,76.0,3);return;

case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){event(55);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
        effect(140,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
        effect(141,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1);effect(142,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);}return;
case 696:
    landing();decelerate(0.5,false);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==6)velocity_x_f4=15.0f;if(!frame_timer_142){if(frame_index_140==7)event(29);if(!frame_timer_142 && frame_index_140==8)velocity_x_f4=0.0f;}}return;
case 707:
    if(velocity_x_f4>12.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<12.0f)velocity_x_f4=12.0f;}
    if(advance()){set_action_and_finalize(700);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){velocity_x_f4=15.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(!(time_counter_144%5))dash_dust(false);if(time_counter_144>30){next_sequence_block();return;}}
    if(sequence_index_13e==2)decelerate(0.5,false);return;
case 708:
    if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4+2.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!remilia_on_surface(this)){if(!(time_counter_144%5))dash_dust(true);velocity_y_f8=static_cast<float>(velocity_y_f8-0.5);
        double y=velocity_y_f8+static_cast<double>(y_f0);if(remilia_surface(this)>=y && velocity_y_f8<0.0f){velocity_y_f8=0.0f;y_f0=remilia_surface(this);select_sequence(2);return;}}
    if(advance()){set_action_and_finalize(700);return;}
    if(entry(1)){velocity_x_f4=-14.0f;velocity_y_f8=4.0f;dash_effects(true,80.0,false);}return;
case 709:
    if(!sequence_index_13e){velocity_y_f8-=acceleration_y_100;double y=velocity_y_f8+static_cast<double>(y_f0);if(remilia_surface(this)>=y && velocity_y_f8<0.0f){next_sequence_block();y_f0=remilia_surface(this);velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e==1){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<=0.0f){velocity_x_f4=0.0f;if(++word_730>=2){next_sequence_block();velocity_x_f4=-5.0f;velocity_y_f8=5.0f;}}}
    if(sequence_index_13e==2 || sequence_index_13e==3){velocity_y_f8=static_cast<float>(velocity_y_f8-0.25);double y=velocity_y_f8+static_cast<double>(y_f0);if(remilia_surface(this)>=y && velocity_y_f8<0.0f){zero_motion();y_f0=remilia_surface(this);next_sequence_block();return;}}
    if(advance())set_action_and_finalize(700);return;
case 710:{
    float p[4];
    if(sequence_index_13e==1){if(time_counter_144>=120){next_sequence_block();return;}if(!(time_counter_144%15)){
        switch(g_match_identifier){
        case 3:
            if(field_73c<4.0f){p[0]=static_cast<float>(field_73c*90.0+field_744);p[1]=0.0f;p[2]=1.0f;p[3]=0.0f;spawn_offset(900,20,100.0,p,4);
                if(field_73c==0.0f){p[2]=0.0f;spawn_offset(900,20,100.0,p,4);}owner_168->dispatch_character_wave_handle(16);field_73c=static_cast<float>(field_73c+1.0);}break;
        case 2:
            if(field_73c<3.0f){p[0]=static_cast<float>(field_73c*120.0+field_744);p[1]=0.0f;p[2]=1.0f;p[3]=0.0f;spawn_offset(900,20,100.0,p,4);
                p[0]=0.0f;if(field_73c==0.0f){p[2]=0.0f;spawn_offset(900,20,100.0,p,4);}owner_168->dispatch_character_wave_handle(16);field_73c=static_cast<float>(field_73c+1.0);}break;
        case 1:
            if(field_744>=90.0f)field_744=90.0f;if(field_744<=-90.0f)field_744=-90.0f;
            if(field_73c<2.0f){double step=field_73c*90.0;p[0]=static_cast<float>(step+(field_744-45.0));p[1]=0.0f;p[2]=1.0f;p[3]=0.0f;spawn_offset(900,20,100.0,p,4);
                p[0]=static_cast<float>(field_73c*90.0+field_744);if(field_73c==0.0f){p[2]=0.0f;spawn_offset(900,20,100.0,p,4);}owner_168->dispatch_character_wave_handle(16);field_73c=static_cast<float>(field_73c+1.0);}break;
        case 0:
            if(field_744>=90.0f)field_744=90.0f;if(field_744<=-90.0f)field_744=-90.0f;
            if(field_73c==0.0f){p[0]=field_744;p[1]=0.0f;p[2]=1.0f;p[3]=0.0f;spawn_offset(900,20,100.0,p,4);p[2]=0.0f;spawn_offset(900,20,100.0,p,4);owner_168->dispatch_character_wave_handle(16);field_73c=static_cast<float>(field_73c+1.0);}break;
        }
    }}
    if(sequence_index_13e==2 && time_counter_144>=60){next_sequence_block();return;}if(advance())set_action_and_finalize(700);if(entry(1))aim_unbounded();return;}
case 711:
    if(sequence_index_13e==5)landing();
    if(sequence_index_13e==2 && time_counter_144>60){next_sequence_block();acceleration_y_100=0.4f;return;}
    if(sequence_index_13e>=3 && sequence_index_13e<=4){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(5);y_f0=remilia_surface(this);return;}}
    if(advance())set_action_and_finalize(700);if(entry(1))velocity_y_f8=0.0f;
    if(entry(2)){float p[3]={0.0f,0.0f,0.0f};spawn(850,x_ec,remilia_surface(this),facing_104,1,p,3);dispatch_character_wave_handle(50);}return;
case 720:
    if(!sequence_index_13e || sequence_index_13e==6)landing();
    if(sequence_index_13e==1 && y_f0>=1280.0f){y_f0=1280.0f;zero_motion();next_sequence_block();return;}
    if(sequence_index_13e==2){
        switch(g_match_identifier){
        case 3:if(time_counter_144==45){x_ec=fighter_170->x_ec;field_73c=x_ec;float p[3]={0.0f,0.0f,6.0f};spawn(901,x_ec,0.0f,static_cast<unsigned char>(facing_104),-1,p,3);}if(time_counter_144>=120)x_ec=field_73c;break;
        case 2:if(time_counter_144==30){x_ec=fighter_170->x_ec;field_73c=x_ec;float p[3]={0.0f,0.0f,6.0f};spawn(901,x_ec,0.0f,static_cast<unsigned char>(facing_104),-1,p,3);}if(time_counter_144>=100)x_ec=field_73c;break;
        case 1:if(time_counter_144==15){x_ec=fighter_170->x_ec;field_73c=x_ec;float p[3]={0.0f,0.0f,6.0f};spawn(901,x_ec,0.0f,static_cast<unsigned char>(facing_104),-1,p,3);}if(time_counter_144>=80)x_ec=field_73c;break;
        case 0:if(!time_counter_144){x_ec=fighter_170->x_ec;field_73c=x_ec;float p[3]={0.0f,0.0f,6.0f};spawn(901,x_ec,0.0f,static_cast<unsigned char>(facing_104),-1,p,3);}if(time_counter_144>=60)x_ec=field_73c;break;
        }
        if(time_counter_144>=60){next_sequence_block();float p[3]={0.0f,0.0f,2.0f};spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);velocity_y_f8=-70.0f;}
    }
    if(sequence_index_13e==3){
        x_ec=field_73c;float trail[3]={0.0f,0.0f,3.0f};spawn(901,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1,trail,3);
        if(static_cast<unsigned char>(crossed())){
            next_sequence_block();layout(8.0f);dispatch_character_wave_handle(57);y_f0=remilia_surface(this);velocity_x_f4=-15.0f;velocity_y_f8=15.0f;acceleration_y_100=0.4f;
            float p[3]={0.0f,0.0f,0.0f};spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);p[1]=25.0f;p[2]=1.0f;
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(30)))+(n*45.0+30.0));
                if(p[0]>=0.0f && p[0]<=180.0f)spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);else spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);}
            p[0]=0.0f;p[1]=35.0f;p[2]=4.0f;
            spawn(901,static_cast<float>(50*facing_104+static_cast<double>(x_ec)),y_f0,static_cast<unsigned char>(facing_104),1,p,3);
            spawn(901,static_cast<float>(50*facing_104+static_cast<double>(x_ec)),y_f0,static_cast<signed char>(-facing_104),1,p,3);
            switch(g_match_identifier){
            case 1:for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(-45.0-n*45.0);p[1]=10.0f;p[2]=7.0f;spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);}break;
            case 2:for(float n=0.0f;n<5.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(-30.0-n*30.0);p[1]=10.0f;p[2]=7.0f;spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);}break;
            case 3:for(float n=0.0f;n<7.0f;n=static_cast<float>(n+1.0)){p[0]=static_cast<float>(-30.0-n*20.0);p[1]=10.0f;p[2]=7.0f;spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);}break;
            }
        }
    }
    if(sequence_index_13e==4 || sequence_index_13e==5){
        if(g_match_identifier==3 && ((classify_fighter_x_boundary()==1 && static_cast<unsigned char>(facing_104)==1)||(classify_fighter_x_boundary()==-1 && facing_104==-1))){
            velocity_x_f4=0.0f;velocity_y_f8=0.0f;acceleration_y_100=0.0f;set_action_and_finalize(721);select_sequence(3);byte_184=1;return;
        }
        velocity_x_f4=static_cast<float>(velocity_x_f4+static_cast<double>(0.1f));if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=remilia_surface(this);select_sequence(6);return;}
    }
    if(advance())set_action_and_finalize(700);if(entry(1)){dispatch_character_wave_handle(13);velocity_x_f4=0.0f;velocity_y_f8=40.0f;}return;
case 721:
    if(sequence_index_13e==7)landing();if(advance())set_action_and_finalize(700);
    if(entry(1)){word_730=1;velocity_x_f4=-30.0f;velocity_y_f8=static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(12)))+10.0);acceleration_y_100=0.3f;dispatch_character_wave_handle(13);}
    if(entry(4)){aim800(10.0f,70.0f);field_744=0.0f;set_oriented_components_f0_f4(0.0f,50.0f);field_108=0.0f;field_10c=80.0f;field_12c=field_744;dispatch_character_wave_handle(14);
        float p[3]={field_12c,0.0f,9.0f};spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);return;}
    if(sequence_index_13e==1 || sequence_index_13e==2)velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e==2){
        if((classify_fighter_x_boundary()==1 && static_cast<unsigned char>(facing_104)==1)||(classify_fighter_x_boundary()==-1 && facing_104==-1)){velocity_x_f4=0.0f;velocity_y_f8=0.0f;acceleration_y_100=0.0f;next_sequence_block();return;}
        if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(7);y_f0=remilia_surface(this);return;}
    }
    if(sequence_index_13e==4){
        float p[3]={0.0f,0.0f,10.0f};spawn(901,static_cast<float>(50*facing_104+static_cast<double>(x_ec)),static_cast<float>(y_f0+80.0),static_cast<unsigned char>(facing_104),-1,p,3);
        if(static_cast<unsigned char>(crossed())){reset_action_scratch();y_f0=remilia_surface(this);velocity_y_f8=0.0f;select_sequence(7);}
        if((classify_fighter_x_boundary()==1 && facing_104==-1)||(classify_fighter_x_boundary()==-1 && static_cast<unsigned char>(facing_104)==1)){
            reset_action_scratch();select_sequence(5);velocity_x_f4=-15.0f;velocity_y_f8=12.0f;acceleration_y_100=0.5f;layout(8.0f);dispatch_character_wave_handle(57);
            float impact[3];
            switch(g_match_identifier){
            case 1:for(float n=0.0f;n<3.0f;n=static_cast<float>(n+1.0)){impact[0]=static_cast<float>(-135.0-n*45.0);impact[1]=10.0f;impact[2]=7.0f;spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,impact,3);}break;
            case 2:for(float n=0.0f;n<5.0f;n=static_cast<float>(n+1.0)){impact[0]=static_cast<float>(-120.0-n*30.0);impact[1]=10.0f;impact[2]=7.0f;spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,impact,3);}break;
            case 3:for(float n=0.0f;n<7.0f;n=static_cast<float>(n+1.0)){impact[0]=static_cast<float>(-120.0-n*20.0);impact[1]=10.0f;impact[2]=7.0f;spawn(901,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,impact,3);}break;
            }return;
        }
    }
    if(sequence_index_13e==5 || sequence_index_13e==6){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=remilia_surface(this);select_sequence(7);}else{velocity_x_f4=static_cast<float>(velocity_x_f4+static_cast<double>(0.1f));if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}}return;
case 730:teleport902(12.0f,18.0f);return;
case 731:teleport902(20.0f,12.0f);return;

case 740:
    if(sequence_index_13e>=1 && sequence_index_13e<=3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(4);y_f0=remilia_surface(this);zero_motion();return;}}
    if(sequence_index_13e==1 && velocity_y_f8<4.0f)next_sequence_block();
    if(advance()){set_action_and_finalize(741);facing_104=-1;}
    if(entry(1)){velocity_x_f4=static_cast<float>((640.0-x_ec)/30.0*facing_104);velocity_y_f8=15.0f;acceleration_y_100=1.0f;finalize(-1);byte_655=1;spell_finish();}return;
case 741:
    if(sequence_index_13e>=1 && sequence_index_13e<=3){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){select_sequence(4);y_f0=remilia_surface(this);zero_motion();return;}}
    if(sequence_index_13e==1 || sequence_index_13e==2){velocity_y_f8-=acceleration_y_100;if(velocity_y_f8<0.0f)velocity_y_f8=0.0f;velocity_x_f4=static_cast<float>((640.0-x_ec)/20.0*facing_104);}
    if(sequence_index_13e==2){
        if(!word_730){switch(g_match_identifier){
            case 3:if(word_732>=60){word_732=0;word_730=1;}else ++word_732;break;
            case 2:if(word_732>=60){word_732=0;word_730=1;}else ++word_732;break;
            case 1:if(word_732>=60){word_732=0;word_730=1;}else ++word_732;break;
            case 0:if(word_732>=60){word_732=0;word_730=1;}else ++word_732;break;
        }}
        if(word_730==1){
            float p[3];
            if(!word_732){dispatch_character_wave_handle(61);p[0]=0.0f;p[1]=0.0f;p[2]=7.0f;spawn_offset(903,0,230.0,p,3);}
            if(!(time_counter_144%6)){
                p[0]=static_cast<float>(remilia_random(360));p[1]=static_cast<float>(static_cast<double>(static_cast<float>(remilia_random(600)))+100.0);p[2]=5.0f;
                spawn(903,static_cast<float>(remilia_cosine(-p[0])*p[1]*facing_104+x_ec),static_cast<float>(remilia_sine(-p[0])*p[1]+(static_cast<double>(y_f0)+230.0)),facing_104,1,p,3);
            }
            switch(g_match_identifier){
            case 3:if(!word_732)ring903(p,12,30.0);if(word_732>=90){word_732=0;word_730=2;}else ++word_732;break;
            case 2:if(!word_732)ring903(p,10,36.0);if(word_732>=90){word_732=0;word_730=2;}else ++word_732;break;
            case 1:if(!word_732)ring903(p,8,45.0);if(word_732>=90){word_732=0;word_730=2;}else ++word_732;break;
            case 0:if(!word_732)ring903(p,6,60.0);if(word_732>=90){word_732=0;word_730=2;}else ++word_732;break;
            }
        }
        if(word_730==2){
            if(!word_732){layout(10.0f);dispatch_character_wave_handle(62);float flash[3]={0.0f,0.0f,6.0f};spawn_offset(903,0,230.0,flash,3);spawn_offset(903,0,230.0,flash,3);spawn_offset(903,0,230.0,flash,3);
                float p[3];switch(g_match_identifier){case 3:burst903(p,30,2.0);break;case 2:burst903(p,20,3.0);break;case 1:burst903(p,12,3.0);break;case 0:burst903(p,8,3.0);break;}
            }
            if(word_732>=30){word_732=0;word_730=0;}else ++word_732;
        }
    }
    if(advance()){set_action_and_finalize(741);flip();}if(entry(1)){velocity_x_f4=0.0f;velocity_y_f8=15.0f;acceleration_y_100=0.3f;}return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){byte_655=1;finalize(-1);spell_finish();}return;
case 795:
    if(!sequence_index_13e){velocity_y_f8=static_cast<float>(velocity_y_f8-static_cast<double>(0.3f));if(static_cast<unsigned char>(crossed())){event(30);select_sequence(1);y_f0=remilia_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:
    if(sequence_index_13e<=2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){event(30);select_sequence(3);y_f0=remilia_surface(this);velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;x_ec=480.0f;}if(x_ec>480.0f)x_ec=480.0f;}
    if(advance())set_action_and_finalize(0);return;
case 798:
    if(sequence_index_13e<=2){velocity_y_f8-=acceleration_y_100;if(static_cast<unsigned char>(crossed())){event(30);select_sequence(3);y_f0=remilia_surface(this);velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;x_ec=800.0f;}if(x_ec<800.0f)x_ec=800.0f;}
    if(advance())set_action_and_finalize(700);return;

default:common_update();return;
}
advance();
}
}
