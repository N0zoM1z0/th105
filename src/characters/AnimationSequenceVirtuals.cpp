#include "AnimationSequenceVirtuals.hpp"

#include <map>

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
    unsigned int const index = static_cast<unsigned int>(frame_index_140);
    frame_150 = frame_158 = &block->records_00[index];
    frame_timer_142 = 0;
    frame_limit_14c = static_cast<short>(frame_150->duration_bits_08);
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
    return frame_index_140 == 0 && sequence_15c->field_14 == 0;
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
    if (block->link_1c != 0) {
        ++sequence_index_13e;
        time_counter_144 = 0;
        sequence_15c = block->link_1c;
    }
    block = sequence_15c;
    sequence_frame_count_148 = static_cast<short>(block->records_00.size());
    set_sequence_frame(0);
    if (sequence_15c->link_18 == 0) {
        sequence_index_13e = 0;
        time_counter_144 = 0;
        return 1;
    }
    return 0;
}

int AnimationSequenceObjectView::previous_sequence_block()
{
    AnimationSequenceBlock *block = sequence_15c;
    if (block->link_18 != 0) {
        --sequence_index_13e;
        time_counter_144 = 0;
        sequence_15c = block->link_18;
    }
    block = sequence_15c;
    sequence_frame_count_148 = static_cast<short>(block->records_00.size());
    return set_sequence_frame(0);
}

int AnimationSequenceObjectView::select_sequence(int sequence)
{
    time_counter_144 = 0;
    int const key = action_id_13c;
    sequence_15c = sequence_tree_160->find(key)->second;
    sequence_index_13e = static_cast<short>(sequence);
    time_counter_144 = 0;
    while (static_cast<short>(sequence) != 0) {
        --sequence;
        sequence_15c = sequence_15c->link_1c;
    }
    AnimationSequenceBlock *const block = sequence_15c;
    sequence_frame_count_148 = static_cast<short>(block->records_00.size());
    return set_sequence_frame(0);
}

int AnimationSequenceObjectView::reset_sequence()
{
    time_counter_144 = 0;
    sequence_index_13e = 0;
    int const key = action_id_13c;
    sequence_15c = sequence_tree_160->find(key)->second;
    AnimationSequenceBlock *const block = sequence_15c;
    sequence_frame_count_148 = static_cast<short>(block->records_00.size());
    return set_sequence_frame(0);
}

} // namespace th105
