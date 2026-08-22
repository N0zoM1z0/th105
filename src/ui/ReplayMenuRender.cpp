#include "ReplayMenu.hpp"

namespace th105 {

struct ReplayProfileFooterView {
    void render_profile_menu_footer();
};

void CMenuReplay::render()
{
    if (!state_04) {
        UiDesignObject *item = items_f0[mode_cursor_fc.selection];
        render_cursor(
            item->x,
            static_cast<float>(item->y + 4.0),
            128.0f);
    } else {
        render_cursor(
            336.0f,
            static_cast<float>(
                static_cast<double>(
                    file_cursor_110.selection - file_cursor_110.window_start) *
                    16.0 +
                128.0),
            256.0f);
    }

    if (replay_list_08.item_count()) {
        for (unsigned int i = 0; i < 16; ++i) {
            float row = static_cast<float>(i);
            float y = static_cast<float>(
                static_cast<double>(row) * 16.0 + 128.0);
            replay_list_08.render_item(
                336.0f, y,
                i + static_cast<unsigned int>(file_cursor_110.window_start));
        }
    }

    design_bc.render();
    guides_124[0].render();
    guides_124[1].render();
    reinterpret_cast<ReplayProfileFooterView *>(this)
        ->render_profile_menu_footer();
}

} // namespace th105
