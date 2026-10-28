#include "ui/SelectConstructor.hpp"

namespace th105 {
CSelect::~CSelect()
{
    for(int i=0;i<15;++i) {
        effects_7fc[i][0].clear_effects_and_resources();
        effects_7fc[i][1].clear_effects_and_resources();
    }
    g_title_resource_manager.release_title_resource_handle(back_textures_61c[0].value);
    g_title_resource_manager.release_title_resource_handle(back_textures_61c[1].value);
    g_title_resource_manager.release_title_resource_handle(extra_textures_48c[0].value);
    g_title_resource_manager.release_title_resource_handle(extra_textures_48c[1].value);
    g_title_resource_manager.release_title_resource_handle(cursor_textures_184[0].value);
    g_title_resource_manager.release_title_resource_handle(cursor_textures_184[1].value);
    g_title_resource_manager.release_title_resource_handle(field_60c);
    g_title_resource_manager.release_title_resource_handle(random_names_3f4.value);
    g_title_resource_manager.release_title_resource_handle(names_34c.value);
    g_title_resource_manager.release_title_resource_handle(background_2b4.value);
    character_design_150.virtual_cleanup();
    background_design_1984.virtual_cleanup();
    for(int i=0;i<choice_count_094;++i) {
        g_title_resource_manager.release_title_resource_handle(pictures_19b8[i].value);
        g_title_resource_manager.release_title_resource_handle(names_19f8[i].value);
    }
    g_title_resource_manager.release_title_resource_handle(music_2ccc.value);
}
}
