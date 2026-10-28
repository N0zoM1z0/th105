case 600:
    landing();texture(0,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){
        if(frame_index_140==3)spell_flash(-45,143.0,1);
        if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,10.0f,0.0f};spawn_offset(850,60,100.0,p,3);dispatch_character_wave_handle(12);}
    }return;
case 602:
    texture(0,2);if(sequence_index_13e==1 && time_counter_144>=30){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        {float n=0.0f;float p[4];do{p[0]=static_cast<float>(n*60.0);p[1]=25.0f;p[2]=0.0f;p[3]=5.0f;orbit852(p);n=static_cast<float>(n+1.0);}while(n<6.0f);}
        {float n=0.0f;float p[4];do{p[0]=static_cast<float>(n*60.0+30.0);p[1]=25.0f;p[2]=0.0f;p[3]=20.0f;orbit852(p);n=static_cast<float>(n+1.0);}while(n<6.0f);}
        {float n=0.0f;float p[4];do{p[0]=static_cast<float>(60.0+n*60.0);p[1]=25.0f;p[2]=0.0f;p[3]=35.0f;orbit852(p);n=static_cast<float>(n+1.0);}while(n<6.0f);}
    }
    if(!sequence_index_13e && frame_index_140==7 && !frame_timer_142)spell_flash(0,100.0,3);return;
case 603:
    landing();texture(0,2);
    if(sequence_index_13e==1){
        if(time_counter_144%10==0 && S(0x730)<10){float p[3]={0.0f,25.0f,0.0f};spawn_offset(853,60,100.0,p,3);dispatch_character_wave_handle(12);++S(0x730);}
        if(time_counter_144>119){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(-45,143.0,3);return;
case 605:
    if(sequence_index_13e>0 || (!sequence_index_13e && frame_index_140>=7))texture(0,2);
    if(sequence_index_13e==1){
        if(time_counter_144>=120){next_sequence_block();return;}
        if(time_counter_144%5==0){
            if(!time_counter_144)dispatch_character_wave_handle(50);
            if(S(0x730)<=15){
                float p[3]={0.0f,0.0f,0.0f};
                if(S(0x730)==15){dispatch_character_wave_handle(51);p[2]=1.0f;}
                spawn_offset(855,0,130.0,p,3);++S(0x730);
            }
        }
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && frame_index_140==7 && !frame_timer_142)spell_flash(0,100.0,5);return;
case 606:
    landing();texture(0,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){
        if(frame_index_140==3)spell_flash(-45,143.0,1);
        if(!frame_timer_142 && frame_index_140==5){
            float p[3]={0.0f,10.0f,0.0f};spawn_offset(856,150,110.0,p,3);
            int angle=0;do{
                p[0]=static_cast<float>(static_cast<float>(udonge_random(30))+(static_cast<float>(angle)+30.0));
                p[1]=10.0f;p[2]=8.0f;
                if(p[0]>=0.0f && p[0]<=180.0f)spawn_offset(856,150,0.0,p,3,1);
                else spawn_offset(856,150,0.0,p,3,-1);
                angle+=60;
            }while(angle<360);
            dispatch_character_wave_handle(55);
        }
    }return;
case 607:
    landing();texture(0,2);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){
        if(frame_index_140==2)spell_flash(-47,122.0,3);
        if(!frame_timer_142 && frame_index_140==4){
            float p[3]={0.0f,5.0f,9.0f};spawn_offset(857,70,96.0,p,3);
            p[2]=1.0f;spawn_offset(857,70,96.0,p,3);
            int angle=0;do{
                p[0]=static_cast<float>(static_cast<float>(udonge_random(30))+(static_cast<float>(angle)+30.0));
                p[1]=10.0f;p[2]=8.0f;
                if(p[0]>=0.0f && p[0]<=180.0f)spawn_offset(856,96,0.0,p,3,1);
                else spawn_offset(856,96,0.0,p,3,-1);
                angle+=60;
            }while(angle<360);
            dispatch_character_wave_handle(5);
        }
    }return;
case 608:
    landing();if(sequence_index_13e>0 || (!sequence_index_13e && frame_index_140>=7))texture(0,2);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){
        if(frame_index_140==3)spell_flash(35,160.0,2);
        if(!frame_timer_142 && frame_index_140==6){float p[3]={80.0f,40.0f,0.0f};spawn_offset(858,50,50.0,p,3);}
    }return;
case 609:
    if(sequence_index_13e<3)landing();
    else{
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){
            S(0x730)=static_cast<short>(static_cast<short>(static_cast<int>(F(0xf4)))*100);
            S(0x732)=static_cast<short>(static_cast<short>(static_cast<int>(F(0xf8)))*100);
            zero_motion();F(0xf0)=0.0f;set_action_and_finalize(97);layout(5.0f);event(22);return;
        }
    }
    if(sequence_index_13e>0 || (!sequence_index_13e && frame_index_140>=7))texture(0,2);
    if(sequence_index_13e==1 && time_counter_144>=45){
        if(S(0x730)==1){
            F(0x7b4)=0.0f;layout(10.0f);float p[3]={0.0f,0.0f,6.0f};spawn_offset(859,0,100.0,p,3);
            select_sequence(3);dispatch_character_wave_handle(56);F(0xf4)=-30.0f;F(0xf8)=15.0f;F(0x100)=0.5f;return;
        }
        next_sequence_block();return;
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(35,160.0,3);
    if(!time_counter_144){
        if(!frame_timer_142 && !frame_index_140 && sequence_index_13e==1){
            if(!(F(0x7b4)<=2.0f))S(0x730)=1;else F(0x7b4)=static_cast<float>(F(0x7b4)+1.0);
            dispatch_character_wave_handle(54);float p[3]={0.0f,0.0f,0.0f};spawn_offset(859,0,100.0,p,3);
        }
        if(entry(3)){set_action_and_finalize(0);return;}
    }return;
case 650:
    texture(0,2);F(0xf8)-=F(0x100);
    if(sequence_index_13e==2 && static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(10);return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==4){spell_flash(-10,145.0,1);zero_motion();}
        if(!frame_timer_142 && frame_index_140==6){float p[3]={0.0f,10.0f,0.0f};spawn_offset(850,60,135.0,p,3);dispatch_character_wave_handle(12);F(0xf4)=-7.0f;F(0xf8)=6.0f;F(0x100)=0.35f;}
    }return;
case 652:
    texture(0,2);if(sequence_index_13e==1 && time_counter_144>=30){next_sequence_block();F(0x100)=0.5f;return;}
    if(sequence_index_13e==2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(10);return;}}
    if(advance())set_action_and_finalize(9);
    if(entry(1)){
        {float n=0.0f;float p[4];do{p[0]=static_cast<float>(n*60.0);p[1]=25.0f;p[2]=0.0f;p[3]=5.0f;orbit852(p);n=static_cast<float>(n+1.0);}while(n<6.0f);}
        {float n=0.0f;float p[4];do{p[0]=static_cast<float>(n*60.0+30.0);p[1]=25.0f;p[2]=0.0f;p[3]=20.0f;orbit852(p);n=static_cast<float>(n+1.0);}while(n<6.0f);}
        {float n=0.0f;float p[4];do{p[0]=static_cast<float>(60.0+n*60.0);p[1]=25.0f;p[2]=0.0f;p[3]=35.0f;orbit852(p);n=static_cast<float>(n+1.0);}while(n<6.0f);}
    }
    if(!sequence_index_13e && frame_index_140==7 && !frame_timer_142)spell_flash(0,100.0,3);return;
case 655:
    if(sequence_index_13e>0 || (!sequence_index_13e && frame_index_140>=7))texture(0,2);
    if(sequence_index_13e==1){
        if(time_counter_144>=120){next_sequence_block();F(0x100)=0.5f;return;}
        if(time_counter_144%5==0){
            if(!time_counter_144)dispatch_character_wave_handle(50);
            if(S(0x730)<=15){
                float p[3]={0.0f,0.0f,0.0f};
                if(S(0x730)==15){dispatch_character_wave_handle(51);p[2]=1.0f;}
                spawn_offset(855,0,130.0,p,3);++S(0x730);
            }
        }
    }
    if(sequence_index_13e>1){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=udonge_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && frame_index_140==7 && !frame_timer_142)spell_flash(0,100.0,5);return;
