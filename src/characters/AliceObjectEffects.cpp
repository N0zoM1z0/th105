#include "AliceObjectEffects.hpp"

#include <math.h>

namespace th105 {

double __cdecl atan2_degrees(float y, float x);

unsigned char AliceObjectFlightState::update_from_owner_and_target(
    short expected_state)
{
    x_ec = owner_348->x_ec;
    y_f0 = owner_348->y_f0 + 100.0;

    if (target_34c) {
        if (facing_104 == 1) {
            heading_12c = static_cast<float>(-atan2_degrees(
                target_34c->y_f0 - y_f0,
                target_34c->x_ec - x_ec));
        } else {
            heading_12c = static_cast<float>(atan2_degrees(
                target_34c->y_f0 - y_f0,
                target_34c->x_ec - x_ec) + 180.0);
        }

        x_delta_squared_370 =
            (target_34c->x_ec - x_ec) * (target_34c->x_ec - x_ec);
        y_delta_squared_374 =
            (target_34c->y_f0 - y_f0) * (target_34c->y_f0 - y_f0);
        target_distance_378 = static_cast<float>(
            sqrt(y_delta_squared_374 + x_delta_squared_370));
        distance_scale_11c = target_distance_378 * 0.00390625;

        if (target_34c->state_13e != expected_state) {
            return 0;
        }
    }

    --lifetime_330;
    return 1;
}

} // namespace th105
