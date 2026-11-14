#include "Collision.hpp"
#include <deque>
#include "EffectSprite.hpp"
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

static inline std::deque<FighterSequenceSlot> &sequence_queue(Fighter *fighter)
{
    return reinterpret_cast<std::deque<FighterSequenceSlot> &>(
        fighter->sequence_controller_55c);
}

void Fighter::advance_fighter_sequence_55c()
{
    if (sequence_queue(this).size() > 0) {
        sequence_queue(this).front();
        sequence_queue(this).pop_front();
        state_55a = static_cast<signed char>(sequence_queue(this).size());
        if (state_55a == 0) {
            return;
        }

        FighterSequenceController *controller = &sequence_controller_55c;
        int record_id = controller->entry_at_checked(0)->record_id_00;
        SpellDataOwner *lookup =
            reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0);
        if (lookup->find_local_then_common_spell_record(record_id)
                ->selector_1c == -1) {
            max_health_176 = lookup->find_local_then_common_spell_record(
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
        max_health_176 = record->value_1e.value;
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

extern unsigned g_spell_texture_load_state;
extern unsigned g_spell_texture_upload_state;

void Fighter::prepare_next_spell_sequence_entry()
{
    if (static_cast<signed char>(reinterpret_cast<std::deque<FighterSequenceSlot> *>(&sequence_controller_55c)->size()) >= state_55b ||
        reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0)->selection_ids_34.size() == 0)
        return;
    counter_558=0;
    FighterSequenceSlot sequence_record;
    SpellDataOwner *lookup=reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0);
    sequence_record.record_id_00=lookup->select_spell_record_id();
    SpellRecordView *record=lookup->find_local_then_common_spell_record(sequence_record.record_id_00);
    if (!record)return;
    sequence_record.field_02=record->value_1e.value;
    if(record->selector_1c==1)sequence_record.field_02=1;
    if(record->card_texture_handle_44)
        sequence_record.sprite_04.set_texture(
            record->card_texture_handle_44,0,0,
            g_spell_texture_load_state,g_spell_texture_upload_state);
    reinterpret_cast<std::deque<FighterSequenceSlot> *>(
        &sequence_controller_55c)->push_back(sequence_record);
    state_55a=static_cast<signed char>(reinterpret_cast<std::deque<FighterSequenceSlot> *>(&sequence_controller_55c)->size());
}

} // namespace th105
