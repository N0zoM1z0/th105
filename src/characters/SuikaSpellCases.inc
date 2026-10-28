case 600:
    if(!sequence_index_13e || sequence_index_13e==5)landing();texture(5,2);
    if(sequence_index_13e==2){F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.4f));if(F(0xf8)<1.0f)F(0xf8)=1.0f;++S(0x730);if(S(0x730)>69){next_sequence_block();return;}}
    if(sequence_index_13e==3 || sequence_index_13e==4){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(5);F(0xf0)=suika_surface(this);zero_motion();return;}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){spell_flash(0,100.0,2);float p[3]={0.0f,0.0f,0.0f};spawn_offset(850,0,100.0,p,3);dispatch_character_wave_handle(50);F(0xf8)=10.0f;}
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2){F(0xf8)=6.0f;F(0xf4)=-8.0f;F(0x100)=0.5f;}return;
case 601:
    if(sequence_index_13e<=2)landing();texture(5,2);
    if(sequence_index_13e==2){
        if(I(0x180)==1){
            if(F(0xec)>750.0f && C(0x104)==1)F(0xec)=750.0f;
            if(F(0xec)<550.0f && C(0x104)==-1)F(0xec)=550.0f;
            next_sequence_block();peer()->set_action_and_finalize(102);
            peer()->at<float>(0xec)=static_cast<float>(510*facing()+F(0xec));peer()->at<float>(0xf0)=F(0xf0);peer()->zero_motion();return;
        }
        if(landing()){peer()->at<float>(0x18c)=0.0f;peer()->at<float>(0x190)=0.0f;peer()->set_action_and_finalize(53);}
    }
    if(advance())set_action_and_finalize(0);if(entry(3))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(50,160.0,2);
    if(sequence_index_13e==3 && !frame_timer_142){
        if(frame_index_140==2){layout(5.0f);peer()->at<float>(0xec)=static_cast<float>(470*facing()+F(0xec));float p[3]={0.0f,0.0f,0.0f};spawn_offset(851,0,0.0,p,3);dispatch_character_wave_handle(55);}
        if(!frame_timer_142 && frame_index_140==3)peer()->at<float>(0xec)=static_cast<float>(450*facing()+F(0xec));
        if(!frame_timer_142 && frame_index_140==4)peer()->at<float>(0xec)=static_cast<float>(400*facing()+F(0xec));
        if(!frame_timer_142 && frame_index_140==5)peer()->at<float>(0xec)=static_cast<float>(330*facing()+F(0xec));
        if(!frame_timer_142 && frame_index_140==6){peer()->consume_steps(1);
            if(peer()->at<short>(0x174)<=0){peer()->at<float>(0x18c)=-5.0f;peer()->at<float>(0x190)=12.0f;peer()->set_action_and_finalize(77);peer()->at<signed char>(0x104)=-C(0x104);return;}
            peer()->set_action_and_finalize(53);peer()->at<unsigned char>(0x104)=B(0x104);
        }
    }return;
case 602:
    if(frame_index_140==19)landing();texture(5,2);if(entry(0))spell_flash(20,50.0,2);
    if(frame_index_140>5 && frame_index_140<18){F(0x108)=0.0f;F(0x10c)=0.0f;F(0x11c)=static_cast<float>(2.0-F(0x73c));F(0x120)=F(0x11c);F(0x73c)=static_cast<float>(F(0x73c)*0.75);}
    if(frame_index_140==18){F(0x11c)=static_cast<float>(F(0x11c)-static_cast<double>(0.1f));if(F(0x11c)<1.0f)F(0x11c)=1.0f;F(0x120)=F(0x11c);}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==6){
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(852,0,0.0,p,3,255);float n=0.0f;
        do{p[0]=static_cast<float>((n*45.0-20.0)+static_cast<float>(suika_random(40)));p[1]=30.0f;p[2]=1.0f;S(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(811,40,0.0,p,3,B(0x730));n=static_cast<float>(n+1.0);}while(n<8.0f);
        dispatch_character_wave_handle(53);
    }
    if(!frame_timer_142 && frame_index_140==18)dispatch_character_wave_handle(54);
    if(!frame_timer_142 && frame_index_140==19){F(0x11c)=1.0f;F(0x120)=1.0f;}return;
case 603:
    if(!sequence_index_13e || sequence_index_13e==7)landing();texture(5,2);
    if(sequence_index_13e==1 || sequence_index_13e==2){
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(7);F(0xf0)=suika_surface(this);F(0xf8)=0.0f;F(0x100)=0.0f;return;}
        if(sequence_index_13e==2 && (I(0x180)==1 || I(0x180)==7)){zero_motion();next_sequence_block();peer()->zero_motion();peer()->set_action_and_finalize(107);sync_grab_peer();return;}
    }
    if(sequence_index_13e==3){F(0xf8)-=F(0x100);if(F(0xf8)<1.0f)F(0xf8)=1.0f;shared_first(1,F(0xec));shared_second(1,F(0xf0));sync_grab_peer();}
    if(sequence_index_13e==4){shared_first(1,F(0xec));shared_second(1,F(0xf0));if(S(0x730)>119){next_sequence_block();return;}++S(0x730);peer()->at<unsigned char>(0x104)=B(0x104);}
    if(sequence_index_13e==5 && frame_index_140>3){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(7);F(0xf0)=suika_surface(this);zero_motion();return;}}
    if(sequence_index_13e==6){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=suika_surface(this);zero_motion();return;}}
    if(sequence_index_13e==7)decelerate(0.75,false);
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(0,100.0,5);
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==2){F(0xf8)=12.5f;F(0x100)=0.5f;}
    if(sequence_index_13e==4){switch(frame_index_140){
        case 0:pose_grab_peer(-135.0f,44,128.0);break;
        case 1:pose_grab_peer(-60.0f,50,85.0);break;
        case 2:pose_grab_peer(-10.0f,20,60.0);break;
        case 3:pose_grab_peer(45.0f,-28,50.0);break;
        case 4:pose_grab_peer(90.0f,-55,100.0);break;
        case 5:pose_grab_peer(135.0f,-50,140.0);break;
        case 6:pose_grab_peer(180.0f,-5,150.0);break;
    }}
    if(sequence_index_13e==5){
        if(!frame_timer_142){
            if(frame_index_140==2){shared_first(0,F(0xec));shared_second(0,F(0xf0));peer()->at<signed char>(0x104)=-C(0x104);peer()->at<float>(0x18c)=36.0f;peer()->at<float>(0x190)=-18.0f;peer()->set_action_and_finalize(88);F(0xf8)=6.0f;F(0xf4)=-6.0f;F(0x100)=0.75f;dispatch_character_wave_handle(51);}
            if(!frame_timer_142 && frame_index_140==4)F(0x100)=0.5f;
        }
        if(!frame_index_140)pose_grab_peer(180.0f,21,140.0);
        else if(frame_index_140==1){pose_grab_peer(120.0f,85,85.0);peer()->at<signed char>(0x104)=-C(0x104);}
    }
    if(entry(1)){F(0xf4)=10.0f;F(0xf8)=10.0f;F(0x100)=0.6f;}
    if(entry(4)){dispatch_character_wave_handle(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(853,20,50.0,p,3);}return;
case 604:
    if(sequence_index_13e<=2)landing();texture(5,2);
    if(sequence_index_13e==2){
        if(I(0x180)==1){
            if(F(0xec)>750.0f && C(0x104)==1)F(0xec)=750.0f;if(F(0xec)<550.0f && C(0x104)==-1)F(0xec)=550.0f;
            next_sequence_block();peer()->at<float>(0xec)=static_cast<float>(510*facing()+F(0xec));peer()->at<float>(0xf0)=F(0xf0);peer()->zero_motion();peer()->set_action_and_finalize(102);return;
        }
        if(landing()){peer()->at<float>(0x18c)=0.0f;peer()->at<float>(0x190)=0.0f;peer()->set_action_and_finalize(53);}
    }
    if(advance())set_action_and_finalize(0);if(entry(3))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(50,160.0,4);
    if(sequence_index_13e==3){
        if(!frame_timer_142 && frame_index_140==2){layout(5.0f);peer()->at<float>(0xec)=static_cast<float>(470*facing()+F(0xec));float p[3]={0.0f,0.0f,0.0f};spawn_offset(854,0,0.0,p,3);dispatch_character_wave_handle(55);}
        if(frame_index_140==2 && time_counter_144%4==0){float p[3]={0.0f,0.0f,1.0f};spawn(854,peer()->at<float>(0xec),static_cast<float>(peer()->at<float>(0xf0)+100.0),B(0x104),1,p,3);}
        if(!frame_timer_142 && frame_index_140==3)peer()->at<float>(0xec)=static_cast<float>(450*facing()+F(0xec));
        if(!frame_timer_142 && frame_index_140==4)peer()->at<float>(0xec)=static_cast<float>(400*facing()+F(0xec));
        if(!frame_timer_142 && frame_index_140==5)peer()->at<float>(0xec)=static_cast<float>(330*facing()+F(0xec));
        if(!frame_timer_142 && frame_index_140==6){S(0x7a4)=600;
            if(peer()->at<short>(0x174)<=0){peer()->at<float>(0x18c)=-5.0f;peer()->at<float>(0x190)=12.0f;peer()->set_action_and_finalize(77);peer()->at<signed char>(0x104)=-C(0x104);return;}
            peer()->set_action_and_finalize(53);peer()->at<unsigned char>(0x104)=B(0x104);
        }
    }return;
case 606:
    texture(5,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==2)spell_flash(-20,135.0,1);
        if(!frame_timer_142 && frame_index_140==7){
            float p[3]={0.0f,0.0f,0.0f};spawn_offset(856,140,70.0,p,3);dispatch_character_wave_handle(19);
            p[0]=0.0f;p[1]=2.0f;p[2]=1.0f;spawn_offset(856,140,70.0,p,3);p[2]=3.0f;float n=0.0f;
            do{p[0]=static_cast<float>(n*45.0-20.0);p[1]=30.0f;S(0x730)=(p[0]<90.0f || p[0]>270.0f)?-1:1;spawn_offset(856,140,70.0,p,3,B(0x730));n=static_cast<float>(n+1.0);}while(n<8.0f);
        }
    }return;
case 607:
    landing();texture(5,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3)spell_flash(-50,130.0,4);
        if(!frame_timer_142 && frame_index_140==7){
            layout(8.0f);float p[3]={-82.0f,30.0f,0.0f};spawn_offset(857,100,0.0,p,3);effect(127,F(0xec),F(0xf0),B(0x104),-1);dispatch_character_wave_handle(59);
            p[2]=1.0f;float n=0.0f;
            do{p[0]=static_cast<float>(n*36.0+static_cast<float>(suika_random(20)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);S(0x730)=(p[0]<0.0f || p[0]>180.0f)?-1:1;spawn_offset(811,100,0.0,p,3,B(0x730));n=static_cast<float>(n+1.0);}while(n<10.0f);
        }
    }return;
case 650:
    texture(5,2);if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(600);select_sequence(1);spell_flash(0,100.0,2);float p[3]={0.0f,0.0f,0.0f};spawn_offset(850,0,100.0,p,3);dispatch_character_wave_handle(50);F(0xf8)=10.0f;}return;
