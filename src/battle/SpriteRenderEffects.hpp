#pragma once

#include "AnimationRenderVirtuals.hpp"
#include "D3DXEffectInterface.hpp"

namespace th105 {

// The observed effect service uses the D3DX-compatible COM call surface.
typedef D3DXEffectInterface RenderEffectService;
extern RenderEffectService *g_render_effect_service;

} // namespace th105
