#pragma once

#include <stddef.h>

namespace th105 {

struct AnimationSequenceFrame {
    unsigned char unknown_00[0x08];
    short duration_08;
    unsigned char unknown_0a[0x7e];
};

struct AnimationSequenceBlock {
    unsigned unknown_00;
    AnimationSequenceFrame *frames_begin_04;
    AnimationSequenceFrame *frames_end_08;
    unsigned char unknown_0c[0x08];
    unsigned char mode_14;
    unsigned char unknown_15[0x03];
    AnimationSequenceBlock *previous_18;
    AnimationSequenceBlock *next_1c;
};

struct AnimationSequenceTreeNode {
    AnimationSequenceTreeNode *left_00;
    AnimationSequenceTreeNode *parent_04;
    AnimationSequenceTreeNode *right_08;
    int key_0c;
    AnimationSequenceBlock *value_10;
    unsigned char unknown_14;
    unsigned char is_end_15;
    unsigned char unknown_16[0x02];
};

struct AnimationSequenceTree;
struct AnimationSequenceTreeIterator {
    AnimationSequenceTree *owner_00;
    AnimationSequenceTreeNode *node_04;
};
struct AnimationSequenceTree {
    unsigned unknown_00;
    AnimationSequenceTreeNode *end_node_04;
    AnimationSequenceTreeIterator *lower_bound(
        AnimationSequenceTreeIterator *result,
        const int *key);
};

class AnimationSequenceObjectView {
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
    virtual void pure_slot_28() = 0;
    virtual void render_slot_2c();
    virtual void render_slot_30();
    virtual void render_slot_34();
    virtual void render_slot_38();
    virtual int finalize_action() = 0;

    void set_action(short action);
    void set_action_sequence(short action, int sequence);
    int apply_sequence_frame();
    int apply_current_frame();

    void dispatch_character_wave_handle(unsigned index);
    void forward_hit_quantity(
        int quantity, int scalar_per_thousand,
        short forwarded_counter_delta, signed char use_dynamic_scalar);

    unsigned char unknown_004[0x138];
    short action_id_13c;
    short sequence_index_13e;
    short frame_index_140;
    short frame_timer_142;
    int time_counter_144;
    short sequence_frame_count_148;
    unsigned char unknown_14a[0x02];
    short frame_limit_14c;
    unsigned char unknown_14e[0x02];
    AnimationSequenceFrame *frame_150;
    void *unknown_154;
    AnimationSequenceFrame *frame_158;
    AnimationSequenceBlock *sequence_15c;
    AnimationSequenceTree *sequence_tree_160;
    unsigned *wave_handles_164;
    void *owner_168;
    void *related_16c;
    void *related_170;

};

typedef char AnimationSequenceFrame_size_must_be_0x88[
    sizeof(AnimationSequenceFrame) == 0x88 ? 1 : -1];
typedef char AnimationSequenceBlock_size_must_be_0x20[
    sizeof(AnimationSequenceBlock) == 0x20 ? 1 : -1];
typedef char AnimationSequenceObject_action_offset_must_be_0x13c[
    offsetof(AnimationSequenceObjectView, action_id_13c) == 0x13c ? 1 : -1];
typedef char AnimationSequenceObject_frame_offset_must_be_0x150[
    offsetof(AnimationSequenceObjectView, frame_150) == 0x150 ? 1 : -1];
typedef char AnimationSequenceObject_tree_offset_must_be_0x160[
    offsetof(AnimationSequenceObjectView, sequence_tree_160) == 0x160 ? 1 : -1];
typedef char AnimationSequenceObject_related_offset_must_be_0x170[
    offsetof(AnimationSequenceObjectView, related_170) == 0x170 ? 1 : -1];

} // namespace th105
