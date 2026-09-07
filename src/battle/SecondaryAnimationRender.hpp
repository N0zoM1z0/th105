#pragma once

#include "battle/EffectSprite.hpp"

#include <deque>
#include <stddef.h>
#include <vector>

namespace th105 {

struct SecondaryAnimationPoint {
    float x;
    float y;

    SecondaryAnimationPoint()
    {
    }

    SecondaryAnimationPoint(float x_value, float y_value)
        : x(x_value), y(y_value)
    {
    }

    SecondaryAnimationPoint operator+(const SecondaryAnimationPoint &other) const
    {
        return SecondaryAnimationPoint(x + other.x, y + other.y);
    }

    SecondaryAnimationPoint operator-(const SecondaryAnimationPoint &other) const
    {
        return SecondaryAnimationPoint(x - other.x, y - other.y);
    }

    SecondaryAnimationPoint operator*(float scale) const
    {
        return SecondaryAnimationPoint(x * scale, y * scale);
    }

    SecondaryAnimationPoint &operator*=(float scale)
    {
        x *= scale;
        y *= scale;
        return *this;
    }

    SecondaryAnimationPoint &operator+=(const SecondaryAnimationPoint &other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    SecondaryAnimationPoint &operator-=(const SecondaryAnimationPoint &other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};

struct SecondaryAnimationOwnerRuntimeView {
    unsigned char reserved_000[0xec];
    float source_x_0ec;
    float source_y_0f0;
    unsigned char reserved_0f4[0x3c];
    std::vector<unsigned int> *texture_handles_130;
};

struct SecondaryAnimationFrameRuntimeView {
    unsigned char reserved_00[0x0a];
    short texture_index_0a;
    unsigned char reserved_0c[4];
    short texture_width_10;
    short texture_height_12;
};

class SecondaryAnimationRenderRuntimeView {
public:
    SecondaryAnimationRenderRuntimeView();
    ~SecondaryAnimationRenderRuntimeView();

    void initialize(
        SecondaryAnimationOwnerRuntimeView *owner,
        const SecondaryAnimationFrameRuntimeView *frame,
        float half_width,
        int subdivision_count,
        int band_count,
        int blend_mode);
    void update_secondary();
    void render_secondary();
    void set_vertex_color(unsigned int color);
    void set_runtime_flags(unsigned char render_enabled, unsigned char update_step)
    {
        render_enabled_24 = render_enabled;
        update_step_25 = update_step;
    }

private:
    SecondaryAnimationOwnerRuntimeView *owner_00;
    int subdivision_count_04;
    int band_count_08;
    int elapsed_0c;
    float half_width_10;
    int blend_mode_14;
    float texture_u_extent_18;
    float texture_v_extent_1c;
    unsigned int texture_handle_20;
    unsigned char render_enabled_24;
    unsigned char update_step_25;
    unsigned char reserved_26[2];
    std::deque<SecondaryAnimationPoint> source_points_28;
    std::deque<SecondaryAnimationPoint> points_3c;
    SpriteVertex28 *vertices_50;
};

typedef char SecondaryAnimationRenderRuntimeView_size[
    sizeof(SecondaryAnimationRenderRuntimeView) == 0x54 ? 1 : -1];
typedef char SecondaryAnimationOwnerRuntimeView_texture_handles_offset[
    offsetof(SecondaryAnimationOwnerRuntimeView, texture_handles_130) == 0x130 ? 1 : -1];
typedef char SecondaryAnimationFrameRuntimeView_texture_index_offset[
    offsetof(SecondaryAnimationFrameRuntimeView, texture_index_0a) == 0x0a ? 1 : -1];

} // namespace th105
