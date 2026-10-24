#include "SakuyaControlMode.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define I(o) FIELD(int,o)
#define S(o) FIELD(short,o)
#define C(o) FIELD(signed char,o)
#define F(o) FIELD(float,o)
#define PEER_VALUE (*reinterpret_cast<short *>(FIELD(unsigned char *,0x170)+0x174))
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define READY (S(0x13C)==700 || S(0x13C)==0)
#define FRONT (*reinterpret_cast<SakuyaControlSequenceView *>(reinterpret_cast<unsigned char *>(this)+0x55C)->at(0))
void SakuyaControlModeView::update_control_mode()
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
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && PEER_VALUE>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (R(100)<=50) { set_action(710); S(0x76A)=2; return; }
            set_action(711);
            F(0x780)=static_cast<float>(R(6))-3.0;
            F(0x784)=static_cast<float>(R(3))+12.0;
            S(0x76A)=2; F(0x788)=0.5f; return;
        }
        if (S(0x76A)==2 && PEER_VALUE>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (C(0x104)==1) {
                if (F(0xEC)<180.0f) {
                    set_action(705); F(0x778)=6.0f;
                    S(0x768)=static_cast<short>(selector_random_roll(60)+60); return;
                }
                if (R(100)>50) {
                    set_action(705); F(0x778)=6.0f;
                    S(0x768)=static_cast<short>(selector_random_roll(60)+90); return;
                } else {
                    set_action(706); F(0x77C)=-6.0f;
                    S(0x768)=static_cast<short>(selector_random_roll(60)+90); return;
                }
            } else {
                if (F(0xEC)>1100.0f) {
                    set_action(705); F(0x778)=6.0f;
                    S(0x768)=static_cast<short>(selector_random_roll(60)+60); return;
                }
                if (R(100)>50) {
                    set_action(705); F(0x778)=6.0f;
                    S(0x768)=static_cast<short>(selector_random_roll(60)+90); return;
                } else {
                    set_action(706); F(0x77C)=-6.0f;
                    S(0x768)=static_cast<short>(selector_random_roll(60)+90); return;
                }
            }
        }

        if (S(0x13C)==705 || S(0x13C)==706) {
            if (C(0x104)==1 && F(0xEC)>1220.0f && F(0xF4)>0.0f) C(0x104)=-1;
            if (C(0x104)==-1 && F(0xEC)<60.0 && F(0xF4)>0.0f) C(0x104)=1;
            if (S(0x768)<=0) { S(0x76A)=1; set_action(700); return; }
        }
        return;
    case 4: case 5: case 6: case 7:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) {
            set_action(720); S(0x76A)=2; face_opponent_and_flip_horizontal_velocity(); return;
        }
        if (S(0x76A)==2 && READY) {
            set_action(721);
            F(0x780)=static_cast<float>(R(6))-3.0;
            F(0x784)=static_cast<float>(R(3))+12.0;
            F(0x788)=0.5f; S(0x76A)=3;
            face_opponent_and_flip_horizontal_velocity(); return;
        }
        if (S(0x76A)==3 && READY) {
            switch (g_match_identifier) {
            case 3: S(0x768)=10; S(0x76A)=4; break;
            case 2: S(0x768)=15; S(0x76A)=4; break;
            case 1: S(0x768)=20; S(0x76A)=4; break;
            case 0: S(0x768)=30; S(0x76A)=4; break;
            default: S(0x76A)=4; break;
            }
        }
        if (S(0x76A)==4 && S(0x768)<=0 && READY) {
            set_action(722); face_opponent_and_flip_horizontal_velocity(); S(0x76A)=1;
        }
        return;
    case 8: case 9: case 10: case 11:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) {
            set_action(730); S(0x76A)=2; face_opponent_and_flip_horizontal_velocity(); return;
        }
        if (S(0x76A)==2 && READY) {
            switch (g_match_identifier) {
            case 3: S(0x768)=10; break;
            case 2: S(0x768)=15; break;
            case 1: S(0x768)=20; break;
            case 0: S(0x768)=30; break;
            }
            S(0x76A)=3;
        }
        if (S(0x76A)==3 && S(0x768)<=0 && READY) {
            set_action(722); face_opponent_and_flip_horizontal_velocity(); S(0x76A)=1;
        }
        return;
    case 248: case 249: case 250: case 251:
    case 252: case 253: case 254: case 255:
        if (S(0x13C)==700) set_action(0);
        update_cpu_action_policy(); return;
    case 12: case 13: case 14: case 15:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) {
            set_action(740); S(0x76A)=2; face_opponent_and_flip_horizontal_velocity(); return;
        }
        if (S(0x76A)==2 && READY) {
            switch (g_match_identifier) {
            case 3: S(0x768)=10; break;
            case 2: S(0x768)=15; break;
            case 1: S(0x768)=20; break;
            case 0: S(0x768)=30; break;
            }
            S(0x76A)=3;
        }
        if (S(0x76A)==3 && S(0x768)<=0 && READY) {
            set_action(722); face_opponent_and_flip_horizontal_velocity(); S(0x76A)=1;
        }
        return;
    }
}
#undef FRONT
#undef READY
#undef R
#undef PEER_VALUE
#undef F
#undef C
#undef S
#undef I
#undef FIELD
}
