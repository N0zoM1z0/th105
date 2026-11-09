#pragma once

#include "battle/PatResourceContracts.hpp"
#include <map>

namespace th105 {

// The PAT loader and animation sequence readers share these signed-key groups.
typedef std::map<int, PatGroup *> CommandGateMap;

typedef char CommandGateGroupWindowOffset[
    offsetof(PatGroup, field_10) == 0x10 ? 1 : -1];

} // namespace th105
