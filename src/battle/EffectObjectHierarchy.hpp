#pragma once

#include "characters/CharacterObject.hpp"

#include <stddef.h>

// Current 1.06a RTTI for CSelectObject and InfoEffectObject proves a shared
// completed-object hierarchy: polymorphic AnimationObject is the primary base
// at +0, while the non-polymorphic CObjectBase handle state is laid out at
// +0x158.  Keeping the source declaration order CObjectBase, AnimationObject
// preserves the observed base-construction order while VC8 still makes the
// polymorphic base primary in the physical object.
class EffectObjectBase : public CObjectBase, public AnimationObject {
public:
    EffectObjectBase() {}
    virtual ~EffectObjectBase();
    virtual void update_slot_28();

    unsigned unknown_160;
    int context_164;
    unsigned unknown_168;
    signed char render_layer_16c;
    unsigned char unknown_16d[3];

    void render_435280();
    void render_if_layer(signed char layer);
    void clear_context_if(int context);
};

class CSelectObject : public EffectObjectBase {
public:
    CSelectObject() {}
    virtual ~CSelectObject();
};

class InfoEffectObject : public EffectObjectBase {
public:
    InfoEffectObject() {}
    virtual ~InfoEffectObject();

    unsigned unknown_170;
    unsigned unknown_174;
};

typedef char EffectObjectBase_size_must_be_0x170[
    sizeof(EffectObjectBase) == 0x170 ? 1 : -1];
typedef char EffectObjectBase_state_offset_must_be_0x158[
    offsetof(EffectObjectBase, state_000) == 0x158 ? 1 : -1];
typedef char EffectObjectBase_handle_offset_must_be_0x15c[
    offsetof(EffectObjectBase, handle_token_004) == 0x15c ? 1 : -1];
typedef char EffectObjectBase_context_offset_must_be_0x164[
    offsetof(EffectObjectBase, context_164) == 0x164 ? 1 : -1];
typedef char EffectObjectBase_layer_offset_must_be_0x16c[
    offsetof(EffectObjectBase, render_layer_16c) == 0x16c ? 1 : -1];
typedef char CSelectObject_size_must_be_0x170[
    sizeof(CSelectObject) == 0x170 ? 1 : -1];
typedef char InfoEffectObject_size_must_be_0x178[
    sizeof(InfoEffectObject) == 0x178 ? 1 : -1];
