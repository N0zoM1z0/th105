#include "Title.hpp"
#include "UiSelectionState.hpp"
#include "LoadingWatch.hpp"

extern "C" void __cdecl play_bgm(const char *path);
extern "C" void __cdecl clear_network_session();
extern "C" const char title_bgm_path[];
extern "C" float __cdecl lookup_orientation_cosine(int angle);

const char title_bgm_path[] = "data/bgm/op.ogg";
const unsigned int title_color_vtable_anchor[] = {0x0040AE80};

namespace th105 {

CTitle::~CTitle()
{
    g_title_resource_manager.release_title_resource_handle(texture_08);
    g_title_resource_manager.release_title_resource_handle(texture_a0);
    design_1dc.virtual_cleanup();
}

void CTitle::advance_menu_item_wave()
{
    ++menu_item_wave_counter;

    int offset = 0;
    float *destination = menu_item_wave_offsets;
    do {
        int phase = menu_item_wave_counter - offset;
        if (phase % 1080 > 720)
            *destination = 10.0 - lookup_orientation_cosine(phase % 360) * 10.0;
        else
            *destination = 0.0f;

        offset += 20;
        ++destination;
    } while (offset < 240);
}

void CTitle::on_scene_enter(int previous_scene)
{
    if (previous_scene != 4 &&
        previous_scene != 3 &&
        previous_scene != 16 &&
        previous_scene != 12 &&
        previous_scene != 1 &&
        previous_scene != 8 &&
        previous_scene != 9)
        play_bgm(title_bgm_path);

    clear_network_session();
    set_ui_selection_state_tracking(0);
}

void CTitle::on_scene_exit(int)
{
    if (has_ui_selection_state_changed())
        set_ui_selection_state_tracking(1);
}

void CLoadingWatch::on_scene_enter(int previous_scene)
{
    if (previous_scene != 2)
        play_bgm(title_bgm_path);
}

} // namespace th105
