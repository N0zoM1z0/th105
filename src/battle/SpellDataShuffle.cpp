#include "battle/SpellData.hpp"
#include <deque>

namespace th105 {
int __cdecl selector_random_roll(int modulus);
typedef std::deque<short> NativeShortDeque;

// The native single-element erase remains an out-of-line VC8 provider.
// Keep its checked iterator contract; push_front uses the owning deque directly.
struct ShortDequeMutationView {
    unsigned unknown_00;
    short **blocks_04;
    unsigned block_capacity_08;
    unsigned head_0c;
    unsigned live_count_10;

    NativeShortDeque::iterator erase_one(NativeShortDeque::iterator position);
};

typedef char SpellShuffleDequeSize[sizeof(NativeShortDeque) == sizeof(ShortDeque8) ? 1 : -1];
typedef char SpellShuffleMutationSize[sizeof(ShortDequeMutationView) == sizeof(ShortDeque8) ? 1 : -1];

void SpellDataOwner::shuffle_selection()
{
    const unsigned count = selection_ids_34.size();
    if (count != 0) {
        NativeShortDeque &selection = selection_ids_34;
        int remaining = 100;
        do {
            NativeShortDeque::iterator it = selection.begin();
            it += static_cast<unsigned>(selector_random_roll(static_cast<int>(count)));
            const short value = *it;
            ShortDequeMutationView *mutation =
                reinterpret_cast<ShortDequeMutationView *>(&selection);
            mutation->erase_one(it);
            selection.push_front(value);
        } while (--remaining != 0);
    }
}
} // namespace th105
