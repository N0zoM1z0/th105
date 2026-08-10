#include "Collision.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

FighterSequenceSlot *FighterSequenceController::entry_at_checked(int index)
{
    unsigned absolute = head_0c;
    if (absolute > live_count_10 + absolute) {
        _invalid_parameter_noinfo();
    }

    const unsigned original = head_0c;
    const unsigned offset = static_cast<unsigned>(index);
    unsigned end = live_count_10;
    absolute += offset;
    end += original;
    if (absolute > end || absolute < original) {
        _invalid_parameter_noinfo();
    }
    if (absolute >= live_count_10 + head_0c) {
        _invalid_parameter_noinfo();
    }

    if (slot_capacity_08 <= absolute) {
        FighterSequenceSlot **slots = slots_04;
        absolute -= slot_capacity_08;
        return slots[absolute];
    }
    FighterSequenceSlot **slots = slots_04;
    return slots[absolute];
}

} // namespace th105
