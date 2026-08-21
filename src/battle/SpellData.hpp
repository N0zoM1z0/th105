#pragma once

#include "assets/String28.hpp"

namespace th105 {

struct SpellTree;

struct SpellRecordCopyShort {
    short value;

    SpellRecordCopyShort() {}
    SpellRecordCopyShort(short source) : value(source) {}
    SpellRecordCopyShort(const SpellRecordCopyShort &source)
        : value(source.value)
    {
        // The target record special member retains this second load/store.
        value = source.value;
    }
    SpellRecordCopyShort &operator=(short source)
    {
        value = source;
        return *this;
    }
    operator short() const { return value; }
};

struct SpellRecordView {
    String28 name_00;
    signed char selector_1c;
    SpellRecordCopyShort value_1e;
    String28 description_20;
    SpellRecordCopyShort value_3c;
    short value_3e;
    void *batch_resource_40;
    void *optional_resource_44;
    int value_48;

    SpellRecordView() {}
};

typedef char SpellRecordView_size_must_be_0x4c[
    sizeof(SpellRecordView) == 0x4c ? 1 : -1];

struct SpellTreeNode {
    SpellTreeNode *left_00;
    SpellTreeNode *parent_04;
    SpellTreeNode *right_08;
    int key_0c;
    SpellRecordView value_10;
    unsigned char color_5c;
    unsigned char is_nil_5d;
    unsigned char padding_5e[2];
};

struct SpellTreeIterator {
    SpellTree *owner;
    SpellTreeNode *node;

    void decrement_checked();
};

struct SpellTreeValue {
    int key;
    SpellRecordView record;

    SpellTreeValue(int key_value, const SpellRecordView &record_value)
        : key(key_value), record(record_value) {}
};

struct SpellTreeInsertResult {
    SpellTree *owner;
    SpellTreeNode *node;
    unsigned char inserted;
    unsigned char padding[3];
};

struct SpellTree {
    unsigned allocator_state_00;
    SpellTreeNode *end_node_04;
    unsigned node_count_08;

    SpellTreeIterator *find_checked(
        SpellTreeIterator *result,
        const int *key);
    SpellTreeInsertResult *insert_unique_value(
        SpellTreeInsertResult *result,
        const SpellTreeValue *value);
    SpellTreeIterator *erase_range_checked(
        SpellTreeIterator *result,
        SpellTreeIterator begin,
        SpellTreeIterator end);
    void destroy_subtree(SpellTreeNode *node);
};

typedef char SpellTreeNode_size_must_be_0x60[
    sizeof(SpellTreeNode) == 0x60 ? 1 : -1];
typedef char SpellTreeValue_size_must_be_0x50[
    sizeof(SpellTreeValue) == 0x50 ? 1 : -1];
typedef char SpellTreeInsertResult_size_must_be_0x0c[
    sizeof(SpellTreeInsertResult) == 0x0c ? 1 : -1];
typedef char SpellTree_size_must_be_0x0c[
    sizeof(SpellTree) == 0x0c ? 1 : -1];

struct DwordDeque4 {
    unsigned allocator_state_00;
    unsigned **blocks_04;
    unsigned block_capacity_08;
    unsigned head_0c;
    unsigned live_count_10;

    void push_back(const unsigned *value);
    unsigned &back_checked();
    void clear_storage();
};

struct ShortTree;

struct ShortTreeNode {
    ShortTreeNode *left_00;
    ShortTreeNode *parent_04;
    ShortTreeNode *right_08;
    short key_0c;
    unsigned char color_0e;
    unsigned char is_nil_0f;
};

struct ShortTreeIterator {
    ShortTree *owner;
    ShortTreeNode *node;
};

struct ShortTreeInsertResult {
    ShortTree *owner;
    ShortTreeNode *node;
    unsigned char inserted;
    unsigned char padding[3];
};

struct ShortTree {
    unsigned allocator_state_00;
    ShortTreeNode *end_node_04;
    unsigned node_count_08;

    ShortTreeIterator *find_checked(
        ShortTreeIterator *result,
        const short *key);
    ShortTreeInsertResult *insert_unique_key(
        ShortTreeInsertResult *result,
        const short *key);
    ShortTreeIterator *erase_range_checked(
        ShortTreeIterator *result,
        ShortTreeIterator begin,
        ShortTreeIterator end);
};

typedef char ShortTreeNode_size_must_be_0x10[
    sizeof(ShortTreeNode) == 0x10 ? 1 : -1];
typedef char ShortTree_size_must_be_0x0c[
    sizeof(ShortTree) == 0x0c ? 1 : -1];

struct ShortDeque8 {
    unsigned unknown_00;
    short **blocks_04;
    unsigned block_capacity_08;
    unsigned head_0c;
    unsigned live_count_10;

    __declspec(noinline) short *front_checked();
    short *push_back(const short *value);
    void clear_storage();
};

struct SpellDataOwner {
    DwordDeque4 image_handles_00;
    SpellTree local_tree_14;
    ShortDeque8 loaded_spell_ids_20;
    ShortDeque8 selection_ids_34;
    unsigned char selected_value_by_index_48[0x20];

    void clear_spell_entries();
    void parse_spell_csv_via_325b0(
        const char *character_name,
        const char *path,
        DwordDeque4 *image_owner,
        SpellTree *destination,
        void *mode_argument);
    void parse_spell_csv_and_build_card_resources(
        const char *character_name,
        const char *path,
        DwordDeque4 *image_owner,
        SpellTree *destination);
    void finalize_loaded_spell_data();
    short select_spell_record_id();
    SpellRecordView *find_local_then_common_spell_record(int key);
    unsigned char load_spell_data(
        int character_key,
        int arg2,
        unsigned char alternate_loader);
    void initialize_side_payload_430f70(const ShortDeque8 *payload);
    unsigned char load_spell_csv_via_325b0(
        int character_key,
        signed char story_mode,
        void *mode_argument);
    unsigned char load_spell_csv_via_32e20(
        int character_key,
        signed char story_mode,
        unsigned char use_owner);
};

extern SpellTree g_common_spell_tree;

} // namespace th105
