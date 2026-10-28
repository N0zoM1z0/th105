case 500:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
        I(0x180)=1;counter(200,120);phase_counter(50);aim_to_peer();if(F(0x744)<-10.0f)F(0x744)=-10.0f;if(F(0x744)>10.0f)F(0x744)=10.0f;
        float p[3]={F(0x744),1.0f,0.0f};spawn_offset(810,72,95.0,p,3);
        p[2]=5.0f;spawn_offset(810,72,95.0,p,3);
        dispatch_character_wave_handle(5);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;dispatch_character_wave_handle(5);}return;
case 501:
    landing();if(!I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
        I(0x180)=1;counter(200,120);phase_counter(50);aim_to_peer();if(F(0x744)<-50.0)F(0x744)=-50.0f;if(F(0x744)>-30.0)F(0x744)=-30.0f;
        float p[3]={F(0x744),1.0f,0.0f};spawn_offset(810,68,127.0,p,3);
        p[2]=5.0f;spawn_offset(810,68,127.0,p,3);
        dispatch_character_wave_handle(5);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;dispatch_character_wave_handle(5);}return;
case 505:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
        I(0x180)=1;counter(200,120);phase_counter(50);aim_to_peer();if(F(0x744)<-10.0f)F(0x744)=-10.0f;if(F(0x744)>10.0f)F(0x744)=10.0f;
        float p[3]={F(0x744),20.0f,0.0f};spawn_offset(811,72,95.0,p,3);
        p[2]=4.0f;spawn_offset(811,72,95.0,p,3);
        dispatch_character_wave_handle(15);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;dispatch_character_wave_handle(5);}return;
case 506:
    landing();if(!I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
        I(0x180)=1;counter(200,120);phase_counter(50);aim_to_peer();if(F(0x744)<-50.0)F(0x744)=-50.0f;if(F(0x744)>-30.0)F(0x744)=-30.0f;
        float p[3]={F(0x744),20.0f,0.0f};spawn_offset(811,68,127.0,p,3);
        p[2]=4.0f;
        dispatch_character_wave_handle(15);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;dispatch_character_wave_handle(5);}return;
case 510:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
        I(0x180)=1;counter(200,120);phase_counter(50);
        float p[3]={-40.0f,30.0f,0.0f};spawn_offset(812,68,127.0,p,3);
        p[2]=5.0f;spawn_offset(812,68,127.0,p,3);
        dispatch_character_wave_handle(5);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;dispatch_character_wave_handle(5);}return;
case 511:
    landing();if(!I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
        I(0x180)=1;counter(200,120);phase_counter(50);
        float p[3]={-30.0f,50.0f,0.0f};spawn_offset(812,68,127.0,p,3);
        p[2]=5.0f;spawn_offset(812,68,127.0,p,3);
        dispatch_character_wave_handle(5);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){I(0x180)=1;dispatch_character_wave_handle(5);}return;
case 520:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(4))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8){dispatch_character_wave_handle(7);I(0x180)=1;counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(815,60,108.0,p,3);}
    if(sequence_index_13e==2 && time_counter_144>19)next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==6){dispatch_character_wave_handle(7);I(0x180)=1;}
    if(sequence_index_13e==6 && time_counter_144>19)next_sequence_block();return;
case 521:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(4))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(7);I(0x180)=1;counter(200,120);phase_counter(50);float p[3]={-25.0f,-0.5f,0.0f};spawn_offset(815,20,145.0,p,3);}
    if(sequence_index_13e==2 && time_counter_144>29)next_sequence_block();
    if(entry(5)){dispatch_character_wave_handle(7);I(0x180)=1;}
    if(sequence_index_13e==6 && time_counter_144>19)next_sequence_block();return;
case 525:
    landing();if(!I(0x6c0))B(0x750)=0;expand_cone();
    if(sequence_index_13e==1){
        if(time_counter_144%30==0){float p[3]={0.0f,1.0f,4.0f};spawn_offset(816,50,110.0,p,3);p[1]=-1.0f;p[2]=4.0f;spawn_offset(816,50,110.0,p,3);}
        if(!B(0x750)||time_counter_144>179){next_sequence_block();S(0x730)=0;return;}
    }
    if(S(0x730)==1){if(S(0x732)%60==0)dispatch_character_wave_handle(13);++S(0x732);}
    if(entry(2)){
        float p[3]={static_cast<float>(udonge_random(360)),0.0f,3.0f};spawn_at_peer(816,p);dispatch_character_wave_handle(14);
        if(peer_in_cone()){p[1]=1.0f;spawn_at_peer(816,p);}
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8){
        S(0x730)=1;counter(200,120);phase_counter(50);I(0x180)=1;
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(816,50,110.0,p,3);p[1]=1.0f;p[2]=0.0f;spawn_offset(816,50,110.0,p,3);
        F(0x7b0)=0.0f;F(0x73c)=1.2f;
    }return;
case 526:
    landing();if(!I(0x6c4))B(0x750)=0;expand_cone();
    if(sequence_index_13e==1){
        if(time_counter_144%30==0){float p[3]={0.0f,1.0f,4.0f};spawn_offset(816,50,110.0,p,3);p[1]=-1.0f;p[2]=4.0f;spawn_offset(816,50,110.0,p,3);}
        if(!B(0x750)||time_counter_144>179){next_sequence_block();S(0x730)=0;return;}
    }
    if(S(0x730)==1){if(S(0x732)%60==0)dispatch_character_wave_handle(13);++S(0x732);}
    if(entry(2)){
        float p[3]={static_cast<float>(udonge_random(360)),0.0f,3.0f};spawn_at_peer(816,p);dispatch_character_wave_handle(14);
        if(peer_in_cone()){p[1]=1.0f;spawn_at_peer(816,p);}
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8){
        S(0x730)=1;counter(200,120);phase_counter(50);I(0x180)=1;
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(816,50,110.0,p,3);p[1]=1.0f;p[2]=0.0f;spawn_offset(816,50,110.0,p,3);
        F(0x7b0)=0.0f;F(0x73c)=1.2f;
    }return;
case 527:
    if(!I(0x6c0))B(0x750)=0;expand_cone();
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(529);return;}
    if(sequence_index_13e==1){
        if(time_counter_144%30==0){float p[3]={0.0f,1.0f,4.0f};spawn_offset(816,50,140.0,p,3);p[1]=-1.0f;p[2]=4.0f;spawn_offset(816,50,140.0,p,3);}
        if(!B(0x750)||time_counter_144>179){next_sequence_block();S(0x730)=0;return;}
    }
    if(S(0x730)==1){if(S(0x732)%60==0)dispatch_character_wave_handle(13);++S(0x732);}
    if(entry(2)){
        float p[3]={static_cast<float>(udonge_random(360)),0.0f,3.0f};spawn_at_peer(816,p);dispatch_character_wave_handle(14);
        if(peer_in_cone()){p[1]=1.0f;spawn_at_peer(816,p);}
    }
    if(advance())set_action_and_finalize(9);
    if(entry(3))F(0x100)=0.5f;
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){
        S(0x730)=1;counter(200,120);phase_counter(50);I(0x180)=1;
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(816,50,140.0,p,3);p[1]=1.0f;p[2]=0.0f;spawn_offset(816,50,140.0,p,3);
        F(0x7b0)=0.0f;F(0x73c)=1.2f;
    }return;
case 528:
    if(!I(0x6c4))B(0x750)=0;expand_cone();
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(529);return;}
    if(sequence_index_13e==1){
        if(time_counter_144%30==0){float p[3]={0.0f,1.0f,4.0f};spawn_offset(816,50,140.0,p,3);p[1]=-1.0f;p[2]=4.0f;spawn_offset(816,50,140.0,p,3);}
        if(!B(0x750)||time_counter_144>179){next_sequence_block();S(0x730)=0;return;}
    }
    if(S(0x730)==1){if(S(0x732)%60==0)dispatch_character_wave_handle(13);++S(0x732);}
    if(entry(2)){
        float p[3]={static_cast<float>(udonge_random(360)),0.0f,3.0f};spawn_at_peer(816,p);dispatch_character_wave_handle(14);
        if(peer_in_cone()){p[1]=1.0f;spawn_at_peer(816,p);}
    }
    if(advance())set_action_and_finalize(9);
    if(entry(3))F(0x100)=0.5f;
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){
        S(0x730)=1;counter(200,120);phase_counter(50);I(0x180)=1;
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(816,50,140.0,p,3);p[1]=1.0f;p[2]=0.0f;spawn_offset(816,50,140.0,p,3);
        F(0x7b0)=0.0f;F(0x73c)=1.2f;
    }return;
case 529:landing();if(advance())set_action_and_finalize(0);return;
case 530:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==4 && B(0x750)==1){next_sequence_block();effect(62,static_cast<float>(F(0xec)-45*facing()),static_cast<float>(F(0xf0)+132.0),B(0x104),1);}
        if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,10.0f,0.0f};spawn_offset(817,60,100.0,p,3);I(0x180)=1;counter(200,120);phase_counter(50);dispatch_character_wave_handle(12);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3){float p[3]={0.0f,10.0f,1.0f};spawn_offset(817,60,100.0,p,3);I(0x180)=1;counter(200,120);phase_counter(50);dispatch_character_wave_handle(12);}return;
case 531:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)==1){next_sequence_block();effect(62,static_cast<float>(32*facing()+F(0xec)),static_cast<float>(F(0xf0)+57.0),B(0x104),1);}
        if(!frame_timer_142 && frame_index_140==5){float p[3]={-30.0f,10.0f,0.0f};spawn_offset(817,25,145.0,p,3);I(0x180)=1;counter(200,120);phase_counter(50);dispatch_character_wave_handle(12);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){float p[3]={-30.0f,10.0f,1.0f};spawn_offset(817,25,145.0,p,3);I(0x180)=1;counter(200,120);phase_counter(50);dispatch_character_wave_handle(12);}return;
case 540:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(4))set_action_and_finalize(0);
    if(entry(1)){dispatch_character_wave_handle(8);I(0x180)=1;counter(200,120);phase_counter(50);float p[3]={2.5f,static_cast<float>(C(0x606)*45.0+120.0),0.0f};spawn_offset(820,-8,120.0,p,3);}
    if(sequence_index_13e==2 && time_counter_144>11)next_sequence_block();
    if(entry(5)){dispatch_character_wave_handle(8);I(0x180)=1;}
    if(sequence_index_13e==6 && time_counter_144>19)next_sequence_block();return;
case 541:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(4))set_action_and_finalize(0);
    if(entry(1)){dispatch_character_wave_handle(8);I(0x180)=1;counter(200,120);phase_counter(50);float p[3]={1.5f,static_cast<float>(C(0x606)*20.0+60.0),0.0f};spawn(820,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+120.0),B(0x104),1,p,3);}
    if(sequence_index_13e==2 && time_counter_144>11)next_sequence_block();
    if(entry(5)){dispatch_character_wave_handle(8);I(0x180)=1;}
    if(sequence_index_13e==6 && time_counter_144>19)next_sequence_block();return;
case 545:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(4))set_action_and_finalize(0);
    if(entry(1)){dispatch_character_wave_handle(17);I(0x180)=1;counter(200,120);phase_counter(50);float p[3]={static_cast<float>(C(0x60a)*static_cast<double>(0.3f)+static_cast<double>(2.2f)),180.0f,0.0f};spawn_offset(821,-8,120.0,p,3);}
    if(sequence_index_13e==2 && time_counter_144>11)next_sequence_block();
    if(entry(5)){dispatch_character_wave_handle(8);I(0x180)=1;}
    if(sequence_index_13e==6 && time_counter_144>19)next_sequence_block();return;
case 546:
    landing();if(!I(0x6c4))B(0x750)=0;if(advance())set_action_and_finalize(0);if(entry(4))set_action_and_finalize(0);
    if(entry(1)){dispatch_character_wave_handle(8);I(0x180)=1;counter(200,120);phase_counter(50);float p[3]={static_cast<float>(C(0x60a)*0.25+1.5),90.0f,0.0f};spawn(821,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+120.0),B(0x104),1,p,3);}
    if(sequence_index_13e==2 && time_counter_144>11)next_sequence_block();
    if(entry(5)){dispatch_character_wave_handle(8);I(0x180)=1;}
    if(sequence_index_13e==6 && time_counter_144>19)next_sequence_block();return;
case 550:
    landing();if(!I(0x6c0))B(0x750)=0;if(S(0x736) && !sequence_index_13e)S(0x4ae)=2;
    if(advance())set_action_and_finalize(0);
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){
        if(sequence_index_13e!=1)return;
        dispatch_character_wave_handle(18);I(0x180)=1;counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(822,0,120.0,p,3);
    }
    if(sequence_index_13e==1 && time_counter_144>24)next_sequence_block();return;
case 551:
    landing();if(!I(0x6c0))B(0x750)=0;if(S(0x736) && !sequence_index_13e)S(0x4ae)=2;
    if(advance())set_action_and_finalize(0);
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){
        if(sequence_index_13e!=1)return;
        dispatch_character_wave_handle(18);I(0x180)=1;counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(822,0,120.0,p,3);
    }
    if(sequence_index_13e==1 && time_counter_144>24)next_sequence_block();return;
