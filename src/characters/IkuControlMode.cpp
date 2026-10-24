#include "IkuControlMode.hpp"
#include <math.h>
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define I(o) FIELD(int,o)
#define S(o) FIELD(short,o)
#define C(o) FIELD(signed char,o)
#define B(o) FIELD(unsigned char,o)
#define F(o) FIELD(float,o)
#define PEER(o) (*reinterpret_cast<float *>(FIELD(unsigned char *,0x170)+(o)))
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define READY (S(0x13C)==700 || S(0x13C)==0)
#define FRONT (*reinterpret_cast<IkuControlSequenceView *>(reinterpret_cast<unsigned char *>(this)+0x55C)->at(0))
void IkuControlModeView::update_control_mode()
{
    --S(0x768);
    I(0x724)=0; I(0x728)=0;
    I(0x6B4)=0; I(0x6B8)=0; I(0x6BC)=0; I(0x6C0)=0;
    I(0x6C4)=0; I(0x6C8)=0; I(0x6CC)=0; I(0x6D0)=0;
    if (S(0x13C)>49 && S(0x13C)<150) {
        S(0x76C)=0; S(0x76A)=0; S(0x766)=0; S(0x768)=0; S(0x764)=0;
    }
    if (S(0x13C)<=199) { S(0x76C)=0; S(0x764)=0; }
    if (C(0x55A)<1) return;
    switch (FRONT) {
    case 0: case 1: case 2: case 3:
        if (S(0x76A)==0 && READY) {
            set_action(770); S(0x76A)=1; return;
        }
        if (S(0x76A)==1 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            set_action(710); S(0x76A)=2; return;
        }
        if (S(0x76A)==2 && READY) {
            if (F(0xEC)<=640.0f) {
                F(0x780)=static_cast<float>(R(8))*static_cast<float>(C(0x104));
                F(0x784)=static_cast<float>(R(4))+8.0;
            } else {
                F(0x780)=-static_cast<float>(R(8))*static_cast<float>(C(0x104));
                F(0x784)=static_cast<float>(R(4))+8.0;
            }
            F(0x788)=0.25f; set_action(701); S(0x76A)=1; return;
        }
        return;
    case 4: case 5: case 6: case 7:
        if (S(0x76A)==0 && READY) {
            set_action(770); S(0x76A)=1; return;
        }
        if (S(0x76A)==1 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            S(0x76C)=static_cast<short>(selector_random_roll(3));
            if (g_match_identifier==0 || g_match_identifier==1) S(0x76C)=0;
            if (S(0x76C)==0) {
                F(0x780)=2.0-static_cast<float>(R(8));
                F(0x784)=static_cast<float>(R(4))+8.0;
                F(0x788)=0.25f; set_action(701); S(0x76A)=2; return;
            }
            if (S(0x76C)==1) {
                float const vy=static_cast<float>(static_cast<float>(R(4))+8.0);
                F(0x784)=vy;
                F(0x788)=0.25f;
                float const delta=PEER(0xEC)-F(0xEC);
                float const distance=static_cast<float>(fabs(static_cast<double>(delta)));
                F(0x780)=distance/((vy*2)*4.0);
                F(0x780)=static_cast<float>(static_cast<unsigned>(selector_random_roll(6)-3))+F(0x780);
                if (F(0x780)>=10.0f) F(0x780)=10.0f;
                if (F(0x780)<=-10.0f) F(0x780)=-10.0f;
                set_action(701); S(0x76A)=2; return;
            }
            if (S(0x76C)==2) {
                if (F(0xEC)<=640.0f) {
                    F(0x780)=static_cast<float>(R(8))*static_cast<float>(C(0x104));
                    F(0x784)=static_cast<float>(R(4))+8.0;
                } else {
                    F(0x780)=-static_cast<float>(R(8))*static_cast<float>(C(0x104));
                    F(0x784)=static_cast<float>(R(4))+8.0;
                }
                F(0x788)=0.25f; set_action(701); S(0x76A)=2; return;
            }
        }
        if (S(0x76A)==2 && READY) { set_action(720); S(0x76A)=1; }
        return;
    case 8: case 9: case 10: case 11:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) set_action(730);
        return;
    case 248: case 249: case 250: case 251:
    case 252: case 253: case 254: case 255:
        if (S(0x13C)==700) set_action(0);
        update_cpu_action_policy();
        return;
    case 12: case 13: case 14: case 15: {
        if (S(0x76A)==0) {
            if (READY) { S(0x76A)=1; set_action(740); return; }
            S(0x4A8)=2; S(0x4AC)=2;
        }
        if (S(0x76A)!=1) return;
        // The native switch supplies these only for identifiers 0..3.
        int period, burst_period;
        float count;
        switch (g_match_identifier) {
        case 3: count=12.0f; burst_period=120; period=240; break;
        case 2: count=12.0f; burst_period=130; period=300; break;
        case 1: count=10.0f; burst_period=140; period=300; break;
        case 0: count=10.0f; burst_period=150; period=300; break;
        }
        ++I(0x7A4);
        float params[3];
        if (I(0x7A4)%period==0 && g_match_identifier!=0) {
            dispatch_character_wave_handle(0);
            float const phase=static_cast<float>(R(30));
            for (float n=0.0f;n<count;n+=1.0) {
                params[0]=static_cast<float>(n*(360.0/count)+phase);
                params[1]=4.0f; params[2]=0.0f;
                spawn_owned_object_via_manager(930,F(0xEC),
                    static_cast<float>(F(0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
            }
            if (g_match_identifier==3) {
                for (float n=0.0f;n<count;n+=1.0) {
                    params[0]=static_cast<float>(n*(360.0/count)+phase+180.0/count);
                    params[1]=6.0f; params[2]=0.0f;
                    spawn_owned_object_via_manager(930,F(0xEC),
                        static_cast<float>(F(0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
                }
            }
        }
        if (I(0x7A4)%burst_period==60) {
            params[0]=0.0f; params[1]=0.0f; params[2]=4.0f;
            I(0x7A8)=1; I(0x7AC)=0;
            spawn_owned_object_via_manager(930,F(0xEC),
                static_cast<float>(F(0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
        }
        if (I(0x7A8)>0) {
            float limit;
            switch (g_match_identifier) {
            case 3: limit=8.0f; break;
            case 2: limit=7.0f; break;
            case 1: limit=6.0f; break;
            case 0: limit=4.0f; break;
            }
            if (I(0x7AC)%4==0) {
                params[0]=static_cast<float>(R(360));
                params[1]=static_cast<float>(R(480))+20.0;
                params[2]=2.0f;
                spawn_owned_object_via_manager(930,
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-params[0])*params[1]*static_cast<float>(C(0x104))+F(0xEC)),
                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-params[0])*params[1]+F(0xF0)+100.0),
                    B(0x104),1,reinterpret_cast<int>(params),3);
                ++I(0x7A8);
            }
            if (static_cast<float>(I(0x7A8)-1)>limit) I(0x7A8)=0;
            ++I(0x7AC);
        }
        return;
    }
    }
}
#undef FRONT
#undef READY
#undef R
#undef PEER
#undef F
#undef B
#undef C
#undef S
#undef I
#undef FIELD
}
