#pragma once

#include "UiPrimitives.hpp"
#include "engine/Sprite.hpp"

namespace th105 {

struct GuideOverlay {
    bool visible;
    unsigned char reserved_01[3];
    DesignTextureHandle texture_04;
    CSprite sprite_08;
    float scroll_9c;
    float wrap_width_a0;
    unsigned char alpha_a4;
    unsigned char reserved_a5[3];

    GuideOverlay();
    ~GuideOverlay();
    void load(int guide_id);
    void update();
    void render();
};

typedef char GuideOverlay_size_must_be_0xa8[
    sizeof(GuideOverlay) == 0xA8 ? 1 : -1];

} // namespace th105
