#include "NetworkSendState.hpp"
namespace th105 {

int NetworkSendStateView::status()
{
    return status_144;
}

struct NetworkReplayStorage {
    void tidy();
};

class NetworkReplayBufferView {
public:
    void reset_428b70();
};

void NetworkReplayBufferView::reset_428b70()
{
    reinterpret_cast<NetworkReplayStorage *>(
        reinterpret_cast<unsigned char *>(this) + 0x3c)->tidy();
}

} // namespace th105
