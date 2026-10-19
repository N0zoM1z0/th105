#pragma once

#include "EffectSprite.hpp"

namespace th105 {
// ABI view of the already recovered407160 texture setup provider.
// Runtime callers do not construct this derived view.
class SpriteTextureSetupView : public CSpriteEx {
public:
    void set_texture_options(unsigned handle, int x, int y,
        int width, int height, int pivot_x, int pivot_y);
};
} // namespace th105
