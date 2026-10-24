#include "AyaControlMode.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define I(o) FIELD(int,o)
#define S(o) FIELD(short,o)
#define C(o) FIELD(signed char,o)
#define F(o) FIELD(float,o)
#define PEER(t,o) (*reinterpret_cast<t *>(FIELD(unsigned char *,0x170)+(o)))
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define READY (S(0x13C)==700 || S(0x13C)==0)
#define FRONT (*reinterpret_cast<AyaControlSequenceView *>(reinterpret_cast<unsigned char *>(this)+0x55C)->at(0))
void AyaControlModeView::update_control_mode()
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
        if (S(0x76A)==1 && PEER(short,0x174)>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            F(0x780)=-static_cast<float>(R(20));
            F(0x784)=static_cast<float>(R(4))+10.0;
            F(0x788)=0.5f; set_action(701); S(0x76A)=2; return;
        }
        if (S(0x76A)==2) {
            if (PEER(short,0x174)>0) {
                if (READY) { set_action(710); S(0x76A)=1; return; }
            } else S(0x76A)=1;
        }
        return;
    case 4: case 5: case 6: case 7:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if ((S(0x76A)==1 || S(0x76A)==3) && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (R(100)<=50 && S(0x76A)==1) {
                set_action(721); S(0x76A)=3; return;
            } else {
                F(0x780)=((PEER(float,0xEC)-F(0xEC))/80.0)*static_cast<float>(C(0x104));
                F(0x784)=16.0f; F(0x788)=0.4f;
                set_action(701); S(0x76A)=2; return;
            }
        } else if (S(0x76A)==2 && READY) { set_action(720); S(0x76A)=1; return; }
        return;
    case 8: case 9: case 10: case 11:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) {
            face_opponent_and_flip_horizontal_velocity(); S(0x76A)=2; set_action(730); return;
        }
        if (S(0x76A)==2 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            S(0x76C)=static_cast<short>(selector_random_roll(3));
            if (S(0x76C)==0) {
                if ((F(0xEC)>=640.0f && C(0x104)==1) || (F(0xEC)<=640.0f && C(0x104)==-1)) {
                    F(0x780)=-static_cast<float>(R(8))-10.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                    F(0x788)=0.5f; set_action(703); S(0x76A)=1; return;
                }
                F(0x784)=static_cast<float>(R(4))+8.0;
                F(0x788)=0.5f;
                F(0x780)=static_cast<float>(R(8))+10.0;
                set_action(702); S(0x76A)=1; return;
            }
            if (S(0x76C)==1) {
                F(0x784)=static_cast<float>(R(4))+8.0;
                F(0x788)=0.5f;
                F(0x780)=static_cast<float>(R(8))+10.0;
                set_action(702); S(0x76A)=1; return;
            }
            if (S(0x76C)==2) {
                if (F(0xEC)<=640.0f) {
                    C(0x104)=1;
                    F(0x780)=static_cast<float>(R(12))+8.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                } else {
                    C(0x104)=-1;
                    F(0x780)=static_cast<float>(R(12))+8.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                }
                F(0x788)=0.5f; set_action(702); S(0x76A)=1; return;
            }
        }
        return;
    case 12: case 13: case 14: case 15:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) { S(0x76A)=2; set_action(740); return; }
        return;
    case 248: case 249: case 250: case 251:
    case 252: case 253: case 254: case 255:
        if (S(0x13C)==700) set_action(0);
        update_cpu_action_policy(); return;
    case 16: case 17: case 18: case 19:
        if (S(0x13C)!=750) I(0x728)=750;
        return;
    }
}
#undef FRONT
#undef READY
#undef R
#undef PEER
#undef F
#undef C
#undef S
#undef I
#undef FIELD
}
