#include "ScenarioData.hpp"
#include "ui/ProfileUiInfrastructure.hpp"
#include "ui/Title.hpp"

namespace th105 {

int __cdecl selector_random_roll(int limit);
extern unsigned char g_round_counter;
void draw_profile_overlay(unsigned char alpha);

static float &scenario_result_tile_scale_x(UiTileA4 &tile)
{
    return *reinterpret_cast<float *>(
        reinterpret_cast<unsigned char *>(&tile) + 0x88);
}

static float &scenario_result_tile_scale_y(UiTileA4 &tile)
{
    return *reinterpret_cast<float *>(
        reinterpret_cast<unsigned char *>(&tile) + 0x8c);
}

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

    UiTileA4 *tile = &tile_05c;
    float *scale = &scales_118[0];
    int remaining = 3;
    do {
        tile->set_color(*(reinterpret_cast<unsigned int *>(scale) - 3));
        const float current_scale = *scale;
        scenario_result_tile_scale_x(*tile) = current_scale;
        scenario_result_tile_scale_y(*tile) = current_scale;

        ScenarioResultSecondaryObject *secondary =
            *(reinterpret_cast<ScenarioResultSecondaryObject **>(scale) - 51);
        ScenarioResultPositionObject *primary =
            *(reinterpret_cast<ScenarioResultPositionObject **>(scale) - 54);
        const int mode = *(reinterpret_cast<int *>(scale) - 6);
        reinterpret_cast<ProfileTileView *>(tile)->render(
            primary->x_04 + secondary->x_0c,
            secondary->y_10,
            mode,
            0);
        ++scale;
    } while (--remaining != 0);
}

} // namespace th105
