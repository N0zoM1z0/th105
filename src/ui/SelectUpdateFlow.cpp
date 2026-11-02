#include "ui/SelectConstructor.hpp"
#include "battle/EffectSprite.hpp"
#include <stddef.h>
extern "C" float __cdecl lookup_orientation_cosine(int angle);
namespace th105 {
// Pointer-only callback interface; slot identities other than14 remain unknown.
struct SelectFlowCallback {
    virtual void slot_00(); virtual void slot_04(); virtual void slot_08();
    virtual void slot_0c(); virtual void slot_10(); virtual void update_14();
};
int CSelect::update_selection()
{
    guides_2d88[0].update();
    guides_2d88[1].update();
    if ((static_cast<SelectFlowCallback *>(selected_effects_1954[0])))
        (static_cast<SelectFlowCallback *>(selected_effects_1954[0]))->update_14();
    if ((static_cast<SelectFlowCallback *>(selected_effects_1954[0])) != (static_cast<SelectFlowCallback *>(selected_effects_1954[1])) && (static_cast<SelectFlowCallback *>(selected_effects_1954[1])))
        (static_cast<SelectFlowCallback *>(selected_effects_1954[1]))->update_14();
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
    if (field_2d7c) {
        --field_2d7c;
        field_2d80 = static_cast<float>(
            (1.0 - lookup_orientation_cosine(field_2d7c * 18)) *
            0.5 * field_2d84);
    }
    field_7f4 = (field_7f4 + 1) % 1024;
    back_images_624[0].set_uv_size(0.0f, static_cast<float>(field_7f4 * 0.5));
    back_images_624[1].set_uv_size(0.0f, static_cast<float>(-static_cast<float>(field_7f4) * 0.5));
    switch (state_008) {
    case 0: return update_characters_41fc90();
    case 1: return update_stage_420560();
    default: return 3;
    }
}
} // namespace th105
