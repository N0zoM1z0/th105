#include "Collision.hpp"

namespace th105 {

namespace {

struct FighterCommonVirtualView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual void slot_28();
    virtual void slot_2c();
    virtual void slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual void slot_40();
    virtual void slot_44();
    virtual void slot_48();
    virtual void slot_4c();
    virtual void slot_50();
};

} // namespace

bool __fastcall is_state_13c_below_32(void *fighter);
void __fastcall update_common_fighter_state_window(void *fighter);

void __fastcall run_common_character_update(void *raw_fighter)
{
    Fighter *fighter = static_cast<Fighter *>(raw_fighter);
    if (fighter->result_186 == 0 &&
        fighter->other_fighter_170->gate_48c == 0) {
        FighterCommonVirtualView *callbacks =
            reinterpret_cast<FighterCommonVirtualView *>(fighter);
        if (is_state_13c_below_32(fighter)) {
            callbacks->slot_48();
            if (fighter->field_4a4 == 0) {
                fighter->value_4a2 = 0;
            }
        }

        if (fighter->state_13c >= 0x32 &&
            fighter->state_13c < 0x96 &&
            fighter->y_f0 > 0.0f) {
            update_common_fighter_state_window(fighter);
        }

        callbacks->slot_50();
    }
}

} // namespace th105
