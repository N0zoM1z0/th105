// JP1.06a 0x00457110. Typed handle publication and checked-list ownership.
// See docs/SYSTEM_EFFECT_TRACKED_ACQUIRE_2026_10_29.md.
#include "battle/SystemEffectManager.hpp"
#include "EffectManagerTrackedState.hpp"
#include <list>
namespace {
typedef EffectManagerTrackedState<SystemEffectObject, SystemEffectObjectBase> SystemEffectTrackedManagerView;
static SystemEffectObject *acquire_system_effect(CHandleManagerEx<SystemEffectObject> *pool)
{
    unsigned handle=0;
    SystemEffectObject *object=pool->acquire(&handle);
    object->handle_token_004=handle;
    return object;
}
}
template<>
SystemEffectObject *TObjectManagerBase<SystemEffectObject,SystemEffectObjectBase>::acquire_and_link_object()
{
    SystemEffectObject *object=acquire_system_effect(&handle_pool_04);
    reinterpret_cast<SystemEffectTrackedManagerView *>(this)->linked_objects_54.push_back(object);
    return object;
}
