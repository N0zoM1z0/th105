#include "battle/BattleObjectManagerRuntime.hpp"
#include "engine/RenderModeManager.hpp"
#include "ui/Title.hpp"
#include "battle/D3DXEffectInterface.hpp"
#include <stddef.h>

namespace th105 {

struct BattleRenderVertex36 {
    unsigned char reserved_00[0x10];
    unsigned color_10;
    float x_14;
    float y_18;
    float u_1c;
    float v_20;
};
typedef char BattleRenderVertex36_size[sizeof(BattleRenderVertex36)==0x24?1:-1];

struct BattleObjectRenderTailView {
    unsigned char reserved_000[0x40];
    BattleBaseEffect effect_40;
    BattleRenderVertex36 vertices_48[4];
    unsigned texture_a_d8;
    unsigned texture_b_dc;
    float offset_a_x_e0;
    float offset_b_x_e4;
    float offset_a_y_e8;
    float offset_b_y_ec;
    unsigned char reserved_f0[8];
    unsigned char fade_f8;

    void render_tail_4666a0();
};

typedef char BOT_vertices_off[offsetof(BattleObjectRenderTailView,vertices_48)==0x48?1:-1];
typedef char BOT_texa_off[offsetof(BattleObjectRenderTailView,texture_a_d8)==0xd8?1:-1];
typedef char BOT_fade_off[offsetof(BattleObjectRenderTailView,fade_f8)==0xf8?1:-1];

void BattleObjectRenderTailView::render_tail_4666a0()
{
    if (fade_f8 == 0xff)
        return;

    if (texture_a_d8 == 0)
        texture_a_d8 = texture_b_dc;

    unsigned width;
    unsigned height;
    g_title_resource_manager.get_texture_size(texture_a_d8, &width, &height);

    vertices_48[0].x_14 = offset_a_x_e0;
    const float top = offset_a_y_e8;
    vertices_48[0].y_18 = top;
    const float right = static_cast<float>(640.0 / static_cast<float>(width) + offset_a_x_e0);
    vertices_48[1].x_14 = right;
    vertices_48[1].y_18 = top;
    vertices_48[2].x_14 = vertices_48[0].x_14;
    const float bottom = static_cast<float>(480.0 / static_cast<float>(height) + offset_a_y_e8);
    vertices_48[2].y_18 = bottom;
    vertices_48[3].y_18 = bottom;
    vertices_48[3].x_14 = right;

    if (texture_b_dc == 0)
        texture_b_dc = texture_a_d8;
    g_title_resource_manager.get_texture_size(texture_b_dc, &width, &height);

    const float u_right = static_cast<float>(640.0 / static_cast<float>(width) + offset_b_x_e4);
    vertices_48[0].u_1c = u_right;
    const float v_top = offset_b_y_ec;
    vertices_48[0].v_20 = v_top;
    const float u_left = offset_b_x_e4;
    vertices_48[1].u_1c = u_left;
    vertices_48[1].v_20 = v_top;
    vertices_48[2].u_1c = u_right;
    const float v_bottom = static_cast<float>(480.0 / static_cast<float>(height) + offset_b_y_ec);
    vertices_48[2].v_20 = v_bottom;
    vertices_48[3].v_20 = v_bottom;
    vertices_48[3].u_1c = u_left;

    g_title_resource_manager.bind_texture(texture_a_d8, 0);
    g_title_resource_manager.bind_texture(texture_b_dc, 1);

    float arg0[4] = {0.5f, 0.5f, 1.0f, 1.0f};
    D3DXEffectInterface *service = static_cast<D3DXEffectInterface *>(effect_40.effect_04);
    float arg1[4];
    int fade = 3 * (255 - static_cast<int>(fade_f8));
    fade >>= 2;
    arg1[2] = 1.0f;
    arg1[3] = 1.0f;
    const unsigned color = (static_cast<unsigned>(fade) << 24) | 0x00ffffffu;
    arg1[0] = 0.5f;
    arg1[1] = 0.5f;
    vertices_48[3].color_10 = color;
    vertices_48[2].color_10 = color;
    vertices_48[1].color_10 = color;
    vertices_48[0].color_10 = color;
    service->SetVector("v4Arg0", reinterpret_cast<const D3DXVECTOR4 *>(arg0));
    service->SetVector("v4Arg1", reinterpret_cast<const D3DXVECTOR4 *>(arg1));
    service->CommitChanges();
    service->Begin(0, 0);
    service->BeginPass(0);
    g_render_mode_manager.submit_primitive(5, 2, vertices_48, 36, 580);
    service->EndPass();
    service->End();
}

} // namespace th105
