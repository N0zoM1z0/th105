#include "BattleController.hpp"

#include "Collision.hpp"

namespace th105 {

struct PostSequenceContextView {
    void update_after_sequence_consume_4712b0();
};

struct PhaseTallyView {
    void add_clamped_counts_4531a0(int first, int second, int third);
};

extern unsigned char g_round_counter;

void BattleController::publish_fighter_terminal_effect_470300(Fighter *fighter)
{
    const signed char one = 1;

    fighter->terminal_pending_4e9 = 2;
    if (fighter->state_72c == 2) {
        if (fighter->state_55a > one) {
            reinterpret_cast<CollisionContext *>(this)
                ->emit_effect_at_collision_center(64, fighter->facing_104);
            return;
        }

        g_round_counter += one;
        reinterpret_cast<CollisionContext *>(this)
            ->emit_effect_at_collision_center(66, fighter->facing_104);
        return;
    }

    reinterpret_cast<CollisionContext *>(this)
        ->emit_effect_at_collision_center(67, fighter->facing_104);
}

void BattleController::advance_round_resolution_470360()
{
    unsigned char advanced_terminal_delay = 0;

    if (fighter_0c->terminal_pending_4e9 != 0) {
        transition_flag_91 = 1;
        if (fighter_0c->terminal_delay_4e8 <= 0) {
            fighter_0c->terminal_finalize_4eb = 1;
            fighter_10->finalize_sequence_entry_45bb10(0);
            fighter_10->statistic_candidate_64c = -1;
            dispatch_round_phase_34(4);
            return;
        }
        --fighter_0c->terminal_delay_4e8;
        advanced_terminal_delay = 1;
    }

    if (fighter_10->terminal_pending_4e9 != 0) {
        if (fighter_10->post_advance_value_650 > 0) {
            if (fighter_10->statistic_enable_655 == 0 ||
                transition_flag_91 != 0) {
                fighter_10->statistic_enable_655 = 0;
                --tally_third_9c;
            }
            if (fighter_10->statistic_candidate_64c == 0) {
                --tally_second_98;
            }
        }
        transition_flag_91 = 0;

        if (fighter_10->consume_spell_sequence_entry() != 0) {
            post_sequence_context_8c->update_after_sequence_consume_4712b0();
            dispatch_round_phase_34(3);
            return;
        }

        if (fighter_0c->accumulated_hit_quantity_178 > 5000) {
            outcome_band_94 = -3;
        } else if (fighter_0c->accumulated_hit_quantity_178 > 2500) {
            outcome_band_94 = -2;
        } else if (fighter_0c->accumulated_hit_quantity_178 > 0) {
            outcome_band_94 = -1;
        }

        fighter_10->terminal_finalize_4eb = 1;
        if (g_battle_phase_block != 0) {
            reinterpret_cast<PhaseTallyView *>(
                reinterpret_cast<unsigned char *>(g_battle_phase_block) +
                0x3f8)
                ->add_clamped_counts_4531a0(
                    outcome_band_94, tally_second_98, tally_third_9c);
        }
        fighter_0c->terminal_pending_4e9 = 0;
        fighter_0c->terminal_finalize_4eb = 0;
        dispatch_round_phase_34(4);
        return;
    }

    if (advanced_terminal_delay != 0) {
        dispatch_round_phase_34(3);
    }
}

} // namespace th105
