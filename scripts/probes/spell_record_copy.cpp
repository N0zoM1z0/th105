#include "../../src/battle/SpellData.hpp"

#include <new>

namespace th105 {

// Force emission of the implicit SpellRecordView copy constructor used by the
// map value and node construction paths.
__declspec(noinline) SpellRecordView *emit_spell_record_copy(
    SpellRecordView *destination,
    const SpellRecordView &source)
{
    return new (destination) SpellRecordView(source);
}

} // namespace th105
