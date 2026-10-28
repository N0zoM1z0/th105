case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){event(55);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(141,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1);effect(142,F(0xec),F(0xf0),B(0x104),-1);
    }return;
case 696:
    landing();decelerate(0.5,true);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6){event(29);B(0x47e)=0;}return;
case 707:
    if(F(0xf4)>12.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<12.0f)F(0xf4)=12.0f;}
    if(advance()){set_action_and_finalize(700);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3){F(0xf4)=15.0f;dash_effects(false,80.0,true);}
    if(sequence_index_13e==1){if(time_counter_144%5==0)dash_dust(false);if(time_counter_144>30){next_sequence_block();return;}}
    if(sequence_index_13e==2)decelerate(0.5,false);return;
case 708:
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!suika_on_surface(this)){
        if(time_counter_144%5==0)dash_dust(true);
        F(0xf8)=static_cast<float>(F(0xf8)-0.5);double predicted=static_cast<double>(F(0xf8))+F(0xf0);
        if(suika_surface(this)>=predicted && F(0xf8)<0.0f){F(0xf8)=0.0f;F(0xf0)=suika_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(700);return;}
    if(entry(1)){F(0xf4)=-14.0f;F(0xf8)=4.0f;dash_effects(true,80.0,false);}return;
case 710:
    if(advance()){set_action_and_finalize(700);return;}
    if(sequence_index_13e==1){if(time_counter_144%10==0)layout(4.0f);switch(g_match_identifier){
        case 0:if(time_counter_144>119){next_sequence_block();return;}break;
        case 1:if(time_counter_144>179){next_sequence_block();return;}break;
        case 2:case 3:if(time_counter_144>239){next_sequence_block();return;}break;
    }}
    if(entry(1)){dispatch_character_wave_handle(15);float p[3]={0.0f,0.0f,0.0f};spawn_offset(900,0,100.0,p,3,255);}return;
case 711:
    if(advance()){set_action_and_finalize(700);return;}
    if(sequence_index_13e==1){if(time_counter_144%10==0)layout(4.0f);switch(g_match_identifier){
        case 0:if(time_counter_144>119){next_sequence_block();return;}break;
        case 1:if(time_counter_144>179){next_sequence_block();return;}break;
        case 2:case 3:if(time_counter_144>239){next_sequence_block();return;}break;
    }}
    if(entry(1)){dispatch_character_wave_handle(25);float p[3]={0.0f,0.0f,0.0f};spawn_offset(901,0,100.0,p,3,255);}return;
case 720:
    landing();if(advance())set_action_and_finalize(700);if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7){
        layout(10.0f);float p[3];switch(g_match_identifier){
        case 0:p[0]=41.0f;p[1]=8.0f;p[2]=9.0f;spawn_offset(910,100,0.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);break;
        case 1:p[0]=81.0f;p[1]=8.0f;p[2]=9.0f;spawn_offset(910,100,0.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);break;
        case 2:p[0]=121.0f;p[1]=8.0f;p[2]=9.0f;spawn_offset(910,100,0.0,p,3);spawn(910,static_cast<float>(100*facing()+F(0xec)),F(0xf0),static_cast<unsigned char>(-B(0x104)),1,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);break;
        case 3:p[0]=200.0f;p[1]=8.0f;p[2]=9.0f;spawn_offset(910,100,0.0,p,3);spawn(910,static_cast<float>(100*facing()+F(0xec)),F(0xf0),static_cast<unsigned char>(-B(0x104)),1,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);break;
        }dispatch_character_wave_handle(59);
    }return;
case 730:
    switch(sequence_index_13e){
    case 0:
        if(frame_index_140>5 && frame_index_140<16){F(0x108)=0.0f;F(0x10c)=0.0f;F(0x11c)=static_cast<float>(3.0-F(0x73c));F(0x120)=F(0x11c);F(0x73c)=static_cast<float>(F(0x73c)*0.75);}break;
    case 1:
        F(0xf4)=0.0f;if(above_stage_margin()){zero_motion();select_sequence(5);return;}F(0xf0)=suika_surface(this);
        if(button_active(0x6f4,0x6bc,0x6dc)){select_sequence(7);return;}
        if(button_active(0x6f8,0x6c0,0x6e0)){select_sequence(8);return;}
        if(button_active(0x6fc,0x6c4,0x6e4)){select_sequence(9);return;}
        if(S(0x76c)==3){flip();F(0xf4)=4.0f;select_sequence(2);return;}
        if(I(0x6b8)<0){F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x73c)=0.0f;if(I(0x6b4)*facing()>0)F(0x73c)=1.0f;if(I(0x6b4)*facing()<0)F(0x73c)=-1.0f;select_sequence(3);return;}break;
    case 2:
        switch(g_match_identifier){case 0:F(0xf4)=3.0f;break;case 1:F(0xf4)=4.0f;break;case 2:F(0xf4)=4.5f;break;case 3:F(0xf4)=5.0f;break;}
        if(classify_fighter_x_boundary()==1 && C(0x104)==-1)B(0x104)=1;
        if(classify_fighter_x_boundary()==-1 && C(0x104)==1)B(0x104)=255;break;
    case 4:case 5:
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);select_sequence(6);dispatch_character_wave_handle(58);layout(10.0f);I(0x180)=0;B(0x184)=1;float p[3];giant_ring920(920,p,8.0f,45.0,30.0f,0);return;}break;
    case 6:
        if(above_stage_margin()){zero_motion();select_sequence(5);return;}break;
case 7:
        if(above_stage_margin()){zero_motion();select_sequence(5);return;}break;
case 8:
        if(above_stage_margin()){zero_motion();select_sequence(5);return;}break;
case 9:
        if(above_stage_margin()){zero_motion();select_sequence(5);return;}break;
case 11:
        if(above_stage_margin()){zero_motion();select_sequence(5);return;}break;
case 13:
        if(above_stage_margin()){zero_motion();select_sequence(5);return;}break;
    case 10:
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);select_sequence(11);return;}break;
    case 12:
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(58);layout(10.0f);select_sequence(13);float p[3];giant_ring920(920,p,8.0f,45.0,30.0f,0);}break;
    case 14:
        if(!frame_index_140){F(0x11c)=static_cast<float>(F(0x11c)-static_cast<double>(0.03f));if(F(0x11c)<0.333f){F(0x11c)=0.333f;F(0x120)=0.333f;next_sequence_frame();return;}F(0x120)=F(0x11c);}break;
    }
    if(advance()){set_action_and_finalize(700);F(0x11c)=1.0f;F(0x120)=1.0f;}
    if(entry(1)){F(0x11c)=1.0f;F(0x120)=1.0f;}
    if(entry(4)){
        F(0xf8)=15.0f;F(0x100)=0.5f;F(0xf4)=static_cast<float>(facing()*(peer()->at<float>(0xec)-F(0xec))/60.0);
        if(F(0xf4)<0.0f)F(0xf4)=0.0f;
        switch(g_match_identifier){case 0:if(F(0xf4)>=6.0f)F(0xf4)=6.0f;break;case 1:if(F(0xf4)>=8.0f)F(0xf4)=8.0f;break;case 2:if(F(0xf4)>=10.0f)F(0xf4)=10.0f;break;case 3:if(F(0xf4)>=12.0f)F(0xf4)=12.0f;break;}
        float p[3];giant_ring920(920,p,8.0f,45.0,30.0f,0);
    }
    if(entry(7)||entry(8)||entry(9)){select_sequence(1);return;}
    if(entry(10)||entry(12)||entry(14)){select_sequence(1);return;}
    switch(sequence_index_13e){
    case 0:
        if(!frame_timer_142){
            if(frame_index_140==6){float p[3]={0.0f,0.0f,0.0f};spawn_offset(920,0,0.0,p,3,255);giant_ring920(920,p,8.0f,45.0,30.0f,40);dispatch_character_wave_handle(53);}
            if(!frame_timer_142 && frame_index_140==16){F(0x11c)=1.0f;F(0x120)=1.0f;return;}
        }break;
    case 2:
        if(!frame_timer_142){
            if(frame_index_140==2){I(0x180)=0;B(0x184)=1;}
            if(!frame_timer_142 && frame_index_140==3){dispatch_character_wave_handle(56);layout(2.0f);float p[3];giant_ring920(920,p,6.0f,60.0,20.0f,70);}
        }
        if(!frame_timer_142){
            if(frame_index_140==6){I(0x180)=0;B(0x184)=1;}
            if(!frame_timer_142 && frame_index_140==7){dispatch_character_wave_handle(56);layout(2.0f);float p[3];giant_ring920(920,p,6.0f,60.0,20.0f,70);return;}
        }break;
    case 7:
        if(!frame_timer_142 && frame_index_140==10){
            B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(57);layout(10.0f);float p[4];giant_ring920(920,p,8.0f,45.0,30.0f,420);
            if(g_match_identifier==1){p[0]=0.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);return;}
            if(g_match_identifier==2){
                p[0]=0.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);int n=10;
                do{p[0]=static_cast<float>(15.0-static_cast<float>(suika_random(30)));p[1]=static_cast<float>(static_cast<float>(suika_random(60))*static_cast<double>(0.1f)+6.0);p[2]=4.0f;p[3]=0.0f;spawn_offset(921,420,200.0,p,4);--n;}while(n);return;
            }
            if(g_match_identifier==3){
                p[0]=0.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);int n=20;
                do{p[0]=static_cast<float>(35.0-static_cast<float>(suika_random(70)));p[1]=static_cast<float>(static_cast<float>(suika_random(60))*static_cast<double>(0.1f)+6.0);p[2]=4.0f;p[3]=0.0f;spawn_offset(921,420,200.0,p,4);--n;}while(n);return;
            }
        }break;
    case 8:
        if(!frame_timer_142 && frame_index_140==6){B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(58);layout(10.0f);float p[3];giant_ring920(855,p,8.0f,45.0,30.0f,310);return;}break;
    case 9:
        if(!frame_timer_142 && frame_index_140==7){
            B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(57);layout(10.0f);float p[4];giant_ring920(855,p,8.0f,45.0,30.0f,240);
            if(g_match_identifier==1){p[0]=-65.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);return;}
            if(g_match_identifier==2){
                p[0]=-65.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);int n=10;
                do{p[0]=static_cast<float>(static_cast<float>(suika_random(30))-80.0);p[1]=static_cast<float>(static_cast<float>(suika_random(60))*static_cast<double>(0.1f)+6.0);p[2]=4.0f;p[3]=0.0f;spawn_offset(921,420,200.0,p,4);--n;}while(n);return;
            }
            if(g_match_identifier==3){
                p[0]=-65.0f;p[1]=20.0f;p[2]=0.0f;p[3]=180.0f;spawn_offset(921,420,200.0,p,4);int n=20;
                do{p[0]=static_cast<float>(static_cast<float>(suika_random(70))-100.0);p[1]=static_cast<float>(static_cast<float>(suika_random(60))*static_cast<double>(0.1f)+6.0);p[2]=4.0f;p[3]=0.0f;spawn_offset(921,420,200.0,p,4);--n;}while(n);return;
            }
        }break;
    case 10:if(!frame_timer_142 && frame_index_140==4){B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(57);return;}break;
    }return;
case 740:
    if(sequence_index_13e>=2 && sequence_index_13e<5){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(5);zero_motion();F(0xf0)=suika_surface(this);return;}}
    if(sequence_index_13e==1){
        F(0x4c0)=0.2f;if(time_counter_144%6==0)orbit_particle930();
        if(F(0x73c)>0.0f){F(0xf8)=F(0x73c);F(0x73c)=static_cast<float>(F(0x73c)*static_cast<double>(0.95f));if(F(0x73c)<=static_cast<double>(0.1f)){F(0x73c)=0.0f;F(0xf8)=0.0f;}}
        if(F(0x73c)==0.0f){++S(0x730);if(S(0x730)>9){F(0x73c)=-1.0f;B(0x184)=1;float dx=static_cast<float>((peer()->at<float>(0xec)-F(0xec))*facing());F(0x744)=-suika_atan(peer()->at<float>(0xf0)-F(0xf0),dx);S(0x730)=0;}}
        if(F(0x73c)==-1.0f){
            ++S(0x730);
            if(S(0x730)>600){B(0x184)=0;F(0x740)=static_cast<float>(F(0x740)-static_cast<double>(0.2f));F(0x748)=static_cast<float>(F(0x748)+static_cast<double>(0.05f));if(F(0x740)<0.0f)F(0x740)=0.0f;
                if(S(0x730)>689){burst999();B(0x113)=255;F(0xf8)=15.0f;F(0x100)=0.2f;next_sequence_block();return;}
            }else{
                if(I(0x180)==6){B(0x184)=1;I(0x180)=0;}
                if(I(0x180)){++S(0x734);if(S(0x734)>4){S(0x734)=0;B(0x184)=1;I(0x180)=0;}}
                float dx=static_cast<float>((peer()->at<float>(0xec)-F(0xec))*facing());float desired=-suika_atan(peer()->at<float>(0xf0)-F(0xf0),dx);float delta=desired-F(0x744);
                if(suika_cosine(delta)>0.0)F(0x740)=static_cast<float>(F(0x740)+0.25);
                else{F(0x740)=static_cast<float>(F(0x740)-static_cast<double>(0.05f));if(F(0x740)<0.0f)F(0x740)=0.0f;}
                // No native initialized fallback is established outside difficulty0..3.
                float turn;int period;
                switch(g_match_identifier){
                case 0:turn=0.8f;period=10;if(F(0x740)>=6.0f)F(0x740)=6.0f;break;
                case 1:turn=1.0f;period=7;if(F(0x740)>=7.0)F(0x740)=7.0f;break;
                case 2:turn=1.25f;period=5;if(F(0x740)>=8.0f)F(0x740)=8.0f;break;
                case 3:turn=1.5f;period=4;if(F(0x740)>=10.0f)F(0x740)=10.0f;break;
                }
                float wrapped=static_cast<float>(static_cast<int>(delta)%360);if(wrapped>180.0f)wrapped=static_cast<float>(wrapped-360.0);if(wrapped<-180.0f)wrapped=static_cast<float>(wrapped+360.0);
                if(!(suika_absolute(wrapped)<=turn)){if(wrapped<0.0f)F(0x744)-=turn;else if(wrapped>0.0f)F(0x744)+=turn;}
                else F(0x744)=desired;
                if(time_counter_144%period==0){dispatch_character_wave_handle(60);shot_particle930();}
            }
            update_oriented_velocity();F(0xf8)+=F(0x748);
        }
    }
    // Both native gravity/crossing passes are retained, with different call order.
    if(sequence_index_13e>1 && sequence_index_13e<5){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(5);F(0xf0)=suika_surface(this);return;}}
    if(advance())set_action_and_finalize(700);if(entry(1))F(0x73c)=25.0f;
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3){burst999();dispatch_character_wave_handle(19);}
        if(frame_index_140>1){if(time_counter_144%2==0)mist817();if(frame_index_140==3){if(B(0x113)>14)B(0x113)-=15;else B(0x113)=0;}}
    }return;
case 750:
    if(sequence_index_13e==1){F(0xf8)-=F(0x100);if(F(0xf8)<=0.0f){F(0xf8)=0.0f;F(0x100)=0.0f;set_action_and_finalize(751);return;}}
    if(advance())set_action_and_finalize(700);if(entry(1)){F(0xf4)=0.0f;F(0xf8)=15.0f;F(0x100)=0.5f;}return;
case 751:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2){float p[3];switch(g_match_identifier){
        case 0:p[0]=0.0f;p[1]=0.0f;p[2]=7.0f;spawn_offset(940,-10,250.0,p,3);p[2]=3.0f;spawn_offset(940,-10,250.0,p,3);p[2]=18.0f;spawn_offset(940,-10,250.0,p,3,255);break;
        case 1:p[0]=0.0f;p[1]=0.0f;p[2]=7.0f;spawn_offset(940,-10,250.0,p,3);p[2]=3.0f;spawn_offset(940,-10,250.0,p,3);p[2]=18.0f;spawn_offset(940,-10,250.0,p,3,255);break;
        case 2:p[0]=0.0f;p[1]=0.0f;p[2]=8.0f;spawn_offset(940,-10,250.0,p,3);p[2]=3.0f;spawn_offset(940,-10,250.0,p,3);p[2]=18.0f;spawn_offset(940,-10,250.0,p,3,255);break;
        case 3:p[0]=0.0f;p[1]=0.0f;p[2]=9.0f;spawn_offset(940,-10,250.0,p,3);p[2]=3.0f;spawn_offset(940,-10,250.0,p,3);p[2]=18.0f;spawn_offset(940,-10,250.0,p,3,255);break;
    }}
    if(sequence_index_13e==1){
        layout(2.0f);F(0x73c)=static_cast<float>(F(0x73c)+static_cast<double>(0.1f));switch(g_match_identifier){
        case 0:if(F(0x73c)>=3.0f)F(0x73c)=3.0f;break;
        case 1:if(F(0x73c)>=4.0f)F(0x73c)=4.0f;break;
        case 2:if(F(0x73c)>=5.0f)F(0x73c)=5.0f;break;
        case 3:if(F(0x73c)>=6.0f)F(0x73c)=6.0f;break;
        }
        F(0x6ac)=F(0x73c);
        if((F(0xec)<peer()->at<float>(0xec) && peer()->at<signed char>(0x104)==1) || (peer()->at<float>(0xec)<F(0xec) && peer()->at<signed char>(0x104)==-1))F(0x6ac)=-F(0x73c);
        if(time_counter_144>299){next_sequence_block();return;}
    }
    if(sequence_index_13e==2 && !frame_timer_142){if(frame_index_140==2){flip();release_fragments811();}if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.2f;}
    if(sequence_index_13e==2 || sequence_index_13e==3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);select_sequence(4);return;}}return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4){B(0x655)=1;finalize(-1);texture(2,-1);copy_health();S(0x76c)=0;S(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);}return;
case 795:
    if(!sequence_index_13e){
        if(time_counter_144%4==0)ending_smoke999();
        F(0xf8)=static_cast<float>(-F(0xf0)*static_cast<double>(0.1f));if(F(0xf8)<-12.0f)F(0xf8)=-12.0f;if(F(0xf8)>-2.0f)F(0xf8)=-2.0f;F(0xf8)=-4.0f;
        F(0xec)=suika_sine_int(time_counter_144*3)*F(0x73c)+F(0x740);F(0x73c)=static_cast<float>(F(0x73c)*static_cast<double>(0.9f));
        double y=F(0xf0);if(suika_surface(this)>=y){
            F(0xf0)=suika_surface(this);next_sequence_block();F(0xf8)=0.0f;F(0xec)=F(0x740);float n=0.0f;float p[3];
            do{p[0]=static_cast<float>((n*45.0-20.0)+static_cast<float>(suika_random(40)));p[1]=static_cast<float>(static_cast<float>(suika_random(13))+12.0);p[2]=0.0f;spawn_offset(999,0,100.0,p,3);n=static_cast<float>(n+1.0);}while(n<8.0f);
        }
    }
    if((sequence_index_13e==1 && time_counter_144>=120) || (sequence_index_13e==2 && S(0x734)==1)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(700);return;
case 797:
    if(!sequence_index_13e && time_counter_144>=0){next_sequence_block();return;}
    if(sequence_index_13e==1){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);F(0xf0)=suika_surface(this);zero_motion();ending_fragments811();return;}}
    if((!sequence_index_13e || sequence_index_13e==1) && time_counter_144%5==0)ending_smoke999();
    if(sequence_index_13e==3 && S(0x734)==1){next_sequence_block();return;}if(advance())set_action_and_finalize(0);return;
case 798:
    if(!sequence_index_13e && time_counter_144>=0){next_sequence_block();return;}
    if(sequence_index_13e==1){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){event(30);select_sequence(2);F(0xf0)=suika_surface(this);zero_motion();ending_fragments811();return;}}
    if((!sequence_index_13e || sequence_index_13e==1) && time_counter_144%4==0)ending_smoke999();
    if(sequence_index_13e==3 && S(0x734)==1){next_sequence_block();return;}if(advance())set_action_and_finalize(700);return;
