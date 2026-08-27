#pragma once

class CSpriteEx;

namespace th105 {

struct BattleBackgroundLayoutRenderView {
    unsigned char unknown_00[0x0c];
    float offset_x_0c;
    float offset_y_10;
    float scale_14;

    void transform_sprite(CSpriteEx *sprite);
};

struct BattleObjectRenderEntry {
    virtual ~BattleObjectRenderEntry();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void render_sprite(CSpriteEx *sprite);
};

struct BattleObjectManagerRenderView {
    void dispatch_render_sprite(CSpriteEx *sprite);
};

extern BattleBackgroundLayoutRenderView g_battle_background_layout;
extern BattleObjectManagerRenderView *g_battle_object_manager_render;

} // namespace th105
