#include "Collision.hpp"

namespace th105 {

void CollisionContext::reset_collision_extents()
{
    overlap_left = -10000;
    overlap_top = -10000;
    overlap_right = 10000;
    overlap_bottom = 10000;
}

void CollisionContext::accumulate_collision_extents(
    const CollisionAabb *first,
    const CollisionAabb *second)
{
    // X endpoints may arrive reversed; narrow the running intersection with
    // the lesser and greater endpoint of each box in turn.
    int first_x = first->left;
    int first_x2 = first->right;
    if (first_x < first_x2) {
        if (overlap_left < first_x) {
            overlap_left = first_x;
        }
        first_x = first->right;
    } else {
        if (overlap_left < first_x2) {
            overlap_left = first_x2;
        }
        first_x = first->left;
    }
    if (overlap_right > first_x) {
        overlap_right = first_x;
    }

    int second_x = second->left;
    int second_x2 = second->right;
    if (second_x < second_x2) {
        if (overlap_left < second_x) {
            overlap_left = second_x;
        }
        second_x = second->right;
    } else {
        if (overlap_left < second_x2) {
            overlap_left = second_x2;
        }
        second_x = second->left;
    }
    if (overlap_right > second_x) {
        overlap_right = second_x;
    }

    if (overlap_top < first->top) {
        overlap_top = first->top;
    }
    if (overlap_top < second->top) {
        overlap_top = second->top;
    }
    if (overlap_bottom > first->bottom) {
        overlap_bottom = first->bottom;
    }
    if (overlap_bottom > second->bottom) {
        overlap_bottom = second->bottom;
    }
}

int CollisionContext::test_and_accumulate_float_aabb_overlap(
    WorldAabb *first,
    WorldAabb *second)
{
    float differences[4];
    differences[0] = second->left - first->right;
    differences[2] = first->left - second->right;
    differences[1] = second->top - first->bottom;
    differences[3] = first->top - second->bottom;

    // The target tests sign bits after float subtraction, including signed
    // zero and NaN representations; this is not a generic <= overlap test.
    int sign_bits = *(int *)&differences[0] & *(int *)&differences[2] &
                    *(int *)&differences[1] & *(int *)&differences[3];
    if (sign_bits & 0x80000000) {
        accumulate_float_collision_extents(first, second);
        return 1;
    }
    return 0;
}

void CollisionContext::transform_local_aabb_to_world(
    const ActorPosition *actor,
    const LocalAabb *local,
    WorldAabb *world)
{
    if (actor->facing == 1) {
        world->left = static_cast<float>(local->left) + actor->x;
        world->right = static_cast<float>(local->right) + actor->x;
    } else {
        world->left = actor->x - static_cast<float>(local->right);
        world->right = actor->x - static_cast<float>(local->left);
    }
    world->top = static_cast<float>(local->top) - actor->y;
    world->bottom = static_cast<float>(local->bottom) - actor->y;
}

} // namespace th105
