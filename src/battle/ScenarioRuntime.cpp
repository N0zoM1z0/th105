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

void CScenarioData::configure(CInputManager *input)
{
    input_064 = input;
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
        entry.value_0cc = 30;
        entry.value_0c0 = 400;
        entry.value_0c4 = 0;
        entry.value_0c8 = 0;
        entry.flag_0d9 = 0;
        entry.flag_0d6 = 0;
        entry.flag_0d7 = 0;
        entry.flag_0d8 = 0;
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

void ScenarioTextEntryDC::render_dynamic()
{
    if (flag_0d9 == 0)
        return;

    if (flag_0d7)
        sprite_004.set_color(0xffffffffu);
    else
        sprite_004.set_color(0x80ffffffu);

    sprite_004.render(
        static_cast<float>(
            static_cast<double>(value_0b8) -
            ((1.0 - scenario_text_wave(3 * value_0cc)) *
                 value_0c0 + value_0c8) * flag_0d5),
        static_cast<float>(value_0c4 + value_0bc + value_0c8));
}

} // namespace th105


namespace th105 {

int ScenarioTextEntryDC::update_dynamic_state()
{
    if (flag_0d6) {
        if (value_0cc > 0)
            --value_0cc;
        flag_0d9 = 1;
    } else if (value_0cc < 30) {
        ++value_0cc;
        if (value_0cc >= 30)
            flag_0d9 = 0;
    }

    if (flag_0d7) {
        if (value_0c8 > 0)
            value_0c8 -= 2;
    } else if (value_0c8 < 20) {
        value_0c8 += 2;
    }
    return value_0c8;
}

} // namespace th105
