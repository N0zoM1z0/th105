#include "InputSelection.hpp"

namespace th105 {

PlayerSlotRecord *get_player_slot_record(unsigned slot)
{
    return reinterpret_cast<PlayerSlotRecord *>(0x006e64c0 + slot * 0x33c);
}

void invalidate_selected_input(unsigned slot)
{
    *reinterpret_cast<PlayerInput **>(0x006e62dc + slot * 4) = 0;
    *reinterpret_cast<signed char *>(0x006e62d8 + slot) = -2;
}

PlayerInput *get_selected_input(unsigned slot)
{
    return *reinterpret_cast<PlayerInput **>(0x006e62dc + slot * 4);
}

signed char *get_combined_menu_input_counters()
{
    return reinterpret_cast<signed char *>(0x006e7558);
}

signed char get_selected_input_source(unsigned slot)
{
    return *reinterpret_cast<signed char *>(0x006e62d8 + slot);
}

unsigned get_session_setup_option()
{
    return *reinterpret_cast<volatile unsigned *>(0x006e62e4);
}

void set_session_setup_option(unsigned value)
{
    *reinterpret_cast<volatile unsigned *>(0x006e62e4) = value;
}

CNetworkBase *get_network_session()
{
    return *reinterpret_cast<CNetworkBase **>(0x006e62fc);
}

} // namespace th105
