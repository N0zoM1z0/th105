#pragma once

#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "Title.hpp"

#include <new>

namespace th105 {

struct MenuString28 {
    unsigned int allocator_state;
    union {
        char buffer[16];
        char *allocation;
    } storage;
    unsigned int size;
    unsigned int capacity;

    MenuString28()
    {
        capacity = 15;
        size = 0;
        storage.buffer[0] = 0;
    }

    ~MenuString28()
    {
        if (capacity >= 16)
            operator delete(storage.allocation);
        capacity = 15;
        size = 0;
        storage.buffer[0] = 0;
    }

    const char *c_str() const
    {
        const char *result = storage.allocation;
        if (capacity < 16)
            result = storage.buffer;
        return result;
    }
};

struct PlayerSlotRecord {
    bool load_profile(const char *path);
    void set_profile_color(
        unsigned char red, unsigned char green, unsigned char blue);
};

typedef char MenuString28_size_must_be_0x1c[
    sizeof(MenuString28) == 0x1C ? 1 : -1];

class CMenuSelect : public Menu {
public:
    CMenuSelect();
    virtual ~CMenuSelect();

    virtual bool update();
    virtual void render();

private:
    bool update_primary_selection();
    bool update_player_assignment();
    int select_profile(MenuString28 *selected, MenuString28 *alternate);

    signed char state_04;
    unsigned char reserved_05;
    unsigned char reserved_06[2];
    TitleDesignResource design_08;
    UiDesignObject *items_3c[8];
    MenuCursorState cursor_5c;
    signed char active_player_70;
    unsigned char reserved_71[3];
    GuideOverlay guides_74[2];
};

typedef char CMenuSelect_size_must_be_0x1c4[
    sizeof(CMenuSelect) == 0x1C4 ? 1 : -1];

} // namespace th105
