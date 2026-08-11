#pragma once

#include <string>

namespace th105 {

// The target uses this exact VC8 checked-string specialization.  Keeping the
// real owning type preserves its 16-byte SSO threshold, copy/EH behavior, and
// template code generation.
typedef std::string String28;

typedef char String28_size_must_be_0x1c[
    sizeof(String28) == 0x1c ? 1 : -1];

} // namespace th105
