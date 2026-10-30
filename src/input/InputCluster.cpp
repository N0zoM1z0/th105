#include "InputStateTableUpdate.cpp"
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
