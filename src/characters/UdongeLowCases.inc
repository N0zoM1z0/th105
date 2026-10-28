case 0:landing();if(F(0xf4)==0.0f)B(0x47e)=0;idle_motion();advance();return;
case 1:landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:landing();idle_motion();advance();return;
case 3:landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:landing();F(0xf4)=4.0f;advance();return;
case 5:landing();F(0xf4)=-4.0f;advance();return;
case 6:normal_jump(0.0f);return;
case 7:normal_jump(5.0f);return;
case 8:normal_jump(-5.0f);return;
case 9:case 11:
    if(F(0x100)==0.0f)F(0x100)=0.6f;F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=udonge_surface(this);zero_motion();return;}
    advance();return;
case 10:
    landing();zero_motion();if(advance()){if(!I(0x6b8)){set_action_and_finalize(0);return;}set_action_and_finalize(2);}return;
case 197:recovery_jump(12.5f);return;
case 198:recovery_jump(-12.5f);return;
case 199:
    landing();if(recover_advance())return;
    if(!sequence_index_13e && frame_index_140==11 && !frame_timer_142)face_without_velocity();return;
case 200:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1){
        if(time_counter_144%5==0)dash_dust(false);
        if(I(0x6b8)<0){if(I(0x6b4)*facing()<=0){set_action_and_finalize(211);return;}set_action_and_finalize(212);return;}
        ++S(0x730);if((I(0x6b4)*facing()<=0 && S(0x730)>5) || S(0x730)>45){set_action_and_finalize(204);return;}
    }
    if(entry(1)){F(0xf4)=9.0f;dash_effects(false,80.0,true);}return;
case 201:
    if((!sequence_index_13e && frame_index_140<2)||sequence_index_13e==3)landing();
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!udonge_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0x100)=0.0f;F(0xf0)=udonge_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(!sequence_index_13e && frame_index_140==2 && !frame_timer_142){F(0xf4)=-12.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,80.0,false);}return;
case 202:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){S(0x730)=0;F(0xf4)=9.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);}
    if(entry(2))flip();return;
case 203:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);
    advance();if(entry(1)){F(0xf4)=-9.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}
    if(entry(2))flip();return;
case 204:
    landing();F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    if(advance()){set_action_and_finalize(0);B(0x47e)=0;}return;
case 208:high_jump(0.0f,20.0f,0.75f);return;
case 209:case 221:high_jump(8.0f,17.5f,0.75f);return;
case 210:case 222:high_jump(-8.0f,17.5f,0.75f);return;
case 211:high_jump(2.0f,20.0f,0.75f);return;
case 212:high_jump(8.5f,15.5f,0.65f);return;
