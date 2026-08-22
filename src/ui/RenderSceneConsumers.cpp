#include "engine/RenderModeManager.hpp"
#include "battle/BattleController.hpp"
#include "battle/EffectSprite.hpp"
#include "UiPrimitives.hpp"

#include <stddef.h>

namespace th105 {

extern float __cdecl lookup_orientation_cosine_quantized_abs(float phase);

struct SceneRendererView {
#define TH105_SCENE_SLOT(N) virtual void scene_slot_##N() = 0;
    TH105_SCENE_SLOT(0)
    TH105_SCENE_SLOT(1)
    TH105_SCENE_SLOT(2)
    TH105_SCENE_SLOT(3)
    TH105_SCENE_SLOT(4)
    TH105_SCENE_SLOT(5)
    TH105_SCENE_SLOT(6)
    TH105_SCENE_SLOT(7)
    TH105_SCENE_SLOT(8)
    TH105_SCENE_SLOT(9)
    TH105_SCENE_SLOT(10)
    TH105_SCENE_SLOT(11)
    TH105_SCENE_SLOT(12)
    TH105_SCENE_SLOT(13)
#undef TH105_SCENE_SLOT
    virtual void render() = 0;
};

extern SceneRendererView *g_scene_renderer;

struct SharedSceneRenderDelegate {
    virtual void scene_slot_0();
    virtual void scene_slot_1();
    virtual bool render();
};

bool SharedSceneRenderDelegate::render()
{
    if (g_render_mode_manager.begin_frame()) {
        g_scene_renderer->render();
        g_render_mode_manager.finish_frame();
        return true;
    }
    return false;
}

struct CFade {
    virtual void fade_slot_0();
    virtual void fade_slot_1();
    virtual void fade_slot_2();
    virtual void fade_slot_3();
    virtual bool render();

    unsigned color_04;
    int timer_08;
};

typedef char CFade_color_offset[offsetof(CFade, color_04) == 0x04 ? 1 : -1];
typedef char CFade_timer_offset[offsetof(CFade, timer_08) == 0x08 ? 1 : -1];

bool CFade::render()
{
    if (timer_08 == 0)
        return true;

    if (g_render_mode_manager.begin_frame()) {
        int alpha_source;
        if (timer_08 > 60)
            alpha_source = 255 * (120 - timer_08);
        else
            alpha_source = 255 * timer_08;

        g_render_mode_manager.draw_rect(
            0.0f,
            0.0f,
            640.0f,
            480.0f,
            color_04 | ((alpha_source / 60) << 24),
            1);
        g_render_mode_manager.finish_frame();
        return true;
    }
    return false;
}

struct EndingRenderCluster93 {
    unsigned char bytes_00[0x93];
    void render();
};

struct Ending {
    virtual void ending_slot_0();
    virtual void ending_slot_1();
    virtual unsigned char render();

    EndingRenderCluster93 cluster_04;
    unsigned char alpha_97;
};

typedef char Ending_cluster_offset[
    offsetof(Ending, cluster_04) == 0x04 ? 1 : -1];
typedef char Ending_alpha_offset[
    offsetof(Ending, alpha_97) == 0x97 ? 1 : -1];

unsigned char Ending::render()
{
    unsigned char result = g_render_mode_manager.begin_frame();
    if (!result)
        return result;

    g_render_mode_manager.prepare_frame();
    if (alpha_97 < 0xff) {
        g_battle_phase_block->run_458cd0();
        cluster_04.render();
    }

    if (alpha_97 != 0) {
        g_render_mode_manager.draw_rect(
            0.0f,
            0.0f,
            640.0f,
            480.0f,
            static_cast<unsigned>(alpha_97) << 24,
            1);
    }

    g_render_mode_manager.finish_frame();
    return 1;
}

struct CLogo {
    virtual void logo_slot_0();
    virtual void logo_slot_1();
    virtual bool render();

    unsigned unknown_04;
    CSpriteEx sprite_08;
};

typedef char CLogo_sprite_offset[
    offsetof(CLogo, sprite_08) == 0x08 ? 1 : -1];

bool CLogo::render()
{
    if (g_render_mode_manager.begin_frame()) {
        g_render_mode_manager.prepare_frame();
        sprite_08.reset_transform();
        sprite_08.finalize_render();
        g_render_mode_manager.finish_frame();
        return true;
    }
    return false;
}

struct OpeningRenderListView {
    void render();
};

struct Opening {
    virtual void opening_slot_0();
    virtual void opening_slot_1();
    virtual bool render();

    unsigned unknown_04;
    OpeningRenderListView list_08;
};

typedef char Opening_list_offset[
    offsetof(Opening, list_08) == 0x08 ? 1 : -1];

bool Opening::render()
{
    if (g_render_mode_manager.begin_frame()) {
        g_render_mode_manager.prepare_frame();
        list_08.render();
        g_render_mode_manager.finish_frame();
        return true;
    }
    return false;
}

struct CLoadingSV {
    virtual void loading_slot_0();
    virtual void loading_slot_1();
    virtual bool render();

    unsigned unknown_04;
    UiSprite94 sprite_08;
    unsigned char reserved_9c[0x1c];
    unsigned short phase_b8;
};

typedef char CLoadingSV_sprite_offset[
    offsetof(CLoadingSV, sprite_08) == 0x08 ? 1 : -1];
typedef char CLoadingSV_phase_offset[
    offsetof(CLoadingSV, phase_b8) == 0xb8 ? 1 : -1];

bool CLoadingSV::render()
{
    if (g_render_mode_manager.begin_frame()) {
        g_render_mode_manager.prepare_frame();
        g_render_mode_manager.draw_rect(
            0.0f,
            0.0f,
            640.0f,
            480.0f,
            0xff000000u,
            1);

        unsigned short phase = phase_b8;
        const unsigned int *methods = sprite_08.vtable;
        float phase_angle = static_cast<float>(phase) * 5.0;
        int alpha = static_cast<int>(
            lookup_orientation_cosine_quantized_abs(phase_angle) * 127.0);
        reinterpret_cast<UiSprite94::SetColor>(methods[1])(
            &sprite_08,
            (static_cast<unsigned>(static_cast<signed char>(alpha) + 127) << 24)
                | 0x00ffffffu);
        sprite_08.render(512.0f, 448.0f);

        g_render_mode_manager.finish_frame();
        return true;
    }
    return false;
}

} // namespace th105
