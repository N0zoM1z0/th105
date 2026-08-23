#pragma once

#include "GuideOverlay.hpp"
#include "MenuCursor.hpp"
#include "UiPrimitives.hpp"

#include <stddef.h>

namespace th105 {

struct ConfigStateView {
    unsigned char reserved_00[0x64];
    int option_64;
    unsigned bgm_percent_68;
    unsigned se_percent_6c;
    unsigned char windowed_70;
    unsigned char option_71;
};

struct CMenuConfigUpdateView {
    void *vtable_000;
    ConfigStateView *config_004;
    GuideOverlay guide_008;
    bool option_b0;
    unsigned char reserved_b1[3];
    unsigned texture_b4;
    UiSprite94 sprites_b8[2];
    unsigned grid_width_1e0;
    int grid_height_1e4;
    unsigned char reserved_1e8[0x3c];
    UiDesignObject *items_224[6];
    UiDesignObject *option_objects_23c[4];
    UiDesignObject *window_objects_24c[4];
    UiDesignObject *option_toggle_objects_25c[2];
    MenuCursorState primary_264;
    MenuCursorState secondary_278;

    bool update();
    void update_secondary_for_primary(int primary);
};

typedef char CMenuConfigUpdate_primary_offset_must_be_0x264[
    offsetof(CMenuConfigUpdateView, primary_264) == 0x264 ? 1 : -1];
typedef char CMenuConfigUpdate_secondary_offset_must_be_0x278[
    offsetof(CMenuConfigUpdateView, secondary_278) == 0x278 ? 1 : -1];
typedef char CMenuConfigUpdate_size_must_be_0x28c[
    sizeof(CMenuConfigUpdateView) == 0x28c ? 1 : -1];

} // namespace th105
