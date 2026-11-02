#include "ui/ProfileSubmenus.hpp"

extern "C" __declspec(dllimport) int __cdecl wsprintfA(char *, const char *, ...);
extern "C" const char profile_stand_path_format[];

namespace th105 {
const char *__cdecl character_key_to_name(int character_key);

void CProfileCharacterSelect::refresh_character_preview()
{
    g_title_resource_manager.release_title_resource_handle(texture_04);
    texture_04 = 0;
    if (character_a0 == -1)
        return;

    char path[260];
    wsprintfA(path, profile_stand_path_format, character_key_to_name(character_a0));
    unsigned handle;
    texture_04 = *g_title_resource_manager.load_texture(&handle, path, 0, 0);
    if (texture_04 == 0)
        return;
    stand_08.set_texture(texture_04, 0, 0, 512, 480);
    stand_08.set_color(0xff808080u);
}
} // namespace th105
