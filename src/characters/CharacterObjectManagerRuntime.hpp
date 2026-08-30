#pragma once

#include <list>
#include <stddef.h>

namespace th105 {

// Narrow target-backed views for the shared runtime lane behind all fifteen
// CharacterObjectManager<Fighter,Object> specializations.  The polymorphic
// animation base is primary at +0x000; the non-polymorphic handle state is
// consequently placed at +0x330 by VC8 despite being the second declared
// physical region in the original hierarchy.
struct CharacterManagerFighterRuntimeView {
    unsigned char unknown_000[0x48c];
    short action_state_48c;
};

struct CharacterManagerLinkedRuntimeView {
    void on_character_object_update();
};

class CharacterManagerAnimationRuntime330 {
public:
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void slot_1c();
    virtual void slot_20();
    virtual void slot_24();
    virtual int update_slot_28();
    virtual void slot_2c();
    virtual int callback_slot_30();
    virtual void slot_34();
    virtual void slot_38();
    virtual void slot_3c();
    virtual int callback_slot_40();

    unsigned char unknown_004[0x168];
    CharacterManagerFighterRuntimeView *related_fighter_16c;
    CharacterManagerAnimationRuntime330 *parent_170;
    unsigned char unknown_174[0x12];
    unsigned short update_delay_186;
    unsigned char unknown_188[0x1a8];
};

struct CharacterManagerHandleState8 {
    unsigned state_000;
    unsigned handle_004;
};

class CharacterManagerObjectRuntimeView
    : public CharacterManagerAnimationRuntime330,
      public CharacterManagerHandleState8 {
public:
    // Re-declaring the inherited virtuals on the concrete view gives a
    // CharacterObject member-pointer type.  Taking their addresses below then
    // makes VC8 emit the observed 5-byte virtual member-pointer thunks.
    virtual int update_slot_28();
    virtual int callback_slot_30();
    virtual int callback_slot_40();

    void update_for_manager();
    void replace_parent(
        CharacterManagerObjectRuntimeView *old_parent,
        CharacterManagerObjectRuntimeView *new_parent);
    int render_special();
    void render_group_callback(signed char group);

    CharacterManagerLinkedRuntimeView *linked_runtime_338;
    unsigned char render_group_33c;
    unsigned char unknown_33d[3];
    unsigned *copied_words_340;
    short active_during_hitstop_344;
    short unknown_346;
};

typedef char CheckCharacterManagerAnimationRuntime330[
    sizeof(CharacterManagerAnimationRuntime330) == 0x330 ? 1 : -1];
typedef char CheckCharacterManagerObjectRuntime348[
    sizeof(CharacterManagerObjectRuntimeView) == 0x348 ? 1 : -1];
typedef char CheckCharacterManagerRelatedFighterOffset[
    offsetof(CharacterManagerObjectRuntimeView, related_fighter_16c) == 0x16c
        ? 1 : -1];
typedef char CheckCharacterManagerParentOffset[
    offsetof(CharacterManagerObjectRuntimeView, parent_170) == 0x170 ? 1 : -1];
typedef char CheckCharacterManagerDelayOffset[
    offsetof(CharacterManagerObjectRuntimeView, update_delay_186) == 0x186
        ? 1 : -1];
typedef char CheckCharacterManagerStateOffset[
    offsetof(CharacterManagerObjectRuntimeView, state_000) == 0x330 ? 1 : -1];
typedef char CheckCharacterManagerHandleOffset[
    offsetof(CharacterManagerObjectRuntimeView, handle_004) == 0x334 ? 1 : -1];
typedef char CheckCharacterManagerLinkedRuntimeOffset[
    offsetof(CharacterManagerObjectRuntimeView, linked_runtime_338) == 0x338
        ? 1 : -1];
typedef char CheckCharacterManagerHitstopOffset[
    offsetof(CharacterManagerObjectRuntimeView, active_during_hitstop_344) ==
            0x344
        ? 1 : -1];

struct CharacterObjectPoolRuntime50 {
    unsigned char storage_000[0x50];

    void release_handle(unsigned handle);
};

class CharacterObjectManagerBaseRuntime {
public:
    void release_all_tracked_objects();
    void update_and_prune(
        void (CharacterManagerObjectRuntimeView::*method)());
    void invoke_each(
        int (CharacterManagerObjectRuntimeView::*method)());
    void invoke_each(
        void (CharacterManagerObjectRuntimeView::*method)(
            CharacterManagerObjectRuntimeView *,
            CharacterManagerObjectRuntimeView *),
        CharacterManagerObjectRuntimeView *old_parent,
        CharacterManagerObjectRuntimeView *new_parent);
    void invoke_each(
        void (CharacterManagerObjectRuntimeView::*method)(signed char),
        signed char group);

    void *manager_vtable_00;
    CharacterObjectPoolRuntime50 pool_04;
    std::list<CharacterManagerObjectRuntimeView *> linked_objects_54;
};

typedef char CheckCharacterObjectManagerBaseRuntime60[
    sizeof(CharacterObjectManagerBaseRuntime) == 0x60 ? 1 : -1];
typedef char CheckCharacterObjectManagerBaseListOffset[
    offsetof(CharacterObjectManagerBaseRuntime, linked_objects_54) == 0x54
        ? 1 : -1];

struct CharacterObjectManagerOwnerRuntimeView {
    unsigned char unknown_000[0x170];
    CharacterManagerFighterRuntimeView *related_fighter_170;
};

class ICharacterObjectManagerRuntime {
public:
    virtual ~ICharacterObjectManagerRuntime();
    virtual CharacterManagerObjectRuntimeView *spawn_object(
        CharacterManagerObjectRuntimeView *parent,
        CharacterManagerObjectRuntimeView *related,
        int action_id,
        float x,
        float y,
        signed char facing,
        unsigned char field_33c,
        const unsigned *copied_words,
        int copied_word_count);
    virtual void release_all();
    virtual void invoke_slot_40_each();
    virtual void update_objects();
    virtual void render_group_each(signed char group);
    virtual void invoke_slot_30_each();
    virtual void render_each();
    virtual void replace_parent_each(
        CharacterManagerObjectRuntimeView *old_parent,
        CharacterManagerObjectRuntimeView *new_parent);
    virtual std::list<CharacterManagerObjectRuntimeView *> &objects();
};

class CharacterObjectManagerRuntime
    : public ICharacterObjectManagerRuntime,
      public CharacterObjectManagerBaseRuntime {
public:
    virtual void release_all();
    virtual void invoke_slot_40_each();
    virtual void update_objects();
    virtual void render_group_each(signed char group);
    virtual void invoke_slot_30_each();
    virtual void render_each();
    virtual void replace_parent_each(
        CharacterManagerObjectRuntimeView *old_parent,
        CharacterManagerObjectRuntimeView *new_parent);
    virtual std::list<CharacterManagerObjectRuntimeView *> &objects();

    CharacterObjectManagerOwnerRuntimeView *owner_64;
};

typedef char CheckCharacterObjectManagerRuntime68[
    sizeof(CharacterObjectManagerRuntime) == 0x68 ? 1 : -1];
typedef char CheckCharacterObjectManagerOwnerOffset[
    offsetof(CharacterObjectManagerRuntime, owner_64) == 0x64 ? 1 : -1];

} // namespace th105
