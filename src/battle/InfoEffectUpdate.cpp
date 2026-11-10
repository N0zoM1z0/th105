#include "battle/InfoEffectState.hpp"
class InfoEffectObject;
namespace th105 {
extern int g_event_effect_id;
extern int g_secondary_event_effect_id;
extern int g_fighter_state_4b8_default;
int __cdecl get_game_mode();
double __cdecl lookup_orientation_cosine_quantized_abs(float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
struct InfoEffectUpdateView : InfoEffectState {
    InfoEffectObject *emit_info_effect_6609c0(int, float, float, int, int);
    int dispatch_info_state_6609f0(int);
    void update_65cb40();
    unsigned char advance_frame_and_dispatch();
    void dispatch_indexed_event_member(unsigned);
};
void InfoEffectUpdateView::update_65cb40()
{
    switch (action_13c) {
    case 1:
        scale_x_11c = static_cast<float>(scale_x_11c + 0.2f);
        scale_y_120 = static_cast<float>(scale_y_120 + 0.2f);
        if (advance_frame_and_dispatch()) --state_158; return;
    case 2:
        if (time_144 == 0) dispatch_indexed_event_member(47);
        if (advance_frame_and_dispatch()) --state_158; return;
    case 10: case 11: case 12: case 13:
        if (time_144 == 0) emit_info_effect_6609c0(20,x_0ec,y_0f0,1,1);
        if (time_144 < 15) {
            scale_x_11c = static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(time_144 * 6.0)) + 1.0);
            scale_y_120 = scale_x_11c;
        } else {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.001f);
            scale_y_120 = static_cast<float>(scale_y_120 - 0.001f);
            if (time_144 == 90) {
                emit_info_effect_6609c0(15,x_0ec,y_0f0,1,1);
                emit_info_effect_6609c0(21,x_0ec,y_0f0,1,1);
                --state_158;
                return;
            }
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 15: {
        if (time_144 == 30) dispatch_info_state_6609f0(1);
        if (scale_x_11c <= 1.5) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.2f);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.2f);
        } else {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.001f);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.001f);
        }
        if (time_144 >= 30) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.5);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.5);
            if (alpha_113 < 15) { --state_158; return; }
            alpha_113 -= 15;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    }
    case 16: {
        if (time_144 == 0) {
            emit_info_effect_6609c0(22,x_0ec,y_0f0,1,1);
            dispatch_indexed_event_member(44);
        }
        if (scale_x_11c <= 1.5) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.2f);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.2f);
        } else {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.001f);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.001f);
        }
        if (time_144 >= 60) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.5);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.5);
            if (alpha_113 < 15) { --state_158; return; }
            alpha_113 -= 15;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    }
    case 17: {
        if (time_144 == 0) {
            emit_info_effect_6609c0(22,x_0ec,y_0f0,1,1);
        }
        if (scale_x_11c <= 2.0) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.2f);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.2f);
        } else {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.001f);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.001f);
        }
        if (time_144 >= 120) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.5);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.5);
            if (alpha_113 < 15) { --state_158; return; }
            alpha_113 -= 15;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    }
    case 18: {
        if (time_144 == 0) {
            emit_info_effect_6609c0(22,x_0ec,y_0f0,1,1);
        }
        if (scale_x_11c <= 1.5) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.2f);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.2f);
        } else {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.001f);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.001f);
        }
        if (time_144 >= 60) {
            scale_x_11c = static_cast<float>(scale_x_11c + 0.5);
            scale_y_120 = static_cast<float>(scale_y_120 + 0.5);
            if (alpha_113 < 15) { --state_158; return; }
            alpha_113 -= 15;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    }
    case 20:
        scale_x_11c = static_cast<float>(scale_x_11c + 0.001f);
        scale_y_120 = static_cast<float>(scale_y_120 + 0.001f);
        if (time_144 == 90) { --state_158; return; }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 21: case 22:
        scale_x_11c = static_cast<float>(scale_x_11c + 0.3f);
        scale_y_120 = static_cast<float>(scale_y_120 + 0.3f);
        if (alpha_113 < 15) { --state_158; return; }
        alpha_113 -= 15;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 30: case 31:
        alpha_113 = static_cast<unsigned char>(127.0 - lookup_orientation_cosine_quantized_abs(static_cast<float>(time_144 * 12.0)) * 127.0);
        ++time_144;
        return;
    case 32: case 33: if (advance_frame_and_dispatch()) --state_158; return;
    case 100:
        if (time_144 == 0) {
            emit_info_effect_6609c0(103,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_event_effect_id == 0 && g_fighter_state_4b8_default != 16 && get_game_mode() != 0) emit_info_effect_6609c0(105,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(101,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 0) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 101: case 111: case 121: case 131: case 141: case 151: case 161: case 171: case 181: case 191: case 201: case 211: case 221: case 231: case 241: case 251: case 261:
        alpha_113 = static_cast<unsigned char>(lookup_orientation_sine_quantized_abs(static_cast<float>(3 * time_144)) * 255.0);
        scale_x_11c = static_cast<float>(scale_x_11c + 0.01f);
        scale_y_120 = scale_x_11c;
        if (time_144 >= 60) { --state_158; return; }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 102: case 112: case 122: case 132: case 142: case 152: case 162: case 172: case 182: case 192: case 202: case 212: case 222: case 232: case 242: case 252: case 262:
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        if (time_144 >= 30) time_144 = 30;
        scale_x_11c = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(3 * time_144)) * 20.0 + 1.0);
        scale_y_120 = scale_x_11c;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 103:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 0) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 104:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 0) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 105:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 110:
        if (time_144 == 0) {
            emit_info_effect_6609c0(113,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 1) emit_info_effect_6609c0(115,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(111,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 1) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 113:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 1) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 114:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 1) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 115:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 1) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 120:
        if (time_144 == 0) {
            emit_info_effect_6609c0(123,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 2) emit_info_effect_6609c0(125,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(121,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 2) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 123:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 2) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 124:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 2) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 125:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 2) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 130:
        if (time_144 == 0) {
            emit_info_effect_6609c0(133,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 3) emit_info_effect_6609c0(135,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(131,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 3) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 133:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 3) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 134:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 3) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 135:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 3) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 140:
        if (time_144 == 0) {
            emit_info_effect_6609c0(143,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 4) emit_info_effect_6609c0(145,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(141,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 4) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 143:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 4) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 144:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 4) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 145:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 4) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 150:
        if (time_144 == 0) {
            emit_info_effect_6609c0(153,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 5) emit_info_effect_6609c0(155,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(151,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 5) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 153:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 5) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 154:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 5) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 155:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 5) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 160:
        if (time_144 == 0) {
            emit_info_effect_6609c0(163,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 6) emit_info_effect_6609c0(165,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(161,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 6) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 163:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 6) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 164:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 6) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 165:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 6) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 170:
        if (time_144 == 0) {
            emit_info_effect_6609c0(173,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 7) emit_info_effect_6609c0(175,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(171,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 7) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 173:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 7) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 174:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 7) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 175:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 7) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 180:
        if (time_144 == 0) {
            emit_info_effect_6609c0(183,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 8) emit_info_effect_6609c0(185,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(181,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 8) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 183:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 8) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 184:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 8) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 185:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 8) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 190:
        if (time_144 == 0) {
            emit_info_effect_6609c0(193,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 9) emit_info_effect_6609c0(195,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(191,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 9) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 193:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 9) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 194:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 9) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 195:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 9) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 200:
        if (time_144 == 0) {
            emit_info_effect_6609c0(203,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 17) emit_info_effect_6609c0(205,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(201,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 17) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 203:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 17) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 204:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 17) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 205:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 17) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 210:
        if (time_144 == 0) {
            emit_info_effect_6609c0(213,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_event_effect_id == 10 && g_fighter_state_4b8_default != 16 && get_game_mode() != 0) emit_info_effect_6609c0(215,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(211,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 10) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 213:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 10) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 214:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 10) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 215:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 10) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 220:
        if (time_144 == 0) {
            emit_info_effect_6609c0(223,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 11) emit_info_effect_6609c0(225,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(221,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 11) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 223:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 11) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 224:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 11) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 225:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 11) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 230:
        if (time_144 == 0) {
            emit_info_effect_6609c0(233,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 12) emit_info_effect_6609c0(235,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(231,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 12) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 233:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 12) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 234:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 12) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 235:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 12) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 240:
        if (time_144 == 0) {
            emit_info_effect_6609c0(243,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_fighter_state_4b8_default == 13) emit_info_effect_6609c0(245,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(241,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 13) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 243:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 13) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 244:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 13) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 245:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 13) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 250:
        if (time_144 == 0) {
            emit_info_effect_6609c0(253,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            if (g_event_effect_id == 14 && g_fighter_state_4b8_default != 16 && get_game_mode() != 0) emit_info_effect_6609c0(255,320.0f,120.0f,1,1);
        }
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(251,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (g_event_effect_id != 14) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 253:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_event_effect_id != 14) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 254:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (fade_latch_174 == 0.0) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (g_secondary_event_effect_id != 14) fade_latch_174 = 1.0f;
        if (advance_frame_and_dispatch()) --state_158; return;
    case 255:
        if (fade_latch_174 == 0.0) {
            scale_x_11c = static_cast<float>(scale_x_11c - 0.25);
            scale_y_120 = scale_x_11c;
            if (scale_x_11c <= 1.0) {
                if (alpha_113 <= 240) alpha_113 += 15;
                else alpha_113 = 255;
                scale_x_11c = 1.0f; scale_y_120 = 1.0f; fade_latch_174 = 1.0f;
            }
        } else {
            fade_latch_174 = static_cast<float>(fade_latch_174 + 1.0);
            if (fade_latch_174 >= 90.0) {
                scale_y_120 = static_cast<float>(scale_y_120 * 0.95f);
                scale_x_11c = static_cast<float>(scale_x_11c + 0.1f);
            if (alpha_113 <= 15) { --state_158; return; }
            alpha_113 -= 15;
            }
        }
        if (g_event_effect_id == 14) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 260:
        if (time_144 == 0) emit_info_effect_6609c0(263,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
        if (g_event_effect_id == 15) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
            if (time_144 % 60 == 0) emit_info_effect_6609c0(261,x_0ec,y_0f0,1,2);
        } else {
            if (alpha_113 <= 10) { --state_158; return; }
            alpha_113 -= 10;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 263:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (g_event_effect_id == 15) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 264:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (g_secondary_event_effect_id == 15) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 270:
        if (time_144 == 0) {
            emit_info_effect_6609c0(273,x_0ec,static_cast<float>(y_0f0-10.0),1,1);
            --state_158;
            return;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 273:
        if (g_event_effect_id == 16 && g_secondary_event_effect_id == 16) {
            if (alpha_113 < 240) alpha_113 += 15;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 274:
        scale_x_11c = static_cast<float>(scale_x_11c - 0.1f);
        if (scale_x_11c < 1.0) scale_x_11c = 1.0f;
        scale_y_120 = scale_x_11c;
        if (g_secondary_event_effect_id == 16) {
            if (alpha_113 < 245) alpha_113 += 10;
            else alpha_113 = 255;
        } else {
            if (alpha_113 <= 20) { --state_158; return; }
            alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158; return;
    case 900: case 901: case 902: case 903: case 904: case 905: case 906: case 907: case 908: case 909: case 910: case 911: case 912: case 913: case 914: case 915: case 916: case 917: case 918: case 919: case 920: case 921: case 922:
        if (frame_142 > 150) {
            alpha_113 -= 5;
            if (alpha_113 == 0) --state_158;
        }
        if (frame_142 < 30)
            x_0ec = static_cast<float>((1.0 - lookup_orientation_sine_quantized_abs(static_cast<float>(frame_142 * 3.0))) * 480.0 + 640.0);
        if (advance_frame_and_dispatch()) --state_158; return;
    default: return;
    }
}
}
