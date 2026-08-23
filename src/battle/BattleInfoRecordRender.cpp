#include "InfoManagerResources.hpp"
#include "Collision.hpp"
#include "SpellRuntime.hpp"
#include "../engine/RenderModeManager.hpp"
#include "../ui/UiPrimitives.hpp"

#include <deque>

namespace th105 {

struct SpellSpriteRenderView {
    virtual void slot_00();
    virtual void slot_04();
    virtual void slot_08();
    virtual void slot_0c();
    virtual void slot_10();
    virtual void slot_14();
    virtual void slot_18();
    virtual void render(float x, float y);
    unsigned char reserved_04[0x84];
    float scale_x_88;
    float scale_y_8c;
    unsigned char reserved_90[4];
};

typedef char SpellSpriteRenderView_size_must_be_0x94[
    sizeof(SpellSpriteRenderView) == 0x94 ? 1 : -1];

static __forceinline void set_sprite_scale(
    SpellSpriteRenderView *sprite,
    float scale)
{
    sprite->scale_x_88 = scale;
    sprite->scale_y_8c = scale;
}

void BattleInfoRecordF8::render_470710(float shift)
{
    if (fighter_18->unknown_4e7 != 0)
        return;

    g_render_mode_manager.set_blend_mode(1);
    int index = fighter_18->state_55a - 1;
    if (index < 0)
        return;

    UiDesignObject **anchor_slot = &group_88[index];
    do {
        float x;
        if (index > 0) {
            if (mode_00 == 0)
                x = (*anchor_slot)->x;
            else
                x = (*anchor_slot)->x - height_ratio_08 * primary_height_04;

            set_sprite_scale(
                reinterpret_cast<SpellSpriteRenderView *>(
                    &fighter_18->sequence_controller_55c
                         .entry_at_checked(index)->sprite_04),
                height_ratio_08);
        } else {
            if (mode_00 == 0)
                x = (*anchor_slot)->x;
            else
                x = (*anchor_slot)->x - primary_height_04;

            set_sprite_scale(
                reinterpret_cast<SpellSpriteRenderView *>(
                    &fighter_18->sequence_controller_55c
                         .entry_at_checked(index)->sprite_04),
                1.0f);
        }

        typedef std::deque<FighterSequenceSlot> NativeSequenceDeque;
        NativeSequenceDeque *sequence = reinterpret_cast<NativeSequenceDeque *>(
            &fighter_18->sequence_controller_55c);
        reinterpret_cast<SpellSpriteRenderView *>(
            &(*sequence)[static_cast<unsigned>(index)].sprite_04)
            ->render(x, (*anchor_slot)->y + shift);

        --index;
        --anchor_slot;
    } while (index >= 0);
}

} // namespace th105
