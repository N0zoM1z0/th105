#include "SelectScenario.hpp"

#include <math.h>

extern "C" void __cdecl _invalid_parameter_noinfo();
extern "C" void *__cdecl get_score_data();

namespace th105 {

struct RenderModeManager {
    bool begin_frame();
    void prepare_frame();
    void finish_frame();
    void set_mode(int mode);
};

extern RenderModeManager g_render_mode_manager;

bool CSelectScenario::render()
{
    if (!g_render_mode_manager.begin_frame())
        return false;

    g_render_mode_manager.set_mode(2);
    g_render_mode_manager.prepare_frame();
    color_44.render(0.0f, 0.0f);
    color_21c.render(0.0f, 0.0f);
    design_2e4.prepare(501);

    int item = 0;
    do {
        unsigned int scenario_index =
            (scenario_count_3c + item - 3 + player_cursor_2bc.selection) %
            scenario_count_3c;
        float offset =
            (static_cast<float>(item - 3) + transition_33c) * 80.0;
        float alpha = 255.0 - static_cast<float>(fabs(offset));
        if (alpha < 0.0f)
            alpha = 0.0f;
        unsigned int color =
            (static_cast<int>(alpha) << 24) | 0xFFFFFF;
        color_174.set_color(color);

        if (scenario_ids_2c.begin == 0 ||
            static_cast<unsigned int>(
                scenario_ids_2c.end - scenario_ids_2c.begin) <= scenario_index)
            _invalid_parameter_noinfo();
        color_174.render(
            scenario_ids_2c.begin[scenario_index], 0,
            static_cast<UiDesignObject *>(selection_data_2b0)->x,
            static_cast<UiDesignObject *>(selection_data_2b0)->y + offset);

        if (scenario_ids_2c.begin == 0 ||
            static_cast<unsigned int>(
                scenario_ids_2c.end - scenario_ids_2c.begin) <= scenario_index)
            _invalid_parameter_noinfo();
        unsigned char *score = static_cast<unsigned char *>(get_score_data());
        int scenario_id = scenario_ids_2c.begin[scenario_index];
        if ((score[scenario_id + 8] & (1 << match_setup_08->game_type)) != 0) {
            color_dc.set_color(color);
            color_dc.render(
                design_100->x, design_100->y + offset);
        }
        ++item;
    } while (item < 7);

    float alpha = (1.0 - static_cast<float>(fabs(transition_33c))) * 255.0;
    if (alpha < 0.0f)
        alpha = 0.0f;
    unsigned int color = (static_cast<int>(alpha) << 24) | 0xFFFFFF;
    design_500[1]->set_color(color);
    design_500[2]->set_color(color);
    design_2e4.render();

    UiDesignObject *scenario = static_cast<UiDesignObject *>(scenario_data_2b4);
    static_cast<UiDesignObject *>(preview_data_2b8)->render(
        scenario->x + 88.0, scenario->y + 10.0);

    g_render_mode_manager.set_mode(1);
    guide_344.render();
    g_render_mode_manager.finish_frame();
    return true;
}

} // namespace th105
