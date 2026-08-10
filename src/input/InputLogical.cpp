#include "InputManager.hpp"

namespace th105 {

void CInputManagerEx::build_player_logical_input_mask()
{
    if (use_injected_input) {
        int zero = 0;
        int decrement = -1;
        int increment = 1;

        {
            unsigned short initial_mask = injected_mask;
            if (initial_mask & 0x0004) {
                if (hold.horizontal > zero)
                    hold.horizontal = zero;
                hold.horizontal += decrement;
            } else if (initial_mask & 0x0008) {
                if (hold.horizontal < zero)
                    hold.horizontal = zero;
                hold.horizontal += increment;
            } else {
                hold.horizontal = zero;
            }

            if (initial_mask & 0x0001) {
                if (hold.vertical > zero)
                    hold.vertical = zero;
                hold.vertical += decrement;
            } else if (initial_mask & 0x0002) {
                if (hold.vertical < zero)
                    hold.vertical = zero;
                hold.vertical += increment;
            } else {
                hold.vertical = zero;
            }

            if (initial_mask & 0x0010)
                hold.buttons[0] += increment;
            else
                hold.buttons[0] = zero;
        }

        unsigned char *mask_bytes = reinterpret_cast<unsigned char *>(
            &injected_mask);
        if (mask_bytes[0] & 0x20)
            hold.buttons[1] += increment;
        else
            hold.buttons[1] = zero;
        if (mask_bytes[0] & 0x40)
            hold.buttons[2] += increment;
        else
            hold.buttons[2] = zero;
        if (mask_bytes[0] & 0x80)
            hold.buttons[3] += increment;
        else
            hold.buttons[3] = zero;
        if (*reinterpret_cast<unsigned short *>(mask_bytes) & 0x0100)
            hold.buttons[4] += increment;
        else
            hold.buttons[4] = zero;
        if (*reinterpret_cast<unsigned short *>(mask_bytes) & 0x0200)
            hold.buttons[5] += increment;
        else
            hold.buttons[5] = zero;
        if (*reinterpret_cast<unsigned short *>(mask_bytes) & 0x0400)
            hold.buttons[6] += increment;
        else
            hold.buttons[6] = zero;
        if (*reinterpret_cast<unsigned short *>(mask_bytes) & 0x0800)
            hold.buttons[7] += increment;
        else
            hold.buttons[7] = zero;
        resolved_mask = *reinterpret_cast<unsigned short *>(mask_bytes);
        return;
    }

    CInputManager::update_player_input_counters_from_raw();
    resolved_mask = 0;
    if (hold.horizontal < 0)
        resolved_mask |= 0x0004;
    else if (hold.horizontal > 0)
        resolved_mask |= 0x0008;
    if (hold.vertical < 0)
        resolved_mask |= 0x0001;
    else if (hold.vertical > 0)
        resolved_mask |= 0x0002;
    for (unsigned i = 0; i < 8; i++) {
        if (hold.buttons[i] != 0)
            resolved_mask |= static_cast<unsigned short>(0x0010 << i);
    }
}

} // namespace th105
