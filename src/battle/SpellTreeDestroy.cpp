#include "SpellData.hpp"

#include <new>

namespace th105 {

void SpellTree::destroy_subtree(SpellTreeNode *node)
{
    SpellTreeNode *current = node;
    while (!current->is_nil_5d) {
        destroy_subtree(current->right_08);
        SpellTreeNode *next = current->left_00;
        current->value_10.description_20.~String28();
        current->value_10.name_00.~String28();
        ::operator delete(current);
        current = next;
    }
}

} // namespace th105
