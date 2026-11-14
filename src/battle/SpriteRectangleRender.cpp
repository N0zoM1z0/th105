#include "battle/EffectSprite.hpp"
#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"
using th105::g_title_resource_manager;
using th105::g_render_mode_manager;
void CSprite::render_rectangle(float left,float top,float right,float bottom)
{
    vertices_08[0].x=left-0.5f;
    vertices_08[0].y=top-0.5f;
    vertices_08[1].x=right-0.5f;
    vertices_08[1].y=top-0.5f;
    vertices_08[2].x=left-0.5f;
    vertices_08[2].y=bottom-0.5f;
    vertices_08[3].x=right-0.5f;
    vertices_08[3].y=bottom-0.5f;
    th105::DesignTextureHandle texture = value_04;
    g_title_resource_manager.bind_texture(texture, 0);
    g_render_mode_manager.device_04->SetFVF(0x144);
    g_render_mode_manager.device_04->DrawPrimitiveUP(5,2,vertices_08,sizeof(SpriteVertex28));
}
