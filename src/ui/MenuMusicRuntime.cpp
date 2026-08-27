#include "MenuMusic.hpp"

#include "ProfileMenu.hpp"
#include "../config/ScoreData.hpp"
#include "../input/InputManager.hpp"

#include <set>

extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);
extern "C" void __cdecl play_bgm(const char *path);
extern "C" th105::CInputManager *g_active_menu_input;
extern "C" const char menu_music_design_path[];
extern "C" const char title_bgm_path[];

namespace th105 {

void __cdecl install_menu_object(void *object);

struct ScoreMusicLookupView {
    unsigned char unknown_000[0x44];
    std::set<unsigned> path_hashes_044;

    bool contains_bgm_path(const char *path);
};

CMenuMusic::CMenuMusic()
{
    design_0e0.load(menu_music_design_path);
    design_0e0.bind_object_alt(&row_anchor_114, 100);
    row_anchor_114->enabled = true;
    guide_144.load(21);
    guide_144.visible = true;
    music_list_004.populate();

    if (music_list_004.item_count() != 0) {
        CInputManager *input = g_active_menu_input;
        if (input != 0)
            cursors_11c[0].input_counter = &input->hold.horizontal;
        else
            cursors_11c[0].input_counter = 0;
        cursors_11c[0].selection = 0;
        cursors_11c[0].window_start = 0;
        cursors_11c[0].item_count = 2;
        cursors_11c[0].page_size = 0;

        if (input != 0)
            cursors_11c[1].input_counter = &input->hold.vertical;
        else
            cursors_11c[1].input_counter = 0;
        cursors_11c[1].selection = 0;
        cursors_11c[1].window_start = 0;
        cursors_11c[1].item_count = 16;
        cursors_11c[1].page_size = 0;
    }
}

CMenuMusic::~CMenuMusic()
{
    music_list_004.shutdown();
    design_0e0.virtual_cleanup();
}

bool CMenuMusic::update_primary()
{
    HoldCounters *input = &g_active_menu_input->hold;
    MenuCursorState *cursor = cursors_11c;
    unsigned char row_change =
        static_cast<unsigned char>(cursor[1].update());
    row_change += row_change;
    const int zero = 0;
    if (cursor[0].update() | row_change) {
        if (cursors_11c[1].selection == 15)
            cursors_11c[0].selection = zero;
        dispatch_indexed_event(0x27);
    }

    if (input->buttons[0] == 1) {
        unsigned index = static_cast<unsigned>(
            cursors_11c[1].selection + 16 * cursors_11c[0].selection);
        const std::string &path = music_list_004.paths_b4.at(index);
        if (reinterpret_cast<ScoreMusicLookupView *>(get_score_data())
                ->contains_bgm_path(path.c_str()))
            play_bgm(music_list_004.paths_b4.at(index).c_str());
    } else if (input->buttons[2] == 1) {
        dispatch_indexed_event(0x28);
        install_menu_object(new CProfileMenu());
    } else if (input->buttons[1] == 1 ||
               is_menu_initial_press(1, zero, zero, zero)) {
        dispatch_indexed_event(0x29);
        play_bgm(title_bgm_path);
        return false;
    }
    return true;
}

bool CMenuMusic::update()
{
    guide_144.update();
    if (music_list_004.item_count() == 0)
        return false;
    return update_primary();
}

void CMenuMusic::render()
{
    if (music_list_004.item_count() == 0)
        return;

    const float left_x = static_cast<float>(
        static_cast<double>(row_anchor_114->x) + 4.0);
    const float top_y = row_anchor_114->y;
    const float cursor_x = static_cast<float>(
        static_cast<double>(cursors_11c[0].selection) * 256.0 +
        static_cast<double>(row_anchor_114->x));
    const float cursor_y = static_cast<float>(
        static_cast<double>(cursors_11c[1].selection) * 16.0 +
        static_cast<double>(row_anchor_114->y));
    render_cursor(cursor_x, cursor_y, 256.0f);

    const float right_x = static_cast<float>(
        static_cast<double>(left_x) + 256.0);
    for (unsigned int row = 0; row < 16; ++row) {
        const float y = static_cast<float>(
            static_cast<float>(row) * 16.0 +
            static_cast<double>(top_y));
        music_list_004.render_item(left_x, y, row);
        music_list_004.render_item(right_x, y, row + 16);
    }

    design_0e0.render();
    guide_144.render();
}

} // namespace th105
