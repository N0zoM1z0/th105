#include "BattleSetup.hpp"

namespace th105 {

void *BattleSlotState::get_battle_slot_object(unsigned slot) const
{
    return objects[slot];
}

unsigned char BattleSlotState::get_battle_slot_flag(unsigned slot) const
{
    return flags[slot];
}

int get_battle_setup_task()
{
    return *reinterpret_cast<volatile int *>(0x006e62e8);
}

} // namespace th105
