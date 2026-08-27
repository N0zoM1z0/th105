#pragma once

#include "battle/BackgroundBase.hpp"

namespace th105 {

struct BattleBackgroundLayoutRenderView {
    unsigned char unknown_00[0x0c];
    float offset_x_0c;
    float offset_y_10;
    float scale_14;

    void transform_sprite(CSpriteEx *sprite);
};

struct BattleObjectManagerRenderView {
    void dispatch_render_sprite(CSpriteEx *sprite);
};

extern BattleBackgroundLayoutRenderView g_battle_background_layout;
extern BattleObjectManagerRenderView *g_battle_object_manager_render;

} // namespace th105
