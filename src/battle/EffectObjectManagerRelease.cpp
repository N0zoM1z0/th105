#include "EffectManager.hpp"
#include "EffectObjectHierarchy.hpp"

#include <list>

namespace {

// CollisionList retains the recovered owner layout. This view supplies the
// checked element type without introducing another callable manager class.
struct InfoEffectTrackedListView {
    virtual ~InfoEffectTrackedListView();
    CHandleManagerEx<InfoEffectObject> pool_004;
    std::list<EffectObjectBase *> objects_054;
};

typedef char CheckTrackedManagerSize[
    sizeof(InfoEffectTrackedListView) == 0x60 ? 1 : -1];
typedef char CheckTrackedListOffset[
    offsetof(InfoEffectTrackedListView, objects_054) == 0x54 ? 1 : -1];

} // namespace

template <>
void TObjectManagerBase<InfoEffectObject, EffectObjectBase>::release_all_tracked_objects()
{
    InfoEffectTrackedListView *manager =
        reinterpret_cast<InfoEffectTrackedListView *>(this);
    for (std::list<EffectObjectBase *>::iterator current =
             manager->objects_054.begin();
         current != manager->objects_054.end(); ++current) {
        unsigned const handle_token = (*current)->handle_token_004;
        handle_pool_04.release_handle(handle_token);
    }
    manager->objects_054.clear();
}
