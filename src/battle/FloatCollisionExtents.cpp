#include "Collision.hpp"

namespace th105 {

void CollisionContext::accumulate_float_collision_extents(
    WorldAabb *first,
    WorldAabb *second)
{
    if (first->left < first->right) {
        if (overlap_left < first->left)
            overlap_left = static_cast<int>(first->left);
        if (overlap_right > first->right)
            overlap_right = static_cast<int>(first->right);
    } else {
        if (overlap_left < first->right)
            overlap_left = static_cast<int>(first->right);
        if (overlap_right > first->left)
            overlap_right = static_cast<int>(first->left);
    }

    if (second->left < second->right) {
        if (overlap_left < second->left)
            overlap_left = static_cast<int>(second->left);
        if (overlap_right > second->right)
            overlap_right = static_cast<int>(second->right);
    } else {
        if (overlap_left < second->right)
            overlap_left = static_cast<int>(second->right);
        if (overlap_right > second->left)
            overlap_right = static_cast<int>(second->left);
    }

    if (overlap_top < first->top)
        overlap_top = static_cast<int>(first->top);
    if (overlap_top < second->top)
        overlap_top = static_cast<int>(second->top);
    if (overlap_bottom > first->bottom)
        overlap_bottom = static_cast<int>(first->bottom);
    if (overlap_bottom > second->bottom)
        overlap_bottom = static_cast<int>(second->bottom);
}

} // namespace th105
