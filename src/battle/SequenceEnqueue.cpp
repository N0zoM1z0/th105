#include "Collision.hpp"
#include "SpellRuntime.hpp"

namespace th105 {

struct FighterSequenceSpriteCopyView {
    void *copy_fighter_sequence_sprite(
        const FighterSequenceSpriteCopyView *source);
};

void FighterSequenceController::enqueue_record(
    const FighterSequenceSlot *record)
{
    if (slot_capacity_08 <= live_count_10 + 1) {
        grow_storage(1);
    }

    unsigned index = head_0c + live_count_10;
    if (slot_capacity_08 <= index) {
        index -= slot_capacity_08;
    }

    if (slots_04[index] == 0) {
        slots_04[index] =
            static_cast<FighterSequenceSlot *>(operator new(0x98));
    }

    FighterSequenceSlot *destination = slots_04[index];
    if (destination != 0) {
        destination->record_id_00 = record->record_id_00;
        destination->field_02 = record->field_02;
        reinterpret_cast<FighterSequenceSpriteCopyView *>(
            &destination->sprite_04)
            ->copy_fighter_sequence_sprite(
                reinterpret_cast<const FighterSequenceSpriteCopyView *>(
                    &record->sprite_04));
    }

    ++live_count_10;
}

} // namespace th105
