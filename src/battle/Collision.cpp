#include "Collision.hpp"

namespace th105 {

void CollisionExtents::reset_collision_extents()
{
    extent_1c = -10000;
    extent_20 = -10000;
    extent_24 = 10000;
    extent_28 = 10000;
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
