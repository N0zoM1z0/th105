namespace th105 {
int __cdecl selector_random_roll(int);
double __cdecl lookup_orientation_cosine_quantized_abs(float);
double __cdecl lookup_orientation_sine_quantized_abs(float);
extern int g_event_runtime_state;
// Pointer-only access view; not a complete allocatable owner.
struct WeatherEffectEntryView { void initialize_action_664e10(); };
#define FIELD(t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(this)+(o)))
#define F(o) FIELD(float,o)
#define I(o) FIELD(int,o)
#define B(o) FIELD(unsigned char,o)
#define R(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
void WeatherEffectEntryView::initialize_action_664e10()
{
    F(0x178) = 0.0f;
    F(0x17c) = 0.0f;
    I(0x170) = 0;
    I(0x174) = 0;
    switch (FIELD(short,0x13c)) {
    case 1: case 2: case 3: case 4: case 11:
    case 82: case 83: case 84: case 85:
        B(0x113) = 0; F(0x12c) = 10.0f; break;
    case 41:
        F(0x12c) = static_cast<float>(80.0 - R(25));
        F(0xf4) = static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x12c)) * 60.0);
        F(0xf8) = static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x12c)) * -60.0);
        break;
    case 42:
        F(0x12c) = static_cast<float>(80.0 - R(25));
        F(0xf4) = static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x12c)) * 50.0);
        F(0xf8) = static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x12c)) * -50.0);
        break;
    case 61:
        B(0x113) = 0; I(0x170) = 0;
        if (F(0xf0) >= 480.0) F(0x12c) = 180.0f;
        break;
    case 62: case 63:
        B(0x113) = 0;
        F(0x11c) = static_cast<float>(R(100) * 0.01f + 1.0);
        F(0x120) = static_cast<float>(R(100) * 0.01f + 1.0);
        I(0x170) = 0; break;
    case 71:
        B(0x113) = 0; I(0x170) = 0;
        F(0xf4) = static_cast<float>(static_cast<float>(R(40) * 0.1f) - 2.0);
        F(0xf8) = static_cast<float>(-2.0 - static_cast<float>(R(150) * 0.01f));
        F(0x11c) = static_cast<float>(R(75) * 0.01f + 0.25);
        F(0x120) = F(0x11c); break;
    case 72:
        B(0x113) = 0; I(0x170) = 0;
        F(0xf4) = static_cast<float>(static_cast<float>(R(40) * 0.1f) - 2.0);
        F(0xf8) = static_cast<float>(-3.0 - static_cast<float>(R(200) * 0.01f));
        F(0x11c) = static_cast<float>(R(100) * 0.01f + 0.5);
        F(0x120) = F(0x11c); break;
    case 81: case 131:
        B(0x113) = 0; I(0x170) = 0; break;
    case 86: I(0x170) = 0; break;
    case 91:
        I(0x170) = 0;
        F(0x12c) = static_cast<float>(95.0 - R(10));
        B(0x113) = 0;
        F(0x11c) = static_cast<float>(R(100) * 0.01f + 1.0);
        F(0x120) = F(0x11c); break;
    case 101:
        F(0x11c) = 1.5f; B(0x113) = 0; I(0x170) = 0; break;
    case 111:
        F(0x12c) = static_cast<float>(R(15) + 30.0);
        B(0x113) = 0; break;
    case 121:
        F(0x11c) = static_cast<float>(R(100) * 0.01f + 1.0);
        F(0x120) = F(0x11c); F(0x12c) = -10.0f; break;
    case 132: case 133:
        B(0x113) = 0;
        F(0x11c) = static_cast<float>(R(100) * 0.01f + 1.0);
        F(0x120) = static_cast<float>(R(100) * 0.01f + 1.0);
        I(0x170) = 0; break;
    case 141:
        F(0x12c) = static_cast<float>(R(15) + 30.0);
        B(0x113) = 0; break;
    case 151:
        B(0x113) = 0; F(0x120) = 2.0f;
        I(0x174) = g_event_runtime_state; break;
    case 152: case 153: case 154: case 155:
        F(0x12c) = static_cast<float>(R(50) - 25.0);
        B(0x113) = 0;
        F(0x178) = static_cast<float>(R(10) * 0.01f); break;
    case 170: F(0x11c) = 3.0f; F(0x120) = 1.5f; break;
    }
}
}
