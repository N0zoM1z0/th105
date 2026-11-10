#include "battle/EffectObjectState.hpp"
namespace th105 {
unsigned __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int limit);
double __cdecl lookup_orientation_cosine_quantized_abs(float angle);
double __cdecl lookup_orientation_sine_quantized_abs(float angle);
// Pointer-only receiver, never instantiated or embedded as a complete owner.
struct EffectObjectEntryView : EffectObjectState {
    void initialize_action_65bf90();
    void emit_fighter_effect_433cc0(int id, float x, float y, int facing, int layer);
    void dispatch_indexed_event_member(unsigned id);
};
#define R(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
#define MT(n) static_cast<float>(mt19937_next_u32() % (n##u))
void EffectObjectEntryView::initialize_action_65bf90()
{
    switch (action_13c) {
    case 51:
        scale_x_11c = 2.0f; scale_y_120 = 2.0f; break;
    case 53: angle_z_12c = static_cast<float>(MT(360)); break;
    case 54: angle_z_12c = static_cast<float>(MT(360)); break;
    case 59: angle_z_12c = 90.0f; break;
    case 62: scale_x_11c = 0.1f; scale_y_120 = 0.1f; break;
    case 64: angle_z_12c = static_cast<float>(MT(360)); break;
    case 65: angle_z_12c = static_cast<float>(MT(360)); break;
    case 66: angle_z_12c = static_cast<float>(MT(360)); break;
    case 67: angle_z_12c = static_cast<float>(MT(360)); break;
    case 68: angle_z_12c = static_cast<float>(MT(360)); break;
    case 69: angle_z_12c = static_cast<float>(MT(360)); break;
    case 101:
        scale_x_11c = static_cast<float>(MT(200) * 0.01f + 0.1f);
        scale_y_120 = scale_x_11c;
        velocity_x_0f4 = static_cast<float>(MT(60) - 30.0);
        velocity_y_0f8 = static_cast<float>(MT(60) - 30.0);
        break;
    case 102: case 103: {
        scale_x_11c = static_cast<float>(MT(1400) * 0.01f + 2.0);
        scale_y_120 = static_cast<float>(MT(300) * 0.01f + 1.0);
        float angle = static_cast<float>(MT(360));
        float speed = static_cast<float>(MT(20) + 5.0);
        velocity_x_0f4 = static_cast<float>(lookup_orientation_cosine_quantized_abs(angle) * speed);
        velocity_y_0f8 = static_cast<float>(lookup_orientation_sine_quantized_abs(angle) * speed);
        angle_z_12c = -angle;
        break;
    }
    case 112:
        scale_x_11c = 3.0f; scale_y_120 = 3.0f;
        angle_z_12c = static_cast<float>(R(360)); break;
    case 125:
        if (context_164->action_13c == 214) {
            if (context_164->sequence_13e == 1 || context_164->sequence_13e == 2)
                angle_z_12c = context_164->angle_12c;
            if (context_164->action_13c == 214) {
                if (context_164->sequence_13e == 3 || context_164->sequence_13e == 4)
                    angle_z_12c = static_cast<float>(context_164->angle_12c + 180.0);
            }
        }
        break;
    case 135: angle_x_124 = 80.0f; break;
    case 136:
        scale_x_11c = static_cast<float>(static_cast<float>(R(15) * 0.1f) + 0.5);
        scale_y_120 = static_cast<float>(static_cast<float>(R(10) * 0.1f) + 1.0);
        alpha_113 = 0;
        break;
    case 140:
        state_170 = 1.0f;
        angle_z_12c = static_cast<float>(R(360));
        angle_x_124 = static_cast<float>(R(140) - 70.0);
        angle_y_128 = static_cast<float>(R(140) - 70.0);
        break;
    case 142: state_170 = 1.0f; break;
    case 150: case 152: case 154: state_170 = 0.0f; break;
    case 151: case 153: case 155: state_170 = 0.0f; alpha_113 = 0; break;
    case 160:
        angle_z_12c = static_cast<float>(R(360));
        velocity_y_0f8 = static_cast<float>(R(30) * 0.1f + 6.0);
        velocity_x_0f4 = static_cast<float>(R(50) * 0.1f + 10.0);
        emit_fighter_effect_433cc0(162,x_0ec,y_0f0,static_cast<unsigned char>(facing_104),1);
        emit_fighter_effect_433cc0(162,x_0ec,y_0f0,static_cast<unsigned char>(facing_104),1);
        emit_fighter_effect_433cc0(163,x_0ec,y_0f0,static_cast<unsigned char>(facing_104),1);
        emit_fighter_effect_433cc0(163,x_0ec,y_0f0,static_cast<unsigned char>(facing_104),1);
        emit_fighter_effect_433cc0(164,x_0ec,y_0f0,static_cast<unsigned char>(facing_104),1);
        emit_fighter_effect_433cc0(164,x_0ec,y_0f0,static_cast<unsigned char>(facing_104),1);
        emit_fighter_effect_433cc0(165,x_0ec,y_0f0,static_cast<unsigned char>(facing_104),1);
        dispatch_indexed_event_member(58);
        break;
    case 161: angle_z_12c = static_cast<float>(R(360)); velocity_y_0f8 = 0.0f; break;
    case 162: case 163: case 164:
        angle_z_12c = static_cast<float>(R(360));
        scale_x_11c = static_cast<float>(R(60) * 0.01f + 0.7f);
        state_170 = static_cast<float>(R(6) + 4.0);
        state_174 = static_cast<float>(7.0 - R(14));
        scale_y_120 = scale_x_11c;
        velocity_y_0f8 = static_cast<float>(R(120) * 0.1f + 2.0);
        velocity_x_0f4 = static_cast<float>(R(300) * 0.1f + 20.0);
        break;
    case 165: angle_z_12c = static_cast<float>(R(360)); break;
    case 200: angle_z_12c = static_cast<float>(R(360)); break;
    case 201: angle_z_12c = static_cast<float>(R(360)); break;
    case 202:
        scale_x_11c = static_cast<float>(R(100) * 0.01f + 0.5);
        scale_y_120 = scale_x_11c;
        angle_z_12c = static_cast<float>(R(360));
        break;
    case 302:
        angle_z_12c = static_cast<float>(80.0 - R(25));
        velocity_x_0f4 = static_cast<float>(lookup_orientation_cosine_quantized_abs(angle_z_12c) * 60.0);
        velocity_y_0f8 = static_cast<float>(lookup_orientation_sine_quantized_abs(angle_z_12c) * -60.0);
        break;
    case 303:
        angle_z_12c = static_cast<float>(80.0 - R(25));
        velocity_x_0f4 = static_cast<float>(lookup_orientation_cosine_quantized_abs(angle_z_12c) * 50.0);
        velocity_y_0f8 = static_cast<float>(lookup_orientation_sine_quantized_abs(angle_z_12c) * -50.0);
        break;
    case 304:
        angle_z_12c = static_cast<float>(R(15) + 30.0);
        alpha_113 = 0;
        break;
    case 300:
        angle_z_12c = 10.0f; alpha_113 = 0; break;
    case 301: case 306: case 307: case 308: case 309:
        angle_z_12c = 10.0f; alpha_113 = 0; break;
    }
}
#undef MT
#undef R
} // namespace th105
