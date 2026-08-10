#pragma once

namespace th105 {

struct BattleSlotState {
    unsigned char unknown_00[0x28];
    void *objects[2];
    unsigned char unknown_30[4];
    unsigned char flags[2];

    void *get_battle_slot_object(unsigned slot) const;
    unsigned char get_battle_slot_flag(unsigned slot) const;
};

int get_battle_setup_task();

} // namespace th105
