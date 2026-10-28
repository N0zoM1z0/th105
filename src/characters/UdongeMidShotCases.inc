case 400:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance()){set_action_and_finalize(0);return;}
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(80*facing()+F(0xec)),static_cast<float>(F(0xf0)+108.0),B(0x104),1);return;}
        if(frame_index_140==3 || frame_index_140==6 || frame_index_140==9){
            if(frame_index_140==3){counter(200,45);I(0x180)=1;}
            aim_to_peer();if(F(0x744)<-20.0f)F(0x744)=-20.0f;if(F(0x744)>20.0f)F(0x744)=20.0f;
            fan800(76,106.0,true);
        }
    }
    if(sequence_index_13e==1 && !frame_timer_142 && (frame_index_140==1 || frame_index_140==4 || frame_index_140==7 || frame_index_140==10 || frame_index_140==13)){
        if(frame_index_140==1){counter(200,45);I(0x180)=1;}
        aim_to_peer();if(F(0x744)<-20.0f)F(0x744)=-20.0f;if(F(0x744)>20.0f)F(0x744)=20.0f;
        fan800(76,106.0,true);
    }return;
case 401:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance()){set_action_and_finalize(0);return;}
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(72*facing()+F(0xec)),static_cast<float>(F(0xf0)+136.0),B(0x104),1);return;}
        if(frame_index_140==3 || frame_index_140==6 || frame_index_140==9){
            if(frame_index_140==3){counter(200,45);I(0x180)=1;}
            aim_to_peer();if(F(0x744)<-60.0)F(0x744)=-60.0f;if(F(0x744)>-20.0f)F(0x744)=-20.0f;
            fan800(73,138.0,true);
        }
    }
    if(sequence_index_13e==1 && !frame_timer_142 && (frame_index_140==1 || frame_index_140==4 || frame_index_140==7 || frame_index_140==10 || frame_index_140==13)){
        if(frame_index_140==1){counter(200,45);I(0x180)=1;}
        aim_to_peer();if(F(0x744)<-60.0)F(0x744)=-60.0f;if(F(0x744)>-20.0f)F(0x744)=-20.0f;
        fan800(73,138.0,true);
    }return;
case 402:
    landing();if(!I(0x6c0))B(0x750)=0;if(advance())set_action_and_finalize(2);
    if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(70*facing()+F(0xec)),static_cast<float>(F(0xf0)+64.0),B(0x104),1);return;}
        if(frame_index_140==3 || frame_index_140==6 || frame_index_140==9){
            if(frame_index_140==3){counter(200,45);I(0x180)=1;}

            fan800(70,64.0,false);
        }
    }
    if(sequence_index_13e==1 && !frame_timer_142 && (frame_index_140==1 || frame_index_140==4 || frame_index_140==7 || frame_index_140==10 || frame_index_140==13)){
        if(frame_index_140==1){counter(200,45);I(0x180)=1;}

        fan800(70,64.0,false);
    }return;
case 404:
    if(sequence_index_13e==2)landing();if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);B(0x47f)=0;F(0xf0)=udonge_surface(this);zero_motion();return;}}
    if(advance()){set_action_and_finalize(0);return;}
    if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142){
            if(frame_index_140==3 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(66*facing()+F(0xec)),static_cast<float>(F(0xf0)+129.0),B(0x104),1);return;}
            if(frame_index_140==3 || frame_index_140==6 || frame_index_140==9){
                if(frame_index_140==3){counter(200,45);I(0x180)=1;}
                aim_to_peer();if(F(0x744)<-20.0f)F(0x744)=-20.0f;if(F(0x744)>20.0f)F(0x744)=20.0f;fan800(67,130.0,true);
            }
        }
        if(!frame_timer_142 && frame_index_140==12)F(0x100)=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==1 || frame_index_140==4 || frame_index_140==7 || frame_index_140==10 || frame_index_140==13){
            if(frame_index_140==1){counter(200,45);I(0x180)=1;}
            aim_to_peer();if(F(0x744)<-20.0f)F(0x744)=-20.0f;if(F(0x744)>20.0f)F(0x744)=20.0f;fan800(67,130.0,true);
        }
        if(!frame_timer_142 && frame_index_140==15)F(0x100)=0.6f;
    }return;
case 406:
    if(sequence_index_13e==2)landing();if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);B(0x47f)=0;F(0xf0)=udonge_surface(this);zero_motion();return;}}
    if(advance()){set_action_and_finalize(0);return;}
    if(entry(1)){set_action_and_finalize(9);return;}if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142){
            if(frame_index_140==4 && B(0x750)){next_sequence_block();effect(62,static_cast<float>(56*facing()+F(0xec)),static_cast<float>(F(0xf0)+100.0),B(0x104),1);return;}
            if(frame_index_140==4 || frame_index_140==7 || frame_index_140==10){
                if(frame_index_140==4){counter(200,45);I(0x180)=1;}
                aim_to_peer();if(F(0x744)<20.0f)F(0x744)=20.0f;if(F(0x744)>60.0)F(0x744)=60.0f;fan800(56,100.0,true);
            }
        }
        if(!frame_timer_142 && frame_index_140==12)F(0x100)=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142){
        if(frame_index_140==1 || frame_index_140==4 || frame_index_140==7 || frame_index_140==10 || frame_index_140==13){
            if(frame_index_140==1){counter(200,45);I(0x180)=1;}
            aim_to_peer();if(F(0x744)<20.0f)F(0x744)=20.0f;if(F(0x744)>60.0)F(0x744)=60.0f;fan800(56,100.0,true);
        }
        if(!frame_timer_142 && frame_index_140==15)F(0x100)=0.6f;
    }return;
case 408:
    landing();
    if(entry(0)){B(0x47e)=0;B(0x184)=1;F(0xf4)=12.0f;I(0x180)=0;zero_motion();B(0x750)=1;}
    if(!I(0x6bc))B(0x750)=0;
    if(sequence_index_13e==2 && F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1){F(0xf4)=12.0f;float p[3]={0.0f,0.0f,3.0f};spawn_offset(848,0,0.0,p,3);B(0x113)=0;S(0x7a6)=0;}
    if(sequence_index_13e==1){if(!time_counter_144)event(29);if(time_counter_144>12){next_sequence_block();return;}}return;
case 409:
    if(entry(0)){F(0x100)=0.35f;B(0x47e)=0;S(0x730)=0;B(0x184)=1;I(0x180)=0;}
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);zero_motion();F(0xf0)=udonge_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    if(entry(0)){I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;}
    if(!I(0x6c4))B(0x750)=0;
    if(advance() || entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)==1){effect(62,static_cast<float>(F(0xec)-46*facing()),static_cast<float>(F(0xf0)+128.0),B(0x104),1);next_sequence_block();return;}
        if(frame_index_140==4){counter(200,60);aim_short(-10,10);fan801(72,95.0,false);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){counter(200,60);aim_short(-10,10);fan801(72,95.0,true);}return;
case 411:
    if(entry(0)){I(0x180)=1;zero_motion();S(0x730)=0;S(0x732)=0;S(0x736)=0;B(0x750)=1;}
    if(!I(0x6c4))B(0x750)=0;
    if(advance() || entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)==1){effect(62,static_cast<float>(F(0xec)-46*facing()),static_cast<float>(F(0xf0)+128.0),B(0x104),1);next_sequence_block();return;}
        if(frame_index_140==4){counter(200,60);aim_short(-50,-20);fan801(66,128.0,false);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){counter(200,60);aim_short(-50,-20);fan801(66,128.0,true);}return;
case 412:
    if(!sequence_index_13e && frame_index_140==3 && !frame_timer_142){dispatch_character_wave_handle(7);I(0x180)=1;spawn(802,F(0xec),F(0xf0),B(0x104),1,0,0);counter(200,60);phase_counter(50);}
    if(advance())set_action_and_finalize(2);return;
case 414:
    if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();F(0xf0)=udonge_surface(this);return;}}
    if(advance()){set_action_and_finalize(0);return;}
    if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)==1){effect(62,static_cast<float>(F(0xec)-47*facing()),static_cast<float>(F(0xf0)+142.0),B(0x104),1);next_sequence_block();return;}
        if(frame_index_140==4){counter(200,60);aim_short(-10,10);fan801(62,127.0,false,true);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){counter(200,60);aim_short(-10,10);fan801(62,127.0,true,true);}return;
case 415:
    if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();F(0xf0)=udonge_surface(this);return;}}
    if(advance()){set_action_and_finalize(0);return;}
    if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)==1){effect(62,static_cast<float>(F(0xec)-47*facing()),static_cast<float>(F(0xf0)+142.0),B(0x104),1);next_sequence_block();return;}
        if(frame_index_140==4){counter(200,60);aim_short(-10,10);fan801(62,127.0,false,true);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){counter(200,60);aim_short(-10,10);fan801(62,127.0,true,true);}return;
case 416:
    if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e<2){F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){select_sequence(2);zero_motion();F(0xf0)=udonge_surface(this);return;}}
    if(advance()){set_action_and_finalize(0);return;}
    if(entry(1)||entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142){
        if(frame_index_140==3 && B(0x750)==1){next_sequence_block();effect(62,static_cast<float>(F(0xec)-47*facing()),static_cast<float>(F(0xf0)+142.0),B(0x104),1);return;}
        if(frame_index_140==4){counter(200,60);aim_short(20,50);fan801(64,105.0,false,true);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){counter(200,60);aim_short(-10,10);fan801(64,105.0,true,true);}return;
case 418:
    if((sequence_index_13e>0 && sequence_index_13e<5)||(!sequence_index_13e && frame_index_140>0)){
        F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){F(0xf0)=udonge_surface(this);zero_motion();select_sequence(5);return;}
        if(I(0x180) && sequence_index_13e==1){zero_motion();select_sequence(4);return;}
    }
    if(!sequence_index_13e && !frame_index_140){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(sequence_index_13e==1 && time_counter_144>23){next_sequence_block();return;}
    if(sequence_index_13e==4){F(0xf4)=static_cast<float>(F(0xf4)+static_cast<double>(0.2f));if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(entry(5)){select_sequence(3);return;}
    if(!sequence_index_13e){
        if(!frame_timer_142){
            if(frame_index_140==1){F(0xf4)=12.0f;F(0xf8)=6.0f;F(0x100)=0.35f;float p[3]={0.0f,F(0xf4),9.0f};spawn_offset(848,0,0.0,p,3);}
            if(!frame_timer_142 && frame_index_140==8)event(29);
        }
        if(frame_index_140>0 && frame_index_140<4)S(0x7a6)=0;
    }
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==3){F(0x100)=0.5f;F(0xf4)=-10.0f;F(0xf8)=7.0f;}return;
