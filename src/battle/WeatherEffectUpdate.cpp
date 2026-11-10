#include "WeatherEffectState.hpp"
namespace th105 {
extern unsigned char g_battle_transition_mode;
extern int g_event_runtime_state;
int __cdecl selector_random_roll(int);
float __cdecl lookup_orientation_sine(int);
extern "C" float __cdecl lookup_orientation_cosine(int);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
struct WeatherMotionView { void set_components(float, float); };
struct WeatherEffectUpdateView : WeatherEffectState {
    void update_663b70();
    unsigned char advance_frame_and_dispatch();
    void set_sprite_uv_size(float, float);
};
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
    switch (action_13c) {
    case 1: {
        if (g_event_runtime_state != 0 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        x_0ec = static_cast<float>(x_0ec - 1.0);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 2: {
        if (g_event_runtime_state != 0 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        x_0ec = static_cast<float>(x_0ec + 1.0);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 3: {
        if (g_event_runtime_state != 0 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        x_0ec = static_cast<float>(x_0ec - 1.0);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 4: {
        if (g_event_runtime_state != 0 || category) retiring_170 = 1;
        unsigned char alpha;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha = alpha_113 - 20;
        } else alpha = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        x_0ec = static_cast<float>(x_0ec + 1.0);
        alpha_113 = alpha;
        if (advance_frame_and_dispatch()) --state_158;
        if (time_144 >= 180) --state_158;
        return;
    }
    case 5: {
        if (g_event_runtime_state != 0 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else if (alpha_113 <= 235) alpha_113 += 20;
        else alpha_113 = 255;
        return;
    }
    case 11: {
        if (g_event_runtime_state != 1 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158;
        y_0f0 = static_cast<float>(lookup_orientation_sine(-100) * 6.0 + y_0f0);
        x_0ec = static_cast<float>(lookup_orientation_cosine(-100) * 6.0 + x_0ec);
        if (time_144 <= 60) {
            if (alpha_113 < 250) alpha_113 += 5;
            else alpha_113 = 255;
        }
        if (time_144 >= 180 || y_0f0 < 480.0) {
            if (alpha_113 <= 10) --state_158;
            else alpha_113 -= 10;
        }
        return;
    }
    case 41: {
        if (g_event_runtime_state != 4 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        }
        if (frame_140 == 0) {
            if (velocity_y_0f8 + y_0f0 <= -100.0) {
                frame_140 = 1; frame_142 = 0;
                velocity_x_0f4 = static_cast<float>(velocity_x_0f4 * 0.5);
                velocity_y_0f8 = static_cast<float>(-velocity_y_0f8 * 0.15f);
                return;
            }
            if (y_0f0 <= 0.0 && static_cast<unsigned>(selector_random_roll(100)) <= 30) {
                frame_140 = 1; frame_142 = 0;
                velocity_x_0f4 = static_cast<float>(velocity_x_0f4 * 0.5);
                velocity_y_0f8 = static_cast<float>(-velocity_y_0f8 * 0.25);
                return;
            }
        }
        if (frame_140 == 1) {
        velocity_y_0f8 = static_cast<float>(velocity_y_0f8 - 0.75);
        if (alpha_113 < 10) { --state_158; return; }
        alpha_113 -= 10;
        }
        y_0f0 = velocity_y_0f8 + y_0f0;
        x_0ec = velocity_x_0f4 + x_0ec;
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 42: {
        if (g_event_runtime_state != 4 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        }
        if (frame_140 == 0 && (velocity_y_0f8 + y_0f0 <= 0.0 ||
                (y_0f0 < 50.0 && static_cast<unsigned>(selector_random_roll(100)) <= 30))) {
            frame_140 = 1; frame_142 = 0;
            velocity_x_0f4 = static_cast<float>(velocity_x_0f4 * 0.5);
            velocity_y_0f8 = static_cast<float>(-velocity_y_0f8 * 0.15f);
            return;
        }
        if (frame_140 == 1) {
        velocity_y_0f8 = static_cast<float>(velocity_y_0f8 - 0.5);
        if (alpha_113 < 10) { --state_158; return; }
        alpha_113 -= 10;
        }
        y_0f0 = velocity_y_0f8 + y_0f0;
        x_0ec = velocity_x_0f4 + x_0ec;
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 61: {
        if (g_event_runtime_state != 6 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 10) { --state_158; return; }
        alpha_113 -= 10;
        } else if (alpha_113 <= 125) alpha_113 += 3;
        else alpha_113 = 128;
        drift_178 = static_cast<float>(drift_178 + 0.25);
        set_sprite_uv_size(drift_178, 0.0f);
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 62: case 63: {
        if (g_event_runtime_state != 6 || category) retiring_170 = 1;
        if (retiring_170 == 1 || time_144 > 180) {
        if (alpha_113 < 3) { --state_158; return; }
        alpha_113 -= 3;
        } else if (alpha_113 <= 125) alpha_113 += 3;
        else alpha_113 = 128;
        x_0ec = static_cast<float>(x_0ec - 0.6f);
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 71: {
        if (g_event_runtime_state != 7 || category) retiring_170 = 1;
        if (retiring_170 == 1 || time_144 > 240) {
        if (alpha_113 < 3) { --state_158; return; }
        alpha_113 -= 3;
        } else if (alpha_113 <= 252) alpha_113 += 3;
        else alpha_113 = 255;
        if (y_0f0 < -200.0) { --state_158; return; }
        velocity_x_0f4 = static_cast<float>(lookup_orientation_sine(4 * time_144) * 0.02f + velocity_x_0f4);
        x_0ec = velocity_x_0f4 * facing_104 + x_0ec;
        y_0f0 = velocity_y_0f8 + y_0f0;
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 72: {
        angle_12c = static_cast<float>(angle_12c + 1.0);
        if (g_event_runtime_state != 7 || category) retiring_170 = 1;
        if (retiring_170 == 1 || time_144 > 240) {
        if (alpha_113 < 3) { --state_158; return; }
        alpha_113 -= 3;
        } else if (alpha_113 <= 252) alpha_113 += 3;
        else alpha_113 = 255;
        if (y_0f0 < -200.0) { --state_158; return; }
        velocity_x_0f4 = static_cast<float>(lookup_orientation_sine(4 * time_144) * 0.05f + velocity_x_0f4);
        x_0ec = velocity_x_0f4 * facing_104 + x_0ec;
        y_0f0 = velocity_y_0f8 + y_0f0;
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 81: {
        if (g_event_runtime_state != 8 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else if (alpha_113 <= 252) alpha_113 += 3;
        else alpha_113 = 255;
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 82: {
        if (g_event_runtime_state != 8 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        x_0ec = static_cast<float>(x_0ec - 1.0);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 83: {
        if (g_event_runtime_state != 8 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        x_0ec = static_cast<float>(x_0ec + 1.0);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 84: {
        if (g_event_runtime_state != 8 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        x_0ec = static_cast<float>(x_0ec - 1.0);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 85: {
        if (g_event_runtime_state != 8 || category) retiring_170 = 1;
        unsigned char alpha;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha = alpha_113 - 20;
        } else alpha = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        x_0ec = static_cast<float>(x_0ec + 1.0);
        alpha_113 = alpha;
        if (advance_frame_and_dispatch()) --state_158;
        if (time_144 >= 180) --state_158;
        return;
    }
    case 86: {
        if (g_event_runtime_state != 8 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else if (alpha_113 <= 235) alpha_113 += 20;
        else alpha_113 = 255;
        return;
    }
    case 91: {
        if (g_event_runtime_state != 9 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158;
        y_0f0 = static_cast<float>(lookup_orientation_sine_quantized_abs(-angle_12c) * 60.0 + y_0f0);
        x_0ec = static_cast<float>(lookup_orientation_cosine_quantized_abs(-angle_12c) * 60.0 * facing_104 + x_0ec);
        if (time_144 <= 20) {
            if (alpha_113 < 240) alpha_113 += 15;
            else alpha_113 = 255;
        }
        if (time_144 >= 180 || y_0f0 < 480.0) {
            if (alpha_113 <= 25) --state_158;
            else alpha_113 -= 25;
        }
        return;
    }
    case 101: {
        if (g_event_runtime_state != 17 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else if (alpha_113 <= 125) alpha_113 += 3;
        else alpha_113 = 128;
        drift_178 = static_cast<float>(drift_178 + 0.25);
        set_sprite_uv_size(drift_178, 0.0f);
        return;
    }
    case 111: {
        if (g_event_runtime_state != 10 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158;
        y_0f0 = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(-angle_12c - 90.0)) * 40.0 + y_0f0);
        x_0ec = static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(-angle_12c - 90.0)) * 40.0 + x_0ec);
        if (time_144 <= 20) {
            if (alpha_113 < 240) alpha_113 += 15;
            else alpha_113 = 255;
        }
        if (time_144 >= 180 || y_0f0 < 480.0) {
            if (alpha_113 <= 25) --state_158;
            else alpha_113 -= 25;
        }
        return;
    }
    case 121: {
        reinterpret_cast<WeatherMotionView *>(reinterpret_cast<unsigned char *>(this)+4)->set_components(-10.0f,100.0f);
        if (x_0ec > 1880.0) { --state_158; return; }
        x_0ec = velocity_x_0f4 + x_0ec;
        y_0f0 = velocity_y_0f8 + y_0f0;
        return;
    }
    case 131: {
        if (g_event_runtime_state != 12 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else if (alpha_113 <= 125) alpha_113 += 3;
        else alpha_113 = 128;
        drift_178 = static_cast<float>(drift_178 - 0.5);
        set_sprite_uv_size(drift_178, 0.0f);
        return;
    }
    case 132: {
        if (g_event_runtime_state != 12 || category) retiring_170 = 1;
        if (retiring_170 == 1 || time_144 > 180) {
        if (alpha_113 < 3) { --state_158; return; }
        alpha_113 -= 3;
        } else if (alpha_113 <= 252) alpha_113 += 3;
        else alpha_113 = 255;
        x_0ec = static_cast<float>(x_0ec - 0.8f);
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 141: {
        if (g_event_runtime_state != 13 || category) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        }
        if (advance_frame_and_dispatch()) --state_158;
        y_0f0 = static_cast<float>(lookup_orientation_sine_quantized_abs(static_cast<float>(-angle_12c - 90.0)) * 60.0 + y_0f0);
        x_0ec = static_cast<float>(lookup_orientation_cosine_quantized_abs(static_cast<float>(-angle_12c - 90.0)) * 60.0 + x_0ec);
        if (time_144 <= 20) {
            if (alpha_113 < 240) alpha_113 += 15;
            else alpha_113 = 255;
        }
        if (time_144 >= 180 || y_0f0 < 480.0) {
            if (alpha_113 <= 25) --state_158;
            else alpha_113 -= 25;
        }
        return;
    }
    case 151: {
        if (event_174 != g_event_runtime_state ||
            (g_event_runtime_state != 14 && g_battle_transition_mode != 5))
            retiring_170 = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) retiring_170 = 1;
        } else if (g_event_runtime_state == 15) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else if (alpha_113 <= 252) alpha_113 += 3;
        else alpha_113 = 255;
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    case 152: {
        if (g_event_runtime_state != 14 && g_battle_transition_mode != 5)
            retiring_170 = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) retiring_170 = 1;
        } else if (g_event_runtime_state == 15) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        angle_12c = drift_178 + angle_12c;
        scale_y_120 = static_cast<float>(scale_y_120 + 0.01f);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 153: {
        if (g_event_runtime_state != 14 && g_battle_transition_mode != 5)
            retiring_170 = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) retiring_170 = 1;
        } else if (g_event_runtime_state == 15) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        angle_12c = drift_178 + angle_12c;
        scale_y_120 = static_cast<float>(scale_y_120 + 0.01f);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 154: {
        if (g_event_runtime_state != 14 && g_battle_transition_mode != 5)
            retiring_170 = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) retiring_170 = 1;
        } else if (g_event_runtime_state == 15) retiring_170 = 1;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha_113 -= 20;
        } else alpha_113 = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        if (advance_frame_and_dispatch()) --state_158;
        angle_12c = drift_178 + angle_12c;
        scale_y_120 = static_cast<float>(scale_y_120 + 0.01f);
        if (time_144 >= 180) --state_158;
        return;
    }
    case 155: {
        if (g_event_runtime_state != 14 && g_battle_transition_mode != 5)
            retiring_170 = 1;
        else if (g_event_runtime_state == 16) {
            if (g_battle_transition_mode == 5) retiring_170 = 1;
        } else if (g_event_runtime_state == 15) retiring_170 = 1;
        unsigned char alpha;
        if (retiring_170 == 1) {
        if (alpha_113 < 20) { --state_158; return; }
        alpha = alpha_113 - 20;
        } else alpha = static_cast<unsigned char>(lookup_orientation_sine(time_144) * 255.0);
        angle_12c = drift_178 + angle_12c;
        scale_y_120 = static_cast<float>(scale_y_120 + 0.01f);
        alpha_113 = alpha;
        if (advance_frame_and_dispatch()) --state_158;
        if (time_144 >= 180) --state_158;
        return;
    }
    case 170: {
        if (alpha_113 < 3) { --state_158; return; }
        alpha_113 -= 3;
        if (advance_frame_and_dispatch()) --state_158;
        return;
    }
    }
}
}
