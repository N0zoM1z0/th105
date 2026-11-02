#include "ProfileSubmenus.hpp"
#include "GuideOverlay.hpp"
#include "MenuCursor.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"
#include "../input/InputManager.hpp"

#include <stddef.h>

extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {

struct PlayerSlotRecord;

void __cdecl dispatch_indexed_event(unsigned index);
bool __cdecl is_menu_initial_press(
    unsigned char key, bool modifier0, bool modifier1, bool modifier2);
void __cdecl install_menu_object(void *object);

class ProfileDeckEditLaunchView {
public:
    ProfileDeckEditLaunchView(
        PlayerSlotRecord *player, int character, CSprite *stand);
private:
    unsigned char storage_000[0x6b0];
};

bool CProfileCharacterSelect::update()
{
    guide_1dc.update();

    CInputManager *input = g_active_menu_input;
    if (input->hold.buttons[0] == 1) {
        dispatch_indexed_event(0x28);
        if (row_1c8.selection < item_count_284) {
            ProfileDeckEditLaunchView *menu =
                new ProfileDeckEditLaunchView(
                    player_9c, character_a0, &stand_08);
            install_menu_object(menu);
            return true;
        }
        return false;
    } else if (
        input->hold.buttons[1] == 1 ||
        is_menu_initial_press(1, false, false, false)) {
        dispatch_indexed_event(0x29);
        return false;
    }

    MenuCursorState *cursor = &column_1b4;
    unsigned char changed = static_cast<unsigned char>(2 * cursor[1].update());
    changed = static_cast<unsigned char>(changed | cursor[0].update());
    if (changed != 0) {
        dispatch_indexed_event(0x27);
        int const count = item_count_284;
        int const row = row_1c8.selection;
        if (row >= count - 1)
            column_1b4.selection = 0;
        character_a0 = column_1b4.selection + 2 * row;
        if (row == count)
            character_a0 = -1;
        refresh_character_preview();
    }

    return true;
}

typedef char ProfileDeckEditLaunchView_size[
    sizeof(ProfileDeckEditLaunchView) == 0x6b0 ? 1 : -1];

} // namespace th105
