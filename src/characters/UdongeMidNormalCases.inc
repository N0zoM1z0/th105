case 300:
    landing();if(directional(0))return;
    if(B(0x47e)){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==4){event(27);B(0x47e)=0;}return;
case 301:
    landing();if(directional(0))return;
    if(B(0x47e)||frame_index_140>3){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==4){float p[3]={0.0f,0.0f,1.0f};spawn_offset(849,0,0.0,p,3);}
    if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(0);
    if(!frame_timer_142 && frame_index_140==4){F(0xf4)=7.5f;B(0x47e)=0;}return;
case 302:
    landing();if(directional(1))return;
    if(!I(0x6bc))B(0x750)=0;
    if(entry(1))F(0xf4)=17.5f;
    if(!sequence_index_13e){if(F(0xf4)>0.0f)F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){
        if(B(0x750)==1){select_sequence(3);effect(62,static_cast<float>(F(0xec)-86*facing()),static_cast<float>(F(0xf0)+108.0),B(0x104),1);B(0x184)=1;return;}
        event(29);float p[3]={0.0f,0.0f,4.0f};spawn_offset(848,0,0.0,p,3);S(0x7a6)=0;B(0x113)=0;F(0xf4)=-250.0f;
    }
    if(entry(3))set_action_and_finalize(0);
    if(entry(4)){F(0xf4)=17.5f;event(29);}
    if(sequence_index_13e==1){
        F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.05f));if(S(0x7a6)<251)S(0x7a6)=static_cast<short>(S(0x7a6)+5);else S(0x7a6)=255;
        if(time_counter_144>17 || I(0x180)){S(0x7a6)=255;next_sequence_block();return;}
    }
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(sequence_index_13e==4){F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.1f));if(time_counter_144>23 || I(0x180)){next_sequence_block();return;}}
    if(sequence_index_13e==5){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}return;
case 303:
    landing();if(directional(0))return;
    if(entry(0)){if(!B(0x47e))zero_motion();B(0x184)=1;I(0x180)=0;}
    if(C(0x47e)>0){F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.6f));if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}}
    if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==2)event(27);return;
case 304:
    landing();if(directional(1))return;
    if(entry(0)){B(0x47e)=0;B(0x184)=1;I(0x180)=0;zero_motion();B(0x750)=1;}
    if(entry(3)){F(0xf4)=F(0x73c);B(0x184)=1;}
    if(!I(0x6bc))B(0x750)=0;
    if((!sequence_index_13e || sequence_index_13e==2 || sequence_index_13e==4) && F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=12.5f;event(28);}
    if(sequence_index_13e==1 && time_counter_144>16){
        if(!B(0x750)){next_sequence_block();return;}
        float p[3]={0.0f,F(0xf4),10.0f};spawn_offset(848,0,0.0,p,3);
        S(0x7a6)=0;B(0x113)=0;B(0x184)=0;I(0x180)=0;F(0x73c)=F(0xf4);F(0xf4)=-280.0f;select_sequence(3);
        effect(62,static_cast<float>(F(0xec)-15*facing()),static_cast<float>(F(0xf0)+60.0),B(0x104),1);return;
    }
    if(sequence_index_13e==3 && time_counter_144>32){next_sequence_block();return;}return;
case 305:
    landing();if(directional(1))return;
    if(frame_index_140>5){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){float p[3]={0.0f,0.0f,5.0f};spawn_offset(849,0,0.0,p,3);}
    if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(1);return;
case 306:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=udonge_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(11);if(!frame_timer_142 && frame_index_140==4)event(28);return;
case 307:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=udonge_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);if(entry(1))set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==5){float p[3]={0.0f,0.0f,3.0f};spawn_offset(849,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==6){dispatch_character_wave_handle(1);F(0xf4)=-7.0f;F(0xf8)=6.0f;F(0x100)=0.5f;}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){dispatch_character_wave_handle(1);F(0xf4)=-7.0f;F(0xf8)=6.0f;F(0x100)=0.5f;}return;
case 308:
    ++S(0x730);if(S(0x730)<11)S(0x7a6)=0;
    if(!sequence_index_13e){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(1);F(0xf0)=udonge_surface(this);zero_motion();return;}}
    if(!I(0x6bc))B(0x750)=0;
    if(advance()){set_action_and_finalize(0);return;}
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9)event(28);return;
case 309:
    if(!I(0x6bc))B(0x750)=0;
    if(sequence_index_13e!=1)F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=udonge_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(entry(2))F(0xf8)=static_cast<float>(F(0xf8)*0.25);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){dispatch_character_wave_handle(1);F(0xf4)=4.0f;F(0xf8)=15.0f;F(0x100)=0.5f;float p[3]={0.0f,0.0f,7.0f};spawn_offset(849,0,0.0,p,3);}return;
case 310:
    if(entry(0)){F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x100)=0.5f;S(0x730)=0;B(0x184)=99;I(0x180)=0;}
    if(I(0x180)){++S(0x730);if(S(0x730)>5){I(0x180)=0;S(0x730)=0;}}
    if(sequence_index_13e==1){
        if(!time_counter_144)F(0xf4)=15.0f;
        if(time_counter_144%8==0)event(27);
        // The native repeats this hit-counter update within sequence1.
        if(I(0x180)){++S(0x730);if(S(0x730)>5){I(0x180)=0;S(0x730)=0;}}
        if(time_counter_144>30){next_sequence_block();F(0xf8)=6.0f;F(0xf4)=static_cast<float>(F(0xf4)*0.5);}
    }
    if(sequence_index_13e==2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0x100)=0.0f;F(0xf0)=udonge_surface(this);set_action_and_finalize(9);return;}}
    if(advance())set_action_and_finalize(9);return;
case 320:
    landing();if(directional(0))return;
    if(!frame_timer_142 && !frame_index_140){B(0x47e)=0;B(0x184)=1;I(0x180)=0;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==2){event(27);B(0x47e)=0;}return;
case 321:
    landing();if(directional(0))return;
    if(!frame_timer_142 && !frame_index_140){if(!B(0x47e))zero_motion();B(0x184)=1;I(0x180)=0;}
    if(frame_index_140>4){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){float p[3]={0.0f,0.0f,1.0f};spawn_offset(849,0,0.0,p,3);}
    if(!frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);F(0xf4)=10.0f;B(0x47e)=0;}
    if(!frame_timer_142 && frame_index_140==6)F(0xf4)=0.0f;return;
case 322:
    landing();if(directional(1))return;
    if(!frame_timer_142 && !frame_index_140){if(!B(0x47e))zero_motion();B(0x184)=1;I(0x180)=0;}
    if(frame_index_140>4){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){F(0xf4)=15.0f;float p[3]={0.0f,0.0f,5.0f};spawn_offset(849,0,0.0,p,3);}
    if(!frame_timer_142 && frame_index_140==5){dispatch_character_wave_handle(1);F(0xf4)=5.0f;B(0x47e)=0;}return;
