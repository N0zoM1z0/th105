#pragma once

namespace th105 {

struct CollisionListNode {
    CollisionListNode *next;
    CollisionListNode *previous;
    void *payload;
};

struct CollisionList {
    unsigned unknown_00;
    CollisionListNode *sentinel;
    unsigned count;
};

void * __cdecl create_collision_list_sentinel();
CollisionList * __fastcall initialize_collision_list(CollisionList *list);
CollisionListNode * __stdcall create_collision_list_node(
    CollisionListNode *next,
    CollisionListNode *previous,
    void **payload);

} // namespace th105
