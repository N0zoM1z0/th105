#include <deque>

namespace th105 {

struct PlayerSlotDeckView {
    unsigned char reserved_000[0x1AC];
    std::deque<unsigned short> decks_1ac[20];

    std::deque<unsigned short> *copy_deck(
        std::deque<unsigned short> *output,
        int index);
};

std::deque<unsigned short> *PlayerSlotDeckView::copy_deck(
    std::deque<unsigned short> *output,
    int index)
{
    if (output != 0)
        *output = decks_1ac[index];
    return &decks_1ac[index];
}

} // namespace th105
