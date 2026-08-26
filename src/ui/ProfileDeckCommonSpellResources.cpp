#include "ProfileDeckEdit.hpp"
#include "../battle/ScenarioData.hpp"
#include "../assets/SpellTexturePool.hpp"

#include <deque>
#include <map>
#include <string.h>

namespace th105 {

typedef std::deque<unsigned> NativeSpellHandleDeque;
typedef std::map<int, SpellRecordView> NativeSpellMap;

extern CompositeTextureUploadState g_spell_composite_upload_state;
extern "C" const char profile_ui_effect_label[];
extern "C" const char common_spell_bar_path[];
extern "C" const char common_spell_name[];
extern "C" const char common_spell_csv_path[];

void ProfileDeckRefreshFacade::clear_common_resources()
{
    NativeSpellHandleDeque &handles =
        *reinterpret_cast<NativeSpellHandleDeque *>(&g_common_spell_image_handles);
    for (NativeSpellHandleDeque::iterator it = handles.begin();
         it != handles.end(); ++it) {
        g_title_resource_manager.release_title_resource_handle(*it);
    }
    handles.clear();

    g_title_resource_manager.release_title_resource_handle(
        g_common_spell_extra_handle);

    NativeSpellMap &records =
        *reinterpret_cast<NativeSpellMap *>(&g_common_spell_tree);
    records.clear();
}

unsigned char ProfileDeckRefreshFacade::reload_common_resources(
    unsigned char red,
    unsigned char green,
    unsigned char blue)
{
    unsigned int handle;
    g_common_spell_extra_handle = *g_title_resource_manager.load_texture(
        &handle, common_spell_bar_path, 0, 0);

    ScenarioEffectConfig128 config;
    config.duration_10c = 400;
    config.flag_110 = 0;
    config.flag_111 = 0;
    config.flag_112 = 0;
    config.option_120 = 0;
    config.option_124 = 0;
    config.mode_118 = 0;
    config.state_11c = 0;
    config.interval_114 = 100000;
    strcpy_s(config.text_000, 256, profile_ui_effect_label);

    config.color_100[0] = 0xff;
    config.color_100[2] = 0xff;
    config.color_100[4] = 0xff;
    config.color_100[1] = red;
    config.color_100[3] = green;
    config.count_108 = 14;
    config.duration_10c = 300;
    config.color_100[5] = blue;
    config.option_120 = 0;
    config.option_124 = 2;
    config.flag_111 = 1;

    reinterpret_cast<ScenarioEffectOwner194 *>(&g_spell_composite_upload_state)
        ->configure(&config);
    reinterpret_cast<SpellDataOwner *>(this)
        ->parse_spell_csv_and_build_card_resources(
            common_spell_name,
            common_spell_csv_path,
            &g_common_spell_image_handles,
            &g_common_spell_tree);
    return 1;
}

} // namespace th105
