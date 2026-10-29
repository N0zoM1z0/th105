// CScenarioData primary vtable slot 0x0c, JP1.06a 0x00457F90.
// Pointer-only render view. Real owned-member layouts are retained; this TU
// does not construct or destroy the view. See SCENARIO_RENDER_2026_10_29.md.
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

struct ScenarioRenderSprite94 {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void render(float x, float y);

    unsigned char unknown_004[0x84];
    float scale_x_088;
    float scale_y_08c;
    unsigned char unknown_090[4];
};
typedef char CheckRenderSprite94[sizeof(ScenarioRenderSprite94) == 0x94 ? 1 : -1];

struct ScenarioRenderDrawEntry9C {
    unsigned int resource_handle_000;
    ScenarioRenderSprite94 sprite_004;
    unsigned char tail_098[4];
};
typedef char CheckRenderEntry9C[sizeof(ScenarioRenderDrawEntry9C) == 0x9c ? 1 : -1];

struct ScenarioTextDrawEntryDC {
    unsigned int resource_handle_000;
    ScenarioRenderSprite94 sprite_004;
    std::string text_098;
    unsigned char flags_0b4[4];
    int values_0b8[7];
    signed char flags_0d4[6];
    unsigned char unknown_0da[2];

    void render_dynamic();
};
typedef char CheckTextEntryDC[sizeof(ScenarioTextDrawEntryDC) == 0xdc ? 1 : -1];

typedef TextFontOwner194 ScenarioRenderFont194;
typedef TextFontConfig128 ScenarioRenderConfig128;

struct ScenarioRenderResult128 {
    unsigned char storage_000[0x128];
    void render_result();
};

class CScenarioDataRenderView : public ::Environment {
public:
    virtual void configure(int scenario_id);
    virtual void clear_runtime();
    virtual signed char update();
    virtual void render();

    SystemEffectManager< ::SystemEffectObject> system_effects_004;
    int scenario_id_064;
    ScenarioRenderFont194 effect_owner_068;
    ScenarioRenderConfig128 effect_config_1fc;
    int field_324;
    int field_328;
    std::map<std::string, ScenarioTextDrawEntryDC> text_entries_32c;
    std::list<ScenarioRenderDrawEntry9C> render_entries_338;
    std::list<ScenarioRenderDrawEntry9C> render_entries_344;
    std::list<ScenarioRenderDrawEntry9C> render_entries_350;
    CScript script_35c;
    ScenarioRenderResult128 result_resources_390;
    std::string string_4b8;
    std::string string_4d4;
    std::string string_4f0;
    unsigned char tail_50c[8];
    int field_514,field_518,field_51c,field_520;
};

typedef char CheckScenarioRender524[sizeof(CScenarioDataRenderView) == 0x524 ? 1 : -1];
typedef char CheckMap32c[offsetof(CScenarioDataRenderView, text_entries_32c) == 0x32c ? 1 : -1];
typedef char CheckList338[offsetof(CScenarioDataRenderView, render_entries_338) == 0x338 ? 1 : -1];
typedef char CheckList344[offsetof(CScenarioDataRenderView, render_entries_344) == 0x344 ? 1 : -1];
typedef char CheckList350[offsetof(CScenarioDataRenderView, render_entries_350) == 0x350 ? 1 : -1];
typedef char CheckResult390[offsetof(CScenarioDataRenderView, result_resources_390) == 0x390 ? 1 : -1];

void CScenarioDataRenderView::render()
{
    g_render_mode_manager.set_blend_mode(1);

    std::list<ScenarioRenderDrawEntry9C>::iterator render_it;
    render_it = render_entries_338.begin();
    for (; render_it != render_entries_338.end(); ++render_it)
        render_it->sprite_004.render(0.0f, 0.0f);

    render_it = render_entries_344.begin();
    for (; render_it != render_entries_344.end(); ++render_it)
        render_it->sprite_004.render(0.0f, 0.0f);

    for (std::map<std::string, ScenarioTextDrawEntryDC>::iterator it = text_entries_32c.begin();
         it != text_entries_32c.end(); ++it) {
        if (it->second.resource_handle_000 != 0) {
            if (it->second.flags_0d4[3] == 0)
                it->second.render_dynamic();
        }
    }

    for (std::map<std::string, ScenarioTextDrawEntryDC>::iterator it = text_entries_32c.begin();
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

            if (tail_50c[1] != 0) {
                render_it = render_entries_350.begin();
                for (; render_it != render_entries_350.end(); ++render_it) {
                    ScenarioRenderSprite94 *sprite = &render_it->sprite_004;
                    float scale = static_cast<float>(
                        static_cast<double>(field_324) / 40.0);
                    sprite->scale_x_088 = 1.0f;
                    sprite->scale_y_08c = scale;
                    render_it->sprite_004.render(0.0f, 394.0f);
                }
            }
        } else if (tail_50c[1] != 0) {
            render_it = render_entries_350.begin();
            for (; render_it != render_entries_350.end(); ++render_it) {
                ScenarioRenderSprite94 *sprite = &render_it->sprite_004;
                sprite->scale_x_088 = 1.0f;
                sprite->scale_y_08c = 1.0f;
                render_it->sprite_004.render(0.0f, 392.0f);
            }
        }
    }

    result_resources_390.render_result();
}

} // namespace th105
