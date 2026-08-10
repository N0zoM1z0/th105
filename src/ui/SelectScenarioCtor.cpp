#include "SelectScenario.hpp"

#include "../input/InputSelection.hpp"

extern "C" void *__cdecl get_score_data();
extern "C" const char select_background_path[];
extern "C" const char select_clear_path[];
extern "C" const char select_character_name_path[];
extern "C" const char select_design_path[];

namespace th105 {

CSelectScenario::CSelectScenario()
    : texture_40(0), texture_d8(0), texture_170(0), texture_218(0)
{
    unsigned int handle;
    unsigned int width;
    unsigned int height;

    texture_40 = *g_title_resource_manager.load_texture(
        &handle, select_background_path, &width, &height);
    color_44.set_texture(texture_40, 0, 0, width, height);

    texture_d8 = *g_title_resource_manager.load_texture(
        &handle, select_clear_path, &width, &height);
    color_dc.set_texture(texture_d8, 0, 0, width, height);

    texture_170 = *g_title_resource_manager.load_texture(
        &handle, select_character_name_path, &width, &height);
    color_174.set_texture(texture_170, 0, 0, width, 64);

    preview_data_2b8 =
        reinterpret_cast<unsigned char *>(get_player_slot_record(0)) + 4;

    scenario_ids_2c.clear();
    long scenario_id = 0;
    do {
        unsigned char *score = static_cast<unsigned char *>(get_score_data());
        if (score[scenario_id + 0x1C] != 0)
            scenario_ids_2c.append(static_cast<int>(scenario_id));
        ++scenario_id;
    } while (scenario_id < 15);
    scenario_count_3c = scenario_ids_2c.size();

    design_2e4.load(select_design_path);
    design_2e4.bind_object(&selection_data_2b0, 200);
    design_2e4.bind_object_alt(&scenario_data_2b4, 300);
    scenario_data_2b4->enabled = true;

    int index = 0;
    do {
        design_2e4.bind_object_alt(&design_500[index], index + 500);
        design_500[index]->enabled = true;
        ++index;
    } while (index < 3);

    design_100 = design_2e4.find_object(100);

    index = 0;
    do {
        design_2e4.bind_object(&design_600[index], index + 600);
        ++index;
    } while (index < 4);

    preview_alpha_340 = 0.0f;
    transition_33c = 0.0f;
    timer_338 = 0;
    guide_344.load(92);
    guide_344.visible = true;
}

} // namespace th105
