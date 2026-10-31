// JP1.06a CTile texture options4098E0; complete canonical266-byte match.
#include "CNumberRuntime.hpp"
#include "Title.hpp"
namespace th105 {
// Preserve each observed unsigned conversion and division under the FP environment.
#pragma fenv_access(on)
void CNumberTileA4::set_texture_options(
    unsigned int handle,
    int x,
    int y,
    int width,
    int height,
    int anchor_x,
    int anchor_y)
{
    width_78 = static_cast<float>(width);
    height_7c = static_cast<float>(height);
    anchor_x_80 = static_cast<float>(anchor_x);
    anchor_y_84 = static_cast<float>(anchor_y);
    texture_handle_04 = handle;

    g_title_resource_manager.get_texture_size(
        handle,
        &handle,
        reinterpret_cast<unsigned int *>(&width));

    vertices_08[0].color_10 =
        vertices_08[1].color_10 =
        vertices_08[2].color_10 =
        vertices_08[3].color_10 = ~0u;

    texture_u_94 = static_cast<float>(x) / handle;
    texture_v_98 = static_cast<float>(y) /
        static_cast<unsigned int>(width);
    texture_width_u_9c = width_78 / handle;
    texture_height_v_a0 = height_7c / static_cast<unsigned int>(width);

    vertices_08[0].z_08 = 0.5f;
    vertices_08[0].rhw_0c = 1.0f;
    vertices_08[1].rhw_0c = 1.0f;
    vertices_08[2].rhw_0c = 1.0f;
    vertices_08[3].rhw_0c = 1.0f;
    scale_y_8c = 1.0f;
    scale_x_88 = 1.0f;
    vertices_08[1].z_08 = 0.5f;
    vertices_08[2].z_08 = 0.5f;
    vertices_08[3].z_08 = 0.5f;
    rotation_90 = 0.0f;
}

#pragma fenv_access(off)
} // namespace th105
