#include "ScenarioData.hpp"

namespace th105 {

// This Scenario TU keeps three VC8 checked-STL member bodies out of line.
// The owning std types remain in ScenarioData.hpp; these narrow views expose
// only the target-observed member ABI at the call sites.
struct ScenarioStringAssignBytesView {
    void assign_bytes(const char *source, unsigned int length);
};

struct ScenarioRenderListClearView {
    void clear_entries();
};

struct ScenarioTextMapIteratorIncrementView {
    void increment();
};

void CScenarioData::configure(int scenario_id)
{
    scenario_id_064 = scenario_id;
    ScenarioEffectConfig128 *config = &effect_config_1fc;
    field_328 = static_cast<int>(0x80000000u);

    config->color_100[0] = 0xff;
    config->color_100[2] = 0xff;
    config->color_100[4] = 0xff;
    config->color_100[1] = 0xc8;
    config->color_100[3] = 0xc8;
    config->color_100[5] = 0xc8;

    effect_owner_068.configure(config);
    result_resources_390.reset();
}

void CScenarioData::set_effect_color_bytes(
    unsigned char c1, unsigned char c3, unsigned char c5)
{
    ScenarioEffectConfig128 *config = &effect_config_1fc;
    config->color_100[0] = 0xff;
    config->color_100[2] = 0xff;
    config->color_100[4] = 0xff;
    config->color_100[1] = c1;
    config->color_100[3] = c3;
    config->color_100[5] = c5;
    effect_owner_068.configure(config);
}

void CScenarioData::clear_runtime()
{
    text_entries_32c.clear();
    system_effects_004.release_all_system_effects();
    script_35c.clear_commands();
}

} // namespace th105

namespace th105 {

void CScenarioData::reset_runtime_state()
{
    std::map<std::string, ScenarioTextEntryDC>::iterator it =
        text_entries_32c.begin();
    while (it != text_entries_32c.end()) {
        ScenarioTextEntryDC &entry = it->second;
        entry.values_0b8[5] = 30;
        entry.values_0b8[2] = 400;
        entry.values_0b8[3] = 0;
        entry.values_0b8[4] = 0;
        entry.flags_0d4[5] = 0;
        entry.flags_0d4[2] = 0;
        entry.flags_0d4[3] = 0;
        entry.flags_0d4[4] = 0;
        reinterpret_cast<ScenarioTextMapIteratorIncrementView *>(&it)
            ->increment();
    }

    state_50c = 0;
    state_50d = 0;
    state_50f = 0;
    state_50e = 0;
    state_510 = 0;
    state_511 = 0;
    field_514 = 0;
    reinterpret_cast<ScenarioStringAssignBytesView *>(&string_4b8)
        ->assign_bytes("", 0);
    reinterpret_cast<ScenarioStringAssignBytesView *>(&string_4d4)
        ->assign_bytes("", 0);
    reinterpret_cast<ScenarioStringAssignBytesView *>(&string_4f0)
        ->assign_bytes("", 0);
    field_324 = 0;
    field_518 = 0;
    field_51c = 0;
    field_520 = 20;
    reinterpret_cast<ScenarioRenderListClearView *>(&render_entries_338)
        ->clear_entries();
    reinterpret_cast<ScenarioRenderListClearView *>(&render_entries_344)
        ->clear_entries();
    reinterpret_cast<ScenarioRenderListClearView *>(&render_entries_350)
        ->clear_entries();
    system_effects_004.release_all_system_effects();
}

} // namespace th105

namespace th105 {

float __cdecl scenario_text_wave(int value);

// Current 0x00454DA0 codegen requires sprite_04 to be a real polymorphic
// 0x94-byte member: VC8 reloads its vptr after the color virtual, then safely
// preserves that vptr across scenario_text_wave before the render virtual.
class ScenarioTextSprite94View {
public:
    virtual void slot_00();
    virtual void set_color_04(unsigned int color);
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void render_1c(float x, float y);

    unsigned int reserved_04;
    unsigned char reserved_08[0x8c];
};

typedef char ScenarioTextSprite94View_size_must_be_0x94[
    sizeof(ScenarioTextSprite94View) == 0x94 ? 1 : -1];

struct ScenarioTextEntryRenderViewDC {
    unsigned int resource_handle_000;
    ScenarioTextSprite94View sprite_004;
    std::string text_098;
    unsigned char flags_0b4[4];
    int values_0b8[7];
    signed char flags_0d4[6];
    unsigned char reserved_0da[2];

    void render_dynamic();
    int update_dynamic_state();
};

typedef char ScenarioTextEntryRenderViewDC_size_must_be_0xdc[
    sizeof(ScenarioTextEntryRenderViewDC) == 0xdc ? 1 : -1];

void ScenarioTextEntryRenderViewDC::render_dynamic()
{
    if (flags_0d4[5] == 0)
        return;

    if (flags_0d4[3])
        sprite_004.set_color_04(0xffffffffu);
    else
        sprite_004.set_color_04(0x80ffffffu);

    sprite_004.render_1c(
        static_cast<float>(
            static_cast<double>(values_0b8[0]) -
            ((1.0 - scenario_text_wave(3 * values_0b8[5])) *
                 values_0b8[2] + values_0b8[4]) * flags_0d4[1]),
        static_cast<float>(values_0b8[3] + values_0b8[1] + values_0b8[4]));
}

} // namespace th105


namespace th105 {

int ScenarioTextEntryRenderViewDC::update_dynamic_state()
{
    if (flags_0d4[2]) {
        if (values_0b8[5] > 0)
            --values_0b8[5];
        flags_0d4[5] = 1;
    } else if (values_0b8[5] < 30) {
        ++values_0b8[5];
        if (values_0b8[5] >= 30)
            flags_0d4[5] = 0;
    }

    if (flags_0d4[3]) {
        if (values_0b8[4] > 0)
            values_0b8[4] -= 2;
    } else if (values_0b8[4] < 20) {
        values_0b8[4] += 2;
    }
    return values_0b8[4];
}

} // namespace th105
