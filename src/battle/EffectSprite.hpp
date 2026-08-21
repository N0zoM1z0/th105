#pragma once

#include "Collision.hpp"

#include <stddef.h>

class IColor {
public:
    IColor();
    virtual ~IColor() {}
    virtual void set_color(unsigned int color) = 0;
    virtual void set_vertex_colors(const unsigned int *colors) = 0;
    virtual void multiply_color(unsigned int color) = 0;
    unsigned int value_04;
};

struct SpriteVertex28 {
    float x;
    float y;
    float z;
    float rhw;
    unsigned int color;
    float u;
    float v;
};

class CSpriteBase : public IColor {
public:
    virtual ~CSpriteBase() {}
    virtual void set_color(unsigned int color);
    virtual void set_vertex_colors(const unsigned int *colors);
    virtual void multiply_color(unsigned int color);
    SpriteVertex28 vertices_08[4];
    unsigned int base_word_78;
    unsigned int base_word_7c;
};

class CSprite : public CSpriteBase {
public:
    CSprite();
    virtual ~CSprite();
    unsigned char copied_extension_080[0x14];
};

struct SpritePoint3 {
    float x;
    float y;
    float z;
};

class CSpriteEx : public CSpriteBase {
public:
    virtual ~CSpriteEx() {}
    void reset_transform();
    void translate(float x, float y, float z);
    void scale_x(float scale, float pivot);
    void scale_y(float scale, float pivot);
    void transform_six(float a, float b, float c, float d, float e, float f);
    void finalize_render();

    SpritePoint3 source_quad_080[4];
    SpritePoint3 working_quad_0b0[4];
    float extra_e0;
    float extra_e4;
};

class CEffectSprite : public CSpriteEx {
public:
    CEffectSprite();
    virtual ~CEffectSprite() {}
    float object_x_0e8;
    float object_y_0ec;
    unsigned char unknown_0f0[0x10];
    signed char object_facing_100;
    unsigned char unknown_101[0x03];
    float reset_zero_104;
    float reset_zero_108;
    unsigned int color_10c;
    int reset_zero_110;
    unsigned char unknown_114[0x04];
    float reset_one_118;
    float reset_one_11c;
    float reset_zero_120;
    float reset_zero_124;
    float reset_zero_128;
};

typedef char IColor_size_must_be_0x08[sizeof(IColor) == 0x08 ? 1 : -1];
typedef char SpriteVertex28_size_must_be_0x1c[sizeof(SpriteVertex28) == 0x1c ? 1 : -1];
typedef char CSpriteBase_size_must_be_0x80[sizeof(CSpriteBase) == 0x80 ? 1 : -1];
typedef char CSpriteBase_first_color_offset_must_be_0x18[offsetof(CSpriteBase, vertices_08) + offsetof(SpriteVertex28, color) == 0x18 ? 1 : -1];
typedef char CSprite_size_must_be_0x94[sizeof(CSprite) == 0x94 ? 1 : -1];
typedef char SpritePoint3_size_must_be_0x0c[sizeof(SpritePoint3) == 0x0c ? 1 : -1];
typedef char CSpriteEx_size_must_be_0xe8[sizeof(CSpriteEx) == 0xe8 ? 1 : -1];
typedef char CSpriteEx_source_quad_offset_must_be_0x80[offsetof(CSpriteEx, source_quad_080) == 0x80 ? 1 : -1];
typedef char CSpriteEx_working_quad_offset_must_be_0xb0[offsetof(CSpriteEx, working_quad_0b0) == 0xb0 ? 1 : -1];
typedef char CEffectSprite_observed_size_must_be_0x12c[sizeof(CEffectSprite) == 0x12c ? 1 : -1];
typedef char CEffectSprite_object_x_offset_must_be_0x0e8[offsetof(CEffectSprite, object_x_0e8) == 0x0e8 ? 1 : -1];
typedef char CEffectSprite_object_facing_offset_must_be_0x100[offsetof(CEffectSprite, object_facing_100) == 0x100 ? 1 : -1];
