#include "SpellData.hpp"

#include <deque>

namespace th105 {

typedef std::deque<short> NativeShortDeque;

// 0x00430F70 preserves a nullable Side+0x08 payload boundary.  The two
// destination fields are the native 0x14-byte VC8 deque representation; use
// its real assignment rather than a raw-header copy so ownership is retained.
void SpellDataOwner::initialize_side_payload_430f70(
    const ShortDeque8 *payload)
{
    if (payload) {
        *reinterpret_cast<NativeShortDeque *>(&loaded_spell_ids_20) =
            *reinterpret_cast<const NativeShortDeque *>(payload);
        *reinterpret_cast<NativeShortDeque *>(&selection_ids_34) =
            *reinterpret_cast<const NativeShortDeque *>(payload);
    }
}

void SpellDataOwner::set_sequence_mode(unsigned char value)
{
    *reinterpret_cast<NativeShortDeque *>(&selection_ids_34) =
        *reinterpret_cast<const NativeShortDeque *>(&loaded_spell_ids_20);
    if (value != 0)
        shuffle_selection();
}

} // namespace th105
