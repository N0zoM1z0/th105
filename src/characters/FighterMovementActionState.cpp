#include <stddef.h>
namespace th105 {

struct FighterMovementActionStateView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void set_action(int action);

    unsigned char reserved_004[0x100];
    signed char facing_104;
    unsigned char reserved_105[0x37];
    unsigned short state_13c;
    unsigned char reserved_13e[0x341];
    unsigned char repeat_47f;
    unsigned char repeat_480;
    unsigned char reserved_481[0x233];
    int field_6b4;
    int field_6b8;

    bool is_at_or_below_stage_surface();
    bool update_facing_from_other_fighter();
    void update_movement_action_state();
};

typedef char CheckFacing[(offsetof(FighterMovementActionStateView, facing_104) == 0x104) ? 1 : -1];
typedef char CheckState[(offsetof(FighterMovementActionStateView, state_13c) == 0x13c) ? 1 : -1];
typedef char CheckRepeat[(offsetof(FighterMovementActionStateView, repeat_47f) == 0x47f) ? 1 : -1];
typedef char CheckField6b4[(offsetof(FighterMovementActionStateView, field_6b4) == 0x6b4) ? 1 : -1];

void FighterMovementActionStateView::update_movement_action_state()
{
    if (is_at_or_below_stage_surface()) {
        repeat_47f = 0;
        repeat_480 = 0;
    }

    if (!is_at_or_below_stage_surface())
        return;

    if (state_13c == 6 || state_13c == 7 || state_13c == 8)
        return;

    if (field_6b8 < 0) {
        update_facing_from_other_fighter();
        if (field_6b4 == 0) {
            if (state_13c != 6)
                set_action(6);
            return;
        }

        int const direction = static_cast<signed char>(facing_104) * field_6b4;
        if (direction > 0) {
            if (state_13c != 7)
                set_action(7);
            return;
        }
        if (direction < 0 && state_13c != 8)
            set_action(8);
        return;
    }

    if (field_6b8 > 0) {
        if (state_13c != 2) {
            if (state_13c != 1) {
                set_action(1);
                update_facing_from_other_fighter();
                return;
            }
        }
        if (state_13c != 1) {
            set_action(2);
            update_facing_from_other_fighter();
            return;
        }
    } else if (field_6b4 != 0) {
        update_facing_from_other_fighter();
        int const direction = static_cast<signed char>(facing_104) * field_6b4;
        if (direction > 0) {
            if (state_13c != 4) {
                set_action(4);
                update_facing_from_other_fighter();
                return;
            }
        } else {
            if (state_13c != 5) {
                set_action(5);
                update_facing_from_other_fighter();
                return;
            }
        }
    } else {
        if (state_13c == 1 || state_13c == 2) {
            set_action(3);
        } else if (state_13c != 0 && state_13c != 3 && state_13c != 10) {
            set_action(0);
            update_facing_from_other_fighter();
            return;
        }
    }
    update_facing_from_other_fighter();
}

} // namespace th105
