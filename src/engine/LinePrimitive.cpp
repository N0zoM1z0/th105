#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"
namespace th105 {
struct LineVertex { float x, y, z, rhw; unsigned color; };
typedef char LineVertexSize[sizeof(LineVertex) == 20 ? 1 : -1];
// Preserve the observed single-precision subtraction/store graph.
#pragma fenv_access(on)
int RenderModeManager::draw_line(float x1, float y1, float x2, float y2, unsigned color)
{
    LineVertex vertices[2];
    vertices[0].x = x1 - 0.5f;
    vertices[1].x = x2 - 0.5f;
    vertices[0].y = y1 - 0.5f;
    vertices[1].y = y2 - 0.5f;
    vertices[0].z = vertices[1].z = 0.0f;
    vertices[0].rhw = vertices[1].rhw = 1.0f;
    vertices[0].color = vertices[1].color = color;
    g_title_resource_manager.bind_texture(DesignTextureHandle(), 0);
    device_04->SetFVF(0x44);
    return device_04->DrawPrimitiveUP(2, 1, vertices, sizeof(vertices[0]));
}
}

#pragma fenv_access(off)
