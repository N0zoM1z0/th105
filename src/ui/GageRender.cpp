// Complete source hypothesis for JP1.06a CGage vslot1C at41B3F0.
// Canonical equality remains pending; see docs/GAGE_RENDER_2026_10_20.md.
#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"
#include <stddef.h>

namespace th105 {
struct GageScreenVertex28 { float x, y, z, rhw; unsigned color; float u, v; };
// The caller rounds the actual getter result to float. This view agrees with
// the independently exact TGageValue providers; original API spelling is open.
struct GageValueView { virtual float value() = 0; };
struct CGageRenderView {
    const void *vtable_00;
    unsigned texture_handle_04;
    GageScreenVertex28 vertices_08[4];
    float width_78, height_7c;
    float pivot_x_80, pivot_y_84;
    float scale_x_88, scale_y_8c;
    float angle_90;
    float u_span_94, v_span_98;
    int fill_mode_9c;
    GageValueView *value_a0;
    void render(float x, float y);
};
double __cdecl lookup_orientation_cosine_quantized_abs(float phase);
double __cdecl lookup_orientation_sine_quantized_abs(float phase);

// Target float assignment homes require the selected strict-FP profile.
#pragma float_control(except, off, push)
void CGageRenderView::render(float x, float y)
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
        float right = x - pivot_x_80 * scale_x_88 + width_78 * scale_x_88 - 0.5f;
        vertices_08[1].x = right;
        float top = y - pivot_y_84 * scale_y_8c - 0.5f;
        vertices_08[1].y = top;
        float left = right - width_78 * fraction * scale_x_88;
        vertices_08[0].x = left;
        vertices_08[2].x = left;
        vertices_08[0].y = top;
        float bottom = height_7c * scale_y_8c + top;
        vertices_08[2].y = bottom;
        vertices_08[3].y = bottom;
        vertices_08[3].x = right;
        float u = vertices_08[1].u - fraction * u_span_94;
        vertices_08[0].u = u;
        vertices_08[2].u = u;
        break;
    }
    case 1: {
        float left = x - pivot_x_80 * scale_x_88 - 0.5f;
        vertices_08[2].x = left;
        float bottom = y - pivot_y_84 * scale_y_8c - 0.5f + scale_y_8c * height_7c;
        vertices_08[2].y = bottom;
        float right = width_78 * scale_x_88 + left;
        vertices_08[3].x = right;
        vertices_08[3].y = bottom;
        vertices_08[0].x = left;
        float top = bottom - fraction * height_7c * scale_y_8c;
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
        float right = width_78 * fraction * scale_x_88 + left;
        vertices_08[1].x = right;
        vertices_08[1].y = top;
        vertices_08[2].x = left;
        float bottom = height_7c * scale_y_8c + top;
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

    g_title_resource_manager.bind_texture(texture_handle_04, 0);
    g_render_mode_manager.device_04->SetFVF(0x144);
    g_render_mode_manager.device_04->DrawPrimitiveUP(
        5, 2, vertices_08, sizeof(GageScreenVertex28));
}
#pragma float_control(pop)

typedef char GageVertexSize[sizeof(GageScreenVertex28) == 0x1c ? 1 : -1];
typedef char GageRenderSize[sizeof(CGageRenderView) == 0xa4 ? 1 : -1];
typedef char GageVerticesOffset[offsetof(CGageRenderView, vertices_08) == 0x08 ? 1 : -1];
typedef char GageUVSpanOffset[offsetof(CGageRenderView, u_span_94) == 0x94 ? 1 : -1];
typedef char GageModeOffset[offsetof(CGageRenderView, fill_mode_9c) == 0x9c ? 1 : -1];
typedef char GageValueOffset[offsetof(CGageRenderView, value_a0) == 0xa0 ? 1 : -1];
} // namespace th105
