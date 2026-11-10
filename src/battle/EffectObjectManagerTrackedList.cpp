#include "battle/EffectManager.hpp"
#include "EffectManagerTrackedState.hpp"

namespace {

struct EffectTrackedObjectPrefix160 {
    unsigned char reserved_000[0x15c];
    unsigned handle_token_15c;
};

typedef char CheckEffectTrackedObjectHandleOffset[
    offsetof(EffectTrackedObjectPrefix160, handle_token_15c) == 0x15c ? 1 : -1];
typedef char CheckEffectTrackedObjectPrefixSize[
    sizeof(EffectTrackedObjectPrefix160) == 0x160 ? 1 : -1];
template <typename ObjectType>
static ObjectType *acquire_effect_for_tracked_object(
    CHandleManagerEx<ObjectType> *pool)
{
    unsigned handle_token = 0;
    ObjectType *object = pool->acquire(&handle_token);
    reinterpret_cast<EffectTrackedObjectPrefix160 *>(object)
        ->handle_token_15c = handle_token;
    return object;
}

template <typename ObjectType, typename BaseObjectType>
static BaseObjectType *acquire_effect_for_tracked_list(
    CHandleManagerEx<ObjectType> *pool)
{
    return reinterpret_cast<BaseObjectType *>(
        acquire_effect_for_tracked_object(pool));
}

} // namespace

template <typename ObjectType, typename BaseObjectType>
ObjectType *TObjectManagerBase<ObjectType, BaseObjectType>::acquire_and_link_object()
{
    typedef EffectManagerTrackedState<ObjectType, BaseObjectType> ManagerView;
    ManagerView *const manager = reinterpret_cast<ManagerView *>(this);
    ObjectType *object = acquire_effect_for_tracked_object(&handle_pool_04);
    manager->linked_objects_54.push_back(
        reinterpret_cast<BaseObjectType *>(object));
    return object;
}

template <typename ObjectType, typename BaseObjectType>
void TObjectManagerBase<ObjectType, BaseObjectType>::preallocate_object_pool(
    unsigned target_count)
{
    typedef EffectManagerTrackedState<ObjectType, BaseObjectType> ManagerView;
    ManagerView *const manager = reinterpret_cast<ManagerView *>(this);
    if (manager->linked_objects_54.size() < target_count) {
        do {
            manager->linked_objects_54.push_back(
                acquire_effect_for_tracked_list<ObjectType, BaseObjectType>(
                    &handle_pool_04));
        } while (manager->linked_objects_54.size() < target_count);
    }
    release_all_tracked_objects();
}

#define TH105_INSTANTIATE_TRACKED_LIST(ObjectType) \
    template ObjectType *TObjectManagerBase<ObjectType, EffectObjectBase>::acquire_and_link_object(); \
    template void TObjectManagerBase<ObjectType, EffectObjectBase>::preallocate_object_pool(unsigned)

TH105_INSTANTIATE_TRACKED_LIST(CSelectObject);
TH105_INSTANTIATE_TRACKED_LIST(WeatherEffectObject);
TH105_INSTANTIATE_TRACKED_LIST(EffectObject);
TH105_INSTANTIATE_TRACKED_LIST(InfoEffectObject);

#undef TH105_INSTANTIATE_TRACKED_LIST
