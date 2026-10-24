#include "SuikaControlMode.hpp"
#include <stdlib.h>
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define I(o) FIELD(int,o)
#define S(o) FIELD(short,o)
#define C(o) FIELD(signed char,o)
#define F(o) FIELD(float,o)
#define PEER(t,o) (*reinterpret_cast<t *>(FIELD(unsigned char *,0x170)+(o)))
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define READY (S(0x13C)==700 || S(0x13C)==0)
#define FRONT (*reinterpret_cast<SuikaControlSequenceView *>(reinterpret_cast<unsigned char *>(this)+0x55C)->at(0))
void SuikaControlModeView::update_control_mode()
{
    --S(0x768);
    I(0x724)=0; I(0x728)=0;
    I(0x6B4)=0; I(0x6B8)=0; I(0x6BC)=0; I(0x6C0)=0;
    I(0x6C4)=0; I(0x6C8)=0; I(0x6CC)=0; I(0x6D0)=0;
    if (S(0x13C)>49 && S(0x13C)<150) {
        S(0x76C)=0; S(0x76A)=0; S(0x766)=0; S(0x768)=0; S(0x764)=0;
    }
    if (S(0x13C)<=199) { S(0x76C)=0; S(0x764)=0; }
    if (S(0x13C)>=50 && S(0x13C)<=149 && FIELD(unsigned char,0x113)!=255) FIELD(unsigned char,0x113)=255;
    if (C(0x55A)<1) return;
    switch (FRONT) {
    case 0: case 1: case 2: case 3:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && PEER(short,0x174)>0 && READY) {
            face_opponent_and_flip_horizontal_velocity(); set_action(710); S(0x76A)=2; return;
        }
        if (S(0x76A)==2 && PEER(short,0x174)>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (F(0xEC)<320.0f) {
                if (C(0x104)==1) {
                    F(0x780)=static_cast<float>(R(5))+5.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                } else {
                    F(0x780)=-5.0-static_cast<float>(R(5));
                    F(0x784)=static_cast<float>(R(4))+8.0;
                }
            } else if (F(0xEC)>960.0) {
                if (C(0x104)==1) {
                    F(0x780)=-5.0-static_cast<float>(R(5));
                    F(0x784)=static_cast<float>(R(4))+8.0;
                } else {
                    F(0x780)=static_cast<float>(R(5))+5.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                }
            } else {
                F(0x780)=5.0-static_cast<float>(R(10));
                F(0x784)=static_cast<float>(R(4))+8.0;
                F(0x788)=0.5f; set_action(701); S(0x76A)=3; return;
            }
            F(0x788)=0.5f; set_action(701); S(0x76A)=3;
        }
        if (S(0x76A)==3 && PEER(short,0x174)>0 && READY) {
            face_opponent_and_flip_horizontal_velocity(); set_action(711); S(0x76A)=4; return;
        }
        if (S(0x76A)==4 && PEER(short,0x174)>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (F(0xEC)<320.0f) {
                if (C(0x104)==1) {
                    F(0x780)=static_cast<float>(R(5))+5.0;
                    F(0x784)=static_cast<float>(R(4))+12.0;
                } else {
                    F(0x780)=-5.0-static_cast<float>(R(5));
                    F(0x784)=static_cast<float>(R(4))+12.0;
                }
            } else if (F(0xEC)>960.0) {
                if (C(0x104)==1) {
                    F(0x780)=-5.0-static_cast<float>(R(5));
                    F(0x784)=static_cast<float>(R(4))+12.0;
                } else {
                    F(0x780)=static_cast<float>(R(5))+5.0;
                    F(0x784)=static_cast<float>(R(4))+12.0;
                }
            } else {
                F(0x780)=5.0-static_cast<float>(R(10));
                F(0x784)=static_cast<float>(R(4))+12.0;
            }
            F(0x788)=0.5f; set_action(701); S(0x76A)=1; return;
        }
        return;
    case 4: case 5: case 6: case 7:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && PEER(short,0x174)>0 && READY) {
            face_opponent_and_flip_horizontal_velocity(); set_action(720); S(0x76A)=2; return;
        }
        if (S(0x76A)==2 && PEER(short,0x174)>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (F(0xEC)<320.0f) {
                if (C(0x104)==1) {
                    F(0x780)=static_cast<float>(R(5))+10.0;
                    F(0x784)=static_cast<float>(R(4))+10.0;
                } else {
                    F(0x780)=-10.0-static_cast<float>(R(5));
                    F(0x784)=static_cast<float>(R(4))+10.0;
                }
            } else if (F(0xEC)>960.0) {
                if (C(0x104)==1) {
                    F(0x780)=-10.0-static_cast<float>(R(5));
                    F(0x784)=static_cast<float>(R(4))+10.0;
                } else {
                    F(0x780)=static_cast<float>(R(5))+10.0;
                    F(0x784)=static_cast<float>(R(4))+10.0;
                }
            } else {
                F(0x780)=10.0-static_cast<float>(R(20));
                F(0x784)=static_cast<float>(R(4))+12.0;
            }
            F(0x788)=0.5f; set_action(701); S(0x76A)=1; return;
        }
        return;
    case 8: case 9: case 10: case 11:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) {
            face_opponent_and_flip_horizontal_velocity(); set_action(730); S(0x76A)=2; return;
        }
        if (S(0x76A)==2 && PEER(short,0x174)>0 && S(0x13C)==730 && S(0x13E)==1 && S(0x768)<=0) {
            face_opponent_and_flip_horizontal_velocity();
            if (R(100)<50) {
                set_sequence(2); S(0x76A)=3; S(0x768)=static_cast<short>(selector_random_roll(60)+60); return;
            } else {
                set_sequence(3); I(0x180)=0; C(0x184)=1; S(0x76A)=4; return;
            }
        }
        if (S(0x76A)==3 && S(0x768)<=0 && S(0x13E)==2) {
            face_opponent_and_flip_horizontal_velocity(); set_sequence(1); F(0xF4)=0.0f; S(0x76A)=5;
            if (R(100)<=20) {
                set_sequence(3); I(0x180)=0; C(0x184)=1; S(0x76A)=4;
            }
            return;
        }
        if (S(0x76A)==4 && S(0x13C)==730 && S(0x13E)==1) {
            S(0x76A)=5;
            if (R(100)<20) {
                set_sequence(2); S(0x76A)=3; S(0x768)=static_cast<short>(selector_random_roll(60)+60); return;
            }
        }
        if (S(0x76A)==5) {
            face_opponent_and_flip_horizontal_velocity();
            if (PEER(float,0xF0)>=200.0 && abs(static_cast<int>(F(0xEC)-PEER(float,0xEC)<=350.0)) && R(100)<=80) {
                S(0x76A)=2; set_sequence(9);
            } else {
                S(0x76A)=2; set_sequence(7);
            }
            zero_velocity_acceleration(); return;
        }
        return;
    case 12: case 13: case 14: case 15:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) { S(0x76A)=1; set_action(740); return; }
        return;
    case 248: case 249: case 250: case 251:
    case 252: case 253: case 254: case 255:
        if (S(0x13C)==700) set_action(0);
        update_cpu_action_policy(); return;
    case 16: case 17: case 18: case 19:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) { S(0x76A)=2; set_action(750); return; }
        if (S(0x76A)==2 && PEER(short,0x174)>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (F(0xEC)<320.0f) {
                if (C(0x104)==1) {
                    F(0x780)=static_cast<float>(R(5))+3.0;
                    F(0x784)=static_cast<float>(R(4))+10.0;
                } else {
                    F(0x780)=-3.0-static_cast<float>(R(5));
                    F(0x784)=static_cast<float>(R(4))+10.0;
                }
            } else if (F(0xEC)>960.0) {
                if (C(0x104)==1) {
                    F(0x780)=-3.0-static_cast<float>(R(5));
                    F(0x784)=static_cast<float>(R(4))+10.0;
                } else {
                    F(0x780)=static_cast<float>(R(5))+3.0;
                    F(0x784)=static_cast<float>(R(4))+10.0;
                }
            } else {
                F(0x780)=6.0-static_cast<float>(R(12));
                F(0x784)=static_cast<float>(R(4))+12.0;
            }
            F(0x788)=0.5f; set_action(701); S(0x76A)=1; return;
        }
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
