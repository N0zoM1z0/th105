#include "CollisionList.hpp"

namespace th105 {

void * __cdecl operator_new(unsigned size);

void * __cdecl create_collision_list_sentinel()
{
    CollisionListNode *node =
        static_cast<CollisionListNode *>(operator_new(12));
    if (node != 0) {
        node->next = node;
    }
    if (&node->previous != 0) {
        node->previous = node;
    }
    return node;
}

CollisionListNode * __stdcall create_collision_list_node(
    CollisionListNode *next,
    CollisionListNode *previous,
    void **payload)
{
    CollisionListNode *node =
        static_cast<CollisionListNode *>(operator_new(12));
    if (node != 0) {
        node->next = next;
    }
    if (&node->previous != 0) {
        node->previous = previous;
    }
    if (&node->payload != 0) {
        node->payload = *payload;
    }
    return node;
}

} // namespace th105
