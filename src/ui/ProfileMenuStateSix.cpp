#include "ProfileMenu.hpp"

#include <string.h>

extern "C" th105::ProfileMenuController g_profile_menu_controller;
extern "C" th105::ProfileNameList g_profile_name_list;
extern "C" const char profile_name_empty[];
extern "C" const char profile_file_extension[];
extern "C" const char profile_copy_suffix[];

extern "C" int __stdcall select_profile_pair(
    th105::MenuString28 *selected,
    th105::MenuString28 *alternate);
extern "C" int __cdecl update_profile_confirmation();
extern "C" int __cdecl update_profile_message();
extern "C" bool __cdecl profile_string_equals(
    const th105::MenuString28 *value,
    const char *text);
th105::ProfileStringTemporary __cdecl concatenate_profile_string(
    const th105::MenuString28 &value,
    const char *suffix);
extern "C" void __cdecl dispatch_indexed_event(unsigned index);

namespace th105 {

bool CProfileMenu::update_state_six()
{
    switch (substate_344) {
    case 0: {
        guides_5a4[4].visible = true;
        switch (select_profile_pair(&string_518, &string_534)) {
        case 1:
            g_profile_menu_controller.set_mode(1);
            g_profile_menu_controller.select_profile(string_534.c_str());
            label_37c->enabled = true;
            substate_344 = 4;
            return true;
        case 2:
            state_340 = 0;
            return true;
        }
        break;
    }

    case 4: {
        guides_5a4[1].visible = true;
        signed char result = editor_3b0.update_selection();
        if (result > 0) {
            dispatch_indexed_event(0x28);
            label_37c->enabled = false;
            editor_3b0.read_profile_name(&string_56c);
            if (!profile_string_equals(&string_56c, profile_name_empty)) {
            string_550.assign(concatenate_profile_string(
                string_56c, profile_file_extension));

                if (_stricmp(string_550.c_str(), string_518.c_str()) != 0) {
                    if (g_profile_name_list.contains(&string_550)) {
                        string_588.assign(concatenate_profile_string(
                            string_56c, profile_copy_suffix));
                        show_profile_message(string_588.c_str(), 0);
                        substate_344 = 3;
                        return true;
                    }
                    goto commit_change;
                }
            }
        } else {
            if (result >= 0)
                break;
            dispatch_indexed_event(0x29);
            label_37c->enabled = false;
        }
        substate_344 = 0;
        break;
    }

    case 1:
    case 2:
        guides_5a4[2].visible = true;
        if (update_profile_confirmation() != 0)
            substate_344 = 0;
        break;

    case 3: {
        guides_5a4[3].visible = true;
        switch (update_profile_message()) {
        case 2:
        case 4:
            substate_344 = 0;
            break;
        case 3:
            goto commit_change;
        default:
            return true;
        }
        break;
    }

    default:
        break;
    }
    return true;

commit_change:
    substate_344 = commit_profile_change() ? 1 : 2;
    return true;
}

} // namespace th105
