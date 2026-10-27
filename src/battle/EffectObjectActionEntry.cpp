namespace th105 {
unsigned __cdecl mt19937_next_u32();
int __cdecl selector_random_roll(int limit);
double __cdecl lookup_orientation_cosine_quantized_abs(float angle);
double __cdecl lookup_orientation_sine_quantized_abs(float angle);
// Pointer-only receiver, never instantiated or embedded as a complete owner.
struct EffectObjectEntryView {
    void initialize_action_65bf90();
    void emit_fighter_effect_433cc0(int id, float x, float y, int facing, int layer);
    void dispatch_indexed_event_member(unsigned id);
};
#define FIELD(p,t,o) (*reinterpret_cast<t *>(reinterpret_cast<unsigned char *>(p)+(o)))
#define F(o) FIELD(this,float,o)
#define S(o) FIELD(this,short,o)
#define B(o) FIELD(this,unsigned char,o)
#define R(n) static_cast<float>(static_cast<unsigned>(selector_random_roll(n)))
#define MT(n) static_cast<float>(mt19937_next_u32() % (n##u))
#define CONTEXT FIELD(this,void *,0x164)
void EffectObjectEntryView::initialize_action_65bf90()
{
    switch (S(0x13c)) {
    case 51:
        F(0x11c) = 2.0f; F(0x120) = 2.0f; break;
    case 53: F(0x12c) = static_cast<float>(MT(360)); break;
    case 54: F(0x12c) = static_cast<float>(MT(360)); break;
    case 59: F(0x12c) = 90.0f; break;
    case 62: F(0x11c) = 0.1f; F(0x120) = 0.1f; break;
    case 64: F(0x12c) = static_cast<float>(MT(360)); break;
    case 65: F(0x12c) = static_cast<float>(MT(360)); break;
    case 66: F(0x12c) = static_cast<float>(MT(360)); break;
    case 67: F(0x12c) = static_cast<float>(MT(360)); break;
    case 68: F(0x12c) = static_cast<float>(MT(360)); break;
    case 69: F(0x12c) = static_cast<float>(MT(360)); break;
    case 101:
        F(0x11c) = static_cast<float>(MT(200) * 0.01f + 0.1f);
        F(0x120) = F(0x11c);
        F(0xf4) = static_cast<float>(MT(60) - 30.0);
        F(0xf8) = static_cast<float>(MT(60) - 30.0);
        break;
    case 102: case 103: {
        F(0x11c) = static_cast<float>(MT(1400) * 0.01f + 2.0);
        F(0x120) = static_cast<float>(MT(300) * 0.01f + 1.0);
        float angle = static_cast<float>(MT(360));
        float speed = static_cast<float>(MT(20) + 5.0);
        F(0xf4) = static_cast<float>(lookup_orientation_cosine_quantized_abs(angle) * speed);
        F(0xf8) = static_cast<float>(lookup_orientation_sine_quantized_abs(angle) * speed);
        F(0x12c) = -angle;
        break;
    }
    case 112:
        F(0x11c) = 3.0f; F(0x120) = 3.0f;
        F(0x12c) = static_cast<float>(R(360)); break;
    case 125:
        if (FIELD(CONTEXT,short,0x13c) == 214) {
            if (FIELD(CONTEXT,short,0x13e) == 1 || FIELD(CONTEXT,short,0x13e) == 2)
                F(0x12c) = FIELD(CONTEXT,float,0x12c);
            if (FIELD(CONTEXT,short,0x13c) == 214) {
                if (FIELD(CONTEXT,short,0x13e) == 3 || FIELD(CONTEXT,short,0x13e) == 4)
                    F(0x12c) = static_cast<float>(FIELD(CONTEXT,float,0x12c) + 180.0);
            }
        }
        break;
    case 135: F(0x124) = 80.0f; break;
    case 136:
        F(0x11c) = static_cast<float>(static_cast<float>(R(15) * 0.1f) + 0.5);
        F(0x120) = static_cast<float>(static_cast<float>(R(10) * 0.1f) + 1.0);
        B(0x113) = 0;
        break;
    case 140:
        F(0x170) = 1.0f;
        F(0x12c) = static_cast<float>(R(360));
        F(0x124) = static_cast<float>(R(140) - 70.0);
        F(0x128) = static_cast<float>(R(140) - 70.0);
        break;
    case 142: F(0x170) = 1.0f; break;
    case 150: case 152: case 154: F(0x170) = 0.0f; break;
    case 151: case 153: case 155: F(0x170) = 0.0f; B(0x113) = 0; break;
    case 160:
        F(0x12c) = static_cast<float>(R(360));
        F(0xf8) = static_cast<float>(R(30) * 0.1f + 6.0);
        F(0xf4) = static_cast<float>(R(50) * 0.1f + 10.0);
        emit_fighter_effect_433cc0(162,F(0xec),F(0xf0),B(0x104),1);
        emit_fighter_effect_433cc0(162,F(0xec),F(0xf0),B(0x104),1);
        emit_fighter_effect_433cc0(163,F(0xec),F(0xf0),B(0x104),1);
        emit_fighter_effect_433cc0(163,F(0xec),F(0xf0),B(0x104),1);
        emit_fighter_effect_433cc0(164,F(0xec),F(0xf0),B(0x104),1);
        emit_fighter_effect_433cc0(164,F(0xec),F(0xf0),B(0x104),1);
        emit_fighter_effect_433cc0(165,F(0xec),F(0xf0),B(0x104),1);
        dispatch_indexed_event_member(58);
        break;
    case 161: F(0x12c) = static_cast<float>(R(360)); F(0xf8) = 0.0f; break;
    case 162: case 163: case 164:
        F(0x12c) = static_cast<float>(R(360));
        F(0x11c) = static_cast<float>(R(60) * 0.01f + 0.7f);
        F(0x170) = static_cast<float>(R(6) + 4.0);
        F(0x174) = static_cast<float>(7.0 - R(14));
        F(0x120) = F(0x11c);
        F(0xf8) = static_cast<float>(R(120) * 0.1f + 2.0);
        F(0xf4) = static_cast<float>(R(300) * 0.1f + 20.0);
        break;
    case 165: F(0x12c) = static_cast<float>(R(360)); break;
    case 200: F(0x12c) = static_cast<float>(R(360)); break;
    case 201: F(0x12c) = static_cast<float>(R(360)); break;
    case 202:
        F(0x11c) = static_cast<float>(R(100) * 0.01f + 0.5);
        F(0x120) = F(0x11c);
        F(0x12c) = static_cast<float>(R(360));
        break;
    case 302:
        F(0x12c) = static_cast<float>(80.0 - R(25));
        F(0xf4) = static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x12c)) * 60.0);
        F(0xf8) = static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x12c)) * -60.0);
        break;
    case 303:
        F(0x12c) = static_cast<float>(80.0 - R(25));
        F(0xf4) = static_cast<float>(lookup_orientation_cosine_quantized_abs(F(0x12c)) * 50.0);
        F(0xf8) = static_cast<float>(lookup_orientation_sine_quantized_abs(F(0x12c)) * -50.0);
        break;
    case 304:
        F(0x12c) = static_cast<float>(R(15) + 30.0);
        B(0x113) = 0;
        break;
    case 300:
        F(0x12c) = 10.0f; B(0x113) = 0; break;
    case 301: case 306: case 307: case 308: case 309:
        F(0x12c) = 10.0f; B(0x113) = 0; break;
    }
}
#undef CONTEXT
#undef MT
#undef R
#undef B
#undef S
#undef F
#undef FIELD
} // namespace th105
