#include "InfoComboRuntime.hpp"
#include "Collision.hpp"

namespace th105 {

void InfoComboResourceRuntimeView::render_combo_46a660(
    float x,
    float y,
    Fighter *fighter,
    std::deque<InfoComboEntry> *entries)
{
    value_60 = fighter->value_49a;
    value_5c = fighter->value_498 > 99 ? 99 : fighter->value_498;
    value_64 = static_cast<float>(fighter->scalar_494 * 100.0);
    value_68 = fighter->value_49c;

    float item_y = 0.0f;
    for (int i = 0; i < 6; ++i)
        items_44[i]->enabled_14 = 0;

    for (std::deque<InfoComboEntry>::iterator it = entries->begin();
         it != entries->end(); ++it) {
        items_44[it->item_index_08]->enabled_14 = 1;
        items_44[it->item_index_08]->x_04 = it->value_00;
        items_44[it->item_index_08]->y_08 = item_y;
        item_y += 12.0f;
    }

    move_1c(x, y);
}

} // namespace th105
