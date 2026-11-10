#include "InfoManagerResources.hpp"
#include "Collision.hpp"
#include "SpellRuntime.hpp"
#include "../engine/RenderModeManager.hpp"
#include "../ui/UiPrimitives.hpp"

#include <deque>

namespace th105 {

static __forceinline void set_sprite_scale(
    CSprite *sprite,
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

    do {
        float x;
        if (index > 0) {
            if (mode_00 == 0)
                x = group_88[index]->x;
            else
                x = group_88[index]->x - height_ratio_08 * primary_height_04;

            set_sprite_scale(
                &fighter_18->sequence_controller_55c
                         .entry_at_checked(index)->sprite_04,
                height_ratio_08);
        } else {
            if (mode_00 == 0)
                x = group_88[index]->x;
            else
                x = group_88[index]->x - primary_height_04;

            set_sprite_scale(
                &fighter_18->sequence_controller_55c
                         .entry_at_checked(index)->sprite_04,
                1.0f);
        }

        typedef std::deque<FighterSequenceSlot> NativeSequenceDeque;
        NativeSequenceDeque *sequence = reinterpret_cast<NativeSequenceDeque *>(
            &fighter_18->sequence_controller_55c);
        (*sequence)[static_cast<unsigned>(index)].sprite_04.render(
            x, group_88[index]->y + shift);

        --index;
    } while (index >= 0);
}

} // namespace th105
