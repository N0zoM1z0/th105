#include "Menu.hpp"

namespace th105 {

// Narrow current-target view of the shared menu cursor sprite.  The object
// base and the +0x88/+0x8C scale fields are independently target-backed; the
// rest of the concrete sprite layout remains intentionally unresolved here.
struct MenuCursorSpriteView {
    unsigned char reserved_00[0x88];
    float scale_x_88;
    float scale_y_8c;

    void render(float x, float y);
};

extern MenuCursorSpriteView g_menu_cursor_sprite;

void Menu::render_cursor(float x, float y, float scale)
{
    g_menu_cursor_sprite.scale_x_88 = scale * (1.0 / 512.0);
    g_menu_cursor_sprite.scale_y_8c = 1.0f;
    g_menu_cursor_sprite.render(x, y);
}

} // namespace th105
