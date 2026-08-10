#include "Collision.hpp"

namespace th105 {

int __fastcall is_state_13c_in_32_95(Fighter *fighter)
{
    return fighter->state_13c >= 0x32 && fighter->state_13c < 0x96;
}

int __fastcall is_positive_y_and_state_window(Fighter *fighter)
{
    return fighter->y_f0 > 0.0f && fighter->field_49e == 0 &&
        fighter->state_13c >= 0x32 && fighter->state_13c < 0x96;
}

int __fastcall is_y_at_or_below_stage_surface(Fighter *fighter)
{
    return fighter->y_f0 <= stage_surface_height_at_x(fighter);
}

} // namespace th105
