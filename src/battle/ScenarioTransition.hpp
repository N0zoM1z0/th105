#pragma once

#include "assets/String28.hpp"

namespace th105 {

// Narrow receiver view shared by the battle controller transition/reset
// paths.  The target passes the phase block in ECX for both calls.
struct ScenarioTransitionView {
    signed char consume_transition_code_458d90();
    unsigned char dispatch_owned_string_458e80(String28 value);
};

} // namespace th105
