#pragma once

namespace th105 {

struct CommandGateEntry {
    unsigned char unknown_00[0x10];
    short value_10;
};

struct CommandGateNode {
    CommandGateNode *left_00;
    CommandGateNode *parent_04;
    CommandGateNode *right_08;
    int key_0c;
    CommandGateEntry *value_10;
    unsigned char unknown_14;
    unsigned char is_end_15;
    unsigned char unknown_16[0x02];
};

struct CommandGateTree;

struct CommandGateIterator {
    CommandGateTree *owner_00;
    CommandGateNode *node_04;
};

struct CommandGateTree {
    unsigned unknown_00;
    CommandGateNode *end_node_04;

    CommandGateIterator *lower_bound(
        CommandGateIterator *result,
        const int *signed_key);
};

} // namespace th105
