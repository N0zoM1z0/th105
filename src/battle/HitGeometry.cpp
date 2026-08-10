#include "Collision.hpp"

namespace th105 {

void CollisionContext::accumulate_descriptor_extents(
    const CollisionAabb *first,
    const ShapeWords *descriptor,
    const CollisionAabb *second)
{
    int local[4];
    local[0] = first->left;
    local[2] = first->right;
    local[1] = descriptor->y0 + first->top;
    local[3] = descriptor->y1 + first->top;
    accumulate_collision_extents(local, &second->left);
}

void CollisionContext::accumulate_descriptor_pair_extents(
    const CollisionAabb *first,
    const ShapeWords *first_descriptor,
    const CollisionAabb *second,
    const ShapeWords *second_descriptor)
{
    int first_local[4];
    int second_local[4];
    first_local[0] = first->left;
    first_local[2] = first->right;
    first_local[1] = first_descriptor->y0 + first->top;
    first_local[3] = first_descriptor->y1 + first->top;
    second_local[0] = second->left;
    second_local[2] = second->right;
    second_local[1] = second_descriptor->y0 + second->top;
    second_local[3] = second_descriptor->y1 + second->top;
    accumulate_collision_extents(first_local, second_local);
}

int CollisionContext::test_descriptor_point_inside(
    const CollisionAabb *aabb,
    const ShapeWords *descriptor,
    int x,
    int y)
{
    const int q0 = descriptor->y0 * (aabb->top - y) - 1 +
        descriptor->x0 * (aabb->left - x);
    const int q1 = descriptor->y0 * (y - aabb->bottom) - 1 +
        descriptor->x0 * (x - aabb->right);
    const int q2 = (aabb->top - y) * descriptor->y1 - 1 +
        (aabb->left - x) * descriptor->x1;
    const int q3 = descriptor->y1 * (y - aabb->bottom) - 1 +
        descriptor->x1 * (x - aabb->right);
    return (q0 >> 31) & (q1 >> 31) & (q2 >> 31) & (q3 >> 31);
}

} // namespace th105
