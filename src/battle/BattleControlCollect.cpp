#include "BattleController.hpp"

namespace th105 {

struct CNetworkBase;

CNetworkBase *__cdecl get_network_session_for_control_collect();
unsigned char __cdecl is_menu_control_pressed(
    unsigned char index,
    unsigned char unused_1,
    unsigned char unused_2,
    unsigned char unused_3);

void BattleInputGate::collect_battle_control_bits_42a560()
{
    unsigned short packed_control_bits = 0;

    if (!get_network_session_for_control_collect()) {
        if (is_menu_control_pressed(59, 0, 0, 0))
            packed_control_bits = 0x8000;
        if (is_menu_control_pressed(60, 0, 0, 0))
            packed_control_bits |= 0x4000;
        if (is_menu_control_pressed(61, 0, 0, 0))
            packed_control_bits |= 0x2000;
        if (is_menu_control_pressed(63, 0, 0, 0))
            packed_control_bits |= 0x1000;
        if (is_menu_control_pressed(64, 0, 0, 0))
            packed_control_bits |= 0x0800;
        if (is_menu_control_pressed(65, 0, 0, 0))
            packed_control_bits |= 0x0400;
    }

    if (first_control_input_000) {
        queue_control_word(
            (first_control_input_000->control_low_bits_062 & 0x03ff) |
            packed_control_bits);
    }

    if (second_control_input_004) {
        queue_control_word(
            second_control_input_004->control_low_bits_062 & 0x03ff);
    }
}

} // namespace th105
