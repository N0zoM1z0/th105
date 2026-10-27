#include "characters/PatchouliActionState.hpp"
// Complete JP1.06a50F200 candidate, not selected or exact.
// See docs/PATCHOULI_ACTION_STATE_2026_10_27.md.
namespace th105 {
#define B(o) at<unsigned char>(o)
#define C(o) at<signed char>(o)
#define S(o) at<short>(o)
#define U(o) at<unsigned>(o)
#define I(o) at<int>(o)
#define F(o) at<float>(o)
void PatchouliActionStateView::dispatch_action_state_vslot28()
{
    S(0x7a0)=0;S(0x7a2)=103;
    if(S(0x7a4)>0) {
        --S(0x7a4);
        if(action_id_13c>=600 && action_id_13c<=689 && (action_id_13c!=605 || sequence_index_13e<1))S(0x7a4)=0;
        if(owner()->at<short>(0x174)<=0 || peer()->at<short>(0x174)<=0)S(0x7a4)=0;
    }
    if(F(0x7b4)>0.0f) {
        F(0x7b4)=static_cast<float>(F(0x7b4)-(static_cast<double>(0.4f)-C(0x606)*static_cast<double>(0.05f)));
        if(F(0x7b4)<0.0f)F(0x7b4)=0.0f;
        F(0x6ac)=-F(0x7b4);
        if((F(0xec)<peer()->at<float>(0xec) && peer()->at<unsigned char>(0x104)==1) ||
           (F(0xec)>peer()->at<float>(0xec) && peer()->at<unsigned char>(0x104)==255))F(0x6ac)=F(0x7b4);
    }
    if(S(0x7b0)>0)--S(0x7b0);
    if(action_id_13c>149 && action_id_13c<159 && !B(0x751)) {
        B(0x751)=1;
        if(action_id_13c>149 && action_id_13c<154)
            spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+94.0),B(0x104),1,0,0);
        if(action_id_13c>153 && action_id_13c<158)
            spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+60.0),B(0x104),1,0,0);
        if(action_id_13c==158)
            spawn(998,static_cast<float>(57*facing()+static_cast<double>(F(0xec))),static_cast<float>(F(0xf0)+100.0),B(0x104),1,0,0);
    }
    if(action_id_13c==710 && sequence_index_13e==1) {
        ++S(0x734);
        switch(g_match_identifier) {
        case 0:
            F(0x740)=static_cast<float>(F(0x740)+static_cast<double>(0.02f));
            if(F(0x740)>=2.0f)F(0x740)=2.0f;
            F(0x73c)=F(0x740)+F(0x73c);F(0x744)-=F(0x740);break;
        case 1:
            F(0x740)=static_cast<float>(F(0x740)+static_cast<double>(0.03f));
            if(F(0x740)>=4.0f)F(0x740)=4.0f;
            F(0x73c)=F(0x740)+F(0x73c);F(0x744)-=F(0x740);break;
        case 2:
            F(0x740)=static_cast<float>(F(0x740)+static_cast<double>(0.04f));
            if(F(0x740)>=4.0f)F(0x740)=4.0f;
            F(0x73c)=F(0x740)+F(0x73c);F(0x744)-=F(0x740);break;
        case 3:
            F(0x740)=static_cast<float>(F(0x740)+static_cast<double>(0.05f));
            if(F(0x740)>=5.0f)F(0x740)=5.0f;
            F(0x73c)=F(0x740)+F(0x73c);F(0x744)-=F(0x740);break;
        }
        if(S(0x734)%2==0 && (F(0xf8)>0.0f || (F(0xf8)<0.0f && F(0xf0)>=100.0f))) {
            float p[3]={static_cast<float>(static_cast<float>(patchouli_random(10))+F(0x73c)-5.0),25.0f,0.0f};
            orbit900(p,0x73c);
            for(int n=2;n;--n) {
                p[0]=static_cast<float>(patchouli_random(360));p[1]=static_cast<float>(static_cast<float>(patchouli_random(4))+8.0);p[2]=4.0f;
                orbit900(p,0x73c);
            }
            if(g_match_identifier==3 || g_match_identifier==2) {
                float q[3]={static_cast<float>(static_cast<float>(patchouli_random(10))+F(0x744)-5.0),25.0f,2.0f};
                orbit900(q,0x744);
                for(int n=2;n;--n) {
                    q[0]=static_cast<float>(patchouli_random(360));q[1]=static_cast<float>(static_cast<float>(patchouli_random(4))+8.0);q[2]=5.0f;
                    orbit900(q,0x744);
                }
            }
        }
    }
    if(S(0x186) || peer()->at<short>(0x48c))return;
    switch(action_id_13c) {
// Complete candidate; branch/type review and exact matching remain pending.
case 0:
    landing();if(F(0xf4)==0.0f)B(0x47e)=0;idle_motion();advance();return;
case 1:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(2);return;
case 2:
    landing();idle_motion();advance();return;
case 3:
    landing();idle_motion();if(advance() && !frame_index_140)set_action_and_finalize(0);return;
case 4:
    landing();F(0xf4)=4.0f;advance();return;
case 5:
    landing();F(0xf4)=-4.0f;advance();return;
case 6:normal_jump(0.0f);return;
case 7:normal_jump(3.0f);return;
case 8:normal_jump(-4.0f);return;
case 9:
    if(F(0x100)==0.0f)F(0x100)=0.6f;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=patchouli_surface(this);zero_motion();return;}
    advance();return;
case 10:
    landing();zero_motion();
    if(advance()){if(I(0x6b8))set_action_and_finalize(2);else set_action_and_finalize(0);}
    return;
case 197:
    landing();
    if(advance()) {
        if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(0);
        if(I(0x6b8)>0)set_action_and_finalize(1);
    }
    if(frame_timer_142)return;
    if(frame_index_140==6)ground_face();
    if(!frame_timer_142 && frame_index_140==6)F(0xf4)=0.0f;
    return;
case 198:
    landing();
    if(advance()) {
        if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(0);
        if(I(0x6b8)>0)set_action_and_finalize(1);
    }
    if(!frame_timer_142) {
        if(frame_index_140==6)ground_face();
        if(!frame_timer_142 && frame_index_140==6)F(0xf4)=0.0f;
    }
    return;
case 199:
    landing();
    if(advance()) {
        if(B(0x72c)==2){set_action_and_finalize(700);S(0x4a8)=3;S(0x4ac)=3;return;}
        set_action_and_finalize(0);
        if(I(0x6b8)>0)set_action_and_finalize(1);
    }
    if(!frame_timer_142 && frame_index_140==5)ground_face();
    return;
case 200:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        if(I(0x6b8)<0) {
            if(I(0x6b4)*facing()<=0)set_action_and_finalize(211);else set_action_and_finalize(212);
            return;
        }
        short ticks=++S(0x730);
        if((I(0x6b4)*facing()<=0 && ticks>=5) || ticks>=60){set_action_and_finalize(204);return;}
    }
    if(entry(1)){F(0xf4)=8.5f;dash_effects(false,80.0,true);}
    return;
case 201:
    if(sequence_index_13e==2) {
        landing();
        if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    }
    if(!patchouli_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<2) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=patchouli_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && frame_index_140==1 && !frame_timer_142) {
        F(0xf4)=-10.0f;F(0xf8)=3.0f;F(0x100)=0.3f;dash_effects(true,80.0,false);
    }return;
case 202:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=patchouli_surface(this);set_action_and_finalize(10);return;}
    if((sequence_index_13e==1 || sequence_index_13e==2) && time_counter_144%5==0)dash_dust(false);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2) {
        F(0xf4)=8.0f;F(0xf8)=3.0f;F(0x100)=0.4f;dash_effects(false,110.0,true);
    }
    if(entry(2))flip();
    return;
case 203:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=patchouli_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e<3 && time_counter_144%5==0)dash_dust(true);
    advance();
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==1) {
        F(0xf4)=-8.0f;F(0xf8)=3.0f;F(0x100)=0.4f;dash_effects(true,120.0,false);
    }
    if(entry(2))flip();
    return;
case 204:
    landing();F(0xf4)=static_cast<float>(F(0xf4)-0.5);
    if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    if(advance()){set_action_and_finalize(0);B(0x47e)=0;}
    return;
case 208:high_jump(0.0f,19.0f);return;
case 209:
case 212:
case 221:high_jump(8.5f,15.0f);return;
case 210:high_jump(-8.5f,15.0f);return;
case 211:high_jump(2.0f,19.0f);return;
case 215:
    landing();
    if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(F(0xf4)<0.0f){F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    return;
case 220:high_jump(0.0f,19.0f);return;
case 222:high_jump(-8.5f,15.0f);return;
case 223:
    landing();B(0x47e)=1;advance();
    if(sequence_index_13e==1) {
        if(time_counter_144%5==0)dash_dust(false);
        short ticks=++S(0x730);
        if((I(0x6b4)*facing()<=0 && ticks>=15) || ticks>=60){set_action_and_finalize(204);return;}
    }
    if(entry(1)){F(0xf4)=6.0f;dash_effects(false,80.0,true);}
    return;
case 224:
    if(sequence_index_13e==2) {
        landing();
        if(sequence_index_13e==2){F(0xf4)=static_cast<float>(F(0xf4)+2.0);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    }
    if(!patchouli_on_surface(this) && time_counter_144%5==0)dash_dust(true);
    if(sequence_index_13e<2) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=patchouli_surface(this);select_sequence(2);return;}
    }
    if(advance()){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && frame_index_140==1 && !frame_timer_142) {
        F(0xf4)=-10.0f;F(0xf8)=3.0f;F(0x100)=0.3f;dash_effects(true,80.0,false);
    }return;
case 225:
    if(sequence_index_13e>=1) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=patchouli_surface(this);set_action_and_finalize(10);return;}
    }
    if(sequence_index_13e>=2 && time_counter_144%5==0)dash_dust(true);
    if(advance())set_action_and_finalize(9);
    if(entry(1)){F(0xf4)=-11.0f;F(0xf8)=4.0f;F(0x100)=0.5f;dash_effects(true,120.0,false);}
    return;
case 226:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=patchouli_surface(this);set_action_and_finalize(10);return;}
    if(sequence_index_13e==1 && time_counter_144%5==0)dash_dust(false);
    advance();
    if(!time_counter_144) {
        if(entry(1)){S(0x730)=0;F(0xf4)=8.0f;F(0xf8)=3.0f;F(0x100)=0.4f;dash_effects(false,110.0,true);}
        if(entry(2))flip();
    }
    return;
case 214: {
    if(advance()){set_action_and_finalize(9);return;}
    if(entry(1)) {
        event(31);
        if(F(0x740)>=135.0f || F(0x740)<=-135.0f){select_sequence(6);return;}
        if(F(0x740)>45.0f || F(0x740)<-45.0f){select_sequence(4);return;}
    }
    if(entry(9))select_sequence(5);
    if(entry(10) || entry(11)){set_action_and_finalize(9);return;}
    int vertical=I(0x6b8),horizontal=I(0x6b4)*facing();
    if(vertical>0)S(0x732)=horizontal>0?-45:(horizontal<0?-135:-90);
    else if(vertical<0)S(0x732)=horizontal>0?45:(horizontal<0?135:90);
    else {if(horizontal>0)S(0x732)=0;else if(horizontal<0)S(0x732)=180;}
    if(sequence_index_13e==9 || sequence_index_13e==10 || sequence_index_13e==11)F(0xf8)-=F(0x100);
    bool retain=true;
    if(sequence_index_13e>0 && sequence_index_13e<9) {
        ++S(0x736);
        S(0x734)=static_cast<short>(S(0x732)-static_cast<int>(F(0x740)));
        if(S(0x734)>180)S(0x734)-=360;
        if(S(0x734)<-180)S(0x734)+=360;
        if(F(0x740)>180.0f)F(0x740)=static_cast<float>(F(0x740)-360.0);
        if(F(0x740)<-180.0f)F(0x740)=static_cast<float>(F(0x740)+360.0);
        if(S(0x734)>0) {
            if(I(0x4b8))F(0x740)=static_cast<float>(F(0x740)+4.0);
            else F(0x740)=static_cast<float>(F(0x740)+5.0);
        }
        if(S(0x734)<0) {
            if(I(0x4b8))F(0x740)=static_cast<float>(F(0x740)-4.0);
            else F(0x740)=static_cast<float>(F(0x740)-5.0);
        }
        F(0xf4)=static_cast<float>(patchouli_cosine(F(0x740))*F(0x73c));
        F(0xf8)=static_cast<float>(patchouli_sine(F(0x740))*F(0x73c));
        if(F(0xf0)>680.0f && F(0xf8)>0.0f)F(0xf8)=0.0f;
        if(I(0x4b8))counter(8,1);else counter(4,1);
        short seq=sequence_index_13e;
        if((seq==1 || seq==2) && (F(0x740)>60.0f || F(0x740)<-60.0f)){select_sequence(3);return;}
        if(seq==4 || seq==5) {
            if(F(0x740)<=45.0f && F(0x740)>=-45.0f){select_sequence(1);return;}
            if(F(0x740)>=135.0f || F(0x740)<=-135.0f){select_sequence(6);return;}
        }
        if((seq==6 || seq==7) && F(0x740)<120.0f && F(0x740)>-120.0f){select_sequence(8);return;}
        int held=I(0x6c8);
        retain=((held || S(0x736)<=10) && S(0x482)>0) ||
               ((held || S(0x736)<=10) && S(0x482)>0);
    }
    if(retain) {
        if(static_cast<unsigned char>(crossed())) {
            F(0xf0)=patchouli_surface(this);F(0xf8)=0.0f;F(0x100)=0.0f;
            if(sequence_index_13e>=9){set_action_and_finalize(10);zero_motion();}
            else {reset_action_scratch();set_action_and_finalize(215);}
        }
        return;
    }
    if(sequence_index_13e==1 || sequence_index_13e==2)release_flight(9);
    if(sequence_index_13e==3) {
        S(0x730)=frame_index_140;
        if(B(0x104)==1) {
            if(peer()->at<float>(0xec)<F(0xec)) {
                B(0x104)=255;goto flight_frame_turn;
            }
        } else if(peer()->at<float>(0xec)>F(0xec)) {
            B(0x104)=static_cast<unsigned char>(-B(0x104));goto flight_frame_turn;
        }
        select_sequence(9);
        set_sequence_frame(static_cast<unsigned short>(S(0x730)));
        goto flight_frame_done;
flight_frame_turn:
        F(0xf4)=-F(0xf4);select_sequence(9);
        set_sequence_frame(static_cast<unsigned short>(S(0x730)));
    }
flight_frame_done:
    if(sequence_index_13e==4 || sequence_index_13e==5)release_flight(10);
    if(sequence_index_13e==6 || sequence_index_13e==7)release_flight(11);
    if(sequence_index_13e==8) {
        S(0x730)=frame_index_140;
        if(B(0x104)==1) {
            if(peer()->at<float>(0xec)<F(0xec)) {
                B(0x104)=255;F(0xf4)=-F(0xf4);
                select_sequence(11);
                set_sequence_frame(static_cast<unsigned short>(S(0x730)));return;
            }
            select_sequence(11);
            set_sequence_frame(static_cast<unsigned short>(S(0x730)));return;
        }
        if(peer()->at<float>(0xec)>F(0xec)) {
            B(0x104)=static_cast<unsigned char>(-B(0x104));F(0xf4)=-F(0xf4);
            select_sequence(11);
            set_sequence_frame(static_cast<unsigned short>(S(0x730)));return;
        }
        select_sequence(11);
        set_sequence_frame(static_cast<unsigned short>(S(0x730)));return;
    }
    return;
}

case 300:
    landing();
    if(directional(0))return;
    if(B(0x47e)) {
        F(0xf4)=static_cast<float>(F(0xf4)-0.5);
        if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    }
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==3){event(27);B(0x47e)=0;}
    return;
case 301:
    landing();if(directional(0))return;
    if(B(0x47e)) {
        F(0xf4)=static_cast<float>(F(0xf4)-0.5);
        if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    }
    if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3) {
            if(B(0x750)==1) {
                next_sequence_block();int direction=B(0x104);
                effect(62,static_cast<float>(F(0xec)-static_cast<double>(15*static_cast<signed char>(direction))),
                       static_cast<float>(F(0xf0)+130.0),direction,1);return;
            }
            float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);
        }
        if(!frame_timer_142 && frame_index_140==5){event(27);B(0x47e)=0;}
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1){float p[3]={0.0f,0.0f,1.0f};spawn_offset(848,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==2){event(27);B(0x47e)=0;}
    }
    return;
case 302:
    landing();if(directional(1))return;
    if(!I(0x6bc))B(0x750)=0;
    F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4) {
            if(B(0x750)==1) {
                next_sequence_block();int direction=B(0x104);
                effect(62,static_cast<float>(F(0xec)-static_cast<double>(65*static_cast<signed char>(direction))),
                       static_cast<float>(F(0xf0)+165.0),direction,1);return;
            }
            F(0xf4)=10.0f;
        }
        if(!frame_timer_142 && frame_index_140==6)event(29);
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1)F(0xf4)=13.0f;
        if(!frame_timer_142 && frame_index_140==3) {
            event(29);float p[3];p[2]=0.0f;p[1]=12.0f;ring820_ground(p,77);
        }
    }
    return;
case 303:
    landing();if(directional(0))return;
    if(C(0x47e)>0) {
        F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.6f));
        if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    }
    if(advance())set_action_and_finalize(2);
    if(!frame_timer_142 && frame_index_140==3)event(27);
    return;
case 304:
    landing();if(directional(1))return;
    if(!I(0x6bc))B(0x750)=0;
    if(advance())set_action_and_finalize(2);
    if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e) {
        if(F(0xf4)>0.0f){F(0xf4)=static_cast<float>(F(0xf4)-1.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
        if(!frame_timer_142 && frame_index_140==3) {
            if(B(0x750)==1) {
                next_sequence_block();effect(62,F(0xec),static_cast<float>(F(0xf0)+50.0),B(0x104),1);return;
            }
            F(0xf4)=12.0f;event(29);
        }
    }
    if(sequence_index_13e==1) {
        if(!frame_timer_142) {
            if(frame_index_140==2){F(0xf4)=15.0f;event(29);}
            if(!frame_timer_142 && frame_index_140==4)F(0xf4)=0.0f;
        }
        if(frame_index_140>=2 && frame_index_140<=7) {
            F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<10.0f)F(0xf4)=10.0f;
            if(time_counter_144%10==0){float p[3];p[2]=0.0f;p[1]=10.0f;ring820_ground(p,77);}
        }
        if(frame_index_140>=8) {
            F(0xf4)=static_cast<float>(F(0xf4)-static_cast<double>(0.3f));
            if(F(0xf4)<0.0f)F(0xf4)=0.0f;
        }
    }
    return;
case 305:
    landing();if(directional(1))return;
    if(frame_index_140>=5){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5)event(29);
    return;
case 306:
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=patchouli_surface(this);zero_motion();return;}
    if(I(0x180)){if(++S(0x730)>=2 && C(0x184)>0){I(0x180)=0;S(0x730)=0;}}
    if(advance())set_action_and_finalize(9);
    if(!frame_timer_142) {
        if(frame_index_140==1)event(27);
        if(!frame_timer_142 && frame_index_140==2){float p[3]={0.0f,0.0f,6.0f};spawn_offset(848,63,53.0,p,3);}
    }
    return;
case 307:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())) {
        if(frame_index_140>=12){set_action_and_finalize(10);F(0xf0)=patchouli_surface(this);zero_motion();return;}
        F(0xf8)=0.0f;
    }
    if(advance())set_action_and_finalize(9);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(sequence_index_13e || frame_timer_142)return;
    if(frame_index_140==5){dispatch_character_wave_handle(18);float p[3]={-10.0f,20.0f,5.0f};spawn_offset(848,96,127.0,p,3);}
    if(!frame_timer_142 && frame_index_140==12)F(0x100)=0.6f;
    return;
case 308:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=patchouli_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3 && B(0x750)==1) {
            next_sequence_block();int direction=B(0x104);
            effect(62,static_cast<float>(20*static_cast<signed char>(direction)+static_cast<double>(F(0xec))),
                   static_cast<float>(F(0xf0)+105.0),direction,1);return;
        }
        if(frame_index_140==3) {
            event(28);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;
            float p[3]={0.0f,0.0f,7.0f};spawn_offset(848,40,47.0,p,3);
        }
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1) {
        event(28);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;
        float p[3]={0.0f,1.0f,7.0f};spawn_offset(848,40,47.0,p,3);
    }
    return;
case 309:
    if(!I(0x6bc))B(0x750)=0;
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed())){set_action_and_finalize(10);F(0xf0)=patchouli_surface(this);zero_motion();return;}
    if(advance())set_action_and_finalize(9);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        dispatch_character_wave_handle(18);F(0xf4)=static_cast<float>(F(0xf4)*0.5);F(0xf8)=3.0f;F(0x100)=0.0f;
        float p[3]={-85.0f,20.0f,12.0f};spawn_offset(848,34,122.0,p,3);
    }
    if(sequence_index_13e==1 && time_counter_144>=30){next_sequence_block();F(0x100)=0.5f;}
    return;
case 310:
    if(I(0x180)){if(++S(0x730)>5){I(0x180)=0;S(0x730)=0;}}
    if(sequence_index_13e==1) {
        if(!time_counter_144)F(0xf4)=15.0f;
        if(time_counter_144%8==0)event(27);
        if(I(0x180)){if(++S(0x730)>5){I(0x180)=0;S(0x730)=0;}}
        if(time_counter_144>30){next_sequence_block();F(0xf8)=6.0f;F(0xf4)=static_cast<float>(F(0xf4)*0.5);}
    }
    if(sequence_index_13e==2) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){F(0xf8)=0.0f;F(0xf0)=patchouli_surface(this);set_action_and_finalize(9);return;}
    }
    if(advance())set_action_and_finalize(9);
    return;
case 320:
    landing();if(directional(0))return;
    F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    if(I(0x180)){if(++S(0x730)>=5 && C(0x184)>0){I(0x180)=0;S(0x730)=0;}}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==4){event(28);F(0xf4)=12.5f;B(0x47e)=0;}
        if(!frame_timer_142 && frame_index_140==5){float p[3]={0.0f,0.0f,9.0f};spawn_offset(848,122,133.0,p,3);}
    }
    return;
case 321:
    landing();if(directional(1))return;
    if(frame_index_140>6){F(0xf4)=static_cast<float>(F(0xf4)+0.5);if(F(0xf4)>0.0f)F(0xf4)=0.0f;}
    else {F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==6) {
            event(29);float p[3]={0.0f,0.0f,10.0f};spawn_offset(848,101,111.0,p,3);
            p[2]=0.0f;p[1]=12.0f;ring820_ground(p,101);
        }
        if(!frame_timer_142 && frame_index_140==7){F(0xf4)=static_cast<float>(F(0xf4)-10.0);B(0x47e)=0;}
    }
    return;
case 322:
    landing();if(directional(1))return;
    if(frame_index_140>5){F(0xf4)=static_cast<float>(F(0xf4)-3.0);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==4){F(0xf4)=15.0f;float p[3]={0.0f,0.0f,0.0f};spawn_offset(819,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==5){event(29);B(0x47e)=0;}
    }
    return;
case 400:
    landing();if(!I(0x6c0))B(0x750)=0;
    ground_fan_tick(63,117.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        if(B(0x750)==1){charge_effect(-12,100.0);return;}
        aim(-10.0f,10.0f);S(0x730)=1;counter(200,40);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1){aim(-10.0f,10.0f);S(0x730)=1;counter(200,40);}
    return;
case 401:
    landing();if(!I(0x6c0))B(0x750)=0;
    ground_fan_tick(100,136.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4 && B(0x750)==1){charge_effect(-24,102.0);return;}
        if(frame_index_140==5){aim(-50.0f,-30.0f);S(0x730)=1;counter(200,40);}
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==2){aim(-50.0f,-30.0f);S(0x730)=1;counter(200,40);}
    return;
case 402:
    landing();if(!I(0x6c0))B(0x750)=0;
    ground_fan_tick(103,63.0);
    if(advance())set_action_and_finalize(2);
    if(entry(1)){set_action_and_finalize(2);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        if(B(0x750)==1){charge_effect(55,132.0);return;}
        aim(-10.0f,10.0f);S(0x730)=1;counter(200,40);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1){aim(-10.0f,10.0f);S(0x730)=1;counter(200,40);}
    return;
case 404:
    air_fan_motion();air_fan_tick(70,115.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4) {
            if(B(0x750)==1){charge_effect(40,190.0);return;}
            aim(-10.0f,10.0f);S(0x730)=1;counter(200,40);
        }
        if(!frame_timer_142 && frame_index_140==13)F(0x100)=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1){aim(-10.0f,10.0f);S(0x730)=1;counter(200,40);}
        if(!frame_timer_142 && frame_index_140==10)F(0x100)=0.6f;
    }
    return;
case 406:
    air_fan_motion();air_fan_tick(50,70.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e) {
        if(!frame_timer_142) {
            if(frame_index_140==4 && B(0x750)==1){charge_effect(40,190.0);return;}
            if(frame_index_140==5){aim(40.0f,60.0f);S(0x730)=1;counter(200,40);}
        }
        if(!frame_timer_142 && frame_index_140==11)F(0x100)=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==2){aim(40.0f,60.0f);S(0x730)=1;counter(200,40);}
        if(!frame_timer_142 && frame_index_140==8)F(0x100)=0.6f;
    }
    return;
case 407:
    landing();if(!I(0x6c0))B(0x750)=0;
    if(S(0x730)>0) {
        S(0x730)=0;I(0x180)=1;
        if(!sequence_index_13e) {
            float p[3];
            for(float n=0.0f;n<4.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(n*40.0-60.0);p[1]=15.0f;p[2]=2.0f;spawn_offset(800,63,117.0,p,3);
            }
        } else {
            float p[3];
            for(float n=0.0f;n<7.0f;n=static_cast<float>(n+1.0)) {
                p[0]=static_cast<float>(n*25.0-75.0);p[1]=15.0f;p[2]=2.0f;spawn_offset(800,63,117.0,p,3);
            }
        }
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        if(B(0x750)==1){charge_effect(-12,100.0);return;}
        aim(-10.0f,10.0f);S(0x730)=1;dispatch_character_wave_handle(0);counter(200,40);phase_counter(30);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1) {
        aim(-10.0f,10.0f);S(0x730)=1;dispatch_character_wave_handle(0);counter(200,40);phase_counter(30);
    }
    return;
case 408:
    if(directional(1))return;
    landing();
    if(frame_index_140>=7){F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;}
    if(I(0x180)){if(++S(0x730)>=5 && C(0x184)>0){I(0x180)=0;S(0x730)=0;}}
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==4){event(28);float p[3]={-30.0f,20.0f,8.0f};spawn_offset(848,96,127.0,p,3);}
    return;
case 409:
    air_fan_motion();burst800(70,115.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4) {
            if(B(0x750)==1){charge_effect(40,190.0);return;}
            aim(-10.0f,10.0f);S(0x730)=1;counter(200,40);dispatch_character_wave_handle(0);
        }
        if(!frame_timer_142 && frame_index_140==13)F(0x100)=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1){aim(-10.0f,10.0f);S(0x730)=1;counter(200,40);dispatch_character_wave_handle(0);}
        if(!frame_timer_142 && frame_index_140==10)F(0x100)=0.6f;
    }
    return;
case 410:
    landing();if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5) {
        I(0x180)=1;phase_counter(50);dispatch_character_wave_handle(1);
        // Packet initializations precede counter in the native call path.
        float p[3];p[1]=5.0f;p[2]=0.0f;counter(200,48);
        for(int angle=0;angle<315;angle+=45){p[0]=static_cast<float>(angle);spawn_offset(801,100,140.0,p,3);}
        p[2]=2.0f;spawn_offset(801,100,140.0,p,3);
    }
    return;
case 411:
    landing();if(!I(0x6c4))B(0x750)=0;
    pair801_tick(63,117.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        if(B(0x750)==1){charge_effect(-12,100.0);return;}
        S(0x730)=1;counter(200,48);
    }
    if(sequence_index_13e==1 && !frame_timer_142 && frame_index_140==1){S(0x730)=1;counter(200,48);}
    return;
case 412:
    landing();if(!I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(2);
    if(!sequence_index_13e && frame_index_140==5 && !frame_timer_142) {
        dispatch_character_wave_handle(7);float p[3]={10.0f,15.0f,9.0f};
        I(0x180)=1;counter(200,48);phase_counter(50);spawn_offset(801,100,56.0,p,3);
    }
    return;
case 414:
    if(sequence_index_13e==1)landing();
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<1) {
        select_sequence(1);B(0x47f)=0;F(0xf0)=patchouli_surface(this);zero_motion();return;
    }
    if(sequence_index_13e<2 && !I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(frame_timer_142)return;
    if(frame_index_140==5){I(0x180)=1;counter(200,48);phase_counter(50);dispatch_character_wave_handle(1);circle801();}
    if(!frame_timer_142 && frame_index_140==15)F(0x100)=0.6f;
    return;
case 415:
    if(sequence_index_13e==2)landing();
    F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<2) {
        select_sequence(2);B(0x47f)=0;F(0xf0)=patchouli_surface(this);zero_motion();return;
    }
    if(!I(0x6c4))B(0x750)=0;
    pair801_tick(70,115.0);
    if(advance())set_action_and_finalize(0);
    if(entry(1) || entry(2)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4) {
            if(B(0x750)==1){charge_effect(-12,100.0);return;}
            S(0x730)=1;counter(200,48);
        }
        if(!frame_timer_142 && frame_index_140==13)F(0x100)=0.6f;
    }
    if(sequence_index_13e==1 && !frame_timer_142) {
        if(frame_index_140==1){S(0x730)=1;counter(200,48);}
        if(!frame_timer_142 && frame_index_140==10)F(0x100)=0.6f;
    }
    return;
case 416:
    if(sequence_index_13e==1)landing();
    if(!sequence_index_13e) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){select_sequence(1);zero_motion();F(0xf0)=patchouli_surface(this);return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
        dispatch_character_wave_handle(1);F(0xf4)=-4.0f;F(0xf8)=8.0f;F(0x100)=0.5f;
        I(0x180)=1;counter(200,48);phase_counter(50);
        float p[3];p[1]=20.0f;p[2]=5.0f;
        for(int angle=30;angle<105;angle+=15){p[0]=static_cast<float>(angle);spawn_offset(801,40,45.0,p,3);}
        p[2]=2.0f;spawn_offset(801,40,45.0,p,3);
    }
    return;
case 418:
    if(directional(1))return;
    landing();F(0xf4)=static_cast<float>(F(0xf4)-0.5);if(F(0xf4)<0.0f)F(0xf4)=0.0f;
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142) {
        if(frame_index_140==4){float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==5){event(29);B(0x47e)=0;}
    }
    return;
case 500:ground810(0x6c0,15.0f);return;
case 501:ground810(0x6c4,25.0f);return;
case 502:air810(60.0f);return;
case 503:air810(45.0f);return;
case 505:
    B(0x17c)=5;landing();if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e==1) {
        if(time_counter_144%3==0) {
            float p[3]={static_cast<float>(patchouli_sine(static_cast<float>(10*time_counter_144))*20.0+10.0),18.0f,0.0f};
            spawn_offset(811,66,117.0,p,3);
        }
        if(time_counter_144>=10*(C(0x609)+4) || (time_counter_144>=20 && !B(0x750))){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){counter(200,60);phase_counter(50);I(0x180)=1;dispatch_character_wave_handle(11);}
    return;
case 506:
    B(0x17c)=5;landing();if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==1) {
        if(time_counter_144%3==0) {
            float p[3]={static_cast<float>(patchouli_sine(static_cast<float>(10*time_counter_144))*20.0-45.0),20.0f,0.0f};
            spawn_offset(811,66,117.0,p,3);
        }
        if(time_counter_144>=10*(C(0x609)+4) || (time_counter_144>=20 && !B(0x750))){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){counter(200,60);phase_counter(50);I(0x180)=1;dispatch_character_wave_handle(11);}
    return;
case 520:
    landing();B(0x17c)=1;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=5)return;
    {
        float p[3]={0.0f,30.0f,4.0f};
        int direction=B(0x104);float y=patchouli_surface(peer());
        spawn(815,peer()->at<float>(0xec),y,direction,1,p,3);
        if(C(0x605)>=3) {
            p[1]=40.0f;p[2]=4.0f;direction=B(0x104);y=patchouli_surface(peer());
            spawn(815,static_cast<float>(peer()->at<float>(0xec)-100.0),y,direction,1,p,3);
        }
        if(C(0x605)>=4) {
            p[1]=40.0f;p[2]=4.0f;direction=B(0x104);y=patchouli_surface(peer());
            spawn(815,static_cast<float>(peer()->at<float>(0xec)+100.0),y,direction,1,p,3);
        }
        counter(200,60);phase_counter(50);
    }
    return;
case 521:
    landing();B(0x17c)=1;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(sequence_index_13e || frame_timer_142 || frame_index_140!=5)return;
    {
        float p[3]={0.0f,30.0f,4.0f};
        int direction=B(0x104);float y=patchouli_surface(peer());
        spawn(815,peer()->at<float>(0xec),y,direction,1,p,3);
        if(C(0x605)>=3) {
            p[1]=40.0f;p[2]=4.0f;direction=B(0x104);y=patchouli_surface(peer());
            spawn(815,static_cast<float>(peer()->at<float>(0xec)+100.0),y,direction,1,p,3);
        }
        if(C(0x605)>=4) {
            p[1]=40.0f;p[2]=4.0f;direction=B(0x104);y=patchouli_surface(peer());
            spawn(815,static_cast<float>(peer()->at<float>(0xec)-100.0),y,direction,1,p,3);
        }
        counter(200,60);phase_counter(50);
    }
    return;
case 525:
    landing();B(0x17c)=6;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        float p[3]={-10.0f,5.0f,0.0f};if(C(0x60a)>=4)p[2]=3.0f;
        spawn_offset(816,62,118.0,p,3);counter(200,60);phase_counter(50);dispatch_character_wave_handle(12);I(0x180)=1;
    }
    return;
case 526:
    landing();B(0x17c)=6;
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        float p[3]={-30.0f,5.0f,0.0f};if(C(0x60a)>=4)p[2]=3.0f;
        spawn_offset(816,62,118.0,p,3);counter(200,60);phase_counter(50);dispatch_character_wave_handle(12);I(0x180)=1;
    }
    return;
case 540:rising820(0x6c0,200.0,7.0f,14.5f);return;
case 541:rising820(0x6c4,500.0,12.5f,18.5f);return;
case 545:
    landing();B(0x17c)=7;if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e==1) {
        if(B(0x750) && (I(0x6bc) || I(0x6c4))){select_sequence(3);return;}
        if(time_counter_144>=120 || !B(0x750)){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(821,100,110.0,p,3);
        counter(200,60);phase_counter(50);dispatch_character_wave_handle(14);I(0x180)=1;
    }
    return;
case 546:
    landing();B(0x17c)=7;if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e==1) {
        if(B(0x750) && (I(0x6bc) || I(0x6c0))){select_sequence(3);return;}
        if(time_counter_144>=120 || !B(0x750)){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(3)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4) {
        float p[3]={0.0f,0.0f,0.0f};spawn_offset(821,100,110.0,p,3);
        counter(200,60);phase_counter(50);dispatch_character_wave_handle(14);I(0x180)=1;
    }
    return;
case 560:
    landing();B(0x17c)=3;if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e<=1) {
        if(S(0x730)==1) {
            float limit=5.0f;
            if(C(0x607)<=3)limit=4.0f;
            if(C(0x607)<=2)limit=3.0f;
            if(C(0x607)<=0)limit=2.0f;
            if(S(0x732)%7==0 && limit>=static_cast<double>(F(0x744))) {
                dispatch_character_wave_handle(S(0x732)%7);
                if(F(0x744)==0.0f) {
                    float p[3]={0.0f,40.0f,0.0f};orbit825(p);
                } else {
                    float p[3]={static_cast<float>(F(0x744)*7.0),40.0f,0.0f};orbit825(p);
                    p[0]=static_cast<float>(F(0x744)*-7.0);orbit825(p);
                }
                F(0x744)=static_cast<float>(F(0x744)+1.0);
            }
        }
        ++S(0x732);
        if((!B(0x750) && time_counter_144>=10) || time_counter_144>=90){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2) {
        phase_counter(50);counter(200,60);I(0x180)=1;S(0x730)=1;
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==1){S(0x730)=2;dispatch_character_wave_handle(8);}
    return;

case 561:
    landing();B(0x17c)=3;if(!I(0x6c4))B(0x750)=0;
    if(sequence_index_13e<=1) {
        if(S(0x730)==1) {
            float limit=5.0f;
            if(C(0x607)<=3)limit=4.0f;
            if(C(0x607)<=2)limit=3.0f;
            if(C(0x607)<=0)limit=2.0f;
            if(S(0x732)%7==0 && limit>=static_cast<double>(F(0x744))) {
                dispatch_character_wave_handle(S(0x732)%7);
                if(F(0x744)==0.0f) {
                    float p[3]={0.0f,40.0f,0.0f};orbit825(p);
                } else {
                    float p[3]={static_cast<float>(F(0x744)*7.0),40.0f,0.0f};orbit825(p);
                    p[0]=static_cast<float>(F(0x744)*-7.0);orbit825(p);
                }
                F(0x744)=static_cast<float>(F(0x744)+1.0);
            }
        }
        ++S(0x732);
        if((!B(0x750) && time_counter_144>=10) || time_counter_144>=90){next_sequence_block();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2) {
        phase_counter(50);counter(200,60);I(0x180)=1;S(0x730)=1;
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==1){S(0x730)=2;dispatch_character_wave_handle(8);}
    return;
case 565:
    landing();B(0x17c)=8;if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        dispatch_character_wave_handle(16);aim(-45.0f,45.0f);
        float p[3]={F(0x744),15.0f,0.0f};spawn_offset(826,70,110.0,p,3);
        counter(200,60);phase_counter(50);I(0x180)=1;
    }
    return;
case 566:
    landing();B(0x17c)=8;if(!I(0x6c4))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        dispatch_character_wave_handle(16);aim(-45.0f,45.0f);
        float p[3]={static_cast<float>(F(0x744)+45.0),15.0f,0.0f};spawn_offset(826,70,110.0,p,3);
        p[0]=static_cast<float>(F(0x744)-45.0);p[1]=15.0f;p[2]=0.0f;spawn_offset(826,70,110.0,p,3);
        counter(200,60);phase_counter(50);I(0x180)=1;
    }
    return;
case 567:
    if(sequence_index_13e==1)landing();
    B(0x17c)=8;F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<1) {
        select_sequence(1);B(0x47f)=0;F(0xf0)=patchouli_surface(this);zero_motion();return;
    }
    if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==5) {
            dispatch_character_wave_handle(16);aim(-45.0f,45.0f);
            float p[3]={F(0x744),15.0f,0.0f};spawn_offset(826,60,110.0,p,3);
            counter(200,60);phase_counter(50);I(0x180)=1;
        }
        if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;
    }
    return;
case 568:
    if(sequence_index_13e==1)landing();
    B(0x17c)=8;F(0xf8)-=F(0x100);
    if(static_cast<unsigned char>(crossed()) && sequence_index_13e<1) {
        select_sequence(1);B(0x47f)=0;F(0xf0)=patchouli_surface(this);zero_motion();return;
    }
    if(!I(0x6c0))B(0x750)=0;
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(9);return;}
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==5) {
            dispatch_character_wave_handle(16);aim(-45.0f,45.0f);
            float p[3]={static_cast<float>(F(0x744)+45.0),15.0f,0.0f};spawn_offset(826,60,110.0,p,3);
            p[0]=static_cast<float>(F(0x744)-45.0);p[1]=15.0f;p[2]=0.0f;spawn_offset(826,60,110.0,p,3);
            counter(200,60);phase_counter(50);I(0x180)=1;
        }
        if(!frame_timer_142 && frame_index_140==9)F(0x100)=0.5f;
    }
    return;
case 570:
    landing();B(0x17c)=13;if(!I(0x6c0))B(0x750)=0;
    if(!sequence_index_13e && S(0x730)>0) {
        if(S(0x730)%4==1 && S(0x730)<35) {
            float p[3];p[1]=40.0f;p[2]=0.0f;p[0]=static_cast<float>(static_cast<float>(patchouli_random(30))+15.0);
            spawn(827,static_cast<float>(static_cast<float>(patchouli_random(300))+F(0xec)-150.0),
                  static_cast<float>(static_cast<float>(patchouli_random(75))+F(0xf0)+150.0),B(0x104),1,p,3);
        }
        ++S(0x730);
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        phase_counter(50);counter(200,60);I(0x180)=1;S(0x730)=1;dispatch_character_wave_handle(8);
    }
    return;
case 571:
    landing();B(0x17c)=13;if(!I(0x6c4))B(0x750)=0;
    if(!sequence_index_13e && S(0x730)>0) {
        if(S(0x730)%4==1 && S(0x730)<35) {
            float p[3];p[1]=40.0f;p[2]=0.0f;p[0]=static_cast<float>(static_cast<float>(patchouli_random(30))+15.0);
            spawn(827,static_cast<float>(static_cast<float>(patchouli_random(300))+F(0xec)-150.0),
                  static_cast<float>(static_cast<float>(patchouli_random(75))+F(0xf0)+150.0),B(0x104),1,p,3);
        }
        ++S(0x730);
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==5) {
        phase_counter(50);counter(200,60);I(0x180)=1;S(0x730)=1;dispatch_character_wave_handle(8);
    }
    return;
case 580:
    landing();B(0x17c)=4;
    if(S(0x730)==1) {
        float limit=4.0f;
        if(C(0x608)==4)limit=7.0f;
        if(C(0x608)<=3)limit=6.0f;
        if(C(0x608)<=2)limit=5.0f;
        if(C(0x608)<=0)limit=4.0f;
        if(S(0x732)%5==0 && limit>=static_cast<double>(F(0x744))) {
            float p[4]={0.0f,0.0f,0.0f,static_cast<float>(F(0x744)*4.0)};
            spawn(830,
                  static_cast<float>((patchouli_cosine(static_cast<float>(-F(0x744)*140.0))*100.0+200.0)*facing()+F(0xec)),
                  static_cast<float>(patchouli_sine(static_cast<float>(-F(0x744)*140.0))*25.0),B(0x104),1,p,4);
            F(0x744)=static_cast<float>(F(0x744)+1.0);
        }
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
        phase_counter(50);counter(200,60);I(0x180)=1;S(0x730)=1;dispatch_character_wave_handle(9);
    }
    return;
case 581:
    landing();B(0x17c)=4;
    if(S(0x730)==1) {
        // Native leaves the scratch cap undefined for skill levels greater than4.
        float limit;
        if(C(0x608)==4)limit=7.0f;
        if(C(0x608)<=3)limit=6.0f;
        if(C(0x608)<=2)limit=5.0f;
        if(C(0x608)<=0)limit=4.0f;
        if(S(0x732)%5==0 && limit>=static_cast<double>(F(0x744))) {
            float p[4]={0.0f,0.0f,0.0f,static_cast<float>(F(0x744)*4.0)};
            spawn(830,
                  static_cast<float>((patchouli_cosine(static_cast<float>(-F(0x744)*140.0))*100.0+450.0)*facing()+F(0xec)),
                  static_cast<float>(patchouli_sine(static_cast<float>(-F(0x744)*140.0))*25.0),B(0x104),1,p,4);
            F(0x744)=static_cast<float>(F(0x744)+1.0);
        }
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){set_action_and_finalize(0);return;}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
        phase_counter(50);counter(200,60);I(0x180)=1;S(0x730)=1;dispatch_character_wave_handle(9);
    }
    return;
case 585:
case 586:
    landing();B(0x17c)=9;if(!I(0x6c0))B(0x750)=0;
    if(sequence_index_13e==1 && time_counter_144>=40){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==3) {
        layout(5.0f);dispatch_character_wave_handle(17);float p[3];p[0]=-95.0f;p[1]=100.0f;
        if(C(0x60d)<4) {
            p[2]=0.0f;spawn_offset(831,-100,-320.0,p,3);
            int direction=static_cast<unsigned char>(-B(0x104));
            float y=static_cast<float>(F(0xf0)-320.0);
            float x=static_cast<float>(100*facing()+static_cast<double>(F(0xec)));
            spawn(831,x,y,direction,1,p,3);
        } else {
            p[2]=3.0f;spawn_offset(831,-110,-480.0,p,3);
            int direction=static_cast<unsigned char>(-B(0x104));
            float y=static_cast<float>(F(0xf0)-480.0);
            float x=static_cast<float>(110*facing()+static_cast<double>(F(0xec)));
            spawn(831,x,y,direction,1,p,3);
        }
        counter(200,60);phase_counter(50);I(0x180)=1;
    }
    return;
case 599:
    if(S(0x730)>0 && frame_index_140<7 && S(0x730)<12) {
        S(0x734)=static_cast<short>(patchouli_random_u32()%35u);
        float p[3];p[0]=static_cast<float>(-20-S(0x734));
        p[1]=static_cast<float>(static_cast<short>(patchouli_random_u32()%5u+10));p[2]=0.0f;
        int direction=B(0x104);
        float x=static_cast<float>(20*static_cast<signed char>(direction)*(S(0x730)+1)+static_cast<double>(F(0xec)));
        spawn(807,x,F(0xf0),direction,1,p,3);
        p[0]=static_cast<float>(patchouli_random_u32()%360u);p[1]=0.0f;p[2]=1.0f;
        direction=B(0x104);x=static_cast<float>(20*static_cast<signed char>(direction)*(S(0x730)+1)+static_cast<double>(F(0xec)));
        spawn(801,x,F(0xf0),direction,1,p,3);
        if(S(0x730)==1){dispatch_character_wave_handle(0);counter(200,60);}
        ++S(0x730);
    }
    if(advance())set_action_and_finalize(0);
    if(!frame_timer_142 && frame_index_140==5)S(0x730)=1;
    return;
case 600:
    landing();texture(5,2);
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3)spell_flash(-33,170.0,3);
        if(!frame_timer_142) {
            if(frame_index_140==4){float p[3]={0.0f,0.0f,0.0f};spawn_offset(890,66,67.0,p,3);}
            if(!frame_timer_142 && frame_index_140==5) {
                float p[3]={0.0f,0.0f,0.0f};spawn_offset(850,-55,230.0,p,3);dispatch_character_wave_handle(50);
            }
        }
    }
    return;
case 601:
    landing();
    if(S(0x730)>0) {
        ++S(0x730);F(0x73c)=static_cast<float>(F(0x73c)+0.5);
        if(S(0x730)%2==1 && S(0x732)<20) {
            float p[3]={static_cast<float>(patchouli_sine(static_cast<float>(10*S(0x730)))*F(0x73c)),25.0f,1.0f};
            spawn_offset(851,63,117.0,p,3);
            p[0]=static_cast<float>(patchouli_sine(static_cast<float>(10*S(0x730)))*-F(0x73c));p[1]=25.0f;p[2]=1.0f;
            spawn_offset(851,63,117.0,p,3);
            p[2]=2.0f;spawn_offset(851,63,117.0,p,3);
            dispatch_character_wave_handle(2);++S(0x732);
        }
    }
    if(sequence_index_13e==1 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1))time_counter_144=0;
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3)spell_flash(33,188.0,2);
        if(!frame_timer_142 && frame_index_140==4)S(0x730)=1;
    }
    return;
case 602:
    if(!sequence_index_13e || sequence_index_13e==2)landing();
    if(entry(0))spell_flash(30,95.0,2);
    if(sequence_index_13e==1) {
        if(I(0x180)){if(++S(0x730)>=8){I(0x180)=0;S(0x730)=0;}}
        if(!frame_index_140 && !frame_timer_142)dispatch_character_wave_handle(52);
        F(0xf8)-=F(0x100);
        if(time_counter_144>=180){set_action_and_finalize(9);F(0x100)=0.5f;return;}
        if(time_counter_144%5==0){float p[3]={0.0f,0.0f,3.0f};spawn_offset(852,0,100.0,p,3);}
        if(static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=patchouli_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {
        time_counter_144=0;F(0xf4)=2.0f;F(0xf8)=3.5f;F(0x100)=0.05f;
        float p[3]={0.0f,0.0f,0.0f};
        spawn(852,F(0xec),static_cast<float>(F(0xf0)+100.0),B(0x104),-1,p,3);
        p[0]=30.0f;p[1]=0.0f;p[2]=1.0f;orbit852(p,150.0);
        p[0]=-90.0f;p[1]=0.0f;p[2]=1.0f;orbit852(p,150.0);
        p[0]=150.0f;p[1]=0.0f;p[2]=1.0f;orbit852(p,150.0);
        for(float n=0.0f;n<4.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(n*90.0+45.0);p[1]=100.0f;p[2]=2.0f;orbit852(p,100.0);
        }
    }
    return;
case 603:
    landing();texture(5,2);
    if((sequence_index_13e==1 && time_counter_144>120) || (sequence_index_13e==2 && time_counter_144>60)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1))time_counter_144=0;
    if(!sequence_index_13e && frame_index_140==6 && !frame_timer_142) {
        S(0x48a)=40;event(23);
        int direction=B(0x104);
        effect(115,static_cast<float>(20*static_cast<signed char>(direction)+static_cast<double>(F(0xec))),
               static_cast<float>(F(0xf0)+240.0),direction,1);
        float p[3]={0.0f,0.0f,0.0f};
        // Native request adds20 in world X, not20*facing.
        spawn(853,static_cast<float>(F(0xec)+20.0),static_cast<float>(F(0xf0)+240.0),B(0x104),1,p,3);
        sequence_window(0,5,60);secondary_cycle();dispatch_character_wave_handle(53);
    }
    return;
case 604:
    landing();texture(5,2);
    if((sequence_index_13e==1 && time_counter_144>=90) || (sequence_index_13e==2 && time_counter_144>=90)){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2)spell_flash(-10,85.0,4);
    if(entry(1)) {
        float p[3]={0.0f,0.0f,0.0f};spawn(854,F(0xec),F(0xf0),B(0x104),-1,p,3);
        p[1]=0.3f;p[2]=8.0f;spawn(854,F(0xec),F(0xf0),B(0x104),-1,p,3);
        dispatch_character_wave_handle(55);time_counter_144=0;
    }
    return;
case 605:
    landing();texture(5,2);
    if(sequence_index_13e==1 && time_counter_144>40){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)) {
        S(0x7a4)=1200;dispatch_character_wave_handle(59);float p[3];
        for(float n=0.0f;n<5.0f;n=static_cast<float>(n+1.0)) {
            p[0]=static_cast<float>(72.0*n);p[1]=0.0f;p[2]=n;spawn_offset(855,0,100.0,p,3);
        }
    }
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(-51,75.0,5);
    return;
case 606:
    landing();texture(5,2);
    if(sequence_index_13e==1 && time_counter_144>=32){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==4)spell_flash(30,95.0,3);
    if(entry(1)){float p[3]={0.0f,0.0f,0.0f};spawn_offset(856,0,210.0,p,3);dispatch_character_wave_handle(12);}
    return;
case 607:
    landing();texture(5,2);
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==4)spell_flash(30,100.0,3);
        if(!frame_timer_142 && frame_index_140==9) {
            float p[3]={0.0f,0.0f,0.0f};
            spawn(857,F(0xec),static_cast<float>(F(0xf0)+210.0),B(0x104),-1,p,3);
            p[0]=180.0f;p[2]=1.0f;
            spawn(857,F(0xec),static_cast<float>(F(0xf0)+210.0),B(0x104),-1,p,3);
            dispatch_character_wave_handle(57);
        }
    }
    return;
case 610:
    landing();texture(5,2);
    if(sequence_index_13e==1 && time_counter_144>=48){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(entry(1)){float p[3]={0.0f,0.0f,0.0f};spawn(860,F(0xec),0.0f,B(0x104),-1,p,3);dispatch_character_wave_handle(58);}
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==2)spell_flash(13,86.0,3);
    return;
case 651:
    if(sequence_index_13e==3)landing();
    else {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){zero_motion();F(0xf0)=patchouli_surface(this);select_sequence(3);return;}
    }
    if(S(0x730)>0) {
        ++S(0x730);F(0x73c)=static_cast<float>(F(0x73c)+0.5);
        if(S(0x730)%2==1 && S(0x732)<20) {
            float p[3]={static_cast<float>(patchouli_sine(static_cast<float>(10*S(0x730)))*F(0x73c)),25.0f,1.0f};
            spawn_offset(851,71,115.0,p,3);
            p[0]=static_cast<float>(patchouli_sine(static_cast<float>(10*S(0x730)))*-F(0x73c));p[1]=25.0f;p[2]=1.0f;
            spawn_offset(851,71,115.0,p,3);
            p[2]=2.0f;spawn_offset(851,71,115.0,p,3);
            dispatch_character_wave_handle(2);++S(0x732);
        }
    }
    if(sequence_index_13e==1 && time_counter_144>=60){next_sequence_block();return;}
    if(advance())set_action_and_finalize(0);
    if(!time_counter_144) {
        if(entry(1))time_counter_144=0;
        if(entry(3)){set_action_and_finalize(9);return;}
    }
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3)spell_flash(41,192.0,2);
        if(!frame_timer_142 && frame_index_140==4)S(0x730)=1;
    }
    if(sequence_index_13e==2 && !frame_timer_142 && frame_index_140==2)F(0x100)=0.5f;
    return;
case 695:
    landing();if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7) {
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
    if(B(0x47e)) {
        F(0xf4)=static_cast<float>(F(0xf4)-0.5);
        if(F(0xf4)<0.0f){F(0xf4)=0.0f;B(0x47e)=0;}
    }
    if(advance())set_action_and_finalize(0);
    if(!sequence_index_13e && !frame_timer_142) {
        if(frame_index_140==3){float p[3]={0.0f,0.0f,0.0f};spawn_offset(848,0,0.0,p,3);}
        if(!frame_timer_142 && frame_index_140==5){event(27);B(0x47e)=0;}
    }
    return;
case 710:
    if(!sequence_index_13e || sequence_index_13e==2)landing();
    if(sequence_index_13e==1) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())){next_sequence_block();F(0xf0)=patchouli_surface(this);zero_motion();return;}
    }
    if(advance())set_action_and_finalize(700);
    if(entry(1)) {
        dispatch_character_wave_handle(11);F(0x73c)=-90.0f;
        float dx=static_cast<float>((peer()->at<float>(0xec)-F(0xec))*static_cast<double>(facing()));
        float dy=peer()->at<float>(0xf0)-F(0xf0);
        F(0x73c)=static_cast<float>(-patchouli_atan(dy,dx)-90.0);
        F(0x744)=static_cast<float>(F(0x73c)+180.0);
        F(0xf4)=static_cast<float>(3.0-static_cast<float>(patchouli_random(6)));
        F(0xf8)=static_cast<float>(static_cast<float>(patchouli_random(10))*static_cast<double>(0.1f)+5.5);
        F(0x100)=0.05f;
    }
    return;
case 720:
    if(sequence_index_13e==1 && F(0xf8)<4.0f){next_sequence_block();return;}
    if(sequence_index_13e==1 || sequence_index_13e==2)F(0xf8)-=F(0x100);
    if(sequence_index_13e==3) {
        F(0xf4)=static_cast<float>(F(0xf4)*static_cast<double>(0.98f));
        F(0xf8)=static_cast<float>(static_cast<double>(0.98f)*F(0xf8));
    }
    if(advance())set_action_and_finalize(700);
    if(entry(1)) {
        F(0xf4)=static_cast<float>(3.0-static_cast<float>(patchouli_random(6)));
        F(0xf8)=static_cast<float>(static_cast<float>(patchouli_random(10))*static_cast<double>(0.1f)+5.5);
        F(0x100)=0.1f;
    }
    return;
case 721:
    if(sequence_index_13e<=1) {
        if(entry(0)) {
            if(F(0xec)>=640.0f)F(0x74c)=static_cast<float>(580.0-static_cast<float>(patchouli_random(360)));
            else F(0x74c)=static_cast<float>(static_cast<float>(patchouli_random(360))+700.0);
            F(0x748)=static_cast<float>(static_cast<float>(patchouli_random(260))+60.0);
            if(F(0x74c)>=static_cast<double>(F(0xec)))B(0x104)=1;else B(0x104)=255;
        }
        F(0xf4)=static_cast<float>((F(0x74c)-F(0xec))*static_cast<double>(0.02f)*facing());
        F(0xf8)=static_cast<float>(static_cast<double>(0.02f)*(F(0x748)-F(0xf0)));
        if(F(0xf4)>6.0f)F(0xf4)=6.0f;
        if(F(0xf8)>6.0f)F(0xf8)=6.0f;
        float dy=F(0x748)-F(0xf0);double vertical_square=patchouli_square(dy);
        float dx=F(0x74c)-F(0xec);
        if(patchouli_square(dx)+vertical_square<=900.0){next_sequence_block();return;}
    }
    if(sequence_index_13e==2) {
        F(0xf4)=static_cast<float>(F(0xf4)*static_cast<double>(0.98f));
        F(0xf8)=static_cast<float>(static_cast<double>(0.98f)*F(0xf8));
    }
    if(advance()){set_action_and_finalize(720);select_sequence(3);}
    return;
case 730:
    if(sequence_index_13e==1 && time_counter_144>=32){next_sequence_block();return;}
    if(sequence_index_13e==1 || sequence_index_13e==2) {
        F(0xf8)-=F(0x100);if(F(0xf8)<0.0f)F(0xf8)=0.0f;
        F(0xf4)=static_cast<float>((640.0-F(0xec))*static_cast<double>(-0.1f));
        if(F(0xf4)>10.0f)F(0xf4)=10.0f;
        if(F(0xf4)<-10.0f)F(0xf4)=-10.0f;
    }
    if(advance())set_action_and_finalize(0);
    if(entry(1)){B(0x104)=255;F(0xf8)=15.0f;F(0x100)=0.5f;}
    return;
case 770:
    if(advance())set_action_and_finalize(700);
    if(!sequence_index_13e && !frame_timer_142 && frame_index_140==7) {
        B(0x655)=1;finalize(-1);texture(2,-1);copy_health();
        S(0x76c)=0;S(0x76a)=1;S(0x766)=0;S(0x768)=0;S(0x764)=0;event(23);
    }
    return;
case 795:
    if(!sequence_index_13e) {
        F(0xf8)=static_cast<float>(F(0xf8)-static_cast<double>(0.3f));
        if(static_cast<unsigned char>(crossed())) {
            select_sequence(1);F(0xf0)=patchouli_surface(this);zero_motion();event(30);return;
        }
    }
    if(advance())set_action_and_finalize(700);
    return;
case 797:
    if(!sequence_index_13e) {
        F(0xf8)-=F(0x100);
        if(F(0xf0)<=150.0f) {
            dispatch_character_wave_handle(6);select_sequence(1);zero_motion();F(0x100)=0.2f;F(0xf8)=4.0f;
            float p[3];p[2]=0.0f;p[1]=12.0f;ring820_surface(p);return;
        }
    }
    if(sequence_index_13e==1 || sequence_index_13e==2) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {
            select_sequence(3);F(0xec)=480.0f;F(0xf0)=patchouli_surface(this);event(30);zero_motion();return;
        }
    }
    if(advance())set_action_and_finalize(0);
    return;
case 798:
    if(!sequence_index_13e) {
        F(0xf8)-=F(0x100);
        if(F(0xf0)<=150.0f) {
            dispatch_character_wave_handle(6);select_sequence(1);zero_motion();F(0x100)=0.2f;F(0xf8)=4.0f;
            float p[3];p[2]=0.0f;p[1]=12.0f;ring820_surface(p);return;
        }
    }
    if(sequence_index_13e==1 || sequence_index_13e==2) {
        F(0xf8)-=F(0x100);
        if(static_cast<unsigned char>(crossed())) {
            event(30);select_sequence(3);F(0xec)=800.0f;F(0xf0)=patchouli_surface(this);zero_motion();return;
        }
    }
    if(advance())set_action_and_finalize(700);
    return;

    default:common_update();return;
    }
}
#undef B
#undef C
#undef S
#undef U
#undef I
#undef F
}
