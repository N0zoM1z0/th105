#pragma once

#include "battle/Collision.hpp"

#include <stddef.h>

namespace th105 {

// Partial derived view.  The target establishes only the fields below; the
// concrete class continues beyond this observed prefix.
struct Sakuya : Fighter {
    short field_730;
    short field_732;
    short field_734;
    short field_736;
    short field_738;
    unsigned char unknown_73a[0x02];
    float field_73c;
    float field_740;
    unsigned char unknown_744[0x08];
    float field_74c;
    unsigned char field_750;
    unsigned char unknown_751[0x03];
    unsigned char skill_cancel_754;
    unsigned char skill_cancel_755;
    unsigned char skill_cancel_756;
    unsigned char unknown_757;

    void on_action_changed();
    void handle_input_and_select_action();
};

typedef char CheckSakuyaField730Offset[
    offsetof(Sakuya, field_730) == 0x730 ? 1 : -1];
typedef char CheckSakuyaSkillCancel754Offset[
    offsetof(Sakuya, skill_cancel_754) == 0x754 ? 1 : -1];

} // namespace th105
