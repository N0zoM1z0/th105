#include "Title.hpp"

namespace th105 {

void TitleDesignResource::bind_object(
    UiDesignObject **result, int object_id)
{
    unsigned int key = object_id;
    UiDesignTree *tree = &object_tree_20;
    UiDesignTreeIterator found = tree->find(&key);
    UiDesignTreeNode *head = tree->head;
    UiDesignTree *owner = found.owner;

    if (owner == 0 || owner != tree)
        _invalid_parameter_noinfo();
    UiDesignTreeNode *node = found.node;
    if (node == head) {
        *result = 0;
        return;
    }
    if (owner == 0)
        _invalid_parameter_noinfo();
    if (node == owner->head)
        _invalid_parameter_noinfo();
    *result = node->value;
}

void TitleDesignResource::bind_object_alt(
    UiDesignObject **result, int object_id)
{
    unsigned int key = object_id;
    UiDesignTree *tree = &object_tree_20;
    UiDesignTreeIterator found = tree->find(&key);
    UiDesignTreeNode *head = tree->head;
    UiDesignTree *owner = found.owner;

    if (owner == 0 || owner != tree)
        _invalid_parameter_noinfo();
    UiDesignTreeNode *node = found.node;
    if (node == head) {
        *result = 0;
        return;
    }
    if (owner == 0)
        _invalid_parameter_noinfo();
    if (node == owner->head)
        _invalid_parameter_noinfo();
    *result = node->value;
}

} // namespace th105
