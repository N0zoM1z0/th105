#include "battle/BackgroundDerived.hpp"

namespace th105 {

BGCommon::BGCommon(int background_id, int variant)
    : BackgroundBase()
{
    initialize_common_4664a0(background_id, variant);
}

BG02::~BG02() {}
BG04::~BG04() {}
BG16::~BG16() {}
BGCommon::~BGCommon() {}

void BG02::slot_04() { ++state_64; }
void BG04::slot_04() { ++state_64; }
void BG16::slot_04() { ++state_64; }

void BG02::slot_08() {}
void BG02::slot_0c() {}
void BG04::slot_0c() {}
void BGCommon::slot_04() {}
void BGCommon::slot_08() {}
void BGCommon::slot_0c() {}

void BG04::slot_10() { render_base_sprites_4659e0(); }
void BG16::slot_10() { render_base_sprites_4659e0(); }
void BGCommon::slot_10() { render_base_sprites_4659e0(); }

void BG02::render_sprite(CSpriteEx *sprite)
{
    sprite->scale_x(1.0f);
    sprite->scale_y(0.30000001f);
    sprite->scale_z(1.0f);
    sprite->rotate_xyz(160.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    sprite->set_color(0x80000000u);
}

void BG04::render_sprite(CSpriteEx *sprite)
{
    sprite->scale_x(1.0f);
    sprite->scale_y(0.30000001f);
    sprite->scale_z(1.0f);
    sprite->rotate_xyz(160.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    sprite->set_color(0x80000000u);
}

void BGCommon::render_sprite(CSpriteEx *sprite)
{
    sprite->scale_x(1.0f);
    sprite->scale_y(0.30000001f);
    sprite->scale_z(1.0f);
    sprite->rotate_xyz(160.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    sprite->set_color(0x80000000u);
}

void BG16::render_sprite(CSpriteEx *sprite)
{
    sprite->scale_x(1.0f);
    sprite->scale_y(0.30000001f);
    sprite->scale_z(1.0f);
    sprite->rotate_xyz(160.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
    sprite->set_color(0x40ffffffu);
}

} // namespace th105
