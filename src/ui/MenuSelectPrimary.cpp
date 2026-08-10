#include "MenuSelect.hpp"

#include "../battle/GameMode.hpp"
#include "../input/InputManager.hpp"
#include "../input/InputSelection.hpp"

extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);
extern "C" void __cdecl install_menu_object_thunk(th105::Menu *object);
extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {

class CMenuPlayerConfig : public Menu {
public:
    explicit CMenuPlayerConfig(PlayerSlotRecord *player);
    virtual ~CMenuPlayerConfig();
    virtual bool update();
    virtual void render();

private:
    unsigned char storage_04[0x284];
};

class CMenuInputConfig : public Menu {
public:
    CMenuInputConfig(PlayerSlotRecord *player, int mode);
    virtual ~CMenuInputConfig();
    virtual bool update();
    virtual void render();

private:
    unsigned char storage_04[0x32C];
};

typedef char CMenuPlayerConfig_size_must_be_0x288[
    sizeof(CMenuPlayerConfig) == 0x288 ? 1 : -1];
typedef char CMenuInputConfig_size_must_be_0x330[
    sizeof(CMenuInputConfig) == 0x330 ? 1 : -1];

bool CMenuSelect::update_primary_selection()
{
    guides_74[0].visible = true;
    HoldCounters *input = &g_active_menu_input->hold;

    if (cursor_5c.update())
        dispatch_indexed_event(0x27);

    UiDesignObject **item = items_3c;
    int count = 8;
    do {
        (*item)->set_color(0xFFFFFFFF);
        ++item;
        --count;
    } while (count != 0);

    if (input->buttons[0] == 1) {
        dispatch_indexed_event(0x28);
        reserved_05 = 0;

        switch (cursor_5c.selection) {
        case 0:
            state_04 = 1;
            active_player_70 = 0;
            return true;
        case 1:
            state_04 = 1;
            active_player_70 = 1;
            return true;
        case 2:
        {
            Menu *menu =
                new CMenuPlayerConfig(get_player_slot_record(0));
            install_menu_object_thunk(menu);
            active_player_70 = 0;
            return true;
        }
        case 3:
        {
            Menu *menu =
                new CMenuPlayerConfig(get_player_slot_record(1));
            install_menu_object_thunk(menu);
            active_player_70 = 1;
            return true;
        }
        case 4:
        {
            Menu *menu =
                new CMenuInputConfig(get_player_slot_record(0), 0);
            install_menu_object_thunk(menu);
            return true;
        }
        case 5:
        {
            Menu *menu;
            if (get_game_mode() == GAME_MODE_NETWORK_SERVER)
                menu = new CMenuInputConfig(get_player_slot_record(1), 1);
            else
                menu = new CMenuInputConfig(get_player_slot_record(1), -1);
            install_menu_object_thunk(menu);
            return true;
        }
        case 6:
            g_scene_mode = 2;
            return true;
        case 7:
            goto cancelled;
        }
    } else if (input->buttons[1] == 1 ||
               is_menu_initial_press(1, 0, 0, 0)) {
        goto cancelled;
    }
    return true;

cancelled:
    dispatch_indexed_event(0x29);
    return false;
}

} // namespace th105
