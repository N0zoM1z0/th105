#include "ProfileMenu.hpp"

extern "C" unsigned char *__cdecl _mbschr(
    const unsigned char *text, unsigned int ch);
extern "C" __declspec(dllimport) int __stdcall CopyFileA(
    const char *existing_path, const char *new_path, int fail_if_exists);
extern "C" __declspec(dllimport) int __stdcall DeleteFileA(const char *path);
extern "C" __declspec(dllimport) int __stdcall MoveFileA(
    const char *old_path, const char *new_path);

extern "C" const char profile_directory_prefix[];
extern "C" const char profile_copy_stem_suffix[];
extern "C" const char profile_file_extension[];
extern "C" const char profile_copy_success_text[];
extern "C" const char profile_copy_failure_text[];
extern "C" const char profile_delete_success_text[];
extern "C" const char profile_delete_failure_text[];
extern "C" const char profile_rename_success_text[];
extern "C" const char profile_rename_failure_text[];
extern "C" const char profile_commit_failure_suffix[];
extern "C" const char profile_commit_success_suffix[];

namespace th105 {

// Current 0x00429970 initializes its hidden return slot as a 0x1c-byte
// MenuString28 (capacity 15, size zero, inline buffer) before appending the
// supplied value.  Keep that concrete return contract here instead of the
// different temporary-dtor view used by other translation units.
MenuString28 __cdecl concatenate_profile_prefix(
    const char *prefix, const MenuString28 &value);

// Current 0x00408C40 has the same hidden-return MenuString28 layout.  This
// ProfileMenu commit TU inlines that temporary's SSO destructor; the accepted
// state-six TU deliberately retains its out-of-line temporary-dtor view because
// that caller has a different visibility/codegen boundary.
MenuString28 __cdecl concatenate_profile_commit_string(
    const MenuString28 &value, const char *suffix);

namespace {

struct MenuStringAppendBytesView {
    MenuString28 &append_bytes(const char *text, unsigned int count);
};

struct MenuStringAssignBytesView {
    MenuString28 &assign_bytes(const char *text, unsigned int count);
};

struct ProfileMenuBaseDataCommitView {
    void initialize_defaults();
    bool save_to_profile(const char *path);
};

} // namespace

bool CProfileMenu::commit_state_one()
{
    MenuString28 message;

    if (_mbschr(
            reinterpret_cast<const unsigned char *>(string_56c.c_str()), '/') ||
        _mbschr(
            reinterpret_cast<const unsigned char *>(string_56c.c_str()), '\\')) {
        message.assign(concatenate_profile_commit_string(
            *reinterpret_cast<MenuString28 *>(&string_56c), profile_commit_failure_suffix));
        show_profile_result(message.c_str());
        return false;
    }

    ProfileMenuBaseData data;
    reinterpret_cast<ProfileMenuBaseDataCommitView *>(&data)
        ->initialize_defaults();

    if (reinterpret_cast<ProfileMenuBaseDataCommitView *>(&data)
            ->save_to_profile(string_550.c_str())) {
        message.assign(concatenate_profile_commit_string(
            *reinterpret_cast<MenuString28 *>(&string_56c), profile_commit_success_suffix));
        show_profile_result(message.c_str());
        initialize_profile_menu();
        return true;
    }

    message.assign(concatenate_profile_commit_string(
        *reinterpret_cast<MenuString28 *>(&string_56c), profile_commit_failure_suffix));
    show_profile_result(message.c_str());
    return false;
}

bool CProfileMenu::commit_state_four()
{
    MenuString28 source_path;
    MenuString28 destination_path;
    MenuString28 destination_stem;

    source_path.assign(concatenate_profile_prefix(
        profile_directory_prefix, *reinterpret_cast<MenuString28 *>(&string_518)));

    destination_stem.assign(concatenate_profile_commit_string(
        concatenate_profile_prefix(profile_directory_prefix, *reinterpret_cast<MenuString28 *>(&string_534)),
        profile_copy_stem_suffix));

    destination_path.assign(concatenate_profile_commit_string(
        destination_stem, profile_file_extension));

    while (!CopyFileA(source_path.c_str(), destination_path.c_str(), 1)) {
        if (destination_path.size >= 0x104) {
            reinterpret_cast<MenuStringAssignBytesView *>(&string_588)
                ->assign_bytes(profile_copy_failure_text, 20);
            show_profile_result(string_588.c_str());
            return false;
        }

        reinterpret_cast<MenuStringAppendBytesView *>(&destination_stem)
            ->append_bytes(profile_copy_stem_suffix, 1);
        destination_path.assign(concatenate_profile_commit_string(
            destination_stem, profile_file_extension));
    }

    reinterpret_cast<MenuStringAssignBytesView *>(&string_588)
        ->assign_bytes(profile_copy_success_text, 14);
    show_profile_result(string_588.c_str());
    initialize_profile_menu();
    return true;
}

bool CProfileMenu::commit_state_five()
{
    MenuString28 path;
    path.assign(concatenate_profile_prefix(
        profile_directory_prefix, *reinterpret_cast<MenuString28 *>(&string_518)));

    if (DeleteFileA(path.c_str())) {
        reinterpret_cast<MenuStringAssignBytesView *>(&string_588)
            ->assign_bytes(profile_delete_success_text, 12);
        show_profile_result(string_588.c_str());
        initialize_profile_menu();
        return true;
    }

    reinterpret_cast<MenuStringAssignBytesView *>(&string_588)
        ->assign_bytes(profile_delete_failure_text, 18);
    show_profile_result(string_588.c_str());
    return false;
}

signed char CProfileMenu::commit_profile_change()
{
    if (_mbschr(
            reinterpret_cast<const unsigned char *>(string_56c.c_str()), '/') ||
        _mbschr(
            reinterpret_cast<const unsigned char *>(string_56c.c_str()), '\\')) {
        reinterpret_cast<MenuStringAssignBytesView *>(&string_588)
            ->assign_bytes(profile_rename_failure_text, 24);
        show_profile_result(string_588.c_str());
        return 0;
    }

    MenuString28 new_path = concatenate_profile_prefix(
        profile_directory_prefix, *reinterpret_cast<MenuString28 *>(&string_550));
    MenuString28 old_path = concatenate_profile_prefix(
        profile_directory_prefix, *reinterpret_cast<MenuString28 *>(&string_518));

    DeleteFileA(string_518.c_str());
    if (MoveFileA(old_path.c_str(), new_path.c_str())) {
        reinterpret_cast<MenuStringAssignBytesView *>(&string_588)
            ->assign_bytes(profile_rename_success_text, 18);
        show_profile_result(string_588.c_str());
        initialize_profile_menu();
        return 1;
    }

    reinterpret_cast<MenuStringAssignBytesView *>(&string_588)
        ->assign_bytes(profile_rename_failure_text, 24);
    show_profile_result(string_588.c_str());
    return 0;
}

} // namespace th105
