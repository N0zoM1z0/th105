#include "RosterOwnedObjects.hpp"

namespace th105 {

#define TH105_DEFINE_ACQUIRE_AND_LINK(FighterName)                            \
    RosterOwnedObjectPrefix338 *                                              \
        FighterName##ObjectManagerBase::acquire_and_link_object()             \
    {                                                                         \
        union LocalSlot {                                                      \
            unsigned handle_token;                                            \
            RosterOwnedObjectPrefix338 *object;                               \
        } local;                                                               \
                                                                              \
        local.handle_token = 0;                                               \
        RosterOwnedObjectPrefix338 *object =                                  \
            pool_04.acquire(&local.handle_token);                             \
        object->handle_token_334 = local.handle_token;                        \
                                                                              \
        CollisionListNode *sentinel = linked_objects_54.sentinel;             \
        local.object = object;                                                \
        CollisionListNode *node = create_collision_list_node(                 \
            sentinel,                                                        \
            sentinel->previous,                                              \
            reinterpret_cast<void **>(&local.object));                        \
        linked_objects_54.std_list_incsize_pointer(1);                        \
        sentinel->previous = node;                                            \
        node->previous->next = node;                                          \
        return object;                                                        \
    }

TH105_DEFINE_ACQUIRE_AND_LINK(Reimu)
TH105_DEFINE_ACQUIRE_AND_LINK(Marisa)
TH105_DEFINE_ACQUIRE_AND_LINK(Alice)
TH105_DEFINE_ACQUIRE_AND_LINK(Patchouli)
TH105_DEFINE_ACQUIRE_AND_LINK(Youmu)
TH105_DEFINE_ACQUIRE_AND_LINK(Remilia)
TH105_DEFINE_ACQUIRE_AND_LINK(Yuyuko)
TH105_DEFINE_ACQUIRE_AND_LINK(Yukari)
TH105_DEFINE_ACQUIRE_AND_LINK(Suika)
TH105_DEFINE_ACQUIRE_AND_LINK(Udonge)
TH105_DEFINE_ACQUIRE_AND_LINK(Komachi)
TH105_DEFINE_ACQUIRE_AND_LINK(Aya)
TH105_DEFINE_ACQUIRE_AND_LINK(Iku)
TH105_DEFINE_ACQUIRE_AND_LINK(Tenshi)

#undef TH105_DEFINE_ACQUIRE_AND_LINK

} // namespace th105
