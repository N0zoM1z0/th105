#include "Collision.hpp"

namespace th105 {

namespace {

struct FighterVirtualView {
    virtual void unknown_00();
    virtual void unknown_04();
    virtual void set_action(short action);
};

void set_fighter_action(Fighter *fighter, short action)
{
    reinterpret_cast<FighterVirtualView *>(fighter)->set_action(action);
}

__forceinline void reset_fighter_action_scratch_after_outcome(Fighter *fighter)
{
    reinterpret_cast<FighterActionScratch *>(
        reinterpret_cast<unsigned char *>(fighter) + 4)
        ->reset_fighter_action_scratch();
}

} // namespace

bool CollisionContext::try_outcome_path_a(
    AttackCandidate *candidate,
    Fighter *fighter)
{
    AttackCandidateFrame *frame = candidate->frame_1a4;
    if (is_state_13c_in_32_95(fighter) == 0 && fighter->field_4a4 == 0) {
        reset_hit_exchange_scratch(candidate->owner_16c, fighter);
    }

    if (fighter->state_4ea == 0) {
        const unsigned short quantity = static_cast<unsigned short>(
            candidate->calculate_descriptor_scaled_quantity_20());
        fighter->value_174 -= quantity;
        if (fighter->value_174 < 1) {
            fighter->value_174 = 1;
        }
        if (candidate->owner_16c->factor_4d4 > 0.0f) {
            deferred_74[candidate->owner_16c->player_index_334] +=
                static_cast<short>(
                    static_cast<short>(quantity) *
                    candidate->owner_16c->factor_4d4);
        }
    }

    if (frame->amount_22 != 0) {
        const short before = fighter->counter_482;
        if ((frame->flags_50 & 0x00400000) != 0) {
            fighter->counter_482 -= frame->amount_22;
            fighter->floor_486 = 0x3c;
        } else if (fighter->select_outcome_path_from_frame_flags(
                       frame->flags_50) == 5) {
            fighter->counter_482 -=
                static_cast<short>(frame->amount_22) / 2;
            fighter->floor_486 = 0x3c;
        }
        if (fighter->counter_482 < 1 && fighter->counter_482 < before) {
            apply_terminal_outcome(candidate, fighter);
            return true;
        }
    }

    candidate->result_180 = 2;
    candidate->result_slot_184 = candidate->source_1a0 - 1;
    candidate->result_186 = frame->result_2e;
    fighter->result_186 = frame->result_30;
    fighter->response_18c = frame->response_3c;
    fighter->response_190 = frame->response_40;
    candidate->owner_16c->adjust_capped_counter_558(static_cast<short>(
        frame->amount_34 * candidate->owner_16c->factor_4d0));
    if (candidate->owner_16c->scale_4d8 > 0.0f) {
        deferred_7c[fighter->player_index_334] += static_cast<short>(
            (static_cast<short>(frame->amount_34) / 2) *
            candidate->owner_16c->scale_4d8);
    }
    update_fighter_facing_from_other_x(fighter);
    dispatch_indexed_event(0x14);
    emit_effect_at_collision_center(0x32, fighter->facing_104);
    reset_collision_extents();
    return false;
}

bool CollisionContext::try_outcome_path_b(
    AttackCandidate *candidate,
    Fighter *fighter)
{
    AttackCandidateFrame *frame = candidate->frame_1a4;
    if (is_state_13c_in_32_95(fighter) == 0 && fighter->field_4a4 == 0) {
        reset_hit_exchange_scratch(candidate->owner_16c, fighter);
    }

    if (fighter->state_4ea == 0) {
        const unsigned short quantity = static_cast<unsigned short>(
            candidate->calculate_descriptor_scaled_quantity_20());
        fighter->value_174 -= quantity;
        if (fighter->value_174 < 1) {
            fighter->value_174 = 1;
        }
        if (candidate->owner_16c->factor_4d4 > 0.0f) {
            deferred_74[candidate->owner_16c->player_index_334] +=
                static_cast<short>(
                    static_cast<short>(quantity) *
                    candidate->owner_16c->factor_4d4);
        }
    }

    if ((frame->flags_50 & 0x00080000) != 0 ||
        candidate->source_168->gate_4e4 != 0) {
        apply_terminal_outcome(candidate, fighter);
        return true;
    }
    if (frame->amount_22 != 0) {
        const short before = fighter->counter_482;
        unsigned short amount =
            static_cast<unsigned short>(frame->amount_22);
        if ((frame->flags_50 & 0x00400000) != 0) {
            amount *= 2;
        }
        fighter->counter_482 -= amount;
        fighter->floor_486 = 0x3c;
        if (fighter->counter_482 < 1 && fighter->counter_482 < before) {
            apply_terminal_outcome(candidate, fighter);
            return true;
        }
    }

    candidate->result_180 = 2;
    candidate->result_slot_184 = candidate->source_1a0 - 1;
    candidate->result_186 = frame->result_2e;
    fighter->result_186 = frame->result_30;
    fighter->response_18c = frame->response_3c;
    fighter->response_190 = frame->response_40;
    candidate->owner_16c->adjust_capped_counter_558(static_cast<short>(
        frame->amount_34 * candidate->owner_16c->factor_4d0));
    if (candidate->owner_16c->scale_4d8 > 0.0f) {
        deferred_7c[fighter->player_index_334] += static_cast<short>(
            (static_cast<short>(frame->amount_34) / 2) *
            candidate->owner_16c->scale_4d8);
    }
    update_fighter_facing_from_other_x(fighter);
    dispatch_indexed_event(0x15);
    emit_effect_at_collision_center(0x33, fighter->facing_104);
    reset_collision_extents();
    return false;
}

bool CollisionContext::dispatch_outcome_path(
    AttackCandidate *candidate,
    Fighter *fighter)
{
    switch (fighter->select_outcome_path_from_frame_flags(
        candidate->frame_1a4->flags_50)) {
    case 0:
        return false;
    case 1:
        set_fighter_action(
            fighter,
            try_outcome_path_a(candidate, fighter) ? 0x8f :
                static_cast<short>(
                    candidate->frame_1a4->action_offset_48 + 0x96));
        reset_fighter_action_scratch_after_outcome(fighter);
        return true;
    case 2:
        set_fighter_action(
            fighter,
            try_outcome_path_b(candidate, fighter) ? 0x8f :
                static_cast<short>(
                    candidate->frame_1a4->action_offset_48 + 0x9f));
        reset_fighter_action_scratch_after_outcome(fighter);
        return true;
    case 3:
        set_fighter_action(
            fighter,
            try_outcome_path_a(candidate, fighter) ? 0x8f :
                static_cast<short>(
                    candidate->frame_1a4->action_offset_48 + 0x9a));
        reset_fighter_action_scratch_after_outcome(fighter);
        return true;
    case 4:
        set_fighter_action(
            fighter,
            try_outcome_path_b(candidate, fighter) ? 0x8f :
                static_cast<short>(
                    candidate->frame_1a4->action_offset_48 + 0xa3));
        reset_fighter_action_scratch_after_outcome(fighter);
        return true;
    case 5:
        set_fighter_action(
            fighter,
            try_outcome_path_a(candidate, fighter) ? 0x91 : 0x9e);
        reset_fighter_action_scratch_after_outcome(fighter);
        return true;
    case 6:
        if (!try_outcome_path_a(candidate, fighter)) {
            return true;
        }
        set_fighter_action(
            fighter,
            is_y_at_or_below_stage_surface(fighter) != 0 ? 0x8f : 0x91);
        return true;
    default:
        reset_fighter_action_scratch_after_outcome(fighter);
        return true;
    }
}

} // namespace th105
