#pragma once

#include "battle/Collision.hpp"
#include "RosterObjectPools.hpp"

#include <stddef.h>

namespace th105 {

struct Sakuya;
typedef ::SakuyaObject SakuyaObject;

struct SakuyaObjectPool {
    SakuyaObjectPoolStorage storage_00;

    SakuyaObject *acquire(unsigned *handle_token);
};

struct SakuyaObjectManagerBase {
    void *manager_vtable_00;
    SakuyaObjectPool pool_04;
    CollisionList linked_objects_54;

    SakuyaObject *acquire_and_link_object();
    void preallocate_object_pool(unsigned target_count);
    CollisionListNode *release_all_tracked_objects();
};

struct SakuyaObjectManager {
    void *interface_vtable_00;
    SakuyaObjectManagerBase base_04;
    Sakuya *owner_64;

    SakuyaObjectManager(Sakuya *owner);
    SakuyaObject *spawn_object(
        SakuyaObject *parent,
        SakuyaObject *related,
        int action_id,
        float x,
        float y,
        signed char facing,
        unsigned char field_33c,
        const unsigned *copied_words,
        int copied_word_count);
};

// Partial derived view.  The target establishes only the fields below; the
// concrete class continues beyond this observed prefix.
struct Sakuya : Fighter {
    short field_730;
    short field_732;
    short field_734;
    short field_736;
    short field_738;
    unsigned char unknown_73a[0x02];
    float field_73c;
    float field_740;
    unsigned char unknown_744[0x08];
    float field_74c;
    unsigned char field_750;
    unsigned char unknown_751[0x03];
    unsigned char skill_cancel_754;
    unsigned char skill_cancel_755;
    unsigned char skill_cancel_756;
    unsigned char unknown_757;

    Sakuya(int base_argument);
    void on_action_changed();
    void handle_input_and_select_action();
};

typedef char CheckSakuyaField730Offset[
    offsetof(Sakuya, field_730) == 0x730 ? 1 : -1];
typedef char CheckSakuyaSkillCancel754Offset[
    offsetof(Sakuya, skill_cancel_754) == 0x754 ? 1 : -1];
typedef char CheckSakuyaObjectManagerSize[
    sizeof(SakuyaObjectManager) == 0x68 ? 1 : -1];
typedef char CheckSakuyaObjectManagerOwnerOffset[
    offsetof(SakuyaObjectManager, owner_64) == 0x64 ? 1 : -1];
typedef char CheckSakuyaObjectObservedSize[
    sizeof(SakuyaObject) == 0x388 ? 1 : -1];
typedef char CheckSakuyaObjectHandleTokenOffset[
    offsetof(SakuyaObject, handle_token_004) == 0x334 ? 1 : -1];
typedef char CheckSakuyaObjectCopiedWordsOffset[
    offsetof(SakuyaObject, copied_words_340) == 0x340 ? 1 : -1];
typedef char CheckSakuyaObjectChildRefsOffset[
    offsetof(SakuyaObject, child_refs_350) == 0x350 ? 1 : -1];
typedef char CheckSakuyaObjectManagerBaseSize[
    sizeof(SakuyaObjectManagerBase) == 0x60 ? 1 : -1];
typedef char CheckSakuyaObjectManagerBaseListOffset[
    offsetof(SakuyaObjectManagerBase, linked_objects_54) == 0x54 ? 1 : -1];

} // namespace th105
