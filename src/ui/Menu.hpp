#pragma once

extern "C" int g_scene_mode;

namespace th105 {

struct PlayerSlotRecord;
struct MenuString28;

class Menu {
public:
    Menu() { g_scene_mode = 22; }
    virtual ~Menu() { g_scene_mode = 22; }

    virtual void unknown_menu_method();
    virtual bool update() = 0;
    virtual void render() = 0;

protected:
    void initialize_profile_menu();
    void render_cursor(float x, float y, float scale);
    void render_profile_player_slot(
        PlayerSlotRecord *player, float x, float y);
    void render_profile_tiles();
    void show_profile_message(const char *message, bool alternate);
    void show_profile_result(const char *message);
    int select_profile(MenuString28 *selected, MenuString28 *alternate);
};

typedef char Menu_size_must_be_0x04[sizeof(Menu) == 0x04 ? 1 : -1];

} // namespace th105
