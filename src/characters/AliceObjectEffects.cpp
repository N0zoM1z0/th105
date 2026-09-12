#include "AliceObjectEffects.hpp"
#include "engine/AngleAtan2.hpp"
#include "CharacterObjectEffects.hpp"
#include "CharacterObjectRuntime.hpp"

#include <math.h>

namespace th105 {

struct AliceObjectOwnerTrackingView {
    CharacterObjectEffectEmitter object_000;
    float tracking_angle_378;

    unsigned char update_owner_tracking_and_proximity();
};

typedef char CheckAliceObjectOwnerTrackingAngleOffset[
    offsetof(AliceObjectOwnerTrackingView, tracking_angle_378) == 0x378 ? 1 : -1];

unsigned char AliceObjectOwnerTrackingView::update_owner_tracking_and_proximity()
{
    float const heading = static_cast<float>(-atan2_degrees(
        static_cast<float>(
            static_cast<double>(object_000.owner_348->y_f0)
            + 100.0 - object_000.y_f0),
        static_cast<float>(object_000.owner_348->x_ec - object_000.x_ec)));
    tracking_angle_378 = heading;

    float speed = static_cast<float>(object_000.spawn_phase_370 + 2.0);
    object_000.spawn_phase_370 = speed;
    if (speed > 20.0f)
        object_000.spawn_phase_370 = 20.0f;

    reinterpret_cast<CharacterObjectRuntime *>(
        reinterpret_cast<unsigned char *>(this) + 4)
        ->set_oriented_components_f0_f4(heading, object_000.spawn_phase_370);

    if (object_000.x_ec - object_000.owner_348->x_ec > 0.0f)
        object_000.facing_104 = -1;
    if (object_000.x_ec - object_000.owner_348->x_ec < 0.0f)
        object_000.facing_104 = 1;

    float delta_x = static_cast<float>(
        object_000.owner_348->x_ec - object_000.x_ec);
    float distance_x = static_cast<float>(fabs(static_cast<double>(delta_x)));
    if (distance_x < 20.0f) {
        float delta_y = static_cast<float>(
            static_cast<double>(object_000.owner_348->y_f0)
            + 100.0 - object_000.y_f0);
        float distance_y = static_cast<float>(fabs(static_cast<double>(delta_y)));
        if (distance_y < 20.0f) {
            --object_000.lifetime_330;
            return 1;
        }
    }
    return 0;
}

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
