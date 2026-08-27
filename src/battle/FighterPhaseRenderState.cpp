#include "battle/EffectSprite.hpp"
#include "battle/BattleRenderHelpers.hpp"
#include "engine/RenderModeManager.hpp"

#include <list>
#include <stddef.h>

namespace th105 {

struct PhaseRenderEntry {
    CSpriteEx sprite;
    signed char blend_mode;
};

typedef char PhaseRenderEntry_sprite_size[(offsetof(PhaseRenderEntry, blend_mode) == 0xe8) ? 1 : -1];

struct FighterPhaseRenderState {
    std::list<PhaseRenderEntry> entries;
    signed char period_0c;
    unsigned char reserved_0d;
    signed short alpha_divisor_0e;
    unsigned color_mask_10;

    void render_45aa00();
    void enqueue_45ad40(const CSpriteEx *source, signed char blend);
};

typedef char PhaseRenderState_period_off[(offsetof(FighterPhaseRenderState, period_0c) == 0x0c) ? 1 : -1];
typedef char PhaseRenderState_divisor_off[(offsetof(FighterPhaseRenderState, alpha_divisor_0e) == 0x0e) ? 1 : -1];
typedef char PhaseRenderState_mask_off[(offsetof(FighterPhaseRenderState, color_mask_10) == 0x10) ? 1 : -1];

void FighterPhaseRenderState::render_45aa00()
{
    if (entries.size() == 0 || period_0c <= 0)
        return;

    std::list<PhaseRenderEntry>::iterator end = entries.end();
    std::list<PhaseRenderEntry>::iterator it = entries.begin();
    CSpriteEx sprite;
    int index = 0;
    for (; it != end; ++it, ++index) {
        if (index % period_0c != static_cast<unsigned>(period_0c - 1))
            continue;

        switch (it->blend_mode) {
        case 0:
            g_render_mode_manager.set_blend_mode(1);
            break;
        case 1:
            g_render_mode_manager.set_blend_mode(2);
            break;
        case 2:
            g_render_mode_manager.set_blend_mode(3);
            break;
        }

        const unsigned source_color = it->sprite.vertices_08[0].color;
        sprite = it->sprite;

        const unsigned alpha =
            (static_cast<unsigned>(source_color >> 24) * index) /
            alpha_divisor_0e;
        const unsigned color = (source_color & color_mask_10) | (alpha << 24);
        sprite.vertices_08[3].color = color;
        sprite.vertices_08[2].color = color;
        sprite.vertices_08[1].color = color;
        sprite.vertices_08[0].color = color;

        g_battle_background_layout.transform_sprite(&sprite);
        sprite.finalize_render();
    }
}

void FighterPhaseRenderState::enqueue_45ad40(
    const CSpriteEx *source, signed char blend)
{
    PhaseRenderEntry entry;
    entries.push_back(entry);
    entries.back().sprite = *source;
    entries.back().blend_mode = blend;
    if (static_cast<int>(entries.size()) > alpha_divisor_0e)
        entries.pop_front();
}

} // namespace th105
