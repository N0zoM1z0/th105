#include "CpuActionPolicies.hpp"
#include "engine/AngleAtan2.hpp"

#include "../battle/Collision.hpp"

#include <stdlib.h>

namespace th105 {

unsigned int __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int limit);

#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + (offset)))
#define I(o) FIELD(int,o)
#define U(o) FIELD(unsigned,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define F(o) FIELD(float,o)
#define PEER(o) (*reinterpret_cast<float *>(FIELD(unsigned char *,0x170)+(o)))
#define PEER_S(o) (*reinterpret_cast<short *>(FIELD(unsigned char *,0x170)+(o)))
#define FRONT (*reinterpret_cast<short *>(reinterpret_cast<FighterSequenceController *>(reinterpret_cast<unsigned char *>(this)+0x55C)->entry_at_checked(0)))
#define RNG(n) static_cast<unsigned>(selector_random_roll(n))
#define PREPARE() if (I(0x180)==0) S(0x764)=0; else if (I(0x180)!=3 && S(0x764)==0) S(0x764)=static_cast<short>(selector_random_roll(100))
#define RANGE(a,b) (S(0x764)>=(a) && S(0x764)<=(b))
#define OUTPUT(button,x,y) { I(button)=2; I(0x6B4)=(x); I(0x6B8)=(y); break; }
#define AIM(limit) (-(int)(short)(int)atan2_degrees(PEER(0xF0)-F(0xF0), (float)C(0x104)*(PEER(0xEC)-F(0xEC))) >= (limit))

void CpuActionPolicyView::update_default_cpu_action_policy()
{
    U(0x724)=0; U(0x728)=0;
    float const h=static_cast<float>(abs(static_cast<int>(PEER(0xEC)-F(0xEC))));
    int const dy=static_cast<int>(PEER(0xF0)-F(0xF0));
    --S(0x768);
    float const v=static_cast<float>(abs(dy));
    I(0x6BC)=0; I(0x6C0)=0; I(0x6C4)=0;
    I(0x6C8)=0; I(0x6CC)=0; I(0x6D0)=0;
    if (S(0x13C)>49 && S(0x13C)<150) {
        S(0x76C)=0; S(0x76A)=0; S(0x766)=0; S(0x768)=0; S(0x764)=0;
        if (mt19937_next_u32()%100<=10) { I(0x6BC)=1; I(0x6B4)=selector_random_roll(3)-1; }
    }
    if (S(0x13C)<=199) { S(0x76C)=0; S(0x764)=0; }
    S(0x76E)=static_cast<short>(selector_random_roll(1000));
    if (PEER_S(0x174)<=0) return;

    switch (S(0x13C)) {
    case 200:
        if (S(0x764)==0) { S(0x764)=100; if (h>=700.0f) S(0x764)=static_cast<short>(selector_random_roll(100)+1); }
        if (((F(0xEC)>PEER(0xEC) && C(0x104)==-1) || (F(0xEC)<PEER(0xEC) && C(0x104)==1)) && S(0x764)>=50) {
            if (h<220.0 && RNG(1000)<85 && v<50.0) { I(0x6B4)=C(0x104); I(0x6BC)=2; }
            else if (h>=150.0f && h<=300.0f && v<50.0 && RNG(1000)<50) { I(0x6B4)=C(0x104); I(0x6C0)=2; }
            else if (h>=250.0 && h<=300.0f && v>50.0 && v<150.0f && RNG(1000)<50) { I(0x6B4)=C(0x104); I(0x6C4)=2; }
        }
        break;
    case 300:
        PREPARE();
        if (RANGE(10,90)) OUTPUT(0x6BC,0,0)
        if (S(0x764)>=90) OUTPUT(0x6BC,C(0x104),1)
        break;
    case 301:
        PREPARE();
        if (RANGE(20,65)) OUTPUT(0x6BC,C(0x104),0)
        if (RANGE(65,85) && S(0x482)>=400) OUTPUT(0x6C0,0,0)
        if (RANGE(85,95) && S(0x482)>=400 && PEER(0xF0)==0.0f) OUTPUT(0x6C0,0,1)
        break;
    case 302:
        PREPARE();
        if (RANGE(0,30) && S(0x482)>=300) OUTPUT(0x6C0,0,0)
        if (RANGE(30,50) && S(0x482)>=400) OUTPUT(0x6C4,0,0)
        if (RANGE(50,60) && S(0x482)>=400) OUTPUT(0x6C4,0,1)
        if (RANGE(60,65) && S(0x482)>=200 && PEER(0xF0)==0.0f) OUTPUT(0x6C0,0,1)
        if (RANGE(65,75) && S(0x482)>=400) { U(0x728)=2; break; }
        if (RANGE(75,85) && S(0x482)>=400 && I(0x180)!=1) { U(0x728)=0x20; break; }
        if (RANGE(95,100) && C(0x55A)>0) {
            switch (FRONT) {
            case 200:
                if (((F(0xEC)>960.0 && C(0x104)==1) || (F(0xEC)<300.0f && C(0x104)==-1)) && I(0x180)==1) { I(0x6D0)=2; break; }
            case 201:
                if ((F(0xEC)>960.0 && C(0x104)==1) || (F(0xEC)<300.0f && C(0x104)==-1)) { I(0x6D0)=2; break; }
            case 202:
                I(0x6D0)=2; break;
            case 205:
                if (((F(0xEC)>860.0 && C(0x104)==1) || (F(0xEC)<400.0 && C(0x104)==-1)) && I(0x180)==1) { I(0x6D0)=2; break; }
            case 212:
                if (((F(0xEC)>860.0 && C(0x104)==1) || (F(0xEC)<400.0 && C(0x104)==-1)) && I(0x180)==1) I(0x6D0)=2;
                break;
            }
        }
        break;
    case 303:
        PREPARE();
        if (RANGE(0,30) && h<80.0f) OUTPUT(0x6BC,0,1)
        if (RANGE(30,50)) OUTPUT(0x6BC,C(0x104),0)
        if (RANGE(50,75)) OUTPUT(0x6BC,C(0x104),1)
        break;
    case 304:
        PREPARE();
        if (RANGE(0,30) && S(0x482)>=300) OUTPUT(0x6C0,0,0)
        if (RANGE(30,50) && S(0x482)>=400) OUTPUT(0x6C4,0,0)
        if (RANGE(50,60) && S(0x482)>=400) OUTPUT(0x6C4,0,1)
        if (RANGE(60,65) && S(0x482)>=200 && PEER(0xF0)==0.0f) OUTPUT(0x6C0,0,1)
        if (RANGE(65,75) && S(0x482)>=400) { U(0x728)=2; break; }
        if (RANGE(75,85) && S(0x482)>=400 && I(0x180)!=1) { U(0x728)=0x20; break; }
        if (RANGE(95,100) && C(0x55A)>0) {
            switch (FRONT) {
            case 200: case 201: case 202: I(0x6D0)=2; break;
            case 205: case 212: if (I(0x180)==1) I(0x6D0)=2; break;
            }
        }
        break;
    case 305:
        PREPARE();
        if (RANGE(65,75) && S(0x482)>=400) { U(0x728)=2; break; }
        break;
    case 306:
        PREPARE();
        if (RANGE(0,15) && PEER(0xF0)>F(0xF0)) { I(0x6BC)=1; I(0x6B4)=C(0x104); I(0x6B8)=0; break; }
        if (RANGE(15,25) && S(0x482)>=300) OUTPUT(0x6C0,0,AIM(30))
        if (RANGE(25,30) && S(0x482)>=400) { U(0x728)=2; break; }
        if (RANGE(30,35) && S(0x482)>=400 && v<80.0f) { U(0x728)=0x20; break; }
        if (RANGE(35,40) && S(0x482)>=400 && v>100.0 && F(0xF0)>PEER(0xF0)) { U(0x728)=0x40; break; }
        break;
    case 307:
        PREPARE();
        if (RANGE(0,30) && S(0x482)>=300) OUTPUT(0x6C0,0,AIM(30))
        if (RANGE(30,40) && S(0x482)>=300) OUTPUT(0x6C4,0,AIM(30))
        if (RANGE(40,45) && S(0x482)>=400) { U(0x728)=2; break; }
        if (RANGE(45,55) && S(0x482)>=400 && I(0x180)==1) { U(0x728)=0x20; break; }
        if (RANGE(95,100) && C(0x55A)>0) {
            switch (FRONT) {
            case 211: if (I(0x180)==1) { I(0x6D0)=2; break; }
            case 212: if (I(0x180)==1) I(0x6D0)=2; break;
            }
        }
        break;
    case 308:
        PREPARE();
        if (RANGE(0,25) && S(0x482)>=300) OUTPUT(0x6C0,0,AIM(20))
        if (RANGE(25,35) && S(0x482)>=300) OUTPUT(0x6C4,0,1)
        if (RANGE(95,100) && C(0x55A)>0 && FRONT==211 && I(0x180)==1) I(0x6D0)=2;
        break;
    case 320:
        PREPARE();
        if (RANGE(0,90)) OUTPUT(0x6BC,0,0)
        break;
    case 321:
        PREPARE();
        if (RANGE(0,50)) OUTPUT(0x6BC,0,0)
        if (RANGE(50,65)) OUTPUT(0x6BC,C(0x104),0)
        if (RANGE(65,80)) OUTPUT(0x6BC,C(0x104),1)
        if (RANGE(80,90) && S(0x482)>=400) OUTPUT(0x6BC,0,0)
        if (RANGE(90,95) && S(0x482)>=400 && PEER(0xF0)==0.0f) OUTPUT(0x6BC,0,1)
        break;
    case 322:
        PREPARE();
        if (RANGE(50,75) && S(0x482)>=400) { U(0x728)=2; break; }
        if (RANGE(75,85) && S(0x482)>=400 && I(0x180)!=1) { U(0x728)=0x20; break; }
        if (RANGE(95,100) && C(0x55A)>0) {
            switch (FRONT) {
            case 200:
                if (((F(0xEC)>960.0 && C(0x104)==1) || (F(0xEC)<300.0f && C(0x104)==-1)) && I(0x180)==1) { I(0x6D0)=2; break; }
            case 201:
                if ((F(0xEC)>960.0 && C(0x104)==1) || (F(0xEC)<300.0f && C(0x104)==-1)) { I(0x6D0)=2; break; }
            case 202:
                I(0x6D0)=2; break;
            case 205:
                if (((F(0xEC)>860.0 && C(0x104)==1) || (F(0xEC)<400.0 && C(0x104)==-1)) && I(0x180)==1) { I(0x6D0)=2; break; }
            case 212:
                if (((F(0xEC)>860.0 && C(0x104)==1) || (F(0xEC)<400.0 && C(0x104)==-1)) && I(0x180)==1) I(0x6D0)=2;
                break;
            }
        }
        break;
    case 400: case 401:
        PREPARE();
        if (RANGE(0,10) && S(0x482)>=400) OUTPUT(0x6C4,0,1)
        if (RANGE(10,20) && S(0x482)>=400) { U(0x728)=2; break; }
        if (RANGE(95,100) && C(0x55A)>0) {
            switch (FRONT) {
            case 202: I(0x6D0)=2; break;
            case 205: if (v<150.0f) { I(0x6D0)=2; break; }
            case 211: I(0x6D0)=2; break;
            }
        }
        break;
    case 402:
        PREPARE();
        if (RANGE(0,10) && S(0x482)>=400) OUTPUT(0x6C4,0,0)
        if (RANGE(10,20) && S(0x482)>=400) OUTPUT(0x6C4,0,1)
        if (RANGE(20,30) && S(0x482)>=400 && h<450.0 && v<100.0) OUTPUT(0x6C4,C(0x104),0)
        if (RANGE(30,45) && S(0x482)>=400) { U(0x728)=2; break; }
        break;
    case 404: case 405: case 406:
        PREPARE();
        if (RANGE(0,10) && S(0x482)>=400 && h<500.0 && v<100.0) OUTPUT(0x6C4,C(0x104),0)
        if (RANGE(10,20) && S(0x482)>=400 && v<100.0 && F(0xF0)>PEER(0xF0)) OUTPUT(0x6C4,0,1)
        if (RANGE(20,30) && S(0x482)>=400) OUTPUT(0x6C4,0,0)
        if (RANGE(30,40) && S(0x482)>=400 && v>100.0 && F(0xF0)>PEER(0xF0)) { U(0x728)=2; break; }
        if (RANGE(95,100) && C(0x55A)>0 && FRONT==211) I(0x6D0)=2;
        break;
    case 410: case 412:
        PREPARE();
        if (RANGE(50,75) && S(0x482)>=400) { U(0x728)=2; break; }
        if (RANGE(75,80) && S(0x482)>=400 && I(0x180)!=1) { U(0x728)=0x20; break; }
        if (RANGE(95,100) && C(0x55A)>0) {
            switch (FRONT) {
            case 200:
                if ((F(0xEC)>960.0 && C(0x104)==1) || (F(0xEC)<300.0f && C(0x104)==-1)) { I(0x6D0)=2; break; }
            case 201:
                if ((F(0xEC)>960.0 && C(0x104)==1) || (F(0xEC)<300.0f && C(0x104)==-1)) { I(0x6D0)=2; break; }
            case 202:
                I(0x6D0)=2; break;
            case 205:
                I(0x6D0)=2; break;
            case 212:
                if (((F(0xEC)>860.0 && C(0x104)==1) || (F(0xEC)<400.0 && C(0x104)==-1)) && I(0x180)==1) I(0x6D0)=2;
                break;
            }
        }
        break;
    case 414: case 415: case 416:
        PREPARE();
        if (RANGE(40,45) && S(0x482)>=400) { U(0x728)=2; break; }
        if (RANGE(45,55) && S(0x482)>=400 && I(0x180)==1) { U(0x728)=0x20; break; }
        if (RANGE(95,100) && C(0x55A)>0) {
            switch (FRONT) {
            case 211: I(0x6D0)=2; break;
            case 212: if (v<150.0f) { I(0x6D0)=2; break; }
            }
            break;
        }
        break;
    }

    switch (S(0x766)) {
    case 0:
        if (S(0x76C)==0) S(0x76C)=static_cast<short>(selector_random_roll(100));
        if (((F(0xEC)>PEER(0xEC) && C(0x104)==-1) || (F(0xEC)<PEER(0xEC) && C(0x104)==1)) && (PEER_S(0x13C)<=95 || PEER_S(0x13C)>=140)) {
#define INPUT_DONE { I(0x6D0)=2; break; }
#define TRY(condition,limit,sequence) if ((condition) && RNG(1000)<(limit) && FRONT==(sequence)) INPUT_DONE
#define CONTROL_DONE(button,x,y) { I(button)=2; I(0x6B4)=(x); I(0x6B8)=(y); break; }
            if (F(0xF0)==0.0f) {
                if (PEER(0xF0)==0.0f) {
                    if (h<=90.0f) {
                        if (RNG(1000)<70) CONTROL_DONE(0x6BC,0,0)
                        if (RNG(1000)<70) CONTROL_DONE(0x6BC,0,1)
                    }
                    if (RNG(1000)<75 && h<350.0f && h>120.0) { S(0x766)=100; S(0x768)=static_cast<short>(selector_random_roll(20)+10); break; }
                    if (C(0x55A)>0) {
                        TRY(h<300.0f,5,200)
                        TRY(h<150.0f,5,201)
                        TRY(h>200.0,3,202)
                        TRY(h>150.0f && v<150.0f,5,205)
                        TRY(h<150.0f,2,211)
                        TRY(h>150.0f && v<200.0,5,212)
                    }
                    if (h<=180.0f) {
                        if (h>=90.0f && RNG(1000)<50) CONTROL_DONE(0x6BC,0,0)
                        if (h>=120.0 && RNG(1000)<=50) { I(0x6BC)=2; I(0x6B4)=C(0x104); I(0x6B8)=1; break; }
                    }
                    if (h<=250.0 && h>=90.0f && RNG(1000)<=50) { I(0x6BC)=2; I(0x6B4)=C(0x104); I(0x6B8)=0; break; }
                    if (h<640.0f && h>350.0f && RNG(1000)<=5 && S(0x482)>=400) { U(0x728)=0x20; break; }
                    if (h>90.0f && RNG(1000)<=15 && S(0x482)>=400) { U(0x728)=2; break; }
                    if (S(0x76E)<=S(0x482)) {
                        if (h>=120.0 && RNG(1000)<=5) CONTROL_DONE(0x6C0,0,1)
                        if (h>=180.0f) {
                            if (RNG(1000)<=10) CONTROL_DONE(0x6C0,0,0)
                            if (h>=240.0) {
                                if (RNG(1000)<=5) CONTROL_DONE(0x6C4,0,0)
                            } else {
                                if (RNG(1000)<=5) CONTROL_DONE(0x6C4,0,1)
                            }
                            if (h<=600.0f) { if (RNG(1000)<=5) { I(0x6C4)=2; I(0x6B4)=C(0x104); I(0x6B8)=0; } }
                        }
                    }
                } else {
                    if (h<520.0f && h>240.0 && v<250.0 && RNG(1000)<=2 && S(0x482)>=600) { U(0x728)=0x40; break; }
                    if (C(0x55A)>0) {
                        TRY(h<300.0f,5,200)
                        TRY(h<150.0f,5,201)
                        TRY(h>200.0,3,202)
                        TRY(h>150.0f && v<150.0f,5,205)
                        TRY(h<150.0f,2,211)
                        TRY(h>150.0f && v<200.0,5,212)
                    }
                    if (RNG(1000)<75 && h<200.0 && h>120.0 && v<75.0f) { S(0x766)=100; S(0x768)=static_cast<short>(selector_random_roll(20)+10); break; }
                    if (S(0x76E)<=S(0x482)) {
                        if (RNG(1000)<10 && S(0x482)>=600 && v<200.0 && h<450.0) CONTROL_DONE(0x6C4,0,0)
                        if (RNG(1000)<10 && S(0x482)>=600 && v<200.0 && h<450.0) { I(0x6C0)=2; I(0x6B4)=C(0x104); I(0x6B8)=0; break; }
                    }
                }
            } else if (PEER(0xF0)==0.0f) {
                if (C(0x55A)>0) {
                    TRY(h<150.0f,2,211)
                    TRY(h>150.0f && v<200.0,5,212)
                }
                if (h<450.0 && h>90.0f && RNG(1000)<=5 && S(0x482)>=600) { U(0x728)=0x40; break; }
                if (h<450.0 && F(0xF0)>PEER(0xF0) && RNG(1000)<=7 && S(0x482)>=800) { U(0x728)=2; break; }
                if (h<=static_cast<float>(((F(0xF4)>0.0f)+1)*120)) {
                    int const rising=(F(0xF0)<PEER(0xF0) && F(0xF8)>0.0f);
                    if (v<static_cast<float>(rising*150+100) && RNG(1000)<50) CONTROL_DONE(0x6BC,0,0)
                }
                if (h<=180.0f && F(0xF0)>PEER(0xF0) && RNG(1000)<75) CONTROL_DONE(0x6BC,0,1)
                if (S(0x76E)<=S(0x482)) {
                    if (h>static_cast<float>((v<200.0)*180+120) && RNG(1000)<50) {
                        I(0x6C0)=2;
                        int const aim=static_cast<int>(atan2_degrees(PEER(0xF0)-F(0xF0),static_cast<float>(C(0x104))*(PEER(0xEC)-F(0xEC))));
                        I(0x6B4)=0; I(0x6B8)=-static_cast<int>(static_cast<short>(aim))>=30;
                    }
                    if (h>250.0 && v<200.0 && RNG(1000)<20) { I(0x6C4)=2; I(0x6B8)=0; I(0x6B4)=0; }
                    if (h<300.0f && v>200.0 && F(0xF0)>PEER(0xF0) && RNG(1000)<25) { I(0x6C4)=2; I(0x6B8)=1; I(0x6B4)=0; }
                }
            } else {
                if (C(0x55A)>0) {
                    TRY(h<150.0f,2,211)
                    TRY(h>150.0f && v<200.0,5,212)
                }
                if (h<=static_cast<float>(((F(0xF4)>0.0f)+1)*120)) {
                    int const rising=(F(0xF0)<PEER(0xF0) && F(0xF8)>0.0f);
                    if (v<static_cast<float>(rising*150+100) && RNG(1000)<50) CONTROL_DONE(0x6BC,0,0)
                }
                if (h<=180.0f && F(0xF0)>PEER(0xF0) && v>60.0 && RNG(1000)<75) CONTROL_DONE(0x6BC,0,1)
                if (h<=280.0f && h>=90.0f && v<100.0 && F(0xF0)<PEER(0xF0) && RNG(1000)<75) { I(0x6BC)=2; I(0x6B4)=C(0x104); I(0x6B8)=0; break; }
                if (h>static_cast<float>((v<200.0)*180+120) && RNG(1000)<50) {
                    I(0x6C0)=2;
                    int const aim=static_cast<int>(atan2_degrees(PEER(0xF0)-F(0xF0),static_cast<float>(C(0x104))*(PEER(0xEC)-F(0xEC))));
                    I(0x6B4)=0; I(0x6B8)=-static_cast<int>(static_cast<short>(aim))>=30;
                }
                if (h>250.0 && v<200.0 && RNG(1000)<20) { I(0x6C4)=2; I(0x6B8)=0; I(0x6B4)=0; }
                if (h>150.0f && h<500.0 && v<100.0 && RNG(1000)<20) { I(0x6C4)=2; I(0x6B8)=0; I(0x6B4)=C(0x104); }
                if (h<300.0f && v>200.0 && F(0xF0)>PEER(0xF0) && RNG(1000)<25) { I(0x6C4)=2; I(0x6B8)=0; I(0x6B4)=0; }
            }
#undef CONTROL_DONE
#undef TRY
#undef INPUT_DONE
        }
        break;
    }

#define CHOOSE(id) { S(0x766)=static_cast<short>(id); return; }
#define DURATION(id,bound,add) { S(0x766)=static_cast<short>(id); S(0x768)=static_cast<short>(selector_random_roll(bound)+(add)); return; }
#define WAIT(bound) { S(0x768)=static_cast<short>(selector_random_roll(bound)); return; }
#define WALL ((C(0x104)==1 && F(0xEC)<240.0) || (C(0x104)==-1 && F(0xEC)>1040.0f))
#define INTERIOR ((C(0x104)==1 && F(0xEC)>=240.0) || (C(0x104)==-1 && F(0xEC)<=1040.0f))
    switch (S(0x766)) {
    case 0: {
        if (S(0x768)>0) return;
        int const roll=selector_random_roll(100);
        S(0x76A)=static_cast<short>(roll);
#define P(a,b) (S(0x76A)>=(a) && S(0x76A)<=(b))
        if (F(0xF0)==0.0f) {
            if (PEER(0xF0)==0.0f) {
                if (h<=90.0f) {
                    if (P(0,9)) CHOOSE(4)
                    if (P(10,14)) CHOOSE(7)
                    if (P(15,29)) CHOOSE(5)
                    if (P(30,39)) CHOOSE(8)
                    if (WALL) {
                        if (P(40,44)) CHOOSE(3)
                        if (P(45,49)) CHOOSE(6)
                    }
                    if (P(50,74)) DURATION((C(0x104)==1)+1,30,15)
                    if (P(75,89) && INTERIOR) DURATION((C(0x104)==1)+9,30,0)
                    WAIT(10)
                }
                if (h<=240.0) {
                    if (P(0,2)) CHOOSE(4)
                    if (P(3,5)) CHOOSE(7)
                    if (P(6,8)) CHOOSE(5)
                    if (P(9,11)) CHOOSE(8)
                    if (P(12,14)) CHOOSE(3)
                    if (P(15,17)) CHOOSE(6)
                    if (WALL) {
                        if (P(20,24)) CHOOSE(3)
                        if (P(25,29)) CHOOSE(6)
                    }
                    if (P(30,39)) DURATION((C(0x104)==-1)+1,30,15)
                    if (P(40,54)) DURATION((C(0x104)==-1)+9,30,15)
                    if (P(55,69)) DURATION((C(0x104)==1)+1,30,15)
                    if (P(70,89)) DURATION((C(0x104)==1)+9,30,0)
                    WAIT(10)
                }
                if (h>=520.0f) {
                    if (P(0,4)) CHOOSE(4)
                    if (P(5,9)) CHOOSE(7)
                    if (P(10,14)) CHOOSE(5)
                    if (P(15,17)) CHOOSE(8)
                    if (P(18,24)) CHOOSE(3)
                    if (P(25,29)) CHOOSE(6)
                    if (P(30,44)) DURATION((C(0x104)==-1)+1,30,30)
                    if (P(45,79)) DURATION(9,30,60)
                    if (P(80,82) && INTERIOR) DURATION((C(0x104)==1)+1,30,15)
                    if (P(83,89) && INTERIOR) DURATION((C(0x104)==1)+9,30,0)
                    WAIT(10)
                }
                if (!(h>=240.0)) return;
                if (P(0,2)) CHOOSE(4)
                if (P(3,5)) CHOOSE(7)
                if (P(6,8)) CHOOSE(5)
                if (P(9,11)) CHOOSE(8)
                if (P(12,15)) CHOOSE(3)
                if (P(16,18)) CHOOSE(6)
                if (WALL) {
                    if (P(20,29)) CHOOSE(3)
                    if (P(30,39)) CHOOSE(6)
                }
                if (P(40,54)) DURATION((C(0x104)==-1)+1,30,10)
                if (P(55,79)) DURATION((C(0x104)==-1)+9,30,0)
                if (P(80,84)) DURATION((C(0x104)==1)+1,30,10)
                if (P(85,99)) DURATION((C(0x104)==1)+9,30,0)
                WAIT(10)
            }
            if (h<=90.0f) {
                if (v>100.0) {
                    if (P(0,6)) CHOOSE(4)
                    if (P(7,10) && v>=200.0) CHOOSE(7)
                    if (P(11,18)) CHOOSE(5)
                    if (P(19,24) && v>=200.0) CHOOSE(8)
                }
                if (WALL && P(25,49) && v>=250.0) DURATION((C(0x104)==-1)+9,30,15)
                if (P(50,69)) DURATION((C(0x104)==1)+1,30,15)
                if (P(70,74)) DURATION((C(0x104)==1)+9,30,0)
                WAIT(10)
            }
            if (h<=240.0) {
                if (P(0,6)) CHOOSE(4)
                if (P(7,10) && v>=200.0) CHOOSE(7)
                if (P(11,18)) CHOOSE(5)
                if (P(19,24) && v>=200.0) CHOOSE(8)
                if (WALL && P(35,50) && v>=400.0) DURATION((C(0x104)==-1)+9,30,15)
                if (P(50,69)) DURATION((C(0x104)==1)+1,30,15)
                if (P(70,74)) DURATION((C(0x104)==1)+9,30,0)
                WAIT(10)
            }
            if (h>=520.0f) {
                if (P(0,9)) CHOOSE(4)
                if (P(10,19)) CHOOSE(7)
                if (P(20,24)) CHOOSE(5)
                if (P(25,29)) CHOOSE(8)
                if (P(30,39)) CHOOSE(3)
                if (P(40,49)) CHOOSE(6)
                if (P(50,54)) DURATION((C(0x104)==-1)+1,30,15)
                if (P(55,95)) DURATION((C(0x104)==-1)+9,30,45)
                WAIT(10)
            }
            if (!(h>=240.0)) return;
            if (P(0,6)) CHOOSE(4)
            if (P(7,12)) CHOOSE(7)
            if (P(13,20)) CHOOSE(5)
            if (P(21,30)) CHOOSE(8)
            if (WALL) {
                if (P(40,49)) CHOOSE(3)
                if (P(50,59)) CHOOSE(6)
            }
            if (P(60,64)) DURATION((C(0x104)==-1)+1,30,10)
            if (P(65,79)) DURATION((C(0x104)==-1)+9,30,20)
            if (P(80,89)) DURATION((C(0x104)==1)+1,40,10)
            if (P(90,99)) S(0x766)=static_cast<short>((C(0x104)==1)+9);
            WAIT(10)
        }
        if (PEER(0xF0)==0.0f) {
            if (PEER(0xF0)!=0.0f) return;
            if (h<=90.0f) {
                if (WALL) {
                    if (P(0,29) && v>200.0) DURATION((C(0x104)==-1)+9,30,15)
                    if (P(30,44)) DURATION(11,30,15)
                }
                if (P(45,59) && v>150.0f) DURATION((C(0x104)==1)+9,30,0)
                WAIT(60)
            }
            if (h<=240.0) {
                if (WALL) {
                    if (P(0,29) && v>100.0) DURATION((C(0x104)==-1)+9,30,0)
                    if (P(30,44)) DURATION(11,30,15)
                }
                if (P(45,54)) DURATION((C(0x104)==-1)+9,30,20)
                if (P(55,64)) DURATION((C(0x104)==1)+9,30,0)
                WAIT(40)
            }
            if (h>=520.0f) {
                if (P(0,34)) DURATION((C(0x104)==-1)+9,30,20)
                if (P(35,39)) DURATION((C(0x104)==1)+9,30,10)
                WAIT(10)
            }
            if (!(h>=240.0)) return;
            if (P(0,9)) DURATION((C(0x104)==-1)+9,15,15)
            if (P(10,19)) DURATION(11,30,30)
            if (P(20,24)) DURATION(12,30,20)
            if (P(45,54)) DURATION((C(0x104)==-1)+9,30,0)
            if (P(55,64)) DURATION((C(0x104)==1)+9,20,15)
            WAIT(10)
        }
        if (h<=90.0f) {
            if (P(0,5)) DURATION((C(0x104)==1)+9,30,0)
            if (!(v>320.0f)) WAIT(60)
            if (F(0xF0)<PEER(0xF0)) {
                if (P(5,9)) DURATION(12,30,15)
                if (P(10,14)) DURATION(11,30,15)
                if (P(15,24)) DURATION((C(0x104)==-1)+9,30,0)
            }
            if (F(0xF0)>PEER(0xF0)) {
                if (P(25,27)) DURATION(17,20,5)
                if (P(28,31)) DURATION(16,20,5)
                if (P(32,35)) DURATION(18,20,5)
                if (P(36,39)) DURATION((C(0x104)==1)+9,30,0)
            }
            WAIT(60)
        }
        if (h<=240.0) {
            if (WALL) {
                if (P(0,14) && F(0xF0)>PEER(0xF0)) DURATION(11,30,15)
                if (P(15,29) && v>150.0f) DURATION((C(0x104)==-1)+9,30,0)
            }
            if (P(30,34)) DURATION((C(0x104)==-1)+9,30,0)
            if (P(35,44)) DURATION((C(0x104)==1)+9,30,0)
            if (P(45,47)) DURATION(17,20,5)
            if (P(48,50)) DURATION(16,20,5)
            if (P(51,54)) DURATION(18,20,5)
            WAIT(60)
        }
        if (h>=520.0f) {
            if (P(0,3)) DURATION((C(0x104)==-1)+9,30,0)
            if (P(4,5)) DURATION((C(0x104)==1)+9,30,0)
            WAIT(30)
        }
        if (!(h>=240.0)) return;
        if (P(0,4)) DURATION((C(0x104)==-1)+9,30,0)
        if (P(5,9)) DURATION((C(0x104)==1)+9,30,0)
        if (P(45,47)) DURATION(17,20,5)
        if (P(48,50)) DURATION(16,20,5)
        if (P(51,54)) DURATION(18,20,5)
        WAIT(40)
#undef P
    }
    case 1:
        I(0x6B4)=1;
        if (S(0x768)>0) break;
        S(0x766)=0;
        if (RNG(100)<=10) S(0x768)=static_cast<short>(selector_random_roll(60));
        break;
    case 2:
        I(0x6B4)=-1;
        if (S(0x768)>0) break;
        S(0x766)=0;
        if (RNG(100)<=10) S(0x768)=static_cast<short>(selector_random_roll(60));
        break;
    case 3: I(0x6B4)=C(0x104); I(0x6B8)=-1; if (F(0xF0)>0.0f) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } break;
    case 4: I(0x6B4)=0; I(0x6B8)=-1; if (F(0xF0)>0.0f) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } break;
    case 5: I(0x6B4)=1; I(0x6B8)=-1; if (F(0xF0)>0.0f) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } break;
    case 6: U(0x724)=16; if (F(0xF0)>0.0f) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } break;
    case 7: U(0x724)=4; if (F(0xF0)>0.0f) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } break;
    case 8: U(0x724)=8; if (F(0xF0)>0.0f) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } break;
    case 9:
        I(0x6B4)=C(0x104); I(0x6B8)=0; U(0x724)=(C(0x104)!=1)+1;
        if (S(0x13C)==200 || S(0x13C)==202) {
            if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); }
        }
        else S(0x766)=0;
        break;
    case 10:
        I(0x6B4)=-C(0x104); I(0x6B8)=0; U(0x724)=(C(0x104)==-1)?1:2;
        if (S(0x13C)==201 || S(0x13C)==203) {
            if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); }
        }
        else S(0x766)=0;
        break;
    case 11: I(0x6B4)=C(0x104); I(0x6B8)=-1; I(0x6C8)=1; if (S(0x13C)==214) { if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } } else S(0x766)=0; break;
    case 12: I(0x6B4)=0; I(0x6B8)=-1; I(0x6C8)=1; if (S(0x13C)==214) { if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } } else S(0x766)=0; break;
    case 13: I(0x6B4)=-C(0x104); I(0x6B8)=-1; I(0x6C8)=1; if (S(0x13C)==214) { if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } } else S(0x766)=0; break;
    case 14: I(0x6B4)=C(0x104); I(0x6B8)=0; I(0x6C8)=1; if (S(0x13C)==214) { if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } } else S(0x766)=0; break;
    case 15: I(0x6B4)=-C(0x104); I(0x6B8)=0; I(0x6C8)=1; if (S(0x13C)==214) { if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } } else S(0x766)=0; break;
    case 16: I(0x6B4)=C(0x104); I(0x6B8)=1; I(0x6C8)=1; if (S(0x13C)==214) { if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } } else S(0x766)=0; break;
    case 17: I(0x6B4)=0; I(0x6B8)=1; I(0x6C8)=1; if (S(0x13C)==214) { if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } } else S(0x766)=0; break;
    case 18: I(0x6B4)=-C(0x104); I(0x6B8)=1; I(0x6C8)=1; if (S(0x13C)==214) { if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); } } else S(0x766)=0; break;
    case 100:
        I(0x6B4)=C(0x104); I(0x6B8)=0; I(0x6BC)=0; U(0x724)=(C(0x104)!=1)+1;
        I(0x6C0)=0; I(0x6C4)=0; I(0x6C8)=0;
        if (S(0x768)<=0) { S(0x766)=0; if (RNG(100)<=100) S(0x768)=static_cast<short>(selector_random_roll(60)); break; }
        if (S(0x13C)==200 && h<220.0) I(0x6BC)=2;
        break;
    default: break;
    }
#undef INTERIOR
#undef WALL
#undef WAIT
#undef DURATION
#undef CHOOSE
#undef AIM
#undef OUTPUT
#undef RANGE
#undef PREPARE
#undef RNG
#undef FRONT
#undef PEER_S
#undef PEER
#undef F
#undef C
#undef B
#undef S
#undef U
#undef I
#undef FIELD
}

} // namespace th105
