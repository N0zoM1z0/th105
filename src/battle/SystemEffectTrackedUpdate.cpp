#include "battle/SystemEffectManager.hpp"
#include "EffectManagerTrackedState.hpp"
#include <list>
template<>
void TObjectManagerBase<SystemEffectObject,SystemEffectObjectBase>::update_and_prune(
    void (SystemEffectObjectBase::*method)())
{
    typedef std::list<SystemEffectObjectBase *> ObjectList;
    typedef EffectManagerTrackedState<SystemEffectObject, SystemEffectObjectBase> ManagerView;
    ObjectList &objects = reinterpret_cast<ManagerView *>(this)->linked_objects_54;
    ObjectList::iterator it = objects.begin();
    while (it != objects.end()) {
        ((*it)->*method)();
        if ((*it)->state_000 != 0) {
            ++it;
        } else {
            handle_pool_04.release_handle((*it)->handle_token_004);
            it = objects.erase(it);
        }
    }
}
