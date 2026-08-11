#include "RosterOwnedObjects.hpp"
#include "CharacterObject.hpp"


namespace th105 {

void RosterObjectManagerBase::release_all_tracked_objects()
{
    typedef std::list<CharacterObject *> TrackedObjectList;

    for (TrackedObjectList::iterator current = linked_objects_54.begin();
         current != linked_objects_54.end();
         ++current) {
        unsigned handle_token = (*current)->handle_token_004;
        pool_04.release_handle(handle_token);
    }
    linked_objects_54.clear();
}

} // namespace th105
