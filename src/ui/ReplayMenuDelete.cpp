#include "ReplayMenu.hpp"
#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" int __cdecl update_profile_message();
extern "C" int __cdecl update_profile_confirmation();
extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char *path);
extern "C" __declspec(dllimport) int __cdecl wsprintfA(
    char *buffer, const char *format, ...);
extern "C" const char replay_delete_prompt[];
extern "C" const char replay_delete_success[];
extern "C" const char replay_delete_failure[];

namespace th105 {

unsigned char CMenuReplay::update_delete_state()
{
    int *axis = &g_active_menu_input->hold.horizontal;
    switch (state_05) {
    case 0:
        if (axis[0] == 1) {
            dispatch_indexed_event(0x27);
            file_cursor_110.move_page_forward();
        } else if (axis[0] == -1) {
            dispatch_indexed_event(0x27);
            file_cursor_110.move_page_backward();
        }
        if (file_cursor_110.update())
            dispatch_indexed_event(0x27);
        if (axis[2] == 1) {
            dispatch_indexed_event(0x28);
            if (replay_list_08.row_is_directory(file_cursor_110.selection)) {
                entries_274.push_back(file_cursor_110.selection);
                replay_list_08.enter_directory(file_cursor_110.selection);
            } else {
                if (replay_list_08.row_at(file_cursor_110.selection)) {
                    show_profile_message(replay_delete_prompt, 0);
                    state_05 = 1;
                }
                return 1;
            }
        } else if (axis[3] == 1) {
            dispatch_indexed_event(0x29);
            if (replay_list_08.go_parent_directory()) {
                state_04 = 0;
                items_f0[0]->set_color(0xffffffffu);
                items_f0[2]->set_color(0xffffffffu);
                return 1;
            }
            file_cursor_110.selection = entries_274.back();
            entries_274.pop_back();
        } else {
            return 1;
        }
        refresh_file_list();
        return 1;
    case 1:
        switch (update_profile_message()) {
        case 2:
        case 4:
            state_05 = 0;
            return 1;
        case 3: {
            std::string *row = replay_list_08.row_at(file_cursor_110.selection);
            const char *name = row->c_str();
            const char *directory = replay_list_08.current_directory()->c_str();
            char path[260];
            wsprintfA(path, "%s/%s", directory, name);
            if (DeleteFileA(path)) {
                show_profile_result(replay_delete_success);
                refresh_file_list();
            } else {
                show_profile_result(replay_delete_failure);
            }
            state_05 = 2;
            return 1;
        }
        default:
            return 1;
        }
    case 2:
        if (update_profile_confirmation())
            state_05 = 0;
        return 1;
    default:
        return 1;
    }
}

} // namespace th105
