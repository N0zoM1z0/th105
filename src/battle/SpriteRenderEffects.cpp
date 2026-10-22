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
    service->vtable->set_vector(service, "v4Arg0", value);
    service->vtable->begin(service);
    service->vtable->configure_pair(service, 0, 0);
    service->vtable->select_mode(service, 0);
    finalize_render();
    service->vtable->finish_first(service);
    service->vtable->finish_second(service);
}

void SpriteRenderEffectView::render_alpha_rgb(
    float alpha, float red, float green, float blue)
{
    if (alpha != 0.0f) {
        float value[4] = {red, green, blue, alpha};
        RenderEffectService *const service = g_render_effect_service;
        service->vtable->set_vector(service, "v4Arg0", value);
        service->vtable->begin(service);
        service->vtable->configure_pair(service, 0, 0);
        service->vtable->select_mode(service, 1);
        finalize_render();
        service->vtable->finish_first(service);
        service->vtable->finish_second(service);
        return;
    }
    finalize_render();
}

void SpriteRenderEffectView::render_luma(float red, float green, float blue)
{
    float value[4] = {red, green, blue, 0.0f};
    RenderEffectService *const service = g_render_effect_service;
    service->vtable->set_vector(service, "v4Arg0", value);
    service->vtable->begin(service);
    service->vtable->configure_pair(service, 0, 0);
    service->vtable->select_mode(service, 2);
    finalize_render();
    service->vtable->finish_first(service);
    service->vtable->finish_second(service);
}

} // namespace th105
