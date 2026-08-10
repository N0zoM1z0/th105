#include "Collision.hpp"

namespace th105 {

bool CollisionContext::try_group_b_pair_response(
    CollisionObject *source,
    CollisionObject *other)
{
    if ((source->frame_1a4->flags_4c & 0x80000) == 0) {
        return false;
    }
    if ((other->frame_158->flags_50 & 0x20000) != 0) {
        return false;
    }
    if (other->gate_189 != 0) {
        return false;
    }
    if (!test_group_b_against_group_b(source, other)) {
        return false;
    }

    other->facing_104 = -other->facing_104;
    other->owner_16c = source->owner_16c;
    other->owner_170 = source->owner_170;
    ++source->counter_188;
    ++other->counter_188;
    reset_collision_extents();
    return true;
}

} // namespace th105
