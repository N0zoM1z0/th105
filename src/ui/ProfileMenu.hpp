#pragma once

#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "MenuSelect.hpp"
#include "Title.hpp"

namespace th105 {

struct ProfileMenuBaseData {
    unsigned char storage[0x33C];

    ProfileMenuBaseData();
    ~ProfileMenuBaseData();
    void cleanup();
};

struct ProfileStringTemporary {
    unsigned int allocator_state;
    union {
        unsigned int buffer_words[4];
        char *allocation;
    } storage;
    unsigned int size;
    unsigned int capacity;

    ~ProfileStringTemporary();
};

struct ProfileEditor168 {
    unsigned char storage[0x168];

    ProfileEditor168();
    ~ProfileEditor168();
    void initialize(void *records, int record_size);
    void shutdown();
    signed char update_selection();
    void read_profile_name(MenuString28 *output);
    void render(float x, float y);
};

struct ProfileMenuController {
    void set_mode(int mode);
    void select_profile(const char *profile);
};

struct ProfileNameList {
    bool contains(const MenuString28 *profile) const;
};

class CProfileMenu : public Menu {
public:
    CProfileMenu();
    virtual ~CProfileMenu();
    virtual bool update();
    virtual void render();

private:
    bool update_primary();
    bool update_state_one();
    bool update_state_two();
    bool update_state_three();
    bool update_state_four();
    bool update_state_five();
    bool update_state_six();
    signed char commit_profile_change();
    void show_profile_message(const char *message, int mode);
    void render_profile_menu_footer();

    ProfileMenuBaseData base_data_004;
    int state_340;
    signed char substate_344;
    unsigned char reserved_345[3];
    TitleDesignResource design_348;
    UiDesignObject *label_37c;
    UiDesignObject *items_380[7];
    MenuCursorState cursor_39c;
    ProfileEditor168 editor_3b0;
    MenuString28 string_518;
    MenuString28 string_534;
    MenuString28 string_550;
    MenuString28 string_56c;
    MenuString28 string_588;
    GuideOverlay guides_5a4[5];
};

typedef char ProfileMenuBaseData_size_must_be_0x33c[
    sizeof(ProfileMenuBaseData) == 0x33C ? 1 : -1];
typedef char ProfileEditor168_size_must_be_0x168[
    sizeof(ProfileEditor168) == 0x168 ? 1 : -1];
typedef char ProfileStringTemporary_size_must_be_0x1c[
    sizeof(ProfileStringTemporary) == 0x1C ? 1 : -1];
typedef char CProfileMenu_size_must_be_0x8ec[
    sizeof(CProfileMenu) == 0x8EC ? 1 : -1];

} // namespace th105
