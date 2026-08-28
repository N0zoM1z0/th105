#include "ui/Title.hpp"
#include <new>

namespace th105 {

// CTitle's two-level state machine: scene-mode transition dispatch first,
// then the MenuCursorState-owned title selection. Typed new expressions keep
// all six target allocation-cleanup states compiler-generated.
extern "C" int g_scene_mode;
extern "C" int g_next_scene_mode;
extern "C" bool __cdecl has_ui_selection_state_changed();
extern "C" void __cdecl dispatch_indexed_event(unsigned int index);
extern "C" signed char *__cdecl get_combined_menu_input_counters();

void *__cdecl get_player2_input();
void __cdecl prepare_title_match_mode(int game_mode, int setup_option);
void __cdecl fade_bgm(int duration, int target);
void __cdecl install_menu_object(void *object);

class CMenuConnect { public: CMenuConnect(); unsigned char storage_00[0x118C]; };
class CMenuReplay { public: CMenuReplay(); unsigned char storage_00[0x280]; };
class CMenuMusic { public: CMenuMusic(); unsigned char storage_00[0x1EC]; };
class CMenuResult { public: CMenuResult(); unsigned char storage_00[0x1148]; };
class CProfileMenu { public: CProfileMenu(); unsigned char storage_00[0x8EC]; };
class CMenuConfig { public: CMenuConfig(); unsigned char storage_00[0x28C]; };

typedef char ConnectSize[sizeof(CMenuConnect) == 0x118C ? 1 : -1];
typedef char ReplaySize[sizeof(CMenuReplay) == 0x280 ? 1 : -1];
typedef char MusicSize[sizeof(CMenuMusic) == 0x1EC ? 1 : -1];
typedef char ResultSize[sizeof(CMenuResult) == 0x1148 ? 1 : -1];
typedef char ProfileSize[sizeof(CProfileMenu) == 0x8EC ? 1 : -1];
typedef char ConfigSize[sizeof(CMenuConfig) == 0x28C ? 1 : -1];

int CTitle::update()
{
    advance_menu_item_wave();

    switch (g_scene_mode) {
    case 8: prepare_title_match_mode(4, 1); return 8;
    case 9: prepare_title_match_mode(5, 1); return 9;
    case 12: prepare_title_match_mode(6, 2); return 12;
    case 6:
        if (g_next_scene_mode != 7) {
            if (reinterpret_cast<unsigned char *>(get_player2_input())[0xEC] == 0)
                prepare_title_match_mode(0, 2);
            else
                prepare_title_match_mode(3, 2);
        }
        fade_bgm(1000, 0);
        return 6;
    default: break;
    }

    if (has_ui_selection_state_changed())
        return 2;

    int *input = reinterpret_cast<int *>(get_combined_menu_input_counters());
    if (cursor_210.update())
        dispatch_indexed_event(0x27);

    if (input[2] == 1) {
        dispatch_indexed_event(0x28);
        switch (cursor_210.selection) {
        case 0: prepare_title_match_mode(0, 1); return 16;
        case 1: prepare_title_match_mode(1, 0); return 3;
        case 2: prepare_title_match_mode(2, 1); return 3;
        case 3: prepare_title_match_mode(3, 1); return 3;
        case 4: install_menu_object(new CMenuConnect()); break;
        case 5: prepare_title_match_mode(8, 0); return 3;
        case 6: install_menu_object(new CMenuReplay()); break;
        case 7: install_menu_object(new CMenuMusic()); break;
        case 8: install_menu_object(new CMenuResult()); break;
        case 9: install_menu_object(new CProfileMenu()); break;
        case 10: install_menu_object(new CMenuConfig()); break;
        case 11: return -1;
        default: break;
        }
    }

    if (input[3] == 1) {
        dispatch_indexed_event(0x29);
        cursor_210.selection = 11;
    }
    return 2;
}

} // namespace th105
