// Shared source fragment; include only within the matching staging context.
    word_7a0 = 0;
    word_7a2 = 85;
    if (action_13c > 149 && action_13c < 159 && !byte_751) {
        byte_751 = 1;
        // Each call can change owner state. Preserve the three later action
        // reads and the unsigned direction argument independently of signed X.
        if (action_13c > 149 && action_13c < 154) {
            const int direction = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(998,
                static_cast<float>(static_cast<signed char>(direction) * 57) + x_ec,
                static_cast<float>(y_f0 + 94.0), direction, 1, 0, 0);
        }
        if (action_13c > 153 && action_13c < 158) {
            const int direction = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(998,
                static_cast<float>(static_cast<signed char>(direction) * 57) + x_ec,
                static_cast<float>(y_f0 + 60.0), direction, 1, 0, 0);
        }
        if (action_13c == 158) {
            const int direction = static_cast<unsigned char>(facing_104);
            spawn_owned_object_via_manager(998,
                static_cast<float>(static_cast<signed char>(direction) * 57) + x_ec,
                static_cast<float>(y_f0 + 100.0), direction, 1, 0, 0);
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
