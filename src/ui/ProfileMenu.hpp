#pragma once

#include <deque>
#include <string>

#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "MenuSelect.hpp"
#include "Title.hpp"

namespace th105 {

struct ProfileMenuBaseData {
    unsigned char reserved_000[0x98];
    std::string string_098;
    std::string string_0b4;
    unsigned char reserved_0d0[0x6C];
    unsigned char flag_13c;
    unsigned char reserved_13d[3];
    unsigned char block_140[0x34];
    unsigned char block_174[0x34];
    unsigned char flag_1a8;
    unsigned char reserved_1a9[3];
    std::deque<unsigned short> decks_1ac[20];

    ProfileMenuBaseData();
    ~ProfileMenuBaseData();
    void cleanup();
    void initialize_defaults();
    bool save_to_profile(const char *path);

private:
    void initialize_default_deck(std::deque<unsigned short> *deck, int index);
    void normalize_profile_name();
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
    unsigned texture_primary_000;
    unsigned texture_secondary_004;
    void *source_008;
    UiTileA4 primary_tile_00c;
    UiTileA4 secondary_tile_0b0;
    int width_154;
    int x_158;
    int y_15c;
    int state_160;
    int record_limit_164;

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
    void reset();
    int item_count();
    void render_item(float x, float y, unsigned int index);
    bool contains(const MenuString28 *profile) const;
    MenuString28 *row_at(unsigned int index);
    void trim_item_text(MenuString28 *value);
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
    bool commit_state_one();
    bool commit_state_four();
    bool commit_state_five();
    signed char commit_profile_change();
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
    std::string string_518;
    std::string string_534;
    std::string string_550;
    std::string string_56c;
    std::string string_588;
    GuideOverlay guides_5a4[5];
};

typedef char ProfileMenuBaseData_size_must_be_0x33c[
    sizeof(ProfileMenuBaseData) == 0x33C ? 1 : -1];
typedef char ProfileEditor168_size_must_be_0x168[
    sizeof(ProfileEditor168) == 0x168 ? 1 : -1];
typedef char ProfileEditor168_source_offset_must_be_0x08[
    offsetof(ProfileEditor168, source_008) == 0x08 ? 1 : -1];
typedef char ProfileEditor168_width_offset_must_be_0x154[
    offsetof(ProfileEditor168, width_154) == 0x154 ? 1 : -1];
typedef char ProfileEditor168_limit_offset_must_be_0x164[
    offsetof(ProfileEditor168, record_limit_164) == 0x164 ? 1 : -1];
typedef char ProfileStringTemporary_size_must_be_0x1c[
    sizeof(ProfileStringTemporary) == 0x1C ? 1 : -1];
typedef char ProfileMenu_std_string_size_must_be_0x1c[
    sizeof(std::string) == 0x1C ? 1 : -1];
typedef char CProfileMenu_size_must_be_0x8ec[
    sizeof(CProfileMenu) == 0x8EC ? 1 : -1];

} // namespace th105
