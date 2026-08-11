#pragma once

#include "battle/Collision.hpp"

namespace th105 {

struct Yukari : Fighter {
    unsigned char try_dispatch_mirrored_gate_actions_200_201(
        int window_value,
        int action_201_override);
};

} // namespace th105
