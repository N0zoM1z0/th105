#include "RenderTimeline.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

void RenderTimelineList::render()
{
    g_render_mode_manager.set_mode(2);
    g_render_mode_manager.set_blend_mode(1);

    for (std::list<RenderTimelineEntry>::iterator it = entries_58.begin();
         it != entries_58.end(); ++it) {
        it->render();
    }

    g_render_mode_manager.set_mode(1);
    g_render_mode_manager.set_sampler_state(0, 1, 1);
    g_render_mode_manager.set_sampler_state(0, 2, 1);
    g_render_mode_manager.set_blend_mode(1);
}

} // namespace th105
