#include <cmath>
#include "TenshiActionState.hpp"
// JP1.06a 0x0063D3E0; complete code and six-table payload.
// See docs/TENSHI_ACTION_STATE_2026_10_27.md.
namespace th105 {
void TenshiActionStateView::dispatch_action_state_vslot28()
{
    word_7a0=0; word_7a2=95; word_830=0;
    if(word_82e>0) --word_82e;
    if(field_838>0) {
        --field_838; field_4c4=0.0f;
        field_4c0=static_cast<float>(field_4c0*0.75);
        word_48e=1;
    }
    if((action_id_13c>=50 && action_id_13c<=149) ||
       field_834<=0 || related_170->word_174<=0) word_82e=0;
    if(word_174<=0 || related_170->word_174<=0) field_838=0;
    if(action_id_13c>=600 && action_id_13c<=689 &&
       (action_id_13c!=606 || sequence_index_13e<1)) field_838=0;
    if(word_174<=0 && byte_72c==2 && action_id_13c>=70 && action_id_13c<=149) {
        if(static_cast<signed char>(byte_55a)>0 && (card()<=15 || card()>=248)) event_owner()->trigger(16);
        byte_82c=0;
    }
    if(byte_72c==2 && byte_55a==1 && word_840==0 && word_174<=0) {
        if(card()>=16 && card()<=19) {
            word_840=1;
            float payload[3]={0.0f,0.0f,0.0f};
            spawn(997,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,payload,3);
            tenshi_bgm_volume(2000,0);
        }
    }
    if(action_id_13c>149 && action_id_13c<159 && !byte_751) {
        byte_751=1;
        if(action_id_13c>149 && action_id_13c<154)
            spawn(998,static_cast<float>(57*facing_104+static_cast<double>(x_ec)),
                  static_cast<float>(y_f0+94.0),static_cast<unsigned char>(facing_104),1,0,0);
        if(action_id_13c>153 && action_id_13c<158)
            spawn(998,static_cast<float>(57*facing_104+static_cast<double>(x_ec)),
                  static_cast<float>(y_f0+60.0),static_cast<unsigned char>(facing_104),1,0,0);
        if(action_id_13c==158)
            spawn(998,static_cast<float>(57*facing_104+static_cast<double>(x_ec)),
                  static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,0,0);
    }
    if(word_186 || related_170->word_48c) return;
    switch(action_id_13c) {
// Character action dispatch; entry guards retain native callback rereads.
case 0:
    landing();if(velocity_x_f4==0.0f)byte_47e=0;
    idle_motion();break;
case 1:
    landing();idle_motion();
    if(advance() && frame_index_140==0)set_action_and_finalize(2);
    return;
case 2:
    landing();idle_motion();break;
case 3:
    landing();idle_motion();
    if(advance() && frame_index_140==0)set_action_and_finalize(0);
    return;
case 4: landing();velocity_x_f4=4.5f;break;
case 5: landing();velocity_x_f4=-4.5f;break;
case 6:
    if(sequence_index_13e==0) {
        landing(); if(sequence_index_13e==0 && !byte_47e) zero_motion();
    }
    if(sequence_index_13e>0) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
    }
    advance();
    if(ENTRY(1)) {velocity_x_f4=0.0f;velocity_y_f8=16.5f;acceleration_y_100=0.7f;byte_47e=0;}
    return;
case 7:
    if(sequence_index_13e==0) {
        landing(); if(sequence_index_13e==0 && !byte_47e) zero_motion();
    }
    if(sequence_index_13e>0) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
    }
    advance();
    if(ENTRY(1)) {velocity_x_f4=6.0f;velocity_y_f8=16.5f;acceleration_y_100=0.7f;byte_47e=0;}
    return;
case 8:
    if(sequence_index_13e==0) {
        landing(); if(sequence_index_13e==0 && !byte_47e) zero_motion();
    }
    if(sequence_index_13e>0) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
    }
    advance();
    if(ENTRY(1)) {velocity_x_f4=-6.0f;velocity_y_f8=16.5f;acceleration_y_100=0.7f;byte_47e=0;}
    return;
case 9:
    if(acceleration_y_100==0.0f) acceleration_y_100=0.6f;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
    break;
case 10:
    landing();zero_motion();
    if(advance()) {if(field_6b8==0)set_action_and_finalize(0);else set_action_and_finalize(2);}
    return;
case 99:
    landing();
    if(sequence_index_13e==3) {
        if(byte_113>3) byte_113-=3;else byte_113=0;
    }
    if(sequence_index_13e==4 && word_840==2) {
        if(++word_730==300) {
            tenshi_fade_in(0xffffffffu,20);layout(10.0f);dispatch_character_wave_handle(54);
            word_730=0;
            float payload[3]={0.0f,0.0f,0.0f};
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
                payload[2]=n;
                spawn(962,static_cast<float>(n*160.0+80.0),0.0f,1,-1,payload,3);
            }
            next_sequence_block();word_730=0;
        }
        if(word_730>=280) {word_732=3;dispatch_character_wave_handle(56);}
        else if(word_730>=180) {
            if(word_730%10==0) {dispatch_character_wave_handle(18);layout(4.0f);}
            word_732=2;
        } else if(word_730>=60) {
            if(word_730%10==0) {dispatch_character_wave_handle(18);layout(2.0f);}
            word_732=1;
        }
    }
    if(sequence_index_13e==5) {
        if(word_730%10==0) layout(10.0f);
        ++word_730;
        int i=0;
        float *position=&samples_7a4[0];
        for(;i<8;++i,++position) {
            *position=static_cast<float>(*position+40.0);
            if(*position>=1000.0f) {
                set_action_and_finalize(750);event_owner()->music(6,0);
                related_170->x_ec=480.0f;
                related_170->y_f0=tenshi_surface(related_170);
                related_170->facing_104=1;
                related_170->zero_motion();related_170->set_action_and_finalize(0);
                y_f0=static_cast<float>(tenshi_surface(this)+150.0);
                facing_104=-1;x_ec=800.0f;zero_motion();return;
            }
        }
    }
    advance();
    if(ENTRY(2)) {
        if(byte_72c==2 && byte_55a==1 && card()>=16 && card()<=19) select_sequence(4);
        else if(!byte_4eb) {
            if(static_cast<signed char>(byte_55a)>0 && byte_72c==2 && card()>=248) copy_health();
            set_action_and_finalize(199);byte_4e9=0;byte_4ec=1;
        }
    }
    return;

case 197:
    if((sequence_index_13e==0 && frame_index_140<=1) || sequence_index_13e==2) landing();
    if(sequence_index_13e<2) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {recover_air_sequence();return;}
    }
    if(advance()) {
        if(byte_72c==2) {set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(0);if(field_6b8>0) set_action_and_finalize(1);
    }
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142) ground_face();
    if(sequence_index_13e==0 && frame_index_140==2 && !frame_timer_142) {
        velocity_y_f8=6.0f;velocity_x_f4=14.5f;acceleration_y_100=0.5f;
    }
    return;
case 198:
    if((sequence_index_13e==0 && frame_index_140<=1) || sequence_index_13e==2) landing();
    if(sequence_index_13e<2) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {recover_air_sequence();return;}
    }
    if(advance()) {
        if(byte_72c==2) {set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(0);if(field_6b8>0) set_action_and_finalize(1);
    }
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142) ground_face();
    if(sequence_index_13e==0 && frame_index_140==2 && !frame_timer_142) {
        velocity_y_f8=6.0f;velocity_x_f4=-14.5f;acceleration_y_100=0.5f;
    }
    return;
case 199:
    landing();
    if(advance()) {
        if(byte_72c==2) {set_action_and_finalize(700);word_4a8=3;word_4ac=3;return;}
        set_action_and_finalize(0);if(field_6b8>0) set_action_and_finalize(1);
    }
    if(sequence_index_13e==0 && frame_index_140==10 && !frame_timer_142) ground_face();
    return;
case 200:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0) dash_dust(false);
        if(field_6b8<0) {
            if(field_6b4*facing_104>0)set_action_and_finalize(212);else set_action_and_finalize(211);return;
        }
        ++word_730;
        if((field_6b4*facing_104<=0 && word_730>5) || word_730>45) {
            set_action_and_finalize(204);return;
        }
    }
    if(sequence_index_13e==0 && frame_index_140==4 && !frame_timer_142) {
        velocity_x_f4=11.0f;dash_effects(false,80.0,true);
    }
    return;
case 201:
    if(sequence_index_13e==0 || sequence_index_13e==3) landing();
    if(sequence_index_13e==3) {velocity_x_f4=static_cast<float>(velocity_x_f4+1.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!static_cast<unsigned char>(tenshi_on_surface(this)) && time_counter_144%5==0) dash_dust(true);
    if(sequence_index_13e<3) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {velocity_y_f8=0.0f;y_f0=tenshi_surface(this);select_sequence(3);return;}
    }
    if(advance()) {set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if(ENTRY(1)) {velocity_x_f4=-12.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(true,80.0,false);}
    return;
case 202:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())) {zero_motion();y_f0=tenshi_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0) dash_dust(false);
    advance();
    if(sequence_index_13e==0 && !frame_timer_142 && frame_index_140==3) {
        word_730=0;velocity_x_f4=11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(false,110.0,true);
    }
    if(ENTRY(2)) flip();
    return;
case 203:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())) {zero_motion();y_f0=tenshi_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0) dash_dust(true);
    advance();
    if(time_counter_144==0) {
        if(!frame_timer_142 && !frame_index_140 && sequence_index_13e==1) {
            velocity_x_f4=-11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(true,120.0,false);
        }
        if(ENTRY(2)) flip();
    }
    return;
case 204:
    landing();velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
    if(velocity_x_f4<0.0f) {velocity_x_f4=0.0f;byte_47e=0;}
    if(advance()) {set_action_and_finalize(0);byte_47e=0;} return;
case 208: {
        if(sequence_index_13e==0) landing();
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
        if(static_cast<unsigned char>(tenshi_on_surface(this)) || velocity_y_f8>0.0f) word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f) velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f) select_sequence(2);
        advance();
        if(!ENTRY(1)) return;
        {
            velocity_x_f4=0.0f;velocity_y_f8=22.5f;acceleration_y_100=0.85f;
            byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }

        return;
    }
case 209: {
        if(sequence_index_13e==0) landing();
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
        if(static_cast<unsigned char>(tenshi_on_surface(this)) || velocity_y_f8>0.0f) word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f) velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f) select_sequence(2);
        advance();
        if(!ENTRY(1)) return;
        {
            velocity_x_f4=10.0f;velocity_y_f8=18.0f;acceleration_y_100=0.85f;
            byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }

        return;
    }
case 210: {
        if(sequence_index_13e==0) landing();
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
        if(static_cast<unsigned char>(tenshi_on_surface(this)) || velocity_y_f8>0.0f) word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f) velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f) select_sequence(2);
        advance();
        if(!ENTRY(1)) return;
        {
            velocity_x_f4=-10.0f;velocity_y_f8=18.0f;acceleration_y_100=0.85f;
            byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }

        return;
    }
case 211: {
        if(sequence_index_13e==0) landing();
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
        if(static_cast<unsigned char>(tenshi_on_surface(this)) || velocity_y_f8>0.0f) word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f) velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f) select_sequence(2);
        advance();
        if(!ENTRY(1)) return;
        {
            velocity_x_f4=3.0f;velocity_y_f8=22.5f;acceleration_y_100=0.85f;
            byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }

        return;
    }
case 212: {
        if(sequence_index_13e==0) landing();
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
        if(static_cast<unsigned char>(tenshi_on_surface(this)) || velocity_y_f8>0.0f) word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f) velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f) select_sequence(2);
        advance();
        if(!ENTRY(1)) return;
        {
            velocity_x_f4=10.0f;velocity_y_f8=16.0f;acceleration_y_100=0.7f;
            byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }

        return;
    }
    case 214: {
        if (advance()) { set_action_and_finalize(9); return; }
        if (time_counter_144==0) {
            if (frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) event(31);
            if (time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==6) { set_action_and_finalize(9); return; }
        }
                if (field_6b8 > 0) {
                    if (facing_104 * field_6b4 > 0) word_732 = -45;
                    else if (facing_104 * field_6b4 < 0) word_732 = -135;
                    else word_732 = -90;
                }
                else if (field_6b8 < 0) {
                    if (facing_104 * field_6b4 > 0) word_732 = 45;
                    else if (facing_104 * field_6b4 < 0) word_732 = 135;
                    else word_732 = 90;
                }
                else {
                    if (facing_104 * field_6b4 > 0) word_732 = 0;
                    else if (facing_104 * field_6b4 < 0) word_732 = 180;
                }
                if (sequence_index_13e == 5 || sequence_index_13e == 6)                 velocity_y_f8 -= acceleration_y_100;
                if (sequence_index_13e > 0 && sequence_index_13e < 5) {
                    ++word_736;
                    word_734 = static_cast<short>(word_732 - static_cast<short>(static_cast<int>(field_740)));
                    if (word_734 > 180) word_734 -= 360;
                    if (word_734 < -180) word_734 += 360;
                    if (word_734 > 0) {
                        if (field_4b8 == 0) field_740 = static_cast<float>(field_740 + 1.5);
                        else field_740 = static_cast<float>(field_740 + 0.5);
                    }
                    if (word_734 < 0) {
                        if (field_4b8 == 0) field_740 = static_cast<float>(field_740 - 1.5);
                        else field_740 = static_cast<float>(field_740 - 0.5);
                    }
                    velocity_x_f4 = tenshi_cosine(field_740) * field_73c;
                    velocity_y_f8 = tenshi_sine(field_740) * field_73c;
                    if (y_f0 > 680.0 && velocity_y_f8 > 0.0) velocity_y_f8 = 0.0f;
                    field_73c = static_cast<float>(field_73c + static_cast<double>(0.3f));
                    if (field_73c > 12.0f) field_73c = 12.0f;
                    if (field_4b8 == 0) counter(5, 1);
                    else counter(10, 1);
                    orientation_12c = -field_740;
                    if (velocity_x_f4 < 0.0) orientation_12c = 180.0 - field_740;
                    if (velocity_x_f4 < 0.0 && sequence_index_13e == 1) select_sequence(3);
                    if (velocity_x_f4 >= 0.0 && sequence_index_13e == 3) select_sequence(1);
                    if (velocity_x_f4 < 0.0 && sequence_index_13e == 2) select_sequence(4);
                    if (velocity_x_f4 >= 0.0 && sequence_index_13e == 4) select_sequence(2);
                    if (time_counter_144 % 5 == 1) {
                        effect(125,                         tenshi_cosine(field_740) * 100.0 * facing_104 + x_ec,                         tenshi_sine(field_740) * 100.0 + y_f0 + 100.0,                         facing_104, 1);
                    }
                    if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                        if ((field_6c8 == 0 && word_736 > 10) || word_482 <= 0) {
                            reset_action_scratch();
                            if (sequence_index_13e == 1 || sequence_index_13e == 2) {
                                if (facing_104 == 1) {
                                    if (x_ec > related_170->x_ec) {
                                        facing_104 = -1;
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(6);
                                    }
                                    else select_sequence(5);
                                }
                                else {
                                    if (x_ec < related_170->x_ec) {
                                        facing_104 = static_cast<unsigned char>(-static_cast<unsigned char>(facing_104));
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(6);
                                    }
                                    else select_sequence(5);
                                }
                            }
                            if (sequence_index_13e == 3 || sequence_index_13e == 4) {
                                if (facing_104 == 1) {
                                    if (x_ec > related_170->x_ec) {
                                        facing_104 = -1;
                                        velocity_x_f4 = -velocity_x_f4;
                                        select_sequence(5);
                                    }
                                    else select_sequence(6);
                                    return;
                                }
                                if (x_ec < related_170->x_ec) {
                                    facing_104 = static_cast<unsigned char>(-static_cast<unsigned char>(facing_104));
                                    velocity_x_f4 = -velocity_x_f4;
                                    select_sequence(5);
                                }
                                else select_sequence(6);
                            }
                            return;
                        }
                    }
                }
                if (static_cast<unsigned char>(crossed())) {
                    y_f0 = tenshi_surface(this);
                    velocity_y_f8 = 0.0f;
                    if (sequence_index_13e < 5) {
                        reset_action_scratch();
                        set_action_and_finalize(215);
                    }
                    else {
                        set_action_and_finalize(10);
                        zero_motion();
                    }
                }
                return;
            }
case 215:
    landing();
    if(velocity_x_f4>0.0f) {velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(velocity_x_f4<0.0f) {velocity_x_f4=static_cast<float>(velocity_x_f4+0.75);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220: {
        if(sequence_index_13e==0) landing();
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
        if(static_cast<unsigned char>(tenshi_on_surface(this)) || velocity_y_f8>0.0f) word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f) velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f) select_sequence(2);
        advance();
        if(ENTRY(1)) {
            velocity_x_f4=0.0f;velocity_y_f8=22.5f;acceleration_y_100=0.85f;
            byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }

        return;
    }
case 221: {
        if(sequence_index_13e==0) landing();
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
        if(static_cast<unsigned char>(tenshi_on_surface(this)) || velocity_y_f8>0.0f) word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f) velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f) select_sequence(2);
        advance();
        if(ENTRY(1)) {
            velocity_x_f4=10.0f;velocity_y_f8=18.0f;acceleration_y_100=0.85f;
            byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }

        return;
    }
case 222: {
        if(sequence_index_13e==0) landing();
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
        if(static_cast<unsigned char>(tenshi_on_surface(this)) || velocity_y_f8>0.0f) word_4ae=2;
        if(sequence_index_13e>0) {
            velocity_y_f8-=acceleration_y_100;
            if(velocity_y_f8<-20.0f) velocity_y_f8=-20.0f;
        }
        if(sequence_index_13e==1 && velocity_y_f8<4.0f) select_sequence(2);
        advance();
        if(ENTRY(1)) {
            velocity_x_f4=-10.0f;velocity_y_f8=18.0f;acceleration_y_100=0.85f;
            byte_47e=0;
            effect(63,x_ec,y_f0,static_cast<unsigned char>(facing_104),1);
        }

        return;
    }
case 223:
    landing();byte_47e=1;advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        ++word_730;
        if((field_6b4*facing_104<=0 && word_730>11) || word_730>45) {set_action_and_finalize(204);return;}
    }
    if(sequence_index_13e==0 && frame_index_140==5 && !frame_timer_142) {
        velocity_x_f4=5.5f;dash_effects(false,80.0,true);
    }
    return;
case 224:
    if(sequence_index_13e==0 || sequence_index_13e==3)landing();
    if(sequence_index_13e==3) {velocity_x_f4=static_cast<float>(velocity_x_f4+1.0);if(velocity_x_f4>0.0f)velocity_x_f4=0.0f;}
    if(!static_cast<unsigned char>(tenshi_on_surface(this)) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {velocity_y_f8=0.0f;y_f0=tenshi_surface(this);select_sequence(3);return;}
    }
    if(advance()) {set_action_and_finalize(0);velocity_x_f4=0.0f;return;}
    if(ENTRY(1)) {velocity_x_f4=-10.0f;velocity_y_f8=4.0f;acceleration_y_100=0.3f;dash_effects(true,80.0,false);}
    return;
case 225:
    if(sequence_index_13e>=1)velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())) {zero_motion();y_f0=tenshi_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e>=2 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(time_counter_144==0) {
        if(!frame_timer_142 && !frame_index_140 && sequence_index_13e==1) {
            velocity_x_f4=-11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(true,120.0,false);
        }
        if(ENTRY(2))flip();
    }
    return;
case 226:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())) {zero_motion();y_f0=tenshi_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e==1 && time_counter_144%5==0)dash_dust(false);
    if(advance())set_action_and_finalize(9);
    if(sequence_index_13e==0 && !frame_timer_142 && frame_index_140==3) {
        word_730=0;velocity_x_f4=11.0f;velocity_y_f8=4.0f;acceleration_y_100=0.5f;dash_effects(false,110.0,true);
    }
    if(ENTRY(2))flip();
    return;


case 300:
    landing();
    if(!directional(0)) {
        if(byte_47e) {velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}}
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142 && frame_index_140==3) {event(28);byte_47e=0;}
    }
    return;
case 301:
    landing();if(directional(0))return;
    if(byte_47e) {velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}}
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)) {set_action_and_finalize(0);return;}
    if(sequence_index_13e!=0)return;
    if(!frame_timer_142) {
        if(frame_index_140==4){velocity_x_f4=15.0f;byte_47e=0;}
        if(!frame_timer_142 && frame_index_140==5)event(29);
    }
    if(frame_index_140>3){velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    return;
case 302:
    if((sequence_index_13e==0 && (frame_index_140<=3 || frame_index_140>=8)) || sequence_index_13e==1)landing();
    if(directional(1))return;
    if(byte_47e){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}}
    if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)){set_action_and_finalize(0);return;}
    if(sequence_index_13e==0) {
        if(!frame_timer_142 && frame_index_140==2 && byte_750) {
            next_sequence_block();
            int direction=static_cast<unsigned char>(facing_104);
            float y=static_cast<float>(y_f0+140.0);
            float x=static_cast<float>(x_ec-static_cast<float>(65*static_cast<signed char>(direction)));
            effect(62,x,y,direction,1);
            return;
        }
        if(frame_index_140>=7){velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
        if(!frame_timer_142) {
            if(frame_index_140==4){velocity_x_f4=10.0f;byte_47e=0;}
            if(!frame_timer_142 && frame_index_140==7)event(29);
        }
    }
    if(sequence_index_13e==1) {
        if(frame_index_140>=3){velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
        if(!frame_timer_142 && frame_index_140==2){velocity_x_f4=20.0f;byte_47e=0;event(29);}
    }
    return;
case 303:
    landing();
    if(!directional(0)) {
        if(static_cast<signed char>(byte_47e)>0){velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.6f));if(velocity_x_f4<0.0f){velocity_x_f4=0.0f;byte_47e=0;}}
        if(advance())set_action_and_finalize(2);
        if(!frame_timer_142 && frame_index_140==2)event(28);
    }
    return;
case 304:
    landing();if(directional(1))return;
    if(velocity_x_f4>0.0f){velocity_x_f4=static_cast<float>(velocity_x_f4-2.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(!field_6bc)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)){set_action_and_finalize(0);return;}
    if(sequence_index_13e!=0)return;
    if(!frame_timer_142 && frame_index_140==3)event(29);
    if(!frame_timer_142 && frame_index_140==4)velocity_x_f4=5.0f;
    if(frame_index_140>=4){velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.2f));if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    return;
case 305:
    landing();
    if(!directional(1)) {
        if(frame_index_140>4){velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142 && frame_index_140==3)event(28);
    }
    return;
case 306:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!frame_timer_142 && frame_index_140==2)event(27);
    return;
case 307:
    if(!field_6bc)byte_750=0;
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
    if(sequence_index_13e==0 && frame_index_140>=3) {
        velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<2.0f)velocity_x_f4=2.0f;
        if(frame_index_140<=6 && word_730>0) {if(word_730%10==1)event(29);++word_730;}
        if(frame_index_140<=8 && velocity_y_f8<=-3.0f)velocity_y_f8=-3.0f;
    }
    if(advance())set_action_and_finalize(9);
    if(ENTRY(1)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==0 && !frame_timer_142 && frame_index_140==3) {
        float payload[4]={0.0f,150.0f,0.0f,0.0f};
        spawn(848,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,payload,4);
        payload[0]=120.0f;spawn(848,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,payload,4);
        payload[0]=240.0f;spawn(848,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,payload,4);
        velocity_x_f4=15.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;word_730=1;
    }
    return;
case 308:
    if(sequence_index_13e==2)landing();
    if(!field_6bc)byte_750=0;
    if(sequence_index_13e==1 && static_cast<unsigned char>(crossed())) {
        next_sequence_block();y_f0=tenshi_surface(this);zero_motion();layout(5.0f);
        float payload[3]={0.0f,20.0f,1.0f};
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
            payload[0]=static_cast<float>(static_cast<float>(tenshi_random(30))+n*45.0);
            if(payload[0]>=0.0f && payload[0]<=180.0f)spawn(848,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,payload,3);
            else spawn(848,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,payload,3);
        }
        dispatch_character_wave_handle(2);
    }
    if(advance())set_action_and_finalize(9);
    if(ENTRY(1)){velocity_x_f4=0.0f;velocity_y_f8=-25.0f;}
    return;
case 309:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);y_f0=tenshi_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(sequence_index_13e==0 && !frame_timer_142 && frame_index_140==2) {event(29);velocity_y_f8=8.5f;acceleration_y_100=0.5f;}
    return;
case 310:
    if(sequence_index_13e<2) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {velocity_y_f8=0.0f;y_f0=tenshi_surface(this);select_sequence(2);return;}
    }
    if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(9);
    if(sequence_index_13e==1 && !frame_timer_142 && !frame_index_140 && static_cast<signed char>(byte_184)>0){field_180=0;event(28);}
    return;

case 320:
    landing();
    if(!directional(0)) {
        if(frame_index_140>=2){velocity_x_f4=static_cast<float>(velocity_x_f4-3.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142) {
            if(frame_index_140==1)event(28);
            if(!frame_timer_142 && frame_index_140==2){velocity_x_f4=15.0f;byte_47e=0;}
        }
    }
    return;
case 321:
    landing();
    if(!directional(1)) {
        if(frame_index_140>=3){velocity_x_f4=static_cast<float>(velocity_x_f4-1.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142) {
            if(frame_index_140==3){velocity_x_f4=15.0f;event(29);byte_47e=0;}
            if(!frame_timer_142 && frame_index_140==5)velocity_x_f4=0.0f;
        }
    }
    return;
case 400:
    landing();if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        aim(-20.0f,20.0f);word_730=1;
        float p[3]={field_744,17.5f,4.0f};
        int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+110.0);
        float x=static_cast<float>(50*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(800,x,y,direction,1,p,3);phase_counter(30);field_180=1;dispatch_character_wave_handle(0);counter(200,45);
    }
    return;
case 401:
    landing();if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        aim(-20.0f,20.0f);word_730=1;
        float p[3]={field_744,17.5f,4.0f};
        int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+110.0);
        float x=static_cast<float>(50*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(800,x,y,direction,1,p,3);field_180=1;dispatch_character_wave_handle(0);counter(200,45);phase_counter(30);
    }
    return;
case 402:
    landing();if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==3) {
        field_180=1;aim(-70.0f,-45.0f);word_730=1;
        float p[3]={field_744,17.5f,4.0f};
        int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+50.0);
        float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(800,x,y,direction,1,p,3);field_180=1;dispatch_character_wave_handle(0);counter(200,45);phase_counter(30);
    }
    return;
case 404: {
        if(sequence_index_13e==2)landing();
        if(sequence_index_13e<2 && !field_6c0)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            select_sequence(2);byte_47f=0;
            y_f0=tenshi_surface(this);zero_motion();return;
        }
        if(advance())set_action_and_finalize(0);
        if(ENTRY(1)){set_action_and_finalize(9);return;}
        if(ENTRY(2)){set_action_and_finalize(9);return;}
        if(sequence_index_13e==0 && !frame_timer_142) {
            if(frame_index_140==6) {
                field_180=1;aim(-10.0f,10.0f);
                float p[3]={field_744,17.5f,4.0f};
                int direction=static_cast<unsigned char>(facing_104);
                float y=static_cast<float>(y_f0+115.0);
                float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(800,x,y,direction,1,p,3);
                dispatch_character_wave_handle(0);counter(200,45);phase_counter(30);
            }
            if(!frame_timer_142 && frame_index_140==15)acceleration_y_100=0.5f;
        }

        return;
    }
case 405: {
        if(sequence_index_13e==2)landing();
        if(sequence_index_13e<2 && !field_6c0)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            select_sequence(2);byte_47f=0;
            y_f0=tenshi_surface(this);zero_motion();return;
        }
        if(advance())set_action_and_finalize(0);
        if(ENTRY(1)){set_action_and_finalize(9);return;}
        if(ENTRY(2)){set_action_and_finalize(9);return;}
        if(sequence_index_13e==0 && !frame_timer_142) {
            if(frame_index_140==6) {
                field_180=1;aim(-20.0f,20.0f);
                float p[3]={field_744,17.5f,4.0f};
                int direction=static_cast<unsigned char>(facing_104);
                float y=static_cast<float>(y_f0+115.0);
                float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(800,x,y,direction,1,p,3);
                dispatch_character_wave_handle(0);counter(200,45);phase_counter(30);
            }
            if(!frame_timer_142 && frame_index_140==15)acceleration_y_100=0.5f;
        }

        return;
    }
case 406: {
        if(sequence_index_13e==2)landing();
        if(sequence_index_13e<2 && !field_6c0)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
            select_sequence(2);byte_47f=0;
            y_f0=tenshi_surface(this);zero_motion();return;
        }
        if(advance())set_action_and_finalize(0);
        if(ENTRY(1)){set_action_and_finalize(9);return;}
        if(ENTRY(2)){set_action_and_finalize(9);return;}
        if(sequence_index_13e==0 && !frame_timer_142) {
            if(frame_index_140==6) {
                field_180=1;aim(25.0f,45.0f);
                float p[3]={field_744,17.5f,4.0f};
                int direction=static_cast<unsigned char>(facing_104);
                float y=static_cast<float>(y_f0+115.0);
                float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(800,x,y,direction,1,p,3);
                dispatch_character_wave_handle(0);counter(200,45);phase_counter(30);
            }
            if(!frame_timer_142 && frame_index_140==15)acceleration_y_100=0.5f;
        }

        return;
    }
case 408:
    landing();
    if(sequence_index_13e==3)velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);
    if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    if(sequence_index_13e==1 || sequence_index_13e==2) {if(time_counter_144%14==0)event(28);++word_730;}
    if(advance())set_action_and_finalize(0);
    if((sequence_index_13e==1 || sequence_index_13e==2) &&
       (frame_index_140==0 || frame_index_140==4) && !frame_timer_142) field_180=0;
    return;
case 409:
    velocity_y_f8-=acceleration_y_100;
    if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);zero_motion();y_f0=tenshi_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    landing();
    if((sequence_index_13e==1 && time_counter_144>=16) || (sequence_index_13e==2 && time_counter_144>=20)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        field_180=1;float p[3]={-10.0f,20.0f,4.0f};
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+115.0);
        float x=static_cast<float>(70*facing_104+static_cast<double>(x_ec));
        spawn(801,x,y,direction,1,p,3);counter(200,60);phase_counter(50);
    } return;
case 411:
    landing();
    if((sequence_index_13e==1 && time_counter_144>=16) || (sequence_index_13e==2 && time_counter_144>=20)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        field_180=1;float p[3]={-10.0f,20.0f,4.0f};
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+115.0);
        float x=static_cast<float>(70*facing_104+static_cast<double>(x_ec));
        spawn(801,x,y,direction,1,p,3);counter(200,60);phase_counter(50);
    } return;
case 412:
    landing();if(advance())set_action_and_finalize(2);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        field_180=1;ring_801(100.0);field_168->dispatch_character_wave_handle(1);counter(200,60);phase_counter(50);
    }return;
case 414: {
        if(sequence_index_13e==4)landing();
        if((sequence_index_13e==1 && time_counter_144>=16) ||
           (sequence_index_13e==2 && time_counter_144>=20)) {next_sequence_block();return;}
        if(sequence_index_13e==2 || sequence_index_13e==3) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                select_sequence(4);y_f0=tenshi_surface(this);zero_motion();return;
            }
        }
        if(advance())set_action_and_finalize(0);
        if(ENTRY(4)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
            field_180=1;float p[3]={-10.0f,20.0f,4.0f};
            int direction=static_cast<unsigned char>(facing_104);
            float y=static_cast<float>(y_f0+115.0);
            float x=static_cast<float>(70*facing_104+static_cast<double>(x_ec));
            spawn(801,x,y,direction,1,p,3);counter(200,60);phase_counter(50);
        }
        if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2)acceleration_y_100=0.5f;

        return;
    }
case 415: {
        if(sequence_index_13e==4)landing();
        if((sequence_index_13e==1 && time_counter_144>=16) ||
           (sequence_index_13e==2 && time_counter_144>=20)) {next_sequence_block();return;}
        if(sequence_index_13e==2 || sequence_index_13e==3) {
            velocity_y_f8-=acceleration_y_100;
            if(static_cast<unsigned char>(crossed())) {
                select_sequence(4);y_f0=tenshi_surface(this);zero_motion();return;
            }
        }
        if(advance())set_action_and_finalize(0);
        if(ENTRY(4)){set_action_and_finalize(9);return;}
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
            field_180=1;float p[3]={-10.0f,20.0f,4.0f};
            int direction=static_cast<unsigned char>(facing_104);
            float y=static_cast<float>(y_f0+115.0);
            float x=static_cast<float>(70*facing_104+static_cast<double>(x_ec));
            spawn(801,x,y,direction,1,p,3);counter(200,60);phase_counter(50);
        }
        if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2)acceleration_y_100=0.5f;

        return;
    }
case 416:
    if(sequence_index_13e==1)landing();
    velocity_y_f8-=acceleration_y_100;
    if(sequence_index_13e<1 && static_cast<unsigned char>(crossed())) {
        select_sequence(1);byte_47f=0;y_f0=tenshi_surface(this);zero_motion();return;
    }
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==6){field_180=1;ring_801(120.0);field_168->dispatch_character_wave_handle(1);counter(200,60);phase_counter(50);}
        if(!frame_timer_142 && frame_index_140==8)acceleration_y_100=0.5f;
    }return;
case 418:
    landing();if(frame_index_140>=5)velocity_x_f4=static_cast<float>(velocity_x_f4-static_cast<double>(0.4f));
    if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==4){event(29);byte_47e=0;}return;
case 500: {
    landing();byte_17c=0;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=10)return;
    float p[3]={0.0f,15.0f,0.0f};
    spawn(810,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);
    spawn(810,x_ec,y_f0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1,p,3);
    effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
    effect(127,x_ec,y_f0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),-1);
    counter(200,120);phase_counter(50);layout(10.0f);return;
}
case 501: {
    landing();byte_17c=0;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=10)return;
    float p[3]={0.0f,30.0f,0.0f};
    spawn(810,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);
    spawn(810,x_ec,y_f0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1,p,3);
    effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
    effect(127,x_ec,y_f0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),-1);
    counter(200,120);phase_counter(50);layout(10.0f);return;
}

case 505:
    landing();byte_17c=4;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=10)return;
    {
        float p[3];
        double peer_y=related_170->y_f0;
        if(tenshi_surface(related_170)>=peer_y) {
            p[0]=0.0f;p[1]=0.0f;p[2]=6.0f;
            spawn(811,related_170->x_ec,related_170->y_f0,static_cast<unsigned char>(facing_104),1,p,3);
        }
        for(float n=0.0f;n<22.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(tenshi_random(360));p[1]=20.0f;p[2]=5.0f;
            spawn(811,static_cast<float>(tenshi_random(40))+n*60.0,
                  20.0-static_cast<float>(tenshi_random(40)),static_cast<unsigned char>(facing_104),1,p,3);
        }
        for(float n=0.0f;n<14.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(-static_cast<float>(tenshi_random(90))-45.0);
            p[1]=static_cast<float>(static_cast<float>(tenshi_random(10))+5.0);p[2]=2.0f;
            spawn(811,static_cast<float>(tenshi_random(60))+n*90.0,
                  20.0-static_cast<float>(tenshi_random(40)),static_cast<unsigned char>(facing_104),1,p,3);
        }
        for(float n=0.0f;n<10.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(-static_cast<float>(tenshi_random(90))-45.0);
            p[1]=static_cast<float>(static_cast<float>(tenshi_random(8))+4.0);p[2]=3.0f;
            spawn(811,static_cast<float>(tenshi_random(100))+n*120.0,
                  20.0-static_cast<float>(tenshi_random(40)),static_cast<unsigned char>(facing_104),1,p,3);
        }
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(-static_cast<float>(tenshi_random(90))-45.0);
            p[1]=static_cast<float>(static_cast<float>(tenshi_random(6))+3.0);p[2]=4.0f;
            spawn(811,static_cast<float>(tenshi_random(120))+n*160.0,
                  20.0-static_cast<float>(tenshi_random(40)),static_cast<unsigned char>(facing_104),1,p,3);
        }
        effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
        effect(127,x_ec,y_f0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),-1);
        counter(200,120);dispatch_character_wave_handle(18);phase_counter(50);layout(10.0f);
    }return;
case 520:
    landing();byte_17c=1;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        float p[3]={90.0f,30.0f,0.0f};
        spawn(815,static_cast<float>(x_ec-static_cast<float>(150*facing_104)),1000.0f,static_cast<unsigned char>(facing_104),1,p,3);
        if(byte_605>=4) {
            int direction=static_cast<unsigned char>(facing_104);
            float x=static_cast<float>(150*static_cast<signed char>(direction)+static_cast<double>(x_ec));
            spawn(815,x,1000.0f,direction,1,p,3);
        }
        counter(200,120);phase_counter(50);dispatch_character_wave_handle(11);
    }return;
case 521:
    landing();byte_17c=1;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        float p[3]={90.0f,30.0f,0.0f};
        spawn(815,static_cast<float>(static_cast<double>(150*facing_104)+x_ec),1000.0f,static_cast<unsigned char>(facing_104),1,p,3);
        if(byte_605>=4) {
            int direction=static_cast<unsigned char>(facing_104);
            float x=static_cast<float>(x_ec-static_cast<float>(150*static_cast<signed char>(direction)));
            spawn(815,x,1000.0f,direction,1,p,3);
        }
        counter(200,120);phase_counter(50);dispatch_character_wave_handle(11);
    }return;
case 525:
    landing();byte_17c=5;if(advance())set_action_and_finalize(0);
    if(sequence_index_13e!=0)return;
    if(!frame_timer_142 && frame_index_140==6) {
        float p[3];
        for(float n=0.0f;n<4.0f;n=static_cast<float>(n+1.0)) {
            p[0]=-n*90.0;p[1]=100.0f;p[2]=0.0f;
            spawn(816,tenshi_cosine(-p[0])*p[1]*facing_104+x_ec,
                  tenshi_sine(-p[0])*(p[1]*0.25)+y_f0,static_cast<unsigned char>(facing_104),1,p,3);
            ++field_834;
        }
        word_82e=static_cast<short>(60*(byte_609+2));counter(200,45);phase_counter(50);dispatch_character_wave_handle(16);
    }
    if(frame_index_140>=6)word_82e=static_cast<short>(60*(byte_609+2));
    return;
case 526:
    landing();byte_17c=5;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        field_180=1;word_830=1;counter(200,45);phase_counter(25);dispatch_character_wave_handle(11);
    }return;
case 527:
    landing();byte_17c=5;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        field_180=1;word_830=2;counter(200,60);phase_counter(50);dispatch_character_wave_handle(11);
    }return;
case 540:
    landing();byte_17c=2;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        float p[3]={-10.0f,20.0f,3.0f};
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+115.0);
        float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(820,x,y,direction,1,p,3);counter(200,120);phase_counter(50);
    }
    if(sequence_index_13e==1 && time_counter_144>=30)next_sequence_block();
    else if(sequence_index_13e==2 && time_counter_144>=30)next_sequence_block();
    return;


case 541:
    landing();byte_17c=2;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        float p[3]={-10.0f,20.0f,3.0f};
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+115.0);
        float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(820,x,y,direction,1,p,3);counter(200,120);phase_counter(50);
    }
    if(sequence_index_13e==1 && time_counter_144>=30)next_sequence_block();
    else if(sequence_index_13e==2 && time_counter_144>=30)next_sequence_block();
    return;
case 542:
    if(sequence_index_13e==2)landing();
    byte_17c=2;
    if(sequence_index_13e<2) {
        velocity_y_f8-=acceleration_y_100;
        double next_y=static_cast<double>(velocity_y_f8)+y_f0;
        if(tenshi_surface(this)>=next_y && velocity_y_f8<0.0f) {
            zero_motion();select_sequence(2);y_f0=tenshi_surface(this);return;
        }
    }
    if(sequence_index_13e<=1 && !field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(9);
    if(ENTRY(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        dispatch_character_wave_handle(7);velocity_x_f4=-4.0f;velocity_y_f8=8.0f;acceleration_y_100=0.5f;field_180=1;
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+62.0);
        float x=static_cast<float>(30*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(816,x,y,direction,1,0,0);counter(200,120);phase_counter(50);
    }return;
case 545:
    landing();byte_17c=6;if(!field_6c0)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)pair_821();
    if(sequence_index_13e==1 && time_counter_144>=12 && (time_counter_144>=40 || !byte_750)) {
        field_180=1;next_sequence_block();
    }return;
case 546:
    landing();byte_17c=6;if(!field_6c4)byte_750=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)pair_821();
    if(sequence_index_13e==1 && time_counter_144>=20 && (time_counter_144>=120 || !byte_750)) {
        field_180=1;next_sequence_block();
    }return;
case 547: {
        if(sequence_index_13e==4)landing();
        byte_17c=6;
        if(!field_6c0)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(sequence_index_13e==3 && frame_index_140>=2 && static_cast<unsigned char>(crossed())) {
            zero_motion();y_f0=tenshi_surface(this);next_sequence_block();return;
        }
        if(advance())set_action_and_finalize(0);
        if(ENTRY(4))set_action_and_finalize(9);
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)pair_821();
        if(sequence_index_13e==1 && time_counter_144>=12 &&
           (time_counter_144>=40 || !byte_750)) {
            field_180=1;next_sequence_block();return;
        }
        if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2)acceleration_y_100=0.5f;

        return;
    }
case 548: {
        if(sequence_index_13e==4)landing();
        byte_17c=6;
        if(!field_6c4)byte_750=0;
        velocity_y_f8-=acceleration_y_100;
        if(sequence_index_13e==3 && frame_index_140>=2 && static_cast<unsigned char>(crossed())) {
            zero_motion();y_f0=tenshi_surface(this);next_sequence_block();return;
        }
        if(advance())set_action_and_finalize(0);
        if(ENTRY(4))set_action_and_finalize(9);
        if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)pair_821();
        if(sequence_index_13e==1 && time_counter_144>=20 &&
           (time_counter_144>=120 || !byte_750)) {
            field_180=1;next_sequence_block();return;
        }
        if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2)acceleration_y_100=0.5f;

        return;
    }
case 560:
    landing();byte_17c=3;if(!field_6c4)byte_750=0;
    if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(ENTRY(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1) {
        counter(200,120);phase_counter(50);velocity_x_f4=10.0f;
        if(byte_607>=2)velocity_x_f4=11.5f;if(byte_607>=4)velocity_x_f4=13.0f;
        dispatch_character_wave_handle(19);effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
    }
    if(sequence_index_13e==1) {
        if(byte_607>=4)dash825();
        float delta=x_ec-related_170->x_ec;
        float distance=static_cast<float>(fabs(static_cast<double>(delta)));
        if(distance<=200.0f) {
            next_sequence_block();velocity_x_f4=25.0f;effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);return;
        }
        if(time_counter_144>=20){select_sequence(3);return;}
    }
    if(sequence_index_13e==2 && !frame_timer_142) {
        if(frame_index_140==1)dispatch_character_wave_handle(14);
        if(!frame_timer_142 && frame_index_140==2 && byte_607>=4) {
        float p[3];p[1]=20.0f;p[2]=3.0f;
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(static_cast<float>(tenshi_random(30))+n*45.0);
            if(p[0]>=0.0f && p[0]<=180.0f) {
                int direction=static_cast<unsigned char>(facing_104);
                float y=y_f0;
                float x=static_cast<float>(150*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(848,x,y,direction,1,p,3);
            } else {
                int direction=static_cast<unsigned char>(facing_104);
                float y=y_f0;
                float x=static_cast<float>(150*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(848,x,y,direction,-1,p,3);
            }
        }
            }
    }
    return;
case 561:
    landing();byte_17c=3;if(!field_6c4)byte_750=0;
    if(sequence_index_13e==2){velocity_x_f4=static_cast<float>(velocity_x_f4-0.75);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(sequence_index_13e==3){velocity_x_f4=static_cast<float>(velocity_x_f4-0.5);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(ENTRY(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1) {
        counter(200,120);phase_counter(50);velocity_x_f4=15.0f;
        if(byte_607>=2)velocity_x_f4=17.0f;if(byte_607>=4)velocity_x_f4=19.0f;
        dispatch_character_wave_handle(19);effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);
    }
    if(sequence_index_13e==1) {
        if(byte_607>=4)dash825();
        float delta=x_ec-related_170->x_ec;
        float distance=static_cast<float>(fabs(static_cast<double>(delta)));
        if(distance<=200.0f) {
            next_sequence_block();velocity_x_f4=25.0f;effect(127,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1);return;
        }
        if(time_counter_144>=40){select_sequence(3);return;}
    }
    if(sequence_index_13e==2 && !frame_timer_142) {
        if(frame_index_140==1)dispatch_character_wave_handle(14);
        if(!frame_timer_142 && frame_index_140==2 && byte_607>=4) {
        float p[3];p[1]=20.0f;p[2]=3.0f;
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(static_cast<float>(tenshi_random(30))+n*45.0);
            if(p[0]>=0.0f && p[0]<=180.0f) {
                int direction=static_cast<unsigned char>(facing_104);
                float y=y_f0;
                float x=static_cast<float>(150*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(848,x,y,direction,1,p,3);
            } else {
                int direction=static_cast<unsigned char>(facing_104);
                float y=y_f0;
                float x=static_cast<float>(150*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(848,x,y,direction,-1,p,3);
            }
        }
            }
    }
    return;
case 565:
    landing();byte_17c=7;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2){counter(200,120);phase_counter(50);event(29);byte_184=1;field_180=0;}
        if(!frame_timer_142 && frame_index_140==7){byte_184=1;field_180=0;burst848(100,3.0f);dispatch_character_wave_handle(17);}
    }return;
case 566:
    landing();byte_17c=7;
    if(!sequence_index_13e && frame_index_140>=8 && frame_index_140<=11) {
        velocity_x_f4=static_cast<float>(velocity_x_f4-4.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2){event(29);counter(200,120);phase_counter(50);byte_184=1;field_180=0;}
        if(!frame_timer_142) {
            if(frame_index_140==7){event(29);byte_184=1;field_180=0;velocity_x_f4=20.0f;}
            if(!frame_timer_142 && frame_index_140==12){byte_184=1;field_180=0;burst848(100,3.0f);dispatch_character_wave_handle(17);}
        }
    }return;
case 567:
    if(sequence_index_13e==5)landing();
    byte_17c=7;velocity_y_f8-=acceleration_y_100;
    {
        double next_y=static_cast<double>(velocity_y_f8)+y_f0;
        if(tenshi_surface(this)>=next_y && velocity_y_f8<0.0f && sequence_index_13e<5) {
            select_sequence(5);byte_47f=0;y_f0=tenshi_surface(this);zero_motion();return;
        }
    }
    if(sequence_index_13e<2 && !field_6c4)byte_750=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142) {
        float dx=static_cast<float>((related_170->x_ec-x_ec)*static_cast<double>(facing_104));
        word_734=static_cast<short>(-static_cast<short>(static_cast<int>(tenshi_atan(related_170->y_f0-y_f0,dx))));
        if(word_734<-10)word_734=-10;if(word_734>10)word_734=10;
        dispatch_character_wave_handle(29);field_180=1;counter(200,60);phase_counter(50);
        float p[3]={0.0f,0.0f,0.0f};
        if(word_738==1)
            spawn(824,48*facing_104+x_ec,y_f0+104.0,static_cast<unsigned char>(facing_104),1,p,3);
        else
            spawn(824,x_ec+48*facing_104,y_f0+104.0,static_cast<unsigned char>(facing_104),1,p,3);
    }
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)) {
        float p[3]={0.0f,0.0f,4.0f};
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+104.0);
        float x=static_cast<float>(x_ec-static_cast<float>(48*static_cast<signed char>(direction)));
        spawn(824,x,y,direction,1,p,3);
    }
    if(ENTRY(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>10 && (!byte_750 || time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)acceleration_y_100=0.6f;
    return;

case 599:
    if(word_730>0 && frame_index_140<7 && word_730<12) {
        word_734=static_cast<short>(tenshi_random_u32()%35u);
        float p[3];
        p[0]=static_cast<float>(-20-word_734);
        p[1]=static_cast<float>(static_cast<short>(tenshi_random_u32()%5u+10u));p[2]=0.0f;
        int direction=static_cast<unsigned char>(facing_104);
        float x=static_cast<float>(20*static_cast<signed char>(direction)*(word_730+1)+static_cast<double>(x_ec));
        spawn(807,x,y_f0,direction,1,p,3);
        p[0]=static_cast<float>(tenshi_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        direction=static_cast<unsigned char>(facing_104);
        x=static_cast<float>(20*static_cast<signed char>(direction)*(word_730+1)+static_cast<double>(x_ec));
        spawn(801,x,y_f0,direction,1,p,3);
        if(word_730==1){dispatch_character_wave_handle(0);counter(200,120);}
        ++word_730;
    }
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5)word_730=1;
    return;
case 600:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==8)spell_flash(0,190.0,2);
        if(!frame_timer_142 && frame_index_140==10) {
            float p[3]={0.0f,10.0f,0.0f};
            spawn(850,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);
            spawn(850,x_ec,y_f0,static_cast<unsigned char>(-static_cast<unsigned char>(facing_104)),1,p,3);
            effect127_pair();layout(10.0f);
        }
    }return;
case 601:
    landing();texture(2,2);
    if(!sequence_index_13e && field_180==1) {
        related_170->set_action_and_finalize(102);related_170->zero_motion();next_sequence_block();
        float p[3]={0.0f,4.0f,0.0f};
        float y=static_cast<float>(related_170->y_f0+100.0);
        spawn(851,related_170->x_ec,y,1,1,p,3);dispatch_character_wave_handle(51);return;
    }
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3)spell_flash(50,110.0,2);
        if(!frame_timer_142 && frame_index_140==6) {
            float p[3]={0.0f,20.0f,3.0f};burst_payload(p,12.0f,30.0,110,0.0,false,848);
        }
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3) {
        forward_hit_quantity(1750,800,1,1);related_170->field_18c=24.0f;related_170->field_190=15.0f;
        related_170->set_action_and_finalize(74);dispatch_character_wave_handle(52);layout(10.0f);related_170->word_4b2=900;
    }return;
case 602:
    texture(2,2);
    if((!sequence_index_13e && frame_index_140<=3) || sequence_index_13e==4)landing();
    if(sequence_index_13e==1) {
        float p[3];
        p[0]=static_cast<float>(static_cast<float>(tenshi_random(60))+80.0);
        p[1]=static_cast<float>(static_cast<float>(tenshi_random(10))+5.0);p[2]=2.0f;
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+166.0);
        float x=static_cast<float>(45*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(852,x,y,direction,1,p,3);
        if(time_counter_144%2==0) {
            p[1]=0.5f;p[2]=3.0f;direction=static_cast<unsigned char>(facing_104);y=static_cast<float>(y_f0+166.0);
            x=static_cast<float>(45*static_cast<signed char>(direction)+static_cast<double>(x_ec));
            spawn(852,x,y,direction,1,p,3);
        }
        if(time_counter_144>=20){next_sequence_block();velocity_y_f8=static_cast<float>(velocity_y_f8*0.25);}
    }
    if(sequence_index_13e==2 || sequence_index_13e==3) {
        velocity_y_f8-=acceleration_y_100;velocity_x_f4=static_cast<float>(velocity_x_f4-0.25);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;
        if(static_cast<unsigned char>(crossed())){select_sequence(4);zero_motion();y_f0=tenshi_surface(this);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2)spell_flash(-25,160.0,3);
        if(!frame_timer_142 && frame_index_140==9) {
            float p[3]={0.0f,25.0f,3.0f};
            burst_payload(p,18.0f,20.0,100,0.0,false,848);
            velocity_x_f4=15.0f;velocity_y_f8=35.0f;acceleration_y_100=0.5f;dispatch_character_wave_handle(50);
            p[2]=4.0f;spawn(852,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);
        }
    }return;
case 603:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==8)spell_flash(0,190.0,5);
        if(!frame_timer_142 && frame_index_140==11) {
            float p[3]={0.0f,10.0f,0.0f};
            spawn(853,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);
            effect127_pair();layout(3.0f);dispatch_character_wave_handle(10);
            p[1]=20.0f;p[2]=1.0f;burst_payload(p,8.0f,45.0,0,0.0,false,848);
        }
    }return;
case 604:
    landing();texture(2,2);
    if(word_730==1) {
        field_73c=static_cast<float>(tenshi_random(360));
        float p[3]={static_cast<float>(field_73c+180.0),300.0f,3.0f};
        spawn(854,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,p,3);
    }
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1))set_action_and_finalize(0);
    if(!sequence_index_13e) {
        if(!frame_timer_142 && frame_index_140==3){spell_flash(50,110.0,4);word_730=1;}
        if(!frame_timer_142) {
            if(frame_index_140==4)word_730=0;
            if(!frame_timer_142 && frame_index_140==6) {
                if(g_fighter_state_4b8_default==16) {
                    float p[3]={0.0f,40.0f,0.0f};
                    int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+90.0);
                    float x=static_cast<float>(120*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                    spawn(854,x,y,direction,1,p,3);
                } else {
                    float p[3];p[0]=0.0f;g_tenshi_weather_counter=0;p[1]=60.0f;p[2]=6.0f;
                    int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+90.0);
                    float x=static_cast<float>(120*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                    spawn(854,x,y,direction,1,p,3);
                    for(int n=0;n<4;++n) {
                        p[0]=static_cast<float>(tenshi_random(360));p[1]=static_cast<float>(static_cast<float>(tenshi_random(5))+5.0);p[2]=7.0f;
                        direction=static_cast<unsigned char>(facing_104);y=static_cast<float>(y_f0+90.0);
                        x=static_cast<float>(120*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                        spawn(854,x,y,direction,1,p,3);
                    }
                }
                // Native mode1 request writes only slot2 at6460EE; slots0/1 are not initialized here.
                float p[3];p[2]=1.0f;
                int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+90.0);
                float x=static_cast<float>(120*static_cast<signed char>(direction)+static_cast<double>(x_ec));
                spawn(854,x,y,direction,1,p,3);
                p[1]=20.0f;p[2]=5.0f;burst_payload(p,12.0f,30.0,120,90.0,false,854);
                dispatch_character_wave_handle(55);
            }
        }
    }return;
case 605:
    if((!sequence_index_13e && frame_index_140<=3) || sequence_index_13e==6)landing();
    texture(2,2);
    if((sequence_index_13e==0 || sequence_index_13e==1) && field_180) {
        if(++word_730>=6){word_730=0;field_180=0;}
    }
    if(sequence_index_13e==1 && time_counter_144>=20){next_sequence_block();velocity_y_f8=0.0f;acceleration_y_100=1.0f;return;}
    if(sequence_index_13e==2 && time_counter_144>=30) {
        next_sequence_block();velocity_y_f8=-50.0f;byte_184=1;dispatch_character_wave_handle(53);
        float p[3]={0.0f,0.0f,0.0f};spawn(855,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);return;
    }
    if(sequence_index_13e==3) {
        velocity_y_f8-=acceleration_y_100;double y=y_f0;
        if(tenshi_surface(this)+150.0>=y) {
            zero_motion();layout(20.0f);select_sequence(4);y_f0=static_cast<float>(tenshi_surface(this)+150.0);
            float p[3]={0.0f,25.0f,1.0f};
            for(float n=0.0f;n<18.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(static_cast<float>(tenshi_random(30))+n*20.0);
                if(p[0]>=0.0f && p[0]<=180.0f)
                    spawn(848,static_cast<float>(100*facing_104+static_cast<double>(x_ec)),tenshi_surface(this),static_cast<unsigned char>(facing_104),1,p,3);
                else
                    spawn(848,static_cast<float>(100*facing_104+static_cast<double>(x_ec)),tenshi_surface(this),static_cast<unsigned char>(facing_104),-1,p,3);
            }
            dispatch_character_wave_handle(54);return;
        }
    }
    if(sequence_index_13e==4 || sequence_index_13e==5) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){select_sequence(6);zero_motion();y_f0=tenshi_surface(this);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2)spell_flash(-25,160.0,3);
        if(!frame_timer_142 && frame_index_140==9) {
            float p[3]={0.0f,25.0f,3.0f};burst_payload(p,18.0f,20.0,100,0.0,false,848);
            velocity_x_f4=7.0f;velocity_y_f8=35.0f;acceleration_y_100=0.5f;dispatch_character_wave_handle(50);
        }
    }
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5){velocity_x_f4=-5.0f;velocity_y_f8=10.0f;acceleration_y_100=0.5f;}
    return;
case 606:
    landing();texture(2,2);
    if(sequence_index_13e==1 && time_counter_144>=36){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)) {
        layout(10.0f);dispatch_character_wave_handle(57);
        float p[3];
        for(float n=0.0f;n<12.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(n*30.0);p[1]=30.0f;p[2]=1.0f;
            if(std::sin(p[0])>0.0)
                spawn(856,x_ec,y_f0,static_cast<unsigned char>(facing_104),-1,p,3);
            else
                spawn(856,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);
        }
        p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn(856,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,p,3);
        p[2]=2.0f;spawn(856,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),-1,p,3);
        p[2]=3.0f;spawn(856,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1,p,3);
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(-72,178.0,4);
    if(sequence_index_13e>=1)field_838=900;
    return;
case 607:
    texture(2,2);
    if(sequence_index_13e==1){if(g_tenshi_weather_counter>=5)g_tenshi_weather_counter-=5;if(time_counter_144>=120){next_sequence_block();return;}}
    if(sequence_index_13e==2 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)) {
        layout(10.0f);dispatch_character_wave_handle(56);
        float p[3]={15.0f,0.0f,3.0f};int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+130.0);
        float x=static_cast<float>(90*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(857,x,y,direction,1,p,3);
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)spell_flash(-55,220.0,5);
    return;
case 657:
    texture(2,2);
    if(sequence_index_13e==1){if(g_tenshi_weather_counter>=5)g_tenshi_weather_counter-=5;if(time_counter_144>=120){next_sequence_block();return;}}
    if(sequence_index_13e==2 && time_counter_144>=60){next_sequence_block();return;}
    if(sequence_index_13e==3 || sequence_index_13e==4) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())){zero_motion();y_f0=tenshi_surface(this);select_sequence(5);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(ENTRY(1)) {
        layout(10.0f);dispatch_character_wave_handle(56);
        float p[3]={15.0f,0.0f,3.0f};int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+130.0);
        float x=static_cast<float>(90*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(857,x,y,direction,1,p,3);
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)spell_flash(-55,220.0,5);
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==1)acceleration_y_100=0.2f;
    return;
case 695:
    landing();
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
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
    if(frame_index_140>5){velocity_x_f4=static_cast<float>(velocity_x_f4-3.0);if(velocity_x_f4<0.0f)velocity_x_f4=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==5){velocity_x_f4=15.0f;event(29);byte_47e=0;}
        if(!frame_timer_142 && frame_index_140==7)velocity_x_f4=0.0f;
    }
    return;
case 710:
    if(sequence_index_13e==1 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(700);
    if(ENTRY(1)) {
        float p[3]={0.0f,0.0f,0.0f};
        int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+115.0);
        float x=static_cast<float>(80*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(900,x,y,direction,1,p,3);
    }
    return;
case 720:
    switch(sequence_index_13e) {
    case 1:
        velocity_y_f8-=acceleration_y_100;
        if(time_counter_144>=30) {
            float distance=x_ec-related_170->x_ec;
            if(tenshi_square(distance)<=400.0f){zero_motion();next_sequence_block();}
        }
        break;
    case 3:
        velocity_y_f8=-40.0f;
        if(static_cast<unsigned char>(crossed())) {
            word_732=1;word_734=static_cast<short>(static_cast<int>(x_ec/160.0));
            if(!byte_82c) {
                byte_82c=1;float p[3]={0.0f,0.0f,0.0f};
                for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
                    p[2]=n;spawn(961,static_cast<float>(n*160.0+80.0),0.0f,1,-1,p,3);
                }
            }
            zero_motion();y_f0=tenshi_surface(this);layout(5.0f);
            float p[3]={0.0f,20.0f,1.0f};
            burst_payload(p,8.0f,45.0,0,0.0,false,848);next_sequence_block();
        }
        break;
    case 4:y_f0=tenshi_surface(this);break;
    }
    if(word_732>=1) {
        // Native difficulty dispatch has no fallback definition. Domain audit pending.
        int budget,spread;
        switch(g_match_identifier) {
        case 3:budget=500;spread=7;break;
        case 2:budget=375;spread=7;break;
        case 1:budget=250;spread=6;break;
        case 0:budget=150;spread=2;break;
        }
        if(word_732%10==1 && word_736<=spread) {
            dispatch_character_wave_handle(10);layout(4.0f);
            if(word_736==0) samples_7a4[word_734]=0.0f;
            else {
                if(word_734+word_736<=7)samples_7a4[word_734+word_736]=static_cast<float>(tenshi_random(budget));
                if(word_734-word_736>=0)samples_7a4[word_734-word_736]=static_cast<float>(tenshi_random(budget));
            }
            ++word_736;
        }
        ++word_732;
    }
    if(advance()) {
        flip();
        if(tenshi_random(100)>50u || related_170->word_174<=0) {
            set_action_and_finalize(701);
            field_780=static_cast<float>(-5.0-static_cast<float>(tenshi_random(15)));
            field_784=10.0f;field_788=0.6f;
        } else {set_action_and_finalize(720);return;}
    }
    if(!time_counter_144) {
        if(ENTRY(1)){flip();velocity_x_f4=field_780;velocity_y_f8=field_784;acceleration_y_100=field_788;time_counter_144=0;}
        if(ENTRY(2))zero_motion();
    }
    return;
case 730:
    if(sequence_index_13e==1) {
        if(word_730%5==0 && field_73c<=5.0f) {
            float p[3]={field_73c,0.0f,0.0f};
            spawn(920,(static_cast<double>(static_cast<float>(tenshi_random(100)))+200.0+200.0*field_73c)*facing_104+x_ec,
                  -100.0f,static_cast<unsigned char>(facing_104),1,p,3);
            p[0]=static_cast<float>(field_73c+6.0);p[1]=0.0f;p[2]=0.0f;
            spawn(920,x_ec-(static_cast<double>(static_cast<float>(tenshi_random(100)))+200.0+200.0*field_73c)*facing_104,
                  -100.0f,static_cast<unsigned char>(facing_104),1,p,3);field_73c=static_cast<float>(field_73c+1.0);
        }
        if(word_730>=120){next_sequence_block();return;}
        ++word_730;
    }
    if(advance())set_action_and_finalize(731);
    return;
case 731:
    landing();
    if(advance()) {
        flip();set_action_and_finalize(701);
        if(static_cast<unsigned char>(facing_104)==1) {
            if(x_ec>=480.0f)field_780=static_cast<float>(-5.0-static_cast<float>(tenshi_random(15)));
            else field_780=static_cast<float>(static_cast<float>(tenshi_random(10))+10.0);
        } else {
            if(x_ec<=800.0f)field_780=static_cast<float>(-5.0-static_cast<float>(tenshi_random(15)));
            else field_780=static_cast<float>(static_cast<float>(tenshi_random(10))+10.0);
        }
        field_784=15.0f;field_788=0.6f;
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        float p[3]={-10.0f,20.0f,8.0f};int direction=static_cast<unsigned char>(facing_104);
        float y=static_cast<float>(y_f0+115.0);
        float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(x_ec));
        spawn(920,x,y,direction,1,p,3);
    }
    if((sequence_index_13e==1 && time_counter_144>=180) || (sequence_index_13e==2 && time_counter_144>=120))next_sequence_block();
    return;
case 740:
    y_f0=tenshi_surface(this);
    if(advance()) {
        if(g_match_identifier!=0)set_action_and_finalize(741);else set_action_and_finalize(700);
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10) {
        dispatch_character_wave_handle(10);
        if(!byte_82c) {
            byte_82c=1;float p[3]={0.0f,0.0f,0.0f};
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
                p[2]=n;spawn(960,static_cast<float>(n*160.0+80.0),0.0f,1,-1,p,3);
            }
        }
        int start_index=static_cast<int>(x_ec/160.0);
        int budget;
        switch(g_match_identifier){case 3:budget=350;break;case 2:budget=350;break;case 1:budget=350;break;case 0:budget=250;break;}
        int index=start_index;
        float *height=&samples_7a4[0];
        for(int count=8;count;--count) {
            *height=static_cast<float>(tenshi_random(150));
            field_73c=static_cast<float>(budget-125*abs(index));
            *height=field_73c+*height;
            if(*height<0.0f)*height=0.0f;
            ++height;--index;
        }
        if(g_tenshi_weather_selector!=5 || byte_55a!=2)return;
        field_740=15.0f;
    }
    if(g_tenshi_weather_selector==5 && byte_55a==2) {
        field_828+=field_740;field_740=static_cast<float>(field_740-1.0);
        if(field_740<0.0f)field_740=0.0f;
        if(field_828>=800.0f)field_828=800.0f;
        event_owner()->pair(0.0f,field_828);
    }
    return;
case 741:
    y_f0=tenshi_surface(this);
    if(sequence_index_13e==1) {
        int interval,duration;float speed;
        switch(g_match_identifier) {
        case 3:interval=4;speed=4.5f;duration=120;break;
        case 2:interval=5;speed=4.0f;duration=90;break;
        case 1:interval=7;speed=3.0f;duration=60;break;
        case 0:interval=15;speed=2.0f;duration=60;break;
        }
        if(time_counter_144%interval==0) {
            dispatch_character_wave_handle(1);field_73c=static_cast<float>(field_73c+20.0);
            float p[3];p[0]=field_73c;p[1]=static_cast<float>(static_cast<float>(tenshi_random(4))+speed);p[2]=0.0f;
            int direction=static_cast<unsigned char>(facing_104);float y=static_cast<float>(y_f0+290.0);
            float x=static_cast<float>(40*static_cast<signed char>(direction)+static_cast<double>(x_ec));
            spawn(930,x,y,direction,1,p,3);
            p[0]=static_cast<float>(field_73c+180.0);p[1]=static_cast<float>(static_cast<float>(tenshi_random(4))+speed);
            direction=static_cast<unsigned char>(facing_104);y=static_cast<float>(y_f0+290.0);
            x=static_cast<float>(40*static_cast<signed char>(direction)+static_cast<double>(x_ec));
            spawn(930,x,y,direction,1,p,3);
        }
        if(time_counter_144>=duration){next_sequence_block();return;}
    }
    if(sequence_index_13e==2 && time_counter_144>=30){next_sequence_block();return;}
    if(advance()){set_action_and_finalize(700);flip();}
    if(ENTRY(1) && !word_730){word_730=1;time_counter_144=0;}
    return;
case 750:
    if(word_738==5 && time_counter_144%5==0)layout(5.0f);
    if(!sequence_index_13e) {
        if(!time_counter_144 && !frame_timer_142 && !frame_index_140) {
            float *height=&samples_7a4[0];
            for(int count=8;count;--count) {
                *height=200.0f;related_170->y_f0=200.0f;
                related_170->velocity_y_f8=0.0f;related_170->set_action_and_finalize(0);
                ++height;field_828=200.0f;
            }
        }
        y_f0=static_cast<float>(tenshi_surface(this)+200.0);x_ec=800.0f;
        if(++word_730>=120) {
            samples_7a4[0]=static_cast<float>(samples_7a4[0]-1.0);samples_7a4[1]=static_cast<float>(samples_7a4[1]-1.0);
            samples_7a4[2]=static_cast<float>(samples_7a4[2]-1.0);samples_7a4[3]=static_cast<float>(samples_7a4[3]-1.0);
            samples_7a4[4]=static_cast<float>(samples_7a4[4]-1.0);samples_7a4[5]=static_cast<float>(samples_7a4[5]-1.0);
            samples_7a4[6]=static_cast<float>(samples_7a4[6]-1.0);samples_7a4[7]=static_cast<float>(samples_7a4[7]-1.0);
            field_828=samples_7a4[0];if(field_828<0.0f)field_828=0.0f;
            event_owner()->pair(0.0f,-field_828);
            if(samples_7a4[0]<=0.0f) {
                samples_7a4[0]=0.0f;samples_7a4[1]=0.0f;samples_7a4[2]=0.0f;samples_7a4[3]=0.0f;
                samples_7a4[4]=0.0f;samples_7a4[5]=0.0f;samples_7a4[6]=0.0f;samples_7a4[7]=0.0f;
                next_sequence_block();field_828=0.0f;event_owner()->pair(0.0f,-0.0f);word_730=0;return;
            }
        }
        if(word_730==120){tenshi_fade_out(0xffffffffu,90);tenshi_play_bgm("data/bgm/st06.ogg");reinterpret_cast<PostSequenceTransitionView *>(g_info_manager)->publish_transition_effect_at_46e130(480.0f);}
    }
    if(sequence_index_13e==1) {
        if(field_74c>0.0f)field_74c=static_cast<float>(field_74c-1.0);
        if(!time_counter_144) {
            finalize(-1);byte_655=1;event_owner()->pair_mode(15,1);copy_health();
            word_76a=1;word_76c=0;word_76e=0;byte_4e9=0;byte_4ec=1;
            word_766=0;word_768=120;word_764=0;event(23);word_736=1;
        }
        y_f0=static_cast<float>(tenshi_surface(this)+200.0);x_ec=800.0f;
    }
    if(sequence_index_13e==2) {
        word_768=240;word_76a=0;word_738=0;
        y_f0=static_cast<float>(tenshi_surface(this)+200.0);x_ec=800.0f;
        if(byte_113<=252)byte_113+=3;
        else {byte_113=255;select_sequence(1);return;}
    }
    if(advance())set_action_and_finalize(700);
    return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=7)return;
    byte_655=1;finalize(-1);
    if(g_tenshi_weather_selector==5)event_owner()->trigger(14);else texture(2,-1);
    copy_health();word_76c=0;word_76a=1;
    word_766=0;word_768=0;word_764=0;event(23);
    return;
case 771:
    if(sequence_index_13e==1) {
        if(byte_113>=3)byte_113-=3;
        else {byte_113=0;set_action_and_finalize(750);select_sequence(2);return;}
    }
    if(advance())set_action_and_finalize(700);
    if(ENTRY(1)) {
        byte_655=1;finalize(-1);
        if(g_tenshi_weather_selector==5)event_owner()->trigger(14);
        copy_health();word_76c=0;word_76a=1;word_766=0;word_768=0;word_764=0;event(23);
    }
    return;
case 780:
    if(!sequence_index_13e) {
        velocity_y_f8=-5.0f;
        if(static_cast<unsigned char>(crossed())) {
            layout(5.0f);float p[3]={0.0f,20.0f,1.0f};dispatch_character_wave_handle(2);
            burst_payload(p,8.0f,45.0,0,0.0,false,848);
            next_sequence_block();zero_motion();y_f0=tenshi_surface(this);return;
        }
        if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(50);
    }
    if(sequence_index_13e==2 && time_counter_144>=20){next_sequence_block();return;}
    if(advance())set_action_and_finalize(700);
    return;
case 781:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==11){effect127_pair();layout(10.0f);dispatch_character_wave_handle(10);}
    return;
case 782:
    if(sequence_index_13e==1 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9){effect127_pair();layout(10.0f);dispatch_character_wave_handle(12);}
    return;
case 788:
    shared_first(1,640.0f);shared_second(1,static_cast<float>(word_730));word_730+=4;
    if(word_730>=480){word_730=480;word_78c=1;}
    return;
case 795:
    {
    if(!sequence_index_13e) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
            next_sequence_block();y_f0=tenshi_surface(this);zero_motion();layout(5.0f);
            float p[3]={0.0f,20.0f,1.0f};burst_payload(p,8.0f,45.0,0,0.0,false,848);
            dispatch_character_wave_handle(2);
        }
    }
    if(sequence_index_13e==2 || sequence_index_13e==3) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
            zero_motion();y_f0=tenshi_surface(this);select_sequence(4);event(30);
            return;
        }
    }
    if(advance())set_action_and_finalize(700);
    if(ENTRY(2)){velocity_y_f8=6.0f;acceleration_y_100=0.5f;}
    return;
    }
case 797:
    {
    if(!sequence_index_13e) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
            next_sequence_block();y_f0=tenshi_surface(this);zero_motion();layout(5.0f);
            float p[3]={0.0f,20.0f,1.0f};burst_payload(p,8.0f,45.0,0,0.0,false,848);
            dispatch_character_wave_handle(2);
        }
    }
    if(sequence_index_13e==2 || sequence_index_13e==3) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
            zero_motion();y_f0=tenshi_surface(this);select_sequence(4);event(30);
            x_ec=480.0f;
            return;
        }
    }
    if(advance())set_action_and_finalize(0);
    if(ENTRY(2)){velocity_y_f8=6.0f;acceleration_y_100=0.5f;}
    return;
    }
case 798:
    {
    if(!sequence_index_13e) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
            next_sequence_block();y_f0=tenshi_surface(this);zero_motion();layout(5.0f);
            float p[3]={0.0f,20.0f,1.0f};burst_payload(p,8.0f,45.0,0,0.0,false,848);
            dispatch_character_wave_handle(2);
        }
    }
    if(sequence_index_13e==2 || sequence_index_13e==3) {
        velocity_y_f8-=acceleration_y_100;
        if(static_cast<unsigned char>(crossed())) {
            zero_motion();y_f0=tenshi_surface(this);select_sequence(4);event(30);
            x_ec=800.0f;
            return;
        }
    }
    if(advance())set_action_and_finalize(700);
    if(ENTRY(2)){velocity_y_f8=6.0f;acceleration_y_100=0.5f;}
    return;
    }

    default: common_update(); return;
    }
    advance();
}
#undef B
#undef C
#undef S
#undef U
#undef I
#undef F
}
