#include "PlayerSlotDeckView.hpp"

namespace th105 {


std::deque<unsigned short> *PlayerSlotDeckView::copy_deck(
    std::deque<unsigned short> *output,
    int index)
{
    if (output != 0)
        *output = decks_1ac[index];
    return &decks_1ac[index];
}

} // namespace th105
