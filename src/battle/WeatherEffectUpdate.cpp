namespace th105 {
extern unsigned char g_battle_transition_mode;
extern int g_event_runtime_state;
int __cdecl selector_random_roll(int);
float __cdecl lookup_orientation_sine(int);
extern "C" float __cdecl lookup_orientation_cosine(int);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
struct WeatherMotionView { void set_components(float, float); };
struct WeatherEffectUpdateView {
    void update_663b70();
    unsigned char advance_frame_and_dispatch();
    void set_sprite_uv_size(float, float);
};
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define I(o) FIELD(int,o)
#define S(o) FIELD(short,o)
#define B(o) FIELD(unsigned char,o)
#define C(o) FIELD(signed char,o)
void WeatherEffectUpdateView::update_663b70()
{
    short category = 0;
    switch (static_cast<signed char>(g_battle_transition_mode)) {
    case 4: case 6: case 14: case 16: category = 1; break;
    case 5: category = 2; break;
    case 0: category = 0; break;
    case 1: category = 0; break;
    case 2: category = 0; break;
    case 3: category = 0; break;
    case 10: category = 0; break;
    case 11: category = 0; break;
    case 12: category = 0; break;
    case 13: category = 0; break;
    case 15: category = 0; break;
    case 17: category = 0; break;
    case 18: category = 0; break;
    }
    switch (S(0x13c)) {
    case 1: {
        if (g_event_runtime_state != 0 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xec) = static_cast<float>(F(0xec) - 1.0);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 2: {
        if (g_event_runtime_state != 0 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xec) = static_cast<float>(F(0xec) + 1.0);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 3: {
        if (g_event_runtime_state != 0 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xec) = static_cast<float>(F(0xec) - 1.0);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 4: {
        if (g_event_runtime_state != 0 || category) I(0x170) = 1;
        unsigned char alpha;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        alpha = B(0x113) - 20;
        } else alpha = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        F(0xec) = static_cast<float>(F(0xec) + 1.0);
        B(0x113) = alpha;
        if (advance_frame_and_dispatch()) --I(0x158);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 5: {
        if (g_event_runtime_state != 0 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else if (B(0x113) <= 235) B(0x113) += 20;
        else B(0x113) = 255;
        return;
    }
    case 11: {
        if (g_event_runtime_state != 1 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xf0) = static_cast<float>(lookup_orientation_sine(-100) * 6.0 + F(0xf0));
        F(0xec) = static_cast<float>(lookup_orientation_cosine(-100) * 6.0 + F(0xec));
        if (I(0x144) <= 60) {
            if (B(0x113) < 250) B(0x113) += 5;
            else B(0x113) = 255;
        }
        if (I(0x144) >= 180 || F(0xf0) < 480.0) {
            if (B(0x113) <= 10) --I(0x158);
            else B(0x113) -= 10;
        }
        return;
    }
    case 41: {
        if (g_event_runtime_state != 4 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        }
        if (S(0x140) == 0) {
            if (F(0xf8) + F(0xf0) <= -100.0) {
                S(0x140) = 1; S(0x142) = 0;
                F(0xf4) = static_cast<float>(F(0xf4) * 0.5);
                F(0xf8) = static_cast<float>(-F(0xf8) * 0.15f);
                return;
            }
            if (F(0xf0) <= 0.0 && static_cast<unsigned>(selector_random_roll(100)) <= 30) {
                S(0x140) = 1; S(0x142) = 0;
                F(0xf4) = static_cast<float>(F(0xf4) * 0.5);
                F(0xf8) = static_cast<float>(-F(0xf8) * 0.25);
                return;
            }
        }
        if (S(0x140) == 1) {
        F(0xf8) = static_cast<float>(F(0xf8) - 0.75);
        if (B(0x113) < 10) { --I(0x158); return; }
        B(0x113) -= 10;
        }
        F(0xf0) = F(0xf8) + F(0xf0);
        F(0xec) = F(0xf4) + F(0xec);
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 42: {
        if (g_event_runtime_state != 4 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        }
        if (S(0x140) == 0 && (F(0xf8) + F(0xf0) <= 0.0 ||
                (F(0xf0) < 50.0 && static_cast<unsigned>(selector_random_roll(100)) <= 30))) {
            S(0x140) = 1; S(0x142) = 0;
            F(0xf4) = static_cast<float>(F(0xf4) * 0.5);
            F(0xf8) = static_cast<float>(-F(0xf8) * 0.15f);
            return;
        }
        if (S(0x140) == 1) {
        F(0xf8) = static_cast<float>(F(0xf8) - 0.5);
        if (B(0x113) < 10) { --I(0x158); return; }
        B(0x113) -= 10;
        }
        F(0xf0) = F(0xf8) + F(0xf0);
        F(0xec) = F(0xf4) + F(0xec);
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 61: {
        if (g_event_runtime_state != 6 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 10) { --I(0x158); return; }
        B(0x113) -= 10;
        } else if (B(0x113) <= 125) B(0x113) += 3;
        else B(0x113) = 128;
        F(0x178) = static_cast<float>(F(0x178) + 0.25);
        set_sprite_uv_size(F(0x178), 0.0f);
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 62: case 63: {
        if (g_event_runtime_state != 6 || category) I(0x170) = 1;
        if (I(0x170) == 1 || I(0x144) > 180) {
        if (B(0x113) < 3) { --I(0x158); return; }
        B(0x113) -= 3;
        } else if (B(0x113) <= 125) B(0x113) += 3;
        else B(0x113) = 128;
        F(0xec) = static_cast<float>(F(0xec) - 0.6f);
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 71: {
        if (g_event_runtime_state != 7 || category) I(0x170) = 1;
        if (I(0x170) == 1 || I(0x144) > 240) {
        if (B(0x113) < 3) { --I(0x158); return; }
        B(0x113) -= 3;
        } else if (B(0x113) <= 252) B(0x113) += 3;
        else B(0x113) = 255;
        if (F(0xf0) < -200.0) { --I(0x158); return; }
        F(0xf4) = static_cast<float>(lookup_orientation_sine(4 * I(0x144)) * 0.02f + F(0xf4));
        F(0xec) = F(0xf4) * C(0x104) + F(0xec);
        F(0xf0) = F(0xf8) + F(0xf0);
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 72: {
        F(0x12c) = static_cast<float>(F(0x12c) + 1.0);
        if (g_event_runtime_state != 7 || category) I(0x170) = 1;
        if (I(0x170) == 1 || I(0x144) > 240) {
        if (B(0x113) < 3) { --I(0x158); return; }
        B(0x113) -= 3;
        } else if (B(0x113) <= 252) B(0x113) += 3;
        else B(0x113) = 255;
        if (F(0xf0) < -200.0) { --I(0x158); return; }
        F(0xf4) = static_cast<float>(lookup_orientation_sine(4 * I(0x144)) * 0.05f + F(0xf4));
        F(0xec) = F(0xf4) * C(0x104) + F(0xec);
        F(0xf0) = F(0xf8) + F(0xf0);
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 81: {
        if (g_event_runtime_state != 8 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else if (B(0x113) <= 252) B(0x113) += 3;
        else B(0x113) = 255;
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 82: {
        if (g_event_runtime_state != 8 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xec) = static_cast<float>(F(0xec) - 1.0);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 83: {
        if (g_event_runtime_state != 8 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xec) = static_cast<float>(F(0xec) + 1.0);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 84: {
        if (g_event_runtime_state != 8 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xec) = static_cast<float>(F(0xec) - 1.0);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 85: {
        if (g_event_runtime_state != 8 || category) I(0x170) = 1;
        unsigned char alpha;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        alpha = B(0x113) - 20;
        } else alpha = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        F(0xec) = static_cast<float>(F(0xec) + 1.0);
        B(0x113) = alpha;
        if (advance_frame_and_dispatch()) --I(0x158);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 86: {
        if (g_event_runtime_state != 8 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else if (B(0x113) <= 235) B(0x113) += 20;
        else B(0x113) = 255;
        return;
    }
    case 91: {
        if (g_event_runtime_state != 9 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xf0) = static_cast<float>(lookup_orientation_sine_quantized_abs(-F(0x12c)) * 60.0 + F(0xf0));
        F(0xec) = static_cast<float>(lookup_orientation_cosine_quantized_abs(-F(0x12c)) * 60.0 * C(0x104) + F(0xec));
        if (I(0x144) <= 20) {
            if (B(0x113) < 240) B(0x113) += 15;
            else B(0x113) = 255;
        }
        if (I(0x144) >= 180 || F(0xf0) < 480.0) {
            if (B(0x113) <= 25) --I(0x158);
            else B(0x113) -= 25;
        }
        return;
    }
    case 101: {
        if (g_event_runtime_state != 17 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else if (B(0x113) <= 125) B(0x113) += 3;
        else B(0x113) = 128;
        F(0x178) = static_cast<float>(F(0x178) + 0.25);
        set_sprite_uv_size(F(0x178), 0.0f);
        return;
    }
    case 111: {
        if (g_event_runtime_state != 10 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xf0) = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(-F(0x12c) - 90.0)) * 40.0 + F(0xf0));
        F(0xec) = static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(-F(0x12c) - 90.0)) * 40.0 + F(0xec));
        if (I(0x144) <= 20) {
            if (B(0x113) < 240) B(0x113) += 15;
            else B(0x113) = 255;
        }
        if (I(0x144) >= 180 || F(0xf0) < 480.0) {
            if (B(0x113) <= 25) --I(0x158);
            else B(0x113) -= 25;
        }
        return;
    }
    case 121: {
        reinterpret_cast<WeatherMotionView *>(reinterpret_cast<unsigned char *>(this)+4)->set_components(-10.0f,100.0f);
        if (F(0xec) > 1880.0) { --I(0x158); return; }
        F(0xec) = F(0xf4) + F(0xec);
        F(0xf0) = F(0xf8) + F(0xf0);
        return;
    }
    case 131: {
        if (g_event_runtime_state != 12 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else if (B(0x113) <= 125) B(0x113) += 3;
        else B(0x113) = 128;
        F(0x178) = static_cast<float>(F(0x178) - 0.5);
        set_sprite_uv_size(F(0x178), 0.0f);
        return;
    }
    case 132: {
        if (g_event_runtime_state != 12 || category) I(0x170) = 1;
        if (I(0x170) == 1 || I(0x144) > 180) {
        if (B(0x113) < 3) { --I(0x158); return; }
        B(0x113) -= 3;
        } else if (B(0x113) <= 252) B(0x113) += 3;
        else B(0x113) = 255;
        F(0xec) = static_cast<float>(F(0xec) - 0.8f);
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 141: {
        if (g_event_runtime_state != 13 || category) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        }
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0xf0) = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(-F(0x12c) - 90.0)) * 60.0 + F(0xf0));
        F(0xec) = static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(-F(0x12c) - 90.0)) * 60.0 + F(0xec));
        if (I(0x144) <= 20) {
            if (B(0x113) < 240) B(0x113) += 15;
            else B(0x113) = 255;
        }
        if (I(0x144) >= 180 || F(0xf0) < 480.0) {
            if (B(0x113) <= 25) --I(0x158);
            else B(0x113) -= 25;
        }
        return;
    }
    case 151: {
        if (I(0x174) != g_event_runtime_state ||
            (g_event_runtime_state != 14 && g_battle_transition_mode != 5))
            I(0x170) = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) I(0x170) = 1;
        } else if (g_event_runtime_state == 15) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else if (B(0x113) <= 252) B(0x113) += 3;
        else B(0x113) = 255;
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    case 152: {
        if (g_event_runtime_state != 14 && g_battle_transition_mode != 5)
            I(0x170) = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) I(0x170) = 1;
        } else if (g_event_runtime_state == 15) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0x12c) = F(0x178) + F(0x12c);
        F(0x120) = static_cast<float>(F(0x120) + 0.01f);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 153: {
        if (g_event_runtime_state != 14 && g_battle_transition_mode != 5)
            I(0x170) = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) I(0x170) = 1;
        } else if (g_event_runtime_state == 15) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0x12c) = F(0x178) + F(0x12c);
        F(0x120) = static_cast<float>(F(0x120) + 0.01f);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 154: {
        if (g_event_runtime_state != 14 && g_battle_transition_mode != 5)
            I(0x170) = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) I(0x170) = 1;
        } else if (g_event_runtime_state == 15) I(0x170) = 1;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        B(0x113) -= 20;
        } else B(0x113) = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        if (advance_frame_and_dispatch()) --I(0x158);
        F(0x12c) = F(0x178) + F(0x12c);
        F(0x120) = static_cast<float>(F(0x120) + 0.01f);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 155: {
        if (g_event_runtime_state != 14 && g_battle_transition_mode != 5)
            I(0x170) = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) I(0x170) = 1;
        } else if (g_event_runtime_state == 15) I(0x170) = 1;
        unsigned char alpha;
        if (I(0x170) == 1) {
        if (B(0x113) < 20) { --I(0x158); return; }
        alpha = B(0x113) - 20;
        } else alpha = static_cast<unsigned char>(lookup_orientation_sine(I(0x144)) * 255.0);
        F(0x12c) = F(0x178) + F(0x12c);
        F(0x120) = static_cast<float>(F(0x120) + 0.01f);
        B(0x113) = alpha;
        if (advance_frame_and_dispatch()) --I(0x158);
        if (I(0x144) >= 180) --I(0x158);
        return;
    }
    case 170: {
        if (B(0x113) < 3) { --I(0x158); return; }
        B(0x113) -= 3;
        if (advance_frame_and_dispatch()) --I(0x158);
        return;
    }
    }
}
}
