#include "MenuConnectStateRuntime.hpp"

namespace th105 {

extern const ConnectKey16 g_connect_key;

ConnectKey16 __cdecl get_connect_key_43aba0()
{
    return g_connect_key;
}

} // namespace th105
