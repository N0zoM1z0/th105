// Compiler-origin witness, not a gameplay wrapper or accepted caller.
// Reuse the independently exact real card/sprite lifetime and original VC8 deque.
#include "battle/FighterSequenceRotate.cpp"
namespace th105 {
typedef std::deque<SequenceRotateCard> SequenceCardDeque;
SequenceCardDeque::iterator probe_sequence_card_erase_range(
    SequenceCardDeque &cards, SequenceCardDeque::iterator first,
    SequenceCardDeque::iterator last)
{
    return cards.erase(first, last);
}
}
