#include "InputCluster.hpp"

namespace th105 {

DirectInputBackend g_direct_input_backend;

void CInputManager::update_player_input_counters_from_raw()
{
    signed char source_id = bindings.source_id;
    if (source_id >= 0) {
        RawGamepadState *state =
            g_direct_input_backend.get_gamepad_state(source_id);
        if (state == 0)
            return;

        if (state->x < -500) {
            if (hold.horizontal > 0)
                hold.horizontal = 0;
            --hold.horizontal;
        } else if (state->x > 500) {
            if (hold.horizontal < 0)
                hold.horizontal = 0;
            ++hold.horizontal;
        } else {
            hold.horizontal = 0;
        }

        if (state->y < -500) {
            if (hold.vertical > 0)
                hold.vertical = 0;
            --hold.vertical;
        } else if (state->y > 500) {
            if (hold.vertical < 0)
                hold.vertical = 0;
            ++hold.vertical;
        } else {
            hold.vertical = 0;
        }

        for (int i = 0; i < 8; ++i) {
            int binding = bindings.buttons[i];
            if (binding >= 0) {
                if (state->buttons[binding] != 0)
                    ++hold.buttons[i];
                else
                    hold.buttons[i] = 0;
            }
        }
        return;
    }

    if (source_id == -1) {
        if (bindings.left >= 0 && bindings.right >= 0) {
            if (g_direct_input_backend.raw_keyboard_state[
                    static_cast<unsigned char>(bindings.left)] & 0x80) {
                if (hold.horizontal > 0)
                    hold.horizontal = 0;
                --hold.horizontal;
            } else if (
                g_direct_input_backend.raw_keyboard_state[
                    static_cast<unsigned char>(bindings.right)] & 0x80) {
                if (hold.horizontal < 0)
                    hold.horizontal = 0;
                ++hold.horizontal;
            } else {
                hold.horizontal = 0;
            }
        }
        if (bindings.up >= 0 && bindings.down >= 0) {
            if (g_direct_input_backend.raw_keyboard_state[
                    static_cast<unsigned char>(bindings.up)] & 0x80) {
                if (hold.vertical > 0)
                    hold.vertical = 0;
                --hold.vertical;
            } else if (
                g_direct_input_backend.raw_keyboard_state[
                    static_cast<unsigned char>(bindings.down)] & 0x80) {
                if (hold.vertical < 0)
                    hold.vertical = 0;
                ++hold.vertical;
            } else {
                hold.vertical = 0;
            }
        }

        for (int i = 0; i < 8; ++i) {
            int binding = bindings.buttons[i];
            if (binding >= 0) {
                if (g_direct_input_backend.raw_keyboard_state[
                        static_cast<unsigned char>(binding)] & 0x80)
                    ++hold.buttons[i];
                else
                    hold.buttons[i] = 0;
            }
        }
        return;
    }

    counters[0] = 0;
    counters[1] = 0;
    counters[2] = 0;
    counters[3] = 0;
    counters[4] = 0;
    counters[5] = 0;
    counters[6] = 0;
    counters[7] = 0;
    counters[8] = 0;
    counters[9] = 0;
}

} // namespace th105
