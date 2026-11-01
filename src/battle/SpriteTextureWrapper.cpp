#include "EffectSprite.hpp"

void CSpriteEx::set_texture(
    unsigned int handle,
    int x,
    int y,
    int width,
    int height)
{
    set_texture_options(
        handle, x, y, width, height, 0, 0);
}
