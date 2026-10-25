#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"

namespace th105 {
struct RectangleLineView {
    int draw_line(float x1, float y1, float x2, float y2, unsigned color);
};
struct RectangleColorVertex {
    float x, y, z, rhw;
    unsigned color;
};
// Keep each coordinate subtraction and its final float store distinct.
#pragma fenv_access(on)
int RenderModeManager::draw_rect(
    float left, float top, float right, float bottom,
    unsigned color, unsigned char filled)
{
    if (!filled) {
        RectangleLineView *lines = reinterpret_cast<RectangleLineView *>(this);
        lines->draw_line(left, top, left, bottom, color);
        lines->draw_line(right, top, right, bottom, color);
        lines->draw_line(left, top, right, top, color);
        return lines->draw_line(left, bottom, right, bottom, color);
    }
    RectangleColorVertex vertices[4];
    vertices[0].x = left - 0.5f;
    vertices[0].y = top - 0.5f;
    vertices[1].x = right - 0.5f;
    vertices[1].y = top - 0.5f;
    vertices[2].x = left - 0.5f;
    vertices[2].y = bottom - 0.5f;
    vertices[3].x = right - 0.5f;
    vertices[3].y = bottom - 0.5f;
    vertices[0].z = vertices[1].z = vertices[2].z = vertices[3].z = 0.5f;
    vertices[0].rhw = vertices[1].rhw = vertices[2].rhw = vertices[3].rhw = 1.0f;
    vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = color;
    g_title_resource_manager.bind_texture(0, 0);
    device_04->SetFVF(0x44);
    return device_04->DrawPrimitiveUP(5, 2, vertices, sizeof(vertices[0]));
}
#pragma fenv_access(off)
} // namespace th105
