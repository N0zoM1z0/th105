#include "ui/ProfileSubmenus.hpp"
#include "input/InputManager.hpp"
#include <stdlib.h>
namespace th105 {
void __cdecl dispatch_indexed_event(unsigned index);
bool CProfileKeyConfig::capture_key_input()
{
    if (count_324 >= 11)
        return false;
    bool active = false;
    for (int key = 1; key < 255; ++key) {
        if (key != 148 && g_direct_input_backend.is_raw_key_down(static_cast<unsigned char>(key))) {
            active = true;
            if (state_328 == 0 && count_324 < 11) {
                if (character_2ec != -1) {
                    for (int i = 0; i < 11; ++i) keys_2f0[i] = -1;
                    count_324 = 0;
                    character_2ec = -1;
                }
                bool duplicate = false;
                for (int i = 0; i < count_324; ++i)
                    if (keys_2f0[i] == key) duplicate = true;
                if (!duplicate) {
                    keys_2f0[count_324] = key;
                    ++count_324;
                    dispatch_indexed_event(40);
                }
            }
        }
    }
    for (int pad = 0; pad < g_direct_input_backend.gamepad_count; ++pad) {
        if (abs(g_direct_input_backend.get_gamepad_state(pad)->x) <= 500 &&
            abs(g_direct_input_backend.get_gamepad_state(pad)->y) <= 500) {
            for (int button = 0; button < 16; ++button) {
                if (g_direct_input_backend.get_gamepad_state(pad)->buttons[button]) {
                    active = true;
                    if (state_328 == 0 && count_324 < 11) {
                        if (character_2ec < 0 || count_324 < 4) {
                            for (int i = 0; i < 11; ++i) keys_2f0[i] = -1;
                            character_2ec = static_cast<signed char>(pad);
                            count_324 = 4;
                            dispatch_indexed_event(40);
                            break;
                        }
                        bool duplicate = false;
                        for (int i = 4; i < count_324; ++i)
                            if (keys_2f0[i] == button) duplicate = true;
                        if (!duplicate) {
                            keys_2f0[count_324] = button;
                            ++count_324;
                            dispatch_indexed_event(40);
                            if (count_324 - 4 >= g_direct_input_backend.get_gamepad_button_count(pad))
                                count_324 = 11;
                        }
                    }
                }
            }
        } else {
            active = true;
            if (state_328 == 0 && (character_2ec < 0 || count_324 < 4)) {
                character_2ec = static_cast<signed char>(pad);
                count_324 = 4;
                dispatch_indexed_event(40);
                for (int i = 4; i < 11; ++i) keys_2f0[i] = -1;
            }
        }
    }
    if (active) {
        ++state_328;
        return true;
    }
    state_328 = 0;
    if (count_324 == 11)
        return false;
    return true;
}
} // namespace th105
