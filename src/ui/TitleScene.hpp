#pragma once

#include "Title.hpp"
#include "DesignBaseLifetime.hpp"

namespace th105 {

class CTitle : public CSceneBase {
public:
    CTitle();
    virtual ~CTitle();
    virtual int update();
    virtual bool render();
    virtual void unknown_scene_method();
    virtual void on_scene_enter(int previous_scene);
    virtual void on_scene_exit(int next_scene);

    void advance_menu_item_wave();

private:
    DesignTextureHandle texture_08;
    CSprite color_0c;
    DesignTextureHandle texture_a0;
    CSprite color_a4;
    CTile color_138;
    CDesignBase design_1dc;
    MenuCursorState cursor_210;
    UiDesignObject *menu_items_224[12];
    float menu_item_wave_offsets[12];
    int reserved_0284;
    int menu_item_wave_counter;
};

typedef char CTitle_size_must_be_0x28c[sizeof(CTitle) == 0x28c ? 1 : -1];

} // namespace th105
