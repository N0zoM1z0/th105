#include "EffectSprite.hpp"

#include <string.h>

namespace th105 {
double __cdecl lookup_orientation_sine_quantized_abs(float phase);
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
}

using th105::lookup_orientation_sine_quantized_abs;
using th105::lookup_orientation_cosine_quantized_abs;


void CSpriteEx::set_uv_size(float width, float height)
{
    const float u = width / texture_width_78;
    vertices_08[0].u = u;
    const float v = height / texture_height_7c;
    vertices_08[0].v = v;
    const float right = extra_e0 + u;
    vertices_08[1].u = right;
    vertices_08[1].v = v;
    vertices_08[2].u = u;
    const float bottom = extra_e4 + v;
    vertices_08[2].v = bottom;
    vertices_08[3].v = bottom;
    vertices_08[3].u = right;
}

void CSpriteEx::reset_transform()
{
    memcpy(working_quad_0b0, source_quad_080, sizeof(source_quad_080));
}


void CSpriteEx::commit_transform()
{
    memcpy(source_quad_080, working_quad_0b0, sizeof(working_quad_0b0));
}

void CSpriteEx::translate(float x, float y, float z)
{
    working_quad_0b0[0].x = x + working_quad_0b0[0].x;
    working_quad_0b0[0].y = working_quad_0b0[0].y + y;
    working_quad_0b0[0].z = working_quad_0b0[0].z + z;
    working_quad_0b0[1].x = working_quad_0b0[1].x + x;
    working_quad_0b0[1].y = working_quad_0b0[1].y + y;
    working_quad_0b0[1].z = working_quad_0b0[1].z + z;
    working_quad_0b0[2].x = working_quad_0b0[2].x + x;
    working_quad_0b0[2].y = working_quad_0b0[2].y + y;
    working_quad_0b0[2].z = working_quad_0b0[2].z + z;
    working_quad_0b0[3].x = x + working_quad_0b0[3].x;
    working_quad_0b0[3].y = y + working_quad_0b0[3].y;
    working_quad_0b0[3].z = z + working_quad_0b0[3].z;
}

void CSpriteEx::scale_x(float scale)
{
    working_quad_0b0[0].x = scale * working_quad_0b0[0].x;
    working_quad_0b0[1].x = working_quad_0b0[1].x * scale;
    working_quad_0b0[2].x = working_quad_0b0[2].x * scale;
    working_quad_0b0[3].x = scale * working_quad_0b0[3].x;
}

void CSpriteEx::scale_x(float scale, float pivot)
{
    for (int i = 0; i < 4; ++i)
        working_quad_0b0[i].x =
            (working_quad_0b0[i].x - pivot) * scale + pivot;
}

void CSpriteEx::scale_y(float scale)
{
    working_quad_0b0[0].y = scale * working_quad_0b0[0].y;
    working_quad_0b0[1].y = working_quad_0b0[1].y * scale;
    working_quad_0b0[2].y = working_quad_0b0[2].y * scale;
    working_quad_0b0[3].y = scale * working_quad_0b0[3].y;
}

void CSpriteEx::scale_y(float scale, float pivot)
{
    for (int i = 0; i < 4; ++i)
        working_quad_0b0[i].y =
            (working_quad_0b0[i].y - pivot) * scale + pivot;
}

void CSpriteEx::scale_z(float scale)
{
    working_quad_0b0[0].z = scale * working_quad_0b0[0].z;
    working_quad_0b0[1].z = working_quad_0b0[1].z * scale;
    working_quad_0b0[2].z = working_quad_0b0[2].z * scale;
    working_quad_0b0[3].z = scale * working_quad_0b0[3].z;
}

void CSpriteEx::scale_z(float scale, float pivot)
{
    for (int i = 0; i < 4; ++i)
        working_quad_0b0[i].z =
            (working_quad_0b0[i].z - pivot) * scale + pivot;
}


// Preserve the runtime floating-point environment for the rotation tests.
#pragma fenv_access(on)
void CSpriteEx::rotate_xyz(
    float x_angle, float y_angle, float z_angle,
    float pivot_x, float pivot_y, float pivot_z)
{
    float cosine, sine;
    float x, y, z;

    if (z_angle) {
        cosine = lookup_orientation_cosine_quantized_abs(z_angle);
        sine = lookup_orientation_sine_quantized_abs(z_angle);

        y = working_quad_0b0[0].y - pivot_y;
        x = working_quad_0b0[0].x - pivot_x;
        working_quad_0b0[0].y = y * cosine + (x * sine + pivot_y);
        working_quad_0b0[0].x = x * cosine + pivot_x - y * sine;

        y = working_quad_0b0[1].y - pivot_y;
        x = working_quad_0b0[1].x - pivot_x;
        working_quad_0b0[1].y = x * sine + pivot_y + y * cosine;
        working_quad_0b0[1].x = x * cosine + pivot_x - y * sine;

        y = working_quad_0b0[2].y - pivot_y;
        x = working_quad_0b0[2].x - pivot_x;
        working_quad_0b0[2].y = x * sine + pivot_y + y * cosine;
        working_quad_0b0[2].x = x * cosine + pivot_x - y * sine;

        y = working_quad_0b0[3].y - pivot_y;
        x = working_quad_0b0[3].x - pivot_x;
        working_quad_0b0[3].y = pivot_y + x * sine + y * cosine;
        working_quad_0b0[3].x = pivot_x + cosine * x - y * sine;
    }

    if (y_angle) {
        cosine = lookup_orientation_cosine_quantized_abs(y_angle);
        sine = lookup_orientation_sine_quantized_abs(y_angle);

        x = working_quad_0b0[0].x - pivot_x;
        z = working_quad_0b0[0].z - pivot_z;
        working_quad_0b0[0].x = x * cosine + (z * sine + pivot_x);
        working_quad_0b0[0].z = z * cosine + pivot_z - x * sine;

        x = working_quad_0b0[1].x - pivot_x;
        z = working_quad_0b0[1].z - pivot_z;
        working_quad_0b0[1].x = z * sine + pivot_x + x * cosine;
        working_quad_0b0[1].z = z * cosine + pivot_z - x * sine;

        x = working_quad_0b0[2].x - pivot_x;
        z = working_quad_0b0[2].z - pivot_z;
        working_quad_0b0[2].x = z * sine + pivot_x + x * cosine;
        working_quad_0b0[2].z = z * cosine + pivot_z - x * sine;

        x = working_quad_0b0[3].x - pivot_x;
        z = working_quad_0b0[3].z - pivot_z;
        working_quad_0b0[3].x = pivot_x + z * sine + x * cosine;
        working_quad_0b0[3].z = pivot_z + cosine * z - x * sine;
    }

    if (x_angle) {
        cosine = lookup_orientation_cosine_quantized_abs(x_angle);
        sine = lookup_orientation_sine_quantized_abs(x_angle);

        y = working_quad_0b0[0].y - pivot_y;
        z = working_quad_0b0[0].z - pivot_z;
        working_quad_0b0[0].y = y * cosine + (z * sine + pivot_y);
        working_quad_0b0[0].z = z * cosine + pivot_z - y * sine;

        y = working_quad_0b0[1].y - pivot_y;
        z = working_quad_0b0[1].z - pivot_z;
        working_quad_0b0[1].y = z * sine + pivot_y + y * cosine;
        working_quad_0b0[1].z = z * cosine + pivot_z - y * sine;

        y = working_quad_0b0[2].y - pivot_y;
        z = working_quad_0b0[2].z - pivot_z;
        working_quad_0b0[2].y = z * sine + pivot_y + y * cosine;
        working_quad_0b0[2].z = z * cosine + pivot_z - y * sine;

        y = working_quad_0b0[3].y - pivot_y;
        z = working_quad_0b0[3].z - pivot_z;
        working_quad_0b0[3].y = pivot_y + z * sine + y * cosine;
        working_quad_0b0[3].z = pivot_z + cosine * z - y * sine;
    }
}
#pragma fenv_access(off)
