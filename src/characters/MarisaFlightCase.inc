// Manual recovery from4A540A..4A5A23 and actual incoming EDI=6 at4A3A42.
// The diagnostic slice has no original standalone ABI; raw code owns these facts.
case 214: {
    if(advance()){set_action_and_finalize(9);return;}
    if(entry(1))event(31);
    if(entry(6)){set_action_and_finalize(9);return;}
    int horizontal=I(0x6b4)*facing();
    if(I(0x6b8)>0){if(horizontal>0)S(0x732)=-45;else if(horizontal<0)S(0x732)=-135;else S(0x732)=-90;}
    else if(I(0x6b8)<0){if(horizontal>0)S(0x732)=45;else if(horizontal<0)S(0x732)=135;else S(0x732)=90;}
    else {if(horizontal>0)S(0x732)=0;else if(horizontal<0)S(0x732)=180;}
    if(sequence_index_13e==5 || sequence_index_13e==6)F(0xf8)-=F(0x100);
    if(sequence_index_13e>0 && sequence_index_13e<5){
        ++S(0x736);
        S(0x734)=static_cast<short>(S(0x732)-static_cast<short>(static_cast<int>(F(0x740))));
        if(S(0x734)>180)S(0x734)=static_cast<short>(S(0x734)-360);
        if(S(0x734)<-180)S(0x734)=static_cast<short>(S(0x734)+360);
        // 4A55C0..4A560C owns separate additions/subtractions per rate.
        if(S(0x734)>0){
            if(!I(0x4b8))F(0x740)=static_cast<float>(F(0x740)+1.5);
            else F(0x740)=static_cast<float>(F(0x740)+0.5);
        }
        if(S(0x734)<0){
            if(!I(0x4b8))F(0x740)=static_cast<float>(F(0x740)-1.5);
            else F(0x740)=static_cast<float>(F(0x740)-0.5);
        }
        F(0xf4)=static_cast<float>(marisa_cosine(F(0x740))*F(0x73c));
        F(0xf8)=static_cast<float>(marisa_sine(F(0x740))*F(0x73c));
        if(F(0xf0)>680.0f && F(0xf8)>0.0f)F(0xf8)=0.0f;
        F(0x73c)=static_cast<float>(F(0x73c)+static_cast<double>(0.3f));if(F(0x73c)>12.0f)F(0x73c)=12.0f;
        counter(I(0x4b8)?10:5,1);
        F(0x12c)=-F(0x740);if(F(0xf4)<0.0f)F(0x12c)=static_cast<float>(180.0-F(0x740));
        if(F(0xf4)<0.0f && sequence_index_13e==1)select_sequence(3);
        if(F(0xf4)>=0.0f && sequence_index_13e==3)select_sequence(1);
        if(F(0xf4)<0.0f && sequence_index_13e==2)select_sequence(4);
        if(F(0xf4)>=0.0f && sequence_index_13e==4)select_sequence(2);
        if(time_counter_144%5==1){
            effect(125,static_cast<float>(marisa_cosine(F(0x740))*100.0*facing()+F(0xec)),
                   static_cast<float>(marisa_sine(F(0x740))*100.0+F(0xf0)+100.0),B(0x104),1);
        }
        // Native repeats this gate at580F and5830 without an intervening write/call.
        if((!I(0x6c8) && S(0x736)>10) || S(0x482)<=0){
            reset_action_scratch();
            if(sequence_index_13e==1 || sequence_index_13e==2){
                if(C(0x104)==1){
                    if(peer()->at<float>(0xec)<F(0xec)){B(0x104)=255;F(0xf4)=-F(0xf4);select_sequence(6);}
                    else select_sequence(5);
                }else{
                    if(F(0xec)<peer()->at<float>(0xec)){C(0x104)=-C(0x104);F(0xf4)=-F(0xf4);select_sequence(6);}
                    else select_sequence(5);
                }
            }
            if(sequence_index_13e==3 || sequence_index_13e==4){
                if(C(0x104)==1){
                    if(peer()->at<float>(0xec)<F(0xec)){B(0x104)=255;F(0xf4)=-F(0xf4);select_sequence(5);return;}
                    select_sequence(6);return;
                }
                if(F(0xec)<peer()->at<float>(0xec)){C(0x104)=-C(0x104);F(0xf4)=-F(0xf4);select_sequence(5);return;}
                select_sequence(6);return;
            }
            return;
        }
    }
    if(static_cast<unsigned char>(crossed())){
        F(0xf0)=marisa_surface(this);F(0x100)=0.0f;F(0xf8)=0.0f;
        if(sequence_index_13e<5){reset_action_scratch();set_action_and_finalize(215);return;}
        set_action_and_finalize(10);zero_motion();return;
    }
    return;
}
