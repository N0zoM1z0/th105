#include "ProfileMenu.hpp"
extern "C" th105::ProfileNameList g_profile_name_list;
extern "C" const char profile_name_empty[];
extern "C" const char profile_file_extension[];
extern "C" const char profile_copy_suffix[];
extern "C" int __cdecl update_profile_confirmation();
extern "C" int __cdecl update_profile_message();
extern "C" bool __cdecl profile_string_equals(const th105::MenuString28 *, const char *);
extern "C" void __cdecl dispatch_indexed_event(unsigned);
th105::ProfileStringTemporary __cdecl concatenate_profile_string(
    const th105::MenuString28 &, const char *);
namespace th105 {
bool CProfileMenu::update_state_one()
{
    switch (substate_344) {
    case 0: {
        guides_5a4[1].visible = true;
        signed char result = editor_3b0.update_selection();
        if (result > 0) {
            dispatch_indexed_event(0x28);
            label_37c->enabled = false;
            editor_3b0.read_profile_name(reinterpret_cast<MenuString28 *>(&string_56c));
            if (!profile_string_equals(reinterpret_cast<MenuString28 *>(&string_56c), profile_name_empty)) {
                reinterpret_cast<MenuString28 *>(&string_550)->assign(
                    concatenate_profile_string(*reinterpret_cast<MenuString28 *>(&string_56c), profile_file_extension));
                if (g_profile_name_list.contains(reinterpret_cast<MenuString28 *>(&string_550))) {
                    reinterpret_cast<MenuString28 *>(&string_588)->assign(
                        concatenate_profile_string(*reinterpret_cast<MenuString28 *>(&string_56c), profile_copy_suffix));
                    show_profile_message(string_588.c_str(), 0);
                    substate_344 = 3;
                } else {
                    substate_344 = commit_state_one() ? 1 : 2;
                }
            } else {
                state_340 = 0;
            }
        } else if (result < 0) {
            dispatch_indexed_event(0x29);
            label_37c->enabled = false;
            state_340 = 0;
        }
        break;
    }
    case 1:
    case 2:
        guides_5a4[2].visible = true;
        if (update_profile_confirmation() != 0) state_340 = 0;
        break;
    case 3:
        guides_5a4[3].visible = true;
        switch (update_profile_message()) {
        case 2:
        case 4:
            state_340 = 0;
            break;
        case 3:
            substate_344 = commit_state_one() ? 1 : 2;
            break;
        }
        break;
    }
    return true;
}
}
