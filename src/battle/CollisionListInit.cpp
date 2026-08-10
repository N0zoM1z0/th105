#include "CollisionList.hpp"

namespace th105 {

CollisionList * __fastcall initialize_collision_list(CollisionList *list)
{
    list->sentinel = static_cast<CollisionListNode *>(
        create_collision_list_sentinel());
    list->count = 0;
    return list;
}

} // namespace th105
