#pragma once

#include "ScriptCommandRegistry.hpp"
#include "SystemEffectManager.hpp"
#include "ui/DesignBaseLifetime.hpp"
#include "ui/UiPrimitives.hpp"

#include <list>
#include <map>
#include <stddef.h>
#include <string>

class SystemEffectObject;

namespace th105 {

struct ScenarioEffectConfig128 {
    char text_000[0x100];
    unsigned char color_100[6];
    unsigned char reserved_106[2];
    int count_108;
    int duration_10c;
    unsigned char flag_110;
    unsigned char flag_111;
    unsigned char flag_112;
    unsigned char reserved_113;
    int interval_114;
    int mode_118;
    int state_11c;
    int option_120;
    int option_124;
};

typedef char ScenarioEffectConfig128_size_must_be_0x128[
    sizeof(ScenarioEffectConfig128) == 0x128 ? 1 : -1];

struct ScenarioEffectOwner194 {
    void *field_000;
    void *field_004;
    void *field_008;
    ScenarioEffectConfig128 config_00c;
    unsigned char reserved_134[0x10];
    void *field_144;
    unsigned char reserved_148[0x0c];
    unsigned int *colors_154;
    unsigned int *allocated_colors_158;
    std::list<void *> payloads_15c;
    unsigned int packed_color_168;
    unsigned int field_16c;
    std::string text_170;
    unsigned int field_18c;
    unsigned int field_190;

    void configure(const ScenarioEffectConfig128 *config);
};

typedef char ScenarioEffectOwner194_size_must_be_0x194[
    sizeof(ScenarioEffectOwner194) == 0x194 ? 1 : -1];

// The result resource owns one CDesignBase, four primary design objects, three
// secondary position objects, one tile, and three parallel value/color/scale
// arrays.  Runtime methods below independently exercise every named tail field.
struct ScenarioResultPositionObject {
    virtual void slot_00();
    virtual void set_color(unsigned int color);
    float x_04;
    float y_08;
    unsigned char reserved_0c[8];
    unsigned char enabled_14;
};

struct ScenarioResultSecondaryObject {
    void *vtable_00;
    unsigned char reserved_04[8];
    float x_0c;
    float y_10;
};

struct ScenarioResultResource {
    unsigned char state_000;
    signed char phase_001;
    unsigned char reserved_002[2];
    int counter_004;
    CDesignBase design_008;
    ScenarioResultPositionObject *primary_03c[4];
    ScenarioResultSecondaryObject *secondary_04c[3];
    unsigned int texture_058;
    UiTileA4 tile_05c;
    int values_100[3];
    unsigned int colors_10c[3];
    float scales_118[3];
    unsigned char alpha_124;
    unsigned char reserved_125[3];

    ScenarioResultResource();
    ~ScenarioResultResource();
    void hide_and_reset();
    void add_nonnegative(int first, int second, int third);
    void enter_phase_three();
    void reset();
    void set_entry_level(int index, int value);
    void render();
    bool update();
};

typedef char ScenarioResultResource_size_must_be_0x128[
    sizeof(ScenarioResultResource) == 0x128 ? 1 : -1];
typedef char ScenarioResultResource_design_offset_must_be_0x08[
    offsetof(ScenarioResultResource, design_008) == 0x08 ? 1 : -1];
typedef char ScenarioResultResource_tile_offset_must_be_0x5c[
    offsetof(ScenarioResultResource, tile_05c) == 0x5c ? 1 : -1];
typedef char ScenarioResultResource_values_offset_must_be_0x100[
    offsetof(ScenarioResultResource, values_100) == 0x100 ? 1 : -1];
typedef char ScenarioResultResource_alpha_offset_must_be_0x124[
    offsetof(ScenarioResultResource, alpha_124) == 0x124 ? 1 : -1];

struct ScenarioRenderEntry9C {
    unsigned int resource_handle_000;
    UiSprite94 sprite_004;
    unsigned char reserved_098[4];
};

typedef char ScenarioRenderEntry9C_size_must_be_0x9c[
    sizeof(ScenarioRenderEntry9C) == 0x9c ? 1 : -1];

struct ScenarioTextEntryDC {
    unsigned int resource_handle_000;
    UiSprite94 sprite_004;
    std::string text_098;
    unsigned char flags_0b4[4];
    int values_0b8[7];
    signed char flags_0d4[6];
    unsigned char reserved_0da[2];

    void render_dynamic();
};

typedef char ScenarioTextEntryDC_size_must_be_0xdc[
    sizeof(ScenarioTextEntryDC) == 0xdc ? 1 : -1];

class CScenarioData {
public:
    virtual void configure(int scenario_id);
    void set_effect_color_bytes(
        unsigned char c1, unsigned char c3, unsigned char c5);
    virtual void clear_runtime();
    virtual int update();
    virtual void render();

    SystemEffectManager< ::SystemEffectObject> system_effects_004;
    int scenario_id_064;
    ScenarioEffectOwner194 effect_owner_068;
    ScenarioEffectConfig128 effect_config_1fc;
    int field_324;
    int field_328;
    std::map<std::string, ScenarioTextEntryDC> text_entries_32c;
    std::list<ScenarioRenderEntry9C> render_entries_338;
    std::list<ScenarioRenderEntry9C> render_entries_344;
    std::list<ScenarioRenderEntry9C> render_entries_350;
    CScript script_35c;
    ScenarioResultResource result_resources_390;
    std::string string_4b8;
    std::string string_4d4;
    std::string string_4f0;
    unsigned char state_50c;
    unsigned char state_50d;
    unsigned char state_50e;
    unsigned char state_50f;
    unsigned char state_510;
    unsigned char state_511;
    unsigned char reserved_512[2];
    int field_514;
    int field_518;
    int field_51c;
    int field_520;

    void reset_runtime_state();
};

typedef char CScenarioData_size_must_be_0x524[
    sizeof(CScenarioData) == 0x524 ? 1 : -1];
typedef char CScenarioData_map_offset_must_be_0x32c[
    offsetof(CScenarioData, text_entries_32c) == 0x32c ? 1 : -1];
typedef char CScenarioData_script_offset_must_be_0x35c[
    offsetof(CScenarioData, script_35c) == 0x35c ? 1 : -1];
typedef char CScenarioData_result_offset_must_be_0x390[
    offsetof(CScenarioData, result_resources_390) == 0x390 ? 1 : -1];

} // namespace th105
