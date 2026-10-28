case 215:
    landing();
    if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:high_jump(0.0f,21.0f,0.75f);return;
case 223:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);++S(0x730);if((I(0x6b4)*facing()<=0 && S(0x730)>9) || S(0x730)>60){set_action_and_finalize(204);return;}}
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){F(0xf4)=5.0f;dash_effects(false,80.0,true);}return;
case 224:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(true);++S(0x730);if((I(0x6b4)*facing()>=0 && S(0x730)>9) || S(0x730)>60){set_action_and_finalize(205);return;}}
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){F(0xf4)=-10.0f;dash_effects(true,80.0,true);}return;
case 225:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<2 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}
    if(entry(3))flip();return;
case 226:
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){S(0x730)=0;F(0xf4)=11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);}
    if(entry(2))flip();return;
