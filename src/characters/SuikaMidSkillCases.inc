case 500:
    landing();B(0x17c)=0;if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);
    if(entry(3) || entry(4)){set_action_and_finalize(0);return;}
    if(sequence_index_13e==1){
        if(S(0x730)>13 && (!B(0x750) || S(0x730)>119)){
            if(C(0x604)<2){next_sequence_block();return;}
            if(C(0x604)==2 || C(0x604)==3){select_sequence(3);return;}
            if(C(0x604)>3){select_sequence(4);return;}
        }
        if(S(0x730)==30){effect(62,static_cast<float>(F(0xec)-5*facing()),static_cast<float>(F(0xf0)+90.0),B(0x104),1);S(0x732)=1;}
        ++S(0x730);
    }
    if((sequence_index_13e==2 || sequence_index_13e==3 || sequence_index_13e==4) && !frame_timer_142 && frame_index_140==2){
        if(S(0x732)==1){float p[4]={0.0f,25.0f,0.0f,120.0f};spawn_offset(810,140,70.0,p,4);
            effect(128,static_cast<float>(200*facing()+F(0xec)),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);layout(12.0f);return;}
        float p[4]={0.0f,8.0f,0.0f,static_cast<float>(C(0x604)*5.0+15.0)};spawn_offset(810,140,70.0,p,4);
        effect(128,static_cast<float>(200*facing()+F(0xec)),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);layout(8.0f);
    }return;
case 501:
    landing();B(0x17c)=0;if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);
    if(entry(3) || entry(4)){set_action_and_finalize(0);return;}
    if(sequence_index_13e==1){
        if(S(0x730)>13 && (!B(0x750) || S(0x730)>119)){
            if(C(0x604)<2){next_sequence_block();return;}
            if(C(0x604)==2 || C(0x604)==3){select_sequence(3);return;}
            if(C(0x604)>3){select_sequence(4);return;}
        }
        if(S(0x730)==30){effect(62,static_cast<float>(13*facing()+F(0xec)),static_cast<float>(F(0xf0)+142.0),B(0x104),1);S(0x732)=1;}
        ++S(0x730);
    }
    if((sequence_index_13e==2 || sequence_index_13e==3 || sequence_index_13e==4) && !frame_timer_142 && frame_index_140==4){
        if(S(0x732)==1){float p[4]={-60.0f,25.0f,4.0f,120.0f};spawn_offset(810,80,166.0,p,4);
            effect(128,static_cast<float>(200*facing()+F(0xec)),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);layout(12.0f);return;}
        float p[4]={-60.0f,8.0f,4.0f,static_cast<float>(C(0x604)*5.0+15.0)};spawn_offset(810,80,166.0,p,4);
        effect(128,static_cast<float>(200*facing()+F(0xec)),F(0xf0),B(0x104),-1);counter(200,120);phase_counter(50);dispatch_character_wave_handle(10);layout(8.0f);
    }return;
case 505:
    landing();B(0x17c)=4;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,7.0f};spawn_offset(815,-10,250.0,p,3);counter(200,120);phase_counter(50);}
    if(sequence_index_13e==1){if(S(0x730)>=0 && (!B(0x750) || S(0x730)>179)){next_sequence_block();return;}++S(0x730);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)release_fragments811();return;
case 506:
    landing();B(0x17c)=4;if(!I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,7.0f};spawn_offset(815,-10,250.0,p,3);counter(200,120);phase_counter(50);}
    if(sequence_index_13e==1){if(S(0x730)>=0 && (!B(0x750) || S(0x730)>179)){next_sequence_block();return;}++S(0x730);}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)release_fragments811();return;
case 507:
    if(sequence_index_13e==3)landing();B(0x17c)=4;if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);select_sequence(3);}}
    if(advance()){set_action_and_finalize(0);return;}if(entry(3)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,7.0f};spawn_offset(815,-10,250.0,p,3);counter(200,120);phase_counter(50);}
    if(sequence_index_13e==1){if(S(0x730)>=0 && (!B(0x750) || S(0x730)>179)){next_sequence_block();return;}++S(0x730);}
    if(sequence_index_13e==2){
        if(!frame_timer_142 && frame_index_140==2){release_fragments811();F(0x100)=0.5f;F(0xf4)=-6.0f;F(0xf8)=7.5f;}
        if(!frame_timer_142 && frame_index_140==8)F(0x100)=0.5f;
    }return;
case 508:
    if(sequence_index_13e==3)landing();B(0x17c)=4;if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);select_sequence(3);}}
    if(advance()){set_action_and_finalize(0);return;}if(entry(3)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,7.0f};spawn_offset(815,-10,250.0,p,3);counter(200,120);phase_counter(50);}
    if(sequence_index_13e==1){if(S(0x730)>=0 && (!B(0x750) || S(0x730)>179)){next_sequence_block();return;}++S(0x730);}
    if(sequence_index_13e==2){
        if(!frame_timer_142 && frame_index_140==2){release_fragments811();F(0x100)=0.5f;F(0xf4)=-6.0f;F(0xf8)=7.5f;}
        if(!frame_timer_142 && frame_index_140==8)F(0x100)=0.5f;
    }return;
case 520:
    if(!sequence_index_13e || sequence_index_13e==6)landing();B(0x17c)=1;
    F(0xf8)-=F(0x100);
    if(sequence_index_13e==4 || sequence_index_13e==5){F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>-5.0f)F(0xf4)=-5.0f;}
    if(static_cast<unsigned char>(crossed())){
        if(sequence_index_13e==3){dispatch_character_wave_handle(12);layout(6.0f);select_sequence(4);F(0xf0)=suika_surface(this);F(0xf4)=-12.5f;F(0xf8)=5.5f;F(0x100)=0.35f;impact_fragments811();return;}
        if(sequence_index_13e==4 || sequence_index_13e==5){select_sequence(6);F(0xf0)=suika_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){F(0xf4)=3.0f;F(0xf8)=12.5f;F(0x100)=0.25f;}
    if(entry(3)){F(0xf4)=18.0f;F(0xf8)=-18.0f;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;
case 521:
    if(!sequence_index_13e || sequence_index_13e==6)landing();B(0x17c)=1;
    F(0xf8)-=F(0x100);
    if(sequence_index_13e==4 || sequence_index_13e==5){F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>-5.0f)F(0xf4)=-5.0f;}
    if(static_cast<unsigned char>(crossed())){
        if(sequence_index_13e==3){dispatch_character_wave_handle(12);layout(6.0f);select_sequence(4);F(0xf0)=suika_surface(this);F(0xf4)=-12.5f;F(0xf8)=5.5f;F(0x100)=0.35f;impact_fragments811();return;}
        if(sequence_index_13e==4 || sequence_index_13e==5){select_sequence(6);F(0xf0)=suika_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){F(0xf4)=8.0f;F(0xf8)=12.5f;F(0x100)=0.25f;}
    if(entry(3)){F(0xf4)=18.0f;F(0xf8)=-18.0f;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;
case 522:
    if(sequence_index_13e==5)landing();B(0x17c)=1;
    F(0xf8)-=F(0x100);
    if(sequence_index_13e==3 || sequence_index_13e==4){F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>-5.0f)F(0xf4)=-5.0f;}
    if(static_cast<unsigned char>(crossed())){
        if(sequence_index_13e==2){dispatch_character_wave_handle(12);layout(6.0f);select_sequence(3);F(0xf0)=suika_surface(this);F(0xf4)=-12.5f;F(0xf8)=5.5f;F(0x100)=0.35f;impact_fragments811();return;}
        if(sequence_index_13e==3 || sequence_index_13e==4){select_sequence(5);F(0xf0)=suika_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(2)){F(0xf4)=18.0f;F(0xf8)=-18.0f;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;
case 523:
    if(sequence_index_13e==5)landing();B(0x17c)=1;
    F(0xf8)-=F(0x100);
    if(sequence_index_13e==3 || sequence_index_13e==4){F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>-5.0f)F(0xf4)=-5.0f;}
    if(static_cast<unsigned char>(crossed())){
        if(sequence_index_13e==2){dispatch_character_wave_handle(12);layout(6.0f);select_sequence(3);F(0xf0)=suika_surface(this);F(0xf4)=-12.5f;F(0xf8)=5.5f;F(0x100)=0.35f;impact_fragments811();return;}
        if(sequence_index_13e==3 || sequence_index_13e==4){select_sequence(5);F(0xf0)=suika_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(2)){F(0xf4)=18.0f;F(0xf8)=-18.0f;dispatch_character_wave_handle(11);counter(200,120);phase_counter(50);}return;
case 525:
    landing();B(0x17c)=5;if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==6){
        layout(8.0f);float p[3];p[2]=2.0f;float n=0.0f;
        do{p[0]=static_cast<float>((n*60.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);
           S(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(816,103,0.0,p,3,B(0x730));n=static_cast<float>(n+1.0);
        }while(n<6.0f);
        p[2]=3.0f;spawn_offset(816,103,0.0,p,3,255);p[2]=0.0f;
        double count=static_cast<float>(C(0x609)+5.0);n=0.0f;
        while(n<count){p[0]=static_cast<float>(-static_cast<float>(suika_random(80))-20.0);p[1]=static_cast<float>(static_cast<float>(suika_random(18))+7.0);
            S(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(816,103,0.0,p,3);n=static_cast<float>(n+1.0);
        }
        effect(127,F(0xec),F(0xf0),B(0x104),-1);dispatch_character_wave_handle(18);counter(200,120);phase_counter(50);
    }return;
case 526:
    landing();B(0x17c)=5;if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==6){
        layout(8.0f);float p[3];p[2]=2.0f;float n=0.0f;
        do{p[0]=static_cast<float>((n*60.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);
           S(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(816,103,0.0,p,3,B(0x730));n=static_cast<float>(n+1.0);
        }while(n<6.0f);
        p[2]=3.0f;spawn_offset(816,103,0.0,p,3,255);p[2]=0.0f;
        double count=static_cast<float>(C(0x609)+7.0);n=0.0f;
        while(n<count){p[0]=static_cast<float>(-static_cast<float>(suika_random(80))-20.0);p[1]=static_cast<float>(static_cast<float>(suika_random(20))+10.0);
            S(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(816,103,0.0,p,3);n=static_cast<float>(n+1.0);
        }
        effect(127,F(0xec),F(0xf0),B(0x104),-1);dispatch_character_wave_handle(18);counter(200,120);phase_counter(50);
    }return;
case 530:
    landing();B(0x17c)=9;if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){I(0x180)=1;layout(8.0f);float p[3]={-80.0f,25.0f,0.0f};spawn_offset(821,100,0.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);dispatch_character_wave_handle(23);counter(200,120);phase_counter(50);}return;
case 531:
    landing();B(0x17c)=9;if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){I(0x180)=1;layout(8.0f);float p[3]={-70.0f,35.0f,0.0f};spawn_offset(821,100,0.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);dispatch_character_wave_handle(23);counter(200,120);phase_counter(50);}return;
case 540:
    landing();B(0x17c)=2;if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){
        phase_counter(50);counter(200,120);I(0x180)=1;float p[3];p[2]=0.0f;
        for(int n=0;n<C(0x606)+6;++n){
            p[0]=static_cast<float>(static_cast<float>(static_cast<float>(suika_random(50))*static_cast<double>(0.1f))+5.0);
            p[1]=static_cast<float>(static_cast<float>(suika_random(14))-7.0);
            spawn_offset(812,43,116.0,p,3);
        }dispatch_character_wave_handle(13);
    }return;
case 541:
    landing();B(0x17c)=2;if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){
        phase_counter(50);counter(200,120);I(0x180)=1;float p[3];p[2]=2.0f;
        for(int n=0;n<C(0x606)+6;++n){
            p[0]=static_cast<float>(-static_cast<float>(suika_random(45))-10.0);p[1]=static_cast<float>(suika_random(6)+6u);
            spawn_offset(812,43,116.0,p,3);
        }dispatch_character_wave_handle(13);
    }return;
case 545:
    B(0x17c)=6;if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e>=2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=suika_surface(this);return;}}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3){phase_counter(50);counter(200,120);F(0x744)=static_cast<float>(suika_random(45));F(0x73c)=10.0f;F(0x740)=15.0f;I(0x180)=1;dispatch_character_wave_handle(19);}
        if(frame_index_140>=2){if(time_counter_144%2==0)mist817();if(frame_index_140==3){if(B(0x113)<15)B(0x113)=0;else B(0x113)-=15;}}
    }
    if(sequence_index_13e==1){
        if(time_counter_144%2==0)mist817();
        if(!S(0x730)){F(0x73c)+=F(0x740);F(0x740)=static_cast<float>(F(0x740)-0.75);if(F(0x740)<=0.0f){F(0x740)=0.0f;S(0x730)=1;}}
        if(S(0x730)==1){
            F(0x740)=static_cast<float>(F(0x740)+static_cast<double>(0.15f));F(0x73c)-=F(0x740);
            if(F(0x73c)<=0.0f){
                B(0x113)=255;dispatch_character_wave_handle(20);F(0x73c)=0.0f;next_sequence_block();F(0xf4)=static_cast<float>(F(0xf4)*static_cast<double>(0.3f));F(0xf8)=12.0f;F(0x100)=0.5f;
                if(C(0x60a)>3){
                    float p[3];float n=0.0f;do{p[0]=static_cast<float>(n*60.0);p[1]=15.0f;p[2]=3.0f;spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<6.0f);
                    n=0.0f;do{p[0]=static_cast<float>(n*60.0+30.0);p[1]=17.5f;p[2]=3.0f;spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<6.0f);return;
                }
                if(C(0x60a)<2)return;
                float p[3];float n=0.0f;do{p[0]=static_cast<float>(n*60.0);p[1]=15.0f;p[2]=3.0f;spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<6.0f);return;
            }
        }steer_cloud(static_cast<double>(0.05f));
    }return;
case 546:
    B(0x17c)=6;if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e>=2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=suika_surface(this);return;}}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){
        phase_counter(50);counter(200,120);F(0x744)=static_cast<float>(suika_random(45));F(0x73c)=10.0f;F(0x740)=15.0f;I(0x180)=1;dispatch_character_wave_handle(19);
        float n=0.0f;do{float p[3]={static_cast<float>(n*45.0+F(0x744)),0.0f,0.0f};spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<8.0f);
    }
    if(sequence_index_13e==1){
        if(!S(0x730)){F(0x73c)+=F(0x740);F(0x740)=static_cast<float>(F(0x740)-0.75);if(F(0x740)<=0.0f){F(0x740)=0.0f;S(0x730)=1;}}
        if(S(0x730)==1){F(0x740)=static_cast<float>(F(0x740)+static_cast<double>(0.1f));F(0x73c)-=F(0x740);
            if(F(0x73c)<=0.0f){dispatch_character_wave_handle(20);F(0x73c)=0.0f;next_sequence_block();zero_motion();
                float n=0.0f;do{float p[3]={static_cast<float>(n*45.0),15.0f,3.0f};spawn_offset(817,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<8.0f);return;
            }
        }steer_cloud(static_cast<double>(0.1f));
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==6)F(0x100)=0.5f;return;
case 547:
    if(sequence_index_13e==2)landing();B(0x17c)=2;
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);double predicted=static_cast<double>(F(0xf8))+F(0xf0);if(suika_surface(this)>=predicted && F(0xf8)<0.0f){zero_motion();select_sequence(2);F(0xf0)=suika_surface(this);return;}}
    if(sequence_index_13e<2 && !I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){if(frame_index_140==8 && B(0x750)==1){next_sequence_block();return;}
        if(!frame_timer_142 && frame_index_140==6){I(0x180)=1;dispatch_character_wave_handle(7);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;spawn_offset(816,30,62.0,0,0);counter(200,120);phase_counter(50);}
    }return;
