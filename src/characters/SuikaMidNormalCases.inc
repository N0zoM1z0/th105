case 300:
    landing();if(directional(0))return;decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3)F(0xf4)=4.0f;
    if(!frame_timer_142 && frame_index_140==4){event(28);B(0x47e)=0;}return;
case 301:
    landing();if(directional(0))return;if(!I(0x6bc))B(0x750)=0;decelerate(0.5,true);
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(F(0xec)-43*facing()),static_cast<float>(F(0xf0)+150.0),B(0x104),1);return;}
        if(!frame_timer_142 && frame_index_140==6){event(29);B(0x47e)=0;}
    }
    if(sequence_index_13e==1 && !frame_timer_142){if(frame_index_140==2)F(0xf4)=10.0f;if(!frame_timer_142 && frame_index_140==4){event(29);B(0x47e)=0;}}return;
case 302:
    landing();if(directional(1))return;if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(0);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(F(0xec)-16*facing()),static_cast<float>(F(0xf0)+135.0),B(0x104),1);return;}
        if(!frame_timer_142 && frame_index_140==6){dispatch_character_wave_handle(0);float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==4){dispatch_character_wave_handle(0);float p[3]={0.0f,0.0f,3.0f};spawn_offset(848,0,0.0,p,3);}return;
case 303:
    landing();if(directional(0))return;if(!I(0x6bc))B(0x750)=0;if(C(0x47e)>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3){event(28);F(0xf4)=8.0f;B(0x47e)=0;}
        if(frame_index_140>2)decelerate(static_cast<double>(0.8f),false);
    }
    if(sequence_index_13e==1){
        if(!frame_timer_142 && frame_index_140==2){
            dispatch_character_wave_handle(1);layout(5.0f);float p[3]={0.0f,0.0f,4.0f};spawn_offset(848,175,85.0,p,3);
            p[0]=-10.0f;p[2]=2.0f;spawn_offset(848,175,85.0,p,3);F(0xf4)=9.5f;B(0x47e)=0;
        }
        if(frame_index_140>=2)decelerate(0.5,false);
    }return;
case 304:
    landing();if(directional(1))return;if(!I(0x6bc))B(0x750)=0;if(C(0x47e)>0)decelerate(static_cast<double>(0.6f),true);
    if(advance())set_action_and_finalize(2);if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e){
        if(frame_index_140>5)decelerate(0.5,false);
        if(!frame_timer_142 && frame_index_140==4){
            if(B(0x750)){next_sequence_block();effect(62,static_cast<float>(34*facing()+F(0xec)),static_cast<float>(F(0xf0)+40.0),B(0x104),1);return;}
            F(0xf4)=15.0f;B(0x47e)=0;event(29);
        }
    }
    if(sequence_index_13e==1){if(frame_index_140>2)decelerate(0.5,false);if(!frame_timer_142 && frame_index_140==1){F(0xf4)=22.5f;B(0x47e)=0;event(29);}}return;
case 305:
    landing();if(directional(0))return;if(frame_index_140>16)decelerate(static_cast<double>(0.6f),false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5)event(28);
    if(!frame_timer_142 && frame_index_140==16){event(29);I(0x180)=0;}return;
case 306:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=suika_surface(this);F(0x100)=0.0f;F(0xf8)=0.0f;return;}
    if(advance())set_action_and_finalize(9);if(!frame_timer_142 && frame_index_140==5)event(28);return;
case 307:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=suika_surface(this);F(0x100)=0.0f;F(0xf8)=0.0f;return;}
    if(frame_index_140>2){F(0xf4)=static_cast<float>(F(0xf4)+static_cast<double>(0.2f));if(F(0xf4)>-2.0f)F(0xf4)=-2.0f;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){
        dispatch_character_wave_handle(1);layout(5.0f);float p[3]={0.0f,0.0f,1.0f};spawn_offset(848,154,62.0,p,3);p[0]=10.0f;p[2]=2.0f;spawn_offset(848,154,62.0,p,3);
        F(0xf4)=-12.5f;F(0xf8)=6.0f;F(0x100)=0.5f;
    }return;
case 308:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=suika_surface(this);F(0xf8)=0.0f;F(0x100)=0.0f;return;}
    if(advance())set_action_and_finalize(9);
    if(!time_counter_144){if(frame_timer_142)return;if(!frame_index_140 && sequence_index_13e==1){set_action_and_finalize(9);return;}}
    if(!frame_timer_142 && frame_index_140==6){F(0xf4)=-4.0f;F(0xf8)=7.0f;F(0x100)=0.5f;event(29);}return;
case 309:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=suika_surface(this);F(0x100)=0.0f;F(0xf8)=0.0f;return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==5){if(F(0xf8)<0.0f)F(0xf8)=0.0f;F(0x100)=-0.2f;}
        if(!sequence_index_13e){if(frame_timer_142)return;if(frame_index_140==5 || frame_index_140==7 || frame_index_140==9 || frame_index_140==11){event(27);I(0x180)=0;B(0x184)=1;}}
        if(!frame_timer_142 && frame_index_140==13)F(0x100)=0.5f;
    }return;
case 310:
    if(I(0x180)){++S(0x730);if(S(0x730)>5){I(0x180)=0;S(0x730)=0;}}
    if(sequence_index_13e==1){
        if(!time_counter_144)F(0xf4)=15.0f;if(time_counter_144%8==0)event(27);
        if(I(0x180)){++S(0x730);if(S(0x730)>5){I(0x180)=0;S(0x730)=0;}}
        if(time_counter_144>30){next_sequence_block();F(0xf8)=6.0f;F(0xf4)=static_cast<float>(F(0xf4)*0.5);}
    }
    if(sequence_index_13e==2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0xf0)=suika_surface(this);set_action_and_finalize(9);return;}}
    if(advance())set_action_and_finalize(9);return;
case 320:
    landing();if(directional(0))return;if(frame_index_140>1)decelerate(2.0,false);
    if(advance())set_action_and_finalize(0);if(!frame_timer_142 && frame_index_140==5){event(28);B(0x47e)=0;}return;
case 321:
    landing();if(directional(1))return;if(frame_index_140>3)decelerate(0.5,false);
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){B(0x47e)=0;F(0xf4)=16.5f;}
    if(!frame_timer_142 && frame_index_140==6)F(0xf4)=0.0f;
    if(!frame_timer_142 && frame_index_140==6)event(29);return;
case 322:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(3);F(0xf8)=0.0f;F(0x100)=0.0f;F(0xf0)=suika_surface(this);}}
    if(sequence_index_13e==3)decelerate(static_cast<double>(0.8f),true);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){event(29);F(0xf4)=15.0f;F(0xf8)=6.0f;F(0x100)=0.9f;}return;
case 330:
    if(frame_index_140<7)F(0xf8)=static_cast<float>(F(0xf8)-0.5);else F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=suika_surface(this);F(0x100)=0.0f;F(0xf8)=0.0f;return;}
    if(advance())set_action_and_finalize(9);if(!frame_timer_142 && frame_index_140==4)event(28);return;
case 331:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=suika_surface(this);F(0x100)=0.0f;F(0xf8)=0.0f;return;}
    if(sequence_index_13e==1){
        if(I(0x180) && C(0x184)>0){++S(0x730);if(S(0x730)>5){S(0x730)=0;I(0x180)=0;}}
        if(time_counter_144%6==0)event(28);
        if(time_counter_144>24){next_sequence_block();B(0x184)=1;I(0x180)=0;F(0xf8)=10.0f;F(0xf4)=7.0f;F(0x100)=0.75f;return;}
    }else if(sequence_index_13e==2){if(!frame_timer_142 && frame_index_140==2)event(29);}
    else if(sequence_index_13e==3 && time_counter_144==45){set_action_and_finalize(9);return;}
    if(advance())set_action_and_finalize(9);if(entry(4))F(0x100)=0.5f;return;
