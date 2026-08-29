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
        PlayerSlotRecord *player, int character, UiSprite94 *stand);
private:
    unsigned char storage_000[0x6b0];
};

struct CProfileCharacterSelectUpdateView {
    bool update_4485b0();
    void refresh_character_preview_4484f0();

    void *vfptr_000;
    unsigned texture_004;
    UiSprite94 stand_008;
    PlayerSlotRecord *player_09c;
    int character_0a0;
    unsigned field_0a4;
    UiSprite94 portrait_0a8;
    TitleDesignResource design_13c;
    UiDesignObject *items_170[17];
    MenuCursorState column_1b4;
    MenuCursorState row_1c8;
    GuideOverlay guide_1dc;
    int item_count_284;
};

bool CProfileCharacterSelectUpdateView::update_4485b0()
{
    guide_1dc.update();

    CInputManager *input = g_active_menu_input;
    if (input->hold.buttons[0] == 1) {
        dispatch_indexed_event(0x28);
        if (row_1c8.selection < item_count_284) {
            ProfileDeckEditLaunchView *menu =
                new ProfileDeckEditLaunchView(
                    player_09c, character_0a0, &stand_008);
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
        character_0a0 = column_1b4.selection + 2 * row;
        if (row == count)
            character_0a0 = -1;
        refresh_character_preview_4484f0();
    }

    return true;
}

typedef char ProfileDeckEditLaunchView_size[
    sizeof(ProfileDeckEditLaunchView) == 0x6b0 ? 1 : -1];
typedef char CProfileCharacterSelectUpdateView_size[
    sizeof(CProfileCharacterSelectUpdateView) == 0x288 ? 1 : -1];
typedef char CProfileCharacterSelectUpdateView_column[
    offsetof(CProfileCharacterSelectUpdateView, column_1b4) == 0x1b4 ? 1 : -1];
typedef char CProfileCharacterSelectUpdateView_row[
    offsetof(CProfileCharacterSelectUpdateView, row_1c8) == 0x1c8 ? 1 : -1];
typedef char CProfileCharacterSelectUpdateView_guide[
    offsetof(CProfileCharacterSelectUpdateView, guide_1dc) == 0x1dc ? 1 : -1];

} // namespace th105
