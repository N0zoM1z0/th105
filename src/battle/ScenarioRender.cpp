#include "engine/Sprite.hpp"
#include "battle/ScenarioData.hpp"
// CScenarioData primary vtable slot 0x0c, JP1.06a 0x00457F90.
// Uses the shared scenario, text, list-entry and result owners.
// See SCENARIO_RENDER_2026_10_29.md.
#include "engine/RenderModeManager.hpp"
#include "battle/SystemEffectManager.hpp"
#include "assets/TextFontOwner.hpp"
#include "battle/ScriptCommandRegistry.hpp"
#include "ui/UiPrimitives.hpp"
#include <list>
#include <map>
#include <string>
#include <stddef.h>

namespace th105 {
struct CInputManager;

void CScenarioData::render()
{
    g_render_mode_manager.set_blend_mode(1);

    std::list<ScenarioRenderEntry9C>::iterator render_it;
    render_it = render_entries_338.begin();
    for (; render_it != render_entries_338.end(); ++render_it)
        render_it->sprite_004.render(0.0f, 0.0f);

    render_it = render_entries_344.begin();
    for (; render_it != render_entries_344.end(); ++render_it)
        render_it->sprite_004.render(0.0f, 0.0f);

    for (std::map<std::string, ScenarioTextEntryDC>::iterator it = text_entries_32c.begin();
         it != text_entries_32c.end(); ++it) {
        if (it->second.resource_handle_000 != 0) {
            if (it->second.flags_0d4[3] == 0)
                it->second.render_dynamic();
        }
    }

    for (std::map<std::string, ScenarioTextEntryDC>::iterator it = text_entries_32c.begin();
         it != text_entries_32c.end(); ++it) {
        if (it->second.resource_handle_000 != 0) {
            if (it->second.flags_0d4[3] != 0)
                it->second.render_dynamic();
        }
    }

    system_effects_004.render_each(&SystemEffectObjectBase::render_effect);
    g_render_mode_manager.set_blend_mode(1);

    if (field_324 != 0) {
        if (field_328 != 0) {
            const float right = static_cast<float>(
                static_cast<double>(field_324) * 2.0 + 392.0);
            g_render_mode_manager.draw_rect(
                8.0f, 392.0f, 632.0f, right,
                static_cast<unsigned>(field_328), 1);

            if (state_50d != 0) {
                render_it = render_entries_350.begin();
                for (; render_it != render_entries_350.end(); ++render_it) {
                    CSprite *sprite = &render_it->sprite_004;
                    float scale = static_cast<float>(
                        static_cast<double>(field_324) / 40.0);
                    sprite->scale_x_88 = 1.0f;
                    sprite->scale_y_8c = scale;
                    render_it->sprite_004.render(0.0f, 394.0f);
                }
            }
        } else if (state_50d != 0) {
            render_it = render_entries_350.begin();
            for (; render_it != render_entries_350.end(); ++render_it) {
                CSprite *sprite = &render_it->sprite_004;
                sprite->scale_x_88 = 1.0f;
                sprite->scale_y_8c = 1.0f;
                render_it->sprite_004.render(0.0f, 392.0f);
            }
        }
    }

    result_resources_390.render();
}

} // namespace th105
