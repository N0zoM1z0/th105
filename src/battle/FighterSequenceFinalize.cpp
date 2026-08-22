#include "Collision.hpp"
#include "SpellRuntime.hpp"

#include "config/ScoreData.hpp"

namespace th105 {

struct FighterSequenceEffectView {
    void finalize_4643f0();
};

void Fighter::finalize_sequence_entry_45bb10(int outcome)
{
    if (state_55a == 0) {
        return;
    }

    if (outcome != 0) {
        if (post_advance_value_650 >= 0) {
            statistic_candidate_64c = post_advance_value_650;
        }

        get_score_data()->record_sequence_result_42c060(
            other_fighter_170->record_key_330,
            record_key_330,
            sequence_controller_55c.entry_at_checked(0)->record_id_00);
        reinterpret_cast<FighterSequenceEffectView *>(
            reinterpret_cast<unsigned char *>(this) + 0x3d0)
            ->finalize_4643f0();
    }

    reinterpret_cast<PlayerIndexedCallbackView *>(
            reinterpret_cast<unsigned char *>(g_info_manager) +
            static_cast<int>(player_index_334) * 0x154 + 0x1d4)
        ->invoke_indexed_record(
            sequence_controller_55c.entry_at_checked(0)->record_id_00,
            outcome);
}

} // namespace th105
