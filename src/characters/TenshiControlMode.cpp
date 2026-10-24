#include "TenshiControlMode.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define I(o) FIELD(int,o)
#define S(o) FIELD(short,o)
#define C(o) FIELD(signed char,o)
#define B(o) FIELD(unsigned char,o)
#define F(o) FIELD(float,o)
#define PEER_VALUE (*reinterpret_cast<short *>(FIELD(unsigned char *,0x170)+0x174))
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define READY (S(0x13C)==700 || S(0x13C)==0)
#define FRONT (*reinterpret_cast<TenshiControlSequenceView *>(reinterpret_cast<unsigned char *>(this)+0x55C)->at(0))
void TenshiControlModeView::update_control_mode()
{
    --S(0x768);
    I(0x724)=0; I(0x728)=0;
    I(0x6B4)=0; I(0x6B8)=0; I(0x6BC)=0; I(0x6C0)=0;
    I(0x6C4)=0; I(0x6C8)=0; I(0x6CC)=0; I(0x6D0)=0;
    if (S(0x13C)>49 && S(0x13C)<150) {
        S(0x76C)=0; S(0x76A)=0; S(0x766)=0; S(0x768)=0; S(0x764)=0;
    }
    if (S(0x13C)<=199) { S(0x76C)=0; S(0x764)=0; }
    if (PEER_VALUE<=0) return;
    if (S(0x13C)>=50 && S(0x13C)<=199) { S(0x76A)=0; S(0x76C)=0; }
    if (C(0x55A)<1) return;
    switch (FRONT) {
    case 0: case 1: case 2: case 3:
        if (S(0x76A)==0 && S(0x13C)==700) {
            set_action(770); S(0x76A)=1; return;
        }
        if (PEER_VALUE<=0) return;
        if (S(0x76A)==1 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            S(0x76A)=2; set_action(710); return;
        }
        if (S(0x76A)==2 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (F(0xEC)<=640.0f) {
                F(0x780)=static_cast<float>(R(12))*static_cast<float>(C(0x104));
                F(0x784)=static_cast<float>(R(4))+12.0;
            } else {
                F(0x780)=-static_cast<float>(R(12))*static_cast<float>(C(0x104));
                F(0x784)=static_cast<float>(R(4))+12.0;
            }
            F(0x788)=0.35f; set_action(701); S(0x76A)=1; return;
        }
        return;
    case 4: case 5: case 6: case 7:
        if (S(0x76A)==0 && S(0x13C)==700) {
            set_action(770); S(0x76A)=1; return;
        }
        if (PEER_VALUE<=0) return;
        if (S(0x76A)==1 && (S(0x13C)==0 || S(0x13C)==700)) set_action(720);
        return;
    case 8: case 9: case 10: case 11: {
        if (S(0x76A)==0 && S(0x13C)==700) {
            set_action(770); S(0x76A)=1; return;
        }
        if (PEER_VALUE<=0) return;
        if (S(0x76A)!=1) return;
        // The native switch leaves the period uninitialized outside 0..3.
        int period;
        switch (g_match_identifier) {
        case 3: period=50; break;
        case 2: period=60; break;
        case 1: period=80; break;
        case 0: period=120; break;
        }
        float params[3];
        if (I(0x83C)%period==0) {
            params[0]=static_cast<float>(R(40))+70.0;
            params[1]=6.0f; params[2]=9.0f;
            spawn_owned_object_via_manager(920,
                static_cast<float>(static_cast<float>(R(1000))+120.0),900.0f,
                B(0x104),1,reinterpret_cast<int>(params),3);
        }
        if (S(0x13C)==0 || S(0x13C)==700) { set_action(731); return; }
        ++I(0x83C); return;
    }
    case 12: case 13: case 14: case 15:
        if (S(0x76A)==0 && S(0x13C)==700) {
            set_action(770); S(0x76A)=1; return;
        }
        if (PEER_VALUE<=0) return;
        if (S(0x76A)==1 && READY) { S(0x76A)=2; set_action(740); return; }
        if (S(0x76A)==2 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            F(0x780)=static_cast<float>(R(8))+5.0;
            F(0x784)=static_cast<float>(R(4))+12.0;
            F(0x788)=0.5f; set_action(701); S(0x76A)=1; return;
        }
        return;
    case 248: case 249: case 250: case 251:
    case 252: case 253: case 254: case 255:
        if (S(0x13C)==700) set_action(0);
        update_cpu_action_policy(); return;
    case 16: case 17: case 18: case 19: {
        if (READY) { set_action(771); return; }
        float params[3];
        if (S(0x13C)==750 && S(0x13E)==1) {
            if (S(0x736)==1 && S(0x174)<=7500) {
                F(0x74C)=2.0f;
                params[0]=0.0f; params[1]=0.0f; params[2]=18.0f;
                S(0x76A)=1; S(0x736)=2;
                S(0x4A8)=180; S(0x4AC)=180; S(0x768)=180;
                spawn_owned_object_via_manager(940,
                    F(0xEC)+static_cast<float>(C(0x104)*30),
                    static_cast<float>(F(0xF0)+120.0),B(0x104),1,reinterpret_cast<int>(params),3);
            }
            if (S(0x736)==2 && S(0x174)<=5000) {
                F(0x74C)=2.0f;
                params[0]=0.0f; params[1]=0.0f; params[2]=18.0f;
                S(0x76A)=1; S(0x736)=3;
                S(0x4A8)=180; S(0x4AC)=180; S(0x768)=180;
                spawn_owned_object_via_manager(940,
                    F(0xEC)+static_cast<float>(C(0x104)*30),
                    static_cast<float>(F(0xF0)+120.0),B(0x104),1,reinterpret_cast<int>(params),3);
            }
            if (S(0x736)==3 && S(0x174)<=2500) {
                F(0x74C)=2.0f;
                params[0]=0.0f; params[1]=0.0f; params[2]=18.0f;
                S(0x76A)=1; S(0x736)=4;
                S(0x4A8)=180; S(0x4AC)=180; S(0x768)=180;
                spawn_owned_object_via_manager(940,
                    F(0xEC)+static_cast<float>(C(0x104)*30),
                    static_cast<float>(F(0xF0)+120.0),B(0x104),1,reinterpret_cast<int>(params),3);
            }
        }
        if (S(0x76A)==0) { S(0x738)=0; S(0x768)=240; }
        if (S(0x76A)==1) {
            S(0x738)=1;
            if (S(0x174)>=7500) {
                if (S(0x768)<=0) { S(0x768)=120; S(0x76A)=2; S(0x732)=0; S(0x738)=2; }
            } else if (S(0x174)>=5000) {
                if (S(0x768)<=0) {
                    if (S(0x76C)==0) {
                        S(0x76A)=2; S(0x738)=2; S(0x768)=120; S(0x76C)=1; S(0x732)=0; return;
                    }
                    if (S(0x76C)==1) {
                        S(0x76A)=3; S(0x76C)=0; S(0x738)=3; S(0x732)=0; S(0x768)=60; return;
                    }
                }
            } else if (S(0x174)>=2500) {
                if (S(0x768)<=0) {
                    if (S(0x76E)==0) {
                        S(0x768)=180; S(0x76A)=4; S(0x76E)=1; S(0x76C)=1; S(0x732)=0; return;
                    }
                    if (S(0x76C)%3==0) {
                        S(0x768)=180; S(0x76A)=4; ++S(0x76C); S(0x732)=0; return;
                    }
                    unsigned const roll=R(100);
                    ++S(0x76C); S(0x768)=240; S(0x732)=0;
                    if (roll<50) { S(0x76A)=2; S(0x738)=2; return; }
                    S(0x76A)=3; S(0x738)=3; return;
                }
            } else if (S(0x768)<=0) {
                S(0x732)=0; S(0x768)=60;
                if (g_match_identifier==0) S(0x768)=120;
                S(0x76A)=7; S(0x738)=4; return;
            }
        }
        if (S(0x76A)==2) {
            S(0x738)=2;
            if (S(0x768)<=0) { S(0x732)=0; S(0x738)=0; S(0x76A)=6; S(0x768)=60; return; }
        }
        if (S(0x76A)==3) {
            S(0x738)=3;
            if (S(0x768)<=0) { S(0x732)=0; S(0x738)=0; S(0x76A)=6; S(0x768)=60; return; }
        }
        if (S(0x76A)==4) {
            S(0x738)=4;
            if (S(0x768)<=0) { S(0x768)=180; S(0x732)=0; S(0x738)=5; S(0x76A)=5; return; }
        }
        if (S(0x76A)==5) {
            S(0x738)=5;
            if (S(0x768)<=0) { S(0x732)=0; S(0x738)=0; S(0x76A)=6; S(0x768)=60; return; }
        }
        if (S(0x76A)==6) {
            S(0x738)=0;
            if (S(0x768)<=0) { S(0x732)=0; S(0x738)=1; S(0x76A)=1; S(0x768)=120; return; }
        }
        if (S(0x76A)==7) {
            S(0x738)=4;
            if (S(0x768)<=0) { S(0x732)=0; S(0x738)=6; S(0x76A)=8; S(0x768)=60; return; }
        }
        if (S(0x76A)==8) {
            S(0x738)=5;
            if (S(0x768)<=0) { S(0x732)=0; S(0x738)=0; S(0x76A)=1; S(0x768)=30; return; }
        }
        return;
    }
    }
}
#undef FRONT
#undef READY
#undef R
#undef PEER_VALUE
#undef F
#undef B
#undef C
#undef S
#undef I
#undef FIELD
}
