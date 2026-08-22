#include "EffectSprite.hpp"

#include <string.h>

float __cdecl lookup_orientation_sine_quantized_abs(float phase);
float __cdecl lookup_orientation_cosine_quantized_abs(float phase);


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


void CSpriteEx::rotate_xyz(
    float x_angle, float y_angle, float z_angle,
    float pivot_x, float pivot_y, float pivot_z)
{
    if (z_angle) {
        float cosine = lookup_orientation_cosine_quantized_abs(z_angle);
        float sine = lookup_orientation_sine_quantized_abs(z_angle);

        float y0 = working_quad_0b0[0].y - pivot_y;
        float x0 = working_quad_0b0[0].x - pivot_x;
        working_quad_0b0[0].y = y0 * cosine + x0 * sine + pivot_y;
        working_quad_0b0[0].x = x0 * cosine + pivot_x - y0 * sine;

        float y1 = working_quad_0b0[1].y - pivot_y;
        float x1 = working_quad_0b0[1].x - pivot_x;
        working_quad_0b0[1].y = x1 * sine + pivot_y + y1 * cosine;
        working_quad_0b0[1].x = x1 * cosine + pivot_x - y1 * sine;

        float y2 = working_quad_0b0[2].y - pivot_y;
        float x2 = working_quad_0b0[2].x - pivot_x;
        working_quad_0b0[2].y = x2 * sine + pivot_y + y2 * cosine;
        working_quad_0b0[2].x = x2 * cosine + pivot_x - y2 * sine;

        float y3 = working_quad_0b0[3].y - pivot_y;
        float x3 = working_quad_0b0[3].x - pivot_x;
        working_quad_0b0[3].y = pivot_y + x3 * sine + y3 * cosine;
        working_quad_0b0[3].x = pivot_x + cosine * x3 - y3 * sine;
    }

    if (y_angle) {
        float cosine = lookup_orientation_cosine_quantized_abs(y_angle);
        float sine = lookup_orientation_sine_quantized_abs(y_angle);

        float x0 = working_quad_0b0[0].x - pivot_x;
        float z0 = working_quad_0b0[0].z - pivot_z;
        working_quad_0b0[0].x = x0 * cosine + z0 * sine + pivot_x;
        working_quad_0b0[0].z = z0 * cosine + pivot_z - x0 * sine;

        float x1 = working_quad_0b0[1].x - pivot_x;
        float z1 = working_quad_0b0[1].z - pivot_z;
        working_quad_0b0[1].x = z1 * sine + pivot_x + x1 * cosine;
        working_quad_0b0[1].z = z1 * cosine + pivot_z - x1 * sine;

        float x2 = working_quad_0b0[2].x - pivot_x;
        float z2 = working_quad_0b0[2].z - pivot_z;
        working_quad_0b0[2].x = z2 * sine + pivot_x + x2 * cosine;
        working_quad_0b0[2].z = z2 * cosine + pivot_z - x2 * sine;

        float x3 = working_quad_0b0[3].x - pivot_x;
        float z3 = working_quad_0b0[3].z - pivot_z;
        working_quad_0b0[3].x = pivot_x + z3 * sine + x3 * cosine;
        working_quad_0b0[3].z = pivot_z + cosine * z3 - x3 * sine;
    }

    if (x_angle) {
        float cosine = lookup_orientation_cosine_quantized_abs(x_angle);
        float sine = lookup_orientation_sine_quantized_abs(x_angle);

        float y0 = working_quad_0b0[0].y - pivot_y;
        float z0 = working_quad_0b0[0].z - pivot_z;
        working_quad_0b0[0].y = y0 * cosine + z0 * sine + pivot_y;
        working_quad_0b0[0].z = z0 * cosine + pivot_z - y0 * sine;

        float y1 = working_quad_0b0[1].y - pivot_y;
        float z1 = working_quad_0b0[1].z - pivot_z;
        working_quad_0b0[1].y = z1 * sine + pivot_y + y1 * cosine;
        working_quad_0b0[1].z = z1 * cosine + pivot_z - y1 * sine;

        float y2 = working_quad_0b0[2].y - pivot_y;
        float z2 = working_quad_0b0[2].z - pivot_z;
        working_quad_0b0[2].y = z2 * sine + pivot_y + y2 * cosine;
        working_quad_0b0[2].z = z2 * cosine + pivot_z - y2 * sine;

        float y3 = working_quad_0b0[3].y - pivot_y;
        float z3 = working_quad_0b0[3].z - pivot_z;
        working_quad_0b0[3].y = pivot_y + z3 * sine + y3 * cosine;
        working_quad_0b0[3].z = pivot_z + cosine * z3 - y3 * sine;
    }
}
