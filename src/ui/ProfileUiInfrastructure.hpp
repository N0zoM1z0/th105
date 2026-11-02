#pragma once

#include "Tile.hpp"

namespace th105 {

struct UiDesignObject;

// Current Profile UI callers prove one common method surface for the loader-zero
// design/list objects at 0x006FD048, 0x006FD07C, 0x006FD24C and 0x006FD294.
// No storage layout is asserted here: only independently observed member ABIs.
struct ProfileRenderListView {
    void load(const char *path);
    void bind_object_alt(UiDesignObject **result, int object_id);
    void clear();
    void set_color(unsigned int color);
    void render();
    void render_offset(float x, float y);
};

extern CSprite g_profile_message_sprite;
extern CSprite g_profile_character_background;
extern CSprite g_menu_cursor_sprite;
extern CTile g_profile_tile;

} // namespace th105
