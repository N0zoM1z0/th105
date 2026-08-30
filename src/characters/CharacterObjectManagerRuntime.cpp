#include "CharacterObjectManagerRuntime.hpp"

namespace th105 {

void CharacterManagerObjectRuntimeView::update_for_manager()
{
    if (related_fighter_16c->action_state_48c == 0 ||
        active_during_hitstop_344 != 0) {
        if (update_delay_186 != 0) {
            --update_delay_186;
            return;
        }

        update_slot_28();
        if (linked_runtime_338)
            linked_runtime_338->on_character_object_update();
    }
}

void CharacterManagerObjectRuntimeView::replace_parent(
    CharacterManagerObjectRuntimeView *old_parent,
    CharacterManagerObjectRuntimeView *new_parent)
{
    if (parent_170 == old_parent)
        parent_170 = new_parent;
}

void CharacterObjectManagerBaseRuntime::update_and_prune(
    void (CharacterManagerObjectRuntimeView::*method)())
{
    typedef std::list<CharacterManagerObjectRuntimeView *> ObjectList;

    for (ObjectList::iterator it = linked_objects_54.begin();
         it != linked_objects_54.end();) {
        ((*it)->*method)();
        if ((*it)->state_000 != 0) {
            ++it;
        } else {
            pool_04.release_handle((*it)->handle_004);
            it = linked_objects_54.erase(it);
        }
    }
}

void CharacterObjectManagerBaseRuntime::invoke_each(
    int (CharacterManagerObjectRuntimeView::*method)())
{
    typedef std::list<CharacterManagerObjectRuntimeView *> ObjectList;

    for (ObjectList::iterator it = linked_objects_54.begin();
         it != linked_objects_54.end(); ++it)
        ((*it)->*method)();
}

void CharacterObjectManagerBaseRuntime::invoke_each(
    void (CharacterManagerObjectRuntimeView::*method)(
        CharacterManagerObjectRuntimeView *,
        CharacterManagerObjectRuntimeView *),
    CharacterManagerObjectRuntimeView *old_parent,
    CharacterManagerObjectRuntimeView *new_parent)
{
    typedef std::list<CharacterManagerObjectRuntimeView *> ObjectList;

    for (ObjectList::iterator it = linked_objects_54.begin();
         it != linked_objects_54.end(); ++it)
        ((*it)->*method)(old_parent, new_parent);
}

void CharacterObjectManagerBaseRuntime::invoke_each(
    void (CharacterManagerObjectRuntimeView::*method)(signed char),
    signed char group)
{
    typedef std::list<CharacterManagerObjectRuntimeView *> ObjectList;

    for (ObjectList::iterator it = linked_objects_54.begin();
         it != linked_objects_54.end(); ++it)
        ((*it)->*method)(group);
}

void CharacterObjectManagerRuntime::release_all()
{
    CharacterObjectManagerBaseRuntime::release_all_tracked_objects();
}

void CharacterObjectManagerRuntime::invoke_slot_40_each()
{
    CharacterObjectManagerBaseRuntime::invoke_each(
        &CharacterManagerObjectRuntimeView::callback_slot_40);
}

void CharacterObjectManagerRuntime::update_objects()
{
    if (owner_64->related_fighter_170->action_state_48c == 0) {
        CharacterObjectManagerBaseRuntime::update_and_prune(
            &CharacterManagerObjectRuntimeView::update_for_manager);
    }
}

void CharacterObjectManagerRuntime::render_group_each(signed char group)
{
    CharacterObjectManagerBaseRuntime::invoke_each(
        &CharacterManagerObjectRuntimeView::render_group_callback, group);
}

void CharacterObjectManagerRuntime::invoke_slot_30_each()
{
    CharacterObjectManagerBaseRuntime::invoke_each(
        &CharacterManagerObjectRuntimeView::callback_slot_30);
}

void CharacterObjectManagerRuntime::render_each()
{
    CharacterObjectManagerBaseRuntime::invoke_each(
        &CharacterManagerObjectRuntimeView::render_special);
}

void CharacterObjectManagerRuntime::replace_parent_each(
    CharacterManagerObjectRuntimeView *old_parent,
    CharacterManagerObjectRuntimeView *new_parent)
{
    CharacterObjectManagerBaseRuntime::invoke_each(
        &CharacterManagerObjectRuntimeView::replace_parent,
        old_parent,
        new_parent);
}

std::list<CharacterManagerObjectRuntimeView *> &
CharacterObjectManagerRuntime::objects()
{
    return linked_objects_54;
}

} // namespace th105
