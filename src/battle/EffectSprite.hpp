#pragma once

#include "Collision.hpp"

#include <stddef.h>

class IColor {
public:
    IColor() : value_04(0) {}
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
    float texture_width_78;
    float texture_height_7c;
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
    void commit_transform();
    void translate(float x, float y, float z);
    void scale_x(float scale);
    void scale_x(float scale, float pivot);
    void scale_y(float scale);
    void scale_y(float scale, float pivot);
    void scale_z(float scale);
    void scale_z(float scale, float pivot);
    void scale_xyz_pivots(
        float x_scale, float y_scale, float z_scale,
        float x_pivot, float y_pivot, float z_pivot);
    void rotate_xyz(
        float x_angle, float y_angle, float z_angle,
        float pivot_x, float pivot_y, float pivot_z);
    void transform_six(float a, float b, float c, float d, float e, float f);
    void finalize_render();
    void set_uv_size(float width, float height);
    void set_texture(
        unsigned int handle, int x, int y, int width, int height);

    SpritePoint3 source_quad_080[4];
    SpritePoint3 working_quad_0b0[4];
    float extra_e0;
    float extra_e4;
};

// Native background vector assignment4663E0 copies0xE8 elements and publishes
// this RTTI vtable. Animation position/action state belongs to its outer owner.
class CEffectSprite : public CSpriteEx {
public:
    virtual ~CEffectSprite() {}
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
typedef char CEffectSprite_size_must_be_0xe8[sizeof(CEffectSprite) == 0xe8 ? 1 : -1];
