case 500:
    if(sequence_index_13e==4)landing();B(0x17c)=0;
    if(sequence_index_13e==1){
        if(time_counter_144>20){set_action_and_finalize(504);return;}
        if(time_counter_144%3==0){float p[3];p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%60u)+180.0-30.0);p[1]=15.0f;p[2]=static_cast<float>(marisa_random_u32()&3u);spawn_offset(810,-95,100.0,p,3);}
        if(I(0x180)!=0 && I(0x180)!=1 && I(0x180)!=3){next_sequence_block();F(0xf4)=-5.0f;F(0xf8)=10.0f;F(0x100)=0.35f;return;}
    }
    if(sequence_index_13e==2 || sequence_index_13e==3){
        F(0xf8)-=F(0x100);F(0xf4)=static_cast<float>(static_cast<double>(0.1f)+F(0xf4));if(F(0xf4)>-1.0f)F(0xf4)=-1.0f;
        if(static_cast<unsigned char>(crossed())){F(0xf0)=marisa_surface(this);zero_motion();select_sequence(4);}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(849,109,84.0,p,3);
        double y=F(0xf0);if(marisa_surface(this)==y)effect(128,static_cast<float>(200*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),-1);
        F(0xf4)=20.0f;counter(200,120);phase_counter(50);dispatch_character_wave_handle(6);
    }return;
case 504:
    if(sequence_index_13e==2)landing();B(0x17c)=0;
    if(sequence_index_13e==0 || sequence_index_13e==1){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=marisa_surface(this);zero_motion();select_sequence(2);}}
    if(advance())set_action_and_finalize(0);return;
case 505:
    if(sequence_index_13e==3)landing();B(0x17c)=4;
    if(sequence_index_13e==1 || sequence_index_13e==2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=marisa_surface(this);zero_motion();select_sequence(3);}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        phase_counter(50);
        // Four native stores at 4AA153/169/175/17C, while the request count is three.
        float p[4]={0.0f,27.5f,0.0f,0.0f};spawn_offset(811,109,84.0,p,3);
        effect(127,static_cast<float>(200*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),-1);
        F(0xf4)=-7.5f;F(0xf8)=10.0f;F(0x100)=0.55f;counter(200,120);dispatch_character_wave_handle(26);
    }return;
case 506:
    if(sequence_index_13e==3)landing();B(0x17c)=4;
    if(sequence_index_13e==1 || sequence_index_13e==2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=marisa_surface(this);zero_motion();select_sequence(3);}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        phase_counter(50);float p[4]={-30.0f,27.5f,0.0f,0.0f};spawn_offset(811,109,84.0,p,3);
        effect(127,static_cast<float>(200*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),-1);
        F(0xf4)=-7.5f;F(0xf8)=10.0f;F(0x100)=0.55f;counter(200,120);dispatch_character_wave_handle(26);
    }return;
case 510:case 512:
    if(sequence_index_13e==4)landing();B(0x17c)=8;
    if(sequence_index_13e==1 || sequence_index_13e==2 || sequence_index_13e==3){
        F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<2.0f)F(0xf4)=2.0f;F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){F(0xf0)=marisa_surface(this);zero_motion();select_sequence(4);F(0x12c)=0.0f;}
        if(sequence_index_13e==1){F(0x73c)=static_cast<float>(F(0x73c)+2.0);F(0x12c)=static_cast<float>(F(0x12c)-25.0);if(F(0x12c)<-720.0f){next_sequence_block();F(0x12c)=0.0f;return;}}
        if(sequence_index_13e==3 && time_counter_144>23){set_action_and_finalize(9);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(812,50,50.0,p,3);p[2]=1.0f;spawn_offset(812,50,50.0,p,3);
        F(0xf4)=17.5f;F(0xf8)=12.5f;F(0x100)=0.45f;counter(200,120);phase_counter(50);dispatch_character_wave_handle(6);F(0x108)=0.0f;F(0x10c)=100.0f;
    }return;
case 520:
    if(!sequence_index_13e || sequence_index_13e==4)landing();B(0x17c)=1;
    if(sequence_index_13e==1){if(time_counter_144>20)next_sequence_block();if(time_counter_144%3==0)rising_trail();}
    if(sequence_index_13e>0 && sequence_index_13e<4){F(0xf8)=static_cast<float>(F(0xf8)-0.75);decelerate(0.5,false);}
    if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=marisa_surface(this);zero_motion();}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        float p[3]={-85.0f,0.0f,1.0f};spawn_offset(849,61,232.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);
        dispatch_character_wave_handle(5);counter(200,120);phase_counter(50);F(0xf4)=12.5f;F(0xf8)=17.5f;F(0x100)=0.6f;
    }return;
case 521:
    if(!sequence_index_13e || sequence_index_13e==4)landing();B(0x17c)=1;
    if(sequence_index_13e==1){if(time_counter_144>20)next_sequence_block();if(time_counter_144%3==0)rising_trail();}
    if(sequence_index_13e>0 && sequence_index_13e<4){F(0xf8)=static_cast<float>(F(0xf8)-0.75);decelerate(static_cast<double>(0.4f),false);}
    if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=marisa_surface(this);zero_motion();}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        float p[3]={-85.0f,0.0f,1.0f};spawn_offset(849,61,232.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);
        dispatch_character_wave_handle(5);counter(200,120);phase_counter(50);F(0xf4)=15.0f;F(0xf8)=25.0f;F(0x100)=0.6f;
    }return;
case 525:
    if(!sequence_index_13e || sequence_index_13e==4)landing();B(0x17c)=5;
    if(sequence_index_13e==1){if(time_counter_144>20){next_sequence_block();F(0xf8)=static_cast<float>(F(0xf8)*0.5);}if(time_counter_144%3==0)rising_trail();}
    if(sequence_index_13e>0 && sequence_index_13e<4){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.55f));decelerate(0.5,false);}
    if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=marisa_surface(this);zero_motion();}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        float p[3];p[0]=-85.0f;p[1]=0.0f;if(C(0x609)>3)p[2]=5.0f;if(C(0x609)<4)p[2]=4.0f;if(C(0x609)<2)p[2]=3.0f;
        spawn_offset(849,61,232.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);
        dispatch_character_wave_handle(28);counter(200,120);phase_counter(50);F(0xf4)=7.0f;F(0xf8)=30.0f;F(0x100)=0.5f;I(0x180)=1;
    }
    if(entry(3))I(0x180)=1;return;
case 526:
    if(!sequence_index_13e || sequence_index_13e==4)landing();B(0x17c)=5;
    if(sequence_index_13e==1){if(time_counter_144>30)next_sequence_block();if(time_counter_144%3==0)rising_trail();}
    if(sequence_index_13e>0 && sequence_index_13e<4){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.55f));decelerate(0.5,false);}
    if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=marisa_surface(this);zero_motion();}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        float p[3]={-85.0f,0.0f,3.0f};spawn_offset(849,61,232.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);
        dispatch_character_wave_handle(28);counter(200,120);phase_counter(50);F(0xf4)=25.0f;F(0xf8)=20.0f;F(0x100)=0.5f;I(0x180)=1;
    }
    if(entry(3))I(0x180)=1;return;
case 530:
    landing();B(0x17c)=9;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
        float p[3]={-70.0f,30.0f,0.0f};spawn_offset(817,18,164.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);
        dispatch_character_wave_handle(30);counter(200,120);phase_counter(50);I(0x180)=1;
    }return;
case 531:
    landing();B(0x17c)=9;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
        float p[3]={-70.0f,50.0f,0.0f};spawn_offset(817,18,164.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);
        dispatch_character_wave_handle(30);counter(200,120);phase_counter(50);I(0x180)=1;
    }return;
