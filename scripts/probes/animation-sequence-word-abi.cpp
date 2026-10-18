// Alternative ABI witness for the already-matched45C390; no duplicate credit.
// The natural short parameter consumes the low word of a four-byte stack slot.
// See docs/AYA_ENTRY_SEQUENCE_WORD_ABI_2026_10_19.md.
#include "characters/AnimationSequenceVirtuals.hpp"

namespace th105 {
extern "C" void __cdecl _invalid_parameter_noinfo(void);

class AnimationSequenceWordAbiView : public AnimationSequenceObjectView {
public:
    int select_sequence(short sequence);
};

int AnimationSequenceWordAbiView::select_sequence(short sequence)
{
    AnimationSequenceTreeIterator found;
    time_counter_144 = 0;
    int const key = action_id_13c;
    AnimationSequenceTreeIterator *const result =
        sequence_tree_160->lower_bound(&found, &key);
    if (result->owner_00 == 0)
        _invalid_parameter_noinfo();
    if (result->node_04 == result->owner_00->end_node_04)
        _invalid_parameter_noinfo();
    sequence_15c = result->node_04->value_10;
    sequence_index_13e = sequence;
    time_counter_144 = 0;
    while (sequence != 0) {
        --sequence;
        sequence_15c = sequence_15c->next_1c;
    }
    AnimationSequenceBlock *const block = sequence_15c;
    sequence_frame_count_148 = block->frames_begin_04 == 0 ? 0 :
        block->frames_end_08 - block->frames_begin_04;
    return set_sequence_frame(0);
}
} // namespace th105
