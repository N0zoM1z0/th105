#include "NetworkSession.hpp"

namespace th105 {

void NetworkSessionState::copy_session_field_6c8_if_unset()
{
    if (unknown_06b0 == 0)
        unknown_06b0 = unknown_06c8;
}

} // namespace th105
