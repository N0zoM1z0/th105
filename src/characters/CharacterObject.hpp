#pragma once

#include "battle/AttackObject.hpp"

#include <stddef.h>


class CObjectBase {
public:
    CObjectBase()
    {
        handle_token_004 = 0;
        state_000 = 1;
    }

    unsigned state_000;
    unsigned handle_token_004;
};


class CharacterObject : public CObjectBase, public AttackObject {
public:
    CharacterObject();
    virtual ~CharacterObject();
    virtual void unknown_character_object_vslot_04();

    unsigned field_338;
    unsigned char field_33c;
    unsigned char unknown_33d[0x03];
    unsigned *copied_words_340;
    short field_344;
    short field_346;
};


typedef char CObjectBase_size_must_be_0x08[
    sizeof(CObjectBase) == 0x08 ? 1 : -1];
typedef char CharacterObject_state_offset_must_be_0x330[
    offsetof(CharacterObject, state_000) == 0x330 ? 1 : -1];
typedef char CharacterObject_handle_offset_must_be_0x334[
    offsetof(CharacterObject, handle_token_004) == 0x334 ? 1 : -1];
typedef char CharacterObject_size_must_be_0x348[
    sizeof(CharacterObject) == 0x348 ? 1 : -1];
