#include "InputManager.hpp"

namespace th105 {

void InputStateTable::set_input_state_table_entry(unsigned char index, bool state)
{
    entries[index] = state;
}

bool DirectInputBackend::is_raw_key_down(unsigned char scan_code) const
{
    return (raw_keyboard_state[scan_code] & 0x80) != 0;
}

void CInputManager::reset_counters()
{
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
