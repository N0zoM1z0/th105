#include "InputCluster.hpp"

namespace th105 {

DirectInputBackend g_direct_input_backend;

void CInputManager::update_player_input_counters_from_raw()
{
    signed char source_id = bindings.source_id;
    if (source_id >= 0) {
        RawGamepadState *state =
            g_direct_input_backend.get_gamepad_state(source_id);
        int zero = 0;
        if (state == reinterpret_cast<RawGamepadState *>(zero))
            return;

        if (state->x < -500) {
            if (hold.horizontal > zero)
                hold.horizontal = zero;
            --hold.horizontal;
        } else if (state->x > 500) {
            if (hold.horizontal < zero)
                hold.horizontal = zero;
            ++hold.horizontal;
        } else {
            hold.horizontal = zero;
        }

        if (state->y < -500) {
            if (hold.vertical > zero)
                hold.vertical = zero;
            --hold.vertical;
        } else if (state->y > 500) {
            if (hold.vertical < zero)
                hold.vertical = zero;
            ++hold.vertical;
        } else {
            hold.vertical = zero;
        }

        int *counter = hold.buttons;
        int remaining = 8;
        do {
            int binding = counter[-10];
            if (binding >= zero)
                if (state->buttons[binding] != zero)
                    ++*counter;
                else
                    *counter = zero;
            ++counter;
        } while (--remaining != 0);
        return;
    }

    if (source_id == -1) {
        int zero = 0;
        unsigned char high_bit = 0x80;
        if (bindings.left >= zero && bindings.right >= zero) {
            if (g_direct_input_backend.raw_keyboard_state[
                    static_cast<unsigned char>(bindings.left)] & high_bit) {
                if (hold.horizontal > zero)
                    hold.horizontal = zero;
                --hold.horizontal;
            } else if (
                g_direct_input_backend.raw_keyboard_state[
                    static_cast<unsigned char>(bindings.right)] & high_bit) {
                if (hold.horizontal < zero)
                    hold.horizontal = zero;
                ++hold.horizontal;
            } else {
                hold.horizontal = zero;
            }
        }
        if (bindings.up >= zero && bindings.down >= zero) {
            if (g_direct_input_backend.raw_keyboard_state[
                    static_cast<unsigned char>(bindings.up)] & high_bit) {
                if (hold.vertical > zero)
                    hold.vertical = zero;
                --hold.vertical;
            } else if (
                g_direct_input_backend.raw_keyboard_state[
                    static_cast<unsigned char>(bindings.down)] & high_bit) {
                if (hold.vertical < zero)
                    hold.vertical = zero;
                ++hold.vertical;
            } else {
                hold.vertical = zero;
            }
        }

        int *counter = hold.buttons;
        int remaining = 8;
        do {
            int binding = counter[-10];
            if (binding >= zero) {
                if (g_direct_input_backend.raw_keyboard_state[
                        static_cast<unsigned char>(binding)] & high_bit)
                    ++*counter;
                else
                    *counter = zero;
            }
            ++counter;
        } while (--remaining != 0);
        return;
    }

    int zero = 0;
    counters[0] = zero;
    counters[1] = zero;
    counters[2] = zero;
    counters[3] = zero;
    counters[4] = zero;
    counters[5] = zero;
    counters[6] = zero;
    counters[7] = zero;
    counters[8] = zero;
    counters[9] = zero;
}

} // namespace th105
