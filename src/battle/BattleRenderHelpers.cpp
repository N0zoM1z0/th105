#include "BattleRenderHelpers.hpp"
#include "EffectSprite.hpp"

#include <list>

namespace th105 {

void BattleBackgroundLayoutRenderView::transform_sprite(CSpriteEx *sprite)
{
    sprite->translate(offset_x_0c, offset_y_10, 0.0f);
    sprite->scale_x(scale_14);
    sprite->scale_y(scale_14);
}

void BattleObjectManagerRenderView::dispatch_render_sprite(CSpriteEx *sprite)
{
    std::list<BattleObjectRenderEntry *> &renderers =
        *reinterpret_cast<std::list<BattleObjectRenderEntry *> *>(
            reinterpret_cast<unsigned char *>(this) + 0x28);
    if (!renderers.empty())
        renderers.back()->render_sprite(sprite);
}

} // namespace th105
