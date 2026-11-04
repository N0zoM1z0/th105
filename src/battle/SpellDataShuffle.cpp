#include "battle/SpellData.hpp"
#include <deque>

namespace th105 {
int __cdecl selector_random_roll(int modulus);
typedef std::deque<short> NativeShortDeque;

// Declaration-only ABI view for the observed out-of-line VC8 deque methods.
// The actual checked iterator and owning deque layout are retained.
struct ShortDequeMutationView {
    unsigned unknown_00;
    short **blocks_04;
    unsigned block_capacity_08;
    unsigned head_0c;
    unsigned live_count_10;

    NativeShortDeque::iterator erase_one(NativeShortDeque::iterator position);
    void push_front(const short &value);
};

typedef char SpellShuffleDequeSize[sizeof(NativeShortDeque) == sizeof(ShortDeque8) ? 1 : -1];
typedef char SpellShuffleMutationSize[sizeof(ShortDequeMutationView) == sizeof(ShortDeque8) ? 1 : -1];

void SpellDataOwner::shuffle_selection()
{
    const unsigned count = selection_ids_34.live_count_10;
    if (count != 0) {
        NativeShortDeque &selection =
            *reinterpret_cast<NativeShortDeque *>(&selection_ids_34);
        int remaining = 100;
        do {
            NativeShortDeque::iterator it = selection.begin();
            it += static_cast<unsigned>(selector_random_roll(static_cast<int>(count)));
            const short value = *it;
            ShortDequeMutationView *mutation =
                reinterpret_cast<ShortDequeMutationView *>(&selection);
            mutation->erase_one(it);
            mutation->push_front(value);
        } while (--remaining != 0);
    }
}
} // namespace th105
