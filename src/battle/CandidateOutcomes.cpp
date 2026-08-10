#include "Collision.hpp"

namespace th105 {

bool CollisionContext::try_candidate_flag_outcome(
    AttackCandidate *candidate,
    Fighter *fighter)
{
    const unsigned flags = candidate->frame_1a4->flags_50;
    if ((flags & 0x00400000) == 0) {
        return false;
    }
    if ((flags & 0x00800000) != 0) {
        return false;
    }
    if ((fighter->frame_158->flags_4c & 0x400) == 0 &&
        fighter->field_4ae == 0) {
        return false;
    }
    if ((flags & 0x01000000) != 0) {
        if (fighter->counter_482 < 4) {
            return false;
        }
        fighter->adjust_counter_482(4, 30);
    }
    candidate->result_180 = 6;
    candidate->result_slot_184 = candidate->source_1a0 - 1;
    ++fighter->field_4a6;
    emit_effect_at_collision_center(0x34, fighter->facing_104);
    reset_collision_extents();
    return true;
}

} // namespace th105
