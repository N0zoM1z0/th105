#pragma once

#include "Collision.hpp"

#include <stddef.h>


// These classes are global in the target's decorated symbols. RTTI proves the
// primary-base chain CEffectSprite -> CSpriteEx -> CSpriteBase -> IColor; every
// layer shares the vptr and dword at +0x04.
class IColor {
public:
    IColor();
    virtual ~IColor();
    virtual void set_color();
    virtual void set_color_components();
    virtual void reset_color();

    unsigned int value_04;
};


class CSpriteBase : public IColor {
public:
    virtual ~CSpriteBase() {}
};


class CSpriteEx : public CSpriteBase {
public:
    virtual ~CSpriteEx() {}
};


class CEffectSprite : public CSpriteEx {
public:
    CEffectSprite();
    virtual ~CEffectSprite();

public:
    unsigned char unknown_008[0xe0];
    float object_x_0e8;
    float object_y_0ec;
    unsigned char unknown_0f0[0x10];
    signed char object_facing_100;
    unsigned char unknown_101[0x03];
    float reset_zero_104;
    float reset_zero_108;
    int reset_minus_one_10c;
    int reset_zero_110;
    unsigned char unknown_114[0x04];
    float reset_one_118;
    float reset_one_11c;
    float reset_zero_120;
    float reset_zero_124;
    float reset_zero_128;
};


typedef char IColor_size_must_be_0x08[sizeof(IColor) == 0x08 ? 1 : -1];
typedef char CSpriteBase_size_must_be_0x08[
    sizeof(CSpriteBase) == 0x08 ? 1 : -1];
typedef char CSpriteEx_size_must_be_0x08[
    sizeof(CSpriteEx) == 0x08 ? 1 : -1];
typedef char CEffectSprite_observed_size_must_be_0x12c[
    sizeof(CEffectSprite) == 0x12c ? 1 : -1];
typedef char CEffectSprite_object_x_offset_must_be_0x0e8[
    offsetof(CEffectSprite, object_x_0e8) == 0x0e8 ? 1 : -1];
typedef char CEffectSprite_object_facing_offset_must_be_0x100[
    offsetof(CEffectSprite, object_facing_100) == 0x100 ? 1 : -1];
