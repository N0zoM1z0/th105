// Private Suika root recovery; incoming EBP=0, EBX=2 from598990.
case 0:
    landing();if(F(0xf4)==0.0f)B(0x47e)=0;idle_motion();advance();return;
case 1:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:
    landing();idle_motion();advance();return;
case 3:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:landing();F(0xf4)=5.5f;advance();return;
case 5:landing();F(0xf4)=-5.5f;advance();return;
case 6:normal_jump(0.0f);return;
case 7:normal_jump(8.0f);return;
case 8:normal_jump(-8.0f);return;
case 9:
    if(F(0x100)==0.0f)F(0x100)=0.6f;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=suika_surface(this);zero_motion();return;}
    advance();return;
case 10:
    landing();zero_motion();if(advance()){if(I(0x6b8))set_action_and_finalize(2);else set_action_and_finalize(0);}return;
case 197:
    landing();
    if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
    if(entry(1))F(0xf4)=11.0f;
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){if(sequence_index_13e!=2)return;zero_motion();}
    if(sequence_index_13e==2 && frame_index_140==5 && !frame_timer_142)ground_face();return;
case 198:
    landing();
    if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
    if(entry(1))F(0xf4)=-11.0f;
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){if(sequence_index_13e!=2)return;zero_motion();}
    if(sequence_index_13e==2 && frame_index_140==5 && !frame_timer_142)ground_face();return;
case 199:
    landing();if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
    if(!frame_timer_142 && frame_index_140==11)ground_face();return;
case 200:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1){
        if(time_counter_144%5==0)dash_dust(false);
        if(I(0x6b8)<0){if(I(0x6b4)*facing()>0)set_action_and_finalize(212);else set_action_and_finalize(211);return;}
        ++S(0x730);if(I(0x6b4)*facing()<=0 || S(0x730)>60){set_action_and_finalize(204);return;}
    }
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){F(0xf4)=10.0f;dash_effects(false,80.0,true);}return;
case 201:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(true);++S(0x730);if((I(0x6b4)*facing()>=0 && S(0x730)>9) || S(0x730)>60){set_action_and_finalize(205);return;}}
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){F(0xf4)=-10.0f;dash_effects(true,80.0,true);}return;
case 202:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    if(sequence_index_13e==1 && time_counter_144>15){next_sequence_block();flip();return;}
    advance();if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){S(0x730)=0;F(0xf4)=11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);}
    if(entry(2))flip();return;
case 203:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<2 && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e==1 && time_counter_144>15){next_sequence_block();flip();return;}
    advance();if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}
    if(entry(3))flip();return;
case 204:
    landing();decelerate(0.5,true);if(advance()){set_action_and_finalize(0);B(0x47e)=0;}return;
case 205:
    landing();F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    if(advance()){set_action_and_finalize(0);B(0x47e)=0;}return;
case 208:high_jump(0.0f,21.0f,0.75f);return;
case 209:high_jump(10.0f,16.0f,0.7f);return;
case 210:case 222:high_jump(-10.0f,16.0f,0.7f);return;
case 211:high_jump(3.0f,19.0f,0.75f);return;
case 212:case 221:high_jump(10.0f,16.0f,0.7f);return;
