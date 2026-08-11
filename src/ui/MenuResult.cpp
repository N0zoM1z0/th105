#include "ResultMenu.hpp"

#include "../config/ScoreData.hpp"
#include "../input/InputManager.hpp"

#include <cstring>

extern "C" const char menu_result_design_path[];
extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {

CMenuResult::CMenuResult()
{
    g_scene_mode = 22;
    design_1050.load(menu_result_design_path);
    design_1050.bind_object_alt(&selection_1084, 100);
    selection_1084->enabled = true;

    available_characters_09c.clear();
    long character = 0;
    do {
        const unsigned char *score =
            reinterpret_cast<const unsigned char *>(get_score_data());
        if (score[0x1C + character] != 0)
            available_characters_09c.append(character);
        ++character;
    } while (character < 15);

    character_count_0ac = available_characters_09c.size();
    if (available_characters_09c.begin == 0 ||
        available_characters_09c.size() == 0)
        _invalid_parameter_noinfo();
    selected_character_0c4 = available_characters_09c.begin[0];

    character_cursor_0b0.input_counter =
        g_active_menu_input == 0
            ? 0
            : &g_active_menu_input->hold.horizontal;
    character_cursor_0b0.item_count = character_count_0ac;
    character_cursor_0b0.selection = 0;
    character_cursor_0b0.window_start = 0;
    character_cursor_0b0.page_size = 0;

    std::memset(initialized_1040, 0, sizeof(initialized_1040));
    guide_10a0.load(11);
    guide_10a0.visible = true;
    refresh_selected_character();
}

CMenuResult::~CMenuResult()
{
    g_title_resource_manager.release_title_resource_handle(texture_004);

    ResultList *list = results_0c8;
    int count = 15;
    do {
        list->clear_entries();
        ++list;
        --count;
    } while (count != 0);

    design_1050.virtual_cleanup();
}

bool CMenuResult::update()
{
    if (results_0c8[selected_character_0c4].entry_count() == 0)
        return false;
    return update_active();
}

void CMenuResult::render()
{
    if (texture_004 != 0)
        character_sprite_008.render(-64.0f, 0.0f);

    const float x = selection_1084->x + 128.0f;
    const float y = selection_1084->y;
    render_cursor(
        x,
        y + static_cast<float>(
                result_cursor_108c.selection - result_cursor_108c.window_start) *
                16.0f,
        512.0f);

    unsigned int row = 0;
    do {
        unsigned int index = result_cursor_108c.window_start + row;
        results_0c8[selected_character_0c4].render_row(
            x,
            y + static_cast<float>(row) * 16.0f,
            index);
        ++row;
    } while (row < 16);

    design_1050.render();
    guide_10a0.render();
}

} // namespace th105
