#include "EffectSprite.hpp"
#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"

#pragma float_control(except, off, push)
void CSpriteEx::finalize_render()
{
    vertices_08[0].x = working_quad_0b0[0].x - 0.5f;
    vertices_08[0].y = working_quad_0b0[0].y - 0.5f;
    vertices_08[1].x = working_quad_0b0[1].x - 0.5f;
    vertices_08[1].y = working_quad_0b0[1].y - 0.5f;
    vertices_08[2].x = working_quad_0b0[2].x - 0.5f;
    vertices_08[2].y = working_quad_0b0[2].y - 0.5f;
    vertices_08[3].x = working_quad_0b0[3].x - 0.5f;
    vertices_08[3].y = working_quad_0b0[3].y - 0.5f;

    vertices_08[0].z = working_quad_0b0[0].z + 0.5f;
    vertices_08[1].z = working_quad_0b0[1].z + 0.5f;
    vertices_08[2].z = working_quad_0b0[2].z + 0.5f;
    vertices_08[3].z = working_quad_0b0[3].z + 0.5f;
    vertices_08[0].rhw = vertices_08[1].rhw =
        vertices_08[2].rhw = vertices_08[3].rhw = 1.0f;

    th105::g_title_resource_manager.bind_texture(value_04, 0);
    th105::g_render_mode_manager.device_04->SetFVF(0x144);
    th105::g_render_mode_manager.device_04->DrawPrimitiveUP(
        5, 2, vertices_08, sizeof(SpriteVertex28));
}
#pragma float_control(pop)
