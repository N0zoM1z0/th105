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
    const int *first,
    const int *second)
{
    // X endpoints may arrive reversed; narrow the running intersection with
    // the lesser and greater endpoint of each box in turn.
    int first_x = first[0];
    int first_x2 = first[2];
    if (first_x < first_x2) {
        if (overlap_left < first_x) {
            overlap_left = first_x;
        }
        first_x = first[2];
    } else {
        if (overlap_left < first_x2) {
            overlap_left = first_x2;
        }
        first_x = first[0];
    }
    if (overlap_right > first_x) {
        overlap_right = first_x;
    }

    int second_x = second[0];
    int second_x2 = second[2];
    if (second_x < second_x2) {
        if (overlap_left < second_x) {
            overlap_left = second_x;
        }
        second_x = second[2];
    } else {
        if (overlap_left < second_x2) {
            overlap_left = second_x2;
        }
        second_x = second[0];
    }
    if (overlap_right > second_x) {
        overlap_right = second_x;
    }

    if (overlap_top < first[1]) {
        overlap_top = first[1];
    }
    if (overlap_top < second[1]) {
        overlap_top = second[1];
    }
    if (overlap_bottom > first[3]) {
        overlap_bottom = first[3];
    }
    if (overlap_bottom > second[3]) {
        overlap_bottom = second[3];
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
