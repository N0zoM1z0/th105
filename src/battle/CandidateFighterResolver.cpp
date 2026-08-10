#include "Collision.hpp"

namespace th105 {

void CollisionContext::resolve_attack_candidate_against_fighter(
    AttackCandidate *candidate,
    Fighter *fighter)
{
    if (candidate->source_168->state_4ea != 0) {
        return;
    }
    if (fighter->state_4ea == 2) {
        return;
    }
    if (static_cast<signed char>(
            is_positive_y_and_state_window(fighter)) != 0) {
        return;
    }
    if (fighter->value_4a2 >= 100) {
        return;
    }

    const unsigned flags = candidate->frame_1a4->flags_50;
    if ((flags & 0x00400000) != 0) {
        if ((flags & 0x00040000) == 0) {
            if (fighter->gate_4ac != 0 ||
                (fighter->frame_158->flags_4c & 0x4000) != 0) {
                return;
            }
        }
    } else if (fighter->gate_4a8 != 0 ||
               (fighter->frame_158->flags_4c & 0x2000) != 0) {
        return;
    }

    int overlap;
    if ((flags & 0x80) != 0) {
        if (fighter->gate_4aa != 0 ||
            (fighter->frame_158->flags_4c & 0x1800) != 0) {
            return;
        }
        overlap = test_group_a_against_primary_box(
            reinterpret_cast<CollisionObject *>(candidate),
            reinterpret_cast<CollisionObject *>(fighter));
    } else {
        overlap = test_group_a_against_group_b(
            reinterpret_cast<CollisionObject *>(candidate),
            reinterpret_cast<CollisionObject *>(fighter));
    }
    if (overlap == 0) {
        return;
    }

    fighter->unknown_490 = static_cast<unsigned char>(
        ~(candidate->frame_1a4->flags_50 >> 22) & 1);
    if (try_frame_flag_pair_outcome(candidate, fighter)) {
        return;
    }
    if (try_candidate_flag_outcome(candidate, fighter)) {
        return;
    }
    if (dispatch_outcome_path(candidate, fighter)) {
        return;
    }
    resolve_general_attack_hit(candidate, fighter);
}

} // namespace th105
