#pragma once

#include "DesignBaseLifetime.hpp"
#include "GuideOverlay.hpp"
#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"

#include <vector>

namespace th105 {

struct PracticeBattleSettingsView {
    unsigned char unknown_000[0x0c];
    int category_value_00c[8];
};

struct PracticeOwnerView {
    unsigned char unknown_000[0x84];
    int menu_state_084;
};

// Current RTTI owns a 0x288 CMenuPractice.  Constructor/destructor xrefs and
// the already exact render close every member boundary below.  Keep this as
// the shared source layout instead of reintroducing offset-only facades.
class CMenuPractice : public Menu {
public:
    explicit CMenuPractice(PracticeOwnerView *owner);
    virtual ~CMenuPractice();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

    void configure_subcursor(int category);

    template <typename T> T &field(unsigned offset)
    {
        return *reinterpret_cast<T *>(
            reinterpret_cast<unsigned char *>(this) + offset);
    }

    PracticeBattleSettingsView *settings_004;
    GuideOverlay guide_008;
    unsigned char field_0b0;
    unsigned char reserved_0b1[3];
    unsigned int texture_0b4;
    UiTileA4 weather_tile_0b8;
    unsigned int unknown_15c;
    CDesignBase design_160;
    UiDesignObject *category_items_194[10];
    std::vector<UiDesignObject *> groups_1bc[10];
    MenuCursorState cursors_25c[2];
    PracticeOwnerView *owner_284;
};

typedef char CMenuPractice_vector_size_must_be_0x10[
    sizeof(std::vector<UiDesignObject *>) == 0x10 ? 1 : -1];
typedef char CMenuPractice_size_must_be_0x288[
    sizeof(CMenuPractice) == 0x288 ? 1 : -1];

} // namespace th105
