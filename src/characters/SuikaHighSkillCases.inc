case 560:
    landing();B(0x17c)=3;if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){float p[3]={7.0f,6.0f,0.0f};spawn_offset(813,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={7.0f,6.0f,3.0f};spawn_offset(813,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}return;
case 561:
    landing();B(0x17c)=3;if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){float p[3]={15.0f,6.0f,0.0f};spawn_offset(813,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={15.0f,6.0f,3.0f};spawn_offset(813,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}return;
case 562:
    if(sequence_index_13e==5)landing();B(0x17c)=3;
    F(0xf8)-=F(0x100);
    {double predicted=static_cast<double>(F(0xf8))+F(0xf0);if(suika_surface(this)>=predicted && F(0xf8)<0.0f && sequence_index_13e<5){select_sequence(5);F(0x100)=0.0f;B(0x47f)=0;F(0xf0)=suika_surface(this);zero_motion();return;}}
    if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;shot808_burst(true,true);
    if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>4 && (!B(0x750) || time_counter_144>25))next_sequence_block();
    if(entry(1)){if(B(0x750)==1)effect(62,static_cast<float>(F(0xec)-23*facing()),static_cast<float>(F(0xf0)+107.0),B(0x104),1);float p[3]={0.0f,0.0f,4.0f};spawn_offset(808,-23,107.0,p,3);}
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142){S(0x730)=1;counter(200,120);}
    if(sequence_index_13e==3 && ((time_counter_144>10 && !B(0x750)) || time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.6f;return;
case 565:
    landing();B(0x17c)=7;if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){float p[3]={7.0f,10.0f,0.0f};spawn_offset(818,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={7.0f,10.0f,3.0f};spawn_offset(818,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}return;
case 566:
    landing();B(0x17c)=7;if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){float p[3]={15.0f,10.0f,0.0f};spawn_offset(818,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={15.0f,10.0f,3.0f};spawn_offset(818,100,85.0,p,3);counter(200,120);phase_counter(50);dispatch_character_wave_handle(14);}return;
case 599:
    if(S(0x730)>0 && frame_index_140<7 && S(0x730)<12){
        S(0x734)=static_cast<short>(suika_random_u32()%35u);
        float p[3];p[0]=static_cast<float>(-20-S(0x734));p[1]=static_cast<float>(static_cast<short>(static_cast<short>(suika_random_u32()%5u)+10));p[2]=0.0f;
        spawn(807,static_cast<float>((S(0x730)+1)*facing()*20+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        p[0]=static_cast<float>(suika_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        spawn(801,static_cast<float>((S(0x730)+1)*facing()*20+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        if(S(0x730)==1){dispatch_character_wave_handle(0);counter(200,120);}++S(0x730);
    }
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)S(0x730)=1;return;
