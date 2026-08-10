#include "InputManager.hpp"

namespace th105 {

void InputStateTable::set_input_state_table_entry(unsigned char index, bool state)
{
    entries[index] = state;
}

bool CInputManager::is_raw_key_down(unsigned char scan_code) const
{
    return raw_keyboard_state[scan_code] >> 7;
}

} // namespace th105
