#include "ui/ProfileSubmenus.hpp"

namespace th105 {
void CProfileCharacterSelect::render()
{
    if (texture_04 != 0)
        stand_08.render(-64.0f, 0.0f);
    if (row_1c8.selection == item_count_284) {
        render_cursor(items_170[2 * item_count_284 - 1]->x,
            static_cast<float>(items_170[2 * item_count_284 - 1]->y + 8.0), 256.0f);
    } else {
        render_cursor(items_170[2 * row_1c8.selection + column_1b4.selection]->x,
            static_cast<float>(items_170[2 * row_1c8.selection + column_1b4.selection]->y + 8.0), 256.0f);
    }
    design_13c.render();
    render_profile_player_slot(player_9c, 0.0f, 0.0f);
    guide_1dc.render();
}
}
