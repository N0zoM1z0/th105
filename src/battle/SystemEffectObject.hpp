#pragma once

#include "characters/CharacterObject.hpp"

#include <stddef.h>

class SystemEffectObjectBase : public CObjectBase, public AnimationObjectBase {
public:
    virtual ~SystemEffectObjectBase();
    virtual void update_state() = 0;
    virtual void reset_state() = 0;
    virtual void render_effect();

    unsigned int resource_handle_138;
};

class SystemEffectObject : public SystemEffectObjectBase {
public:
    virtual void update_state();
    virtual void reset_state();

    int mode_13c;
    int timer_140;

private:
    __forceinline unsigned char &alpha_byte()
    {
        return reinterpret_cast<unsigned char *>(&effect_000.color_10c)[3];
    }
};

typedef char SystemEffectObjectBase_size_must_be_0x13c[
    sizeof(SystemEffectObjectBase) == 0x13c ? 1 : -1];
typedef char SystemEffectObjectBase_resource_offset_must_be_0x138[
    offsetof(SystemEffectObjectBase, resource_handle_138) == 0x138 ? 1 : -1];
typedef char SystemEffectObject_size_must_be_0x144[
    sizeof(SystemEffectObject) == 0x144 ? 1 : -1];
typedef char SystemEffectObject_mode_offset_must_be_0x13c[
    offsetof(SystemEffectObject, mode_13c) == 0x13c ? 1 : -1];
typedef char SystemEffectObject_timer_offset_must_be_0x140[
    offsetof(SystemEffectObject, timer_140) == 0x140 ? 1 : -1];
