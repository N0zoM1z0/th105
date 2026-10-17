#include <stddef.h>

namespace th105 {

// Verified entry phase of Reimu's 81550-byte +0x28 root @ 0x478FA0.
// This staging helper is not the target root or an original function boundary.
// Its bool reports whether the entry phase completes the update; false means
// the still-unreconstructed action switch must run. No root implementation or
// exact credit is claimed. Numeric field labels preserve unresolved meanings.
struct ReimuPreludePeerView {
    unsigned char reserved_000[0x174];
    short word_174;
    unsigned char reserved_176[0x316];
    short word_48c;
};

class ReimuActionStatePreludeView {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual int set_action(short action);

    int spawn_owned_object_via_manager(
        int object_id, float x, float y, int direction, int arg5, int arg6, int arg7);
    bool run_checked_prelude();

    unsigned char reserved_004[0xe8];
    float x_ec;
    float y_f0;
    unsigned char reserved_0f4[0x10];
    signed char facing_104;
    unsigned char reserved_105[0x37];
    short action_13c;
    unsigned char reserved_13e[0x32];
    ReimuPreludePeerView *peer_170;
    short word_174;
    unsigned char reserved_176[0xa];
    int state_180;
    unsigned char reserved_184[2];
    short word_186;
    unsigned char reserved_188[0x5c9];
    unsigned char byte_751;
    unsigned char reserved_752[0x4e];
    short word_7a0;
    short word_7a2;
    unsigned char reserved_7a4[0x24];
    short timer_7c8;
    short count_7ca;
    short latch_7cc;
};

typedef char ReimuPrelude_x_offset[(offsetof(ReimuActionStatePreludeView, x_ec) == 0xec) ? 1 : -1];
typedef char ReimuPrelude_y_offset[(offsetof(ReimuActionStatePreludeView, y_f0) == 0xf0) ? 1 : -1];
typedef char ReimuPrelude_facing_offset[(offsetof(ReimuActionStatePreludeView, facing_104) == 0x104) ? 1 : -1];
typedef char ReimuPrelude_action_offset[(offsetof(ReimuActionStatePreludeView, action_13c) == 0x13c) ? 1 : -1];
typedef char ReimuPrelude_peer_offset[(offsetof(ReimuActionStatePreludeView, peer_170) == 0x170) ? 1 : -1];
typedef char ReimuPrelude_word174_offset[(offsetof(ReimuActionStatePreludeView, word_174) == 0x174) ? 1 : -1];
typedef char ReimuPrelude_state_offset[(offsetof(ReimuActionStatePreludeView, state_180) == 0x180) ? 1 : -1];
typedef char ReimuPrelude_gate_offset[(offsetof(ReimuActionStatePreludeView, word_186) == 0x186) ? 1 : -1];
typedef char ReimuPrelude_effect_offset[(offsetof(ReimuActionStatePreludeView, byte_751) == 0x751) ? 1 : -1];
typedef char ReimuPrelude_initial_words_offset[(offsetof(ReimuActionStatePreludeView, word_7a0) == 0x7a0 && offsetof(ReimuActionStatePreludeView, word_7a2) == 0x7a2) ? 1 : -1];
typedef char ReimuPrelude_counter_offsets[(offsetof(ReimuActionStatePreludeView, timer_7c8) == 0x7c8 && offsetof(ReimuActionStatePreludeView, count_7ca) == 0x7ca && offsetof(ReimuActionStatePreludeView, latch_7cc) == 0x7cc) ? 1 : -1];
typedef char ReimuPrelude_peer_offsets[(offsetof(ReimuPreludePeerView, word_174) == 0x174 && offsetof(ReimuPreludePeerView, word_48c) == 0x48c) ? 1 : -1];

bool ReimuActionStatePreludeView::run_checked_prelude()
{
    word_7a0 = 0;
    word_7a2 = 85;
    if (action_13c > 149 && action_13c < 159 && !byte_751) {
        byte_751 = 1;
        // Each call can change owner state. Preserve the three later action
        // reads and the unsigned direction argument independently of signed X.
        if (action_13c > 149 && action_13c < 154) {
            const float y = static_cast<float>(y_f0 + 94.0);
            const float x = static_cast<float>(x_ec + static_cast<int>(facing_104) * 57);
            spawn_owned_object_via_manager(998, x, y,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
        if (action_13c > 153 && action_13c < 158) {
            const float y = static_cast<float>(y_f0 + 60.0);
            const float x = static_cast<float>(x_ec + static_cast<int>(facing_104) * 57);
            spawn_owned_object_via_manager(998, x, y,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
        if (action_13c == 158) {
            const float y = static_cast<float>(y_f0 + 100.0);
            const float x = static_cast<float>(x_ec + static_cast<int>(facing_104) * 57);
            spawn_owned_object_via_manager(998, x, y,
                static_cast<unsigned char>(facing_104), 1, 0, 0);
        }
    }
    if (timer_7c8 > 0) {
        if (word_174 <= 0 || peer_170->word_174 <= 0)
            timer_7c8 = 0;
        if (latch_7cc == 0 && (state_180 == 1 || state_180 == 7)) {
            count_7ca = static_cast<short>(count_7ca + 1);
            latch_7cc = 1;
        }
        if (count_7ca >= 7 && action_13c <= 10) {
            set_action(669);
            return true;
        }
        // Clearing the timer above does not bypass this decrement or the
        // action-669 test: the cleared timer can finish this phase at -1.
        timer_7c8 = static_cast<short>(timer_7c8 - 1);
    }
    if (word_186 != 0 || peer_170->word_48c != 0)
        return true;
    return false;
}

} // namespace th105
