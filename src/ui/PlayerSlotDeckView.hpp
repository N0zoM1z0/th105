#pragma once

#include <deque>
#include <stddef.h>

namespace th105 {

// Nonowning view of the PlayerSlotRecord deck storage used by copy_deck.
// The shared method is defined in PlayerSlotDeckView.cpp; no view is constructed.
struct PlayerSlotDeckView {
    unsigned char reserved_000[0x1AC];
    std::deque<unsigned short> decks_1ac[20];

    std::deque<unsigned short> *copy_deck(
        std::deque<unsigned short> *output, int index);
};

typedef char PlayerSlotDeckStorageOffset[
    offsetof(PlayerSlotDeckView, decks_1ac) == 0x1AC ? 1 : -1];
typedef char PlayerSlotDeckStorageExtent[
    sizeof(PlayerSlotDeckView) == 0x33C ? 1 : -1];

} // namespace th105
