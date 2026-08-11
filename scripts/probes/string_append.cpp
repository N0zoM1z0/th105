#include "../../src/assets/String28.hpp"

namespace th105 {

// This wrapper forces VC8 to emit the underlying three-argument append COMDAT.
// Compare the `append` symbol, not this wrapper, with target 0x00408A40.
__declspec(noinline) String28 &emit_string_append(
    String28 &destination,
    const String28 &source,
    unsigned int position,
    unsigned int count)
{
    return destination.append(source, position, count);
}

} // namespace th105
