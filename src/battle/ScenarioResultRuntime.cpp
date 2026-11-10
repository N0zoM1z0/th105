#include "ScenarioData.hpp"
#include "ui/ProfileUiInfrastructure.hpp"
#include "ui/Title.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);
extern unsigned char g_round_counter;
void draw_profile_overlay(unsigned char alpha);

void ScenarioResultResource::hide_and_reset()
{
    ScenarioResultPositionObject *object = primary_03c[1];
    colors_10c[0] = 0;
    object->x_04 = 640.0f;
    object->y_08 = 0.0f;

    object = primary_03c[2];
    colors_10c[1] = 0;
    object->x_04 = 640.0f;
    object->y_08 = 0.0f;

    object = primary_03c[3];
    colors_10c[2] = 0;
    object->x_04 = 640.0f;
    object->y_08 = 0.0f;

    phase_001 = 0;
    counter_004 = 0;
    alpha_124 = 0;
    state_000 = 0;
}

void ScenarioResultResource::add_nonnegative(
    int first, int second, int third)
{
    values_100[0] = first + values_100[0] < 0 ? 0 : first + values_100[0];
    values_100[1] = second + values_100[1] < 0 ? 0 : second + values_100[1];
    values_100[2] = third + values_100[2] < 0 ? 0 : third + values_100[2];
}

void ScenarioResultResource::enter_phase_three()
{
    if (state_000 != 0 && phase_001 == 2) {
        phase_001 = 3;
        counter_004 = 0;
        int *value = &values_100[0];
        int remaining = 3;
        do {
            if (selector_random_roll(3) < *value)
                ++g_round_counter;
            ++value;
        } while (--remaining != 0);
    }
}

void ScenarioResultResource::reset()
{
    values_100[0] = 3;
    values_100[1] = 3;
    values_100[2] = 3;

    ScenarioResultPositionObject *object = primary_03c[1];
    colors_10c[0] = 0;
    object->x_04 = 640.0f;
    object->y_08 = 0.0f;

    object = primary_03c[2];
    colors_10c[1] = 0;
    object->x_04 = 640.0f;
    object->y_08 = 0.0f;

    object = primary_03c[3];
    colors_10c[2] = 0;
    object->x_04 = 640.0f;
    object->y_08 = 0.0f;

    phase_001 = 0;
    counter_004 = 0;
    alpha_124 = 0;
    state_000 = 0;
}

void ScenarioResultResource::set_entry_level(int index, int value)
{
    if (value > 15)
        value = 15;
    else if (value < 0)
        return;

    if (values_100[index] != 0) {
        colors_10c[index] = 0xffffffffu;
        scales_118[index] = static_cast<float>(
            static_cast<double>(15 - value) / 7.5 + 1.0);
    } else {
        scales_118[index] = 1.0f;
        colors_10c[index] =
            (static_cast<unsigned>(255 * value / 15) << 24) | 0x00ffffffu;
    }
}

void ScenarioResultResource::render()
{
    if (state_000 == 0)
        return;
    if (alpha_124 != 0)
        draw_profile_overlay(alpha_124);
    primary_03c[0]->set_color(
        (static_cast<unsigned>(alpha_124) << 24) | 0x00ffffffu);
    reinterpret_cast<TitleDesignResource *>(&design_008)->render();

    CTile *tile = &tile_05c;
    for (unsigned int index = 0; index < 3; ++index) {
        tile->set_color(colors_10c[index]);
        const float current_scale = scales_118[index];
        tile->scale_x_88 = current_scale;
        tile->scale_y_8c = current_scale;

        ScenarioResultSecondaryObject *secondary =
            secondary_04c[index];
        ScenarioResultPositionObject *primary =
            primary_03c[index + 1];
        const int mode = values_100[index];
        tile->render(
            primary->x_04 + secondary->x_0c,
            secondary->y_10,
            mode,
            0);
    }
}

} // namespace th105
