#include "AnimationRenderVirtuals.hpp"

namespace th105 {

void AnimationRenderObjectView::render_group_callback(signed char group)
{
    if (group != render_group_33c)
        return;

    if (aux_renderer_154) {
        aux_renderer_154->render_auxiliary();
        if (secondary_renderer_338)
            secondary_renderer_338->render_secondary();
        AnimationRenderObjectView::render_main();
        aux_renderer_154->finish_render_pass();
        return;
    }

    if (secondary_renderer_338)
        secondary_renderer_338->render_secondary();
    AnimationRenderObjectView::render_main();
}

} // namespace th105
