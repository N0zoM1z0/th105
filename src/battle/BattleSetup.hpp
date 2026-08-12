#pragma once

#include "GameMode.hpp"

namespace th105 {

class Character;

struct BattleSlotState {
    unsigned char unknown_00[0x28];
    Character *slot_characters[3];
    unsigned char slot_active[3];

    Character *get_slot_character(unsigned slot) const;
    unsigned char is_slot_active(unsigned slot) const;
    int create_fighter_for_slot(int slot, const MatchSetup::Side *setup);
};

int get_battle_setup_task();

} // namespace th105
