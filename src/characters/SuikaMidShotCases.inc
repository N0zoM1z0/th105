case 400:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==4 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(F(0xec)-40*facing()),static_cast<float>(F(0xf0)+70.0),B(0x104),1);return;}
        if(!frame_timer_142 && frame_index_140==6){float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,85,100.0,p,3);counter(200,45);phase_counter(30);I(0x180)=1;dispatch_character_wave_handle(2);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && (frame_index_140==3 || frame_index_140==8 || frame_index_140==13)){
        if(frame_index_140==3){counter(200,45);phase_counter(30);}float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,85,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);
    }return;
case 401:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){counter(200,45);phase_counter(30);aim_float(-20.0f,20.0f);float p[3]={F(0x744),30.0f,3.0f};spawn_offset(800,85,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(3);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){counter(200,45);phase_counter(30);aim_float(-20.0f,20.0f);float p[3]={F(0x744),30.0f,3.0f};spawn_offset(800,85,100.0,p,3);p[0]=static_cast<float>(F(0x744)+10.0);spawn_offset(800,85,100.0,p,3);p[0]=static_cast<float>(F(0x744)-10.0);spawn_offset(800,85,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(3);}return;
case 402:
    landing();if(!I(0x6c0))B(0x750)=0;if(C(0x47e)>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142){if(frame_index_140==2 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(28*facing()+F(0xec)),static_cast<float>(F(0xf0)+57.0),B(0x104),1);return;}if(frame_index_140==3){event(29);B(0x47e)=0;}}
        if(!frame_timer_142 && frame_index_140==4){counter(200,45);phase_counter(30);dispatch_character_wave_handle(1);effect(58,static_cast<float>(198*facing()+F(0xec)),0.0f,B(0x104),-1);layout(4.0f);}
    }
    if(sequence_index_13e==1){
        if(!frame_timer_142){
            if(frame_index_140==1)F(0xf4)=10.0f;
            if(!frame_timer_142){
                if(frame_index_140==2){event(29);B(0x47e)=0;}
                if(!frame_timer_142 && frame_index_140==3){
                    F(0xf4)=0.0f;dispatch_character_wave_handle(1);counter(200,45);phase_counter(30);effect(58,static_cast<float>(198*facing()+F(0xec)),0.0f,B(0x104),-1);layout(7.0f);
                    float p[3]={0.0f,0.0f,7.0f};spawn_offset(800,210,0.0,p,3);float n=0.0f;
                    do{p[0]=static_cast<float>((n*60.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);p[2]=1.0f;
                       S(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(811,40,0.0,p,3,B(0x730));n=static_cast<float>(n+1.0);
                    }while(n<6.0f);
                }
            }
        }
        decelerate(static_cast<double>(0.7f),false);
    }return;
case 404:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);B(0x47f)=0;F(0xf0)=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==4 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(F(0xec)-35*facing()),static_cast<float>(F(0xf0)+80.0),B(0x104),1);return;}
        if(!frame_timer_142 && frame_index_140==6){counter(200,45);phase_counter(30);float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3 || frame_index_140==8 || frame_index_140==13){if(frame_index_140==3){counter(200,45);phase_counter(30);}float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==16)F(0x100)=0.5f;
    }return;
case 405:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);B(0x47f)=0;F(0xf0)=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(!frame_timer_142 && frame_index_140==6){counter(200,45);phase_counter(30);aim_float(-20.0f,20.0f);float p[3]={F(0x744),30.0f,3.0f};spawn_offset(800,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(3);}
        if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3){counter(200,45);phase_counter(30);aim_float(-20.0f,20.0f);float p[3]={F(0x744),30.0f,3.0f};spawn_offset(800,50,100.0,p,3);p[0]=static_cast<float>(F(0x744)+10.0);spawn_offset(800,50,100.0,p,3);p[0]=static_cast<float>(F(0x744)-10.0);spawn_offset(800,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(3);}
        if(!frame_timer_142 && frame_index_140==6)F(0x100)=0.5f;
    }return;
case 406:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);B(0x47f)=0;F(0xf0)=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==4 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(F(0xec)-40*facing()),static_cast<float>(F(0xf0)+70.0),B(0x104),1);return;}
        if(!frame_timer_142 && frame_index_140==6){counter(200,45);phase_counter(30);float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3 || frame_index_140==8 || frame_index_140==13){if(frame_index_140==3){counter(200,45);phase_counter(30);}float p[3]={15.0f,10.0f,0.0f};spawn_offset(800,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==16)F(0x100)=0.5f;
    }return;
case 408:
    landing();
    if(frame_index_140<9){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<10.0f)F(0xf4)=10.0f;}
    else F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.7f));
    if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==4)F(0xf4)=15.0f;if(!frame_timer_142){if(frame_index_140==6)event(29);if(!frame_timer_142 && (frame_index_140==7 || frame_index_140==8 || frame_index_140==9))I(0x180)=0;}}return;
case 409:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=suika_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={10.0f,8.0f,0.0f};spawn_offset(801,85,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={10.0f,8.0f,0.0f};spawn_offset(801,85,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
    return;
case 411:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={30.0f,8.0f,0.0f};spawn_offset(801,85,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={30.0f,8.0f,0.0f};spawn_offset(801,85,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
    return;
case 412:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={10.0f,17.5f,0.0f};spawn_offset(801,18,88.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
    return;
case 414:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);B(0x47f)=0;F(0xf0)=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={10.0f,8.0f,0.0f};spawn_offset(801,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={10.0f,8.0f,0.0f};spawn_offset(801,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==7)F(0x100)=0.5f;
    }return;
case 415:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);B(0x47f)=0;F(0xf0)=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={30.0f,8.0f,0.0f};spawn_offset(801,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={30.0f,8.0f,0.0f};spawn_offset(801,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==7)F(0x100)=0.5f;
    }return;
case 416:
    if(sequence_index_13e==2)landing();if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){select_sequence(2);B(0x47f)=0;F(0xf0)=suika_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(0);if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==6){counter(200,60);phase_counter(50);float p[3]={10.0f,0.0f,0.0f};spawn_offset(801,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==3){counter(200,60);phase_counter(50);float p[3]={10.0f,0.0f,0.0f};spawn_offset(801,50,100.0,p,3);I(0x180)=1;dispatch_character_wave_handle(2);}
        if(!frame_timer_142 && frame_index_140==7)F(0x100)=0.5f;
    }return;
case 418:
    if(!sequence_index_13e || sequence_index_13e==5)landing();
    if(sequence_index_13e==2 && time_counter_144%15==0)event(28);
    if(sequence_index_13e<5){
        F(0xf8)-=F(0x100);
        if((sequence_index_13e==1 || sequence_index_13e==2) && I(0x180)!=0 && I(0x180)!=3){select_sequence(3);F(0xf4)=-3.0f;F(0xf8)=13.0f;F(0x100)=0.75f;I(0x180)=1;return;}
        if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0x100)=0.0f;F(0xf0)=suika_surface(this);select_sequence(5);return;}
    }
    if(sequence_index_13e==5){
        if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
        if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+1.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    }
    if(advance())set_action_and_finalize(0);if(entry(1)){F(0xf4)=12.0f;F(0xf8)=9.0f;F(0x100)=0.5f;}return;
