#include "InputCluster.hpp"

namespace th105 {

void InputStateTableStorage::update_input_state_table()
{
    const unsigned char *raw_keyboard_state =
        g_direct_input_backend.raw_keyboard_state;

    for (unsigned i = 0; i < tracked_keys.size(); i++) {
        unsigned char key = tracked_keys.at(i);
        if (raw_keyboard_state[key] & 0x80)
            key_counters[key]++;
        else
            key_counters[key] = 0;
    }

    int modifier_down;
    if (!(raw_keyboard_state[0x2a] & 0x80) &&
        !(raw_keyboard_state[0x36] & 0x80))
        modifier_down = 0;
    else
        modifier_down = 1;
    modifier_states[0] = static_cast<unsigned char>(modifier_down);

    if (!(raw_keyboard_state[0x38] & 0x80) &&
        !(raw_keyboard_state[0xb8] & 0x80))
        modifier_down = 0;
    else
        modifier_down = 1;
    modifier_states[1] = static_cast<unsigned char>(modifier_down);

    if (!(raw_keyboard_state[0x1d] & 0x80) &&
        !(raw_keyboard_state[0x9d] & 0x80))
        modifier_down = 0;
    else
        modifier_down = 1;
    modifier_states[2] = static_cast<unsigned char>(modifier_down);
}

void InputStateTableStorage::add_tracked_key(unsigned char key)
{
    for (unsigned i = 0; i < tracked_keys.size(); i++) {
        if (tracked_keys.at(i) == key)
            return;
    }
    tracked_keys.push_back(key);
}

} // namespace th105
