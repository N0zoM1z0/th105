#include "engine/RenderModeManager.hpp"
#include "battle/BattleController.hpp"
#include "battle/EffectSprite.hpp"
#include "ui/UiPrimitives.hpp"

#include <stddef.h>

namespace th105 {

extern float __cdecl lookup_orientation_cosine_quantized_abs(float phase);


struct CLoadingWatchRenderView {
    virtual void loading_slot_0();
    virtual void loading_slot_1();
    virtual bool render();

    unsigned unknown_04;
    UiSprite94 sprite_08;
    unsigned short phase_9c;
    unsigned char reserved_9e[6];
};

typedef char CLoadingWatchRenderView_sprite_offset[
    offsetof(CLoadingWatchRenderView, sprite_08) == 0x08 ? 1 : -1];
typedef char CLoadingWatchRenderView_phase_offset[
    offsetof(CLoadingWatchRenderView, phase_9c) == 0x9c ? 1 : -1];

bool CLoadingWatchRenderView::render()
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

        unsigned short phase = phase_9c;
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
