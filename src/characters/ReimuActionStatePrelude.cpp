#include "ReimuActionStateStaging.hpp"

namespace th105 {

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
