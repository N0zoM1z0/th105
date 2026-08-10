#include "Collision.hpp"
#include "GameMode.hpp"

namespace th105 {

namespace {

typedef void (__thiscall *ContextDepletionCallback)(
    CollisionContext *context, Fighter *fighter);
typedef void (__thiscall *FighterActionCallback)(
    Fighter *fighter, int action);

__forceinline bool has_candidate_flag_20(
    const AttackCandidate *candidate)
{
    AttackCandidateFrame *frame =
        *reinterpret_cast<AttackCandidateFrame * volatile const *>(
            &candidate->frame_1a4);
    return (static_cast<unsigned char>(frame->flags_50) & 0x20) != 0;
}

void invoke_context_slot_2c(
    CollisionContext *context,
    Fighter *fighter)
{
    ContextDepletionCallback callback =
        reinterpret_cast<ContextDepletionCallback>(
            (*reinterpret_cast<void ***>(context))[11]);
    callback(context, fighter);
}

void invoke_fighter_slot_08(Fighter *fighter, int action)
{
    FighterActionCallback callback =
        reinterpret_cast<FighterActionCallback>(
            (*reinterpret_cast<void ***>(fighter))[2]);
    callback(fighter, action);
}

} // namespace

void CollisionContext::resolve_general_attack_hit(
    AttackCandidate *candidate,
    Fighter *fighter)
{
    AttackCandidateFrame *frame = candidate->frame_1a4;
    bool boosted_path = false;

    if (static_cast<signed char>(
            is_state_13c_in_32_95(fighter)) == 0 &&
        fighter->field_4a4 == 0) {
        reset_hit_exchange_scratch(candidate->owner_16c, fighter);
    }

    if (fighter->threshold_scale_4c4 != 0.0f) {
        double increment;
        unsigned current_flags;
        if (has_candidate_flag_20(candidate)) {
            increment = static_cast<float>(frame->threshold_increment_26);
        } else {
            current_flags = fighter->frame_158->flags_4c;
            if (static_cast<signed char>(current_flags) < 0) {
                goto threshold_done;
            }
            if ((current_flags & 0x100) != 0) {
                increment = static_cast<float>(
                    frame->threshold_increment_26) *
                    fighter->threshold_scale_4c4 * 0.5;
                goto apply_threshold_increment;
            }
            increment = static_cast<float>(frame->threshold_increment_26);
        }
        increment *= fighter->threshold_scale_4c4;
apply_threshold_increment:
        fighter->value_4a0 += static_cast<short>(increment);
    }
threshold_done:

    signed char action_bias = frame->action_offset_48;
    int selected_action = -1;
    if (fighter->value_4a0 < 100) {
        candidate->result_180 = 7;
        fighter->value_4a2 += frame->result_accumulator_increment_28;
        candidate->owner_16c->value_49c = fighter->value_4a2;
        fighter->field_4a4 = 0x14;
    } else {
        candidate->result_180 = 1;
        fighter->value_4a0 = 0;
        fighter->value_4a2 += frame->result_accumulator_increment_28;
        fighter->field_4a4 = 0;
        candidate->owner_16c->value_49c = fighter->value_4a2;
        reinterpret_cast<FighterActionScratch *>(
            reinterpret_cast<unsigned char *>(fighter) + 4)
            ->reset_fighter_action_scratch();

        bool boost_gate =
            (fighter->frame_158->flags_4c & 0x40) != 0 ||
            (fighter->gate_4e6 != 0 &&
             candidate->owner_16c->value_498 == 0);
        if (get_game_mode() == GAME_MODE_PRACTICE &&
            *reinterpret_cast<int *>(
                *reinterpret_cast<int *>(0x006e4e28) + 0x24) == 0 &&
            candidate->owner_16c->value_498 == 0) {
            boost_gate = true;
        }
        if ((frame->flags_50 & 0x400) != 0 && boost_gate) {
            boosted_path = true;
            ++action_bias;
            if (action_bias > 3) {
                action_bias = 3;
            }
        }

        if (fighter->value_174 < 1 || fighter->value_4a2 >= 100) {
            selected_action = frame->action_code_36 == 0x46 ? 0x47 :
                frame->action_code_36;
        } else if (is_y_at_or_below_stage_surface(fighter) == 0 ||
                   (fighter->frame_158->flags_4c & 4) != 0) {
            selected_action = frame->action_code_36;
            if (selected_action == 0) {
                selected_action = 0x46;
            } else if (boosted_path && selected_action == 0x47) {
                selected_action = 0x4a;
            } else if (boosted_path && selected_action == 0x49) {
                selected_action = 0x58;
            }
        } else {
            selected_action = frame->alternate_action_code_38;
            if (selected_action != 0) {
                if (boosted_path && selected_action == 0x47) {
                    selected_action = 0x4a;
                } else if (boosted_path && selected_action == 0x49) {
                    selected_action = 0x58;
                }
            } else if ((fighter->frame_158->flags_4c & 1) != 0) {
                selected_action = action_bias +
                    ((frame->flags_50 & 1) != 0 ? 0x38 : 0x32);
            } else if ((fighter->frame_158->flags_4c & 2) != 0) {
                selected_action = action_bias + 0x3e;
            }
        }
    }

    if (static_cast<signed char>(
            is_state_13c_in_32_95(fighter)) == 0) {
        for (int i = 0; i <= action_bias && i < 3; ++i) {
            emit_effect_at_collision_center(0xc9, fighter->facing_104);
        }
        if (action_bias > 1) {
            emit_effect_at_collision_center(0xc9, fighter->facing_104);
        }
    }

    candidate->result_slot_184 = candidate->source_1a0 - 1;
    candidate->result_186 = frame->candidate_output_2a;
    fighter->result_186 = frame->fighter_output_2c;

    short hit_quantity;
    if (boosted_path) {
        candidate->owner_16c->flag_491 |= 0x20;
        fighter->response_18c = frame->response_3c * 1.5;
        fighter->response_190 = frame->response_40 * 1.5;
        fighter->field_49e = static_cast<unsigned short>(
            ((frame->boosted_response_quantity_24 * 3) / 2) *
            candidate->owner_16c->scalar_494);
        hit_quantity = static_cast<short>(
            (candidate->calculate_descriptor_scaled_quantity_1c() * 4) / 3);
        emit_effect_at_collision_center(0x36, candidate->facing_104);
    } else {
        fighter->response_18c = frame->response_3c;
        fighter->response_190 = frame->response_40;
        fighter->field_49e = static_cast<unsigned short>(
            frame->boosted_response_quantity_24 *
            candidate->owner_16c->scalar_494);
        hit_quantity = static_cast<short>(
            candidate->calculate_descriptor_scaled_quantity_1c());
    }

    candidate->owner_16c->adjust_capped_counter_558(
        static_cast<short>(
            frame->owner_capped_counter_quantity_32 *
            candidate->owner_16c->factor_4d0));
    if (candidate->owner_16c->scale_4d8 > 0.0f) {
        deferred_7c[fighter->player_index_334] += static_cast<short>(
            hit_quantity * candidate->owner_16c->scale_4d8);
    } else {
        fighter->adjust_capped_counter_558(hit_quantity / 20);
    }

    ++candidate->owner_16c->value_498;
    candidate->owner_16c->scalar_494 *=
        static_cast<float>(frame->owner_multiplier_per_1000_1e) / 1000.0;
    candidate->owner_16c->flag_491 |= frame->owner_flag_bits_49;
    candidate->owner_16c->value_49a += hit_quantity;
    if (candidate->owner_16c->factor_4d4 > 0.0f) {
        deferred_74[candidate->owner_16c->player_index_334] +=
            static_cast<short>(
                hit_quantity * candidate->owner_16c->factor_4d4);
    }

    fighter->accumulated_hit_quantity_178 += hit_quantity;
    if (fighter->state_4ea == 0) {
        fighter->value_174 -= hit_quantity;
        if (fighter->value_174 < 1) {
            fighter->value_174 = 0;
            invoke_context_slot_2c(this, fighter);
            selected_action = frame->action_code_36 == 0x46 ? 0x47 :
                frame->action_code_36;
        }
    }

    if (candidate->result_180 != 7 || fighter->value_174 < 1) {
        update_fighter_facing_from_other_x(fighter);
    }
    if (selected_action >= 0) {
        invoke_fighter_slot_08(fighter, selected_action);
    }
    emit_effect_at_collision_center(
        frame->effect_46, candidate->facing_104);
    reset_collision_extents();
    dispatch_indexed_event(frame->indexed_event_44);
}

} // namespace th105
