// JP1.06a CTile texture options4098E0; complete canonical266-byte match.
#include "CNumberRuntime.hpp"
#include "Title.hpp"
using namespace th105;
// Preserve each observed unsigned conversion and division under the FP environment.
#pragma fenv_access(on)
void CTile::set_texture_options(
    unsigned int handle,
    int x,
    int y,
    int width,
    int height,
    int anchor_x,
    int anchor_y)
{
    texture_width_78 = static_cast<float>(width);
    texture_height_7c = static_cast<float>(height);
    pivot_x_80 = static_cast<float>(anchor_x);
    pivot_y_84 = static_cast<float>(anchor_y);
    value_04 = handle;

    g_title_resource_manager.get_texture_size(
        handle,
        &handle,
        reinterpret_cast<unsigned int *>(&width));

    vertices_08[0].color =
        vertices_08[1].color =
        vertices_08[2].color =
        vertices_08[3].color = ~0u;

    u_origin_94 = static_cast<float>(x) / handle;
    v_origin_98 = static_cast<float>(y) /
        static_cast<unsigned int>(width);
    u_step_9c = texture_width_78 / handle;
    v_step_a0 = texture_height_7c / static_cast<unsigned int>(width);

    vertices_08[0].z = 0.5f;
    vertices_08[0].rhw = 1.0f;
    vertices_08[1].rhw = 1.0f;
    vertices_08[2].rhw = 1.0f;
    vertices_08[3].rhw = 1.0f;
    scale_y_8c = 1.0f;
    scale_x_88 = 1.0f;
    vertices_08[1].z = 0.5f;
    vertices_08[2].z = 0.5f;
    vertices_08[3].z = 0.5f;
    angle_90 = 0.0f;
}

#pragma fenv_access(off)
