#include "PatchouliControlMode.hpp"
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
#define FRONT (*reinterpret_cast<PatchouliControlSequenceView *>(reinterpret_cast<unsigned char *>(this)+0x55C)->at(0))
void PatchouliControlModeView::update_control_mode()
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
        if (S(0x76A)==1) {
            if (PEER_VALUE>0) {
                if (READY) { face_opponent_and_flip_horizontal_velocity(); set_action(710); S(0x76A)=1; return; }
            } else S(0x76A)=1;
        }
        if (S(0x76A)==2 && PEER_VALUE>0 && READY) {
            face_opponent_and_flip_horizontal_velocity();
            F(0x780)=static_cast<float>(R(15));
            F(0x784)=static_cast<float>(R(4))+8.0;
            F(0x788)=0.3f; set_action(701); S(0x76A)=1; return;
        }
        return;
    case 4: case 5: case 6: case 7: {
        float params[3];
        if ((S(0x13C)==720 && S(0x13E)==3) || S(0x13C)==721) {
            if (S(0x7A6)>0) --S(0x7A6);
            if (S(0x7A6)==0) {
                params[0]=0.0f; params[1]=0.0f; params[2]=0.0f;
                S(0x7A6)=-1;
                spawn_owned_object_via_manager(910,F(0xEC),
                    static_cast<float>(F(0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
                dispatch_character_wave_handle(12);
            }
            --S(0x7A8);
            if (S(0x7A8)<=0) {
                dispatch_character_wave_handle(12);
                float const phase=static_cast<float>(R(360));
                switch (g_match_identifier) {
                case 3:
                    S(0x7A8)=300;
                    for (float n=0.0f;n<12.0f;n+=1.0) {
                        params[0]=static_cast<float>(n*30.0+phase);
                        params[1]=6.0f; params[2]=3.0f;
                        spawn_owned_object_via_manager(910,F(0xEC),
                            static_cast<float>(F(0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
                    }
                    break;
                case 2:
                    S(0x7A8)=300;
                    for (float n=0.0f;n<9.0f;n+=1.0) {
                        params[0]=static_cast<float>(n*40.0+phase);
                        params[1]=6.0f; params[2]=3.0f;
                        spawn_owned_object_via_manager(910,F(0xEC),
                            static_cast<float>(F(0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
                    }
                    break;
                case 1:
                    S(0x7A8)=300;
                    for (float n=0.0f;n<8.0f;n+=1.0) {
                        params[0]=static_cast<float>(n*45.0+phase);
                        params[1]=6.0f; params[2]=3.0f;
                        spawn_owned_object_via_manager(910,F(0xEC),
                            static_cast<float>(F(0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
                    }
                    break;
                case 0:
                    S(0x7A8)=360;
                    for (float n=0.0f;n<6.0f;n+=1.0) {
                        params[0]=static_cast<float>(n*60.0+phase);
                        params[1]=6.0f; params[2]=3.0f;
                        spawn_owned_object_via_manager(910,F(0xEC),
                            static_cast<float>(F(0xF0)+100.0),B(0x104),1,reinterpret_cast<int>(params),3);
                    }
                    break;
                }
            }
        }
        if (S(0x76A)==0 && READY) { set_action(770); S(0x76A)=1; return; }
        if (S(0x76A)==1 && READY) {
            face_opponent_and_flip_horizontal_velocity(); set_action(720); S(0x76A)=2; return;
        }
        if (S(0x76A)==2 && S(0x13C)==720 && S(0x13E)==3) { S(0x76A)=3; S(0x768)=60; return; }
        if (S(0x76A)==3 && S(0x768)<=0) { set_action(721); S(0x76A)=4; return; }
        if (S(0x76A)==4 && S(0x13C)==720) {
            S(0x768)=static_cast<short>(selector_random_roll(30)+60); S(0x76A)=3; return;
        }
        return;
    }
    case 248: case 249: case 250: case 251:
    case 252: case 253: case 254: case 255:
        if (S(0x13C)==700) set_action(0);
        update_cpu_action_policy(); return;
    case 8: case 9: case 10: case 11: {
        if (S(0x13C)==730 && S(0x13E)==2) {
            ++S(0x7AA);
            // Native identifiers0..3 supply these; no default initialization.
            float threshold, rings, chance;
            switch (g_match_identifier) {
            case 3: threshold=120.0f; rings=4.0f; chance=25.0f; break;
            case 2: threshold=120.0f; rings=3.0f; chance=15.0f; break;
            case 1: threshold=120.0f; rings=2.0f; chance=10.0f; break;
            case 0: threshold=180.0f; rings=2.0f; chance=0.0f; break;
            }
            if (static_cast<float>(S(0x7AA))>=threshold && S(0x7AA)%10==0) {
                if (static_cast<float>(S(0x7AA))==threshold) {
                    S(0x7AE)=0;
                    F(0x73C)=F(0xEC); F(0x740)=static_cast<float>(F(0xF0)+100.0);
                }
                if (static_cast<float>(S(0x7AE))<rings) {
                    dispatch_character_wave_handle(61);
                    float const selected=static_cast<float>(R(6));
                    float params[4];
                    for (float n=0.0f;n<6.0f;n+=1.0) {
                        params[0]=static_cast<float>(n*60.0);
                        params[1]=static_cast<float>((S(0x7AE)+1)*200.0);
                        params[2]=0.0f; params[3]=0.0f;
                        if (n==selected) params[3]=1.0f;
                        float const x=static_cast<float>(lookup_orientation_cosine_quantized_abs(-params[0])*params[1]+F(0x73C));
                        float const y=static_cast<float>(lookup_orientation_sine_quantized_abs(-params[0])*params[1]+F(0x740));
                        spawn_owned_object_via_manager(920,x,y,B(0x104),-1,reinterpret_cast<int>(params),4);
                        if (S(0x7AE)>=1) {
                            for (float j=0.0f;j<static_cast<float>(S(0x7AE));j+=1.0) {
                                float child[2];
                                child[0]=static_cast<float>(params[0]-120.0);
                                child[1]=static_cast<float>((j+1.0)*200.0);
                                if (static_cast<float>(R(100))<=chance) params[3]=1.0f;
                                spawn_owned_object_via_manager(920,
                                    static_cast<float>(lookup_orientation_cosine_quantized_abs(-child[0])*child[1]+x),
                                    static_cast<float>(lookup_orientation_sine_quantized_abs(-child[0])*child[1]+y),
                                    B(0x104),-1,reinterpret_cast<int>(params),4);
                            }
                        }
                    }
                    ++S(0x7AE);
                } else { S(0x7AE)=0; S(0x7AA)=0; }
            }
        }
        if (S(0x76A)==0 && READY) { set_action(730); S(0x76A)=1; return; }
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
