case 600:
    landing();texture(5,2);
    if(sequence_index_13e==1){if(time_counter_144>60){next_sequence_block();return;}if(time_counter_144%10==0)effect(127,static_cast<float>(F(0xec)-100*facing()),F(0xf0),B(0x104),-1);}
    if(advance())set_action_and_finalize(0);if(!sequence_index_13e && frame_index_140==2 && !frame_timer_142)spell_flash(-23,94.0,3);
    if(entry(1)){spawn_offset(990,-80,130.0,0,0);dispatch_character_wave_handle(10);float p[3]={0.0f,0.0f,0.0f};spawn_offset(850,25,87.0,p,3);p[2]=2.0f;spawn_offset(850,25,87.0,p,3);p[2]=4.0f;spawn_offset(850,25,87.0,p,3);}return;
case 601:
    landing();texture(5,2);
    if(sequence_index_13e==1){if(time_counter_144>90){next_sequence_block();return;}if(time_counter_144%10==0)effect(127,static_cast<float>(F(0xec)-100*facing()),F(0xf0),B(0x104),-1);}
    if(advance())set_action_and_finalize(0);if(!sequence_index_13e && frame_index_140==2 && !frame_timer_142)spell_flash(-23,94.0,3);
    if(entry(1)){spawn_offset(990,-80,130.0,0,0);dispatch_character_wave_handle(10);float p[3]={0.0f,2.0f,0.0f};spawn_offset(851,25,87.0,p,3);p[1]=-2.0f;spawn_offset(851,25,87.0,p,3);p[1]=0.0f;p[2]=2.0f;spawn_offset(851,25,87.0,p,3);}return;
case 602:
    landing();texture(5,2);
    if(sequence_index_13e==1){
        if(time_counter_144%10==0 && time_counter_144<91){float p[3]={0.0f,0.0f,5.0f};spawn_offset(852,25,150.0,p,3);effect(127,static_cast<float>(F(0xec)-100*facing()),F(0xf0),B(0x104),-1);}
        if(time_counter_144>120){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)spell_flash(18,83.0,5);
    if(entry(1)){spawn_offset(990,-80,130.0,0,0);dispatch_character_wave_handle(11);float p[3]={0.0f,0.0f,0.0f};spawn_offset(852,25,150.0,p,3);p[2]=2.0f;spawn_offset(852,25,150.0,p,3);p[2]=4.0f;spawn_offset(852,25,150.0,p,3);}return;
case 603:
    if(sequence_index_13e==6)landing();texture(5,2);
    if(sequence_index_13e==1)F(0xf8)-=F(0x100);
    if(sequence_index_13e==3){
        if(time_counter_144%10==0 && time_counter_144<91){float p[3]={F(0x73c),0.0f,5.0f};spawn_offset(853,30,53.0,p,3);}
        if(facing()*I(0x6b4)>0 || I(0x6b8)<0)F(0x73c)=static_cast<float>(F(0x73c)-static_cast<double>(0.2f));
        if(facing()*I(0x6b4)<0 || I(0x6b8)>0)F(0x73c)=static_cast<float>(F(0x73c)+static_cast<double>(0.2f));
        F(0xf4)=static_cast<float>(marisa_cosine(static_cast<float>(180.0-F(0x73c)))*3.0);
        F(0xf8)=static_cast<float>(marisa_sine(static_cast<float>(180.0-F(0x73c)))*3.0);
        if(time_counter_144>120){next_sequence_block();return;}
    }
    if(sequence_index_13e==4 || sequence_index_13e==5){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=marisa_surface(this);select_sequence(6);return;}}
    if(advance())set_action_and_finalize(0);if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)spell_flash(18,83.0,5);
    if(sequence_index_13e==1 && !frame_timer_142){
        if(!frame_index_140){F(0xf4)=-4.0f;F(0xf8)=23.0f;F(0x100)=0.6f;}
        if(!frame_timer_142 && frame_index_140==9){F(0xf4)=static_cast<float>(F(0xf4)*static_cast<double>(0.2f));F(0xf8)=static_cast<float>(static_cast<double>(0.2f)*F(0xf8));F(0x100)=0.0f;zero_motion();}
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2){
        dispatch_character_wave_handle(11);float p[3]={60.0f,0.0f,0.0f};F(0x73c)=60.0f;spawn_offset(853,30,53.0,p,3);p[2]=2.0f;spawn_offset(853,30,53.0,p,3);p[2]=4.0f;spawn_offset(853,30,53.0,p,3);
    }
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==1)F(0x100)=0.5f;return;
case 604:
    landing();texture(5,2);if(sequence_index_13e==1 && time_counter_144>120){next_sequence_block();return;}
    if(entry(1)){dispatch_character_wave_handle(10);float p=0.0f;spawn_offset(853,-25,150.0,&p,1);p=90.0f;spawn_offset(853,-25,150.0,&p,1);p=180.0f;spawn_offset(853,-25,150.0,&p,1);p=270.0f;spawn_offset(853,-25,150.0,&p,1);}
    if(advance())set_action_and_finalize(0);if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)spell_flash(-2,120.0,3);return;
case 605:
    if(sequence_index_13e==4)landing();if(sequence_index_13e<2)texture(5,2);
    if(I(0x180)==1 && !S(0x732)){S(0x732)=1;dispatch_character_wave_handle(14);}
    if(sequence_index_13e==1){
        if((classify_fighter_x_boundary()!=0 && I(0x180)!=1 && ((C(0x104)==1 && F(0xec)>640.0f) || (C(0x104)==-1 && F(0xec)<640.0f))) || (!B(0x184) && I(0x180)==2)){
            next_sequence_block();F(0xf4)=-2.5f;F(0xf8)=15.0f;F(0x100)=0.5f;
        }
        float p[3];p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%60u)-30.0);p[1]=static_cast<float>(marisa_random_u32()%10u+15u);p[2]=2.0f;
        spawn(810,static_cast<float>(F(0xec)-90*facing()),static_cast<float>(F(0xf0)+95.0),static_cast<unsigned char>(-C(0x104)),1,p,3);
    }
    if(sequence_index_13e==2 || sequence_index_13e==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=marisa_surface(this);select_sequence(4);return;}}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){S(0x48a)=40;event(23);sequence_window(0,2,60);secondary_cycle();effect(115,static_cast<float>(F(0xec)-0.0),static_cast<float>(F(0xf0)+70.0),B(0x104),1);}
    if(entry(1)){B(0x184)=20;F(0xf4)=30.0f;dispatch_character_wave_handle(13);float p[3]={0.0f,0.0f,0.0f};spawn_offset(857,0,0.0,p,3);if(marisa_on_surface(this))effect(127,F(0xec),0.0f,B(0x104),1);}
    if(sequence_index_13e==1 && !frame_timer_142){int state=I(0x180);I(0x180)=0;if(!state)F(0xf4)=25.0f;else F(0xf4)=10.0f;}return;
case 606:
    if(!sequence_index_13e || sequence_index_13e==4)landing();texture(5,2);
    if(sequence_index_13e==1){
        if(time_counter_144>40)next_sequence_block();
        if(time_counter_144%3==0){float p[3];p[0]=static_cast<float>(static_cast<float>(marisa_random_u32()%60u)+95.0-30.0);p[1]=15.0f;p[2]=static_cast<float>(marisa_random_u32()&3u);spawn_offset(810,40,51.0,p,3);}
        if(I(0x180)){++S(0x730);if(S(0x730)>3){S(0x730)=0;I(0x180)=0;}}
    }
    if(sequence_index_13e>0 && sequence_index_13e<4){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.85f));decelerate(static_cast<double>(0.35f),false);}
    if(sequence_index_13e==3 && static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=marisa_surface(this);zero_motion();}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){S(0x48a)=40;event(23);sequence_window(0,3,60);secondary_cycle();effect(115,static_cast<float>(66*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+81.0),B(0x104),1);}
    if(entry(1)){float p[3]={-80.0f,0.0f,2.0f};spawn_offset(849,61,232.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);dispatch_character_wave_handle(15);F(0xf4)=15.0f;F(0xf8)=32.5f;F(0x100)=0.6f;}return;
case 607:
    if(sequence_index_13e==4)landing();if(sequence_index_13e<3)texture(5,2);
    if(sequence_index_13e==1 && time_counter_144>60){next_sequence_block();dispatch_character_wave_handle(16);float p[3]={0.0f,0.0f,3.0f};spawn_offset(858,-200,275.0,p,3);p[2]=4.0f;spawn_offset(858,-200,275.0,p,3);}
    if(sequence_index_13e==2 && S(0x730)==1){next_sequence_block();zero_motion();F(0x100)=0.5f;F(0xf0)=1600.0f;}
    if(sequence_index_13e==3){F(0xf8)=static_cast<float>(F(0xf8)-0.5);if(static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=marisa_surface(this);zero_motion();}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){float p[3]={0.0f,0.0f,1.0f};spawn_offset(858,0,0.0,p,3);S(0x48a)=40;event(23);sequence_window(0,5,60);secondary_cycle();effect(115,static_cast<float>(66*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+81.0),B(0x104),1);F(0xf4)=-30.0f;}return;
case 608:
    landing();texture(5,2);
    if(sequence_index_13e<5 && S(0x730)>0){
        if(sequence_index_13e<4 && S(0x730)%4==1){dispatch_character_wave_handle(19);float p[4];p[0]=static_cast<float>(static_cast<double>(marisa_random(40))-20.0);p[1]=10.0f;p[2]=static_cast<float>(marisa_random(4));p[3]=0.0f;spawn_offset(859,25,87.0,p,4);}++S(0x730);
    }
    if((sequence_index_13e==1 || sequence_index_13e==3) && time_counter_144>40){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(5)){set_action_and_finalize(0);return;}if(entry(1))spell_flash(-23,94.0,1);
    if(entry(6))spell_flash(-25,106.0,1);
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142)S(0x730)=1;
    if(sequence_index_13e==7 && frame_index_140==2 && !frame_timer_142)S(0x730)=1;return;
case 610:
    landing();
    if(sequence_index_13e==1){float p[4]={static_cast<float>((15*S(0x732)+S(0x730))*6),10.0f,static_cast<float>(S(0x732)%4),0.0f};spawn_offset(861,28,185.0,p,4);++S(0x732);++S(0x730);if(sequence_index_13e==1 && time_counter_144>60){next_sequence_block();return;}}
    if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && frame_index_140==2 && !frame_timer_142){S(0x48a)=40;event(23);effect(115,static_cast<float>(F(0xec)-20*facing()),static_cast<float>(F(0xf0)+80.0),B(0x104),1);sequence_window(0,1,60);}
    if(entry(6))spell_flash(-25,106.0,4);
    if(!sequence_index_13e && frame_index_140==5 && !frame_timer_142){S(0x730)=1;float p[4]={0.0f,0.0f,4.0f,0.0f};spawn_offset(861,28,185.0,p,4);p[2]=5.0f;p[3]=0.0f;spawn_offset(861,28,185.0,p,4);}
    if(sequence_index_13e==7 && frame_index_140==2 && !frame_timer_142)S(0x730)=1;return;
case 611:
    if(sequence_index_13e==3)landing();texture(5,2);
    if(sequence_index_13e==1 || sequence_index_13e==2){F(0xf8)-=F(0x100);F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>-1.0f)F(0xf4)=-1.0f;if(F(0xf4)>0.0f)F(0xf4)=0.0f;if(static_cast<unsigned char>(crossed())){F(0xf0)=marisa_surface(this);zero_motion();select_sequence(3);}}
    if(advance())set_action_and_finalize(0);if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9)spell_flash(-23,94.0,2);
    if(entry(1)){dispatch_character_wave_handle(20);float p[4]={0.0f,25.0f,0.0f,0.0f};F(0xf4)=-25.0f;F(0xf8)=10.0f;F(0x100)=0.5f;spawn_offset(860,73,95.0,p,4);effect(127,static_cast<float>(200*facing()+static_cast<double>(F(0xec))),F(0xf0),B(0x104),-1);}return;
case 612:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==5){float p[4]={0.0f,0.0f,0.0f,0.0f};spawn_offset(863,70,165.0,p,4);dispatch_character_wave_handle(7);}
        if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){S(0x48a)=40;event(23);effect(115,static_cast<float>(F(0xec)-22*facing()),static_cast<float>(F(0xf0)+104.0),B(0x104),1);sequence_window(0,1,60);}
    }return;
case 613:
    if(sequence_index_13e==2)landing();
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(2);F(0xf0)=marisa_surface(this);return;}}
    if(sequence_index_13e==1 && time_counter_144>20){set_action_and_finalize(9);return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3){F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x100)=0.0f;spell_flash(-46,150.0,1);}
        if(!frame_timer_142 && frame_index_140==6){dispatch_character_wave_handle(7);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;float p[4]={0.0f,0.0f,1.0f,0.0f};spawn_offset(863,30,62.0,p,4);}
    }return;
case 615:
    landing();texture(5,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==7){
            dispatch_character_wave_handle(24);S(0x7a6)=600;S(0x7a4)=0;float p[3];float n=0.0f;
            do{p[0]=static_cast<float>(90.0*n);p[1]=0.0f;p[2]=static_cast<float>(n+0.0);spawn(865,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1,p,3);n=static_cast<float>(n+1.0);}while(n<4.0f);
            for(int angle=0;angle<360;angle+=45){p[0]=static_cast<float>(static_cast<double>(angle)+30.0+static_cast<double>(marisa_random(40)));p[1]=13.0f;p[2]=2.0f;spawn(848,F(0xec),F(0xf0),B(0x104),(p[0]>=0.0f && p[0]<=180.0f)?1:-1,p,3);}
        }
        if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142)spell_flash(-36,83.0,2);
    }return;
case 619:
    landing();texture(5,2);
    if((sequence_index_13e==1 && time_counter_144>44) || (sequence_index_13e==4 && time_counter_144>89) || (sequence_index_13e==5 && time_counter_144>39)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);if(entry(4))spawn_offset(990,-80,130.0,0,0);
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==3)spell_flash(-16,100.0,5);if(!frame_timer_142 && frame_index_140==5){float p[3]={0.0f,0.0f,11.0f};spawn_offset(869,100,105.0,p,3);dispatch_character_wave_handle(10);++S(0x732);}}return;
case 658:
    if(sequence_index_13e==5)landing();else texture(5,2);
    if(S(0x730)>0){if(sequence_index_13e<4 && S(0x730)%4==1){dispatch_character_wave_handle(19);float p[4];p[0]=static_cast<float>(static_cast<double>(marisa_random(40))-20.0);p[1]=10.0f;p[2]=static_cast<float>(marisa_random(4));p[3]=0.0f;spawn_offset(859,25,107.0,p,4);}++S(0x730);}
    if((sequence_index_13e==1 || sequence_index_13e==3) && time_counter_144>40){next_sequence_block();return;}
    if(sequence_index_13e==4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();F(0xf0)=marisa_surface(this);return;}}
    if(advance())set_action_and_finalize(0);if(entry(5)){set_action_and_finalize(9);return;}if(entry(1))spell_flash(-23,106.0,1);
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142)S(0x730)=1;
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.3f;return;
