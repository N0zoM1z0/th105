#include "ResultMenu.hpp"
#include "ProfileMenu.hpp"

#include <deque>
#include <vector>

#include "../input/InputManager.hpp"

extern "C" th105::CInputManager *g_active_menu_input;
extern "C" void __cdecl dispatch_indexed_event(unsigned index);
extern "C" bool __cdecl is_menu_initial_press(
    int primary, int modifier_a, int modifier_b, int modifier_c);
extern "C" void __cdecl prepare_result_match(int mode, int player);
extern "C" void __cdecl prepare_scenario_match(int player);
extern "C" int g_next_scene_mode;

namespace th105 {

void __cdecl push_ui_selection_menu_facade(void *object);

extern MatchSetup *get_match_setup();

// Borrowed view of the result list's three parallel selection containers.
// Never constructed; the preceding list and string storage are not accessed.
struct ResultSelectionView {
    unsigned char prefix_000[0xCC];
    std::deque<int> labels_cc;
    std::deque<int> values_e0;
    std::deque<short> replays_f4;
};
typedef char ResultSelectionView_size_must_be_0x108[
    sizeof(ResultSelectionView) == sizeof(ResultList) ? 1 : -1];

bool CMenuResult::update_active()
{
    guide_10a0.update();
    HoldCounters *input = &g_active_menu_input->hold;

    if (character_cursor_0b0.update()) {
        dispatch_indexed_event(0x27);
        selected_character_0c4 =
            reinterpret_cast<std::vector<int> &>(available_characters_09c)[
                character_cursor_0b0.selection];
        refresh_selected_character();
    } else if (result_cursor_108c.update()) {
        dispatch_indexed_event(0x27);
    }

    if (input->buttons[0] == 1) {
        short *replay = &reinterpret_cast<ResultSelectionView *>(results_0c8)[
            selected_character_0c4].replays_f4[
            result_cursor_108c.selection];
        if (*replay >= 0) {
            dispatch_indexed_event(0x28);
            prepare_result_match(7, 0);
            reinterpret_cast<int *>(get_match_setup())[2] =
                selected_character_0c4;
            reinterpret_cast<unsigned int *>(get_match_setup())[0] =
                reinterpret_cast<ResultSelectionView *>(results_0c8)[
                    selected_character_0c4].values_e0[
                    result_cursor_108c.selection];
            reinterpret_cast<unsigned int *>(get_match_setup())[10] =
                reinterpret_cast<ResultSelectionView *>(results_0c8)[
                    selected_character_0c4].labels_cc[
                    result_cursor_108c.selection];

            reinterpret_cast<std::deque<short> *>(
                reinterpret_cast<unsigned char *>(get_match_setup()) + 0x30)
                ->clear();
            replay = &reinterpret_cast<ResultSelectionView *>(results_0c8)[
                selected_character_0c4].replays_f4[
                result_cursor_108c.selection];
            reinterpret_cast<std::deque<short> *>(
                reinterpret_cast<unsigned char *>(get_match_setup()) + 0x30)
                ->push_back(*replay);
            prepare_scenario_match(0);
            g_scene_mode = 6;
            g_next_scene_mode = 7;
        }
    } else if (input->buttons[2] == 1) {
        dispatch_indexed_event(0x28);
        CProfileMenu *menu;
        menu = new CProfileMenu;
        push_ui_selection_menu_facade(menu);
    } else if (input->buttons[1] == 1 ||
               is_menu_initial_press(1, 0, 0, 0)) {
        dispatch_indexed_event(0x29);
        return false;
    }
    return true;
}

} // namespace th105
