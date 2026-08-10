#include "SelectScenario.hpp"

extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);
extern "C" const char scenario_stand_path_format[];
extern "C" const char *__cdecl get_scenario_name(int scenario_id);

namespace th105 {

void CSelectScenario::apply_scenario(int scenario_id)
{
    char path[260];
    unsigned int handle;
    unsigned int width;
    unsigned int height;

    g_title_resource_manager.release_title_resource_handle(texture_218);
    texture_218 = 0;
    if (scenario_id == 15)
        return;

    wsprintfA(
        path, scenario_stand_path_format, get_scenario_name(scenario_id));
    unsigned int loaded = *g_title_resource_manager.load_texture(
        &handle, path, &width, &height);
    const unsigned int *methods = color_21c.vtable;
    texture_218 = loaded;
    reinterpret_cast<UiSprite94::SetTextureOptions>(methods[4])(
        &color_21c, loaded, 0, 0, width, height, 64, 0);
}

} // namespace th105
