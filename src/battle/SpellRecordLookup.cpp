#include "SpellData.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

// Define the common tree in this comparison unit so strict DIR32 validation
// can verify its zero-filled target bytes and checked-iterator addends.
SpellTree g_common_spell_tree;

SpellRecordView *SpellDataOwner::find_local_then_common_spell_record(int key)
{
    SpellTree *local_tree = &local_tree_14;
    SpellTreeIterator result;
    local_tree->find_checked(&result, &key);
    SpellTree *local_owner = result.owner;
    if (local_owner == 0 || local_owner != local_tree) {
        _invalid_parameter_noinfo();
    }

    SpellTreeNode *local_node = result.node;
    if (local_node != local_tree->end_node_04) {
        if (local_owner == 0) {
            _invalid_parameter_noinfo();
        }
        if (local_node == local_owner->end_node_04) {
            _invalid_parameter_noinfo();
        }
        return reinterpret_cast<SpellRecordView *>(
            reinterpret_cast<unsigned char *>(local_node) + 0x10);
    }

    SpellTreeIterator *common_result =
        g_common_spell_tree.find_checked(&result, &key);
    SpellTreeNode *common_node = common_result->node;
    SpellTree *common_owner = common_result->owner;
    if (common_owner == 0 || common_owner != &g_common_spell_tree) {
        _invalid_parameter_noinfo();
    }
    if (common_node != g_common_spell_tree.end_node_04) {
        if (common_owner == 0) {
            _invalid_parameter_noinfo();
        }
        if (common_node == common_owner->end_node_04) {
            _invalid_parameter_noinfo();
        }
        return reinterpret_cast<SpellRecordView *>(
            reinterpret_cast<unsigned char *>(common_node) + 0x10);
    }
    return 0;
}

} // namespace th105
