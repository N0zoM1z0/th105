#include "battle/SystemEffectManager.hpp"
#include "EffectManagerTrackedState.hpp"

#include <list>

typedef EffectManagerTrackedState<SystemEffectObject, SystemEffectObjectBase> SystemEffectTrackedListView;


template <>
void TObjectManagerBase<SystemEffectObject, SystemEffectObjectBase>::release_all_tracked_objects()
{
    SystemEffectTrackedListView *manager =
        reinterpret_cast<SystemEffectTrackedListView *>(this);
    for (std::list<SystemEffectObjectBase *>::iterator it = manager->linked_objects_54.begin();
         it != manager->linked_objects_54.end(); ++it)
        handle_pool_04.release_handle((*it)->handle_token_004);
    manager->linked_objects_54.clear();
}
