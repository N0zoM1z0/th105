#include "engine/Sprite.hpp"
#include "ui/Title.hpp"

#pragma float_control(except, off, push)
void CSprite::set_texture_options(unsigned handle, int x, int y,
    int width, int height, int pivot_x, int pivot_y)
{
    texture_width_78 = static_cast<float>(width);
    texture_height_7c = static_cast<float>(height);
    pivot_x_80 = static_cast<float>(pivot_x);
    pivot_y_84 = static_cast<float>(pivot_y);
    value_04 = handle;

    // Both input values have been published before their storage is reused
    // for the unsigned texture extents, as in the original size-query call.
    th105::g_title_resource_manager.get_texture_size(
        handle, &handle, reinterpret_cast<unsigned *>(&pivot_x));

    float left = static_cast<float>(x) / handle;
    vertices_08[0].u = left;
    float top = static_cast<float>(y) / static_cast<unsigned>(pivot_x);
    vertices_08[0].v = top;
    float right = static_cast<float>(x + width) / handle;
    vertices_08[1].u = right;
    vertices_08[1].v = top;
    vertices_08[2].u = left;
    float bottom = static_cast<float>(y + height) / static_cast<unsigned>(pivot_x);

    vertices_08[0].color = vertices_08[1].color =
        vertices_08[2].color = vertices_08[3].color = ~0u;
    vertices_08[2].v = bottom;
    vertices_08[3].v = bottom;
    vertices_08[3].u = right;
    vertices_08[0].z = vertices_08[1].z =
        vertices_08[2].z = vertices_08[3].z = 0.5f;
    scale_x_88 = scale_y_8c = vertices_08[0].rhw = vertices_08[1].rhw =
        vertices_08[2].rhw = vertices_08[3].rhw = 1.0f;
    angle_90 = 0.0f;
}
#pragma float_control(pop)
