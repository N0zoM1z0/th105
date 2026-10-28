case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
        event(55);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(141,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1);
        effect(142,F(0xec),F(0xf0),B(0x104),-1);
    }return;
case 696:
    landing();
    if(!frame_timer_142 && !frame_index_140){if(!B(0x47e))zero_motion();B(0x184)=1;I(0x180)=0;}
    if(frame_index_140>4){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){
        if(frame_index_140==3)F(0xf4)=15.0f;
        if(!frame_timer_142 && frame_index_140==5){dispatch_character_wave_handle(1);F(0xf4)=5.0f;B(0x47e)=0;}
    }return;
case 710:
    landing();if(advance())set_action_and_finalize(700);
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){
        if(sequence_index_13e!=1)return;
        F(0x73c)=90.0f;
        switch(g_match_identifier){case 0:S(0x730)=2;break;case 1:S(0x730)=4;break;case 2:S(0x730)=6;break;case 3:S(0x730)=8;break;}
    }
    if(sequence_index_13e!=1)return;
    if(time_counter_144%12==0 && S(0x730)>0){
        float p[3]={F(0x73c),20.0f,0.0f};orbit900(p);
        p[0]=-F(0x73c);p[1]=20.0f;p[2]=0.0f;orbit900(p);
        dispatch_character_wave_handle(5);--S(0x730);F(0x73c)=static_cast<float>(F(0x73c)+10.0);
    }
    if(!S(0x730)){++S(0x732);if(S(0x732)>=90)next_sequence_block();}return;
case 725:
    landing();if(advance())set_action_and_finalize(0);
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){
        if(sequence_index_13e!=1)return;
        dispatch_character_wave_handle(8);float p[3];
        switch(g_match_identifier){
        case 0:p[0]=2.5f;p[1]=240.0f;p[2]=0.0f;spawn_offset(911,-8,120.0,p,3);break;
        case 1:p[0]=2.5f;p[1]=240.0f;p[2]=0.0f;spawn_offset(911,-8,120.0,p,3);break;
        case 2:p[0]=2.75f;p[1]=300.0f;p[2]=0.0f;spawn_offset(911,-8,120.0,p,3);break;
        case 3:p[0]=3.0f;p[1]=360.0f;p[2]=0.0f;spawn_offset(911,-8,120.0,p,3);break;
        }
    }
    if(sequence_index_13e==1 && time_counter_144>=48)next_sequence_block();return;
case 726:
    landing();expand_cone();
    if(sequence_index_13e==1){
        if(time_counter_144%30==0){
            float p[3]={0.0f,1.0f,4.0f};spawn_offset(912,50,110.0,p,3);
            p[1]=-1.0f;p[2]=4.0f;spawn_offset(912,50,110.0,p,3);
        }
        if(peer_in_cone())S(0x7ae)=3;
        if(time_counter_144>=180){next_sequence_block();S(0x730)=0;return;}
    }
    if(S(0x730)==1){if(S(0x732)%60==0)dispatch_character_wave_handle(13);++S(0x732);}
    if(entry(2)){
        float p[3]={static_cast<float>(udonge_random(360)),0.0f,3.0f};spawn_at_peer(912,p);dispatch_character_wave_handle(14);
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8){
        S(0x730)=1;float p[3]={0.0f,0.0f,0.0f};spawn_offset(912,50,110.0,p,3);
        p[1]=1.0f;p[2]=0.0f;spawn_offset(912,50,110.0,p,3);F(0x7b0)=0.0f;
        switch(g_match_identifier){case 0:F(0x73c)=0.6f;return;case 1:F(0x73c)=0.8f;return;case 2:F(0x73c)=1.2f;return;case 3:F(0x73c)=1.5f;return;}
    }return;
case 730:
    if(sequence_index_13e==1){
        switch(g_match_identifier){case 0:S(0x736)=2;break;case 1:S(0x736)=4;break;case 2:S(0x736)=5;break;case 3:S(0x736)=6;break;}
        if(entry(1))S(0x732)=static_cast<short>(udonge_random(S(0x736)));
        if(S(0x730)>=S(0x736)){if(S(0x7a6)<30){next_sequence_block();return;}S(0x7a6)=static_cast<short>(S(0x7a6)-30);}
        if(time_counter_144%15==0 && S(0x730)<S(0x736)){
            dispatch_character_wave_handle(19);
            float p[4];p[0]=static_cast<float>(-45.0-static_cast<float>(udonge_random(40)));
            p[1]=static_cast<float>(static_cast<float>(udonge_random(5))+20.0);p[2]=1.0f;p[3]=0.0f;
            if(S(0x732)==S(0x730))p[3]=1.0f;
            if(S(0x730)%2==0)spawn(920,F(0xec),F(0xf0),B(0x104),1,p,4);
            else spawn(920,F(0xec),F(0xf0),static_cast<unsigned char>(-C(0x104)),1,p,4);
            ++S(0x730);
        }
    }
    if(advance())set_action_and_finalize(0);return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){
        B(0x655)=1;finalize(-1);texture(2,-1);copy_health();
        S(0x76c)=0;S(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);
    }return;
case 795:
    if(!sequence_index_13e){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.3f));
        if(static_cast<unsigned char>(crossed())){select_sequence(1);F(0xf0)=udonge_surface(this);zero_motion();event(30);return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:
    F(0xf4)=3.0f;if(S(0x730)<252)S(0x730)=static_cast<short>(S(0x730)+3);else S(0x730)=255;
    S(0x7a6)=S(0x730);
    if(F(0xec)>=480.0){F(0xec)=480.0f;S(0x7a6)=255;zero_motion();set_action_and_finalize(0);return;}
    if(advance())set_action_and_finalize(0);return;
case 798:
    F(0xf4)=3.0f;if(S(0x730)<252)S(0x730)=static_cast<short>(S(0x730)+3);else S(0x730)=255;
    S(0x7a6)=S(0x730);
    if(F(0xec)<=800.0){F(0xec)=800.0f;S(0x7a6)=255;zero_motion();set_action_and_finalize(700);return;}
    if(advance())set_action_and_finalize(700);return;
