#include "Collision.hpp"

namespace th105 {

int g_fighter_state_4b8_default;

struct FighterEmbeddedState3d0 {
    void step();
};

struct BattleSceneRendererVtable {
    void *unused_00;
    void *unused_04;
    void *unused_08;
    void *unused_0c;
    void *unused_10;
    void *unused_14;
    void (__thiscall *notify_counter_threshold)(
        void *renderer, int mode, int player_index, int counter_steps);
};

struct BattleSceneRendererView {
    BattleSceneRendererVtable *vtable_00;
};

struct FighterIndexedEventDispatchView {
    void dispatch_action_indexed_event(unsigned event_index);
};

namespace {

short &fighter_short(Fighter *fighter, unsigned offset)
{
    return *reinterpret_cast<short *>(
        reinterpret_cast<unsigned char *>(fighter) + offset);
}

} // namespace

void __fastcall process_fighter_transient_status(Fighter *fighter)
{
    unsigned char *raw = reinterpret_cast<unsigned char *>(fighter);
    unsigned short &pending_48a =
        *reinterpret_cast<unsigned short *>(raw + 0x48a);

    if (fighter->gate_48c != 0) {
        --fighter->gate_48c;
    }
    if (pending_48a != 0) {
        fighter->gate_48c = pending_48a;
        pending_48a = 0;
    }

    fighter->peer_component_6ac = 0.0f;
    fighter->x_scale_4dc = 1.0f;
    fighter->y_scale_4e0 = 1.0f;

    if (fighter->value_174 < 0) {
        fighter->value_174 = 0;
    }
    if (fighter->value_47c < 0) {
        fighter->value_47c = 0;
    }
    if (fighter->value_174 > fighter->maximum_176) {
        fighter->value_174 = fighter->maximum_176;
    }
    if (!is_state_13c_in_32_95(fighter)) {
        fighter->value_47c = fighter->value_174;
    }

    reinterpret_cast<FighterEmbeddedState3d0 *>(raw + 0x3d0)->step();

    int &countdown_670 = *reinterpret_cast<int *>(raw + 0x670);
    if (countdown_670 > 0) {
        --countdown_670;
    }

    unsigned short const gate_4b2 =
        *reinterpret_cast<unsigned short *>(raw + 0x4b2);
    if (gate_4b2 != 0) {
        fighter->state_4b8 = 16;
    } else {
        fighter->state_4b8 = g_fighter_state_4b8_default;
    }

    signed char *entry = fighter->scalar_modifier_table_604;
    if (fighter->unknown_4e5 != 0) {
        int remaining = 32;
        do {
            *entry = entry[32] < 0 ? 0 : 4;
            ++entry;
        } while (--remaining != 0);
    } else {
        int remaining = 32;
        do {
            unsigned int const value =
                static_cast<unsigned char>(entry[32]);
            *entry++ = static_cast<signed char>(
                static_cast<signed char>(value) < 0 ? 0 : value);
        } while (--remaining != 0);
    }
}

void __fastcall update_fighter_counter_thresholds(Fighter *fighter)
{
    short const counter = fighter->unknown_484;
    if (counter < 1000) {
        short const accumulated = fighter_short(fighter, 0x488);
        if (accumulated < 4800) {
            if (fighter->state_4b8 == 8) {
                fighter_short(fighter, 0x488) = accumulated + 50;
            } else {
                if (counter <= 800) {
                    fighter_short(fighter, 0x488) = accumulated + 5;
                }
                if (counter <= 600) {
                    fighter_short(fighter, 0x488) += 2;
                }
                if (counter <= 400) {
                    fighter_short(fighter, 0x488) += 3;
                }
                if (counter <= 200) {
                    fighter_short(fighter, 0x488) += 8;
                }
                if (counter <= 0) {
                    fighter_short(fighter, 0x488) += 10;
                }
            }

            if (fighter_short(fighter, 0x488) >= 4800) {
                BattleSceneRendererView *renderer =
                    reinterpret_cast<BattleSceneRendererView *>(g_info_manager);
                renderer->vtable_00->notify_counter_threshold(
                    renderer,
                    2,
                    fighter->player_index_334,
                    counter / 200);
                fighter->unknown_484 += 200;
                fighter_short(fighter, 0x488) = 0;
            }
        }
    }

    if (fighter->floor_486 != 0) {
        --fighter->floor_486;
        return;
    }

    if (fighter->state_4b8 == 4) {
        fighter->counter_482 += 12;
    } else {
        fighter->counter_482 += 6;
    }
    if (fighter->unknown_484 < fighter->counter_482) {
        fighter->counter_482 = fighter->unknown_484;
    }
}

void __fastcall decrement_fighter_timers_and_cleanup(void *raw_fighter)
{
    Fighter *fighter = static_cast<Fighter *>(raw_fighter);
    if (fighter->other_fighter_170->gate_48c != 0) {
        return;
    }
    if (fighter->result_186 != 0) {
        --fighter->result_186;
        return;
    }

    short const countdown_6a0 = fighter_short(fighter, 0x6a0);
    if (countdown_6a0 > 0) {
        fighter_short(fighter, 0x6a0) = countdown_6a0 - 1;
    }
    if (fighter->value_4a0 != 0) {
        --fighter->value_4a0;
    }

    if (fighter->value_4a2 != 0) {
        if (fighter->state_13c >= 197 && fighter->state_13c <= 199) {
            short *raw = reinterpret_cast<short *>(fighter);
            raw[594] = 0;
            raw[593] = 0;
        } else if (fighter->field_4a4 == 0 &&
                   !is_state_13c_in_32_95(fighter)) {
            short *raw = reinterpret_cast<short *>(fighter);
            raw[594] = 0;
            raw[593] = 0;
        }
    }
    if (fighter->field_4a4 != 0) {
        if (is_state_13c_in_32_95(fighter)) {
            fighter->field_4a4 = 0;
        } else {
            --fighter->field_4a4;
        }
    }

    if (fighter->gate_4a8 != 0) {
        --fighter->gate_4a8;
    }
    if (fighter->gate_4aa != 0) {
        --fighter->gate_4aa;
    }
    if ((fighter->frame_158->flags_4c & 0x1000) != 0) {
        fighter->gate_4aa = 10;
    }
    if (fighter->gate_4ac != 0) {
        --fighter->gate_4ac;
    }
    if (fighter->blocker_48e != 0) {
        --fighter->blocker_48e;
    }
    if (fighter->field_4ae != 0) {
        --fighter->field_4ae;
    }
    if (fighter->statistic_candidate_64c > 0) {
        --fighter->statistic_candidate_64c;
    }

    short &gate_4b0 = fighter_short(fighter, 0x4b0);
    short &gate_4b2 = fighter_short(fighter, 0x4b2);
    if (gate_4b0 > 0) {
        --gate_4b0;
    }
    if (gate_4b2 > 0) {
        --gate_4b2;
    }

    signed char threshold_state = 5;
    if (fighter->counter_558 >= 500 &&
        fighter->state_55a < threshold_state &&
        fighter->state_72c != 2) {
        fighter->prepare_next_spell_sequence_entry();
        reinterpret_cast<FighterIndexedEventDispatchView *>(fighter)
            ->dispatch_action_indexed_event(0x24);
        fighter->counter_558 = 0;
        update_fighter_counter_thresholds(fighter);
        return;
    }
    if (fighter->state_55a >= threshold_state) {
        fighter->counter_558 = 0;
    }

    update_fighter_counter_thresholds(fighter);
}

} // namespace th105
