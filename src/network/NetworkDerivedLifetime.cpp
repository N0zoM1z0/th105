#include "NetworkSendState.hpp"

namespace th105 {

class CNetworkBaseLifetimeView {
public:
    virtual ~CNetworkBaseLifetimeView();
protected:
    unsigned char reserved_004[0x3B0];
    NetworkSendStateView state_3b4;
    unsigned char reserved_4fc[0x6DC - 0x4FC];
};

class NetworkSecondaryInterfaceView {
public:
    virtual void network_secondary_slot_0();

    int state_04;
};

class CNetworkServerLifetimeView : public CNetworkBaseLifetimeView, public NetworkSecondaryInterfaceView {
public:
    virtual ~CNetworkServerLifetimeView();
};

class CNetworkClientLifetimeView : public CNetworkBaseLifetimeView, public NetworkSecondaryInterfaceView {
public:
    virtual ~CNetworkClientLifetimeView();
};

CNetworkServerLifetimeView::~CNetworkServerLifetimeView()
{
    state_3b4.publish_callback(0);
}

CNetworkClientLifetimeView::~CNetworkClientLifetimeView()
{
    state_3b4.publish_callback(static_cast<NetworkSecondaryInterfaceView *>(this));
}

typedef char Base_size[sizeof(CNetworkBaseLifetimeView)==0x6DC?1:-1];
typedef char Server_size[sizeof(CNetworkServerLifetimeView)==0x6E4?1:-1];
}
