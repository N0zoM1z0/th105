#include "AnimationRenderVirtuals.hpp"

namespace th105 {

void AnimationRenderObjectView::render_color_mode()
{
    switch (sprite_004.reset_zero_110) {
    case 0:
        sprite_004.finalize_render();
        return;
    case 1:
        reinterpret_cast<SpriteRenderEffectView *>(&sprite_004)->render_luma(
            0.299f, 0.587f, 0.114f);
        return;
    case 3:
        reinterpret_cast<SpriteRenderEffectView *>(&sprite_004)->render_alpha_rgb(
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[3]) / 255.0),
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[2]) / 255.0),
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[1]) / 255.0),
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[0]) / 255.0));
        return;
    case 4:
        reinterpret_cast<SpriteRenderEffectView *>(&sprite_004)->render_rgb(
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[2]) / 255.0),
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[1]) / 255.0),
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[0]) / 255.0));
        return;
    case 5:
        reinterpret_cast<SpriteRenderEffectView *>(&sprite_004)->render_luma_alpha(
            0.299f, 0.587f, 0.114f,
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[3]) / 255.0),
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[2]) / 255.0),
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[1]) / 255.0),
            static_cast<float>(static_cast<double>(sprite_004.unknown_114[0]) / 255.0));
        return;
    default:
        return;
    }
}

} // namespace th105
