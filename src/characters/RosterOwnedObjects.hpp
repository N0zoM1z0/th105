#pragma once

#include "battle/CollisionList.hpp"
#include "engine/CriticalSectionWrapper.hpp"

#include <list>
#include <stddef.h>
#include <vector>


class ReimuObject;
class MarisaObject;
class AliceObject;
class PatchouliObject;
class YoumuObject;
class RemiliaObject;
class YuyukoObject;
class YukariObject;
class SuikaObject;
class UdongeObject;
class KomachiObject;
class AyaObject;
class IkuObject;
class TenshiObject;

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
typedef std::vector<unsigned> CheckedUnsignedVector16;
typedef std::list<unsigned> CheckedUnsignedList12;

template <typename ObjectType>
struct CharacterObjectPoolStorageT {
    unsigned proxy_or_base_00;
    std::vector<ObjectType *> slots_04;
    CheckedUnsignedVector16 generations_14;
    CheckedUnsignedList12 free_slots_24;
    unsigned generation_counter_30;
    CriticalSectionWrapper lock_34;
};

typedef CharacterObjectPoolStorageT<RosterOwnedObjectPrefix338>
    CharacterObjectPoolStorage;

typedef char CheckCharacterObjectPoolStorageSize[
    sizeof(CharacterObjectPoolStorage) == 0x50 ? 1 : -1];
typedef char CheckCharacterObjectPoolGenerationCounterOffset[
    offsetof(CharacterObjectPoolStorage, generation_counter_30) == 0x30 ? 1 : -1];
typedef char CheckCharacterObjectPoolLockOffset[
    offsetof(CharacterObjectPoolStorage, lock_34) == 0x34 ? 1 : -1];

#define TH105_DECLARE_ROSTER_OBJECT_MANAGER(FighterName)                      \
    typedef CharacterObjectPoolStorageT< ::FighterName##Object>               \
        FighterName##ObjectPoolStorage;                                       \
    struct FighterName##ObjectPool {                                          \
        FighterName##ObjectPoolStorage storage_00;                            \
        ::FighterName##Object *acquire(unsigned *handle_token);                \
    };                                                                        \
    struct FighterName##ObjectManagerBase {                                   \
        void *manager_vtable_00;                                              \
        FighterName##ObjectPool pool_04;                                      \
        CollisionList linked_objects_54;                                     \
        ::FighterName##Object *acquire_and_link_object();                     \
    };                                                                        \
    struct FighterName##ObjectManager {                                       \
        void *interface_vtable_00;                                            \
        FighterName##ObjectManagerBase base_04;                               \
        void *owner_64;                                                       \
        ::FighterName##Object *spawn_object(                                  \
            ::FighterName##Object *parent,                                    \
            ::FighterName##Object *related,                                   \
            int action_id, float x, float y, signed char facing,              \
            unsigned char field_33c, const unsigned *copied_words,            \
            int copied_word_count);                                           \
    };                                                                        \
    typedef char Check##FighterName##ObjectManagerBaseSize[                   \
        sizeof(FighterName##ObjectManagerBase) == 0x60 ? 1 : -1];             \
    typedef char Check##FighterName##ObjectManagerSize[                       \
        sizeof(FighterName##ObjectManager) == 0x68 ? 1 : -1]

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
