namespace th105 {
extern int g_event_effect_id;
extern int g_secondary_event_effect_id;
extern int g_fighter_state_4b8_default;
int __cdecl get_game_mode();
double __cdecl lookup_orientation_cosine_quantized_abs(float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
struct InfoEffectUpdateView {
    int emit_info_effect_6609c0(int, float, float, int, int);
    int dispatch_info_state_6609f0(int);
    void update_65cb40();
    unsigned char advance_frame_and_dispatch();
    void dispatch_indexed_event_member(unsigned);
};
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define I(o) FIELD(int,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
void InfoEffectUpdateView::update_65cb40()
{
    switch (S(0x13c)) {
    case 1:
        F(0x11c) = static_cast<float>(F(0x11c) + 0.2f);
        F(0x120) = static_cast<float>(F(0x120) + 0.2f);
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 2:
        if (I(0x144) == 0) dispatch_indexed_event_member(47);
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 10: case 11: case 12: case 13:
        if (I(0x144) == 0) emit_info_effect_6609c0(20,F(0xec),F(0xf0),1,1);
        if (I(0x144) < 15) {
            F(0x11c) = static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(I(0x144) * 6.0)) + 1.0);
            F(0x120) = F(0x11c);
        } else {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.001f);
            F(0x120) = static_cast<float>(F(0x120) - 0.001f);
            if (I(0x144) == 90) {
                emit_info_effect_6609c0(15,F(0xec),F(0xf0),1,1);
                emit_info_effect_6609c0(21,F(0xec),F(0xf0),1,1);
                --I(0x158);
                return;
            }
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 15: {
        if (I(0x144) == 30) dispatch_info_state_6609f0(1);
        if (F(0x11c) <= 1.5) {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.2f);
            F(0x120) = static_cast<float>(F(0x120) + 0.2f);
        } else {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.001f);
            F(0x120) = static_cast<float>(F(0x120) + 0.001f);
        }
        if (I(0x144) >= 30) {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.5);
            F(0x120) = static_cast<float>(F(0x120) + 0.5);
            if (B(0x113) < 15) { --I(0x158); return; }
            B(0x113) -= 15;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    }
    case 16: {
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(22,F(0xec),F(0xf0),1,1);
            dispatch_indexed_event_member(44);
        }
        if (F(0x11c) <= 1.5) {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.2f);
            F(0x120) = static_cast<float>(F(0x120) + 0.2f);
        } else {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.001f);
            F(0x120) = static_cast<float>(F(0x120) + 0.001f);
        }
        if (I(0x144) >= 60) {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.5);
            F(0x120) = static_cast<float>(F(0x120) + 0.5);
            if (B(0x113) < 15) { --I(0x158); return; }
            B(0x113) -= 15;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    }
    case 17: {
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(22,F(0xec),F(0xf0),1,1);
        }
        if (F(0x11c) <= 2.0) {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.2f);
            F(0x120) = static_cast<float>(F(0x120) + 0.2f);
        } else {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.001f);
            F(0x120) = static_cast<float>(F(0x120) + 0.001f);
        }
        if (I(0x144) >= 120) {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.5);
            F(0x120) = static_cast<float>(F(0x120) + 0.5);
            if (B(0x113) < 15) { --I(0x158); return; }
            B(0x113) -= 15;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    }
    case 18: {
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(22,F(0xec),F(0xf0),1,1);
        }
        if (F(0x11c) <= 1.5) {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.2f);
            F(0x120) = static_cast<float>(F(0x120) + 0.2f);
        } else {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.001f);
            F(0x120) = static_cast<float>(F(0x120) + 0.001f);
        }
        if (I(0x144) >= 60) {
            F(0x11c) = static_cast<float>(F(0x11c) + 0.5);
            F(0x120) = static_cast<float>(F(0x120) + 0.5);
            if (B(0x113) < 15) { --I(0x158); return; }
            B(0x113) -= 15;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    }
    case 20:
        F(0x11c) = static_cast<float>(F(0x11c) + 0.001f);
        F(0x120) = static_cast<float>(F(0x120) + 0.001f);
        if (I(0x144) == 90) { --I(0x158); return; }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 21: case 22:
        F(0x11c) = static_cast<float>(F(0x11c) + 0.3f);
        F(0x120) = static_cast<float>(F(0x120) + 0.3f);
        if (B(0x113) < 15) { --I(0x158); return; }
        B(0x113) -= 15;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 30: case 31:
        B(0x113) = static_cast<unsigned char>(127.0 - lookup_orientation_cosine_quantized_abs(static_cast<float>(I(0x144) * 12.0)) * 127.0);
        ++I(0x144);
        return;
    case 32: case 33: if (advance_frame_and_dispatch()) --I(0x158); return;
    case 100:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(103,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_event_effect_id == 0 && g_fighter_state_4b8_default != 16 && get_game_mode() != 0) emit_info_effect_6609c0(105,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(101,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 0) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 101: case 111: case 121: case 131: case 141: case 151: case 161: case 171: case 181: case 191: case 201: case 211: case 221: case 231: case 241: case 251: case 261:
        B(0x113) = static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(static_cast<float>(3 * I(0x144))) * 255.0);
        F(0x11c) = static_cast<float>(F(0x11c) + 0.01f);
        F(0x120) = F(0x11c);
        if (I(0x144) >= 60) { --I(0x158); return; }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 102: case 112: case 122: case 132: case 142: case 152: case 162: case 172: case 182: case 192: case 202: case 212: case 222: case 232: case 242: case 252: case 262:
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        if (I(0x144) >= 30) I(0x144) = 30;
        F(0x11c) = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(3 * I(0x144))) * 20.0 + 1.0);
        F(0x120) = F(0x11c);
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 103:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 0) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 104:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 0) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 105:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 110:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(113,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 1) emit_info_effect_6609c0(115,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(111,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 1) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 113:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 1) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 114:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 1) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 115:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 1) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 120:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(123,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 2) emit_info_effect_6609c0(125,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(121,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 2) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 123:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 2) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 124:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 2) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 125:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 2) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 130:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(133,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 3) emit_info_effect_6609c0(135,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(131,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 3) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 133:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 3) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 134:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 3) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 135:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 3) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 140:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(143,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 4) emit_info_effect_6609c0(145,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(141,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 4) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 143:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 4) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 144:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 4) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 145:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 4) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 150:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(153,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 5) emit_info_effect_6609c0(155,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(151,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 5) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 153:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 5) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 154:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 5) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 155:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 5) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 160:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(163,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 6) emit_info_effect_6609c0(165,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(161,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 6) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 163:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 6) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 164:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 6) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 165:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 6) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 170:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(173,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 7) emit_info_effect_6609c0(175,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(171,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 7) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 173:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 7) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 174:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 7) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 175:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 7) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 180:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(183,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 8) emit_info_effect_6609c0(185,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(181,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 8) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 183:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 8) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 184:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 8) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 185:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 8) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 190:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(193,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 9) emit_info_effect_6609c0(195,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(191,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 9) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 193:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 9) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 194:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 9) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 195:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 9) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 200:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(203,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 17) emit_info_effect_6609c0(205,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(201,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 17) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 203:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 17) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 204:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 17) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 205:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 17) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 210:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(213,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_event_effect_id == 10 && g_fighter_state_4b8_default != 16 && get_game_mode() != 0) emit_info_effect_6609c0(215,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(211,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 10) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 213:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 10) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 214:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 10) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 215:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 10) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 220:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(223,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 11) emit_info_effect_6609c0(225,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(221,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 11) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 223:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 11) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 224:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 11) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 225:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 11) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 230:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(233,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 12) emit_info_effect_6609c0(235,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(231,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 12) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 233:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 12) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 234:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 12) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 235:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 12) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 240:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(243,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_fighter_state_4b8_default == 13) emit_info_effect_6609c0(245,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(241,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 13) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 243:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 13) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 244:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 13) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 245:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 13) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 250:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(253,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            if (g_event_effect_id == 14 && g_fighter_state_4b8_default != 16 && get_game_mode() != 0) emit_info_effect_6609c0(255,320.0f,120.0f,1,1);
        }
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(251,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (g_event_effect_id != 14) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 253:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_event_effect_id != 14) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 254:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (F(0x174) == 0.0) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (g_secondary_event_effect_id != 14) F(0x174) = 1.0f;
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 255:
        if (F(0x174) == 0.0) {
            F(0x11c) = static_cast<float>(F(0x11c) - 0.25);
            F(0x120) = F(0x11c);
            if (F(0x11c) <= 1.0) {
                if (B(0x113) <= 240) B(0x113) += 15;
                else B(0x113) = 255;
                F(0x11c) = 1.0f; F(0x120) = 1.0f; F(0x174) = 1.0f;
            }
        } else {
            F(0x174) = static_cast<float>(F(0x174) + 1.0);
            if (F(0x174) >= 90.0) {
                F(0x120) = static_cast<float>(F(0x120) * 0.95f);
                F(0x11c) = static_cast<float>(F(0x11c) + 0.1f);
            if (B(0x113) <= 15) { --I(0x158); return; }
            B(0x113) -= 15;
            }
        }
        if (g_event_effect_id == 14) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 260:
        if (I(0x144) == 0) emit_info_effect_6609c0(263,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
        if (g_event_effect_id == 15) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
            if (I(0x144) % 60 == 0) emit_info_effect_6609c0(261,F(0xec),F(0xf0),1,2);
        } else {
            if (B(0x113) <= 10) { --I(0x158); return; }
            B(0x113) -= 10;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 263:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (g_event_effect_id == 15) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 264:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (g_secondary_event_effect_id == 15) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 270:
        if (I(0x144) == 0) {
            emit_info_effect_6609c0(273,F(0xec),static_cast<float>(F(0xf0)-10.0),1,1);
            --I(0x158);
            return;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 273:
        if (g_event_effect_id == 16 && g_secondary_event_effect_id == 16) {
            if (B(0x113) < 240) B(0x113) += 15;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 274:
        F(0x11c) = static_cast<float>(F(0x11c) - 0.1f);
        if (F(0x11c) < 1.0) F(0x11c) = 1.0f;
        F(0x120) = F(0x11c);
        if (g_secondary_event_effect_id == 16) {
            if (B(0x113) < 245) B(0x113) += 10;
            else B(0x113) = 255;
        } else {
            if (B(0x113) <= 20) { --I(0x158); return; }
            B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158); return;
    case 900: case 901: case 902: case 903: case 904: case 905: case 906: case 907: case 908: case 909: case 910: case 911: case 912: case 913: case 914: case 915: case 916: case 917: case 918: case 919: case 920: case 921: case 922:
        if (S(0x142) > 150) {
            B(0x113) -= 5;
            if (B(0x113) == 0) --I(0x158);
        }
        if (S(0x142) < 30)
            F(0xec) = static_cast<float>((1.0 - lookup_orientation_sine_quantized_abs(static_cast<float>(S(0x142) * 3.0))) * 480.0 + 640.0);
        if (advance_frame_and_dispatch()) --I(0x158); return;
    default: return;
    }
}
}
