#include "AnimationRenderVirtuals.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

void AuxiliarySpriteRenderView::finish_render_pass()
{
    g_render_mode_manager.apply_render_mode(1, 0);
    g_battle_render_pass += 2;
}

} // namespace th105
