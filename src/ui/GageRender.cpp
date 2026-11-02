// Complete source hypothesis for JP1.06a CGage vslot1C at41B3F0.
// Canonical equality remains pending; see docs/GAGE_RENDER_2026_10_20.md.
#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"
#include <stddef.h>
#include "Gage.hpp"

namespace th105 {
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
double __cdecl lookup_orientation_sine_quantized_abs(float phase);

} // namespace th105
using namespace th105;

// Target float assignment homes require the selected strict-FP profile.
#pragma float_control(except, off, push)
void CGage::render(float x, float y)
{
    if (value_a0 == 0)
        return;
    float fraction = value_a0->value();
    if (fraction <= 0.0f)
        return;
    if (fraction >= 1.0f)
        fraction = 1.0f;
    switch (fill_mode_9c) {
    case 0: {
        float right = x - pivot_x_80 * scale_x_88 + texture_width_78 * scale_x_88 - 0.5f;
        vertices_08[1].x = right;
        float top = y - pivot_y_84 * scale_y_8c - 0.5f;
        vertices_08[1].y = top;
        float left = right - texture_width_78 * fraction * scale_x_88;
        vertices_08[0].x = left;
        vertices_08[2].x = left;
        vertices_08[0].y = top;
        float bottom = texture_height_7c * scale_y_8c + top;
        vertices_08[2].y = bottom;
        vertices_08[3].y = bottom;
        vertices_08[3].x = right;
        float u = vertices_08[1].u - fraction * u_span_94;
        vertices_08[0].u = u;
        vertices_08[2].u = u;
        break;
    }
    case 1: {
        // Live field binding; docs/GAGE_RENDER_CONTEXT_2026_10_21.md.
        const float &height = texture_height_7c;
        float left = x - pivot_x_80 * scale_x_88 - 0.5f;
        vertices_08[2].x = left;
        float bottom = y - pivot_y_84 * scale_y_8c - 0.5f + scale_y_8c * height;
        vertices_08[2].y = bottom;
        float right = texture_width_78 * scale_x_88 + left;
        vertices_08[3].x = right;
        vertices_08[3].y = bottom;
        vertices_08[0].x = left;
        float top = bottom - fraction * height * scale_y_8c;
        vertices_08[0].y = top;
        vertices_08[1].y = top;
        vertices_08[1].x = right;
        float v = vertices_08[2].v - fraction * v_span_98;
        vertices_08[0].v = v;
        vertices_08[1].v = v;
        break;
    }
    case 2: {
        float left = x - pivot_x_80 * scale_x_88 - 0.5f;
        vertices_08[0].x = left;
        float top = y - pivot_y_84 * scale_y_8c - 0.5f;
        vertices_08[0].y = top;
        float right = texture_width_78 * fraction * scale_x_88 + left;
        vertices_08[1].x = right;
        vertices_08[1].y = top;
        vertices_08[2].x = left;
        float bottom = texture_height_7c * scale_y_8c + top;
        vertices_08[2].y = bottom;
        vertices_08[3].y = bottom;
        vertices_08[3].x = right;
        float u = vertices_08[1].u - fraction * u_span_94;
        vertices_08[0].u = u;
        vertices_08[2].u = u;
        break;
    }
    }
    if (angle_90 != 0.0f) {
        float cosine = static_cast<float>(
            lookup_orientation_cosine_quantized_abs(angle_90));
        float sine = static_cast<float>(
            lookup_orientation_sine_quantized_abs(angle_90));
        float old_x = vertices_08[0].x;
        float old_y = vertices_08[0].y;
        vertices_08[0].x = x + (old_x - x) * cosine - (old_y - y) * sine;
        vertices_08[0].y = y + (old_x - x) * sine + (old_y - y) * cosine;

        old_x = vertices_08[1].x;
        old_y = vertices_08[1].y;
        vertices_08[1].x = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[1].y = (old_x - x) * sine + y + (old_y - y) * cosine;

        old_x = vertices_08[2].x;
        old_y = vertices_08[2].y;
        vertices_08[2].x = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[2].y = (old_x - x) * sine + y + (old_y - y) * cosine;

        old_x = vertices_08[3].x;
        old_y = vertices_08[3].y;
        vertices_08[3].x = (old_x - x) * cosine + x - (old_y - y) * sine;
        vertices_08[3].y = y + (old_x - x) * sine + cosine * (old_y - y);
    }

    g_title_resource_manager.bind_texture(value_04, 0);
    g_render_mode_manager.device_04->SetFVF(0x144);
    g_render_mode_manager.device_04->DrawPrimitiveUP(
        5, 2, vertices_08, sizeof(SpriteVertex28));
}
#pragma float_control(pop)

typedef char GageVertexSize[sizeof(SpriteVertex28) == 0x1c ? 1 : -1];
typedef char GageRenderSize[sizeof(CGage) == 0xa4 ? 1 : -1];
typedef char GageVerticesOffset[offsetof(CGage, vertices_08) == 0x08 ? 1 : -1];
typedef char GageUVSpanOffset[offsetof(CGage, u_span_94) == 0x94 ? 1 : -1];
typedef char GageModeOffset[offsetof(CGage, fill_mode_9c) == 0x9c ? 1 : -1];
typedef char GageValueOffset[offsetof(CGage, value_a0) == 0xa0 ? 1 : -1];
