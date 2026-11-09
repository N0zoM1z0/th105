#include "ui/TitleScene.hpp"

namespace th105 {

extern "C" void *__cdecl get_combined_menu_input();
unsigned int get_session_setup_option();
int get_game_mode();
extern "C" const char title_base_path[];
extern "C" const char title_menu_item_path[];
extern "C" const char title_design_path[];

CTitle::CTitle()
{
    unsigned int width;
    unsigned int height;

    {
        unsigned int handle1;
        texture_08.value = *g_title_resource_manager.load_texture(
            &handle1, title_base_path, &width, &height);
        color_0c.set_texture(texture_08.value, 0, 0, 640, 480);
    }

    {
        unsigned int handle2;
        texture_a0.value = *g_title_resource_manager.load_texture(
            &handle2, title_menu_item_path, &width, &height);
        color_a4.set_texture_options(
            texture_a0.value, 0, 0, width, 16, width >> 1, 0);
        color_138.set_texture_options(
            texture_a0.value, 0, 16, width, 24, width >> 1, 0);
    }

    design_1dc.load(title_design_path);

    void *input = get_combined_menu_input();
    if (input)
        cursor_210.input_counter = reinterpret_cast<int *>(
            reinterpret_cast<unsigned char *>(input) + 0x3C);
    else
        cursor_210.input_counter = 0;
    cursor_210.selection = 0;
    cursor_210.window_start = 0;
    cursor_210.page_size = 0;
    cursor_210.item_count = 12;

    for (int i = 0; i < 12; ++i) {
        design_1dc.find_object(&menu_items_224[i], i + 100);
        menu_item_wave_offsets[i] = 0.0f;
    }

    reserved_0284 = 0;
    menu_item_wave_counter = 0;

    if (get_session_setup_option() == 2 && get_game_mode() != 6) {
        cursor_210.selection = 6;
    } else {
        switch (get_game_mode()) {
        case 0: cursor_210.selection = 0; break;
        case 1: cursor_210.selection = 1; break;
        case 2: cursor_210.selection = 2; break;
        case 3: cursor_210.selection = 3; break;
        case 4:
        case 5:
        case 6: cursor_210.selection = 4; break;
        case 8: cursor_210.selection = 5; break;
        case 7: cursor_210.selection = 8; break;
        default: break;
        }
    }
}

}
