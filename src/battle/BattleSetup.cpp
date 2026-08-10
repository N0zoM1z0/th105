#include "BattleSetup.hpp"

namespace th105 {

Character *BattleSlotState::get_slot_character(unsigned slot) const
{
    return slot_characters[slot];
}

unsigned char BattleSlotState::is_slot_active(unsigned slot) const
{
    return slot_active[slot];
}

int get_battle_setup_task()
{
    return *reinterpret_cast<volatile int *>(0x006e62e8);
}

} // namespace th105
