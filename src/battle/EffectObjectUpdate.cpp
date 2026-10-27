namespace th105 {
unsigned __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int limit);
float __cdecl lookup_orientation_sine(int angle);
extern int g_fighter_state_4b8_default;
extern short g_info_mode_value_6fa88c;
// Pointer-only EffectObject runtime view; never instantiated or allocated.
struct EffectObjectUpdateView {
    void update_659aa0();
    void emit_fighter_effect_433cc0(int id, float x, float y, int facing, int layer);
    void dispatch_indexed_event_member(unsigned id);
    unsigned char advance_frame_and_dispatch();
};
struct EffectObjectMotionView { void set_components(float angle, float magnitude); };
#define MOTION reinterpret_cast<EffectObjectMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define FIELD(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) FIELD(this,float,o)
#define I(o) FIELD(this,int,o)
#define S(o) FIELD(this,short,o)
#define B(o) FIELD(this,unsigned char,o)
#define C(o) FIELD(this,signed char,o)
#define CONTEXT FIELD(this,void *,0x164)
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define RF(n) static_cast<float>(R(n))
#define MT(n) (mt19937_next_u32() % (n##u))
#define EMIT(id,layer) emit_fighter_effect_433cc0(id,F(0xec),F(0xf0),B(0x104),layer)
#define BURST(count,id) { for (int repeat=count; repeat!=0; --repeat) { EMIT(id,1); } }
#define PAIRS(count) { for (int repeat=count; repeat!=0; --repeat) { EMIT(102,1); EMIT(103,1); } }
#define FINISH { if (advance_frame_and_dispatch()) --I(0x158); return; }
#define KILL { --I(0x158); return; }
void EffectObjectUpdateView::update_659aa0()
{
    short action = S(0x13c);
    switch (action) {
    case 1:
        if (I(0x144) == 0) {
            F(0x12c) = static_cast<float>(MT(360));
            BURST(4,101);
        }
        FINISH;
    case 2:
        if (I(0x144) == 0) {
            F(0x12c) = static_cast<float>(MT(360));
            BURST(6,101);
            PAIRS(3);
        }
        FINISH;
    case 3:
        if (I(0x144) == 0) {
            F(0x12c) = static_cast<float>(MT(360));
            EMIT(100,1);
            BURST(8,101);
            PAIRS(6);
        }
        FINISH;
    case 4:
        if (I(0x144) == 0) {
            F(0x12c) = static_cast<float>(MT(360));
            EMIT(104,1);
            BURST(10,101);
            PAIRS(6);
        }
        FINISH;
    case 5:
        if (I(0x144) == 0) {
            F(0x12c) = static_cast<float>(MT(360));
            BURST(4,101);
        }
        FINISH;
    case 6:
        if (I(0x144) == 0) {
            F(0x12c) = static_cast<float>(MT(360));
            BURST(6,101);
            PAIRS(3);
        }
        FINISH;
    case 7:
        if (I(0x144) == 0) {
            F(0x12c) = static_cast<float>(MT(360));
            EMIT(100,1);
            BURST(8,101);
            PAIRS(3);
        }
        F(0x11c) += 0.1f; F(0x120) = F(0x11c);
        FINISH;
    case 8:
        if (I(0x144) == 0) {
            F(0x12c) = static_cast<float>(MT(360));
            EMIT(100,1);
            BURST(10,101);
            PAIRS(5);
        }
        F(0x11c) += 0.1f; F(0x120) = F(0x11c);
        FINISH;
    case 9:
        if (I(0x144) == 0) F(0x12c) = static_cast<float>(static_cast<float>(MT(40)) - 20.0);
        FINISH;
    case 10:
        if (I(0x144) == 0) F(0x12c) = static_cast<float>(static_cast<float>(MT(40)) - 20.0);
        FINISH;
    case 11:
        if (I(0x144) == 0) F(0x12c) = static_cast<float>(static_cast<float>(MT(40)) - 20.0);
        FINISH;
    case 12:
        if (I(0x144) == 0) F(0x12c) = static_cast<float>(static_cast<float>(MT(40)) - 20.0);
        FINISH;
    case 13:
        if (I(0x144) == 0) { EMIT(105,1); F(0x12c)=static_cast<float>(MT(360)); BURST(4,102); }
        FINISH;
    case 14:
        if (I(0x144) == 0) { F(0x12c)=static_cast<float>(MT(360)); EMIT(106,1); BURST(6,102); }
        FINISH;
    case 15:
        if (I(0x144) == 0) F(0x12c)=static_cast<float>(MT(360));
        FINISH;
    case 16:
        if (I(0x144) == 0) F(0x12c)=static_cast<float>(MT(360));
        FINISH;
    case 38:
        if (I(0x144) == 0) F(0x12c)=static_cast<float>(MT(360));
        FINISH;
    case 50:
        if (I(0x144) == 0) { BURST(4,101); }
        FINISH;
    case 51:
        if (I(0x144) == 0) { BURST(4,103); }
        FINISH;
    case 52:
        if (I(0x144) == 0) { dispatch_indexed_event_member(37); BURST(3,101); }
        FINISH;
    case 53: {
        if (I(0x144) == 0) {
            dispatch_indexed_event_member(38); EMIT(104,1);
            BURST(16,101); PAIRS(8); BURST(3,200); BURST(6,201);
        }
        unsigned char alpha=B(0x113);
        F(0x12c) += 5.0; F(0x11c) += 0.3f; F(0x120) += 0.3f;
        if (alpha <= 10) KILL;
        B(0x113)=alpha-10; B(0x112)-=10; B(0x111)-=10;
        FINISH;
    }
    case 54: {
        if (I(0x144) == 0) { dispatch_indexed_event_member(25); EMIT(104,1); BURST(8,101); PAIRS(4); }
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (B(0x113)<=10) KILL;
        B(0x113)-=10;
        FINISH;
    }
    case 58: case 59: {
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.4f; F(0x120)=F(0x11c);
        if (alpha<=20) --I(0x158); else B(0x113)=alpha-20;
        FINISH;
    }
    case 61:
        if (I(0x144)==0) dispatch_indexed_event_member(43);
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (B(0x113)<=20) KILL;
        B(0x113)-=20; B(0x112)-=20; B(0x111)-=20;
        FINISH;
    case 62: {
        if (I(0x144)==0) { dispatch_indexed_event_member(45); EMIT(113,1); }
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.2f; F(0x120)+=0.2f;
        if (alpha<=25) KILL;
        B(0x113)=alpha-25; B(0x112)-=25; B(0x111)-=25;
        FINISH;
    }
    case 63:
        if (I(0x144)==0) { dispatch_indexed_event_member(43); EMIT(60,-1); }
        F(0x11c)+=0.1f; F(0x120)+=0.15f;
        FINISH;
    case 64: {
        if (I(0x144)==0) { dispatch_indexed_event_member(50); EMIT(104,1); BURST(16,101); PAIRS(8); }
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (B(0x113)<=10) KILL;
        B(0x113)-=10;
        FINISH;
    }
    case 65: {
        if (I(0x144)==0) { EMIT(104,1); BURST(16,101); PAIRS(8); }
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (B(0x113)<=10) KILL;
        B(0x113)-=10;
        FINISH;
    }
    case 66: {
        if (I(0x144)==0) { EMIT(104,1); BURST(16,101); PAIRS(8); }
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (B(0x113)<=10) KILL;
        B(0x113)-=10;
        FINISH;
    }
    case 67: {
        if (I(0x144)==0) { EMIT(104,1); BURST(16,101); PAIRS(8); }
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (B(0x113)<=10) KILL;
        B(0x113)-=10;
        FINISH;
    }
    case 68: {
        if (I(0x144)==0) { EMIT(104,1); BURST(16,101); PAIRS(8); }
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (B(0x113)<=10) KILL;
        B(0x113)-=10;
        FINISH;
    }
    case 69: {
        if (I(0x144)==0) dispatch_indexed_event_member(35);
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (alpha<=15) KILL;
        F(0x12c)-=25.0; B(0x113)=alpha-15; B(0x111)-=15; B(0x110)-=15;
        FINISH;
    }
    case 70: {
        if (I(0x144)==0) dispatch_indexed_event_member(53);
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.3f; F(0x120)+=0.3f;
        if (alpha<=15) KILL;
        F(0x12c)-=25.0; B(0x113)=alpha-15; B(0x111)-=15; B(0x110)-=15;
        FINISH;
    }
    case 71:
        if (I(0x144)==0) dispatch_indexed_event_member(54);
        if (S(0x140)==0) { F(0x11c)*=0.8f; F(0x120)=F(0x11c); }
        if (S(0x140)==1) {
            unsigned char alpha=B(0x113);
            F(0x11c)+=0.3f; F(0x120)=F(0x11c); F(0x12c)-=25.0;
            if (alpha<=15) KILL;
            B(0x110)-=15; B(0x113)=alpha-15;
        }
        FINISH;
    case 100:
        F(0x11c)+=0.5; F(0x120)=F(0x11c);
        if (B(0x113)<=20) --I(0x158);
        else { B(0x113)-=20; B(0x112)-=20; B(0x111)-=20; }
        FINISH;
    case 101:
        F(0xf8)-=1.0;
        F(0xec)=F(0xf4)+F(0xec);
        F(0xf0)=F(0xf0)+F(0xf8);
        if (F(0xf8)<0.0 && F(0xf0)<0.0 && MT(100)<15)
            F(0xf8)=static_cast<float>(-F(0xf8)*0.5);
        if (B(0x113)<=20) KILL;
        B(0x113)-=20; B(0x112)-=20; B(0x111)-=20;
        F(0x11c)*=0.8f; F(0x120)=F(0x11c);
        if (F(0x11c)<=0.0) KILL;
        FINISH;
    case 102: case 103: {
        unsigned char alpha=B(0x113);
        F(0xec)=static_cast<float>(C(0x104)*F(0xf4)+F(0xec));
        F(0xf0)=F(0xf8)+F(0xf0);
        if (alpha<=10) --I(0x158); else B(0x113)=alpha-10;
        F(0x120)*=0.98f; F(0x11c)+=0.05f;
        FINISH;
    }
    case 104:
        F(0x11c)+=1.25; F(0x120)=F(0x11c);
        if (B(0x113)<=20) --I(0x158);
        else { B(0x113)-=20; B(0x112)-=20; B(0x111)-=20; }
        FINISH;
    case 105: {
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.15f; F(0x120)=F(0x11c);
        if (alpha<=15) --I(0x158);
        else { B(0x113)=alpha-15; B(0x112)-=15; B(0x111)-=15; }
        FINISH;
    }
    case 60: case 106:
        F(0x11c)+=0.4f; F(0x120)=F(0x11c);
        if (B(0x113)<=20) --I(0x158);
        else { B(0x113)-=20; B(0x112)-=20; B(0x111)-=20; }
        FINISH;
    case 112: case 137: {
        void *context=CONTEXT;
        if (!context) KILL;
        F(0xec)=FIELD(context,float,0xec);
        F(0xf0)=static_cast<float>(FIELD(context,float,0xf0)+100.0);
        if (action==112) F(0x12c)+=1.0; else F(0x12c)-=1.0;
        F(0x11c)-=0.3f; F(0x120)-=0.3f;
        if (F(0x11c)<1.0) { F(0x11c)=1.0f; F(0x120)=1.0f; }
        if (S(0x140)==0 && (FIELD(context,short,0x4a2)<100 || FIELD(context,short,0x13c)==99)) {
            S(0x140)=1; S(0x142)=0; return;
        }
        if (S(0x140)==1) {
            if (B(0x113)<=20) KILL;
            B(0x113)-=20; B(0x112)-=20; B(0x111)-=20;
        }
        FINISH;
    }
    case 113: {
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.4f; F(0x120)+=0.4f;
        if (alpha<=15) KILL;
        B(0x113)=alpha-15; B(0x112)-=15; B(0x111)-=15;
        FINISH;
    }
    case 115:
        if (I(0x144)==0) { F(0x12c)=static_cast<float>(MT(360)); F(0x11c)=2.0f; F(0x120)=2.0f; }
        F(0x12c)+=2.0;
        if (S(0x140)==41) {
            if (B(0x113)<5) KILL;
            B(0x113)-=5;
        }
        FINISH;
    case 123:
        if (I(0x144)==0) F(0xf8)=-10.0f;
        if (B(0x113)<15) KILL;
        B(0x113)-=15; B(0x112)-=15; B(0x111)-=15;
        F(0xf0)=F(0xf8)+F(0xf0);
        FINISH;
    case 124:
        if (I(0x144)==0) F(0xf4)=-10.0f;
        if (B(0x113)<15) KILL;
        B(0x113)-=15; B(0x112)-=15; B(0x111)-=15;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);
        FINISH;
    case 125: {
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.2f; F(0x120)=F(0x11c);
        if (alpha<25) KILL;
        B(0x113)=alpha-25; B(0x112)-=25; B(0x111)-=25;
        FINISH;
    }
    case 126: case 127: case 128: case 129: FINISH;
    case 131: case 132: case 133: case 134: {
        int time=I(0x144);
        if (time==0) F(0xf8)=20.0f;
        F(0xf8)-=1.0;
        if (F(0xf8)<1.0) F(0xf8)=1.0f;
        F(0x11c)+=0.1f;
        if (F(0x11c)>1.0) F(0x11c)=1.0f;
        F(0x120)=F(0x11c);
        if (time>=60) {
            if (B(0x113)<=15) KILL;
            B(0x113)-=15;
        }
        F(0xf0)=F(0xf8)+F(0xf0);
        FINISH;
    }
    case 136:
        F(0x11c)-=0.005f; F(0x120)+=0.02f; F(0xf0)+=15.0;
        B(0x113)=static_cast<unsigned char>(lookup_orientation_sine(6*I(0x144))*255.0);
        if (6*I(0x144)>=180) KILL;
        FINISH;
    case 140: {
        unsigned char alpha=B(0x113);
        F(0x11c)=static_cast<float>(F(0x170)*0.5+F(0x11c));
        F(0x170)*=0.94f; F(0x120)=F(0x11c);
        if (alpha<5) KILL;
        B(0x113)=alpha-5; B(0x112)-=5; B(0x111)-=5;
        FINISH;
    }
    case 141: {
        unsigned char alpha=B(0x113);
        F(0x11c)*=0.85f; F(0x120)=F(0x11c);
        if (alpha<15) KILL;
        B(0x113)=alpha-15; B(0x112)-=15; B(0x111)-=15;
        FINISH;
    }
    case 135: case 142: {
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.3f; F(0x120)=F(0x11c);
        if (alpha<15) KILL;
        B(0x113)=alpha-15;
        FINISH;
    }
    case 150: case 152: case 154: {
        unsigned char alpha=B(0x113);
        F(0x11c)+=0.15f; F(0x120)=F(0x11c);
        if (alpha<15) KILL;
        B(0x113)=alpha-15;
        FINISH;
    }
    case 151: case 153: case 155:
        if (F(0x170)==0.0) {
            if (B(0x113)>=240) { B(0x113)=255; F(0x170)=1.0f; }
            else B(0x113)+=15;
        } else {
            if (B(0x113)<15) KILL;
            B(0x113)-=15;
        }
        F(0xf0)+=10.0;
        FINISH;
    case 160: {
        int time=I(0x144);
        if (time>=25) {
            if (B(0x113)<15) KILL;
            B(0x113)-=15;
        }
        if (time%6==0) EMIT(161,-1);
        F(0x12c)+=6.0; F(0xf8)-=0.3f; F(0xf4)*=0.96f;
        if (F(0xf0)+F(0xf8)<=0.0 && F(0xf8)<0.0) F(0xf8)=-F(0xf8);
        F(0xec)=F(0xf4)*C(0x104)+F(0xec);
        F(0xf0)=F(0xf8)+F(0xf0);
        FINISH;
    }
    case 161:
        if (B(0x113)<15) KILL;
        B(0x113)-=15; F(0xf8)-=0.005f; F(0xf0)=F(0xf8)+F(0xf0);
        FINISH;
    case 162: case 163: case 164: {
        int decay=static_cast<int>(F(0x170));
        unsigned char alpha=B(0x113);
        if (alpha<static_cast<signed char>(decay)) KILL;
        B(0x113)=static_cast<unsigned char>(alpha-decay);
        F(0x12c)=F(0x174)+F(0x12c);
        F(0xf8)-=0.3f; F(0xf4)*=0.92f;
        if (F(0xf0)+F(0xf8)<=0.0 && F(0xf8)<0.0) F(0xf8)=-F(0xf8);
        F(0xec)=F(0xf4)*C(0x104)+F(0xec); F(0xf0)=F(0xf8)+F(0xf0);
        FINISH;
    }
    case 165:
        if (B(0x113)<15) KILL;
        F(0x12c)-=15.0; B(0x113)-=15;
        F(0x11c)+=0.3f; F(0x120)=F(0x11c);
        FINISH;
    case 200:
        if (I(0x144)==0) {
            float speed=static_cast<float>(RF(10)+5.0);
            MOTION->set_components(-RF(180),speed);
        }
        F(0x12c)+=6.0; F(0xf8)-=0.5;
        if (R(100)<20) EMIT(202,1);
        if (F(0xf8)<0.0 && F(0xf0)<0.0) {
            if (R(100)<20) F(0xf8)=static_cast<float>(-F(0xf8)*0.5);
            I(0x144)=60;
        }
        if (I(0x144)>60) {
            if (B(0x113)>=15) B(0x113)-=15;
            else {
                if (g_fighter_state_4b8_default==16) {
                    g_info_mode_value_6fa88c+=40;
                    if (g_info_mode_value_6fa88c>999) g_info_mode_value_6fa88c=999;
                } else if (g_info_mode_value_6fa88c>=41) g_info_mode_value_6fa88c-=40;
                else g_info_mode_value_6fa88c=1;
                dispatch_indexed_event_member(26);
                KILL;
            }
        }
        F(0xec)=C(0x104)*F(0xf4)+F(0xec); F(0xf0)=F(0xf8)+F(0xf0);
        FINISH;
    case 201:
        if (I(0x144)==0) {
            float speed=static_cast<float>(RF(8)+4.0);
            MOTION->set_components(-RF(180),speed);
        }
        F(0x12c)-=12.0; F(0xf8)-=0.25;
        if (R(100)<10) EMIT(202,1);
        if (F(0xf8)<0.0 && F(0xf0)<0.0) {
            if (R(100)<20) F(0xf8)=static_cast<float>(-F(0xf8)*0.5);
            I(0x144)=60;
        }
        if (I(0x144)>60) {
            if (B(0x113)>=15) B(0x113)-=15;
            else {
                if (g_fighter_state_4b8_default==16) {
                    g_info_mode_value_6fa88c+=5;
                    if (g_info_mode_value_6fa88c>999) g_info_mode_value_6fa88c=999;
                } else if (g_info_mode_value_6fa88c>=6) g_info_mode_value_6fa88c-=5;
                else g_info_mode_value_6fa88c=1;
                dispatch_indexed_event_member(26);
                KILL;
            }
        }
        F(0xec)=C(0x104)*F(0xf4)+F(0xec); F(0xf0)=F(0xf8)+F(0xf0);
        FINISH;
    case 202:
        if (I(0x144)==0) MOTION->set_components(-RF(360),1.0f);
        F(0xf8)-=0.05f;
        if (F(0x11c)>0.0) { F(0x11c)-=0.01f; F(0x120)-=0.01f; }
        if (B(0x113)<15) KILL;
        B(0x113)-=15; B(0x110)-=10;
        F(0xec)=C(0x104)*F(0xf4)+F(0xec);
        B(0x111)-=10; F(0xf0)=F(0xf8)+F(0xf0);
        FINISH;
    case 300: advance_frame_and_dispatch(); return;
    default: return;
    }
}
#undef MOTION
#undef KILL
#undef FINISH
#undef PAIRS
#undef BURST
#undef EMIT
#undef MT
#undef RF
#undef R
#undef CONTEXT
#undef C
#undef B
#undef S
#undef I
#undef F
#undef FIELD
} // namespace th105
