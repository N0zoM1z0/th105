#pragma once

#include "FileList.hpp"
#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "Title.hpp"

#include <deque>
#include <string>

namespace th105 {

class MusicList : public CFileList {
public:
    MusicList();
    virtual void populate();

private:
    friend class CMenuMusic;
    std::deque<std::string> paths_b4;
    std::deque<std::string> titles_c8;
};

class CMenuMusic : public Menu {
public:
    CMenuMusic();
    virtual ~CMenuMusic();
    virtual bool update();
    virtual void render();

private:
    bool update_primary();

    MusicList music_list_004;
    TitleDesignResource design_0e0;
    UiDesignObject *row_anchor_114;
    unsigned int reserved_118;
    MenuCursorState cursors_11c[2];
    GuideOverlay guide_144;
};

typedef char MusicList_size_must_be_0xdc[
    sizeof(MusicList) == 0xdc ? 1 : -1];
typedef char CMenuMusic_size_must_be_0x1ec[
    sizeof(CMenuMusic) == 0x1ec ? 1 : -1];

} // namespace th105
