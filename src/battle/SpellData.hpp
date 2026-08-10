#pragma once

namespace th105 {

struct SpellTree;

struct SpellTreeNode {
    unsigned char unknown_00[0x10];
};

struct SpellTreeIterator {
    SpellTree *owner;
    SpellTreeNode *node;
};

struct SpellTree {
    unsigned char unknown_00[0x04];
    SpellTreeNode *end_node_04;

    SpellTreeIterator *find_checked(
        SpellTreeIterator *result,
        const int *key);
};

struct SpellRecordView {
    unsigned char unknown_00[0x1c];
    signed char selector_1c;
    unsigned char unknown_1d;
    short value_1e;
    unsigned char unknown_20[0x1c];
    short value_3c;
    short value_3e;
    void *batch_resource_40;
    void *optional_resource_44;
    int value_48;
};

struct ShortDeque8 {
    unsigned unknown_00;
    short **blocks_04;
    unsigned block_capacity_08;
    unsigned head_0c;
    unsigned live_count_10;

    __declspec(noinline) short *front_checked();
};

struct SpellDataOwner {
    unsigned char unknown_00[0x14];
    SpellTree local_tree_14;
    unsigned char unknown_1c[0x04];
    ShortDeque8 loaded_spell_ids_20;
    ShortDeque8 selection_ids_34;
    unsigned char selected_value_by_index_48[0x20];

    void clear_spell_entries();
    void finalize_loaded_spell_data();
    short select_spell_record_id();
    SpellRecordView *find_local_then_common_spell_record(int key);
    unsigned char load_spell_data(
        int character_key,
        int arg2,
        unsigned char alternate_loader);
    unsigned char load_spell_csv_via_325b0(
        int character_key,
        int arg2,
        void *mode_argument);
    unsigned char load_spell_csv_via_32e20(
        int character_key,
        int arg2,
        unsigned char use_owner);
    void parse_spell_csv_via_325b0(
        const char *character_name,
        const char *path,
        SpellDataOwner *owner,
        SpellTree *destination,
        void *mode_argument);
    void parse_spell_csv_and_build_card_resources(
        const char *character_name,
        const char *path,
        void *image_owner,
        SpellTree *destination);
};

extern SpellTree g_common_spell_tree;

} // namespace th105
