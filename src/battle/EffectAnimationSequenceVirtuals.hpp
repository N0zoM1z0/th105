#pragma once

#include <stddef.h>
#include <map>
#include "battle/EffectResourceGroup.hpp"

namespace th105 {

typedef std::map<int, EffectResourceGroup *> EffectAnimationMap;

class EffectAnimationSequenceView {
public:
    virtual void scalar_delete_slot_00();
    virtual int set_action_sequence_and_finalize(short action, int sequence);
    virtual int set_action_and_finalize(short action);
    virtual int select_sequence(int sequence);
    virtual int reset_sequence();
    virtual unsigned char next_sequence_block();
    virtual int previous_sequence_block();
    virtual int set_sequence_frame(short frame);
    virtual unsigned char next_sequence_frame();
    virtual int previous_sequence_frame();

    int apply_sequence_frame();
    int apply_current_frame();

    unsigned char unknown_004[0x138];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    short frame_count_148;
    unsigned char unknown_14a[0x02];
    short frame_limit_14c;
    unsigned char unknown_14e[0x02];
    FrameData *frame_150;
    unsigned char unknown_154[0x0c];
    EffectAnimationMap *sequence_tree_160;
    unsigned char unknown_164[0x04];
    EffectResourceGroup *sequence_168;
};

typedef char EffectAnimationSequence_action_offset_must_be_0x13c[
    offsetof(EffectAnimationSequenceView, action_id_13c) == 0x13c ? 1 : -1];
typedef char EffectAnimationSequence_frame_index_offset_must_be_0x140[
    offsetof(EffectAnimationSequenceView, frame_index_140) == 0x140 ? 1 : -1];
typedef char EffectAnimationSequence_frame_count_offset_must_be_0x148[
    offsetof(EffectAnimationSequenceView, frame_count_148) == 0x148 ? 1 : -1];
typedef char EffectAnimationSequence_frame_offset_must_be_0x150[
    offsetof(EffectAnimationSequenceView, frame_150) == 0x150 ? 1 : -1];
typedef char EffectAnimationSequence_tree_offset_must_be_0x160[
    offsetof(EffectAnimationSequenceView, sequence_tree_160) == 0x160 ? 1 : -1];
typedef char EffectAnimationSequence_block_offset_must_be_0x168[
    offsetof(EffectAnimationSequenceView, sequence_168) == 0x168 ? 1 : -1];

} // namespace th105
