#pragma once

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

struct ProfileSpriteView {
    void set_texture(
        unsigned int handle,
        int x,
        int y,
        unsigned int width,
        unsigned int height);
    void render(float x, float y);
};

struct ProfileTileView {
    void render(float x, float y, int column, int row);
};

struct MenuCursorSpriteView {
    void set_texture(
        unsigned int handle,
        int x,
        int y,
        unsigned int width,
        unsigned int height);
    void render(float x, float y);
};

} // namespace th105
