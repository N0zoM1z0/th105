case 400:
    landing();
    if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<5)) && !I(0x6c0))B(0x750)=0;
    shot800_fan(94,102.0);
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1){
        if((!B(0x750) && time_counter_144>1 && time_counter_144<5) || time_counter_144>15){next_sequence_block();return;}
        if(time_counter_144==5)effect(62,static_cast<float>(F(0xec)-12*facing()),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){aim_short(-10,10);S(0x730)=1;counter(200,45);}return;
case 401:
    landing();
    if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<5)) && !I(0x6c0))B(0x750)=0;
    shot800_fan(96,130.0);
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1){
        if((!B(0x750) && time_counter_144>1 && time_counter_144<5) || time_counter_144>15){next_sequence_block();return;}
        if(time_counter_144==5)effect(62,static_cast<float>(F(0xec)-12*facing()),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){aim_short(-40,-20);S(0x730)=1;counter(200,45);}return;
case 402:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(S(0x730)>=0){
        --S(0x730);
        if(!S(0x730) && sequence_index_13e<4){
            I(0x180)=1;dispatch_character_wave_handle(0);phase_counter(5);
            float p[3];p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%30u)-15.0);
            p[1]=static_cast<float>(15+2*S(0x732));p[2]=static_cast<float>(static_cast<float>(marisa_random_u32()&3u)+2.0);
            spawn_offset(800,87,67.0,p,3);S(0x730)=4;++S(0x732);
        }
    }
    if(advance())set_action_and_finalize(2);
    if(sequence_index_13e==3 && (!B(0x750) || time_counter_144>=30)){next_sequence_block();return;}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){S(0x730)=1;counter(200,45);effect(62,static_cast<float>(90*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+70.0),B(0x104),1);}return;
case 404:
    if(sequence_index_13e==3)landing();
    if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<5)) && !I(0x6c0))B(0x750)=0;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<3){select_sequence(3);B(0x47f)=0;F(0xf0)=marisa_surface(this);zero_motion();return;}
    shot800_fan(80,115.0);
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1){
        if((!B(0x750) && time_counter_144>1 && time_counter_144<5) || time_counter_144>15){next_sequence_block();return;}
        if(time_counter_144==5)effect(62,static_cast<float>(F(0xec)-25*facing()),static_cast<float>(F(0xf0)+125.0),B(0x104),1);
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){F(0xf4)=-6.0f;F(0xf8)=6.0f;F(0x100)=0.5f;aim_short(-10,10);S(0x730)=1;counter(200,45);}
    if(entry(3))set_action_and_finalize(9);return;
case 406:
    if(sequence_index_13e==3)landing();
    if((!sequence_index_13e || (sequence_index_13e==1 && time_counter_144<5)) && !I(0x6c0))B(0x750)=0;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<3){select_sequence(3);B(0x47f)=0;F(0xf0)=marisa_surface(this);zero_motion();return;}
    shot800_fan(69,87.0,10);
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1){
        if((!B(0x750) && time_counter_144>1 && time_counter_144<5) || time_counter_144>15){next_sequence_block();return;}
        if(time_counter_144==5 && B(0x750)==1)effect(62,static_cast<float>(F(0xec)-25*facing()),static_cast<float>(F(0xf0)+125.0),B(0x104),1);
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){F(0xf4)=-6.0f;F(0xf8)=6.0f;F(0x100)=0.5f;aim_short(20,40);S(0x730)=1;counter(200,45);}
    if(entry(3))set_action_and_finalize(9);return;
case 408:
    landing();decelerate(0.75,false);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){dispatch_character_wave_handle(1);float p[3]={0.0f,2.0f,1.0f};spawn_offset(848,106,103.0,p,3);}return;
case 409:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=marisa_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    landing();if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
        aim_short(-20,20);dispatch_character_wave_handle(2);counter(200,60);I(0x180)=1;phase_counter(50);
        if(!S(0x738)){float p[3]={static_cast<float>(S(0x734)),5.0f,0.0f};spawn_offset(801,44,85.0,p,3);}
        else{float p[3]={static_cast<float>(S(0x734)),5.0f,1.0f};spawn_offset(801,44,85.0,p,3);}
    }
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1 && time_counter_144>0){
        if((!B(0x750) && time_counter_144<10) || time_counter_144>29){next_sequence_block();return;}
        if(time_counter_144==10){effect(62,static_cast<float>(F(0xec)-23*facing()),static_cast<float>(F(0xf0)+93.0),B(0x104),1);S(0x738)=1;}
    }
    if(sequence_index_13e==3 && time_counter_144>20)next_sequence_block();return;
case 411:
    landing();if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
        phase_counter(50);aim_short(-10,10);dispatch_character_wave_handle(4);I(0x180)=1;counter(200,60);
        if(S(0x738)==1)spawn_offset(803,44,85.0,0,0);else spawn_offset(803,44,85.0,0,0);
    }
    if(advance())set_action_and_finalize(0);
    if((sequence_index_13e==1 && time_counter_144>=5 && (!B(0x750) || time_counter_144>=26)) || (sequence_index_13e==4 && time_counter_144>8))next_sequence_block();return;
case 412:
    landing();if(sequence_index_13e<2 && !I(0x6c4))S(0x738)=1;
    if(sequence_index_13e==2 && frame_index_140==1 && !frame_timer_142){
        dispatch_character_wave_handle(7);float p[3]={0.0f,0.0f,0.0f};I(0x180)=1;counter(200,60);phase_counter(50);
        if(S(0x738)==1)spawn_offset(802,70,162.0,p,3);else spawn_offset(802,70,162.0,p,3);
    }
    if(advance())set_action_and_finalize(0);if(sequence_index_13e==1 && time_counter_144>4)next_sequence_block();return;
case 414:
    if(sequence_index_13e==5)landing();F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){select_sequence(5);B(0x47f)=0;F(0xf0)=marisa_surface(this);zero_motion();return;}
    if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
        counter(200,60);I(0x180)=1;phase_counter(50);aim_short(-40,40);dispatch_character_wave_handle(2);
        if(!S(0x738)){float p[3]={static_cast<float>(S(0x734)),0.0f,0.0f};spawn_offset(801,48,104.0,p,3);}
        else{float p[3]={static_cast<float>(S(0x734)),0.0f,1.0f};spawn_offset(801,48,104.0,p,3);}
    }
    if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1){
        F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.01f));
        if((!B(0x750) && time_counter_144<10) || time_counter_144>30){next_sequence_block();return;}
        if(time_counter_144==10){S(0x738)=1;effect(62,static_cast<float>(F(0xec)-23*facing()),static_cast<float>(F(0xf0)+107.0),B(0x104),1);}
    }
    if(sequence_index_13e==3 && time_counter_144>20){next_sequence_block();return;}
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.6f;return;
case 415:
    if(sequence_index_13e==6)landing();F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<6){select_sequence(6);B(0x47f)=0;F(0xf0)=marisa_surface(this);zero_motion();return;}
    if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){
        aim_short(-10,10);dispatch_character_wave_handle(4);I(0x180)=1;counter(200,60);phase_counter(50);
        if(S(0x738)==1){float p[3]={static_cast<float>(S(0x734)),2.0f,0.0f};spawn_offset(803,48,104.0,p,3);}
        else{float p[3]={static_cast<float>(S(0x734)),2.0f,0.0f};spawn_offset(803,48,104.0,p,3);}
    }
    if(advance())set_action_and_finalize(0);if(entry(6)){set_action_and_finalize(9);return;}
    if((sequence_index_13e==1 && time_counter_144>=5 && (!B(0x750) || time_counter_144>=26)) || (sequence_index_13e==4 && time_counter_144>8)){next_sequence_block();return;}
    if(sequence_index_13e==5 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.6f;return;
case 416:
    if(sequence_index_13e==1)landing();
    if(!sequence_index_13e){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=marisa_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
        dispatch_character_wave_handle(2);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;
        float p[3]={60.0f,0.0f,0.0f};I(0x180)=1;counter(200,60);phase_counter(50);spawn_offset(801,30,30.0,p,3);
    }return;
case 418:
    landing();decelerate(0.5,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){
        if(frame_index_140==4){float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==5){event(29);B(0x47e)=0;}
    }return;
case 420:
    landing();if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1 && time_counter_144>1){next_sequence_block();return;}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;S(0x7a8)=40;S(0x7a4)=1;S(0x730)=1;counter(200,60);}return;
case 421:
    landing();if(advance())set_action_and_finalize(2);
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;S(0x7a8)=40;S(0x7a4)=1;S(0x730)=1;counter(200,60);}return;
case 422:
    if(sequence_index_13e==3)landing();F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<3){select_sequence(3);B(0x47f)=0;F(0xf0)=marisa_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1 && time_counter_144>1){next_sequence_block();return;}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;F(0xf4)=-6.0f;F(0xf8)=6.0f;F(0x100)=0.5f;S(0x7a8)=40;S(0x7a4)=1;S(0x730)=1;counter(200,60);}
    if(entry(3))set_action_and_finalize(9);return;
case 430:
    landing();if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){counter(200,120);S(0x7a8)=60;S(0x7a4)=8;I(0x180)=1;phase_counter(50);}
    if(advance())set_action_and_finalize(0);
    if((sequence_index_13e==1 && time_counter_144>=17) || (sequence_index_13e==3 && time_counter_144>=21))next_sequence_block();return;
case 431:
    landing();if(advance())set_action_and_finalize(2);
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;S(0x7a8)=60;S(0x7a4)=8;S(0x730)=1;counter(200,120);}
    if(sequence_index_13e==3 && time_counter_144>20)next_sequence_block();return;
case 432:
    if(sequence_index_13e==5)landing();F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<5){select_sequence(5);B(0x47f)=0;F(0xf0)=marisa_surface(this);zero_motion();return;}
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){counter(200,120);I(0x180)=1;S(0x7a8)=60;S(0x7a4)=8;phase_counter(50);}
    if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.01f));if(time_counter_144>16){next_sequence_block();return;}}
    if(sequence_index_13e==3 && time_counter_144>=21){next_sequence_block();return;}
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.6f;return;
