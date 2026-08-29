#pragma once

#include "Input.hpp"

namespace th105 {

struct CNetworkBase;
struct PlayerSlotRecord;

PlayerSlotRecord *get_player_slot_record(unsigned slot);
void invalidate_selected_input(unsigned slot);
PlayerInput *get_selected_input(unsigned slot);
signed char *get_combined_menu_input_counters();
signed char get_selected_input_source(unsigned slot);
unsigned get_session_setup_option();
void set_session_setup_option(unsigned value);
CNetworkBase *get_network_session();
void __cdecl rebind_selected_input_43b640(
    int slot,
    signed char require_distinct);

} // namespace th105
