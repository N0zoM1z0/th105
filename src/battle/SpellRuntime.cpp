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
            reinterpret_cast<CSprite *>(
                &controller->slots_04[controller->head_0c]->sprite_04)
                ->~CSprite();
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

struct SequencePrepareSprite94 : CSpriteBase {
    float pivot_x, pivot_y, scale_x, scale_y, angle;
    void set_texture(unsigned handle,int x,int y,unsigned width,unsigned height);
};
struct SequencePrepareRecord98 {
    short record_id;
    unsigned short value;
    SequencePrepareSprite94 sprite;
};
typedef char prepare_record_size[sizeof(SequencePrepareRecord98)==0x98?1:-1];
extern unsigned g_spell_texture_load_state;
extern unsigned g_spell_texture_upload_state;

void Fighter::prepare_next_spell_sequence_entry()
{
    if (static_cast<signed char>(reinterpret_cast<std::deque<SequencePrepareRecord98> *>(&sequence_controller_55c)->size()) >= state_55b ||
        reinterpret_cast<std::deque<short> *>(&reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0)->selection_ids_34)->size() == 0)
        return;
    counter_558=0;
    SequencePrepareRecord98 sequence_record;
    SpellDataOwner *lookup=reinterpret_cast<SpellDataOwner *>(spell_lookup_4f0);
    sequence_record.record_id=lookup->select_spell_record_id();
    SpellRecordView *record=lookup->find_local_then_common_spell_record(sequence_record.record_id);
    if (!record)return;
    sequence_record.value=record->value_1e.value;
    if(record->selector_1c==1)sequence_record.value=1;
    if(record->optional_resource_44)
        sequence_record.sprite.set_texture(
            reinterpret_cast<unsigned>(record->optional_resource_44),0,0,
            g_spell_texture_load_state,g_spell_texture_upload_state);
    sequence_controller_55c.enqueue_record(reinterpret_cast<const FighterSequenceSlot *>(&sequence_record));
    state_55a=static_cast<signed char>(reinterpret_cast<std::deque<SequencePrepareRecord98> *>(&sequence_controller_55c)->size());
}

} // namespace th105
