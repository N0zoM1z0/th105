case 215:
    landing();
    if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220:high_jump(0.0f,22.5f,0.85f);return;
case 209:case 221:high_jump(10.0f,18.0f,0.85f);return;
case 210:case 222:high_jump(-10.0f,18.0f,0.85f);return;
case 223:
    landing();B(0x47e)=1;advance();
    if(!time_counter_144 && !frame_timer_142 && !frame_index_140){if(sequence_index_13e!=1)return;if(!S(0x730)){F(0xf4)=7.5f;dash_effects(false,80.0,true);}}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);++S(0x730);if((I(0x6b4)*facing()<=0 && S(0x730)>15) || S(0x730)>45){set_action_and_finalize(204);return;}}return;
case 224:
    if(!sequence_index_13e || sequence_index_13e==3)landing();
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!marisa_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0x100)=0.0f;F(0xf0)=marisa_surface(this);select_sequence(3);return;}}
    if(advance()){set_action_and_finalize(0);F(0xf4)=0.0f;F(0x100)=0.0f;return;}
    if(entry(1) && !S(0x730)){S(0x730)=1;F(0xf4)=-14.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,80.0,false);}return;
case 225:
    if(sequence_index_13e>0)F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=marisa_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e>1 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(entry(1)){F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}return;
case 226:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=marisa_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e==1 && time_counter_144%5==0)dash_dust(false);
    if(advance())set_action_and_finalize(9);
    if(entry(1)){S(0x730)=0;F(0xf4)=11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);}
    if(entry(2))flip();return;
