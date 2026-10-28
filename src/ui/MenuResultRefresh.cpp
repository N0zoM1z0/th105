#include "ResultMenu.hpp"

#include "../input/InputManager.hpp"

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);
extern "C" const char scenario_stand_path_format[];
extern "C" const char *__cdecl get_scenario_name(int scenario_id);
extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {

struct ResultTextureCall {
    TextureHandleResult load_texture(const char *, unsigned *, unsigned *);
};

void CMenuResult::refresh_selected_character()
{
    char path[260];

    g_title_resource_manager.release_title_resource_handle(texture_004);
    texture_004 = 0;
    if (selected_character_0c4 != 15) {
        wsprintfA(
            path,
            scenario_stand_path_format,
            get_scenario_name(selected_character_0c4));
        texture_004 = reinterpret_cast<ResultTextureCall *>(&g_title_resource_manager)
            ->load_texture(path, 0, 0).value;
        if (texture_004 != 0) {
            character_sprite_008.set_texture(
                texture_004, 0, 0, 0x200, 0x1E0);
            character_sprite_008.set_color(0xFF808080);
        }
    }

    if (!initialized_1040[selected_character_0c4]) {
        initialized_1040[selected_character_0c4] = true;
        ResultList *list = &results_0c8[selected_character_0c4];
        list->set_character_id(selected_character_0c4);
        list->populate();
    }

    if (results_0c8[selected_character_0c4].entry_count() != 0) {
        int count = results_0c8[selected_character_0c4].entry_count();
        if (g_active_menu_input != 0)
            result_cursor_108c.input_counter = &g_active_menu_input->hold.vertical;
        else
            result_cursor_108c.input_counter = 0;
        result_cursor_108c.selection = 0;
        result_cursor_108c.window_start = 0;
        result_cursor_108c.item_count = count;
        result_cursor_108c.page_size = 16;
    }
}

} // namespace th105
