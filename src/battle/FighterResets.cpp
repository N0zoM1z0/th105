#include "Collision.hpp"

namespace th105 {

void __fastcall reset_fighter_fields_6bc_728(CollisionContext *context)
{
    Fighter *volatile *fighter = context->fighters;
    int count = 2;
    do {
        (*fighter)->snapshot_6d4.buttons[0] = 0;
        (*fighter)->field_6f4 = 0;
        (*fighter)->field_6bc = 0;
        (*fighter)->snapshot_6d4.buttons[1] = 0;
        (*fighter)->field_6f8 = 0;
        (*fighter)->field_6c0 = 0;
        (*fighter)->snapshot_6d4.buttons[2] = 0;
        (*fighter)->field_6fc = 0;
        (*fighter)->field_6c4 = 0;
        (*fighter)->snapshot_6d4.buttons[5] = 0;
        (*fighter)->field_708 = 0;
        (*fighter)->field_6d0 = 0;
        (*fighter)->field_728 = 0;
        ++fighter;
    } while (--count != 0);
}

void __fastcall reset_fighter_fields_6b4_728(CollisionContext *context)
{
    Fighter *volatile *fighter = context->fighters;
    int count = 2;
    do {
        (*fighter)->snapshot_6d4.horizontal = 0;
        (*fighter)->field_6b4 = 0;
        (*fighter)->snapshot_6d4.vertical = 0;
        (*fighter)->field_6b8 = 0;
        (*fighter)->snapshot_6d4.buttons[0] = 0;
        (*fighter)->field_6f4 = 0;
        (*fighter)->field_6bc = 0;
        (*fighter)->snapshot_6d4.buttons[1] = 0;
        (*fighter)->field_6f8 = 0;
        (*fighter)->field_6c0 = 0;
        (*fighter)->snapshot_6d4.buttons[2] = 0;
        (*fighter)->field_6fc = 0;
        (*fighter)->field_6c4 = 0;
        (*fighter)->snapshot_6d4.buttons[3] = 0;
        (*fighter)->field_700 = 0;
        (*fighter)->field_6c8 = 0;
        (*fighter)->snapshot_6d4.buttons[4] = 0;
        (*fighter)->field_704 = 0;
        (*fighter)->field_6cc = 0;
        (*fighter)->snapshot_6d4.buttons[5] = 0;
        (*fighter)->field_708 = 0;
        (*fighter)->field_6d0 = 0;
        (*fighter)->field_728 = 0;
        (*fighter)->field_724 = 0;
        ++fighter;
    } while (--count != 0);
}

} // namespace th105
