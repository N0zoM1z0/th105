#include "Menu.hpp"
#include "MenuCursor.hpp"
#include "MenuPractice.hpp"
#include "GuideOverlay.hpp"
#include "Title.hpp"
#include "UiPrimitives.hpp"
#include "../input/InputManager.hpp"

#include <vector>

extern "C" th105::CInputManager *g_active_menu_input;

namespace th105 {

struct BattleController;

struct ProfileFooterMemberView {
    void render_profile_menu_footer();
};

class CMenuBattle : public Menu {
public:
    explicit CMenuBattle(BattleController *owner);
    virtual ~CMenuBattle();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    signed char state_04;
    TitleDesignResource design_08;
    UiDesignObject *items_3c[5];
    MenuCursorState cursor_50;
    std::vector<int> menu_entries_64;
    BattleController *owner_74;
};

typedef char CMenuBattle_size_must_be_0x78[
    sizeof(CMenuBattle) == 0x78 ? 1 : -1];

CMenuBattle::~CMenuBattle()
{
    design_08.virtual_cleanup();
}

void CMenuBattle::render()
{
    UiDesignObject *item = items_3c[cursor_50.selection];
    render_cursor(item->x, item->y + 4.0f + 4.0f, 256.0f);
    design_08.render();
    reinterpret_cast<ProfileFooterMemberView *>(this)
        ->render_profile_menu_footer();
}

class CMenuConfig : public Menu {
public:
    virtual ~CMenuConfig();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    template <typename T> T &field(unsigned offset)
    {
        return *reinterpret_cast<T *>(
            reinterpret_cast<unsigned char *>(this) + offset);
    }

    signed char state_04;
    GuideOverlay guide_08;
    bool option_b0;
    unsigned texture_b4;
    UiSprite94 sprites_b8[2];
    int grid_width_1e0;
    int grid_height_1e4;
    TitleDesignResource design_1e8;
};

typedef char CMenuConfig_prefix_must_end_0x21c[
    sizeof(CMenuConfig) == 0x21c ? 1 : -1];

CMenuConfig::~CMenuConfig()
{
    g_title_resource_manager.release_title_resource_handle(texture_b4);
    design_1e8.virtual_cleanup();
}

void CMenuConfig::render()
{
    MenuCursorState &cursor = field<MenuCursorState>(0x264);
    UiDesignObject **items = &field<UiDesignObject *>(0x224);
    UiDesignObject *selected = items[cursor.selection];
    render_cursor(selected->x, selected->y + 4.0f, 200.0f);
    design_1e8.render();

    UiDesignObject *first_anchor = field<UiDesignObject *>(0x24c);
    sprites_b8[0].render(first_anchor->x + 4.0f, first_anchor->y);
    UiDesignObject *second_anchor = field<UiDesignObject *>(0x250);
    sprites_b8[1].render(second_anchor->x + 4.0f, second_anchor->y);
    guide_08.render();
}

struct CTileRenderView {
    void render(float x, float y, int column, int row);
};

void CMenuPractice::render()
{
    MenuCursorState &cursor = field<MenuCursorState>(0x25c);
    UiDesignObject **items = &field<UiDesignObject *>(0x194);
    UiDesignObject *selected = items[cursor.selection];
    render_cursor(selected->x, selected->y + 4.0f, 256.0f);

    field<TitleDesignResource>(0x160).render();

    std::vector<UiDesignObject *> *groups =
        &field<std::vector<UiDesignObject *> >(0x1bc);
    UiDesignObject *&y_source = groups[1][0];
    UiDesignObject *&x_source = groups[1][0];
    void *owner = field<void *>(0x04);
    int row = *reinterpret_cast<int *>(
        reinterpret_cast<unsigned char *>(owner) + 0x10);
    reinterpret_cast<CTileRenderView *>(&field<UiTileA4>(0xb8))->render(
        x_source->x + 18.0f, y_source->y, 0, row);

    field<GuideOverlay>(0x08).render();
}

class CMenuConnect : public Menu {
public:
    virtual ~CMenuConnect();
    virtual void unknown_menu_method();
    virtual bool update();
    virtual void render();

private:
    template <typename T> T &field(unsigned offset)
    {
        return *reinterpret_cast<T *>(
            reinterpret_cast<unsigned char *>(this) + offset);
    }

    bool update_state_zero();
    bool update_state_one();
    bool update_state_middle();
    bool update_state_six();
};

bool CMenuConnect::update()
{
    GuideOverlay *guide = &field<GuideOverlay>(0xc4c);
    int guide_count = 8;
    do {
        guide->update();
        guide->visible = false;
        ++guide;
    } while (--guide_count);

    UiDesignObject **item = &field<UiDesignObject *>(0x40);
    if (field<signed char>(0x08) != 6) {
        int remaining = 7;
        do {
            (*item)->set_color(0xffffffffu);
            ++item;
        } while (--remaining);
    } else {
        int index = 0;
        do {
            if (field<int>(0x3c8) == index)
                (*item)->set_color(0xffffffffu);
            else
                (*item)->set_color(0xff808080u);
            ++index;
            ++item;
        } while (index < 7);
    }

    switch (field<signed char>(0x08)) {
    case 0:
        field<GuideOverlay>(0xc4c).visible = true;
        return update_state_zero();
    case 1:
        return update_state_one();
    case 2:
    case 3:
    case 4:
    case 5:
        return update_state_middle();
    case 6:
        field<unsigned char>(0xcf4) = 1;
        return update_state_six();
    default:
        return true;
    }
}

} // namespace th105
