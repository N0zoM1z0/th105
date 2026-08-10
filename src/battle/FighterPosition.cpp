#include "Collision.hpp"

namespace th105 {

void __fastcall integrate_and_clamp_fighter_position(void *raw_fighter)
{
    Fighter *fighter = static_cast<Fighter *>(raw_fighter);
    if (fighter->result_186 != 0 ||
        fighter->other_fighter_170->gate_48c != 0) {
        return;
    }

    const float delta_x =
        static_cast<float>(static_cast<signed char>(fighter->facing_104)) *
        (fighter->body_overlap_x_6a4 + fighter->x_component_f4 +
         fighter->other_fighter_170->peer_component_6ac) *
        fighter->x_scale_4dc;

    const signed char edge = fighter->classify_fighter_x_boundary();
    if (0.0 <= delta_x * static_cast<float>(edge) &&
        static_cast<char>(
            fighter->test_proposed_x_against_stage_height(delta_x)) == 0) {
        fighter->x_ec += delta_x;
    }

    if (fighter->x_ec < 40.0f) {
        fighter->x_ec = 40.0f;
    }
    if (fighter->x_ec > 1240.0f) {
        fighter->x_ec = 1240.0f;
    }

    fighter->y_f0 += fighter->y_scale_4e0 * fighter->y_component_f8;
    if (static_cast<char>(is_y_at_or_below_stage_surface(fighter)) != 0) {
        fighter->y_f0 = stage_surface_height_at_x(fighter);
    }
}

} // namespace th105
