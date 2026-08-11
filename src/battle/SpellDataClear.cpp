#include "battle/SpellData.hpp"
#include "ui/Title.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

namespace {

struct DwordDeque4Iterator {
    DwordDeque4 *owner;
    unsigned absolute;
};

__forceinline unsigned &dereference_checked(DwordDeque4Iterator *iterator)
{
    DwordDeque4 *owner = iterator->owner;
    unsigned absolute = iterator->absolute;
    unsigned block = absolute >> 2;
    unsigned within_block = absolute & 3;
    if (absolute >= owner->head_0c + owner->live_count_10) {
        _invalid_parameter_noinfo();
    }
    if (owner->block_capacity_08 <= block) {
        block -= owner->block_capacity_08;
    }
    return owner->blocks_04[block][within_block];
}

__forceinline void increment_checked(DwordDeque4Iterator *iterator)
{
    DwordDeque4 *owner = iterator->owner;
    if (iterator->absolute >= owner->head_0c + owner->live_count_10) {
        _invalid_parameter_noinfo();
    }
    ++iterator->absolute;
}

} // namespace

void SpellDataOwner::clear_spell_entries()
{
    DwordDeque4 *handles = &image_handles_00;
    DwordDeque4Iterator current = {handles, handles->head_0c};
    if (current.absolute > handles->head_0c + handles->live_count_10) {
        _invalid_parameter_noinfo();
    }
    for (;;) {
        DwordDeque4Iterator finish = {
            handles,
            handles->head_0c + handles->live_count_10};
        if (handles->head_0c > finish.absolute) {
            _invalid_parameter_noinfo();
        }
        if (current.absolute == finish.absolute) {
            break;
        }
        g_title_resource_manager.release_title_resource_handle(
            dereference_checked(&current));
        increment_checked(&current);
    }
    handles->clear_storage();

    SpellTree *tree = &local_tree_14;
    tree->destroy_subtree(tree->end_node_04->parent_04);
    tree->end_node_04->parent_04 = tree->end_node_04;
    tree->node_count_08 = 0;
    tree->end_node_04->left_00 = tree->end_node_04;
    tree->end_node_04->right_08 = tree->end_node_04;
}

} // namespace th105
