// Canonical JP1.06a CScenarioData member destruction. The destructor is
// implicit: no redundant vptr publication or hand-authored cleanup sequence.
#include "battle/ScenarioData.hpp"
#include "assets/TextFontOwner.hpp"
#include <string.h>
extern "C" const char profile_ui_effect_label[];
namespace th105 {
// The common empty Environment base has its native+4 RTTI position.
class ScenarioLifetimeView : public ::Environment {
public:
 ScenarioLifetimeView();
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

// Full authored constructor; source1528/native1527 remains nonexact on
// persistent receiver/config register allocation. The config reference is
// actively used after the command registrations, matching its native lifetime.
ScenarioLifetimeView::ScenarioLifetimeView()
{
 TextFontConfig128 &config = config_1fc;
 script_35c.register_command<TCommand1<std::string> >(1, "");
 script_35c.register_command<TCommand1<std::string> >(0, "Label");
 script_35c.register_command<CComCharacter >(2, "Character");
 script_35c.register_command<TCommand2<std::string, std::string> >(3, "Face");
 script_35c.register_command<TCommand2<std::string, int> >(4, "Action");
 script_35c.register_command<TCommand4<std::string, int, float, float> >(5, "Object");
 script_35c.register_command<TCommand2<int, int> >(6, "Stage");
 script_35c.register_command<TCommand1<std::string> >(9, "Bgm");
 script_35c.register_command<TCommand1<std::string> >(9, "PlayBgm");
 script_35c.register_command<CCommand0 >(10, "StopBgm");
 script_35c.register_command<TCommand2<int, int> >(11, "FadeBgm");
 script_35c.register_command<TCommand3<std::string, int, bool> >(13, "CrossFadeBgm");
 script_35c.register_command<TCommand2<std::string, int> >(12, "PlaySE");
 script_35c.register_command<TCommand1<std::string> >(7, "Background");
 script_35c.register_command<TCommand3<std::string, int, int> >(8, "CG");
 script_35c.register_command<TCommand1<int> >(14, "Sleep");
 script_35c.register_command<TCommand1<int> >(15, "Next");
 script_35c.register_command<TCommand4<std::string, int, int, int> >(16, "Font");
 script_35c.register_command<TCommand1<std::string> >(17, "Color");
 script_35c.register_command<TCommand4<unsigned char, unsigned char, unsigned char, unsigned char> >(18, "Window");
 script_35c.register_command<TCommand1<int> >(19, "Hide");
 script_35c.register_command<CCommand0 >(20, "Result");
 script_35c.register_command<CCommand0 >(21, "StaffRoll");
 script_35c.register_command<CCommand0 >(22, "End");
 strcpy_s(config.face_000,256,profile_ui_effect_label);
 config.height_108=24;
 config.colors_100[0]=255;
 config.colors_100[2]=255;
 config.colors_100[4]=255;
 config.colors_100[1]=0;
 config.colors_100[3]=0;
 config.colors_100[5]=0;
 config.origin_x_118=0;
 config.origin_y_11c=8;
 config.spacing_x_120=0;
 config.spacing_y_124=8;
 config.outline_111=1;
 font_068.configure(&config);
}
}
