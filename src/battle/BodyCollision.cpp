#include "Collision.hpp"

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

    float first_motion =
        fighters[0]->x_scale_4dc * fighters[0]->x_component_f4;
    float second_motion =
        fighters[1]->x_scale_4dc * fighters[1]->x_component_f4;
    float first_coupled_motion =
        (fighters[1]->peer_component_6ac + fighters[0]->x_component_f4) *
        fighters[0]->x_scale_4dc;
    float second_coupled_motion =
        (fighters[0]->peer_component_6ac + fighters[1]->x_component_f4) *
        fighters[1]->x_scale_4dc;

    signed char first_boundary = fighters[0]->classify_fighter_x_boundary();
    signed char second_boundary = fighters[1]->classify_fighter_x_boundary();

    if (g_body_collision_edge_owner_b == 0) {
        if (first_boundary != -1) {
            g_body_collision_edge_owner_b = -1;
        }
    } else if (g_body_collision_edge_owner_b == 1 && second_boundary != -1) {
        g_body_collision_edge_owner_b = -1;
    }

    if (g_body_collision_edge_owner_a == 0) {
        if (first_boundary != 1) {
            g_body_collision_edge_owner_a = -1;
        }
    } else if (g_body_collision_edge_owner_a == 1 && second_boundary != 1) {
        g_body_collision_edge_owner_a = -1;
    }

    if (first_boundary == -1 && g_body_collision_edge_owner_b < 0) {
        g_body_collision_edge_owner_b = 0;
        goto update_second_edge_owner;
    }
    if (second_boundary == -1 && g_body_collision_edge_owner_b < 0) {
        g_body_collision_edge_owner_b = 1;
    }
    if (first_boundary != 1 || g_body_collision_edge_owner_a >= 0) {
        goto update_second_edge_owner;
    }
    g_body_collision_edge_owner_a = 0;

update_second_edge_owner:
    if (second_boundary == 1 && g_body_collision_edge_owner_a < 0) {
        g_body_collision_edge_owner_a = 1;
    }

    WorldAabb first_box;
    WorldAabb second_box;
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

    if (first_boundary == -1 && g_body_collision_edge_owner_b == 0) {
        fighters[1]->x_ec -= second_box.right - first_box.left - 1.0;
        if (first_coupled_motion *
                    static_cast<signed char>(fighters[0]->facing_104) +
                second_coupled_motion *
                    static_cast<signed char>(fighters[1]->facing_104) <
            0.0f) {
            return;
        }
        if (static_cast<signed char>(fighters[1]->facing_104) *
                second_coupled_motion < 0.0f) {
            return;
        }
        fighters[0]->body_overlap_x_6a4 = -first_coupled_motion;
        fighters[1]->body_overlap_x_6a4 = -second_coupled_motion;
        return;
    }

    if (second_boundary == -1 && g_body_collision_edge_owner_b == 1) {
        fighters[0]->x_ec -= first_box.right - second_box.left - 1.0;
        if (second_coupled_motion *
                    static_cast<signed char>(fighters[1]->facing_104) +
                first_coupled_motion *
                    static_cast<signed char>(fighters[0]->facing_104) <
            0.0f) {
            return;
        }
        if (static_cast<signed char>(fighters[0]->facing_104) *
                first_coupled_motion < 0.0f) {
            return;
        }
        fighters[0]->body_overlap_x_6a4 = -first_coupled_motion;
        fighters[1]->body_overlap_x_6a4 = -second_coupled_motion;
        return;
    }

    if (second_boundary == 1 && g_body_collision_edge_owner_a == 1) {
        fighters[0]->x_ec += second_box.right - first_box.left - 1.0;
        if (second_coupled_motion *
                    static_cast<signed char>(fighters[1]->facing_104) +
                first_coupled_motion *
                    static_cast<signed char>(fighters[0]->facing_104) >
            0.0f) {
            return;
        }
        if (static_cast<signed char>(fighters[0]->facing_104) *
                first_coupled_motion > 0.0f) {
            return;
        }
        fighters[0]->body_overlap_x_6a4 = -first_coupled_motion;
        fighters[1]->body_overlap_x_6a4 = -second_coupled_motion;
        return;
    }

    if (first_boundary == 1 && g_body_collision_edge_owner_a == 0) {
        fighters[1]->x_ec += first_box.right - second_box.left - 1.0;
        if (first_coupled_motion *
                    static_cast<signed char>(fighters[0]->facing_104) +
                second_coupled_motion *
                    static_cast<signed char>(fighters[1]->facing_104) >
            0.0f) {
            return;
        }
        if (static_cast<signed char>(fighters[1]->facing_104) *
                second_coupled_motion > 0.0f) {
            return;
        }
        fighters[0]->body_overlap_x_6a4 = -first_coupled_motion;
        fighters[1]->body_overlap_x_6a4 = -second_coupled_motion;
        return;
    }

    if (first_box.left + first_box.right <=
            second_box.right + second_box.left &&
        (first_box.left + first_box.right !=
             second_box.right + second_box.left ||
         first_box.bottom + first_box.top <=
             second_box.top + second_box.bottom)) {
        float separation = first_box.right - second_box.left - 1.0;
        if (separation < 0.0f) {
            separation = 0.0f;
        }
        if (static_cast<char>(
                fighters[0]->test_proposed_x_against_stage_height(
                    -separation * 0.5)) == 0) {
            fighters[0]->x_ec -= separation * 0.5;
        }
        if (static_cast<char>(
                fighters[1]->test_proposed_x_against_stage_height(
                    separation * 0.5)) == 0) {
            fighters[1]->x_ec += separation * 0.5;
        }

        if (second_motion *
                static_cast<signed char>(fighters[1]->facing_104) >
            first_motion *
                static_cast<signed char>(fighters[0]->facing_104)) {
            return;
        }
        first_coupled_motion =
            (second_coupled_motion *
                 static_cast<signed char>(fighters[1]->facing_104) +
             first_coupled_motion *
                 static_cast<signed char>(fighters[0]->facing_104)) * 0.5;
        fighters[0]->body_overlap_x_6a4 =
            static_cast<signed char>(fighters[0]->facing_104) *
                first_coupled_motion - first_motion;
        fighters[1]->body_overlap_x_6a4 =
            first_coupled_motion *
                static_cast<signed char>(fighters[1]->facing_104) -
            second_motion;
        return;
    }

    float separation = second_box.right - first_box.left - 1.0;
    if (separation < 0.0f) {
        separation = 0.0f;
    }
    const float half_separation = separation * 0.5;
    if (static_cast<char>(
            fighters[0]->test_proposed_x_against_stage_height(half_separation)) == 0) {
        fighters[0]->x_ec += half_separation;
    }
    if (static_cast<char>(
            fighters[1]->test_proposed_x_against_stage_height(-separation * 0.5)) == 0) {
        fighters[1]->x_ec -= half_separation;
    }

    if (static_cast<signed char>(fighters[1]->facing_104) * second_motion <
        static_cast<signed char>(fighters[0]->facing_104) * first_motion) {
        return;
    }
    first_motion =
        (second_coupled_motion *
             static_cast<signed char>(fighters[1]->facing_104) +
         first_coupled_motion *
             static_cast<signed char>(fighters[0]->facing_104)) * 0.5;
    fighters[0]->body_overlap_x_6a4 =
        static_cast<signed char>(fighters[0]->facing_104) * first_motion -
        fighters[0]->x_component_f4;
    fighters[1]->body_overlap_x_6a4 =
        first_motion * static_cast<signed char>(fighters[1]->facing_104) -
        fighters[1]->x_component_f4;
}

} // namespace th105
