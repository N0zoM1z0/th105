#pragma once

#include "battle/CollisionList.hpp"

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

#define TH105_DECLARE_ROSTER_OBJECT_MANAGER(FighterName)                      \
    struct FighterName##ObjectPool {                                          \
        unsigned char unknown_00[0x50];                                      \
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
