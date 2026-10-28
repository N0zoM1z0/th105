case 605:
    texture(5,2);
    switch(sequence_index_13e){
    case 0:
        if(entry(0)){set_counter_48a(40);event(23);effect(115,static_cast<float>(20*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+50.0),B(0x104),1);secondary_cycle();sequence_window(0,4,60);}
        if(frame_index_140>5 && frame_index_140<16){F(0x108)=0.0f;F(0x10c)=0.0f;F(0x11c)=static_cast<float>(3.0-F(0x73c));F(0x120)=F(0x11c);F(0x73c)=static_cast<float>(F(0x73c)*0.75);}
        if(frame_index_140==3 && !frame_timer_142){B(0x184)=1;I(0x180)=0;}break;
    case 1:
        F(0xf4)=0.0f;if(above_stage_margin()){zero_motion();select_sequence(5);return;}F(0xf0)=suika_surface(this);
        if(!S(0x7a6)){select_sequence(14);dispatch_character_wave_handle(54);return;}
        if(I(0x6b8)>0){
            if(button_active(0x6f4,0x6bc,0x6dc)||button_active(0x6f8,0x6c0,0x6e0)||button_active(0x6fc,0x6c4,0x6e4)){select_sequence(15);return;}
        }else{
            if(button_active(0x6f4,0x6bc,0x6dc)){select_sequence(7);return;}
            if(button_active(0x6f8,0x6c0,0x6e0)){select_sequence(8);return;}
            if(button_active(0x6fc,0x6c4,0x6e4)){select_sequence(9);return;}
        }
        if(I(0x6b4)>0){B(0x104)=1;F(0xf4)=4.0f;select_sequence(2);return;}
        if(I(0x6b4)<0){B(0x104)=255;F(0xf4)=4.0f;select_sequence(2);return;}
        if(I(0x6b8)<0){F(0xf4)=0.0f;F(0xf8)=0.0f;F(0x73c)=0.0f;if(I(0x6b4)*facing()>0)F(0x73c)=1.0f;if(I(0x6b4)*facing()<0)F(0x73c)=-1.0f;select_sequence(3);return;}break;
    case 2:
        F(0xf4)=0.0f;if(above_stage_margin()){F(0xf8)=0.0f;select_sequence(5);return;}F(0xf0)=suika_surface(this);
        if(!S(0x7a6)){select_sequence(14);dispatch_character_wave_handle(54);return;}
        if(frame_index_140==6 && !frame_timer_142){I(0x180)=0;B(0x184)=1;}
        if(button_active(0x6f4,0x6bc,0x6dc)){select_sequence(7);B(0x184)=1;I(0x180)=0;return;}
        if(button_active(0x6f8,0x6c0,0x6e0)){select_sequence(8);B(0x184)=1;I(0x180)=0;return;}
        if(button_active(0x6fc,0x6c4,0x6e4)){select_sequence(9);B(0x184)=1;I(0x180)=0;return;}
        if(!I(0x6b4)){F(0xf4)=0.0f;select_sequence(1);return;}
        if(I(0x6b4)>0){B(0x104)=1;F(0xf4)=4.0f;}if(I(0x6b4)<0){B(0x104)=255;F(0xf4)=4.0f;}
        if(I(0x6b8)<0){F(0x73c)=0.0f;F(0xf4)=0.0f;F(0xf8)=0.0f;if(I(0x6b4))F(0x73c)=1.0f;if(I(0x6b4)>0)B(0x104)=1;if(I(0x6b4)<0)B(0x104)=255;select_sequence(3);return;}break;
    case 4:case 5:
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);select_sequence(6);dispatch_character_wave_handle(56);layout(4.0f);float p[3];giant_ring855(p,8.0f,45.0,30.0f,0);return;}
        if(button_active(0x6f4,0x6bc,0x6dc)){select_sequence(10);B(0x184)=1;I(0x180)=0;return;}
        if(button_active(0x6f8,0x6c0,0x6e0)){select_sequence(12);B(0x184)=1;I(0x180)=0;F(0xf8)=5.0f;F(0x100)=0.45f;return;}
        if(button_active(0x6fc,0x6c4,0x6e4)){select_sequence(16);B(0x184)=1;I(0x180)=0;return;}break;
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
    case 10:case 16:case 17:
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);select_sequence(11);return;}break;
    case 12:
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=suika_surface(this);B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(58);layout(10.0f);select_sequence(13);float p[3];giant_ring855(p,8.0f,45.0,30.0f,0);}break;
    case 14:
        if(!frame_index_140){F(0x11c)=static_cast<float>(F(0x11c)-static_cast<double>(0.03f));if(F(0x11c)<0.333f){F(0x11c)=0.333f;F(0x120)=0.333f;next_sequence_frame();return;}F(0x120)=F(0x11c);}break;
    }
    if(advance()){select_sequence(1);return;}
    if(entry(1)){F(0x11c)=1.0f;F(0x120)=1.0f;}
    if(entry(4)){F(0xf8)=10.0f;F(0x100)=0.3f;F(0xf4)=static_cast<float>(F(0x73c)*5.0);float p[3];giant_ring855(p,8.0f,45.0,30.0f,0);}
    if(entry(7)||entry(8)||entry(9)){select_sequence(1);return;}
    if(entry(10)||entry(12)||entry(14)){select_sequence(1);return;}
    if(entry(15)){set_action_and_finalize(0);F(0x11c)=1.0f;F(0x120)=1.0f;}
    if(entry(16)){select_sequence(1);return;}
    switch(sequence_index_13e){
    case 0:
        if(frame_index_140>5)S(0x7a6)=600;
        if(frame_index_140==6 && !frame_timer_142){float p[3]={0.0f,0.0f,0.0f};spawn_offset(855,0,0.0,p,3,255);giant_ring855(p,8.0f,45.0,30.0f,40);dispatch_character_wave_handle(53);}
        if(frame_index_140==16 && !frame_timer_142){F(0x11c)=1.0f;F(0x120)=1.0f;return;}break;
    case 1:if(frame_index_140==3 && !frame_timer_142){B(0x184)=1;I(0x180)=0;}break;
    case 2:
        if(frame_index_140==3 && !frame_timer_142){dispatch_character_wave_handle(56);layout(2.0f);float p[3];giant_ring855(p,6.0f,60.0,20.0f,70);}
        if(frame_index_140==7 && !frame_timer_142){dispatch_character_wave_handle(56);layout(2.0f);float p[3];giant_ring855(p,6.0f,60.0,20.0f,70);return;}break;
    case 3:if(frame_index_140==4 && !frame_timer_142){I(0x180)=0;B(0x184)=1;}break;
    case 7:
        if(frame_index_140==10 && !frame_timer_142){B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(57);layout(10.0f);float p[3];giant_ring855(p,8.0f,45.0,30.0f,420);}break;
    case 8:
        if(frame_index_140==6 && !frame_timer_142){B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(58);layout(10.0f);float p[3];giant_ring855(p,8.0f,45.0,30.0f,310);}break;
    case 9:
        if(frame_index_140==7 && !frame_timer_142){B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(57);layout(10.0f);float p[4];giant_ring855(p,8.0f,45.0,30.0f,240);p[0]=-65.0f;p[1]=20.0f;p[2]=5.0f;p[3]=180.0f;spawn_offset(855,250,460.0,p,4);}break;
    case 10:if(frame_index_140==4 && !frame_timer_142){B(0x184)=1;I(0x180)=0;dispatch_character_wave_handle(57);}break;
    case 15:
        if(frame_index_140==7 && !frame_timer_142){dispatch_character_wave_handle(58);layout(10.0f);float p[3]={0.0f,7.0f,3.0f};spawn_offset(855,210,0.0,p,3);}break;
    case 16:
        if(frame_index_140==3 && !frame_timer_142){B(0x184)=1;I(0x180)=0;F(0xf8)=12.0f;F(0x100)=0.3f;F(0xf4)=static_cast<float>(F(0xf4)+4.0);if(F(0xf4)>5.0f)F(0xf4)=5.0f;dispatch_character_wave_handle(57);}break;
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
