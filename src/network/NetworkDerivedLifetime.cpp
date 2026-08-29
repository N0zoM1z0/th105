namespace th105 {

struct NetworkCleanupView {
    void cleanup(void *peer);
};

class CNetworkBaseLifetimeView {
public:
    virtual ~CNetworkBaseLifetimeView();
protected:
    unsigned char reserved_004[0x3B0];
    NetworkCleanupView cleanup_3b4;
    unsigned char reserved_3b5[0x6DC - 0x3B5];
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
    cleanup_3b4.cleanup(0);
}

CNetworkClientLifetimeView::~CNetworkClientLifetimeView()
{
    cleanup_3b4.cleanup(static_cast<NetworkSecondaryInterfaceView *>(this));
}

typedef char Base_size[sizeof(CNetworkBaseLifetimeView)==0x6DC?1:-1];
typedef char Server_size[sizeof(CNetworkServerLifetimeView)==0x6E4?1:-1];
}
