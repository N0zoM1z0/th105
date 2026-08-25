#pragma once

#include <stddef.h>
#include <vector>

namespace th105 {

struct EffectAnimationFrame28 {
    unsigned char unknown_00[0x08];
    short duration_08;
    unsigned char unknown_0a[0x12];
};

struct EffectAnimationBlockView {
    unsigned unknown_00;
    std::vector<EffectAnimationFrame28> frames_04;
    unsigned char mode_14;
    unsigned char unknown_15[0x03];
    EffectAnimationBlockView *previous_18;
    EffectAnimationBlockView *next_1c;
};

struct EffectAnimationTreeNode {
    EffectAnimationTreeNode *left_00;
    EffectAnimationTreeNode *parent_04;
    EffectAnimationTreeNode *right_08;
    int key_0c;
    EffectAnimationBlockView *value_10;
    unsigned char unknown_14;
    unsigned char is_end_15;
    unsigned char unknown_16[0x02];
};

struct EffectAnimationTree;
struct EffectAnimationTreeIterator {
    EffectAnimationTree *owner_00;
    EffectAnimationTreeNode *node_04;
};
struct EffectAnimationTree {
    unsigned unknown_00;
    EffectAnimationTreeNode *end_node_04;
    EffectAnimationTreeIterator *lower_bound(
        EffectAnimationTreeIterator *result,
        const int *key);
};

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
    EffectAnimationFrame28 *frame_150;
    unsigned char unknown_154[0x0c];
    EffectAnimationTree *sequence_tree_160;
    unsigned char unknown_164[0x04];
    EffectAnimationBlockView *sequence_168;
};

typedef char EffectAnimationFrame28_size_must_be_0x1c[
    sizeof(EffectAnimationFrame28) == 0x1c ? 1 : -1];
typedef char EffectAnimationBlock_size_must_be_0x20[
    sizeof(EffectAnimationBlockView) == 0x20 ? 1 : -1];
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
