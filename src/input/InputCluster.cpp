#include "InputCluster.hpp"

#include <cstring>

namespace th105 {

void __stdcall clear_input_key_list_storage(void *storage);

signed char CInputManagerCluster::get_active_source() const
{
    return active_source;
}

InputStateTableStorage::InputStateTableStorage()
{
}

void InputStateTableStorage::reset_input_state_table()
{
    std::memset(key_counters, 0, sizeof(key_counters));
    clear_input_key_list_storage(&tracked_keys);
    modifier_states[0] = 0;
    modifier_states[1] = 0;
    modifier_states[2] = 0;
}

void InputStateTableStorage::update_input_state_table()
{
    const unsigned char *raw_keyboard_state =
        reinterpret_cast<const unsigned char *>(0x006ecff0);

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

bool InputStateTableStorage::is_initial_press(
    unsigned char key,
    bool require_modifier_0,
    bool require_modifier_1,
    bool require_modifier_2) const
{
    if (key_counters[key] != 1)
        return false;
    if (require_modifier_0 && !modifier_states[0])
        return false;
    if (require_modifier_1 && !modifier_states[1])
        return false;
    if (require_modifier_2 && !modifier_states[2])
        return false;
    return true;
}

} // namespace th105
