#include "NetworkSendState.hpp"
#include "NetworkUdpEvent.hpp"

namespace th105 {

class CNetworkBaseLifetimeView {
public:
    virtual ~CNetworkBaseLifetimeView();
protected:
    unsigned char reserved_004[0x3B0];
    NetworkSendStateView state_3b4;
    unsigned char reserved_4fc[0x6DC - 0x4FC];
};

class CNetworkServerLifetimeView : public CNetworkBaseLifetimeView, public INetworkUDPEventProc {
public:
    virtual ~CNetworkServerLifetimeView();
    virtual void on_peer_data(unsigned slot, const void *payload, int size);
    virtual int route_payload(unsigned slot, int *code,
        const unsigned char *payload, int size, void **reply,
        unsigned short *reply_size);
private:
    unsigned char server_tail_6e4[8];
};

class CNetworkClientLifetimeView : public CNetworkBaseLifetimeView, public INetworkUDPEventProc {
public:
    virtual ~CNetworkClientLifetimeView();
    virtual void on_accepted(unsigned code, const void *payload, unsigned size);
    virtual void on_rejected(unsigned code);
    virtual void on_primary_data(const void *payload, int size);
    virtual void on_peer_data(unsigned slot, const void *payload, int size);
    virtual int route_payload(unsigned slot, int *code,
        const unsigned char *payload, int size, void **reply,
        unsigned short *reply_size);
};

CNetworkServerLifetimeView::~CNetworkServerLifetimeView()
{
    state_3b4.publish_callback(0);
}

CNetworkClientLifetimeView::~CNetworkClientLifetimeView()
{
    state_3b4.publish_callback(static_cast<INetworkUDPEventProc *>(this));
}

typedef char Base_size[sizeof(CNetworkBaseLifetimeView)==0x6DC?1:-1];
typedef char Server_size[sizeof(CNetworkServerLifetimeView)==0x6EC?1:-1];
typedef char Client_size[sizeof(CNetworkClientLifetimeView)==0x6E4?1:-1];
}
