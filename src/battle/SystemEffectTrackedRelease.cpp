#include "battle/SystemEffectManager.hpp"

#include <list>

namespace {

// The shared owner still stores the recovered list layout as CollisionList.
// Expose its checked list type without constructing a second owner.
struct SystemEffectTrackedListView {
    virtual ~SystemEffectTrackedListView();
    CHandleManagerEx<SystemEffectObject> pool_004;
    std::list<SystemEffectObjectBase *> objects_054;
};

typedef char CheckTrackedManagerSize[
    sizeof(SystemEffectTrackedListView) == 0x60 ? 1 : -1];
typedef char CheckTrackedListOffset[
    offsetof(SystemEffectTrackedListView, objects_054) == 0x54 ? 1 : -1];

} // namespace

template <>
void TObjectManagerBase<SystemEffectObject, SystemEffectObjectBase>::release_all_tracked_objects()
{
    SystemEffectTrackedListView *manager =
        reinterpret_cast<SystemEffectTrackedListView *>(this);
    for (std::list<SystemEffectObjectBase *>::iterator it = manager->objects_054.begin();
         it != manager->objects_054.end(); ++it)
        handle_pool_04.release_handle((*it)->handle_token_004);
    manager->objects_054.clear();
}
