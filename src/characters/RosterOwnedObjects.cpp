#include "RosterOwnedObjects.hpp"

namespace th105 {

#define TH105_DEFINE_ACQUIRE_AND_LINK(FighterName)                            \
    ::FighterName##Object *                                                   \
        FighterName##ObjectManagerBase::acquire_and_link_object()             \
    {                                                                         \
        union LocalSlot {                                                      \
            unsigned handle_token;                                            \
            RosterOwnedObjectPrefix338 *object;                               \
        } local;                                                               \
                                                                              \
        local.handle_token = 0;                                               \
        ::FighterName##Object *object =                                       \
            pool_04.acquire(&local.handle_token);                             \
        reinterpret_cast<RosterOwnedObjectPrefix338 *>(object)                \
            ->handle_token_334 = local.handle_token;                          \
                                                                              \
        CollisionListNode *sentinel = linked_objects_54.sentinel;             \
        local.object = reinterpret_cast<RosterOwnedObjectPrefix338 *>(object); \
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

#define TH105_DEFINE_PREALLOCATE(FighterName)                                 \
    void FighterName##ObjectManagerBase::preallocate_object_pool(             \
            unsigned target_count)                                           \
    {                                                                         \
        while (linked_objects_54.count < target_count) {                     \
            union LocalSlot {                                                 \
                unsigned handle_token;                                        \
                RosterOwnedObjectPrefix338 *object;                           \
            } local;                                                          \
                                                                              \
            local.handle_token = 0;                                           \
            ::FighterName##Object *object =                                   \
                pool_04.acquire(&local.handle_token);                         \
            reinterpret_cast<RosterOwnedObjectPrefix338 *>(object)            \
                ->handle_token_334 = local.handle_token;                      \
                                                                              \
            CollisionListNode *sentinel = linked_objects_54.sentinel;         \
            local.object =                                                    \
                reinterpret_cast<RosterOwnedObjectPrefix338 *>(object);       \
            CollisionListNode *node = create_collision_list_node(             \
                sentinel,                                                     \
                sentinel->previous,                                           \
                reinterpret_cast<void **>(&local.object));                    \
            linked_objects_54.std_list_incsize_pointer(1);                    \
            sentinel->previous = node;                                        \
            node->previous->next = node;                                      \
        }                                                                     \
        reinterpret_cast<RosterObjectManagerBase *>(this)                    \
            ->release_all_tracked_objects();                                  \
    }

TH105_DEFINE_PREALLOCATE(Reimu)
TH105_DEFINE_PREALLOCATE(Marisa)
TH105_DEFINE_PREALLOCATE(Alice)
TH105_DEFINE_PREALLOCATE(Patchouli)
TH105_DEFINE_PREALLOCATE(Youmu)
TH105_DEFINE_PREALLOCATE(Remilia)
TH105_DEFINE_PREALLOCATE(Yuyuko)
TH105_DEFINE_PREALLOCATE(Yukari)
TH105_DEFINE_PREALLOCATE(Suika)
TH105_DEFINE_PREALLOCATE(Udonge)
TH105_DEFINE_PREALLOCATE(Komachi)
TH105_DEFINE_PREALLOCATE(Aya)
TH105_DEFINE_PREALLOCATE(Iku)
TH105_DEFINE_PREALLOCATE(Tenshi)

#undef TH105_DEFINE_PREALLOCATE

} // namespace th105
