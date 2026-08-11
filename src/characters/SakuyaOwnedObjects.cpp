#include "Sakuya.hpp"

namespace th105 {

SakuyaObject *SakuyaObjectManagerBase::acquire_and_link_object()
{
    union LocalSlot {
        unsigned handle_token;
        SakuyaObject *object;
    } local;

    local.handle_token = 0;
    SakuyaObject *object = pool_04.acquire(&local.handle_token);
    object->handle_token_334 = local.handle_token;

    CollisionListNode *sentinel = linked_objects_54.sentinel;
    local.object = object;
    CollisionListNode *node = create_collision_list_node(
        sentinel,
        sentinel->previous,
        reinterpret_cast<void **>(&local.object));
    linked_objects_54.std_list_incsize_pointer(1);
    sentinel->previous = node;
    node->previous->next = node;
    return object;
}

CollisionListNode *SakuyaObjectManagerBase::preallocate_object_pool(
    unsigned target_count)
{
    while (linked_objects_54.count < target_count) {
        union LocalSlot {
            unsigned handle_token;
            SakuyaObject *object;
        } local;

        local.handle_token = 0;
        SakuyaObject *object = pool_04.acquire(&local.handle_token);
        object->handle_token_334 = local.handle_token;

        CollisionListNode *sentinel = linked_objects_54.sentinel;
        local.object = object;
        CollisionListNode *node = create_collision_list_node(
            sentinel,
            sentinel->previous,
            reinterpret_cast<void **>(&local.object));
        linked_objects_54.std_list_incsize_pointer(1);
        sentinel->previous = node;
        node->previous->next = node;
    }
    return release_all_tracked_objects();
}

} // namespace th105
