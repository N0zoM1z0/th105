case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){event(55);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);effect(141,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1);effect(142,F(0xec),F(0xf0),B(0x104),-1);}return;
case 696:
    landing();if(frame_index_140>5)decelerate(3.0,false);if(advance())set_action_and_finalize(0);
    if(!frame_timer_142){if(frame_index_140==4){F(0xf4)=15.0f;float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);}if(!frame_timer_142 && frame_index_140==5){event(29);B(0x47e)=0;}}return;
case 707:
    landing();if(F(0xf4)>12.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<12.0f)F(0xf4)=12.0f;}
    if(advance()){set_action_and_finalize(700);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=15.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);if(time_counter_144>30){next_sequence_block();return;}}
    if(sequence_index_13e==2)decelerate(0.5,false);return;
case 708:
    if(!sequence_index_13e || sequence_index_13e==2)landing();
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!marisa_on_surface(this)){
        if(time_counter_144%5==0)dash_dust(true);
        double velocity=F(0xf8)-0.5;F(0xf8)=static_cast<float>(velocity);double predicted=velocity+F(0xf0);
        if(marisa_surface(this)>=predicted && F(0xf8)<0.0f){F(0xf8)=0.0f;F(0xf0)=marisa_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(700);return;}
    if(entry(1)){F(0xf4)=-14.0f;F(0xf8)=4.0f;dash_effects(true,80.0,false);}return;
case 710:
    landing();if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5)aimed900(94,102.0);
    if(sequence_index_13e==1 && time_counter_144>60)next_sequence_block();return;
case 711:
    if(!sequence_index_13e)landing();else{F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=marisa_surface(this);set_action_and_finalize(709);return;}}
    if(advance())set_action_and_finalize(700);
    if(entry(1)){F(0xf8)=14.0f;F(0xf4)=static_cast<float>(static_cast<double>(marisa_random(10))-5.0);F(0x100)=0.3f;}
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==7){aimed900(72,88.0);F(0xf4)=-10.0f;F(0xf8)=5.0f;F(0x100)=0.3f;}
    if(sequence_index_13e==2 && time_counter_144>20)next_sequence_block();return;
case 720:
    if(!sequence_index_13e && frame_index_140>2)F(0xf8)-=F(0x100);
    if(sequence_index_13e==1){F(0xf8)=static_cast<float>(F(0xf8)*static_cast<double>(0.9f));F(0xf4)=static_cast<float>(static_cast<double>(0.9f)*F(0xf4));if(time_counter_144>71){select_sequence(4);F(0xf4)=0.0f;F(0xf8)=0.0f;return;}}
    if(entry(2)){
        if(F(0xec)>=640.0f)F(0x74c)=static_cast<float>(580.0-static_cast<double>(marisa_random(360)));else F(0x74c)=static_cast<float>(static_cast<double>(marisa_random(360))+700.0);
        F(0x748)=static_cast<float>(static_cast<double>(marisa_random(260))+60.0);B(0x104)=F(0xec)<=F(0x74c)?1:255;
    }
    if(sequence_index_13e==3){
        S(0x736)=0;S(0x738)=0;F(0xf4)=static_cast<float>(facing()*(F(0x74c)-F(0xec))*static_cast<double>(0.05f));F(0xf8)=static_cast<float>((F(0x748)-F(0xf0))*static_cast<double>(0.05f));
        double dy=marisa_square(F(0x748)-F(0xf0));if(marisa_square(F(0x74c)-F(0xec))+dy<=900.0){next_sequence_block();return;}
    }
    if(sequence_index_13e==4){S(0x736)=0;S(0x738)=0;}
    if(sequence_index_13e==5 && time_counter_144>19){S(0x738)=1;if(time_counter_144%5==0)S(0x736)=static_cast<short>(static_cast<short>(marisa_random(6))+1);}
    if(sequence_index_13e==6 && time_counter_144>19)S(0x738)=1;if(sequence_index_13e==7 && time_counter_144>59)S(0x738)=1;
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=3.0f;F(0xf8)=14.0f;F(0x100)=0.3f;}
    if(entry(1)){float p[3];switch(g_match_identifier){case 0:orbit901(p,120.0,3.0f);break;case 1:orbit901(p,90.0,4.0f);break;case 2:orbit901(p,72.0,5.0f);break;case 3:orbit901(p,60.0,6.0f);break;}F(0x73c)=0.0f;F(0x740)=0.0f;F(0x744)=3.0f;S(0x730)=0;S(0x732)=0;}return;
case 730:
    landing();if(sequence_index_13e==1 && time_counter_144>29){next_sequence_block();return;}if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){float p[3]={0.0f,0.0f,11.0f};spawn_offset(920,100,105.0,p,3);dispatch_character_wave_handle(10);++S(0x732);}return;
case 731:wind_action();return;
case 732:
    landing();if(sequence_index_13e==1 && time_counter_144>29){next_sequence_block();return;}if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){float p[3]={-35.0f,0.0f,11.0f};spawn_offset(920,90,130.0,p,3);dispatch_character_wave_handle(10);++S(0x732);}return;
case 733:wind_action();return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5){B(0x655)=1;finalize(-1);texture(5,-1);copy_health();S(0x76c)=0;S(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);}return;
case 795:
    if(!sequence_index_13e){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.3f));if(static_cast<unsigned char>(crossed())){select_sequence(1);F(0xf0)=marisa_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(700);return;
case 797:ending_slide(0,480.0f);return;
case 798:ending_slide(700,800.0f);return;
