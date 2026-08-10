#include "Title.hpp"

namespace th105 {

UiDesignTreeIterator UiDesignTree::find(const unsigned int *key)
{
    UiDesignTreeNode *candidate = head;
    UiDesignTreeNode *node = head->parent;

    while (!node->is_nil) {
        if (node->key < *key) {
            node = node->right;
        } else {
            candidate = node;
            node = node->left;
        }
    }

    UiDesignTreeIterator found;
    found.node = candidate;
    found.owner = this;
    UiDesignTreeIterator end;
    const UiDesignTreeIterator *selected;
    if (candidate == head || *key < candidate->key) {
        end.owner = this;
        end.node = head;
        selected = &end;
    } else {
        selected = &found;
    }
    return *selected;
}

} // namespace th105
