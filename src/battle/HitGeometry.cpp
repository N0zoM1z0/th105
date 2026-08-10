#include "Collision.hpp"

namespace th105 {

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
