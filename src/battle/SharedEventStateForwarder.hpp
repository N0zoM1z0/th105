#pragma once

namespace th105 {

// The current roster uses several class-specific views of this unused-receiver
// forwarding ABI.  Keeping the implementation in its own TU is target-backed:
// making the SharedEventState setter definition visible causes VC8 to inline it,
// unlike the linked 1.06a body.
struct SharedEventStateForwarder {
    char set_shared_first_target(char enabled, float target);
    char set_shared_second_target(char enabled, float target);
    char set_shared_third_target(char enabled, float target);
};

} // namespace th105
