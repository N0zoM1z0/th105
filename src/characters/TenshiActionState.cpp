#include "characters/TenshiActionState.hpp"
// JP1.06a 63D3E0 complete candidate, not selected or exact.
// Remaining semantic and compiler-ownership limits are in the evidence document.
namespace th105 {
#define B(o) at<unsigned char>(o)
#define C(o) at<signed char>(o)
#define S(o) at<short>(o)
#define U(o) at<unsigned>(o)
#define I(o) at<int>(o)
#define F(o) at<float>(o)
void TenshiActionStateView::dispatch_action_state_vslot28()
{
    float request500[3],request501[3];
    float *paired_request;
    S(0x7a0)=0; S(0x7a2)=95; S(0x830)=0;
    if(S(0x82e)>0) --S(0x82e);
    if(I(0x838)>0) {
        --I(0x838); F(0x4c4)=0.0f;
        F(0x4c0)=static_cast<float>(F(0x4c0)*0.75);
        S(0x48e)=1;
    }
    if((action_id_13c>=50 && action_id_13c<=149) ||
       I(0x834)<=0 || peer()->at<short>(0x174)<=0) S(0x82e)=0;
    if(S(0x174)<=0 || peer()->at<short>(0x174)<=0) I(0x838)=0;
    if(action_id_13c>=600 && action_id_13c<=689 &&
       (action_id_13c!=606 || sequence_index_13e<1)) I(0x838)=0;
    if(S(0x174)>0 || B(0x72c)==2) {
        if(S(0x174)<=0 && action_id_13c>=70 && action_id_13c<=149) {
            if(C(0x55a)>0 && (card()<=15 || card()>=248)) event_owner()->trigger(16);
            B(0x82c)=0;
        }
        if(B(0x72c)==2 && B(0x55a)==1 && S(0x840)==0 && S(0x174)<=0) {
            if(card()>=16 && card()<=19) {
                S(0x840)=1;
                float payload[3]={0.0f,0.0f,0.0f};
                spawn(997,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1,payload,3);
                tenshi_bgm_volume(2000,0);
            }
        }
    }
    if(action_id_13c>149 && action_id_13c<159 && !B(0x751)) {
        B(0x751)=1;
        if(action_id_13c>149 && action_id_13c<154)
            spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),
                  static_cast<float>(F(0xf0)+94.0),B(0x104),1,0,0);
        if(action_id_13c>153 && action_id_13c<158)
            spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),
                  static_cast<float>(F(0xf0)+60.0),B(0x104),1,0,0);
        if(action_id_13c==158)
            spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),
                  static_cast<float>(F(0xf0)+100.0),B(0x104),1,0,0);
    }
    if(S(0x186) || peer()->at<short>(0x48c)) return;
    switch(action_id_13c) {
// Complete unselected JP1.06a candidate; see TENSHI_ACTION_STATE_2026_10_27.md.
case 0:
    landing();
    if(F(0xf4)==0.0f) B(0x47e)=0;
    if(!B(0x47e)) {zero_motion();advance();return;}
    if(F(0xf4)>0.0f) {
        F(0xf4)=static_cast<float>(F(0xf4)-0.5);
        if(F(0xf4)<0.0f) {zero_motion();B(0x47e)=0;}
    }
    if(F(0xf4)<0.0f) {
        F(0xf4)=static_cast<float>(F(0xf4)+0.5);
        if(F(0xf4)>0.0f) {zero_motion();B(0x47e)=0;}
    }
    advance();return;
case 1:
    landing();
    if(B(0x47e)) {
        if(F(0xf4)>0.0f) {
            F(0xf4)=static_cast<float>(F(0xf4)-0.5);
            if(F(0xf4)<0.0f) {zero_motion();B(0x47e)=0;}
        }
        if(F(0xf4)<0.0f) {
            F(0xf4)=static_cast<float>(F(0xf4)+0.5);
            if(F(0xf4)>0.0f) {zero_motion();B(0x47e)=0;}
        }
    } else zero_motion();
    if(advance() && frame_index_140==0) set_action_and_finalize(2);
    return;
case 2:
    landing();
    if(B(0x47e)) {
        if(F(0xf4)>0.0f) {
            F(0xf4)=static_cast<float>(F(0xf4)-0.5);
            if(F(0xf4)<0.0f) {zero_motion();B(0x47e)=0;}
        }
        if(F(0xf4)<0.0f) {
            F(0xf4)=static_cast<float>(F(0xf4)+0.5);
            if(F(0xf4)>0.0f) {zero_motion();B(0x47e)=0;}
        }
    } else zero_motion();
    advance();return;
case 3:
    landing();
    if(B(0x47e)) {
        if(F(0xf4)>0.0f) {
            F(0xf4)=static_cast<float>(F(0xf4)-0.5);
            if(F(0xf4)<0.0f) {zero_motion();B(0x47e)=0;}
        }
        if(F(0xf4)<0.0f) {
            F(0xf4)=static_cast<float>(F(0xf4)+0.5);
            if(F(0xf4)>0.0f) {zero_motion();B(0x47e)=0;}
        }
    } else zero_motion();
    if(advance() && frame_index_140==0) set_action_and_finalize(0);
    return;
case 4: landing();F(0xf4)=4.5f;advance();return;
case 5: landing();F(0xf4)=-4.5f;advance();return;
case 6:
    if(sequence_index_13e==0) {
        landing(); if(sequence_index_13e==0 && !B(0x47e)) zero_motion();
    }
    if(sequence_index_13e>0) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);F(0xf0)=tenshi_surface(this);zero_motion();return;}
    }
    advance();
    if(entry(1)) {F(0xf4)=0.0f;F(0xf8)=16.5f;F(0x100)=0.7f;B(0x47e)=0;}
    return;
case 7:
    if(sequence_index_13e==0) {
        landing(); if(sequence_index_13e==0 && !B(0x47e)) zero_motion();
    }
    if(sequence_index_13e>0) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);F(0xf0)=tenshi_surface(this);zero_motion();return;}
    }
    advance();
    if(entry(1)) {F(0xf4)=6.0f;F(0xf8)=16.5f;F(0x100)=0.7f;B(0x47e)=0;}
    return;
case 8:
    if(sequence_index_13e==0) {
        landing(); if(sequence_index_13e==0 && !B(0x47e)) zero_motion();
    }
    if(sequence_index_13e>0) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);F(0xf0)=tenshi_surface(this);zero_motion();return;}
    }
    advance();
    if(entry(1)) {F(0xf4)=-6.0f;F(0xf8)=16.5f;F(0x100)=0.7f;B(0x47e)=0;}
    return;
case 9:
    if(F(0x100)==0.0f) F(0x100)=0.6f;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);F(0xf0)=tenshi_surface(this);zero_motion();return;}
    advance();return;
case 10:
    landing();zero_motion();
    if(advance()) {if(I(0x6b8))set_action_and_finalize(2);else set_action_and_finalize(0);}
    return;
case 99:
    landing();
    if(sequence_index_13e==3) {
        if(B(0x113)<=3) B(0x113)=0;else B(0x113)-=3;
    }
    if(sequence_index_13e==4 && S(0x840)==2) {
        if(++S(0x730)==300) {
            tenshi_fade_in(0xffffffffu,20);layout(10.0f);dispatch_character_wave_handle(54);
            S(0x730)=0;
            float payload[3]={0.0f,0.0f,0.0f};
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
                payload[2]=n;
                spawn(962,static_cast<float>(n*160.0+80.0),0.0f,1,-1,payload,3);
            }
            next_sequence_block();S(0x730)=0;
        }
        if(S(0x730)>=280) {S(0x732)=3;dispatch_character_wave_handle(56);}
        else if(S(0x730)>=180) {
            if(S(0x730)%10==0) {dispatch_character_wave_handle(18);layout(4.0f);}
            S(0x732)=2;
        } else if(S(0x730)>=60) {
            if(S(0x730)%10==0) {dispatch_character_wave_handle(18);layout(2.0f);}
            S(0x732)=1;
        }
    }
    if(sequence_index_13e==5) {
        if(S(0x730)%10==0) layout(10.0f);
        ++S(0x730);
        float *position=&F(0x7a4);
        for(int i=0;i<8;++i,++position) {
            *position=static_cast<float>(*position+40.0);
            if(*position>=1000.0f) {
                set_action_and_finalize(750);event_owner()->music(6,0);
                peer()->at<float>(0xec)=480.0f;
                peer()->at<float>(0xf0)=tenshi_surface(peer());
                peer()->at<unsigned char>(0x104)=1;
                peer()->zero_motion();peer()->set_action_and_finalize(0);
                F(0xf0)=static_cast<float>(tenshi_surface(this)+150.0);
                B(0x104)=255;F(0xec)=800.0f;zero_motion();return;
            }
        }
    }
    advance();
    if(entry(2)) {
        if(B(0x72c)==2 && B(0x55a)==1 && card()>=16 && card()<=19) select_sequence(4);
        else if(!B(0x4eb)) {
            if(C(0x55a)>0 && B(0x72c)==2 && card()>=248) copy_health();
            set_action_and_finalize(199);B(0x4e9)=0;B(0x4ec)=1;
        }
    }
    return;

case 197:
    if((sequence_index_13e==0 && frame_index_140<=1) || sequence_index_13e==2) landing();
    if(sequence_index_13e<2) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {recover_air_sequence();return;}
    }
    if(advance()) {
        if(B(0x72c)==2) {set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(0);if(I(0x6b8)>0) set_action_and_finalize(1);
    }
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142) ground_face();
    if(sequence_index_13e==0 && frame_index_140==2 && !frame_timer_142) {
        F(0xf8)=6.0f;F(0xf4)=14.5f;F(0x100)=0.5f;
    }
    return;
case 198:
    if((sequence_index_13e==0 && frame_index_140<=1) || sequence_index_13e==2) landing();
    if(sequence_index_13e<2) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {recover_air_sequence();return;}
    }
    if(advance()) {
        if(B(0x72c)==2) {set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(0);if(I(0x6b8)>0) set_action_and_finalize(1);
    }
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142) ground_face();
    if(sequence_index_13e==0 && frame_index_140==2 && !frame_timer_142) {
        F(0xf8)=6.0f;F(0xf4)=-14.5f;F(0x100)=0.5f;
    }
    return;
case 199:
    landing();
    if(advance()) {
        if(B(0x72c)==2) {set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(0);if(I(0x6b8)>0) set_action_and_finalize(1);
    }
    if(sequence_index_13e==0 && frame_index_140==10 && !frame_timer_142) ground_face();
    return;
case 200:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0) dash_dust(false);
        if(I(0x6b8)<0) {
            if(I(0x6b4)*facing()<=0)set_action_and_finalize(211);else set_action_and_finalize(212);return;
        }
        short ticks=++S(0x730);
        if((I(0x6b4)*facing()<=0 && ticks>5) || ticks>45) {
            set_action_and_finalize(204);return;
        }
    }
    if(sequence_index_13e==0 && frame_index_140==4 && !frame_timer_142) {
        F(0xf4)=11.0f;dash_effects(false,80.0,true);
    }
    return;
case 201:
    if(sequence_index_13e==0 || sequence_index_13e==3) landing();
    if(sequence_index_13e==3) {F(0xf4)=static_cast<float>(F(0xf4)+1.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!tenshi_on_surface(this) && time_counter_144%5==0) dash_dust(true);
    if(sequence_index_13e<3) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {F(0xf8)=0.0f;F(0xf0)=tenshi_surface(this);select_sequence(3);return;}
    }
    if(advance()) {set_action_and_finalize(0);F(0xf4)=0.0f;return;}
    if(entry(1)) {F(0xf4)=-12.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,80.0,false);}
    return;
case 202:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())) {zero_motion();F(0xf0)=tenshi_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0) dash_dust(false);
    advance();
    if(sequence_index_13e==0 && !frame_timer_142 && frame_index_140==3) {
        S(0x730)=0;F(0xf4)=11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);
    }
    if(entry(2)) flip();
    return;
case 203:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())) {zero_motion();F(0xf0)=tenshi_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0) dash_dust(true);
    advance();
    if(time_counter_144==0) {
        if(!frame_timer_142 && !frame_index_140 && sequence_index_13e==1) {
            F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);
        }
        if(entry(2)) flip();
    }
    return;
case 204:
    landing();F(0xf4)=static_cast<float>(F(0xf4)-0.5);
    if(F(0xf4)<0.0f) {F(0xf4)=0.0f;B(0x47e)=0;}
    if(advance()) {set_action_and_finalize(0);B(0x47e)=0;} return;
case 208: jump_cycle(0.0f,22.5f,0.85f);return;
case 209: jump_cycle(10.0f,18.0f,0.85f);return;
case 210: jump_cycle(-10.0f,18.0f,0.85f);return;
case 211: jump_cycle(3.0f,22.5f,0.85f);return;
case 212: jump_cycle(10.0f,16.0f,0.7f);return;
case 214: {
    if(advance()) {set_action_and_finalize(9);return;}
    if(time_counter_144==0) {
        if(!frame_timer_142 && !frame_index_140 && sequence_index_13e==1) event(31);
        if(entry(6)) {set_action_and_finalize(9);return;}
    }
    int vertical=I(0x6b8),horizontal=I(0x6b4)*facing();
    if(vertical>0) S(0x732)=horizontal>0?-45:(horizontal<0?-135:-90);
    else if(vertical<0) S(0x732)=horizontal>0?45:(horizontal<0?135:90);
    else {if(horizontal>0)S(0x732)=0;else if(horizontal<0)S(0x732)=180;}
    if(sequence_index_13e==5 || sequence_index_13e==6) F(0xf8)-=F(0x100);
    bool retain=true;
    if(sequence_index_13e>0 && sequence_index_13e<5) {
        ++S(0x736);
        S(0x734)=static_cast<short>(S(0x732)-static_cast<int>(F(0x740)));
        if(S(0x734)>180)S(0x734)-=360;
        if(S(0x734)<-180)S(0x734)+=360;
        if(S(0x734)>0)F(0x740)=static_cast<float>(F(0x740)+(I(0x4b8)?0.5:1.5));
        if(S(0x734)<0)F(0x740)=static_cast<float>(F(0x740)-(I(0x4b8)?0.5:1.5));
        F(0xf4)=static_cast<float>(tenshi_cosine(F(0x740))*F(0x73c));
        F(0xf8)=static_cast<float>(tenshi_sine(F(0x740))*F(0x73c));
        if(F(0xf0)>680.0f && F(0xf8)>0.0f)F(0xf8)=0.0f;
        F(0x73c)=static_cast<float>(F(0x73c)+static_cast<double>(0.3f));
        if(F(0x73c)>12.0f)F(0x73c)=12.0f;
        counter(I(0x4b8)?10:5,1);
        F(0x12c)=-F(0x740);
        if(F(0xf4)<0.0f)F(0x12c)=static_cast<float>(180.0-F(0x740));
        if(F(0xf4)<0.0f && sequence_index_13e==1)select_sequence(3);
        if(0.0f<=F(0xf4) && sequence_index_13e==3)select_sequence(1);
        if(F(0xf4)<0.0f && sequence_index_13e==2)select_sequence(4);
        if(0.0f<=F(0xf4) && sequence_index_13e==4)select_sequence(2);
        if(time_counter_144%5==1) {
            int direction=B(0x104);
            float y=static_cast<float>(tenshi_sine(F(0x740))*100.0+F(0xf0)+100.0);
            float x=static_cast<float>(tenshi_cosine(F(0x740))*100.0*facing()+F(0xec));
            effect(125,x,y,direction,1);
        }
        retain=((I(0x6c8)!=0 || S(0x736)<=10) && S(0x482)>0) ||
               ((I(0x6c8)!=0 || S(0x736)<=10) && S(0x482)>0);
    }
    if(retain) {
        if(static_cast<unsigned char>(crossed())) {
            F(0xf0)=tenshi_surface(this);F(0xf8)=0.0f;
            if(sequence_index_13e>=5) {set_action_and_finalize(10);zero_motion();}
            else {reset_action_scratch();set_action_and_finalize(215);}
        }
        return;
    }
    reset_action_scratch();
    if(sequence_index_13e==1 || sequence_index_13e==2) {
        if(B(0x104)==1) {
            if(peer()->at<float>(0xec)<F(0xec)) {
                B(0x104)=255;F(0xf4)=-F(0xf4);select_sequence(6);
            } else select_sequence(5);
        } else if(peer()->at<float>(0xec)>F(0xec)) {
            B(0x104)=static_cast<unsigned char>(-B(0x104));F(0xf4)=-F(0xf4);select_sequence(6);
        } else select_sequence(5);
    }
    if(sequence_index_13e==3 || sequence_index_13e==4) {
        if(B(0x104)==1) {
            if(peer()->at<float>(0xec)<F(0xec)) {
                B(0x104)=255;F(0xf4)=-F(0xf4);select_sequence(5);
            } else select_sequence(6);
        } else if(peer()->at<float>(0xec)>F(0xec)) {
            B(0x104)=static_cast<unsigned char>(-B(0x104));F(0xf4)=-F(0xf4);select_sequence(5);
        } else select_sequence(6);
    }
    return;
}
case 215:
    landing();
    if(F(0xf4)>0.0f) {F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(F(0xf4)<0.0f) {F(0xf4)=static_cast<float>(F(0xf4)+0.75);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);return;
case 220: jump_cycle(0.0f,22.5f,0.85f);return;
case 221: jump_cycle(10.0f,18.0f,0.85f);return;
case 222: jump_cycle(-10.0f,18.0f,0.85f);return;
case 223:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        short ticks=++S(0x730);
        if((I(0x6b4)*facing()<=0 && ticks>11) || ticks>45) {set_action_and_finalize(204);return;}
    }
    if(sequence_index_13e==0 && frame_index_140==5 && !frame_timer_142) {
        F(0xf4)=5.5f;dash_effects(false,80.0,true);
    }
    return;
case 224:
    if(sequence_index_13e==0 || sequence_index_13e==3)landing();
    if(sequence_index_13e==3) {F(0xf4)=static_cast<float>(F(0xf4)+1.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(!tenshi_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<3) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {F(0xf8)=0.0f;F(0xf0)=tenshi_surface(this);select_sequence(3);return;}
    }
    if(advance()) {set_action_and_finalize(0);F(0xf4)=0.0f;}
    else if(entry(1)) {F(0xf4)=-10.0f;F(0xf8)=4.0f;F(0x100)=0.3f;dash_effects(true,80.0,false);}
    return;
case 225:
    if(sequence_index_13e>=1)F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())) {zero_motion();F(0xf0)=tenshi_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e>=2 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(time_counter_144==0) {
        if(!frame_timer_142 && !frame_index_140 && sequence_index_13e==1) {
            F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);
        }
        if(entry(2))flip();
    }
    return;
case 226:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())) {zero_motion();F(0xf0)=tenshi_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e==1 && time_counter_144%5==0)dash_dust(false);
    if(advance())set_action_and_finalize(9);
    if(sequence_index_13e==0 && !frame_timer_142 && frame_index_140==3) {
        S(0x730)=0;F(0xf4)=11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(false,110.0,true);
    }
    if(entry(2))flip();
    return;


case 300:
    landing();
    if(!directional(0)) {
        if(B(0x47e)) {F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}}
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142 && frame_index_140==3) {event(28);B(0x47e)=0;}
    }
    return;
case 301:
    landing();if(directional(0))return;
    if(B(0x47e)) {F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}}
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {set_action_and_finalize(0);return;}
    if(sequence_index_13e!=0)return;
    if(!frame_timer_142) {
        if(frame_index_140==4){F(0xf4)=15.0f;B(0x47e)=0;}
        if(!frame_timer_142 && frame_index_140==5)event(29);
    }
    if(frame_index_140>3){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    return;
case 302:
    if((sequence_index_13e==0 && (frame_index_140<=3 || frame_index_140>=8)) || sequence_index_13e==1)landing();
    if(directional(1))return;
    if(B(0x47e)){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}}
    if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(sequence_index_13e==0) {
        if(!frame_timer_142 && frame_index_140==2 && B(0x750)) {
            next_sequence_block();
            int direction=B(0x104);
            float y=static_cast<float>(F(0xf0)+140.0);
            float x=static_cast<float>(F(0xec)-static_cast<double>(65*static_cast<signed char>(direction)));
            effect(62,x,y,direction,1);
            return;
        }
        if(frame_index_140>=7){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
        if(!frame_timer_142) {
            if(frame_index_140==4){F(0xf4)=10.0f;B(0x47e)=0;}
            if(!frame_timer_142 && frame_index_140==7)event(29);
        }
    }
    if(sequence_index_13e==1) {
        if(frame_index_140>=3){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
        if(!frame_timer_142 && frame_index_140==2){F(0xf4)=20.0f;B(0x47e)=0;event(29);}
    }
    return;
case 303:
    landing();
    if(!directional(0)) {
        if(C(0x47e)>0){F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.6f));if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}}
        if(advance())set_action_and_finalize(2);
        if(!frame_timer_142 && frame_index_140==2)event(28);
    }
    return;
case 304:
    landing();if(directional(1))return;
    if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-2.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(sequence_index_13e!=0)return;
    if(!frame_timer_142 && frame_index_140==3)event(29);
    if(!frame_timer_142 && frame_index_140==4)F(0xf4)=5.0f;
    if(frame_index_140>=4){F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.2f));if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    return;
case 305:
    landing();
    if(!directional(1)) {
        if(frame_index_140>4){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142 && frame_index_140==3)event(28);
    }
    return;
case 306:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=tenshi_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!frame_timer_142 && frame_index_140==2)event(27);
    return;
case 307:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=tenshi_surface(this);zero_motion();return;}
    if(sequence_index_13e==0 && frame_index_140>=3) {
        F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<2.0f)F(0xf4)=2.0f;
        if(frame_index_140<=6 && S(0x730)>0) {if(S(0x730)%10==1)event(29);++S(0x730);}
        if(frame_index_140<=8 && F(0xf8)<=-3.0f)F(0xf8)=-3.0f;
    }
    if(advance())set_action_and_finalize(9);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==0 && !frame_timer_142 && frame_index_140==3) {
        float payload[4]={0.0f,150.0f,0.0f,0.0f};
        spawn(848,F(0xec),F(0xf0),B(0x104),1,payload,4);
        payload[0]=120.0f;spawn(848,F(0xec),F(0xf0),B(0x104),1,payload,4);
        payload[0]=240.0f;spawn(848,F(0xec),F(0xf0),B(0x104),1,payload,4);
        F(0xf4)=15.0f;F(0xf8)=8.0f;F(0x100)=0.5f;S(0x730)=1;
    }
    return;
case 308:
    if(sequence_index_13e==2)landing();
    if(!I(0x6bc))B(0x750)=0;
    if(sequence_index_13e==1 && static_cast<unsigned char>(crossed())) {
        next_sequence_block();F(0xf0)=tenshi_surface(this);zero_motion();layout(5.0f);
        float payload[3]={0.0f,20.0f,1.0f};
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
            payload[0]=static_cast<float>(static_cast<float>(tenshi_random(30))+n*45.0);
            if(payload[0]<0.0f || payload[0]>180.0f)spawn(848,F(0xec),F(0xf0),B(0x104),-1,payload,3);
            else spawn(848,F(0xec),F(0xf0),B(0x104),1,payload,3);
        }
        dispatch_character_wave_handle(2);
    }
    if(advance())set_action_and_finalize(9);
    if(entry(1)){F(0xf4)=0.0f;F(0xf8)=-25.0f;}
    return;
case 309:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=tenshi_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(sequence_index_13e==0 && !frame_timer_142 && frame_index_140==2) {event(29);F(0xf8)=8.5f;F(0x100)=0.5f;}
    return;
case 310:
    if(sequence_index_13e<2) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {F(0xf8)=0.0f;F(0xf0)=tenshi_surface(this);select_sequence(2);return;}
    }
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(9);
    if(sequence_index_13e==1 && !frame_timer_142 && !frame_index_140 && C(0x184)>0){I(0x180)=0;event(28);}
    return;

case 320:
    landing();
    if(!directional(0)) {
        if(frame_index_140>=2){F(0xf4)=static_cast<float>(F(0xf4)-3.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142) {
            if(frame_index_140==1)event(28);
            if(!frame_timer_142 && frame_index_140==2){F(0xf4)=15.0f;B(0x47e)=0;}
        }
    }
    return;
case 321:
    landing();
    if(!directional(1)) {
        if(frame_index_140>=3){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
        if(advance())set_action_and_finalize(0);
        if(!frame_timer_142) {
            if(frame_index_140==3){F(0xf4)=15.0f;event(29);B(0x47e)=0;}
            if(!frame_timer_142 && frame_index_140==5)F(0xf4)=0.0f;
        }
    }
    return;
case 400:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        aim(-20.0f,20.0f);S(0x730)=1;
        float p[3]={F(0x744),17.5f,4.0f};
        int direction=B(0x104);
        float y=static_cast<float>(F(0xf0)+110.0);
        float x=static_cast<float>(50*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(800,x,y,direction,1,p,3);phase_counter(30);I(0x180)=1;dispatch_character_wave_handle(0);counter(200,45);
    }
    return;
case 401:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        aim(-20.0f,20.0f);S(0x730)=1;
        float p[3]={F(0x744),17.5f,4.0f};
        int direction=B(0x104);
        float y=static_cast<float>(F(0xf0)+110.0);
        float x=static_cast<float>(50*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(800,x,y,direction,1,p,3);I(0x180)=1;dispatch_character_wave_handle(0);counter(200,45);phase_counter(30);
    }
    return;
case 402:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==3) {
        I(0x180)=1;aim(-70.0f,-45.0f);S(0x730)=1;
        float p[3]={F(0x744),17.5f,4.0f};
        int direction=B(0x104);
        float y=static_cast<float>(F(0xf0)+50.0);
        float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(800,x,y,direction,1,p,3);I(0x180)=1;dispatch_character_wave_handle(0);counter(200,45);phase_counter(30);
    }
    return;
case 404: air_800(-10.0f,10.0f);return;
case 405: air_800(-20.0f,20.0f);return;
case 406: air_800(25.0f,45.0f);return;
case 408:
    landing();
    if(sequence_index_13e==3)F(0xf4)=static_cast<float>(F(0xf4)-0.5);
    if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    if(sequence_index_13e==1 || sequence_index_13e==2) {if(time_counter_144%14==0)event(28);++S(0x730);}
    if(advance())set_action_and_finalize(0);
    if((sequence_index_13e==1 || sequence_index_13e==2) &&
       (frame_index_140==0 || frame_index_140==4) && !frame_timer_142) I(0x180)=0;
    return;
case 409:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())) {set_action_and_finalize(10);zero_motion();F(0xf0)=tenshi_surface(this);return;}
    if(advance())set_action_and_finalize(9);return;
case 410:
    landing();
    if((sequence_index_13e==1 && time_counter_144>=16) || (sequence_index_13e==2 && time_counter_144>=20)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        I(0x180)=1;float p[3]={-10.0f,20.0f,4.0f};
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+115.0);
        float x=static_cast<float>(70*facing()+static_cast<double>(F(0xec)));
        spawn(801,x,y,direction,1,p,3);counter(200,60);phase_counter(50);
    } return;
case 411:
    landing();
    if((sequence_index_13e==1 && time_counter_144>=16) || (sequence_index_13e==2 && time_counter_144>=20)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        I(0x180)=1;float p[3]={-10.0f,20.0f,4.0f};
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+115.0);
        float x=static_cast<float>(70*facing()+static_cast<double>(F(0xec)));
        spawn(801,x,y,direction,1,p,3);counter(200,60);phase_counter(50);
    } return;
case 412:
    landing();if(advance())set_action_and_finalize(2);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        I(0x180)=1;ring_801(100.0);dispatch_character_wave_handle(1);counter(200,60);phase_counter(50);
    }return;
case 414: air_801();return;
case 415: air_801();return;
case 416:
    if(sequence_index_13e==1)landing();
    F(0xf8)-=F(0x100);
    if(sequence_index_13e<1 && static_cast<unsigned char>(crossed())) {
        select_sequence(1);B(0x47f)=0;F(0xf0)=tenshi_surface(this);zero_motion();return;
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==6){I(0x180)=1;ring_801(120.0);dispatch_character_wave_handle(1);counter(200,60);phase_counter(50);}
        if(!frame_timer_142 && frame_index_140==8)F(0x100)=0.5f;
    }return;
case 418:
    landing();if(frame_index_140>=5)F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.4f));
    if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==4){event(29);B(0x47e)=0;}return;
case 500:
    landing();B(0x17c)=0;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=10)return;
    request500[0]=0.0f;request500[1]=15.0f;request500[2]=0.0f;
    spawn(810,F(0xec),F(0xf0),B(0x104),1,request500,3);
    paired_request=request500;
    goto paired_810_tail;
case 501:
    landing();B(0x17c)=0;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=10)return;
    request501[0]=0.0f;request501[1]=30.0f;request501[2]=0.0f;
    spawn(810,F(0xec),F(0xf0),B(0x104),1,request501,3);
    paired_request=request501;
paired_810_tail:
    spawn(810,F(0xec),F(0xf0),static_cast<unsigned char>(-B(0x104)),1,paired_request,3);
    effect(127,F(0xec),F(0xf0),B(0x104),-1);
    effect(127,F(0xec),F(0xf0),static_cast<unsigned char>(-B(0x104)),-1);
    counter(200,120);phase_counter(50);layout(10.0f);return;

case 505:
    landing();B(0x17c)=4;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=10)return;
    {
        float p[3];
        float peer_y=peer()->at<float>(0xf0);
        if(tenshi_surface(peer())>=peer_y) {
            p[0]=0.0f;p[1]=0.0f;p[2]=6.0f;
            spawn(811,peer()->at<float>(0xec),peer()->at<float>(0xf0),B(0x104),1,p,3);
        }
        for(float n=0.0f;n<22.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(tenshi_random(360));p[1]=20.0f;p[2]=5.0f;
            int direction=B(0x104);
            float y=static_cast<float>(20.0-static_cast<float>(tenshi_random(40)));
            float x=static_cast<float>(static_cast<float>(tenshi_random(40))+n*60.0);
            spawn(811,x,y,direction,1,p,3);
        }
        for(float n=0.0f;n<14.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(-static_cast<float>(tenshi_random(90))-45.0);
            p[1]=static_cast<float>(static_cast<float>(tenshi_random(10))+5.0);p[2]=2.0f;
            int direction=B(0x104);
            float y=static_cast<float>(20.0-static_cast<float>(tenshi_random(40)));
            float x=static_cast<float>(static_cast<float>(tenshi_random(60))+n*90.0);
            spawn(811,x,y,direction,1,p,3);
        }
        for(float n=0.0f;n<10.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(-static_cast<float>(tenshi_random(90))-45.0);
            p[1]=static_cast<float>(static_cast<float>(tenshi_random(8))+4.0);p[2]=3.0f;
            int direction=B(0x104);
            float y=static_cast<float>(20.0-static_cast<float>(tenshi_random(40)));
            float x=static_cast<float>(static_cast<float>(tenshi_random(100))+n*120.0);
            spawn(811,x,y,direction,1,p,3);
        }
        for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(-static_cast<float>(tenshi_random(90))-45.0);
            p[1]=static_cast<float>(static_cast<float>(tenshi_random(6))+3.0);p[2]=4.0f;
            int direction=B(0x104);
            float y=static_cast<float>(20.0-static_cast<float>(tenshi_random(40)));
            float x=static_cast<float>(static_cast<float>(tenshi_random(120))+n*160.0);
            spawn(811,x,y,direction,1,p,3);
        }
        effect(127,F(0xec),F(0xf0),B(0x104),-1);
        effect(127,F(0xec),F(0xf0),static_cast<unsigned char>(-B(0x104)),-1);
        counter(200,120);dispatch_character_wave_handle(18);phase_counter(50);layout(10.0f);
    }return;
case 520:
    landing();B(0x17c)=1;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        float p[3]={90.0f,30.0f,0.0f};
        spawn(815,static_cast<float>(F(0xec)-static_cast<double>(150*facing())),1000.0f,B(0x104),1,p,3);
        if(C(0x605)>=4) {
            int direction=B(0x104);
            float x=static_cast<float>(150*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
            spawn(815,x,1000.0f,direction,1,p,3);
        }
        counter(200,120);phase_counter(50);dispatch_character_wave_handle(11);
    }return;
case 521:
    landing();B(0x17c)=1;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        float p[3]={90.0f,30.0f,0.0f};
        spawn(815,static_cast<float>(static_cast<double>(150*facing())+F(0xec)),1000.0f,B(0x104),1,p,3);
        if(C(0x605)>=4) {
            int direction=B(0x104);
            float x=static_cast<float>(F(0xec)-static_cast<double>(150*static_cast<signed char>(direction)));
            spawn(815,x,1000.0f,direction,1,p,3);
        }
        counter(200,120);phase_counter(50);dispatch_character_wave_handle(11);
    }return;
case 525:
    landing();B(0x17c)=5;if(advance())set_action_and_finalize(0);
    if(sequence_index_13e!=0)return;
    if(!frame_timer_142 && frame_index_140==6) {
        float p[3];
        for(float n=0.0f;n<4.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(-n*90.0);p[1]=100.0f;p[2]=0.0f;
            int direction=B(0x104);
            float y=static_cast<float>(tenshi_sine(-p[0])*(p[1]*0.25)+F(0xf0));
            float x=static_cast<float>(tenshi_cosine(-p[0])*p[1]*facing()+F(0xec));
            spawn(816,x,y,direction,1,p,3);++I(0x834);
        }
        S(0x82e)=static_cast<short>(60*(C(0x609)+2));counter(200,45);phase_counter(50);dispatch_character_wave_handle(16);
    }
    if(frame_index_140>=6)S(0x82e)=static_cast<short>(60*(C(0x609)+2));
    return;
case 526:
    landing();B(0x17c)=5;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        I(0x180)=1;S(0x830)=1;counter(200,45);phase_counter(25);dispatch_character_wave_handle(11);
    }return;
case 527:
    landing();B(0x17c)=5;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        I(0x180)=1;S(0x830)=2;counter(200,60);phase_counter(50);dispatch_character_wave_handle(11);
    }return;
case 540:
    landing();B(0x17c)=2;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        float p[3]={-10.0f,20.0f,3.0f};
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+115.0);
        float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(820,x,y,direction,1,p,3);counter(200,120);phase_counter(50);
    }
    if(sequence_index_13e==1 && time_counter_144>=30)next_sequence_block();
    else if(sequence_index_13e==2 && time_counter_144>=30)next_sequence_block();
    return;


case 541:
    landing();B(0x17c)=2;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        float p[3]={-10.0f,20.0f,3.0f};
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+115.0);
        float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(820,x,y,direction,1,p,3);counter(200,120);phase_counter(50);
    }
    if(sequence_index_13e==1 && time_counter_144>=30)next_sequence_block();
    else if(sequence_index_13e==2 && time_counter_144>=30)next_sequence_block();
    return;
case 542:
    if(sequence_index_13e==2)landing();
    B(0x17c)=2;
    if(sequence_index_13e<2) {
        F(0xf8)-=F(0x100);
        float next_y=F(0xf8)+F(0xf0);
        if(tenshi_surface(this)>=next_y && F(0xf8)<0.0f) {
            zero_motion();select_sequence(2);F(0xf0)=tenshi_surface(this);return;
        }
    }
    if(sequence_index_13e<=1 && !I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(9);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        dispatch_character_wave_handle(7);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;I(0x180)=1;
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+62.0);
        float x=static_cast<float>(30*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(816,x,y,direction,1,0,0);counter(200,120);phase_counter(50);
    }return;
case 545:
    landing();B(0x17c)=6;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)pair_821();
    if(sequence_index_13e==1 && time_counter_144>=12 && (time_counter_144>=40 || !B(0x750))) {
        I(0x180)=1;next_sequence_block();
    }return;
case 546:
    landing();B(0x17c)=6;if(!I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)pair_821();
    if(sequence_index_13e==1 && time_counter_144>=20 && (time_counter_144>=120 || !B(0x750))) {
        I(0x180)=1;next_sequence_block();
    }return;
case 547: air_pair821(0x6c0,12,40);return;
case 548: air_pair821(0x6c4,20,120);return;
case 560:
    landing();B(0x17c)=3;if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1) {
        counter(200,120);phase_counter(50);F(0xf4)=10.0f;
        if(C(0x607)>=2)F(0xf4)=11.5f;if(C(0x607)>=4)F(0xf4)=13.0f;
        dispatch_character_wave_handle(19);effect(127,F(0xec),F(0xf0),B(0x104),-1);
    }
    if(sequence_index_13e==1) {
        if(C(0x607)>=4)dash825();
        float delta=F(0xec)-peer()->at<float>(0xec);
        float distance=static_cast<float>(fabs(static_cast<double>(delta)));
        if(distance<=200.0f) {
            next_sequence_block();F(0xf4)=25.0f;effect(127,F(0xec),F(0xf0),B(0x104),-1);return;
        }
        if(time_counter_144>=20){select_sequence(3);return;}
    }
    dash_burst_tail();return;
case 561:
    landing();B(0x17c)=3;if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)-0.75);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(sequence_index_13e==3){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1) {
        counter(200,120);phase_counter(50);F(0xf4)=15.0f;
        if(C(0x607)>=2)F(0xf4)=17.0f;if(C(0x607)>=4)F(0xf4)=19.0f;
        dispatch_character_wave_handle(19);effect(127,F(0xec),F(0xf0),B(0x104),-1);
    }
    if(sequence_index_13e==1) {
        if(C(0x607)>=4)dash825();
        float delta=F(0xec)-peer()->at<float>(0xec);
        float distance=static_cast<float>(fabs(static_cast<double>(delta)));
        if(distance<=200.0f) {
            next_sequence_block();F(0xf4)=25.0f;effect(127,F(0xec),F(0xf0),B(0x104),-1);return;
        }
        if(time_counter_144>=40){select_sequence(3);return;}
    }
    dash_burst_tail();return;
case 565:
    landing();B(0x17c)=7;if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2){counter(200,120);phase_counter(50);event(29);B(0x184)=1;I(0x180)=0;}
        if(!frame_timer_142 && frame_index_140==7){B(0x184)=1;I(0x180)=0;burst848(100,3.0f);dispatch_character_wave_handle(17);}
    }return;
case 566:
    landing();B(0x17c)=7;
    if(!sequence_index_13e && frame_index_140>=8 && frame_index_140<=11) {
        F(0xf4)=static_cast<float>(F(0xf4)-4.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2){event(29);counter(200,120);phase_counter(50);B(0x184)=1;I(0x180)=0;}
        if(!frame_timer_142) {
            if(frame_index_140==7){event(29);B(0x184)=1;I(0x180)=0;F(0xf4)=20.0f;}
            if(!frame_timer_142 && frame_index_140==12){B(0x184)=1;I(0x180)=0;burst848(100,3.0f);dispatch_character_wave_handle(17);}
        }
    }return;
case 567:
    if(sequence_index_13e==5)landing();
    B(0x17c)=7;F(0xf8)-=F(0x100);
    {
        double next_y=static_cast<double>(F(0xf8))+F(0xf0);
        if(tenshi_surface(this)>=next_y && F(0xf8)<0.0f && sequence_index_13e<5) {
            select_sequence(5);B(0x47f)=0;F(0xf0)=tenshi_surface(this);zero_motion();return;
        }
    }
    if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==2 && frame_index_140==2 && !frame_timer_142) {
        float dx=static_cast<float>((peer()->at<float>(0xec)-F(0xec))*static_cast<double>(facing()));
        float dy=peer()->at<float>(0xf0)-F(0xf0);
        S(0x734)=static_cast<short>(-static_cast<short>(static_cast<int>(tenshi_atan(dy,dx))));
        if(S(0x734)<-10)S(0x734)=-10;if(S(0x734)>10)S(0x734)=10;
        dispatch_character_wave_handle(29);I(0x180)=1;counter(200,60);phase_counter(50);
        float p[3]={0.0f,0.0f,0.0f};
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+104.0);
        float x=static_cast<float>(48*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(824,x,y,direction,1,p,3);
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {
        float p[3]={0.0f,0.0f,4.0f};
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+104.0);
        float x=static_cast<float>(F(0xec)-static_cast<double>(48*static_cast<signed char>(direction)));
        spawn(824,x,y,direction,1,p,3);
    }
    if(entry(5)){set_action_and_finalize(9);return;}
    if(sequence_index_13e==1 && time_counter_144>10 && (!B(0x750) || time_counter_144>25))next_sequence_block();
    if(sequence_index_13e==3 && time_counter_144>40)next_sequence_block();
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5)F(0x100)=0.6f;
    return;

case 599:
    if(S(0x730)>0 && frame_index_140<7 && S(0x730)<12) {
        S(0x734)=static_cast<short>(tenshi_random_u32()%35u);
        float p[3];
        p[0]=static_cast<float>(-20-S(0x734));
        p[1]=static_cast<float>(static_cast<short>(tenshi_random_u32()%5u+10u));p[2]=0.0f;
        int direction=B(0x104);
        float x=static_cast<float>(20*static_cast<signed char>(direction)*(S(0x730)+1)+static_cast<double>(F(0xec)));
        spawn(807,x,F(0xf0),direction,1,p,3);
        p[0]=static_cast<float>(tenshi_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        direction=B(0x104);
        x=static_cast<float>(20*static_cast<signed char>(direction)*(S(0x730)+1)+static_cast<double>(F(0xec)));
        spawn(801,x,F(0xf0),direction,1,p,3);
        if(S(0x730)==1){dispatch_character_wave_handle(0);counter(200,120);}
        ++S(0x730);
    }
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5)S(0x730)=1;
    return;
case 600:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==8)spell_flash(0,190.0,2);
        if(!frame_timer_142 && frame_index_140==10) {
            float p[3]={0.0f,10.0f,0.0f};
            spawn(850,F(0xec),F(0xf0),B(0x104),1,p,3);
            spawn(850,F(0xec),F(0xf0),static_cast<unsigned char>(-B(0x104)),1,p,3);
            effect127_pair();layout(10.0f);
        }
    }return;
case 601:
    landing();texture(2,2);
    if(!sequence_index_13e && I(0x180)==1) {
        peer()->set_action_and_finalize(102);peer()->zero_motion();next_sequence_block();
        float p[3]={0.0f,4.0f,0.0f};
        float y=static_cast<float>(peer()->at<float>(0xf0)+100.0);
        spawn(851,peer()->at<float>(0xec),y,1,1,p,3);dispatch_character_wave_handle(51);return;
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3)spell_flash(50,110.0,2);
        if(!frame_timer_142 && frame_index_140==6) {
            float p[3]={0.0f,20.0f,3.0f};burst_payload(p,12.0f,30.0,110,0.0,false,848);
        }
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==3) {
        forward_hit_quantity(1750,800,1,1);peer()->at<float>(0x18c)=24.0f;peer()->at<float>(0x190)=15.0f;
        peer()->set_action_and_finalize(74);dispatch_character_wave_handle(52);layout(10.0f);peer()->at<short>(0x4b2)=900;
    }return;
case 602:
    texture(2,2);
    if((!sequence_index_13e && frame_index_140<=3) || sequence_index_13e==4)landing();
    if(sequence_index_13e==1) {
        float p[3];
        p[0]=static_cast<float>(static_cast<float>(tenshi_random(60))+80.0);
        p[1]=static_cast<float>(static_cast<float>(tenshi_random(10))+5.0);p[2]=2.0f;
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+166.0);
        float x=static_cast<float>(45*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(852,x,y,direction,1,p,3);
        if(time_counter_144%2==0) {
            p[1]=0.5f;p[2]=3.0f;direction=B(0x104);y=static_cast<float>(F(0xf0)+166.0);
            x=static_cast<float>(45*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
            spawn(852,x,y,direction,1,p,3);
        }
        if(time_counter_144>=20){next_sequence_block();F(0xf8)=static_cast<float>(F(0xf8)*0.25);}
    }
    if(sequence_index_13e==2 || sequence_index_13e==3) {
        F(0xf8)-=F(0x100);F(0xf4)=static_cast<float>(F(0xf4)-0.25);if(F(0xf4)<0.0f)F(0xf4)=0.0f;
        if(static_cast<unsigned char>(crossed())){select_sequence(4);zero_motion();F(0xf0)=tenshi_surface(this);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2)spell_flash(-25,160.0,3);
        if(!frame_timer_142 && frame_index_140==9) {
            float p[3]={0.0f,25.0f,3.0f};
            burst_payload(p,18.0f,20.0,100,0.0,false,848);
            F(0xf4)=15.0f;F(0xf8)=35.0f;F(0x100)=0.5f;dispatch_character_wave_handle(50);
            p[2]=4.0f;spawn(852,F(0xec),F(0xf0),B(0x104),-1,p,3);
        }
    }return;
case 603:
    landing();texture(2,2);if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==8)spell_flash(0,190.0,5);
        if(!frame_timer_142 && frame_index_140==11) {
            float p[3]={0.0f,10.0f,0.0f};
            spawn(853,F(0xec),F(0xf0),B(0x104),1,p,3);
            effect127_pair();layout(3.0f);dispatch_character_wave_handle(10);
            p[1]=20.0f;p[2]=1.0f;burst_payload(p,8.0f,45.0,0,0.0,false,848);
        }
    }return;
case 604:
    landing();texture(2,2);
    if(S(0x730)==1) {
        F(0x73c)=static_cast<float>(tenshi_random(360));
        float p[3]={static_cast<float>(F(0x73c)+180.0),300.0f,3.0f};
        spawn(854,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1,p,3);
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1))set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3){spell_flash(50,110.0,4);S(0x730)=1;}
        if(!frame_timer_142) {
            if(frame_index_140==4)S(0x730)=0;
            if(!frame_timer_142 && frame_index_140==6) {
                if(g_fighter_state_4b8_default==16) {
                    float p[3]={0.0f,40.0f,0.0f};
                    int direction=B(0x104);float y=static_cast<float>(F(0xf0)+90.0);
                    float x=static_cast<float>(120*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
                    spawn(854,x,y,direction,1,p,3);
                } else {
                    float p[3];p[0]=0.0f;g_tenshi_weather_counter=0;p[1]=60.0f;p[2]=6.0f;
                    int direction=B(0x104);float y=static_cast<float>(F(0xf0)+90.0);
                    float x=static_cast<float>(120*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
                    spawn(854,x,y,direction,1,p,3);
                    for(int n=0;n<4;++n) {
                        p[0]=static_cast<float>(tenshi_random(360));p[1]=static_cast<float>(static_cast<float>(tenshi_random(5))+5.0);p[2]=7.0f;
                        direction=B(0x104);y=static_cast<float>(F(0xf0)+90.0);
                        x=static_cast<float>(120*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
                        spawn(854,x,y,direction,1,p,3);
                    }
                }
                // Native mode1 request writes only slot2 at6460EE; slots0/1 are not initialized here.
                float p[3];p[2]=1.0f;
                int direction=B(0x104);float y=static_cast<float>(F(0xf0)+90.0);
                float x=static_cast<float>(120*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
                spawn(854,x,y,direction,1,p,3);
                p[1]=20.0f;p[2]=5.0f;burst_payload(p,12.0f,30.0,120,90.0,false,854);
                dispatch_character_wave_handle(55);
            }
        }
    }return;
case 605:
    if((!sequence_index_13e && frame_index_140<=3) || sequence_index_13e==6)landing();
    texture(2,2);
    if(static_cast<unsigned short>(sequence_index_13e)<=1 && I(0x180)) {
        if(++S(0x730)>=6){S(0x730)=0;I(0x180)=0;}
    }
    if(sequence_index_13e==1 && time_counter_144>=20){next_sequence_block();F(0xf8)=0.0f;F(0x100)=1.0f;return;}
    if(sequence_index_13e==2 && time_counter_144>=30) {
        next_sequence_block();F(0xf8)=-50.0f;B(0x184)=1;dispatch_character_wave_handle(53);
        float p[3]={0.0f,0.0f,0.0f};spawn(855,F(0xec),F(0xf0),B(0x104),-1,p,3);return;
    }
    if(sequence_index_13e==3) {
        F(0xf8)-=F(0x100);float y=F(0xf0);
        if(tenshi_surface(this)+150.0>=y) {
            zero_motion();layout(20.0f);select_sequence(4);F(0xf0)=static_cast<float>(tenshi_surface(this)+150.0);
            float p[3]={0.0f,25.0f,1.0f};burst_payload(p,18.0f,20.0,100,0.0,true,848);
            dispatch_character_wave_handle(54);return;
        }
    }
    if(sequence_index_13e==4 || sequence_index_13e==5) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){select_sequence(6);zero_motion();F(0xf0)=tenshi_surface(this);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==2)spell_flash(-25,160.0,3);
        if(!frame_timer_142 && frame_index_140==9) {
            float p[3]={0.0f,25.0f,3.0f};burst_payload(p,18.0f,20.0,100,0.0,false,848);
            F(0xf4)=7.0f;F(0xf8)=35.0f;F(0x100)=0.5f;dispatch_character_wave_handle(50);
        }
    }
    if(sequence_index_13e==4 && !frame_timer_142 && frame_index_140==5){F(0xf4)=-5.0f;F(0xf8)=10.0f;F(0x100)=0.5f;}
    return;
case 606:
    landing();texture(2,2);
    if(sequence_index_13e==1 && time_counter_144>=36){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {
        layout(10.0f);dispatch_character_wave_handle(57);
        float p[3];
        for(float n=0.0f;n<12.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(n*30.0);p[1]=30.0f;p[2]=1.0f;
            int layer=tenshi_sine_radians(p[0])<=0.0?1:-1;
            spawn(856,F(0xec),F(0xf0),B(0x104),layer,p,3);
        }
        p[0]=0.0f;p[1]=0.0f;p[2]=0.0f;spawn(856,F(0xec),F(0xf0),B(0x104),1,p,3);
        p[2]=2.0f;spawn(856,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1,p,3);
        p[2]=3.0f;spawn(856,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1,p,3);
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3)spell_flash(-72,178.0,4);
    if(sequence_index_13e>=1)I(0x838)=900;
    return;
case 607:
    texture(2,2);
    if(sequence_index_13e==1){if(g_tenshi_weather_counter>=5)g_tenshi_weather_counter-=5;if(time_counter_144>=120){next_sequence_block();return;}}
    if(sequence_index_13e==2 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {
        layout(10.0f);dispatch_character_wave_handle(56);
        float p[3]={15.0f,0.0f,3.0f};int direction=B(0x104);
        float y=static_cast<float>(F(0xf0)+130.0);
        float x=static_cast<float>(90*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(857,x,y,direction,1,p,3);
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)spell_flash(-55,220.0,5);
    return;
case 657:
    texture(2,2);
    if(sequence_index_13e==1){if(g_tenshi_weather_counter>=5)g_tenshi_weather_counter-=5;if(time_counter_144>=120){next_sequence_block();return;}}
    if(sequence_index_13e==2 && time_counter_144>=60){next_sequence_block();return;}
    if(sequence_index_13e==3 || sequence_index_13e==4) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=tenshi_surface(this);select_sequence(5);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {
        layout(10.0f);dispatch_character_wave_handle(56);
        float p[3]={15.0f,0.0f,3.0f};int direction=B(0x104);
        float y=static_cast<float>(F(0xf0)+130.0);
        float x=static_cast<float>(90*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(857,x,y,direction,1,p,3);
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8)spell_flash(-55,220.0,5);
    if(sequence_index_13e==3 && !frame_timer_142 && frame_index_140==1)F(0x100)=0.2f;
    return;
case 695:
    landing();
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==6) {
        event(55);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(140,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),1);
        effect(141,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1);
        effect(142,F(0xec),F(0xf0),B(0x104),-1);
    }
    return;
case 696:
    landing();
    if(frame_index_140>5){F(0xf4)=static_cast<float>(F(0xf4)-3.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==5){F(0xf4)=15.0f;event(29);B(0x47e)=0;}
        if(!frame_timer_142 && frame_index_140==7)F(0xf4)=0.0f;
    }
    return;
case 710:
    if(sequence_index_13e==1 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(700);
    if(entry(1)) {
        float p[3]={0.0f,0.0f,0.0f};
        int direction=B(0x104);float y=static_cast<float>(F(0xf0)+115.0);
        float x=static_cast<float>(80*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(900,x,y,direction,1,p,3);
    }
    return;
case 720:
    switch(sequence_index_13e) {
    case 1:
        F(0xf8)-=F(0x100);
        if(time_counter_144>=30) {
            float distance=F(0xec)-peer()->at<float>(0xec);
            if(tenshi_square(distance)<=400.0f){zero_motion();next_sequence_block();}
        }
        break;
    case 3:
        F(0xf8)=-40.0f;
        if(static_cast<unsigned char>(crossed())) {
            S(0x732)=1;S(0x734)=static_cast<short>(static_cast<int>(F(0xec)/160.0));
            if(!B(0x82c)) {
                B(0x82c)=1;float p[3]={0.0f,0.0f,0.0f};
                for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
                    p[2]=n;spawn(961,static_cast<float>(n*160.0+80.0),0.0f,1,-1,p,3);
                }
            }
            zero_motion();F(0xf0)=tenshi_surface(this);layout(5.0f);
            float p[3]={0.0f,20.0f,1.0f};
            burst_payload(p,8.0f,45.0,0,0.0,false,848);next_sequence_block();
        }
        break;
    case 4:F(0xf0)=tenshi_surface(this);break;
    }
    if(S(0x732)>=1) {
        // Native difficulty dispatch has no fallback definition. Domain audit pending.
        int budget,spread;
        switch(g_match_identifier) {
        case 0:budget=150;spread=2;break;
        case 1:budget=250;spread=6;break;
        case 2:budget=375;spread=7;break;
        case 3:budget=500;spread=7;break;
        }
        if(S(0x732)%10==1 && S(0x736)<=spread) {
            dispatch_character_wave_handle(10);layout(4.0f);
            if(S(0x736)) {
                if(S(0x734)+S(0x736)<=7)F(0x7a4+4*(S(0x734)+S(0x736)))=static_cast<float>(tenshi_random(budget));
                if(S(0x734)-S(0x736)>=0)F(0x7a4+4*(S(0x734)-S(0x736)))=static_cast<float>(tenshi_random(budget));
            } else F(0x7a4+4*S(0x734))=0.0f;
            ++S(0x736);
        }
        ++S(0x732);
    }
    if(advance()) {
        flip();
        if(tenshi_random(100)>50u || peer()->at<short>(0x174)<=0) {
            set_action_and_finalize(701);
            F(0x780)=static_cast<float>(-5.0-static_cast<float>(tenshi_random(15)));
            F(0x784)=10.0f;F(0x788)=0.6f;
        } else {set_action_and_finalize(720);return;}
    }
    if(!time_counter_144) {
        if(entry(1)){flip();F(0xf4)=F(0x780);F(0xf8)=F(0x784);F(0x100)=F(0x788);time_counter_144=0;}
        if(entry(2))zero_motion();
    }
    return;
case 730:
    if(sequence_index_13e==1) {
        if(S(0x730)%5==0 && F(0x73c)<=5.0f) {
            float p[3]={F(0x73c),0.0f,0.0f};int direction=B(0x104);
            float x=static_cast<float>((static_cast<float>(tenshi_random(100))+200.0+200.0*F(0x73c))*facing()+F(0xec));
            spawn(920,x,-100.0f,direction,1,p,3);
            p[0]=static_cast<float>(F(0x73c)+6.0);p[1]=0.0f;p[2]=0.0f;
            direction=B(0x104);float base_x=F(0xec);
            x=static_cast<float>(base_x-(static_cast<float>(tenshi_random(100))+200.0+200.0*F(0x73c))*facing());
            spawn(920,x,-100.0f,direction,1,p,3);F(0x73c)=static_cast<float>(F(0x73c)+1.0);
        }
        if(S(0x730)>=120){next_sequence_block();return;}
        ++S(0x730);
    }
    if(advance())set_action_and_finalize(731);
    return;
case 731:
    landing();
    if(advance()) {
        flip();set_action_and_finalize(701);
        if(B(0x104)==1) {
            if(F(0xec)>=480.0f)F(0x780)=static_cast<float>(-5.0-static_cast<float>(tenshi_random(15)));
            else F(0x780)=static_cast<float>(static_cast<float>(tenshi_random(10))+10.0);
        } else {
            if(F(0xec)<=800.0f)F(0x780)=static_cast<float>(-5.0-static_cast<float>(tenshi_random(15)));
            else F(0x780)=static_cast<float>(static_cast<float>(tenshi_random(10))+10.0);
        }
        F(0x784)=15.0f;F(0x788)=0.6f;
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==8) {
        float p[3]={-10.0f,20.0f,8.0f};int direction=B(0x104);
        float y=static_cast<float>(F(0xf0)+115.0);
        float x=static_cast<float>(70*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
        spawn(920,x,y,direction,1,p,3);
    }
    if((sequence_index_13e==1 && time_counter_144>=180) || (sequence_index_13e==2 && time_counter_144>=120))next_sequence_block();
    return;
case 740:
    F(0xf0)=tenshi_surface(this);
    if(advance())set_action_and_finalize(g_match_identifier?741:700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==10) {
        dispatch_character_wave_handle(10);
        if(!B(0x82c)) {
            B(0x82c)=1;float p[3]={0.0f,0.0f,0.0f};
            for(float n=0.0f;n<8.0f;n=static_cast<float>(n+1.0)) {
                p[2]=n;spawn(960,static_cast<float>(n*160.0+80.0),0.0f,1,-1,p,3);
            }
        }
        double position=F(0xec)/160.0;
        int budget;
        switch(g_match_identifier){case 0:budget=250;break;case 1:case 2:case 3:budget=350;break;}
        int index=static_cast<int>(position);float *height=&F(0x7a4);
        for(int count=8;count;--count) {
            *height=static_cast<float>(tenshi_random(150));
            F(0x73c)=static_cast<float>(budget-125*(index<0?-index:index));
            *height=F(0x73c)+*height;
            if(*height<0.0f)*height=0.0f;
            ++height;--index;
        }
        if(g_tenshi_weather_selector!=5 || B(0x55a)!=2)return;
        F(0x740)=15.0f;
    }
    if(g_tenshi_weather_selector==5 && B(0x55a)==2) {
        F(0x828)+=F(0x740);F(0x740)=static_cast<float>(F(0x740)-1.0);
        if(F(0x740)<0.0f)F(0x740)=0.0f;
        if(F(0x828)>=800.0f)F(0x828)=800.0f;
        event_owner()->pair(0.0f,F(0x828));
    }
    return;
case 741:
    F(0xf0)=tenshi_surface(this);
    if(sequence_index_13e==1) {
        unsigned interval,duration;float speed;
        switch(g_match_identifier) {
        case 0:interval=15;speed=2.0f;duration=60;break;
        case 1:interval=7;speed=3.0f;duration=60;break;
        case 2:interval=5;speed=4.0f;duration=90;break;
        case 3:interval=4;speed=4.5f;duration=120;break;
        }
        if(static_cast<unsigned>(time_counter_144)%interval==0) {
            dispatch_character_wave_handle(1);F(0x73c)=static_cast<float>(F(0x73c)+20.0);
            float p[3];p[0]=F(0x73c);p[1]=static_cast<float>(static_cast<float>(tenshi_random(4))+speed);p[2]=0.0f;
            int direction=B(0x104);float y=static_cast<float>(F(0xf0)+290.0);
            float x=static_cast<float>(40*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
            spawn(930,x,y,direction,1,p,3);
            p[0]=static_cast<float>(F(0x73c)+180.0);p[1]=static_cast<float>(static_cast<float>(tenshi_random(4))+speed);
            direction=B(0x104);y=static_cast<float>(F(0xf0)+290.0);
            x=static_cast<float>(40*static_cast<signed char>(direction)+static_cast<double>(F(0xec)));
            spawn(930,x,y,direction,1,p,3);
        }
        if(static_cast<unsigned>(time_counter_144)>=duration){next_sequence_block();return;}
    }
    if(sequence_index_13e==2 && time_counter_144>=30){next_sequence_block();return;}
    if(advance()){set_action_and_finalize(700);flip();}
    if(entry(1) && !S(0x730)){S(0x730)=1;time_counter_144=0;}
    return;
case 750:
    if(S(0x738)==5 && static_cast<unsigned>(time_counter_144)%5u==0)layout(5.0f);
    if(!sequence_index_13e) {
        if(!time_counter_144 && !frame_timer_142 && !frame_index_140) {
            float *height=&F(0x7a4);
            for(int count=8;count;--count) {
                *height=200.0f;peer()->at<float>(0xf0)=200.0f;
                peer()->at<float>(0xf8)=0.0f;peer()->set_action_and_finalize(0);
                ++height;F(0x828)=200.0f;
            }
        }
        F(0xf0)=static_cast<float>(tenshi_surface(this)+200.0);F(0xec)=800.0f;
        if(++S(0x730)>=120) {
            F(0x7a4)=static_cast<float>(F(0x7a4)-1.0);F(0x7a8)=static_cast<float>(F(0x7a8)-1.0);
            F(0x7ac)=static_cast<float>(F(0x7ac)-1.0);F(0x7b0)=static_cast<float>(F(0x7b0)-1.0);
            F(0x7b4)=static_cast<float>(F(0x7b4)-1.0);F(0x7b8)=static_cast<float>(F(0x7b8)-1.0);
            F(0x7bc)=static_cast<float>(F(0x7bc)-1.0);F(0x7c0)=static_cast<float>(F(0x7c0)-1.0);
            F(0x828)=F(0x7a4);if(F(0x828)<0.0f)F(0x828)=0.0f;
            event_owner()->pair(0.0f,-F(0x828));
            if(F(0x7a4)<=0.0f) {
                F(0x7a4)=0.0f;F(0x7a8)=0.0f;F(0x7ac)=0.0f;F(0x7b0)=0.0f;
                F(0x7b4)=0.0f;F(0x7b8)=0.0f;F(0x7bc)=0.0f;F(0x7c0)=0.0f;
                next_sequence_block();F(0x828)=0.0f;event_owner()->pair(0.0f,-0.0f);S(0x730)=0;return;
            }
        }
        if(S(0x730)==120){tenshi_fade_out(0xffffffffu,90);tenshi_play_bgm("data/bgm/st06.ogg");transition(480.0f);}
    }
    if(sequence_index_13e==1) {
        if(F(0x74c)>0.0f)F(0x74c)=static_cast<float>(F(0x74c)-1.0);
        if(!time_counter_144) {
            finalize(-1);B(0x655)=1;event_owner()->pair_mode(15,1);copy_health();
            S(0x76a)=1;S(0x76c)=0;S(0x76e)=0;B(0x4e9)=0;B(0x4ec)=1;
            S(0x766)=0;S(0x768)=120;S(0x764)=0;event(23);S(0x736)=1;
        }
        F(0xf0)=static_cast<float>(tenshi_surface(this)+200.0);F(0xec)=800.0f;
    }
    if(sequence_index_13e==2) {
        S(0x768)=240;S(0x76a)=0;S(0x738)=0;
        F(0xf0)=static_cast<float>(tenshi_surface(this)+200.0);F(0xec)=800.0f;
        if(B(0x113)<=252)B(0x113)+=3;
        else {B(0x113)=255;select_sequence(1);return;}
    }
    if(advance())set_action_and_finalize(700);
    return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=7)return;
    B(0x655)=1;finalize(-1);
    if(g_tenshi_weather_selector==5)event_owner()->trigger(14);else texture(2,-1);
    copy_health();S(0x76c)=0;S(0x76a)=1;
    S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);
    return;
case 771:
    if(sequence_index_13e==1) {
        if(B(0x113)<3){B(0x113)=0;set_action_and_finalize(750);select_sequence(2);return;}
        B(0x113)-=3;
    }
    if(advance())set_action_and_finalize(700);
    if(entry(1)) {
        B(0x655)=1;finalize(-1);
        if(g_tenshi_weather_selector==5)event_owner()->trigger(14);
        copy_health();I(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);
    }
    return;
case 780:
    if(!sequence_index_13e) {
        F(0xf8)=-5.0f;
        if(static_cast<unsigned char>(crossed())) {
            layout(5.0f);float p[3]={0.0f,20.0f,1.0f};dispatch_character_wave_handle(2);
            burst_payload(p,8.0f,45.0,0,0.0,false,848);
            next_sequence_block();zero_motion();F(0xf0)=tenshi_surface(this);return;
        }
        if(!frame_timer_142 && frame_index_140==5)dispatch_character_wave_handle(50);
    }
    if(sequence_index_13e==2 && time_counter_144>=20){next_sequence_block();return;}
    if(advance())set_action_and_finalize(700);
    return;
case 781:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==11){effect127_pair();layout(10.0f);dispatch_character_wave_handle(10);}
    return;
case 782:
    if(sequence_index_13e==1 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==9){effect127_pair();layout(10.0f);dispatch_character_wave_handle(12);}
    return;
case 788:
    shared_first(1,640.0f);shared_second(1,static_cast<float>(S(0x730)));S(0x730)+=4;
    if(S(0x730)>=480){S(0x730)=480;S(0x78c)=1;}
    return;
case 795:
    {
    if(!sequence_index_13e) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {
            next_sequence_block();F(0xf0)=tenshi_surface(this);zero_motion();layout(5.0f);
            float p[3]={0.0f,20.0f,1.0f};burst_payload(p,8.0f,45.0,0,0.0,false,848);
            dispatch_character_wave_handle(2);
        }
    }
    if(sequence_index_13e==2 || sequence_index_13e==3) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {
            zero_motion();F(0xf0)=tenshi_surface(this);select_sequence(4);event(30);
            return;
        }
    }
    if(advance())set_action_and_finalize(700);
    if(entry(2)){F(0xf8)=6.0f;F(0x100)=0.5f;}
    return;
    }
case 797:
    {
    if(!sequence_index_13e) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {
            next_sequence_block();F(0xf0)=tenshi_surface(this);zero_motion();layout(5.0f);
            float p[3]={0.0f,20.0f,1.0f};burst_payload(p,8.0f,45.0,0,0.0,false,848);
            dispatch_character_wave_handle(2);
        }
    }
    if(sequence_index_13e==2 || sequence_index_13e==3) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {
            zero_motion();F(0xf0)=tenshi_surface(this);select_sequence(4);event(30);
            F(0xec)=480.0f;
            return;
        }
    }
    if(advance())set_action_and_finalize(0);
    if(entry(2)){F(0xf8)=6.0f;F(0x100)=0.5f;}
    return;
    }
case 798:
    {
    if(!sequence_index_13e) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {
            next_sequence_block();F(0xf0)=tenshi_surface(this);zero_motion();layout(5.0f);
            float p[3]={0.0f,20.0f,1.0f};burst_payload(p,8.0f,45.0,0,0.0,false,848);
            dispatch_character_wave_handle(2);
        }
    }
    if(sequence_index_13e==2 || sequence_index_13e==3) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {
            zero_motion();F(0xf0)=tenshi_surface(this);select_sequence(4);event(30);
            F(0xec)=800.0f;
            return;
        }
    }
    if(advance())set_action_and_finalize(700);
    if(entry(2)){F(0xf8)=6.0f;F(0x100)=0.5f;}
    return;
    }

    default: common_update(); return;
    }
}
#undef B
#undef C
#undef S
#undef U
#undef I
#undef F
}
