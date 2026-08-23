#include "characters/Sakuya.hpp"

namespace th105 {

static SakuyaObject *acquire_sakuya_for_tracked_object(SakuyaObjectPool *pool)
{
    unsigned handle_token = 0;
    SakuyaObject *object = pool->acquire(&handle_token);
    object->handle_token_004 = handle_token;
    return object;
}

static CharacterObject *acquire_sakuya_for_tracked_list(SakuyaObjectPool *pool)
{
    return reinterpret_cast<CharacterObject *>(
        acquire_sakuya_for_tracked_object(pool));
}

SakuyaObject *SakuyaObjectManagerBase::acquire_and_link_object()
{
    RosterObjectManagerBase *const manager =
        reinterpret_cast<RosterObjectManagerBase *>(this);
    SakuyaObject *object = acquire_sakuya_for_tracked_object(&pool_04);
    manager->linked_objects_54.push_back(
        reinterpret_cast<CharacterObject *>(object));
    return object;
}

void SakuyaObjectManagerBase::preallocate_object_pool(unsigned target_count)
{
    RosterObjectManagerBase *const manager =
        reinterpret_cast<RosterObjectManagerBase *>(this);
    if (manager->linked_objects_54.size() < target_count) {
        do {
            manager->linked_objects_54.push_back(
                acquire_sakuya_for_tracked_list(&pool_04));
        } while (manager->linked_objects_54.size() < target_count);
    }
    manager->release_all_tracked_objects();
}

} // namespace th105
