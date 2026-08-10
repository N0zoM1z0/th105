#include "Collision.hpp"

namespace th105 {

void CollisionContext::apply_terminal_outcome(
    AttackCandidate *candidate,
    Fighter *fighter)
{
    AttackCandidateFrame *frame = candidate->frame_1a4;
    fighter->consume_counter_484_steps(1);
    reset_hit_exchange_scratch(candidate->owner_16c, fighter);

    candidate->result_180 = 2;
    candidate->result_slot_184 = candidate->source_1a0 - 1;
    candidate->result_186 = frame->result_2e;
    candidate->owner_16c->flag_491 |= 4;

    fighter->result_186 = frame->result_30;
    fighter->response_18c = frame->response_3c;
    fighter->response_190 = frame->response_40;
    fighter->field_49e = 0x4000;

    candidate->owner_16c->adjust_capped_counter_558(frame->amount_34);

    if (candidate->owner_16c->scale_4d8 > 0.0f) {
        deferred_7c[fighter->player_index_334] +=
            static_cast<short>(
                (static_cast<short>(frame->amount_34) / 2) *
                candidate->owner_16c->scale_4d8);
    }

    update_fighter_facing_from_other_x(fighter);
    dispatch_indexed_event(0x14);
    emit_effect_at_collision_center(0x35, fighter->facing_104);
    reset_collision_extents();
}

} // namespace th105
