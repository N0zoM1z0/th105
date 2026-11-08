#include "EffectAnimationSequenceVirtuals.hpp"

namespace th105 {

int EffectAnimationSequenceView::apply_sequence_frame()
{
    EffectResourceGroup *const block = sequence_168;
    unsigned int const index = static_cast<unsigned int>(frame_index_140);
    frame_150 = &block->frames_04[index];
    frame_timer_142 = 0;
    frame_limit_14c = static_cast<short>(frame_150->duration_bits_08);
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
    return frame_index_140 == 0 && sequence_168->suppress_wrap_signal_14 == 0;
}

int EffectAnimationSequenceView::previous_sequence_frame()
{
    frame_index_140 = static_cast<short>(
        (frame_index_140 + frame_count_148 - 1) % frame_count_148);
    return apply_sequence_frame();
}

unsigned char EffectAnimationSequenceView::next_sequence_block()
{
    EffectResourceGroup *block = sequence_168;
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
    EffectResourceGroup *block = sequence_168;
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
    int const key = action_id_13c;
    sequence_168 = sequence_tree_160->find(key)->second;
    sequence_index_13e = static_cast<short>(sequence);
    time_counter_144 = 0;
    while (static_cast<short>(sequence) != 0) {
        --sequence;
        sequence_168 = sequence_168->next_1c;
    }
    EffectResourceGroup *const block = sequence_168;
    frame_count_148 = static_cast<short>(block->frames_04.size());
    return set_sequence_frame(0);
}

int EffectAnimationSequenceView::reset_sequence()
{
    sequence_index_13e = 0;
    time_counter_144 = 0;
    int const key = action_id_13c;
    sequence_168 = sequence_tree_160->find(key)->second;
    EffectResourceGroup *const block = sequence_168;
    frame_count_148 = static_cast<short>(block->frames_04.size());
    return set_sequence_frame(0);
}

} // namespace th105
