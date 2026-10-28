// Raw JP1.06a4A3EAA..4A442A; private partial recovery, not a complete unit.
case 0:
    landing();if(F(0xf4)==0.0f)B(0x47e)=0;idle_motion();advance();return;
case 1:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:
    landing();idle_motion();advance();return;
case 3:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:landing();F(0xf4)=6.0f;advance();return;
case 5:landing();F(0xf4)=-5.0f;advance();return;
case 6:normal_jump(0.0f);return;
case 7:normal_jump(5.0f);return;
case 8:normal_jump(-4.0f);return;
case 9:
    if(F(0x100)==0.0f)F(0x100)=0.6f;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=marisa_surface(this);zero_motion();return;}
    advance();return;
case 10:
    landing();zero_motion();if(advance()){if(I(0x6b8))set_action_and_finalize(2);else set_action_and_finalize(0);}return;
case 197:
    if((!sequence_index_13e && frame_index_140<=4) || sequence_index_13e==2)landing();
    if(sequence_index_13e<2)F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){F(0xf0)=marisa_surface(this);zero_motion();select_sequence(2);return;}
    if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
    if(sequence_index_13e==2 && frame_index_140==3 && !frame_timer_142)ground_face();
    if(!sequence_index_13e && frame_index_140==5 && !frame_timer_142){F(0xf8)=6.0f;F(0xf4)=14.5f;F(0x100)=0.5f;}return;
case 198:
    if((!sequence_index_13e && frame_index_140<=3) || sequence_index_13e==2)landing();
    if(sequence_index_13e<2)F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2){F(0xf0)=marisa_surface(this);zero_motion();select_sequence(2);return;}
    if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
    if(sequence_index_13e==2 && frame_index_140==3 && !frame_timer_142)ground_face();
    if(!sequence_index_13e && frame_index_140==4 && !frame_timer_142){F(0xf8)=6.0f;F(0xf4)=-14.5f;F(0x100)=0.5f;}return;
case 199:
    landing();if(advance()){if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}set_action_and_finalize(0);if(I(0x6b8)>0)set_action_and_finalize(1);}
    if(!sequence_index_13e && frame_index_140==12 && !frame_timer_142)ground_face();return;
case 200:
    landing();B(0x47e)=1;
    if(F(0xf4)>12.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<12.0f)F(0xf4)=12.0f;}
    advance();
    if(sequence_index_13e==1){
        if(time_counter_144%5==0)dash_dust(false);
        if(I(0x6b8)<0){if(I(0x6b4)*facing()>0)set_action_and_finalize(212);else set_action_and_finalize(211);return;}
        ++S(0x730);if((I(0x6b4)*facing()<=0 && S(0x730)>5) || S(0x730)>45){set_action_and_finalize(204);return;}
    }
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){F(0xf4)=15.0f;dash_effects(false,80.0,true);}return;
case 201:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!marisa_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0x100)=0.0f;F(0xf0)=marisa_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);zero_motion();return;}
    if(entry(1)){F(0xf4)=-14.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,80.0,false);}return;
case 202:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=marisa_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){S(0x730)=0;F(0xf4)=11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);}
    if(entry(2))flip();return;
case 203:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=marisa_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}
    if(entry(2))flip();return;
case 204:
    landing();F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    if(advance()){set_action_and_finalize(0);B(0x47e)=0;}return;
case 208:high_jump(0.0f,22.5f,0.85f);return;
case 211:high_jump(3.0f,22.5f,0.85f);return;
case 212:high_jump(10.0f,16.0f,0.7f);return;
