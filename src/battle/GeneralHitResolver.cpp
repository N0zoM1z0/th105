#include "Collision.hpp"
#include "GameMode.hpp"

namespace th105 {
// This file remains an unselected 1.06a hypothesis; see the dated evidence note.
struct BattleInputGate;
extern BattleInputGate *g_battle_input_gate;

namespace {

typedef void (__thiscall *ContextDepletionCallback)(
    CollisionContext *context, Fighter *fighter);
typedef void (__thiscall *FighterActionCallback)(
    Fighter *fighter, int action);

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
        if ((candidate->frame_1a4->flags_50 & 0x20) != 0) {
            increment = static_cast<float>(frame->threshold_increment_26);
        } else {
            current_flags = fighter->frame_158->flags_4c;
            if ((current_flags & 0x80) != 0) {
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

    int selected_action = -1;
    signed char action_bias = frame->action_offset_48;
    if (fighter->value_4a0 >= 100) {
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
            *reinterpret_cast<int *>(reinterpret_cast<unsigned char *>(g_battle_input_gate) + 0x24) == 0 &&
            candidate->owner_16c->value_498 == 0) {
            boost_gate = true;
        }
        if ((candidate->frame_1a4->flags_50 & 0x400) != 0 && boost_gate) {
            boosted_path = true;
            ++action_bias;
            if (action_bias > 3) {
                action_bias = 3;
            }
        }

        if (fighter->value_174 <= 0 || fighter->value_4a2 >= 100) {
            unsigned short action = frame->action_code_36;
            selected_action = action == 0x46 ? 0x47 : action;
        } else if (static_cast<signed char>(is_y_at_or_below_stage_surface(fighter)) != 0 &&
                   (fighter->frame_158->flags_4c & 4) == 0) {
            unsigned short action = frame->alternate_action_code_38;
            if (action != 0) {
                if (boosted_path) {
                    if (action == 0x47) selected_action = 0x4a;
                    else if (action == 0x49) selected_action = 0x58;
                    else selected_action = action;
                } else selected_action = action;
            } else if ((fighter->frame_158->flags_4c & 1) != 0) {
                if ((candidate->frame_1a4->flags_50 & 1) != 0)
                    selected_action = static_cast<unsigned short>(action_bias + 0x38);
                else
                    selected_action = static_cast<unsigned short>(action_bias + 0x32);
            } else if ((fighter->frame_158->flags_4c & 2) != 0) {
                selected_action = static_cast<unsigned short>(action_bias + 0x3e);
            }
        } else {
            unsigned short action = frame->action_code_36;
            if (action != 0) {
                if (boosted_path) {
                    if (action == 0x47) selected_action = 0x4a;
                    else if (action == 0x49) selected_action = 0x58;
                    else selected_action = action;
                } else selected_action = action;
            } else selected_action = 0x46;
        }
    } else {
        candidate->result_180 = 7;
        fighter->value_4a2 += frame->result_accumulator_increment_28;
        candidate->owner_16c->value_49c = fighter->value_4a2;
        fighter->field_4a4 = 0x14;
    }

    if (static_cast<signed char>(
            is_state_13c_in_32_95(fighter)) == 0) {
        for (int i = 0; i <= action_bias && i < 3; ++i) {
            emit_effect_at_collision_center(0xc9, fighter->facing_104);
        }
        if (action_bias >= 2) {
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
        fighter->field_49e = static_cast<short>(
            ((frame->boosted_response_quantity_24 * 3) / 2) *
            candidate->owner_16c->scalar_494);
        hit_quantity = static_cast<short>(
            (static_cast<short>(candidate->calculate_descriptor_scaled_quantity_1c()) * 4) / 3);
        emit_effect_at_collision_center(0x36, candidate->facing_104);
    } else {
        fighter->response_18c = frame->response_3c;
        fighter->response_190 = frame->response_40;
        fighter->field_49e = static_cast<short>(
            frame->boosted_response_quantity_24 *
            candidate->owner_16c->scalar_494);
        hit_quantity = static_cast<short>(
            candidate->calculate_descriptor_scaled_quantity_1c());
    }

    // Native low-16-bit resource quantity is distinct from hit_quantity.
    short resource_amount = static_cast<short>(
        candidate->owner_16c->factor_4d0 *
            frame->owner_capped_counter_quantity_32);
    candidate->owner_16c->adjust_capped_counter_558(static_cast<unsigned short>(resource_amount));
    if (candidate->owner_16c->scale_4d8 > 0.0f) {
        deferred_7c[fighter->player_index_334] += static_cast<short>(
            static_cast<float>(static_cast<short>(resource_amount)) * candidate->owner_16c->scale_4d8);
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
        if (fighter->value_174 <= 0) {
            fighter->value_174 = 0;
            invoke_context_slot_2c(this, fighter);
            selected_action = frame->action_code_36 == 0x46 ? 0x47 :
                frame->action_code_36;
        }
    }

    if (candidate->result_180 != 7 || fighter->value_174 <= 0) {
        update_fighter_facing_from_other_x(fighter);
    }
    if (static_cast<short>(selected_action) >= 0) {
        invoke_fighter_slot_08(fighter, selected_action);
    }
    emit_effect_at_collision_center(
        frame->effect_46, candidate->facing_104);
    reset_collision_extents();
    dispatch_indexed_event(frame->indexed_event_44);
}

} // namespace th105
