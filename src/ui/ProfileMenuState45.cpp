#include "ProfileMenu.hpp"

extern "C" const char profile_copy_prompt_suffix[];
extern "C" const char profile_delete_prompt_suffix[];
extern "C" int __cdecl update_profile_confirmation();
extern "C" int __cdecl update_profile_message();
th105::ProfileStringTemporary __cdecl concatenate_profile_string(
    const th105::MenuString28 &value,
    const char *suffix);

namespace th105 {

bool CProfileMenu::update_state_four()
{
    switch (substate_344) {
    case 0:
        guides_5a4[4].visible = true;
        switch (select_profile(reinterpret_cast<MenuString28 *>(&string_518),
            reinterpret_cast<MenuString28 *>(&string_534))) {
        case 1:
            reinterpret_cast<MenuString28 *>(&string_588)->assign(
                concatenate_profile_string(
                    *reinterpret_cast<MenuString28 *>(&string_534),
                    profile_copy_prompt_suffix));
            show_profile_message(string_588.c_str(), 0);
            substate_344 = 3;
            return true;
        case 2:
            state_340 = 0;
            return true;
        }
        break;
    case 1:
    case 2:
        guides_5a4[2].visible = true;
        if (update_profile_confirmation() != 0)
            substate_344 = 0;
        break;
    case 3:
        guides_5a4[3].visible = true;
        switch (update_profile_message()) {
        case 2:
        case 4:
            substate_344 = 0;
            break;
        case 3:
            substate_344 = commit_state_four() ? 1 : 2;
            break;
        default:
            return true;
        }
        break;
    }
    return true;
}

bool CProfileMenu::update_state_five()
{
    switch (substate_344) {
    case 0:
        guides_5a4[4].visible = true;
        switch (select_profile(reinterpret_cast<MenuString28 *>(&string_518),
            reinterpret_cast<MenuString28 *>(&string_534))) {
        case 1:
            reinterpret_cast<MenuString28 *>(&string_588)->assign(
                concatenate_profile_string(
                    *reinterpret_cast<MenuString28 *>(&string_534),
                    profile_delete_prompt_suffix));
            show_profile_message(string_588.c_str(), 0);
            substate_344 = 3;
            return true;
        case 2:
            state_340 = 0;
            return true;
        }
        break;
    case 1:
    case 2:
        guides_5a4[2].visible = true;
        if (update_profile_confirmation() != 0)
            substate_344 = 0;
        break;
    case 3:
        guides_5a4[3].visible = true;
        switch (update_profile_message()) {
        case 2:
        case 4:
            substate_344 = 0;
            break;
        case 3:
            substate_344 = commit_state_five() ? 1 : 2;
            break;
        default:
            return true;
        }
        break;
    }
    return true;
}

} // namespace th105
