#include "NetworkSendState.hpp"
#include "NetworkUdpEvent.hpp"

namespace th105 {

class CNetworkBaseCtorDependency {
public:
    CNetworkBaseCtorDependency();
    virtual ~CNetworkBaseCtorDependency();
protected:
    unsigned char reserved_004[0x3b0];
    NetworkSendStateView state_3b4;
    unsigned char reserved_4fc[0x6dc - 0x4fc];
};

class CNetworkServerCtorView : public CNetworkBaseCtorDependency,
                               public INetworkUDPEventProc {
public:
    CNetworkServerCtorView();
    virtual ~CNetworkServerCtorView();
    virtual void on_peer_data(unsigned slot, const void *payload, int size);
    virtual int route_payload(unsigned slot, int *code,
        const unsigned char *payload, int size, void **reply,
        unsigned short *reply_size);
private:
    unsigned char server_tail_6e4[8];
};

class CNetworkClientCtorView : public CNetworkBaseCtorDependency,
                               public INetworkUDPEventProc {
public:
    CNetworkClientCtorView();
    virtual ~CNetworkClientCtorView();
    virtual void on_accepted(unsigned code, const void *payload, unsigned size);
    virtual void on_rejected(unsigned code);
    virtual void on_primary_data(const void *payload, int size);
    virtual void on_peer_data(unsigned slot, const void *payload, int size);
    virtual int route_payload(unsigned slot, int *code,
        const unsigned char *payload, int size, void **reply,
        unsigned short *reply_size);
};

CNetworkServerCtorView::CNetworkServerCtorView()
{
    state_3b4.publish_callback(static_cast<INetworkUDPEventProc *>(this));
}

CNetworkClientCtorView::CNetworkClientCtorView()
{
    state_3b4.publish_callback(static_cast<INetworkUDPEventProc *>(this));
}

extern CNetworkBaseCtorDependency *g_network_session;

CNetworkBaseCtorDependency *__cdecl create_connect_session_43ce00()
{
    CNetworkServerCtorView *session = new CNetworkServerCtorView;
    g_network_session = session;
    return session;
}

CNetworkBaseCtorDependency *__cdecl create_connect_client_43ce80()
{
    CNetworkClientCtorView *session = new CNetworkClientCtorView;
    g_network_session = session;
    return session;
}

typedef char NetworkBaseCtorDependency_size[
    sizeof(CNetworkBaseCtorDependency) == 0x6dc ? 1 : -1];
typedef char NetworkSecondaryCtorView_size[
    sizeof(INetworkUDPEventProc) == 8 ? 1 : -1];
typedef char NetworkServerCtorView_size[
    sizeof(CNetworkServerCtorView) == 0x6ec ? 1 : -1];
typedef char NetworkClientCtorView_size[
    sizeof(CNetworkClientCtorView) == 0x6e4 ? 1 : -1];

} // namespace th105
