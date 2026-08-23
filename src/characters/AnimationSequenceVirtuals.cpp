#include "AnimationSequenceVirtuals.hpp"

extern "C" void __cdecl _invalid_parameter_noinfo(void);

namespace th105 {

void AnimationSequenceObjectView::set_action(short action)
{
    action_id_13c = action;
    reset_sequence();
}

void AnimationSequenceObjectView::set_action_sequence(short action, int sequence)
{
    action_id_13c = action;
    select_sequence(sequence);
}

int AnimationSequenceObjectView::apply_sequence_frame()
{
    AnimationSequenceBlock *const block = sequence_15c;
    AnimationSequenceFrame *const begin = block->frames_begin_04;
    unsigned int const index = static_cast<unsigned int>(frame_index_140);
    unsigned int const count = begin == 0 ? 0 :
        static_cast<unsigned int>(block->frames_end_08 - begin);
    if (begin == 0 || index >= count)
        _invalid_parameter_noinfo();
    frame_150 = frame_158 = block->frames_begin_04 + index;
    frame_timer_142 = 0;
    frame_limit_14c = frame_150->duration_08;
    return apply_current_frame();
}

int AnimationSequenceObjectView::set_sequence_frame(short frame)
{
    frame_index_140 = frame;
    return apply_sequence_frame();
}

unsigned char AnimationSequenceObjectView::next_sequence_frame()
{
    frame_index_140 = static_cast<short>(
        (frame_index_140 + 1) % sequence_frame_count_148);
    apply_sequence_frame();
    return frame_index_140 == 0 && sequence_15c->mode_14 == 0;
}

int AnimationSequenceObjectView::previous_sequence_frame()
{
    frame_index_140 = static_cast<short>(
        (frame_index_140 + sequence_frame_count_148 - 1) %
        sequence_frame_count_148);
    return apply_sequence_frame();
}

unsigned char AnimationSequenceObjectView::next_sequence_block()
{
    AnimationSequenceBlock *block = sequence_15c;
    if (block->next_1c != 0) {
        ++sequence_index_13e;
        time_counter_144 = 0;
        sequence_15c = block->next_1c;
    }
    block = sequence_15c;
    sequence_frame_count_148 = block->frames_begin_04 == 0 ? 0 :
        block->frames_end_08 - block->frames_begin_04;
    set_sequence_frame(0);
    if (sequence_15c->previous_18 == 0) {
        sequence_index_13e = 0;
        time_counter_144 = 0;
        return 1;
    }
    return 0;
}

int AnimationSequenceObjectView::previous_sequence_block()
{
    AnimationSequenceBlock *block = sequence_15c;
    if (block->previous_18 != 0) {
        --sequence_index_13e;
        time_counter_144 = 0;
        sequence_15c = block->previous_18;
    }
    block = sequence_15c;
    sequence_frame_count_148 = block->frames_begin_04 == 0 ? 0 :
        block->frames_end_08 - block->frames_begin_04;
    return set_sequence_frame(0);
}

int AnimationSequenceObjectView::select_sequence(int sequence)
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
    sequence_index_13e = static_cast<short>(sequence);
    time_counter_144 = 0;
    while (static_cast<short>(sequence) != 0) {
        --sequence;
        sequence_15c = sequence_15c->next_1c;
    }
    AnimationSequenceBlock *const block = sequence_15c;
    sequence_frame_count_148 = block->frames_begin_04 == 0 ? 0 :
        block->frames_end_08 - block->frames_begin_04;
    return set_sequence_frame(0);
}

int AnimationSequenceObjectView::reset_sequence()
{
    AnimationSequenceTreeIterator found;
    time_counter_144 = 0;
    sequence_index_13e = 0;
    int const key = action_id_13c;
    AnimationSequenceTreeIterator *const result =
        sequence_tree_160->lower_bound(&found, &key);
    if (result->owner_00 == 0)
        _invalid_parameter_noinfo();
    if (result->node_04 == result->owner_00->end_node_04)
        _invalid_parameter_noinfo();
    sequence_15c = result->node_04->value_10;
    AnimationSequenceBlock *const block = sequence_15c;
    sequence_frame_count_148 = block->frames_begin_04 == 0 ? 0 :
        block->frames_end_08 - block->frames_begin_04;
    return set_sequence_frame(0);
}

} // namespace th105
