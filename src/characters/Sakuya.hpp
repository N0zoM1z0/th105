#pragma once

#include "battle/Collision.hpp"
#include "OwnedObjectContainers.hpp"

#include <deque>
#include <stddef.h>

namespace th105 {

struct Sakuya;

struct SakuyaObject {
    unsigned char unknown_000[0xec];
    float x_ec;
    float y_f0;
    unsigned char unknown_0f4[0x10];
    signed char facing_104;
    unsigned char unknown_105[0x2b];
    unsigned field_130;
    unsigned char unknown_134[0x2c];
    unsigned field_160;
    unsigned char unknown_164[0x04];
    Sakuya *owner_168;
    SakuyaObject *related_16c;
    unsigned copied_related_field_170;
    unsigned char unknown_174[0x1c0];
    unsigned handle_token_334;
    unsigned char unknown_338[0x04];
    unsigned char field_33c;
    unsigned char unknown_33d[0x03];
    unsigned *copied_words_340;
    unsigned char unknown_344[0x04];
    Sakuya *owner_348;
    SakuyaObject *parent_34c;
    std::deque<SakuyaObject *> child_refs_350;
    unsigned char unknown_364[0x24];
};

struct SakuyaObjectPool {
    unsigned char unknown_00[0x50];

    SakuyaObject *acquire(unsigned *handle_token);
};

struct SakuyaObjectManagerBase {
    void *manager_vtable_00;
    SakuyaObjectPool pool_04;
    CollisionList linked_objects_54;

    SakuyaObject *acquire_and_link_object();
    CollisionListNode *preallocate_object_pool(unsigned target_count);
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
    offsetof(SakuyaObject, handle_token_334) == 0x334 ? 1 : -1];
typedef char CheckSakuyaObjectCopiedWordsOffset[
    offsetof(SakuyaObject, copied_words_340) == 0x340 ? 1 : -1];
typedef char CheckSakuyaObjectChildRefsOffset[
    offsetof(SakuyaObject, child_refs_350) == 0x350 ? 1 : -1];
typedef char CheckSakuyaObjectManagerBaseSize[
    sizeof(SakuyaObjectManagerBase) == 0x60 ? 1 : -1];
typedef char CheckSakuyaObjectManagerBaseListOffset[
    offsetof(SakuyaObjectManagerBase, linked_objects_54) == 0x54 ? 1 : -1];

} // namespace th105
