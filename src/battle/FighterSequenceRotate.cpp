#include "Collision.hpp"
#include "EffectSprite.hpp"
#include "SpellRuntime.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

struct FighterSequenceSpriteCopyView {
    void *copy_fighter_sequence_sprite(
        const FighterSequenceSpriteCopyView *source);
};

namespace {

void copy_sequence_slot(
    FighterSequenceSlot *destination,
    const FighterSequenceSlot *source)
{
    destination->record_id_00 = source->record_id_00;
    destination->field_02 = source->field_02;
    reinterpret_cast<FighterSequenceSpriteCopyView *>(
        &destination->sprite_04)
        ->copy_fighter_sequence_sprite(
            reinterpret_cast<const FighterSequenceSpriteCopyView *>(
                &source->sprite_04));
}

} // namespace

unsigned char Fighter::rotate_front_spell_sequence_entry_to_back()
{
    FighterSequenceController *controller = &sequence_controller_55c;
    if (controller->live_count_10 == 0) {
        return 0;
    }

    const unsigned head = controller->head_0c;
    if (head > head + controller->live_count_10) {
        _invalid_parameter_noinfo();
    }
    if (head >= controller->head_0c + controller->live_count_10) {
        _invalid_parameter_noinfo();
    }

    unsigned index = head;
    if (controller->slot_capacity_08 <= index) {
        index -= controller->slot_capacity_08;
    }

    FighterSequenceSlot temporary;
    copy_sequence_slot(&temporary, controller->slots_04[index]);

    if (controller->live_count_10 != 0) {
        reinterpret_cast<CSprite *>(
            &controller->slots_04[controller->head_0c]->sprite_04)
            ->~CSprite();
        ++controller->head_0c;
        if (controller->slot_capacity_08 <= controller->head_0c) {
            controller->head_0c = 0;
        }
        if (--controller->live_count_10 == 0) {
            controller->head_0c = 0;
        }
    }

    controller->enqueue_record(&temporary);
    state_55a = static_cast<signed char>(controller->live_count_10);
    return static_cast<unsigned char>(controller->live_count_10);
}

} // namespace th105
