#include "ScenarioData.hpp"
#include "ui/Title.hpp"

namespace th105 {

ScenarioRenderEntry9C::~ScenarioRenderEntry9C()
{
    g_title_resource_manager.release_title_resource_handle(
        resource_handle_000);
}

void CScenarioData::trim_render_entries_and_begin_fade_455cd0()
{
    int fade_step = 20;
    if (state_511)
        fade_step = 4;

    while (render_entries_350.size() > 1)
        render_entries_350.pop_front();

    if (!render_entries_350.empty())
        render_entries_350.front().reserved_098[1] = -fade_step;
}

} // namespace th105
