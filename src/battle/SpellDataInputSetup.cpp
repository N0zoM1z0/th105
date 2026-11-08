#include "SpellData.hpp"
#include "characters/CharacterSpellResource.hpp"

#include <deque>

namespace th105 {

typedef std::deque<short> NativeShortDeque;

// 0x004324F0 preserves a nullable Side+0x08 payload boundary.  The two
// destination fields are the native 0x14-byte VC8 deque representation; use
// its real assignment rather than a raw-header copy so ownership is retained.
void CharacterSpellResources::initialize_side_payload(
    const ShortDeque8 *payload)
{
    if (payload) {
        loaded =
            *reinterpret_cast<const NativeShortDeque *>(payload);
        selection =
            *reinterpret_cast<const NativeShortDeque *>(payload);
    }
}

void SpellDataOwner::set_sequence_mode(unsigned char value)
{
    selection_ids_34 = loaded_spell_ids_20;
    if (value != 0)
        shuffle_selection();
}

} // namespace th105
