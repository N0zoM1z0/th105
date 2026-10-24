#include "characters/SakuyaObjectActionEntry.hpp"
// JP1.06a 0x004E8060: complete source candidate, nonexact.
// Evidence and finite trials: docs/SAKUYA_OBJECT_ENTRY_2026_10_24.md.
namespace th105 {
#define FIELD(type,offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this)+(offset)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define I(o) FIELD(int,o)
#define H FIELD(float *,0x340)
#define MOTION reinterpret_cast<SakuyaEntryMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define SELECT() if (H[2]>0.0f) select_sequence(static_cast<int>(H[2]))
#define SPAWN(action,count) spawn_parented(action,F(0xEC),F(0xF0),B(0x104),-1,reinterpret_cast<const unsigned *>(payload),count)
__forceinline static float random_float(int n) { return static_cast<float>(static_cast<unsigned>(selector_random_roll(n))); }
void SakuyaObjectEntryView::initialize_action_entry()
{
    F(0xF4)=0.0f; F(0xF8)=0.0f;
    F(0x370)=0.0f; F(0x374)=0.0f; F(0x378)=0.0f; F(0x37C)=0.0f;
    S(0x384)=0; F(0x380)=0.0f; S(0x386)=0; B(0x184)=0;
    S(0x364)=0; S(0x366)=0; S(0x368)=0; S(0x36A)=0; S(0x36C)=0;
    switch (S(0x13C)) {
    case 800: {
        float payload[4];
        B(0x184)=1; F(0x12C)=H[0]; SELECT();
        if (S(0x13E)<=2) {
            MOTION->set_components(H[0],H[1]);
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=3.0f; SPAWN(800,3);
        }
        if (S(0x13E)>=4 && S(0x13E)<=6) {
            MOTION->set_components(H[0],H[1]);
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=7.0f; SPAWN(800,3);
        }
        return;
    }
    case 801: {
        float payload[4];
        B(0x184)=1; F(0x12C)=H[0]; SELECT();
        if (S(0x13E)<=2) {
            MOTION->set_components(H[0],H[1]);
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=3.0f; SPAWN(801,3);
        }
        return;
    }
    case 803: {
        float payload[4];
        B(0x184)=1; F(0x12C)=H[0]; F(0x374)=255.0f; SELECT();
        if (S(0x13E)==0 || S(0x13E)==3) {
            MOTION->set_components(H[0],H[1]);
            payload[0]=F(0x12C); payload[1]=0.0f; payload[2]=2.0f; SPAWN(803,3);
        }
        return;
    }
    case 805:
        B(0x184)=1; F(0x12C)=H[0]; SELECT(); return;
    case 810:
        F(0x124)=0.0f; B(0x17C)=0; F(0x128)=0.0f; S(0x344)=1; SELECT(); return;
    case 811: {
        float payload[4];
        B(0x17C)=1; B(0x184)=3; SELECT();
        if (S(0x13E)==0) {
            MOTION->set_components(H[0],H[1]); F(0x12C)=-atan2_degrees(F(0xF8),F(0xF4));
            payload[0]=F(0x12C); payload[1]=0.0f; payload[2]=3.0f; SPAWN(811,3);
        }
        return;
    }
    case 812: {
        float payload[4];
        B(0x17C)=2; B(0x184)=1; F(0x12C)=H[0]; SELECT();
        if (S(0x13E)==0) { payload[0]=H[0]; payload[1]=0.0f; payload[2]=1.0f; SPAWN(812,3); }
        return;
    }
    case 813:
        F(0x370)=1.0f; B(0x17C)=3; S(0x344)=1; SELECT();
        if (S(0x13E)<=5) {
            F(0x12C)=random_float(90)-45.0;
            S(0x364)=static_cast<short>(selector_random_roll(11));
            S(0x366)=static_cast<short>(selector_random_roll(11));
            S(0x368)=static_cast<short>(selector_random_roll(11));
            S(0x36A)=static_cast<short>(selector_random_roll(5));
            S(0x36C)=static_cast<short>(selector_random_roll(5));
            F(0xF4)=random_float(9)-4.0;
            F(0xF8)=-random_float(10)*static_cast<double>(0.1f);
        }
        if (S(0x13E)==6 || S(0x13E)==7 || S(0x13E)==9 || S(0x13E)==10) {
            F(0xF8)=H[1]; F(0xF4)=H[0];
        }
        return;
    case 815:
        F(0x124)=0.0f; B(0x17C)=4; F(0x128)=0.0f;
        S(0x364)=static_cast<short>(static_cast<int>(F(0xEC)));
        S(0x366)=static_cast<short>(static_cast<int>(F(0xF0)));
        B(0x184)=1; I(0x180)=0; F(0x12C)=H[0]; SELECT();
        if (S(0x13E)==2) F(0x370)=0.5f;
        if (S(0x13E)==3) F(0x370)=0.5f;
        if (S(0x13E)==4) F(0x370)=0.6f;
        return;
    case 816: {
        float payload[4];
        B(0x17C)=5;
        if (*reinterpret_cast<signed char *>(FIELD(unsigned char *,0x348)+0x609)==4) {
            B(0x184)=6; if (H[3]==1.0f) B(0x184)=7;
        } else { B(0x184)=5; if (H[3]==1.0f) B(0x184)=6; }
        F(0x374)=255.0f; SELECT();
        if (S(0x13E)==0) {
            MOTION->set_components(H[0],H[1]); F(0x12C)=-atan2_degrees(F(0xF8),F(0xF4));
            payload[0]=F(0x12C); payload[1]=0.0f; payload[2]=3.0f; SPAWN(816,3);
        }
        return;
    }
    case 817: B(0x17C)=6;
    case 802:
        B(0x184)=1; F(0x12C)=H[0]; SELECT();
        if (S(0x13E)<=2) MOTION->set_components(H[0],H[1]);
        return;
    case 818:
        B(0x17C)=7; B(0x184)=1; F(0x12C)=H[0]; I(0x180)=0; SELECT();
        if (S(0x13E)==0) { S(0x344)=1; MOTION->set_components(H[0],H[1]); }
        if (S(0x13E)==2) { S(0x344)=1; F(0x11C)=1.5f; F(0x120)=1.5f; }
        return;
    case 849: S(0x344)=1; SELECT(); return;
    case 804: case 850:
        B(0x184)=1; F(0x12C)=H[0]; SELECT(); return;
    case 851: S(0x344)=1; B(0x113)=0; SELECT(); return;
    case 852: {
        F(0x120)=F(0x11C)=static_cast<float>(random_float(7)*static_cast<double>(0.1f)+1.0);
        F(0x124)=static_cast<unsigned>(selector_random_roll(50))+30.0f+(static_cast<unsigned>(selector_random_roll(100))<50)*180;
        F(0x12C)=random_float(60); F(0x128)=random_float(90)-25.0;
        SELECT();
        if (S(0x13E)==0) F(0xF4)=random_float(12);
        if (S(0x13E)==1) { B(0x184)=1; MOTION->set_components(static_cast<float>(random_float(90)-45.0),20.0f); }
        return;
    }
    case 853: {
        float payload[4];
        B(0x184)=1; F(0x12C)=H[0]; SELECT();
        if (S(0x13E)==1) {
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=4.0f; payload[3]=0.0f; SPAWN(853,4);
            payload[2]=5.0f; SPAWN(853,4);
        }
        return;
    }
    case 854: B(0x113)=0; S(0x344)=1; SELECT(); return;
    case 855:
        SELECT();
        if (S(0x13E)==0) {
            F(0xF4)=random_float(12);
            F(0x120)=F(0x11C)=static_cast<float>(random_float(9)*static_cast<double>(0.1f)+static_cast<double>(1.7f));
            F(0x124)=static_cast<unsigned>(selector_random_roll(50))+30.0f+(static_cast<unsigned>(selector_random_roll(100))<50)*180;
            F(0x12C)=random_float(60); F(0x128)=random_float(90)-25.0;
        }
        if (S(0x13E)==1) {
            F(0x120)=2.0f; H[1]=60.0f; H[0]=static_cast<unsigned>(selector_random_roll(40))-20.0f; F(0x12C)=H[0];
        }
        if (S(0x13E)==2) { B(0x184)=1; MOTION->set_components(static_cast<float>(random_float(80)-40.0),60.0f); }
        return;
    case 856: {
        float payload[4];
        B(0x184)=1; SELECT();
        if (S(0x13E)==0) {
            MOTION->set_components(H[0],H[1]); F(0x12C)=-atan2_degrees(F(0xF8),F(0xF4));
            payload[0]=F(0x12C); payload[1]=0.0f; payload[2]=3.0f; SPAWN(856,3);
        }
        return;
    }
    case 857: {
        float payload[4];
        B(0x184)=1; F(0x12C)=H[0]; SELECT();
        if (S(0x13E)==0 || S(0x13E)==1) {
            MOTION->set_components(H[0],H[1]);
            if (S(0x13E)==0) { payload[0]=H[0]; payload[1]=0.0f; payload[2]=2.0f; SPAWN(857,3); }
            if (S(0x13E)==1) { payload[0]=H[0]; payload[1]=0.0f; payload[2]=3.0f; SPAWN(857,3); }
        }
        return;
    }
    case 858: {
        float payload[4];
        B(0x184)=1; F(0x12C)=H[0]; SELECT();
        if (S(0x13E)==0) {
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=1.0f; payload[3]=0.0f; SPAWN(858,3);
            MOTION->set_components(H[0],H[1]);
        }
        if (S(0x13E)==2) {
            payload[0]=0.0f; payload[1]=0.0f; payload[2]=3.0f; payload[3]=0.0f;
            spawn_unparented(858,F(0xEC),F(0xF0),B(0x104),1,reinterpret_cast<const unsigned *>(payload),4);
        }
        return;
    }
    case 859: {
        float payload[4];
        SELECT();
        if (S(0x13E)==0) {
            F(0x11C)=0.0f; F(0x120)=0.0f; B(0x113)=128;
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=1.0f;
            spawn_parented(859,F(0xEC),F(0xF0),1,-1,reinterpret_cast<const unsigned *>(payload),3);
            payload[2]=2.0f; spawn_parented(859,F(0xEC),F(0xF0),1,-1,reinterpret_cast<const unsigned *>(payload),3);
            payload[2]=3.0f; spawn_parented(859,F(0xEC),F(0xF0),1,-1,reinterpret_cast<const unsigned *>(payload),3);
            MOTION->set_components(H[0],H[1]);
        }
        if (S(0x13E)==1) { F(0x11C)=0.0f; F(0x120)=0.0f; }
        if (S(0x13E)==2) { F(0x12C)=random_float(360); F(0x11C)=0.0f; F(0x120)=0.0f; }
        if (S(0x13E)==3) { F(0x12C)=random_float(360); F(0x11C)=0.0f; F(0x120)=0.0f; }
        if (S(0x13E)==4) F(0x370)=0.75f;
        if (S(0x13E)==5) F(0x370)=0.75f;
        if (S(0x13E)==6) F(0x370)=0.9f;
        return;
    }
    case 900: {
        float payload[4];
        B(0x184)=1; SELECT();
        if (S(0x13E)==0) {
            MOTION->set_components(H[0],H[1]); F(0x12C)=-atan2_degrees(F(0xF8),F(0xF4));
            payload[0]=F(0x12C); payload[1]=0.0f; payload[2]=3.0f; SPAWN(856,3);
        }
        return;
    }
    case 901: {
        float payload[4];
        SELECT();
        if (S(0x13E)==0) {
            F(0x11C)=0.0f; F(0x120)=0.0f; B(0x113)=128;
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=1.0f;
            spawn_parented(901,F(0xEC),F(0xF0),1,-1,reinterpret_cast<const unsigned *>(payload),3);
            payload[2]=2.0f; spawn_parented(901,F(0xEC),F(0xF0),1,-1,reinterpret_cast<const unsigned *>(payload),3);
            payload[2]=3.0f; spawn_parented(901,F(0xEC),F(0xF0),1,-1,reinterpret_cast<const unsigned *>(payload),3);
            MOTION->set_components(H[0],H[1]);
        }
        if (S(0x13E)==1) { F(0x11C)=0.0f; F(0x120)=0.0f; }
        if (S(0x13E)==2) { F(0x12C)=random_float(360); F(0x11C)=0.0f; F(0x120)=0.0f; }
        if (S(0x13E)==3) { F(0x12C)=random_float(360); F(0x11C)=0.0f; F(0x120)=0.0f; }
        if (S(0x13E)==4) F(0x370)=0.75f;
        if (S(0x13E)==5) F(0x370)=0.75f;
        if (S(0x13E)==6) F(0x370)=0.9f;
        if (S(0x13E)==7) {
            double const heading=H[0]; B(0x184)=1; F(0x12C)=heading; MOTION->set_components(H[0],H[1]);
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=8.0f; SPAWN(901,3);
        }
        if (S(0x13E)==8) F(0x12C)=H[0];
        return;
    }
    case 920: {
        float payload[4];
        F(0x12C)=H[0]; SELECT();
        if (S(0x13E)<=1) {
            F(0x374)=10.0f; F(0x370)=random_float(10)+20.0;
            if (static_cast<unsigned>(selector_random_roll(100))<50) F(0x370)*=-1.0;
            B(0x184)=1; S(0x344)=1; MOTION->set_components(H[0],H[1]);
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=3.0f; SPAWN(920,3);
        }
        if (S(0x13E)==2) {
            B(0x184)=1; MOTION->set_components(H[0],H[1]);
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=3.0f; SPAWN(920,3);
        }
        if (S(0x13E)==3) { S(0x344)=1; F(0x12C)=H[0]; }
        return;
    }
    case 930: {
        float payload[4];
        F(0x12C)=H[0]; SELECT();
        if (S(0x13E)<=1) {
            F(0x374)=10.0f; F(0x370)=random_float(10)+20.0;
            if (static_cast<unsigned>(selector_random_roll(100))<50) F(0x370)*=-1.0;
            B(0x184)=1; S(0x344)=1; MOTION->set_components(H[0],H[1]);
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=3.0f; SPAWN(930,3);
        }
        if (S(0x13E)==2) {
            B(0x184)=1; MOTION->set_components(H[0],H[1]);
            payload[0]=H[0]; payload[1]=0.0f; payload[2]=3.0f; SPAWN(930,3);
        }
        if (S(0x13E)==3) { S(0x344)=1; F(0x12C)=H[0]; }
        return;
    }
    case 980: continue_action_980(); return;
    case 998: return;
    case 999:
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E)==4) { F(0xF4)=H[0]; F(0xF8)=H[1]; }
        return;
    }
}
#undef SPAWN
#undef SELECT
#undef MOTION
#undef H
#undef I
#undef B
#undef S
#undef F
#undef FIELD
}
