#include "SpriteRenderEffects.hpp"

namespace th105 {

void SpriteRenderEffectView::render_luma_alpha(
    float luma_red, float luma_green, float luma_blue,
    float alpha, float red, float green, float blue)
{
    if (alpha != 0.0f) {
        float luma[4] = {luma_red, luma_green, luma_blue, 0.0f};
        RenderEffectService *const service = g_render_effect_service;
        service->SetVector("v4Arg0", reinterpret_cast<const D3DXVECTOR4 *>(luma));
        float color[4] = {red, green, blue, alpha};
        service->SetVector("v4Arg1", reinterpret_cast<const D3DXVECTOR4 *>(color));
        service->CommitChanges();
        service->Begin(0, 0);
        service->BeginPass(3);
        finalize_render();
        service->EndPass();
        service->End();
        return;
    }
    render_luma(luma_red, luma_green, luma_blue);
}

} // namespace th105
