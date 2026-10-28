case 540:
    landing();B(0x17c)=2;if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){phase_counter(50);counter(200,120);I(0x180)=1;float p[3]={4.0f,0.0f,0.0f};spawn_offset(820,70,165.0,p,3);dispatch_character_wave_handle(7);}
    if(sequence_index_13e==1 && !frame_index_140 && !B(0x750)){select_sequence(0);frame_index_140=7;}return;
case 541:
    landing();B(0x17c)=2;if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){phase_counter(50);counter(200,120);I(0x180)=1;float p[3]={10.0f,0.0f,0.0f};spawn_offset(820,70,165.0,p,3);dispatch_character_wave_handle(7);}
    if(sequence_index_13e==1 && !frame_index_140 && !B(0x750)){select_sequence(0);frame_index_140=7;}return;
case 542:
    if(sequence_index_13e==2)landing();B(0x17c)=2;
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(2);F(0xf0)=marisa_surface(this);return;}}
    if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){dispatch_character_wave_handle(7);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;I(0x180)=1;float p[3]={0.0f,0.0f,1.0f};spawn_offset(820,30,62.0,p,3);counter(200,120);phase_counter(50);}return;
case 545:
    landing();B(0x17c)=6;if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){phase_counter(50);counter(200,120);I(0x180)=1;float p=0.0f;spawn_offset(821,70,165.0,&p,1);dispatch_character_wave_handle(7);}
    if(sequence_index_13e==1 && !frame_index_140 && !B(0x750)){select_sequence(0);frame_index_140=7;}return;
case 547:
    if(sequence_index_13e==2)landing();B(0x17c)=2;
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(2);F(0xf0)=marisa_surface(this);return;}}
    if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==8 && B(0x750)==1){next_sequence_block();return;}
        if(frame_index_140==6){I(0x180)=1;dispatch_character_wave_handle(7);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;spawn_offset(816,30,62.0,0,0);counter(200,120);phase_counter(50);}
    }return;
case 550:
    landing();B(0x17c)=10;if(advance())set_action_and_finalize(9);
    if(!frame_timer_142 && frame_index_140==5){float p[3];p[0]=-90.0f;p[1]=20.0f;p[2]=static_cast<float>(marisa_random(6));spawn_offset(822,53,124.0,p,3);}return;
case 551:
    landing();B(0x17c)=10;if(advance())set_action_and_finalize(9);
    if(!frame_timer_142 && frame_index_140==5){float p[3];p[0]=180.0f;p[1]=20.0f;p[2]=static_cast<float>(marisa_random(6));spawn_offset(822,53,124.0,p,3);}return;
case 560:shot825_action(false,false);return;
case 561:shot825_action(false,true);return;
case 562:shot825_action(true,false);return;
case 563:shot825_action(true,true);return;
case 565:shot826_action(false,false);return;
case 566:shot826_action(false,true);return;
case 567:shot826_action(true,false);return;
case 568:shot826_action(true,true);return;
case 570:shot827_action(false,false);return;
case 571:shot827_action(false,true);return;
case 572:shot827_action(true,false);return;
case 573:shot827_action(true,true);return;
case 599:
    if(S(0x730)>0 && frame_index_140<7 && S(0x730)<12){
        S(0x734)=static_cast<short>(marisa_random_u32()%35u);
        float p[3];p[0]=static_cast<float>(-20-S(0x734));p[1]=static_cast<float>(static_cast<short>(static_cast<short>(marisa_random_u32()%5u)+10));p[2]=0.0f;
        spawn(807,static_cast<float>((S(0x730)+1)*facing()*20+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        p[0]=static_cast<float>(marisa_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        spawn(801,static_cast<float>((S(0x730)+1)*facing()*20+static_cast<double>(F(0xec))),F(0xf0),B(0x104),1,p,3);
        if(S(0x730)==1){dispatch_character_wave_handle(0);counter(200,120);}++S(0x730);
    }
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5)S(0x730)=1;return;
