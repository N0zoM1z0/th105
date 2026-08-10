#include "Collision.hpp"

namespace th105 {

void CollisionContext::reset_collision_extents()
{
    extent_1c = -10000;
    extent_20 = -10000;
    extent_24 = 10000;
    extent_28 = 10000;
}

void CollisionContext::accumulate_collision_extents(
    const int *first,
    const int *second)
{
    int first_x = first[0];
    int first_x2 = first[2];
    if (first_x < first_x2) {
        if (extent_1c < first_x) {
            extent_1c = first_x;
        }
        first_x = *(volatile const int *)(first + 2);
    } else {
        if (extent_1c < first_x2) {
            extent_1c = first_x2;
        }
        first_x = *(volatile const int *)first;
    }
    if (extent_24 > first_x) {
        extent_24 = first_x;
    }

    int second_x = second[0];
    int second_x2 = second[2];
    if (second_x < second_x2) {
        if (extent_1c < second_x) {
            extent_1c = second_x;
        }
        second_x = *(volatile const int *)(second + 2);
    } else {
        if (extent_1c < second_x2) {
            extent_1c = second_x2;
        }
        second_x = *(volatile const int *)second;
    }
    if (extent_24 > second_x) {
        extent_24 = second_x;
    }

    if (extent_20 < first[1]) {
        extent_20 = first[1];
    }
    if (extent_20 < second[1]) {
        extent_20 = second[1];
    }
    if (extent_28 > first[3]) {
        extent_28 = first[3];
    }
    if (extent_28 > second[3]) {
        extent_28 = second[3];
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

    int sign_bits = *(int *)&differences[0] & *(int *)&differences[2] &
                    *(int *)&differences[1] & *(int *)&differences[3];
    if (sign_bits & 0x80000000) {
        accumulate_float_collision_extents(first, second);
        return 1;
    }
    return 0;
}

void __stdcall transform_local_aabb_to_world(
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
