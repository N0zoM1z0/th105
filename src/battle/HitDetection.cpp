#include "Collision.hpp"

namespace th105 {

bool CollisionContext::try_frame_flag_pair_outcome(
    AttackCandidate *candidate,
    Fighter *fighter)
{
    const unsigned candidate_flags = candidate->frame_1a4->flags_50;

    if ((candidate_flags & 0x2000) &&
        (fighter->frame_158->flags_4c & 0x8000)) {
        goto matched;
    }
    if ((candidate_flags & 0x4000) &&
        (fighter->frame_158->flags_4c & 0x10000)) {
        goto matched;
    }
    if ((candidate_flags & 0x8000) &&
        (fighter->frame_158->flags_4c & 0x20000)) {
        goto matched;
    }
    if ((candidate_flags & 0x10000) &&
        (fighter->frame_158->flags_4c & 0x40000)) {
        goto matched;
    }
    return false;

matched:
    candidate->result_180 = 3;
    fighter->result_180 = 3;
    reset_collision_extents();
    return true;
}

} // namespace th105
