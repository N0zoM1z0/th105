#pragma once

#include "EffectSprite.hpp"

#include <stddef.h>


class AnimationObjectBase {
public:
    CEffectSprite effect_000;
};


class Environment {
public:
    unsigned owner_field_000;
    unsigned char flag_004;
    unsigned char flag_005;
    unsigned char unknown_006[0x1e];
};


class AnimationObject : public AnimationObjectBase, public Environment {
public:
    AnimationObject()
    {
        pointer_154 = 0;
        flag_004 = 0;
        flag_005 = 0;
    }
    virtual ~AnimationObject();
    virtual void unknown_vslot_04();
    virtual void set_action(int action_id);
    virtual void unknown_vslot_0c();

    void *pointer_154;
};


// Constructor-owned AttackObject tail. Keeping the recovered assignment block
// as one inlined subobject preserves the target boundary: base initialization,
// derived vptr installation, then the tail's exact observed store order.
class AttackObjectState {
public:
    __forceinline AttackObjectState()
    {
        tail_1ac[0] = 0;
        tail_1ac[1] = 0;
        tail_1ac[2] = 0;
        tail_1ac[3] = 0;
        tail_1ac[4] = 0;
        tail_1ac[5] = 0;
        tail_1ac[6] = 0;
        tail_1ac[7] = 0;
        tail_1ac[8] = 0;
        tail_1ac[9] = 0;
        flag_057 = 0;
        flag_058 = 0;
        tail_1ac[10] = 0;
        frame_04c = 0;
        frame_03c = 0;
        result_028 = 0;
        result_slot_02c = 0;
        result_02e = 0;
        flag_030 = 0;
        flag_031 = 0;
        result_020 = 0;
        owner_010 = 0;
        related_014 = 0;
        related_018 = 0;
        table_index_024 = -1;
    }

    unsigned char unknown_000[0x08];
    unsigned owner_field_008;
    unsigned char unknown_00c[0x04];
    void *owner_010;
    void *related_014;
    void *related_018;
    short value_01c;
    short maximum_01e;
    unsigned result_020;
    signed char table_index_024;
    unsigned char unknown_025[0x03];
    unsigned result_028;
    unsigned char result_slot_02c;
    unsigned char unknown_02d;
    unsigned short result_02e;
    unsigned char flag_030;
    unsigned char flag_031;
    unsigned char unknown_032[0x0a];
    void *frame_03c;
    unsigned char unknown_040[0x0c];
    void *frame_04c;
    unsigned char unknown_050[0x07];
    unsigned char flag_057;
    unsigned char flag_058;
    unsigned char unknown_059[0x153];
    unsigned tail_1ac[11];
};


class AttackObject : public AnimationObject {
public:
    AttackObject();
    virtual ~AttackObject();
    virtual void unknown_vslot_04();
    virtual void set_action(int action_id);
    virtual void unknown_vslot_0c();

    AttackObjectState state_158;
};


typedef char AnimationObjectBase_size_must_be_0x12c[
    sizeof(AnimationObjectBase) == 0x12c ? 1 : -1];
typedef char Environment_size_must_be_0x24[
    sizeof(Environment) == 0x24 ? 1 : -1];
typedef char AnimationObject_effect_offset_must_be_0x04[
    offsetof(AnimationObject, effect_000) == 0x04 ? 1 : -1];
typedef char AnimationObject_environment_flag_offset_must_be_0x134[
    offsetof(AnimationObject, flag_004) == 0x134 ? 1 : -1];
typedef char AnimationObject_pointer_offset_must_be_0x154[
    offsetof(AnimationObject, pointer_154) == 0x154 ? 1 : -1];
typedef char AnimationObject_size_must_be_0x158[
    sizeof(AnimationObject) == 0x158 ? 1 : -1];
typedef char AttackObjectState_size_must_be_0x1d8[
    sizeof(AttackObjectState) == 0x1d8 ? 1 : -1];
typedef char AttackObjectState_owner_field_offset_must_be_0x08[
    offsetof(AttackObjectState, owner_field_008) == 0x08 ? 1 : -1];
typedef char AttackObject_state_offset_must_be_0x158[
    offsetof(AttackObject, state_158) == 0x158 ? 1 : -1];
typedef char AttackObject_size_must_be_0x330[
    sizeof(AttackObject) == 0x330 ? 1 : -1];
