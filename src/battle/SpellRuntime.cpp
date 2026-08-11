#include "Collision.hpp"
#include "SpellRuntime.hpp"

#include "config/ScoreData.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

bool Fighter::is_front_sequence_entry_ready_55a(signed char index)
{
    if (state_55a <= index) {
        return false;
    }

    int required =
        sequence_controller_55c.entry_at_checked(index)->field_02 -
        (state_4b8 == 2);
    required = required < 1
        ? 1
        : sequence_controller_55c.entry_at_checked(index)->field_02 -
              (state_4b8 == 2);
    return state_55a >= required;
}

void Fighter::advance_fighter_sequence_55c()
{
    if (sequence_controller_55c.live_count_10 > 0) {
        FighterSequenceController *controller = &sequence_controller_55c;
        const unsigned head = controller->head_0c;
        if (head > head + controller->live_count_10) {
            _invalid_parameter_noinfo();
        }
        if (head >= controller->live_count_10 + controller->head_0c) {
            _invalid_parameter_noinfo();
        }

        if (controller->live_count_10 != 0) {
            SpellSpriteWork *sprite =
                &controller->slots_04[controller->head_0c]->sprite_04;
            sprite->vtable_00 = reinterpret_cast<void *>(0x006AC624);
            ++controller->head_0c;
            if (controller->slot_capacity_08 <= controller->head_0c) {
                controller->head_0c = 0;
            }
            if (--controller->live_count_10 == 0) {
                controller->head_0c = 0;
            }
        }

        int live_count = controller->live_count_10;
        state_55a = static_cast<signed char>(live_count);
        if (state_55a == 0) {
            return;
        }

        int record_id = controller->entry_at_checked(0)->record_id_00;
        SpellDataOwner *lookup =
            reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0);
        if (lookup->find_local_then_common_spell_record(record_id)
                ->selector_1c == -1) {
            maximum_176 = lookup->find_local_then_common_spell_record(
                static_cast<short>(controller->entry_at_checked(0)
                    ->record_id_00))->value_1e.value;
        }
    }
}

unsigned char Fighter::consume_spell_sequence_entry()
{
    if (state_72c != 2) {
        return 0;
    }
    if (state_55a <= 0) {
        return 0;
    }

    reinterpret_cast<PlayerIndexedCallbackView *>(
            reinterpret_cast<unsigned char *>(g_info_manager) +
            static_cast<int>(player_index_334) * 0x154 + 0x1d4)
        ->invoke_indexed_record(
            static_cast<short>(
                sequence_controller_55c.entry_at_checked(0)->record_id_00),
            0);

    if (statistic_enable_655 != 0 &&
        sequence_controller_55c.entry_at_checked(0)->record_id_00 < 200) {
        get_score_data()->update_observed_record_statistics(
            other_fighter_170->record_key_330,
            record_key_330,
            static_cast<short>(
                sequence_controller_55c.entry_at_checked(0)->record_id_00),
            statistic_candidate_64c);
    }

    advance_fighter_sequence_55c();
    if (state_55a > 0) {
        SpellRecordView *record =
            reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0)
                ->find_local_then_common_spell_record(static_cast<short>(
                    sequence_controller_55c.entry_at_checked(0)->record_id_00));
        maximum_176 = record->value_1e.value;
        if (sequence_controller_55c.entry_at_checked(0)->record_id_00 < 200) {
            post_advance_value_650 = static_cast<int>(
                reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0)
                    ->find_local_then_common_spell_record(static_cast<short>(
                        sequence_controller_55c.entry_at_checked(0)->record_id_00))
                    ->value_3c.value);
        } else {
            post_advance_value_650 = -1;
        }
        statistic_enable_655 = 0;
        statistic_candidate_64c = -1;
        return 1;
    }

    post_advance_value_650 = -1;
    statistic_enable_655 = 0;
    statistic_candidate_64c = -1;
    return 0;
}

void Fighter::prepare_next_spell_sequence_entry()
{
    const signed char pending_state = static_cast<signed char>(
        sequence_controller_55c.live_count_10);
    if (pending_state >= state_55b || spell_nonzero_gate_534 == 0) {
        return;
    }

    counter_558 = 0;
    FighterSequenceSlot sequence_record;
    sequence_record.sprite_04.vtable_00 = reinterpret_cast<void *>(0x006ac668);
    *reinterpret_cast<int *>(sequence_record.sprite_04.unknown_04) = 0;

    SpellDataOwner *lookup =
        reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0);
    short record_id = lookup->select_spell_record_id();
    SpellRecordView *record =
        lookup->find_local_then_common_spell_record(record_id);
    if (record == 0) {
        return;
    }

    sequence_record.record_id_00 = record_id;
    sequence_record.field_02 =
        record->selector_1c == 1 ? 1 : record->value_1e;
    if (record->optional_resource_44 != 0) {
        sequence_record.sprite_04.load_optional_spell_resource(
            record->optional_resource_44,
            0,
            0,
            reinterpret_cast<void *>(0x006e4c64),
            reinterpret_cast<void *>(0x006e4c60));
    }
    sequence_controller_55c.enqueue_record(&sequence_record);
    state_55a = pending_state;
}

} // namespace th105
