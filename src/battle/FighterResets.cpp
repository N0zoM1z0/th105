#include "Collision.hpp"

namespace th105 {

void __fastcall reset_fighter_fields_6bc_728(CollisionContext *context)
{
    Fighter *volatile *fighter = context->fighters;
    int count = 2;
    do {
        (*fighter)->field_6dc = 0;
        (*fighter)->field_6f4 = 0;
        (*fighter)->field_6bc = 0;
        (*fighter)->field_6e0 = 0;
        (*fighter)->field_6f8 = 0;
        (*fighter)->field_6c0 = 0;
        (*fighter)->field_6e4 = 0;
        (*fighter)->field_6fc = 0;
        (*fighter)->field_6c4 = 0;
        (*fighter)->field_6f0 = 0;
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
        (*fighter)->field_6d4 = 0;
        (*fighter)->field_6b4 = 0;
        (*fighter)->field_6d8 = 0;
        (*fighter)->field_6b8 = 0;
        (*fighter)->field_6dc = 0;
        (*fighter)->field_6f4 = 0;
        (*fighter)->field_6bc = 0;
        (*fighter)->field_6e0 = 0;
        (*fighter)->field_6f8 = 0;
        (*fighter)->field_6c0 = 0;
        (*fighter)->field_6e4 = 0;
        (*fighter)->field_6fc = 0;
        (*fighter)->field_6c4 = 0;
        (*fighter)->field_6e8 = 0;
        (*fighter)->field_700 = 0;
        (*fighter)->field_6c8 = 0;
        (*fighter)->field_6ec = 0;
        (*fighter)->field_704 = 0;
        (*fighter)->field_6cc = 0;
        (*fighter)->field_6f0 = 0;
        (*fighter)->field_708 = 0;
        (*fighter)->field_6d0 = 0;
        (*fighter)->field_728 = 0;
        (*fighter)->field_724 = 0;
        ++fighter;
    } while (--count != 0);
}

} // namespace th105
