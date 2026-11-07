#include "Collision.hpp"

namespace th105 {

void CollisionContext::accumulate_descriptor_extents(
    const CollisionAabb *first,
    const ShapeWords *descriptor,
    const CollisionAabb *second)
{
    CollisionAabb local;
    local.left = first->left;
    local.right = first->right;
    local.top = descriptor->y0 + first->top;
    local.bottom = descriptor->y1 + first->top;
    accumulate_collision_extents(&local, second);
}

void CollisionContext::accumulate_descriptor_pair_extents(
    const CollisionAabb *first,
    const ShapeWords *first_descriptor,
    const CollisionAabb *second,
    const ShapeWords *second_descriptor)
{
    CollisionAabb first_local;
    CollisionAabb second_local;
    first_local.left = first->left;
    first_local.right = first->right;
    first_local.top = first_descriptor->y0 + first->top;
    first_local.bottom = first_descriptor->y1 + first->top;
    second_local.left = second->left;
    second_local.right = second->right;
    second_local.top = second_descriptor->y0 + second->top;
    second_local.bottom = second_descriptor->y1 + second->top;
    accumulate_collision_extents(&first_local, &second_local);
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

int CollisionContext::test_aabb_against_descriptor_shape(
    const CollisionAabb *first,
    const ShapeWords *descriptor,
    const CollisionAabb *second)
{
    // The native broad phase ANDs four 32-bit wrapped endpoint differences.
    // Unsigned arithmetic makes that wrapping explicit in C++.
    unsigned overlap = static_cast<unsigned>(descriptor->y0) -
                       second->bottom + first->top;
    overlap &= static_cast<unsigned>(second->top) - descriptor->y1 - first->top;
    overlap &= static_cast<unsigned>(first->left) - second->right;
    overlap &= static_cast<unsigned>(second->left) - first->right;
    if ((overlap & 0x80000000u) == 0) {
        return 0;
    }

    if ((second->bottom - first->top) * descriptor->y1 +
            descriptor->x1 * (second->right - first->left) < 0) {
        return 0;
    }
    if ((second->top - first->top) * descriptor->y0 +
            descriptor->x0 * (second->right - first->left) < 0) {
        return 0;
    }
    if ((second->bottom - first->bottom) * descriptor->y0 +
            descriptor->x0 * (second->left - first->right) > 0) {
        return 0;
    }
    if ((second->top - first->bottom) * descriptor->y1 +
            descriptor->x1 * (second->left - first->right) > 0) {
        return 0;
    }

    accumulate_descriptor_extents(first, descriptor, second);
    return 1;
}

int CollisionContext::test_descriptor_shapes_overlap(
    const CollisionAabb *first,
    const ShapeWords *first_descriptor,
    const CollisionAabb *second,
    const ShapeWords *second_descriptor)
{
    int broad_phase = second_descriptor->y0 - first_descriptor->y1 -
        first->top + second->top;
    broad_phase &= second->left - first->right;
    broad_phase &= first_descriptor->y0 - second_descriptor->y1 -
        second->top + first->top;
    broad_phase &= first->left - second->right;
    if ((static_cast<unsigned>(broad_phase) & 0x80000000u) == 0) {
        return 0;
    }

    if (test_descriptor_point_inside(
            first, first_descriptor, second->left, second->top) ||
        test_descriptor_point_inside(
            first, first_descriptor, second->right, second->bottom) ||
        test_descriptor_point_inside(
            first, first_descriptor,
            second->left + second_descriptor->x0,
            second->top + second_descriptor->y0) ||
        test_descriptor_point_inside(
            first, first_descriptor,
            second->left + second_descriptor->x1,
            second->top + second_descriptor->y1) ||
        test_descriptor_point_inside(
            second, second_descriptor, first->left, first->top)) {
        accumulate_descriptor_pair_extents(
            first, first_descriptor, second, second_descriptor);
        return 1;
    }

    return 0;
}

} // namespace th105
