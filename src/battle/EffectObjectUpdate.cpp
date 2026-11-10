#include "battle/EffectObjectState.hpp"
namespace th105 {
unsigned __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int limit);
float __cdecl lookup_orientation_sine(int angle);
extern int g_fighter_state_4b8_default;
extern short g_info_mode_value_6fa88c;
// Pointer-only EffectObject runtime view; never instantiated or allocated.
struct EffectObjectUpdateView : EffectObjectState {
    void update_659aa0();
    void emit_fighter_effect_433cc0(int id, float x, float y, int facing, int layer);
    void dispatch_indexed_event_member(unsigned id);
    unsigned char advance_frame_and_dispatch();
};
struct EffectObjectMotionView { void set_components(float angle, float magnitude); };
#define MOTION reinterpret_cast<EffectObjectMotionView *>(reinterpret_cast<unsigned char *>(this)+4)
#define R(n) static_cast<unsigned>(selector_random_roll(n))
#define RF(n) static_cast<float>(R(n))
#define MT(n) (mt19937_next_u32() % (n##u))
#define EMIT(id,layer) emit_fighter_effect_433cc0(id,x_0ec,y_0f0,static_cast<unsigned char>(facing_104),layer)
#define BURST(count,id) { for (int repeat=count; repeat!=0; --repeat) { EMIT(id,1); } }
#define PAIRS(count) { for (int repeat=count; repeat!=0; --repeat) { EMIT(102,1); EMIT(103,1); } }
#define FINISH { if (advance_frame_and_dispatch()) --state_158; return; }
#define KILL { --state_158; return; }
void EffectObjectUpdateView::update_659aa0()
{
    short action = action_13c;
    switch (action) {
    case 1:
        if (time_144 == 0) {
            angle_z_12c = static_cast<float>(MT(360));
            BURST(4,101);
        }
        FINISH;
    case 2:
        if (time_144 == 0) {
            angle_z_12c = static_cast<float>(MT(360));
            BURST(6,101);
            PAIRS(3);
        }
        FINISH;
    case 3:
        if (time_144 == 0) {
            angle_z_12c = static_cast<float>(MT(360));
            EMIT(100,1);
            BURST(8,101);
            PAIRS(6);
        }
        FINISH;
    case 4:
        if (time_144 == 0) {
            angle_z_12c = static_cast<float>(MT(360));
            EMIT(104,1);
            BURST(10,101);
            PAIRS(6);
        }
        FINISH;
    case 5:
        if (time_144 == 0) {
            angle_z_12c = static_cast<float>(MT(360));
            BURST(4,101);
        }
        FINISH;
    case 6:
        if (time_144 == 0) {
            angle_z_12c = static_cast<float>(MT(360));
            BURST(6,101);
            PAIRS(3);
        }
        FINISH;
    case 7:
        if (time_144 == 0) {
            angle_z_12c = static_cast<float>(MT(360));
            EMIT(100,1);
            BURST(8,101);
            PAIRS(3);
        }
        scale_x_11c += 0.1f; scale_y_120 = scale_x_11c;
        FINISH;
    case 8:
        if (time_144 == 0) {
            angle_z_12c = static_cast<float>(MT(360));
            EMIT(100,1);
            BURST(10,101);
            PAIRS(5);
        }
        scale_x_11c += 0.1f; scale_y_120 = scale_x_11c;
        FINISH;
    case 9:
        if (time_144 == 0) angle_z_12c = static_cast<float>(static_cast<float>(MT(40)) - 20.0);
        FINISH;
    case 10:
        if (time_144 == 0) angle_z_12c = static_cast<float>(static_cast<float>(MT(40)) - 20.0);
        FINISH;
    case 11:
        if (time_144 == 0) angle_z_12c = static_cast<float>(static_cast<float>(MT(40)) - 20.0);
        FINISH;
    case 12:
        if (time_144 == 0) angle_z_12c = static_cast<float>(static_cast<float>(MT(40)) - 20.0);
        FINISH;
    case 13:
        if (time_144 == 0) { EMIT(105,1); angle_z_12c=static_cast<float>(MT(360)); BURST(4,102); }
        FINISH;
    case 14:
        if (time_144 == 0) { angle_z_12c=static_cast<float>(MT(360)); EMIT(106,1); BURST(6,102); }
        FINISH;
    case 15:
        if (time_144 == 0) angle_z_12c=static_cast<float>(MT(360));
        FINISH;
    case 16:
        if (time_144 == 0) angle_z_12c=static_cast<float>(MT(360));
        FINISH;
    case 38:
        if (time_144 == 0) angle_z_12c=static_cast<float>(MT(360));
        FINISH;
    case 50:
        if (time_144 == 0) { BURST(4,101); }
        FINISH;
    case 51:
        if (time_144 == 0) { BURST(4,103); }
        FINISH;
    case 52:
        if (time_144 == 0) { dispatch_indexed_event_member(37); BURST(3,101); }
        FINISH;
    case 53: {
        if (time_144 == 0) {
            dispatch_indexed_event_member(38); EMIT(104,1);
            BURST(16,101); PAIRS(8); BURST(3,200); BURST(6,201);
        }
        unsigned char alpha=alpha_113;
        angle_z_12c += 5.0; scale_x_11c += 0.3f; scale_y_120 += 0.3f;
        if (alpha <= 10) KILL;
        alpha_113=alpha-10; red_112-=10; green_111-=10;
        FINISH;
    }
    case 54: {
        if (time_144 == 0) { dispatch_indexed_event_member(25); EMIT(104,1); BURST(8,101); PAIRS(4); }
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha_113<=10) KILL;
        alpha_113-=10;
        FINISH;
    }
    case 58: case 59: {
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.4f; scale_y_120=scale_x_11c;
        if (alpha<=20) --state_158; else alpha_113=alpha-20;
        FINISH;
    }
    case 61:
        if (time_144==0) dispatch_indexed_event_member(43);
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha_113<=20) KILL;
        alpha_113-=20; red_112-=20; green_111-=20;
        FINISH;
    case 62: {
        if (time_144==0) { dispatch_indexed_event_member(45); EMIT(113,1); }
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.2f; scale_y_120+=0.2f;
        if (alpha<=25) KILL;
        alpha_113=alpha-25; red_112-=25; green_111-=25;
        FINISH;
    }
    case 63:
        if (time_144==0) { dispatch_indexed_event_member(43); EMIT(60,-1); }
        scale_x_11c+=0.1f; scale_y_120+=0.15f;
        FINISH;
    case 64: {
        if (time_144==0) { dispatch_indexed_event_member(50); EMIT(104,1); BURST(16,101); PAIRS(8); }
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha_113<=10) KILL;
        alpha_113-=10;
        FINISH;
    }
    case 65: {
        if (time_144==0) { EMIT(104,1); BURST(16,101); PAIRS(8); }
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha_113<=10) KILL;
        alpha_113-=10;
        FINISH;
    }
    case 66: {
        if (time_144==0) { EMIT(104,1); BURST(16,101); PAIRS(8); }
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha_113<=10) KILL;
        alpha_113-=10;
        FINISH;
    }
    case 67: {
        if (time_144==0) { EMIT(104,1); BURST(16,101); PAIRS(8); }
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha_113<=10) KILL;
        alpha_113-=10;
        FINISH;
    }
    case 68: {
        if (time_144==0) { EMIT(104,1); BURST(16,101); PAIRS(8); }
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha_113<=10) KILL;
        alpha_113-=10;
        FINISH;
    }
    case 69: {
        if (time_144==0) dispatch_indexed_event_member(35);
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha<=15) KILL;
        angle_z_12c-=25.0; alpha_113=alpha-15; green_111-=15; blue_110-=15;
        FINISH;
    }
    case 70: {
        if (time_144==0) dispatch_indexed_event_member(53);
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.3f; scale_y_120+=0.3f;
        if (alpha<=15) KILL;
        angle_z_12c-=25.0; alpha_113=alpha-15; green_111-=15; blue_110-=15;
        FINISH;
    }
    case 71:
        if (time_144==0) dispatch_indexed_event_member(54);
        if (frame_140==0) { scale_x_11c*=0.8f; scale_y_120=scale_x_11c; }
        if (frame_140==1) {
            unsigned char alpha=alpha_113;
            scale_x_11c+=0.3f; scale_y_120=scale_x_11c; angle_z_12c-=25.0;
            if (alpha<=15) KILL;
            blue_110-=15; alpha_113=alpha-15;
        }
        FINISH;
    case 100:
        scale_x_11c+=0.5; scale_y_120=scale_x_11c;
        if (alpha_113<=20) --state_158;
        else { alpha_113-=20; red_112-=20; green_111-=20; }
        FINISH;
    case 101:
        velocity_y_0f8-=1.0;
        x_0ec=velocity_x_0f4+x_0ec;
        y_0f0=y_0f0+velocity_y_0f8;
        if (velocity_y_0f8<0.0 && y_0f0<0.0 && MT(100)<15)
            velocity_y_0f8=static_cast<float>(-velocity_y_0f8*0.5);
        if (alpha_113<=20) KILL;
        alpha_113-=20; red_112-=20; green_111-=20;
        scale_x_11c*=0.8f; scale_y_120=scale_x_11c;
        if (scale_x_11c<=0.0) KILL;
        FINISH;
    case 102: case 103: {
        unsigned char alpha=alpha_113;
        x_0ec=static_cast<float>(facing_104*velocity_x_0f4+x_0ec);
        y_0f0=velocity_y_0f8+y_0f0;
        if (alpha<=10) --state_158; else alpha_113=alpha-10;
        scale_y_120*=0.98f; scale_x_11c+=0.05f;
        FINISH;
    }
    case 104:
        scale_x_11c+=1.25; scale_y_120=scale_x_11c;
        if (alpha_113<=20) --state_158;
        else { alpha_113-=20; red_112-=20; green_111-=20; }
        FINISH;
    case 105: {
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.15f; scale_y_120=scale_x_11c;
        if (alpha<=15) --state_158;
        else { alpha_113=alpha-15; red_112-=15; green_111-=15; }
        FINISH;
    }
    case 60: case 106:
        scale_x_11c+=0.4f; scale_y_120=scale_x_11c;
        if (alpha_113<=20) --state_158;
        else { alpha_113-=20; red_112-=20; green_111-=20; }
        FINISH;
    case 112: case 137: {
        EffectObjectContextState *context=context_164;
        if (!context) KILL;
        x_0ec=context->x_0ec;
        y_0f0=static_cast<float>(context->y_0f0+100.0);
        if (action==112) angle_z_12c+=1.0; else angle_z_12c-=1.0;
        scale_x_11c-=0.3f; scale_y_120-=0.3f;
        if (scale_x_11c<1.0) { scale_x_11c=1.0f; scale_y_120=1.0f; }
        if (frame_140==0 && (context->value_4a2<100 || context->action_13c==99)) {
            frame_140=1; frame_142=0; return;
        }
        if (frame_140==1) {
            if (alpha_113<=20) KILL;
            alpha_113-=20; red_112-=20; green_111-=20;
        }
        FINISH;
    }
    case 113: {
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.4f; scale_y_120+=0.4f;
        if (alpha<=15) KILL;
        alpha_113=alpha-15; red_112-=15; green_111-=15;
        FINISH;
    }
    case 115:
        if (time_144==0) { angle_z_12c=static_cast<float>(MT(360)); scale_x_11c=2.0f; scale_y_120=2.0f; }
        angle_z_12c+=2.0;
        if (frame_140==41) {
            if (alpha_113<5) KILL;
            alpha_113-=5;
        }
        FINISH;
    case 123:
        if (time_144==0) velocity_y_0f8=-10.0f;
        if (alpha_113<15) KILL;
        alpha_113-=15; red_112-=15; green_111-=15;
        y_0f0=velocity_y_0f8+y_0f0;
        FINISH;
    case 124:
        if (time_144==0) velocity_x_0f4=-10.0f;
        if (alpha_113<15) KILL;
        alpha_113-=15; red_112-=15; green_111-=15;
        x_0ec=facing_104*velocity_x_0f4+x_0ec;
        FINISH;
    case 125: {
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.2f; scale_y_120=scale_x_11c;
        if (alpha<25) KILL;
        alpha_113=alpha-25; red_112-=25; green_111-=25;
        FINISH;
    }
    case 126: case 127: case 128: case 129: FINISH;
    case 131: case 132: case 133: case 134: {
        int time=time_144;
        if (time==0) velocity_y_0f8=20.0f;
        velocity_y_0f8-=1.0;
        if (velocity_y_0f8<1.0) velocity_y_0f8=1.0f;
        scale_x_11c+=0.1f;
        if (scale_x_11c>1.0) scale_x_11c=1.0f;
        scale_y_120=scale_x_11c;
        if (time>=60) {
            if (alpha_113<=15) KILL;
            alpha_113-=15;
        }
        y_0f0=velocity_y_0f8+y_0f0;
        FINISH;
    }
    case 136:
        scale_x_11c-=0.005f; scale_y_120+=0.02f; y_0f0+=15.0;
        alpha_113=static_cast<unsigned char>(lookup_orientation_sine(6*time_144)*255.0);
        if (6*time_144>=180) KILL;
        FINISH;
    case 140: {
        unsigned char alpha=alpha_113;
        scale_x_11c=static_cast<float>(state_170*0.5+scale_x_11c);
        state_170*=0.94f; scale_y_120=scale_x_11c;
        if (alpha<5) KILL;
        alpha_113=alpha-5; red_112-=5; green_111-=5;
        FINISH;
    }
    case 141: {
        unsigned char alpha=alpha_113;
        scale_x_11c*=0.85f; scale_y_120=scale_x_11c;
        if (alpha<15) KILL;
        alpha_113=alpha-15; red_112-=15; green_111-=15;
        FINISH;
    }
    case 135: case 142: {
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.3f; scale_y_120=scale_x_11c;
        if (alpha<15) KILL;
        alpha_113=alpha-15;
        FINISH;
    }
    case 150: case 152: case 154: {
        unsigned char alpha=alpha_113;
        scale_x_11c+=0.15f; scale_y_120=scale_x_11c;
        if (alpha<15) KILL;
        alpha_113=alpha-15;
        FINISH;
    }
    case 151: case 153: case 155:
        if (state_170==0.0) {
            if (alpha_113>=240) { alpha_113=255; state_170=1.0f; }
            else alpha_113+=15;
        } else {
            if (alpha_113<15) KILL;
            alpha_113-=15;
        }
        y_0f0+=10.0;
        FINISH;
    case 160: {
        int time=time_144;
        if (time>=25) {
            if (alpha_113<15) KILL;
            alpha_113-=15;
        }
        if (time%6==0) EMIT(161,-1);
        angle_z_12c+=6.0; velocity_y_0f8-=0.3f; velocity_x_0f4*=0.96f;
        if (y_0f0+velocity_y_0f8<=0.0 && velocity_y_0f8<0.0) velocity_y_0f8=-velocity_y_0f8;
        x_0ec=velocity_x_0f4*facing_104+x_0ec;
        y_0f0=velocity_y_0f8+y_0f0;
        FINISH;
    }
    case 161:
        if (alpha_113<15) KILL;
        alpha_113-=15; velocity_y_0f8-=0.005f; y_0f0=velocity_y_0f8+y_0f0;
        FINISH;
    case 162: case 163: case 164: {
        int decay=static_cast<int>(state_170);
        unsigned char alpha=alpha_113;
        if (alpha<static_cast<signed char>(decay)) KILL;
        alpha_113=static_cast<unsigned char>(alpha-decay);
        angle_z_12c=state_174+angle_z_12c;
        velocity_y_0f8-=0.3f; velocity_x_0f4*=0.92f;
        if (y_0f0+velocity_y_0f8<=0.0 && velocity_y_0f8<0.0) velocity_y_0f8=-velocity_y_0f8;
        x_0ec=velocity_x_0f4*facing_104+x_0ec; y_0f0=velocity_y_0f8+y_0f0;
        FINISH;
    }
    case 165:
        if (alpha_113<15) KILL;
        angle_z_12c-=15.0; alpha_113-=15;
        scale_x_11c+=0.3f; scale_y_120=scale_x_11c;
        FINISH;
    case 200:
        if (time_144==0) {
            float speed=static_cast<float>(RF(10)+5.0);
            MOTION->set_components(-RF(180),speed);
        }
        angle_z_12c+=6.0; velocity_y_0f8-=0.5;
        if (R(100)<20) EMIT(202,1);
        if (velocity_y_0f8<0.0 && y_0f0<0.0) {
            if (R(100)<20) velocity_y_0f8=static_cast<float>(-velocity_y_0f8*0.5);
            time_144=60;
        }
        if (time_144>60) {
            if (alpha_113>=15) alpha_113-=15;
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
        x_0ec=facing_104*velocity_x_0f4+x_0ec; y_0f0=velocity_y_0f8+y_0f0;
        FINISH;
    case 201:
        if (time_144==0) {
            float speed=static_cast<float>(RF(8)+4.0);
            MOTION->set_components(-RF(180),speed);
        }
        angle_z_12c-=12.0; velocity_y_0f8-=0.25;
        if (R(100)<10) EMIT(202,1);
        if (velocity_y_0f8<0.0 && y_0f0<0.0) {
            if (R(100)<20) velocity_y_0f8=static_cast<float>(-velocity_y_0f8*0.5);
            time_144=60;
        }
        if (time_144>60) {
            if (alpha_113>=15) alpha_113-=15;
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
        x_0ec=facing_104*velocity_x_0f4+x_0ec; y_0f0=velocity_y_0f8+y_0f0;
        FINISH;
    case 202:
        if (time_144==0) MOTION->set_components(-RF(360),1.0f);
        velocity_y_0f8-=0.05f;
        if (scale_x_11c>0.0) { scale_x_11c-=0.01f; scale_y_120-=0.01f; }
        if (alpha_113<15) KILL;
        alpha_113-=15; blue_110-=10;
        x_0ec=facing_104*velocity_x_0f4+x_0ec;
        green_111-=10; y_0f0=velocity_y_0f8+y_0f0;
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
} // namespace th105
