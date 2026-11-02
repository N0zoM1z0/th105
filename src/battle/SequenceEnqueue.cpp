#include "Collision.hpp"
#include "SpellRuntime.hpp"
#include <new>

namespace th105 {

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
    new (destination) FighterSequenceSlot(*record);

    ++live_count_10;
}

} // namespace th105
