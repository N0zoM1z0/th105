#include "EffectAnimationSequenceVirtuals.hpp"

extern "C" void __cdecl _invalid_parameter_noinfo(void);

namespace th105 {

int EffectAnimationSequenceView::apply_sequence_frame()
{
    EffectAnimationBlockView *const block = sequence_168;
    unsigned int const index = static_cast<unsigned int>(frame_index_140);
    frame_150 = &block->frames_04[index];
    frame_timer_142 = 0;
    frame_limit_14c = frame_150->duration_08;
    return apply_current_frame();
}

int EffectAnimationSequenceView::set_sequence_frame(short frame)
{
    frame_index_140 = frame;
    return apply_sequence_frame();
}

unsigned char EffectAnimationSequenceView::next_sequence_frame()
{
    frame_index_140 = static_cast<short>(
        (frame_index_140 + 1) % frame_count_148);
    apply_sequence_frame();
    return frame_index_140 == 0 && sequence_168->mode_14 == 0;
}

int EffectAnimationSequenceView::previous_sequence_frame()
{
    frame_index_140 = static_cast<short>(
        (frame_index_140 + frame_count_148 - 1) % frame_count_148);
    return apply_sequence_frame();
}

unsigned char EffectAnimationSequenceView::next_sequence_block()
{
    EffectAnimationBlockView *block = sequence_168;
    if (block->next_1c != 0) {
        ++sequence_index_13e;
        time_counter_144 = 0;
        sequence_168 = block->next_1c;
    }
    block = sequence_168;
    frame_count_148 = static_cast<short>(block->frames_04.size());
    set_sequence_frame(0);
    if (sequence_168->previous_18 == 0) {
        sequence_index_13e = 0;
        time_counter_144 = 0;
        return 1;
    }
    return 0;
}

int EffectAnimationSequenceView::previous_sequence_block()
{
    EffectAnimationBlockView *block = sequence_168;
    if (block->previous_18 != 0) {
        --sequence_index_13e;
        time_counter_144 = 0;
        sequence_168 = block->previous_18;
    }
    block = sequence_168;
    frame_count_148 = static_cast<short>(block->frames_04.size());
    return set_sequence_frame(0);
}

int EffectAnimationSequenceView::select_sequence(int sequence)
{
    EffectAnimationTreeIterator found;
    int const key = action_id_13c;
    EffectAnimationTreeIterator *const result =
        sequence_tree_160->lower_bound(&found, &key);
    if (result->owner_00 == 0)
        _invalid_parameter_noinfo();
    if (result->node_04 == result->owner_00->end_node_04)
        _invalid_parameter_noinfo();
    sequence_168 = result->node_04->value_10;
    sequence_index_13e = static_cast<short>(sequence);
    time_counter_144 = 0;
    while (static_cast<short>(sequence) != 0) {
        --sequence;
        sequence_168 = sequence_168->next_1c;
    }
    EffectAnimationBlockView *const block = sequence_168;
    frame_count_148 = static_cast<short>(block->frames_04.size());
    return set_sequence_frame(0);
}

int EffectAnimationSequenceView::reset_sequence()
{
    EffectAnimationTreeIterator found;
    sequence_index_13e = 0;
    time_counter_144 = 0;
    int const key = action_id_13c;
    EffectAnimationTreeIterator *const result =
        sequence_tree_160->lower_bound(&found, &key);
    if (result->owner_00 == 0)
        _invalid_parameter_noinfo();
    if (result->node_04 == result->owner_00->end_node_04)
        _invalid_parameter_noinfo();
    sequence_168 = result->node_04->value_10;
    EffectAnimationBlockView *const block = sequence_168;
    frame_count_148 = static_cast<short>(block->frames_04.size());
    return set_sequence_frame(0);
}

} // namespace th105
