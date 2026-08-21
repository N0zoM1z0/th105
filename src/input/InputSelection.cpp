#include "InputSelection.hpp"

namespace th105 {

extern unsigned char g_player_slot_records[];
extern PlayerInput *g_selected_inputs[];
extern signed char g_selected_input_sources[];
extern unsigned char g_combined_menu_input_storage[];
extern volatile unsigned g_session_setup_option;
extern CNetworkBase *g_network_session;

PlayerSlotRecord *get_player_slot_record(unsigned slot)
{
    return reinterpret_cast<PlayerSlotRecord *>(
        g_player_slot_records + slot * 0x33c);
}

void invalidate_selected_input(unsigned slot)
{
    g_selected_inputs[slot] = 0;
    g_selected_input_sources[slot] = -2;
}

PlayerInput *get_selected_input(unsigned slot)
{
    return g_selected_inputs[slot];
}

signed char *get_combined_menu_input_counters()
{
    return reinterpret_cast<signed char *>(
        g_combined_menu_input_storage + 0x38);
}

signed char get_selected_input_source(unsigned slot)
{
    return g_selected_input_sources[slot];
}

unsigned get_session_setup_option()
{
    return g_session_setup_option;
}

void set_session_setup_option(unsigned value)
{
    g_session_setup_option = value;
}

CNetworkBase *get_network_session()
{
    return g_network_session;
}

} // namespace th105
