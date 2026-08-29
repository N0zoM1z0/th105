#include "Collision.hpp"

namespace th105 {

void CollisionContext::accumulate_float_collision_extents(
    WorldAabb *first,
    WorldAabb *second)
{
    if (first->left < first->right) {
        if (extent_1c < first->left)
            extent_1c = static_cast<int>(first->left);
        if (extent_24 > first->right)
            extent_24 = static_cast<int>(first->right);
    } else {
        if (extent_1c < first->right)
            extent_1c = static_cast<int>(first->right);
        if (extent_24 > first->left)
            extent_24 = static_cast<int>(first->left);
    }

    if (second->left < second->right) {
        if (extent_1c < second->left)
            extent_1c = static_cast<int>(second->left);
        if (extent_24 > second->right)
            extent_24 = static_cast<int>(second->right);
    } else {
        if (extent_1c < second->right)
            extent_1c = static_cast<int>(second->right);
        if (extent_24 > second->left)
            extent_24 = static_cast<int>(second->left);
    }

    if (extent_20 < first->top)
        extent_20 = static_cast<int>(first->top);
    if (extent_20 < second->top)
        extent_20 = static_cast<int>(second->top);
    if (extent_28 > first->bottom)
        extent_28 = static_cast<int>(first->bottom);
    if (extent_28 > second->bottom)
        extent_28 = static_cast<int>(second->bottom);
}

} // namespace th105
