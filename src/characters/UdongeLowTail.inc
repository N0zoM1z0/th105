case 215:
    landing();
    if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:high_jump(0.0f,20.0f,0.75f);return;
case 223:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);++S(0x730);if((I(0x6b4)*facing()<=0 && S(0x730)>15)||S(0x730)>45){set_action_and_finalize(204);return;}}
    if(entry(1)){F(0xf4)=4.5f;dash_effects(false,80.0,true);}return;
case 224:
    if((!sequence_index_13e && frame_index_140<2)||sequence_index_13e==3)landing();
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!udonge_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0xf0)=udonge_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(!sequence_index_13e && frame_index_140==2 && !frame_timer_142){F(0xf4)=-12.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,80.0,false);}return;
case 225:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);
    advance();if(entry(1)){F(0xf4)=-9.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}
    if(entry(2))flip();return;
case 226:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){S(0x730)=0;F(0xf4)=9.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);}
    if(entry(2))flip();return;
