#include "Collision.hpp"

// TH105 1.06a body-collision phase at 0x0046CCA0. The CollisionContext
// name is an ABI view; original class and TU spelling remain unknown.

namespace th105 {

// Each byte remembers which fighter owns one stage-boundary side.  The target
// stores -1 while no owner is latched and player indices 0/1 otherwise.
signed char g_body_collision_edge_owner_a = -1;
signed char g_body_collision_edge_owner_b = -1;

void CollisionContext::resolve_fighter_body_collision()
{
    fighters[0]->body_overlap_x_6a4 = 0.0f;
    fighters[1]->body_overlap_x_6a4 = 0.0f;

    if (fighters[0]->frame_158->body_aabb_54 == 0 ||
        fighters[1]->frame_158->body_aabb_54 == 0) {
        return;
    }

    float first_coupled_motion;
    float second_coupled_motion;
    float first_motion;
    float second_motion;
    first_motion =
        fighters[0]->x_scale_4dc * fighters[0]->x_component_f4;
    second_motion =
        fighters[1]->x_scale_4dc * fighters[1]->x_component_f4;
    first_coupled_motion =
        (fighters[1]->peer_component_6ac + fighters[0]->x_component_f4) *
        fighters[0]->x_scale_4dc;
    second_coupled_motion =
        (fighters[0]->peer_component_6ac + fighters[1]->x_component_f4) *
        fighters[1]->x_scale_4dc;

    // Target +0x08 is a boundary byte until edge resolution finishes, then
    // a float separation. Only the member written in the active phase is read.
    union BoundarySeparationScratch {
        signed char boundary;
        float separation;
    } first_scratch;
    first_scratch.boundary = fighters[0]->classify_fighter_x_boundary();
    signed char second_boundary = fighters[1]->classify_fighter_x_boundary();

    if (g_body_collision_edge_owner_b == 0) {
        if (first_scratch.boundary != -1) {
            g_body_collision_edge_owner_b = -1;
        }
    } else if (g_body_collision_edge_owner_b == 1 && second_boundary != -1) {
        g_body_collision_edge_owner_b = -1;
    }

    if (g_body_collision_edge_owner_a == 0) {
        if (first_scratch.boundary != 1) {
            g_body_collision_edge_owner_a = -1;
        }
    } else if (g_body_collision_edge_owner_a == 1 && second_boundary != 1) {
        g_body_collision_edge_owner_a = -1;
    }

    WorldAabb first_box;
    WorldAabb second_box;
    if (first_scratch.boundary == -1 && g_body_collision_edge_owner_b < 0) {
        g_body_collision_edge_owner_b = 0;
    } else if (second_boundary == -1 && g_body_collision_edge_owner_b < 0) {
        g_body_collision_edge_owner_b = 1;
    }
    if (first_scratch.boundary == 1 && g_body_collision_edge_owner_a < 0) {
        g_body_collision_edge_owner_a = 0;
    } else if (second_boundary == 1 && g_body_collision_edge_owner_a < 0) {
        g_body_collision_edge_owner_a = 1;
    }

    transform_local_aabb_to_world(
        reinterpret_cast<const ActorPosition *>(fighters[0]),
        fighters[0]->frame_158->body_aabb_54,
        &first_box);
    transform_local_aabb_to_world(
        reinterpret_cast<const ActorPosition *>(fighters[1]),
        fighters[1]->frame_158->body_aabb_54,
        &second_box);
    if (test_and_accumulate_float_aabb_overlap(&first_box, &second_box) == 0) {
        return;
    }
    reset_collision_extents();

    if (first_scratch.boundary == -1 && g_body_collision_edge_owner_b == 0) {
        fighters[1]->x_ec -= second_box.right - first_box.left - 1.0;
        if (!(first_coupled_motion *
                    static_cast<signed char>(fighters[0]->facing_104) +
                second_coupled_motion *
                    static_cast<signed char>(fighters[1]->facing_104) >=
            0.0f)) {
            return;
        }
        if (!(static_cast<signed char>(fighters[1]->facing_104) *
                second_coupled_motion >= 0.0f)) {
            return;
        }
        fighters[0]->body_overlap_x_6a4 = -first_coupled_motion;
        fighters[1]->body_overlap_x_6a4 = -second_coupled_motion;
        return;
    }

    if (second_boundary == -1 && g_body_collision_edge_owner_b == 1) {
        fighters[0]->x_ec -= first_box.right - second_box.left - 1.0;
        if (!(second_coupled_motion *
                    static_cast<signed char>(fighters[1]->facing_104) +
                first_coupled_motion *
                    static_cast<signed char>(fighters[0]->facing_104) >=
            0.0f)) {
            return;
        }
        if (!(static_cast<signed char>(fighters[0]->facing_104) *
                first_coupled_motion >= 0.0f)) {
            return;
        }
        fighters[0]->body_overlap_x_6a4 = -first_coupled_motion;
        fighters[1]->body_overlap_x_6a4 = -second_coupled_motion;
        return;
    }

    if (second_boundary == 1 && g_body_collision_edge_owner_a == 1) {
        fighters[0]->x_ec += second_box.right - first_box.left - 1.0;
        if (!(second_coupled_motion *
                    static_cast<signed char>(fighters[1]->facing_104) +
                first_coupled_motion *
                    static_cast<signed char>(fighters[0]->facing_104) <=
            0.0f)) {
            return;
        }
        if (!(static_cast<signed char>(fighters[0]->facing_104) *
                first_coupled_motion <= 0.0f)) {
            return;
        }
        fighters[0]->body_overlap_x_6a4 = -first_coupled_motion;
        fighters[1]->body_overlap_x_6a4 = -second_coupled_motion;
        return;
    }

    if (first_scratch.boundary == 1 && g_body_collision_edge_owner_a == 0) {
        fighters[1]->x_ec += first_box.right - second_box.left - 1.0;
        if (!(first_coupled_motion *
                    static_cast<signed char>(fighters[0]->facing_104) +
                second_coupled_motion *
                    static_cast<signed char>(fighters[1]->facing_104) <=
            0.0f)) {
            return;
        }
        if (!(static_cast<signed char>(fighters[1]->facing_104) *
                second_coupled_motion <= 0.0f)) {
            return;
        }
        fighters[0]->body_overlap_x_6a4 = -first_coupled_motion;
        fighters[1]->body_overlap_x_6a4 = -second_coupled_motion;
        return;
    }

    // Both ordinary separation paths share one averaged horizontal velocity.
    float average_motion;
    if (!(first_box.left + first_box.right >
            second_box.right + second_box.left) &&
        (first_box.left + first_box.right !=
             second_box.right + second_box.left ||
         !(first_box.top + first_box.bottom <
               second_box.top + second_box.bottom))) {
        first_scratch.separation = first_box.right - second_box.left - 1.0;
        if (first_scratch.separation < 0.0f) {
            first_scratch.separation = 0.0f;
        }
        if (static_cast<char>(
                fighters[0]->test_proposed_x_against_stage_height(
                    -first_scratch.separation * 0.5)) == 0) {
            fighters[0]->x_ec -= first_scratch.separation * 0.5;
        }
        if (static_cast<char>(
                fighters[1]->test_proposed_x_against_stage_height(
                    first_scratch.separation * 0.5)) == 0) {
            fighters[1]->x_ec += first_scratch.separation * 0.5;
        }

        if (!(second_motion *
                  static_cast<signed char>(fighters[1]->facing_104) <=
              first_motion *
                  static_cast<signed char>(fighters[0]->facing_104))) {
            return;
        }
        average_motion =
            (second_coupled_motion *
                 static_cast<signed char>(fighters[1]->facing_104) +
             first_coupled_motion *
                 static_cast<signed char>(fighters[0]->facing_104)) * 0.5;
        // Round each directional velocity before subtracting its old motion.
        second_coupled_motion =
            average_motion * static_cast<signed char>(fighters[1]->facing_104);
        first_coupled_motion =
            static_cast<signed char>(fighters[0]->facing_104) * average_motion;
        first_motion = first_coupled_motion - first_motion;
        second_motion = second_coupled_motion - second_motion;
        fighters[0]->body_overlap_x_6a4 = first_motion;
        fighters[1]->body_overlap_x_6a4 = second_motion;
        return;
    }

    first_scratch.separation = second_box.right - first_box.left - 1.0;
    if (first_scratch.separation < 0.0f) {
        first_scratch.separation = 0.0f;
    }
    const double half_separation = first_scratch.separation * 0.5;
    if (static_cast<char>(
            fighters[0]->test_proposed_x_against_stage_height(half_separation)) == 0) {
        fighters[0]->x_ec += half_separation;
    }
    if (static_cast<char>(
            fighters[1]->test_proposed_x_against_stage_height(
                -first_scratch.separation * 0.5)) == 0) {
        fighters[1]->x_ec -= half_separation;
    }

    if (!(static_cast<signed char>(fighters[0]->facing_104) * first_motion <=
          static_cast<signed char>(fighters[1]->facing_104) * second_motion)) {
        return;
    }
    average_motion =
        (second_coupled_motion *
             static_cast<signed char>(fighters[1]->facing_104) +
         first_coupled_motion *
             static_cast<signed char>(fighters[0]->facing_104)) * 0.5;
    second_coupled_motion =
        average_motion * static_cast<signed char>(fighters[1]->facing_104);
    first_coupled_motion =
        static_cast<signed char>(fighters[0]->facing_104) * average_motion;
    fighters[0]->body_overlap_x_6a4 = first_coupled_motion - fighters[0]->x_component_f4;
    fighters[1]->body_overlap_x_6a4 = second_coupled_motion - fighters[1]->x_component_f4;
}

} // namespace th105
