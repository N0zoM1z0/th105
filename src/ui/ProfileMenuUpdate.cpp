#include "ProfileMenu.hpp"

namespace th105 {

bool CProfileMenu::update()
{
    UiDesignObject **item = items_380;
    if (state_340 == 0) {
        int count = 7;
        do {
            (*item)->set_color(0xFFFFFFFF);
            ++item;
            --count;
        } while (count != 0);
    } else {
        int index = 0;
        do {
            if (cursor_39c.selection == index)
                (*item)->set_color(0xFFFFFFFF);
            else
                (*item)->set_color(0xFF808080);
            ++index;
            ++item;
        } while (index < 7);
    }

    GuideOverlay *guide = guides_5a4;
    int guide_count = 5;
    do {
        guide->update();
        guide->visible = false;
        ++guide;
        --guide_count;
    } while (guide_count != 0);

    switch (state_340) {
    case 0:
        return update_primary();
    case 1:
        return update_state_one();
    case 2:
        return update_state_two();
    case 4:
        return update_state_four();
    case 5:
        return update_state_five();
    case 6:
        return update_state_six();
    case 3:
        return update_state_three();
    default:
        return true;
    }
}

} // namespace th105
