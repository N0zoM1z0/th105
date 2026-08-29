#include "../ui/Title.hpp"

namespace th105 {

struct NetworkShutdownStateView {
    void shutdown_412fd0();
};

class CNetworkBase {
public:
    virtual ~CNetworkBase();

    unsigned char reserved_004[0x274];
    unsigned int texture_278;
    unsigned char reserved_27c[0x138];
    NetworkShutdownStateView shutdown_state_3b4;
};

extern CNetworkBase *g_network_session;

extern "C" void __cdecl clear_network_session()
{
    if (g_network_session == 0)
        return;

    NetworkShutdownStateView *shutdown_state =
        &g_network_session->shutdown_state_3b4;
    CNetworkBase *session = g_network_session;
    shutdown_state->shutdown_412fd0();
    g_title_resource_manager.release_title_resource_handle(
        session->texture_278);
    delete g_network_session;
    g_network_session = 0;
}

} // namespace th105
