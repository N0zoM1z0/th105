#pragma once

#include "engine/Sprite.hpp"

namespace th105 {

struct InfoLongRecord154Runtime {
    void *resource_000;
    CSprite primary_004;
    CSprite secondary_098;
    int timer_12c;
    unsigned char alpha_primary_130;
    unsigned char alpha_secondary_131;
    unsigned char mirrored_132;
    unsigned char reserved_133;
    float x_134;
    float y_138;
    float velocity_x_13c;
    float velocity_y_140;
    float scale_144;
    unsigned char reserved_148[4];
    unsigned char active_14c;
    unsigned char reserved_14d[3];
    int lifetime_150;

    void render_4325c0();
    void update_4327c0();
};

typedef char InfoLongRecord154Runtime_size_must_be_0x154[
    sizeof(InfoLongRecord154Runtime) == 0x154 ? 1 : -1];

} // namespace th105
