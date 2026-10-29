#include "AnimationRenderVirtuals.hpp"

namespace th105 {

void AnimationRenderObjectView::set_sprite_uv_size(float width, float height)
{
    sprite_004.sprite_000.set_uv_size(width, height);
}

} // namespace th105
