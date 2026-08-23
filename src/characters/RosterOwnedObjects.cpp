#include "characters/RosterOwnedObjects.hpp"

namespace th105 {

#define TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(FighterName)                    \
    static ::FighterName##Object *acquire_##FighterName##_for_tracked_object( \
            FighterName##ObjectPool *pool)                                    \
    {                                                                         \
        unsigned handle_token = 0;                                            \
        ::FighterName##Object *object = pool->acquire(&handle_token);         \
        reinterpret_cast<RosterOwnedObjectPrefix338 *>(object)                \
            ->handle_token_334 = handle_token;                                \
        return object;                                                        \
    }                                                                         \
                                                                              \
    static CharacterObject *acquire_##FighterName##_for_tracked_list(         \
            FighterName##ObjectPool *pool)                                    \
    {                                                                         \
        return reinterpret_cast<CharacterObject *>(                           \
            acquire_##FighterName##_for_tracked_object(pool));                \
    }

TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Reimu)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Marisa)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Alice)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Patchouli)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Youmu)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Remilia)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Yuyuko)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Yukari)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Suika)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Udonge)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Komachi)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Aya)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Iku)
TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST(Tenshi)

#undef TH105_DEFINE_ACQUIRE_FOR_TRACKED_LIST

#define TH105_DEFINE_ACQUIRE_AND_LINK(FighterName)                            \
    ::FighterName##Object *                                                   \
        FighterName##ObjectManagerBase::acquire_and_link_object()             \
    {                                                                         \
        RosterObjectManagerBase *const manager =                              \
            reinterpret_cast<RosterObjectManagerBase *>(this);                \
        ::FighterName##Object *object =                                       \
            acquire_##FighterName##_for_tracked_object(&pool_04);             \
        manager->linked_objects_54.push_back(                                 \
            reinterpret_cast<CharacterObject *>(object));                     \
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
        RosterObjectManagerBase *const manager =                              \
            reinterpret_cast<RosterObjectManagerBase *>(this);                \
        if (manager->linked_objects_54.size() < target_count) {               \
            do {                                                              \
                manager->linked_objects_54.push_back(                         \
                    acquire_##FighterName##_for_tracked_list(&pool_04));      \
            } while (manager->linked_objects_54.size() < target_count);       \
        }                                                                     \
        manager->release_all_tracked_objects();                               \
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
