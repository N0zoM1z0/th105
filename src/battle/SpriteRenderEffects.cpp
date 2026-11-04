#include "SpriteRenderEffects.hpp"

namespace th105 {

void SpriteRenderEffectView::render_rgb(float red, float green, float blue)
{
    if (red == 0.0f && green == 0.0f && blue == 0.0f) {
        finalize_render();
        return;
    }
    float value[4] = {red, green, blue, 0.0f};
    RenderEffectService *const service = g_render_effect_service;
    service->SetVector("v4Arg0", reinterpret_cast<const D3DXVECTOR4 *>(value));
    service->CommitChanges();
    service->Begin(0, 0);
    service->BeginPass(0);
    finalize_render();
    service->EndPass();
    service->End();
}

void SpriteRenderEffectView::render_alpha_rgb(
    float alpha, float red, float green, float blue)
{
    if (alpha != 0.0f) {
        float value[4] = {red, green, blue, alpha};
        RenderEffectService *const service = g_render_effect_service;
        service->SetVector("v4Arg0", reinterpret_cast<const D3DXVECTOR4 *>(value));
        service->CommitChanges();
        service->Begin(0, 0);
        service->BeginPass(1);
        finalize_render();
        service->EndPass();
        service->End();
        return;
    }
    finalize_render();
}

void SpriteRenderEffectView::render_luma(float red, float green, float blue)
{
    float value[4] = {red, green, blue, 0.0f};
    RenderEffectService *const service = g_render_effect_service;
    service->SetVector("v4Arg0", reinterpret_cast<const D3DXVECTOR4 *>(value));
    service->CommitChanges();
    service->Begin(0, 0);
    service->BeginPass(2);
    finalize_render();
    service->EndPass();
    service->End();
}

} // namespace th105
