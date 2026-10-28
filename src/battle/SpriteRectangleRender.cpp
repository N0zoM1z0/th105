#include "battle/EffectSprite.hpp"
#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"
namespace th105 {
struct SpriteRectangleRenderView : CSpriteBase {
    void render_rectangle(float left,float top,float right,float bottom);
};
void SpriteRectangleRenderView::render_rectangle(float left,float top,float right,float bottom)
{
    vertices_08[0].x=left-0.5f;
    vertices_08[0].y=top-0.5f;
    vertices_08[1].x=right-0.5f;
    vertices_08[1].y=top-0.5f;
    vertices_08[2].x=left-0.5f;
    vertices_08[2].y=bottom-0.5f;
    vertices_08[3].x=right-0.5f;
    vertices_08[3].y=bottom-0.5f;
    g_title_resource_manager.bind_texture(value_04,0);
    g_render_mode_manager.device_04->SetFVF(0x144);
    g_render_mode_manager.device_04->DrawPrimitiveUP(5,2,vertices_08,sizeof(SpriteVertex28));
}
}
