#include "characters/RemiliaObjectActionEntry.hpp"
namespace th105 {
#define FIELD(type, offset) (*reinterpret_cast<type *>(reinterpret_cast<unsigned char *>(this) + offset))
#define F(offset) FIELD(float, offset)
#define S(offset) FIELD(short, offset)
#define B(offset) FIELD(unsigned char, offset)
#define H FIELD(float *, 0x340)
#define MOTION reinterpret_cast<RemiliaEntryMotionView *>(reinterpret_cast<unsigned char *>(this) + 4)
#define AUX(type, offset) (*reinterpret_cast<type *>(FIELD(unsigned char *, 0x154) + offset))
__forceinline static float random_float(int limit)
{
    return static_cast<float>(static_cast<unsigned>(selector_random_roll(limit)));
}
void RemiliaObjectEntryView::initialize_action_entry()
{
    F(0xF4) = 0.0f;
    F(0xF8) = 0.0f;
    F(0x370) = 0.0f;
    F(0x374) = 0.0f;
    F(0x378) = 0.0f;
    F(0x37C) = 0.0f;
    S(0x384) = 0;
    F(0x380) = 0.0f;
    S(0x386) = 0;
    B(0x184) = 0;
    S(0x364) = 0;
    S(0x366) = 0;
    S(0x368) = 0;
    S(0x36A) = 0;
    S(0x36C) = 0;
    float payload[3];
    switch (S(0x13C)) {
    case 800:
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0) {
            B(0x184) = 1;
            MOTION->set_components(H[0], H[1]);
            F(0x12C) = H[0];
            payload[0] = H[0]; payload[1] = 0.0f; payload[2] = 1.0f;
            spawn_parented(800, F(0xEC), F(0xF0), FIELD(signed char, 0x104), -1,
                           reinterpret_cast<const unsigned *>(payload), 3);
        }
        if (S(0x13E) == 1) F(0x12C) = H[0];
        if (S(0x13E) == 2 || S(0x13E) == 3) {
            F(0x12C) = random_float(360);
            F(0x120) = F(0x11C) = random_float(10) * 0.05f + 1.0f;
            MOTION->set_components(H[0], H[1]);
        }
        return;
    case 801:
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0) {
            B(0x184) = 10;
            MOTION->set_components(H[0], H[1]);
            F(0x12C) = H[0];
        }
        return;
    case 803:
        B(0x184) = 1;
        select_sequence(static_cast<int>(H[2]));
        return;
    case 810:
        B(0x17C) = 0;
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0) {
            F(0x12C) = random_float(360);
            F(0x120) = F(0x11C) = random_float(10) * 0.05f + 1.0f;
        }
        return;
    case 811:
    case 820:
        select_sequence(static_cast<int>(H[2]));
        return;
    case 815:
        B(0x184) = 1;
        F(0x12C) = H[0];
        B(0x17C) = 1;
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0) {
            F(0x128) = 70.0f;
            F(0x370) = 1.0f;
            F(0x374) = random_float(360) - 180.0f;
            F(0x37C) = (F(0x374) < 0.0f) * 2;
            F(0x380) = 10.0f;
        }
        if (S(0x13E) == 1) {
            replace_secondary(991, 10.0f, 20, 1, 2);
            B(0x184) = 2;
            MOTION->set_components(H[0], H[1]);
            F(0x12C) = H[0];
        }
        if (S(0x13E) == 2) { F(0x128) = 70.0f; F(0x370) = 0.15f; }
        if (S(0x13E) == 3) {
            F(0x128) = 70.0f; F(0x370) = 0.2f; F(0x374) = 12.0f;
        }
        return;
    case 816:
        B(0x184) = 1;
        F(0x12C) = H[0];
        B(0x17C) = 5;
        select_sequence(static_cast<int>(H[2]));
        return;
    case 817:
        B(0x184) = 1;
        F(0x12C) = H[0];
        B(0x17C) = 9;
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0) MOTION->set_components(H[0], H[1]);
        return;
    case 821:
        B(0x17C) = 6;
        F(0x12C) = H[0];
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0) B(0x184) = 4;
        if (S(0x13E) == 3) B(0x184) = 4;
        if (S(0x13E) == 4) B(0x184) = 4;
        return;
    case 825:
        B(0x17C) = 3;
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0) {
            F(0x108) = 0.0f; F(0x10C) = 80.0f; F(0x12C) = H[0];
        }
        return;
    case 826:
        B(0x17C) = 7;
        select_sequence(static_cast<int>(H[2]));
        switch (S(0x13E)) {
        case 0:
            F(0x12C) = random_float(360);
            F(0x124) = 85 * FIELD(signed char, 0x104);
            return;
        case 1:
            F(0x12C) = random_float(360);
            F(0x374) = random_float(20) * 0.1f - 1.0f;
            return;
        case 3:
            F(0x12C) = random_float(360);
            F(0x124) = static_cast<float>(static_cast<unsigned>(selector_random_roll(20) + 50)) * FIELD(signed char, 0x104);
            if (static_cast<unsigned>(selector_random_roll(100)) < 50) F(0x128) = 180.0f;
            F(0x120) = F(0x11C) = random_float(40) * 0.01f + 0.8f;
            return;
        case 4:
        case 6:
            B(0x184) = 1;
            return;
        case 5:
            F(0x11C) = static_cast<float>(random_float(200) * 0.01f) + 1.0f;
            F(0x120) = static_cast<float>(random_float(100) * 0.01f) + 1.0f;
            return;
        case 7:
            F(0x11C) = static_cast<float>(random_float(200) * 0.01f) + 1.0f;
            F(0x120) = static_cast<float>(random_float(100) * 0.01f) + 1.0f;
            return;
        }
        return;
    case 850:
        S(0x344) = 1;
        B(0x184) = 1;
        if (H[2] != 0.0f) select_sequence(static_cast<int>(H[2]));
        return;
    case 851:
        if (H[2] != 0.0f) select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0 || S(0x13E) == 1) S(0x344) = 1;
        if (S(0x13E) == 2 || S(0x13E) == 3) {
            double const angle = H[0];
            B(0x184) = 1;
            F(0x12C) = static_cast<float>(angle);
        }
        if (S(0x13E) == 4) F(0x370) = 0.25f;
        return;
    case 852:
        S(0x344) = 1;
        if (H[2] != 0.0f) select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0 || S(0x13E) == 1) {
            F(0x12C) = random_float(360);
            F(0x128) = 45.0f;
            F(0x124) = -45 * FIELD(signed char, 0x104);
            F(0x370) = 0.3f; F(0x374) = 12.0f;
        }
        return;
    case 853:
        S(0x344) = 1;
        B(0x184) = 1;
        if (H[2] != 0.0f) select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 4) F(0x370) = 1.0f;
        if (S(0x13E) == 6) {
            F(0x11C) = static_cast<float>(random_float(100) * 0.01f) + 0.25f;
            replace_auxiliary(990);
            AUX(float, 0xF8) = 10.0f;
            AUX(float, 0xFC) = 10.0f;
            AUX(float, 0xE8) = F(0xEC);
            AUX(float, 0xEC) = F(0xF0);
            AUX(signed char, 0x104) = FIELD(signed char, 0x104);
            F(0xF8) = 30.0f;
        }
        return;
    case 854:
        if (H[2] != 0.0f) select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0 || S(0x13E) == 1) S(0x344) = 1;
        if (S(0x13E) == 2) {
            F(0x12C) = H[0]; B(0x184) = 5;
            payload[0] = H[0]; payload[1] = 0.0f; payload[2] = 6.0f;
            spawn_parented(854, F(0xEC), F(0xF0), FIELD(signed char, 0x104), 1,
                           reinterpret_cast<const unsigned *>(payload), 3);
        }
        if (S(0x13E) == 3) F(0x12C) = H[0];
        if (S(0x13E) == 4) F(0x370) = 0.25f;
        if (S(0x13E) == 5) { F(0x128) = 70.0f; F(0x370) = 0.4f; F(0x374) = 12.0f; }
        if (S(0x13E) == 6) F(0x12C) = H[0];
        if (S(0x13E) == 7) F(0x370) = 0.4f;
        return;
    case 855:
        if (H[2] != 0.0f) select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0 || S(0x13E) == 1) {
            F(0x12C) = random_float(360);
            F(0x128) = 60.0f;
            F(0x124) = -50 * FIELD(signed char, 0x104);
            F(0x370) = 0.6f; F(0x374) = 12.0f;
        }
        if (S(0x13E) == 2) { F(0x12C) = -120.0f; F(0x370) = 1.0f; }
        return;
    case 856:
        if (H[2] != 0.0f) select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0 || S(0x13E) == 1) {
            F(0x12C) = random_float(360);
            F(0x128) = 60.0f;
            F(0x124) = 50 * FIELD(signed char, 0x104);
            F(0x370) = 0.6f; F(0x374) = 12.0f;
        }
        if (S(0x13E) == 2) { F(0x12C) = -60.0f; F(0x370) = 1.0f; }
        return;
    case 857:
        B(0x184) = 1;
    case 848:
        F(0x12C) = H[0];
        select_sequence(static_cast<int>(H[2]));
        return;
    case 900:
        B(0x184) = 1;
        F(0x12C) = H[0];
        select_sequence(static_cast<int>(H[2]));
        return;
    case 901:
        select_sequence(static_cast<int>(H[2]));
        switch (S(0x13E)) {
        case 0:
            F(0x12C) = random_float(360);
            F(0x124) = 85 * FIELD(signed char, 0x104);
            return;
        case 1:
            F(0x12C) = random_float(360);
            F(0x374) = random_float(20) * 0.1f - 1.0f;
            return;
        case 2:
        case 9:
            F(0x12C) = H[0];
            return;
        case 3:
            F(0x12C) = random_float(360);
            F(0x124) = static_cast<float>(static_cast<unsigned>(selector_random_roll(20) + 50)) * FIELD(signed char, 0x104);
            if (static_cast<unsigned>(selector_random_roll(100)) < 50) F(0x128) = 180.0f;
            F(0x120) = F(0x11C) = random_float(40) * 0.01f + 0.8f;
            return;
        case 4:
            B(0x184) = 1;
            return;
        case 5:
            F(0x11C) = static_cast<float>(random_float(200) * 0.01f) + 1.0f;
            F(0x120) = static_cast<float>(random_float(100) * 0.01f) + 1.0f;
            return;
        case 6:
            F(0x120) = F(0x11C) = 3.0f; B(0x113) = 0; F(0x124) = 85.0f;
            return;
        case 7:
            B(0x184) = 1;
            MOTION->set_components(H[0], H[1]);
            return;
        case 8:
            F(0x12C) = H[0];
            return;
        case 10:
            F(0x12C) = random_float(360);
            F(0x128) = static_cast<float>(static_cast<unsigned>(selector_random_roll(20) + 50));
            if (static_cast<unsigned>(selector_random_roll(100)) < 50) F(0x124) = 180.0f;
            F(0x120) = F(0x11C) = random_float(40) * 0.01f + 0.8f;
            return;
        }
        return;
    case 902:
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0 || S(0x13E) == 5) {
            B(0x184) = 1;
            F(0x12C) = H[0];
            MOTION->set_components(H[0], H[1]);
        }
        if (S(0x13E) == 1) {
            B(0x113) = 0; B(0x184) = 0;
            F(0x12C) = H[0];
            MOTION->set_components(H[0], H[1]);
        }
        if (S(0x13E) == 2) {
            F(0x370) = 1.0f;
            F(0x12C) = random_float(360);
            F(0x124) = random_float(140) - 70.0f;
            F(0x128) = random_float(140) - 70.0f;
        }
        if (S(0x13E) == 3) F(0x120) = F(0x11C) = random_float(10) * 0.1f + 0.5f;
        return;
    case 903:
        select_sequence(static_cast<int>(H[2]));
        if (S(0x13E) == 0) F(0x12C) = H[0];
        if (S(0x13E) == 1) B(0x184) = 1;
        if (S(0x13E) == 2) F(0x120) = F(0x11C) = random_float(10) * 0.1f + 0.5f;
        if (S(0x13E) == 3) {
            B(0x184) = 1;
            F(0x12C) = H[0];
            MOTION->set_components(H[0], H[1]);
        }
        if (S(0x13E) == 5) F(0x120) = F(0x11C) = random_float(15) * 0.1f + 0.25f;
        if (S(0x13E) == 6) {
            F(0x370) = 1.0f;
            F(0x12C) = random_float(360);
            F(0x124) = random_float(140) - 70.0f;
            F(0x128) = random_float(140) - 70.0f;
        }
        if (S(0x13E) == 7) { F(0x370) = 1.0f; B(0x113) = 0; }
        return;
    // The native remap retains an explicit terminal selector 998.
    case 998:
        return;
    case 980:
        continue_action_980();
        return;
    }
}
#undef AUX
#undef MOTION
#undef H
#undef B
#undef S
#undef F
#undef FIELD
}
