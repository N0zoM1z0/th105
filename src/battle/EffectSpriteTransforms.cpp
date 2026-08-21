#include "EffectSprite.hpp"

#include <string.h>


void CSpriteEx::reset_transform()
{
    memcpy(working_quad_0b0, source_quad_080, sizeof(source_quad_080));
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

void CSpriteEx::scale_x(float scale, float pivot)
{
    for (int i = 0; i < 4; ++i)
        working_quad_0b0[i].x =
            (working_quad_0b0[i].x - pivot) * scale + pivot;
}

void CSpriteEx::scale_y(float scale, float pivot)
{
    for (int i = 0; i < 4; ++i)
        working_quad_0b0[i].y =
            (working_quad_0b0[i].y - pivot) * scale + pivot;
}
