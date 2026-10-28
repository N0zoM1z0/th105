case 608:
    if(!sequence_index_13e || sequence_index_13e==1)landing();texture(5,2);
    if(sequence_index_13e>2 && sequence_index_13e<12){shared_first(1,F(0xec));shared_second(1,F(0xf0));}
    switch(sequence_index_13e){
    case 0:
        if(I(0x180)==1){zero_motion();select_sequence(2);peer()->zero_motion();moving_grab_pose(0.0f,70.0,0.0);peer()->set_action_and_finalize(100);return;}break;
    case 3:case 4:
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){peer()->at<signed char>(0x104)=-C(0x104);zero_motion();select_sequence(5);layout(10.0f);F(0xf0)=suika_surface(this);moving_grab_pose(0.0f,10.0,120.0);peer()->set_action_and_finalize(109);return;}break;
    case 6:case 7:
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){peer()->at<signed char>(0x104)=-C(0x104);zero_motion();select_sequence(8);layout(10.0f);F(0xf0)=suika_surface(this);moving_grab_pose(0.0f,10.0,120.0);peer()->set_action_and_finalize(109);return;}break;
    case 9:case 10:
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();select_sequence(11);F(0xf0)=suika_surface(this);peer()->set_action_and_finalize(107);moving_grab_pose(180.0f,21.0,140.0);return;}break;
    case 12:case 13:
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=suika_surface(this);set_action_and_finalize(10);zero_motion();return;}break;
    }
    if(advance())set_action_and_finalize(0);
    if(entry(2)){set_action_and_finalize(0);return;}
    if(entry(12)){F(0xf4)=-10.0f;F(0xf8)=12.5f;F(0x100)=0.5f;}
    if(!sequence_index_13e){
        if(!frame_timer_142 && frame_index_140==3)spell_flash(0,100.0,5);
        if(!frame_timer_142 && frame_index_140==7){double y=peer()->at<float>(0xf0);B(0x184)=suika_surface(peer())==y?1:0;}
    }
    if(sequence_index_13e==2){
        if(!frame_index_140){moving_grab_pose(0.0f,70.0,0.0);peer()->set_action_and_finalize(100);}
        else if(frame_index_140==1){moving_grab_pose(0.0f,48.0,120.0);peer()->set_action_and_finalize(107);}
    }
    if(sequence_index_13e==3){
        if(!frame_index_140){moving_grab_pose(0.0f,-25.0,143.0);peer()->set_action_and_finalize(107);}
        else if(frame_index_140==1){moving_grab_pose(0.0f,-35.0,140.0);peer()->set_action_and_finalize(107);}
    }
    if(sequence_index_13e==4 && !frame_index_140)moving_grab_vertical();
    if(sequence_index_13e==5){
        switch(frame_index_140){
        case 0:moving_grab_pose(0.0f,10.0,120.0);peer()->set_action_and_finalize(109);break;
        case 1:moving_grab_pose(-45.0f,55.0,117.0);peer()->set_action_and_finalize(109);break;
        case 2:
            moving_grab_pose(0.0f,83.0,0.0);peer()->at<short>(0x186)=20;peer()->set_action_and_finalize(97);peer()->select_sequence(3);peer()->zero_motion();
            if(!frame_timer_142){forward_hit_quantity(!S(0x4b2)&&I(0x4b8)==1?625:500,980,1,1);grab_impact_effect(3,95);dispatch_character_wave_handle(5);}break;
        case 4:moving_grab_pose(0.0f,60.0,55.0);peer()->set_action_and_finalize(103);break;
        case 5:moving_grab_pose(0.0f,48.0,120.0);peer()->set_action_and_finalize(103);break;
        }
    }
    if(sequence_index_13e==6){
        if(!frame_index_140){moving_grab_pose(0.0f,-25.0,143.0);peer()->set_action_and_finalize(107);}
        else if(frame_index_140==1){moving_grab_pose(0.0f,-35.0,140.0);peer()->set_action_and_finalize(107);}
    }
    if(sequence_index_13e==7 && !frame_index_140)moving_grab_vertical();
    if(sequence_index_13e==8){
        switch(frame_index_140){
        case 0:moving_grab_pose(0.0f,10.0,120.0);peer()->set_action_and_finalize(109);break;
        case 1:moving_grab_pose(-45.0f,55.0,117.0);peer()->set_action_and_finalize(109);break;
        case 2:
            moving_grab_pose(0.0f,83.0,0.0);peer()->at<short>(0x186)=20;peer()->set_action_and_finalize(97);peer()->select_sequence(3);peer()->zero_motion();
            if(!frame_timer_142){
                forward_hit_quantity(!S(0x4b2)&&I(0x4b8)==1?1250:1000,980,1,1);grab_impact_effect(3,95);dispatch_character_wave_handle(5);
                float p[3];p[2]=1.0f;float n=0.0f;
                do{p[0]=static_cast<float>(n*36.0+static_cast<float>(suika_random(20)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+30.0);S(0x730)=(p[0]<0.0f||p[0]>180.0f)?-1:1;spawn_offset(811,95,0.0,p,3,B(0x730));n=static_cast<float>(n+1.0);}while(n<10.0f);
            }break;
        case 4:moving_grab_pose(0.0f,60.0,55.0);peer()->set_action_and_finalize(103);break;
        case 5:moving_grab_pose(0.0f,48.0,120.0);peer()->set_action_and_finalize(103);break;
        }
    }
    if(sequence_index_13e==9){
        peer()->at<unsigned char>(0x104)=B(0x104);shared_first(1,F(0xec));shared_second(1,F(0xf0));
        peer()->at<float>(0xec)=static_cast<float>(facing()*(F(0xf4)+45.0)+F(0xec));peer()->at<float>(0xf0)=static_cast<float>(F(0xf0)+120.0+F(0xf8));peer()->set_action_and_finalize(107);
    }
    if(sequence_index_13e==10){
        switch(frame_index_140){
        case 0:moving_grab_pose(-135.0f,44.0,128.0);break;
        case 1:moving_grab_pose(-60.0f,50.0,85.0);break;
        case 2:moving_grab_pose(-10.0f,20.0,60.0);break;
        case 3:moving_grab_pose(45.0f,-28.0,50.0);break;
        case 4:moving_grab_pose(90.0f,-55.0,100.0);break;
        case 5:moving_grab_pose(135.0f,-50.0,140.0);break;
        case 6:moving_grab_pose(180.0f,-5.0,150.0);break;
        }
    }
    if(sequence_index_13e==11){
        if(!frame_timer_142 && frame_index_140==2){
            peer()->at<signed char>(0x104)=-C(0x104);peer()->at<float>(0xf4)=0.0f;peer()->at<float>(0xf8)=0.0f;peer()->set_action_and_finalize(89);
            dispatch_character_wave_handle(51);layout(20.0f);dispatch_character_wave_handle(12);peer()->at<float>(0xec)=static_cast<float>(60*facing()+F(0xec));peer()->at<float>(0xf0)=suika_surface(peer());
            forward_hit_quantity(!S(0x4b2)&&I(0x4b8)==1?6875:5500,980,1,1);grab_impact_effect(4,37);peer()->at<float>(0x12c)=0.0f;peer()->at<short>(0x186)=44;
            float p[3];p[2]=0.0f;float n=0.0f;
            do{p[0]=static_cast<float>(n*36.0+static_cast<float>(suika_random(20)));p[1]=static_cast<float>(static_cast<float>(suika_random(8))+45.0);S(0x730)=(p[0]<0.0f||p[0]>180.0f)?-1:1;spawn_offset(858,37,0.0,p,3,B(0x730));n=static_cast<float>(n+1.0);}while(n<10.0f);
            p[2]=3.0f;n=0.0f;
            do{p[0]=static_cast<float>(n*(-36.0)-static_cast<float>(suika_random(20)));p[1]=static_cast<float>(static_cast<float>(suika_random(25))+60.0);spawn_offset(858,37,0.0,p,3);n=static_cast<float>(n+1.0);}while(n<5.0f);
            p[2]=1.0f;spawn_offset(858,37,0.0,p,3);p[2]=2.0f;spawn_offset(858,37,0.0,p,3,255);
        }
        if(!frame_index_140){peer()->set_action_and_finalize(107);moving_grab_pose(180.0f,21.0,140.0);}
        else if(frame_index_140==1){peer()->set_action_and_finalize(107);moving_grab_pose(120.0f,85.0,85.0);peer()->at<signed char>(0x104)=-C(0x104);}
    }
    if(entry(3)){F(0xf4)=2.0f;F(0xf8)=11.0f;F(0x100)=0.75f;}
    if(entry(6)){F(0xf4)=2.0f;F(0xf8)=25.0f;F(0x100)=1.25f;}
    if(entry(9)){F(0xf4)=2.0f;F(0xf8)=60.0f;F(0x100)=1.75f;}
    if(entry(12)){shared_first(0,F(0xec));shared_second(0,F(0xf0));peer()->at<short>(0x186)=0;return;}
    return;
