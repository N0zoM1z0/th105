#include "Collision.hpp"

namespace th105 {

namespace {

struct FighterActionView {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void set_action(int action);
};

typedef void (__thiscall *SetFighterAction)(Fighter *fighter, int action);

} // namespace

int __cdecl selector_random_roll(int limit);

bool __fastcall is_state_13c_below_32(void *raw_fighter)
{
    Fighter *fighter = static_cast<Fighter *>(raw_fighter);
    return fighter->state_13c < 0x32;
}

void __fastcall update_common_fighter_state_window(void *raw_fighter)
{
    Fighter *fighter = static_cast<Fighter *>(raw_fighter);
    if ((fighter->frame_158->flags_4c & 0x100000) != 0 ||
        fighter->value_4a2 >= 100 ||
        fighter->value_174 <= 0 ||
        is_y_at_or_below_stage_surface(fighter)) {
        return;
    }
    if (fighter->field_49e != 0) {
        --fighter->field_49e;
        return;
    }

    FighterActionView *action =
        reinterpret_cast<FighterActionView *>(fighter);
    if (fighter->field_6b0 == 0 && fighter->state_72c == 3) {
        switch (*reinterpret_cast<int *>(
            *reinterpret_cast<unsigned *>(0x006e4e28) + 0x28)) {
        case 0:
            fighter->value_4a2 = 0;
            update_fighter_facing_from_other_x(fighter);
            action->set_action(0xb4);
            return;
        case 1:
            fighter->value_4a2 = 0;
            update_fighter_facing_from_other_x(fighter);
            action->set_action(0xb5);
            return;
        case 2: {
            fighter->value_4a2 = 0;
            update_fighter_facing_from_other_x(fighter);
            void **vtable = *reinterpret_cast<void ***>(fighter);
            const int next_action = selector_random_roll(2) + 0xb4;
            reinterpret_cast<SetFighterAction>(vtable[2])(
                fighter, next_action);
            return;
        }
        default:
            return;
        }
    }

    if (fighter->field_6b4 != 0 &&
        (fighter->field_6c8 | fighter->field_6c4 |
         fighter->field_6c0 | fighter->field_6bc) != 0) {
        fighter->value_4a2 = 0;
        update_fighter_facing_from_other_x(fighter);
        if (static_cast<signed char>(fighter->facing_104) *
                fighter->field_6b4 > 0) {
            action->set_action(0xb4);
            return;
        }
        action->set_action(0xb5);
    }
}

} // namespace th105
