#include "YukariControlMode.hpp"
namespace th105 {
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define I(o) FIELD(int,o)
#define S(o) FIELD(short,o)
#define C(o) FIELD(signed char,o)
#define B(o) FIELD(unsigned char,o)
#define F(o) FIELD(float,o)
#define PEER(t,p,o) (*reinterpret_cast<t *>(FIELD(unsigned char *,p)+(o)))
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define READY (S(0x13C)==700 || S(0x13C)==0)
#define FRONT (*reinterpret_cast<YukariControlSequenceView *>(reinterpret_cast<unsigned char *>(this)+0x55C)->at(0))
void YukariControlModeView::update_control_mode()
{
    float params[3];
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
        if (S(0x76A)==1) {
            if (PEER(short,0x170,0x174)>0) {
                if (READY) { face_opponent_and_flip_horizontal_velocity(); set_action(710); S(0x76A)=1; return; }
            } else S(0x76A)=1;
        }
        return;
    case 4: case 5: case 6: case 7:
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) { face_opponent_and_flip_horizontal_velocity(); set_action(720); S(0x76A)=2; return; }
        if (S(0x76A)==2 && READY) { face_opponent_and_flip_horizontal_velocity(); set_action(721); S(0x76A)=1; return; }
        return;
    case 8: case 9: case 10: case 11:
        if (S(0x76A)>=1) {
            --S(0x7C0);
            if (S(0x7C0)<=0 && (S(0x13C)==700 || S(0x13C)==705 || S(0x13C)==706 ||
                (S(0x13C)>=701 && S(0x13C)<=703 && S(0x13E)>0) || S(0x13C)==704)) {
                face_opponent_and_flip_horizontal_velocity(); set_action(730); return;
            }
        }
        if (S(0x7BE)>0) {
            if (PEER(short,0x168,0x174)<=0) S(0x7BE)=0;
            int period;
            switch (g_match_identifier) {
            case 3: period=6; break;
            case 2: period=8; break;
            case 1: period=9; break;
            case 0: period=10; break;
            }
            if (S(0x7BE)%period==0) {
                params[0]=0.0f; params[1]=0.0f; params[2]=0.0f;
                spawn_owned_object_via_manager(920,
                    static_cast<float>(F(0xEC)+(100.0-static_cast<float>(R(300)))*static_cast<float>(C(0x104))),
                    static_cast<float>((F(0xF0)+300.0)-static_cast<float>(R(400))),
                    B(0x104),-1,reinterpret_cast<int>(params),3);
            }
            --S(0x7BE);
        }
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1) {
            if (PEER(short,0x170,0x174)>0 && READY) {
                face_opponent_and_flip_horizontal_velocity();
                if (C(0x104)==1 ? F(0xEC)<180.0f : F(0xEC)>1100.0f) {
                    set_action(705); F(0x778)=5.0f;
                } else {
                if (R(100)>50) { set_action(705); F(0x778)=4.0f; }
                else { set_action(706); F(0x77C)=-4.0f; }
                }
                S(0x768)=static_cast<short>(selector_random_roll(30)+30); return;
            } else {
                if ((S(0x13C)==705 || S(0x13C)==706) && S(0x768)<=0) {
                    S(0x76A)=2; set_action(700); return;
                }
            }
        }
        if (S(0x76A)==2 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            S(0x76C)=static_cast<short>(selector_random_roll(3));
            if (S(0x76C)==0) {
                if ((F(0xEC)>=640.0f && C(0x104)==1) || (F(0xEC)<=640.0f && C(0x104)==-1)) {
                    F(0x780)=-static_cast<float>(R(3))-6.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                    F(0x788)=0.2f; set_action(703); S(0x76A)=1; return;
                } else {
                    F(0x784)=static_cast<float>(R(4))+8.0;
                    F(0x788)=0.2f; F(0x780)=static_cast<float>(R(3))+6.0;
                    set_action(702); S(0x76A)=1; return;
                }
            }
            if (S(0x76C)==1) {
                F(0x784)=static_cast<float>(R(4))+8.0;
                F(0x788)=0.2f; F(0x780)=static_cast<float>(R(3))+6.0;
                set_action(702); S(0x76A)=1; return;
            }
            if (S(0x76C)==2) {
                if (F(0xEC)<=640.0f) {
                    C(0x104)=1; F(0x780)=static_cast<float>(R(3))+6.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                } else {
                    C(0x104)=-1; F(0x780)=static_cast<float>(R(3))+6.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                }
                S(0x76A)=1; F(0x788)=0.2f; set_action(702); S(0x76A)=1; return;
            }
        }
        return;
    case 12: case 13: case 14: case 15:
        if (S(0x174)<=S(0x176)*static_cast<double>(0.33f)) {
            if (S(0x7C2)<=0) {
                switch (g_match_identifier) {
                case 3: S(0x7C2)=60; break;
                case 2: S(0x7C2)=65; break;
                case 1: case 0: S(0x7C2)=70; break;
                }
                params[0]=0.0f; params[1]=0.0f; params[2]=0.0f;
                spawn_owned_object_via_manager(930,PEER(float,0x170,0xEC),
                    static_cast<float>(PEER(float,0x170,0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
            }
            --S(0x7C2);
        }
        if (S(0x7C4)>0) {
            if (S(0x7C4)%10==0) {
                dispatch_character_wave_handle(22);
                float burst[3]; burst[0]=0.0f; burst[1]=40.0f; burst[2]=1.0f;
                if (S(0x7C6)==0) {
                    spawn_owned_object_via_manager(930,
                        static_cast<float>((C(0x104)==-1)*1280.0),static_cast<float>(F(0xF0)+100.0),
                        B(0x104),1,reinterpret_cast<int>(burst),3);
                } else {
                    spawn_owned_object_via_manager(930,
                        static_cast<float>((C(0x104)==-1)*1280.0),static_cast<float>(S(0x7C6)*75.0+(F(0xF0)+100.0)),
                        B(0x104),1,reinterpret_cast<int>(burst),3);
                    spawn_owned_object_via_manager(930,
                        static_cast<float>((C(0x104)==-1)*1280.0),static_cast<float>((F(0xF0)+100.0)-S(0x7C6)*75.0),
                        B(0x104),1,reinterpret_cast<int>(burst),3);
                }
                ++S(0x7C6);
            }
            --S(0x7C4);
        }
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            if (S(0x174)<=S(0x176)*static_cast<double>(0.33f)) {
                ++S(0x76E); S(0x76A)=2; set_action(741); return;
            }
            if (S(0x76E)%2==0) { S(0x76A)=2; ++S(0x76E); set_action(740); return; }
            S(0x76A)=2; ++S(0x76E); set_action(741); return;
        }
        if (S(0x76A)==2 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            S(0x76C)=static_cast<short>(selector_random_roll(3));
            if (S(0x76C)==0) {
                if ((F(0xEC)>=640.0f && C(0x104)==1) || (F(0xEC)<=640.0f && C(0x104)==-1)) {
                    F(0x780)=-static_cast<float>(R(3))-6.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                    F(0x788)=0.3f; set_action(703); S(0x76A)=1; return;
                } else {
                    F(0x784)=static_cast<float>(R(4))+8.0;
                    F(0x788)=0.3f; F(0x780)=static_cast<float>(R(3))+6.0;
                    set_action(702); S(0x76A)=1; return;
                }
            }
            if (S(0x76C)==1) {
                F(0x784)=static_cast<float>(R(4))+8.0;
                F(0x788)=0.3f; F(0x780)=static_cast<float>(R(3))+6.0;
                set_action(702); S(0x76A)=1; return;
            }
            if (S(0x76C)==2) {
                if (F(0xEC)<=640.0f) {
                    C(0x104)=1; F(0x780)=static_cast<float>(R(3))+6.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                } else {
                    C(0x104)=-1; F(0x780)=static_cast<float>(R(3))+6.0;
                    F(0x784)=static_cast<float>(R(4))+8.0;
                }
                S(0x76A)=1; F(0x788)=0.3f; set_action(702); S(0x76A)=1; return;
            }
        }
        return;
    case 248: case 249: case 250: case 251:
    case 252: case 253: case 254: case 255:
        if (S(0x13C)==700) set_action(0);
        update_cpu_action_policy(); return;
    case 16: case 17: case 18: case 19:
        if (S(0x13C)==750 && S(0x13E)==2) {
            if (S(0x7C8)%300==0) {
                float count;
                switch (g_match_identifier) {
                case 3: count=10.0f; break;
                case 2: count=8.0f; break;
                case 1: case 0: count=6.0f; break;
                }
                float const phase=static_cast<float>(R(360));
                for (float n=0.0f;n<count;n+=1.0) {
                    params[0]=static_cast<float>(n*(360.0/count)+phase);
                    params[1]=static_cast<float>(360.0/count); params[2]=1.0f;
                    spawn_owned_object_via_manager(940,F(0xEC),static_cast<float>(F(0xF0)+100.0),
                        B(0x104),1,reinterpret_cast<int>(params),3);
                }
                params[2]=5.0f;
                spawn_owned_object_via_manager(940,F(0xEC),static_cast<float>(F(0xF0)+100.0),
                    B(0x104),1,reinterpret_cast<int>(params),3);
                dispatch_character_wave_handle(53);
            }
            ++S(0x7C8);
        }
        if (S(0x76A)==0 && READY) { set_action(771); S(0x76A)=1; return; }
        return;
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
