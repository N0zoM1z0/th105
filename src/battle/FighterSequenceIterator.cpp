#include "Collision.hpp"

namespace th105 {

extern "C" void __cdecl _invalid_parameter_noinfo(void);

struct FighterSequenceIterator {
    unsigned unknown_00;
    FighterSequenceController *owner_04;
    unsigned absolute_position_08;

    FighterSequenceSlot *dereference_checked();
};

typedef char FighterSequenceIterator_size_must_be_0x0c[
    sizeof(FighterSequenceIterator) == 0x0c ? 1 : -1];

FighterSequenceSlot *FighterSequenceIterator::dereference_checked()
{
    const unsigned position = absolute_position_08;

    if (owner_04 == 0) {
        _invalid_parameter_noinfo();
    }

    if (absolute_position_08 >= owner_04->head_0c + owner_04->live_count_10) {
        _invalid_parameter_noinfo();
    }

    if (owner_04->slot_capacity_08 > position) {
        return owner_04->slots_04[position];
    }
    return owner_04->slots_04[position - owner_04->slot_capacity_08];
}

} // namespace th105
