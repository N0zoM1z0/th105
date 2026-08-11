#pragma once

#include "CharacterObject.hpp"
#include "RosterOwnedObjects.hpp"

#include <deque>
#include <stddef.h>


template <typename ObjectType, size_t TrailingSize>
struct RosterObjectTail {
    void *owner_348;
    ObjectType *parent_34c;
    std::deque<ObjectType *> child_refs_350;
    unsigned char unknown_364[TrailingSize];

    __forceinline RosterObjectTail()
    {
        parent_34c = 0;
    }
};

// The tail is a non-primary base, not a member: VC8 consequently constructs
// CharacterObject, initializes the tail, and only then installs the fighter
// object vptr, exactly as observed in both target allocation paths.
#define TH105_DEFINE_ROSTER_OBJECT(FighterName, TailBytes, ObjectSize)         \
    typedef RosterObjectTail<FighterName##Object, TailBytes>                  \
        FighterName##ObjectTail;                                              \
    class FighterName##Object : public CharacterObject,                       \
                                private FighterName##ObjectTail {             \
    public:                                                                    \
        __forceinline FighterName##Object()                                    \
        {                                                                      \
        }                                                                      \
    };                                                                         \
    typedef char FighterName##ObjectTail_size_must_match[                      \
        sizeof(FighterName##ObjectTail) == 0x1c + TailBytes ? 1 : -1];        \
    typedef char FighterName##Object_size_must_match[                          \
        sizeof(FighterName##Object) == ObjectSize ? 1 : -1]

TH105_DEFINE_ROSTER_OBJECT(Reimu, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Marisa, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Alice, 0x28, 0x38c);
TH105_DEFINE_ROSTER_OBJECT(Patchouli, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Youmu, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Remilia, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Yuyuko, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Yukari, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Suika, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Udonge, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Komachi, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Aya, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Iku, 0x24, 0x388);
TH105_DEFINE_ROSTER_OBJECT(Tenshi, 0x24, 0x388);

#undef TH105_DEFINE_ROSTER_OBJECT
