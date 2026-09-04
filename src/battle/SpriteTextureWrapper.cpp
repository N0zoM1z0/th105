#include "EffectSprite.hpp"

namespace th105 {

struct CSpriteTextureOptionsView {
    void set_texture_options(
        unsigned int handle,
        int x,
        int y,
        int width,
        int height,
        int anchor_x,
        int anchor_y);
};

} // namespace th105

void CSpriteEx::set_texture(
    unsigned int handle,
    int x,
    int y,
    int width,
    int height)
{
    reinterpret_cast<th105::CSpriteTextureOptionsView *>(this)->set_texture_options(
        handle, x, y, width, height, 0, 0);
}
