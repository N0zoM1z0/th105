#pragma once

#include "battle/CollisionList.hpp"
#include "engine/CriticalSectionWrapper.hpp"

#include <stddef.h>

namespace th105 {

// Every roster-owned object exposes this prefix to its manager.  The complete
// allocation span is character-specific (Alice is 0x38c; the others are
// 0x388), so this view deliberately stops after the observed handle token.
struct RosterOwnedObjectPrefix338 {
    unsigned char unknown_000[0x334];
    unsigned handle_token_334;
};

typedef char CheckRosterOwnedObjectHandleTokenOffset[
    offsetof(RosterOwnedObjectPrefix338, handle_token_334) == 0x334 ? 1 : -1];
typedef char CheckRosterOwnedObjectPrefixSize[
    sizeof(RosterOwnedObjectPrefix338) == 0x338 ? 1 : -1];

// Common VC8 checked-container layout observed in every one of the fifteen
// normalized 519-byte pool acquire functions.  The first dword in each
// container is the checked-iterator proxy/allocator base.
struct CheckedPointerVector16 {
    unsigned proxy_or_base_00;
    RosterOwnedObjectPrefix338 **begin_04;
    RosterOwnedObjectPrefix338 **end_08;
    RosterOwnedObjectPrefix338 **capacity_0c;
};

struct CheckedUnsignedVector16 {
    unsigned proxy_or_base_00;
    unsigned *begin_04;
    unsigned *end_08;
    unsigned *capacity_0c;
};

struct CheckedUnsignedList12 {
    unsigned proxy_or_base_00;
    CollisionListNode *sentinel_04;
    unsigned count_08;
};

struct CharacterObjectPoolStorage {
    unsigned proxy_or_base_00;
    CheckedPointerVector16 slots_04;
    CheckedUnsignedVector16 generations_14;
    CheckedUnsignedList12 free_slots_24;
    unsigned generation_counter_30;
    CriticalSectionWrapper lock_34;
};

typedef char CheckCharacterObjectPoolStorageSize[
    sizeof(CharacterObjectPoolStorage) == 0x50 ? 1 : -1];
typedef char CheckCharacterObjectPoolGenerationCounterOffset[
    offsetof(CharacterObjectPoolStorage, generation_counter_30) == 0x30 ? 1 : -1];
typedef char CheckCharacterObjectPoolLockOffset[
    offsetof(CharacterObjectPoolStorage, lock_34) == 0x34 ? 1 : -1];

#define TH105_DECLARE_ROSTER_OBJECT_MANAGER(FighterName)                      \
    struct FighterName##ObjectPool {                                          \
        CharacterObjectPoolStorage storage_00;                               \
        RosterOwnedObjectPrefix338 *acquire(unsigned *handle_token);          \
    };                                                                        \
    struct FighterName##ObjectManagerBase {                                   \
        void *manager_vtable_00;                                              \
        FighterName##ObjectPool pool_04;                                      \
        CollisionList linked_objects_54;                                     \
        RosterOwnedObjectPrefix338 *acquire_and_link_object();                \
    };                                                                        \
    typedef char Check##FighterName##ObjectManagerBaseSize[                   \
        sizeof(FighterName##ObjectManagerBase) == 0x60 ? 1 : -1]

TH105_DECLARE_ROSTER_OBJECT_MANAGER(Reimu);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Marisa);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Alice);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Patchouli);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Youmu);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Remilia);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Yuyuko);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Yukari);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Suika);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Udonge);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Komachi);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Aya);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Iku);
TH105_DECLARE_ROSTER_OBJECT_MANAGER(Tenshi);

#undef TH105_DECLARE_ROSTER_OBJECT_MANAGER

} // namespace th105
