#include "characters/UdongeActionEntry.hpp"
// JP1.06a 0x005D0E60 Udonge action entry: one switch; the 404 and 650 epilogue scheduling remains nonexact.
// Evidence and finite controls: docs/UDONGE_ACTION_ENTRY_2026_10_24.md.
namespace th105 {
#define FIELD(type,o) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
#define I(o) FIELD(int,o)
void UdongeActionEntryView::initialize_action_entry()
{
    float payload[3];
        switch (action_id_13c) {
        case 4: velocity_x_f4=4.0f; return;
        case 5: velocity_x_f4=-4.0f; return;
        case 50: case 57: case 63: velocity_x_f4=-15.0f; velocity_y_f8=0.0f; F(0x18C)=0.0f; F(0x190)=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 51: velocity_x_f4=-20.0f; velocity_y_f8=0.0f; F(0x18C)=0.0f; F(0x190)=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 53: S(0x730)=0; S(0x732)=0;
        case 52: velocity_x_f4=-25.0f; velocity_y_f8=0.0f; F(0x18C)=0.0f; F(0x190)=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 54: case 60: case 66: velocity_x_f4=0.0f; velocity_y_f8=0.0f; F(0x18C)=0.0f; F(0x190)=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 55: case 58: case 61: case 64: case 67: velocity_x_f4=-20.0f; velocity_y_f8=0.0f; F(0x18C)=0.0f; F(0x190)=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 56: case 62: velocity_x_f4=-10.0f; velocity_y_f8=0.0f; F(0x18C)=0.0f; F(0x190)=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 59: case 65: S(0x730)=0; S(0x732)=0; velocity_x_f4=-25.0f; velocity_y_f8=0.0f; F(0x18C)=0.0f; F(0x190)=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 70:
            S(0x730)=0; velocity_x_f4=-F(0x18C); velocity_y_f8=F(0x190); acceleration_y_100=0.8f;
            if (velocity_x_f4>0.0f) S(0x730)=1;
            if (velocity_x_f4<0.0f) S(0x730)=-1;
            F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 71:
            velocity_x_f4=-F(0x18C); velocity_y_f8=F(0x190); acceleration_y_100=0.5f; S(0x730)=7; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 72:
            velocity_x_f4=-F(0x18C); velocity_y_f8=F(0x190); acceleration_y_100=1.3f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 73: case 88:
            velocity_x_f4=-F(0x18C); velocity_y_f8=F(0x190); acceleration_y_100=0.8f; S(0x730)=7; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 74: case 75:
            velocity_x_f4=-F(0x18C); velocity_y_f8=F(0x190); acceleration_y_100=0.8f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 76: {
            advance_secondary_event_effect_cycle();
            int n=5;
            do { emit_effect(201,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1); } while (--n);
            ++S(0x730); F(0x108)=static_cast<float>(S(0x7A0)); F(0x10C)=static_cast<float>(S(0x7A2)); S(0x186)=5;
            emit_effect(38,x_ec-facing_104*50,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
            emit_effect(59,x_ec-facing_104*50,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
            velocity_x_f4=0.0f; velocity_y_f8=0.0f; acceleration_y_100=0.0f;
            publish_battle_layout_scalar(2.0f); dispatch_indexed_event_member(22); F(0x12C)=0.0f; reset_action_visual_state(); return;
        }
        case 77:
            velocity_x_f4=-F(0x18C); velocity_y_f8=F(0x190); acceleration_y_100=0.8f;
            F(0x108)=static_cast<float>(S(0x7A0)); F(0x10C)=static_cast<float>(S(0x7A2)); F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 78: {
            advance_secondary_event_effect_cycle();
            int n=5;
            do { emit_effect(201,x_ec,y_f0,static_cast<unsigned char>(facing_104),1); } while (--n);
            ++S(0x730); velocity_x_f4=0.0f; velocity_y_f8=0.0f; acceleration_y_100=0.0f;
            publish_battle_layout_scalar(4.0f); dispatch_indexed_event_member(22);
            emit_effect(38,x_ec-facing_104*50,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
            emit_effect(59,x_ec-facing_104*50,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1);
            F(0x12C)=0.0f; reset_action_visual_state(); return;
        }
        case 89: {
            advance_secondary_event_effect_cycle(); emit_effect(58,x_ec,0.0f,static_cast<unsigned char>(facing_104),-1);
            int n=5;
            do { emit_effect(201,x_ec,static_cast<float>(y_f0+100.0),static_cast<unsigned char>(facing_104),1); } while (--n);
            F(0x12C)=0.0f; reset_action_visual_state(); return;
        }
        case 97: {
            advance_secondary_event_effect_cycle(); emit_effect(58,x_ec,0.0f,static_cast<unsigned char>(facing_104),-1);
            int n=5;
            do { emit_effect(201,x_ec,y_f0,static_cast<unsigned char>(facing_104),1); } while (--n);
            F(0x12C)=0.0f; reset_action_visual_state(); return;
        }
        case 98:
            zero_velocity_acceleration(); B(0x47F)=0; S(0x730)=0; reset_action_visual_state(); return;
        case 99:
            zero_velocity_acceleration(); F(0x73C)=0.0f; F(0x740)=0.0f; F(0x744)=0.0f;
            B(0x47F)=0; F(0x748)=0.0f; S(0x730)=0; S(0x732)=0; F(0x74C)=0.0f;
            S(0x734)=0; S(0x736)=0; S(0x738)=0; return;
        case 140:
            velocity_x_f4=-11.0f; S(0x730)=0; velocity_y_f8=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 143: case 144:
            velocity_x_f4=-12.0f; S(0x730)=0; velocity_y_f8=0.0f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 145:
            velocity_x_f4=-10.0f; velocity_y_f8=14.0f; acceleration_y_100=0.5f; F(0x12C)=0.0f; reset_action_visual_state(); return;
        case 149:
            velocity_x_f4=-10.0f; velocity_y_f8=14.0f; acceleration_y_100=0.5f; reset_action_visual_state(); return;
        case 214:
            velocity_x_f4=0.0f; S(0x736)=0; velocity_y_f8=0.0f; acceleration_y_100=0.6f;
            F(0x108)=0.0f; F(0x10C)=95.0f; F(0x73C)=9.0f; F(0x74C)=0.0f; return;
        case 300: case 301:
            if (!B(0x47E)) zero_velocity_acceleration(); phase_state_180=0; B(0x184)=1; return;
        case 302:
            if (!B(0x47E)) zero_velocity_acceleration(); B(0x184)=1; phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 303: case 321: case 322:
            if (!B(0x47E)) zero_velocity_acceleration(); phase_state_180=0; B(0x184)=1; return;
        case 304:
            B(0x47E)=0; B(0x184)=1; phase_state_180=0; zero_velocity_acceleration(); B(0x750)=1; return;
        case 305: velocity_y_f8=0.0f; velocity_x_f4=12.5f; acceleration_y_100=0.0f;
        case 320: B(0x47E)=0; phase_state_180=0; B(0x184)=1; return;
        case 306: S(0x730)=0; phase_state_180=0; B(0x184)=1; return;
        case 307:
            B(0x184)=1; phase_state_180=0; B(0x750)=1; velocity_x_f4*=0.2f; velocity_y_f8=0.2f*velocity_y_f8; acceleration_y_100=0.0f; return;
        case 308: {
            acceleration_y_100=0.5f;
            payload[0]=velocity_x_f4; payload[1]=velocity_y_f8; payload[2]=5.0f;
            B(0x750)=1; B(0x184)=1; phase_state_180=0; S(0x7A6)=0;
            spawn_owned_object_via_manager(848,x_ec,y_f0,static_cast<unsigned char>(facing_104),1,reinterpret_cast<const unsigned *>(payload),3);
            S(0x730)=0; velocity_y_f8=5.5f; return;
        }
        case 309: B(0x750)=1; B(0x184)=1; phase_state_180=0; return;
        case 310:
            velocity_x_f4=0.0f; velocity_y_f8=0.0f; S(0x730)=0; phase_state_180=0; acceleration_y_100=0.5f; B(0x184)=99; return;
        case 400:
            phase_state_180=0; zero_velocity_acceleration(); S(0x730)=0; S(0x732)=0; S(0x734)=0; B(0x750)=1; return;
        case 401: case 402: case 411:
            phase_state_180=0; zero_velocity_acceleration(); S(0x730)=0; S(0x732)=0; S(0x736)=0; B(0x750)=1; return;
        case 404:
        case 406:
            acceleration_y_100 = 0.0f;
            phase_state_180 = 0;
            S(0x730) = 0;
            S(0x732) = 0;
            S(0x736) = 0;
            velocity_x_f4 *= 0.2f;
            B(0x750) = 1;
            velocity_y_f8 = 0.2f * velocity_y_f8;
            return;
        case 408:
            velocity_x_f4=17.5f; velocity_y_f8=0.0f; B(0x47E)=0; S(0x730)=0; B(0x184)=1; phase_state_180=0; return;
        case 409:
            acceleration_y_100=0.35f; B(0x47E)=0; S(0x730)=0; B(0x184)=1; phase_state_180=0; return;
        case 410:
            phase_state_180=0; zero_velocity_acceleration(); S(0x730)=0; S(0x732)=0; S(0x736)=0; S(0x738)=0; B(0x750)=1; return;
        case 412:
            phase_state_180=0; zero_velocity_acceleration(); return;
        case 414: case 415: case 416:
            S(0x730)=0; S(0x732)=0; S(0x736)=0; velocity_x_f4*=0.25f; phase_state_180=1;
            B(0x750)=1; velocity_y_f8=0.25f*velocity_y_f8; acceleration_y_100=0.0f; return;
        case 418:
            velocity_x_f4=12.0f; phase_state_180=0; B(0x47E)=0; B(0x184)=1; return;
        case 500: case 501: B(0x17C)=0; zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 505: case 506: B(0x17C)=4; zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 510: case 511: B(0x17C)=8; zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 520: case 521: B(0x17C)=1; zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 525: case 526:
            F(0x73C)=0.0f; S(0x730)=0; S(0x732)=0; B(0x17C)=5; zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 527: case 528:
            F(0x73C)=0.0f; S(0x730)=0; acceleration_y_100=0.0f; S(0x732)=0; B(0x17C)=5;
            velocity_x_f4*=0.1f; velocity_y_f8=0.1f*velocity_y_f8; phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 529: zero_velocity_acceleration(); B(0x47E)=0; return;
        case 530: case 531: B(0x17C)=9; zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 540: case 541:
            B(0x17C)=2; phase_state_180=0; zero_velocity_acceleration(); S(0x730)=0; S(0x732)=0; S(0x734)=0; B(0x750)=1; return;
        case 545: case 546:
            B(0x17C)=6; phase_state_180=0; zero_velocity_acceleration(); S(0x730)=0; S(0x732)=0; S(0x734)=0; B(0x750)=1; return;
        case 550: case 551:
            B(0x17C)=10; phase_state_180=0; zero_velocity_acceleration(); S(0x730)=0; S(0x732)=0; S(0x734)=0; S(0x736)=0; B(0x750)=1;
            if (C(0x60E)>=4) { S(0x4AE)=2; S(0x736)=1; } return;
        case 560: case 561:
            B(0x17C)=3; phase_state_180=0; zero_velocity_acceleration(); S(0x730)=0; S(0x732)=0; B(0x750)=1; return;
        case 565: case 566: case 567: case 568:
            B(0x17C)=7; phase_state_180=0; zero_velocity_acceleration(); F(0x73C)=0.0f;
            S(0x730)=0; F(0x740)=0.0f; B(0x750)=1; return;
        case 600: case 606: case 607: case 608:
            zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; return;
        case 602: case 605: case 652: case 655:
            S(0x730)=0; S(0x732)=0; phase_state_180=1; zero_velocity_acceleration(); return;
        case 603:
            zero_velocity_acceleration(); S(0x730)=0; phase_state_180=0; B(0x47E)=0; return;
        case 609:
            zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; S(0x730)=0; return;
        case 650:
            acceleration_y_100 = 0.0f;
            phase_state_180 = 0;
            B(0x47E) = 0;
            velocity_x_f4 *= 0.1f;
            velocity_y_f8 = 0.1f * velocity_y_f8;
            return;
        case 700: return;
        case 701: case 702: case 703:
            if (B(0x47E)) return; zero_velocity_acceleration(); return;
        case 704: case 707: zero_velocity_acceleration(); return;
        case 705: velocity_x_f4=6.0f; return;
        case 706: velocity_x_f4=-6.0f; return;
        case 708: velocity_x_f4=0.0f;
        case 709: S(0x730)=0; return;
        case 710:
            F(0x73C)=0.0f; S(0x730)=0; S(0x732)=0; zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 725:
            phase_state_180=0; zero_velocity_acceleration(); S(0x730)=0; S(0x732)=0; S(0x734)=0; return;
        case 726:
            F(0x73C)=0.0f; S(0x730)=0; S(0x732)=0; B(0x17C)=5; zero_velocity_acceleration(); phase_state_180=0; B(0x47E)=0; B(0x750)=1; return;
        case 730:
            zero_velocity_acceleration(); F(0x73C)=0.0f; S(0x730)=0; S(0x732)=0; S(0x734)=0; S(0x736)=0; return;
        case 797: case 798:
            zero_velocity_acceleration(); velocity_y_f8=0.0f; S(0x7A6)=0; S(0x730)=0; dispatch_character_wave_handle(9); return;
        default: initialize_common_action_state(); return;
        }
}
#undef I
#undef C
#undef B
#undef S
#undef F
#undef FIELD
}
