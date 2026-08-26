#include "EffectSprite.hpp"

void CSpriteEx::scale_xyz_pivots(
    float x_scale, float y_scale, float z_scale,
    float x_pivot, float y_pivot, float z_pivot)
{
    scale_x(x_scale, x_pivot);
    scale_y(y_scale, y_pivot);
    scale_z(z_scale, z_pivot);
}
