#include "Menu.hpp"
#include "ProfileUiInfrastructure.hpp"

namespace th105 {

void Menu::render_cursor(float x, float y, float scale)
{
    g_menu_cursor_sprite.scale_x_88 = scale * (1.0 / 512.0);
    g_menu_cursor_sprite.scale_y_8c = 1.0f;
    g_menu_cursor_sprite.render(x, y);
}

} // namespace th105
