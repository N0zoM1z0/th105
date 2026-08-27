#include "../../src/battle/EffectSprite.hpp"

#include <deque>

namespace th105 {

struct FighterSequenceSlotGenerated {
    short record_id_00;
    unsigned short field_02;
    CSprite sprite_04;
};

typedef char FighterSequenceSlotGenerated_size_must_be_0x98[
    sizeof(FighterSequenceSlotGenerated) == 0x98 ? 1 : -1];

typedef std::deque<FighterSequenceSlotGenerated> FighterSequenceDequeGenerated;

void probe_fighter_sequence_deque_push(
    FighterSequenceDequeGenerated &items,
    const FighterSequenceSlotGenerated &value)
{
    items.push_back(value);
}

FighterSequenceDequeGenerated::iterator probe_fighter_sequence_deque_erase_range(
    FighterSequenceDequeGenerated &items,
    FighterSequenceDequeGenerated::iterator first,
    FighterSequenceDequeGenerated::iterator last)
{
    return items.erase(first, last);
}

void probe_fighter_sequence_deque_lifetime()
{
    FighterSequenceDequeGenerated items;
}

} // namespace th105
