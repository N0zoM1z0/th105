#include "TObjectManagerBase.hpp"
#include "CharacterObject.hpp"

#include <list>

namespace {

// The real owner retains CollisionList storage; this non-owning view supplies
// its observed checked-list element type without adding another callable owner.
template <typename ObjectType, typename BaseObjectType>
struct RosterTrackedListView {
    void *manager_vtable_00;
    CHandleManagerEx<ObjectType> pool_04;
    std::list<BaseObjectType *> linked_objects_54;
};

typedef RosterTrackedListView<ReimuObject, CharacterObject> RosterTrackedLayout;
typedef char CheckRosterTrackedLayoutSize[
    sizeof(RosterTrackedLayout) == 0x60 ? 1 : -1];
typedef char CheckRosterTrackedListOffset[
    offsetof(RosterTrackedLayout, linked_objects_54) == 0x54 ? 1 : -1];

} // namespace

template <typename ObjectType, typename BaseObjectType>
void TObjectManagerBase<ObjectType, BaseObjectType>::release_all_tracked_objects()
{
    typedef std::list<BaseObjectType *> TrackedObjectList;
    RosterTrackedListView<ObjectType, BaseObjectType> *manager =
        reinterpret_cast<RosterTrackedListView<ObjectType, BaseObjectType> *>(this);

    for (typename TrackedObjectList::iterator current = manager->linked_objects_54.begin();
         current != manager->linked_objects_54.end();
         ++current) {
        unsigned handle_token = (*current)->handle_token_004;
        handle_pool_04.release_handle(handle_token);
    }
    manager->linked_objects_54.clear();
}

#define TH105_INSTANTIATE_ROSTER_RELEASE(FighterName)                         \
    template void TObjectManagerBase<FighterName##Object, CharacterObject>:: \
        release_all_tracked_objects()

TH105_INSTANTIATE_ROSTER_RELEASE(Reimu);
TH105_INSTANTIATE_ROSTER_RELEASE(Marisa);
TH105_INSTANTIATE_ROSTER_RELEASE(Sakuya);
TH105_INSTANTIATE_ROSTER_RELEASE(Alice);
TH105_INSTANTIATE_ROSTER_RELEASE(Patchouli);
TH105_INSTANTIATE_ROSTER_RELEASE(Youmu);
TH105_INSTANTIATE_ROSTER_RELEASE(Remilia);
TH105_INSTANTIATE_ROSTER_RELEASE(Yuyuko);
TH105_INSTANTIATE_ROSTER_RELEASE(Yukari);
TH105_INSTANTIATE_ROSTER_RELEASE(Suika);
TH105_INSTANTIATE_ROSTER_RELEASE(Udonge);
TH105_INSTANTIATE_ROSTER_RELEASE(Komachi);
TH105_INSTANTIATE_ROSTER_RELEASE(Aya);
TH105_INSTANTIATE_ROSTER_RELEASE(Iku);
TH105_INSTANTIATE_ROSTER_RELEASE(Tenshi);

#undef TH105_INSTANTIATE_ROSTER_RELEASE
