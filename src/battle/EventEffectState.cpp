#include "EventEffectState.hpp"
#include "BattleBackgroundLayout.hpp"
#include "EffectSprite.hpp"
#include "engine/RenderModeManager.hpp"

namespace th105 {

int EventEffectStateView::set_event_id(int event_id)
{
    if (current_event_id == event_id)
        return event_id;
    current_event_id = event_id;
    return publish_stage_state(g_battle_transition_mode);
}

int EventEffectStateView::emit_effect(
    int effect_id, float x, float y, int flag_a, int flag_b)
{
    return emitter_48.emit(effect_id, x, y, flag_a, flag_b, 0);
}

int EventEffectStateView::dispatch_emitter_state(int state)
{
    return emitter_48.dispatch_state(state);
}


void EventEffectStateView::render_background_effects()
{
    g_render_mode_manager.set_blend_mode(1);
    g_render_mode_manager.set_mode(2);
    g_render_mode_manager.set_sampler_state(0, 2, 3);

    for (std::deque<BackgroundRenderEntry>::iterator it =
             background_entries_28.begin();
         it != background_entries_28.end(); ++it) {
        CSpriteEx *sprite = it->sprite;
        if (sprite != 0) {
            sprite->reset_transform();
            sprite->scale_x(3.0f);
            sprite->scale_y(3.0f);
            sprite->scale_z(3.0f);
            sprite->translate(0.0f, -100.0f, 0.0f);
            g_battle_background_layout.place_sprite(sprite, 1.0f, 1.0f);
            sprite->set_color((static_cast<unsigned int>(it->alpha) << 24) |
                              0x00ffffffu);
            sprite->finalize_render();
        } else if (it != background_entries_28.begin()) {
            g_render_mode_manager.draw_rect(
                0.0f, 0.0f, 640.0f, 480.0f,
                static_cast<unsigned int>(it->alpha) << 24, 1);
        }
    }

    g_render_mode_manager.set_sampler_state(0, 2, 1);
    g_render_mode_manager.set_mode(1);
}

} // namespace th105
