#include "NetworkSession.hpp"

namespace th105 {

void NetworkSessionState::copy_session_field_6c8_if_unset()
{
    if (unknown_06c0 == 0)
        unknown_06c0 = unknown_06d8;
}

} // namespace th105
