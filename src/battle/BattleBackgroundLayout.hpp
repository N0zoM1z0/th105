#pragma once

class CSpriteEx;

namespace th105 {

// Current 1.06a global battle-setup/background layout object at 0x006FBCC0.
// The sprite-placement helper at 0x00427200 directly exercises these fields.
struct BattleBackgroundLayoutView {
    unsigned char reserved_00[0x14];
    float scale_14;
    float left_18;
    float top_1c;
    unsigned char reserved_20[0x10];
    float right_30;
    float bottom_34;
    unsigned char reserved_38[0x08];
    float runtime_scalar_40;

    void place_sprite(CSpriteEx *sprite, float x_scale, float y_scale);
    void set_runtime_scalar(float value);
};

extern BattleBackgroundLayoutView g_battle_background_layout;

} // namespace th105
