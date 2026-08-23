#include "AnimationRenderVirtuals.hpp"

namespace th105 {

struct RenderEffectService;
struct RenderEffectServiceVTable {
    void *slots_000_084[34];
    void (__stdcall *set_vector)(
        RenderEffectService *service,
        const char *name,
        const float *value);
    void *slots_08c_0f8[28];
    void (__stdcall *configure_pair)(
        RenderEffectService *service, int first, int second);
    void (__stdcall *select_mode)(RenderEffectService *service, int mode);
    void (__stdcall *begin)(RenderEffectService *service);
    void (__stdcall *finish_first)(RenderEffectService *service);
    int (__stdcall *finish_second)(RenderEffectService *service);
};
struct RenderEffectService {
    RenderEffectServiceVTable *vtable;
};
extern RenderEffectService *g_render_effect_service;

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
