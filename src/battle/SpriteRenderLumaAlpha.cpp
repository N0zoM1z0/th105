#include "SpriteRenderEffects.hpp"

namespace th105 {

void SpriteRenderEffectView::render_luma_alpha(
    float luma_red, float luma_green, float luma_blue,
    float alpha, float red, float green, float blue)
{
    if (alpha != 0.0f) {
        float luma[4] = {luma_red, luma_green, luma_blue, 0.0f};
        RenderEffectService *const service = g_render_effect_service;
        service->vtable->set_vector(service, "v4Arg0", luma);
        float color[4] = {red, green, blue, alpha};
        service->vtable->set_vector(service, "v4Arg1", color);
        service->vtable->begin(service);
        service->vtable->configure_pair(service, 0, 0);
        service->vtable->select_mode(service, 3);
        finalize_render();
        service->vtable->finish_first(service);
        service->vtable->finish_second(service);
        return;
    }
    render_luma(luma_red, luma_green, luma_blue);
}

} // namespace th105
