#pragma once

#include "FileList.hpp"
#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "Title.hpp"

#include <list>

namespace th105 {

class CMenuReplay : public Menu {
public:
    CMenuReplay();
    virtual ~CMenuReplay();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    void refresh_file_list();
    unsigned char update_delete_state();
    unsigned char update_mode_state();

    signed char state_04;
    signed char state_05;
    unsigned char reserved_06[2];
    CReplayList replay_list_08;
    TitleDesignResource design_bc;
    UiDesignObject *items_f0[3];
    MenuCursorState mode_cursor_fc;
    MenuCursorState file_cursor_110;
    GuideOverlay guides_124[2];
    std::list<int> entries_274;
};

typedef char CMenuReplay_size_must_be_0x280[
    sizeof(CMenuReplay) == 0x280 ? 1 : -1];

} // namespace th105
