#include "BattleBackgroundLayout.hpp"
#include "EffectSprite.hpp"

namespace th105 {

void BattleBackgroundLayoutView::place_sprite(
    CSpriteEx *sprite,
    float x_scale,
    float y_scale)
{
    float y = 420.0 / scale_14 - (bottom_34 + top_1c) * y_scale;
    float x = (640.0 - (right_30 + left_18)) * x_scale + 320.0 / scale_14;
    sprite->translate(x, y, 0.0f);
    sprite->scale_x(scale_14);
    sprite->scale_y(scale_14);
}

} // namespace th105
