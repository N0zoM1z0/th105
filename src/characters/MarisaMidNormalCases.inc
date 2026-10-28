case 300:
    landing();if(directional(0))return;
    if(B(0x47e))decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==4){event(27);B(0x47e)=0;}return;
case 301:
    landing();if(directional(0))return;
    if(B(0x47e))decelerate(0.5,true);if(frame_index_140>4)decelerate(1.5,false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==3)F(0xf4)=30.0f;if(!frame_timer_142 && frame_index_140==4){F(0xf4)=10.0f;event(27);B(0x47e)=0;}}
    if(frame_index_140>3)decelerate(0.5,false);return;
case 302:
    if(sequence_index_13e==0 || sequence_index_13e==1 || sequence_index_13e==4)landing();
    if(frame_index_140<2 && !I(0x6bc))B(0x750)=0;
    if(!sequence_index_13e){if(F(0xf4)>0.0f)F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(entry(2)){dispatch_character_wave_handle(17);F(0xf4)=15.5f;F(0xf8)=6.5f;F(0x100)=0.55f;}
    if(entry(3)){dispatch_character_wave_handle(17);F(0xf4)=18.5f;F(0xf8)=7.5f;F(0x100)=0.55f;}
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e==1){
        if(!B(0x750) && time_counter_144<2){next_sequence_block();return;}
        if(time_counter_144>12){select_sequence(3);return;}
        if(time_counter_144==2)effect(62,F(0xec),static_cast<float>(F(0xf0)+68.0),B(0x104),1);
    }
    if(sequence_index_13e==3 || sequence_index_13e==2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){dispatch_character_wave_handle(18);select_sequence(4);F(0xf0)=marisa_surface(this);F(0xf8)=0.0f;F(0xf4)=5.0f;return;}}
    if(sequence_index_13e==4)decelerate(0.5,false);return;
case 303:
    landing();if(directional(0))return;if(C(0x47e)>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);if(!frame_timer_142 && frame_index_140==3)event(27);return;
case 304:
    landing();if(directional(1))return;if(F(0xf4)>0.0f)decelerate(2.0,false);
    if(!I(0x6bc))B(0x750)=0;if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){
        if(B(0x750)==1){next_sequence_block();effect(62,static_cast<float>(75*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+98.0),B(0x104),1);return;}
        F(0xf4)=15.0f;event(28);
    }
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==1){F(0xf4)=25.0f;event(28);}if(!frame_timer_142 && frame_index_140==4)F(0xf4)=0.0f;}return;
case 305:
    landing();if(directional(1))return;if(frame_index_140>4)decelerate(1.0,false);
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==4)event(28);return;
case 306:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=marisa_surface(this);zero_motion();return;}
    if(sequence_index_13e==1 && time_counter_144>12)next_sequence_block();
    if(advance())set_action_and_finalize(9);if(!sequence_index_13e && frame_index_140==1 && !frame_timer_142)event(27);return;
case 307:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=marisa_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)==1){next_sequence_block();return;}
        if(frame_index_140==5){dispatch_character_wave_handle(1);F(0xf4)=-8.0f;F(0xf8)=7.0f;F(0x100)=0.5f;float p[3]={0.0f,0.0f,1.0f};spawn_offset(848,67,110.0,p,3);}
    }
    if(sequence_index_13e==1){
        if(!frame_index_140){
            if(!B(0x750) && time_counter_144<5){select_sequence(0);frame_index_140=3;return;}
            if(time_counter_144==5)effect(62,static_cast<float>(F(0xec)-static_cast<double>(70*facing())),static_cast<float>(F(0xf0)+180.0),B(0x104),1);
        }
        if(!frame_timer_142 && frame_index_140==3){
            dispatch_character_wave_handle(1);F(0xf4)=-8.0f;F(0xf8)=7.0f;F(0x100)=0.5f;
            //4A7092/4A709F write only slots0/1; native count is3. No invented slot2 value.
            float p[3];p[0]=0.0f;p[1]=20.0f;spawn_offset(804,67,110.0,p,3);
        }
    }return;
case 308:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=marisa_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)==1){next_sequence_block();return;}
        if(frame_index_140==5){dispatch_character_wave_handle(1);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;float p[3]={60.0f,1.0f,1.0f};spawn_offset(848,30,30.0,p,3);}
    }
    if(sequence_index_13e==1){
        if(!frame_index_140){
            if(!B(0x750) && time_counter_144<5){select_sequence(0);frame_index_140=3;return;}
            if(time_counter_144==5)effect(62,static_cast<float>(F(0xec)-static_cast<double>(70*facing())),static_cast<float>(F(0xf0)+180.0),B(0x104),1);
        }
        if(!frame_timer_142 && frame_index_140==3){
            dispatch_character_wave_handle(1);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;
            //4A7363/4A7370 write only slots0/1; native count is3. No invented slot2 value.
            float p[3];p[0]=60.0f;p[1]=20.0f;spawn_offset(804,30,30.0,p,3);
        }
    }return;
case 309:
    F(0xf8)-=F(0x100);F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.3f));if(F(0xf4)<2.0f)F(0xf4)=2.0f;
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=marisa_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){event(29);F(0xf4)=10.0f;F(0xf8)=15.0f;F(0x100)=0.85f;}return;
case 310:
    //4A74D4 TEST AH,5/JP rejects unordered values: clamp only ordered FX<0.
    if(sequence_index_13e==2){decelerate(1.0,false);landing();}
    else{F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);F(0xf0)=marisa_surface(this);F(0xf8)=0.0f;F(0x100)=0.0f;I(0x180)=1;}}
    if(advance()){if(I(0x6b8)>0)set_action_and_finalize(2);else set_action_and_finalize(3);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7)event(29);return;
case 320:
    landing();if(directional(0))return;if(frame_index_140>1)decelerate(2.0,false);
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==2){event(28);B(0x47e)=0;}return;
case 321:
    landing();if(directional(0))return;if(frame_index_140>3)decelerate(0.5,false);
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==3){event(28);F(0xf4)=7.5f;B(0x47e)=0;}return;
case 322:
    landing();if(directional(1))return;if(frame_index_140>5)decelerate(3.0,false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==4){F(0xf4)=15.0f;float p[3]={0.0f,0.0f,0.0f};spawn(848,F(0xec),F(0xf0),B(0x104),1,p,3);}if(!frame_timer_142 && frame_index_140==5){event(29);B(0x47e)=0;}}return;
