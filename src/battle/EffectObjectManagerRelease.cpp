#include "EffectManager.hpp"
#include "EffectManagerTrackedState.hpp"
#include "EffectObjectHierarchy.hpp"

#include <list>



template <>
void TObjectManagerBase<InfoEffectObject, EffectObjectBase>::release_all_tracked_objects()
{
    typedef EffectManagerTrackedState<InfoEffectObject, EffectObjectBase> ManagerView;
    ManagerView *manager = reinterpret_cast<ManagerView *>(this);
    for (std::list<EffectObjectBase *>::iterator current =
             manager->linked_objects_54.begin();
         current != manager->linked_objects_54.end(); ++current) {
        unsigned const handle_token = (*current)->handle_token_004;
        handle_pool_04.release_handle(handle_token);
    }
    manager->linked_objects_54.clear();
}
