#pragma once

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

typedef char RenderEffectService_set_vector_slot_must_be_0x88[
    offsetof(RenderEffectServiceVTable, set_vector) == 0x88 ? 1 : -1];
typedef char RenderEffectService_configure_pair_slot_must_be_0xfc[
    offsetof(RenderEffectServiceVTable, configure_pair) == 0xfc ? 1 : -1];
typedef char RenderEffectService_begin_slot_must_be_0x104[
    offsetof(RenderEffectServiceVTable, begin) == 0x104 ? 1 : -1];
typedef char RenderEffectService_finish_second_slot_must_be_0x10c[
    offsetof(RenderEffectServiceVTable, finish_second) == 0x10c ? 1 : -1];

} // namespace th105
