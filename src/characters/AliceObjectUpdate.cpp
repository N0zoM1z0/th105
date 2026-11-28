#include "characters/AliceObjectUpdate.hpp"

namespace th105 {

#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define RF(n) static_cast<float>(R(n))
#define TURN_TO_OWNER() do { layer_33c = -1; if (x_ec - owner_348->x_ec > 0.0f) facing_104 = -1; if (x_ec - owner_348->x_ec < 0.0f) facing_104 = 1; field_370 = 0.0f; } while (0)
#define RETIRE() do { --lifetime_330; return; } while (0)
#define MOVE() do { x_ec = facing_104 * velocity_x_f4 + x_ec; y_f0 = velocity_y_f8 + y_f0; } while (0)
#define FINISH() do { if (advance_frame()) --lifetime_330; return; } while (0)

void AliceObjectUpdateView::update_action_state() {
float nextY;
switch(action_id_13c) {
case 800: {

    if(retire_on_collision5()) return;
    if(sequence_index_13e<=6) {
        if(frame_index_140==0) {
            if(emit_or_retire(0,0,4)) return;
            if(field_180!=0) {next_sequence_frame();float packet[3]={0.0f,0.0f,static_cast<float>(sequence_index_13e+7)};spawn_unparented(800,x_ec,y_f0,facing_104,1,packet,3);return;}
            if(is_oob()) RETIRE();motion_004.set_components(params_340[0],params_340[1]);MOVE();
        }
        if(frame_index_140==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(byte_113<=20) RETIRE();byte_113-=20;}
    }
    else {scale_x_11c+=static_cast<double>(0.02f);scale_y_120=scale_x_11c;if(byte_113<=10) RETIRE();byte_113-=10;}
    FINISH();


}
case 801: {
 {
    if(sequence_index_13e<=6) {
        if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=5) select_sequence(6);

        if(owner_348->action_id_13c<=399 || owner_348->action_id_13c>=410) {if(sequence_index_13e<=4) {select_sequence(5);TURN_TO_OWNER();}}
        else if(((owner_348->action_id_13c==404 && owner_348->sequence_index_13e==8) || (owner_348->action_id_13c==405 && owner_348->sequence_index_13e==8) || (owner_348->action_id_13c==406 && owner_348->sequence_index_13e==8)) && sequence_index_13e<=4) {select_sequence(5);TURN_TO_OWNER();}
        switch(sequence_index_13e) {
        case 0:
            field_370+=velocity_x_f4;field_374+=velocity_y_f8;velocity_x_f4*=0.75;velocity_y_f8=static_cast<float>(0.75*velocity_y_f8);if(time_counter_144>=10) select_sequence(2);
            x_ec=static_cast<float>((static_cast<double>(field_370)+params_340[0])*facing_104+owner_348->x_ec);y_f0=static_cast<float>(static_cast<double>(params_340[1])+field_374+owner_348->y_f0);break;
        case 2:
            x_ec=static_cast<float>((static_cast<double>(field_370)+params_340[0])*facing_104+owner_348->x_ec);y_f0=static_cast<float>(static_cast<double>(params_340[1])+field_374+owner_348->y_f0);break;
        case 3:
            if(time_counter_144%3==0 && word_364<=6) {
                owner_348->dispatch_character_wave_handle(0);++word_364;AliceUpdateOwnerView *target = target_170;field_378=-atan2_degrees(static_cast<float>(target->y_f0+100.0-y_f0),static_cast<float>((target->x_ec-static_cast<double>(x_ec))*facing_104));
                if(params_340[2]==1.0f) {if(field_378<20.0f) field_378=20.0f;if(field_378>60.0f) field_378=60.0f;}else {if(field_378<-20.0f) field_378=-20.0f;if(field_378>20.0f) field_378=20.0f;}
                float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(20))+field_378-10.0);packet[1]=12.5f;packet[2]=static_cast<float>(word_364%7);
                spawn_unparented(800,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);packet[2]=static_cast<float>(static_cast<double>(word_364%7)+7.0);
                spawn_unparented(800,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(0);
            }
            if(time_counter_144>=30) next_sequence_block();
            x_ec=static_cast<float>((static_cast<double>(field_370)+params_340[0])*facing_104+owner_348->x_ec);y_f0=static_cast<float>(static_cast<double>(params_340[1])+field_374+owner_348->y_f0);break;
        case 5:if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
        case 6:
            if(is_vx_over5()) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;break;
        }
    }
    if(sequence_index_13e>=7 && sequence_index_13e<=12) {
        if(((owner_348->action_id_13c>49 && owner_348->action_id_13c<150) || word_174<=-500) && sequence_index_13e<=9) {select_sequence(6);return;}
        if(owner_348->action_id_13c!=402 && sequence_index_13e<=9) {select_sequence(5);TURN_TO_OWNER();}
        switch(sequence_index_13e) {
        case 7:
            if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==7) {velocity_x_f4=27.5f;velocity_y_f8=0.0f;}if(time_counter_144>=4) {next_sequence_block();return;}x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);break;
        case 8:case 9:
            velocity_x_f4-=4.0;if(velocity_x_f4<4.0f) velocity_x_f4=4.0f;
            if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==9) {float packet[3]={0.0f,0.0f,10.0f};spawn_parented(801,static_cast<float>(static_cast<double>(45*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);}
            if(sequence_index_13e==9 && time_counter_144>=40) {select_sequence(5);TURN_TO_OWNER();}x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);break;
        case 10:
            if(!related_34c) RETIRE();if(related_34c->sequence_index_13e==9) {if(field_180!=0) {if(word_364>=7) {word_364=0;field_180=0;}else ++word_364;}x_ec=static_cast<float>(static_cast<double>(45*facing_104)+related_34c->x_ec);y_f0=static_cast<float>(related_34c->y_f0+5.0);}
            else {byte_184=0;scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(scale_x_11c<=0.01f) RETIRE();}break;
        case 11: {
            rotation_12c+=15.0;if(!related_34c) RETIRE();x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;
            if(related_34c->byte_184<=0) {scale_y_120*=static_cast<double>(0.65f);if(scale_y_120<=0.01f) RETIRE();}else {scale_y_120+=static_cast<double>(0.3f);if(scale_y_120>3.0f) scale_y_120=3.0f;}break;
        }
        case 12: {
            if(!related_34c) RETIRE();x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;scale_y_120=static_cast<float>(lookup_orientation_sine(3*time_counter_144)*6.0);scale_x_11c=scale_y_120;if(byte_113<9) RETIRE();byte_113-=9;break;
        }
        }
    }
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) {TURN_TO_OWNER();}return;
}


}
case 802: {
 {
    if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=5) select_sequence(6);
    if((owner_348->action_id_13c<=399 || owner_348->action_id_13c>=410) && sequence_index_13e<=4) {select_sequence(5);TURN_TO_OWNER();}
    if(((owner_348->action_id_13c==404 && owner_348->sequence_index_13e==8) || (owner_348->action_id_13c==406 && owner_348->sequence_index_13e==8)) && sequence_index_13e<=4) {select_sequence(5);TURN_TO_OWNER();}
    switch(sequence_index_13e) {
    case 0:
        field_370+=velocity_x_f4;field_374+=velocity_y_f8;velocity_x_f4*=0.75;velocity_y_f8=static_cast<float>(0.75*velocity_y_f8);if(time_counter_144>=10) select_sequence(1);
        x_ec=static_cast<float>((static_cast<double>(field_370)+params_340[0])*facing_104+owner_348->x_ec);y_f0=static_cast<float>(static_cast<double>(params_340[1])+field_374+owner_348->y_f0);break;
    case 1:
        if(owner_348->sequence_index_13e>=5) next_sequence_block();
        x_ec=static_cast<float>((static_cast<double>(field_370)+params_340[0])*facing_104+owner_348->x_ec);y_f0=static_cast<float>(static_cast<double>(params_340[1])+field_374+owner_348->y_f0);break;
    case 2:
        x_ec=static_cast<float>((static_cast<double>(field_370)+params_340[0])*facing_104+owner_348->x_ec);y_f0=static_cast<float>(static_cast<double>(params_340[1])+field_374+owner_348->y_f0);break;
    case 3:
        if(time_counter_144%3==0 && word_364<=12) {
            owner_348->dispatch_character_wave_handle(time_counter_144%3);++word_364;AliceUpdateOwnerView *target = owner_348->target_170;field_378=-atan2_degrees(static_cast<float>(target->y_f0+100.0-y_f0),static_cast<float>((target->x_ec-static_cast<double>(x_ec))*facing_104));if(field_378<-20.0f) field_378=-20.0f;if(field_378>20.0f) field_378=20.0f;
            float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(20))+field_378-10.0);packet[1]=17.5f;packet[2]=static_cast<float>(word_364%7);spawn_unparented(800,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);packet[2]=static_cast<float>(static_cast<double>(word_364%7)+7.0);spawn_unparented(800,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(0);
        }
        if(time_counter_144>=40) next_sequence_block();
        x_ec=static_cast<float>((static_cast<double>(field_370)+params_340[0])*facing_104+owner_348->x_ec);y_f0=static_cast<float>(static_cast<double>(params_340[1])+field_374+owner_348->y_f0);break;
    case 5:if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    case 6:
        if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;break;
    }
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) {TURN_TO_OWNER();}return;
}


}
case 803: {
 {
    if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=4) select_sequence(5);
    if((owner_348->action_id_13c<=399 || owner_348->action_id_13c>=410) && sequence_index_13e<=3) {select_sequence(4);TURN_TO_OWNER();}
    switch(sequence_index_13e) {
    case 0:
        if(time_counter_144>60 || absolute_scalar_float(target_170->x_ec-x_ec)<300.0f) ++word_366;
        if(word_366>0) {velocity_x_f4-=4.0;if(velocity_x_f4<0.0f) {velocity_x_f4=0.0f;next_sequence_block();return;}}MOVE();break;
    case 2:
        if(time_counter_144%3==0 && word_364<=7) {
            owner_348->dispatch_character_wave_handle(time_counter_144%3);++word_364;if(field_378<-20.0f) field_378=-20.0f;if(field_378>20.0f) field_378=20.0f;
            float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(60))-30.0);packet[1]=30.0f;packet[2]=static_cast<float>(word_364%7);spawn_unparented(804,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);packet[2]+=7.0;spawn_unparented(800,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(0);
        }if(time_counter_144>=30) next_sequence_block();break;
    case 4:if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    case 5:
        if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;break;
    case 6:if(update_flight_state(5)) return;break;
    }
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) {TURN_TO_OWNER();}return;
}


}
case 804: {

    if(field_180==5) RETIRE();
    if(sequence_index_13e<=6) {
        if(frame_index_140==0) {
            params_340[1]-=2.0;if(params_340[1]<0.5f) params_340[1]=0.5f;if(emit_repeated(0,0,3)) RETIRE();if(time_counter_144>=30) {next_sequence_frame();return;}
            if(field_180!=0) {next_sequence_frame();params_340[1]=0.5f;for(int count=4;count!=0;--count) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(30))+10.0);packet[2]=static_cast<float>(sequence_index_13e+7);spawn_unparented(804,x_ec,y_f0,facing_104,1,packet,3);}return;}
            if(x_ec>1380.0f || x_ec<-100.0 || y_f0>1000.0 || y_f0<-160.0) RETIRE();motion_004.set_components(params_340[0],params_340[1]);MOVE();
        }
        if(frame_index_140==1) {params_340[1]-=2.0;if(params_340[1]<0.5f) params_340[1]=0.5f;motion_004.set_components(params_340[0],params_340[1]);MOVE();scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(byte_113<=20) RETIRE();byte_113-=20;}
    }
    else {params_340[1]-=2.0;if(params_340[1]<0.5f) params_340[1]=0.5f;motion_004.set_components(params_340[0],params_340[1]);MOVE();scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(byte_113<=word_364) RETIRE();byte_113 -= static_cast<unsigned char>(word_364);}
    FINISH();


}
case 805: {
 {
    if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=5) select_sequence(6);
    short phase=sequence_index_13e;if(phase!=6 && phase!=7 && (word_174<-500 || owner_348->word_174<=0)) select_sequence(6);
    switch(sequence_index_13e) {
    case 0: {
        motion_004.set_components(params_340[0],params_340[1]);params_340[1]-=2.0;if(params_340[1]<0.0f) {params_340[1]=0.0f;next_sequence_block();return;}MOVE();if(y_f0<stage_surface_height()) y_f0=stage_surface_height();break;
    }
    case 1: {
        if(time_counter_144>=60) {next_sequence_block();return;}if((owner_348->action_id_13c==410 || owner_348->action_id_13c==411 || owner_348->action_id_13c==412 || owner_348->action_id_13c==414 || owner_348->action_id_13c==415 || owner_348->action_id_13c==416) && owner_348->sequence_index_13e==1) {next_sequence_block();word_366=1;return;}break;
    }
    case 3:
        if(word_366==1) {
            if(time_counter_144==0) {owner_348->dispatch_character_wave_handle(1);++word_364;AliceUpdateOwnerView *target = target_170;field_378=-atan2_degrees(static_cast<float>(target->y_f0+100.0-y_f0),static_cast<float>((target->x_ec-static_cast<double>(x_ec))*facing_104));if(field_378<-80.0f) field_378=-80.0f;if(field_378>80.0f) field_378=80.0f;float packet[3]={field_378,0.0f,0.0f};spawn_parented(807,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);}
            if(time_counter_144>=90) next_sequence_block();
        }else {
            if(time_counter_144%3==0 && word_364<=7) {owner_348->dispatch_character_wave_handle(0);++word_364;AliceUpdateOwnerView *target = target_170;field_378=-atan2_degrees(static_cast<float>(target->y_f0+100.0-y_f0),static_cast<float>((target->x_ec-static_cast<double>(x_ec))*facing_104));if(field_378<-80.0f) field_378=-80.0f;if(field_378>80.0f) field_378=80.0f;
                float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(20))+field_378-10.0);packet[1]=12.5f;packet[2]=static_cast<float>(word_364%7);spawn_unparented(806,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);packet[2]=static_cast<float>(static_cast<double>(word_364%7)+7.0);spawn_unparented(806,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);
            }if(time_counter_144>=30) next_sequence_block();
        }break;
    case 5:if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    case 6:
        if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<10) RETIRE();byte_113-=10;break;
    case 7: {
        if(owner_348->action_id_13c==609 && owner_348->sequence_index_13e==1 && related_34c) {if((related_34c->action_id_13c==805 && related_34c->sequence_index_13e==8) || related_34c->action_id_13c==859) {set_action(859);select_sequence(4);byte_184=1;word_364=0;return;}}
        if(update_flight_state(6)) return;break;
    }
    case 8: {
        if(owner_348->word_174<=0 || target_170->word_174<=0) {--owner_348->word_7a6;owner_348->doll_flag_7d1[word_388]=0;select_sequence(6);return;}
        if(owner_348->doll_flag_7d1[word_388]!=0) {next_sequence_block();owner_348->doll_flag_7d1[word_388]=0;return;}
        owner_348->doll_x_7b0[word_388]=x_ec;owner_348->doll_y_7c0[word_388]=y_f0;
        if(owner_348->action_id_13c==560 && owner_348->sequence_index_13e==1) {--owner_348->word_7a6;set_action(825);select_sequence(1);time_counter_144=0;return;}
        if(owner_348->action_id_13c==609 && owner_348->sequence_index_13e==1) {--owner_348->word_7a6;set_action(859);select_sequence(1);word_364=0;byte_184=1;time_counter_144=0;return;}break;
    }
    case 10:if(time_counter_144>=60) {select_sequence(5);return;}break;
    }
    if(advance_frame()) --lifetime_330;
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) {
        unsigned char level=static_cast<unsigned char>(owner_348->byte_607);short maximum=1;if(level==2 || owner_348->byte_60f==2) maximum=2;if(level==3 || owner_348->byte_60f==3) maximum=2;if(level==4 || owner_348->byte_60f==4) maximum=3;
        short index=owner_348->word_7a6;if(index<=maximum) {word_388=index;++owner_348->word_7a6;owner_348->doll_x_7b0[word_388]=x_ec;owner_348->doll_y_7c0[word_388]=y_f0;select_sequence(8);}
    }return;
}


}
case 806: {

    if(field_180==5) RETIRE();
    if(sequence_index_13e<=6) {
        if(frame_index_140==0) {if(emit_repeated(0,0,4)) RETIRE();if(field_180!=0 || time_counter_144>60) {next_sequence_frame();float packet[3]={0.0f,0.0f,static_cast<float>(sequence_index_13e+7)};spawn_unparented(806,x_ec,y_f0,facing_104,1,packet,3);return;}
            if((x_ec>1380.0f || x_ec<-100.0f || y_f0>1000.0f || y_f0<-160.0f)) RETIRE();motion_004.set_components(params_340[0],params_340[1]);MOVE();}
        if(frame_index_140==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(byte_113<=20) RETIRE();byte_113-=20;}
    }else {scale_x_11c+=static_cast<double>(0.02f);scale_y_120=scale_x_11c;if(byte_113<=10) RETIRE();byte_113-=10;}FINISH();


}
case 807: {
 {
    if(field_180==5) RETIRE();
    if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && frame_index_140<=1) {for(float index=0.0f;index<12.0f;index+=1.0) emit_effect(201,static_cast<float>(lookup_orientation_cosine_quantized_abs(rotation_12c)*(index*130.0)*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(rotation_12c)*130.0+y_f0),facing_104,1);RETIRE();}
    short frame=frame_index_140;if(frame<=1 && (!related_34c || related_34c->sequence_index_13e==6)) {select_frame(2);return;}
    if(frame==0 && time_counter_144>=20) {scale_y_120+=static_cast<double>(0.15f);if(scale_y_120>=2.0f) {byte_184=4;scale_y_120=2.0f;next_sequence_frame();}}
    if(frame_index_140==1) {advance_six(0);if(field_180!=0 && ++word_364>=7) {word_364=0;field_180=0;}}
    if(frame_index_140==2) {byte_184=0;scale_y_120*=static_cast<double>(0.9f);if(frame_timer_142>=60) RETIRE();}FINISH();
}


}
case 810: {

    if(sequence_index_13e<=2 && (emit_repeated(0,1,3) || word_174<=-750)) select_sequence(3);
    if(sequence_index_13e==0) {motion_004.set_components(params_340[0],params_340[1]);params_340[0]-=2.0;params_340[1]-=1.0;if(params_340[1]<0.0f) {params_340[1]=0.0f;next_sequence_block();return;}MOVE();if(y_f0<0.0f) y_f0=0.0f;}
    if(sequence_index_13e==1) {
        if(time_counter_144==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(810,x_ec,y_f0,facing_104,1,packet,3);}if(time_counter_144%15==0) owner_348->dispatch_character_wave_handle(4);advance_six(0);if(field_178>0) {select_sequence(3);return;}
        if(field_180!=0 && ++word_364>=4) {word_364=0;field_180=0;}
        if(time_counter_144>=10*(owner_348->byte_604+8) || byte_184<=0) {next_sequence_block();layer_33c = -1;if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;return;}
    }
    if(sequence_index_13e==2) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==3) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==4 && update_flight_state(3)) return;
    if(sequence_index_13e==5) {
        rotation_12c+=25.0;if(!related_34c) RETIRE();
        if(related_34c->sequence_index_13e!=1) {if(byte_113<20) RETIRE();scale_x_11c+=static_cast<double>(0.1f);byte_113-=20;byte_112-=20;byte_111-=20;}
        else {scale_x_11c+=static_cast<double>(0.1f);if(scale_x_11c>3.0f) scale_x_11c=2.5f;scale_y_120=scale_x_11c;if(byte_113<=225) byte_113+=30;else byte_113=255;}
    }
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) {TURN_TO_OWNER();}return;


}
case 811: {

    if(sequence_index_13e==0) {
        if(emit_repeated(0,1,3) || word_174<=-500) select_sequence(1);
        if(time_counter_144==0) {float packet[3]={0.0f,0.0f,3.0f};spawn_parented(811,x_ec,y_f0,facing_104,1,packet,3);}advance_six(0);
        if(word_364==0) {params_340[1]-=0.5;if(params_340[1]<0.0f) {params_340[1]=0.0f;word_364=1;}motion_004.set_components(params_340[0],params_340[1]);MOVE();}
        if(word_364==1 && ++word_366>=30) {if(owner_348->byte_608>=3) {byte_184=1;field_180=0;}word_364=2;}
        if(word_364==2) {
            params_340[0]=-atan2_degrees(static_cast<float>(owner_348->y_f0+100.0-y_f0),owner_348->x_ec-x_ec);params_340[1]+=0.5;if(field_370>20.0f) field_370=20.0f;motion_004.set_components(params_340[0],params_340[1]);AliceUpdateOwnerView *owner=owner_348;x_ec=velocity_x_f4+x_ec;nextY=velocity_y_f8+y_f0;y_f0=nextY;if(absolute_scalar_float(owner->x_ec-x_ec)<20.0f && absolute_scalar_float(static_cast<float>(owner->y_f0+100.0-nextY))<20.0f) RETIRE();
        }
    }
    if(sequence_index_13e==1) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<10) RETIRE();byte_113-=10;}
    if(sequence_index_13e==2 && update_flight_state(1)) return;
    if(sequence_index_13e==3) {if(!related_34c) RETIRE();if(related_34c->sequence_index_13e!=0) {if(byte_113<20) RETIRE();scale_x_11c+=static_cast<double>(0.1f);byte_113-=20;byte_112-=20;byte_111-=20;}else {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;nextY=static_cast<float>(scale_x_11c+static_cast<double>(0.1f));scale_x_11c=nextY;if(nextY>2.5f) scale_x_11c=2.0f;scale_y_120=scale_x_11c;if(byte_113<=225) byte_113+=30;else byte_113=255;}rotation_12c+=25.0;}FINISH();


}
case 815: {

    if(field_180==5) RETIRE();
    switch(sequence_index_13e) {
    case 0: {
        if(emit_repeated(0,1,4)) RETIRE();if(static_cast<double>(y_f0)+velocity_y_f8<=stage_surface_height() || word_174<0) {publish_battle_layout_scalar(5.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(815,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(6);y_f0=stage_surface_height();velocity_y_f8=-velocity_y_f8;velocity_x_f4*=static_cast<double>(0.2f);return;}
        if((x_ec>1380.0f || x_ec<-100.0f || y_f0>1000.0f || y_f0<-160.0f)) RETIRE();velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    case 1:rotation_12c+=15.0;if(byte_113<=5) RETIRE();byte_113-=5;velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    case 2:advance_six(0);scale_x_11c-=static_cast<double>(0.01f);scale_y_120=scale_x_11c;if(byte_113>10) {byte_113-=10;byte_111-=10;byte_110-=10;}else RETIRE();break;
    case 3:scale_x_11c+=static_cast<double>(0.02f);scale_y_120=scale_x_11c;if(time_counter_144>0) {if(byte_110<=20) {byte_111-=20;byte_110-=20;}else {if(byte_113<=20) RETIRE();byte_111=0;byte_110=0;byte_113-=20;}}break;
    case 4:scale_x_11c+=static_cast<double>(0.1f);scale_y_120=scale_x_11c;if(time_counter_144>=0) {if(byte_110>=30) {byte_111-=30;byte_110-=30;}else {byte_111=0;byte_110=0;}if(byte_113<25) RETIRE();byte_113-=25;}break;
    }FINISH();


}
case 816: {

    if(field_180==5) RETIRE();
    switch(sequence_index_13e) {
    case 0: {
        rotation_12c+=15.0;if(rotation_12c>=360.0f) rotation_12c=360.0f;if(emit_repeated(0,1,4)) RETIRE();
        if(velocity_y_f8<0.0f) {
            double dySquared=square_float_value(static_cast<float>(target_170->y_f0+100.0-y_f0));
            if(square_float_value(target_170->x_ec-x_ec)+dySquared<=2500.0) {publish_battle_layout_scalar(5.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(816,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(6);velocity_y_f8=static_cast<float>(-velocity_y_f8*0.25);velocity_x_f4*=static_cast<double>(0.2f);return;}
        }
        if(static_cast<double>(y_f0)+velocity_y_f8<=stage_surface_height()) {y_f0=stage_surface_height();publish_battle_layout_scalar(5.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(816,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(6);velocity_y_f8=static_cast<float>(-velocity_y_f8*0.25);velocity_x_f4*=static_cast<double>(0.2f);return;}
        if(x_ec>1380.0f || x_ec<-100.0 || y_f0>1000.0 || y_f0<-160.0) RETIRE();velocity_y_f8-=1.0;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    case 1:rotation_12c+=15.0;if(byte_113<=5) RETIRE();byte_113-=5;velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    case 2:advance_six(0);scale_x_11c-=static_cast<double>(0.01f);scale_y_120=scale_x_11c;if(byte_113<=10) RETIRE();byte_113-=10;byte_111-=10;byte_110-=10;FINISH();
    case 3:scale_x_11c+=static_cast<double>(0.02f);scale_y_120=scale_x_11c;if(time_counter_144>0) {if(byte_110<=20) {byte_111-=20;byte_110-=20;}else {if(byte_113<=20) RETIRE();byte_111=0;byte_110=0;byte_113-=20;}}break;
    case 4:scale_x_11c+=static_cast<double>(0.1f);scale_y_120=scale_x_11c;if(time_counter_144>=0) {if(byte_110>=30) {byte_111-=30;byte_110-=30;}else {byte_111=0;byte_110=0;}if(byte_113<25) RETIRE();byte_113-=25;}break;
    case 5:if(time_counter_144%2==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(816,x_ec,static_cast<float>(50*time_counter_144+y_f0),facing_104,1,packet,3);}if(time_counter_144==4) RETIRE();break;
    }FINISH();


}
case 817: {
    if(field_180==5) RETIRE();
    switch(sequence_index_13e) {
    case 0: {
        if((owner_348->action_id_13c==530 || owner_348->action_id_13c==531) && owner_348->sequence_index_13e==0 && owner_348->frame_index_140==0) {select_sequence(6);velocity_x_f4=0.0f;velocity_y_f8=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();if(static_cast<double>(y_f0)+velocity_y_f8<=stage_surface_height()) {velocity_x_f4=0.0f;velocity_y_f8=0.0f;next_sequence_block();y_f0=stage_surface_height();return;}
        if(x_ec>1380.0f || x_ec<-100.0 || y_f0>1000.0 || y_f0<-160.0) RETIRE();velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    case 1: {
        if((owner_348->action_id_13c==530 || owner_348->action_id_13c==531) && owner_348->sequence_index_13e==0 && owner_348->frame_index_140==0) {select_sequence(6);velocity_x_f4=0.0f;velocity_y_f8=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();velocity_x_f4=2.0f;velocity_y_f8=0.0f;if(y_f0>stage_surface_height()) {select_sequence(0);return;}
        if(owner_348->byte_60d>=2 && word_364==0) {AliceUpdateOwnerView *target = target_170;double dx=(target->x_ec-static_cast<double>(x_ec))*facing_104;if(dx<=200.0 && dx>=0.0 && target->y_f0>y_f0) {
            word_364=1;select_sequence(7);velocity_x_f4=4.0f;velocity_y_f8=static_cast<float>((static_cast<double>(owner_348->byte_60d)-2.0)*4.0+7.0);return;
        }}
        if((square_float_value(x_ec-target_170->x_ec)<=2500.0 && square_float_value(y_f0-target_170->y_f0)<=10000.0) || y_f0<stage_surface_height() || word_174<0) {
            publish_battle_layout_scalar(10.0f);select_sequence(6);byte_135=0;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(817,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(6);y_f0=stage_surface_height();velocity_y_f8=12.0f;velocity_x_f4=-10.0f;return;
        }
        if(x_ec>1380.0f || x_ec<-100.0 || y_f0>1000.0 || y_f0<-160.0) RETIRE();x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    case 2:advance_six(0);scale_x_11c-=static_cast<double>(0.01f);scale_y_120=scale_x_11c;if(byte_113<=10) RETIRE();byte_113-=10;byte_111-=10;byte_110-=10;FINISH();
    case 3:scale_x_11c+=static_cast<double>(0.02f);scale_y_120=scale_x_11c;if(time_counter_144>0) {if(byte_110<=20) {byte_111-=20;byte_110-=20;}else {if(byte_113<=20) RETIRE();byte_111=0;byte_110=0;byte_113-=20;}}break;
    case 4:scale_x_11c+=static_cast<double>(0.1f);scale_y_120=scale_x_11c;if(time_counter_144>=0) {if(byte_110>=30) {byte_111-=30;byte_110-=30;}else {byte_111=0;byte_110=0;}if(byte_113<25) RETIRE();byte_113-=25;}break;
    case 5:if(time_counter_144%2==0) {float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(817,x_ec,static_cast<float>(50*time_counter_144+y_f0),facing_104,1,packet,3);}if(time_counter_144==4) RETIRE();break;
    case 6:rotation_12c+=15.0;if(byte_113<=5) RETIRE();byte_113-=5;velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    case 7: {
        if((owner_348->action_id_13c==530 || owner_348->action_id_13c==531) && owner_348->sequence_index_13e==0 && owner_348->frame_index_140==0) {select_sequence(6);velocity_x_f4=0.0f;velocity_y_f8=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();velocity_y_f8-=0.5;if(static_cast<double>(velocity_y_f8)+y_f0<=stage_surface_height()) {select_sequence(1);y_f0=stage_surface_height();velocity_y_f8=0.0f;return;}
        if((square_float_value(x_ec-target_170->x_ec)<=10000.0 && square_float_value(y_f0-target_170->y_f0)<=10000.0) || word_174<0) {publish_battle_layout_scalar(10.0f);select_sequence(6);byte_135=0;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(817,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(6);velocity_y_f8=12.0f;velocity_x_f4=-10.0f;return;}
        if(x_ec>1380.0f || x_ec<-100.0 || y_f0>1000.0 || y_f0<-160.0) RETIRE();x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    case 8: {
        if(emit_repeated(0,3,5)) RETIRE();velocity_y_f8-=0.5;if(static_cast<double>(velocity_y_f8)+y_f0<=stage_surface_height() || (square_float_value(x_ec-target_170->x_ec)<=2500.0 && square_float_value(y_f0-target_170->y_f0)<=10000.0) || y_f0<stage_surface_height() || word_174<0) {publish_battle_layout_scalar(10.0f);select_sequence(6);byte_135=0;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(817,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(6);velocity_y_f8=12.0f;velocity_x_f4=-10.0f;return;}
        if(x_ec>1380.0f || x_ec<-100.0 || y_f0>1000.0 || y_f0<-160.0) RETIRE();x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    case 9: {
        if((owner_348->action_id_13c==530 || owner_348->action_id_13c==531) && owner_348->sequence_index_13e==0 && owner_348->frame_index_140==0) {select_sequence(6);velocity_x_f4=0.0f;velocity_y_f8=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();if(static_cast<double>(y_f0)+velocity_y_f8<=stage_surface_height()) {velocity_x_f4=0.0f;velocity_y_f8=0.0f;next_sequence_block();y_f0=stage_surface_height();return;}
        if(x_ec>1380.0f || x_ec<-100.0 || y_f0>1000.0 || y_f0<-160.0) RETIRE();velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    case 10: {
        if((owner_348->action_id_13c==530 || owner_348->action_id_13c==531) && owner_348->sequence_index_13e==0 && owner_348->frame_index_140==0) {select_sequence(6);velocity_x_f4=0.0f;velocity_y_f8=7.5f;return;}
        if(emit_repeated(0,3,5)) RETIRE();velocity_x_f4=static_cast<float>(owner_348->byte_60d+3.0);velocity_y_f8=0.0f;if(y_f0>stage_surface_height()) {select_sequence(0);return;}
        if(owner_348->byte_60d>=2) {AliceUpdateOwnerView *target = target_170;double dx=(target->x_ec-static_cast<double>(x_ec))*facing_104;if(dx<=200.0 && dx>=0.0 && target->y_f0<=y_f0) {
            select_sequence(8);emit_effect(1,x_ec,y_f0,facing_104,1);owner_348->dispatch_indexed_event_member(1);velocity_x_f4+=3.0;velocity_y_f8=4.0f;return;
        }}
        if((square_float_value(x_ec-target_170->x_ec)<=2500.0 && square_float_value(y_f0-target_170->y_f0)<=10000.0) || y_f0<stage_surface_height() || word_174<0) {
            publish_battle_layout_scalar(10.0f);select_sequence(6);byte_135=0;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(817,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(6);y_f0=stage_surface_height();velocity_y_f8=12.0f;velocity_x_f4=-10.0f;return;
        }
        if(x_ec>1380.0f || x_ec<-100.0 || y_f0>1000.0 || y_f0<-160.0) RETIRE();x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    }FINISH();
}
case 820: {

    byte_17c=2;if(sequence_index_13e<=4 && (emit_repeated(0,1,3) || word_174<=-500)) select_sequence(5);
    if(sequence_index_13e==0) {rotation_12c+=20.0;if(time_counter_144==18) {velocity_y_f8=0.0f;velocity_x_f4=0.0f;rotation_12c=0.0f;next_sequence_block();layer_33c=1;return;}velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;if(y_f0<0.0f) y_f0=0.0f;}
    if(sequence_index_13e==1 && time_counter_144>=static_cast<short>(static_cast<int>(params_340[3]+20.0))) {next_sequence_block();return;}
    if(sequence_index_13e==2) {rotation_12c+=40.0;if(time_counter_144>=9) {rotation_12c=0.0f;next_sequence_block();return;}}
    if(sequence_index_13e==3) {if(time_counter_144==0) {owner_348->dispatch_character_wave_handle(7);params_340[0]=45.0f;params_340[1]=55.0f;}params_340[1]-=5.0;if(params_340[1]<-0.5f) {params_340[1]=-0.5f;byte_184=0;}motion_004.set_components(params_340[0],params_340[1]);advance_six(0);if(field_178>0) {select_sequence(4);return;}if(time_counter_144>=90) {next_sequence_block();layer_33c = -1;if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;return;}MOVE();}
    if(sequence_index_13e==4) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==5) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==6 && update_flight_state(5)) return;FINISH();


}
case 821: {
 {
    byte_17c=6;if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=1) select_sequence(3);
    if(sequence_index_13e==0) {MOVE();}if(sequence_index_13e>=1 && sequence_index_13e<=2) {velocity_x_f4-=2.0;int collision=field_180;if(collision!=0) {if(owner_348->action_id_13c>=545 && owner_348->action_id_13c<=549) owner_348->field_180=collision;}if(velocity_x_f4<-0.5f) velocity_x_f4=-0.5f;if(velocity_x_f4<=0.0f && sequence_index_13e==1) {byte_184=0;select_sequence(2);}MOVE();}
    if(sequence_index_13e==2) {if(byte_113<10) RETIRE();byte_113-=10;}
    if(sequence_index_13e==3) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==4) {scale_x_11c+=static_cast<double>(0.05f);scale_y_120*=static_cast<double>(0.8f);if(scale_y_120<=0.01f) RETIRE();velocity_x_f4=10.0f;x_ec=static_cast<float>(static_cast<double>(facing_104)*10.0+x_ec);}
    if(sequence_index_13e==5) {scale_x_11c+=static_cast<double>(0.05f);scale_y_120=scale_x_11c;if(byte_113<30) RETIRE();byte_113-=30;}
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {velocity_x_f4=25.0f;owner_348->dispatch_character_wave_handle(12);float packet[3]={0.0f,0.0f,4.0f};spawn_unparented(821,static_cast<float>(static_cast<double>(130*facing_104)+x_ec),static_cast<float>(y_f0+4.0),facing_104,layer_33c,packet,3);}return;
}


}
case 825: {

    byte_17c=3;
    if(sequence_index_13e<=2 && (emit_repeated(0,1,3) || word_174<=-750)) select_sequence(3);
    if(sequence_index_13e==0) {motion_004.set_components(params_340[0],params_340[1]);params_340[0]-=2.0;params_340[1]-=1.0;if(params_340[1]<0.0f) {params_340[1]=0.0f;next_sequence_block();return;}MOVE();if(y_f0<0.0f) y_f0=0.0f;}
    if(sequence_index_13e==1) {
        AliceUpdateOwnerView *target = target_170;field_378=-atan2_degrees(static_cast<float>(target->y_f0+100.0-y_f0),static_cast<float>((target->x_ec-static_cast<double>(x_ec))*facing_104));motion_004.set_components(field_378,2.0f);
        if(time_counter_144==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(825,x_ec,y_f0,facing_104,1,packet,3);}if(time_counter_144%15==0) owner_348->dispatch_character_wave_handle(4);advance_six(0);if(field_178>0) {select_sequence(3);return;}
        if(field_180!=0 && ++word_364>=4) {word_364=0;field_180=0;}
        if(time_counter_144>=5*(owner_348->byte_607+18) || byte_184<=0) {next_sequence_block();layer_33c = -1;if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;return;}
        x_ec=static_cast<float>(velocity_x_f4*static_cast<double>(facing_104)+x_ec);y_f0=velocity_y_f8+y_f0;
    }
    if(sequence_index_13e==2) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==3) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==4 && update_flight_state(3)) return;
    if(sequence_index_13e==5) {
        rotation_12c+=25.0;if(!related_34c) RETIRE();
        if(related_34c->sequence_index_13e==1) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;scale_x_11c+=static_cast<double>(0.1f);if(scale_x_11c>3.0f) scale_x_11c=2.5f;scale_y_120=scale_x_11c;if(byte_113<=225) byte_113+=30;else byte_113=255;}
        else {if(byte_113<20) RETIRE();scale_x_11c+=static_cast<double>(0.1f);byte_113-=20;byte_112-=20;byte_111-=20;}
    }
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) {TURN_TO_OWNER();}return;


}
case 827: {

    switch(sequence_index_13e) {
    case 0:case 3: {
        if(emit_repeated(0,3,5)) RETIRE();float trail[3]={0.0f,0.0f,1.0f};spawn_unparented(827,x_ec,y_f0,facing_104,1,trail,3);advance_six(0);short count=owner_348->word_7a6;
        if(count>0) {
            double dySquared=square_float_value(y_f0-owner_348->doll_y_7c0[count - 1]);double distance=square_float_value(x_ec-owner_348->doll_x_7b0[owner_348->word_7a6 - 1])+dySquared;
            if(static_cast<double>(square_int_value(35))>=distance) {
                x_ec=owner_348->doll_x_7b0[owner_348->word_7a6 - 1];y_f0=owner_348->doll_y_7c0[owner_348->word_7a6 - 1];owner_348->doll_flag_7d1[owner_348->word_7a6 - 1]=1;
                if(owner_348->word_7a6==1) {params_340[0]=-atan2_degrees(static_cast<float>(target_170->y_f0-static_cast<double>(y_f0)+100.0),static_cast<float>((target_170->x_ec-static_cast<double>(x_ec))*facing_104));}
                else {params_340[0]=-atan2_degrees(owner_348->doll_y_7c0[owner_348->word_7a6 - 2]-y_f0,static_cast<float>((owner_348->doll_x_7b0[owner_348->word_7a6 - 2]-static_cast<double>(x_ec))*facing_104));}--owner_348->word_7a6;field_180=0;byte_184=1;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(827,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(13);
            }
        }
        motion_004.set_components(params_340[0],params_340[1]);x_ec=static_cast<float>(velocity_x_f4*static_cast<double>(facing_104)+x_ec);y_f0=velocity_y_f8+y_f0;
        if(owner_348->word_7a6<=0 && (x_ec<-100.0f || x_ec>1380.0f || y_f0>1060.0f || y_f0<-260.0f)) RETIRE();break;
    }
    case 1:case 4:scale_x_11c*=static_cast<double>(0.98f);scale_y_120=scale_x_11c;if(byte_113<=5) RETIRE();byte_113-=5;byte_111-=5;byte_110-=5;break;
    case 2:scale_x_11c+=field_370;scale_y_120=scale_x_11c;field_370-=static_cast<double>(0.2f);if(field_370<0.05f) field_370=0.05f;if(byte_113<=10) RETIRE();byte_113-=10;byte_111-=10;byte_110-=10;FINISH();
    case 5:case 6: {
        if(emit_repeated(0,3,5)) RETIRE();float trail[3]={0.0f,0.0f,1.0f};spawn_unparented(827,x_ec,y_f0,facing_104,1,trail,3);advance_six(0);short count=owner_348->word_7a6;
        if(count>0) {
            double dySquared=square_float_value(y_f0-owner_348->doll_y_7c0[count - 1]);double distance=square_float_value(x_ec-owner_348->doll_x_7b0[owner_348->word_7a6 - 1])+dySquared;
            if(static_cast<double>(square_int_value(15))>=distance) {
                x_ec=owner_348->doll_x_7b0[owner_348->word_7a6 - 1];y_f0=owner_348->doll_y_7c0[owner_348->word_7a6 - 1];owner_348->doll_flag_7d1[owner_348->word_7a6 - 1]=1;
                if(owner_348->word_7a6==1) {params_340[0]=-atan2_degrees(static_cast<float>(target_170->y_f0-static_cast<double>(y_f0)+100.0),static_cast<float>((target_170->x_ec-static_cast<double>(x_ec))*facing_104));}
                else {params_340[0]=-atan2_degrees(owner_348->doll_y_7c0[owner_348->word_7a6 - 2]-y_f0,static_cast<float>((owner_348->doll_x_7b0[owner_348->word_7a6 - 2]-static_cast<double>(x_ec))*facing_104));}
                --owner_348->word_7a6;field_180=0;byte_184=1;float packet[3]={0.0f,0.0f,2.0f};spawn_unparented(827,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(13);
            }
        }
        motion_004.set_components(params_340[0],params_340[1]);x_ec=static_cast<float>(velocity_x_f4*static_cast<double>(facing_104)+x_ec);y_f0=velocity_y_f8+y_f0;
        if(owner_348->word_7a6<=0 && (x_ec<-100.0f || x_ec>1380.0f || y_f0>1060.0f || y_f0<-260.0f)) RETIRE();break;
    }
    }FINISH();


}
case 830: {

    if(sequence_index_13e==0) {
        field_370+=field_374;field_374-=1.5;if(field_374<0.0f) field_374=0.0f;facing_104=owner_348->facing_104;
        x_ec=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(4*owner_348->word_7ac)+params_340[2]*120.0))*field_370+owner_348->x_ec);
        y_f0=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(4*owner_348->word_7ac)+params_340[2]*120.0))*field_370*0.25+(owner_348->y_f0+100.0));layer_33c = static_cast<int>(static_cast<double>(4 * owner_348->word_7ac) + params_340[2] * 120.0) % 360 > 180 ? 1 : -1;
        if(owner_348->word_174<=0) {next_sequence_block();velocity_x_f4=0.0f;velocity_y_f8=0.0f;return;}
        if(owner_348->action_id_13c==565 && owner_348->byte_7d0==1) {short count=owner_348->word_7a4;if(static_cast<double>(count)==params_340[2]) {owner_348->word_7a4=count-1;owner_348->byte_7d0=0;set_action(831);select_sequence(0);time_counter_144=0;return;}}
        if(owner_348->action_id_13c==566 && owner_348->byte_7d0==1) {--owner_348->word_7a4;set_action(834);select_sequence(0);time_counter_144=0;return;}
    }
    if(sequence_index_13e==1) {velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}FINISH();


}
case 831: {
 {
    AliceUpdateOwnerView *owner = owner_348;
    if(owner->action_id_13c>49 && owner->action_id_13c<150 && sequence_index_13e<=3) {select_sequence(4);velocity_x_f4=0.0f;velocity_y_f8=0.0f;return;}
    if(sequence_index_13e==0) {
        field_370=static_cast<float>((static_cast<double>(50*owner->facing_104)+owner->x_ec-x_ec)*(static_cast<double>(50*owner->facing_104)+owner->x_ec-x_ec));field_374=static_cast<float>((owner->y_f0+115.0-y_f0)*(owner->y_f0+115.0-y_f0));field_378=sqrt_float_value(field_374+field_370);
        params_340[0]=-atan2_degrees(static_cast<float>(owner->y_f0+115.0-y_f0),static_cast<float>(static_cast<double>(50*owner->facing_104)+owner->x_ec-x_ec));params_340[1]=static_cast<float>(field_378*static_cast<double>(0.2f));if(params_340[1]>50.0f) params_340[1]=50.0f;motion_004.set_components(params_340[0],params_340[1]);if(velocity_x_f4<0.0f) facing_104=-1; else facing_104=1;
        if(time_counter_144>=16) {next_sequence_block();facing_104=owner_348->facing_104;x_ec=static_cast<float>(static_cast<double>(50*facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+115.0);return;}x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;
    }
    if(sequence_index_13e==1) {if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(831,static_cast<float>(static_cast<double>(60*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(9);}x_ec=static_cast<float>(static_cast<double>(50*facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+115.0);}
    if(sequence_index_13e==1) {if(owner_348->action_id_13c!=565 || owner_348->sequence_index_13e>=3) {field_370=0.0f;field_374=0.0f;field_378=0.0f;next_sequence_block();return;}}
    if(sequence_index_13e==3) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==4) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==5) {
        if(word_364==0) {if(time_counter_144<40) {if(related_34c) {x_ec=static_cast<float>(static_cast<double>(60*facing_104)+related_34c->x_ec);y_f0=static_cast<float>(related_34c->y_f0+5.0);}scale_x_11c=static_cast<float>(static_cast<double>(time_counter_144&2)*static_cast<double>(0.2f)+1.0);scale_y_120=scale_x_11c;}else word_364=1;if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) RETIRE();if(owner_348->action_id_13c!=565 || sequence_index_13e==3) word_364=1;}
        if(word_364==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(scale_x_11c<0.02f) RETIRE();}
    }
    if(sequence_index_13e==6) {
        if(owner_348->action_id_13c<=49 || owner_348->action_id_13c>=150) {if(word_364<=1 && owner_348->action_id_13c!=565) word_364=2;}
        else if(word_364<=1) {for(int index=0;index<30;++index) {double centerY=y_f0+10.0;emit_effect(201,static_cast<float>(static_cast<double>(RF(20))+(static_cast<double>(40*index*facing_104)+x_ec)),static_cast<float>(centerY-static_cast<double>(RF(20))),facing_104,1);}RETIRE();}
        if(word_364==0) {if(related_34c) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;}scale_y_120+=static_cast<double>(0.1f);if(scale_y_120>0.7f) {scale_y_120=0.7f;word_364=1;byte_184=10;return;}}
        if(word_364==1) {if(related_34c) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;if(related_34c->word_364==1) word_364=2;}advance_six(0);if(field_180!=0 && ++word_366>=3) {word_366=0;field_180=0;}}
        if(word_364==2) {byte_184=0;scale_y_120*=static_cast<double>(0.85f);if(scale_y_120<=0.01f) RETIRE();}
    }FINISH();
}


}
case 834: {
 {
    if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=3) {select_sequence(4);velocity_x_f4=0.0f;velocity_y_f8=0.0f;return;}
    if(sequence_index_13e==0) {
        float desiredX=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(3*owner_348->word_7ac)+params_340[2]*120.0))*20.0+(static_cast<double>(75*owner_348->facing_104)+owner_348->x_ec));
        float desiredY=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(3*owner_348->word_7ac)+params_340[2]*120.0))*80.0+(owner_348->y_f0+100.0));
        double dx=static_cast<double>(desiredX)-x_ec;field_370=static_cast<float>(dx*dx);double dy=static_cast<double>(desiredY)-y_f0;field_374=static_cast<float>(dy*dy);field_378=sqrt_float_value(field_374+field_370);
        params_340[0]=-atan2_degrees(desiredY-y_f0,static_cast<float>(desiredX-x_ec));params_340[1]=static_cast<float>(field_378*static_cast<double>(0.2f));if(params_340[1]>50.0f) params_340[1]=50.0f;motion_004.set_components(params_340[0],params_340[1]);if(velocity_x_f4<0.0f) facing_104=-1; else facing_104=1;
        if(time_counter_144>=16) {next_sequence_block();facing_104=owner_348->facing_104;x_ec=static_cast<float>(desiredX);y_f0=desiredY;return;}x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;
    }
    if(sequence_index_13e==1) {
        if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(834,static_cast<float>(static_cast<double>(60*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(9);}
        float desiredX=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(3*owner_348->word_7ac)+params_340[2]*120.0))*20.0+(static_cast<double>(75*owner_348->facing_104)+owner_348->x_ec));
        float desiredY=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(3*owner_348->word_7ac)+params_340[2]*120.0))*80.0+(owner_348->y_f0+100.0));x_ec=static_cast<float>(desiredX);y_f0=desiredY;
    }
    if(sequence_index_13e==1) {if(owner_348->action_id_13c!=566 || owner_348->sequence_index_13e>=3) {field_370=0.0f;field_374=0.0f;field_378=0.0f;next_sequence_block();return;}}
    if(sequence_index_13e==3) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==4) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==5) {
        if(word_364==0) {if(time_counter_144<40) {if(related_34c) {x_ec=static_cast<float>(static_cast<double>(60*facing_104)+related_34c->x_ec);y_f0=static_cast<float>(related_34c->y_f0+5.0);}scale_x_11c=static_cast<float>(static_cast<double>(time_counter_144&2)*static_cast<double>(0.2f)+1.0);scale_y_120=scale_x_11c;}else word_364=1;if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) RETIRE();if(owner_348->action_id_13c!=566 || sequence_index_13e==3) word_364=1;}
        if(word_364==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(scale_x_11c<0.02f) RETIRE();}
    }
    if(sequence_index_13e==6) {
        if(owner_348->action_id_13c<=49 || owner_348->action_id_13c>=150) {if(word_364<=1 && owner_348->action_id_13c!=566) word_364=2;}
        else if(word_364<=1) {for(int index=0;index<20;++index) {double centerY=y_f0+10.0;emit_effect(201,static_cast<float>(static_cast<double>(RF(30))+(static_cast<double>(60*index*facing_104)+x_ec)),static_cast<float>(centerY-static_cast<double>(RF(20))),facing_104,1);}RETIRE();}
        if(word_364==0) {if(related_34c) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;}scale_y_120+=static_cast<double>(0.1f);if(scale_y_120>0.7f) {scale_y_120=0.7f;word_364=1;byte_184=10;return;}}
        if(word_364==1) {if(related_34c) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;if(related_34c->word_364==1) word_364=2;}advance_six(0);if(field_180!=0 && ++word_366>=3) {word_366=0;field_180=0;}}
        if(word_364==2) {byte_184=0;scale_y_120*=static_cast<double>(0.85f);if(scale_y_120<=0.01f) RETIRE();}
    }FINISH();
}


}
case 849: {
 {
    switch(sequence_index_13e) {
    case 1:case 2:case 3: {
        if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=3) {select_sequence(4);return;}
        if(owner_348->action_id_13c!=301 && sequence_index_13e<=2) {select_sequence(3);field_370=0.0f;return;}
        if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==1) {velocity_x_f4=30.0f;velocity_y_f8=5.0f;}
        if(sequence_index_13e<=2) {
            velocity_x_f4-=3.0;if(velocity_x_f4<=1.0f) velocity_x_f4=1.0f;velocity_y_f8-=0.5;if(velocity_y_f8<0.5f) velocity_y_f8=0.5f;field_370=facing_104*velocity_x_f4+field_370;field_374+=velocity_y_f8;x_ec=static_cast<float>(static_cast<double>(30*facing_104)+owner_348->x_ec+field_370);y_f0=static_cast<float>(owner_348->y_f0+100.0+field_374);owner_348->field_180=field_180;
            if(sequence_index_13e==2 && time_counter_144%2==0 && frame_index_140>=1) {field_378=static_cast<float>(static_cast<double>(RF(90))-45.0);float packet[3]={field_378,0.0f,5.0f};spawn_unparented(849,static_cast<float>(lookup_orientation_cosine_quantized_abs(-field_378)*100.0*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(-field_378)*100.0+y_f0),facing_104,1,packet,3);}
        }
        if(sequence_index_13e==3) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}break;
    }
    case 4:if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;break;
    case 5:scale_x_11c+=static_cast<double>(0.01f);scale_y_120*=static_cast<double>(0.8f);if(scale_y_120<=0.05f) RETIRE();motion_004.set_components(params_340[0],15.0f);MOVE();break;
    case 6:case 7:case 8: {
        if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=7) {select_sequence(4);field_370=0.0f;return;}if(owner_348->action_id_13c!=302 && sequence_index_13e<=7) {select_sequence(3);field_370=0.0f;field_374=0.0f;return;}
        if(sequence_index_13e==6) {
            if(related_34c) {x_ec=static_cast<float>(static_cast<double>(facing_104)*field_370+related_34c->x_ec);y_f0=related_34c->y_f0+field_374;field_370=static_cast<float>(lookup_orientation_cosine_quantized_abs(params_340[0])*5.0+field_370);field_374=static_cast<float>(lookup_orientation_sine_quantized_abs(params_340[0])*15.0+field_374);}
            else {select_sequence(3);if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;field_370=0.0f;field_374=0.0f;return;}
        }
        if(sequence_index_13e==7) {
            if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {float packet[3]={0.0f,0.0f,9.0f};spawn_unparented(849,static_cast<float>((lookup_orientation_cosine_quantized_abs(params_340[0])*5.0+135.0)*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(params_340[0])*15.0+y_f0+3.0),facing_104,1,packet,3);}
            if(related_34c) {x_ec=static_cast<float>(field_370*static_cast<double>(facing_104)+related_34c->x_ec);y_f0=related_34c->y_f0+field_374;}
            else {select_sequence(3);if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;field_370=0.0f;field_374=0.0f;return;}
        }
        if(sequence_index_13e==8) {
            if(((owner_348->action_id_13c>49 && owner_348->action_id_13c<150) || owner_348->action_id_13c!=302) && frame_index_140<=1) {select_frame(2);return;}
            if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {byte_184=1;field_180=0;velocity_x_f4=30.0f;velocity_y_f8=0.0f;}
            velocity_x_f4-=3.0;if(velocity_x_f4<=0.5f) velocity_x_f4=0.5f;field_370=facing_104*velocity_x_f4+field_370;field_374=velocity_y_f8+field_374;x_ec=static_cast<float>(static_cast<double>(110*facing_104)+owner_348->x_ec+field_370);y_f0=static_cast<float>(owner_348->y_f0+105.0+field_374);owner_348->field_180=field_180;if(frame_index_140==2 && frame_timer_142==10) RETIRE();
        }break;
    }
    case 9:scale_x_11c+=static_cast<double>(0.05f);scale_y_120*=static_cast<double>(0.85f);if(byte_113<15) RETIRE();byte_113-=15;velocity_x_f4=10.0f;x_ec=static_cast<float>(static_cast<double>(facing_104)*10.0+x_ec);break;
    case 10:if(update_flight_state(4)) return;break;
    case 11:case 12: {
        if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) {select_sequence(4);rotation_12c=0.0f;field_370=0.0f;return;}
        if(owner_348->action_id_13c!=304) {select_sequence(3);rotation_12c=0.0f;field_370=0.0f;field_374=0.0f;return;}
        motion_004.set_components(params_340[0],params_340[1]);params_340[1]-=4.0;if(params_340[1]<=1.0f) params_340[1]=1.0f;field_370=static_cast<float>(velocity_x_f4*static_cast<double>(facing_104)+field_370);field_374=velocity_y_f8+field_374;x_ec=static_cast<float>(static_cast<double>(30*facing_104)+owner_348->x_ec+field_370);y_f0=static_cast<float>(owner_348->y_f0+100.0+field_374);int collision=field_180;if(collision!=0) owner_348->field_180=collision;if(sequence_index_13e==12) {if(time_counter_144>=3) byte_184=0;if(time_counter_144>=10) {select_sequence(3);rotation_12c=0.0f;field_370=0.0f;field_374=0.0f;return;}}
        break;
    }
    case 13:scale_x_11c+=static_cast<double>(0.05f);scale_y_120*=static_cast<double>(0.85f);if(byte_113<15) RETIRE();byte_113-=15;motion_004.set_components(params_340[0],params_340[1]);MOVE();break;
    case 14:case 15:case 16: {
        if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=15) {select_sequence(4);field_370=0.0f;return;}if(owner_348->action_id_13c!=307 && sequence_index_13e<=15) {select_sequence(3);field_370=0.0f;field_374=0.0f;return;}
        if(sequence_index_13e==14) {
            if(related_34c) {x_ec=static_cast<float>(static_cast<double>(facing_104)*field_370+related_34c->x_ec);y_f0=related_34c->y_f0+field_374;field_370=static_cast<float>(lookup_orientation_cosine_quantized_abs(params_340[0])*5.0+field_370);field_374=static_cast<float>(lookup_orientation_sine_quantized_abs(params_340[0])*15.0+field_374);}
            else {select_sequence(3);if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;field_370=0.0f;field_374=0.0f;return;}
        }
        if(sequence_index_13e==15) {
            if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {float packet[3]={0.0f,0.0f,9.0f};spawn_unparented(849,static_cast<float>((lookup_orientation_cosine_quantized_abs(params_340[0])*5.0+135.0)*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(params_340[0])*15.0+y_f0+3.0),facing_104,1,packet,3);}
            if(related_34c) {x_ec=static_cast<float>(field_370*static_cast<double>(facing_104)+related_34c->x_ec);y_f0=related_34c->y_f0+field_374;}
            else {select_sequence(3);if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;field_370=0.0f;field_374=0.0f;return;}
        }
        if(sequence_index_13e==16) {
            if(((owner_348->action_id_13c>49 && owner_348->action_id_13c<150) || owner_348->action_id_13c!=307) && frame_index_140<=1) {select_frame(2);return;}
            if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {byte_184=1;field_180=0;velocity_x_f4=30.0f;velocity_y_f8=0.0f;}
            velocity_x_f4-=3.0;if(velocity_x_f4<=0.5f) velocity_x_f4=0.5f;field_370=facing_104*velocity_x_f4+field_370;field_374=velocity_y_f8+field_374;x_ec=static_cast<float>(static_cast<double>(50*facing_104)+owner_348->x_ec+field_370);y_f0=static_cast<float>(owner_348->y_f0+140.0+field_374);owner_348->field_180=field_180;if(frame_index_140==2 && frame_timer_142==10) RETIRE();
        }break;
    }
    case 17:case 18: {
        if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=18) {select_sequence(4);field_370=0.0f;return;}if(owner_348->action_id_13c!=308 && sequence_index_13e<=18) {select_sequence(3);field_370=0.0f;field_374=0.0f;return;}
        if(sequence_index_13e==17) {if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {byte_184=0;field_180=0;}x_ec=static_cast<float>((field_370+25.0)*static_cast<double>(facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+95.0+field_374);motion_004.set_components(params_340[0],params_340[1]);field_370=velocity_x_f4+field_370;field_374=velocity_y_f8+field_374;}
        if(sequence_index_13e==18) {if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {float packet[3]={45.0f,2.0f,13.0f};spawn_unparented(849,x_ec,y_f0,facing_104,1,packet,3);params_340[0]=45.0f;params_340[1]=30.0f;}
            x_ec=static_cast<float>((field_370+25.0)*static_cast<double>(facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+95.0+field_374);motion_004.set_components(params_340[0],params_340[1]);params_340[1]-=3.0;if(params_340[1]<0.5f) params_340[1]=0.5f;if(time_counter_144>=8) byte_184=0;field_370=velocity_x_f4+field_370;field_374=velocity_y_f8+field_374;if(time_counter_144>=26) {select_sequence(3);field_370=0.0f;field_374=0.0f;return;}
        }break;
    }
    case 19:case 20: {
        if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) {select_sequence(4);return;}
        if(owner_348->action_id_13c!=408 && sequence_index_13e<=20) {select_sequence(3);field_370=0.0f;if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;return;}
        if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==19) {velocity_x_f4=30.0f;velocity_y_f8=5.0f;}
        if(sequence_index_13e<=20) {velocity_x_f4-=3.0;if(velocity_x_f4<=1.0f) velocity_x_f4=1.0f;velocity_y_f8-=0.5;if(velocity_y_f8<0.5f) velocity_y_f8=0.5f;field_370=facing_104*velocity_x_f4+field_370;field_374+=velocity_y_f8;x_ec=static_cast<float>(static_cast<double>(30*facing_104)+owner_348->x_ec+field_370);y_f0=static_cast<float>(owner_348->y_f0+100.0+field_374);owner_348->field_180=field_180;
            if(sequence_index_13e==20 && time_counter_144%2==0 && frame_index_140>=1) {field_378=static_cast<float>(static_cast<double>(RF(90))-45.0);float packet[3]={field_378,0.0f,5.0f};spawn_unparented(849,static_cast<float>(lookup_orientation_cosine_quantized_abs(-field_378)*100.0*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(-field_378)*100.0+y_f0),facing_104,1,packet,3);}
        }break;
    }
    case 21:
        if(time_counter_144==0) {float packet[3]={0.0f,0.0f,22.0f};spawn_parented(849,x_ec,y_f0,facing_104,1,packet,3);}
        {if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) {select_sequence(4);return;}if(owner_348->action_id_13c!=418) {select_sequence(3);if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;field_370=0.0f;return;}}
        x_ec=static_cast<float>((lookup_orientation_cosine(10*(18-time_counter_144))*150.0+150.0)*static_cast<double>(facing_104)+owner_348->x_ec);y_f0=static_cast<float>(lookup_orientation_sine(10*(18-time_counter_144))*25.0+(owner_348->y_f0+50.0));if(10*time_counter_144>=180) layer_33c=1;if(10*time_counter_144==170) {byte_184=1;field_180=0;}if(10*time_counter_144==190) byte_184=0;if(field_180!=0) owner_348->field_180=field_180;if(10*time_counter_144>=350) RETIRE();break;
    case 22:
        if(related_34c) {layer_33c=related_34c->layer_33c;short phase=related_34c->sequence_index_13e;if(phase!=21 && phase!=23) RETIRE();x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;scale_y_120=scale_x_11c;if(byte_113<=225) byte_113+=30;else byte_113=255;}
        else {if(byte_113<30) RETIRE();scale_x_11c+=static_cast<double>(0.1f);byte_113-=30;byte_112-=30;byte_111-=30;}rotation_12c+=25.0;break;
    case 23:
        if(time_counter_144==0) {float packet[3]={0.0f,0.0f,22.0f};spawn_parented(849,x_ec,y_f0,facing_104,1,packet,3);}
        {if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) {select_sequence(4);return;}if(owner_348->action_id_13c!=418) {select_sequence(3);if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;field_370=0.0f;return;}}
        x_ec=static_cast<float>((lookup_orientation_cosine(10*(time_counter_144+18))*150.0+150.0)*static_cast<double>(facing_104)+owner_348->x_ec);y_f0=static_cast<float>(lookup_orientation_sine(10*(time_counter_144+18))*25.0+(owner_348->y_f0+50.0));if(10*time_counter_144>=180) layer_33c = -1;if(10*time_counter_144==170) {byte_184=1;field_180=0;}if(10*time_counter_144==190) byte_184=0;if(field_180!=0) owner_348->field_180=field_180;if(10*time_counter_144>=350) RETIRE();break;
    case 24:case 25: {
        if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=24) {select_sequence(4);field_370=0.0f;return;}if(owner_348->action_id_13c!=309 && sequence_index_13e<=24) {select_sequence(3);field_370=0.0f;field_374=0.0f;return;}
        if(sequence_index_13e==24) {if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {byte_184=0;field_180=0;}x_ec=static_cast<float>((field_370+25.0)*static_cast<double>(facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+95.0+field_374);motion_004.set_components(params_340[0],params_340[1]);field_370=velocity_x_f4+field_370;field_374=velocity_y_f8+field_374;}
        if(sequence_index_13e==25) {if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {float packet[3]={-45.0f,2.0f,13.0f};spawn_unparented(849,x_ec,y_f0,facing_104,1,packet,3);params_340[0]=-45.0f;params_340[1]=30.0f;}
            x_ec=static_cast<float>((field_370+30.0)*static_cast<double>(facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+120.0+field_374);motion_004.set_components(params_340[0],params_340[1]);params_340[1]-=3.0;if(params_340[1]<0.5f) params_340[1]=0.5f;if(time_counter_144>=8) byte_184=0;field_370=velocity_x_f4+field_370;field_374=velocity_y_f8+field_374;if(time_counter_144>=18) {select_sequence(3);field_370=0.0f;field_374=0.0f;return;}
        }break;
    }
    }
    advance_frame();
    if(sequence_index_13e==2 && frame_index_140>=1 && frame_timer_142==0) {owner_348->dispatch_indexed_event_member(27);byte_184=1;field_180=0;}
    if(sequence_index_13e==20 && frame_index_140>=1 && frame_timer_142==0) {owner_348->dispatch_indexed_event_member(27);byte_184=1;field_180=0;}
    if(time_counter_144==0) {
        if(frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==21) select_sequence(3);
        if(time_counter_144==0) {
            if(frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==3) {if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;field_370=0.0f;}
            if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==12) {owner_348->dispatch_indexed_event_member(27);float packet[3]={params_340[0],3.0f,13.0f};spawn_unparented(849,x_ec,y_f0,facing_104,1,packet,3);}
        }
    }return;
}


}
case 850: {

    if(field_180==5) RETIRE();
    if(sequence_index_13e==0) {rotation_12c+=30.0;if(static_cast<double>(y_f0)+velocity_y_f8<=stage_surface_height()) {publish_battle_layout_scalar(10.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};y_f0=stage_surface_height();spawn_unparented(850,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(21);velocity_y_f8=static_cast<float>(-velocity_y_f8*0.5);velocity_x_f4*=static_cast<double>(0.2f);return;}velocity_y_f8-=1.0;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;}
    if(sequence_index_13e==1) {rotation_12c+=15.0;if(byte_113<=10) RETIRE();byte_113-=10;velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;}
    if(sequence_index_13e==2) {advance_six(0);scale_x_11c-=static_cast<double>(0.005f);scale_y_120=scale_x_11c;if(byte_113<=5) RETIRE();byte_113-=5;byte_111-=5;byte_110-=5;}
    if(sequence_index_13e==3) {scale_x_11c+=static_cast<double>(0.2f);scale_y_120=scale_x_11c;if(time_counter_144>0) {if(byte_110<=25) {byte_111-=25;byte_110-=25;}else {if(byte_113<=25) RETIRE();byte_111=0;byte_110=0;byte_113-=25;}}}
    if(sequence_index_13e==4) {scale_x_11c+=static_cast<double>(0.01f);scale_y_120=scale_x_11c;if(time_counter_144>=0) {if(byte_110>=25) {byte_111-=25;byte_110-=25;}else {byte_111=0;byte_110=0;}if(byte_113<25) RETIRE();byte_113-=25;}}
    if(sequence_index_13e==5) {scale_x_11c+=static_cast<double>(0.01f);scale_y_120=scale_x_11c;motion_004.set_components(params_340[0],params_340[1]);params_340[1]-=1.5;if(params_340[1]<0.5f) params_340[1]=0.5f;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0=static_cast<float>(velocity_y_f8*static_cast<double>(0.2f)+y_f0);if(byte_113>=5) byte_113-=5;else RETIRE();}FINISH();


}
case 851: {

    if(sequence_index_13e<=1) {
        field_370=facing_104*field_378+field_370;field_378-=1.0;if(field_378<1.0f) field_378=1.0f;word_36c+=3;word_36a+=4*facing_104;if(word_36c>=90) word_36c=90;field_37c+=3.0;
        double orbitX=lookup_orientation_cosine_quantized_abs(static_cast<float>(params_340[3]+static_cast<double>(word_36a)));double elevationX=lookup_orientation_sine_quantized_abs(static_cast<float>(word_36c));x_ec=static_cast<float>(elevationX*field_37c*orbitX+field_370);
        double orbitY=lookup_orientation_sine_quantized_abs(static_cast<float>(params_340[3]+static_cast<double>(word_36a)));y_f0=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(word_36c))*field_37c*orbitY+field_374);
    }
    if(sequence_index_13e==0) {byte_184=0;if(field_378==1.0f) {next_sequence_block();layer_33c=1;byte_184=1;return;}}
    if(sequence_index_13e==1) {
        if(time_counter_144==0) {float packet[4]={0.0f,0.0f,5.0f,0.0f};spawn_parented(851,x_ec,y_f0,facing_104,1,packet,4);}advance_six(0);if(field_180!=0 && ++word_368>=30) {word_368=0;field_180=0;byte_184=1;}
        if(time_counter_144>=120) {byte_184=0;next_sequence_block();layer_33c = -1;field_370=0.0f;if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;return;}
    }
    if(sequence_index_13e==2) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==3) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==4 && update_flight_state(3)) return;
    if(sequence_index_13e==5) {if(!related_34c) RETIRE();if(related_34c->sequence_index_13e==1) {if(byte_113<=225) byte_113+=30;else byte_113=255;x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;}else {if(byte_113<30) RETIRE();scale_x_11c+=static_cast<double>(0.15f);scale_y_120=scale_x_11c;byte_113-=30;}rotation_12c+=25.0;}
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) {TURN_TO_OWNER();}return;


}
case 852: {
 {
    AliceUpdateOwnerView *owner = owner_348;
    if(owner->action_id_13c>49 && owner->action_id_13c<150 && sequence_index_13e<=3) {select_sequence(4);velocity_x_f4=0.0f;velocity_y_f8=0.0f;return;}
    if(sequence_index_13e==0) {
        field_370=static_cast<float>((static_cast<double>(50*owner->facing_104)+owner->x_ec-x_ec)*(static_cast<double>(50*owner->facing_104)+owner->x_ec-x_ec));field_374=static_cast<float>((owner->y_f0+115.0-y_f0)*(owner->y_f0+115.0-y_f0));field_378=sqrt_float_value(field_374+field_370);
        params_340[0]=-atan2_degrees(static_cast<float>(owner->y_f0+115.0-y_f0),static_cast<float>(static_cast<double>(50*owner->facing_104)+owner->x_ec-x_ec));params_340[1]=static_cast<float>(field_378*static_cast<double>(0.2f));if(params_340[1]>50.0f) params_340[1]=50.0f;motion_004.set_components(params_340[0],params_340[1]);if(velocity_x_f4<0.0f) facing_104=-1; else facing_104=1;
        if(time_counter_144>=16) {next_sequence_block();facing_104=owner_348->facing_104;x_ec=static_cast<float>(static_cast<double>(50*facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+115.0);return;}x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;
    }
    if(sequence_index_13e==1) {if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(852,static_cast<float>(static_cast<double>(60*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(23);}x_ec=static_cast<float>(static_cast<double>(50*facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+115.0);}
    if(sequence_index_13e==1) {if(owner_348->action_id_13c!=602 || owner_348->sequence_index_13e>=3) {field_370=0.0f;field_374=0.0f;field_378=0.0f;next_sequence_block();return;}}
    if(sequence_index_13e==3) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==4) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==5) {
        if(word_364==0) {if(time_counter_144<60) {if(related_34c) {x_ec=static_cast<float>(static_cast<double>(60*facing_104)+related_34c->x_ec);y_f0=static_cast<float>(related_34c->y_f0+5.0);}scale_x_11c=static_cast<float>(static_cast<double>(time_counter_144&2)*static_cast<double>(0.2f)+1.0);scale_y_120=scale_x_11c;}else word_364=1;if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) RETIRE();if(owner_348->action_id_13c!=602 || sequence_index_13e==3) word_364=1;}
        if(word_364==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(scale_x_11c<0.02f) RETIRE();}
    }
    if(sequence_index_13e==6) {
        if(owner_348->action_id_13c<=49 || owner_348->action_id_13c>=150) {if(word_364<=1 && owner_348->action_id_13c!=602) word_364=2;}
        else if(word_364<=1) RETIRE();
        if(word_364==0) {if(related_34c) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;}scale_y_120+=static_cast<double>(0.15f);if(scale_y_120>1.0f) {scale_y_120=1.0f;word_364=1;byte_184=20;return;}}
        if(word_364==1) {if(time_counter_144%2==0) {float packet[3]={0.0f,0.0f,7.0f};spawn_parented(852,static_cast<float>(static_cast<double>(RF(960))*facing_104+x_ec),y_f0,facing_104,1,packet,3);}if(related_34c) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;if(related_34c->word_364==1) word_364=2;}advance_six(0);if(field_180!=0 && ++word_366>=3) {word_366=0;field_180=0;}}
        if(word_364==2) {byte_184=0;scale_y_120*=static_cast<double>(0.85f);if(scale_y_120<=0.01f) RETIRE();}
    }
    if(sequence_index_13e==7) {scale_x_11c+=static_cast<double>(0.05f);scale_y_120=scale_x_11c;rotation_12c+=30.0;if(related_34c) y_f0=related_34c->y_f0;if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) RETIRE();if(byte_113<10) RETIRE();byte_113-=10;byte_111-=10;byte_110-=10;x_ec=static_cast<float>(static_cast<double>(25*facing_104)+x_ec);if(x_ec>1380.0f || x_ec<-100.0f) RETIRE();}FINISH();
}


}
case 853: {

    if(field_180==5) RETIRE();
    if(sequence_index_13e==0) {rotation_12c+=30.0;if(static_cast<double>(y_f0)+velocity_y_f8<=stage_surface_height()) {publish_battle_layout_scalar(10.0f);next_sequence_block();float packet[3]={0.0f,0.0f,2.0f};y_f0=stage_surface_height();spawn_unparented(853,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(25);velocity_y_f8=static_cast<float>(-velocity_y_f8*0.5);velocity_x_f4*=static_cast<double>(0.2f);return;}velocity_y_f8-=2.0;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;}
    if(sequence_index_13e==1) {rotation_12c+=15.0;if(byte_113<=10) RETIRE();byte_113-=10;velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;}
    if(sequence_index_13e==2) {advance_six(0);scale_x_11c-=static_cast<double>(0.005f);scale_y_120=scale_x_11c;}
    if(sequence_index_13e==3) {scale_x_11c+=static_cast<double>(0.3f);scale_y_120=scale_x_11c;if(time_counter_144>0) {if(byte_110<=25) {byte_111-=25;byte_110-=25;}else {if(byte_113<=25) RETIRE();byte_111=0;byte_110=0;byte_113-=25;}}}
    if(sequence_index_13e==4) {scale_x_11c+=static_cast<double>(0.05f);scale_y_120=scale_x_11c;if(time_counter_144>=0) {if(byte_110>=25) {byte_111-=25;byte_110-=25;}else {byte_111=0;byte_110=0;}if(byte_113<25) RETIRE();byte_113-=25;}}
    if(sequence_index_13e==5) {scale_x_11c+=static_cast<double>(0.01f);scale_y_120=scale_x_11c;motion_004.set_components(params_340[0],params_340[1]);params_340[1]-=1.5;if(params_340[1]<0.5f) {params_340[1]=0.5f;if(byte_113<5) RETIRE();byte_113-=5;}x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0=static_cast<float>(velocity_y_f8*static_cast<double>(0.2f)+y_f0);}if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==3) --lifetime_330;return;


}
case 854: {

    if(sequence_index_13e<=1) {
        if(params_340[3]<=359.0f) {
            field_370=facing_104*field_378+field_370;field_378-=2.0;if(field_378<2.0f) field_378=2.0f;word_36c+=3;word_36a+=4*facing_104;if(word_36c>=90) word_36c=90;
            double orbitX=lookup_orientation_cosine_quantized_abs(static_cast<float>(params_340[3]+static_cast<double>(word_36a)));double elevationX=lookup_orientation_sine_quantized_abs(static_cast<float>(word_36c));x_ec=static_cast<float>(elevationX*100.0*orbitX+field_370);y_f0=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(params_340[3]+static_cast<double>(word_36a)))*(lookup_orientation_sine_quantized_abs(static_cast<float>(word_36c))*100.0)+field_374);
        }
        else {
            field_370=facing_104*field_378+field_370;field_378-=2.0;if(field_378<2.0f) field_378=2.0f;word_36c+=3;word_36a-=4*facing_104;if(word_36c>=90) word_36c=90;
            double orbitX=lookup_orientation_cosine_quantized_abs(static_cast<float>(params_340[3]+static_cast<double>(word_36a)));double elevationX=lookup_orientation_sine_quantized_abs(static_cast<float>(word_36c));x_ec=static_cast<float>(elevationX*200.0*orbitX+field_370);y_f0=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(params_340[3]+static_cast<double>(word_36a)))*(lookup_orientation_sine_quantized_abs(static_cast<float>(word_36c))*200.0)+field_374);
        }
    }
    if(sequence_index_13e==0) {byte_184=0;if(field_378<=2.0f) {next_sequence_block();layer_33c=1;byte_184=1;return;}}
    if(sequence_index_13e==1) {
        if(time_counter_144==0) {float packet[4]={0.0f,0.0f,params_340[3]<360.0f?5.0f:6.0f,0.0f};spawn_parented(854,x_ec,y_f0,facing_104,1,packet,4);}advance_six(0);if(field_180!=0 && ++word_368>=30) {word_368=0;field_180=0;byte_184=1;}
        if(time_counter_144>=120) {byte_184=0;next_sequence_block();layer_33c = -1;field_370=0.0f;if(x_ec-owner_348->x_ec>0.0f) facing_104=-1;if(x_ec-owner_348->x_ec<0.0f) facing_104=1;return;}
    }
    if(sequence_index_13e==2) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==3) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==4 && update_flight_state(3)) return;
    if(sequence_index_13e==5 || sequence_index_13e==6) {if(!related_34c) RETIRE();if(related_34c->sequence_index_13e==1) {if(byte_113<=225) byte_113+=30;else byte_113=255;x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;}else {if(byte_113<30) RETIRE();scale_x_11c+=static_cast<double>(0.15f);scale_y_120=scale_x_11c;byte_113-=30;}rotation_12c+=25.0;}
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) {TURN_TO_OWNER();}return;


}
case 855: {
 {
    if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=3) {select_sequence(4);velocity_x_f4=0.0f;velocity_y_f8=0.0f;return;}
    if(sequence_index_13e==0) {
        float desiredX=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(4*owner_348->word_7ac)+params_340[3]*60.0))*(field_380*0.25+20.0)+(static_cast<double>(75*owner_348->facing_104)+owner_348->x_ec));
        float desiredY=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(4*owner_348->word_7ac)+params_340[3]*60.0))*(field_380+80.0)+(owner_348->y_f0+100.0));
        double dx=static_cast<double>(desiredX)-x_ec;field_370=static_cast<float>(dx*dx);double dy=static_cast<double>(desiredY)-y_f0;field_374=static_cast<float>(dy*dy);field_378=sqrt_float_value(field_374+field_370);
        params_340[0]=-atan2_degrees(static_cast<float>(desiredY-y_f0),static_cast<float>(desiredX-x_ec));params_340[1]=static_cast<float>(field_378*static_cast<double>(0.2f));if(params_340[1]>50.0f) params_340[1]=50.0f;motion_004.set_components(params_340[0],params_340[1]);if(velocity_x_f4<0.0f) facing_104=-1; else facing_104=1;
        if(time_counter_144>=16) {next_sequence_block();facing_104=owner_348->facing_104;x_ec=static_cast<float>(desiredX);y_f0=static_cast<float>(desiredY);return;}x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;
    }
    if(sequence_index_13e==1) {
        if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(855,static_cast<float>(static_cast<double>(60*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(27);}
        float desiredX=static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(static_cast<double>(4*owner_348->word_7ac)+params_340[3]*60.0))*(field_380*0.25+20.0)+(static_cast<double>(75*owner_348->facing_104)+owner_348->x_ec));
        float desiredY=static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(static_cast<double>(4*owner_348->word_7ac)+params_340[3]*60.0))*(field_380+80.0)+(owner_348->y_f0+100.0));field_380+=2.0;x_ec=static_cast<float>(desiredX);y_f0=desiredY;
    }
    if(sequence_index_13e==1) {if(owner_348->action_id_13c!=605 || owner_348->sequence_index_13e>=3) {field_370=0.0f;field_374=0.0f;field_378=0.0f;next_sequence_block();return;}}
    if(sequence_index_13e==3) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==4) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==5) {
        if(word_364==0) {if(time_counter_144<90) {if(related_34c) {x_ec=static_cast<float>(static_cast<double>(60*facing_104)+related_34c->x_ec);y_f0=static_cast<float>(related_34c->y_f0+5.0);}scale_x_11c=static_cast<float>(static_cast<double>(time_counter_144&2)*static_cast<double>(0.2f)+1.0);scale_y_120=scale_x_11c;}else word_364=1;if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) RETIRE();if(owner_348->action_id_13c!=605 || sequence_index_13e==3) word_364=1;}
        if(word_364==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(scale_x_11c<0.02f) RETIRE();}
    }
    if(sequence_index_13e==6) {
        if(owner_348->action_id_13c<=49 || owner_348->action_id_13c>=150) {if(word_364<=1 && owner_348->action_id_13c!=605) word_364=2;}
        else if(word_364<=1) RETIRE();
        if(word_364==0) {if(related_34c) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;}scale_y_120+=static_cast<double>(0.1f);if(scale_y_120>0.5f) {scale_y_120=0.5f;word_364=1;byte_184=10;return;}}
        if(word_364==1) {if(related_34c) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;if(related_34c->word_364==1) word_364=2;}advance_six(0);if(field_180!=0 && ++word_366>=3) {word_366=0;field_180=0;}}
        if(word_364==2) {byte_184=0;scale_y_120*=static_cast<double>(0.85f);if(scale_y_120<=0.01f) RETIRE();}
    }FINISH();
}


}
case 856: {
 {
    if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150 && sequence_index_13e<=5) select_sequence(6);
    if(sequence_index_13e==0) {motion_004.set_components(params_340[0],params_340[1]);params_340[1]-=1.0;if(params_340[1]<=0.0f) {params_340[1]=0.0f;next_sequence_block();return;}MOVE();}
    if(sequence_index_13e==1 && time_counter_144>=10) {next_sequence_block();return;}
    if(sequence_index_13e==3) {if(time_counter_144==0) {owner_348->dispatch_character_wave_handle(29);float packet[4]={static_cast<float>(static_cast<double>(-8*(static_cast<int>(params_340[3])%4))+60.0),0.0f,8.0f,params_340[3]};spawn_parented(856,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,4);}if(time_counter_144>=120) next_sequence_block();}
    if(sequence_index_13e==5) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==6) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==7 && update_flight_state(6)) return;
    if(sequence_index_13e==8) {
        {double r=rotation_12c;rotation_12c=static_cast<float>(r+field_370);}field_370*=static_cast<double>(0.9f);if(field_180==5 || !related_34c) RETIRE();short phase=related_34c->sequence_index_13e;if(phase==6 || phase==5) RETIRE();if(phase==4) {select_frame(2);return;}
        if(frame_index_140==0 && time_counter_144>=10) {scale_y_120+=static_cast<double>(0.15f);if(scale_y_120>=2.0f) {byte_184=4;scale_y_120=2.0f;next_sequence_frame();}}
        if(frame_index_140==1) {scale_y_120=static_cast<float>(static_cast<double>(time_counter_144&2)*static_cast<double>(0.2f)+2.0);advance_six(0);if(field_180!=0 && ++word_364>=7) {word_364=0;field_180=0;}}
        if(frame_index_140==2) {scale_y_120*=static_cast<double>(0.8f);if(frame_timer_142>=20) RETIRE();}
    }
    if(sequence_index_13e==9) {if(!related_34c) RETIRE();if(word_364==0) {scale_x_11c=static_cast<float>(static_cast<double>(time_counter_144%2)*static_cast<double>(0.2f)+1.0);scale_y_120=scale_x_11c;if(related_34c->frame_index_140==2) word_364=1;}if(word_364==1) {scale_y_120*=static_cast<double>(0.9f);if(frame_timer_142>=60) RETIRE();}}
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) {TURN_TO_OWNER();}return;
}


}
case 857: {

    if(sequence_index_13e==0 || sequence_index_13e==1) {
        if(owner_348->word_174<=0) {select_sequence(5);return;}
        if(sequence_index_13e==0) {params_340[1]-=2.0;if(params_340[1]<0.0f) {params_340[1]=0.0f;next_sequence_block();return;}}
        if(sequence_index_13e==1) {
            if(time_counter_144==10) {owner_348->dispatch_character_wave_handle(30);AliceUpdateOwnerView *target = target_170;field_370=-atan2_degrees(static_cast<float>(target->y_f0+100.0-y_f0),static_cast<float>((target->x_ec-static_cast<double>(x_ec))*facing_104));float packet[3]={0.0f,0.0f,3.0f};spawn_parented(857,static_cast<float>(static_cast<double>(40*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);packet[0]=field_370;packet[1]=0.0f;packet[2]=2.0f;spawn_parented(857,static_cast<float>(static_cast<double>(40*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,-1,packet,3);}
            if(time_counter_144==20) {owner_348->dispatch_character_wave_handle(30);float packet[3]={static_cast<float>(field_370-90.0),0.0f,2.0f};spawn_parented(857,static_cast<float>(static_cast<double>(40*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,-1,packet,3);}
            if(time_counter_144==30) {owner_348->dispatch_character_wave_handle(30);float packet[3]={static_cast<float>(field_370-180.0),0.0f,2.0f};spawn_parented(857,static_cast<float>(static_cast<double>(40*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,-1,packet,3);}
            if(time_counter_144==40) {owner_348->dispatch_character_wave_handle(30);float packet[3]={static_cast<float>(field_370-270.0),0.0f,2.0f};spawn_parented(857,static_cast<float>(static_cast<double>(40*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,-1,packet,3);}
            if(time_counter_144>=150) {select_sequence(8);field_370=0.0f;return;}
        }motion_004.set_components(params_340[0],params_340[1]);MOVE();
    }
    if(sequence_index_13e==2) {
        if(!related_34c) RETIRE();
        if(word_364==0) {x_ec=static_cast<float>(static_cast<double>(40*facing_104)+related_34c->x_ec);y_f0=static_cast<float>(related_34c->y_f0+5.0);if(related_34c->sequence_index_13e!=1) word_364=2;
            if(word_364==0) {scale_y_120+=static_cast<double>(0.05f);if(scale_y_120>=1.0f) {scale_y_120=1.0f;byte_184=1;word_364=1;}if(!related_34c || related_34c->sequence_index_13e!=1) word_364=2;}
        }
        if(word_364==1) {advance_six(0);if(field_180!=0 && ++word_366>=5) {field_180=0;byte_184=1;word_366=0;}if(!related_34c || related_34c->sequence_index_13e!=1) word_364=2;}
        if(word_364==2) {byte_184=0;scale_y_120*=static_cast<double>(0.85f);if(byte_113<8) RETIRE();byte_113-=8;byte_110-=8;byte_111-=8;}
    }
    if(sequence_index_13e==3) {
        if(word_364==0) {
            scale_x_11c=static_cast<float>((1.0-field_370)*0.75+0.25);scale_y_120=scale_x_11c;field_370*=static_cast<double>(0.95f);
            if(field_370<=0.75f) {if(field_180==0) byte_184=1;advance_six(0);advance_phase(0);if(field_180!=0 && ++word_366>=5) {field_180=0;byte_184=1;word_366=0;}}
            if(time_counter_144%15==0) {float packet[3]={0.0f,0.0f,4.0f};spawn_parented(857,x_ec,y_f0,facing_104,1,packet,3);}
            if(!related_34c) word_364=1;else {x_ec=static_cast<float>(static_cast<double>(40*facing_104)+related_34c->x_ec);y_f0=static_cast<float>(related_34c->y_f0+5.0);scale_x_11c=static_cast<float>(static_cast<double>(time_counter_144%2)*static_cast<double>(0.1f)+1.0);scale_y_120=scale_x_11c;short phase=related_34c->sequence_index_13e;if(phase==5 || phase==6 || phase==8) word_364=1;}
        }
        if(word_364==1) {scale_x_11c*=static_cast<double>(0.97f);scale_y_120=scale_x_11c;if(byte_113<8) RETIRE();byte_113-=8;byte_110-=8;byte_111-=8;}
    }
    if(sequence_index_13e==4) {if(!related_34c) RETIRE();x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;scale_x_11c+=static_cast<double>(0.2f);scale_y_120=scale_x_11c;if(byte_113<8) RETIRE();byte_113-=8;}
    if(sequence_index_13e==5) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;}
    if(sequence_index_13e==6) {if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
    if(sequence_index_13e==7 && update_flight_state(5)) return;
    if(sequence_index_13e==8) {if(owner_348->word_174<=0) {select_sequence(5);return;}if(time_counter_144>=30) {select_sequence(6);return;}}
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==5) {TURN_TO_OWNER();}return;


}
case 858: {
 {
    if(sequence_index_13e!=15 && sequence_index_13e<=19) {if(owner_348->action_id_13c>=50 && owner_348->action_id_13c<=149) {select_sequence(15);velocity_x_f4=0.0f;velocity_y_f8=0.0f;return;}}
    if(sequence_index_13e!=15 && sequence_index_13e!=16 && sequence_index_13e<=19) {if(owner_348->action_id_13c!=608 || owner_348->sequence_index_13e>1) {rotation_12c=0.0f;select_sequence(16);velocity_x_f4=0.0f;velocity_y_f8=0.0f;return;}}
    switch(sequence_index_13e) {
    case 0:case 1: {
        if(owner_348->input_x_6b4>0 && facing_104 == -1) {facing_104=1;velocity_x_f4=-velocity_x_f4;}if(owner_348->input_x_6b4<0 && facing_104 == 1) {facing_104=-1;velocity_x_f4=-velocity_x_f4;}
        if(owner_348->input_x_6b4*facing_104>0) {velocity_x_f4+=2.0;if(velocity_x_f4>10.0f) velocity_x_f4=10.0f;}else {velocity_x_f4-=2.0;if(velocity_x_f4<0.0f) velocity_x_f4=0.0f;}
        if(owner_348->input_y_6b8<0) {velocity_y_f8+=2.0;if(velocity_y_f8>10.0f) velocity_y_f8=10.0f;}if(owner_348->input_y_6b8>0) {velocity_y_f8-=2.0;if(velocity_y_f8<-10.0f) velocity_y_f8=-10.0f;}
        if(owner_348->input_y_6b8==0) {if(velocity_y_f8>0.0f) {velocity_y_f8-=2.0;if(velocity_y_f8<0.0f) velocity_y_f8=0.0f;}else {velocity_y_f8+=2.0;if(velocity_y_f8>0.0f) velocity_y_f8=0.0f;}}
        if(sequence_index_13e==0 && velocity_x_f4>5.0f) select_sequence(1);if(sequence_index_13e==1 && velocity_x_f4<5.0f) select_sequence(0);
        if(owner_348->input_a_6bc>0 && owner_348->input_a_6bc<4) {
            if(owner_348->input_x_6b4==0 && owner_348->input_y_6b8==0) {word_364=0;byte_184=1;select_sequence(2);return;}
            if(owner_348->input_x_6b4*facing_104>0 && owner_348->input_y_6b8==0) {word_364=0;byte_184=1;select_sequence(3);return;}
            if(owner_348->input_x_6b4*facing_104>0 && owner_348->input_y_6b8>0) {word_364=0;byte_184=1;select_sequence(6);return;}if(owner_348->input_x_6b4*facing_104==0 && owner_348->input_y_6b8>0) {word_364=0;byte_184=1;select_sequence(6);return;}
            if(owner_348->input_x_6b4*facing_104==0 && owner_348->input_y_6b8<0) {word_364=0;byte_184=4;velocity_x_f4=0.0f;velocity_y_f8=0.0f;select_sequence(9);return;}
        }
        if(owner_348->input_b_6c0>0 && owner_348->input_b_6c0<4) {word_364=0;byte_184=0;select_sequence(11);return;}if(owner_348->input_c_6c4>0 && owner_348->input_c_6c4<4) {word_364=0;byte_184=0;select_sequence(13);return;}
        x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;if(y_f0<=0.0f) y_f0=0.0f;if(x_ec>1260.0f) x_ec=1260.0f;if(x_ec<20.0f) x_ec=20.0f;break;
    }
    case 2: {
        if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) {velocity_x_f4=30.0f;velocity_y_f8=2.0f;}velocity_x_f4-=3.0;if(velocity_x_f4<=1.0f) velocity_x_f4=1.0f;velocity_y_f8-=0.5;if(velocity_y_f8<0.5f) velocity_y_f8=0.5f;
        if(frame_index_140>=2 && time_counter_144%2==0 && frame_index_140>=1) {field_378=static_cast<float>(static_cast<double>(RF(90))-45.0);float packet[3]={field_378,0.0f,21.0f};spawn_unparented(858,static_cast<float>(lookup_orientation_cosine_quantized_abs(-field_378)*100.0*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(-field_378)*100.0+y_f0),facing_104,1,packet,3);}
        if(owner_348->input_a_6bc>0 && owner_348->input_a_6bc<4 && field_180!=0) {if(owner_348->input_x_6b4*facing_104>0 && owner_348->input_y_6b8==0) {word_364=0;byte_184=1;select_sequence(3);return;}if(owner_348->input_x_6b4*facing_104>0 && owner_348->input_y_6b8>0) {word_364=0;byte_184=1;select_sequence(6);return;}if(owner_348->input_x_6b4*facing_104==0 && owner_348->input_y_6b8>0) {word_364=0;byte_184=1;select_sequence(6);return;}if(owner_348->input_x_6b4*facing_104==0 && owner_348->input_y_6b8<0) {word_364=0;byte_184=4;velocity_x_f4=0.0f;velocity_y_f8=0.0f;select_sequence(9);return;}}
        if(owner_348->input_b_6c0>0 && owner_348->input_b_6c0<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(11);return;}if(owner_348->input_c_6c4>0 && owner_348->input_c_6c4<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(13);return;}
        x_ec=facing_104*velocity_x_f4+x_ec;y_f0+=velocity_y_f8;if(y_f0<=0.0f) y_f0=0.0f;if(x_ec>1260.0f) x_ec=1260.0f;if(x_ec<20.0f) x_ec=20.0f;break;
    }
    case 3:case 4:case 5: {
        if(sequence_index_13e==4 && time_counter_144>=16) {next_sequence_block();return;}if(sequence_index_13e>=4) {velocity_x_f4-=3.0;if(velocity_x_f4<=0.5f) velocity_x_f4=0.5f;}
        if(owner_348->input_b_6c0>0 && owner_348->input_b_6c0<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(11);return;}if(owner_348->input_c_6c4>0 && owner_348->input_c_6c4<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(13);return;}x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;if(y_f0<=0.0f) y_f0=0.0f;if(x_ec>1260.0f) x_ec=1260.0f;if(x_ec<20.0f) x_ec=20.0f;break;
    }
    case 6:
        rotation_12c+=40.0;velocity_x_f4-=1.0;if(velocity_x_f4<0.0f) velocity_x_f4=0.0f;if(velocity_y_f8>0.0f) {velocity_y_f8-=1.0;if(velocity_y_f8<0.0f) velocity_y_f8=0.0f;}else {velocity_y_f8+=1.0;if(velocity_y_f8>0.0f) velocity_y_f8=0.0f;}
        if(time_counter_144>=9) {rotation_12c=0.0f;next_sequence_block();owner_348->dispatch_character_wave_handle(7);float packet[3]={45.0f,25.0f,22.0f};spawn_unparented(858,static_cast<float>(static_cast<double>(105*facing_104)+x_ec),static_cast<float>(y_f0-105.0),facing_104,1,packet,3);params_340[0]=45.0f;params_340[1]=35.0f;byte_184=1;field_180=0;return;}
        x_ec=facing_104*velocity_x_f4+x_ec;y_f0+=velocity_y_f8;if(y_f0<=0.0f) y_f0=0.0f;if(x_ec>1260.0f) x_ec=1260.0f;if(x_ec<20.0f) x_ec=20.0f;break;
    case 7: {
        params_340[1]-=2.0;if(params_340[1]<-0.5f) {params_340[1]=-0.5f;byte_184=0;}motion_004.set_components(params_340[0],params_340[1]);if(time_counter_144>=20) {next_sequence_block();return;}
        if(owner_348->input_b_6c0>0 && owner_348->input_b_6c0<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(11);return;}if(owner_348->input_c_6c4>0 && owner_348->input_c_6c4<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(13);return;}x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;if(y_f0<=0.0f) y_f0=0.0f;if(x_ec>1260.0f) x_ec=1260.0f;if(x_ec<20.0f) x_ec=20.0f;break;
    }
    case 8: {
        params_340[1]-=5.0;if(params_340[1]<-0.5f) {params_340[1]=-0.5f;byte_184=0;}motion_004.set_components(params_340[0],params_340[1]);if(time_counter_144>=30) {select_sequence(0);return;}
        if(owner_348->input_b_6c0>0 && owner_348->input_b_6c0<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(11);return;}if(owner_348->input_c_6c4>0 && owner_348->input_c_6c4<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(13);return;}x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;if(y_f0<=0.0f) y_f0=0.0f;if(x_ec>1260.0f) x_ec=1260.0f;if(x_ec<20.0f) x_ec=20.0f;break;
    }
    case 9:
        velocity_x_f4-=1.0;if(velocity_x_f4<0.0f) velocity_x_f4=0.0f;if(velocity_y_f8>0.0f) {velocity_y_f8-=1.0;if(velocity_y_f8<0.0f) velocity_y_f8=0.0f;}else {velocity_y_f8+=1.0;if(velocity_y_f8>0.0f) velocity_y_f8=0.0f;}x_ec=facing_104*velocity_x_f4+x_ec;y_f0+=velocity_y_f8;if(y_f0<=0.0f) y_f0=0.0f;if(x_ec>1260.0f) x_ec=1260.0f;if(x_ec<20.0f) x_ec=20.0f;break;
    case 10: {
        if(time_counter_144==0) {float packet[3]={0.0f,0.0f,23.0f};spawn_parented(858,x_ec,y_f0,facing_104,1,packet,3);}if(time_counter_144%15==0) owner_348->dispatch_character_wave_handle(4);if(field_180!=0 && ++word_364>=4) {word_364=0;field_180=0;}
        if(time_counter_144>=45) {select_sequence(0);if(x_ec-owner_348->x_ec>0.0f) facing_104=1;if(x_ec-owner_348->x_ec<0.0f) facing_104=-1;return;}
        velocity_y_f8*=static_cast<double>(0.95f);if(owner_348->input_b_6c0>0 && owner_348->input_b_6c0<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(11);return;}if(owner_348->input_c_6c4>0 && owner_348->input_c_6c4<4 && field_180!=0) {word_364=0;byte_184=0;select_sequence(13);return;}x_ec=facing_104*velocity_x_f4+x_ec;y_f0+=velocity_y_f8;if(y_f0<=0.0f) y_f0=0.0f;if(x_ec>1260.0f) x_ec=1260.0f;if(x_ec<20.0f) x_ec=20.0f;break;
    }
    case 11:velocity_x_f4=0.0f;velocity_y_f8=0.0f;word_364=0;break;
    case 12:
        if(time_counter_144%3==0 && word_364<=6) {owner_348->dispatch_character_wave_handle(0);++word_364;AliceUpdateOwnerView *target = target_170;field_378=-atan2_degrees(static_cast<float>(target->y_f0+100.0-y_f0),static_cast<float>((target->x_ec-static_cast<double>(x_ec))*facing_104));if(field_378<-30.0f) field_378=-30.0f;if(field_378>30.0f) field_378=30.0f;
            float packet[3];packet[0]=static_cast<float>(static_cast<double>(RF(20))+field_378-10.0);packet[1]=12.5f;packet[2]=static_cast<float>(static_cast<double>(word_364%7)+26.0);spawn_unparented(858,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);packet[2]=static_cast<float>(static_cast<double>(word_364%7)+7.0);spawn_unparented(800,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(0);
        }
        if(time_counter_144>=18 && owner_348->input_c_6c4>0 && owner_348->input_c_6c4<4) {word_364=0;byte_184=0;select_sequence(13);return;}if(time_counter_144>=40) select_sequence(0);break;
    case 13: {
        word_364=0;if(owner_348->input_x_6b4*facing_104>0) {velocity_x_f4+=1.0;if(velocity_x_f4>2.0f) velocity_x_f4=2.0f;}else velocity_x_f4=0.0f;
        if(owner_348->input_y_6b8<0) {velocity_y_f8+=1.0;if(velocity_y_f8>2.0f) velocity_y_f8=2.0f;}if(owner_348->input_y_6b8>0) {velocity_y_f8-=1.0;if(velocity_y_f8<-2.0f) velocity_y_f8=-2.0f;}if(owner_348->input_y_6b8==0) velocity_y_f8=0.0f;x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    }
    case 14: {
        if(owner_348->input_x_6b4*facing_104>0) {velocity_x_f4+=1.0;if(velocity_x_f4>2.0f) velocity_x_f4=2.0f;}else if(owner_348->input_x_6b4*facing_104<0) {velocity_x_f4-=1.0;if(velocity_x_f4<-2.0f) velocity_x_f4=-2.0f;}else velocity_x_f4=0.0f;
        if(owner_348->input_y_6b8<0) {velocity_y_f8+=1.0;if(velocity_y_f8>2.0f) velocity_y_f8=2.0f;}if(owner_348->input_y_6b8>0) {velocity_y_f8-=1.0;if(velocity_y_f8<-2.0f) velocity_y_f8=-2.0f;}if(owner_348->input_y_6b8==0) velocity_y_f8=0.0f;
        if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==14) {owner_348->dispatch_character_wave_handle(9);float packet[3]={0.0f,0.0f,33.0f};spawn_parented(858,static_cast<float>(static_cast<double>(20*facing_104)+x_ec),static_cast<float>(y_f0+5.0),facing_104,1,packet,3);}if(time_counter_144>=60) select_sequence(0);x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    }
    case 15:if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;rotation_12c+=15.0;if(byte_113<20) RETIRE();byte_113-=20;x_ec=facing_104*velocity_x_f4+x_ec;y_f0+=velocity_y_f8;break;
    case 16:if(update_owner_tracking_and_proximity()) return;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    case 20:if(update_flight_state(15)) return;break;
    case 21:scale_x_11c+=static_cast<double>(0.01f);scale_y_120*=static_cast<double>(0.8f);if(scale_y_120<=0.05f) RETIRE();motion_004.set_components(params_340[0],15.0f);x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    case 22:scale_x_11c+=static_cast<double>(0.05f);scale_y_120*=static_cast<double>(0.85f);if(scale_y_120<=0.01f) RETIRE();x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    case 23: {
        rotation_12c+=25.0;if(!related_34c) RETIRE();x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;
        if(related_34c->sequence_index_13e!=10) {if(byte_113<20) RETIRE();scale_x_11c+=static_cast<double>(0.1f);byte_113-=20;byte_112-=20;byte_111-=20;}else {scale_x_11c+=static_cast<double>(0.1f);if(scale_x_11c>3.0f) scale_x_11c=2.5f;scale_y_120=scale_x_11c;if(byte_113<=225) byte_113+=30;else byte_113=255;}x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;
    }
    case 24:if(!related_34c) RETIRE();{x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;short phase=related_34c->sequence_index_13e;if(phase==15 || phase==16) RETIRE();}break;
    case 26:case 27:case 28:case 29:case 30:case 31:case 32:
        if(frame_index_140==0) {if(emit_repeated(0,0,4)) RETIRE();if(field_180!=0) {next_sequence_frame();float packet[3]={0.0f,0.0f,static_cast<float>(sequence_index_13e+7)};spawn_unparented(800,x_ec,y_f0,facing_104,1,packet,3);return;}if(x_ec>1380.0f || x_ec<-100.0f || y_f0>1000.0f || y_f0<-160.0f) RETIRE();motion_004.set_components(params_340[0],params_340[1]);x_ec=facing_104*velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;}
        if(frame_index_140==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(byte_113<=20) RETIRE();byte_113-=20;}break;
    case 33:
        if(related_34c) {if(word_364==0) {if(related_34c->sequence_index_13e!=14) word_364=1;if(time_counter_144<45) {x_ec=static_cast<float>(static_cast<double>(60*facing_104)+related_34c->x_ec);y_f0=static_cast<float>(related_34c->y_f0+5.0);scale_x_11c=static_cast<float>(static_cast<double>(time_counter_144&2)*static_cast<double>(0.2f)+1.0);scale_y_120=scale_x_11c;}else word_364=1;if(owner_348->action_id_13c>49 && owner_348->action_id_13c<150) RETIRE();}}else word_364=1;
        if(word_364==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(scale_x_11c<0.02f) RETIRE();}break;
    case 34:
        if(related_34c) {
            if(word_364<=1 && related_34c->word_364==1) word_364=2;
            if(word_364==0) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;scale_y_120+=static_cast<double>(0.1f);if(scale_y_120>0.75f) {scale_y_120=0.75f;word_364=1;byte_184=10;return;}}
            if(word_364==1) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;if(related_34c->word_364==1) word_364=2;advance_six(0);if(field_180!=0 && ++word_366>=3) {word_366=0;field_180=0;}}
        }else word_364=2;
        if(word_364==2) {byte_184=0;scale_y_120*=static_cast<double>(0.85f);if(scale_y_120<=0.01f) RETIRE();}break;
    }
    advance_frame();
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==3) {select_sequence(0);return;}
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) {float packet[3]={0.0f,0.0f,22.0f};spawn_unparented(858,static_cast<float>(static_cast<double>(40*facing_104)+x_ec),y_f0,facing_104,1,packet,3);byte_184=1;field_180=0;owner_348->dispatch_character_wave_handle(29);velocity_x_f4=40.0f;velocity_y_f8=0.0f;}
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==6) {select_sequence(0);return;}
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==9) {select_sequence(0);return;}
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==10) {velocity_y_f8=15.0f;word_364=0;}
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==11) {select_sequence(0);return;}
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==13) {select_sequence(0);return;}
    if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==15) {select_sequence(0);return;}
    if(sequence_index_13e==2) {if(frame_index_140>=2 && frame_index_140<=6) {if(frame_timer_142!=0) return;byte_184=1;if(field_180!=0) word_364=1;field_180=0;}if(frame_timer_142==0 && frame_index_140==8 && word_364>0) field_180=1;}return;
}


}
case 859: {
 {
    short entryPhase=sequence_index_13e;switch(entryPhase) {
    case 1:case 2: {
        if(owner_348->action_id_13c!=609 || owner_348->sequence_index_13e!=1) {select_sequence(3);return;}
        if(entryPhase==2) {advance_six(0);advance_phase(0);if(field_180!=0 && ++word_364>4) {word_364=0;byte_184=1;field_180=0;}if(time_counter_144%3==0) {float packet[3];packet[0]=RF(360);packet[1]=static_cast<float>(static_cast<double>(RF(15))+5.0);packet[2]=6.0f;spawn_unparented(859,x_ec,y_f0,facing_104,-1,packet,3);}}break;
    }
    case 3:if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<10) RETIRE();byte_113-=10;break;
    case 4: {
        advance_six(0);advance_phase(0);if(owner_348->action_id_13c!=609 || owner_348->sequence_index_13e!=1) RETIRE();publish_bounds_descriptor(0,10,static_cast<int>(scale_x_11c*256.0),-10,static_cast<short>(static_cast<int>(rotation_12c)),0,0);if(update_flight_state(6)) return;if(field_180!=0 && ++word_364>4) {word_364=0;byte_184=1;field_180=0;}break;
    }
    case 5:
        if(word_364==0) {if(related_34c && related_34c->sequence_index_13e==2) {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;}else word_364=1;}
        else {scale_x_11c*=static_cast<double>(0.98f);scale_y_120=scale_x_11c;if(byte_113<6) RETIRE();byte_113-=6;byte_110-=6;byte_111-=6;}break;
    case 6:motion_004.set_components(params_340[0],params_340[1]);params_340[1]*=static_cast<double>(0.95f);scale_x_11c*=static_cast<double>(0.99f);scale_y_120=scale_x_11c;if(byte_113<6) RETIRE();byte_113-=6;byte_110-=6;byte_111-=6;MOVE();break;
    }
    if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==2) {float packet[3]={0.0f,0.0f,5.0f};spawn_parented(859,x_ec,y_f0,facing_104,-1,packet,3);}return;
}


}
case 900: {

    if(field_180==5) RETIRE();
    switch(sequence_index_13e) {
    case 0:
        if(owner_348->word_174<=0 || word_174<-500) {select_sequence(2);return;}
        if(time_counter_144>=60) {next_sequence_block();owner_348->dispatch_character_wave_handle(34);AliceUpdateOwnerView *target = target_170;double aim=atan2_degrees(static_cast<float>(target->y_f0+100.0-y_f0),static_cast<float>((target->x_ec-static_cast<double>(x_ec))*facing_104));params_340[0]=static_cast<float>(15.0-aim-static_cast<double>(RF(30)));params_340[1]=0.0f;if(params_340[0]>60.0f) params_340[0]=60.0f;if(params_340[0]<-60.0f) params_340[0]=-60.0f;return;}
        velocity_y_f8*=static_cast<double>(0.9f);velocity_x_f4=static_cast<float>(static_cast<double>(0.9f)*velocity_x_f4);x_ec=static_cast<float>(velocity_x_f4*static_cast<double>(facing_104)+x_ec);y_f0+=velocity_y_f8;break;
    case 1: {
        if(owner_348->word_174<=0 || word_174<-500) {select_sequence(2);return;}
        if(time_counter_144%3==0) {float packet[3]={0.0f,0.0f,6.0f};spawn_unparented(900,x_ec,y_f0,facing_104,-1,packet,3);}
        if(static_cast<double>(y_f0)+velocity_y_f8<=stage_surface_height() || word_174<0 || square_float_value(target_170->x_ec-x_ec)+square_float_value(static_cast<float>(target_170->y_f0+100.0-y_f0))<=2500.0) {
            publish_battle_layout_scalar(5.0f);next_sequence_block();float packet[3]={0.0f,0.0f,3.0f};spawn_unparented(900,x_ec,y_f0,facing_104,1,packet,3);owner_348->dispatch_character_wave_handle(6);velocity_y_f8=static_cast<float>(static_cast<double>(RF(5))+8.0);velocity_x_f4*=static_cast<double>(0.2f);return;
        }
        if((x_ec>1580.0f || x_ec<-300.0f || y_f0>1000.0f)) RETIRE();
        switch(g_match_identifier) {
        case 3:{turn_heading(0.0f,1.5f,100.0f);params_340[1]+=0.5;if(params_340[0]>90.0f) params_340[0]=90.0f;if(params_340[0]<-90.0f) params_340[0]=-90.0f;if(params_340[1]>=30.0f) params_340[1]=30.0f;break;}
        case 2:{turn_heading(0.0f,1.0f,100.0f);params_340[1]+=static_cast<double>(0.4f);if(params_340[0]>90.0f) params_340[0]=90.0f;if(params_340[0]<-90.0f) params_340[0]=-90.0f;if(params_340[1]>=25.0f) params_340[1]=25.0f;break;}
        case 1:{turn_heading(0.0f,0.5f,100.0f);params_340[1]+=static_cast<double>(0.3f);if(params_340[0]>90.0f) params_340[0]=90.0f;if(params_340[0]<-90.0f) params_340[0]=-90.0f;if(params_340[1]>=20.0f) params_340[1]=20.0f;break;}
        case 0:{turn_heading(0.0f,0.25f,100.0f);params_340[1]+=static_cast<double>(0.3f);if(params_340[0]>90.0f) params_340[0]=90.0f;if(params_340[0]<-90.0f) params_340[0]=-90.0f;if(params_340[1]>=15.0f) params_340[1]=15.0f;break;}
        }motion_004.set_components(params_340[0],params_340[1]);x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    }
    case 2:rotation_12c+=15.0;if(byte_113<=5) RETIRE();byte_113-=5;velocity_y_f8-=0.5;x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;break;
    case 3:advance_six(0);advance_phase(0);scale_x_11c-=static_cast<double>(0.01f);scale_y_120=scale_x_11c;if(byte_113<=10) RETIRE();byte_113-=10;byte_111-=10;byte_110-=10;break;
    case 4:scale_x_11c+=static_cast<double>(0.02f);scale_y_120=scale_x_11c;if(time_counter_144>0) {if(byte_110<=20) {byte_111-=20;byte_110-=20;}else {if(byte_113<=20) RETIRE();byte_111=0;byte_110=0;byte_113-=20;}}break;
    case 5:scale_x_11c+=static_cast<double>(0.1f);scale_y_120=scale_x_11c;if(time_counter_144>=0) {if(byte_110>=30) {byte_111-=30;byte_110-=30;}else {byte_111=0;byte_110=0;}if(byte_113<25) RETIRE();byte_113-=25;}break;
    case 6:scale_x_11c*=static_cast<double>(0.9f);scale_y_120=scale_x_11c;if(byte_113<10) RETIRE();byte_113-=10;break;
    }FINISH();


}
case 901: {

    if(sequence_index_13e==0) {
        if(word_174<=-500 || owner_348->word_174<=0) select_sequence(1);
        if(time_counter_144==0) {float packet[3]={0.0f,0.0f,params_340[3]==0.0f?3.0f:4.0f};spawn_parented(901,x_ec,y_f0,facing_104,1,packet,3);}advance_six(0);if(field_180!=0 && ++word_368>=3) {word_368=0;byte_184=1;field_180=0;}
        if(word_364==0) {params_340[1]-=static_cast<double>(0.1f);if(params_340[1]<1.0f) {params_340[1]=1.0f;word_364=1;}motion_004.set_components(params_340[0],params_340[1]);MOVE();}
        if(word_364==1) {if(++word_366>=30) {byte_184=1;field_180=0;word_364=2;}motion_004.set_components(params_340[0],params_340[1]);MOVE();}
        if(word_364==2) {params_340[0]=-atan2_degrees(static_cast<float>(owner_348->y_f0+100.0-y_f0),owner_348->x_ec-x_ec);params_340[1]+=0.25;if(field_370>6.0f) field_370=6.0f;motion_004.set_components(params_340[0],params_340[1]);x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;double dySquared=square_float_value(static_cast<float>(owner_348->y_f0+100.0-y_f0));if(square_float_value(owner_348->x_ec-x_ec)+dySquared<=400.0) RETIRE();}
    }
    if(sequence_index_13e==1) {if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<10) RETIRE();byte_113-=10;}
    if(sequence_index_13e==2 && update_flight_state(1)) return;
    short phase=sequence_index_13e;if(phase==3 || phase==4) {
        if(related_34c) {if(related_34c->sequence_index_13e!=0) {if(byte_113<10) RETIRE();scale_x_11c+=static_cast<double>(0.1f);byte_113-=10;}else {x_ec=related_34c->x_ec;y_f0=related_34c->y_f0;nextY=static_cast<float>(scale_x_11c+static_cast<double>(0.1f));scale_x_11c=nextY;if(nextY>2.5f) scale_x_11c=2.0f;scale_y_120=scale_x_11c;if(byte_113<=225) byte_113+=30;else byte_113=255;}}
        else {if(byte_113<15) RETIRE();scale_x_11c+=static_cast<double>(0.1f);scale_y_120=scale_x_11c;byte_113-=15;}rotation_12c+=25.0;
    }FINISH();


}
case 902: {
 {
    short phase=sequence_index_13e;if(phase<=3 && owner_348->word_174<=0) {select_sequence(4);return;}
    switch(phase) {
    case 0:case 1: {params_340[1]*=static_cast<double>(0.9f);motion_004.set_components(params_340[0],params_340[1]);rotation_12c+=25.0;x_ec=velocity_x_f4+x_ec;y_f0=velocity_y_f8+y_f0;break;}
    case 2: {
        if(time_counter_144>=400) {next_sequence_block();return;}
        float dx=x_ec-field_370;float dy=y_f0-field_374;float radius=sqrt_float_value(dy*dy+dx*dx);velocity_x_f4=static_cast<float>((dx-dy*static_cast<double>(facing_104)*3.0)/radius);velocity_y_f8=static_cast<float>((dy-dx*static_cast<double>(facing_104)*-3.0)/radius);float angle=static_cast<float>(90.0-atan2_degrees(velocity_y_f8,facing_104*velocity_x_f4));params_340[0]=angle;rotation_12c=angle;
        if(time_counter_144%2==0) {field_378=static_cast<float>(static_cast<double>(RF(90))+params_340[0]-45.0);float packet[3]={field_378,0.0f,5.0f};spawn_unparented(902,static_cast<float>(lookup_orientation_cosine_quantized_abs(-field_378)*100.0*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(-field_378)*100.0+y_f0),facing_104,1,packet,3);}
        switch(g_match_identifier) {
        case 3:if(time_counter_144%6==0) {field_378=static_cast<float>(static_cast<double>(RF(20))+params_340[0]-10.0);float packet[3];packet[0]=field_378;packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+7.0);packet[2]=static_cast<float>(word_368%7);spawn_unparented(903,static_cast<float>(lookup_orientation_cosine_quantized_abs(-field_378)*50.0*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(-field_378)*50.0+y_f0),facing_104,1,packet,3);++word_368;owner_348->dispatch_character_wave_handle(0);}break;
        case 2:if(time_counter_144%6==0) {field_378=static_cast<float>(static_cast<double>(RF(20))+params_340[0]-10.0);float packet[3];packet[0]=field_378;packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+7.0);packet[2]=static_cast<float>(word_368%7);spawn_unparented(903,static_cast<float>(lookup_orientation_cosine_quantized_abs(-field_378)*50.0*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(-field_378)*50.0+y_f0),facing_104,1,packet,3);++word_368;owner_348->dispatch_character_wave_handle(0);}break;
        case 1:if(time_counter_144%6==0) {field_378=static_cast<float>(static_cast<double>(RF(20))+params_340[0]-10.0);float packet[3];packet[0]=field_378;packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+7.0);packet[2]=static_cast<float>(word_368%7);spawn_unparented(903,static_cast<float>(lookup_orientation_cosine_quantized_abs(-field_378)*50.0*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(-field_378)*50.0+y_f0),facing_104,1,packet,3);++word_368;owner_348->dispatch_character_wave_handle(0);}break;
        case 0:if(time_counter_144%6==0) {field_378=static_cast<float>(static_cast<double>(RF(20))+params_340[0]-10.0);float packet[3];packet[0]=field_378;packet[1]=static_cast<float>(RF(60)*static_cast<double>(0.1f)+7.0);packet[2]=static_cast<float>(word_368%7);spawn_unparented(903,static_cast<float>(lookup_orientation_cosine_quantized_abs(-field_378)*50.0*static_cast<double>(facing_104)+x_ec),static_cast<float>(lookup_orientation_sine_quantized_abs(-field_378)*50.0+y_f0),facing_104,1,packet,3);++word_368;owner_348->dispatch_character_wave_handle(0);}break;
        }
        if(field_180!=0 && ++word_364>=5) {word_364=0;byte_184=1;field_180=0;}x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;break;
    }
    case 3: {float dx=x_ec-field_370;float dy=y_f0-field_374;float radius=sqrt_float_value(dy*dy+dx*dx);velocity_x_f4=static_cast<float>((dx-dy*static_cast<double>(facing_104)*3.0)/radius);velocity_y_f8=static_cast<float>((dy-dx*static_cast<double>(facing_104)*-3.0)/radius);float angle=static_cast<float>(90.0-atan2_degrees(velocity_y_f8,facing_104*velocity_x_f4));params_340[0]=angle;rotation_12c=angle;if(byte_113>=5) byte_113-=5;else RETIRE();break;}
    case 4:if(velocity_x_f4>5.0f) velocity_x_f4=5.0f;if(velocity_x_f4<-5.0f) velocity_x_f4=-5.0f;if(velocity_y_f8>5.0f) velocity_y_f8=5.0f;if(velocity_y_f8<-5.0f) velocity_y_f8=-5.0f;velocity_y_f8-=0.5;x_ec=velocity_x_f4+x_ec;y_f0+=velocity_y_f8;rotation_12c+=15.0;if(byte_113<10) RETIRE();byte_113-=10;break;
    case 5:scale_x_11c+=static_cast<double>(0.01f);scale_y_120*=static_cast<double>(0.8f);if(scale_y_120<=0.05f) RETIRE();motion_004.set_components(params_340[0],15.0f);MOVE();break;
    }FINISH();
}


}
case 903: {
 {
    int collision=field_180;if(collision==5) RETIRE();
    if(sequence_index_13e<=6) {if(frame_index_140==0) {if(collision!=0 || time_counter_144>=60) {next_sequence_frame();return;}if(x_ec>1380.0f || x_ec<-100.0f || y_f0>1000.0f || y_f0<-160.0f) RETIRE();motion_004.set_components(params_340[0],params_340[1]);MOVE();}if(frame_index_140==1) {scale_x_11c*=static_cast<double>(0.85f);scale_y_120=scale_x_11c;if(byte_113<=20) RETIRE();byte_113-=20;}}
    else {scale_x_11c*=static_cast<double>(0.9f);scale_y_120=scale_x_11c;if(byte_113<=10) RETIRE();byte_113-=10;}FINISH();
}


}
case 980: {
update_ping_pong_motion();FINISH();


}
case 998: {

    if(sequence_index_13e==0) {

        if(owner_348->action_id_13c>153 && owner_348->action_id_13c<158) {x_ec=static_cast<float>(static_cast<double>(60*facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+60.0);}
        if(owner_348->action_id_13c>149 && owner_348->action_id_13c<154) {x_ec=static_cast<float>(static_cast<double>(60*facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+110.0);}
        if(owner_348->action_id_13c==158) {x_ec=static_cast<float>(static_cast<double>(60*facing_104)+owner_348->x_ec);y_f0=static_cast<float>(owner_348->y_f0+100.0);}
        if(owner_348->action_id_13c<150 || owner_348->action_id_13c>158) {next_sequence_block();owner_348->byte_751=0;}
    }
    if(sequence_index_13e==1) {if(byte_113<10) RETIRE();byte_111-=10;byte_110-=10;byte_113-=10;}FINISH();


}
case 999: {
 {
    short phase=sequence_index_13e;switch(phase) {
    case 0: {velocity_y_f8-=static_cast<double>(0.3f);if(static_cast<double>(y_f0)+velocity_y_f8<=stage_surface_height()) {owner_348->word_78c=1;y_f0=stage_surface_height();velocity_x_f4=0.0f;velocity_y_f8=0.0f;acceleration_y_100=0.0f;select_sequence(1);return;}break;}
    case 2:if(owner_348->word_78e==1) {next_sequence_block();facing_104=1;return;}break;
    case 3:case 4:if(phase>=4) velocity_y_f8-=acceleration_y_100;break;
    }
    x_ec=static_cast<float>(static_cast<double>(facing_104)*velocity_x_f4+x_ec);y_f0+=velocity_y_f8;if(advance_frame()) --lifetime_330;if(time_counter_144==0 && frame_timer_142==0 && frame_index_140==0 && sequence_index_13e==4) {velocity_x_f4=15.0f;velocity_y_f8=15.0f;acceleration_y_100=0.2f;}return;
}

}
default:advance_frame();return;
}
}
}
