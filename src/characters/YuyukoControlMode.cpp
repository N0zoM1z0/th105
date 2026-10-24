#include "YuyukoControlMode.hpp"
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
#define FRONT (*reinterpret_cast<YuyukoControlSequenceView *>(reinterpret_cast<unsigned char *>(this)+0x55C)->at(0))
void YuyukoControlModeView::update_control_mode()
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
                F(0x784)=static_cast<float>(R(4))+10.0;
                F(0x788)=0.3f; set_action(701); S(0x76A)=2; return;
            }
            F(0x788)=0.3f; set_action(701); S(0x76A)=2;
        }
        if (S(0x76A)==2) {
            if (PEER_VALUE>0) {
                if (READY) { face_opponent_and_flip_horizontal_velocity(); set_action(710); S(0x76A)=1; return; }
            } else S(0x76A)=1;
        }
        return;
    case 4: case 5: case 6: case 7:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) { set_action(720); S(0x76A)=2; return; }
        if (S(0x76A)==2 && PEER_VALUE>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (F(0xEC)<320.0f) {
                if (C(0x104)==1) { set_action(725); S(0x76A)=1; return; }
                else { set_action(726); S(0x76A)=1; return; }
            } else if (F(0xEC)>960.0) {
                if (C(0x104)==1) { set_action(726); S(0x76A)=1; return; }
                else { set_action(725); S(0x76A)=1; return; }
            } else {
                if (R(100)<=50) { set_action(725); S(0x76A)=1; return; }
                else { set_action(726); S(0x76A)=1; return; }
            }
        }
        return;
    case 8: case 9: case 10: case 11:
        if (S(0x76A)==0 && READY) { set_action(730); S(0x76A)=1; return; }
        if (S(0x13C)==731 && S(0x13E)==2) {
            --I(0x7A4); --I(0x7A8);
            if (I(0x7A4)<=0) {
                float count;
                switch (g_match_identifier) {
                case 3: count=6.0f; break;
                case 2: count=4.0f; break;
                case 1: count=3.0f; break;
                case 0: count=1.0f; break;
                }
                if (I(0x7A4)%30==0) {
                    if (count>static_cast<float>(I(0x7AC))) {
                        float const x=static_cast<float>(static_cast<float>(R(800))+240.0);
                        float const y=static_cast<float>(static_cast<float>(R(400))+100.0);
                        float params[3];
                        params[1]=static_cast<float>(R(100))+650.0;
                        for (float index=0.0f; index<12.0f; index+=1.0) {
                            params[0]=index*30.0;
                            params[2]=0.0f;
                            spawn_owned_object_via_manager(920,x,y,B(0x104),1,reinterpret_cast<int>(params),3);
                        }
                        ++I(0x7AC); dispatch_character_wave_handle(13); return;
                    } else { I(0x7AC)=0; I(0x7A4)=180; return; }
                }
            }
        }
        return;
    case 248: case 249: case 250: case 251:
    case 252: case 253: case 254: case 255:
        if (S(0x13C)==700) set_action(0);
        update_cpu_action_policy(); return;
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
