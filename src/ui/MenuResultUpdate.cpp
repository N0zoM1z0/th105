#include "ResultMenu.hpp"

#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);
extern "C" void __cdecl prepare_result_match(int mode, int player);
extern "C" void __cdecl prepare_scenario_match(int player);
extern "C" void __cdecl install_menu_object_thunk(th105::Menu *object);
extern "C" void __fastcall release_owned_pointer_buffer(void *buffer);
extern "C" int g_next_scene_mode;

namespace th105 {

extern MatchSetup *get_match_setup();

struct ResultReplayString {
    void assign(const short *source);
};

class CMenuReplay : public Menu {
public:
    CMenuReplay();
    virtual ~CMenuReplay();
    virtual bool update();
    virtual void render();

private:
    unsigned char storage_04[0x8E8];
};

typedef char CMenuReplay_size_must_be_0x8ec[
    sizeof(CMenuReplay) == 0x8EC ? 1 : -1];

bool CMenuResult::update_active()
{
    guide_10a0.update();
    HoldCounters *input = &g_active_menu_input->hold;

    if (character_cursor_0b0.update()) {
        dispatch_indexed_event(0x27);
        unsigned int index = character_cursor_0b0.selection;
        if (available_characters_09c.begin == 0 ||
            static_cast<unsigned int>(
                available_characters_09c.end -
                available_characters_09c.begin) <= index)
            _invalid_parameter_noinfo();
        selected_character_0c4 = available_characters_09c.begin[index];
        refresh_selected_character();
    } else if (result_cursor_108c.update()) {
        dispatch_indexed_event(0x27);
    }

    if (input->buttons[0] == 1) {
        short *replay = results_0c8[selected_character_0c4].replays().at(
            result_cursor_108c.selection);
        if (*replay < 0)
            return true;

        dispatch_indexed_event(0x28);
        prepare_result_match(7, 0);
        reinterpret_cast<int *>(get_match_setup())[2] =
            selected_character_0c4;
        reinterpret_cast<unsigned int *>(get_match_setup())[0] =
            *results_0c8[selected_character_0c4].values().at(
                result_cursor_108c.selection);
        reinterpret_cast<unsigned int *>(get_match_setup())[10] =
            *results_0c8[selected_character_0c4].labels().at(
                result_cursor_108c.selection);

        unsigned char *setup =
            reinterpret_cast<unsigned char *>(get_match_setup());
        release_owned_pointer_buffer(setup + 0x30);
        replay = results_0c8[selected_character_0c4].replays().at(
            result_cursor_108c.selection);
        reinterpret_cast<ResultReplayString *>(
            reinterpret_cast<unsigned char *>(get_match_setup()) + 0x30)
            ->assign(replay);
        prepare_scenario_match(0);
        g_scene_mode = 6;
        g_next_scene_mode = 7;
        return true;
    }

    if (input->buttons[2] == 1) {
        dispatch_indexed_event(0x28);
        CMenuReplay *menu;
        menu = new CMenuReplay;
        install_menu_object_thunk(menu);
        return true;
    }

    if (input->buttons[1] != 1 &&
        !is_menu_initial_press(1, 0, 0, 0))
        return true;

    dispatch_indexed_event(0x29);
    return false;
}

} // namespace th105
