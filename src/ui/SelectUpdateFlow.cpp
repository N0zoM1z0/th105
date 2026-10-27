#include "ui/GuideOverlay.hpp"
#include "battle/EffectSprite.hpp"
#include <stddef.h>
extern "C" float __cdecl lookup_orientation_cosine(int angle);
namespace th105 {
// Pointer-only callback interface; slot identities other than14 remain unknown.
struct SelectFlowCallback {
    virtual void slot_00(); virtual void slot_04(); virtual void slot_08();
    virtual void slot_0c(); virtual void slot_10(); virtual void update_14();
};
// Read/write owner view, never instantiated or allocated.
struct SelectUpdateFlowView {
    unsigned char unknown_000[8];
    int state_008;
    unsigned char unknown_00c[0x624-0xc];
    CSpriteEx back_images_624[2];
    int scroll_counter_7f4;
    unsigned char unknown_7f8[0x1954-0x7f8];
    SelectFlowCallback *callbacks_1954[2];
    unsigned char unknown_195c[0x2d78-0x195c];
    unsigned char guide_mix_2d78;
    unsigned char unknown_2d79[3];
    int transition_ticks_2d7c;
    float transition_2d80, transition_origin_2d84;
    GuideOverlay guides_2d88[2];
    int update_flow_4208e0();
    int update_characters_41fc90();
    int update_stage_420560();
};
typedef char flow_counter_offset[offsetof(SelectUpdateFlowView,scroll_counter_7f4)==0x7f4?1:-1];
typedef char flow_guides_offset[offsetof(SelectUpdateFlowView,guides_2d88)==0x2d88?1:-1];

int SelectUpdateFlowView::update_flow_4208e0()
{
    guides_2d88[0].update();
    guides_2d88[1].update();
    if (callbacks_1954[0])
        callbacks_1954[0]->update_14();
    if (callbacks_1954[0] != callbacks_1954[1] && callbacks_1954[1])
        callbacks_1954[1]->update_14();
    if (state_008 == 0) {
        guides_2d88[0].visible = true;
        guides_2d88[1].visible = false;
        if (guide_mix_2d78 != 0)
            guide_mix_2d78 -= 15;
    } else {
        guides_2d88[0].visible = false;
        guides_2d88[1].visible = true;
        if (guide_mix_2d78 < 255)
            guide_mix_2d78 += 15;
    }
    if (transition_ticks_2d7c) {
        --transition_ticks_2d7c;
        transition_2d80 = static_cast<float>(
            (1.0 - lookup_orientation_cosine(transition_ticks_2d7c * 18)) *
            0.5 * transition_origin_2d84);
    }
    scroll_counter_7f4 = (scroll_counter_7f4 + 1) % 1024;
    back_images_624[0].set_uv_size(0.0f, static_cast<float>(scroll_counter_7f4 * 0.5));
    back_images_624[1].set_uv_size(0.0f, static_cast<float>(-static_cast<float>(scroll_counter_7f4) * 0.5));
    switch (state_008) {
    case 0: return update_characters_41fc90();
    case 1: return update_stage_420560();
    default: return 3;
    }
}
} // namespace th105
