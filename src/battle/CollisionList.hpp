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

    __forceinline CollisionList()
    {
        sentinel = buy_sentinel();
        count = 0;
    }

    CollisionListNode *buy_sentinel();
    CollisionListNode *create_node(
        CollisionListNode *next,
        CollisionListNode *previous,
        void **payload);
    void std_list_incsize_pointer(unsigned amount);
};

void * __cdecl create_collision_list_sentinel();
CollisionList * __fastcall initialize_collision_list(CollisionList *list);
CollisionListNode * __stdcall create_collision_list_node(
    CollisionListNode *next,
    CollisionListNode *previous,
    void **payload);

} // namespace th105
