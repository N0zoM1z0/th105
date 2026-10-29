// Canonical JP1.06a CScenarioData member destruction. The destructor is
// implicit: no redundant vptr publication or hand-authored cleanup sequence.
#include "battle/ScenarioData.hpp"
#include "assets/TextFontOwner.hpp"
namespace th105 {
class ScenarioLifetimeView {
public:
 virtual void configure(int);
 virtual void clear_runtime();
 virtual int update();
 virtual void render();
 SystemEffectManager< ::SystemEffectObject> system_effects_004;
 int scenario_id_064;
 TextFontOwner194 font_068;
 TextFontConfig128 config_1fc;
 int field_324,field_328;
 std::map<std::string,ScenarioTextEntryDC> text_entries_32c;
 std::list<ScenarioRenderEntry9C> render_entries_338;
 std::list<ScenarioRenderEntry9C> render_entries_344;
 std::list<ScenarioRenderEntry9C> render_entries_350;
 CScript script_35c;
 ScenarioResultResource result_390;
 std::string string_4b8,string_4d4,string_4f0;
 unsigned char tail_50c[0x18];
};
typedef char ScenarioSize[sizeof(ScenarioLifetimeView)==0x524?1:-1];
typedef char ScenarioFontOffset[offsetof(ScenarioLifetimeView, font_068) == 0x68 ? 1 : -1];
typedef char ScenarioMapOffset[offsetof(ScenarioLifetimeView, text_entries_32c) == 0x32c ? 1 : -1];
typedef char ScenarioScriptOffset[offsetof(ScenarioLifetimeView, script_35c) == 0x35c ? 1 : -1];
typedef char ScenarioResultOffset[offsetof(ScenarioLifetimeView, result_390) == 0x390 ? 1 : -1];
// Unmapped emission helper only. It instantiates the implicit C++ destructor;
// no target address, authored bytes or runtime call is assigned to this helper.
void destroy_scenario_lifetime_probe(ScenarioLifetimeView *value) { delete value; }
}
