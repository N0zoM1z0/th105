#include "WeatherEffectState.hpp"
namespace th105 {
int __cdecl selector_random_roll(int);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
extern int g_event_runtime_state;
// Pointer-only access view; not a complete allocatable owner.
struct WeatherEffectEntryView : WeatherEffectState { void initialize_action_664e10(); };
#define R(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
void WeatherEffectEntryView::initialize_action_664e10()
{
    drift_178 = 0.0f;
    state_17c = 0.0f;
    retiring_170 = 0;
    event_174 = 0;
    switch (action_13c) {
    case 1: case 2: case 3: case 4: case 11:
    case 82: case 83: case 84: case 85:
        alpha_113 = 0; angle_12c = 10.0f; break;
    case 41:
        angle_12c = static_cast<float>(80.0 - R(25));
        velocity_x_0f4 = static_cast<float>(lookup_orientation_cosine_quantized_abs(angle_12c) * 60.0);
        velocity_y_0f8 = static_cast<float>(lookup_orientation_sine_quantized_abs(angle_12c) * -60.0);
        break;
    case 42:
        angle_12c = static_cast<float>(80.0 - R(25));
        velocity_x_0f4 = static_cast<float>(lookup_orientation_cosine_quantized_abs(angle_12c) * 50.0);
        velocity_y_0f8 = static_cast<float>(lookup_orientation_sine_quantized_abs(angle_12c) * -50.0);
        break;
    case 61:
        alpha_113 = 0; retiring_170 = 0;
        if (y_0f0 >= 480.0) angle_12c = 180.0f;
        break;
    case 62: case 63:
        alpha_113 = 0;
        scale_x_11c = static_cast<float>(R(100) * 0.01f + 1.0);
        scale_y_120 = static_cast<float>(R(100) * 0.01f + 1.0);
        retiring_170 = 0; break;
    case 71:
        alpha_113 = 0; retiring_170 = 0;
        velocity_x_0f4 = static_cast<float>(static_cast<float>(R(40) * 0.1f) - 2.0);
        velocity_y_0f8 = static_cast<float>(-2.0 - static_cast<float>(R(150) * 0.01f));
        scale_x_11c = static_cast<float>(R(75) * 0.01f + 0.25);
        scale_y_120 = scale_x_11c; break;
    case 72:
        alpha_113 = 0; retiring_170 = 0;
        velocity_x_0f4 = static_cast<float>(static_cast<float>(R(40) * 0.1f) - 2.0);
        velocity_y_0f8 = static_cast<float>(-3.0 - static_cast<float>(R(200) * 0.01f));
        scale_x_11c = static_cast<float>(R(100) * 0.01f + 0.5);
        scale_y_120 = scale_x_11c; break;
    case 81: case 131:
        alpha_113 = 0; retiring_170 = 0; break;
    case 86: retiring_170 = 0; break;
    case 91:
        retiring_170 = 0;
        angle_12c = static_cast<float>(95.0 - R(10));
        alpha_113 = 0;
        scale_x_11c = static_cast<float>(R(100) * 0.01f + 1.0);
        scale_y_120 = scale_x_11c; break;
    case 101:
        scale_x_11c = 1.5f; alpha_113 = 0; retiring_170 = 0; break;
    case 111:
        angle_12c = static_cast<float>(R(15) + 30.0);
        alpha_113 = 0; break;
    case 121:
        scale_x_11c = static_cast<float>(R(100) * 0.01f + 1.0);
        scale_y_120 = scale_x_11c; angle_12c = -10.0f; break;
    case 132: case 133:
        alpha_113 = 0;
        scale_x_11c = static_cast<float>(R(100) * 0.01f + 1.0);
        scale_y_120 = static_cast<float>(R(100) * 0.01f + 1.0);
        retiring_170 = 0; break;
    case 141:
        angle_12c = static_cast<float>(R(15) + 30.0);
        alpha_113 = 0; break;
    case 151:
        alpha_113 = 0; scale_y_120 = 2.0f;
        event_174 = g_event_runtime_state; break;
    case 152: case 153: case 154: case 155:
        angle_12c = static_cast<float>(R(50) - 25.0);
        alpha_113 = 0;
        drift_178 = static_cast<float>(R(10) * 0.01f); break;
    case 170: scale_x_11c = 3.0f; scale_y_120 = 1.5f; break;
    }
}
}
