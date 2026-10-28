case 560:
    if(!I(0x6c0))B(0x750)=0;if(!sequence_index_13e)landing();
    F(0xf8)-=F(0x100);if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e==1 || sequence_index_13e==2){if(B(0x113)<246)B(0x113)+=10;else B(0x113)=255;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){B(0x113)=0;dispatch_character_wave_handle(9);I(0x180)=1;F(0xf4)=-4.0f;F(0xf8)=12.5f;F(0x100)=0.45f;counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,0.0f};spawn_offset(825,0,0.0,p,3);}return;
case 561:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e==1 || sequence_index_13e==2){if(B(0x113)<246)B(0x113)+=10;else B(0x113)=255;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){dispatch_character_wave_handle(9);I(0x180)=1;B(0x113)=0;counter(200,120);phase_counter(50);float p[3]={0.0f,0.0f,2.0f};spawn_offset(825,0,0.0,p,3);}return;
case 565:
    if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e==2)landing();
    if(update_beam_radius())return;
    if(advance())set_action_and_finalize(0);
    if(entry(1))begin_beams826(false);
    return;
case 566:
    if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e==2)landing();
    if(update_beam_radius())return;
    if(advance())set_action_and_finalize(0);
    if(entry(1))begin_beams826(true);
    return;
case 567:
    if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e==4)landing();
    F(0xf8)-=F(0x100);if(sequence_index_13e<4 && static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);select_sequence(4);return;}
    if(update_beam_radius())return;
    if(advance())set_action_and_finalize(0);
    if(entry(1))begin_beams826(false);
    if(entry(4)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==6)F(0x100)=0.5f;
    return;
case 568:
    if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e==4)landing();
    F(0xf8)-=F(0x100);if(sequence_index_13e<4 && static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=udonge_surface(this);select_sequence(4);return;}
    if(update_beam_radius())return;
    if(advance())set_action_and_finalize(0);
    if(entry(1))begin_beams826(true);
    if(entry(4)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==6)F(0x100)=0.5f;
    return;
